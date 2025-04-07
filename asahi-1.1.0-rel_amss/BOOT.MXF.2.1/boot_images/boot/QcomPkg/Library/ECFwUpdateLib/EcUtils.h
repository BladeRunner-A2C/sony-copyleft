/** @file EcUtils.h

  Header file for EC FW update related utility routines.

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------
  2023/03/22     bkulkarn    Changes to update EC Firmware version in SMBIOS Type-0 table
  2023/02/28     sumesahu    Fix for Boot KPI during empty EC FW
  2023/02/23     bkulkarn    Support to query & update EC device status in NV and code refactoring
  2023/02/04     sumesahu    FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine, code refactoring
  2023/01/17     ananns      Cleaning up reference to global device context structure
  2022/07/29     bkulkarn    Initial version
=============================================================================*/

#ifndef __ECUTILS_H_
#define __ECUTILS_H_

#include <stdbool.h>
#include <Guid/SystemResourceTable.h>

/* Common EC FW FFS GUID: {4DC8BBB0-D3F6-4407-B46B-4B729F606DC0}*/
#define EC_FW_FFS_FILE_GUID \
  { \
    0x4DC8BBB0, 0xD3F6, 0x4407, { 0xB4, 0x6B, 0x4B, 0x72, 0x9F, 0x60, 0x6D, 0xC0 } \
  }

/* The list of EC Device Firmware Resource GUIDs in deviceContext_<>_<VENDOR>_<PART> that apply for each platform */

/* EC Device Firmware Resource GUID for 8380 ITE-8987: {22C5BC99-FA15-410E-A396-8B069DE0601A} */
#define EC_DEVICE_FW_8380_ITE_8987_GUID \
  { \
    0x22C5BC99, 0xFA15, 0x410E, { 0xA3, 0x96, 0x8B, 0x06, 0x9D, 0xE0, 0x60, 0x1A } \
  }

typedef struct _VERSION_INFO
{
  UINT8     main_ver;
  UINT8     sub_ver;
  UINT8     test_ver;
}VERSION_INFO;

typedef struct _FULL_VERSION_INFO
{
  UINT32    fw_version;
  UINT32    lowest_supported_version;
}FULL_VERSION_INFO;

typedef struct _CORRUPTION_INFO
{
  UINT8 corruption_status;
  CHAR8 name[40];
}CORRUPTION_INFO;

typedef enum
{
  UNKNOWN_CORRUPTION_BIT,
  P1_BBK   = 0x01,
  P2_BBK   = 0x02,
  P1_MBK   = 0x04,
  P2_MBK   = 0x08,
  SYNC_BIT = 0x80,
  ALL_PARTITIONS_OK = (P1_BBK|P1_MBK|P2_BBK|P2_MBK|SYNC_BIT)
} PARTITION_BIT;

/*
 * Global enum for unique EC device identifier.
 * Append any new device in deviceContext_<>_<VENDOR>_<PART> to the end.
 */
typedef enum
{
  EC_DEVICE_ID_UNKNOWN,
  EC_DEVICE_ID_8380_ITE_8987 = 0x8987,
  EC_DEVICE_ID_8380_ITE_5671 = 0x5671,
} EC_DEVICE_ID;

typedef struct _EC_DEVICE_ID_TO_GUID_MAPPING
{
  UINT16        EcDeviceId;
  EFI_GUID      EcFwResourceGUID;
} EC_DEVICE_ID_TO_GUID_MAPPING;

extern EC_DEVICE_ID_TO_GUID_MAPPING EcDeviceIdToGUIDMappings[];

/**
 * @brief Function to read the EC FW version from firmware binary.
 *
 * @param ver_info         Pointer to structure containing EC FW version
 * @param ver_str          Pointer to string to be searched within FW binary
 *
 * @retval status          A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
GetOnBinaryEcFwVersions(
  const char *ver_str
  );

/**
 * @brief Function to query and save full EC FW version
 * (Fv, LsFv and code-mirror tag) from IC.
 *
 * @param none
 *
 * @retval status    `     A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
GetOnDeviceFullEcFwVersion (
  void
  );

/**
 * @brief Function to compare provided EC FW version with version stored in NV.
 *
 * @param ver_info         Pointer to structure containing EC FW version
 *
 * @retval retVal          An integer indicating result of the operation.
 *
 **/
int
CompareWithOnDeviceEcFwVersion (
  VERSION_INFO *ver_info
  );

/**
 * @brief Function to compare provided EC FW version with on device FW version.
 *
 * @param ver_info         Pointer to structure containing EC FW version
 *
 * @retval retVal          An integer indicating result of the operation.
 *
 **/
int
CompareWithNvEcFwVersion (
  VERSION_INFO *ver_info
  );

/**
 * @brief Function to read the EC FW FFS file entry from FV
 *
 * @param Image             Pointer to FV image handle
 * @param ImageSize         Size of FV image buffer
 * @param Buffer            Pointer to pointer that contains EC FW FFS contents
 * @param BufferSize        Pointer to buffer that contains EC FW FFS contents
 *
 * @retval status           A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
ReadEcFwFromFV (
  IN VOID       *Image,
  IN UINTN       ImageSize,
  IN VOID       **Buffer,
  IN OUT UINTN  *BufferSize
  );

/**
 * @brief Function to query the EC device ID from EC hardware.
 *
 * @param none
 *
 * @retval status          A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
GetEcDeviceId (
  void
  );

/**
 * @brief Function to get the FW partition corruption status from EC hardware.
 *
 * @param corruption_status  Pointer to corruption status variable.
 *
 * @retval status            A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
GetEcFwCorruptionStatus (
  UINT8 *corruption_status
  );

/**
 * @brief Find the Firmware Resource GUID for the EC device.
 *
 * @param FwResourceGuid - Pointer to GUID that is modified to correspond to the current
 *                         platform type.
 *
 * @retval status           A EFI_STATUS indicating result of the operation.
 *
 */
EFI_STATUS
GetEcFwResourceGuid (
  OUT EFI_GUID *FwResourceGuid
  );

/**
 * @brief Function to query the device status
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved Device status successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the IsDeviceInitDone is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetDeviceStatus (
  OUT boolean *IsDeviceUp
  );

/**
 * @brief Function to compare the different in FW version against On IC with On NV variable
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved FwVersion comparsion status successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the IsOnIcFwVersionSame is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CompareOnIcFwVersion (
  OUT boolean *IsOnIcFwVersionSame
  );


/**
 * @brief Function to create and query the On IC LsFv
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved On IC Lowest supported Fw Version successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the LsFwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CreateAndGetOnIcLsFwVersion (
  OUT UINT32 *LsFwVersion
  );

/**
 * @brief Function to create and query the On IC FW version
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved On IC Fw Version successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the FwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CreateAndGetOnIcFwVersion (
  OUT UINT32 *FwVersion
  );

/**
 * @brief Function to query the On IC Lowest Supported FW version
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved On IC Lowest Supported Firmware Version successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the OnIcLsFwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetOnIcLsFwVersion (
  OUT UINT32 *OnIcLsFwVersion
  );

/**
 * @brief Function to set the Firmware Update Done status
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Successfully set the Fw Update status
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
SetFwUpdateStatus (
  IN UINT8 FwUpdateStatus
  );

/**
 * @brief Function to query the Firmware Update Done status
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved Fw update status successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the IsFwUpdateDone is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetFwUpdateStatus (
  OUT boolean *IsFwUpdateDone
  );

/**
 * @brief Function to query and save EC FW version from NV area
 *
 * @param none
 *
 * @retval status    `     A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
GetOnNvEcFwVersion (
  UINT32 *FwVersion
  );

/**
 * @brief Function to query and save EC Lowest Supported (Ls)
 * FW version from NV area
 *
 * @param none
 *
 * @retval status    `     A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
GetOnNvEcLsFwVersion (
  UINT32 *LsFwVersion
  );

/**
 * @brief Function to query the Code Mirror Tag value
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved CodeMirrorTag Value successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the CodeMirrorTag is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetCodeMirrorTag (
  OUT UINT8 *CodeMirrorTag
  );

/**
 * @brief Function to query a byte from the EC FW version offset
 *
 * @param FwImageData                    Pointer to the FwImageData
 *
 * @retval EFI_SUCCESS                   Retrieved EC FW version starting byte successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the FwImageData is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetECVersionOffset (
  IN byte *FwImageData,
  IN UINTN Size,
  OUT byte *Data
  );

/**
 * @brief Function to set the valid raw buffer exist status
 *
 * @param RawBuffStatus                  Set the Raw buffer status value
 *
 * @retval EFI_SUCCESS                   Successfully set the valid buffer status
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
SetRawBuffExistStatus (
  IN UINT8 RawBuffStatus
  );

/**
 * @brief Function to query the Valid raw buffer exist status
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Successfully read raw buffer status
 * @retval EFI_INVALID_PARAMETER         Pointer to the IsValidRawBuffExist is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetRawBuffExistStatus (
  OUT boolean *IsValidRawBuffExist
  );

/**
 * @brief Function to create and assign On binary Firmware version
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   On binary fw version is assigned successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the FwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CreateAndSetOnBinFwVersion (
  OUT UINT32 *FwVersion
  );

/**
 * @brief Function to create and query the On binary Lowest Supported Firmware version
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved On binary lowest supported fw version successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the LsFwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CreateAndGetOnBinLsFwVersion (
  OUT UINT32  *LsFwVersion
  );

/**
 * @brief Function to compare the FwVersion with NV Fw Version and On IC Fw Version
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved On binary lowest supported fw version successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the LsFwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CompareFwVersion (
  OUT boolean *IsFwVersionLesser
  );

/**
 * @brief Function to compare the different in Lowest Supportted version against
 * On IC with On NV variable
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved LsFwVersion comparsion status successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the IsLsFwVersionSame is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CompareOnIcLsFwVersions (
  OUT boolean *IsLsFwVersionSame
  );

/**
 * @brief Function to print On IC and On Binary main,sub and test version
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Version details are printed successfully
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
DisplayVersionMismatchDetails (
  void
  );

/**
 * @brief Function to query the On IC and On Binary version details
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved On IC and On binary version info successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the OnIcFwVersion/OnIcLsFwVersion/
 *                                       OnBinFwVersion/OnBinLsFwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetOnIcAndOnBinVersion (
  OUT UINT32 *OnIcFwVersion,
  OUT UINT32 *OnIcLsFwVersion,
  OUT UINT32 *OnBinFwVersion,
  OUT UINT32 *OnBinLsFwVersion
  );

/**
 * @brief Function to print EC Fw version details
 * (Chip ID, device ID, On IC Fw version and LsFw version)
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   EC Fw Version details are printed successfully
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
DisplayEcFwVersionDetails (
  void
  );

/**
 * @brief Function to print EC Fw Partition details
 * (P1BBK, P1MBK, P2BBK, P2MBK)
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   EC Fw Version details are printed successfully
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
DisplayEcFwPartitionDetails (
  void
  );

/**
 * @brief Function to wait for EC Fw getting stable and running in MBK
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   EC Fw Version details are printed successfully
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
WaitForEcFwToStable (
  void
  );

/**
 * @brief Function to check if P1BBK is intact
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   P1BBK is proper
 * @retval others                        P1BBK is corrupted
 *
 **/
EFI_STATUS
EcFwCheckP1BBKCorruption (
  VOID
  );


/**
 * @brief Function to query and update the EC device status
 *
 * @param none
 *
 * @retval status          A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
QueryAndUpdateDeviceStatus(
  void
  );

/**
 * @brief Standalone routine to query the EC Firmware version from other modules
 * - This function inits the I2C connection with I2C core.
 * - Queries the EC to read the version.
 * - Releases the resources.
 *
 * @param pEcFwVersion An out parameter containing valid EC firmware version in
 *                     case of success.
 * @retval status      A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
GetEcFwVersion(
  OUT VERSION_INFO *pEcFwVersion
  );

#endif
