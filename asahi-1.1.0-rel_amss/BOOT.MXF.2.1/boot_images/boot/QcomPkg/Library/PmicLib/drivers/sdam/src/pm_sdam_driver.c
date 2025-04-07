/*! \file pm_sdam_driver.c
*  \n
*  \brief SDAM driver initialization.
*  \n
*  \n &copy; Copyright 2018-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
                            Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/sdam/src/pm_sdam_driver.c#1 $

$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/24/18   rl      Created
========================================================================== */
/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_sdam_driver.h"
#include "CoreVerify.h"
#include "pm_log_utils.h"
#include "hw_module_type.h"
#include "pm_device.h"

/*===========================================================================

                         DEFINITIONS

===========================================================================*/

#define REG_SDAM(reg) ((sdam_ptr->base_address)     \
    + ((sdam_index)*(sdam_ptr->sdam_reg_table->peripheral_offset))  \
    +  (sdam_ptr->sdam_reg_table->reg))

#define SLAVE_SDAM sdam_ptr->comm_ptr->slave_id

#define SDAM_SIZE_MULTIPLIER 32

#define PMIC_SDAM_MAX_HW_VER 0x10

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the sdam data */
static pm_sdam_data_type *pm_sdam_data_arr[PM_MAX_NUM_PMICS];

static boolean sdam_initialized = FALSE;

static pm_sdam_reg_info_type sdam_reg =
{
  .peripheral_offset = 0x100,
  .mem_start         = 0x0040,
  .trig_arg          = 0x0042,
  .trig_busy_ret     = 0x0043,
  .sdam_size         = 0x0044,
  .trig_set          = 0x00E5,
  .trig_clr          = 0x00E6,
};



/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void
pm_sdam_driver_init(pm_comm_info_type *comm_ptr,
                    peripheral_info_type *peripheral_info,
                    uint32 pmic_index)
{
  pm_sdam_data_type *sdam_ptr = NULL; 
  uint8 sdam_index = 0, num_of_periph = 0;
  static DALSYSSyncHandle sync_handle_copy;

  if(sdam_initialized == TRUE)
  {
    return;
  }
  if(comm_ptr == NULL || peripheral_info == NULL)
  {
    CORE_VERIFY_PTR(0);
  }

  sdam_ptr = pm_sdam_data_arr[pmic_index];

  if(sdam_ptr == NULL)
  {
    num_of_periph = pm_target_information_get_periph_count_info(PM_PROP_SDAM_NUM, pmic_index);

    if (!num_of_periph)
    {
      return;
    }

    pm_malloc(sizeof(pm_sdam_data_type), (void**)&(sdam_ptr));
    CORE_VERIFY_PTR(sdam_ptr);
    
    sdam_ptr->base_address = peripheral_info->base_address;
    
    sdam_index = PM_SDAM_1 ;
    
    sdam_ptr->dig_maj_min_ver = ((peripheral_info->digital_major_version << 4) | 
                                 peripheral_info->digital_minor_version);

    CORE_VERIFY (sdam_ptr->dig_maj_min_ver <= PMIC_SDAM_MAX_HW_VER);

    /* Assign Comm ptr */
    sdam_ptr->comm_ptr = comm_ptr;

    /* SDAM Register Info */
    sdam_ptr->sdam_reg_table = &sdam_reg;

    if(sdam_ptr->sdam_reg_table == NULL)
    {
      CORE_VERIFY_PTR(0);
    }

    sdam_ptr->num_of_periph = num_of_periph;

    /* Allocate memory to store sdam size */
    pm_malloc((sizeof(uint32) * sdam_ptr->num_of_periph),
              (void**)&(sdam_ptr->sdam_mem_size));
    
    if(sync_handle_copy == NULL)
    {
      if( DAL_SUCCESS !=
          DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE,
          &(sdam_ptr->sdam_dal_sync_handle), NULL) )
      {
        CORE_VERIFY_PTR(0);
      }

      sync_handle_copy = sdam_ptr->sdam_dal_sync_handle;
    }
    else
    {
      sdam_ptr->sdam_dal_sync_handle = sync_handle_copy;
    }

    /* Get size of sdam memory */
    pm_comm_read_byte(SLAVE_SDAM, REG_SDAM(sdam_size),
                      (uint8*)(&(sdam_ptr->sdam_mem_size[sdam_index])));

    /* WA for detection and initialization; To be removed */
    if(sdam_ptr->sdam_mem_size[sdam_index] == 0)
    {
      sdam_ptr->sdam_mem_size[sdam_index] = 4;
    }
    /* End of WA */
    
    sdam_ptr->sdam_mem_size[sdam_index] *= SDAM_SIZE_MULTIPLIER;

    pm_sdam_data_arr[pmic_index] = sdam_ptr;
  }
  else
  {
    /* If already initialized for this pmic do not reinitialize but get the size
    * size of memory associated with peripheral and store the information
    */
    /* Get size of sdam memory */
    sdam_index = (peripheral_info->base_address - sdam_ptr->base_address)/sdam_reg.peripheral_offset;
    if((sdam_ptr->sdam_mem_size != NULL) && (sdam_index <= sdam_ptr->num_of_periph))
    {
      pm_comm_read_byte(SLAVE_SDAM, REG_SDAM(sdam_size),
                        (uint8*)(&(sdam_ptr->sdam_mem_size[sdam_index])));
    }
    else
    {
      CORE_VERIFY_PTR(0);
    }

    /* WA for detection and initialization; To be removed */
    if(sdam_ptr->sdam_mem_size[sdam_index] == 0)
    {
      sdam_ptr->sdam_mem_size[sdam_index] = 4;
    }
    /* End of WA */
    
    sdam_ptr->sdam_mem_size[sdam_index] *= SDAM_SIZE_MULTIPLIER;
  }

  return;
}

pm_err_flag_type
pm_sdam_driver_self_init(void)
{
  uint32 slave_id = 0, num_of_sdam = 0;
  peripheral_info_type peripheral_info;
  pm_comm_info_type* comm_info = NULL;
  pm_register_address_type* sdam_base_address_list_ptr = NULL;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS, err_sid = PM_ERR_FLAG_SUCCESS;
  uint32 *num_of_sdam_pmics = NULL;

  if(sdam_initialized)
  {
    return err_flag;
  }
  err_flag |= pm_device_setup();

  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    CORE_VERIFY(0);
  }

  if((FALSE == pm_target_information_initialized()) || (FALSE == pm_comm_initialized()))
  {
    return PM_ERR_FLAG_FAILURE;
  }

  sdam_base_address_list_ptr =
    (pm_register_address_type *)pm_target_information_get_specific_info(PM_PROP_SDAM_ADDR_DATA);

  num_of_sdam_pmics = (uint32 *)pm_target_information_get_specific_info(PM_PROP_SDAM_PMICS_NUM);

  if((sdam_base_address_list_ptr == NULL) || (num_of_sdam_pmics == NULL))
  {
     CORE_VERIFY(0);
  }

  for(uint8 i = 0; i < *num_of_sdam_pmics; i++)
  {
    err_sid = pm_get_slave_id(i, 0, &slave_id);
    if(err_sid != PM_ERR_FLAG_SUCCESS)
    {
      continue;
    }

    num_of_sdam = pm_target_information_get_periph_count_info(PM_PROP_SDAM_NUM, i);

    if(num_of_sdam == 0 || sdam_base_address_list_ptr[i] == 0)
    {
      continue;
    }

    for(uint8 j = 0; j < num_of_sdam; j++)
    {
      memset(&peripheral_info, 0, sizeof(peripheral_info_type));

      comm_info = pm_comm_get_comm_info(PM_SPMI_BUSID_0, i, 0);
      if(comm_info == NULL)
      {
        CORE_VERIFY(0);
      }

      peripheral_info.base_address = (sdam_base_address_list_ptr[i]) +
                                     (j * sdam_reg.peripheral_offset);

      err_flag = pm_target_information_read_peripheral_rev(comm_info,
                                                           &peripheral_info);
      
      //SDAM peripheral not accessible discard
      if(err_flag != PM_ERR_FLAG_SUCCESS)
      {
        err_flag = PM_ERR_FLAG_SUCCESS;
        continue;
      }

      //This has to be an SDAM peripheral otherwise there is a data flaw.
      if((pm_hw_module_type)peripheral_info.peripheral_type != PM_HW_MODULE_SDAM)
      {
        CORE_VERIFY(0);
      }
      else
      {
        pm_sdam_driver_init(comm_info, &peripheral_info, i);
      }
    }
  }

  sdam_initialized = TRUE;

  return err_flag;
}

pm_sdam_data_type*
pm_sdam_get_data(uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  err_flag = pm_sdam_driver_self_init();

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    CORE_VERIFY(0);
  }

  if(pmic_index < PM_MAX_NUM_PMICS)
  {
    return pm_sdam_data_arr[pmic_index];
  }
  return NULL;
}


uint8
pm_sdam_get_num_periph(uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  err_flag = pm_sdam_driver_self_init();

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    CORE_VERIFY(0);
  }

  if( (pmic_index < PM_MAX_NUM_PMICS) &&
      (pm_sdam_data_arr[pmic_index] != NULL))
  {
    return pm_sdam_data_arr[pmic_index]->num_of_periph;
  }

  return 0;
}

