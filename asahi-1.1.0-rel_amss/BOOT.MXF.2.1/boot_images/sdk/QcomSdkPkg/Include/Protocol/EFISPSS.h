/**
  file  EFISPSS.h

  SPSS Protocol for UEFI.

*/
/*=============================================================================
   Copyright (c) 2022-2023, Qualcomm Technologies, Inc.  All Rights Reserved.
   Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/16/23   eb      Adjustments to reuse ABL structs and add VBH
 11/24/22   eb      Initial version
=============================================================================*/
#ifndef __EFISPSS_H__
#define __EFISPSS_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/

#include <Uefi.h>

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/

/*  Protocol GUID definition */
/** @ingroup efi_spss_protocol */
#define EFI_SPSS_PROTOCOL_GUID \
   { 0xa322ff2c, 0x6d1a, 0x44de, { 0xa4, 0x70, 0xc0, 0xa8, 0x9e, 0x48, 0xc2, 0xe6 } }

#define SHA256_SIZE 32

/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/

/** @ingroup */
extern EFI_GUID gEfiQcomSPSSProtocolGuid;

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/

/** @cond */
/* Protocol declaration.  */
typedef struct _QCOM_SPSS_PROTOCOL QCOM_SPSS_PROTOCOL;
/** @endcond */

// Request structs for TZ according to KeymasterClient.h
typedef struct {
  UINT32 CmdId;
  UINT32 RotOffset;
  UINT32 RotSize;
  CHAR8 RotDigest[SHA256_SIZE];
} __attribute__ ((packed)) KMSetRotReq;

typedef struct {
  UINT32 IsUnlocked;
  CHAR8 PublicKey[SHA256_SIZE];
  UINT32 Color;
  UINT32 SystemVersion;
  UINT32 SystemSecurityLevel;
} __attribute__ ((packed)) KMBootState;

typedef struct {
  UINT32 CmdId;
  UINT32 Version;
  UINT32 Offset;
  UINT32 Size;
  KMBootState BootState;
} __attribute__ ((packed)) KMSetBootStateReq;

typedef struct {
  UINT32 CmdId;
  CHAR8 Vbh[SHA256_SIZE];
} __attribute__ ((packed)) KMSetVbhReq;

typedef struct KeymintSharedInfoStruct_t {
  KMSetRotReq RootOfTrust;
  KMSetBootStateReq BootInfo;
  KMSetVbhReq Vbh;
} __attribute__ ((packed)) KeymintSharedInfoStruct;

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/

/**
* Share Keymint info with SPSS Driver
*
* @param KeymintSharedInfoStruct  *keymint_shared_info
*   Keymint shared info
*
* @return int
*   Status:
*     0 - Success
*     Negative value indicates failure.
*/
typedef
EFI_STATUS
(EFIAPI *QCOM_SPSS_SHARE_KEYMINT_INFO)
(
  IN  const KeymintSharedInfoStruct    *keymint_shared_info
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/

/** @ingroup
  @par Summary
    Android SPSS Protocol interface.

  @par Parameters
  @inputprotoparams
*/
struct _QCOM_SPSS_PROTOCOL {
  QCOM_SPSS_SHARE_KEYMINT_INFO      SPSSDxe_ShareKeyMintInfo;
};

#endif /* __EFISPSS_H__ */