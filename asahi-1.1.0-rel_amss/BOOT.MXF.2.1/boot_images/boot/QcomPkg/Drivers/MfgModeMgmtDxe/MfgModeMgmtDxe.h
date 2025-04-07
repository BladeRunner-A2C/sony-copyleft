/**
@file  MfgModeMgmtDxe.h
@brief Qualcomm UEFI Manufacturing Mode Protocol declarations.
*/
/*=============================================================================
Copyright (c) 2023 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when           who         what, where, why
--------       ---         --------------------------------------------------
2023/03/16     gpavithr    Initial revision
=============================================================================*/
#ifndef __MFGMODEMGMT_H_
#define __MFGMODEMGMT_H_

/**
  Function to enable MfgMode from MfgModeToggleApp.
  
  @retval  EFI_SUCCESS    MANUFACTURING_MODE is enabled successfully.
  @retval  EFI_XXXXXX     Failure occured.
  
**/
EFI_STATUS
EnableMfgModeFromNV(
  VOID
  );

#endif // #ifndef __MFGMODEMGMT_H_