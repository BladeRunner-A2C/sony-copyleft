/** @file MpPowerLib.h
   
  The Multicore power  common definitions

  Copyright (c) 2015, Qualcomm Technologies, Inc. All rights reserved.
  
**/

/*=============================================================================
                              EDIT HISTORY

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Include/Library/MpPowerLib.h#1 $ 
  $DateTime: 2024/04/02 23:00:31 $ 
  $Author: cirrusp4svc $ 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 09/24/15   rli     Initial revision
=============================================================================*/
#ifndef __MPPOWERLIB_H_
#define __MPPOWERLIB_H_


/*=========================================================================
      Include Files
==========================================================================*/

/*===========================================================================

                        Defines and Structs

===========================================================================*/

/*===========================================================================

                        Public Functions

===========================================================================*/
/**
  @brief MpPowerInit - chipset-specific initialization
  @return - EFI_SUCCESS on success, otherwise error status
*/
EFI_STATUS MpPowerInit (VOID);

/**
  @brief MpPower - chipset-specific multicore enablement
  @param[in]  CoreNum - number of cores
  @return - EFI_SUCCESS on success, otherwise error status
*/
EFI_STATUS MpPower (UINTN  CoreNum);



#endif // __MPPOWERLIB_H_
