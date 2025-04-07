/**********************************************************************
 *
 *   UFS EYEMON implementation
 *
 * Copyright (c) 2022-2023 Qualcomm Technologies, Inc.  
*  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 *
 **********************************************************************/

/*======================================================================

                        EDIT HISTORY FOR MODULE


when         who     what, where, why
----------   ---     --------------------------------------------------- 
2023-07-21   jt      Add re-initialization 
2022-04-18   jt      Initial creation
=======================================================================*/

#include "ufs_core.h"
#include "ufs_errno.h"
#include "ufs_eyemon.h"
#include "ufs_memory.h"
#include "ufs_utp_core.h"
#include "UfsPhyHwio.h"
#include "HALhwio.h"

int32 ufs_eyemon_handle_check (struct ufs_handle *handle)
{
   int32_t rc = EOK; 
   ufs_host_t *hba;
   static uint8_t eom_reinit_done = 0; 

   // Check input parameter
   if (handle == NULL) {
      return -EINVAL;
   }

   hba = handle->phc; 

   // Make sure the host controller interface is ready
   if (hba == NULL) {
      return -EINVAL;
   }

   // Do re-initialization to apply the EOM-specific PHY settings
   if (eom_reinit_done == 0) {
      hba->eom_enabled = 1; 
      hba->plat_cfg.core_skip = 0;

      rc = ufs_utp_init (hba);
      if (rc != EOK) {
         ufs_error_log (hba, 0x030f); 
         return rc; 
      }

      rc = ufs_finish_reinit (handle); 
      if (rc != EOK) {
         ufs_error_log (hba, 0x0311); 
         return rc; 
      }

      eom_reinit_done = 1; 
   }

   return EOK; 
}

int32_t ufs_eyemon_get_capabilities (struct ufs_handle *handle, ufs_eyemon_mode mode, uint8_t lane_num, ufs_eyemon_caps *caps)
{
   int32_t rc = EOK; 
   static ufs_eyemon_caps eyemon_device_caps, eyemon_host_caps; 
   ufs_eyemon_caps eyemon_caps; 
   ufs_host_t *hba; 
   static uint8_t has_device_caps = 0, has_host_caps = 0; 
   uint32_t uic = 0, val = 0; 

   rc = ufs_eyemon_handle_check (handle); 
   if (rc != EOK) {
      return rc; 
   }

   if (caps == NULL) {
      return -EINVAL; 
   }

   if (((mode == UFS_EYEMON_DEVICE) && (has_device_caps == 1)) || 
       ((mode == UFS_EYEMON_HOST) && (has_host_caps == 1))) {
      goto CapsEnd; 
   }

   hba = handle->phc; 

   uic = (mode == UFS_EYEMON_DEVICE) ? UICCMDR_DME_PEER_GET : UICCMDR_DME_GET; 

   rc = ufs_utp_uic_getset(hba, uic, UIC_ARG0_MIBattr(RX_EYEMON_Capabililty, GenSelectRx(lane_num)), 0, &val); 
   if (rc != EOK) {
      ufs_error_log(hba, 0x0300); 
      return rc; 
   }
   eyemon_caps.eyemon_supported = (uint8_t)val; 

   rc = ufs_utp_uic_getset(hba, uic, UIC_ARG0_MIBattr(RX_EYEMON_Timing_MAX_Steps_Capability, GenSelectRx(lane_num)), 0, &val);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0301); 
      return rc; 
   }
   eyemon_caps.timing_max_steps = (uint8_t)val; 

   rc = ufs_utp_uic_getset(hba, uic, UIC_ARG0_MIBattr(RX_EYEMON_Timing_MAX_Offset_Capability, GenSelectRx(lane_num)), 0, &val);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0302); 
      return rc; 
   }
   eyemon_caps.timing_max_offset = (uint8_t)val; 

   rc = ufs_utp_uic_getset(hba, uic, UIC_ARG0_MIBattr(RX_EYEMON_Voltage_MAX_Steps_Capability, GenSelectRx(lane_num)), 0, &val);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0303); 
      return rc; 
   }
   eyemon_caps.voltage_max_steps = (uint8_t)val; 

   rc = ufs_utp_uic_getset(hba, uic, UIC_ARG0_MIBattr(RX_EYEMON_Voltage_MAX_Offset_Capability, GenSelectRx(lane_num)), 0, &val);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0304); 
      return rc; 
   }
   eyemon_caps.voltage_max_offset = (uint8_t)val; 

   if (mode == UFS_EYEMON_DEVICE) {
      osal_memcpy(&eyemon_device_caps, &eyemon_caps, sizeof(ufs_eyemon_caps));  
      has_device_caps = 1; 
   }
   else {
      osal_memcpy(&eyemon_host_caps, &eyemon_caps, sizeof(ufs_eyemon_caps));
      has_host_caps = 1;   
   }

CapsEnd: 
   if (mode == UFS_EYEMON_DEVICE) {
      osal_memcpy(caps, &eyemon_device_caps, sizeof(ufs_eyemon_caps));
   }
   else {
      osal_memcpy(caps, &eyemon_host_caps, sizeof(ufs_eyemon_caps));
   }
   return EOK; 
}

int32_t ufs_eyemon_set_config (struct ufs_handle *handle, ufs_eyemon_mode mode, uint8_t lane_num, ufs_eyemon_config *config)
{
   int32_t rc = EOK; 
   ufs_eyemon_caps caps; 
   ufs_host_t *hba;
   uint8_t timing_steps = 0, voltage_steps = 0;
   uint32_t uic = 0; 

   rc = ufs_eyemon_handle_check (handle); 
   if (rc != EOK) {
      return rc; 
   }

   if (config == NULL) {
      return -EINVAL; 
   }

   hba = handle->phc; 

   rc = ufs_eyemon_get_capabilities (handle, mode, lane_num, &caps);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0305); 
      return rc; 
   }

   if ((caps.timing_max_steps < config->timing_steps.val) || 
       (caps.voltage_max_steps < config->voltage_steps.val)) {
      return -EINVAL; 
   }

   uic = (mode == UFS_EYEMON_DEVICE) ? UICCMDR_DME_PEER_SET : UICCMDR_DME_SET; 

   // Configure RX_EYEMON_Timing_Steps
   timing_steps = config->timing_steps.val| (config->timing_steps.direction << 6); 
   rc = ufs_utp_uic_getset(hba, uic, UIC_ARG0_MIBattr(RX_EYEMON_Timing_Steps, GenSelectRx(lane_num)), timing_steps, NULL); 
   if (rc != EOK) {
      ufs_error_log(hba, 0x0306); 
      return rc;
   }

   // Configure RX_EYEMON_Voltage_Steps
   voltage_steps = config->voltage_steps.val | (config->voltage_steps.direction << 6); 
   rc = ufs_utp_uic_getset(hba, uic, UIC_ARG0_MIBattr(RX_EYEMON_Voltage_Steps, GenSelectRx(lane_num)), voltage_steps, NULL); 
   if (rc != EOK) {
      ufs_error_log(hba, 0x0307); 
      return rc;
   }

   // Configure RX_EYEMON_Target_Test_Count
   rc = ufs_utp_uic_getset(hba, uic, UIC_ARG0_MIBattr(RX_EYEMON_Target_Test_Count, GenSelectRx(lane_num)), config->target_test_count, NULL); 
   if (rc != EOK) {
      ufs_error_log(hba, 0x0308); 
      return rc;
   }

   return rc; 
}

int32_t ufs_eyemon_enable (struct ufs_handle *handle, ufs_eyemon_mode mode, uint8_t lane_num, boolean enable)
{
   int32_t rc = EOK; 
   ufs_eyemon_caps caps; 
   ufs_host_t *hba; 
   uint8_t val = (enable == TRUE) ? 1: 0; 
   uint32_t uic = 0; 

   rc = ufs_eyemon_handle_check (handle); 
   if (rc != EOK) {
      return rc; 
   }

   hba = handle->phc; 

   rc = ufs_eyemon_get_capabilities (handle, mode, lane_num, &caps); 
   if (rc != EOK) {
      ufs_error_log(hba, 0x0309); 
      return rc; 
   }

   // Make sure MPHY supports the eye monitor function 
   if (caps.eyemon_supported == 0) {
      return -EPERM;
   }

   uic = (mode == UFS_EYEMON_DEVICE) ? UICCMDR_DME_PEER_SET : UICCMDR_DME_SET; 

   // Set RX_EYEMON_Eanble 
   rc = ufs_utp_uic_getset(hba, uic, UIC_ARG0_MIBattr(RX_EYEMON_Enable, GenSelectRx(lane_num)), val, NULL); 
   if (rc != EOK) {
      ufs_error_log(hba, 0x030a); 
      return rc; 
   }

   return EOK; 
}

int32_t ufs_eyemon_get_result (struct ufs_handle *handle, ufs_eyemon_mode mode, uint8_t lane_num, ufs_eyemon_result *result)
{
   int32_t rc = EOK; 
   ufs_eyemon_caps caps;
   ufs_host_t *hba;
   uint32_t eyemon_status = 1, uic = 0, val = 0; 

   rc = ufs_eyemon_handle_check (handle); 
   if (rc != EOK) {
      return rc; 
   }

   if (result == NULL) {
      return -EINVAL; 
   }

   hba = handle->phc; 

   rc = ufs_eyemon_get_capabilities (handle, mode, lane_num, &caps); 
   if (rc != EOK) {
      ufs_error_log(hba, 0x030b); 
      return rc; 
   }

   // Make sure MPHY supports the eye monitor function 
   if (caps.eyemon_supported == 0) {
      return -EPERM;
   }

   uic = (mode == UFS_EYEMON_DEVICE) ? UICCMDR_DME_PEER_GET : UICCMDR_DME_GET; 

   rc = ufs_utp_uic_getset(hba, uic, UIC_ARG0_MIBattr(RX_EYEMON_Start, GenSelectRx(lane_num)), 0, &eyemon_status);
   if (rc != EOK) {
      ufs_error_log(hba, 0x030c); 
      return rc; 
   }

   if (eyemon_status == 0) {
      // Read out the error count 
      rc = ufs_utp_uic_getset(hba, uic, UIC_ARG0_MIBattr(RX_EYEMON_Error_Count, GenSelectRx(lane_num)), 0, &val);  
      if (rc != EOK) {
         ufs_error_log(hba, 0x030d); 
         return rc;
      }
      result->error_count = (uint8_t)val; 

      // Read out the tested bit count
      rc = ufs_utp_uic_getset(hba, uic, UIC_ARG0_MIBattr(RX_EYEMON_Tested_Count, GenSelectRx(lane_num)), 0, &val);  
      if (rc != EOK) {
         ufs_error_log(hba, 0x030e); 
         return rc;
      }
      result->tested_count = (uint8_t)val; 

      return EOK; 
   }
   else {
      return -EBUSY; 
   }
}

int32_t ufs_eyemon_pm_change (struct ufs_handle *handle, uint8_t gear, uint8_t lanes, uint8_t adapt)
{
   int32_t rc = EOK; 
   ufs_bsp_speed_config config; 
   ufs_host_t *hba = handle->phc; 

   rc = ufs_eyemon_handle_check (handle); 
   if (rc != EOK) {
      return rc; 
   }

   config.enable_hs = 1; 
   config.gear = gear; 
   config.num_lanes = lanes; 
   config.rate = hba->cfg_entries.perf_speed_params.rate & 0xff; 
   config.adapt = adapt;  

   memset(&hba->curr_speed_config, 0x00, sizeof(ufs_bsp_speed_config)); 

   rc = ufs_utp_gear_sw (hba, &config); 
   if (rc != EOK) {
      ufs_error_log(hba, 0x0310); 
      return rc; 
   }

   return EOK; 
}

int32_t ufs_eyemon_set_coarse_code (struct ufs_handle *handle, uint8_t lane_num, uint8_t coarse_code)
{
   int32_t rc = EOK; 
   ufs_host_t *hba = handle->phc; 

   rc = ufs_eyemon_handle_check (handle); 
   if (rc != EOK) {
      return rc; 
   }

   if (lane_num == 0) {  
      HWIO_REG_OUT (hba->ufs_hci_addr, UFS_MEM_QSERDES_RX0_AUXDATA_TB, 
                    (HWIO_UFS_MEM_QSERDES_RX0_AUXDATA_TB_AUXDATA_THRESH_BIN_MUX_BMSK | coarse_code)); 
   }
   else if (lane_num == 1) {
      HWIO_REG_OUT (hba->ufs_hci_addr, UFS_MEM_QSERDES_RX1_AUXDATA_TB, 
                    (HWIO_UFS_MEM_QSERDES_RX1_AUXDATA_TB_AUXDATA_THRESH_BIN_MUX_BMSK | coarse_code)); 
   }
   else {
     return -EINVAL; 
   }

   return EOK; 
}




