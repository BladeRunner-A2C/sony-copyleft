/**
 *  @file  EFIPcieEom.h
 *  @brief PCIe EOM Protocol for UEFI.
 */

/*=============================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

#ifndef __EFI_PCIE_EOM_H___
#define __EFI_PCIE_EOM_H___

/*===========================================================================
  INCLUDE FILES
===========================================================================*/

#include <Uefi.h>
#include <Library/BaseLib.h>

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/** @ingroup efi_pcie_eom_protocol_data
 * Protocol Revision
 */
#define EFI_PCIE_EOM_PROTOCOL_REVISION1 0x0000000000010000

/** @ingroup efi_pcie_eom_protocol_data
 * Protocol version.
 */
#define EFI_PCIE_EOM_PROTOCOL_VERSION EFI_PCIE_EOM_PROTOCOL_REVISION1

/** @ingroup efi_pcie_eom_protocol_data
 *  Protocol GUID definition
 */
#define EFI_PCIE_EOM_PROTOCOL_GUID \
   { 0x1850702f, 0xd8e8, 0x4d5d, { 0x81, 0x6c, 0x2b, 0xdf, 0x63, 0x82, 0x65, 0xd3 } }

/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/** @cond */
/**
 * External reference to the PCIe EOM Protocol GUID.
 */
extern EFI_GUID gEfiPcieEomProtocolGuid;
/** @endcond */

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/
/** @cond */
/** @ingroup efi_pcie_eom_protocol_data
 * Protocol declaration.
 */
typedef struct _EFI_PCIE_EOM_PROTOCOL EFI_PCIE_EOM_PROTOCOL;
/** @endcond */

/** @ingroup efi_pcie_eom_protocol_data
 * Enumerated directions in which Voltage threshold can be offset.
 */
typedef enum
{
   PCIE_EOM_VOLTAGE_DIR_POS,
   PCIE_EOM_VOLTAGE_DIR_NEG
} PcieEomVoltageDirType;

/** @ingroup efi_pcie_eom_protocol_data
 * Stores the Port capabilities.
 */
typedef struct
{
   INT32    MinTime;
   INT32    MaxTime;
   INT32    MinVoltage;
   INT32    MaxVoltage;
   UINT32   NumLanes;
} PcieEomPortConfigType;

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/**
 * @ingroup efi_pcie_eom_protocol_apis
 *
 * @par Summary
 * Returns the configuration of the target port
 *
 * @param[in]  Port        Target port index
 * @param[out] PortConfig  Pointer to target port config
 *
 * @par Description
 * Returns the configuration of the target port
 *
 * @return
 * EFI_SUCCESS             - Operation completed successfully \n
 * EFI_INAVLID_PARAMETER   - Input parameter is invalid
 */
typedef  EFI_STATUS  (EFIAPI *EFI_PCIE_EOM_GET_CONFIG)
(
   IN    UINT32                  Port,
   OUT   PcieEomPortConfigType   *PortConfig
);

/**
 * @ingroup efi_pcie_eom_protocol_apis
 *
 * @par Summary
 * Initialize the EOM registers
 *
 * @param[in] Port         Target port index
 * @param[in] Lane         Target lane index
 * @param[in] VoltageDir   Direction of voltage threshold offset
 *
 * @par Description
 * Initializes the EOM registers prior to sampling the error
 * count in the positive or negative voltage domains on the
 * specified lane for the target port.
 *
 * @return
 * EFI_SUCCESS             - Operation completed successfully \n
 * EFI_INAVLID_PARAMETER   - Input parameter is invalid \n
 * EFI_ABORTED             - Operation failed to complete successfully.
 */
typedef  EFI_STATUS  (EFIAPI *EFI_PCIE_EOM_INIT)
(
   IN    UINT32                  Port,
   IN    UINT32                  Lane,
   IN    PcieEomVoltageDirType   VoltageDir
);

/**
 * @ingroup efi_pcie_eom_protocol_apis
 *
 * @par Summary
 * Start error counter
 *
 * @param[in] Port         Target port index
 * @param[in] Lane         Target lane index
 * @param[in] TimeStep     Step within MinTime and MaxTime to set as time
 *                         offset
 * @param[in] VoltageStep  Step within MinVoltage and MaxVoltage to set as
 *                         voltage offset
 *
 * @par Description
 * Starts counting errors at the given time and voltage offsets
 * on a specified lane for the target port
 *
 * @return
 * EFI_SUCCESS             - Operation completed successfully \n
 * EFI_INAVLID_PARAMETER   - Input parameter is invalid \n
 * EFI_ABORTED             - Operation failed to complete successfully
 */
typedef  EFI_STATUS  (EFIAPI *EFI_PCIE_EOM_START)
(
   IN    UINT32                  Port,
   IN    UINT32                  Lane,
   IN    INT32                   TimeStep,
   IN    INT32                   VoltageStep
);

/**
 * @ingroup efi_pcie_eom_protocol_apis
 *
 * @par Summary
 * Stop error counter
 *
 * @param[in] Port         Target port index
 * @param[in] Lane         Target lane index
 *
 * @par Description
 * Stops counting errors on the specified lane for a given port
 *
 * @return
 * EFI_SUCCESS             - Operation completed successfully \n
 * EFI_INAVLID_PARAMETER   - Input parameter is invalid \n
 * EFI_ABORTED             - Operation failed to complete successfully
 */
typedef  EFI_STATUS  (EFIAPI *EFI_PCIE_EOM_STOP)
(
   IN    UINT32                  Port,
   IN    UINT32                  Lane
);

/**
 * @ingroup efi_pcie_eom_protocol_apis
 *
 * @par Summary
 * Returns error count
 *
 * @param[in]  Port         Target port index
 * @param[in]  Lane         Target lane index
 * @param[out] ErrorCount   Error count at set time and voltage steps
 *
 * @par Description
 * Returns the error count on a specified lane for a given port
 *
 * @return
 * EFI_SUCCESS             - Operation completed successfully \n
 * EFI_INAVLID_PARAMETER   - Input parameter is invalid \n
 * EFI_ABORTED             - Operation failed to complete successfully
 */
typedef  EFI_STATUS  (EFIAPI *EFI_PCIE_EOM_GET_RESULT)
(
   IN    UINT32                  Port,
   IN    UINT32                  Lane,
   OUT   UINT32                  *ErrorCount
);

/**
 * @ingroup efi_pcie_eom_protocol_apis
 *
 * @par Summary
 * Deinitializes EOM registers
 *
 * @param[in]  Port         Target port index
 * @param[in]  Lane         Target lane index
 *
 * @par Description
 * Deinitializes EOM registers on the specified lane for a given
 * port
 *
 * @return
 * EFI_SUCCESS             - Operation completed successfully \n
 * EFI_INAVLID_PARAMETER   - Input parameter is invalid \n
 * EFI_ABORTED             - Operation failed to complete successfully
 */
typedef  EFI_STATUS  (EFIAPI *EFI_PCIE_EOM_DEINIT)
(
   IN    UINT32                  Port,
   IN    UINT32                  Lane
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_pcie_eom_protocol_prot
 *  @par Summary
 *  Qualcomm PCIe EOM Protocol Interface.
 *
 *  @par Parameters
 *  @inputprotoparams{pcieeom_proto_params.tex}
 */
struct _EFI_PCIE_EOM_PROTOCOL
{
   UINT64                    Version;
   EFI_PCIE_EOM_GET_CONFIG   GetConfig;
   EFI_PCIE_EOM_INIT         Init;
   EFI_PCIE_EOM_START        Start;
   EFI_PCIE_EOM_STOP         Stop;
   EFI_PCIE_EOM_GET_RESULT   GetResult;
   EFI_PCIE_EOM_DEINIT       DeInit;
};

#endif
