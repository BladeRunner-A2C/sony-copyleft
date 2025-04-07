#ifndef __MDPTYPES_H__
#define __MDPTYPES_H__
/*=============================================================================
 
  File: MDPTypes.h
 
  Header file for common driver types
  
 
  Copyright (c) 2011-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include "hal_mdss.h"

/*===========================================================================

                                 Defines 

===========================================================================*/
/* Number of I2C Slave addresses
*/
#define MDP_I2C_SLAVE_ID_NUM    2
/*===========================================================================

                                Helper Macros

===========================================================================*/

/*===========================================================================

                                Enumeration

===========================================================================*/

/* Supported MDP Pixel formats 
 */
typedef enum
{
  MDP_PIXEL_FORMAT_NONE = 0,
  MDP_PIXEL_FORMAT_RGB_565_16BPP,
  MDP_PIXEL_FORMAT_RGB_666_18BPP,
  MDP_PIXEL_FORMAT_RGB_888_24BPP,
  MDP_PIXEL_FORMAT_ARGB_1555_16BPP,
  MDP_PIXEL_FORMAT_XRGB_8888_32BPP,
  MDP_PIXEL_FORMAT_ARGB_8888_32BPP,
  MDP_PIXEL_FORMAT_BGR_565_16BPP,
  MDP_PIXEL_FORMAT_BGR_888_24BPP,
  MDP_PIXEL_FORMAT_ABGR_1555_16BPP,
  MDP_PIXEL_FORMAT_XBGR_8888_32BPP,
  MDP_PIXEL_FORMAT_ABGR_8888_32BPP,
  MDP_PIXEL_FORMAT_Y_CBCR_H2V2_12BPP,          /**< 4:2:0, Pseudo planar, Cb(U) in MSB, viewing in bytes in chroma plane, it is CrCbCrCbCrCb..., same as NV21*/
  MDP_PIXEL_FORMAT_Y_CRCB_H2V2_12BPP,          /**< 4:2:0, Pseudo planar, Cr(V) in MSB, viewing in bytes in chroma plane, it is CbCrCbCrCbCr..., same as NV12*/
  MDP_PIXEL_FORMAT_YCRYCB_H2V1_16BPP,          /**< 4:2:2, YCrYCb(YVYU) interleave */
  MDP_PIXEL_FORMAT_YCBYCR_H2V1_16BPP,          /**< 4:2:2, YCbYCr(YUYV) interleave */
  MDP_PIXEL_FORMAT_CRYCBY_H2V1_16BPP,          /**< 4:2:2, CrYCbY(VYUY) interleave */
  MDP_PIXEL_FORMAT_CBYCRY_H2V1_16BPP,          /**< 4:2:2, CbYCrY(UYVY) interleave */
  MDP_PIXEL_FORMAT_Y_CRCB_H2V1_16BPP,          /**< 4:2:2, Pseduo planar, Cr(U) in MSB */
  MDP_PIXEL_FORMAT_Y_CBCR_H2V1_16BPP,          /**< 4:2:2, Pseudo planar, Cb(V) in MSB */
  MDP_PIXEL_FORMAT_Y_CBCR_H2V2_VC1_12BPP,      /**< Identical packing to Y_CBCR_H2V2_12BPP */
  MDP_PIXEL_FORMAT_Y_CRCB_H2V2_VC1_12BPP,      /**< Identical packing to Y_CRCB_H2V2_12BPP */
  MDP_PIXEL_FORMAT_Y_CR_CB_H2V2_12BPP,         /**< 4:2:0, planar, Y,CR(V),Cb(U) in seperate plane */
  MDP_PIXEL_FORMAT_Y_CR_CB_H2V2_16BPP,         /**< 4:2:2, planar, Y,CR(V),Cb(U) in seperate plane */
  MDP_PIXEL_FORMAT_Y_CBCR_SUPERTILE_4x2_12BPP, /**< 4:2:0, Pseudo planar, Cr(V), Cb(U) are in 4x2 tile format*/
  MDP_PIXEL_FORMAT_RGBA_5551_16BPP,
  MDP_PIXEL_FORMAT_RGBA_8888_32BPP,
  MDP_PIXEL_FORMAT_RGB_101010_30BPP,
  MDP_PIXEL_FORMAT_XRGB_2101010_32BPP,         /**< 10 bit XRGB format */
  MDP_PIXEL_FORMAT_ARGB_2101010_32BPP,
  MDP_PIXEL_FORMAT_XBGR_2101010_32BPP,
  MDP_PIXEL_FORMAT_ABGR_2101010_32BPP,
  MDP_PIXEL_FORMAT_RGBX_1010102_32BPP,
  MDP_PIXEL_FORMAT_RGBA_1010102_32BPP,
  MDP_PIXEL_FORMAT_BGRX_1010102_32BPP,
  MDP_PIXEL_FORMAT_BGRA_1010102_32BPP,
  MDP_PIXEL_FORMAT_Y_CRCB_H2V2_P010_24BPP,     /**< 10 bit 4:2:0, Pseudo planar, CB(U) in MSB, viewing in bytes in chroma plane, it is CrCbCrCbCrCb... */
  MDP_PIXEL_FORMAT_Y_CBCR_H2V2_P010_24BPP,     /**< 10 bit 4:2:0, Pseudo planar, CR(V) in MSB, viewing in bytes in chroma plane, it is CbCrCbCrCbCr... */
  MDP_PIXEL_FORMAT_Y_CRCB_H2V2_TP10_16BPP,     /**< 10 bit tiled 4:2:0 format, CR(V) in MSB, viewing in bytes in chroma plane, it is CrCbCrCbCrCb...   */
  MDP_PIXEL_FORMAT_Y_CBCR_H2V2_TP10_16BPP,     /**< 10 bit tiled 4:2:0 format, CR(V) in MSB, viewing in bytes in chroma plane, it is CbCrCbCrCbCr...   */
  MDP_PIXEL_FORMAT_RGB_PLANAR_888_8BPP,        /**< 8bit RGB Planar format, viewing it as rrrrggggbbbb..*/
  MDP_PIXEL_FORMAT_MAX,
  MDP_PIXEL_FORMAT_FORCE_32BIT = 0x7FFFFFFF
} MDP_PixelFormatType;

typedef enum
{
  MDP_ROTATE_NONE,      /**< Do not rotate. */
  MDP_ROTATE_90,        /**< Rotate clockwise 90 degrees. */
  MDP_ROTATE_180,       /**< Rotate clockwise 180 degrees. */
  MDP_ROTATE_270,       /**< Rotate clockwise 270 degrees. */
  MDP_ROTATE_NONE_FLIP_HORZ, /**< Rotate 0 degrees, flip horizontally. */
  MDP_ROTATE_NONE_FLIP_VERT, /**< Rotate 0 degrees, flip vertically. */
  MDP_ROTATE_90_FLIP_HORZ,   /**< Rotate 90 degrees, flip horizontally. */
  MDP_ROTATE_90_FLIP_VERT,   /**< Rotate 90 degrees, flip vertically. */
  MDP_ROTATE_180_FLIP_HORZ,  /**< Rotate 180 degrees, flip horizontally. */
  MDP_ROTATE_180_FLIP_VERT,  /**< Rotate 180 degrees, flip vertically. */
  MDP_ROTATE_270_FLIP_HORZ,  /**< Rotate 270 degrees, flip horizontally. */
  MDP_ROTATE_270_FLIP_VERT,  /**< Rotate 270 degrees, flip vertically. */
  MDP_ROTATE_MAX,       /**< Maximum number of rotating modes. */
  MDP_ROTATE_FORCE_32BIT = 0x7FFFFFFF
} MDP_RotateFlipType;



/* MDP Status types
 */
typedef enum
{
  MDP_STATUS_OK            = 0,        /* Command successful */
  MDP_STATUS_SUCCESS       = MDP_STATUS_OK,
  MDP_STATUS_BAD_HANDLE,               /* Bad Destination Handle */
  MDP_STATUS_BAD_PARAM,                /* Bad Parameter */
  MDP_STATUS_NOT_SUPPORTED,            /* Operation not supported */
  MDP_STATUS_NO_RESOURCES,             /* Out of resources */
  MDP_STATUS_FAILED,                   /* Command Failed */
  MDP_STATUS_TIMEOUT,                  /* Command not completed within expected time */
  MDP_STATUS_HW_ERROR,                 /* Hardware isn't responding as expected */
  MDP_STATUS_INVALID_STATE,            /* Not in correct state to perform task */
  MDP_STATUS_BUFFER_TOO_SMALL,         /* A function needs a larger buffer for the amount of data*/  
  MDP_STATUS_MAX,
  MDP_STATUS_FORCE_32BIT = 0x7FFFFFFF
} MDP_Status;


/* MDP Display interface
 */
typedef enum
{
  MDP_DISPLAY_PRIMARY,                 /* Primary display */
  MDP_DISPLAY_SECONDARY,               /* Secondary display */
  MDP_DISPLAY_EXTERNAL,                /* 1st External display */
  MDP_DISPLAY_EXTERNAL2,               /* 2nd External display */
  MDP_DISPLAY_EXTERNAL3,               /* 3rd External display */
  MDP_DISPLAY_EXTERNAL4,               /* 4th External display */
  MDP_DISPLAY_EXTERNAL5,               /* 5th External display */
  MDP_DISPLAY_EXTERNAL6,               /* 6th External display */
  MDP_DISPLAY_MAX,
  MDP_DISPLAY_FORCE_32BIT = 0x7FFFFFFF
} MDP_Display_IDType;

/*!
 * \enum MDP_DP_LinkTrainingType
 *
 * The \b MDP_DP_LinkTrainingType defines the types of Link Training.
 *
 */
typedef enum
{
   MDP_DP_LINK_TRAINING_TYPE_NO_TRAINING          = 0x00000000,        /**< No Link Training                        */
   MDP_DP_LINK_TRAINING_TYPE_FULL_TRAINING,                            /**< Full Link Training                      */
   MDP_DP_LINK_TRAINING_TYPE_FAST_TRAINING,                            /**< Fast Link Training                      */
   MDP_DP_LINK_TRAINING_TYPE_MAX,
   MDP_DP_LINK_TRAINING_TYPE_FORCE_32BIT          = 0x7FFFFFFF
}MDP_DP_LinkTrainingType;

/*!
 * \enum MDP_Lock_Type
 *
 * Software locks to prevent re-entrancy of various code sections.
 *
 */
typedef enum {
  MDP_LOCK_TYPE_DISPLAY_PWR_CTRL = 0,         /**< Display power control lock */
  MDP_LOCK_TYPE_MAX,
  MDP_LOCK_TYPE_FORCE_32BIT      = 0x7FFFFFFF
} MDP_Lock_Type;

/** Defines the OEM backlight configuration options.
*/
typedef enum
{
    MDP_PANEL_BACKLIGHTTYPE_NONE = 0,     /**< No backlight adjustment is available. */
    MDP_PANEL_BACKLIGHTTYPE_PMIC,         /**< Backlight is controlled through PMIC PWM or WLED.  For OLED, PMIC uses SWIRE to control brightness */
    MDP_PANEL_BACKLIGHTTYPE_I2C,          /**< Backlight is controlled through I2C. */
    MDP_PANEL_BACKLIGHTTYPE_DSI,          /**< Backlight is controlled through the DSI command. */
    MDP_PANEL_BACKLIGHTTYPE_ACPI,         /**< Backlight is controlled through the ACPI method. */
    MDP_PANEL_BACKLIGHTTYPE_AUX,          /**< Backlight is controlled through DP using AUX commands. */
    MDP_PANEL_BACKLIGHTTYPE_AUX_CUSTOM1,  /**< Backlight is controlled through DP using AUX commands. (OLED at DPCD 320h) */
    MDP_PANEL_BACKLIGHTTYPE_AUX_CUSTOM2,  /**< Backlight is controlled through DP using AUX commands. (OLED at DPCD 354h) */
    MDP_PANEL_BACKLIGHTTYPE_MAX,          /**< Enumeration marker for the max. */
    MDP_PANEL_BACKLIGHTTYPE_FORCE_32BIT = 0x7FFFFFFF /**< Forces the enumeration to 32 bits. */
} MDP_Panel_BacklightType;


/** PMIC module for secondary power sources
*/
typedef enum
{
    MDP_PMIC_MODULE_CONTROLTYPE_NONE = 0,
    /**< No secondary power control method */

    MDP_PMIC_MODULE_CONTROLTYPE_IBB_LAB_LCD,
    /**< Secondary power through IBB/LAB LCD mode. */

    MDP_PMIC_MODULE_CONTROLTYPE_IBB_LAB_OLED,
    /**< OLED power supply using IBB/LAB OLED mode */

    MDP_PMIC_MODULE_CONTROLTYPE_PM_LCD_WLED,
    /**< Secondary power through PMIC dedicated LCD/WLED module. */

    MDP_PMIC_MODULE_CONTROLTYPE_PM_AMOLED,
    /**< OLED power supply using PMIC dedicated AMOLED modulee */

    MDP_PMIC_MODULE_CONTROLTYPE_MAX,
    /**< Enumeration marker for the max. */

    MDP_PMIC_MODULE_CONTROLTYPE_FORCE_32BIT = 0X7FFFFFFF
    /**< Forces the enumeration to 32 bits. */

} MDP_PmicModuleControlType;


/** PMIC control method for backlight control.
*/
typedef enum
{
    MDP_PMIC_BACKLIGHT_CONTROLTYPE_NONE = 0,
    /**< No backlight control method. */

    MDP_PMIC_BACKLIGHT_CONTROLTYPE_LPG,
    /**< Backlight controlled through LPG module. */

    MDP_PMIC_BACKLIGHT_CONTROLTYPE_WLED,
    /**< Backlight controlled through WLED module. */

    MDP_PMIC_BACKLIGHT_CONTROLTYPE_PWM,
    /**< Backlight controlled through PWM module. */

    MDP_PMIC_BACKLIGHT_CONTROLTYPE_MAX,
    /**< Enumeration marker for the max. */

    MDP_PMIC_BACKLIGHT_CONTROLTYPE_FORCE_32BIT = 0X7FFFFFFF
    /**< Forces the enumeration to 32 bits. */

} MDP_PmicBacklightControlType;



/* MDP_RESET_STATE_TYPE
 * reset gpio pin polarity and state
 */
typedef enum
{
  MDP_RESET_STATE_INVALID,
  MDP_RESET_STATE_LEVEL_LOW,
  MDP_RESET_STATE_LEVEL_HIGH,
  MDP_RESET_STATE_EDGE_LOW2HIGH,
  MDP_RESET_STATE_EDGE_HIGH2LOW,
  MDP_RESET_STATE_MAX,
} MDP_RESET_STATE_TYPE;


/*!
* \b MDP_HDMI_AudioFormatType
*
*  Defines the audio formats supported by the HDMI display
*/
typedef enum
{
  MDP_HDMI_AUDIO_FORMAT_RESERVED = 0,                  /* Reserved for future */
  MDP_HDMI_AUDIO_FORMAT_LPCM,                          /* Audio codec type Linear PCM */
  MDP_HDMI_AUDIO_FORMAT_AC3,                           /* Audio codec type AC3 */
  MDP_HDMI_AUDIO_FORMAT_MPEG1_LAYER1_AND_2,            /* Audio codec type MPEG1 Layer1 and 2 */
  MDP_HDMI_AUDIO_FORMAT_MP3,                           /* Audio codec type MP3*/
  MDP_HDMI_AUDIO_FORMAT_MPEG2,                         /* Audio codec type MPEG2 */
  MDP_HDMI_AUDIO_FORMAT_AAC,                           /* Audio codec type AAC */
  MDP_HDMI_AUDIO_FORMAT_DTS,                           /* Audio codec type DTS */
  MDP_HDMI_AUDIO_FORMAT_ATRAC,                         /* Audio codec type ATRAC */
  MDP_HDMI_AUDIO_FORMAT_ONE_BIT_AUDIO,                 /* Audio codec type 1 bit audio */
  MDP_HDMI_AUDIO_FORMAT_DOLBY_DIGITAL_PLUS,            /* Audio codec type Dolby Digital+ */
  MDP_HDMI_AUDIO_FORMAT_DTS_HD,                        /* Audio codec type DTS HD*/
  MDP_HDMI_AUDIO_FORMAT_MAT,                           /* Audio codec type MAT */
  MDP_HDMI_AUDIO_FORMAT_DST,                           /* Audio codec type DST */
  MDP_HDMI_AUDIO_FORMAT_WMA_PRO,                       /* Audio codec type WMA PRO */
  MDP_HDMI_AUDIO_FORMAT_RESERVED1,                     /* Reserved for future */
  MDP_HDMI_AUDIO_FORMAT_MAX,
  MDP_HDMI_AUDIO_FORMAT_FORCE_32BIT = 0x7FFFFFFF
} MDP_HDMI_AudioFormatType;

/*!
* \b MDP_DP_ConnectionModeType
*
*  DP display connection mode
*/
typedef enum {
  MDP_DP_CONNECTION_MODE_NATIVE = 0x00000000,    /**< Native DP */
  MDP_DP_CONNECTION_MODE_ALT_MODE,               /**< DP Alt Mode */
  MDP_DP_CONNECTION_MODE_TUNNELING,              /**< DP Tunneling Mode */
  MDP_DP_CONNECTION_MODE_MAX
} MDP_DP_ConnectionModeType;

/*!
* \b MDP_DP_AltModeConnectionPolarityType
*
*  DP Alt Mode cable connection status
*/
typedef enum
{
  MDP_DP_ALTMODE_CONNECTION_POLARITY_DISCONNECTED = 0x00000000,      /**< Disconnected. */
  MDP_DP_ALTMODE_CONNECTION_POLARITY_DEFAULT,                        /**< Connected in normal polarity. */
  MDP_DP_ALTMODE_CONNECTION_POLARITY_REVERSE,                        /**< Connected in reverted polarity. */
  MDP_DP_ALTMODE_CONNECTION_POLARITY_MAX,
} MDP_DP_AltModeConnectionPolarityType;

/*!
* \b MDP_DP_AltModeConnectionPinAssignmentType
*
*  DP Alt Mode cable connection pin assignment
*/
typedef enum
{
  MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_INVALID = 0x00000000,  /**< Not connected */
  MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_DFPD_A,                /**< Downstream Facing Port DP Pin A */
  MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_DFPD_B,                /**< Downstream Facing Port DP Pin B */
  MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_DFPD_C,                /**< Downstream Facing Port DP Pin C */
  MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_DFPD_D,                /**< Downstream Facing Port DP Pin D */
  MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_DFPD_E,                /**< Downstream Facing Port DP Pin E */
  MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_DFPD_F,                /**< Downstream Facing Port DP Pin F */
  MDP_DP_ALTMODE_CONNECTION_PINASSIGNMENT_MAX,
} MDP_DP_AltModeConnectionPinAssignmentType;

/*!
* \b MDP_DP_TunneledEventType
*
*  DP Tunneled event types
*/
typedef enum {
  MDP_DP_TUNNELED_EVENT_NONE = 0,
  MDP_DP_TUNNELED_EVENT_HPD_IN,    /**< DP Tunneled Hot Plug Event */
  MDP_DP_TUNNELED_EVENT_MAX,
} MDP_DP_TunneledEventType;

/*!
* \b MDP_DP_ControllerModeType
*
*  DP Controller Mode Type
*/
typedef enum {
  MDP_DP_CONTROLLER_MODE_DEFAULT    = 0,  /* DP over USB-C Mode */
  MDP_DP_CONTROLLER_MODE_DP         = 1,  /* DP Mode     */
  MDP_DP_CONTROLLER_MODE_MAX,
} MDP_DP_ControllerModeType;

/*===========================================================================

                        Structures 

===========================================================================*/


/* MDP Buffer Pool descriptor
 */
typedef struct {
  uint8 *pBuffer;                 /**< Pointer to buffer data */
  uint32 uBufferSize;             /**< Length of buffer in bytes */
}MDP_BufferType;

/* MDP point descriptor
 */
typedef struct {
    uint32 uX;
    uint32 uY;
} MDPPointType;


/* Rectangle descriptor
 */
typedef struct {
    uint32 uX;
    uint32 uY;
    uint32 uWidth;
    uint32 uHeight;
} MDPRectType;

/* MDPResolution Parameters
 */
typedef struct
{
  uint32   uWidth;                                 /* Width in px */
  uint32   uHeight;                                /* Height in lines */
} MDP_ResolutionType;

/*!
 * \b MDP_AddressType
 * 
 * Data structure holds the 64-bit address information
 */
typedef union 
{
  struct 
  {
      uint32 uLowPart;
      int32  iHighPart;
  } u;
  int64  iQuadPart;
} MDP_AddressType;


/* Frame buffer surface structure
 */
typedef struct {
    MDP_PixelFormatType  ePixelFormat;      /* Pixel format */
    uint32               uWidth;            /* Surface width */
    uint32               uHeight;           /* Surface height */
    uint32               uBytesPerPixel;    /* pixel format bytes per pixel */
    uint32               uNumPlanes;        /* Num of planes for a format */
    void                *pPlane0Offset;     /* Plane 0 offset */
    uint32               uPlane0Stride;     /* Plane 0 stride */
    void                *pPlane1Offset;     /* Plane 1 offset */
    uint32               uPlane1Stride;     /* Plane 1 stride */
    void                *pPlane2Offset;     /* Plane 2 offset */  
    uint32               uPlane2Stride;     /* Plane 2 stride */
} MDPSurfaceInfo;


/*  MDP_I2C_Configuration
*   
*   Hold information for I2C configuration
*/
typedef struct
{
    uint32         aI2CSlaveAddressList[MDP_I2C_SLAVE_ID_NUM];     /**< I2C Slave address                           */
    uint32         uI2CNumOfSlaves;                                /**< Number of Slave address                     */
    uint32         uI2CBusFrequency;                               /**< I2C Frequency                               */
    uint32         uI2CGSBICore;                                   /**< I2C QUP instance (must be between 1 to 12)  */
                                                                   /**< QUP can be found at go/IPCAT->GPIO MAPPING  */ 
    uint32         uI2COffsetLengthInByte;                         /**< I2C register address offset length in byte  */
    MDP_BufferType sI2CInitSequence;                               /**< I2C initialization sequence buffer          */
    MDP_BufferType sI2CTermSequence;                               /**< I2C termination sequence buffer             */
} MDP_I2C_Configuration;

/** Defines a generic allocated buffer for a panel.
*/
typedef struct
{
  uint32   uSize;
  /**< Length of buffer in bytes */
  uint8   *pBuffer;
  /**< Pointer to buffer data */
} MDP_Panel_AllocatedBufType;

/* MDP_DP_BondedModeInfoType
 *
 * Defines the DP bonded mode configuration
 */
typedef struct
{
  bool32  bEnabled;                 /**< DP bonded mode enable */
  uint32  uDeviceIDMapping[4];      /**< Mapping of DP Devices operating in bonded mode */
  uint32  uNumDevices;              /**< Number of DP Devices operating in bonded mode */
  uint32  uMasterClockDeviceID;     /**< Define the DP Device sourcing the resource for the shared master clock in bonded mode */
  bool32  bExternalMasterDevice;    /**< Master DP Device is not one of the DP devices responsible for physically driving a link in bonded mode */
  uint32  uMasterAUXDeviceID;       /**< Define the DP Device sourcing the resource for the shared master AUX in bonded mode */
} MDP_DP_BondedModeInfoType;

/** DP AUX Override mode.
*/
typedef enum {
  MDP_DP_OVERRIDE_MODE_OFF = 0,  /**< Do not override any DP sections. */
  MDP_DP_OVERRIDE_MODE_REPLACE,  /**< Override using provided buffers whether or not panel failed. */
  MDP_DP_OVERRIDE_MODE_FALLBACK, /**< Override using provided buffers when panel fails. */
  MDP_DP_OVERRIDE_MODE_MAX,
  MDP_DP_OVERRIDE_MODE_FORCE_32BIT = 0x7FFFFFFF
} MDP_DP_OverrideModeType;

/** Defines the buffers for AUX override from ACPI.
*/
typedef struct
{
  MDP_Panel_AllocatedBufType sEDID;       /**< EDID buffer from ACPI */
  MDP_Panel_AllocatedBufType sDPCDCaps;   /**< DPCD caps buffer from ACPI */
  MDP_Panel_AllocatedBufType sDPCDStatus; /**< DPCD status buffer from ACPI */
} MDP_DP_OverrideBufsType;

/** DP PHY SSC mode configuration.
    This enum configures the SSC for the DP panels
*/
typedef enum
{
  MDP_DP_SSC_DISABLED = 0x00000000,  /**< SSC disabled */
  MDP_DP_SSC_ENABLED_DOWNSPREAD,     /**< SSC enabled with downspread */
  MDP_DP_SSC_ENABLED_CENTERSPREAD,   /**< SSC enabled with centerspread */
  MDP_DP_SSC_MAX                     /**< Enumeration marker for the max. @newpage */
} MDP_DP_PHY_SSCConfigType;

/*!
* \b MDP_Display_HDMI_AudioModeInfoPropType
*
*  Defines the audio capabilities supported by the HDMI display
*/
typedef struct
{
  uint32                                  uAudioModeIndex;                                      /* Index to query the various audio capabilities associated with a particular audio format */
  MDP_HDMI_AudioFormatType                eAudioFormat;                                         /* Type of audio format this mode is associated with */
  uint16                                  uSupportedAudioSampleRateMask;                        /* Various sample rates supported with this audio format type (Use QDI_HDMI_AudioSampleRateType) */
  uint16                                  uSupportedAudioChannelMask;                           /* Various audio channels supported with this audio format type (Use QDI_HDMI_AudioChannelNumType) */
  uint32                                  uSupportedSpeakerLocationMask;                        /* Various speaker locations supported by this sink device (Use QDI_HDMI_AudioSpeakerLocationType) */
  union 
  {
    uint32                                uSupportedAudioSampleBitDepthMask;                    /* For LPCM audio format, this field indicates the various sample bit depths supported (Use QDI_HDMI_AudioSampleBitDepthType) */ 
    uint32                                uAudioMaxBitRate;                                     /* For non LPCM audio formats, this field indicates maximum bit rate supported */
  }audioStreamInfo;
  uint32                                  uReserved[4];                                         /* Reserved for future */
} MDP_Display_HDMI_AudioModeInfoPropType;

/*!
* \b MDP_DP_AltModeInfoType
*
*  Defines the DP Alt Mode hot plug related info
*/
typedef struct {
  MDP_DP_AltModeConnectionPolarityType        eConnectionPolarity;      /* DP Alt Mode plug polarity */
  MDP_DP_AltModeConnectionPinAssignmentType   eConnectionPinAssignment; /* DP Alt Mode pin assignment */
  bool32                                      bConcurrencyMode;         /* DP Alt Mode & USB SS concurrency */
} MDP_DP_AltModeInfoType;

/*!
* \b MDP_HotPlugEventDataType
*
*  External display hot plug event data
*/
typedef union {
  MDP_DP_AltModeInfoType sDPAltModeHPDInfo;    /* DP Alt Mode hot plug related info */
} MDP_HotPlugEventDataType;

#endif // __MDPLIB_H__

