/**
@file     UfsEyemon.h
@brief   UFS Eye Monitor DXE Header File

This file contains the definitions of the constants, data structures,
and interfaces for the UFS driver in UEFI.

 Copyright (c) 2022 Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


when            who   what, where, why
----------      ---   -----------------------------------------------------------
2022-07-19      jt    Initial version
=============================================================================*/

#ifndef _UFS_EYEMON_H_
#define _UFS_EYEMON_H_

#include <Protocol/EFIStorageEyemon.h>

/**
  Gets the Eye Monitor capabilities

  @param[in]  This                Pointer to the EFI_STORAGE_EYEMON_PROTOCOL instance
  @param[in]  Params              Eye Monitor Parameters
  @param[out] Capabilities        Pointer containing the Eye Monitor capabilities 

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
  @retval EFI_DEVICE_ERROR        Failed to get the capabilities. 
**/
EFI_STATUS EFIAPI UFSEyemonGetCapabilities (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This, 
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN EFI_STORAGE_EYEMON_CAPS     *Capabilities
);

/**
  Changes the Power Mode for Eye Monitor measurement

  @param[in]  This                Pointer to the EFI_STORAGE_EYEMON_PROTOCOL instance
  @param[in]  Params              Eye Monitor Parameters
  @param[in]  Gear                HS Gear to switch to
  @param[in]  Adapt               Enable adapt or not 

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
  @retval EFI_DEVICE_ERROR        Failed to change the power mode. 
**/
EFI_STATUS EFIAPI UFSEyemonPmChange (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This,
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN UINT8                       Gear, 
   IN UINT8                       Adapt
);

/**
  Sets the Coarse Code for Host Side Eye Monitor measurement 

  @param[in]  This                Pointer to the EFI_STORAGE_EYEMON_PROTOCOL instance
  @param[in]  Params              Eye Monitor Parameters
  @param[in]  CoarseCode          Coarse code value      

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
  @retval EFI_DEVICE_ERROR        Error in setting the coarse code. 
**/
EFI_STATUS EFIAPI UFSEyemonSetCoarseCode (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This,
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN UINT8                       CoarseCode
);

/**
  Sets the Eye Monitor config values for measurement (timing/voltage steps, target test count)

  @param[in]  This                Pointer to the EFI_STORAGE_EYEMON_PROTOCOL instance
  @param[in]  Params              Eye Monitor parameters
  @param[in]  Config              Eye Monitor configuration values

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
  @retval EFI_DEVICE_ERROR        Failed to set the configuration values. 
**/
EFI_STATUS EFIAPI UFSEyemonConfig (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This, 
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN EFI_STORAGE_EYEMON_CONFIG   *Config
);

/**
  Enables/disables Eye Monitor measurement 

  @param[in]  This                Pointer to the EFI_STORAGE_EYEMON_PROTOCOL instance
  @param[in]  Params              Eye Monitor parameters
  @param[in]  Enable              Enable/disable Eye Monitor measurement 

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
  @retval EFI_DEVICE_ERROR        Failed to enable/disable Eye Monitor.  
**/
EFI_STATUS EFIAPI UFSEyemonEnable (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This, 
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN BOOLEAN                     Enable
);
   
/**
  Gets the Eye Monitor Result (error/test count)

  @param[in]  This                Pointer to the EFI_STORAGE_EYEMON_PROTOCOL instance
  @param[in]  Params              Eye Monitor parameters
  @param[out] Result              Eye Monitor Result

  @retval EFI_SUCCESS             Function completed successfully.
  @retval EFI_INVALID_PARAMETER   Parameter is invalid.
  @retval EFI_NOT_READY           Measurement still in progress.
  @retval EFI_DEVICE_ERROR        Failed to get the result.  
**/   
EFI_STATUS EFIAPI UFSEyemonGetResult (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This,
   IN EFI_STORAGE_EYEMON_PARAMS   *Params,   
   OUT EFI_STORAGE_EYEMON_RESULT  *Result
);

#define UFS_DEV_FROM_EYEMON(a) CR (a, UFS_DEV, Eyemon, UFS_DEV_SIGNATURE)

#endif /* _UFS_EYEMON_H_ */

