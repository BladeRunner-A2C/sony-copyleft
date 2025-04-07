/*! \file pm_rpmh_target.c
*  \n
*  \brief This file contains PMIC functions to run sleep enter and sleep exit settings.
*  \n
*  &copy; Copyright 2013-2018 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/dev/aop.ho/5.0/parasv.aop.ho.5.0.lanai_pmic_stubs_verification/aop_proc/core/pmic/pm/target/kailua/src/init/pm_rpmh_target_init.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/10/15    kt      Initial version.
05/04/23    arua    Palawan Pmic Stub
08/18/23    arua    PGA R5_4 L3C Changes
04/10/23    arua    APC Detection Removal
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "CoreVerify.h"
#include "pm_comm.h"
#include "pm_target_information.h"
#include "pm_rpmh_target.h"
#include "pm_config.h"
#include "pm_config_target.h"
//#include "pm_prm_init.h"
#include "pm_rpmh.h"
#include "pm_vrm.h"
#include "ChipInfo.h"
#include "pm_config_interface.h"
#include "aop_settings.h"

/*===========================================================================

                 LOCAL CONSTANT AND MACRO DEFINITIONS

===========================================================================*/
#define PMICA_INDEX  0  //PMIC index for A pmic
#define PMICB_INDEX  1  //PMIC index for B pmic
#define PMICC_INDEX  2  //PMIC index for C pmic
#define PMICD_INDEX  3  //PMIC index for D pmic
#define PMICE_INDEX  4  //PMIC index for E pmic
#define PMICI_INDEX  8  //PMIC index for I pmic

#define SMPS_BASE_ADDR         0x1400
#define SMPS_ADDR_OFFSET       0x300
#define SMPS_PERPH_TYPE_OFFSET 0x4
#define LDO_BASE_ADDR         0x4000
#define LDO_ADDR_OFFSET       0x100
#define BOB_BASE_ADDR         0xA000
#define BOB_ADDR_OFFSET       0x100
#define CLK_BASE_ADDR         0x5000
#define CLK_ADDR_OFFSET       0x100
#define SDAM1_MEM108_ADDR     0x70AC
#define SDAM1_MEM110_ADDR     0x70AE
#define AZURA_SLAVE_ID        0x0
#define RAIL_INDEX_1          0
#define RAIL_INDEX_3          2
#define RAIL_INDEX_5          4

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

static volatile boolean g_pm_stub_pmic_type = FALSE;
uint32 lanai_humu_rev_id = 0; // TODO - Remove dependency in target_main.c

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/

/**
 * @name pm_rpmh_sleep_init
 *
 * @brief Initializes the sleep settings LUT.
 *
 * @param  sleep_mode: can be vdd_min/XO shutdown
 *
 * @return None.
 *
 * @sideeffects None.
 *
 * @sideeffects Sleep settings should be available in config.
 *
 */
__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_rpmh_sleep_init()
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    return err_flag;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_rpmh_platform_pre_init(void)
{
   pm_register_data_type chrome = 0;
   pm_register_data_type apc4phase = 0;
   pm_register_data_type hamilton = 0;
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   
   pm_vrm_vreg_rail_info_type** rail_info = NULL;
   pm_vrm_vreg_rail_info_type* pm_rail_info = NULL;

/* Read sdam1.mem108 to identify Hamilton vs Moselle */
   err_flag = pm_comm_read_byte(AZURA_SLAVE_ID, SDAM1_MEM108_ADDR, &hamilton, 0);
   CORE_VERIFY(err_flag == PM_ERR_FLAG_SUCCESS);
/*sdam1.mem108 decode: 1 -> Hamilton , 2-> Moselle */
   if(hamilton==1)
   {
        rail_info = (pm_vrm_vreg_rail_info_type**)pm_target_information_get_specific_info(PM_PROP_SMPS_RAIL);
        CORE_VERIFY_PTR(rail_info);
         
        pm_rail_info = (pm_vrm_vreg_rail_info_type*)set_ddr_access((uint64_t)rail_info[PMICE_INDEX]);
        CORE_VERIFY_PTR(pm_rail_info);
        /* for hamilton S3E Min is 806 Max is 1003, Drv Owner is WLANBB*/
        pm_rail_info[RAIL_INDEX_3].MinVoltage = 806;
        pm_rail_info[RAIL_INDEX_3].MaxVoltage = 1003;
        pm_rail_info[RAIL_INDEX_3].DrvOwnMask = PM_DRV_WLANBB;
        pm_rail_info[RAIL_INDEX_3].MinMode = PM_RET_MODE_VAL;
   }

/* Read sdam1.mem110 to identify mobile vs chrome */
   err_flag = pm_comm_read_byte(AZURA_SLAVE_ID, SDAM1_MEM110_ADDR, &chrome, 0);
   CORE_VERIFY(err_flag == PM_ERR_FLAG_SUCCESS);
/*sdam1.mem110 decode: 0 -> mobile(DMIC) , 1-> chrome(EEPROM, QET, QPM) */

   if(chrome)
   {
        rail_info = (pm_vrm_vreg_rail_info_type**)pm_target_information_get_specific_info(PM_PROP_SMPS_RAIL);
        CORE_VERIFY_PTR(rail_info);
         
        pm_rail_info = (pm_vrm_vreg_rail_info_type*)set_ddr_access((uint64_t)rail_info[PMICB_INDEX]);
        CORE_VERIFY_PTR(pm_rail_info);
        /* for chrome S1B Min voltage to 1880  */
        pm_rail_info[RAIL_INDEX_1].MinVoltage = 1880;
   }
   
   return err_flag;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_rpmh_platform_init(void)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

   return err_flag;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_rpmh_platform_post_init(void)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

   return err_flag;
}


__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_rpmh_update_rsrc_config(vrm_pmic_rsrc_data *data, uint8 *access_allowed)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    vrm_result result = VRM_SUCCESS;
    uint32 slave_id = 0;
    uint16 base_addr = 0;
    uint16 offset = 0;
    uint16 periph_addr = 0;
    uint8 slave_id_index = 0;

    if (g_pm_stub_pmic_type == TRUE)
    {
        data->mode_info.seq_type   = VRM_NO_PMIC_SEQ;
        data->volt_info.seq_type   = VRM_NO_PMIC_SEQ;
        data->enable_info.seq_type = VRM_NO_PMIC_SEQ;

        data->enable_info.current_state = data->enable_info.min_state;
        data->volt_info.current_state = data->volt_info.min_state;
        data->mode_info.current_state = data->mode_info.min_state;

        data->settling_en = 0;
        data->settling_err_en = 0;
        data->dep_en = 0;

        data->pstm_pbs_ready_en =0x00;
        
        if (*access_allowed == TRUE)
        {

            // Get VRM arbiter id
            if (data->periph_info.periph_type == PM_VRM_PERIPH_SMPS)
            {
                base_addr = SMPS_BASE_ADDR;
                offset = SMPS_ADDR_OFFSET;
                slave_id_index = 1;
            }
            else if (data->periph_info.periph_type == PM_VRM_PERIPH_LDO)
            {
                base_addr = LDO_BASE_ADDR;
                offset = LDO_ADDR_OFFSET;
                slave_id_index = 1;
            }
            else if (data->periph_info.periph_type == PM_VRM_PERIPH_BOB)
            {
                base_addr = BOB_BASE_ADDR;
                offset = BOB_ADDR_OFFSET;
                slave_id_index = 1;
            }
            else if (data->periph_info.periph_type == PM_VRM_PERIPH_CLK)
            {
                base_addr = CLK_BASE_ADDR;
                offset = CLK_ADDR_OFFSET;
                slave_id_index = 0;
                data->base_addr = base_addr;
            }

            if (base_addr != 0)
            {
                slave_id = (2 * data->periph_info.pmic_index) + slave_id_index;

                periph_addr = base_addr + (offset * data->periph_info.periph_index);

                err_flag = pm_comm_get_vrm_id (slave_id, periph_addr, &(data->vrm_arb_id)); 
                //CORE_VERIFY (err_flag == PM_ERR_FLAG_SUCCESS);
            }

            result = vrm_register_rsrc(data);
            CORE_VERIFY(result == VRM_SUCCESS);
        }

        *access_allowed = FALSE;
    }

    return PM_ERR_FLAG_SUCCESS;
}


__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_rpmh_pmic_detect_err_init(void)
{
    uint32 num_rsrc = 0;
    
    pm_target_information_init();

    vrm_init();

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_SMPS_NUM, 1);
    pm_vrm_vreg_register_resources(1, PM_VRM_PERIPH_SMPS, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_SMPS_NUM, 2);
    pm_vrm_vreg_register_resources(2, PM_VRM_PERIPH_SMPS, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_SMPS_NUM, 3);
    pm_vrm_vreg_register_resources(3, PM_VRM_PERIPH_SMPS, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_SMPS_NUM, 4);
    pm_vrm_vreg_register_resources(4, PM_VRM_PERIPH_SMPS, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_SMPS_NUM, 8);
    pm_vrm_vreg_register_resources(8, PM_VRM_PERIPH_SMPS, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_SMPS_NUM, 9);
    pm_vrm_vreg_register_resources(9, PM_VRM_PERIPH_SMPS, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_LDO_NUM, 1);
    pm_vrm_vreg_register_resources(1, PM_VRM_PERIPH_LDO, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_LDO_NUM, 2);
    pm_vrm_vreg_register_resources(2, PM_VRM_PERIPH_LDO, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_LDO_NUM, 3);
    pm_vrm_vreg_register_resources(3, PM_VRM_PERIPH_LDO, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_LDO_NUM, 4);
    pm_vrm_vreg_register_resources(4, PM_VRM_PERIPH_LDO, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_LDO_NUM, 0xC);
    pm_vrm_vreg_register_resources(0xC, PM_VRM_PERIPH_LDO, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_LDO_NUM, 0xD);
    pm_vrm_vreg_register_resources(0xD, PM_VRM_PERIPH_LDO, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_BOB_NUM, 1);
    pm_vrm_vreg_register_resources(1, PM_VRM_PERIPH_BOB, num_rsrc);

    pm_vrm_clk_register_resources(0, PM_VRM_PERIPH_CLK, PM_MAX_NUM_CLKS - 1);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_PSTM_SEQ, 0);
    pm_vrm_pstm_register_resources(0, PM_VRM_PERIPH_PSTM, num_rsrc);

    pm_vrm_target_register_resources();

    vrm_post_init();

    pm_rpmh_init();

    //pm_prm_init();

    return PM_ERR_FLAG_SUCCESS;
}


__attribute__((section("rinit_code_sec_pool1")))
boolean pm_is_target_specific_stub_enable(void)
{
    pm_model_type pm_model = pm_get_pmic_model(PMICA_INDEX);

    if ((PMIC_IS_UNKNOWN == pm_model) || (PMIC_IS_INVALID == pm_model))
    {
        g_pm_stub_pmic_type = TRUE;
    }
    else
    {
        g_pm_stub_pmic_type = FALSE;
    }

   return g_pm_stub_pmic_type;
}
