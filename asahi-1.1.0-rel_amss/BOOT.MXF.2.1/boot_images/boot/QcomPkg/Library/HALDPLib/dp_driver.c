/*=============================================================================

  File: dpdriver.c

  DP Panel driver

  Copyright (c) 2016-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/


/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include <Library/PcdLib.h>
#include "MDPLib_i.h"
#include "dp_i.h"
#include "dp_driver.h"
#include "DPInterface.h"
#include "dp_dsc.h"
#include "edid.h"

/* -----------------------------------------------------------------------
** Structure Types 
** ----------------------------------------------------------------------- */
/*!
* \b DPModeType
*
*  Mode information for DP
*/
typedef struct
{
  uint32 uIdxEDIDModeList;  /**< Index for this mode in sEDIDModeList which has all the info */
} DPModeType;

/*!
* \b DPDriverBondedModeConfigType
*
*  Internal structure for holding DP bonded mode configuration info
*/
typedef struct
{
  bool32          bEnabled;              /**< If display is operating in bonded mode */
  DP_DeviceIDType eSourceClockDeviceID;  /**< Device ID of the DP device providing the shared source clock */   
  uint32          uNumDevices;           /**< Number of DP devices driven in bonded mode */
  bool32          bExternalMasterDevice; /**< Master DP Device is not one of the DP devices driving the display */
  DP_DeviceIDType eMasterAUXDeviceID;    /**< Device ID of the DP device providing the master AUX */   
} DPDriverBondedModeConfigType;

/*!
* \b DPDriverConfigType
*
*  Internal structure for holding DP command data
*/
typedef struct {
  MDP_Display_IDType              eDisplayId;                                        /**< Physical display ID  */
  DP_HandleType                   hDPHandle[MDP_MAX_NUM_DP_DEVICES];                 /**< DP device handle for DP Host driver */
  DP_HandleType                   hDPHostRouterHandle;                               /**< DP device handle for DP Host Router driver */
  uint32                          uLastHostErrorCode;                                /**< DP last host error code for packet to peripheral */
  uint32                          uLastPanelErrorCode;                               /**< DP last panel error code for packet from peripheral */
  uint32                          uCmdBufSize;                                       /**< DP command buffer size */
  DPModeType                      sMode[DP_DRIVER_MAX_MODES];                        /**< Mode info */
  uint32                          uTotalModes;                                       /**< Total number of supported modes */
  DPDriverBondedModeConfigType    sBondedModeConfig;                                 /**< DP device bonded mode configuration info */
  uint8                           uPPSBuffer[MDP_PANEL_DSC_PPS_TOTAL_PACKET_SIZE];   /**< DP Sink DSC PPS buffer */
  MDP_DP_ConnectionModeType       eDPConnectionMode;                                 /**< DP display connection mode */
} DPDriverConfigType;

/* -----------------------------------------------------------------------
** Global variables
** ----------------------------------------------------------------------- */
DPDriverConfigType gDPDriverConfig[DP_DEVICE_NUM];

/* Table for MDP to DP connection polarity mapping */
DP_ConnectionStatusType gMDPToDPConnectionPolarityMapping[MDP_DP_ALTMODE_CONNECTION_POLARITY_MAX] = 
{
  DP_CONNECTION_STATUS_DISCONNECTED,              /**< MDP_DP_ALTMODE_CONNECTION_POLARITY_DISCONNECTED      */
  DP_CONNECTION_POLARITY_POLARITY_DEFAULT,        /**< MDP_DP_ALTMODE_CONNECTION_POLARITY_POLARITY_DEFAULT  */
  DP_CONNECTION_POLARITY_POLARITY_REVERSE,        /**< MDP_DP_ALTMODE_CONNECTION_POLARITY_POLARITY_REVERSE  */
};

/* Table for MDP to DP connection pin assignment mapping */
DP_ConnectionPinAssignment gMDPToDPConnectionPinMapping[MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_MAX] = 
{
  DP_CONNECTION_PINASSIGNMENT_INVALID,        /**< MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_INVALID   */
  DP_CONNECTION_PINASSIGNMENT_DFPD_A,         /**< MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_DFPD_A    */
  DP_CONNECTION_PINASSIGNMENT_DFPD_B,         /**< MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_DFPD_B    */
  DP_CONNECTION_PINASSIGNMENT_DFPD_C,         /**< MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_DFPD_C    */
  DP_CONNECTION_PINASSIGNMENT_DFPD_D,         /**< MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_DFPD_D    */
  DP_CONNECTION_PINASSIGNMENT_DFPD_E,         /**< MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_DFPD_E    */
  DP_CONNECTION_PINASSIGNMENT_DFPD_F,         /**< MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_DFPD_F    */
};

/* -----------------------------------------------------------------------
** Macro defines
** ----------------------------------------------------------------------- */
#define DPDRIVER_ARRAY_SIZE(arr)                 (sizeof((arr)) / sizeof(arr[0]))
#define DPDRIVER_GETMAX_CONTROLLERS(_dp_cfg_)    (((_dp_cfg_)->sBondedModeConfig.uNumDevices < MDP_MAX_NUM_DP_DEVICES) ? ((_dp_cfg_)->sBondedModeConfig.uNumDevices) : (MDP_MAX_NUM_DP_DEVICES))
#define DP_MODE_TIMING_SCALE_UNITY               100
#define DP_HOST_HANDLE_DEFAULT_INDEX             0
// Get the DP mode on a port
// Bit 0-1:DPTX0 (Port0), 2-3: DPTX1 (Port1), 4-5:DPTX2 (Port2)
#define DISPLAY_USB_GET_PORT_MODE(_value_, _port_) (((_value_) >> ((_port_) * 2)) & 0x3)

/* -----------------------------------------------------------------------
** Local Prototypes
** ----------------------------------------------------------------------- */
static void GetPanelAttributesFromPanelInfo(MDP_Panel_AttrType *pPanelAttr, 
                                            DP_PanelInfoType   *pPanelInfo);

static void ScaleModeTimings(DP_PanelInfoType *pPanelInfo,
                             uint32            uScale);

static void GetPanelInfoFromPanelAttributes(DP_PanelInfoType    *pPanelInfo,
                                            MDP_Panel_AttrType  *pPanelAttr);

static bool32 IsAltModeDevice(DP_DeviceIDType eDeviceID);

static DP_MSTStreamIDType GetStreamID(MDP_Display_IDType eDisplayId);

static bool32 IsDPTunnelingDevice(DP_DeviceIDType eDeviceID);

static DP_Status ConfigureGPIO(MDP_Display_IDType eDisplayId);

static MDP_DP_ControllerModeType GetControllerModeInfo(MDP_Display_IDType eDisplayId);
/* -----------------------------------------------------------------------
** Local functions
** ----------------------------------------------------------------------- */

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: GetDPDeviceIDFromDeviceIDMapping()
**
** DESCRIPTION:
**   Get the DP_DeviceIDType from the DP Device ID Mapping.
**
*//* -------------------------------------------------------------------- */
static DP_DeviceIDType GetDPDeviceIDFromDeviceIDMapping(uint32 uDeviceIDMapping)
{
  DP_DeviceIDType eDeviceID = DP_DEVICE_ID_NONE;
  
  switch (uDeviceIDMapping)
  {
  case MDP_DRIVER_DP_DEVICE_ID_ALT_MODE_0:
    eDeviceID = DP_DEVICE_ID_ALT_MODE_0;
    break;
  case MDP_DRIVER_DP_DEVICE_ID_ALT_MODE_1:
    eDeviceID = DP_DEVICE_ID_ALT_MODE_1;
    break;
  case MDP_DRIVER_DP_DEVICE_ID_ALT_MODE_2:
    eDeviceID = DP_DEVICE_ID_ALT_MODE_2;
    break;
  case MDP_DRIVER_DP_DEVICE_ID_EDP:
    eDeviceID = DP_DEVICE_ID_EDP;
    break;
  default:
    break;
  }

  return eDeviceID;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: GetDPDeviceID()
**
** DESCRIPTION:
**   Map MDP_Display_IDType to DP_DeviceIDType
**
*//* -------------------------------------------------------------------- */
static DP_DeviceIDType GetDPDeviceID(MDP_Display_IDType eDisplayId,
                                     uint32             uDeviceIndex)
{
  DP_DeviceIDType         eDeviceID  = DP_DEVICE_ID_NONE;
  MDP_Panel_AttrType     *pPanelAttr = MDP_GET_DISPLAYINFO(eDisplayId);

  if (TRUE == pPanelAttr->uAttrs.sDp.sBondedModeConfig.bEnabled)
  {
    if (uDeviceIndex < DPDRIVER_ARRAY_SIZE(pPanelAttr->uAttrs.sDp.sBondedModeConfig.uDeviceIDMapping))
    {
      eDeviceID = GetDPDeviceIDFromDeviceIDMapping(pPanelAttr->uAttrs.sDp.sBondedModeConfig.uDeviceIDMapping[uDeviceIndex]);
    }
  }
  else
  {
    switch (eDisplayId)
    {
    case MDP_DISPLAY_PRIMARY:
      eDeviceID = DP_DEVICE_ID_EDP;        /* DPTX3 --> primary eDP (eDP_0) */
      break;
    case MDP_DISPLAY_EXTERNAL:
    case MDP_DISPLAY_EXTERNAL2:
      eDeviceID = DP_DEVICE_ID_ALT_MODE_0; /* DPTX0 --> USB3_DP_PHY_PRI, DP over Type_c port 0 */
      break;
    case MDP_DISPLAY_EXTERNAL3:
    case MDP_DISPLAY_EXTERNAL4:
      eDeviceID = DP_DEVICE_ID_ALT_MODE_1; /* DPTX1 --> USB3_DP_PHY_SEC, DP over Type_c port 1 */
      break;
    case MDP_DISPLAY_EXTERNAL5:
    case MDP_DISPLAY_EXTERNAL6:
      eDeviceID = DP_DEVICE_ID_ALT_MODE_2; /* DPTX2 --> USB3_DP_PHY_SEC, DP over Type_c port 2 */
      break;
    default:
      break;
    }
  }

  return eDeviceID;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: GetDPDriverContext()
**
** DESCRIPTION:
**   Get local context for DP Driver
**
*//* -------------------------------------------------------------------- */
static DPDriverConfigType* GetDPDriverContext(MDP_Display_IDType eDisplayId)
{
  DPDriverConfigType *pContext  = NULL;
  DP_DeviceIDType     eDeviceID = GetDPDeviceID(eDisplayId, 0);

  if (1 == DP_DEVICE_NUM)
  {
     /* single device context means eDP only use only once device  context */
     pContext = &gDPDriverConfig[0];
  }
  else
  {
     if (DP_DEVICE_ID_NONE < eDeviceID &&
         DP_DEVICE_MAX     > eDeviceID)
     {
       pContext = &gDPDriverConfig[eDeviceID - 1];
     }
  }

  return pContext;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: GetStreamID()
**
** DESCRIPTION:
**   Map QDI_Display_IDType to DP_MSTStreamIDType
**
*//* -------------------------------------------------------------------- */
static DP_MSTStreamIDType GetStreamID(MDP_Display_IDType eDisplayId)
{
  DP_MSTStreamIDType eStreamID = DP_MST_STREAM_ID_0;

  switch (eDisplayId)
  {
  case MDP_DISPLAY_EXTERNAL2:
  case MDP_DISPLAY_EXTERNAL4:
  case MDP_DISPLAY_EXTERNAL6:
    eStreamID = DP_MST_STREAM_ID_1;
    break;
  default:
    break;
  }

  return eStreamID;
}

/* ----------------------------------------------------------------------
** FUNCTION: SetupOpenConfig()
**
** DESCRIPTION:
**    Setup the config for DP_Host_Open
**
-------------------------------------------------------------------- */
static void SetupOpenConfig(DPDriverConfigType    *pDPConfig,
                            MDP_Panel_AttrType    *pPanelConfig,
                            DP_HostOpenConfigType *pOpenConfig,
                            uint32                 uFlags,
                            uint32                 uDeviceIndex)
{
  if ((NULL == pDPConfig)    ||
      (NULL == pPanelConfig) || 
      (NULL == pOpenConfig))
  {
    DP_LOG_MESSAGE_ERROR("SetupOpenConfig: Invalid input ");
  }
  else
  {
    // Initialize the DP open context data
    MDP_OSAL_MEMZERO(pOpenConfig, sizeof(DP_HostOpenConfigType));

    bool32 bInternalDisplay = (pDPConfig->eDisplayId < MDP_DISPLAY_EXTERNAL) ? TRUE : FALSE;

    pOpenConfig->eDisplayID          = pDPConfig->eDisplayId;
    pOpenConfig->bReadDPCD           = TRUE;
    pOpenConfig->bReadEDID           = TRUE;
    pOpenConfig->uLaneSwingLevel     = DPCD_SPEC_MIN_VOLTAGE_SWING_LEVEL;
    pOpenConfig->uPreemphasisLevel   = DPCD_SPEC_MIN_PRE_EMPHASIS_LEVEL;
    pOpenConfig->eSSCMode            = (bInternalDisplay ? pPanelConfig->uAttrs.sDp.eSSCMode : FALSE);
    pOpenConfig->eBrightnessType     = pPanelConfig->sBacklightConfig.eBacklightType;

    switch (pDPConfig->eDPConnectionMode)
    {
      case MDP_DP_CONNECTION_MODE_ALT_MODE:
      {
        MDP_DP_AltModeConnectionPolarityType       eConnectionPolarity = (pPanelConfig->uAttrs.sDp.eConnectionPolarity < MDP_DP_ALTMODE_CONNECTION_POLARITY_MAX) ?
                                                                          pPanelConfig->uAttrs.sDp.eConnectionPolarity : MDP_DP_ALTMODE_CONNECTION_POLARITY_DISCONNECTED;
        MDP_DP_AltModeConnectionPinAssignmentType  ePinAssignment      = (pPanelConfig->uAttrs.sDp.eConnectionPinAssignment < MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_MAX) ?
                                                                          pPanelConfig->uAttrs.sDp.eConnectionPinAssignment : MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_INVALID;

        pOpenConfig->eConnectionPolarity   = gMDPToDPConnectionPolarityMapping[eConnectionPolarity];
        pOpenConfig->ePinAssignment        = gMDPToDPConnectionPinMapping[ePinAssignment];

        if (MDP_DP_CONTROLLER_MODE_DP == GetControllerModeInfo(pDPConfig->eDisplayId))
        {
          pOpenConfig->eConfigFlags        |= DP_CONFIG_FLAG_ALT_MODE_FIXED_LANE_CONFIGURATION;
          pOpenConfig->eConnectionPolarity  = DP_CONNECTION_POLARITY_POLARITY_DEFAULT;
          pOpenConfig->ePinAssignment       = DP_CONNECTION_PINASSIGNMENT_DFPD_C;

          // Configure DP GPIOs that controls AUX and HPD
          ConfigureGPIO(pDPConfig->eDisplayId);
        }

        break;
      }
      case MDP_DP_CONNECTION_MODE_TUNNELING:
      {
        pOpenConfig->bTunnelingMode    = TRUE;
        pOpenConfig->hHostRouterHandle = pDPConfig->hDPHostRouterHandle;
        break;
      }
      default:
      {
        pOpenConfig->eConnectionPolarity = DP_CONNECTION_POLARITY_POLARITY_REVERSE;
        pOpenConfig->ePinAssignment      = DP_CONNECTION_PINASSIGNMENT_DFPD_C;
        break;
      }
    }

    // Allow HPD failure by polling and ignoring for EDP and internal displays
    pOpenConfig->eConfigFlags       |= (bInternalDisplay) ? DP_CONFIG_FLAG_HPD_FAILSAFE : DP_CONFIG_FLAG_NONE;

    // Save DP displayID 
    pOpenConfig->eDeviceID                  = GetDPDeviceID(pDPConfig->eDisplayId, uDeviceIndex);
    pOpenConfig->eBrightnessType            = pPanelConfig->sBacklightConfig.eBacklightType;

    // Copy over relevant bonded mode configuration parameters
    pOpenConfig->sBondedModeConfig.bEnabled             = pDPConfig->sBondedModeConfig.bEnabled;
    pOpenConfig->sBondedModeConfig.eSourceClockDeviceID = pDPConfig->sBondedModeConfig.eSourceClockDeviceID;
    pOpenConfig->sBondedModeConfig.eMasterAUXDeviceID   = pDPConfig->sBondedModeConfig.eMasterAUXDeviceID;

    if ((TRUE == pOpenConfig->sBondedModeConfig.bEnabled) &&
        (TRUE == IsAltModeDevice(pOpenConfig->eDeviceID)))
    {
      // Fixed lane configuration for Alt-mode devices in bonded mode
      pOpenConfig->eConfigFlags        |= DP_CONFIG_FLAG_ALT_MODE_FIXED_LANE_CONFIGURATION;
      pOpenConfig->eConnectionPolarity  = DP_CONNECTION_POLARITY_POLARITY_DEFAULT;
      // Perform reset of DP/USB3 combo PHY
      pOpenConfig->eConfigFlags        |= DP_CONFIG_FLAG_ALT_MODE_COMMON_RESET;
    }

    // Copy AUX override buffers and mode from XML for internal panels and
    // for external display, if it is in Fallback mode, for the platforms with headless displays    
    if ((TRUE == bInternalDisplay) ||
        (MDP_DP_OVERRIDE_MODE_FALLBACK == pPanelConfig->uAttrs.sDp.eOverrideMode))
    {
      pOpenConfig->sOverrideConfig.eMode = pPanelConfig->uAttrs.sDp.eOverrideMode;
      pOpenConfig->sOverrideConfig.pBufs = &pPanelConfig->uAttrs.sDp.sOverrideBufs;
    }
    else
    {
      // Disable overrides for external displays
      pOpenConfig->sOverrideConfig.eMode = MDP_DP_OVERRIDE_MODE_OFF;
    }

    if ((MDP_PANEL_BACKLIGHTTYPE_AUX         == pPanelConfig->sBacklightConfig.eBacklightType) ||
        (MDP_PANEL_BACKLIGHTTYPE_AUX_CUSTOM1 == pPanelConfig->sBacklightConfig.eBacklightType) ||
        (MDP_PANEL_BACKLIGHTTYPE_AUX_CUSTOM2 == pPanelConfig->sBacklightConfig.eBacklightType))
    {
      // Indicate that backlight is to be configured through DP AUX
      pOpenConfig->eCapabilityMask |= DP_CAPS_BRIGHTNESS;
    }

    pOpenConfig->sSourceOverrideCaps.uMaxLinkRateInKHz =  pPanelConfig->uAttrs.sDp.uMaxLinkRate;
  }
}

/* ----------------------------------------------------------------------
** FUNCTION: SetupOpenConfig()
**
** DESCRIPTION:
**    Setup the config for DP_Host_Open
**
-------------------------------------------------------------------- */
static void SetupBondedModeConfig(DPDriverConfigType *pDPConfig)
{
  if (NULL == pDPConfig)
  {
    DP_LOG_MESSAGE_ERROR("SetupOpenConfig: Invalid input ");
  }
  else
  {
    MDP_Panel_AttrType *pPanelAttr = MDP_GET_DISPLAYINFO(pDPConfig->eDisplayId);

    // Populate default bonded mode configuration
    pDPConfig->sBondedModeConfig.bEnabled              = FALSE;
    pDPConfig->sBondedModeConfig.uNumDevices           = 1;
    pDPConfig->sBondedModeConfig.eSourceClockDeviceID  = DP_DEVICE_ID_NONE;
    pDPConfig->sBondedModeConfig.eMasterAUXDeviceID    = DP_DEVICE_ID_NONE;
    pDPConfig->sBondedModeConfig.bExternalMasterDevice = FALSE;

    // Populate the DP driver config with the bonded mode config from the panel attributes
    if (TRUE == pPanelAttr->uAttrs.sDp.sBondedModeConfig.bEnabled)
    {
      DP_DeviceIDType eSourceClockDeviceID  = GetDPDeviceIDFromDeviceIDMapping(pPanelAttr->uAttrs.sDp.sBondedModeConfig.uMasterClockDeviceID);
      DP_DeviceIDType eMasterAUXDeviceID    = GetDPDeviceIDFromDeviceIDMapping(pPanelAttr->uAttrs.sDp.sBondedModeConfig.uMasterAUXDeviceID);
      uint32          uNumDevices           = pPanelAttr->uAttrs.sDp.sBondedModeConfig.uNumDevices;
      bool32          bExternalMasterDevice = pPanelAttr->uAttrs.sDp.sBondedModeConfig.bExternalMasterDevice;

      if ((DP_DEVICE_ID_NONE != eSourceClockDeviceID) && 
          (DP_DEVICE_ID_NONE != eMasterAUXDeviceID) &&
          (uNumDevices < MDP_MAX_NUM_DP_DEVICES))
      {
        pDPConfig->sBondedModeConfig.eSourceClockDeviceID  = eSourceClockDeviceID;
        pDPConfig->sBondedModeConfig.eMasterAUXDeviceID    = eMasterAUXDeviceID;
        pDPConfig->sBondedModeConfig.uNumDevices           = uNumDevices;
        pDPConfig->sBondedModeConfig.bEnabled              = TRUE;
        pDPConfig->sBondedModeConfig.bExternalMasterDevice = bExternalMasterDevice;
      }
      else
      {
        DP_LOG_MESSAGE_ERROR("DPDriver_Open: invalid bonded mode configuration, eDisplayId = %d", pDPConfig->eDisplayId);
      }
    }
  }
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DPDriver_Open()
**
** DESCRIPTION:
**   Initialize DP panel to use display.
**
*//* -------------------------------------------------------------------- */
MDP_Status DPDriver_Open(MDP_Display_IDType eDisplayId,
                         uint32             uFlags)
{
  MDP_Status               eStatus          = MDP_STATUS_OK;
  DPDriverConfigType      *pDPConfig        = NULL;

  if (NULL == (pDPConfig = GetDPDriverContext(eDisplayId)))
  {
    eStatus = MDP_STATUS_NOT_SUPPORTED;
    DP_LOG_MESSAGE_ERROR("DPDrv%d: DPDriver_Open: Invalid display ID\n", eDisplayId);
  }
  else
  {
    DP_HostOpenConfigType     sOpenConfig      = { 0 };
    DP_GetPropertyParamsType  sDPProp;
    MDP_Panel_AttrType       *pPanelAttr       = MDP_GET_DISPLAYINFO(eDisplayId);
    uint32                    uDeviceIndex;

    pDPConfig->eDisplayId         = eDisplayId;
    pDPConfig->eDPConnectionMode  = (pPanelAttr->uAttrs.sDp.eDPConnectionMode < MDP_DP_CONNECTION_MODE_MAX) ?
                                     pPanelAttr->uAttrs.sDp.eDPConnectionMode : MDP_DP_CONNECTION_MODE_NATIVE;

    SetupBondedModeConfig(pDPConfig);

    for (uDeviceIndex = 0; uDeviceIndex < DPDRIVER_GETMAX_CONTROLLERS(pDPConfig); uDeviceIndex++)
    {
      SetupOpenConfig(pDPConfig, pPanelAttr, &sOpenConfig, uFlags, uDeviceIndex);

      // Initialize the host side 
      if (DP_STATUS_SUCCESS != DP_Host_Open(&pDPConfig->hDPHandle[uDeviceIndex], &sOpenConfig))
      {
        eStatus = MDP_STATUS_FAILED;

        // In case of failure, power down and close the context
        DP_Host_Power(pDPConfig->hDPHandle[uDeviceIndex], FALSE);
        DP_Host_Close(pDPConfig->hDPHandle[uDeviceIndex]);

        // Clear the DP handle since the memory is already free
        pDPConfig->hDPHandle[uDeviceIndex] = NULL;
        
        DP_LOG_MESSAGE_ERROR("DPDrv%d: DPDriver_Open: DP_Host_Open failed, uDeviceIndex =%d, eStatus =%d\n", eDisplayId, uDeviceIndex, eStatus);
      }
    }

    // If master DP device is not one of the DP devices opened above and is an alt-mode device, perform a common (DP & USB3) PHY reset
    if ((TRUE == pDPConfig->sBondedModeConfig.bEnabled) && 
        (TRUE == pDPConfig->sBondedModeConfig.bExternalMasterDevice) &&
        (TRUE == IsAltModeDevice(pDPConfig->sBondedModeConfig.eSourceClockDeviceID)))
    {
      DP_SetPropertyParamsType sPropertyData;
      
      DP_OSAL_MemSet(&sPropertyData, 0x00, sizeof(DP_SetPropertyParamsType));
      sPropertyData.sPHYResetInfo.eDeviceID      = pDPConfig->sBondedModeConfig.eSourceClockDeviceID;
      sPropertyData.sPHYResetInfo.ePHYResetFlag |= DP_PHY_RESET_ALT_MODE_COMMON_RESET;
      
      if (DP_STATUS_SUCCESS != (DP_Host_SetProperty(pDPConfig->hDPHandle[0], DP_SETPROPERTY_RESET_PHY , &sPropertyData)))
      {
        eStatus = MDP_STATUS_FAILED;
        DP_LOG_MESSAGE_ERROR("DPDrv%d: DPDriver_Open: failed to set bonded mode config, uDeviceIndex =%d, Status =%d\n", eDisplayId, uDeviceIndex, eStatus);
      }
    }

    DISP_OSAL_MemZero(&sDPProp, sizeof(sDPProp));
	  
	  // Update raw EDID in display attribute structure taken from DP Host 
    sDPProp.sEdidInfo.uDataLength = sizeof(pPanelAttr->sEDID);
    sDPProp.sEdidInfo.pDataBuf    = (void*)&pPanelAttr->sEDID;
  
    if (DP_STATUS_SUCCESS != DP_Host_GetProperty(pDPConfig->hDPHandle[0], DP_GETPROPERTY_EDID_INFO, &sDPProp))
    {
      DISP_OSAL_LOGX("DPDriver_Open: Failed updating EDID, eDisplayId = %d", eDisplayId);
    }
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DPDriver_IsDisplayPlugged()
**
** DESCRIPTION:
**   check DP panel is plugged in.
**
*//* -------------------------------------------------------------------- */
bool32 DPDriver_IsDisplayPlugged(MDP_Display_IDType eDisplayId)
{
  bool32                     bPluggedIn  = FALSE;
  DP_GetPropertyParamsType   sPropData;
  DPDriverConfigType         *pDPConfig  = GetDPDriverContext(eDisplayId);

  if ((NULL              != pDPConfig) &&
      (DP_STATUS_SUCCESS == DP_Host_GetProperty(pDPConfig->hDPHandle[0], DP_GETPROPERTY_CONNECTION_STATUS, &sPropData)))
  {   
    bPluggedIn = sPropData.bPluggedIn;
  }   
      
  return bPluggedIn;
}

/* ----------------------------------------------------------------------
** FUNCTION: DPDriver_Term()
**
** DESCRIPTION:
**    Close the DP Host driver
**
-------------------------------------------------------------------- */
MDP_Status DPDriver_Term(MDP_Display_IDType eDisplayId)
{
  MDP_Status               eStatus   = MDP_STATUS_OK;
  DPDriverConfigType      *pDPConfig = GetDPDriverContext(eDisplayId);
  uint32                   uDeviceIndex;

  // Close DP host driver
  if (NULL != pDPConfig)
  {
    for (uDeviceIndex = 0; uDeviceIndex < DPDRIVER_GETMAX_CONTROLLERS(pDPConfig); uDeviceIndex++)
    {
      if (DP_STATUS_SUCCESS != DP_Host_Power(pDPConfig->hDPHandle[uDeviceIndex], FALSE))
      {
        eStatus = MDP_STATUS_FAILED;
        DP_LOG_MESSAGE_ERROR("DPDrv%d: DPDriver_Term: DP_Host_Power failed, uDeviceIndex =%d, eStatus =%d\n", eDisplayId, uDeviceIndex, eStatus);
      }

      if (DP_STATUS_SUCCESS != DP_Host_Close(pDPConfig->hDPHandle[uDeviceIndex]))
      {
        eStatus = MDP_STATUS_FAILED;
        DP_LOG_MESSAGE_ERROR("DPDrv%d: DPDriver_Term: DP_Host_Close failed, uDeviceIndex =%d, eStatus =%d\n", eDisplayId, uDeviceIndex, eStatus);
      }
    }

    DP_OSAL_MemSet(pDPConfig, 0x00, sizeof(DPDriverConfigType));
  }

  return eStatus;
}

/* ----------------------------------------------------------------------
** FUNCTION: DPDriver_SetMode()
**
** DESCRIPTION:
**    Set a panel mode
**
-------------------------------------------------------------------- */
MDP_Status DPDriver_SetMode(MDP_Panel_AttrType *pPanelInfo,
                            uint32              uFlags)
{
  DP_Status                eStatus       = DP_STATUS_SUCCESS;
  MDP_Status               eRetStatus    = MDP_STATUS_OK;
  DPDriverConfigType      *pDPConfig     = NULL;
  DP_SetPropertyParamsType sPropertyData;

  if ((NULL == pPanelInfo) ||
      (NULL == (pDPConfig = GetDPDriverContext(pPanelInfo->eDisplayId))))
  {
    DP_LOG_MESSAGE_ERROR("DPDriver_SetMode: Invalid input \n");
    eRetStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    uint32 uLinkRate   = 0;      // Default: Get from DPCD
    uint32 uNumLanes   = 0;      // Default: Calculate as needed
    uint32 uModeIndex  = 0;      // Default: First mode 
    uint32 uDeviceIndex;
   
    /* If we are not trying to force the mode from the driver supported list or reading from xml */
    if ((pPanelInfo->eDisplayFlags & MDP_PANEL_FLAG_TIMING_FROM_EDID) && 
        (FALSE == pPanelInfo->bForceMode))
    {
      /* timing from panel edid */
       uModeIndex = pPanelInfo->uPhysicalModeIndex;
    }
    else
    {
      /* timing from panel xml file */
      if (0 != pPanelInfo->uAttrs.sDp.uLinkRateInKhz)
      {
        uLinkRate = pPanelInfo->uAttrs.sDp.uLinkRateInKhz;
      }

      /* Override number of lanes  */
      if (0 != pPanelInfo->uAttrs.sDp.uNumberOfLanes)
      {
        uNumLanes = pPanelInfo->uAttrs.sDp.uNumberOfLanes;
      }

      if (NULL != pPanelInfo)
      {
        /* Get timing information from XML */
        DP_OSAL_MemSet(&sPropertyData, 0x00, sizeof(DP_SetPropertyParamsType));
        GetPanelInfoFromPanelAttributes(&sPropertyData.sPanelInfo, pPanelInfo);
        
        if (TRUE == pDPConfig->sBondedModeConfig.bEnabled)
        {
          /* Timing info in panel attributes represents display with all bonded devices combined.
           * Timings need to be scaled down per DP device at the DP Host level. */
          ScaleModeTimings(&sPropertyData.sPanelInfo, DP_MODE_TIMING_SCALE_UNITY / pDPConfig->sBondedModeConfig.uNumDevices);
        }

        DP_LOG_MESSAGE_INFO("DPDrv%d: DPDriver_SetMode: ndx=%d pclk=%d w=%d hfp=%d bfp=%d h=%d vfp=%d vbp=%d, frate=%x\n",
                            pPanelInfo->eDisplayId,
                            sPropertyData.sPanelInfo.uModeIndex,
                            sPropertyData.sPanelInfo.uPclkFreq,
                            sPropertyData.sPanelInfo.uVisibleWidthInPixels,
                            sPropertyData.sPanelInfo.uHsyncFrontPorchInPixels,
                            sPropertyData.sPanelInfo.uHsyncBackPorchInPixels,
                            sPropertyData.sPanelInfo.uVisibleHeightInPixels,
                            sPropertyData.sPanelInfo.uVsyncFrontPorchInLines,
                            sPropertyData.sPanelInfo.uVsyncBackPorchInLines,
                            sPropertyData.sPanelInfo.uRefreshRate);

        for (uDeviceIndex = 0; uDeviceIndex < DPDRIVER_GETMAX_CONTROLLERS(pDPConfig); uDeviceIndex++)
        {
          // Set the mode
          eStatus = DP_Host_SetProperty(pDPConfig->hDPHandle[uDeviceIndex], DP_SETPROPERTY_PANEL_INFO, &sPropertyData);
          if (DP_STATUS_SUCCESS != eStatus)
          {
            DP_LOG_MESSAGE_WARN("DPDrv%d: DPDriver_SetModeInfo: failed to set panel info, uDeviceIndex =%d, eStatus=%d\n", pPanelInfo->eDisplayId, uDeviceIndex, eStatus);
          }
        }
      }
    }

    for (uDeviceIndex = 0; uDeviceIndex < DPDRIVER_GETMAX_CONTROLLERS(pDPConfig); uDeviceIndex++)
    {
      if (0 != uLinkRate)
      {
        DP_OSAL_MemSet(&sPropertyData, 0x00, sizeof(DP_SetPropertyParamsType));
        sPropertyData.uLinkRate = uLinkRate;
        if(DP_STATUS_SUCCESS != (eStatus = DP_Host_SetProperty(pDPConfig->hDPHandle[uDeviceIndex], DP_SETPROPERTY_LINK_RATE, &sPropertyData)))
        {
          DP_LOG_MESSAGE_WARN("DPDrv%d: DPDriver_SetMode: failed to set link rate, uDeviceIndex =%d, eStatus=%d\n", pPanelInfo->eDisplayId, uDeviceIndex, eStatus);
        }
      }
	  
      if (0 != uNumLanes)
      {
        DP_OSAL_MemSet(&sPropertyData, 0x00, sizeof(DP_SetPropertyParamsType));
        sPropertyData.uLaneNumber = uNumLanes;
        if (DP_STATUS_SUCCESS != (eStatus = DP_Host_SetProperty(pDPConfig->hDPHandle[uDeviceIndex], DP_SETPROPERTY_LANE_NUMBER, &sPropertyData)))
        {
          DP_LOG_MESSAGE_WARN("DPDrv%d: DPDriver_SetMode: failed to set link rate, uDeviceIndex =%d, eStatus=%d\n", pPanelInfo->eDisplayId, uDeviceIndex, eStatus);
        }
      }
	  
      DP_OSAL_MemSet(&sPropertyData, 0x00, sizeof(DP_SetPropertyParamsType));
      sPropertyData.sPanelInfo.uModeIndex = uModeIndex;
      if (DP_STATUS_SUCCESS != (eStatus = DP_Host_SetProperty(pDPConfig->hDPHandle[uDeviceIndex], DP_SETPROPERTY_PANEL_MODE_INDEX, &sPropertyData)))
      {
        DP_LOG_MESSAGE_ERROR("DPDrv%d: DPDriver_SetMode: failed to set Mode Index, uDeviceIndex =%d, eStatus=%d\n", pPanelInfo->eDisplayId, uDeviceIndex, eStatus);
        eRetStatus = MDP_STATUS_FAILED;
        break;
      }

      if (DP_STATUS_SUCCESS != DP_Host_SetProperty(pDPConfig->hDPHandle[uDeviceIndex], DP_SETPROPERTY_COLOR_SPACE, NULL))
      {
        DP_LOG_MESSAGE_WARN("DPDriver_SetMode: failed to set color blend space, uDeviceIndex =%d, eStatus=%d\n", pPanelInfo->eDisplayId, uDeviceIndex, eStatus);
      }
    }

    if (MDP_STATUS_OK == eRetStatus)
    {
      for (uDeviceIndex = 0; uDeviceIndex < DPDRIVER_GETMAX_CONTROLLERS(pDPConfig); uDeviceIndex++)
      {
        if (DP_STATUS_SUCCESS != (eStatus = DP_Host_Commit(pDPConfig->hDPHandle[uDeviceIndex])))
        {
          eRetStatus = MDP_STATUS_FAILED;
          DP_LOG_MESSAGE_ERROR("DPDrv%d: DPDriver_SetMode: failed to commit, uDeviceIndex =%d, eStatus=%d\n", pPanelInfo->eDisplayId, uDeviceIndex, eStatus);
          break;
        }      
      }
    }
  }

  return eRetStatus;
}

/* ----------------------------------------------------------------------
** FUNCTION: DPDriver_GetModeInfo()
**
** DESCRIPTION:
**    Get DP panel mode info.
**
-------------------------------------------------------------------- */
MDP_Status DPDriver_GetModeInfo(MDP_Panel_AttrType *pPanelInfo)
{
  MDP_Status                      eStatus   = MDP_STATUS_OK;
  DPDriverConfigType             *pDPConfig = NULL;

  if ((NULL == pPanelInfo)                                               ||
      (NULL == (pDPConfig = GetDPDriverContext(pPanelInfo->eDisplayId))))
  {
    eStatus = MDP_STATUS_FAILED;
  }
  else
  {
    DP_GetPropertyParamsType       sDPProp;

    DP_OSAL_MemSet(&sDPProp, 0x00, sizeof(DP_GetPropertyParamsType));
    sDPProp.sPanelInfo.uModeIndex = (pPanelInfo->bForceMode) ? 0: pPanelInfo->uPhysicalModeIndex;

    // Query the mode
    if (DP_STATUS_SUCCESS == DP_Host_GetProperty(pDPConfig->hDPHandle[0], DP_GETPROPERTY_GET_MODE_INFO, &sDPProp))
    {
      if (pPanelInfo->bForceMode)
      {
        EDID_DispModeAttrType sModeInfo;

        MDP_OSAL_MEMZERO(&sModeInfo, sizeof(EDID_DispModeAttrType));

        if (MDP_STATUS_OK != (eStatus = (MDP_Status)EDID_GetMode_ByIndex(&sModeInfo, pPanelInfo->uPhysicalModeIndex)))
        {
          DP_LOG_MESSAGE_ERROR("DPDrv%d: DPDriver_GetModeInfo: failed to get mode information by index\n", pPanelInfo->eDisplayId);
        }
        else
        {
          pPanelInfo->sActiveTiming.uHsyncPulseWidthDclk     = sModeInfo.sActiveTimingInfo.iHsyncPulseWidthDclk;
          pPanelInfo->sActiveTiming.uHsyncFrontPorchDclk     = sModeInfo.sActiveTimingInfo.iHsyncFrontPorchDclk;
          pPanelInfo->sActiveTiming.uHsyncBackPorchDclk      = sModeInfo.sActiveTimingInfo.iHsyncBackPorchDclk;       
          pPanelInfo->sActiveTiming.uHsyncInvertSignal       = sModeInfo.sActiveTimingInfo.bIsHsyncActiveLow;
          pPanelInfo->sActiveTiming.uVsyncPulseWidthLines    = sModeInfo.sActiveTimingInfo.iVsyncPulseWidthLines;
          pPanelInfo->sActiveTiming.uVsyncFrontPorchLines    = sModeInfo.sActiveTimingInfo.iVsyncFrontPorchLines;
          pPanelInfo->sActiveTiming.uVsyncBackPorchLines     = sModeInfo.sActiveTimingInfo.iVsyncBackPorchLines;
          pPanelInfo->sActiveTiming.uVsyncInvertSignal       = sModeInfo.sActiveTimingInfo.bIsVsyncActiveLow;
          pPanelInfo->uRefreshRate                           = sModeInfo.sDisplayModeInfo.uRefreshRate;
          pPanelInfo->uDisplayWidth                          = sModeInfo.sDisplayModeInfo.uWidthPx;
          pPanelInfo->uDisplayHeight                         = sModeInfo.sDisplayModeInfo.uHeightPx;
          pPanelInfo->uPixelRate                             = sModeInfo.sDisplayModeInfo.uPixelRate;
          pPanelInfo->uAttrs.sDp.uRefreshRate                = sModeInfo.sDisplayModeInfo.uRefreshRate;
          pPanelInfo->sActiveTiming.uDataEnInvertSignal      = FALSE;
          pPanelInfo->sActiveTiming.uHsyncSkewDclk           = 0;

          if (DP_PIXEL_FORMAT_RGB_101010_30BPP == sDPProp.sPanelInfo.eColorFormat)
          {
            pPanelInfo->eColorFormat = MDP_PIXEL_FORMAT_RGB_101010_30BPP;
          }
          else if (DP_PIXEL_FORMAT_RGB_666_18BPP == sDPProp.sPanelInfo.eColorFormat)
          {
            pPanelInfo->eColorFormat = MDP_PIXEL_FORMAT_RGB_666_18BPP;
          }
          else
          {
            pPanelInfo->eColorFormat = MDP_PIXEL_FORMAT_RGB_888_24BPP;
          }
        }
      } 
      else
      {
        if (TRUE == pDPConfig->sBondedModeConfig.bEnabled)
        {
          // Timing info in panel attributes to be represented as single display with all bonded devices combined
          ScaleModeTimings(&sDPProp.sPanelInfo, DP_MODE_TIMING_SCALE_UNITY * pDPConfig->sBondedModeConfig.uNumDevices);
        }

        // Populate panel attributes with info recieved from the query
        GetPanelAttributesFromPanelInfo(pPanelInfo, &sDPProp.sPanelInfo);
      }

      DP_LOG_MESSAGE_INFO("DPDrv%d: DPDriver_GetModeInfo:#%d Resolution=%dx%dp%d Pclock=%dHz\n",
                          pPanelInfo->eDisplayId,
                          pPanelInfo->uPhysicalModeIndex,
                          pPanelInfo->uDisplayWidth,
                          pPanelInfo->uDisplayHeight,
                          pPanelInfo->uRefreshRate>>16,
                          sDPProp.sPanelInfo.uPclkFreq);
    }
    else
    {
      eStatus = MDP_STATUS_FAILED;
    }
  }

  return eStatus;
}

/* ----------------------------------------------------------------------
** FUNCTION: DPDriver_SendComamndSequence()
**
** DESCRIPTION:
**    DP Driver sends meta data to client (panel)
**
-------------------------------------------------------------------- */
MDP_Status DPDriver_SendCommandSequence(MDP_Panel_AttrType  *pPanelInfo,
                                        MdpPanelCommandType  eCommand,
                                        void                *pPayload,
                                        uint32               uFlags)
{
    MDP_Status               eStatus          = MDP_STATUS_NOT_SUPPORTED;
    DPDriverConfigType      *pDPConfig        = GetDPDriverContext(pPanelInfo->eDisplayId);

    if (pDPConfig)
    {
       switch (eCommand)
       {
          case MDP_PANEL_COMMAND_PPS:
          {
            // Send PPS
            DP_SetPropertyParamsType  sPropertyData;
      
            DISP_OSAL_MemZero(&sPropertyData, sizeof(DP_SetPropertyParamsType)); 
            sPropertyData.sDSCPPSParams.uStreamId  = GetStreamID(pDPConfig->eDisplayId);
            sPropertyData.sDSCPPSParams.pPPSBuffer = (uint8*)&(pDPConfig->uPPSBuffer[0]) + MDP_PANEL_DSC_HEADER_SIZE + MDP_PANEL_DSC_XML_HEADER_SIZE;
            sPropertyData.sDSCPPSParams.uSize      = MDP_PANEL_DSC_PAYLOAD_SIZE;
      
            if (DP_STATUS_SUCCESS != DP_Host_SetProperty(pDPConfig->hDPHandle[0], DP_SETPROPERTY_UPDATE_PPS, &sPropertyData))
            {
              DP_LOG_MESSAGE_WARN("DPDriver_SendCommandSequence: Failed to send DSC PPS for display %d", pDPConfig->eDisplayId);
            }

            break;
          }
             
          default:
             break;
       }
    }

    return eStatus;
}

/* ----------------------------------------------------------------------
** FUNCTION: DPDriver_GetFrameCRC()
**
** DESCRIPTION:
**    Enable CRC capture or read from CRC registers
**
-------------------------------------------------------------------- */
MDP_Status DPDriver_GetFrameCRC(MDP_Panel_AttrType *pPanelInfo,
                                uint64             *pCRC)
{
    MDP_Status                 eStatus          = MDP_STATUS_BAD_PARAM;
    DPDriverConfigType        *pDPConfig        = GetDPDriverContext(pPanelInfo->eDisplayId);
    DP_GetPropertyParamsType   sParams;

    if (pDPConfig)
    {
          eStatus = (MDP_Status)DP_Host_GetProperty(pDPConfig->hDPHandle[0], DP_GETPROPERTY_FRAME_CRC, &sParams);
          if (eStatus == MDP_STATUS_OK)
          {
             *pCRC = sParams.uCRC;
          }
    }

    return eStatus;
}

/* ----------------------------------------------------------------------
** FUNCTION: DPDriver_BrightnessEnable()
**
** DESCRIPTION:
**    Enable panel brightness through AUX
**
-------------------------------------------------------------------- */
MDP_Status DPDriver_BrightnessEnable(MDP_Display_IDType eDisplayId, bool32 bEnable)
{
  MDP_Status                eStatus     = MDP_STATUS_OK;
  DPDriverConfigType       *pDPConfig   = NULL;

  if (NULL == (pDPConfig = GetDPDriverContext(eDisplayId)))
  {
    eStatus = MDP_STATUS_BAD_HANDLE;
    DP_LOG_MESSAGE_ERROR("DPDrv%d: DPDriver_BrightnessEnable: Invalid display\n", eDisplayId);
  }
  else
  {
    DP_SetPropertyParamsType  sBacklightProperty;
    DISP_OSAL_MemZero(&sBacklightProperty, sizeof(DP_SetPropertyParamsType));

    sBacklightProperty.sBrightnessInfo.eBrightnessRequest = bEnable ? DP_BRIGHTNESS_REQUEST_ON : DP_BRIGHTNESS_REQUEST_OFF;

    if (MDP_STATUS_OK != (eStatus = (MDP_Status)DP_Host_SetProperty(pDPConfig->hDPHandle[0], 
                                                                    DP_SETPROPERTY_BRIGHTNESS_CONTROL, 
                                                                    &sBacklightProperty)))
    {
      DP_LOG_MESSAGE_ERROR("DPDrv%d: DPDriver_BrightnessEnable: Failed for display with status 0x%x \n",
                           eDisplayId, eStatus);
    }
  }
  
  return eStatus;
}

/* ----------------------------------------------------------------------
** FUNCTION: DPDriver_BrightnessLevel()
**
** DESCRIPTION:
**    Set panel brightness to requested level
**
-------------------------------------------------------------------- */
MDP_Status DPDriver_BrightnessLevel(MDP_Display_IDType eDisplayId, float fNewLevel, uint32 uMillinits)
{
  MDP_Status               eStatus          = MDP_STATUS_OK;
  DPDriverConfigType      *pDPConfig        = GetDPDriverContext(eDisplayId);

  if (NULL == pDPConfig)
  {
    eStatus = MDP_STATUS_BAD_HANDLE;
  }
  else
  {
    DP_SetPropertyParamsType  sPropertyData;
    DISP_OSAL_MemZero(&sPropertyData, sizeof(DP_SetPropertyParamsType));
  
    // Initialize brightness request to new level
    sPropertyData.sBrightnessInfo.fLevel              = fNewLevel;
    sPropertyData.sBrightnessInfo.eBrightnessRequest  = DP_BRIGHTNESS_REQUEST_LEVEL;
    sPropertyData.sBrightnessInfo.uMillinits          = uMillinits;

    // Send the request to DP Host
    if (DP_STATUS_SUCCESS != DP_Host_SetProperty(pDPConfig->hDPHandle[0], DP_SETPROPERTY_BRIGHTNESS_CONTROL, &sPropertyData))
    {
      DP_LOG_MESSAGE_ERROR("DPDrv%d: DPDriver_SetBacklight: Failed with status %d for display\n", eDisplayId, eStatus);
    }
  }
  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DPDriver_SetConnectionStatus()
**
** DESCRIPTION:
**   Set DP connection status in driver context.
**
*//* -------------------------------------------------------------------- */
MDP_Status DPDriver_SetConnectionStatus(MDP_Display_IDType eDisplayId, bool32 bConnected, MDP_HotPlugEventDataType *pHotPlugData)
{
  MDP_Status               eStatus          = MDP_STATUS_OK;
  MDP_Panel_AttrType      *pPanelAttr       = MDP_GET_DISPLAYINFO(eDisplayId);

  if (NULL == pPanelAttr)
  {
    eStatus = MDP_STATUS_BAD_HANDLE;
  }
  else
  {
    MDP_HotPlugEventDataType *psHPDEventData  = pHotPlugData;

    // Save the HPD configuration in panel attributes which will read during DPDriver_Open()
    if (TRUE == bConnected)
    {
      if (NULL != psHPDEventData)
      {
        DP_DeviceIDType eDeviceID = GetDPDeviceID(eDisplayId, 0);

        if (FALSE == IsAltModeDevice(eDeviceID))
        {
          DP_LOG_MESSAGE_ERROR("DPDrv%d: Received DP Alt Mode connection status event for non DP Altmode Display \n", eDisplayId);
          eStatus = MDP_STATUS_FAILED;
        }
        else
        {
          pPanelAttr->uAttrs.sDp.eDPConnectionMode        = MDP_DP_CONNECTION_MODE_ALT_MODE;
          pPanelAttr->uAttrs.sDp.eConnectionPolarity      = psHPDEventData->sDPAltModeHPDInfo.eConnectionPolarity;
          pPanelAttr->uAttrs.sDp.eConnectionPinAssignment = psHPDEventData->sDPAltModeHPDInfo.eConnectionPinAssignment;
          pPanelAttr->uAttrs.sDp.bConcurrencyMode         = psHPDEventData->sDPAltModeHPDInfo.bConcurrencyMode;
        }
      }
    }
    else // HPD Out
    {
      // Not implemented
    }
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: GetPanelInfoFromPanelAttributes()
**
** DESCRIPTION:
**   Populate the DP_PanelInfoType struct with timing info from the 
**   MDP_Panel_AttrType struct.
**
*//* -------------------------------------------------------------------- */
static void GetPanelInfoFromPanelAttributes(DP_PanelInfoType   *pPanelInfo,
                                            MDP_Panel_AttrType *pPanelAttr)
{
  if ((NULL == pPanelInfo) ||
      (NULL == pPanelAttr))
  {
    DP_LOG_MESSAGE_ERROR("GetPanelInfoFromPanelAttributes: Invalid input");
  }
  else
  {
    pPanelInfo->uVisibleWidthInPixels    = pPanelAttr->uDisplayWidth;
    pPanelInfo->uHsyncFrontPorchInPixels = pPanelAttr->sActiveTiming.uHsyncFrontPorchDclk;
    pPanelInfo->uHsyncBackPorchInPixels  = pPanelAttr->sActiveTiming.uHsyncBackPorchDclk;
    pPanelInfo->uHsyncPulseInPixels      = pPanelAttr->sActiveTiming.uHsyncPulseWidthDclk;
    pPanelInfo->uHsyncSkewInPixels       = pPanelAttr->sActiveTiming.uHsyncSkewDclk;
    pPanelInfo->uVisibleHeightInPixels   = pPanelAttr->uDisplayHeight;
    pPanelInfo->uVsyncFrontPorchInLines  = pPanelAttr->sActiveTiming.uVsyncFrontPorchLines;
    pPanelInfo->uVsyncBackPorchInLines   = pPanelAttr->sActiveTiming.uVsyncBackPorchLines;
    pPanelInfo->uVsyncPulseInLines       = pPanelAttr->sActiveTiming.uVsyncPulseWidthLines;
    pPanelInfo->uHLeftBorderInPixels     = pPanelAttr->sActiveTiming.uHLeftBorderDClk;
    pPanelInfo->uHRightBorderInPixels    = pPanelAttr->sActiveTiming.uHRightBorderDClk;
    pPanelInfo->uVTopBorderInLines       = pPanelAttr->sActiveTiming.uVTopBorderLines;
    pPanelInfo->uVBottomBorderInLines    = pPanelAttr->sActiveTiming.uVBottomBorderLines;
    pPanelInfo->bHSyncActiveLow          = pPanelAttr->sActiveTiming.uHsyncInvertSignal;
    pPanelInfo->bVSyncActiveLow          = pPanelAttr->sActiveTiming.uVsyncInvertSignal;
    pPanelInfo->uRefreshRate             = pPanelAttr->uAttrs.sDp.uRefreshRate;
    pPanelInfo->uPclkFreq                = (uint32)(((uint64)pPanelAttr->uDisplayWidth +
                                           pPanelAttr->sActiveTiming.uHsyncFrontPorchDclk +
                                           pPanelAttr->sActiveTiming.uHsyncBackPorchDclk +
                                           pPanelAttr->sActiveTiming.uHsyncPulseWidthDclk) *
                                           (uint64) ((uint64)pPanelAttr->uDisplayHeight +
                                           pPanelAttr->sActiveTiming.uVsyncFrontPorchLines +
                                           pPanelAttr->sActiveTiming.uVsyncBackPorchLines +
                                           pPanelAttr->sActiveTiming.uVsyncPulseWidthLines) *
                                           pPanelAttr->uAttrs.sDp.uRefreshRate / 0x10000);
    pPanelInfo->bInterlaced              = pPanelAttr->sActiveTiming.bInterlaced;

    if (MDP_PIXEL_FORMAT_RGB_101010_30BPP == pPanelAttr->eColorFormat)
    {
      pPanelInfo->eColorFormat = DP_PIXEL_FORMAT_RGB_101010_30BPP;
    }
    else if (MDP_PIXEL_FORMAT_RGB_666_18BPP == pPanelAttr->eColorFormat)
    {
      pPanelInfo->eColorFormat = DP_PIXEL_FORMAT_RGB_666_18BPP;
    }
    else
    {
      pPanelInfo->eColorFormat = DP_PIXEL_FORMAT_RGB_888_24BPP;
    }
  }
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: ScaleModeTimings()
**
** DESCRIPTION:
**   Upscales/downscales timings for tiled/bonded mode DP configurations.
**
*//* -------------------------------------------------------------------- */
static void ScaleModeTimings(DP_PanelInfoType *pPanelInfo,
                             uint32            uScale)
{
  if (NULL != pPanelInfo)
  {
    pPanelInfo->uPclkFreq                = ((uint64)pPanelInfo->uPclkFreq * uScale) / DP_MODE_TIMING_SCALE_UNITY;
    pPanelInfo->uVisibleWidthInPixels    = (pPanelInfo->uVisibleWidthInPixels * uScale) / DP_MODE_TIMING_SCALE_UNITY;
    pPanelInfo->uHsyncFrontPorchInPixels = (pPanelInfo->uHsyncFrontPorchInPixels * uScale) / DP_MODE_TIMING_SCALE_UNITY;
    pPanelInfo->uHsyncBackPorchInPixels  = (pPanelInfo->uHsyncBackPorchInPixels * uScale) / DP_MODE_TIMING_SCALE_UNITY;
    pPanelInfo->uHsyncPulseInPixels      = (pPanelInfo->uHsyncPulseInPixels * uScale) / DP_MODE_TIMING_SCALE_UNITY;
    pPanelInfo->uHLeftBorderInPixels     = (pPanelInfo->uHLeftBorderInPixels * uScale) / DP_MODE_TIMING_SCALE_UNITY;
    pPanelInfo->uHRightBorderInPixels    = (pPanelInfo->uHRightBorderInPixels * uScale) / DP_MODE_TIMING_SCALE_UNITY;
  }
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: GetPanelAttributesFromPanelInfo()
**
** DESCRIPTION:
**   Populate the MDP_Panel_AttrType struct with timing info from the
**   DP_PanelInfoType struct.
**
*//* -------------------------------------------------------------------- */
static void GetPanelAttributesFromPanelInfo(MDP_Panel_AttrType *pPanelAttr,
                                            DP_PanelInfoType   *pPanelInfo)
{
  if ((NULL == pPanelAttr) ||
      (NULL == pPanelInfo))
  {
    DP_LOG_MESSAGE_ERROR("GetPanelAttributesFromPanelInfo: Invalid input");
  }
  else
  {
    pPanelAttr->uDisplayWidth                       = pPanelInfo->uVisibleWidthInPixels;
    pPanelAttr->uDisplayHeight                      = pPanelInfo->uVisibleHeightInPixels;
    pPanelAttr->uAttrs.sDp.uRefreshRate             = pPanelInfo->uRefreshRate;
    pPanelAttr->uRefreshRate                        = pPanelInfo->uRefreshRate;
    pPanelAttr->sActiveTiming.uHsyncBackPorchDclk   = pPanelInfo->uHsyncBackPorchInPixels;
    pPanelAttr->sActiveTiming.uHsyncFrontPorchDclk  = pPanelInfo->uHsyncFrontPorchInPixels;
    pPanelAttr->sActiveTiming.uHsyncPulseWidthDclk  = pPanelInfo->uHsyncPulseInPixels;
    pPanelAttr->sActiveTiming.uHsyncSkewDclk        = pPanelInfo->uHsyncSkewInPixels;
    pPanelAttr->sActiveTiming.uVsyncBackPorchLines  = pPanelInfo->uVsyncBackPorchInLines;
    pPanelAttr->sActiveTiming.uVsyncFrontPorchLines = pPanelInfo->uVsyncFrontPorchInLines;
    pPanelAttr->sActiveTiming.uVsyncPulseWidthLines = pPanelInfo->uVsyncPulseInLines;
    pPanelAttr->sActiveTiming.uHLeftBorderDClk      = pPanelInfo->uHLeftBorderInPixels;
    pPanelAttr->sActiveTiming.uHRightBorderDClk     = pPanelInfo->uHRightBorderInPixels;
    pPanelAttr->sActiveTiming.uVTopBorderLines      = pPanelInfo->uVTopBorderInLines;
    pPanelAttr->sActiveTiming.uVBottomBorderLines   = pPanelInfo->uVBottomBorderInLines;
    pPanelAttr->sActiveTiming.bInterlaced           = pPanelInfo->bInterlaced;
    pPanelAttr->sActiveTiming.uHsyncInvertSignal    = pPanelInfo->bHSyncActiveLow;     
    pPanelAttr->sActiveTiming.uVsyncInvertSignal    = pPanelInfo->bVSyncActiveLow;
    pPanelAttr->sActiveTiming.uDataEnInvertSignal   = FALSE;

    if (DP_PIXEL_FORMAT_RGB_101010_30BPP == pPanelInfo->eColorFormat)
    {
      pPanelAttr->eColorFormat = MDP_PIXEL_FORMAT_RGB_101010_30BPP;
    }
    else if (DP_PIXEL_FORMAT_RGB_666_18BPP == pPanelInfo->eColorFormat)
    {
      pPanelAttr->eColorFormat = MDP_PIXEL_FORMAT_RGB_666_18BPP;
    }
    else
    {
      pPanelAttr->eColorFormat = MDP_PIXEL_FORMAT_RGB_888_24BPP;
    }        
  }
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DPDriver_UpdateBondedModeTimings()
**
** DESCRIPTION:
**   Scale the panel attribute timings to represent the display with all 
**   bonded devices combined.
**
*//* -------------------------------------------------------------------- */
void DPDriver_UpdateBondedModeTimings(MDP_Panel_AttrType *pPanelAttr)
{
  if (NULL == pPanelAttr)
  {
    DP_LOG_MESSAGE_ERROR("DPDriver_UpdateBondedModeTimings: Invalid input");
  }
  else
  {
    DP_PanelInfoType sPanelInfo;

    MDP_OSAL_MEMZERO(&sPanelInfo, sizeof(DP_PanelInfoType));

    /* Populate timing info from panel attributes struct into the DP panel info struct  */
    GetPanelInfoFromPanelAttributes(&sPanelInfo, pPanelAttr);

    /* Upscale the horizontal timing parmeters in the DP panel info struct based on
     * the total number of devices operating in bonded mode */
    ScaleModeTimings(&sPanelInfo, DP_MODE_TIMING_SCALE_UNITY * pPanelAttr->uAttrs.sDp.sBondedModeConfig.uNumDevices);

    /* Update the panel attribute timing info with the scaled timing info */
    GetPanelAttributesFromPanelInfo(pPanelAttr, &sPanelInfo);
  }
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: IsAltModeDevice()
**
** DESCRIPTION:
**   Returns true if DP Device ID belongs to an Alt-Mode device.
**
*//* -------------------------------------------------------------------- */
static bool32 IsAltModeDevice(DP_DeviceIDType eDeviceID)
{
  bool32 bRetVal = FALSE;

  switch (eDeviceID)
  {
  case DP_DEVICE_ID_ALT_MODE_0:
  case DP_DEVICE_ID_ALT_MODE_1:
  case DP_DEVICE_ID_ALT_MODE_2:
    bRetVal = TRUE;
    break;
  default:
    break;
  }

  return bRetVal;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: IsDPTunnelingDevice()
**
** DESCRIPTION:
**   Returns true if DP Device ID belongs to a DP Tunneling device.
**
*//* -------------------------------------------------------------------- */
static bool32 IsDPTunnelingDevice(DP_DeviceIDType eDeviceID)
{
  bool32 bRetVal = FALSE;

  switch (eDeviceID)
  {
  case DP_DEVICE_ID_ALT_MODE_0:
  case DP_DEVICE_ID_ALT_MODE_1:
  case DP_DEVICE_ID_ALT_MODE_2:
    bRetVal = TRUE;
    break;
  default:
    break;
  }

  return bRetVal;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DPDriver_GetEDID()
**
** DESCRIPTION:
**   Retrieve panel EDID.
**
*//* -------------------------------------------------------------------- */
MDP_Status DPDriver_GetEDID(MDP_Display_IDType eDisplayId, void *pEDIDInfo, uint32 *pEDIDSize)
{ 
  MDP_Status             eRetStatus = MDP_STATUS_SUCCESS;
  DPDriverConfigType    *pDPConfig  = GetDPDriverContext(eDisplayId);

  if ((NULL == pDPConfig) ||
      (NULL == pDPConfig->hDPHandle[DP_HOST_HANDLE_DEFAULT_INDEX]))
  {
    eRetStatus = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    if (NULL == pEDIDSize)
    {
      eRetStatus = MDP_STATUS_BAD_PARAM;
    }
    else
    {
      DP_GetPropertyParamsType sDPProp;
      
      DISP_OSAL_MemZero(&sDPProp, sizeof(sDPProp));

      if (NULL == pEDIDInfo)
      {
        // Just a query for the sizes
        sDPProp.sEdidInfo.uDataLength = 0;
      }
      else
      {
        // Pass in the size of the EDID structure
        sDPProp.sEdidInfo.uDataLength = *pEDIDSize;
      }

      sDPProp.sEdidInfo.pDataBuf = pEDIDInfo;

      if (DP_STATUS_SUCCESS == DP_Host_GetProperty(pDPConfig->hDPHandle[DP_HOST_HANDLE_DEFAULT_INDEX], DP_GETPROPERTY_EDID_INFO, &sDPProp))
      {
        // Return the EDID length on success
        *pEDIDSize = sDPProp.sEdidInfo.uDataLength;
      }
      else
      {
        *pEDIDSize = 0;
      }
    }
  }

  return eRetStatus;
}



/**********************************************************************************************************************

FUNCTION: ConfigureGPIO()

   This function will configure the GPIOs that controls the Aux and HPD

Parameters:
   eDisplayId    -[in]    : Display Id

Return:
   DP_Status

**********************************************************************************************************************/
static DP_Status ConfigureGPIO(MDP_Display_IDType eDisplayId)
{
  DP_Status                   eStatus           = DP_STATUS_SUCCESS; 

  MDPPlatformParams sMDPPlatformParam;
    
  MDP_OSAL_MEMZERO(&sMDPPlatformParam, sizeof(sMDPPlatformParam));
    
  sMDPPlatformParam.sDPGPIOConfigInfo.eDPControllerModeType = MDP_DP_CONTROLLER_MODE_DP; 
    
  if (MDP_STATUS_OK != MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_DPGPIOCONFIG, &sMDPPlatformParam))
  {
    DP_LOG_MESSAGE_ERROR("DP_ConfigureGPIO: MDPPlatformConfigure(MDPPLATFORM_CONFIG_DPGPIOCONFIG) failed for %d\n", eDisplayId );
    eStatus = DP_STATUS_FAIL;
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  GetControllerModeInfo
//
//  @brief
//      This function DP Controller mode setup by UEFI environment variable or 
//      PCD setting.
//
//  @params
//      [IN] eDisplayId
//          Display Id
//
//  @return
//     MDP_DP_ControllerModeType
//-------------------------------------------------------------------------------------------------
//
static MDP_DP_ControllerModeType GetControllerModeInfo(MDP_Display_IDType eDisplayId)
{
  MDP_DP_ControllerModeType eDPControllerModeType = MDP_DP_CONTROLLER_MODE_DEFAULT;

  // Currently DPTX2 is supported in USB-DP (Alt/Tunnel) or DP only (Std DP) mode
  if (MDP_DISPLAY_EXTERNAL5 == eDisplayId)
  {
    uint8                    uDPControllerModeType = 0;
    
    /* Retrieve the DP Controller mode from UEFI environment variable */
    if (MDP_STATUS_OK != MDP_GetEnvironmentVariable(L"DPControllerModeType", &uDPControllerModeType, sizeof(uint32)))
    {
      /* Failed to DP Controller mode from UEFI environment variable, try reading from the PCD setting */
      uDPControllerModeType = PcdGet32(PcdDPControllerModeType);
    }
    
    if (0 != uDPControllerModeType)
    {
      // Get the DP mode on Port2(DPTX2)
      eDPControllerModeType = DISPLAY_USB_GET_PORT_MODE(uDPControllerModeType, 2);
    }
  }

  return eDPControllerModeType;
}

