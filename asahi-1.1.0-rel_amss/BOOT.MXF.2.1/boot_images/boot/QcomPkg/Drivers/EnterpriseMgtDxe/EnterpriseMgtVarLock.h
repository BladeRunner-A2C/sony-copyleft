/**
  @file EnterpriseMgtVarLock.h
  @brief EnterpriseMgt dxe helper functions to lock UEFI variable.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Drivers/EnterpriseMgtDxe/EnterpriseMgtVarLock.h#1 $
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/
#ifndef __ENTERPRISEMGTVARLOCK_H__
#define __ENTERPRISEMGTVARLOCK_H__

#include "EnterpriseMgtDxeBaseDef.h"

/**
  Protocol function to lock EnterpriseMgt UEFI Variable.

  @retval EFI_SUCCESS          Locked successfully.
  @retval EnterpriseMgtLockUEFIVariable returned value.
**/
EFI_STATUS EnterpriseMgtLockNowVar( VOID );

/**
  Function to register a callback for Ready to Boot Event.

  @retval EFI_SUCCESS           Registered successfully.
  @retval EfiCreateEventReadyToBootEx returned value.
**/
EFI_STATUS EnterpriseMgtRegisterForReadyToBootEvent( VOID );

#endif /*__ENTERPRISEMGTVARLOCK_H__*/