/*! \file pm_smps_driver.c
*  \n
*  \brief This file contains SMPS peripheral driver initialization during which the driver
*         driver data is stored. 
*  \n   
*  \n &copy; Copyright 2012-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/smps/src/pm_smps_driver.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/04/17   aab     Optimized driver for better mem usage
10/27/17   aab     Added support for new regualtor Mode 
11/12/17   aab     Moved common Register address defination to driver file  
11/03/15   al      Updated rails API
07/10/15   al      Adding support for HP type
12/06/14   al      Porting optimization changes
07/16/14   akm     Comm change Updates
03/31/14   akm     Updated to the latest PMIC driver architecture   
12/06/12   hw      Rearchitecturing module driver to peripheral driver
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_smps_driver.h"
#include "pm_target_information.h"
#include "pm_version.h"
#include "device_info.h"

/*===========================================================================

                        STATIC VARIABLES 

===========================================================================*/
#define PM_HF_VPWM_PMIC5_DIG_MAJ_VER 0x03

enum {
  PMIC_BUCK_FTS_MAX_HW_VER = 0x20,
  PMIC_BUCK_HF_MAX_HW_VER  = 0x60,
};

/* Static global variable to store the SMPS driver data */
static pm_smps_data_type *pm_smps_data_arr[PM_MAX_NUM_PMICS];

static pm_pwr_register_info_type smps_reg =
{
    .peripheral_offset = 0x300, 
    .STATUS            = 0x008,
    .STATUS2           = 0x009, 
    .STATUS3           = 0x000,
    .STATUS4           = 0x00B,
    .ULS_VSET_LB       = 0x039,
    .AHC_CTL1_HR       = 0x031,
    .AHC_CTL           = 0x033,
    .VOLTAGE_CTRL1     = 0x040, 
    .VOLTAGE_CTRL2     = 0x041,
    .VSET_VALID_LB     = 0x042, 
    .VSET_VALID_UB     = 0x043, 
    .MODE_CTL          = 0x045, 
    .EN_CTL            = 0x046,  
    .FOLLOW_HWEN       = 0x047,
    .CLK_DIV           = 0x050, 
    .QM_MODE           = 0x051,
    .QM_PS_ENTRY       = 0x063,
    .PMIC4_ULS_VSET_LB = 0x068, 
    .QM_PS_EXIT        = 0x06B, 
    .OCP               = 0x088,
    .OCP_CTL2          = 0x089,
    .BROADCAST_CFG     = 0x08B, 
    .PD_CTL            = 0x0A0, 
    .GANG_CTL1         = 0x0C0,    
    .ECM_EN_CTL        = 0x000, 
    .VOUT_EXT_CTRL1_LB = 0x000, 
    .RGB_HR_VOUT_MAX   = 0x000
};


/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/


/*===========================================================================

                     INTERNAL DRIVER FUNCTIONS 

===========================================================================*/

void pm_smps_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index)
{
    pm_smps_data_type *smps_ptr = NULL;
    uint16 smps_index = 0;
    pm_register_address_type base_address = 0;
    pm_register_address_type periph_offset = 0;
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_register_address_type reg = 0x0;
    pm_register_data_type max_volt[2] = {0};
    uint8 num_of_peripherals = 0;
    uint8 dig_maj_min_ver = 0;
  
    dig_maj_min_ver = ((peripheral_info->digital_major_version << 4) | peripheral_info->digital_minor_version);

    // Initialize the driver for CTL peripheral subtypes only and return in other cases
    switch(peripheral_info->peripheral_type)
    {
      case PM_HW_MODULE_FTS:
        switch(peripheral_info->peripheral_subtype)
        {
          case PM_HW_MODULE_FTS__FTS_CTL:
          case PM_HW_MODULE_FTS__FTS2p5_CTL:
          case PM_HW_MODULE_FTS__FTS426_CTL:
          case PM_HW_MODULE_FTS__FTS510_CTL:
          case PM_HW_MODULE_FTS__FTS520_CTL:
          case PM_HW_MODULE_FTS__FTS525_CTL:
          case PM_HW_MODULE_FTS__FTS526_CTL:
            CORE_VERIFY (dig_maj_min_ver <= PMIC_BUCK_FTS_MAX_HW_VER);
            break;
          default:
            return;
        }
        break;
      case PM_HW_MODULE_HF_BUCK:
        switch(peripheral_info->peripheral_subtype)
        {
          case PM_HW_MODULE_HF_BUCK_GP_CTL:
          case PM_HW_MODULE_HF_BUCK_RF_CTL:
          case PM_HW_MODULE_HF_BUCK_VPWM_CTL:
            CORE_VERIFY (dig_maj_min_ver <= PMIC_BUCK_HF_MAX_HW_VER);
            break;
          default:
            return;
        }
        break;
      case PM_HW_MODULE_ULT_BUCK:
        switch(peripheral_info->peripheral_subtype)
        {
          case PM_HW_MODULE_ULT_BUCK_CTL_LV:
          case PM_HW_MODULE_ULT_BUCK_CTL2:
          case PM_HW_MODULE_ULT_BUCK_CTL3:
          case PM_HW_MODULE_ULT_BUCK_CTL_MV:
            break;
          default:
            return;
        }
        break;
      default:
        return;
    }

    smps_ptr = pm_smps_data_arr[pmic_index];


    if (smps_ptr == NULL)
    {
        num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_SMPS_NUM, pmic_index);
        
        if (num_of_peripherals == 0)
        {
            return;
        }

        pm_malloc( sizeof(pm_smps_data_type), (void**)&smps_ptr);

        /* Assign Comm ptr */
        smps_ptr->comm_ptr = comm_ptr;

        /* SMPS Register Info - Obtaining Data through dal config */
        smps_ptr->pm_pwr_data.pwr_reg_table = &smps_reg;

        CORE_VERIFY_PTR(smps_ptr->pm_pwr_data.pwr_reg_table);

        smps_ptr->pm_pwr_data.base_address = peripheral_info->base_address;

        smps_ptr->pm_pwr_data.num_of_peripherals = num_of_peripherals;

        /* SMPS pwr rail specific info pointer malloc to save all the peripheral's base address, Type, Range and Vset */
        pm_malloc(sizeof(pm_pwr_specific_info_type)*(smps_ptr->pm_pwr_data.num_of_peripherals), (void**)&(smps_ptr->pm_pwr_data.pwr_specific_info));

        CORE_VERIFY_PTR(smps_ptr->pm_pwr_data.pwr_specific_info);

        /* Save first SMPS peripheral's base address */
        smps_ptr->pm_pwr_data.pwr_specific_info[0].periph_base_address = peripheral_info->base_address;

        pm_smps_data_arr[pmic_index] = smps_ptr;
    }

    if (smps_ptr != NULL)
    {
        base_address = smps_ptr->pm_pwr_data.pwr_specific_info[0].periph_base_address;
        periph_offset = smps_ptr->pm_pwr_data.pwr_reg_table->peripheral_offset;

        /* Peripheral Baseaddress should be >= first peripheral's base addr */
        CORE_VERIFY(peripheral_info->base_address >= base_address);

        /* Calculate SMPS peripheral index */
        smps_index = ((peripheral_info->base_address - base_address)/periph_offset);

        /* Peripheral Index should be less than number of peripherals */
        CORE_VERIFY(smps_index < (smps_ptr->pm_pwr_data.num_of_peripherals));

        /* Save SMPS's Peripheral Type value */
        smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].periph_type = peripheral_info->peripheral_type;

        /* Save each SMPS peripheral's base address */
        smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].periph_base_address = peripheral_info->base_address;

        if (((smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].periph_type == PM_HW_MODULE_HF_BUCK) && 
                    (peripheral_info->peripheral_subtype >= PM_HW_MODULE_HF_BUCK_VPWM_CTL)) || 
                ((smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].periph_type == PM_HW_MODULE_FTS) && 
                 (peripheral_info->peripheral_subtype >= PM_HW_MODULE_FTS__FTS426_CTL)))
        {
            /* Flag this rail peripheral as unified register map peripheral */
            smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].is_periph_unified_reg = TRUE;
            smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].is_ret_present = TRUE;  //Retention is supported

            //Since SMPS peripheral subtype of old/new PMICs is the same, we are using Dig major ver to differentate PMICs that supports new Mode reg bit definatin
            if ( (peripheral_info->peripheral_type == PM_HW_MODULE_FTS ) && 
                    (peripheral_info->peripheral_subtype >= PM_HW_MODULE_FTS__FTS510_CTL) )
            {
                smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].pmic4_flag = FALSE;
                reg = (pm_register_address_type)(peripheral_info->base_address + smps_ptr->pm_pwr_data.pwr_reg_table->ULS_VSET_LB);
            }
            else if ((peripheral_info->peripheral_type == PM_HW_MODULE_HF_BUCK ) && 
                    (peripheral_info->peripheral_subtype >= PM_HW_MODULE_HF_BUCK_VPWM_CTL))
            {
                smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].pmic4_flag = FALSE;
                reg = (pm_register_address_type)(peripheral_info->base_address + smps_ptr->pm_pwr_data.pwr_reg_table->ULS_VSET_LB);

                if( (peripheral_info->peripheral_subtype == PM_HW_MODULE_HF_BUCK_VPWM_CTL) &&
                        (peripheral_info->digital_major_version < PM_HF_VPWM_PMIC5_DIG_MAJ_VER) ) 
                {
                    smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].pmic4_flag = TRUE;
                    reg = (pm_register_address_type)(peripheral_info->base_address + smps_ptr->pm_pwr_data.pwr_reg_table->PMIC4_ULS_VSET_LB);
                }
            }
            else
            {
                smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].pmic4_flag = TRUE;
                reg = (pm_register_address_type)(peripheral_info->base_address + smps_ptr->pm_pwr_data.pwr_reg_table->PMIC4_ULS_VSET_LB);
            }

            /* Read current SMPS's upper limit voltage value and save it */
            err_flag = pm_comm_read_byte_array(smps_ptr->comm_ptr->slave_id, reg, 2, max_volt);
            CORE_VERIFY (err_flag == PM_ERR_FLAG_SUCCESS);

            /* SMPS Vset Info - 1mV step for HT rails */
            smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].pwr_vset.RangeMin = 0;
            smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].pwr_vset.RangeMax = ((max_volt[1]<<8) | (max_volt[0]))*1000;
            smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].pwr_vset.VStep = 1000; 
        }
        else
        {
           CORE_VERIFY(0); //Abort
        }

        smps_ptr->pm_pwr_data.pwr_specific_info[smps_index].is_periph_stepper = TRUE;
    }
}



pm_smps_data_type* pm_smps_get_data(uint8 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS) 
  {
      return pm_smps_data_arr[pmic_index];
  }

    return NULL;
}

uint8 pm_smps_get_num_peripherals(uint8 pmic_index)
{
  if((pmic_index < PM_MAX_NUM_PMICS) && 
  	  (pm_smps_data_arr[pmic_index] != NULL))
  {
      return pm_smps_data_arr[pmic_index]->pm_pwr_data.num_of_peripherals;
  }

  return 0;
}

