/**
  @file PlatformInfo.c

  Interface implementation file for the PlatformInfo driver.
*/
/*
  ====================================================================

  Copyright (c) 2011, 2022, 2024 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ====================================================================


  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "PlatformInfoInternal.h"

#include "Library/BaseLib.h"
#include "com_dtypes.h"
#include "pm_version.h"
#include "smem.h"
#include "DDIChipInfo.h"
#include "DALDeviceId.h"
#include "Library/CoreMsgRam.h"
#include "DTBExtnLib.h"
#include "ChipInfo.h"
#include "OEMInfo.h"

/*
 * Number of bytes to reserve for marketing data when allocating the
 * SocInfo SMEM region. TZ populates it because the data and the code
 * that processes it is too large to put in Boot IMEM.
 *
 * Kailua had around 200B of marketing information as of March 2023.
 * Double that amount to give us some leeway. This amount is also
 * hardcoded in TZ because we don't have a way to share the size with it.
 *
 * (while we could temporarily repurpose nNumPartNameMappings and store
 * this size there, it could cause problems if TZ doesn't populate the
 * region correctly. TZ might not even run in some PLs.)
 *
 * Any changes to this number must also be reflected in TZ's version.
 */
#define PLATFORMINFO_SMEM_MARKETING_DATA_SIZE_BYTES 400

/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * PlatformInfoRPMType
 *
 */
typedef struct
{
  DalPlatformInfoPlatformInfoType   PlatformInfo;
  uint32                            nNumKVPS;
  PlatformInfoKVPSType              aKVPS[];
} PlatformInfoRPMType;

/*
 * PlatformInfoKVPSCDTType
 *
 *
 */
typedef struct PACK(PlatformInfoKVPSCDTType)
{
  uint8 nKey;
  uint8 nValue;
} PlatformInfoKVPSCDTType;

/*
 * PlatformInfoCDTType
 *
 * Storage structure which mimics the format of the EEPROM platform ID section.
 */
typedef struct PACK(PlatformInfoCDTType_v5)
{
  uint8                 nVersion;
  uint8                 nPlatform;
  uint8                 nHWVersionMajor;
  uint8                 nHWVersionMinor;
  uint8                 nSubtype;
  uint8                 nOEMVariantID;
  uint8                 nNumKVPS;
  PlatformInfoKVPSCDTType  aKVPS[];
} PlatformInfoCDTType_v5;


typedef struct PACK(PlatformInfoCDTType_v3)
{
  uint8                 nVersion;
  uint8                 nPlatform;
  uint8                 nHWVersionMajor;
  uint8                 nHWVersionMinor;
  uint8                 nSubtype;
  uint8                 nNumKVPS;
  PlatformInfoKVPSCDTType  aKVPS[];
} PlatformInfoCDTType_v3;

typedef PlatformInfoCDTType_v5 PlatformInfoCDTType;


/*
 * PlatformInfoPmicFamilyType
 *
 * An enum to define Chip Family type.
 */
typedef enum
{
  PLATFORMINFO_PMIC_FAMILY_A     = 0,
  PLATFORMINFO_PMIC_FAMILY_B     = 1,
}PlatformInfoPmicFamilyType;


/*=========================================================================
      Global data and Typedefs
==========================================================================*/

#define PLATINFO_DTB_NODE "/soc/PlatformInfo"


PlatformInfoCDTType gPlatInfoCDTDefault = {
  .nVersion        = 0x05,
  .nPlatform       = 0x08,
  .nHWVersionMajor = 0x01,
  .nHWVersionMinor = 0x00,
  .nSubtype        = 0x00,
  .nNumKVPS        = 0x00,
  .nOEMVariantID   = 0x00,
};


/*=========================================================================
      Function Prototypes
==========================================================================*/

static DALResult PlatformInfo_InitGlblCtxt (PlatformInfoDrvCtxt *pDrvCtxt);
static DALResult PlatformInfo_InitSMem     (PlatformInfoDrvCtxt *pDrvCtxt);
static DALResult PlatformInfo_CDTInit (PlatformInfoDrvCtxt *pDrvCtxt, uint8_t *pCDT);
void ChipInfo_UpdateDisabledFeaturesFromXblConfig(void);

/*=========================================================================
      Function Definitions
==========================================================================*/

/* =========================================================================
**  Function : PlatformInfo_Init
** =========================================================================*/
/**
  See PlatformInfo.h
*/
DALResult PlatformInfo_Init
(
  void
)
{
  PlatformInfoDrvCtxt *pDrvCtxt = PlatformInfo_GetDrvCtxt();

  if (pDrvCtxt->bInitialized)
  {
    return DAL_SUCCESS;
  }

  /*
   * Only detect if loading scripts haven't already set the platform
   * type manually.
   */
  if (pDrvCtxt->PlatformInfo.platform == DALPLATFORMINFO_TYPE_UNKNOWN)
  {
    pDrvCtxt->PlatformInfo.platform = PlatformInfo_DetectPlatformType();
  }

  pDrvCtxt->bInitialized = TRUE;
  return DAL_SUCCESS;
}


/* =========================================================================
**  Function : PlatformInfo_InitGlblCtxt
** =========================================================================*/
/**
  This function allocates and fills in the global context.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.

  @return
  None.
*/

static DALResult PlatformInfo_InitGlblCtxt
(
  PlatformInfoDrvCtxt *pDrvCtxt
)
{
  DALResult eResult;
  uint32 nSize, nKVPSSize;

  /*-----------------------------------------------------------------------*/
  /* Ensure global context has been initialized.                           */
  /*-----------------------------------------------------------------------*/

  DALGLBCTXT_Init();

  /*-----------------------------------------------------------------------*/
  /* Allocate the context.                                                 */
  /*-----------------------------------------------------------------------*/

  nKVPSSize = pDrvCtxt->nNumKVPS * sizeof(PlatformInfoKVPSType);
  nSize = sizeof(PlatformInfoGlbCtxType) + nKVPSSize;

  eResult = DALGLBCTXT_AllocCtxt("DAL_PLATFORM_INFO", nSize,
    0, (void **)&pDrvCtxt->pGlbCtxt);

  /*-----------------------------------------------------------------------*/
  /* Fill it in if possible.                                               */
  /*-----------------------------------------------------------------------*/

  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  pDrvCtxt->pGlbCtxt->PlatformInfo = pDrvCtxt->PlatformInfo;
  pDrvCtxt->pGlbCtxt->nNumKVPS = pDrvCtxt->nNumKVPS;
  DALSYS_memscpy(pDrvCtxt->pGlbCtxt->aKVPS, nKVPSSize, pDrvCtxt->aKVPS, nKVPSSize);

  return DAL_SUCCESS;

} /* PlatformInfo_InitGlblCtxt */


/* =========================================================================
**  Function : PlatformInfo_InitSmem
** =========================================================================*/
/*
  Initializes and populates the SMEM (socinfo) location in which to store
  chip, platform, and build information.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
*/

static DALResult PlatformInfo_InitSMem
(
  PlatformInfoDrvCtxt *pDrvCtxt
)
{
  DalPlatformInfoSMemType     *pSMem;
  DalPlatformInfoSMemPMICType *aPMICInfo;
  DalDeviceHandle             *phChipInfo = NULL;
  pm_device_info_type          PmicDeviceInfo;
  DALResult                    eResult = DAL_SUCCESS;
  pm_err_flag_type             ePMICErr;
  uint32                       i, nPMICIndex, nNumPMICs;
  uint32                       nSize, nPMICArraySize;
  uint32                       nClusterArraySize = 0, nNumClusters = 0, nClusterIdx, nMask;
  uint32 nDisabledFeaturesArraySize = 0, nPartIdx;
  uint32 *aClusterArray, *aDisabledFeaturesArray;
  ChipInfoSKUType              SKUInfo = {0};
  msg_ram_err                  smem_err;
  uint32                       nKVPSSize = 0;
  PlatformInfoKVPSType        *aKVPSData = NULL;
  uint32                       nBootCluster, nBootCore, nNumFunctionalClusters;
  ChipInfoResult               eChipInfoResult;

  /*
   * Reads the disabled parts info from xbl_config file.
   */
  ChipInfo_UpdateDisabledFeaturesFromXblConfig();

  /*-----------------------------------------------------------------------*/
  /* Calculate array sizes and allocate SMEM.                              */
  /*-----------------------------------------------------------------------*/

  for (i = 0, nNumPMICs = 0;; i++)
  {
    ePMICErr = pm_get_pmic_info(i, &PmicDeviceInfo);
    if (ePMICErr == PM_ERR_FLAG_FEATURE_NOT_SUPPORTED)
    {
      break;
    }

    if (PmicDeviceInfo.ePmicModel != PMIC_IS_UNKNOWN)
    {
      nNumPMICs++;
    }
  }

  nPMICArraySize = sizeof(DalPlatformInfoSMemPMICType) * nNumPMICs;

  eResult = DAL_DeviceAttach(DALDEVICEID_CHIPINFO, &phChipInfo);
  if (eResult == DAL_SUCCESS)
  {
    for (nNumClusters = 0;; nNumClusters++)
    {
      eResult = DalChipInfo_GetDisabledCPUs(phChipInfo, nNumClusters, &nMask);
      if (eResult == DAL_ERROR_OUT_OF_RANGE_PARAMETER)
      {
        break;
      }
    }
    nClusterArraySize = sizeof(uint32) * nNumClusters;

    nDisabledFeaturesArraySize = sizeof(uint32) * CHIPINFO_NUM_PARTS;
  }

  nKVPSSize = pDrvCtxt->nNumKVPS * sizeof(PlatformInfoKVPSType);

  nSize = sizeof(DalPlatformInfoSMemType) + nClusterArraySize + nDisabledFeaturesArraySize + nPMICArraySize + nKVPSSize;
  nSize += PLATFORMINFO_SMEM_MARKETING_DATA_SIZE_BYTES;

  pSMem = (DalPlatformInfoSMemType *) smem_alloc(SMEM_HW_SW_BUILD_ID, nSize);
  if (pSMem == NULL)
  {
    return DAL_ERROR;
  }

  DALSYS_memset(pSMem, 0, nSize);

  /*-----------------------------------------------------------------------*/
  /* Get misc information.                                                 */
  /*-----------------------------------------------------------------------*/

  pSMem->nFormat = DALPLATFORMINFO_SMEM_FORMAT;


  /*-----------------------------------------------------------------------*/
  /* Get chip information.                                                 */
  /*-----------------------------------------------------------------------*/

  if (phChipInfo != NULL)
  {
    DalChipInfo_GetChipId(phChipInfo, (DalChipInfoIdType *)&pSMem->eChipId);
    DalChipInfo_GetChipVersion(phChipInfo, &pSMem->nChipVersion);
    DalChipInfo_GetRawChipId(phChipInfo, &pSMem->nRawChipId);
    DalChipInfo_GetRawChipVersion(phChipInfo, &pSMem->nRawChipVersion);
    DalChipInfo_GetFoundryId(phChipInfo,
      (DalChipInfoFoundryIdType *)&pSMem->nFoundryId);
    DalChipInfo_GetSerialNumber(phChipInfo, &pSMem->nChipSerial);
    DalChipInfo_GetChipFamily(phChipInfo, &pSMem->nChipFamily);
    DalChipInfo_GetRawDeviceFamily(phChipInfo, &pSMem->nRawDeviceFamily);
    DalChipInfo_GetRawDeviceNumber(phChipInfo, &pSMem->nRawDeviceNumber);
    DalChipInfo_GetChipIdString(phChipInfo, pSMem->szChipIdStr, DALPLATFORMINFO_SMEM_MAX_CHIP_ID_LENGTH);
    DalChipInfo_GetQFPROMChipId(phChipInfo, &pSMem->nQFPROMChipId);
    DalChipInfo_GetModemSupport(phChipInfo, &pSMem->nModemSupported);

    pSMem->nNumClusters = nNumClusters;
    pSMem->nClusterArrayOffset = sizeof(DalPlatformInfoSMemType);
    aClusterArray = (uint32 *)((uintnt)pSMem + pSMem->nClusterArrayOffset);
    for (nClusterIdx = 0; nClusterIdx < nNumClusters; nClusterIdx++)
    {
      eResult = DalChipInfo_GetDisabledCPUs(phChipInfo, nClusterIdx, &nMask);
      if (eResult != DAL_SUCCESS)
      {
        break;
      }
      aClusterArray[nClusterIdx] = nMask;
    }

    pSMem->nNumParts = CHIPINFO_NUM_PARTS;
    pSMem->nDisabledFeaturesArrayOffset = sizeof(DalPlatformInfoSMemType) + nClusterArraySize;
    aDisabledFeaturesArray = (uint32 *)((uintnt)pSMem + pSMem->nDisabledFeaturesArrayOffset);
    for (nPartIdx = 1 /* 0 is CHIPINFO_PART_UNKNOWN so iterating from 1.*/; nPartIdx < CHIPINFO_NUM_PARTS; nPartIdx++)
    {
	  /*
		* nIdx (second parameter) is unsed currently, so keeping it 0x0 for now.
		* Need to update this once we start supporting the multiple instances of the IP(s)
	  */

      eChipInfoResult = ChipInfo_GetDisabledFeatures(nPartIdx, 0, &nMask);
      if (eChipInfoResult != CHIPINFO_SUCCESS)
      {
        break;
      }
      aDisabledFeaturesArray[nPartIdx] = nMask;
    }

    eChipInfoResult = ChipInfo_GetNumFunctionalClusters(&nNumFunctionalClusters);
    if (eChipInfoResult == CHIPINFO_SUCCESS)
    {
      pSMem->nNumFunctionalClusters = nNumFunctionalClusters;
    }

    eChipInfoResult = ChipInfo_GetBootClusterAndCore(&nBootCluster, &nBootCore);
    if (eChipInfoResult == CHIPINFO_SUCCESS)
    {
      pSMem->nBootCluster = nBootCluster;
      pSMem->nBootCore = nBootCore;
    }

    /*
     * No return value check since it isn't relevant to this function.
     * Just copy SKUInfo into SMEM directly. If it's invalid, ChipInfo
     * will need to handle it.
    */
    ChipInfo_GetSKU(&SKUInfo);
    pSMem->eFeatureCode = SKUInfo.eFeatureCode;
    pSMem->ePCode = SKUInfo.ePCode;

    // Reserve space for the marketing data array.
    // This will be filled by TZ, on PLs that use TZ. It will be left
    // at 0 for other PLs.
    pSMem->nPartNameMapOffset = pSMem->nDisabledFeaturesArrayOffset + nDisabledFeaturesArraySize;
    pSMem->nNumPartNameMappings = 0;
  }

  /*-----------------------------------------------------------------------*/
  /* Get platform information.                                             */
  /*-----------------------------------------------------------------------*/

  pSMem->ePlatformType = pDrvCtxt->PlatformInfo.platform;
  pSMem->nPlatformVersion = pDrvCtxt->PlatformInfo.version;
  pSMem->nPlatformSubtype = pDrvCtxt->PlatformInfo.subtype;
  pSMem->bFusion = pDrvCtxt->PlatformInfo.fusion;
  pSMem->nOEMVariantID = pDrvCtxt->PlatformInfo.OEMVariantID;

  /*-----------------------------------------------------------------------*/
  /* Get PMIC information.                                                 */
  /*-----------------------------------------------------------------------*/

  pSMem->nNumPMICs = nNumPMICs;
  pSMem->nPMICArrayOffset = sizeof(DalPlatformInfoSMemType)
    + nClusterArraySize + nDisabledFeaturesArraySize + PLATFORMINFO_SMEM_MARKETING_DATA_SIZE_BYTES;
  aPMICInfo =
    (DalPlatformInfoSMemPMICType *)((uintnt)pSMem + pSMem->nPMICArrayOffset);

  for (i = 0, nPMICIndex = 0;; i++)
  {
    ePMICErr = pm_get_pmic_info(i, &PmicDeviceInfo);
    if (ePMICErr == PM_ERR_FLAG_FEATURE_NOT_SUPPORTED || nPMICIndex >= nNumPMICs)
    {
      break;
    }

    if (PmicDeviceInfo.ePmicModel != PMIC_IS_UNKNOWN)
    {
      aPMICInfo[nPMICIndex].nPMICModel =
        ((PLATFORMINFO_PMIC_FAMILY_B << 16) | (PmicDeviceInfo.ePmicModel));

      aPMICInfo[nPMICIndex].nPMICVersion =
        DALPLATFORMINFO_VERSION(PmicDeviceInfo.nPmicAllLayerRevision,
                                PmicDeviceInfo.nPmicMetalRevision);

      nPMICIndex++;
    }
  }

  /*
   * Copy up to three PMICs from main array into legacy array.
   */
  DALSYS_memscpy(pSMem->aPMICInfo, sizeof(pSMem->aPMICInfo),
    aPMICInfo, nPMICArraySize);

  /*
   * Store the SMEM base address in MSG_RAM so that images without SMEM
   * which have access to MSG_RAM (like AOP) can retrieve ChipInfo as well.
   */
  smem_err = msg_ram_set_smem_address(SMEM_HW_SW_BUILD_ID, (uint32)(uintptr_t)pSMem);
  if (smem_err != MSG_RAM_SET_SUCCESS)
  {
    DALSYS_Free(pSMem);
    return DAL_ERROR;
  }

  pSMem->nKVPSOffset = pSMem->nPMICArrayOffset + nPMICArraySize;
  pSMem->nNumKVPS = pDrvCtxt->nNumKVPS;

  aKVPSData = (PlatformInfoKVPSType *)((uintnt)pSMem + pSMem->nKVPSOffset);

  DALSYS_memscpy(aKVPSData, nKVPSSize, pDrvCtxt->aKVPS, nKVPSSize);

  return DAL_SUCCESS;

} /* END PlatformInfo_InitSMem */


/* =========================================================================
**  Function : PlatformInfo_InitRPM
** =========================================================================*/
/*
  Initialize and populate the IMEM location used to communicate to RPM.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
*/

static DALResult PlatformInfo_InitRPM
(
  PlatformInfoDrvCtxt *pDrvCtxt
)
{
  PlatformInfoRPMType *pRPM;
  uint32 nKVPSSize;
  DALResult eResult;

  eResult = PlatformInfo_GetPropertyValue("rpm_buffer_addr", (void **)&pRPM);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  pRPM->PlatformInfo = pDrvCtxt->PlatformInfo;
  pRPM->nNumKVPS = pDrvCtxt->nNumKVPS;
  if (pRPM->nNumKVPS > 0)
  {
    nKVPSSize = pRPM->nNumKVPS * sizeof(PlatformInfoKVPSType);
    DALSYS_memscpy(pRPM->aKVPS, nKVPSSize, pDrvCtxt->aKVPS, nKVPSSize);
  }

  return DAL_SUCCESS;

} /* END PlatformInfo_InitRPM */


/* =========================================================================
**  Function : PlatformInfo_DeviceTreeInit
** =========================================================================*/
/*
  Initialize and populate the platform info by reading device tree.

  @param **ppPlatformInfo [out] -- pointer to platform info structure that will
                                   contain the data read from device tree.
*/

static DALResult PlatformInfo_DeviceTreeInit
(
  uint8_t **ppPlatformInfo
)
{
  fdt_node_handle node;
  uint32_t nPlatInfoSize = 0;
  int nDTResult = 0;
  DALResult eResult = DAL_SUCCESS;

  nDTResult = fdt_get_node_handle(&node, NULL, PLATINFO_DTB_NODE);
  if (nDTResult != FDT_ERR_QC_NOERROR)
  {
    return DAL_ERROR;
  }

  /*
   * Platform info was located in the device tree.
   * Allocate memory to store the platform info.
   */
  nDTResult = fdt_get_prop_size(&node, "PlatformInfo", &nPlatInfoSize);
  if (nDTResult != FDT_ERR_QC_NOERROR)
  {
    return DAL_ERROR;
  }

  eResult = DALSYS_Malloc(nPlatInfoSize, (void **)ppPlatformInfo);
  if (eResult != DAL_SUCCESS)
  {
    return eResult;
  }

  /*
   * Populate the data
   */
  nDTResult = fdt_get_uint8_prop_list(&node, "PlatformInfo", (uint8_t*)*ppPlatformInfo, nPlatInfoSize);
  if (nDTResult != FDT_ERR_QC_NOERROR)
  {
    return DAL_ERROR;
  }

  return DAL_SUCCESS;

} /* END PlatformInfo_DeviceTreeInit */


/* =========================================================================
**  Function : PlatformInfo_CDTInit
** =========================================================================*/
/*
  Populate the platform information based on data from the CDT.

  @param *pDrvCtxt [in] -- Handle to the DAL driver context.
  @param *pPlatformInfo [in] -- Pointer to the CDT data.
*/

static DALResult PlatformInfo_CDTInit
(
  PlatformInfoDrvCtxt *pDrvCtxt,
  uint8_t *pCDT
)
{
  static boolean bCDTInitialized = FALSE;
  DALResult eResult;
  uint32 nSize, i, nVal;
  PlatformInfoKVPSCDTType *aKVPs;
  PlatformInfoCDTType *pPlatformInfo;
  uint32_t nOEMOverride;

  if (bCDTInitialized == TRUE)
  {
    return DAL_SUCCESS;
  }

  if (pCDT == NULL)
  {
    /*
     * Platform info was not found in storage media. Try to read device tree.
     */
    eResult = PlatformInfo_DeviceTreeInit(&pCDT);
    if (eResult != DAL_SUCCESS || pCDT == NULL)
    {
      /*
       * Platform info could not be read from device tree.
       * Fall back to default values.
       */
      pCDT = (uint8_t *)&gPlatInfoCDTDefault;
    }
  }

  pPlatformInfo = (PlatformInfoCDTType *)pCDT;

  /*-----------------------------------------------------------------------*/
  /* Get platform type.                                                    */
  /*-----------------------------------------------------------------------*/
  /*
   * Only update the platform type if it hasn't already been set through
   * scripts or detecting pre-sil.
   */
  if (pDrvCtxt->PlatformInfo.platform == DALPLATFORMINFO_TYPE_UNKNOWN)
  {
    pDrvCtxt->PlatformInfo.platform =
      (DalPlatformInfoPlatformType)pPlatformInfo->nPlatform;
  }


  /*-----------------------------------------------------------------------*/
  /* Get platform version.                                                 */
  /*-----------------------------------------------------------------------*/

  pDrvCtxt->PlatformInfo.version =
    DALPLATFORMINFO_VERSION(pPlatformInfo->nHWVersionMajor,
                            pPlatformInfo->nHWVersionMinor);

  /*-----------------------------------------------------------------------*/
  /* Get platform sub-type.                                                */
  /*-----------------------------------------------------------------------*/

  if (pPlatformInfo->nVersion >= 2)
  {
    pDrvCtxt->PlatformInfo.subtype = pPlatformInfo->nSubtype;
  }

  /*-----------------------------------------------------------------------*/
  /* Get key-value pairs.                                                  */
  /*-----------------------------------------------------------------------*/

  if (pPlatformInfo->nVersion >= 3)
  {
    if (pPlatformInfo->nVersion == 3)
    {
      pDrvCtxt->nNumKVPS = ((PlatformInfoCDTType_v3 *)pPlatformInfo)->nNumKVPS;
      aKVPs = ((PlatformInfoCDTType_v3 *)pPlatformInfo)->aKVPS;
    }
    else
    {
      pDrvCtxt->nNumKVPS = pPlatformInfo->nNumKVPS;
      aKVPs = pPlatformInfo->aKVPS;
    }

    if (pDrvCtxt->nNumKVPS > 0)
    {
      nSize = pDrvCtxt->nNumKVPS * sizeof(PlatformInfoKVPSType);
      eResult = DALSYS_Malloc(nSize, (void **)&pDrvCtxt->aKVPS);
      if (eResult != DAL_SUCCESS)
      {
        return DAL_ERROR;
      }

      for (i = 0; i < pDrvCtxt->nNumKVPS; i++)
      {
        pDrvCtxt->aKVPS[i].nKey = aKVPs[i].nKey;
        pDrvCtxt->aKVPS[i].nValue = aKVPs[i].nValue;
      }
    }

    /*-----------------------------------------------------------------------*/
    /* Get Fusion.                                                           */
    /*-----------------------------------------------------------------------*/

    eResult =
      PlatformInfo_GetKeyValue(DALPLATFORMINFO_KEY_FUSION, &nVal);
    if (eResult == DAL_SUCCESS)
    {
      pDrvCtxt->PlatformInfo.fusion = nVal;
    }
  }

  if (pPlatformInfo->nVersion >= 5)
  {
    pDrvCtxt->PlatformInfo.OEMVariantID = pPlatformInfo->nOEMVariantID;
  }


  // Apply any OEMVariant overrides that the OEM specified via ADC, GPIO, etc.
  // This also requires that they create an OEMInfo.dtsi. See the OEMInfo driver.
  nOEMOverride = OEMInfo_GetVariant();
  if (nOEMOverride)
  {
    pDrvCtxt->PlatformInfo.OEMVariantID = nOEMOverride;
  }

  bCDTInitialized = TRUE;
  return DAL_SUCCESS;

} /* END PlatformInfo_CDTInit */


/* =========================================================================
**  Function : PlatformInfo_CDTConfigPreDDR
** =========================================================================*/
/*
  See DDIPlatformInfo.h
*/

DALResult PlatformInfo_CDTConfigPreDDR
(
  void                *pPlatformInfo
)
{
  PlatformInfoDrvCtxt *pDrvCtxt = PlatformInfo_GetDrvCtxt();
  DALResult eResult;

  /*
   * Initialize CDT data.
   */
  eResult = PlatformInfo_CDTInit(pDrvCtxt, pPlatformInfo);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  /*
   * Initialize the location for communication to RPM.
   */
  PlatformInfo_InitRPM(pDrvCtxt);

  return DAL_SUCCESS;

} /* END PlatformInfo_CDTConfigPreDDR*/


/* =========================================================================
**  Function : PlatformInfo_CDTConfigPostDDR
** =========================================================================*/
/*
  See DDIPlatformInfo.h
*/

DALResult PlatformInfo_CDTConfigPostDDR
(
  void                *pPlatformInfo
)
{
  PlatformInfoDrvCtxt *pDrvCtxt = PlatformInfo_GetDrvCtxt();
  DALResult eResult;

  /*
   * Initialize CDT data.
   */
  eResult = PlatformInfo_CDTInit(pDrvCtxt, pPlatformInfo);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  /*
   * Initialize the DAL global context.
   */
  PlatformInfo_InitGlblCtxt(pDrvCtxt);

  /*
   * Initialize the SMEM (socinfo) location.
   */
  eResult = PlatformInfo_InitSMem(pDrvCtxt);
  if (eResult != DAL_SUCCESS)
  {
    return DAL_ERROR;
  }

  return DAL_SUCCESS;
}
