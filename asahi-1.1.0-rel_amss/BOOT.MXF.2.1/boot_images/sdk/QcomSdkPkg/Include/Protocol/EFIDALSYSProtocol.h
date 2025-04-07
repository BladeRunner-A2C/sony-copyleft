/** @file EFIDALSYSProtocol.h

  DALSYS Protocol for UEFI

  Copyright (c) 2010-2011,2014 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/15/14   aa      Updated INIT Function declaration to accept new parameter
 08/14/14   aa      Updated DEINIT Function declaration to accept new parameter
 05/01/14   asmitp  Renamed header file DALSYSProtocol.h to EFIDALSYSProtocol.h
 01/27/11   sho     Add history

=============================================================================*/

#ifndef __DAL_SYS_PROTOCOL_H__
#define __DAL_SYS_PROTOCOL_H__

#include <DALStdDef.h>
#include <DALSysTypes.h>
#include <devcfgTypes.h>
#include <DALReg.h>

#define DALSYS_REVISION 0x0000000000010002

/** @ingroup efi_dal_sys_protocol_apis
 * @return
  EFI_SUCCESS       --      Function completed successfully
*/
typedef 
void
(EFIAPI *EFI_DALSYS_PROTOCOL_INIT)(
   IN    DALREG_DriverInfoList      *pModDriverList,
   IN    DALProps                   *pDALStringDevInfoList,
   OUT   DALSYSFncPtrTbl            **pFncTblPtr
);

/** @ingroup efi_dal_sys_protocol_apis
 * @return
  EFI_SUCCESS       --      Function completed successfully
*/
typedef 
void
(EFIAPI *EFI_DALSYS_PROTOCOL_DEINIT)(
   IN    DALREG_DriverInfoList      *pModDriverList,
   IN    DALProps                   *pDALStringDevInfoList
   );

/** @ingroup efi_dal_sys_protocol_prot
*/									
typedef struct _EFI_DALSYS_PROTOCOL {
   UINT64                     revision;
   EFI_DALSYS_PROTOCOL_INIT   init;
   EFI_DALSYS_PROTOCOL_DEINIT deinit;
//   EFI_DALSYS_PROTOCOL_EVENTCREATE DALSYS_EventCreate;
} 
EFI_DALSYS_PROTOCOL; 

extern EFI_GUID gEfiDalSysProtocolGuid;

#endif
