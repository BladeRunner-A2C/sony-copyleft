/**
  @file  EFIQPPC.h
  @brief QPPC Protocol for UEFI.
*/
/*=============================================================================
  Copyright 2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who       what, where, why
 --------   ---       -----------------------------------------------------------
 12/08/22   saichait  Created.

=============================================================================*/
#ifndef __EFIQPPC_H__
#define __EFIQPPC_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/
#include <QPPCTypes.h>
#include <Uefi.h>

/** @ingroup efi_qppc_protocol_data
  Protocol version.
*/
#define EFI_QPPC_PROTOCOL_VERSION_1 0x0000000000010000
#define EFI_QPPC_PROTOCOL_VERSION_2 0x0000000000020000
#define EFI_QPPC_PROTOCOL_VERSION   EFI_QPPC_PROTOCOL_VERSION_2

/* Define new GUID for QPPC */
#define EFI_QPPC_PROTOCOL_GUID {0xa6deb54d, 0x0253, 0x1a4d, { 0x8a, 0x82, 0x67, 0x7a, 0x68, 0x3b, 0x0d, 0x29 }}
/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the QPPC Protocol GUID.
*/
extern EFI_GUID gEfiQppcProtocolGuid;


/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/
/**
  Protocol declaration.
*/
typedef struct _EFI_QPPC_PROTOCOL EFI_QPPC_PROTOCOL;

/*===========================================================================
  FUNCTION PROTOTYPES
===========================================================================*/

/* EFI_REGISTER_CALLBACK */

/** @ingroup efi_register_callback
 * @ingroup efi_qppc_protocol_apis
  @par Summary
  Register client callback function with QPPC

  @param[in]  This                  Pointer to the EFI_QPPC_PROTOCOL instance.
  @param[in]  pfnCB                 Pointer to callback function.
  @param[in]  nData                 Callback data.

  @par Description
  This function takes callback function pointer and callback data from user and register 
  it with QPPC driver. QPPC driver will invoke callback function when certain events 
  need to process from client.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_REGISTER_CALLBACK) (
  IN  EFI_QPPC_PROTOCOL   *This,
  IN  PQPPC_CB             pfnCB,
  IN  QPPC_CBData          nData
);


/* EFI_QPPC_GetConfig */

/** @ingroup efi_query
 * @ingroup efi_qppc_protocol_apis
  @par Summary
  Query specific data available in PCCT table.

  @param[in]  This                  Pointer to the EFI_QPPC_PROTOCOL instance.
  @param[in]  eQuery                Query type.
  @param[in]  Param                 Query parameters.
  @param[out] pnResult              Query results.

  @par Description
  This function parse PCCT table and get specific configuration queried by user then it return
  query specific data to user.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_QPPC_GetConfig) (
  IN  EFI_QPPC_PROTOCOL     *This,
  IN  QPPCQueryType          eQuery,
  IN  QppcQueryParam         Param,
  OUT QppcQueryResultType   *pnResult
);

/* EFI_SET_CONFIG */

/** @ingroup efi_setconfig
 * @ingroup efi_qppc_protocol_apis
  @par Summary
  Set specific configuration in QPPC.

  @param[in]  This                  Pointer to the EFI_QPPC_PROTOCOL instance.
  @param[in]  eConfig               Set configuration type.
  @param[in]  Param                 configuration parameters.
  @param[out] pnResult              cnfiguration results (optional).

  @par Description
  This function set specific configuration in PCCT table and notify respective PDP
  to process the configuration change.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS
(EFIAPI *EFI_QPPC_SETCONFIG)(
  IN  EFI_QPPC_PROTOCOL     *This,
  IN  QPPCConfigType         eConfig,
  IN  QppcConfigParam        Param,
  OUT UINT32                *pnResult
);

/****
  TBD: EFI_GetConfig is required to read debug data.
 ****/
 
/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_qppc_protocol
 * @ingroup efi_qppc_protocol_prot
  @par Summary
  QPPC Protocol interface.

  @par Parameters
  @inputprotoparams{qppc_proto_params.tex}
*/
struct _EFI_QPPC_PROTOCOL {
   UINT64                           Version;
   EFI_REGISTER_CALLBACK            RegisterCallback;  /* Added in EFI_QPPC_PROTOCOL_VERSION_1 */
   EFI_QPPC_GetConfig               GetConfig;         /* Added in EFI_QPPC_PROTOCOL_VERSION_1 */
   EFI_QPPC_SETCONFIG               SetConfig;         /* Added in EFI_QPPC_PROTOCOL_VERSION_1 */
};
 
#endif