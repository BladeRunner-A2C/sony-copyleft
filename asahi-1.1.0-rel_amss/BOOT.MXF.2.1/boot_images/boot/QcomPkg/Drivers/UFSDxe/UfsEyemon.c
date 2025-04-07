/**
* @file     UfsEyemon.c
* @brief   UFSDxe Eye Monitor 
*
*  Copyright (c) 2022 Qualcomm Technologies, Inc. All rights reserved.
*/


/*=============================================================================
                              EDIT HISTORY


when            who   what, where, why
----------      ---   ----------------------------------------------------------- 
2022-09-16      jt    Move ufs_open out of the entry point 
2022-07-11      jt    Initial version 
=============================================================================*/

#include "UFS.h"
#include "UfsEyemon.h"
#include <api/storage/ufs_api.h>
#include <api/storage/ufs_eyemon.h>
#include <Protocol/BlockIo.h>
#include <Protocol/BlockIo2.h>
#include <Protocol/BlockIoCrypto.h>
#include <Protocol/EFIRpmb.h>
#include <Protocol/EFICardInfo.h>
#include <Protocol/EFIEraseBlock.h>
#include <Protocol/EFIStorageWriteProtect.h>
#include <Protocol/EFIStorageDeviceMgmt.h>
#include <Protocol/EFIStorageEyemon.h>
#include <Library/UefiBootServicesTableLib.h>

/* Eye Monitor protocol */
const EFI_STORAGE_EYEMON_PROTOCOL gUfsEyemonProtocol = {
   EFI_STORAGE_EYEMON_PROTOCOL_REVISION,   /* Revision */
   UFSEyemonGetCapabilities, 
   UFSEyemonPmChange,
   UFSEyemonSetCoarseCode,
   UFSEyemonConfig,
   UFSEyemonEnable,  
   UFSEyemonGetResult
};

/**
   Gets the Eye Monitor capabilities.
**/
EFI_STATUS EFIAPI UFSEyemonGetCapabilities (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This, 
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN EFI_STORAGE_EYEMON_CAPS     *Capabilities)
{
   INT32 rc;
   UFS_DEV *UfsDevice;
   ufs_eyemon_caps eyemon_caps; 
   struct ufs_handle *hUFS;
   UINT8 LaneNum = 0; 

   if ((This == NULL) || (Params == NULL) || (Capabilities == NULL)) {
      return EFI_INVALID_PARAMETER; 
   }

   UfsDevice = UFS_DEV_FROM_EYEMON (This);   
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (Params->LaneNum != LANE_ALL) {
      LaneNum = Params->LaneNum; 
   }

   rc = ufs_eyemon_get_capabilities (hUFS, (ufs_eyemon_mode)Params->Mode, LaneNum, &eyemon_caps);  
   if (rc != UFS_EOK) { 
      DEBUG ((EFI_D_ERROR, "ufs_eyemon_get_capabilities failed %d\n", rc));
      return EFI_DEVICE_ERROR; 
   }

   Capabilities->Supported = eyemon_caps.eyemon_supported; 
   Capabilities->TimingMaxSteps = eyemon_caps.timing_max_steps; 
   Capabilities->TimingMaxOffset = eyemon_caps.timing_max_offset; 
   Capabilities->VoltageMaxSteps = eyemon_caps.voltage_max_steps;
   Capabilities->VoltageMaxOffset = eyemon_caps.voltage_max_offset; 

   return EFI_SUCCESS; 
}

/**
   Changes the Power Mode for Eye Monitor measurement.
**/
EFI_STATUS EFIAPI UFSEyemonPmChange (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This,
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN UINT8                       Gear, 
   IN UINT8                       Adapt)
{
   UINT8 NumLanes = 0; 
   INT32 rc;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;

   if ((This == NULL) || (Params == NULL)) {
      return EFI_INVALID_PARAMETER; 
   }

   UfsDevice = UFS_DEV_FROM_EYEMON (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (Params->LaneNum == LANE_0) {
      NumLanes = 1;  
   }
   else if ((Params->LaneNum == LANE_1) || (Params->LaneNum == LANE_ALL)) {
      NumLanes = 2; 
   }
   else {
      return EFI_INVALID_PARAMETER; 
   }

   rc = ufs_eyemon_pm_change(hUFS, Gear, NumLanes, Adapt);  
   if (rc != UFS_EOK) {
      DEBUG ((EFI_D_ERROR, "ufs_eyemon_pm_change failed %d\n", rc));
      return EFI_DEVICE_ERROR; 
   }

   return EFI_SUCCESS; 
}

/**
   Sets the Coarse Code for Host Side Eye Monitor measurement.
**/ 
EFI_STATUS EFIAPI UFSEyemonSetCoarseCode (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This,
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN UINT8                       CoarseCode)
{
   INT32 rc;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;

   if ((This == NULL) || (Params == NULL)) {
      return EFI_INVALID_PARAMETER; 
   }

   /* Device Eye Monitor doesn't require to set the coarse code value */
   if (Params->Mode == DEVICE_EYEMON) {
      return EFI_SUCCESS; 
   }

   UfsDevice = UFS_DEV_FROM_EYEMON (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (Params->LaneNum == LANE_ALL) {
      rc = ufs_eyemon_set_coarse_code(hUFS, 0, CoarseCode);  
      if (rc != UFS_EOK) {
         DEBUG ((EFI_D_ERROR, "ufs_eyemon_set_coarse_code Lane 0 failed %d\n", rc));
         return EFI_DEVICE_ERROR; 
      }
      rc = ufs_eyemon_set_coarse_code(hUFS, 1, CoarseCode);  
      if (rc != UFS_EOK) {
         DEBUG ((EFI_D_ERROR, "ufs_eyemon_set_coarse_code Lane 1 failed %d\n", rc));
         return EFI_DEVICE_ERROR; 
      }
   }
   else {
      rc = ufs_eyemon_set_coarse_code(hUFS, Params->LaneNum, CoarseCode); 
      if (rc != UFS_EOK) {
         DEBUG ((EFI_D_ERROR, "ufs_eyemon_set_coarse_code failed %d\n", rc));
         return EFI_DEVICE_ERROR; 
      }
   }

   return EFI_SUCCESS; 
}

/**
   Sets the Eye Monitor config values for measurement.
**/
EFI_STATUS EFIAPI UFSEyemonConfig (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This, 
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN EFI_STORAGE_EYEMON_CONFIG   *Config)
{
   INT32 rc;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   ufs_eyemon_config eyemon_cfg; 

   if ((This == NULL) || (Params == NULL) || (Config == NULL)) {
      return EFI_INVALID_PARAMETER; 
   }

   UfsDevice = UFS_DEV_FROM_EYEMON (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   eyemon_cfg.timing_steps.direction = Config->TimingDirection; 
   eyemon_cfg.timing_steps.val = Config->TimingSteps; 

   eyemon_cfg.voltage_steps.direction = Config->VoltageDirection; 
   eyemon_cfg.voltage_steps.val = Config->VoltageSteps; 

   eyemon_cfg.target_test_count = Config->TargetTestCount; 

   if (Params->LaneNum == LANE_ALL) {
      rc = ufs_eyemon_set_config(hUFS, (ufs_eyemon_mode)Params->Mode, 0, &eyemon_cfg);
      if (rc != UFS_EOK) {
         DEBUG ((EFI_D_ERROR, "ufs_eyemon_set_config Lane 0 failed %d\n", rc));
         return EFI_DEVICE_ERROR; 
      }
      rc = ufs_eyemon_set_config(hUFS, (ufs_eyemon_mode)Params->Mode, 1, &eyemon_cfg);
      if (rc != UFS_EOK) {
         DEBUG ((EFI_D_ERROR, "ufs_eyemon_set_config Lane 1 failed %d\n", rc));
         return EFI_DEVICE_ERROR; 
      }
   }
   else {
      rc = ufs_eyemon_set_config(hUFS, (ufs_eyemon_mode)Params->Mode, Params->LaneNum, &eyemon_cfg);
      if (rc != UFS_EOK) {
         DEBUG ((EFI_D_ERROR, "ufs_eyemon_set_config failed %d\n", rc));
         return EFI_DEVICE_ERROR; 
      }
   }

   return EFI_SUCCESS; 
}

/**
   Enables/disables Eye Monitor measurement.
**/
EFI_STATUS EFIAPI UFSEyemonEnable (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This, 
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN BOOLEAN                     Enable)
{
   INT32 rc;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;

   if ((This == NULL) || (Params == NULL)) {
      return EFI_INVALID_PARAMETER; 
   }

   UfsDevice = UFS_DEV_FROM_EYEMON (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   if (Params->LaneNum == LANE_ALL) {
      rc = ufs_eyemon_enable(hUFS, (ufs_eyemon_mode)Params->Mode, 0, Enable); 
      if (rc != UFS_EOK) { 
         DEBUG ((EFI_D_ERROR, "ufs_eyemon_enable Lane 0 failed %d\n", rc));
         return EFI_DEVICE_ERROR; 
      }
      rc = ufs_eyemon_enable(hUFS, (ufs_eyemon_mode)Params->Mode, 1, Enable); 
      if (rc != UFS_EOK) { 
         DEBUG ((EFI_D_ERROR, "ufs_eyemon_enable Lane 1 failed %d\n", rc));
         return EFI_DEVICE_ERROR; 
      }
   }
   else {
      rc = ufs_eyemon_enable(hUFS, (ufs_eyemon_mode)Params->Mode, Params->LaneNum, Enable); 
      if (rc != UFS_EOK) { 
         DEBUG ((EFI_D_ERROR, "ufs_eyemon_enable failed %d\n", rc));
         return EFI_DEVICE_ERROR; 
      }
   }

   return EFI_SUCCESS; 
}

/**
   Gets the Eye Monitor Result.
**/
EFI_STATUS EFIAPI UFSEyemonGetResult (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This, 
   IN EFI_STORAGE_EYEMON_PARAMS   *Params,  
   OUT EFI_STORAGE_EYEMON_RESULT  *Result)
{
   INT32 rc;
   UFS_DEV *UfsDevice;
   struct ufs_handle *hUFS;
   ufs_eyemon_result eyemon_result; 

   if ((This == NULL) || (Params == NULL) || (Result == NULL)) {
      return EFI_INVALID_PARAMETER; 
   }

   UfsDevice = UFS_DEV_FROM_EYEMON (This);
   hUFS = (struct ufs_handle *) UfsDevice->DeviceHandle;

   rc = ufs_eyemon_get_result(hUFS, (ufs_eyemon_mode)Params->Mode, Params->LaneNum, &eyemon_result); 
   if (rc == -UFS_EBUSY) {
      return EFI_NOT_READY; 
   }
   else if (rc != UFS_EOK) {
      DEBUG ((EFI_D_ERROR, "ufs_eyemon_get_result failed %d\n", rc));
      return EFI_DEVICE_ERROR; 
   }

   Result->ErrorCount = eyemon_result.error_count; 
   Result->TestedCount = eyemon_result.tested_count; 

   return EFI_SUCCESS; 
}





