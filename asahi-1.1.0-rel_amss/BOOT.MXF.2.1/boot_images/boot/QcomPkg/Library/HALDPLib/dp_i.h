#ifndef _DP_I_H
#define _DP_I_H

/*=============================================================================
 
  File: dp_i.h
 
  Internal header file for DP Host
  
 
 Copyright (c) 2016-2023 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
 =============================================================================*/

/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/
#include "dp_types.h"
#include "dp_host.h"
#include "dp_spec.h"
#include "dp_tunneled_spec.h"
#include "hal_dp.h"
#include "dp_system.h"
#include <math.h>

/* --------------------------------------------------------------------------------------------------------------------
Enumerated types
---------------------------------------------------------------------------------------------------------------------*/

/* Dirty bits to indicate which configuration is changed and needs to be applied to hardware */
typedef enum
{
   DP_DIRTYFIELD_NONE                             = 0,
   DP_DIRTYFIELD_SETMODE                          = DP_BIT(0),        /* Panel Mode has changed                    */
   DP_DIRTYFIELD_LINK_RATE                        = DP_BIT(1),        /* Desired Link rate changed                 */
   DP_DIRTYFIELD_SINK_ATTRIB                      = DP_BIT(2),        /* Sink attributes changed                   */
   DP_DIRTYFIELD_TU_PARAMETERS                    = DP_BIT(3),        /* TU related parameters changed             */
   DP_DIRTYFIELD_MAINLINK_PACKET                  = DP_BIT(4),        /* Main link attributes changed              */
   DP_DIRTYFIELD_STREAM_ATTRIB                    = DP_BIT(5),        /* Stream attributes changed                 */
   DP_DIRTYFIELD_LANE_NUMBER                      = DP_BIT(6),        /* Desired Lane Number changed               */
   DP_DIRTYFIELD_DPCD_CONFIG                      = DP_BIT(7),        /* DPCD config changed                       */
   DP_DIRTYFIELD_HPD_POLARITY                     = DP_BIT(8),        /* HPD Polarity changed                      */   
   DP_DIRTYFIELD_BPC                              = DP_BIT(9),        /* Bit depth changed                         */
} DP_DeviceDirtyFieldType;


/* Link training status types */
typedef enum
{    
   DP_LINK_TRAINING_STATUS_NONE                   = 0,
   DP_LINK_TRAINING_STATUS_CLK_RECOVERY_DONE      = DP_BIT(0),        /* clock recovery is done                    */
   DP_LINK_TRAINING_STATUS_CHANNEL_EQ_DONE        = DP_BIT(1),        /* Channel equalization is done              */
   DP_LINK_TRAINING_STATUS_SYMBOL_LOCKED          = DP_BIT(2),        /* Symbol is locked                          */
   DP_LINK_TRAINING_STATUS_INTERLANE_ALIGN_DONE   = DP_BIT(3),        /* Inter-lane align is done                  */ 
   DP_LINK_TRAINING_STATUS_MAX,
   DP_LINK_TRAINING_STATUS_32BIT                  = 0x7FFFFFFF
} DP_LinkTrainingStatusType;

/* DP CTS test request*/
typedef enum
{
  DP_TEST_NONE                                    = 0,                /* No test is requested                             */
  DP_TEST_LINK_TRAINING                           = DP_BIT(0),        /* Link training test requested                     */
  DP_TEST_PATTERN                                 = DP_BIT(1),        /* Test video pattern requested                     */
  DP_TEST_EDID_READ                               = DP_BIT(2),        /* EDID read test requested                         */
  DP_TEST_PHY_PATTERN                             = DP_BIT(3),        /* Request the PHY test pattern                     */
  DP_TEST_FAUX_PATTERN                            = DP_BIT(4),        /* Request the Source to send the FAUX test pattern */
  DP_TEST_AUDIO_PATTERN                           = DP_BIT(5),        /* Test audio pattern requested                     */
  DP_TEST_AUDIO_DISABLED_VIDEO                    = DP_BIT(6),        /* Video stream output is requested to be disabled during audio test*/
} DP_TestRequestType;

/* DP PHY test pattern request*/
typedef enum
{
  DP_PHY_TEST_PATTERN_NONE                                = 0,        /* No PHY test pattern is requested                 */
  DP_PHY_TEST_PATTERN_D10_2_NO_SCRAMBLING,                            /* 10.2 without scrambling                          */
  DP_PHY_TEST_PATTERN_SYMBOL_ERR_MEASUREMENT_CNT,                     /* Symbol error measurement count                   */
  DP_PHY_TEST_PATTERN_PRBS7,                                          /* PRBS7                                            */
  DP_PHY_TEST_PATTERN_80_BIT_CUSTOM_PATTERN,                          /* 80bit custom pattern transmitted                 */
  DP_PHY_TEST_PATTERN_CP2520_PATTERN_1,                               /* CP2520 pattern 1                                 */
  DP_PHY_TEST_PATTERN_CP2520_PATTERN_2,                               /* CP2520 pattern 2                                 */
  DP_PHY_TEST_PATTERN_CP2520_PATTERN_3,                               /* CP2520 pattern 3                                 */
  DP_PHY_TEST_PATTERN_MAX,
} DP_PHYTestPatternType;

typedef enum
{
  DP_HOST_FLAG_NONE                               = 0,                /* No host flag set                                 */
  DP_HOST_FLAG_DS_PORT_STATUS_CHANGED             = DP_BIT(0),        /* Downstream port status changed                   */
  DP_HOST_FLAG_REDUNDANT_IRQ_HPD                  = DP_BIT(1),        /* Redundant IRQ HPD from sink                      */
  DP_HOST_FLAG_IRQ_HPD_OUT                        = DP_BIT(2),        /* IRQ HPD unplug is detected                       */
  DP_HOST_FLAG_AUX_INTERRUPT_DRIVEN               = DP_BIT(3),        /* Interrupt driven Aux                             */
  DP_HOST_FLAG_AUX_PN_SWITCH_INVERTED             = DP_BIT(4),        /* TypeC AUX P/N switch GPIO polarity is inverted   */
  DP_HOST_FLAG_AUX_FAILSAFE                       = DP_BIT(5),        /* Panel AUX has failed and is in failsafe mode     */
  DP_HOST_FLAG_TOPOLOGY_UPDATED                   = DP_BIT(6),        /* Topology update needs to be handled              */
  DP_HOST_FLAG_DISABLE_DSC                        = DP_BIT(7),        /* Disable DSC                                      */
  DP_HOST_FLAG_UNPLUG_HPD_DETECTED                = DP_BIT(8),        /* Unplug HPD event is detected                     */
  DP_HOST_FLAG_DISABLE_MST                        = DP_BIT(9),        /* Disable MST                                      */
  DP_HOST_FLAG_ALT_MODE_FIXED_LANE_CONFIGURATION  = DP_BIT(10),       /* Fixed lane configuration for alt-mode devices    */
  DP_HOST_FLAG_STRICT_EDID_CHECK                  = DP_BIT(11),       /* Enforce strict EDID check of CRC                 */
  DP_HOST_FLAG_SIMULATION_MODE                    = DP_BIT(12),       /* Enable or Disable Simulation mode for DP         */
  DP_HOST_FLAG_HPD_FAILSAFE                       = DP_BIT(13),       /* Enable eDP-like HPD, poll, wait, and ignore fail */
  DP_HOST_FLAG_MULTIFUNCTION_CONFIGURATION        = DP_BIT(14),       /* Enable concurrency in USB, shared lane config    */
  DP_HOST_FLAG_LINK_TRAINING_EQ_FALLBACK          = DP_BIT(15),       /* Fallback case in channel equalization failure    */
  DP_HOST_FLAG_DISABLE_ADAPTIVE_SYNC              = DP_BIT(16),       /* Disable Adaptive Sync(QSync)                     */
  DP_HOST_FLAG_AUX_EOT                            = DP_BIT(17),        /* AUX/I2C transaction with STOP (MOT=0)            */
  DP_HOST_FLAG_DISABLE_PSR                        = DP_BIT(18),       /* Disable PSR                                      */
  DP_HOST_FLAG_TUNNELED_PATH_TEARDOWN             = DP_BIT(20),       /* DP Tunneling path is torn down                   */
} DP_HostFlagType;

/* Shared resource configuration in DP bonded mode */
typedef enum
{
  DP_BONDED_MODE_SHARED_RESOURCE_NONE                   = 0x00000000,   /* No shared resource                             */
  DP_BONDED_MODE_SHARED_RESOURCE_EXTERNAL_PIXEL_CLOCK,                  /* Pixel clock sourced from another DP device     */
  DP_BONDED_MODE_SHARED_RESOURCE_MAX,
  DP_BONDED_MODE_SHARED_RESOURCE_FORCE_32BIT            = 0x7FFFFFFF
} DP_BondedModeSharedResourceType;


/* Modes of operation for Panel Self Refresh(PSR) feature in eDP panels */

typedef enum
{
  DP_PSR_MODE_DISABLE                    = 0x00000000,                   /**< PSR feature disabled    */
  DP_PSR_MODE_ENABLE_PSR,                                                /**< PSR Version 1           */
  DP_PSR_MODE_ENABLE_PSR2,                                               /**< PSR2 without FrameSync  */
  DP_PSR_MODE_ENABLE_PSR2_FRAME_SYNC,                                    /**< PSR2 with FrameSync     */
  DP_PSR_MODE_MAX,
  DP_PSR_MODE_FORCE_32BIT                = 0x7FFFFFFF
} DP_PSRModeType;

/* --------------------------------------------------------------------------------------------------------------------
** Macros and Struct
---------------------------------------------------------------------------------------------------------------------*/
#define MAX_AUX_CMD_BUFFER                                    144

#define DP_AUX_HW_TIMEOUT_MS                                  4        // HW timeout for AUX transactions


#ifdef DPDRIVER_EDP_MODE 
  /*
  * In eDP mode we only need to parse the internal panel's EDID
  * which will be limited to the first EDID block 
  */
  #define DP_MAX_NUM_CONTEXTS                                 1
  #define DPHOST_GET_DEVICE_CTX_FROM_ID(_deviceId)            (&(gDpSharedData.sDeviceCtx[0]))
  #define DP_EDID_MAX_NUM_OF_BLOCKS                           (0x04)   //Maximum number of pages for EDID structure
#else
  #define DP_MAX_NUM_CONTEXTS                                 DP_DEVICE_MAX
  #define DPHOST_GET_DEVICE_CTX_FROM_ID(_deviceId_)           (&(gDpSharedData.sDeviceCtx[((_deviceId_)<DP_DEVICE_MAX)?(_deviceId_):DP_DEVICE_ID_ALT_MODE_0]))
  #define DP_EDID_MAX_NUM_OF_BLOCKS                           (0x80)   //Maximum number of pages for EDID structure
#endif

#define DP_EDID_START_ADDRESS                                 (0x50)   //Start address of Display Port EDID base blocks.
#define DP_EDID_BLOCK_SIZE                                    (0x80)   //Each page size in the EDID ROM
#define DP_EDID_MAX_BUF_SIZE                                  (DP_EDID_BLOCK_SIZE * DP_EDID_MAX_NUM_OF_BLOCKS)
#define DP_EDID_EXT_BLOCK_NUM_OFFSET                          (0x7E)
#define DP_EDID_SEGMENT_ADDRESS                               (0x30)

/* Link rates supported by DP Host */
#define DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_162MBps              162000
#define DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_270MBps              270000
#define DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_540MBps              540000
#define DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_810MBps              810000
#define DP_LINK_SYMBOL_SIZE                                   10       // symbol size = 10 bits

// FEC overhead for DP Link
#define DP_LINKRATE_FEC_OVERHEAD_RATIO                        0.97582

#define DP_MAX_RESOLUTION_WIDTH                               4096
#define DP_MAX_RESOLUTION_HEIGHT                              4096
#define DP_MAX_RESOLUTION_WIDTH_EXTERNAL                      3840
#define DP_MAX_RESOLUTION_HEIGHT_EXTERNAL                     2160
#define DP_MIN_RESOLUTION_WIDTH                               640
#define DP_MIN_RESOLUTION_HEIGHT                              480
#define DP_MAX_REFRESH_RATE_HZ                                120
#define DP_MIN_REFRESH_RATE_HZ                                24
#define DP_MAX_PIXEL_RATE                                     12943360
#define DP_NUM_COLOR_COMPONENTS                               3        // 3 for RGB format
#define DP_MIN_BPC_SUPPORT                                    8

#define DP_PREFERRED_REFRESH_RATE_HZ                          60

// List of displays for which a soft HPD can be requested
#define DP_MAX_HPD_LIST_SIZE                                  4

// PPS buffer size
#define DP_PPS_BUFFER_SIZE                                    128

#define DP_EDID_READ_RETRY_NUMBER                             3        // Retry reading EDID

// Maximum bytes that a generic SDP holds
#define DP_GENERIC_SDP_PAYLOAD_BYTES_MAX                      32

// DSC compression ratio
#define DP_DSC_COMPRESSION_RATIO                              3

// EDID invalid bandwidth filter that will filter out all modes 
#define DP_INVALID_BANDWIDTH                                  1 

// Number of ASCII character for device identification string
#define DP_DEVICE_IDENTIFIER_STRING_LEN                       6

/* OUI Device string of the Kandou retimer */
#define DP_RETIMER_KB8001                                     "KB8001"

/* Get the color info from DP_PixelFormatType */
#define DPHOST_GETPIXELFMT(_pixelFmt_)                        (gsDPPixelFormatInfo[((_pixelFmt_)<DP_PIXEL_FORMAT_MAX)?(_pixelFmt_):DP_PIXEL_FORMAT_NONE])

#define DPHOST_GETFLAG(  _flag_, _bit_)                       (((_flag_) & (_bit_)) ? 1: 0)
#define DPHOST_SETFLAG(  _flag_, _bit_)                       ((_flag_) | ( _bit_))
#define DPHOST_CLEARFLAG(_flag_, _bit_)                       ((_flag_) & (~(_bit_)))

/* Return _mapFlag_ with _mapBit_ set if _flag_ has _bit_ set */
#define DPHOST_MAPSETFLAG(_flag_, _mapFlag_, _bit_, _mapBit_) (((_flag_) & (_bit_)) ? ((_mapFlag_) | (_mapBit_)) : (_mapFlag_))

#define DPHOST_GETCTX_FROM_HANDLE(hHandle)                    ((DP_DisplayCtxType*) hHandle)
#define DPHOST_GET_DEVICE_CTX(_displayCtx_)                   ((NULL == (_displayCtx_))? NULL:(_displayCtx_)->pDeviceCtx)
#define DPHOST_GET_STREAM_CTX(_displayCtx_)                   ((NULL == (_displayCtx_))? NULL:(_displayCtx_)->pStreamCtx)
#define DPHOST_GET_HOSTROUTER_CTX(_displayCtx_)               ((NULL == (_displayCtx_))? NULL:(_displayCtx_)->pHostRouterCtx)

#define DPHOST_MAX(a,b)                                       (a > b ? a : b)
#define DPHOST_MIN(a,b)                                       (a < b ? a : b)

#define Q16                                                   (16)
#define Q16_MAX                                               (1<<Q16)

/* Truncate a Q16.16 value and only return the whole number portion */
#define Q16_WHOLE(x)                                          ((int32)((x)>>16))

/* Truncate a Q16.16 value and only return the ceil of whole number portion , if fractional value is present adding 1 so to round off to uper whole number  */
#define Q16_CEIL_WHOLE(x)                                     ((x) & 0x0000FFFF)? Q16_WHOLE(((x) + Q16_MAX)):Q16_WHOLE((x))

/* Ceil function for integer division */
#define DPHOST_CEIL(_x_, _y_)                                 (((_x_) + (_y_) - 1) / (_y_))

/* Rounding macro for floats (i/o: float/uint32) */
#define DPHOST_ROUND(x)                                       ((x)>=0?(uint32)((x)+0.5):(uint32)((x)-0.5))

/* Convert a float _value_ in the range 0.0 - 1.0 to an integer value in the _range_ */
#define DPHOST_FLOAT_TO_INT(_value_,_range_)                  (((_value_) < 1.0f) ? (uint32)(((_value_) * (_range_)) + 0.5f) : (_range_))

#define DPHOST_ARRAY_SIZE(arr)                                (sizeof((arr)) / sizeof(arr[0]))

/* Defines for kilo */
#define DP_KILO(_x_)                                          ((_x_)*1000)

/* Defines for mega */
#define DP_MEGA(_x_)                                          ((_x_)*1000000)

/* Convert Q16 value to decimal */
#define DP_Q16_TO_DECIMAL(_val_)                              ((_val_) >> 16)

/* Convert decimal to Q16 value */
#define DP_DECIMAL_TO_Q16(_val_)                              ((_val_) << 16)

/* Check if device is LTTPR repeater */
#define DPHOST_CHECK_IS_LTTPR_REPEATER(_devicectx_)           ((DP_LTTPR_NO_REPEATER < (_devicectx_)->eLTTPRRepeaterID) && (DP_LTTPR_REPEATER_MAX > (_devicectx_)->eLTTPRRepeaterID))

/* --------------------------------------------------------------------------------------------------------------------
** Preprocessor Definitions and Constants
** ----------------------------------------------------------------------------------------------------------------- */

/* Forward declaration */
typedef struct _DP_DisplayCtxType DP_DisplayCtxType;

//-------------------------------------------------------------------------------------------------
//  DP_PixelFormat_Info
//
//  @brief
//      Color format info.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct 
{
   uint32                   uBitsPerPixel;                      /**< Bits per pixel                                   */
   uint32                   uBitsPerComponent;                  /**< Bits per each color component (R/G/B, Y/U/V)     */
} DP_PixelFormat_Info;

//-------------------------------------------------------------------------------------------------
//  DP_MSTSinkList
//
//  @brief
//      List of MST sinks that require HPD in/out.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  MDP_Display_IDType eDisplayID; /**< New or removed sink      */
  bool32             bHPDIn;     /**< Requires Soft HDP IN/OUT */
} DP_MSTSinkList;

//-------------------------------------------------------------------------------------------------
//  DP_BondedModeConfigType
//
//  @brief
//      DP bonded mode configuration info.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  bool32                           bEnabled;               /**< Is the DP Device part of a bonded mode configuration                     */
  DP_BondedModeSharedResourceType  eSharedResourceConfig;  /**< Specifies the resource to be shared by the DP Devices in bonded mode     */
  DP_DeviceIDType                  eSourceClockDeviceID;   /**< Device ID of DP Device sourcing the shared clock                         */
  DP_DeviceIDType                  eMasterAUXDeviceID;     /**< Device ID of the master device for AUX transactions in bonded mode       */
} DP_BondedModeConfigType;

//-------------------------------------------------------------------------------------------------
//  DP_AUXFunctionType
//
//  @brief
//      Types of DP AUX function that can be installed.
//
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  DP_AUX_FUNCTION_TYPE_PHYSICAL = 0,  /**< AUX physical function */
  DP_AUX_FUNCTION_TYPE_SIM,           /**< AUX SIM function */
  DP_AUX_FUNCTION_TYPE_REDIRECTOR,    /**< AUX redirector function */
  DP_AUX_FUNCTION_TYPE_TUNNELING,     /**< USB4 tunneling function */
  DP_AUX_FUNCTION_TYPE_MAX,
  DP_AUX_FUNCTION_TYPE_FORCE_32BIT  = 0x7FFFFFFF
} DP_AUXFunctionType;

typedef DP_HandleType OSEventType;
typedef DP_HandleType OSThreadType;
typedef char OSCharType;

//-------------------------------------------------------------------------------------------------
//  DP_AuxTableType
//
//  @brief
//      AUX read/write function pointer structure
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  DP_Status(*DP_AUX_Read)(
    DP_DisplayCtxType  *pDisplayCtx,
    DP_ReadPacketType  *psReadPacket);

  DP_Status(*DP_AUX_Write)(
    DP_DisplayCtxType  *pDisplayCtx,
    DP_WritePacketType *psWritePacket);
} DP_AuxTableType;

//-------------------------------------------------------------------------------------------------
//  DP_TunneledModeCfg
//
//  @brief
//      DP tunneling mode configuration info.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  bool32                       bTunnelingMode;    /**< DP tunneling mode enable */
  DP_TunneledDPCapsFieldsType  sDPLocalCaps;      /**< Fields of DP_LOCAL_CAP register in the DP Adapter Configuration Capability section  */
  DP_TunneledDPCapsFieldsType  sDPRemoteCaps;     /**< Fields of DP_REMOTE_CAP register in the DP Adapter Configuration Capability section */
  DP_TunneledDPCapsFieldsType  sDPCommonCaps;     /**< Fields of DP_COMMON_CAP register in the DP Adapter Configuration Capability section */
  bool32                       bMFDPModeEnabled;  /**< MFDP mode enable/disable                                                            */
} DP_TunneledModeCfg;

//-------------------------------------------------------------------------------------------------
//  DP_StreamCtxType
//
//  @brief
//      Present Stream context for one of the streams associated with the same DP device.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct _DP_StreamCtxType
{
  bool32                     bInUse;                                         /**< Is context in use with a handle allocated        */
  MDP_Display_IDType         eDisplayID;                                     /**< DisplayID associated with this stream            */
  DP_MSTStreamIDType         eMSTStreamId;                                   /**< MST stream this context is driving               */
  bool32                     bInitialized;                                   /**< Is context initialized and ready to be active    */
  bool32                     bSinkConnected;                                 /**< Whether this display is connected                */
  uint32                     uDirtyBits;                                     /**< Which config has changed                         */
  uint32                     uPixelClkInKhz;                                 /**< Pixel clk                                        */
  uint32                     uModeIndex;                                     /**< Present mode                                     */
  bool32                     bEDIDObtained;                                  /**< Has EDID been read from display                  */
  uint32                     uNumModes;                                      /**< Number of modes supported by display             */
  DP_PanelInfoType           sPanelInfo[MAX_DP_PANEL_MODE];                  /**< Panel info for all the display modes             */
  uint8                      auEDIDCache[DP_EDID_MAX_BUF_SIZE];              /**< DP Sink EDID data                                */
  uint32                     uEDIDDataLength;                                /**< Length of EDID data                              */
  DP_AudioModeInfoPropType   sAudioModeInfo[MAX_DP_AUDIO_MODE];              /**< Audio mode list                                  */
  uint32                     uNumberOfAudioModes;                            /**< Number of audio modes supported by DP sink       */
  DP_VendorInfoType          sVendorInfo;                                    /**< Vendor specific info                             */
  uint32                     uBitDepth;                                      /**< Sink device bit depth                            */
  uint32                     uMSTAvailablePBN;                               /**< PBN available for this MST sink                  */
  DP_SinkDSCCapType          sDSCCaps;                                       /**< DSC capabilities of sink                         */
  DP_SinkFECCapType          sFECCaps;                                       /**< FEC capabilities of sink                         */
  DP_DSCInfoType             sDSCInfo;                                       /**< DSC info                                         */
  uint32                     uVirtualChannelId;                              /**< Virtual channel id                               */
  uint32                     uMaxNumSlots;                                   /**< The max number of slots the stream can have      */
  uint32                     uPixelRate;                                     /**< The number of pixels per frame                   */
  DP_HandleType              hHPDWorkItem;                                   /**< HPD work item                                    */
  DP_AuxTableType            sAuxFunctions;                                  /**< Function pointer table for AUX communication     */
  DP_SinkBrightnessCapType   sBrightnessCaps;                                /**< Brightness control capabilities of sink          */
  DP_DeviceSpecificInfoType  sDeviceSpecificInfo[DP_DEVICESPECIFIC_MAX];     /**< Device specific idenfitication info of sink      */
  MDP_Panel_BacklightType    eBrightnessType;                                /**< Panel brightness control type                    */
  uint32                     uMaxBitDepth;                                   /**< Max bit depth for stream                         */
} DP_StreamCtxType;
 
//-------------------------------------------------------------------------------------------------
//  DP_DeviceCtxType
//
//  @brief
//      Present Device context for DP device.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct _DP_DeviceCtxType
{
  DP_DeviceIDType            eDeviceID;                             /**< Which DP device in case there should be multiple   */
  MDP_Display_IDType         eDisplayID;                            /**< DisplayID for the physical device                  */  
  bool32                     bInitialized;                          /**< Is device handle initialized                       */
  bool32                     bLinkConfigured;                       /**< Is link configured, used in DP_Host_SetMode        */
  uint32                     uNumLanes;                             /**< Number of lanes enabled : 1, 2 or 4                */
  uint32                     uLinkRateInKhz;                        /**< Link rate                                          */
  bool32                     bSynchronousClk;                       /**< Are pixel clk and link clk in synchronous mode     */
  MDP_DP_PHY_SSCConfigType   eSSCMode;                              /**< Enable spread spectrum clocking (downspread)       */
  bool32                     bPluggedIn;                            /**< Is external display connected                      */
  bool32                     bInvertedPlug;                         /**< USB type-C plug orientation (TRUE:porselect = 1)   */
  DP_LinkTrainingType        eLinkTrainingType;                     /**< Type of link training requested by user            */
  uint32                     uVoltageSwingLevel;                    /**< Current voltage swing level set to Sink            */
  uint32                     uPreEmphasisLevel;                     /**< Current pre-emphasis level set to Sink             */
  uint32                     uMaxVoltSwingLvl;                      /**< Max voltage swing level supported by sink          */
  uint32                     uMaxPreemphLvl;                        /**< Max pre-emphasis level supported by sink           */
  DP_ConnectionPinAssignment ePinAssignment;                        /**< DP Pin assignment                                  */
  DP_TestRequestType         ePendingTestRequest;                   /**< Pending test request                               */
  uint32                     uSinkCount;                            /**< Sink count on connected port                       */
  bool32                     bCPReady;                              /**< Indicate when all Sink devices are CP-capable      */
  DP_ControllerIDType        eControllerID;                         /**< DP controller index                                */
  OSEventType                hIRQPollingEventExit;                  /**< Indicate IRQPollingThread exit                     */
  OSEventType                hIRQPollingEventStalled;               /**< Indicate IRQPollingThread is stalled               */
  OSThreadType               hIRQPollingThread;                     /**< Thread to poll for IRQ_HPD event                   */
  bool32                     bLinkLost;                             /**< Link lost                                          */
  uint32                     uIRQPollingIntervalInMs;               /**< Interval between polling IRQ HPG in ms             */
  OSEventType                hAuxAccessLock;                        /**< Lock to sync DPCD reads and writes                 */
  DP_ConnectionStatusType    eConnectionPolarity;                   /**< Connection polarity                                */
  uint32                     uLaneMapping;                          /**< Defines Physical to logic lane mapping             */
  DP_DPCDSinkCapType         sSinkDPCDCap;                          /**< Sink capabilities read from DPCD                   */
  bool32                     bDualPixelMode;                        /**< Enable 2 Pixels per clock mode                     */
  DP_PHYTestPatternType      ePhyTestPattern;                       /**< DP PHY test pattern request                        */
  DP_CapsInfoType            eCapabilityMask;                       /**< Bitwise DP capability mask                         */
  uint32                     uFlags;                                /**< Defines DP related flags specified in
                                                                         DP_HostFlagType enum                               */
  bool32                     bMSTEnabled;                           /**< MST is enabled for this context                    */
  DP_StreamCtxType           aStreamCtx[DP_MST_STREAM_ID_MAX];      /**< Context specific to each stream                    */
  uint32                     uNumActiveStreams;                     /**< Number of Active streams                           */
  uint32                     uRemainingVCSlots;                     /**< Remaining VC slots for MST streams                 */
  uint32                     uTotalPixelRate;                       /**< Total number of pixels per frame                   */
  /**< DP AUX Transaction wait status parameter */
  OSEventType                hAuxReadyEvent;                        /**< Event to signal that AUX transaction status 
                                                                         is ready                                           */
  uint8                      uAUXCmdBuffer[MAX_AUX_CMD_BUFFER];     /**< Shared buffer for AUX Cmd Buffer                   */
  uint32                     uAUXCmdBufferCurrentSize;              /**< Current queued Command size in Cmd buffer          */
  uint32                     uAUXNumOfTransaction;                  /**< Current number of AUX Transaction                  */
  DP_TransactionModeType     eAUXTransactionTypeInQueue;            /**< Current AUX Transaction type in CMD FIFO           */
  uint32                     uMaxAUXCmdFifoLen;                     /**< The Max AUX CMD FIFO length                        */
  volatile bool32            bAuxReady;                             /**< DP AUX is configured                               */
  uint32                     uDeviceServiceIRQVector;               /**< Device Service IRQ vector                          */
  uint32                     uMSTSinkHPDCount;                      /**< Number of MST sinks that require HPD IN/OUT        */
  DP_MSTSinkList             sMSTSinkHPDList[DP_MAX_HPD_LIST_SIZE]; /**< List of new or disconnected sinks                  */
  uint32                     uMaxRefreshRate;                       /**< The maximum value of refresh rate (in Hz) that   
                                                                         can be supported by Panel read from EDID           */
  uint32                     uMinRefreshRate;                       /**< The minimum value of refresh rate (in Hz) that    
                                                                         can be supported by Panel read from EDID           */
  uint8                      aSinkStatus[6];                        /**< Raw sink status DPCD registers 0x0202~0x0207       */
  DP_DiagLevelType           eDiagLevel;                            /**< Diagnostic level configuration                     */
  DP_PSRRequestType          ePSRState;                             /**< Cache of the last PSR requested state              */
  DP_DPCDSinkCapRawDataType  sDPCDCapRawData;                       /**< Raw DPCD caps                                      */  
  DP_Config_PreEmphSwingType sPreEmphSwingConfigType;               /**< Pre-emphasis/Voltage swing override config data    */
  DP_BondedModeConfigType    sBondedModeConfig;                     /**< Bonded mode configuration info                     */
  DP_TunneledModeCfg         sTunnelingModeConfig;                  /**< DP tunneling mode config                           */
  DP_DeviceModeType          eDeviceDPMode;                         /**< DP Device mode i.e., eDP, DP, Alt mode or 
                                                                         tunneling                                          */
  bool32                     bFECEnabled;                           /**< Forward Error Correction enabled                   */
  DP_LTTPRCapType            sLTTPRCaps;                            /**< Link training tunable phy repeater caps            */
  DP_LTTPR_RepeaterIDType    eLTTPRRepeaterID;                      /**< ID of the current repeater being trained           */
  DP_LTTPR_DeviceInfoType    sLTTPRDeviceInfo;                      /**< LTTPR device specific idenfitication info          */
  uint32                     uLTTPRCETrainingIntervalInUs;          /**< LTTPR device specific channel equalization timing  */  
  DP_CustomSinkType          eCustomSinkType;                       /**< Specific custom sink type                          */
  DP_SourceCapType           sSourceOverrideCaps;                   /**< DP source caps that override DP sink caps          */
} DP_DeviceCtxType;

//-------------------------------------------------------------------------------------------------
//  DP_HostRouterDeviceCtxType
//
//  @brief
//      Present Device context for the DP Tunneling Host Router Device.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct _DP_HostRouterDeviceCtxType
{
  DP_DeviceIDType                eDeviceID;           /**< Which DP device in case there should be multiple */
  MDP_Display_IDType             eDisplayID;          /**< DisplayID for the physical device                */
  bool32                         bInitialized;        /**< Is device handle initialized                     */
  DP_HostRouterControllerIDType  eControllerID;       /**< DP Tunneling Host Router controller index        */
} DP_HostRouterDeviceCtxType;

//-------------------------------------------------------------------------------------------------
//  DP_DisplayCtxType
//
//  @brief
//      Present Display context for the external Display.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct _DP_DisplayCtxType
{
  DP_DeviceCtxType           *pDeviceCtx;              /**< Display context shared by displays connected to the same device                      */
  DP_StreamCtxType           *pStreamCtx;              /**< Display Context specific to a single stream                                          */
  DP_HostRouterDeviceCtxType *pHostRouterCtx;          /**< DP Tunneling Host Router context; shared by displays connected to the same device    */
} DP_DisplayCtxType;

//-------------------------------------------------------------------------------------------------
//  DP_TUSizePararmType
//
//  @brief
//      Transfer Unit config parameters.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  MDP_Display_IDType       eDisplayId;                         /**< Display Id                                               */
  uint32                   uWidth;                             /**< Screen width (adjusted according to DSC)                 */
  double                   dPixelClockInMhz;                   /**< Pixel clock freq in Khz (adjusted according to DSC)      */
  double                   dLinkClockInMhz;                    /**< Link clock freq in Khz (adjusted incase FEC is enabled)  */
  double                   dHBlankPeriod;                      /**< Horizontal Blanking Period (adjusted according to DSC)   */
  uint32                   uNumberOfLanes;                     /**< Number of Lanes in use                                   */
  uint32                   uBPP;                               /**< Bits per pixel(18/24/30).always 24 for DSC               */
  HAL_DP_PixelFormatType   ePixelFormat;                       /**< Pixel format                                             */
  bool32                   bSynchronousClk;                    /**< Pixel and Link clock are synchronous                     */
  bool32                   bDSCEnabled;                        /**< DSC is Enabled                                           */
  bool32                   bFECEnabled;                        /**< FEC is Enabled                                           */
  bool32                   bRB2Timing;                         /**< Is the current display mode an RB2 timing                */
  double                   dActualPixelClk;                    /**< Original pixel clk with SSC (pixel clock of the hardware)*/
  double                   dActualLinkClk;                     /**< Actual Link Clock frequency                              */
  uint32                   uOriginalWidth;                     /**< original width without DSC adjustment                    */
  uint32                   uOriginalhbp;                       /**< Horizontal blanking period without DSC adjustment        */
} DP_TUSizeCalcParamType;

//-------------------------------------------------------------------------------------------------
//  DP_RGSizePararmType
//
//  @brief
//      Rate Governor config parameters.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
   MDP_Display_IDType       eDisplayId;                         /**< Display Id                                               */
   uint32                   uVisWidth;                          /**< Screen width                                   */
   uint32                   uPixelClockInKhz;                   /**< Pixel clock freq in Khz                        */
   double                   dLinkClockInMhz;                    /**< Link clock freq in Mhz                         */
   uint32                   uNumberOfLanes;                     /**< Number of Lanes in use                         */
   uint32                   uBPP;                               /**< Bits per pixel                                 */
   bool32                   bYUV420;                            /**< Pixel format is YUV420                         */
   bool32                   bSynchronousClk;                    /**< Pixel and Link clock are synchronous           */
   bool32                   bDSCEnabled;                        /**< DSC is Enabled                                 */
   bool32                   bFECEnabled;                        /**< FEC is Enabled                                 */
   float                    fDSCOverHead;                       /**< DSC overhead by EOC and dummy bytes            */
} DP_RGCalcParamType;

//-------------------------------------------------------------------------------------------------
//  DP_DeviceDataType
//
//  @brief
//      Device context for all the devices.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct 
{
  bool32                      bInitialized;                                   /**< Flag indicating if DP driver is initialized                 */
  OSEventType                 hHostLock;                                      /**< A global lock to protect resources shared among all
                                                                                   devices and streams, created in DP_Host_Init.               */ 
  DP_DeviceCtxType            sDeviceCtx[DP_MAX_NUM_CONTEXTS];                      /**< Present context of this device                              */
  int32                       uSourceClockRefCount[DP_DEVICE_MAX];            /**< Ref counts for clock sources; required for
                                                                                   bookkeeping in bonded mode configurations                   */
  DP_HostRouterDeviceCtxType  sHostRouterDeviceCtx[DP_DEVICE_MAX];            /**< Present DP Tunneling Host Router context of this device     */
} DP_DeviceDataType;

//-------------------------------------------------------------------------------------------------
//  DP_ControllerInfoType
//
//  @brief
//      Struct used for dynamic controller availability.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  DP_ControllerIDType eControllerID; /**< Controller ID.                   */
  bool32              bInUse;        /**< TRUE if controller is allocated. */
} DP_ControllerInfoType;

//-------------------------------------------------------------------------------------------------
//  DP_PSRCfgType
//
//  @brief
//      PSR configuration to be applied
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{                                                           
   DP_PSRModeType                   ePSRMode;                          /**< Mode of operation for PSR feature                */
   bool32                           bMainLinkActive;                   /* Mainlink shut down/Active during PSR */
   bool32                           bVerifyCRC;                        /* Frame CRC verification done by sink */
   bool32                           bCaptureSecondFrame;               /* Capture 2nd frame instead of 1st after PSR entry */
} DP_PSRCfgType;

/*---------------------------------------------------------------------------------------------------------------------
 * Global Data Definitions
 *-------------------------------------------------------------------------------------------------------------------*/
extern DP_PixelFormat_Info                    gsDPPixelFormatInfo[DP_PIXEL_FORMAT_MAX];
extern DP_DeviceDataType                      gDpSharedData;

//-------------------------------------------------------------------------------------------------
//  DP_LinkTraining
//
//  @brief
//      API does DP link training
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] eLinkTrainingType
//          Calculated RG parameters.
//      [IN] uFlags
//          Reserved.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_LinkTraining(DP_DisplayCtxType        *pDisplayCtx,
                          DP_LinkTrainingType       eLinkTrainingType,
                          DP_FlagsType              uFlags);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkDPCDCap
//
//  @brief
//      This function will read Sink Capability Data from DPCD over AUX Channel.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_ReadSinkDPCDCap(DP_DisplayCtxType   *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkDPCDStatus
//
//  @brief
//      This function will read Sink Status Raw Data from DPCD over AUX Channel.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [OUT] psDPCDSinkStatus
//          Pointer to DPCD Sink Status Data struct.
//      [IN] uReadFlags
//          Flags to be used for DP AUX read.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_ReadSinkDPCDStatus(DP_DisplayCtxType      *pDisplayCtx,
                                DP_DPCDSinkStatusType  *psDPCDSinkStatus, 
                                uint32                  uReadFlags);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkDSCCap
//
//  @brief
//      This function will read Sink DSC Capability over AUX Channel
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkDSCCap(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkDSCStatus
//
//  @brief
//      This function will read sink DSC Status
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkDSCStatus(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkDSCEnable
//
//  @brief
//      This function will read DSC enable flag from sink
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkDSCEnable(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkFECCap
//
//  @brief
//      This function will read Sink FEC Capability over AUX Channel
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkFECCap(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkFECStatus
//
//  @brief
//      This function will read sink FEC Status
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkFECStatus(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkFECEnable
//
//  @brief
//      This function will read FEC enable flag from sink
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkFECEnable(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkPSRStatus
//
//  @brief
//      Read PSR status from Sink
//
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context handle.
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
DP_Status  DP_ReadSinkPSRStatus(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkCRC
//
//  @brief
//      Read CRC values from Sink
//
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context handle.
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
DP_Status  DP_ReadSinkCRC(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkFECConfig
//
//  @brief
//      This function will write FEC configuration to sink
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] bEnable
//          Flag used to determine if DSC needs to be enabled/disabled
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkFECConfig(DP_DisplayCtxType *pDisplayCtx, bool32 bEnable);

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkDPCDLink
//
//  @brief
//      This function will Write the link setting to panel DPCD
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_WriteSinkDPCDLink(DP_DisplayCtxType    *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkDPCDTrainingPattern
//
//  @brief
//      This function will select the training pattern for link training to panel DPCD.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] eTraingPattern
//          Link Training pattern.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_WriteSinkDPCDTrainingPattern(DP_DisplayCtxType              *pDisplayCtx,
                                          DP_DPCDTrainingPatternSetType   eTraingPattern);

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkDPCDLevels
//
//  @brief
//      This function will select the training Voltage Swing Level and Pre-emphasis Level.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] uDesiredVoltageSwingLevel
//          The desired Voltage Swing level for link training.
//      [IN] uDesiredPreEmphasisLevel
//          The desired pre-emphasis level for link training.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_WriteSinkDPCDLevels(DP_DisplayCtxType   *pDisplayCtx,
                                 uint32               uDesiredVoltageSwingLevel,
                                 uint32               uDesiredPreEmphasisLevel);

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkDPCDPower
//
//  @brief
//      This function will set the sink power state. i.e Power on/off for main link or AUX.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] ePowerState
//          Sink power state to be set.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_WriteSinkDPCDPower(DP_DisplayCtxType     *pDisplayCtx,
                                DP_DPCDPowerStateType  ePowerState);

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkDPCDDownSpreadEnabled
//
//  @brief
//      This function will indicate that downspread has been enabled on host side.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_WriteSinkDPCDDownSpreadEnabled(DP_DisplayCtxType    *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkDSCConfig
//
//  @brief
//      This function will write sink DSC configuration.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] bEnable
//          Flag used to determine if DSC needs to be enabled/disabled
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkDSCConfig(DP_DisplayCtxType *pDisplayCtx, bool32 bEnable);

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkALPMConfig
//
//  @brief
//      This function will toggle sink's ALPM feature
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] bEnable
//          TRUE:  Enable ALPM ; FALSE: Disable ALPM
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkALPMConfig(DP_DisplayCtxType* pDisplayCtx, bool32 bEnable);

//-------------------------------------------------------------------------------------------------
//  DP_ParseSinkEDID
//
//  @brief
//      This function will parse the EDID info from the Raw EDID Data.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ParseSinkEDID(DP_DisplayCtxType    *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkEDIDRaw
//
//  @brief
//      This function will read EDID Raw Data from Sink over I2c.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkEDIDRaw(DP_DisplayCtxType    *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ParseSinkEDID
//
//  @brief
//      This function will calculate the TU based the the lane #, link clock, 
//      pixel clock, color format.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [OUT] psTUConfig
//          The TU parameters.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_CalculateTU(DP_TUSizeCalcParamType          *psDisplayInfo,
                         HAL_DP_TUConfigType             *psTUConfig);

//-------------------------------------------------------------------------------------------------
//  DP_CalculateLink
//
//  @brief
//      This function will Calculate the Link settings, such as clock freq, number of lane needed.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] psDPCDSinkCap
//          Pointer to sink DPCD capabilitess.
//      [IN] psPanelInfo
//          Pointer to panel info corresponding to current mode.
//      [OUT] pPixClkInfo
//          Pointer to pixel clock info (dividers, etc.).
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_CalculateLink(DP_DisplayCtxType        *pDisplayCtx,
                            DP_DPCDSinkCapType       *psDPCDSinkCap,
                            DP_PanelInfoType         *psPanelInfo,
                            DP_PixelClk_Info         *pPixClkInfo);

//-------------------------------------------------------------------------------------------------
//  DP_CalculateMisc0
//
//  @brief
//      This function will calculate the MISCO value according to DP Spec.
//
//  @params
//      [IN] eColorFormat
//          Sink color format.
//
//  @return
//      uint8.
//-------------------------------------------------------------------------------------------------
//
uint8  DP_CalculateMisc0(DP_PixelFormatType eColorFormat );

//-------------------------------------------------------------------------------------------------
//  DP_Host_AuxInstall
//
//  @brief
//      Install AUX function table. AUX functions may need initialization before use.
//
//  @params
//      [IN] pDeviceCtx
//          Device context.
//      [IN] pStreamCtx
//          Stream context.
//      [IN] eFunctionType
//          Type of AUX function (physical, simulated, section redirector)
//
//  @return
//      void
//-------------------------------------------------------------------------------------------------
void DP_Host_AuxInstall(DP_DeviceCtxType  *pDeviceCtx,
                        DP_StreamCtxType  *pStreamCtx,
                        DP_AUXFunctionType eFunctionType);

//-------------------------------------------------------------------------------------------------
//  DP_Host_AuxWriteRaw
//
//  @brief
//      This function will write to AUX/I2c channel.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN/OUT] psWritePacket
//          The write packet.
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_AuxWriteRaw(DP_DisplayCtxType   *pDisplayCtx,
                              DP_WritePacketType  *psWritePacket);

//-------------------------------------------------------------------------------------------------
//  DP_Host_AUX_ClientWrite
//
//  @brief
//      This function will write to AUX/I2c channel through wired channel
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN/OUT] psReadPacket
//          The read packet.
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_AUX_ClientWrite(DP_DisplayCtxType  *pDisplayCtx,
                                  DP_WritePacketType *psWritePacket);

//-------------------------------------------------------------------------------------------------
//  DP_Host_Simulation_ClientWrite
//
//  @brief
//      This function will write to AUX/I2c channel from memory.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN/OUT] psReadPacket
//          The read packet.
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_Simulation_ClientWrite(DP_DisplayCtxType  *pDisplayCtx,
                                         DP_WritePacketType *psWritePacket);

//-------------------------------------------------------------------------------------------------
//  DP_Host_AuxReadRaw
//
//  @brief
//      This function will read from AUX/I2c channel.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN/OUT] psReadPacket
//          The read packet.
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_AuxReadRaw(DP_DisplayCtxType   *pDisplayCtx,
                             DP_ReadPacketType   *psReadPacket);

//-------------------------------------------------------------------------------------------------
//  DP_Host_AUX_ClientRead
//
//  @brief
//      This function will read from AUX/I2c channel through wired channel.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN/OUT] psReadPacket
//          The read packet.
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_Host_AUX_ClientRead(DP_DisplayCtxType *pDisplayCtx,
                                  DP_ReadPacketType *psReadPacket);

//-------------------------------------------------------------------------------------------------
//  DP_Host_Simulation_ClientRead
//
//  @brief
//      This function will read from AUX/I2c channel from memory.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN/OUT] psReadPacket
//          The read packet.
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_Simulation_ClientRead(DP_DisplayCtxType *pDisplayCtx,
                                        DP_ReadPacketType *psReadPacket);

//-------------------------------------------------------------------------------------------------
//  DP_Host_SetAUXFailsafeMode
//
//  @brief
//      This function simulates the display AUX being plugged-in.
//
//  @params
//      [IN] pDeviceCtx
//          Handle to DP Device context.
//      [IN] pStreamCtx
//          Handle to DP Stream context.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
DP_Status DP_Host_SetAUXFailsafeMode(DP_DeviceCtxType *pDeviceCtx,
                                     DP_StreamCtxType *pStreamCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadTestRequest
//
//  @brief
//      This function will read DPCP test request fields for compliance test.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_ReadTestRequest(DP_DisplayCtxType    *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_WriteTestResponse
//
//  @brief
//      This function will write DPCP test response fields for compliance test.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_WriteTestResponse(DP_DisplayCtxType    *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_CheckTrainingResult
//
//  @brief
//      This function will get the max (among all lanes) drive setting requested by the sink.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] psDPCDSinkStatus
//          Pointer to DPCP sink status.
//      [IN] eTrainingType
//          type of link training done.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
bool32  DP_CheckTrainingResult(DP_DisplayCtxType           *pDisplayCtx,
                               DP_DPCDSinkStatusType       *psDPCDSinkStatus,
                               DP_LinkTrainingStatusType    eTrainingType);

//-------------------------------------------------------------------------------------------------
//  DP_Host_SetMode
//
//  @brief
//      Set selected display mode.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_Host_SetMode(DP_DisplayCtxType    *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadLinkRateOverride
//
//  @brief
//      This function will read registry key for maximum link rate override.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      uint32.
//-------------------------------------------------------------------------------------------------
//
uint32 DP_ReadLinkRateOverride(DP_DisplayCtxType    *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_Host_AuxRead
//
//  @brief
//      API to read AUX data from DPCD offset. This API breaks each read into 16 bytes segments.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [OUT] pMessage
//          Message that is read from sink which is allocated by caller.
//      [IN/OUT] pMessageSize
//          Message size. Size is updated if size is different from caller provided value.
//      [IN] uReadAddress
//          DPCD offset to read from.
//      [IN] eTranscationType
//          DP Transaction type native aux or I2C
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_AuxRead(DP_DisplayCtxType      *pDisplayCtx,
                          uint8                  *pMessage,
                          uint32                 *pMessageSize,
                          uint32                  uReadAddress,
                          DP_TransactionModeType  eTransactionType);

//-------------------------------------------------------------------------------------------------
//  DP_Host_AuxWrite
//
//  @brief
//      API to write data over AUX at specified DPCD address. Data should be written in 
//      16 byte segments
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN] eMessageType
//          Message type to be written to sink.
//      [OUT] pMessage
//          Message that is written to sink.
//      [IN] uMessageSize
//          Message size.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_AuxWrite(DP_DisplayCtxType      *pDisplayCtx,
                           uint8                  *pMessage,
                           uint32                  uMessageSize, 
                           uint32                  uWriteAddress);

//-------------------------------------------------------------------------------------------------
//  DP_CalculateRG
//
//  @brief
//      Use link rate, pclk, link count to calculate rate governor for MST.
//
//  @params
//      [IN] psDisplayInfo
//          Display config parameters.
//      [OUT] psRGConfig
//          Calculated RG parameters.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_CalculateRG(DP_RGCalcParamType *psDisplayInfo,
                         HAL_DP_RGConfigType *psRGConfig);

/**********************************************************************************************************************

FUNCTION: DP_ReadSinkStatus()

This function will read sink status register for sink count and CP readiness. 

Parameters:
   pDisplayCtx                       -[in ] Pointer to context

Return:
DP_Status

**********************************************************************************************************************/
DP_Status  DP_ReadSinkStatus(DP_DisplayCtxType      *pDisplayCtx);

/**********************************************************************************************************************

FUNCTION: DP_ReadSinkSymbolStatus()

This function will read sink registers for symbol error counts. 

Parameters:
   pDisplayCtx                      -[in ] Pointer to context
   pDisplayCtx                      -[out] Pointer to fetch symbol errors (optional)

Return:
DP_Status

**********************************************************************************************************************/
DP_Status  DP_ReadSinkSymbolStatus(DP_DisplayCtxType       *pDisplayCtx,
                                   DP_SinkSymbolStatusType *pSymbolStatusRawData);


/**********************************************************************************************************************

FUNCTION: DP_WriteSinkPSRConfiguration()

This function will enable/disable PSR and set PSR config. 

Parameters:
   pDeviceCtx                       -[in ] Pointer to device context
   pPSRCfg                          -[in ] Pointer to PSR config

Return:
DP_Status

**********************************************************************************************************************/
DP_Status  DP_WriteSinkPSRConfiguration(DP_DisplayCtxType *pDisplayCtx, 
                                        DP_PSRCfgType     *pPSRCfg);

//-------------------------------------------------------------------------------------------------
//  eDP_PSR_Request
//
//  @brief
//      Function to set PSR state of source and sink
//
//
//  @params
//      [IN/OUT] pDisplayCtx
//          Pointer to context handle.
//      [IN] ePSRRequest
//          Type of PSR Request
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
//
DP_Status eDP_PSR_Request(DP_DisplayCtxType  *pDisplayCtx,  
                          DP_PSRRequestType   ePSRRequest);

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkASSREnable
//
//  @brief
//      Function will enable/disable ASSR mode on the sink
//
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context handle.
//      [IN] bEnable
//          Enable/Disable ASSR
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkASSREnable(DP_DisplayCtxType *pDisplayCtx, bool32 bEnable);

//-------------------------------------------------------------------------------------------------
//  DP_SetControllerResources
//
//  @brief
//      set resources for chosen controller.
//
//  @params
//      [IN] eControllerID
//          DP_ControllerIDType
//      [IN] eDisplayID
//          QDI display ID.
//
//  @return
//      void 
//-------------------------------------------------------------------------------------------------
// 
void DP_SetControllerResources(DP_ControllerIDType eControllerID, MDP_Display_IDType eDisplayID);

//-------------------------------------------------------------------------------------------------
//  DP_EDIDRead
//
//  @brief
//      1. EDID read of 1 block, the block index needs to be specified.
//      2. The function is used for both SST and MST.
//      3. The size of the block is fixed at DP_EDID_BLOCK_SIZE.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN] uBlockIdx
//          Index of EDID block to be read.
//      [OUT] puReadDataBuffer
//          The output data buffer.
//      [IN] uReadDataBufferSize
//          The size of the output data buffer
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_EDIDRead(DP_DisplayCtxType* pDisplayCtx, uint8 uBlockIdx, uint8* puReadDataBuffer, uint32 uReadDataBufferSize);

/* ----------------------------------------------------------------------
*
** FUNCTION: DP_GetDisplayMap()
*/
/*!
* \DESCRIPTION
*     Retrieve display ID using device and stream ID
*
* \param [in]   eDeviceID        - Device ID
* \param [in]   eStreamID        - Stream ID

*
* \retval QDI Display ID
*
**********************************************************************************************/
MDP_Display_IDType DP_GetDisplayMap(DP_DeviceIDType eDeviceID, DP_MSTStreamIDType eStreamID);

//-------------------------------------------------------------------------------------------------
//  DPMST_TriggerMSTACT
//
//  @brief
//       Trigger MST ACT (Allocation Change Trigger) Sequence and wait until it is done.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context handle.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DPMST_TriggerMSTACT(DP_DisplayCtxType* pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_WriteGUID
//
//  @brief
//       Write to sink DPCD GUID .
//
//  @params
//      [IN] pDisplayCtx
//          DP Context handle.
//      [IN] pGUID
//          GUID string to be written.
//      [IN] uGUIDSize
//          size of GUID string.
//
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_WriteGUID(DP_DisplayCtxType* pDisplayCtx, uint8* pGUID, uint32 uGUIDSize);

//-------------------------------------------------------------------------------------------------
//  DP_ReadDeviceOUI
//
//  @brief
//       Read and log IEEE OUI, Device Identification String, and HW/FW version
//
//  @params
//      [IN] pDisplayCtx
//          DP Context handle.
//
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_ReadDeviceOUI(DP_DisplayCtxType* pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkBrightnessCap
//
//  @brief
//      This function will read Sink Brightness Capability over AUX Channel
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkBrightnessCap(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkBrightnessEnable
//
//  @brief
//      Function to enable/disable brightness
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context
//      [IN] bEnable
//          TRUE to enable backlight
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkBrightnessEnable(DP_DisplayCtxType *pDisplayCtx,
                                        bool32             bEnable);

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkBrightnessLevel
//
//  @brief
//      This function will write Sink Brightness level over AUX Channel
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context
//      [IN] fLevel
//          Backlight level to set in percentage
//      [IN] uMillinits
//          Backlight level to set in millinits 
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkBrightnessLevel(DP_DisplayCtxType *pDisplayCtx,
                                       float              fLevel,
                                       uint32             uMillinits);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkLTTPRCap
//
//  @brief
//      This function will read the repater LTTPR caps if present.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkLTTPRCap(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkLTTPRRepeaterOUI
//
//  @brief
//      Read and log LTTPR device-specific data of the repeater which consists of 
//      IEEE Organizational Unique ID (OUI) and Device Identification String
//
//
//  @params
//      [IN] pDisplayCtx
//          DP Context handle.
//      [IN] eRepeaterID
//          Index of the repeater
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_ReadSinkLTTPRRepeaterOUI(DP_DisplayCtxType       *pDisplayCtx,
                                      DP_LTTPR_RepeaterIDType  eRepeaterID);

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkLTTPRRepeaterMode
//
//  @brief
//      This function will update the repater LTTPR mode if present.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context
//      [IN] bTransparentMode
//          TRUE to enable transparent mode
//          FALSE to disable transparent mode
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkLTTPRRepeaterMode(DP_DisplayCtxType *pDisplayCtx, bool32 bTransparentMode);

//-------------------------------------------------------------------------------------------------
//  DP_WriteCustomLTTPRInitSequence
//
//  @brief
//      This function will run the LTTPR custom init sequence.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context
//      [IN] eCustomSinkType
//          Custom sink type
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteCustomLTTPRInitSequence(DP_DisplayCtxType *pDisplayCtx,
                                           DP_CustomSinkType  eCustomSinkType);


//-------------------------------------------------------------------------------------------------
//  DP_EnableCustomLTTPRIntercept
//
//  @brief
//      This function will enable the Custom LTTPR intercept.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context
//      [IN] bEnable 
//          Flag to enable/disable intercept.
//      [IN] eCustomSinkType
//          Custom sink type
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_EnableCustomLTTPRIntercept(DP_DisplayCtxType *pDisplayCtx,
                                         bool32             bEnable,
                                         DP_CustomSinkType  eCustomSinkType);


//-------------------------------------------------------------------------------------------------
//  DP_WriteCustomLTTPRDPCDLevels()
//
//  @brief
//      This function will select the training Voltage Swing Level and Pre-emphasis Level for custom LTTPR retimer.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context
//      [IN] uDesiredVoltageSwingLevel
//          The desired Voltage Swing level for link training
//      [IN] uDesiredPreEmphasisLevel
//          The desired pre-emphasis level for link training
//      [IN] eCustomSinkType
//          Custom sink type
//
//  @return: 
//     DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteCustomLTTPRDPCDLevels(DP_DisplayCtxType  *pDisplayCtx,
                                         uint32              uDesiredVoltageSwingLevel,
                                         uint32              uDesiredPreEmphasisLevel,
                                         DP_CustomSinkType   eCustomSinkType);

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  DP_ReadLTTPRCETrainingInterval
//
//  @brief
//      Read and log LTTPR device Chanel Equalization training interval data of the repeater
//
//  @params
//      [IN] pDisplayCtx
//          DP Context handle.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadLTTPRCETrainingInterval(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DP_GetRepeaterDPCDOffset
//
//  @brief
//      This function will calculate the remapped DPCD address of the matching LTTPR repeater
//      DPCD address for a particular repeater ID.  Only addresses 102h - 106h are remapped DPCD registers.
//
//  @params
//      [IN] eRepeaterID
//          Repeater ID
//      [IN] uDPCDOffset
//          The base DPCD address to be written to
//
//  @return
//      The equivelent offset of the Phy repeater DPCD address for a particular repeater
//-------------------------------------------------------------------------------------------------
//
uint32  DP_GetRepeaterDPCDOffset(DP_LTTPR_RepeaterIDType eRepeaterID, uint32 uDPCDOffset);

//-------------------------------------------------------------------------------------------------
// DP_WriteSinkMSTEnable
//
// @brief
//    Enable MST.
//
// @params
//    [IN] pDisplayCtx
//      DP Context handle.
//    [IN] bEnable
//      Enable/Disable MST.
//
// @return
//    DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_WriteSinkMSTEnable(DP_DisplayCtxType *pDisplayCtx, bool32 bEnable);

//-------------------------------------------------------------------------------------------------
//  DP_IdentifyCustomSink
//
//  @brief
//      Compare and identify the sink type
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to display context
//      [IN] eSinkClass
//          DP Sink type
//      [IN] uSinkNameLength
//          Sink name length
//
//  @return
//     Particular custom sink type.
//-------------------------------------------------------------------------------------------------

DP_CustomSinkType DP_IdentifyCustomSink(DP_DisplayCtxType *pDisplayCtx,
                                        DP_SinkClassType   eSinkClass,
                                        uint32             uSinkNameLength);

//-------------------------------------------------------------------------------------------------
//  DP_IsValidLTTPR
//
//  @brief
//      Determines if a repeater is present and valid.
//
//  @params
//      pDisplayCtx          -[in ] Pointer to dp display context
//
//  @return
//      TRUE if downstream repeaters are valid
//-------------------------------------------------------------------------------------------------
bool32  DP_IsValidLTTPR(DP_DisplayCtxType *pDisplayCtx);


#endif // _DP_I_H
