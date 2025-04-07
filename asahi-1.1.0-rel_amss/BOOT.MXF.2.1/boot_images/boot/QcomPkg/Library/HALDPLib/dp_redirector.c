/*=====================================================================================================================
  Copyright (c) 2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  =====================================================================================================================*/

/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/
#include "dp_i.h"
#include "dp_redirector.h"
#include "dp_sim.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------------------------------------
 * Defines and Macros
 *-------------------------------------------------------------------------------------------------------------------*/

// Maximum redirected sections with the AUX redirector
#define MAX_REDIRECT_SECTIONS                4

// Get redirector context depending on device id.
#define GET_REDIRECT_CTX_FROM_ID(_deviceId_) (&(gsRedirectCtx[((_deviceId_)<DP_DEVICE_MAX)?(_deviceId_):DP_DEVICE_ID_ALT_MODE_0]))

/*---------------------------------------------------------------------------------------------------------------------
 * Structures and Enumerations
 *-------------------------------------------------------------------------------------------------------------------*/

/* Types of DP AUX Functions that can be redirected to */
typedef enum
{
  DP_REDIRECT_FUNCTION_PHYSICAL = 0, /**< AUX physical function */
  DP_REDIRECT_FUNCTION_SIM,          /**< AUX SIM function */
  DP_REDIRECT_FUNCTION_DUMMY,        /**< AUX dummy fail/success function */
  DP_REDIRECT_FUNCTION_MAX,
  DP_REDIRECT_FUNCTION_FORCE_32BIT  = 0x7FFFFFFF
} DP_RedirectFunctionType;

/* Defines the transaction directions the AUX redirector can match against. */
typedef enum
{
  DP_REDIRECT_DIR_READ         = 0x00000000,  /**< Represents a read transaction */
  DP_REDIRECT_DIR_WRITE,                      /**< Represents a write transaction */
  DP_REDIRECT_DIR_READ_WRITE,                 /**< Represents a read or write transaction */
  DP_REDIRECT_DIR_FORCE_32BIT  = 0x7FFFFFFF
} DP_RedirectDirType;

/* Defines the transaction sections the AUX redirector can match against. */
typedef enum
{
  DP_REDIRECT_SECTION_ALL = 0,        /**< Any AUX section */
  DP_REDIRECT_SECTION_EDID,           /**< EDID AUX section */
  DP_REDIRECT_SECTION_DPCD_CAPS,      /**< DPCD Caps AUX section */
  DP_REDIRECT_SECTION_DPCD_STATUS,    /**< DPCD Status AUX section*/
  DP_REDIRECT_SECTION_EXT_DPCD_CAPS,  /**< Extended DPCD caps AUX section */
  DP_REDIRECT_SECTION_MAX,
  DP_REDIRECT_SECTION_FORCE_32BIT
} DP_RedirectSectionType;

/* Configuration for an AUX redirector section. */
typedef struct
{
  DP_RedirectSectionType  eSection;      /**< Section of AUX transaction, implies transaction mode */
  DP_RedirectDirType      eDir;          /**< Type of AUX transaction (read / write / read & write) */
  DP_RedirectFunctionType eAUXFunction;  /**< AUX Function Type to redirect to */
  bool32                  bOnlyFallback; /**< Only use this configuration when display has failed */
  union
  {
    DP_DeviceIDType      eDeviceId;      /**< For DP_REDRICT_FUNCTION_PHYSICAL, the device to send AUX to */
    bool32               bDummySuccess;  /**< For DP_REDRICT_FUNCTION_DUMMY, what status to report */
  } sTarget;
} DP_RedirectConfigType;

/* Stored redirector context per device */
typedef struct
{
  DP_RedirectConfigType aCfgs[MAX_REDIRECT_SECTIONS]; /**< Redirect configs for a device */
  uint32                uNumCfgs;                     /**< Number of redirect configs */
} DP_RedirectorCtxType;

/*---------------------------------------------------------------------------------------------------------------------
 * Global Data Definitions
 *-------------------------------------------------------------------------------------------------------------------*/

/* LUT to map from DP_TransactionSectionType to beginning and end address range */
static uint32 gaRedirectSectionToAddrRange[DP_REDIRECT_SECTION_MAX][2] =
{
  {0x00000000, 0xffffffff}, // DP_AUX_REDIRECT_SECTION_ALL
  {0x00000000, 0xffffffff}, // DP_AUX_REDIRECT_SECTION_EDID (Whole I2C range for now)
  {0x00000000, 0x000000ff}, // DP_AUX_REDIRECT_SECTION_DPCD_CAPS
  {0x00000200, 0x000002ff}, // DP_AUX_REDIRECT_SECTION_DPCD_STATUS
  {0x00002200, 0x000022ff}, // DP_AUX_REDIRECT_SECTION_EXT_DPCD_CAPS
};

/* LUT to map from DP_TransactionSectionType to DP_TransactionModeType */
static DP_TransactionModeType geRedirectSectionToMode[DP_REDIRECT_SECTION_MAX] =
{
  DP_TRANSACTION_MODE_NONE, // DP_AUX_REDIRECT_SECTION_ALL
  DP_TRANSACTION_MODE_I2C,  // DP_AUX_REDIRECT_SECTION_EDID
  DP_TRANSACTION_MODE_AUX,  // DP_AUX_REDIRECT_SECTION_DPCD_CAPS
  DP_TRANSACTION_MODE_AUX,  // DP_AUX_REDIRECT_SECTION_DPCD_STATUS
  DP_TRANSACTION_MODE_AUX,  // DP_AUX_REDIRECT_SECTION_EXT_DPCD_CAPS
};

static DP_RedirectorCtxType gsRedirectCtx[DP_DEVICE_MAX];

/*---------------------------------------------------------------------------------------------------------------------
 * Private Functions
 *-------------------------------------------------------------------------------------------------------------------*/

//-------------------------------------------------------------------------------------------------
//  GetMatchingRedirectConfig
//
//  @brief
//      Search through a list of AUX redirector section configs for one that matches the transaction.
//
//  @params
//      [IN] pConfigs
//          List of AUX redirector section configurations.
//      [IN] uNumConfigs
//          Number of AUX configurations provided in list.
//      [IN] eTransactionDir
//          Direction of transaction to match config against.
//      [IN] eTransactionMode
//          Mode of transaction to match config against.
//      [IN] uAddress
//          Address of transaction to match against.
//      [IN] bFallbackMode
//          Whether or not to match against fallback only configurations.
//
//  @return
//      A pointer to a matching DP_RedirectConfigType or NULL if none.
//-------------------------------------------------------------------------------------------------
//
static DP_RedirectConfigType *GetMatchingRedirectConfig(DP_RedirectConfigType  *pConfigs,
                                                        uint32                  uNumConfigs,
                                                        DP_RedirectDirType      eTransactionDir,
                                                        DP_TransactionModeType  eTransactionMode,
                                                        uint32                  uAddress,
                                                        bool32                  bFallbackMode)
{
  DP_RedirectConfigType *pFoundConfig = NULL;

  for (uint32 uConfig = 0; uConfig < uNumConfigs; uConfig++)
  {
    if ((TRUE == pConfigs[uConfig].bOnlyFallback) &&
        (FALSE == bFallbackMode))
    {
      // Skip fallback only configurations when not in fallback mode.
    }
    else if ((DP_REDIRECT_DIR_READ_WRITE != pConfigs[uConfig].eDir) &&
             (eTransactionDir != pConfigs[uConfig].eDir))
    {
      // Skip configurations that don't match the transaction direction.
    }
    else if ((DP_REDIRECT_SECTION_ALL != pConfigs[uConfig].eSection) &&
             (eTransactionMode != geRedirectSectionToMode[pConfigs[uConfig].eSection]))
    {
      // Skip configurations that don't match the transaction section by mode.
    }
    else if ((DP_REDIRECT_SECTION_ALL != pConfigs[uConfig].eSection) &&
             ((uAddress < gaRedirectSectionToAddrRange[pConfigs[uConfig].eSection][0]) ||
              (uAddress > gaRedirectSectionToAddrRange[pConfigs[uConfig].eSection][1])))
    {
      // Skip configurations that don't match the transaction section by address.
    }
    else
    {
      pFoundConfig = &pConfigs[uConfig];
      break;
    }
  }
  return pFoundConfig;
}

/*---------------------------------------------------------------------------------------------------------------------
 * Public Functions
 *-------------------------------------------------------------------------------------------------------------------*/

//-------------------------------------------------------------------------------------------------
//  DP_Redirector_ConfigureOverrides
//
//  @brief
//      Configure redirector with provided overrides.
//
//  @params
//      [IN] eDeviceID
//          DP Device ID to configure.
//      [IN] pOverrideCfg
//          Override configuration containing buffers to replace and mode of override.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
DP_Status DP_Redirector_ConfigureOverrides(DP_DeviceIDType         eDeviceID,
                                           DP_Config_OverrideType *pOverrideCfg)
{
  DP_Status eStatus = DP_STATUS_SUCCESS;

  if ((NULL == pOverrideCfg) ||
      (NULL == pOverrideCfg->pBufs) ||
      (eDeviceID > DP_DEVICE_MAX))
  {
    DP_LOG_MESSAGE_ERROR("DP_Redirector_ConfigureOverrides: Invalid Parameter.");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    DP_RedirectorCtxType *pRedirectCtx  = GET_REDIRECT_CTX_FROM_ID(eDeviceID);
    bool32                bOnlyFallback = (pOverrideCfg->eMode == MDP_DP_OVERRIDE_MODE_FALLBACK) ? TRUE : FALSE;
    uint32                uCfg          = 0;

    DISP_OSAL_MemZero(pRedirectCtx, sizeof(DP_RedirectorCtxType));

    // Load EDID buffer into SIM if it exists and redirect to it.
    if ((NULL != pOverrideCfg->pBufs->sEDID.pBuffer) &&
        (pOverrideCfg->pBufs->sEDID.uSize > 0))
    {
      if (MAX_REDIRECT_SECTIONS == uCfg)
      {
        DP_LOG_MESSAGE_ERROR("DP_Redirector_ConfigureOverrides: Hit maximum redirected sections (%d).", uCfg);
      }
      else if (!SIM_LoadSection((SIM_DeviceIDType)eDeviceID,
                                SIM_SECTION_EDID,
                                pOverrideCfg->pBufs->sEDID.pBuffer,
                                pOverrideCfg->pBufs->sEDID.uSize))
      {
        DP_LOG_MESSAGE_ERROR("DP_Redirector_ConfigureOverrides: Failed to load section into SIM, skipping buffer.");
      }
      else
      {
        pRedirectCtx->aCfgs[uCfg].eSection      = DP_REDIRECT_SECTION_EDID;
        pRedirectCtx->aCfgs[uCfg].eDir          = DP_REDIRECT_DIR_READ_WRITE;
        pRedirectCtx->aCfgs[uCfg].eAUXFunction  = DP_REDIRECT_FUNCTION_SIM;
        pRedirectCtx->aCfgs[uCfg].bOnlyFallback = bOnlyFallback;
        uCfg++;
      }
    }

    // Load DPCD caps buffer into SIM if it exists and redirect to it.
    if ((NULL != pOverrideCfg->pBufs->sDPCDCaps.pBuffer) &&
        (pOverrideCfg->pBufs->sDPCDCaps.uSize > 0))
    {

      if (MAX_REDIRECT_SECTIONS == uCfg)
      {
        DP_LOG_MESSAGE_ERROR("DP_Redirector_ConfigureOverrides: Hit maximum redirected sections (%d).", uCfg);
      }
      else if (!SIM_LoadSection((SIM_DeviceIDType)eDeviceID,
                                SIM_SECTION_DPCD_CAPS,
                                pOverrideCfg->pBufs->sDPCDCaps.pBuffer,
                                pOverrideCfg->pBufs->sDPCDCaps.uSize))
      {
        DP_LOG_MESSAGE_ERROR("DP_Redirector_ConfigureOverrides: Failed to load DPCD caps into SIM, skipping buffer.");
      }
      else
      {
        pRedirectCtx->aCfgs[uCfg].eSection      = DP_REDIRECT_SECTION_DPCD_CAPS;
        pRedirectCtx->aCfgs[uCfg].eDir          = DP_REDIRECT_DIR_READ;
        pRedirectCtx->aCfgs[uCfg].eAUXFunction  = DP_REDIRECT_FUNCTION_SIM;
        pRedirectCtx->aCfgs[uCfg].bOnlyFallback = bOnlyFallback;
        uCfg++;
      }
    }

    // Load DPCD status buffer into SIM if it exists and redirect to it.
    if ((NULL != pOverrideCfg->pBufs->sDPCDStatus.pBuffer) &&
        (pOverrideCfg->pBufs->sDPCDStatus.uSize > 0))
    {
      if (MAX_REDIRECT_SECTIONS == uCfg)
      {
        DP_LOG_MESSAGE_ERROR("DP_Redirector_ConfigureOverrides: Hit maximum redirected sections (%d).", uCfg);
      }
      else if (!SIM_LoadSection((SIM_DeviceIDType)eDeviceID,
                                SIM_SECTION_DPCD_STATUS,
                                pOverrideCfg->pBufs->sDPCDStatus.pBuffer,
                                pOverrideCfg->pBufs->sDPCDStatus.uSize))
      {
        DP_LOG_MESSAGE_ERROR("DP_Redirector_ConfigureOverrides: Failed to load DPCD status into SIM, skipping buffer.");
      }
      else
      {
        pRedirectCtx->aCfgs[uCfg].eSection      = DP_REDIRECT_SECTION_DPCD_STATUS;
        pRedirectCtx->aCfgs[uCfg].eDir          = DP_REDIRECT_DIR_READ;
        pRedirectCtx->aCfgs[uCfg].eAUXFunction  = DP_REDIRECT_FUNCTION_SIM;
        pRedirectCtx->aCfgs[uCfg].bOnlyFallback = bOnlyFallback;
        uCfg++;
      }
    }

    // Other writes default to dummy success when the display is in a failed state
    pRedirectCtx->aCfgs[uCfg].eSection              = DP_REDIRECT_SECTION_ALL;
    pRedirectCtx->aCfgs[uCfg].eDir                  = DP_REDIRECT_DIR_WRITE;
    pRedirectCtx->aCfgs[uCfg].eAUXFunction          = DP_REDIRECT_FUNCTION_DUMMY;
    pRedirectCtx->aCfgs[uCfg].sTarget.bDummySuccess = TRUE;
    pRedirectCtx->aCfgs[uCfg].bOnlyFallback         = TRUE;
    uCfg++;

    // Reads outside provided sections will try the real link and fail if the display is still unconnected

    pRedirectCtx->uNumCfgs = uCfg;
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_Redirector_ConfigureSlave
//
//  @brief
//      Configure redirector to redirect to a master AUX device for bonded mode.
//      EDIDs will be redirected to master, and failed DPCD sections will redirect to master on read.
//
//  @params
//      [IN] eDeviceID
//          DP Device ID to configure.
//      [IN] eMasterAUXDeviceID
//          Device ID of the master AUX.
//      [IN] pOverrideCfg
//          Override configuration containing buffers to replace and mode of override.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
DP_Status DP_Redirector_ConfigureSlave(DP_DeviceIDType         eDeviceID,
                                       DP_DeviceIDType         eMasterAUXDeviceID,
                                       DP_Config_OverrideType *pOverrideCfg)
{
  DP_Status eStatus = DP_STATUS_SUCCESS;

  if ((eDeviceID > DP_DEVICE_MAX) ||
      (eMasterAUXDeviceID > DP_DEVICE_MAX) ||
      (NULL == pOverrideCfg))
  {
    DP_LOG_MESSAGE_ERROR("DP_Redirector_ConfigureSlave: Invalid parameter provided.");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    DP_RedirectorCtxType *pRedirectCtx = GET_REDIRECT_CTX_FROM_ID(eDeviceID);

    DISP_OSAL_MemZero(pRedirectCtx, sizeof(DP_RedirectorCtxType));

    // NOTE: The following takes advantage of the fact that the AUX redirector uses the first matched configuration.

    // Regardless of panel state, redirect EDID to bonded master display
    pRedirectCtx->aCfgs[0].eSection              = DP_REDIRECT_SECTION_EDID;
    pRedirectCtx->aCfgs[0].eDir                  = DP_REDIRECT_DIR_READ_WRITE;
    pRedirectCtx->aCfgs[0].eAUXFunction          = DP_REDIRECT_FUNCTION_PHYSICAL;
    pRedirectCtx->aCfgs[0].sTarget.eDeviceId     = eMasterAUXDeviceID;
    pRedirectCtx->aCfgs[0].bOnlyFallback         = FALSE;

    // If panel has failed, non-EDID writes return dummy success and do nothing
    pRedirectCtx->aCfgs[1].eSection              = DP_REDIRECT_SECTION_ALL;
    pRedirectCtx->aCfgs[1].eDir                  = DP_REDIRECT_DIR_WRITE;
    pRedirectCtx->aCfgs[1].eAUXFunction          = DP_REDIRECT_FUNCTION_DUMMY;
    pRedirectCtx->aCfgs[1].sTarget.bDummySuccess = TRUE;
    pRedirectCtx->aCfgs[1].bOnlyFallback         = TRUE;

    // Redirect DPCD caps reads to master, if we have an override mode of REPLACE, and a provided buffer, then the
    // master display will have that section redirected to DP Sim, and we can use it with or without AUX failure.
    if ((MDP_DP_OVERRIDE_MODE_REPLACE == pOverrideCfg->eMode) &&
        (pOverrideCfg->pBufs->sDPCDCaps.uSize > 0)            &&
        (NULL != pOverrideCfg->pBufs->sDPCDCaps.pBuffer))
    {
      // Redirect DPCD caps reads to master always, if master has it replaced/overridden
      pRedirectCtx->aCfgs[2].bOnlyFallback = FALSE;
    }
    else
    {
      // Redirect DPCD caps reads to master only on fail, if master is using real AUX
      pRedirectCtx->aCfgs[2].bOnlyFallback = TRUE;
    }

    pRedirectCtx->aCfgs[2].eSection          = DP_REDIRECT_SECTION_DPCD_CAPS;
    pRedirectCtx->aCfgs[2].eDir              = DP_REDIRECT_DIR_READ;
    pRedirectCtx->aCfgs[2].eAUXFunction      = DP_REDIRECT_FUNCTION_PHYSICAL;
    pRedirectCtx->aCfgs[2].sTarget.eDeviceId = eMasterAUXDeviceID;

    // Redirect DPCD status reads to master, if we have an override mode of REPLACE, and a provided buffer, then the
    // master display will have that section redirected to DP Sim, and we can use it with or without AUX failure.
    if ((MDP_DP_OVERRIDE_MODE_REPLACE == pOverrideCfg->eMode) &&
        (pOverrideCfg->pBufs->sDPCDStatus.uSize > 0)          &&
        (NULL != pOverrideCfg->pBufs->sDPCDStatus.pBuffer))
    {
      // Redirect DPCD status reads to master always, if master has it replaced/overridden
      pRedirectCtx->aCfgs[3].bOnlyFallback = FALSE;
    }
    else
    {
      // Redirect DPCD status reads to master only on fail, if master is using real AUX
      pRedirectCtx->aCfgs[3].bOnlyFallback = TRUE;
    }

    pRedirectCtx->aCfgs[3].eSection          = DP_REDIRECT_SECTION_DPCD_STATUS;
    pRedirectCtx->aCfgs[3].eDir              = DP_REDIRECT_DIR_READ;
    pRedirectCtx->aCfgs[3].eAUXFunction      = DP_REDIRECT_FUNCTION_PHYSICAL;
    pRedirectCtx->aCfgs[3].sTarget.eDeviceId = eMasterAUXDeviceID;

    pRedirectCtx->uNumCfgs = 4;
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_Host_Redirector_ClientRead
//
//  @brief
//      This function will redirect AUX/I2C reads to SIM, a particular device, or a dummy function.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN/OUT] psReadPacket
//          The read packet.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_Redirector_ClientRead(DP_DisplayCtxType *pDisplayCtx,
                                        DP_ReadPacketType *psReadPacket)
{
  DP_Status         eStatus    = DP_STATUS_SUCCESS;
  DP_DeviceCtxType *pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType *pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx) ||
      (NULL == psReadPacket))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    DP_RedirectorCtxType *pRedirectCtx   = GET_REDIRECT_CTX_FROM_ID(pDeviceCtx->eDeviceID);
    bool32                bPanelFailsafe = DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_AUX_FAILSAFE) ? TRUE : FALSE;

    // Find first matching configuration for this transaction
    DP_RedirectConfigType *pSectionConfig = GetMatchingRedirectConfig(pRedirectCtx->aCfgs,
                                                                      pRedirectCtx->uNumCfgs,
                                                                      DP_REDIRECT_DIR_READ,
                                                                      psReadPacket->eTransactionType,
                                                                      psReadPacket->uAddress,
                                                                      bPanelFailsafe);

    if (NULL != pSectionConfig)
    {
      switch(pSectionConfig->eAUXFunction)
      {
        case DP_REDIRECT_FUNCTION_PHYSICAL:
        {
          // Redirect to MST stream 0 on another device by using a temporary display context
          DP_DisplayCtxType sTempDisplayCtx;

          sTempDisplayCtx.pDeviceCtx = DPHOST_GET_DEVICE_CTX_FROM_ID(pSectionConfig->sTarget.eDeviceId);
          sTempDisplayCtx.pStreamCtx = &sTempDisplayCtx.pDeviceCtx->aStreamCtx[DP_MST_STREAM_ID_0];

          if (pSectionConfig->sTarget.eDeviceId != pDeviceCtx->eDeviceID)
          {
            // Using DP_Host_AuxReadRawso that the target can also redirect
            eStatus = DP_Host_AuxReadRaw(&sTempDisplayCtx, psReadPacket);
          }
          else
          {
            // Avoid looping back to this function infinitely if "redirected" to normal AUX
            eStatus = DP_Host_AUX_ClientRead(&sTempDisplayCtx, psReadPacket);
          }
          break;
        }
        case DP_REDIRECT_FUNCTION_SIM:
        {
          eStatus = DP_Host_Simulation_ClientRead(pDisplayCtx, psReadPacket);
          break;
        }
        case DP_REDIRECT_FUNCTION_DUMMY:
        {
          if (pSectionConfig->sTarget.bDummySuccess)
          {
            // Dummy success reads don't make sense as we can't give back a valid read packet.
            eStatus = DP_STATUS_FAILED_RESOURCE_NOT_READY;
          }
          else
          {
            eStatus = DP_STATUS_FAILED_RESOURCE_FATAL_ERROR;
          }
          break;
        }
        default:
        {
          eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
          break;
        }
      }
    }
    else if ((!DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_AUX_FAILSAFE)) &&
             (DP_STATUS_SUCCESS != (eStatus = DP_Host_AUX_ClientRead(pDisplayCtx, psReadPacket))))
    {
      // If AUX fails and we aren't in failsafe, turn on panel failsafe mode
      DP_Host_SetAUXFailsafeMode(pDeviceCtx, pStreamCtx);

      // Try the transaction once again, allowing redirection.
      eStatus = DP_Host_AuxReadRaw(pDisplayCtx, psReadPacket);
    }
  }
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_Host_Redirector_ClientWrite
//
//  @brief
//      This function will redirect AUX/I2C writes to SIM, a particular device, or a dummy function
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN/OUT] psReadPacket
//          The read packet.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_Redirector_ClientWrite(DP_DisplayCtxType  *pDisplayCtx,
                                         DP_WritePacketType *psWritePacket)
{
  DP_Status         eStatus    = DP_STATUS_SUCCESS;
  DP_DeviceCtxType *pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType *pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx) ||
      (NULL == psWritePacket))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    DP_RedirectorCtxType *pRedirectCtx   = GET_REDIRECT_CTX_FROM_ID(pDeviceCtx->eDeviceID);
    bool32                bPanelFailsafe = DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_AUX_FAILSAFE) ? TRUE : FALSE;

    // Find first matching configuration for this transaction
    DP_RedirectConfigType *pSectionConfig = GetMatchingRedirectConfig(pRedirectCtx->aCfgs,
                                                                      pRedirectCtx->uNumCfgs,
                                                                      DP_REDIRECT_DIR_WRITE,
                                                                      psWritePacket->eTransactionType,
                                                                      psWritePacket->uAddress,
                                                                      bPanelFailsafe);

    if (NULL != pSectionConfig)
    {
      switch(pSectionConfig->eAUXFunction)
      {
        case DP_REDIRECT_FUNCTION_PHYSICAL:
        {
          // Redirect to MST stream 0 on another device by using a temporary display context
          DP_DisplayCtxType sTempDisplayCtx;

          sTempDisplayCtx.pDeviceCtx = DPHOST_GET_DEVICE_CTX_FROM_ID(pSectionConfig->sTarget.eDeviceId);
          sTempDisplayCtx.pStreamCtx = &sTempDisplayCtx.pDeviceCtx->aStreamCtx[DP_MST_STREAM_ID_0];

          if (pSectionConfig->sTarget.eDeviceId != pDeviceCtx->eDeviceID)
          {
            // Using DP_Host_AuxWriteRaw so that the target can also redirect
            eStatus = DP_Host_AuxWriteRaw(&sTempDisplayCtx, psWritePacket);
          }
          else
          {
            // Avoid looping back to this function infinitely if redirected to normal AUX
            eStatus = DP_Host_AUX_ClientWrite(&sTempDisplayCtx, psWritePacket);
          }
          break;
        }
        case DP_REDIRECT_FUNCTION_SIM:
        {
          eStatus = DP_Host_Simulation_ClientWrite(pDisplayCtx, psWritePacket);
          break;
        }
        case DP_REDIRECT_FUNCTION_DUMMY:
        {
          if (pSectionConfig->sTarget.bDummySuccess)
          {
            eStatus = DP_STATUS_SUCCESS;
          }
          else
          {
            eStatus = DP_STATUS_FAILED_RESOURCE_FATAL_ERROR;
          }
          break;
        }
        default:
        {
          eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
          break;
        }
      }
    }
    else if ((!DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_AUX_FAILSAFE)) &&
             (DP_STATUS_SUCCESS != (eStatus = DP_Host_AUX_ClientWrite(pDisplayCtx, psWritePacket))))
    {
      // If AUX fails and we aren't in failsafe, turn on panel failsafe mode
      DP_Host_SetAUXFailsafeMode(pDeviceCtx, pStreamCtx);

      // Try the transaction once again, allowing redirection.
      eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, psWritePacket);
    }
  }
  return eStatus;
}

#ifdef __cplusplus
}
#endif
