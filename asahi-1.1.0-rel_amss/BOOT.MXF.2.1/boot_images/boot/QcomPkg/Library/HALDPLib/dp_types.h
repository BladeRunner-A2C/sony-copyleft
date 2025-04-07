#ifndef _DP_TYPES_H_
#define _DP_TYPES_H_
/*! \file */
/*=====================================================================================================
 
  File: dp_types.h
 
  Header file for data types used by DP driver 
   
  Copyright (c) 2016-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
====================================================================================================*/
#include "MDPTypes.h"
#include "hal_dp.h"

/* --------------------------------------------------------------------------------------------------------------------
** Macros and Struct
---------------------------------------------------------------------------------------------------------------------*/
/* Define bit shift */
#define  DP_BIT(x)                                      ((uint32)(1<<(x)))

#define  MAX_DP_PANEL_MODE                              32                      /**< Max display mode of DP panel, must match EDID_DISP_MODE_LIST_MAX_NUM */
#define  MAX_DP_AUDIO_MODE                              32                      /**< Max audio mode of DP panel                                           */

#define  DP_IEEE_OUI_LEN                                3                       /**< Max length of IEEE OUI string                                        */
#define  DP_DEVICE_ID_STRING_LEN                        6+1                     /**< Max length of the device identification ASCII string + NULL char      */

#define  DP_SDP_HEADER_BYTES                            4

#define  PANEL_CONTROL_MAX_SINK_SIZE                    4                       /**< Maximum number of sinks that can be supported in PanelSinkStatusType  */

/* --------------------------------------------------------------------------------------------------------------------
Enumerated types
---------------------------------------------------------------------------------------------------------------------*/

/*!
 * \enum DP_TransactionModeType
 *
 * The \b DP_TransactionModeType defines types of AUX Transaction. It either is AUX for DPCD read/write or I2C over 
 * AUX for EDID read.
 *
 */
typedef enum
{
  DP_TRANSACTION_MODE_NONE                       = 0x00000000,
  DP_TRANSACTION_MODE_AUX,                                             /**< This is a native AUX Transaction                           */
  DP_TRANSACTION_MODE_I2C,                                             /**< This is an I2C over AUX Transaction                        */
  DP_TRANSACTION_MODE_SET_CONFIG,                                      /**< This is a SET_CONFIG non IRQ over Tunneled AUX Transaction */
  DP_TRANSACTION_MODE_MAX,
  DP_TRANSACTION_MODE_FORCE_32BIT                = 0x7FFFFFFF
} DP_TransactionModeType;

/*!
 * \enum DP_TransactionFlags
 *
 * The \b DP_TransactionFlags defines various flags used in DP AUX transactions. 
 * These flags are set and propagated through DP_WritePacketType.uFlags and DP_ReadPacketType.uFlags
 *
 */
typedef enum
{
  DP_AUX_TRANSACTION_FLAG_NONE              = 0x00000000,
  DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG    = DP_BIT(0),               /**< Use Stall() instead of Sleep() while polling                      */
  DP_AUX_TRANSACTION_I2C_SET_MOT_FLAG       = DP_BIT(1),               /**< Set Middle Of Transaction (MOT) bit for I2C over AUX transactions */
  DP_AUX_TRANSACTION_FLAG_MAX,
  DP_AUX_TRANSACTION_FLAG_FORCE_32BIT       = 0x7FFFFFFF
} DP_AUX_TransactionFlags;

/*!
 * \enum DP_ClockSourceType
 *
 * The \b DP_ClockSourceType defines possible clock source for DP link clock and pixel clock.
 */
typedef enum
{
  DP_CLOCKSOURCE_NONE                            = 0,
  DP_CLOCKSOURCE_DPPLL,                                                /**< Clock is from DP PLL                    */
  DP_CLOCKSOURCE_DSI1PLL,                                              /**< Clock is from DSI1 PLL                  */
  DP_CLOCKSOURCE_DSI2PLL,                                              /**< Clock is from DSI1 PLL                  */
  DP_CLOCKSOURCE_HDMIPLL,                                              /**< Clock is from HDMI PLL                  */
  DP_CLOCKSOURCE_MAX,
  DP_CLOCKSOURCE_FORCE_32BIT                     = 0x7FFFFFFF
} DP_ClockSourceType;

/* 
 * \enum DP_BrightnessRequestType
 *
 * Brightness Request Types definitions
 */
typedef enum {
    DP_BRIGHTNESS_REQUEST_OFF = 0,  // Voltage disabled
    DP_BRIGHTNESS_REQUEST_ON,       // Voltage Enabled (assumed default level)
    DP_BRIGHTNESS_REQUEST_LEVEL,    // Specific voltage level requested
    DP_BRIGHTNESS_REQUEST_MAX,
    DP_BRIGHTNESS_REQUEST_FORCE_32BIT = 0x7FFFFFFF
} DP_BrightnessRequestType;


/*!
 * \enum DP_SetPropertyType
 *
 * The \b DP_SetPropertyType defines property type for host driver to set.
 */
typedef enum
{
  DP_SETPROPERTY_NONE                            = 0,
  DP_SETPROPERTY_PANEL_MODE_INDEX,                                     /**< Set index of panel modes                */
  DP_SETPROPERTY_PANEL_INFO,                                           /**< Overwrite current mode of panel info    */
  DP_SETPROPERTY_LINK_RATE,                                            /**< Overwrite Link Rate(270000 or 162000)Khz*/
  DP_SETPROPERTY_LANE_NUMBER,                                          /**< Overwrite desired lane number           */
  DP_SETPROPERTY_ASSR_ENABLE,                                          /**< Overwrite the setting of ASSR           */
  DP_SETPROPERTY_ENHANCEDFRAME_ENABLE,                                 /**< Overwrite the setting of enhanced Frame */
  DP_SETPROPERTY_LINK_TRAINING_TYPE,                                   /**< Set the sink link training type         */
  DP_SETPROPERTY_CLOCKS,                                               /**< Set clocks dynamically                  */
  DP_SETPROPERTY_RESETCORE,                                            /**< Reset all eDP blocks, core, aux, PHY    */
  DP_SETPROPERTY_CONNECTION_STATUS,                                    /**< Set connection status                   */
  DP_SETPROPERTY_INTERRUPT_ENABLE,                                     /**< Enable interrupts                       */
  DP_SETPROPERTY_INTERRUPT_DISABLE,                                    /**< Disable interrupts                      */
  DP_SETPROPERTY_INTERRUPT_CLEAR,                                      /**< Clear interrupts                        */
  DP_SETPROPERTY_AUDIO_CONFIG,                                         /**< Set audio parameters                    */
  DP_SETPROPERTY_AUDIO_ENABLE,                                         /**< Enable/Disable DP audio engine          */
  DP_SETPROPERTY_LINK_CLOCK,                                           /**< Set DP link clock property              */
  DP_SETPROPERTY_SIGNAL_EVENT,                                         /**< Signal a DP event                       */
  DP_SETPROPERTY_UPDATE_SINK_STATUS,                                   /**< Update DP sink status                   */
  DP_SETPROPERTY_PSR_CONFIG,                                           /**< Set eDP Panel self refresh config       */
  DP_SETPROPERTY_UPDATE_PPS,                                           /**< Update and flush PPS info to Panel      */
  DP_SETPROPERTY_REFRESHRATE,                                          /**< Update Refresh rate dynamically         */
  DP_SETPROPERTY_PRE_EMPHASIS_LEVEL,                                   /**< Overwrite pre-emphasis Level            */
  DP_SETPROPERTY_VOLTAGE_SWING_LEVEL,                                  /**< Overwrite voltage swing Level           */
  DP_SETPROPERTY_TEST_PATTERN,                                         /**< Set test pattern request                */
  DP_SETPROPERTY_WRITE,                                                /**< Write at given address                  */
  DP_SETPROPERTY_MAIN_LINK_STATE,                                      /**< Configures main link                    */
  DP_SETPROPERTY_PHY_POWER,                                            /**< Turn on/off PHY and PLL                 */
  DP_SETPROPERTY_GENERIC_SDP_CONFIG,                                   /**< Configure Generic SDP                   */
  DP_SETPROPERTY_GENERIC_SDP_ENABLE,                                   /**< Configure Generic SDP enable status     */
  DP_SETPROPERTY_SIMULATION_MODE,                                      /**< Turn on/off DP Simulation               */
  DP_SETPROPERTY_BRIGHTNESS_CONTROL,                                   /**< Enable/Disable and set brightness level */
  DP_SETPROPERTY_RESET_PHY,                                            /**< Reset DP PHY                            */
  DP_SETPROPERTY_COLOR_SPACE,                                          /**< Configure color space                   */
  DP_SETPROPERTY_MAX,
  DP_SETPROPERTY_FORCE_32BIT                     = 0x7FFFFFFF
} DP_SetPropertyType;

/*!
 * \enum DP_GetPropertyType
 *
 * The \b DP_GetPropertyType defines property type for host driver to query.
 */
typedef enum
{
  DP_GETPROPERTY_NONE                            = 0,
  DP_GETPROPERTY_GET_MODE_INFO,                                        /**< Get Panel modes                                           */
  DP_GETPROPERTY_AUXSTATUS,                                            /**< Get DP AUX status                                         */
  DP_GETPROPERTY_LANE_NUMBER,                                          /**< Get DP panel lane number                                  */
  DP_GETPROPERTY_LINK_RATE,                                            /**< Get DP panel link rate                                    */
  DP_GETPROPERTY_CONNECTION_STATUS,                                    /**< Get a flag if DP panel support ASSR                       */
  DP_GETPROPERTY_ENHANCEDFRAME_ENABLE,                                 /**< Get flag if panel support ENHANCEDFRAME                   */
  DP_GETPROPERTY_EDID_INFO,                                            /**< Get EDID info                                             */
  DP_GETPROPERTY_INTERRUPT_STATUS,                                     /**< Get interrupt status                                      */
  DP_GETPROPERTY_AUDIO_MODE_INFO,                                      /**< Extracts the audio capabilities(eg: samplerate, channel#) */
  DP_GETPROPERTY_VENDOR_SPECIFIC_INFO,                                 /**< Get DP Vendor specific info                               */
  DP_GETPROPERTY_ROUTING_INFO,                                         /**< Get routing info                                          */
  DP_GETPROPERTY_SINK_STATUS,                                          /**< Get DP sink status                                        */
  DP_GETPROPERTY_DSC_INFO,                                             /**< Get DP Panel DSC info                                     */
  DP_GETPROPERTY_STREAM_INFO,                                          /**< Get Stream info                                           */
  DP_GETPROPERTY_REFRESHRATE,                                          /**< Get Refresh rate info                                     */
  DP_GETPROPERTY_DISPLAY_RANGE_INFO,                                   /**< Get Display Range info read from EDID                     */
  DP_GETPROPERTY_READ,                                                 /**< Read from the address                                     */
  DP_GETPROPERTY_TOPOPLOGY_CHANGED,                                    /**< Get topology change status                                */
  DP_GETPROPERTY_PSR_CONFIG,                                           /**< Get current PSR configuration                             */
  DP_GETPROPERTY_PRE_EMPHASIS_LEVEL,                                   /**< Get current pre-emphasis level                            */
  DP_GETPROPERTY_VOLTAGE_SWING_LEVEL,                                  /**< Get current voltage swing level                           */
  DP_GETPROPERTY_DPCD_CAPS_INFO,                                       /**< Get DPCD caps                                             */  
  DP_GETPROPERTY_AUX_FAILSAFE_MODE,                                    /**< Get if panel is in AUX failsafe mode                      */  
  DP_GETPROPERTY_DEVICE_SPECIFIC_INFO,                                 /**< Get Sink IEEE OUI, Device String Id and HW/FW Revisions   */
  DP_GETPROPERTY_FRAME_CRC,                                            /**< Get frame CRC                                             */  
  DP_GETPROPERTY_MAX,
  DP_GETPROPERTY_FORCE_32BIT                     = 0x7FFFFFFF
} DP_GetPropertyType;


/*!
 * \enum DP_LaneMapType
 *
 * The \b DP_LaneMapType defines physical lane and logic lane mapping.   
 *
 */
typedef enum
{
   DP_LANEMAP_TYPE_NONE                           = 0x00000000,
   DP_LANEMAP_TYPE_0123,                                               /**< Physical lane map to logic lane as 0123 */
   DP_LANEMAP_TYPE_0132,                                               /**< Physical lane map to logic lane as 0132 */
   DP_LANEMAP_TYPE_0213,                                               /**< Physical lane map to logic lane as 0213 */
   DP_LANEMAP_TYPE_0231,                                               /**< Physical lane map to logic lane as 0231 */
   DP_LANEMAP_TYPE_0312,                                               /**< Physical lane map to logic lane as 0312 */
   DP_LANEMAP_TYPE_0321,                                               /**< Physical lane map to logic lane as 0321 */
   DP_LANEMAP_TYPE_1023,                                               /**< Physical lane map to logic lane as 1023 */
   DP_LANEMAP_TYPE_1032,                                               /**< Physical lane map to logic lane as 1032 */
   DP_LANEMAP_TYPE_1203,                                               /**< Physical lane map to logic lane as 1203 */
   DP_LANEMAP_TYPE_1230,                                               /**< Physical lane map to logic lane as 1230 */
   DP_LANEMAP_TYPE_1302,                                               /**< Physical lane map to logic lane as 1302 */
   DP_LANEMAP_TYPE_1320,                                               /**< Physical lane map to logic lane as 1320 */
   DP_LANEMAP_TYPE_2013,                                               /**< Physical lane map to logic lane as 2013 */
   DP_LANEMAP_TYPE_2031,                                               /**< Physical lane map to logic lane as 2031 */
   DP_LANEMAP_TYPE_2103,                                               /**< Physical lane map to logic lane as 2103 */
   DP_LANEMAP_TYPE_2130,                                               /**< Physical lane map to logic lane as 2130 */
   DP_LANEMAP_TYPE_2301,                                               /**< Physical lane map to logic lane as 2301 */
   DP_LANEMAP_TYPE_2310,                                               /**< Physical lane map to logic lane as 2310 */
   DP_LANEMAP_TYPE_3012,                                               /**< Physical lane map to logic lane as 3012 */
   DP_LANEMAP_TYPE_3021,                                               /**< Physical lane map to logic lane as 3021 */
   DP_LANEMAP_TYPE_3102,                                               /**< Physical lane map to logic lane as 3102 */
   DP_LANEMAP_TYPE_3120,                                               /**< Physical lane map to logic lane as 3120 */
   DP_LANEMAP_TYPE_3201,                                               /**< Physical lane map to logic lane as 3201 */
   DP_LANEMAP_TYPE_3210,                                               /**< Physical lane map to logic lane as 3210 */
   DP_LANEMAP_TYPE_MAX,
   DP_LANEMAP_TYPE_FORCE_32BIT                    = 0x7FFFFFFF
} DP_LaneMapType;

/*!
 * \enum DP_RGBMapType
 *
 * The \b DP_RGBMapType defines RGB component mapping.   
 *
 */
typedef enum
{
   DP_RGBMAP_TYPE_NONE                            = 0x00000000,
   DP_RGBMAP_TYPE_RGB,                                                 /**< Color component order is RGB            */
   DP_RGBMAP_TYPE_RBG,                                                 /**< Color component order is RBG            */
   DP_RGBMAP_TYPE_GBR,                                                 /**< Color component order is GBR            */
   DP_RGBMAP_TYPE_GRB,                                                 /**< Color component order is GRB            */
   DP_RGBMAP_TYPE_BGR,                                                 /**< Color component order is BGR            */
   DP_RGBMAP_TYPE_BRG,                                                 /**< Color component order is BRG            */
   DP_RGBMAP_TYPE_MAX,
   DP_RGBMAP_TYPE_FORCE_32BIT                     = 0x7FFFFFFF
} DP_RGBMapType;

/*!
 * \enum DP_LinkTrainingType
 *
 * The \b DP_TrainingType defines the types of Link Training.
 *
 */
typedef enum
{
   DP_LINK_TRAINING_TYPE_NO_TRAINING              = 0x00000000,        /**< No Link Training                        */
   DP_LINK_TRAINING_TYPE_FULL_TRAINING,                                /**< Full Link Training                      */
   DP_LINK_TRAINING_TYPE_FAST_TRAINING,                                /**< Training patterns are sent - panel status not read */
   DP_LINK_TRAINING_TYPE_MAX,
   DP_LINK_TRAINING_TYPE_FORCE_32BIT              = 0x7FFFFFFF
} DP_LinkTrainingType;

/*!
 * \enum DP_PixelFormatType
 *
 * The \b DP_PixelFormatType defines the supported display/LCD color specific formats.
 *
 */
typedef enum
{
   DP_PIXEL_FORMAT_NONE                           = 0x00000000,
   DP_PIXEL_FORMAT_RGB_666_18BPP,                                      /**< Color Format RGB666                     */
   DP_PIXEL_FORMAT_RGB_888_24BPP,                                      /**< Color Format RGB888                     */
   DP_PIXEL_FORMAT_RGB_101010_30BPP,                                   /**< Color Format RGB101010                  */
   DP_PIXEL_FORMAT_MAX,
   DP_PIXEL_FORMAT_FORCE_32BIT                    = 0x7FFFFFFF
} DP_PixelFormatType;

/*!
* \enum DP_BitDepthType
*
* The \b DP_BitDepthType defines the supported bit depth per color channel.
*
*/
typedef enum
{
  DP_BITDEPTH_NONE                                = 0,
  DP_BITDEPTH_6BPC                                = 6,                /**< 6  Bit per color channel                */
  DP_BITDEPTH_8BPC                                = 8,                /**< 8  Bit per color channel                */
  DP_BITDEPTH_10BPC                               = 10,               /**< 10 Bit per color channel                */
  DP_BITDEPTH_12BPC                               = 12,               /**< 12 Bit per color channel                */
  DP_BITDEPTH_16BPC                               = 16,               /**< 16 Bit per color channel                */
  DP_BITDEPTH_MAX,
  DP_BITDEPTH_FORCE_32BIT                         = 0x7FFFFFFF
} DP_BitDepthType;

/*!
* \b DP_ConnectionStatusType
*
* Enumeration DP cable connection status, 
*
*/
typedef enum
{
  DP_CONNECTION_POLARITY_POLARITY_DEFAULT = 0,   /* DP cable is connected in normal polarity.    */
  DP_CONNECTION_POLARITY_POLARITY_REVERSE = 1,   /* DP cable is connected in reverted polarity.  */
  DP_CONNECTION_STATUS_DISCONNECTED       = 2,   /* DP cable is disconnected.                    */
  DP_CONNECTION_STATUS_MAX,
  DP_CONNECTION_STATUS_32BIT              = 0x7FFFFFFF
} DP_ConnectionStatusType;

/*!
* \b DP_ConnectionPinAssignment
*
* Enumeration DP cable pin assignment,
*
*/
typedef enum
{
  DP_CONNECTION_PINASSIGNMENT_INVALID  = 0x00,    /* No DP cable is connected                     */
  DP_CONNECTION_PINASSIGNMENT_DFPD_A   = 0x01,    /* DFP_D(Downstream Facing Port DP) Pin A       */
  DP_CONNECTION_PINASSIGNMENT_DFPD_B   = 0x02,    /* DFP_D(Downstream Facing Port DP) Pin B       */
  DP_CONNECTION_PINASSIGNMENT_DFPD_C   = 0x03,    /* DFP_D(Downstream Facing Port DP) Pin C       */
  DP_CONNECTION_PINASSIGNMENT_DFPD_D   = 0x04,    /* DFP_D(Downstream Facing Port DP) Pin D       */
  DP_CONNECTION_PINASSIGNMENT_DFPD_E   = 0x05,    /* DFP_D(Downstream Facing Port DP) Pin E       */
  DP_CONNECTION_PINASSIGNMENT_DFPD_F   = 0x06,    /* DFP_D(Downstream Facing Port DP) Pin F       */
  DP_CONNECTION_PINASSIGNMENT_UFPD_A   = 0x07,    /* UFP_D(Upstream Facing Port DP)   Pin A       */
  DP_CONNECTION_PINASSIGNMENT_UFPD_B   = 0x08,    /* UFP_D(Upstream Facing Port DP)   Pin B       */
  DP_CONNECTION_PINASSIGNMENT_UFPD_C   = 0x09,    /* UFP_D(Upstream Facing Port DP)   Pin C       */
  DP_CONNECTION_PINASSIGNMENT_UFPD_D   = 0x0A,    /* UFP_D(Upstream Facing Port DP)   Pin D       */
  DP_CONNECTION_PINASSIGNMENT_UFPD_E   = 0x0B,    /* UFP_D(Upstream Facing Port DP)   Pin E       */
  DP_CONNECTION_PINASSIGNMENT_MAX,
  DP_CONNECTION_PINASSIGNMENT_32BIT    = 0X7FFFFFFF
} DP_ConnectionPinAssignment;

//-------------------------------------------------------------------------------------------------
//  DP_CapsInfoType
//
//  @brief
//      Bitwise capability mask.
//
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  DP_CAPS_NONE        = 0x00000000,
  DP_CAPS_MST         = 0x00000001, /**< MST is supported on this platform. 
                                         Caps is passed from DPDrver to host. */
  DP_CAPS_DSC         = 0x00000002, /**< DSC is supported on this platform.   */
  DP_CAPS_BRIGHTNESS  = 0x00000004, /**< Brightness control is supported.      */
  DP_CAPS_MAX,
  DP_CAPS_FORCE_32BIT = 0x7FFFFFFF
} DP_CapsInfoType;

//-------------------------------------------------------------------------------------------------
//  DP_PSRRequestType
//
//  @brief
//      PSR request type
//
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  DP_PSR_REQUEST_NONE              = 0,
  DP_PSR_REQUEST_DISABLE,                  /**< Disable PSR feature on sink & source - sink cannot enter/exit PSR */
  DP_PSR_REQUEST_ENABLE,                   /**< Enable PSR feature on sink & source  - sink can now enter/exit PSR */
  DP_PSR_REQUEST_ENTER,                    /**< Indicate PSR enter to sink */
  DP_PSR_REQUEST_EXIT,                     /**< Indicate PSR exit to sink  */
  DP_PSR_REQUEST_WAIT_FOR_ENTER_DONE,      /**< Wait for PSR enter to complete */
  DP_PSR_REQUEST_WAIT_FOR_EXIT_DONE,       /**< Wait for PSR exit to complete */
  DP_PSR_REQUEST_SETUP_TX_FOR_VIDEO,       /**< Set up main link for video */
  DP_PSR_REQUEST_TX_TURN_ON,               /**< Turn main link on (to be called before PSR exit) */
  DP_PSR_REQUEST_MAX,
  DP_PSR_REQUEST_32BIT             = 0x7FFFFFFF
} DP_PSRRequestType;

//-------------------------------------------------------------------------------------------------
//  DP_PanelMode_FlagType
//
//  @brief
//      Set of flag indicating Panel mode index to be updated or not.
//
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  DP_MODESET_FLAG_NONE              = 0,
  DP_MODESET_FLAG_UPDATEONLY,                 /**< Only update mode without a physical mode change */
  DP_MODESET_FLAG_32BIT             = 0x7FFFFFFF
} DP_PanelMode_FlagType;

//-------------------------------------------------------------------------------------------------
//  DP_Config_FlagType
//
//  @brief
//      Set of flag for setting up DP configuration.
//
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  DP_CONFIG_FLAG_NONE                               = 0x00000000,
  DP_CONFIG_FLAG_AUX_PIN_SWITCH_INVERTED            = 0x00000001, /**< TypeC AUX P/N switch GPIO polarity is inverted   */
  DP_CONFIG_FLAG_DISABLE_DSC                        = 0x00000002, /**< Disable DSC                                      */
  DP_CONFIG_FLAG_DISABLE_MST                        = 0x00000004, /**< Disable MST                                      */
  DP_CONFIG_FLAG_ALT_MODE_FIXED_LANE_CONFIGURATION  = 0x00000008, /**< Fixed pin assignment and polarity in alt-mode    */
  DP_CONFIG_FLAG_STRICT_EDID_CHECK                  = 0x00000010, /**< Enforce strict EDID check of CRC                 */
  DP_CONFIG_FLAG_HPD_FAILSAFE                       = 0x00000020, /**< eDP style HPD. Poll, wait, and ignore failure    */
  DP_CONFIG_FLAG_ALT_MODE_COMMON_RESET              = 0x00000040, /**< Reset the DP/USB combo PHY                       */
  DP_CONFIG_FLAG_32BIT                              = 0x7FFFFFFF
} DP_Config_FlagType;

//-------------------------------------------------------------------------------------------------
//  DP_DiagLevelType
//
//  @brief
//      DP Diagnostic level configuration
//
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  DP_DIAG_LEVEL_0 = 0,  /**< Default no additional diagnostic logging */
  DP_DIAG_LEVEL_1 = 1,  /**< Source/Sink CRC */
  DP_DIAG_LEVEL_2 = 2,  /**< Sink PSR Status and Sink Link Status */
  DP_DIAG_LEVEL_3 = 3,  /**< Sink EDID/DPCD logging */
} DP_DiagLevelType;

//-------------------------------------------------------------------------------------------------
//  DP_SinkClassType
//
//  @brief
//      DP Sink Class Type
//
//-------------------------------------------------------------------------------------------------
typedef enum 
{
  DP_SINKCLASS_DEFAULT = 0,
  DP_SINKCLASS_REPEATER,
} DP_SinkClassType;

//-------------------------------------------------------------------------------------------------
//  DP_CustomSinkType
//
//  @brief
//      DP Custom Sink Class Type
//
//-------------------------------------------------------------------------------------------------
typedef enum {
   DP_CUSTOM_SINKID_NONE = 0,
   DP_CUSTOM_SINKID_1,  // Kandou KB8001
} DP_CustomSinkType;

//-------------------------------------------------------------------------------------------------
//  DP_DeviceSpecificType
//
//  @brief
//      DP_DeviceSpecificType defines the specifics of a devices that includes the OUI, Device String ID and HW/FW revisions. 
//
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  DP_DEVICESPECIFIC_SINK          = 0,        /**< Sink Device-specific field     */
  DP_DEVICESPECIFIC_BRANCH,                   /**< Branch Device-specific field   */
  DP_DEVICESPECIFIC_MAX,
  DP_DEVICESPECIFIC_32BIT         = 0x7FFFFFFF
} DP_DeviceSpecificType;

//-------------------------------------------------------------------------------------------------
//  DP_GPIOResourceType
//
//  @brief
//      DP GPIO resource ennumeration 
//
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  DP_GPIO_RESOURCE_AUX_POLARITY_SEL = 0,     /* DP GPIO resource for Aux polarity select    */
  DP_GPIO_RESOURCE_AUX_SWITCH_SEL   = 1,     /* DP GPIO resource for Aux switch select      */
  DP_GPIO_RESOURCE_TYPE_MAX,
  DP_GPIO_RESOURCE_TYPE_32BIT       = 0x7FFFFFFF
} DP_GPIOResourceType;

/*--------------------------------------------------------------------------------------------------------------------
 Data structure Defines
---------------------------------------------------------------------------------------------------------------------*/
typedef MDP_Display_HDMI_AudioModeInfoPropType      DP_AudioModeInfoPropType;

typedef void                                       *DP_HandleType;


/*!
 * \struct DP_ClockConfigType
 *
 * The \b DP_ClockConfigType defines the clock setting for DP link clock and pixel clock.
 *
 */
typedef struct  
{
   DP_ClockSourceType               eLinkClockSource;                   /**< Desired clock Source for link clock     */
   uint32                           uLinkClockFreq;                     /**< Desired link clock frequency            */
   DP_ClockSourceType               ePixelClockSource;                  /**< Desired clock Source for pixel clock    */
   uint32                           uPixelClockFreq;                    /**< Desired pixel clock frequency           */
   uint32                           uRefreshRateFreq;                   /**< Desired refresh rate in Hz              */
} DP_ClockConfigType;


/*!
 * \struct DP_PanelInfoType
 *
 * The \b DP_PanelInfoType defines the panel parameters, color format, timing parameters.
 *
 */
typedef struct
{
   uint32                           uModeIndex;
   DP_PixelFormatType               eColorFormat;                       /**< Color format of panel                                        */
   uint32                           uRefreshRate;                       /**< Refresh rate.                                                */
   uint32                           uPclkFreq;                          /**< Panel Pixel clk frequency in Hz                              */

   uint32                           uVisibleWidthInPixels;              /**< Visible active area width in pixels                          */
   uint32                           uVisibleHeightInPixels;             /**< Visible active area height in pixels                         */

   uint32                           uHsyncFrontPorchInPixels;           /**< HSYNC Front Porch width in pixels                            */
   uint32                           uHsyncBackPorchInPixels;            /**< HSYNC Back Porch width in pixels                             */
   uint32                           uHsyncPulseInPixels;                /**< HSYNC pulse width in pixels                                  */
   uint32                           uHsyncSkewInPixels;                 /**< HSYNC active edge is delayed from VSYNC                      */

   uint32                           uVsyncFrontPorchInLines;            /**< VSYNC Front Porch width in lines                             */
   uint32                           uVsyncBackPorchInLines;             /**< VSYNC Back Porch width in lines                              */
   uint32                           uVsyncPulseInLines;                 /**< VSYNC pulse width in lines                                   */
   
   uint32                           uHLeftBorderInPixels;               /**< Left border in pixels                                        */
   uint32                           uHRightBorderInPixels;              /**< Right border in pixels                                       */
   uint32                           uVTopBorderInLines;                 /**< Top border in lines                                          */
   uint32                           uVBottomBorderInLines;              /**< Bottom border in lines                                       */
   
   bool32                           bHSyncActiveLow;                    /**< Hsync polarity                                               */
   bool32                           bVSyncActiveLow;                    /**< Vsync polarity                                               */
   bool32                           bInterlaced;                        /**< Interlaced support                                           */
   bool32                           bAudioSupported;                    /**< Indicates whether current display mode supports Audio        */
   uint32                           u3DFrameFormat;                     /**< Indicates the type of 3D format this mode is associated with */
   uint32                           uAspectRatio;                       /**< Indicates the aspect ratio of the current mode               */
   uint32                           uRotation;                          /**< Indicates the orientation of the screen                      */
   bool32                           bVirtualMode;                       /**< Indicates artificial mode injected to the mode list.         */
} DP_PanelInfoType;

//-------------------------------------------------------------------------------------------------
//  DP_DSCInfoType
//
//  @brief
//      DP DSC Block Information.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct 
{
  bool32   bDSCEnabled;              /**< Display Stream Compression enabled                              */
  uint32   uMajorVersion;            /**< Display Stream Compression major version                        */
  uint32   uMinorVersion;            /**< Display Stream Compression minor version                        */
  uint32   uCompressionRatio;        /**< Compression Ratio                                               */
  uint32   uSliceWidth;              /**< Slice width                                                     */
  uint32   uSliceHeight;             /**< Slice Height                                                    */
  uint32   uSlicesPerLine;           /**< Slices per line                                                 */
  bool32   bBlockPredEnabled;        /**< Block prediction enabled                                        */
  bool32   bFECEnabled;              /**< Forward Error Correction enabled                                */
  uint32   uProfileID;               /**< DSC Profile ID                                                  */
  uint32   uDSCPixelsPerLine;        /**< DSC pixels per line                                             */
  uint32   uDSCWidth;                /**< Active width adjusted for compression                           */
  double   dDSCHBlankPeriod;         /**< horizontal blanking period adjusted for compression             */
  uint32   uDSCPixelClkInKhz;        /**< Pixel clock adjusted for compression                            */
  uint32   uFECLinkClkInKhz;         /**< Link clock adjusted for FEC                                     */
  uint32   uDSCDTONumerator;         /**< DSC DTO Numerator                                               */
  uint32   uDSCDTODenominator;       /**< DSC DTO Denominator                                             */
  float    fDSCOverheadRatio;        /**< DSC overhead ratio                                              */
  uint32   uInputBitsPerComponent;   /**< Original stream bits per component                              */
  uint32   uOutputBitsPerPixel;      /**< Stream bits per pixel adjusted for compression                  */
} DP_DSCInfoType;

/*!
 * \struct DP_PanelModeInfo
 *
 * The \b DP_PanelModeInfo defines the panel mode index.
 *
 */
typedef struct
{
   uint32                            uModeIndex;                          /**< Indicates the panel mode index        */
   uint32                            uFlags;                               /**< Indicates mode index is to be updated */
} DP_PanelModeInfo;

/*!
 * \struct DP_PanelModesType
 *
 * The \b DP_PanelModesType defines the array of the possible modes the panel supports 
 *
 */
typedef struct
{
   DP_PanelInfoType                sPanelInfo[MAX_DP_PANEL_MODE];      /**< Current panel display mode              */
} DP_PanelModesType;

/*!
 * \struct DP_WritePacketType
 *
 * The \b DP_WritePacketType defines DP AUX write packet. 
 *
 */
typedef struct
{
   DP_TransactionModeType          eTransactionType;                   /**< AUX transaction type                    */
   uint32                          uAddress;                           /**< AUX Write start address                 */
   uint8                          *puWriteData;                        /**< Buffer of data to be written            */
   uint32                          uWriteDataSize;                     /**< Size of data to be written in byte      */
   uint32                          uBytesWritten;                      /**< How many bytes written                  */
   bool32                          bQueueOnly;                         /**< Only queue the command - do not send    */
   DP_AUX_TransactionFlags         eFlags;                             /**< Flags for stall/sleep, set MoT in I2C   */
} DP_WritePacketType;

/*!
 * \struct DP_ReadPacketType
 *
 * The \b DP_ReadPacketType defines DP AUX read packet. 
 *
 */
typedef struct
{
   DP_TransactionModeType          eTransactionType;                   /**< AUX transaction type                    */
   uint32                          uAddress;                           /**< AUX Write start address                 */
   uint8                          *puReadDataBuffer;                   /**< Data buffer for return values           */
   uint32                          uReadSize;                          /**< Data size to be read in byte            */
   uint32                          uBytesRead;                         /**< How many bytes Read from FIFO           */
   bool32                          bQueueOnly;                         /**< Only queue the command - do not send    */
   DP_AUX_TransactionFlags         eFlags;                             /**< Flags for stall/sleep, set MoT in I2C   */
   bool32                          bTunneledMode;                      /**< Whether transcation in tunneled mode    */
} DP_ReadPacketType;

/*!
 * \struct DP_PeSwPairType
 *
 *  pre-emphasis and voltage swing
 *
 */
typedef struct
{
  uint16 uPreEmphasis;
  uint16 uVoltageSwing;
}DP_PeSwPairType;

/*!
 * \struct DP_Config_PreEmphSwing
 *
 *  The length of the list, specified as 1st element, determines how to interpret the list
 *    -> 1st element of this override list is the length of the remaining list
 *  If the length is 9 then it is a list of Pre-emphasis and Voltage Swing value pairs:
 *    -> Each element is a combination where 0-7bits is swing value and 8-15bits is pre-emphasis value
 *  If the length is 2 then list contains a couple of multiplier values
 *    -> 2nd element is pre-emphasis value multiplier and 3rd element is swing value multiplier
 *
 *  Any other length value of the list will be treated as invalid
 */
typedef struct
{
  uint16           uLength;
  DP_PeSwPairType  aValueLUT[3][3];
  uint16           aMultiplierList[2];
}DP_Config_PreEmphSwingType;

//-------------------------------------------------------------------------------------------------
//  DP_Config_BondedModeType
//
//  @brief
//      Defines the DP bonded mode configuration info of the DP display.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  bool32             bEnabled;                    /**< True if DP is in bonded mode */
  DP_DeviceIDType    eSourceClockDeviceID;        /**< Device ID of DP Device sourcing the shared clock */
  DP_DeviceIDType    eMasterAUXDeviceID;          /**< Device ID of DP master AUX to use for edid, failsafe, etc  */
} DP_Config_BondedModeType;

//-------------------------------------------------------------------------------------------------
//  DP_Config_OverrideType
//
//  @brief
//      Defines the configuration and buffers to override AUX with.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct {
  MDP_DP_OverrideModeType  eMode; /**< Override mode (off/fallback/replace) */
  MDP_DP_OverrideBufsType *pBufs; /**< Pointer to override buffers */
} DP_Config_OverrideType;

//-------------------------------------------------------------------------------------------------
//  DP_SourceCapType
//
//  @brief
//      DP source caps struct.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{                                                           
  uint32 uMaxLinkRateInKHz; /**< Maximum link rate supported by DP source; 0 if no cap set */
} DP_SourceCapType;

/*!
 * \struct DP_HostOpenConfigType
 *
 * The \b DP_HostOpenConfigType defines open parameters for DP_Host_Open().
 *
 */
typedef struct  
{
   DP_DeviceIDType                  eDeviceID;                          /**< DP device instance ID                        */
   MDP_Display_IDType               eDisplayID;                         /**< DisplayID associated with this context       */
   bool32                           bHPDActiveLow;                      /**< Indicate if HPD from panel in active low     */
   uint32                           uLaneSwingLevel;                    /**< Lane voltage swing level                     */
   uint32                           uPreemphasisLevel;                  /**< Lane pre-emphasis level                      */
   MDP_DP_PHY_SSCConfigType         eSSCMode;                           /**< Enable SSC mode                              */
   bool32                           bAsynchronousMode;                  /**< Enable async mode for pixel rate & link rate */
   bool32                           bReadDPCD;                          /**< Flag to read DPCD from panel                 */
   bool32                           bReadEDID;                          /**< Flag to read EDID from panel                 */
   uint32                           uPowerupWaitinMs;                   /**< Time to wait after panel powering up         */
   uint32                           uMaxAuxRetry;                       /**< Number of retry before AUX I/O success.      */
   bool32                           bAuxUsePolling;                     /**< Indicates Interrupt driven mechanism to be   
                                                                             used or not for AUX transaction wait         */
   bool32                           bInitContextOnly;                   /**< Context init only for continuous splash      */
   DP_ConnectionPinAssignment       ePinAssignment;                     /**< Pin assignment                               */
   DP_ConnectionStatusType          eConnectionPolarity;                /**< Connection polarity                          */
   uint32                           uLaneMapping;                       /**< Defines Physical to logic lane mapping       */
   DP_MSTStreamIDType               eStreamId;                          /**< Caller should pass in which stream to drive  */
   DP_CapsInfoType                  eCapabilityMask;                    /**< Bitwise DP capability mask such as MST       */
   DP_ControllerIDType              eDPControllerId;                    /**< Controller ID returned by DP_Host_open()     */
   uint32                           uNumStreams;                        /**< Number of streams that can be supported on  
                                                                             this DP device, returned by DP_Host_open()   */
   DP_Config_FlagType               eConfigFlags;                       /**< Configuration flags from DP_Config_FlagType  */
   DP_DiagLevelType                 eDiagLevel;                         /**< Diagnostic level                             */
   DP_Config_PreEmphSwingType       sPreEmphSwingConfigType;            /**< Pre-emph and Swing override config data      */
   DP_Config_BondedModeType         sBondedModeConfig;                  /**< Bonded mode configuration                    */
   DP_Config_OverrideType           sOverrideConfig;                    /**< DP AUX override buffers from XML             */
   bool32                           bTunnelingMode;                     /**< DP Tunneling mode enable                     */
   DP_HandleType                    hHostRouterHandle;                  /**< DP Tunneling Host Router handle              */   
   MDP_Panel_BacklightType          eBrightnessType;                    /**< Panel brightness control type                */
   DP_SourceCapType                 sSourceOverrideCaps;                /**< DP source caps that override DP sink caps    */
} DP_HostOpenConfigType;

/*!
* \b DP_AudioCfgType
*
*  Defines audio parameters
*/
typedef struct
{
  DP_DeviceIDType                 eDeviceID;                          /**< DP device ID                               */
  uint32                          uLinkRate;                          /**< Indicate if HPD from panel in active low   */
  DP_AudioSampleRateType          eAudioSampleRate;                   /**< Audio sample rate                          */
  DP_AudioChannelType             eAudioNumOfChannel;                 /**< Number of audio channels                   */
  DP_AudioFormatType              eAudioFormat;                       /**< Audio format                               */
  DP_AudioSampleBitDepthType      eAudioSampleBitDepth;               /**< Audio bit depth                            */
} DP_AudioCfgType;

/*!
* \b DP_DSCPPSCfgType
*
*  Defines DSC PPS parameters
*/
typedef struct
{
  uint32                          uStreamId;                          /**<                             */
  uint8                          *pPPSBuffer;                         /**<                             */
  uint32                          uSize;                              /**<                             */
} DP_DSCPPSCfgType;

/*!
* \b DP_GenericSDPCfgType
*
*  Defines Generic SDP configuration parameters for a slot.
*/
typedef struct
{
   uint8         uHB0;              /**< Generic SDP header byte 0                */
   uint8         uHB1;              /**< Generic SDP header byte 1                */
   uint8         uHB2;              /**< Generic SDP Header byte 2                */
   uint8         uHB3;              /**< Generic SDP header byte 3                */
   uint8        *pPayloadBuffer;    /**< Generic SDP payload buffer               */
   uint32        uPayloadBytes;     /**< Generic SDP payload buffer size in bytes */
   uint32        uSDPIndex;         /**< Generic SDP slot index                   */
} DP_GenericSDPCfgType;

/*!
* \b DP_GenericSDPEnableType
*
*  Defines Generic SDP enable configuration for a slot.
*/
typedef struct
{
  uint32         uSDPIndex;    /**< Generic SDP slot index   */
  bool32         bEnabled;     /**< Enabled status for slot */
} DP_GenericSDPEnableType;

/*!
* \b WriteInfoType
*
* Structure captures address write information.
* Writes [IN]pNumBytes starting from 'uAddress'.
* As [OUT]pNumBytes has number of bytes wrote
*/
typedef struct
{
  DP_TransactionModeType     eMode;            /* Mode of the write                       */
  uint32                     uAddress;         /* Address to write                        */
  uint32                     uDataBufSize;     /* Size of the data buffer                 */
  uint8                     *pDataBuf;         /* Data buffer storing the data to write   */
  uint32                    *pNumBytes;        /* Number of bytes to write/written        */
} WriteInfoType;

/*!
 * \enum DP_LinkCommandType
 *
 * The \b DP_LinkCommandType defines the command to the main link Finite State Machine states, 
 *
 */
typedef enum
{
   DP_LINKCOMMAND_TYPE_NONE                    = 0x00000000,
   DP_LINKCOMMAND_TYPE_ENABLE,                                     /**< Enable DP Main link Controller          */
   DP_LINKCOMMAND_TYPE_SEND_PATTERN1,                              /**< Trigger main link to send train pattern1*/
   DP_LINKCOMMAND_TYPE_SEND_PATTERN2,                              /**< Trigger main link to send train pattern2*/
   DP_LINKCOMMAND_TYPE_SEND_PATTERN3,                              /**< Trigger main link to send train pattern3*/
   DP_LINKCOMMAND_TYPE_SEND_PATTERN4,                              /**< Trigger main link to send train pattern4*/
   DP_LINKCOMMAND_TYPE_SEND_SYMBOL_ERM,                            /**< Send symbol error rate measure  pattern */
   DP_LINKCOMMAND_TYPE_SEND_PRBS7,                                 /**< Trigger main link to send PRBS7 pattern */
   DP_LINKCOMMAND_TYPE_SEND_CUSTOM_PATTERN,                        /**< Trigger to send 80bit custom pattern    */
   DP_LINKCOMMAND_TYPE_SEND_VIDEO,                                 /**< Trigger main link to send video data    */
   DP_LINKCOMMAND_TYPE_PUSH_IDLE,                                  /**< Trigger to send push for idle state     */
   DP_LINKCOMMAND_TYPE_DISABLE,                                    /**< Disable DP Main link Controller         */
   DP_LINKCOMMAND_TYPE_MAX,
   DP_LINKCOMMAND_TYPE_FORCE_32BIT             = 0x7FFFFFFF
} DP_LinkCommandType;

/*!
 * \enum DP_PHYModeType
 *
 * Defines the various PHY modes.
 *
 */
typedef enum
{
   DP_PHY_MODE_NONE            = 0x00000000,
   DP_PHY_MODE_USB_DATA,                        /**< USB SS only PHY mode              */
   DP_PHY_MODE_DP,                              /**< DP only PHY mode                  */
   DP_PHY_MODE_CONCURRENCY,                     /**< USB SS & DP concurrency PHY mode  */
   DP_PHY_MODE_DP_TUNNELING_PLL_ON,             /**< USB4 DP Tunneling DP PLL ON       */
   DP_PHY_MODE_DP_TUNNELING_PLL_OFF,            /**< USB4 DP Tunneling DP PLL OFF      */
   DP_PHY_MODE_MAX,
   DP_PHY_MODE_FORCE_32BIT     = 0x7FFFFFFF
} DP_PHYModeType;

/*!
 * \enum DP_PHYPowerModuleType
 *
 * Defines HW modules that can be powered on/off inside DP controller.
 *
 */
typedef enum
{
   DP_PHY_POWER_NONE                         = 0x00000000,
   DP_PHY_POWER_PHY                          = DP_BIT(0),  /**< HW component: DP PHY                       */
   DP_PHY_POWER_PLL                          = DP_BIT(1),  /**< HW component: DP PLL                       */
   DP_PHY_POWER_PHY_TIMING_FIFO              = DP_BIT(2),  /**< HW component: DP PHY timing FIFO           */
   DP_PHY_POWER_MAX,
   DP_PHY_POWER_FORCE_32BIT                  = 0x7FFFFFFF
} DP_PHYPowerModuleType;

/*!
 * \enum DP_PHYResetFlagType
 *
 * The \b DP_PHYResetFlagType defines the various PHY reset options.
 *
 */
typedef enum
{
  DP_PHY_RESET_NONE                               = 0x00000000,
  DP_PHY_RESET_ALT_MODE_COMMON_RESET              = 0x00000001,  /**< Reset the DP/USB combo PHY */
  DP_PHY_RESET_FORCE_32BIT                        = 0x7FFFFFFF
} DP_PHYResetFlagType;

/*!
* \b DP_DisplayModeAspectRatioType
*
*  Indicates the various aspect ratio that the sink can support
*/
typedef enum
{
  DP_DISPLAY_MODE_ASPECT_RATIO_NONE     = 0x0,
  DP_DISPLAY_MODE_ASPECT_RATIO_4_3,                   /* Aspect ratio of 4:3 */
  DP_DISPLAY_MODE_ASPECT_RATIO_16_9,                  /* Aspect ratio of 16:9 */
  DP_DISPLAY_MODE_ASPECT_RATIO_16_10,                 /* Aspect ratio of 16:10 */
  DP_DISPLAY_MODE_ASPECT_RATIO_5_4,                   /* Aspect ratio of 5:4 */
  DP_DISPLAY_MODE_ASPECT_RATIO_15_9,                  /* Aspect ratio of 15:9 */
  DP_DISPLAY_MODE_ASPECT_RATIO_5_3,                   /* Aspect ratio of 5:3 */ 
  DP_DISPLAY_MODE_ASPECT_RATIO_MAX,
  DP_DISPLAY_MODE_ASPECT_RATIO_32BIT    = 0x7FFFFFFF
}DP_DisplayModeAspectRatioType;

//-------------------------------------------------------------------------------------------------
//  PanelSinkStatusFlags
//
//  @brief
//      Flags used in PanelSinkStatusType.uFlags
//-------------------------------------------------------------------------------------------------
//
typedef enum _PanelSinkStatusFlags
{
  PANELSINKSTATUS_SINK_COUNT_FLAG = 0x00000001,      /**< Reports sink count not including current display */
  PANELSINKSTATUS_FLAG_MAX
} PanelSinkStatusFlags;

/*!
* \b DP_PHYPowerType
*
*  Defines properties to power up DP PHY modules.
*/
typedef struct
{
  bool32                           bEnabled;    /**< Boolean indicating if components are to be enabled/disabled   */
  DP_PHYPowerModuleType            uModules;    /**< Flag indicating which PHY related HW blocks are to configured */
} DP_PHYPowerType;

/*!
* \b DP_SimulationConfigType
*
*   Defines properties to set up DP simulation mode configuration
*/
typedef struct
{
  bool32                           bEnabled;    /**< Boolean indicating if components are to be enabled/disabled   */
  DP_DeviceIDType                  eDeviceId;   /**< Device ID                                                     */
  DP_StreamIDType                  eStreamId;   /**< Stream ID                                                     */
  MDP_Display_IDType               eDisplayId;  /**< Display ID for logging                                        */
} DP_SimulationConfigType;

/*!
* \b DP_BrightnessControlType
*
*  Defines properties to control panel brightness
*/
typedef struct
{
  DP_BrightnessRequestType         eBrightnessRequest;                 /**< Brightness request enabled/disabled/level     */
  float                            fLevel;                             /**< Brightness level to be configured [0.0-1.0]   */
  uint32                           uMillinits;                         /**< Brightness to be configured in Millinits      */
} DP_BrightnessControlType;

/*!
 * \struct DP_PHYResetType
 *
 * The \b DP_PHYResetType struct defines the DP PHY reset info.
 *
 */
typedef struct
{
  DP_DeviceIDType       eDeviceID;        /**< ID of DP Device PHY to reset */
  DP_PHYResetFlagType   ePHYResetFlag;    /**< Type of PHY reset            */
} DP_PHYResetType;

/*!
* \b DP_SetPropertyParamsType
*
*  Defines the union of all the types used for SetProperty
*/
typedef union
{
  bool32                           bEnabled;                           /**< DP_SETPROPERTY_SET_ASSR_ENABLE,        
                                                                            DP_SETPROPERTY_LINK_CLOCK              */
  DP_PanelModeInfo                 sModeInfo;                          /**< DP_SETPROPERTY_PANEL_MODE_INDEX        */
  DP_PanelInfoType                 sPanelInfo;                         /**< DP_SETPROPERTY_PANEL_INFO              */
  uint32                           uLinkRate;                          /**< DP_SETPROPERTY_LINK_RATE               */
  uint32                           uLaneNumber;                        /**< DP_SETPROPERTY_LANE_NUMBER             */
  DP_LinkTrainingType              eLinkTrainingType;                  /**< DP_SETPROPERTY_LINK_TRAINING_TYPE      */
  DP_ClockConfigType               sClockConfig;                       /**< DP_SETPROPERTY_CLOCKS                  */
  bool32                           bConnected;                         /**< DP_SETPROPERTY_CONNECTION_STATUS       */
  uint32                           uInterruptList;                     /**< DP_SETPROPERTY_INTERRUPT_ENABLE, 
                                                                            DP_SETPROPERTY_INTERRUPT_DISABLE, 
                                                                            DP_SETPROPERTY_INTERRUPT_CLEAR, 
                                                                            DP_SETPROPERTY_SIGNAL_EVENT            */
  DP_AudioCfgType                  sAudioParams;                       /**< DP_SETPROPERTY_AUDIO_CONFIG            */
  DP_PSRRequestType                ePSRRequest;                        /**< DP_SETPROPERTY_PSR_CONFIG              */
  DP_DSCPPSCfgType                 sDSCPPSParams;                      /**< DP_SETPROPERTY_UPDATE_PPS              */
  uint32                           uPreEmphasisLevel;                  /**< DP_SETPROPERTY_PRE_EMPHASIS_LEVEL      */
  uint32                           uVoltageSwingLevel;                 /**< DP_SETPROPERTY_VOLTAGE_SWING_LEVEL     */
  uint32                           uTestPatternType;                   /**< DP_SETPROPERTY_TEST_PATTERN            */
  WriteInfoType                    sWriteInfo;                         /**< DP_SETPROPERTY_WRITE_ADDR              */
  DP_LinkCommandType               eLinkCommandtype;                   /**< DP_SETPROPERTY_MAIN_LINK_STATE         */
  DP_PHYPowerType                  sPHYPowerInfo;                      /**< DP_SETPROPERTY_PHY_POWER               */
  DP_GenericSDPCfgType             sGenericSDPCfg;                     /**< DP_SETPROPERTY_GENERIC_SDP_CONFIG      */
  DP_GenericSDPEnableType          sGenericSDPEnable;                  /**< DP_SETPROPERTY_GENERIC_SDP_ENABLE      */
  DP_SimulationConfigType          sSimulationInfo;                    /**< DP_SETPROPERTY_SIMULATION_MODE         */
  DP_BrightnessControlType         sBrightnessInfo;                    /**< DP_SETPROPERTY_BRIGHTNESS_CONTROL      */
  DP_PHYResetType                  sPHYResetInfo;                      /**< DP_SETPROPERTY_RESET_PHY               */
  DP_DSCInfoType                  *pSinkDSCCap;                        /**< DP_SETPROPERTY_DSC_PPS_INFO            */
} DP_SetPropertyParamsType;

/*!
* \b EdidInfoType
*
* Structure captures RAW EDID information
*/
typedef struct
{
  uint32                                  uDataLength;                  /* Length of the EDID data block */
  uint8*                                  pDataBuf;                     /* Data buffer storing the raw EDID data */
} EdidInfoType;

/*!
* \b DpcdInfoType
*
* Structure captures RAW DPCD information
*/
typedef struct
{
  uint32                                  uDataLength;                  /* Length of the DPCD data block */
  uint8*                                  pDataBuf;                     /* Data buffer storing the raw DPCD data */
} DpcdInfoType;

/*!
* \b  DP_LipSyncInfoType
*
*  Defines the audio/video latency HDMI display
*/
typedef struct
{
  uint8            uVideoLatency;              /* Video latency in milliseconds for progressive video format */
  uint8            uInterlaceVideoLatency;     /* Video latency in milliseconds for interlaced video format */
  uint8            uAudioLatency;              /* Audio latency in milliseconds for progressive video format */
  uint8            uInterlaceAudioLatency;     /* Audio latency in milliseconds for interlaced video format */
} DP_LipSyncInfoType;

/*!
* \b DP_VendorInfoType
*
* Structure captures vendor specific parameters
*/
typedef struct
{
  bool32                                  bVideoOnly;                                           /* HDMI display support DVI mode (Video only) or HDMI mode (Audio and Video) */
  DP_LipSyncInfoType                      sLipSyncInfo;                                         /* Video and audio latency info */
  uint8                                   uSupportedDeepColorModeMask;                          /* Pixel depth for each deep color mode HDMI display can support (Use QDI_HDMI_DeepColorModeType) */
  uint8                                   uSupportedContentFilterMask;                          /* Sink supports various content filters (Use QDI_HDMI_ContentFilterType) */
  uint16                                  uPhysicalAddr;                                        /* 16 bit physical address of the source device, upper 16 bit is ignored. */
  bool32                                  bAISupport;                                           /* ACP, ISRC1 and ISRC2 packets supported or not */
  bool32                                  bDVIDualSupport;                                      /* Sink supports DVI Dual mode */
  DP_DisplayModeAspectRatioType           ePreferredAspectRatio;                                /* Preferred aspect ratio reported by the Sink */
  uint32                                  uMaxScreenWidthInMillimeter;                          /* Maximum screen width reported by the Sink in millimeters */
  uint32                                  uMaxScreenHeightInMillimeter;                         /* Maximum screen height reported by the Sink in millimeters */
  uint8                                   uManufacturerId[2];                                   /* Manufacturer ID : using EISA ID,  uManufacturerId[0] is low byte */
  uint16                                  uProductId;                                           /* Product code,  used to differentiate between different models from the manufacturer */
  uint8                                   uNameDescriptionLength;                               /* Sink name description length */
  uint8                                   uNameDescription[13];                                 /* Sink name description*/
  uint32                                  uReserved[2];                                         /* Reserved for future use */
} DP_VendorInfoType;

/*!
* \b DP_StreamInfoType
*
* Structure captures stream specific info
*/
typedef struct
{
  uint32                            uVirtualChannelId;  /* Stream virtual channel id */
} DP_StreamInfoType;

/*!
 * \struct DP_RefreshRateRangeType
 *
 * The \b DP_RefreshRateRangeType defines refresh rate range, that can be supported by panel.
 *
 */
typedef struct  
{
   uint32                            uMaxRefreshRate;     /* The maximum value of refresh rate that can be supported by Panel read from EDID */
   uint32                            uMinRefreshRate;     /* The minimum value of refresh rate that can be supported by Panel read from EDID */
} DP_RefreshRateRangeType;

/*!
* \b ReadInfoType
*
* Structure captures address read information.
* Reads [IN]pNumBytes starting from 'uAddress'.
* As [OUT]pNumBytes has number of bytes read.
*/
typedef struct
{
  DP_TransactionModeType         eMode;                 /* Mode of the read                  */
  uint32                         uAddress;              /* Address to read                   */
  uint32                         uDataBufSize;          /* Size of the buffer                */
  uint8                         *pDataBuf;              /* Data buffer storing the raw data  */
  uint32                        *pNumBytes;             /* Number of bytes 'to read' or read */
} ReadInfoType;

/*!
* \b DP_DeviceSpecificInfoType
*
*  Defines the structure for Device-specific identifier information 
*/
typedef struct
{
  uint32                           uDataLength;                             /**< Number of byte of device-specific data obtained  */
  uint8                            aIEEEOUI[DP_IEEE_OUI_LEN];               /**< IEEE OUI Identifier of the device                */
  uint8                            aDeviceString[DP_DEVICE_ID_STRING_LEN];  /**< Identifier string of the device                  */
  uint8                            uHWRevision;                             /**< Hardware revision of the device                  */
  uint8                            uFWMajorRevision;                        /**< Firmware major revision of the device            */
  uint8                            uFWMinorRevision;                        /**< Firmware minor revision of the device            */
  bool32                           bIsLinkCTSDevice;                        /**< Link CTS device is present                       */
} DP_DeviceSpecificInfoType;

/*!
* \b DP_DisplayRoutingType
*
* This structure contains audio routing information such as controller ID, stream ID.
*/
typedef struct
{
  uint32              uControllerId;                /**< DP Controller index */
  uint32              uStreamId;                    /**< Muti stream (MST) Video stream index */
} DP_DisplayRoutingType;

/*
* Struct to hold information on new added or disconnected sinks
* This information is used in MST case
*/
typedef struct
{
  MDP_Display_IDType     eDisplayId;                                /**< Display ID for which HPD interrupt
                                                                         is required                          */
  bool32                 bHDPIn;                                    /**< HPD IN/OUT required for this display */
} PanelSinkInfoType;

/*
* Sink status
*/
typedef struct
{
  bool32                 bPluggedIn;                                /**< Downstream sink is plugged in        */
  bool32                 bLinkLost;                                 /**< Link to downstream is lost           */
  uint32                 uSinkCount;                                /**< Sink count not including current 
                                                                         display used in MST case             */
  PanelSinkInfoType      sSinkList[PANEL_CONTROL_MAX_SINK_SIZE];    /**< List of added/disconnected sinks     */
  uint32                 uFlags;                                    /**< Flags used for querying sinks        */ 
} PanelSinkStatusType;

/*!
* \b DP_GetPropertyParamsType
*
*  Defines the union of all the types used for GetProperty
*/
typedef union
{
  bool32                            bEnabled;                                         /**< DP_GETPROPERTY_ASSR_ENABLE,            */
  DP_PanelInfoType                  sPanelInfo;                                       /**< DP_GETPROPERTY_GET_MODE_INFO           */
  uint32                            uLinkRateInKhz;                                   /**< DP_GETPROPERTY_LINK_RATE               */
  uint32                            uLaneNumber;                                      /**< DP_GETPROPERTY_LANE_NUMBER             */
  bool32                            bAUXStatusOK;                                     /**< DP_GETPROPERTY_AUXSTATUS               */
  bool32                            bPluggedIn;                                       /**< DP_GETPROPERTY_CONNECTION_STATUS       */
  EdidInfoType                      sEdidInfo;                                        /**< DP_GETPROPERTY_EDID_INFO               */
  uint32                            uInterruptList;                                   /**< DP_GETPROPERTY_INTERRUPT_STATUS        */
  DP_AudioModeInfoPropType         *psAudioModeInfo;                                  /**< DP_GETPROPERTY_AUDIO_MODE_INFO         */
  DP_VendorInfoType                 sVendorInfo;                                      /**< DP_GETPROPERTY_VENDOR_SPECIFIC_INFO    */
  DP_DisplayRoutingType             sRoutingInfo;                                     /**< DP_GETPROPERTY_ROUTING_INFO            */
//  uint32                            uIntEvent;                                      /**< DP_DISPLAY_PROPERTYID_SIGNALEVENT      */
  PanelSinkStatusType               sSinkStatus;                                      /**< DP_GETPROPERTY_SINK_STATUS             */
  DP_DSCInfoType                    sDSCInfo;                                         /**< DP_GETPROPERTY_DSC_INFO                */
  DP_StreamInfoType                 sStreamInfo;                                      /**< DP_GETPROPERTY_STREAM_VC_INFO          */
  DP_RefreshRateRangeType           sRefreshRateRangeInfo;                            /**< DP_GETPROPERTY_DISPLAY_RANGE_INFO      */
  ReadInfoType                      sReadInfo;                                        /**< DP_GETPROPERTY_READ_ADDR               */
  bool32                            bTopologyChanged;                                 /**< DP_GETPROPERTY_TOPOPLOGY_CHANGED       */
  DP_PSRRequestType                 ePSRState;                                        /**< DP_GETPROPERTY_PSR_CONFIG              */
  uint32                            uPreEmphasisLevel[2];                             /**< DP_GETPROPERTY_PRE_EMPHASIS_LEVEL      */
  uint32                            uVoltageSwingLevel[2];                            /**< DP_GETPROPERTY_VOLTAGE_SWING_LEVEL     */  
  DpcdInfoType                      sDPCDInfo;                                        /**< DP_SETPROPERTY_SIGNAL_EVENT            */
  DP_DeviceSpecificInfoType         sDeviceSpecificInfo[DP_DEVICESPECIFIC_MAX];       /**< DP_GETPROPERTY_DEVICE_SPECIFIC_INFO    */
  uint64                            uCRC;                                             /**< DP_GETPROPERTY_CRC_INFO                */
} DP_GetPropertyParamsType;


/*!
* \b DP_PixelClk_Info
*
*  Defines the structure for pixel clock divider info
*/
typedef struct
{
  uint32                           uPixelClkMNDInputMhz;               /* Input frequency to MND RCG block          */
  uint32                           uPixelClk_M;                        /* M value for Pixel clock to MMSS_CC        */
  uint32                           uPixelClk_N;                        /* N value for Pixel clock to MMSS_CC        */
  uint32                           uPixelClk_2D;                       /* 2D Value for MMSS_CC                      */
  uint32                           uPixelDivider;                      /* divider for pixel clock to MMSS_CC        */
  uint32                           uSWMvid;                            /* SWMvid value to DP Sink                   */
  uint32                           uSWNvid;                            /* SWMvid value to DP Sink                   */
  double                           dActualPixelClkMHz;                 /* Actual pixel clock value with SSC         */
  double                           dActualLinkClkMHz;                  /* Actual Link Clock value with SSC          */
} DP_PixelClk_Info;

/*!
* \b DP_LTTPR_DeviceInfoType
*
*  Defines the structure for LTTPR Device-specific identifier information 
*/
typedef struct
{
  uint8                            aIEEEOUI[DP_IEEE_OUI_LEN];               /**< IEEE OUI Identifier of the device   */
  uint8                            aDeviceString[DP_DEVICE_ID_STRING_LEN];  /**< Identifier string of the device     */
} DP_LTTPR_DeviceInfoType;

#endif //_DP_TYPES_H_
