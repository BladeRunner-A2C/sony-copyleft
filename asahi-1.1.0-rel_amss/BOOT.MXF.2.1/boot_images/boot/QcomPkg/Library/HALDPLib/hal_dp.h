#ifndef _HAL_DP_H_
#define _HAL_DP_H_
/*! \file */

/*=============================================================================
 
  File: hal_dp.h
 
  Header file for DP controller hardware functionality 
   
  Copyright (c) 2016-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/



/*=====================================================================================================================
*                         INCLUDE FILES
=====================================================================================================================*/
#include "hal_mdss.h"


/* --------------------------------------------------------------------------------------------------------------------
Enumerated types
---------------------------------------------------------------------------------------------------------------------*/

/*!
 * \enum DP_DeviceIDType
 *
 * The \b DP_DeviceIDType lists all supported DP device IDs
 *
 */
 typedef enum 
{
  DP_DEVICE_ID_NONE                             = 0x00000000,
  DP_DEVICE_ID_ALT_MODE_0,                                             /**< DP over Type-C Port 0 */
  DP_DEVICE_ID_ALT_MODE_1,                                             /**< DP over Type-C Port 1 */
  DP_DEVICE_ID_ALT_MODE_2,                                             /**< DP over Type-C Port 2 */ 
  DP_DEVICE_ID_EDP,                                                    /**< DP 3 / EDP Port       */
  DP_DEVICE_MAX,
  DP_DEVICE_FORCE_32BIT                         = 0x7FFFFFFF
} DP_DeviceIDType;

/*!
* \enum DP_DeviceModeType
*
* The \b DP_DeviceModeType lists all supported DP device mode types
*
*/
typedef enum
{
  DP_DEVICE_MODETYPE_DP                        = 0x00000000,            /**< DP                    */
  DP_DEVICE_MODETYPE_EDP,                                               /**< eDP                   */
  DP_DEVICE_MODETYPE_ALTMODE,                                           /**< DP over Type-C        */
  DP_DEVICE_MODETYPE_TUNNELING,                                         /**< USB4 DP Tunneling     */
  DP_DEVICE_MODETYPE_MAX,
  DP_DEVICE_MODETYPE_FORCE_32BIT               = 0x7FFFFFFF
}DP_DeviceModeType;


/*!
 * \enum DP_StreamIDType
 *
 * The \b DP_StreamIDType provides a list of supported streams on a single DP port
 *
 */
typedef enum
{
   DP_STREAM_ID_SST                             = 0x00000000,          /**< Single Stream Transport */ 
   DP_STREAM_ID_MST0                            = DP_STREAM_ID_SST,    /**< Multi Stream Transport Stream 0 */ 
   DP_STREAM_ID_MST1,                                                  /**< Multi Stream Transport Stream 1 */ 
   DP_STREAM_ID_MAX,
   DP_STREAM_ID_32BIT                           = 0x7FFFFFFF,
} DP_StreamIDType;

/*!
 * \enum DP_ControllerIDType
 *
 * The \b DP_ControllerIDType lists all supported DP controllers
 *
 */
typedef enum
{
  DP_CONTROLLER_ID_NONE                         = 0x00000000,
  DP_CONTROLLER_ID_DP_0,                                               /**< DP Controller 0 */ 
  DP_CONTROLLER_ID_DP_1,                                               /**< DP Controller 1 */
  DP_CONTROLLER_ID_DP_2,                                               /**< DP Controller 2 */ 
  DP_CONTROLLER_ID_DP_3,                                               /**< DP Controller 3 */
  DP_CONTROLLER_ID_MAX,
  DP_CONTROLLER_FORCE_32BIT                     = 0x7FFFFFFF
} DP_ControllerIDType;

/*!
 * \enum HAL_DP_InterruptType
 *
 * The \b HAL_DP_InterruptType provides the possible configuration/status read interrupts for DP controller and DP 
 * PHY.
 *
 */
typedef enum
{
   HAL_DP_INTR_TYPE_NONE                           = 0x00000000,
   HAL_DP_INTR_TYPE_HPD                            = HAL_MDSS_BIT(1),  /**< Indicates Sink has request via HDP pin  */
   HAL_DP_INTR_TYPE_AUX_I2C_DONE                   = HAL_MDSS_BIT(2),  /**< Indicates AUX/I2C transaction is done   */
   HAL_DP_INTR_TYPE_WRONG_ADDRESS                  = HAL_MDSS_BIT(3),  /**< Indicates wrong AUX address was given   */
   HAL_DP_INTR_TYPE_CONSECUTIVE_TIMEOUT            = HAL_MDSS_BIT(4),  /**< AUX/I2C has timed out consecutively     */
   HAL_DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER         = HAL_MDSS_BIT(5),  /**< AUX/I2C has NACK/DEFER consecutively    */
   HAL_DP_INTR_TYPE_WRONG_READDATA_COUNT           = HAL_MDSS_BIT(6),  /**< # of read data bytes is not expected    */
   HAL_DP_INTR_TYPE_AUX_NACK_DURING_I2C            = HAL_MDSS_BIT(7),  /**< AUX NACK`ed during an I2C transaction   */
   HAL_DP_INTR_TYPE_AUX_DEFER_DURING_I2C           = HAL_MDSS_BIT(8),  /**< AUX DEFER`ed during an I2C transaction  */
   HAL_DP_INTR_TYPE_PLL_UNLOCK_DET                 = HAL_MDSS_BIT(9),  /**< Indicates PLL in DP PHY has unlocked    */
   HAL_DP_INTR_TYPE_DPPHY_AUX_ERROR                = HAL_MDSS_BIT(10), /**< Indicates DPPHY AUX detected an error   */
   HAL_DP_INTR_TYPE_READY_FOR_VIDEO                = HAL_MDSS_BIT(11), /**< DP HW is ready to receive video         */
   HAL_DP_INTR_TYPE_IDLE_PATTERNS_SENT             = HAL_MDSS_BIT(12), /**< Idle patterns are sent after push idle  */
   HAL_DP_INTR_TYPE_FRAME_END                      = HAL_MDSS_BIT(13), /**< Indicate end of a frame                 */
   HAL_DP_INTR_TYPE_CRC_UPDATED                    = HAL_MDSS_BIT(14), /**< Indicate MISR registers have new values */
   HAL_DP_INTR_TYPE_AUX_RX_STOP_ERR                = HAL_MDSS_BIT(15), /**< Indicate STOP pattern error on AUX RX   */
   HAL_DP_INTR_TYPE_AUX_RX_DEC_ERR                 = HAL_MDSS_BIT(16), /**< Indicate Data decode error on AUX RX.   */
   HAL_DP_INTR_TYPE_AUX_RX_SYNC_ERR                = HAL_MDSS_BIT(17), /**< Indicate SYNC pattern error on AUX RX   */
   HAL_DP_INTR_TYPE_AUX_RX_ALIGN_ERR               = HAL_MDSS_BIT(18), /**< RX received less than 8 bits data       */
   HAL_DP_INTR_TYPE_AUX_TX_REQ_ERR                 = HAL_MDSS_BIT(19), /**< REQ. signal is late on TX.              */
   HAL_DP_INTR_TYPE_ENCRYPTION_READY               = HAL_MDSS_BIT(20), /**< Encryption ready interrupt.             */
   HAL_DP_INTR_TYPE_ENCRYPTION_NOT_READY           = HAL_MDSS_BIT(21), /**< Encryption not ready interrupt.         */
   HAL_DP_INTR_TYPE_AUTH_SUCCESS                   = HAL_MDSS_BIT(22), /**< HDCP1.3 authentication ready.           */
   HAL_DP_INTR_TYPE_AUTH_FAIL                      = HAL_MDSS_BIT(23), /**< HDCP1.3 authentication failed.          */
   HAL_DP_INTR_TYPE_HPD_PLUG_INT                   = HAL_MDSS_BIT(24), /**< Indicate cable plug event               */
   HAL_DP_INTR_TYPE_HPD_IRQ_INT                    = HAL_MDSS_BIT(25), /**< This event is a Sink to Source interrupt
                                                                            request while the devices are deemed to 
                                                                            be connected.                           */
   HAL_DP_INTR_TYPE_HPD_REPLUG_INT                 = HAL_MDSS_BIT(26), /**< This event is a Sink to Source 'Replug'
                                                                            notification generated to inform the 
                                                                            Source that a broader change has occurred 
                                                                            in the Sink such that the Source needs to 
                                                                            start at the initial connect capability 
                                                                            check of the Sink                       */
   HAL_DP_INTR_TYPE_HPD_UNPLUG_INT                 = HAL_MDSS_BIT(27), /**< Indicate cable unplug event             */
   HAL_DP_INTR_TYPE_SST_FIFO_UNDERFLOW             = HAL_MDSS_BIT(28), /**< SST Fifo underflow event                */
   HAL_DP_INTR_TYPE_FRAME_END_STREAM1              = HAL_MDSS_BIT(29), /**< Indicate end of a frame for stream 1    */
   HAL_DP_INTR_TYPE_MAX,
   HAL_DP_INTR_TYPE_FORCE_32BIT                    = 0x7FFFFFFF
} HAL_DP_InterruptType;


/*!
 * \enum HAL_DP_PSRInterruptType
 *
 * The \b HAL_DP_PSRInterruptType provides the possible interrupts particular to DP PSR feature
 *
 */
typedef enum
{
   HAL_DP_INTR_TYPE_PSR_NONE                       = 0x00000000,
   HAL_DP_INTR_TYPE_PSR_UPDATE                     = 0x00000001,
   HAL_DP_INTR_TYPE_PSR_CAPTURE                    = 0x00000002,  
   HAL_DP_INTR_TYPE_PSR_EXIT                       = 0x00000004,  
   HAL_DP_INTR_TYPE_PSR_UPDATE_ERR                 = 0x00000008,      
   HAL_DP_INTR_TYPE_PSR_WAKE_ERR                   = 0x00000010,  
   HAL_DP_INTR_TYPE_PSR_FORCE_32BIT                = 0x7FFFFFFF
} HAL_DP_PSRInterruptType;

/*!
 * \enum HAL_DP_LinkCommandType
 *
 * The \b HAL_DP_LinkCommandType defines the command to the main link Finite State Machine states, 
 *
 */
typedef enum
{
   HAL_DP_LINKCOMMAND_TYPE_NONE                    = 0x00000000,
   HAL_DP_LINKCOMMAND_TYPE_ENABLE,                                     /**< Enable DP Main link Controller          */
   HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN1,                              /**< Trigger main link to send train pattern1*/
   HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN2,                              /**< Trigger main link to send train pattern2*/
   HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN3,                              /**< Trigger main link to send train pattern3*/
   HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN4,                              /**< Trigger main link to send train pattern4*/
   HAL_DP_LINKCOMMAND_TYPE_SEND_SYMBOL_ERM,                            /**< Send symbol error rate measure  pattern */
   HAL_DP_LINKCOMMAND_TYPE_SEND_PRBS7,                                 /**< Trigger main link to send PRBS7 pattern */
   HAL_DP_LINKCOMMAND_TYPE_SEND_CUSTOM_PATTERN,                        /**< Trigger to send 80bit custom pattern    */
   HAL_DP_LINKCOMMAND_TYPE_SEND_VIDEO,                                 /**< Trigger main link to send video data    */
   HAL_DP_LINKCOMMAND_TYPE_PUSH_IDLE,                                  /**< Trigger to send push for idle state     */

   HAL_DP_LINKCOMMAND_TYPE_DISABLE,                                    /**< Disable DP Main link Controller         */
   HAL_DP_LINKCOMMAND_TYPE_MAX,
   HAL_DP_LINKCOMMAND_TYPE_FORCE_32BIT             = 0x7FFFFFFF
} HAL_DP_LinkCommandType;

/*!
 * \enum HAL_DP_LinkStatusType
 *
 * The \b HAL_DP_LinkStatusType defines status of the main link for SW to query.
 *
 */
typedef enum
{
   HAL_DP_LINKSTATUS_TYPE_NONE                     = 0x00000000,
   HAL_DP_LINKSTATUS_TYPE_ENABLED                  = HAL_MDSS_BIT(0),  /**< DP Main link Controller is enabled      */
   HAL_DP_LINKSTATUS_TYPE_READY_FOR_VIDEO          = HAL_MDSS_BIT(1),  /**< HW is ready to accept video data        */
   HAL_DP_LINKSTATUS_TYPE_IDLE_PATTERNS_SENT       = HAL_MDSS_BIT(2),  /**< Push for Idle Pattern has been sent     */
   HAL_DP_LINKSTATUS_TYPE_READY_STATE              = HAL_MDSS_BIT(3),  /**< HW is up and ready for command          */
   HAL_DP_LINKSTATUS_TYPE_SENDING_PATTERN1         = HAL_MDSS_BIT(4),  /**< HW is sending link training pattern 1   */
   HAL_DP_LINKSTATUS_TYPE_SENDING_PATTERN2         = HAL_MDSS_BIT(5),  /**< HW is sending link training pattern 2   */
   HAL_DP_LINKSTATUS_TYPE_SENDING_PATTERN3         = HAL_MDSS_BIT(6),  /**< HW is sending link training pattern 3   */
   HAL_DP_LINKSTATUS_TYPE_SENDING_PATTERN4         = HAL_MDSS_BIT(7),  /**< HW is sending link training pattern 3   */   
   HAL_DP_LINKSTATUS_TYPE_SENDING_SYMBOL_ERM       = HAL_MDSS_BIT(8),  /**< HW is sending sending symbol error rate measure pattern */
   HAL_DP_LINKSTATUS_TYPE_SENDING_PRBS7            = HAL_MDSS_BIT(9),  /**< HW is sending PRBS7 pattern 3           */
   HAL_DP_LINKSTATUS_TYPE_SENDING_CUSTOM_PATTERN   = HAL_MDSS_BIT(10), /**< HW is sending 80bit custom pattern      */
   HAL_DP_LINKSTATUS_TYPE_SENDING_IDLE_PATTERN     = HAL_MDSS_BIT(11), /**< Sending idle pattern after video enabled*/
   HAL_DP_LINKSTATUS_TYPE_SENDING_BS               = HAL_MDSS_BIT(12), /**< HW is sending blank sequence            */
   HAL_DP_LINKSTATUS_TYPE_SENDING_MSA              = HAL_MDSS_BIT(13), /**< HW is sending Main Stream Attribute     */
   HAL_DP_LINKSTATUS_TYPE_SENDING_VSC              = HAL_MDSS_BIT(14), /**< HW is sending Video Stream Config       */
   HAL_DP_LINKSTATUS_TYPE_SENDING_ACTIVE18BPP      = HAL_MDSS_BIT(15), /**< HW is sending 18bpp Video data          */
   HAL_DP_LINKSTATUS_TYPE_SENDING_ACTIVE24BPP      = HAL_MDSS_BIT(16), /**< HW is sending 24bpp Video data          */ 
   HAL_DP_LINKSTATUS_TYPE_SENDING_IDLE_PATTERN2    = HAL_MDSS_BIT(17), /**< HW is sending push for idle pattern     */
   HAL_DP_LINKSTATUS_TYPE_DISABLED                 = HAL_MDSS_BIT(18), /**< DP Main link Controller is disabled     */
   HAL_DP_LINKSTATUS_TYPE_MAX,
   HAL_DP_LINKSTATUS_TYPE_FORCE_32BIT              = 0x7FFFFFFF
} HAL_DP_LinkStatusType;

/*!
 * \enum HAL_DP_AUXStatusType
 *
 * The \b HAL_DP_AUXStatusType defines status of the AUX for SW to query.   
 *
 */
typedef enum
{
   HAL_DP_AUXSTATUS_TYPE_NONE                      = 0x00000000,
   HAL_DP_AUXSTATUS_TYPE_AUX_I2C_DONE              = HAL_MDSS_BIT(0),  /**< Indicates AUX/I2C transaction is done   */
   HAL_DP_AUXSTATUS_TYPE_WRONG_ADDRESS             = HAL_MDSS_BIT(1),  /**< Indicates wrong AUX address was given   */
   HAL_DP_AUXSTATUS_TYPE_CONSECUTIVE_TIMEOUT       = HAL_MDSS_BIT(2),  /**< AUX/I2C has timed out consecutively     */
   HAL_DP_AUXSTATUS_TYPE_CONSECUTIVE_NACK_DEFER    = HAL_MDSS_BIT(3),  /**< AUX/I2C has NACK/DEFER consecutively    */
   HAL_DP_AUXSTATUS_TYPE_WRONG_READDATA_COUNT      = HAL_MDSS_BIT(4),  /**< # of read data bytes is not expected    */
   HAL_DP_AUXSTATUS_TYPE_AUX_NACK_DURING_I2C       = HAL_MDSS_BIT(5),  /**< AUX NACK`ed during an I2C transaction   */
   HAL_DP_AUXSTATUS_TYPE_AUX_DEFER_DURING_I2C      = HAL_MDSS_BIT(6),  /**< AUX DEFER`ed during an I2C transaction  */
   HAL_DP_AUXSTATUS_TYPE_MAX,
   HAL_DP_AUXSTATUS_TYPE_FORCE_32BIT               = 0x7FFFFFFF
}HAL_DP_AUXStatusType;

/*!
* \enum HAL_DP_AUXFlags
*
* The \b HAL_DP_AUXFlags defines flags for AUX read/write.
*
*/
typedef enum
{
  HAL_DP_AUXFLAGS_NONE                  = 0x00000000,
  HAL_DP_AUXFLAGS_READ                  = HAL_MDSS_BIT(0),              /**< Indicates this is a AUX read operation   */
  HAL_DP_AUXFLAGS_FORCE_32BIT           = 0x7FFFFFFF
} HAL_DP_AUXFlagType;

/*!
 * \enum HAL_DP_AuxTransactionModeType
 *
 * The \b HAL_DP_AuxTransactionModeType defines types of AUX Transaction.
 *
 */
typedef enum
{
   HAL_DP_AUX_TRANSACTION_MODE_NONE               = 0x00000000,
   HAL_DP_AUX_TRANSACTION_MODE_NATIVE,                                /**< Native AUX Transaction       */
   HAL_DP_AUX_TRANSACTION_MODE_I2C,                                   /**< I2C over AUX Transaction     */
   HAL_DP_AUX_TRANSACTION_MODE_MAX,
   HAL_DP_AUX_TRANSACTION_MODE_FORCE_32BIT        = 0x7FFFFFFF
} HAL_DP_AuxTransactionModeType;

/*!
 * \enum HAL_DP_LaneMapType
 *
 * The \b HAL_DP_LaneMapType defines physical lane and logic lane mapping.   
 *
 */
typedef enum
{
   HAL_DP_LANEMAP_TYPE_NONE                        = 0x00000000,
   HAL_DP_LANEMAP_TYPE_0123,                                           /**< Physical lane map to logic lane as 0123 */
   HAL_DP_LANEMAP_TYPE_0132,                                           /**< Physical lane map to logic lane as 0132 */
   HAL_DP_LANEMAP_TYPE_0213,                                           /**< Physical lane map to logic lane as 0213 */
   HAL_DP_LANEMAP_TYPE_0231,                                           /**< Physical lane map to logic lane as 0231 */
   HAL_DP_LANEMAP_TYPE_0312,                                           /**< Physical lane map to logic lane as 0312 */
   HAL_DP_LANEMAP_TYPE_0321,                                           /**< Physical lane map to logic lane as 0321 */
   HAL_DP_LANEMAP_TYPE_1023,                                           /**< Physical lane map to logic lane as 1023 */
   HAL_DP_LANEMAP_TYPE_1032,                                           /**< Physical lane map to logic lane as 1032 */
   HAL_DP_LANEMAP_TYPE_1203,                                           /**< Physical lane map to logic lane as 1203 */
   HAL_DP_LANEMAP_TYPE_1230,                                           /**< Physical lane map to logic lane as 1230 */
   HAL_DP_LANEMAP_TYPE_1302,                                           /**< Physical lane map to logic lane as 1302 */
   HAL_DP_LANEMAP_TYPE_1320,                                           /**< Physical lane map to logic lane as 1320 */
   HAL_DP_LANEMAP_TYPE_2013,                                           /**< Physical lane map to logic lane as 2013 */
   HAL_DP_LANEMAP_TYPE_2031,                                           /**< Physical lane map to logic lane as 2031 */
   HAL_DP_LANEMAP_TYPE_2103,                                           /**< Physical lane map to logic lane as 2103 */
   HAL_DP_LANEMAP_TYPE_2130,                                           /**< Physical lane map to logic lane as 2130 */
   HAL_DP_LANEMAP_TYPE_2301,                                           /**< Physical lane map to logic lane as 2301 */
   HAL_DP_LANEMAP_TYPE_2310,                                           /**< Physical lane map to logic lane as 2310 */
   HAL_DP_LANEMAP_TYPE_3012,                                           /**< Physical lane map to logic lane as 3012 */
   HAL_DP_LANEMAP_TYPE_3021,                                           /**< Physical lane map to logic lane as 3021 */
   HAL_DP_LANEMAP_TYPE_3102,                                           /**< Physical lane map to logic lane as 3102 */
   HAL_DP_LANEMAP_TYPE_3120,                                           /**< Physical lane map to logic lane as 3120 */
   HAL_DP_LANEMAP_TYPE_3201,                                           /**< Physical lane map to logic lane as 3201 */
   HAL_DP_LANEMAP_TYPE_3210,                                           /**< Physical lane map to logic lane as 3210 */
   HAL_DP_LANEMAP_TYPE_MAX,
   HAL_DP_LANEMAP_TYPE_FORCE_32BIT                 = 0x7FFFFFFF
} HAL_DP_LaneMapType;

/*!
 * \enum HAL_DP_RGBMapType
 *
 * The \b HAL_DP_RGBMapType defines RGB component mapping.   
 *
 */
typedef enum
{
   HAL_DP_PIXELFORMAT_TYPE_RGB                         = 0x0,
   HAL_DP_PIXELFORMAT_TYPE_YUV420                      = 0x1,         
   HAL_DP_PIXELFORMAT_TYPE_YUV422                      = 0x2,
   HAL_DP_PIXELFORMAT_TYPE_MAX,
   HAL_DP_PIXELFORMAT_TYPE_FORCE_32BIT                  = 0x7FFFFFFF
} HAL_DP_PixelFormatType;

/*!
 * \enum HAL_DP_RGBMapType
 *
 * The \b HAL_DP_RGBMapType defines RGB component mapping.   
 *
 */
typedef enum
{
   HAL_DP_RGBMAP_TYPE_NONE                         = 0x00000000,
   HAL_DP_RGBMAP_TYPE_RGB,                                             /**< Color component order is RGB            */
   HAL_DP_RGBMAP_TYPE_RBG,                                             /**< Color component order is RBG            */
   HAL_DP_RGBMAP_TYPE_GBR,                                             /**< Color component order is GBR            */
   HAL_DP_RGBMAP_TYPE_GRB,                                             /**< Color component order is GRB            */
   HAL_DP_RGBMAP_TYPE_BGR,                                             /**< Color component order is BGR            */
   HAL_DP_RGBMAP_TYPE_BRG,                                             /**< Color component order is BRG            */
   HAL_DP_RGBMAP_TYPE_MAX,
   HAL_DP_RGBMAP_TYPE_FORCE_32BIT                  = 0x7FFFFFFF
} HAL_DP_RGBMapType;

/*!
 * \enum HAL_DP_PixelEncodingType
 *
 * The \b HAL_DP_PixelEncodingType defines pixel encoding type.
 * The pixel encoding type is used for VSC SDP Data Byte 16, bits 4-7.
 *
 */
typedef enum
{
  HAL_DP_PIXEL_ENCODING_RGB               = 0x0000000,                 /**< RGB pixel encoding         */
  HAL_DP_PIXEL_ENCODING_YCBCR_444         = 0x0000001,                 /**< YCbCr 444 pixel encoding   */
  HAL_DP_PIXEL_ENCODING_YCBCR_422         = 0x0000002,                 /**< YCbCr 422 pixel encoding   */
  HAL_DP_PIXEL_ENCODING_YCBCR_420         = 0x0000003,                 /**< YCbCr 420 pixel encoding   */
  HAL_DP_PIXEL_ENCODING_Y_ONLY            = 0x0000004,                 /**< Only Y pixel encoding      */
  HAL_DP_PIXEL_ENCODING_RAW               = 0x0000005,                 /**< RAW pixel encoding         */
  HAL_DP_PIXEL_ENCODING_MAX,
  HAL_DP_PIXEL_ENCODING_FORCE_32BIT       = 0x7FFFFFFF
} HAL_DP_PixelEncodingType;

/*!
 * \enum HAL_DP_ColorimetryFormatType
 *
 * The \b HAL_DP_ColorimetryFormatType defines colorimetry format type.
 * The colorimetry format is used for VSC SDP Data Byte 16, bits 0-3.
 *
 */
typedef enum
{
  HAL_DP_COLORIMETRY_FORMAT_SRGB           = 0x0000000,                /**< Colorimetry format sRGB    */
  HAL_DP_COLORIMETRY_FORMAT_BT2020_RGB     = 0x0000006,                /**< Colorimetry format BT.2020 */
  HAL_DP_COLORIMETRY_FORMAT_MAX,
  HAL_DP_COLORIMETRY_FORMAT_FORCE_32BIT    = 0x7FFFFFFF
} HAL_DP_ColorimetryFormatType;

/*!
 * \enum HAL_DP_HDR10DynamincRange
 *
 * The \b HAL_DP_HDR10DynamincRange defines dynamic range feature.
 *
*/
typedef enum
{
  HAL_DP_DYNAMIC_RANGE_VESA,                                           /**< HDR10 Dynamic Range VESA */
  HAL_DP_DYNAMIC_RANGE_CEA,                                            /**< HDR10 Dynamic Range SEA  */
  HAL_DP_DYNAMIC_RANGE_FORCE_32BIT         = 0x7FFFFFFF
} HAL_DP_HDR10DynamincRange;

/*!
 * \enum HAL_DP_HDR10ContentType
 *
 * The \b HAL_DP_HDR10ContentType defines HDR Content Type.
 *
 */
typedef enum
{
  HAL_DP_CONTENT_NOT_DEFINED,                                          /**< HDR10 Content Type Not Defined  */
  HAL_DP_CONTENT_GRAPHICS,                                             /**< HDR10 Content Type Graphics     */
  HAL_DP_CONTENT_PHOTO,                                                /**< HDR10 Content Type Photo        */
  HAL_DP_CONTENT_VIDEO,                                                /**< HDR10 Content Type Video        */
  HAL_DP_CONTENT_GAME,                                                 /**< HDR10 Content Type Game         */
  HAL_DP_CONTENT_FORCE_32BIT               = 0x7FFFFFFF
} HAL_DP_HDR10ContentType;

/*!
 * \enum HAL_DP_ModuleType
 *
 * The \b HAL_DP_ModuleType defines HW module inside DP controller.
 *
 */
typedef enum
{
   HAL_DP_MODULE_TYPE_NONE                         = 0x00000000,
   HAL_DP_MODULE_TYPE_MAINLINK                     = HAL_MDSS_BIT(0),  /**< HW module: mainlink                     */
   HAL_DP_MODULE_TYPE_AUX                          = HAL_MDSS_BIT(1),  /**< HW module: AUX                          */
   HAL_DP_MODULE_TYPE_PHY                          = HAL_MDSS_BIT(2),  /**< HW module: DP PHY                       */
   HAL_DP_MODULE_TYPE_PLL                          = HAL_MDSS_BIT(3),  /**< HW module: DP PLL                       */
   HAL_DP_MODULE_TYPE_CONTROLLER                   = HAL_MDSS_BIT(4),  /**< HW module: DP Controller                */
   HAL_DP_MODULE_TYPE_MAX,
   HAL_DP_MODULE_TYPE_FORCE_32BIT                  = 0x7FFFFFFF
} HAL_DP_ModuleType;


/*!
 * \enum HAL_DP_PropertyType
 *
 * The \b HAL_DP_PropertyType defines controller property ID to be set.
 *
 */
typedef enum
{
   HAL_DP_PROPERTY_TYPE_NONE                               = 0x00000000,
   HAL_DP_PROPERTY_TYPE_MAX,
   HAL_DP_PROPERTY_TYPE_FORCE_32BIT                        = 0x7FFFFFFF
} HAL_DP_PropertyType;

/*!
 * \enum HAL_DP_PllConfigFlagType
 *
 *
 * \brief
 *     Configuration flags for DP PLL.
 *
 */
typedef enum _HAL_DP_PllConfigFlagType
{
   HAL_DP_PLLCONFIG_FLAG_NONE                     = 0x00000000,
   HAL_DP_PLLCONFIG_FLAG_SVS                      = HAL_MDSS_BIT(1),   /**< enable PLL SVS mode                      */
   HAL_DP_PLLCONFIG_FLAG_SSC                      = HAL_MDSS_BIT(2),   /**< enable PLL SSC mode                      */
   HAL_DP_PLLCONFIG_FLAG_DPUSB_CONCURRENCY        = HAL_MDSS_BIT(3),   /**< DP/USB concurrency, sharing PHY with USB */
   HAL_DP_PLLCONFIG_FLAG_PLL                      = HAL_MDSS_BIT(4),   /**< Configure PLL only                       */
   HAL_DP_PLLCONFIG_FLAG_MAX                      = HAL_MDSS_BIT(30),
   HAL_DP_PLLCONFIG_FLAG_FORCE_32_BIT             = 0x7FFFFFFF
} HAL_DP_PllConfigFlagType;

/*!
 * \enum HAL_DP_PSR_CmdType
 *
 * The \b HAL_DP_PSR_CmdType defines PSR commands
 *
 */
typedef enum
{
  HAL_DP_PSR_CMD_NONE                = 0,
  HAL_DP_PSR_CMD_ENTER               = HAL_MDSS_BIT(0),
  HAL_DP_PSR_CMD_EXIT                = HAL_MDSS_BIT(1),
  HAL_DP_PSR_CMD_UPDATE              = HAL_MDSS_BIT(2),
  HAL_DP_PSR_CMD_BURST_UPDATE        = HAL_MDSS_BIT(3),
  HAL_DP_PSR_CMD_32_BIT              = 0x7FFFFFFF
} HAL_DP_PSR_CmdType;

/*!
* \b DP_AudioChannelNumType
*
* The various audio channel number for DP Display
*/
typedef enum
{
  DP_AUDIO_CHANNEL_NONE         = 0x0,
  DP_AUDIO_CHANNEL_2            = 0x1,
  DP_AUDIO_CHANNEL_4            = 0x2,
  DP_AUDIO_CHANNEL_6            = 0x4,
  DP_AUDIO_CHANNEL_8            = 0x8,
  DP_AUDIO_CHANNEL_MAX,
  DP_AUDIO_CHANNEL_FORCE_32BIT  = 0x7FFFFFFF
} DP_AudioChannelType;

/*!
* \b DP_AudioFormatType
*
*  Defines the audio formats supported by the DP display
*/
typedef enum
{
  DP_AUDIO_FORMAT_RESERVED = 0,                  /* Reserved for future */
  DP_AUDIO_FORMAT_LPCM,                          /* Audio codec type Linear PCM */
  DP_AUDIO_FORMAT_AC3,                           /* Audio codec type AC3 */
  DP_AUDIO_FORMAT_MPEG1_LAYER1_AND_2,            /* Audio codec type MPEG1 Layer1 and 2 */
  DP_AUDIO_FORMAT_MP3,                           /* Audio codec type MP3*/
  DP_AUDIO_FORMAT_MPEG2,                         /* Audio codec type MPEG2 */
  DP_AUDIO_FORMAT_AAC,                           /* Audio codec type AAC */
  DP_AUDIO_FORMAT_DTS,                           /* Audio codec type DTS */
  DP_AUDIO_FORMAT_ATRAC,                         /* Audio codec type ATRAC */
  DP_AUDIO_FORMAT_ONE_BIT_AUDIO,                 /* Audio codec type 1 bit audio */
  DP_AUDIO_FORMAT_DOLBY_DIGITAL_PLUS,            /* Audio codec type Dolby Digital+ */
  DP_AUDIO_FORMAT_DTS_HD,                        /* Audio codec type DTS HD*/
  DP_AUDIO_FORMAT_MAT,                           /* Audio codec type MAT */
  DP_AUDIO_FORMAT_DST,                           /* Audio codec type DST */
  DP_AUDIO_FORMAT_WMA_PRO,                       /* Audio codec type WMA PRO */
  DP_AUDIO_FORMAT_RESERVED1,                     /* Reserved for future */
  DP_AUDIO_FORMAT_MAX,
  DP_AUDIO_FORMAT_FORCE_32BIT = 0x7FFFFFFF
} DP_AudioFormatType;

/*!
* \b DP_AudioSampleRateType
*
* The various audio sample rate for DP Display
*/
typedef enum
{
  DP_AUDIO_SAMPLE_RATE_NONE         = 0x0,
  DP_AUDIO_SAMPLE_RATE_32KHZ        = 0x1,
  DP_AUDIO_SAMPLE_RATE_44_1KHZ      = 0x2,
  DP_AUDIO_SAMPLE_RATE_48KHZ        = 0x4,
  DP_AUDIO_SAMPLE_RATE_88_2KHZ      = 0x8,
  DP_AUDIO_SAMPLE_RATE_96KHZ        = 0x10,
  DP_AUDIO_SAMPLE_RATE_176_4KHZ     = 0x20,
  DP_AUDIO_SAMPLE_RATE_192KHZ       = 0x40,
  DP_AUDIO_SAMPLE_RATE_MAX,
  DP_AUDIO_SAMPLE_RATE_FORCE_32BIT  = 0x7FFFFFFF
} DP_AudioSampleRateType;

/*!
* \b DP_AudioSampleBitDepthType
*
* The various audio sample bit depth for DP Display
*/
typedef enum
{
  DP_AUDIO_BIT_DEPTH_NONE   = 0x0,              /* No Audio Bit Depth */
  DP_AUDIO_BIT_DEPTH_16_BIT = 0x1,              /* Audio Bit Depth 16bit per sample*/
  DP_AUDIO_BIT_DEPTH_20_BIT = 0x2,              /* Audio Bit Depth 20bit per sample*/
  DP_AUDIO_BIT_DEPTH_24_BIT = 0x4,              /* Audio Bit Depth 24bit per sample*/
  DP_AUDIO_BIT_DEPTH_MAX,
  DP_AUDIO_BIT_DEPTH_FORCE_32BIT = 0x7FFFFFFF
} DP_AudioSampleBitDepthType;


/*!
* \b DP_AudioChannelAllocType
*
*  Defines the mapping between the audio channel and sink device speakers
*
*  FL  - Front Left
*  FC  - Front Center
*  FR  - Front Right
*  FLC - Front Left Center
*  FRC - Front Right Center
*  RL  - Rear Left
*  RC  - Rear Center
*  RR  - Rear Right
*  RLC - Rear Left Center
*  RRC - Rear Right Center
*  LFE - Low Frequencey Effect
*/
typedef enum
{
  DP_AUDIO_CHANNEL_ALLOC_CODE_0 = 0x0, /* Allocate to FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_1,        /* Allocate to LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_2,        /* Allocate to FC, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_3,        /* Allocate to FC, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_4,        /* Allocate to RC, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_5,        /* Allocate to RC, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_6,        /* Allocate to RC, FC, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_7,        /* Allocate to RC, FC, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_8,        /* Allocate to RR, RL, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_9,        /* Allocate to RR, RL, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_10,       /* Allocate to RR, RL, FC, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_11,       /* Allocate to RR, RL, FC, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_12,       /* Allocate to RC, RR, RL, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_13,       /* Allocate to RC, RR, RL, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_14,       /* Allocate to RC, RR, RL, FC, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_15,       /* Allocate to RC, RR, RL, FC, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_16,       /* Allocate to RRC, RLC, RR, RL, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_17,       /* Allocate to RRC, RLC, RR, RL, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_18,       /* Allocate to RRC, RLC, RR, RL, FC, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_19,       /* Allocate to RRC, RLC, RR, RL, FC, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_20,       /* Allocate to FRC, FLC, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_21,       /* Allocate to FRC, FLC, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_22,       /* Allocate to FRC, FLC, FC, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_23,       /* Allocate to FRC, FLC, FC, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_24,       /* Allocate to FRC, FLC, RC, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_25,       /* Allocate to FRC, FLC, RC, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_26,       /* Allocate to FRC, FLC, RC, FC, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_27,       /* Allocate to FRC, FLC, RC, FC, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_28,       /* Allocate to FRC, FLC, RR, RL, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_29,       /* Allocate to FRC, FLC, RR, RL, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_30,       /* Allocate to FRC, FLC, RR, RL, FC, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_31,       /* Allocate to FRC, FLC, RR, RL, FC, LFE, FR, FL speakers */
  DP_AUDIO_CHANNEL_ALLOC_CODE_MAX,
  DP_AUDIO_CHANNEL_ALLOC_CODE_FORCE_32BIT = 0x7FFFFFFF
} DP_AudioChannelAllocType;

/*!
* \b DP_AudioLevelShiftType
*
*  Defines the audio attenuation level to be shifted by the sink device
*/
typedef enum
{
  DP_AUDIO_LEVEL_SHIFT_0DB = 0x0,  /* 0 Decibel */
  DP_AUDIO_LEVEL_SHIFT_1DB,          /* 1 Decibel */
  DP_AUDIO_LEVEL_SHIFT_2DB,          /* 2 Decibel */
  DP_AUDIO_LEVEL_SHIFT_3DB,          /* 3 Decibel */
  DP_AUDIO_LEVEL_SHIFT_4DB,          /* 4 Decibel */
  DP_AUDIO_LEVEL_SHIFT_5DB,          /* 5 Decibel */
  DP_AUDIO_LEVEL_SHIFT_6DB,          /* 6 Decibel */
  DP_AUDIO_LEVEL_SHIFT_7DB,          /* 7 Decibel */
  DP_AUDIO_LEVEL_SHIFT_8DB,          /* 8 Decibel */
  DP_AUDIO_LEVEL_SHIFT_9DB,          /* 9 Decibel */
  DP_AUDIO_LEVEL_SHIFT_10DB,         /* 10 Decibel */
  DP_AUDIO_LEVEL_SHIFT_11DB,         /* 11 Decibel */
  DP_AUDIO_LEVEL_SHIFT_12DB,         /* 12 Decibel */
  DP_AUDIO_LEVEL_SHIFT_13DB,         /* 13 Decibel */
  DP_AUDIO_LEVEL_SHIFT_14DB,         /* 14 Decibel */
  DP_AUDIO_LEVEL_SHIFT_15DB,         /* 15 Decibel */
  DP_AUDIO_LEVEL_SHIFT_MAX,
  DP_AUDIO_LEVEL_SHIFT_FORCE_32BIT = 0x7FFFFFFF
} DP_AudioLevelShiftType;

/*!
* \enum DP_ClockStatusType
*
*
* \brief
*     Defines the status bit mask of DP related clocks
*
*/
typedef enum
{
  DP_CLOCKSTATUS_NONE                     = 0x00000000,
  DP_CLOCKSTATUS_MAIN_LINK_CLK_ACTIVE     = HAL_MDSS_BIT(0),    /**< Indicator that the main clock is active                                  */
  DP_CLOCKSTATUS_IF_LINK_CLK_ACTIVE       = HAL_MDSS_BIT(1),    /**< Indicator that the link interface clock is active                        */
  DP_CLOCKSTATUS_HDCP1P3_LINK_CLK_ACTIVE  = HAL_MDSS_BIT(2),    /**< Indicator that the HDCP1.3 link clock is active                          */
  DP_CLOCKSTATUS_HDCP2P2_LINK_CLK_ACTIVE  = HAL_MDSS_BIT(3),    /**< Indicator that the HDCP2.2 link clock is active                          */
  DP_CLOCKSTATUS_SDP_LINK_CLK_ACTIVE      = HAL_MDSS_BIT(4),    /**< Indicator that the sdp link clock is active (not used)                   */
  DP_CLOCKSTATUS_AUDIO_LINK_CLK_ACTIVE    = HAL_MDSS_BIT(5),    /**< Indicator that the audio link clock is active (not used)                 */
  DP_CLOCKSTATUS_P0CLK23_ACTIVE           = HAL_MDSS_BIT(6),    /**< Indicator that the SST pixel lane 2/3 clock is active (async fifos)      */
  DP_CLOCKSTATUS_P0CLK1_ACTIVE            = HAL_MDSS_BIT(7),    /**< Indicator that the SST pixel lane 1 clock is active (async fifos)        */
  DP_CLOCKSTATUS_P0CLK0_ACTIVE            = HAL_MDSS_BIT(8),    /**< Indicator that the SST pixel lane 0 clock is active (async fifos)        */
  DP_CLOCKSTATUS_P0CLK_ACTIVE             = HAL_MDSS_BIT(9),    /**< Indicator that the SST / MST stream 0 pixel clock is active (front end)  */
  DP_CLOCKSTATUS_TPG_P0CLK_ACTIVE         = HAL_MDSS_BIT(10),   /**< Indicator that the SST / MST stream 0 TPG pixel clock is active          */
  DP_CLOCKSTATUS_AUX_CLK_ACTIVE           = HAL_MDSS_BIT(11),   /**< Indicator that the AUX clock is active                                   */
  DP_CLOCKSTATUS_HDCP_SCLK_ACTIVE         = HAL_MDSS_BIT(12),   /**< indicator that the HDCP general control SCLK is active                   */
  DP_CLOCKSTATUS_HDCP1P3_SCLK_ACTIVE      = HAL_MDSS_BIT(13),   /**< Indicator that the HDCP1.3 branch of SCLK is active                      */
  DP_CLOCKSTATUS_CRYPTO_CLK_ACTIVE        = HAL_MDSS_BIT(14),   /**< Indicator that the crypto clock is active                                */
  DP_CLOCKSTATUS_TPG_P1CLK_ACTIVE         = HAL_MDSS_BIT(15),   /**< Indicator that the MST stream 1 TPG pixel clock is active                */
  DP_CLOCKSTATUS_MST_P0CLK0_CLK_ACTIVE    = HAL_MDSS_BIT(16),   /**< Indicator that the MST stream 0 pixel clock is active (async fifos)      */
  DP_CLOCKSTATUS_MST_P1CLK_CLK_ACTIVE     = HAL_MDSS_BIT(17),   /**< Indicator that the MST stream 1 pixel clock is active (front end)        */
  DP_CLOCKSTATUS_MST_P1CLK0_CLK_ACTIVE    = HAL_MDSS_BIT(18),   /**< Indicator that the MST stream 1 pixel clock is active (async fifos)      */
  DP_CLOCKSTATUS_BIST_MISR40_CLK_ACTIVE   = HAL_MDSS_BIT(19),   /**< Indicator that the PHY BIST / MISR40 clock is active                     */
  DP_CLOCKSTATUS_MISR_CLK_ACTIVE          = HAL_MDSS_BIT(20),   /**< Indicator that the legacy MISR clock is active                           */
  DP_CLOCKSTATUS_MAX,
  DP_CLOCKSTATUS__FORCE_32_BIT            = 0x7FFFFFFF
} DP_ClockStatusType;

//-------------------------------------------------------------------------------------------------
//  DP_MSTStreamIDType
//
//  @brief
//      MST stream IDs.
//
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  DP_MST_STREAM_ID_0,            /**< MST0 */
  DP_MST_STREAM_ID_1,            /**< MST1 */
  DP_MST_STREAM_ID_MAX,
  DP_MST_STREAM_ID_FORCE_32BIT = 0x7FFFFFFF
} DP_MSTStreamIDType;

//-------------------------------------------------------------------------------------------------
//  HAL_DP_HDP_ConnectionType
//
//  @brief
//      HDP connection status
//
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
    DP_HPD_STATUS_DISCONNECTED,
    DP_HPD_STATUS_CONNECT_PENDING,
    DP_HPD_STATUS_CONNECTED,
    DP_HPD_STATUS_HPD_IO_GLITH_COUNT,
    DP_HPD_STATUS_IRQ_HPD_PULSE_COUNT,
    DP_HPD_STATUS_HPD_REPLUG_COUNT,
    DP_HPD_STATUS_MAX,
    DP_HPD_STATUS_FORCE_32BIT          = 0x7FFFFFFF
} DP_HPD_StatusType;

//-------------------------------------------------------------------------------------------------
//  HAL_DP_PSRModeType
//
//  @brief
//      Modes of operation for Panel Self Refresh(PSR) feature in eDP panels
//
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  HAL_DP_PSR_MODE_DISABLE                  = 0x00000000,  /**< PSR feature disabled    */
  HAL_DP_PSR_MODE_ENABLE_PSR,                             /**< PSR Version 1           */
  HAL_DP_PSR_MODE_ENABLE_PSR2,                            /**< PSR2 without FrameSync  */
  HAL_DP_PSR_MODE_ENABLE_PSR2_FRAME_SYNC,                 /**< PSR2 with FrameSync     */
  HAL_DP_PSR_MODE_MAX,
  HAL_DP_PSR_MODE_FORCE_32BIT              = 0x7FFFFFFF
} HAL_DP_PSRModeType;

//-------------------------------------------------------------------------------------------------
//  HAL_DP_ResetFlagType
//
//  @brief
//      Defines flags to control DP controller reset
//
//-------------------------------------------------------------------------------------------------
typedef enum
{
  HAL_DP_RESET_FLAG_NONE                         = 0x00000000,
  HAL_DP_RESET_FLAG_ASSERT                       = HAL_MDSS_BIT(1),  /**< Only assert reset           */
  HAL_DP_RESET_FLAG_DEASSERT                     = HAL_MDSS_BIT(2),  /**< Only de-assert reset        */
  HAL_DP_RESET_FLAG_MAX,
  HAL_DP_RESET_FLAG_FORCE_32BIT                  = 0x7FFFFFFF
} HAL_DP_ResetFlagType;

/* --------------------------------------------------------------------------------------------------------------------
** Macros and Struct
---------------------------------------------------------------------------------------------------------------------*/
#define HAL_DP_AUX_INTR_ALL        (HAL_DP_INTR_TYPE_AUX_I2C_DONE            |\
                                    HAL_DP_INTR_TYPE_WRONG_ADDRESS           |\
                                    HAL_DP_INTR_TYPE_CONSECUTIVE_TIMEOUT     |\
                                    HAL_DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER  |\
                                    HAL_DP_INTR_TYPE_WRONG_READDATA_COUNT    |\
                                    HAL_DP_INTR_TYPE_AUX_NACK_DURING_I2C     |\
                                    HAL_DP_INTR_TYPE_AUX_DEFER_DURING_I2C    |\
                                    HAL_DP_INTR_TYPE_PLL_UNLOCK_DET          |\
                                    HAL_DP_INTR_TYPE_DPPHY_AUX_ERROR         |\
                                    HAL_DP_INTR_TYPE_AUX_RX_STOP_ERR         |\
                                    HAL_DP_INTR_TYPE_AUX_RX_DEC_ERR          |\
                                    HAL_DP_INTR_TYPE_AUX_RX_SYNC_ERR         |\
                                    HAL_DP_INTR_TYPE_AUX_RX_ALIGN_ERR        |\
                                    HAL_DP_INTR_TYPE_AUX_TX_REQ_ERR)

#define HAL_DP_INTR_ALL            (HAL_DP_INTR_TYPE_HPD                     |\
                                    HAL_DP_INTR_TYPE_AUX_I2C_DONE            |\
                                    HAL_DP_INTR_TYPE_WRONG_ADDRESS           |\
                                    HAL_DP_INTR_TYPE_CONSECUTIVE_TIMEOUT     |\
                                    HAL_DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER  |\
                                    HAL_DP_INTR_TYPE_WRONG_READDATA_COUNT    |\
                                    HAL_DP_INTR_TYPE_AUX_NACK_DURING_I2C     |\
                                    HAL_DP_INTR_TYPE_AUX_DEFER_DURING_I2C    |\
                                    HAL_DP_INTR_TYPE_PLL_UNLOCK_DET          |\
                                    HAL_DP_INTR_TYPE_DPPHY_AUX_ERROR         |\
                                    HAL_DP_INTR_TYPE_READY_FOR_VIDEO         |\
                                    HAL_DP_INTR_TYPE_IDLE_PATTERNS_SENT      |\
                                    HAL_DP_INTR_TYPE_FRAME_END               |\
                                    HAL_DP_INTR_TYPE_CRC_UPDATED             |\
                                    HAL_DP_INTR_TYPE_SST_FIFO_UNDERFLOW      |\
                                    HAL_DP_INTR_TYPE_FRAME_END_STREAM1       |\
                                    HAL_DP_INTR_TYPE_DPPHY_AUX_ERROR         |\
                                    HAL_DP_INTR_TYPE_AUX_RX_STOP_ERR         |\
                                    HAL_DP_INTR_TYPE_AUX_RX_DEC_ERR          |\
                                    HAL_DP_INTR_TYPE_AUX_RX_SYNC_ERR         |\
                                    HAL_DP_INTR_TYPE_AUX_RX_ALIGN_ERR        |\
                                    HAL_DP_INTR_TYPE_AUX_TX_REQ_ERR          |\
                                    HAL_DP_HDCP_INTR_ALL                     |\
                                    HAL_DP_INTR_TYPE_HPD_PLUG_INT            |\
                                    HAL_DP_INTR_TYPE_HPD_IRQ_INT             |\
                                    HAL_DP_INTR_TYPE_HPD_REPLUG_INT          |\
                                    HAL_DP_INTR_TYPE_HPD_UNPLUG_INT)

#define HAL_DP_HDCP_INTR_ALL       (HAL_DP_INTR_TYPE_ENCRYPTION_NOT_READY    |\
                                    HAL_DP_INTR_TYPE_ENCRYPTION_READY        |\
                                    HAL_DP_INTR_TYPE_AUTH_FAIL               |\
                                    HAL_DP_INTR_TYPE_AUTH_SUCCESS)
/* Link rates supported by DP Controller */
#define HAL_DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_162MBps   162000
#define HAL_DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_270MBps   270000
#define HAL_DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_540MBps   540000
#define HAL_DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_810MBps   810000

/* Validate DP controller ID */
#define HAL_DP_ValidateControllerID(_eControllerId_)  ((_eControllerId_ > DP_CONTROLLER_ID_NONE) && (_eControllerId_ < DP_CONTROLLER_ID_MAX))

/*!
 * \struct HAL_DP_WritePacketType
 *
 * The \b HAL_DP_WritePacketType defines write parameters to the CMD_FIFO.
 *
 */
typedef struct
{
   HAL_DP_AuxTransactionModeType    eTransactionType;                  /**< AUX transaction type                    */
   uint32                           uNumofTransactions;                /**< # of Transaction in the buffer          */
   uint8                           *puWriteData;                       /**< Buffer of data to be written            */
   uint32                           uWriteDataSize;                    /**< Size of data to be written in byte      */
   uint32                           uBytesWritten;                     /**< How many bytes written                  */
} HAL_DP_WritePacketType;


/*!
 * \struct HAL_DP_ReadPacketType
 *
 * The \b HAL_DP_ReadPacketType defines read packet for AUX/I2C read from DATA_FIFO.
 *
 */
typedef struct
{
   uint8                           *puReadDataBuffer;                  /**< Data buffer for return values           */
   uint32                           uReadSize;                         /**< Data size to be read in byte            */
   uint32                           uBytesRead;                        /**< How many bytes Read from FIFO           */
} HAL_DP_ReadPacketType;

/*!
 * \struct HAL_DP_AUXAttribType
 *
 * The \b HAL_DP_AUXAttribType defines AUX attribute, i.e. Endian settings, the clock cycles before a Timeout, how
 * many time out will trigger interrupt. Default value should work.
 *
 */
typedef struct
{
   uint32                           *puTimeoutCount;                    /**< How many clk before timeout             */
   uint32                           *puTimeoutLimit;                    /**< TO # before an interrupt                */
   uint32                           *puReadZeroLimit;                   /**< Read # with no data before irq          */
   uint32                           *puNackDeferLimit;                  /**< nack/defer # before an irq              */
   uint32                           *puI2CDeferLimit;                   /**< I2C defer # before an irq               */
   bool32                           *pbStopTXOnPhyErr;                  /**< Stop TX upon PHY error?                 */
   bool32                           *pbTXLittleEndian;                  /**< is TX little Endian?                    */
   bool32                           *pbRXLittleEndian;                  /**< is RX little Endian?                    */
} HAL_DP_AUXAttribType;

/*!
 * \struct HAL_DP_AUXConfigType
 *
 * The \b HAL_DP_AUXConfigType defines AUX controller parameters
 *
 */
typedef struct
{
   HAL_DP_AUXAttribType            *psAUXAttrib;                       /**< Default value should work               */
} HAL_DP_AUXConfigType;

/*!
 * \struct HAL_DP_CustomPatternType
 *
 * The \b HAL_DP_CustomPatternType defines 80 bit custom pattern values
 *
 */
typedef struct
{
   uint32                           uCustomPattern_R0;                  /**< 80 Bit Pattern R0                       */
   uint32                           uCustomPattern_R1;                  /**< 80 Bit Pattern R1                       */
   uint32                           uCustomPattern_R2;                  /**< 80 Bit Pattern R2                       */
} HAL_DP_CustomPatternType;

/*!
 * \struct HAL_DP_MSAPacketType
 *
 * The \b HAL_DP_MSAPacketType defines Main stream attribute according to DP V1.2 spec
 *
 */
typedef struct                                                          /**< Main Stream Attribute                   */
{
   uint32                           uSWMVid;                            /**< SW M value for video                    */
   uint32                           uSWNVid;                            /**< SW N value for video                    */
   uint32                           uVisibleWidthInPixels;              /**< Visible active area width in pixels     */
   uint32                           uVisibleHeightInPixels;             /**< Visible active area height in pixels    */
   uint32                           uHsyncFrontPorchInPixels;           /**< HSYNC Front Porch width in pixels       */
   uint32                           uHsyncBackPorchInPixels;            /**< HSYNC Back Porch width in pixels        */
   uint32                           uHsyncPulseInPixels;                /**< HSYNC pulse width in pixels             */
   uint32                           uHsyncSkewInPixels;                 /**< HSYNC active edge is delayed from VSYNC */
   uint32                           uVsyncFrontPorchInLines;            /**< VSYNC Front Porch width in lines        */
   uint32                           uVsyncBackPorchInLines;             /**< VSYNC Back Porch width in lines         */
   uint32                           uVsyncPulseInLines;                 /**< VSYNC pulse width in lines              */
   uint32                           uHLeftBorderInPixels;               /**< Left border in pixels                   */
   uint32                           uHRightBorderInPixels;              /**< Right border in pixels                  */
   uint32                           uVTopBorderInLines;                 /**< Top border in lines                     */
   uint32                           uVBottomBorderInLines;              /**< Bottom border in lines                  */
   bool32                           bHSyncActiveLow;                    /**< Hsync polarity                          */
   bool32                           bVSyncActiveLow;                    /**< Vsync polarity                          */
   uint32                           uMisc0;                             /**< Misc data 0 defined by DP1.2            */
   uint32                           uMisc1;                             /**< Misc data 1 defined by DP1.2            */
   uint32                           uStreamId;                          /**< 0: SST/MST0; 1: MST1                    */
} HAL_DP_MSAPacketType;

/*!
 * \struct HAL_DP_VSCPacketType
 *
 * The \b HAL_DP_VSCPacketType defines Video Stream Configuration according to DP V1.2 spec. Only used for 3D.
 *
 */
typedef struct                                                          /**< Video Stream Configuration              */
{
   bool32                           bSendVSC;                           /**< Sending VSC data?                       */
   uint8                            uVSC_DB0;                           /**< VSC DB0 Value                           */
   uint8                            uVSC_PB4;                           /**< VSC PB4 Value                           */
   uint8                            uVSC_HB0;                           /**< VSC HB0 Value                           */
   uint8                            uVSC_PB0;                           /**< VSC PB0 Value                           */
   uint8                            uVSC_HB1;                           /**< VSC HB1 Value                           */
   uint8                            uVSC_PB1;                           /**< VSC PB1 Value                           */
   uint8                            uVSC_HB2;                           /**< VSC HB2 Value                           */
   uint8                            uVSC_PB2;                           /**< VSC PB2 Value                           */
   uint8                            uVSC_HB3;                           /**< VSC HB3 Value                           */
   uint8                            uVSC_PB3;                           /**< VSC PB3 Value                           */
} HAL_DP_VSCPacketType;

/*!
 * \struct HAL_DP_StreamAttribType
 *
 * The \b HAL_DP_StreamAttribType defines the configuration that must provided by
 * host driver/panel driver
 *
 */
typedef struct
{
   bool32                           bSynchronousClk;                    /**< is link clk/pixel clk in Sync?          */
   bool32                           bEnhancedFraming;                   /**< Enable Enhanced eDP Framing?            */
   bool32                           bASSR;                              /**< Enable ASSR authentication?             */
   bool32                           bInterlaced;                        /**< interlaced mode                         */
} HAL_DP_StreamAttribType;

/*!
 * \struct HAL_DP_SinkAttribType
 *
 * The \b HAL_DP_SinkAttribType defines the DP panel HW attributes, which should not
 * change for a given panel.
 *
 */
typedef struct
{
   HAL_DP_LaneMapType              eLaneMapping;                       /**< Logical/physical lane map               */
   HAL_DP_PixelFormatType          ePixelFormat;                       /**< Pixel format                            */
   HAL_DP_RGBMapType               eRGBMapping;                        /**< RGB Mapping                             */
   uint32                          uLaneNumber;                        /**< # of lanes (1, 2, 4)                    */
   uint32                          uBitPerComponent;                   /**< Bit per Component                       */
   uint32                          uStreamId;                          /**< 0: SST/MST0; 1: MST1                    */
} HAL_DP_SinkAttribType;

/*!
 * \struct HAL_DP_PPSConfigType
 *
 * The \b HAL_DP_PPSConfigType defines the DSC PPS data to be sent to the panel
 *
 */
typedef struct
{
   uint32                          uStreamId;                          /**< 0: SST/MST0; 1: MST1                    */
   uint8                          *puPPSBuffer;                        /**< PPS data buffer address                 */
   uint32                          uBufferSize;                        /**< PPS data buffer size                    */
} HAL_DP_PPSConfigType;

/*!
 * \struct HAL_DP_TUConfigType
 *
 * The \b HAL_DP_TUConfigType defines the Transfer Unit size related configuration.
 *
 */
typedef struct
{
   uint32                           uTuSize;                            /**< Desired TU Size                         */
   uint32                           uValidBoundaryLink;                 /**< Upper valid boundary                    */
   uint32                           uDelayStartLink;                    /**< # of clock cycles to delay              */
   bool32                           bBoundaryModEnable;                 /**< Enable boundary Moderation?             */
   uint32                           uValidLowerBoundary;                /**< Valid lower boundary link               */
   uint32                           uUpperBoundaryCount;                /**< Upper boundary Count                    */
   uint32                           uLowerBoundaryCount;                /**< Lower boundary Count                    */
   double                           dRatioByTU;                         /**< Ratio by TU                             */
} HAL_DP_TUConfigType;

/*!
 * \struct HAL_DP_DSCConfigType
 *
 * The \b HAL_DP_DSCConfigType defines DSC related configuration.
 *
 */
typedef struct
{
  bool32                           bCompressed;
  uint32                           uStreamId;
  uint32                           uCompressionRatio;
  uint32                           uSlicesPerLine;
  uint32                           uTargetBppUncompressed;
  uint32                           uSliceWidth;
  uint32                           uCompressedPixelsPerLine;
  uint32                           uDTONumerator;
  uint32                           uDTODenominator;
  uint32                           uBeInLane;                           /**< Blank end in lane            */
} HAL_DP_DSCConfigType;

/*!
 * \struct HAL_DP_RGConfigType
 *
 * The \b HAL_DP_RGConfigType defines the rate governor parameters for MST.
 *
 */
typedef struct
{
   double                           dMinSlotCount;                      /**< Minimum time slot allocayion that the   
                                                                             RG could operate in                     */
   uint32                           uPBN;                               /**< Payload BW number                       */
   double                           dMaxSlotCount;                      /**< Maximum time slot allocation per MTP
                                                                             that the supported stream could use     */
   double                           dChosenSlotCount;                   /**< The chosen target time slot             */
   uint32                           uTS_INT_PLUS1;                      /**< Ceiling of target chosen slot count     */
   uint32                           uY_FRAC_ENUM;                       /**< Quantized enumerator for representation 
                                                                             of chosen slot count                    */
   uint32                           uX_INT;                             /**< Quantized integer for representation of
                                                                             chosen slot count                       */
   uint32                           uSlotCount;                         /**< Time slots for a partocular mode        */ 
} HAL_DP_RGConfigType;

/*!
 * \struct HAL_DP_OptionalType
 *
 * The \b HAL_DP_OptionalType defines the configuration that can work with the HW default
 * value.
 *
 */
typedef struct                                                          /**< Default values should work              */
{
   bool32                           *pbBypassLaneSkew;                  /**< Bypass Inter-lane Skew insert?          */
   bool32                           *pbBypassScrambler;                 /**< Bypass Scrambler?                       */
   bool32                           *pbBypass8B10B;                     /**< Bypass 8B10B? pads 0 to msb             */
   bool32                           *pbForcePixeClkOn;                  /**< Force Pixel Clk on                      */
   bool32                           *pbLCDSelfTest;                     /**< Drive LCD_Self_Test Pad?                */
   bool32                           *pbLinkBigEndian;                   /**< is main link little Endian?             */
   bool32                           *pbPixelBigEndian;                  /**< is Pixel data little Endian?            */
   uint32                           *puSafeToExitLevel;                 /**< Level that is safe to exit              */
   uint32                           *puIdlePatternRepNum;               /**< Idle pattern repetition #               */
   uint32                           *puMSA2VSCDelay;                    /**< delay between MSA and VSC               */
   uint32                           *puVSCRepNum;                       /**< # of VSC repetition                     */
   HAL_DP_CustomPatternType         *psCustomPattern;                   /**< 80 Bit Custom Pattern                   */
   uint32                           *puHBR2ComplianceScramblerReset;    /**< HBR2 Compliance Scrambler Reset         */
   bool32                           *pbBypassFECRS;                     /**< Bypass the FEC parity insertion         */
} HAL_DP_OptionalType;

/*!
 * \struct HAL_DP_HPDConfigType
 *
 * The \b HAL_DP_HPDConfigType defines the HPD configuration 
 * value.
 *
 */
typedef struct                                                          
{
  DP_DeviceIDType   eDeviceID;             // HPD config differs between devices
  DP_DeviceModeType eDeviceDPMode;         // DP Device Mode
  bool32            bEnable;               // Enable HPD hardware       
  bool32            bActiveLow;            // HPD pin is active low     
} HAL_DP_HPDConfigType;

/**<!
 * \struct HAL_DP_AuxHwCapsType
 *
 * The \b HAL_DP_AuxHwCapsType defines AUX HW capabilities for caller to query
 *
 */
typedef struct
{
  uint32                           uAUXCmdFifoLen;                     /**< Length of AUX CMD_FIFO                  */
  uint32                           uMaxAUXCmdLen;                      /**< Max length of AUX CMD packet            */
  uint32                           uMaxI2CCmdLen;                      /**< Length of I2C CMD_FIFO                  */
} HAL_DP_AuxHwCapsType;

/**<!
* \struct HAL_DP_AudioConfigType
*
* The \b HAL_DP_AudioConfigType defines audio configurations
*
*/
typedef struct
{
  bool32                          bAudioInfoPacket;                   /* Enable/Disable Audio InfoFrame Packet      */
  bool32                          bInhibitDownMix;                    /* Enable/Disable Audio output down mixing    */
  bool32                          bSSCMode;                           /* Enable/Disable SSC mode                    */
  uint32                          uLinkRateInKhz;                     /* Link rate                                  */
  DP_AudioChannelType             eAudioNumOfChannel;                 /* HDMI_Device_AudioChannelType               */
  DP_AudioSampleRateType          eAudioSampleRate;                   /* HDMI_Device_AudioSampleRateType            */
  DP_AudioFormatType              eAudioFormat;                       /* Audio format                               */
  DP_AudioSampleBitDepthType      eAudioSampleBitDepth;               /* Audio bit depth                            */
  DP_AudioChannelAllocType        eChannelAllocCode;                  /* Audio channel to speaker mapping           */
  DP_AudioLevelShiftType          eLevelShiftValue;                   /* Audio attenuation level                    */
  DP_MSTStreamIDType              eMSTStreamID;                       /* MST Stream ID                              */
} HAL_DP_AudioConfigType;

/**<!
* \struct HAL_DP_MSTVCAllocationType
*
* The \b HAL_DP_MSTVCAllocationType defines MST virtual channel and time slot allocation
*
*/
typedef struct
{
  uint32 uStream0VCID;       /**< Virtual channel ID for stream 0 */
  uint32 uStream0StartSlot;  /**< Start slot index for stream 0   */
  uint32 uStream0SlotCount;  /**< Slot count for stream 0         */
  uint32 uStream1VCID;       /**< Virtual channel ID for stream 1 */
  uint32 uStream1StartSlot;  /**< Start slot index for stream 1   */
  uint32 uStream1SlotCount;  /**< Slot count for stream 0         */
} HAL_DP_MSTVCAllocationType;

/**<!
* \struct HAL_DP_PSRConfigType
*
* The \b HAL_DP_PSRConfigType defines PSR config to applied
*
*/
typedef struct
{
  HAL_DP_PSRModeType    ePSRMode;                   /**< Mode of operation for PSR feature                */
  bool32                bMainLinkActive;            /**< Will Mainlink be Active during PSR               */
  bool32                bVerifyCRC;                 /**< Will Frame CRC verification be done by sink      */
  bool32                bCaptureSecondFrame;        /**< Capture 2nd frame instead of 1st after PSR entry */
  bool32                bTrainingOnExit;            /**< Fast link training is required on PSR exit       */
} HAL_DP_PSRConfigType;

/*!
 * \struct HAL_DP_GenericSDPConfigType
 *
 * The \b HAL_DP_GenericSDPConfigType defines a generic SDP header and payload
 * for use with the generic SDP HAL
 */
typedef struct
{
   uint8       uHB0;                /**< Generic SDP header byte 0                     */
   uint8       uHB1;                /**< Generic SDP header byte 1                     */
   uint8       uHB2;                /**< Generic SDP Header byte 2                     */
   uint8       uHB3;                /**< Generic SDP header byte 3                     */
   uint8      *pSDPPayload;         /**< Generic SDP payload (no header)               */
   uint32      uPayloadBytes;       /**< Generic SDP payload size in bytes (no header) */
} HAL_DP_GenericSDPConfigType;

/*!
 * \struct HAL_DP_VSCSDPConfigType
 *
 * The \b HAL_DP_VSCSDPConfigType defines a VSC SDP header and payload
 * for use with the VSC SDP HAL
 */
typedef struct
{
  uint8       uHB0;                                                     /**< VSC SDP header byte 0                     */
  uint8       uHB1;                                                     /**< VSC SDP header byte 1                     */
  uint8       uHB2;                                                     /**< VSC SDP Header byte 2                     */
  uint8       uHB3;                                                     /**< VSC SDP header byte 3                     */
  uint8      *pSDPPayload;                                              /**< VSC SDP payload (no header)               */
  uint32      uPayloadBytes;                                            /**< VSC SDP payload size in bytes (no header) */
} HAL_DP_VSCSDPConfigType;

/*---------------------------------------------------------------------------------------------------------------------
Public Function declarations
---------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************
*
** FUNCTION: HAL_DP_SetupBIST()
*/
/*!
* \brief
*     Set BIST test pattern in DP controller
*
* \param [in]   eControllerId   - DP core ID
* \param [in]   psMainStream    - Main stream info for the timing info
* \param [in]   uVideoPattern   - Test pattern ID. 0->disable test pattern
*
* \retval HAL_MDSS_ErrorType
*
**********************************************************************************************************************/
HAL_MDSS_ErrorType HAL_DP_SetupBIST(DP_ControllerIDType   eControllerId,
                                    HAL_DP_MSAPacketType *psMainStream,
                                    uint32                uVideoPattern);

/**********************************************************************************************************************
*
** FUNCTION: HAL_DP_Init()
*/
/*!
* \brief
*     Initializes DP HW Block
*
* \param [in]   eControllerId       - DP core ID
*
* \retval None
*
**********************************************************************************************************************/
void HAL_DP_Init(DP_ControllerIDType eControllerId);

/**********************************************************************************************************************
*
** FUNCTION: HAL_DP_Reset()
*/
/*!
* \brief
*     Resets DP HW Block
*
* \param [in]   eControllerId       - DP core ID
* \param [in]   uModule             - Bit array of HW module to be reset
* \param [in]   uResetFlag          - Reserved
*
* \retval HAL_MDSS_ErrorType
*
**********************************************************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Reset(DP_ControllerIDType eControllerId,
                                uint32              uModule,
                                uint32              uResetFlag);

/****************************************************************************

FUNCTION: HAL_DP_Interrupt_Enable()

   Enables interrupts

Parameters:
   eControllerId              -[in] DP core ID
   eInterruptSrc              -[in] DP interrupt mask to enable
   uEnableFlags               -[in] Reserved

Return: 
   HAL_MDSS_ErrorType

****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Interrupt_Enable(DP_ControllerIDType           eControllerId,
                                           HAL_DP_InterruptType          eInterruptSrc,
                                           uint32                        uEnableFlags);

/****************************************************************************

FUNCTION: HAL_DP_Interrupt_Disable()

   Disables interrupts

Parameters:
   eControllerId              -[in] DP core ID
   eInterruptSrc              -[in] DP interrupt mask to disable
   uEnableFlags               -[in] Reserved

Return: 
   HAL_MDSS_ErrorType

****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Interrupt_Disable(DP_ControllerIDType           eControllerId,
                                            HAL_DP_InterruptType          eInterruptSrc,
                                            uint32                        uEnableFlags);

/**********************************************************************************************************************
*
** FUNCTION: HAL_DP_Interrupt_Clear()
*/
/*!
* \brief
*     Clears or Acknowledges the interrupts
*
* \param [in]   eControllerId       - DP core ID
* \param [in]   eInterruptSrc       - Interrupt sources to be clear.
* \param [in]   uClearFlags         - Reserved
*
* \retval HAL_MDSS_ErrorType
*
**********************************************************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Interrupt_Clear(DP_ControllerIDType           eControllerId,
                                          HAL_DP_InterruptType          eInterruptSrc,
                                          uint32                        uClearFlags );

/**********************************************************************************************************************
*
** FUNCTION: HAL_DP_Interrupt_GetStatus()
*/
/*!
* \brief
*     Returns the interrupts status
*
* \param [in]     eControllerId     - DP core ID
* \param [in/out] peIntrStatus      - Status for each module.
* \param [in]     uGetStatusFlags   - Reserved
*
* \retval HAL_MDSS_ErrorType
*
**********************************************************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Interrupt_GetStatus(DP_ControllerIDType           eControllerId,
                                              HAL_DP_InterruptType         *peIntrStatus,
                                              uint32                        uGetStatusFlags);

/**********************************************************************************************************************
*
** FUNCTION:HAL_DP_Write()
*/
/*!
* \brief
*     This API write AUX packet to CMD FIFO and trigger the transaction upon request.
*
* \param [in] eControllerId         - DP core ID
* \param [in] psWritePacket         - pointer to data struct to be written out.
* \param [in] uWriteFlags           - Reserved
*
* \retval HAL_MDSS_ErrorType
*
**********************************************************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Write(DP_ControllerIDType        eControllerId,
                                HAL_DP_WritePacketType    *psWritePacket,
                                uint32                     uWriteFlags);

/****************************************************************************

FUNCTION: HAL_DP_Read()
   
  This API allows users to read data from DATA FIFO, the read command has 
  already sent to panel by HAL_DP_AUXWriteFifo, and triggered.

Parameters:
  eControllerId              -[in] DP core ID
  psReadPacket               -[in] pointer to data struct to be read.
  uAUXReadFlags              -[in] Reserved

Return: 
  HAL_MDSS_ErrorType

****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Read(DP_ControllerIDType     eControllerId,
                               HAL_DP_ReadPacketType  *psReadPacket,
                               uint32                  uAUXReadFlags);


/****************************************************************************

FUNCTION: HAL_DP_AUXChannel_Enable()
   
  This API allows users to enable/disable AUX channel. 

Parameters:
  eControllerId         -[in] DP core ID
  bEnable               -[in] TRUE = enable, FALSE = disable

Return: 
  void

****************************************************************************/
void HAL_DP_AUXChannel_Enable(DP_ControllerIDType eControllerId,
                              bool32              bEnable);


/****************************************************************************

FUNCTION: HAL_DP_AUX_Status()
   
  This API allows users to get AUX channel status. 
  It also clears previous transaction details when done

Parameters:
   eControllerId              -[in] DP core ID

Return: 
  AUX status

****************************************************************************/
HAL_DP_AUXStatusType HAL_DP_AUX_Status(DP_ControllerIDType eControllerId);

/****************************************************************************

FUNCTION: HAL_DP_AUX_ClearTransaction()
   
  This API allows users to clear previous AUX transaction. 

Parameters:
   eControllerId              -[in] DP core ID

Return: 
  void

****************************************************************************/
void HAL_DP_AUX_ClearTransaction(DP_ControllerIDType eControllerId);

/****************************************************************************

FUNCTION: HAL_DP_AUX_GetHwCaps()
   
  This API allows users to get AUX HW capabilities. 

Parameters:
  eControllerId         -[in] DP core ID
  psHwCap               -[out] pointer to hw caps

Return: 
  void

****************************************************************************/
void HAL_DP_AUX_GetHwCaps(DP_ControllerIDType    eControllerId,
                          HAL_DP_AuxHwCapsType  *psHwCap);

/**********************************************************************************************************************
FUNCTION: HAL_DP_AUXConfig()
   
  This API Config AUX for AUX/I2C transaction.

Parameters: 
  eControllerId              -[in] DP core ID
  psWritePacket              -[in] Pointer to data struct to be write out.
  uAUXConfigFlags            -[in] Reserved

Return:  
  HAL_MDSS_ErrorType

**********************************************************************************************************************/
HAL_MDSS_ErrorType HAL_DP_AUXConfig(DP_ControllerIDType        eControllerId,
                                    HAL_DP_AUXConfigType      *psAUXCtrlConfig,
                                    uint32                     uAUXConfigFlags);

/****************************************************************************
*
** FUNCTION: HAL_DP_Mainlink_Enable()
*/
/*!
* \brief
*   The \b Enable main link  
*
* \param [in]   eControllerId   - DP core ID
* \param [in]   bEnable         - TRUE - Enable, FALSE - Disable
*
* \retval void
*
****************************************************************************/
void HAL_DP_Mainlink_Enable(DP_ControllerIDType eControllerId,
                            bool32              bEnable);

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetBackPressure()
   
   Turn on/off MDP back pressure for the DP Stream

Parameters: 
   eControllerId              -[in] DP core ID
   eStreamId                  -[in] Stream ID
   bEnable                    -[in] TRUE - Enable, FALSE - Disable

Return:  
   None

**********************************************************************************************************************/
void HAL_DP_SetBackPressure(DP_ControllerIDType     eControllerId,
                            DP_StreamIDType         eStreamId,
                            bool32                  bEnable);

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetLinkState()
   
   This API set the Main Link State

Parameters: 
   eControllerId              -[in] DP core ID
   peLinkState                -[in] Link state to set.

Return:  
   None

**********************************************************************************************************************/
void HAL_DP_SetLinkState(DP_ControllerIDType     eControllerId,
                         HAL_DP_LinkCommandType  peLinkState);

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetTUConfig()
   
   This API set the TU configuration 

Parameters: 
   eControllerId              -[in] DP core ID
   psTUConfig                 -[in] Pointer to TU configurations structure.

Return:  
   None

**********************************************************************************************************************/
void HAL_DP_SetTUConfig(DP_ControllerIDType     eControllerId,
                        HAL_DP_TUConfigType    *psTUConfig);

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetDSCConfig()
   
   This API set the DSC configuration 

Parameters: 
   eControllerId              -[in] DP core ID
   psDSCConfig                -[in] Pointer to DSC configurations structure.

Return:  
   None

**********************************************************************************************************************/
void HAL_DP_SetDSCConfig(DP_ControllerIDType     eControllerId,
                         HAL_DP_DSCConfigType   *psDSCConfig);

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetFECConfig()

   This API sets the FEC configuration

Parameters:
   eControllerId        -[in] DP core ID
   bEnable              -[in] Flag used to enable/disable FEC
   bTunneledMode        -[in] Boolean used to indicate if in DP tunneling mode

Return:
   None

**********************************************************************************************************************/
void HAL_DP_SetFECConfig(DP_ControllerIDType    eControllerId,
                         bool32                 bEnable,
                         bool32                 bTunneledMode);

/**********************************************************************************************************************
FUNCTION: HAL_DP_DSC_SendPPS()
   
   This API sends the DSC PPS through SDP

Parameters: 
   eControllerId              -[in] DP core ID
   psPPSConfig                -[in] Pointer to PPS config structrure

Return:  
   None

**********************************************************************************************************************/
void  HAL_DP_DSC_SendPPS(DP_ControllerIDType   eControllerId,
                         HAL_DP_PPSConfigType *psPPSConfig);

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetSinkAttrib()
   
   This API set the sink attributes

Parameters: 
   eControllerId              -[in] DP core ID
   psSinkAttrib               -[in] Pointer to sink attributes structure.

Return:  
   None

**********************************************************************************************************************/
void HAL_DP_SetSinkAttrib(DP_ControllerIDType     eControllerId,
                          HAL_DP_SinkAttribType  *psSinkAttrib);

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetStreamAttrib()
   
   This API set the stream attributes

Parameters: 
   eControllerId              -[in] DP core ID
   psStreamAttrib             -[in] Pointer to stream attributes structure.

Return:  
   None

**********************************************************************************************************************/
void HAL_DP_SetStreamAttrib(DP_ControllerIDType       eControllerId,
                            HAL_DP_StreamAttribType  *psStreamAttrib);

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetMSA()
   
   This API set the MSA structure for main video stream.

Parameters: 
   eControllerId              -[in] DP core ID
   psMainStream               -[in] Pointer to MSA structure.

Return:  
   None

**********************************************************************************************************************/
void HAL_DP_SetMSA(DP_ControllerIDType     eControllerId,
                   HAL_DP_MSAPacketType   *psMainStream);

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetVSC()
   
   This API set the VSC structure for 3D video stream.

Parameters: 
   eControllerId              -[in] DP core ID
   psVSCPacket                -[in] Pointer to VSC structure.

Return:  
   None

**********************************************************************************************************************/
void HAL_DP_SetVSC(DP_ControllerIDType     eControllerId,
                   HAL_DP_VSCPacketType   *psVSCPacket);

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetOptionalConfig()
   
   This API Config optional settings for DP controller.

Parameters: 
   eControllerId              -[in] DP core ID
   psCtrlOptionalCfg          -[in] Pointer to optional  configuration structure.

Return:  
   None

**********************************************************************************************************************/
void HAL_DP_SetOptionalConfig(DP_ControllerIDType     eControllerId,
                              HAL_DP_OptionalType    *psCtrlOptionalCfg);

/****************************************************************************
*
** FUNCTION: HAL_DP_Mainlink_Status()
*/
/*!
* \brief
*   \b Get Main link status 
*
* \param [in]   eControllerId   - DP core ID
*
* \retval bit-field of HAL_DP_LinkStatusType
*
****************************************************************************/
uint32 HAL_DP_Mainlink_Status(DP_ControllerIDType eControllerId);

/****************************************************************************
*
** FUNCTION: HAL_DP_HPD_Engine_Enable()
*/
/*!
* \brief
*   The \b Enable Hot Plug Detect functionality 
*
* \param [in] eControllerId   - DP core ID
* \param [in] psConfig        - HPD configuration
*
* \retval void
*
****************************************************************************/
void HAL_DP_HPD_Engine_Enable(DP_ControllerIDType   eControllerId,
                              HAL_DP_HPDConfigType *psConfig);

/****************************************************************************
*
** FUNCTION: HAL_DP_HPD_PanelPlugged()
*/
/*!
* \brief
*   The \b Checks whether panel is plugged in
*
* \param [in]   eControllerId   - DP core ID
*
* \retval DP_HPD_StatusType for connection
*
****************************************************************************/
DP_HPD_StatusType HAL_DP_HPD_PanelPlugged(DP_ControllerIDType eControllerId);


/****************************************************************************
*
** FUNCTION: HAL_DP_ReadVersionInfo()
*/
/*!
* \brief
*     Returns the version information
*
* \param [in]     eControllerId     - DP core ID
* \param [in/out] psDPVersionInfo   - Version information
*
* \retval None
*
****************************************************************************/
void HAL_DP_ReadVersionInfo(DP_ControllerIDType eControllerId,
                            HAL_HW_VersionType *psDPVersionInfo);


/****************************************************************************
*
** FUNCTION: HAL_DP_AudioSetup()
*/
/*!
* \brief
*     Configure DP audio engine
*
* \param [in] eControllerId         - DP core ID
* \param [in] psAudioConfig         - Audio engine configure info
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_AudioSetup(DP_ControllerIDType     eControllerId,
                                     HAL_DP_AudioConfigType *psAudioConfig);

/****************************************************************************
*
** FUNCTION: HAL_DP_Audio_Enable()
*/
/*!
* \brief
*     Enable/Disable audio engine
*
* \param [in] eControllerId         - DP core ID
* \param [in] bEnable               - Enable/disable audio engine
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Audio_Enable(DP_ControllerIDType eControllerId,
                                       bool32              bEnable);

/****************************************************************************
*
** FUNCTION: HAL_DP_GetRegBaseOffset()
*/
/*!
* \brief
*     Get DP register address offset for a given DP controller ID
*
* \param [in]  eControllerId - DP core ID
*
* \retval - register base offset
*
****************************************************************************/
uintPtr HAL_DP_GetRegBaseOffset(DP_ControllerIDType  eControllerId);


/****************************************************************************
*
** FUNCTION: HAL_DP_GetPixelClkRegBaseOffset()
*/
/*!
* \brief
*     Get DP Pclk register address offset for a given DP controller ID and 
*     stream ID
*
* \param [in]  eControllerId - DP core ID
* \param [in]  eStreamID     - Stream ID
*
* \retval - register base offset
*
****************************************************************************/
uintPtr HAL_DP_GetPixelClkRegBaseOffset(DP_ControllerIDType  eControllerId,
                                        DP_StreamIDType      eStreamId);

/****************************************************************************
*
** FUNCTION: HAL_DP_GetClockStatus()
*/
/*!
* \brief
*     Returns status of DP related clocks
*
* \param [in]     eControllerId     - DP core ID
* \param [in/out] puClockStatus     - Clock status
*
* \retval None
*
****************************************************************************/
void HAL_DP_GetClockStatus(DP_ControllerIDType  eControllerId,
                           DP_ClockStatusType  *puClockStatus);

/****************************************************************************
*
** FUNCTION: HAL_DP_CrossbarConfig()
*/
/*!
* \brief
*     Configure the DP controller to PHY crossbar.
*
* \param [in]  eControllerId - DP Core ID
* \param [in]  ePhyId        - DP PHY ID
*
* \retval - register base offset
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_CrossbarConfig(DP_ControllerIDType eControllerId,
                                         DP_DeviceIDType     ePhyId);

/****************************************************************************
*
** FUNCTION: HAL_DP_SetRGConfig()
*/
/*!
* \brief
*   The \b Set MSt Rate Governor related configuration 
*
* \param [in]   eControllerId - DP core ID
* \param [in]   uStreamID     - Stream ID to configure
* \param [in]   psRGConfig    - Pointer to the RG configuration 
*
* \retval void
*
****************************************************************************/
void HAL_DP_SetRGConfig(DP_ControllerIDType  eControllerId,
                        uint32               uStreamID,
                        HAL_DP_RGConfigType *psRGConfig);

/****************************************************************************
*
** FUNCTION: HAL_DP_MSTVCConfig()
*/
/*!
* \brief
*     Configure the DP MST virtual channel and time slot allocation.
*
* \param [in]  eControllerId - DP Core ID
* \param [in]  pVCAllocation - Virtual channel and slot allocation
*
* \retval - register base offset
*
****************************************************************************/
void HAL_DP_MSTVCConfig(DP_ControllerIDType         eControllerId,
                        HAL_DP_MSTVCAllocationType *pVCAllocation);

/****************************************************************************
*
** FUNCTION: HAL_DP_MST_Enable()
*/
/*!
* \brief
*   The \b Enable MST on DP controller
*
* \param [in]   eControllerId   - DP core ID
* \param [in]   bEnable         - TRUE - Enable, FALSE - Disable
*
* \retval void
*
****************************************************************************/
void HAL_DP_MST_Enable(DP_ControllerIDType eControllerId,
                       bool32              bEnable);

/****************************************************************************
*
** FUNCTION: HAL_DP_MST_Stream_Enable()
*/
/*!
* \brief
*   Stream specific MST enable/disable
*
* \param [in]   eControllerId   - DP core ID
* \param [in]   eStreamId       - Stream ID
* \param [in]   bEnable         - TRUE - Enable, FALSE - Disable
*
* \retval void
*
****************************************************************************/
void HAL_DP_MST_Stream_Enable(DP_ControllerIDType eControllerId,
                              DP_StreamIDType     eStreamId,
                              bool32              bEnable);

/****************************************************************************
*
** FUNCTION: HAL_DP_TriggerMSTACT()
*/
/*!
* \brief
*   The \b Trigger MST ACT (Allocation Change Trigger)
*
* \param [in]   eControllerId   - DP core ID
*
* \retval void
*
****************************************************************************/
void HAL_DP_TriggerMSTACT(DP_ControllerIDType eControllerId);

//-------------------------------------------------------------------------------------------------
//  HAL_eDP_PSR_VSC_Setup
//
//  @brief
//      Function configure VSC SDP settings for PSR on the eDP controller
//      It is the callers responsibility to set appropriate Interface Flush flags so that these settings are applied
//
//  @params
//      [IN] eControllerId
//          Controller ID.
//
//  @return
//      None 
//-------------------------------------------------------------------------------------------------
//
void HAL_eDP_PSR_VSC_Setup(DP_ControllerIDType eControllerId);

//-------------------------------------------------------------------------------------------------
//  HAL_eDP_PSR_Config
//
//  @brief
//      Function configures PSR configuration on the controller side
//
//  @params
//      [IN] eControllerId
//          Controller ID.
//      [IN] pConfig
//          config to be applied
//
//  @return
//      None 
//-------------------------------------------------------------------------------------------------
//
void HAL_eDP_PSR_Config(DP_ControllerIDType  eControllerId, HAL_DP_PSRConfigType *pConfig);

//-------------------------------------------------------------------------------------------------
//  HAL_eDP_PSR_Command
//
//  @brief
//      Function to execute PSR commands (enter, exit, etc.)
//
//  @params
//      [IN] eControllerId
//          DP controller ID.
//      [IN] eCommand
//          PSR command.
//
//  @return
//      None 
//-------------------------------------------------------------------------------------------------
//
void HAL_eDP_PSR_Command(DP_ControllerIDType  eControllerId, HAL_DP_PSR_CmdType eCommand);

//-------------------------------------------------------------------------------------------------
//  HAL_eDP_PSR_Interrupt_Status
//
//  @brief
//      Function to get PSR interrupt status
//
//  @params
//      [IN] eControllerId
//          DP controller ID.
//
//  @return
//      Bit-field of interrupts that fired 
//-------------------------------------------------------------------------------------------------
//
uint32 HAL_eDP_PSR_Interrupt_Status(DP_ControllerIDType  eControllerId);

//-------------------------------------------------------------------------------------------------
//  HAL_eDP_PSR_Interrupt_Clear
//
//  @brief
//      Function to clear PSR interrupts
//
//  @params
//      [IN] eControllerId
//          DP controller ID
//      [IN] uInterrupts
//          Bit-field of interrupts to be cleared
//
//
//  @return
//      None
//-------------------------------------------------------------------------------------------------
//
void HAL_eDP_PSR_Interrupt_Clear(DP_ControllerIDType  eControllerId, uint32 uInterrupts);

//-------------------------------------------------------------------------------------------------
//  HAL_DP_CRC_Capture
//
//  @brief
//      Function to capture the controller CRC (R, G, and B components)
//
//  @params
//      [IN] eControllerId
//          DP controller ID
//      [OUT] pCRC_R
//          CRC value for component red
//      [OUT] pCRC_G
//          CRC value for component green
//      [OUT] pCRC_B
//          CRC value for component blue
//
//
//  @return
//      HAL_MDSS_ErrorType
//-------------------------------------------------------------------------------------------------
//
HAL_MDSS_ErrorType HAL_DP_CRC_Capture(DP_ControllerIDType eControllerId,  uint16 *pCRC_R, uint16 *pCRC_G, uint16 *pCRC_B);

//-------------------------------------------------------------------------------------------------
//  HAL_DP_Enable_DoubleBuffer
//
//  @brief
//      Function to enable double-buffering for DP registers
//
//  @params
//      [IN] eControllerId
//          DP controller ID
//      [IN] bEnable
//          TRUE to enable
//
//  @return
//      None
//-------------------------------------------------------------------------------------------------
//
void HAL_DP_Enable_DoubleBuffer(DP_ControllerIDType eControllerId, bool32 bEnable);

/****************************************************************************
*
** FUNCTION: HAL_DP_GenericSDP_Enable()
*/
/*!
* \brief
*     Enable/Disable a generic SDP to send over a DP stream every frame.
*     The caller is required to flush this peripheral using FLUSH and
*     FLUSH_PERIPH
*
* \param [in] eControllerId     - Controller to enable the generic SDP for
* \param [in] eStreamId         - Stream to enable the generic SDP for
* \param [in] uGenericIndex     - Which generic sdp slot to enable/disable
* \param [in] bEnable           - True, if enabled
*
* \retval void
*
****************************************************************************/
void HAL_DP_GenericSDP_Enable(DP_ControllerIDType  eControllerId,
                              DP_MSTStreamIDType   eStreamId,
                              uint32               uGenericIndex,
                              bool32               bEnable);

/****************************************************************************
*
** FUNCTION: HAL_DP_GenericSDP_Config()
*/
/*!
* \brief
*     Configure Generic SDP sent on a DP stream.
*     The caller is required to flush this peripheral using FLUSH and
*     FLUSH_PERIPH
*
* \param [in] eControllerId         - Controller to configure
* \param [in] eStreamId             - Stream to configure
* \param [in] uGenericIndex         - Which generic sdp slot to configure
* \param [in] psGenericSDPCfg       - Generic SDP configuration
*
* \retval void
*
****************************************************************************/
void HAL_DP_GenericSDP_Config(DP_ControllerIDType          eControllerId,
                              DP_MSTStreamIDType           eStreamId,
                              uint32                       uGenericIndex,
                              HAL_DP_GenericSDPConfigType *psGenericSDPCfg);

/****************************************************************************
*
** FUNCTION: HAL_DP_VSCSDP_Enable()
*/
/*!
* \brief
*     Enable/Disable a VSC SDP to send over a DP stream every frame.
*     The caller is required to flush this peripheral using FLUSH and
*     FLUSH_PERIPH
*
* \param [in] eControllerId     - Controller to enable the generic SDP for
* \param [in] eStreamId         - Stream to enable the generic SDP for
* \param [in] bEnable           - True, if enabled
*
* \retval void
*
****************************************************************************/
void HAL_DP_VSCSDP_Enable(DP_ControllerIDType  eControllerId,
                          DP_MSTStreamIDType   eStreamId,
                          bool32               bEnable);

/****************************************************************************
*
** FUNCTION: HAL_DP_VSCSDP_Config()
*/
/*!
* \brief
*     Configure VSC SDP sent on a DP stream.
*     The caller is required to flush this peripheral using FLUSH and
*     FLUSH_PERIPH
*
* \param [in] eControllerId     - Controller to configure
* \param [in] eStreamId         - Stream to enable the generic SDP for
* \param [in] psVSCSDPCfg       - VSC SDP configuration
*
* \retval void
*
****************************************************************************/
void HAL_DP_VSCSDP_Config(DP_ControllerIDType      eControllerId,
                          DP_MSTStreamIDType       eStreamId,
                          HAL_DP_VSCSDPConfigType *psVSCSDPCfg);

/****************************************************************************
*
** FUNCTION: HAL_DP_Enable_MISR()
*/
/*!
 \brief
*     Enable DP MISR control
*
* \param [in]      eControllerId  - DP core ID
* \param [in]      bEnable        - TRUE to enable
*
****************************************************************************/
void HAL_DP_Enable_MISR(DP_ControllerIDType eControllerId, bool32 bEnable);

/****************************************************************************
*
** FUNCTION: HAL_DP_Get_Frame_CRC()
*/
/*!
* \brief
*     Enable CRC Capture
*
* \param [in]      eControllerId  - DP core ID
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Get_Frame_CRC(DP_ControllerIDType eControllerId, uint64 *pCRC);

/****************************************************************************
*
** FUNCTION: HAL_DP_LinkInterfaceClockGatingEnable()
*/
/*!
* \brief
*     Set the link interface clock gating enable to DP PHY based on 
*     if in tunneling mode
*
* \param [in]      eControllerId  - DP core ID
* \param [in]      bTunneledMode  - Boolean used to indicate if in DP
*                                   tunneling mode
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_LinkInterfaceClockGatingEnable(DP_ControllerIDType eControllerId,
                                                         bool32              bTunnelingMode);

/****************************************************************************
*
** FUNCTION: HAL_DP_ConfigureLinkInterfaceMode()
*/
/*!
* \brief
*     Configure DP controller link interface to be in tunneled mode or
*     native DP mode
*
* \param [in]      eControllerId  - DP core ID
* \param [in]      bTunneledMode  - Boolean used to indicate if in DP
*                                   tunneling mode
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_ConfigureLinkInterfaceMode(DP_ControllerIDType eControllerId,
                                                     bool32              bTunnelingMode);


#endif // _HAL_DP_H_
