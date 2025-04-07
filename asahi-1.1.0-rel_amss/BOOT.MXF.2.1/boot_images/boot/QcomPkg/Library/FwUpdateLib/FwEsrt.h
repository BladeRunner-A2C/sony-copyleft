/** @file FwESRT.h

   Header for functions to maintain the ESRT , including ESRT
   header and ESRT entry .
  
  Copyright (c) 2012-2015, 2017-2018, 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when           who      what, where, why
 --------       ---      --------------------------------------------------
 2022/06/03     gpavithr Add support for formfactor CRD, IDPS For HAMOA
 2021/03/11     kbarad   Added support of Capsule update on CPD device
 2018/08/31     prema    Changes for SysFwVersion Entry handling to update SysFwVersion and ESRT entry
 2018/05/28     prema    FAT to NV migration for ESRT data storage
 2018/05/25     prema    Updated System Firmware Resource GUID for 8180
 2017/05/08     gparam   Changes to centralize ESRT update to DPP to the end of
                         SetImage API
 2017/04/18     gparam   Changes to centralize the recording of update status
                         in DPP for future use
 2017/04/18     gparam   Updated function names to match the latest capsule flow +
                         Removed unused/redundant definitions/parameters not
                         used in capsule flow
 2017/02/27     pkn      Added changes required to support new update type - FWCLASS_GUID
 2017/02/24     gparam   Changes to correct the prefilled known SystemFirmware
                         GUIDs for the default Qualcomm form-factors
 2017/02/22     gparam   Added the default 8998 specific system firmware GUIDs and
                         removed 8996 GUID
 2017/02/13     gpavithr Changes to use ESRTDxe inplace of local functions
                         to directly create and/or operate on ESRT table
 2015/03/31     mic      Added 8994 platform types
 2013/04/11     rsb      Added 8084 platform types
 2012/11/30     mic      Added ESRT entry print function
 2012/11/09     jmb      Adding CBH platform
 2012/10/21     mic      Code review
 2012/08/14     ash      Added 8064 WB292 and V1 variants
 2012/06/18     jd       rename OEM_UPDATE_EVENT_GUID
 2012/06/05     rs       Added UXCapsule OEM Update Event GUID
 2012/05/09     rsb      Platform run-time type detection for FW Resource GUID
 2012/05/07     jd       Migrated to DPP Protocol.
 2012/02/01     mic      Initial version

=============================================================================*/
#ifndef __QCOM_FW_ESRT_H_
#define __QCOM_FW_ESRT_H_

#include <Guid/SystemResourceTable.h>

#define QCOM_FW_UPDATE_PRODUCT_VERSION_10 0x00010000
#define QCOM_FW_UPDATE_PRODUCT_VERSION_11 0x00010001
#define QCOM_FW_UPDATE_PRODUCT_VERSION_12 0x00010002

#define SYSTEM_FW_VERSION_SIGNATURE            SIGNATURE_64('S','Y','S','F','W','V','E','R')

#define SYSTEM_FW_VERSION_MAJOR_REVISION 0x0001
#define SYSTEM_FW_VERSION_MINOR_REVISION 0x0000

#define SYSTEM_FW_VERSION_REVISION       (SYSTEM_FW_VERSION_MAJOR_REVISION << 16 | SYSTEM_FW_VERSION_MINOR_REVISION)

#define DEFAULT_SYSTEM_FW_VERSION                  0x00010000
#define DEFAULT_SYSTEM_FW_LOWEST_SUPPORTED_VERSION 0x0


/* System Firmware Resource GUID for 8380 IDP: {6ad6c997-c5c9-4c23-821e-fe4bd515d8eb}*/
#define QCOM_FW_UPDATE_SYSTEM_FW_8380_IDP_UFS_GUID \
{ \
  0x6ad6c997, 0xc5c9, 0x4c23, { 0x82, 0x1e, 0xfe, 0x4b, 0xd5, 0x15, 0xd8, 0xeb } \
}

/* System Firmware Resource GUID for 8380 CRD: {13661e4e-794e-4bff-ab6b-34863e156170} */
#define QCOM_FW_UPDATE_SYSTEM_FW_8380_CRD_UFS_GUID \
{ \
  0x13661e4e, 0x794e, 0x4bff, { 0xab, 0x6b, 0x34, 0x86, 0x3e, 0x15, 0x61, 0x70 } \
}

/* System Firmware Resource GUID for 8380 IDPS: {b348c327-bd2b-499b-8e67-34a68596f6d3} */
#define QCOM_FW_UPDATE_SYSTEM_FW_8380_IDPS_UFS_GUID \
{ \
  0xb348c327, 0xbd2b, 0x499b, { 0x8e, 0x67, 0x34, 0xa6, 0x85, 0x96, 0xf6, 0xd3 } \
}

/* System Firmware Resource GUID for 8380 IDP: {92ae9706-0120-453b-9deb-c11c04077216} */
#define QCOM_FW_UPDATE_SYSTEM_FW_8380_IDP_SPINOR_GUID \
{ \
  0x92ae9706, 0x0120, 0x453b, { 0x9d, 0xeb, 0xc1, 0x1c, 0x04, 0x07, 0x72, 0x16 } \
}

/* System Firmware Resource GUID for 8380 CRD: {57f92a58-2eac-4c42-8b57-03949979140a} */
#define QCOM_FW_UPDATE_SYSTEM_FW_8380_CRD_SPINOR_GUID \
{ \
  0x57f92a58, 0x2eac, 0x4c42, { 0x8b, 0x57, 0x03, 0x94, 0x99, 0x79, 0x14, 0x0a } \
}

/* System Firmware Resource GUID for 8380 IDPS: {fc1fd8d7-beb5-4c6c-8f33-19247da25c1b} */
#define QCOM_FW_UPDATE_SYSTEM_FW_8380_IDPS_SPINOR_GUID \
{ \
  0xfc1fd8d7, 0xbeb5, 0x4c6c, { 0x8f, 0x33, 0x19, 0x24, 0x7d, 0xa2, 0x5c, 0x1b } \
}

/* System Firmware Resource GUID for UNKNOWN platform type: {06CE6651-B594-4AC3-B57A-D9637CC335A8} */

#define QCOM_FW_UPDATE_SYSTEM_FW_UNKNOWN_GUID \
{ \
  0x06CE6651, 0xB594, 0x4AC3, { 0xB5, 0x7A, 0xD9, 0x63, 0x7C, 0xC3, 0x35, 0xA8 } \
}

/* UX Capsule GUID : {3b8c8162-188c-46a4-aec9-be43f1d65697}  */

#define QCOM_FW_UPDATE_UX_CAPSULE_GUID \
{ \
  0x3B8C8162, 0x188C, 0x46A4, { 0xAE, 0xC9, 0xBE, 0x43, 0xF1, 0xD6, 0x56, 0x97 } \
}

#define QCOM_FW_UPDATE_ESRT_GUID \
{ \
  0xB122A263, 0x3661, 0x4F68, { 0x99, 0x29, 0x78, 0xf8, 0xb0, 0xd6, 0x21, 0x80 } \
}

/*{592515FE-F062-4AD0-89C8-9118F0F2D6BF}*/
#define QCOM_FW_UPDATE_OEM_UPDATE_EVENT_GUID \
{ \
  0x592515FE, 0xF062, 0x4AD0, { 0x89, 0xC8, 0x91, 0x18, 0xF0, 0xF2, 0xD6, 0xBF } \
}

typedef enum {
  FW_TYPE_UNKNOWN,
  FW_TYPE_SYSTEM,
  FW_TYPE_DEVICE,
  FW_TYPE_DRIVER
} ESRT_FWTYPE;

typedef enum {
  FW_LAST_ATMPT_STATUS_SUCCESS,
  FW_LAST_ATMPT_STATUS_UNSUCCESSFUL,
  FW_LAST_ATMPT_STATUS_INSUFF_RESOURCE,
  FW_LAST_ATMPT_STATUS_INCORRECT_VERSION,
  FW_LAST_ATMPT_STATUS_INVALID_IMG_FMT,
  FW_LAST_ATMPT_STATUS_AUTHEN_ERROR,
  FW_LAST_ATMPT_STATUS_POWER_AC_NOT_CONNECTED,
  FW_LAST_ATMPT_STATUS_POWER_INSUFFICIENT_BATTERY

} ESRT_LAST_ATTEMPT_STATUS;

/* The list of System Firmware Resource types for each platform, this enumeration must match
   one to one with qcomFwResourceGUIDs. */
typedef enum _QCOM_FW_RESOURCE_TYPE
{
  QCOM_FW_UPDATE_SYSTEM_FW_8380_IDP_TYPE,
  QCOM_FW_UPDATE_SYSTEM_FW_8380_CRD_TYPE,
  QCOM_FW_UPDATE_SYSTEM_FW_8380_IDPS_TYPE,
  QCOM_FW_UPDATE_SYSTEM_FW_UNKNOWN_TYPE

} QCOM_FW_RESOURCE_TYPE;

typedef struct
{
  UINT32 FWResrcCnt;
  UINT32 FWResrcMax;
  UINT64 FWResrcVer;

}ESRT_TABLE_HEADER;


// 
// System-firmware version data
//
typedef struct _QC_SYSFW_VERSION_DATA {
    //
    // Identifies compatible system-firmware version data.
    // This value must contain ASCII string "SYSFWVER" encoded
    // as 64 bit constant 0x5245565746535953.
    //
    UINT64 Signature;
    //
    // Revision number of system firmware version data expressed in a.b format.
    // Value is calculated as (a << 16 | b).
    //
    UINT32 Revision;
    //
    // Size of the whole version data. Value should be greater than
    // or equal to 28 but less than or equal
    // to logical block size.    
    //
    UINT32 VersionDataSize;
    //
    // CRC32 checksum of the whole version data. CRC32 is computed by setting
    // this field to 0, and computing the 32-bit CRC for VersionDataSize bytes.
    //
    UINT32 VersionDataCrc32;
    //
    // System firmware version as defined by ESRT table definition.    
    //
    UINT32 FwVersion;
    //
    // Lowest supported version as defined by ESRT table definition.
    //
    UINT32 LowestSupportedFwVersion;

    //
    // Reserved for future expansion. Size : BlockSize - VersionDataSize.
    //
    //VOID *Reserved;
} QC_SYSFW_VERSION_DATA;

/**
  Return if this FMP is a system FMP or a device FMP, based upon FmpImageInfo.

  @param[in] FmpImageInfo A pointer to EFI_FIRMWARE_IMAGE_DESCRIPTOR

  @return TRUE  It is a system FMP.
  @return FALSE It is a device FMP.
**/
EFI_STATUS 
UpdateVarSystemFmpCapsuleImageTypeIdGuid (
  IN EFI_GUID  SystemFwGuid
  );

/**
 *  Find the Firmware Resource GUID for the device platform.
 *
 * @param FwResourceGuid - Pointer to GUID that is modified to correspond to the current
 *                         platform type.
 *
 * @return EFI_STATUS
 */

EFI_STATUS
QcomGetFwGuidForPlatform(
  OUT EFI_GUID *FwResourceGuid
  );

/**
  Validate SysFwVersionData retrieved from SysFwVersion Patition

  @param[in]  QC_SYSFW_VERSION_DATA   SysFwVersionData buffer pointer to be validate for CRC32

  @retval EFI_SUCCESS                When valid CRC32 retrieved for given SysFwVerData
  @retval EFI_INVALID_PARAMETER      When NULL SysFwVersion data is passed
  @retval EFI_VOLUME_CORRUPTED       When invalid SysFwVer signature or Version or CRC found

**/
EFI_STATUS
EFIAPI
QcomValidateSysFwVersionData (
  IN QC_SYSFW_VERSION_DATA *SysFwVersionData
);

/**
  Get SystemFwVersion data from SysFwVersion partition.
  This function will get QC_SYSFW_VERSION_DATA block of memory by reading
  full SysFwVersion partition and copy only QC_SYSFW_VERSION_DATA size of memory.
  
  On successful returning of QC_SYSFW_VERSION_DATA size of memory, this block of memory
  will be validate for Signature, Version, CRC.
  
  @param [out] FwVersion                - Pointer to current firmware version.
  @param [out] LowestSupportedFwVersion - Pointer to current lowest supported version.
  
  @retval EFI_STATUS

**/

EFI_STATUS
EFIAPI
QcomGetSysFwVersion (
  OUT UINT32                   *FwVersion,
  OUT UINT32                   *LowestSupportedFwVersion
  );

/**
  This function sets SysFwVersion data into SysFwVersion partition.
  
  @param [IN] FwVersion                - New firmware version.
  @param [IN] LowestSupportedFwVersion - New lowest supported version.
  
  @retval EFI_STATUS

**/

EFI_STATUS
QcomSetSysFwVersion (
  IN UINT32                 FwVersion,
  IN UINT32                 LowestSupportedFwVersion
 );

/**
  Reading SystemFwVersion partion based on SysFwVersion partition guid
  
  This function expects size of QC_SYSFW_VERSION_DATA memory on.
  And this function will read full SysFwVersion partition and return full
  size value. On reading full data, only QC_SYSFW_VERSION_DATA size of data
  will be copy to destination buffer and same buffer will be return to caller.
  
  @param  VOID***             : **Buffer
  
  @retval EFI_STATUS
  @retval EFI_SUCESS            Action completed successfully
**/
EFI_STATUS
EFIAPI
QcomReadSysFwVerPartition (
  IN OUT VOID        **Buffer
  );

/**
  Write SystemFwVersion data into SysFwVersion partion.
  This function recalculate and update CRC for given inputdata
  as and when data is received
  
  @param  VOID***             : *Buffer   Buffer to write
  @param  UINTN               : BuffSize  Size of buffer to write
  
  @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
QcomWriteSysFwPartition (
  IN  VOID         *Buffer,
  IN  UINTN         BufferSize
  );

/**
  This function prints current SysFwVersion entry info
  by reading entry from SysFwVersion partition.
   
  @DebugLevel - Debug level
  
  @return : EFI_STATUS
**/
EFI_STATUS
QcomPrintSysFwVerPartitionData(
  IN UINTN                      DebugLevel
  );

/**
 * Initialize lock used to handle cache buffer
 * 
 * @return : EFI_STATUS
**/
EFI_STATUS
EFIAPI
QcomInitSysFwVersionContext (
  VOID
  );

#endif
