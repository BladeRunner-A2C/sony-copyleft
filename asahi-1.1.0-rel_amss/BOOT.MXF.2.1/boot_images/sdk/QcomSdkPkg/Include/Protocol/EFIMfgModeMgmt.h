/**
@file  EFIMfgModeMgmt.h
@brief UEFI Manufacturing Mode Management Protocol definitions.
*/
/*=============================================================================
Copyright (c) 2023 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY

when         who         what, where, why
--------     ---         ----------------------------------------------------------- 
2023/03/16   gpavithr      Initial revision
=============================================================================*/
#ifndef __EFI_MFGMODEMGMT_H_
#define __EFI_MFGMODEMGMT_H_

/** @defgroup EFI_QC_MFG_MODE_MGMT_PROTOCOL  EFI_QC_MFG_MODE_MGMT_PROTOCOL
 *  @ingroup Protocols 
 */
 /** @defgroup  EFI_QC_MFG_MODE_MGMT_PROTOCOL_prot PROTOCOL
 *  @ingroup EFI_QC_MFG_MODE_MGMT_PROTOCOL 
 */ 
 /** @defgroup  EFI_QC_MFG_MODE_MGMT_PROTOCOL_apis APIs
 *  @ingroup EFI_QC_MFG_MODE_MGMT_PROTOCOL 
 */ 

/** @defgroup  EFI_QC_MFG_MODE_MGMT_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup EFI_QC_MFG_MODE_MGMT_PROTOCOL 
 */ 

/*===========================================================================
MACRO DECLARATIONS
===========================================================================*/
/* Protocol version. */
#define EFI_QC_MFG_MODE_MGMT_PROTOCOL_REVISION_1 0x00010000
#define EFI_QC_MFG_MODE_MGMT_PROTOCOL_REVISION   EFI_QC_MFG_MODE_MGMT_PROTOCOL_REVISION_1 


/* Protocol GUID definition */
#define EFI_QC_MFG_MODE_MGMT_PROTOCOL_GUID \
        { 0x299ba6bc, 0xc2cd, 0x4019, {0xbe, 0x4c, 0x54, 0xe6, 0xcd, 0xec, 0x7b, 0x55 } };

/*===========================================================================
EXTERNAL VARIABLES
===========================================================================*/
/* External reference to the MFG_MODE_MGMT Protocol GUID. */
extern EFI_GUID gEfiQCMfgModeMgmtProtocolGuid;

/*===========================================================================
TYPE DEFINITIONS
===========================================================================*/
/** @addtogroup EFI_QC_MFG_MODE_MGMT_PROTOCOL_data 
@{ */
/* Mfg Mode status enum type */
typedef enum {
  EFI_QC_MFG_MODE_DISABLED = 0,
  EFI_QC_MFG_MODE_ENABLED
}EFI_QC_MFG_MODE_STATUS_TYPE;
/** @} */

/* Protocol declaration */
typedef struct _EFI_QC_MFG_MODE_MGMT_PROTOCOL EFI_QC_MFG_MODE_MGMT_PROTOCOL;

/*===========================================================================
FUNCTION DEFINITIONS
===========================================================================*/
/* EFI_MFG_MODE_GET */
/** @ingroup EFI_MFG_MODE_MGMT_PROTOCOL_apis
  @par Summary
  Returns the status of MfgMode on device.

  @par Description
  Function that indicates if device is in manufacturing mode or not.

  @param[out]  pMfgModeStatus       EFI_QC_MFG_MODE_ENABLED/EFI_QC_MFG_MODE_DISABLED depending
                                    on whether mfgmode is enabled/disabled.

  @retval      EFI_SUCCESS          Mfgmode status is returned successfully.
  @retval      EFI_XXXXXX           Failure occured.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_QC_MFG_MODE_GET)(
  OUT EFI_QC_MFG_MODE_STATUS_TYPE *pMfgModeStatus
  );

/* EFI_MFG_MODE_SET */
/** @ingroup EFI_MFG_MODE_MGMT_PROTOCOL_apis
  @par Summary
  OEM specific modules in UEFI does a call to SetManufacturingMode() to
  enable manufacturing mode on the device before UEFI_READY_TO_BOOT Event.

  @param[in]  value               EFI_QC_MFG_MODE_ENABLED : Enable manufacturing mode.
  
  @retval  EFI_SUCCESS            MANUFACTURING_MODE is enabled successfully.
  @retval  EFI_UNSUPPORTED        Disabling mfgmode using value(EFI_QC_MFG_MODE_DISABLED)
                                  is not supported.
  @retval  EFI_XXXXXX             Failure occured.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_QC_MFG_MODE_SET)(
  IN EFI_QC_MFG_MODE_STATUS_TYPE value
  );

/*===========================================================================
PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup EFI_QC_MFG_MODE_MGMT_PROTOCOL_prot
  @par Summary
  EFI_QC_MFG_MODE_MGMT_PROTOCOL interface.
*/
struct _EFI_QC_MFG_MODE_MGMT_PROTOCOL {
  UINT64                    Revision;
  EFI_QC_MFG_MODE_SET       SetManufacturingMode; /* Added in EFI_QC_MFG_MODE_MGMT_PROTOCOL_REVISION_1 */
  EFI_QC_MFG_MODE_GET       GetManufacturingMode; /* Added in EFI_QC_MFG_MODE_MGMT_PROTOCOL_REVISION_1 */
};

#endif  /* __EFIMFGMODEMGMTH_ */

