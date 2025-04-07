#ifndef _DP_HOST_H_
#define _DP_HOST_H_
/*! \file */

/*=============================================================================
 
  File: dp_host.h
 
  DP Host layer header file
  
 
 Copyright (c) 2016-2020 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
 =============================================================================*/

#include "hal_dp.h"
#include "dp_types.h"


/* --------------------------------------------------------------------------------------------------------------------
** Macros and Struct
---------------------------------------------------------------------------------------------------------------------*/
#define DPHOST_CHECK_DP_TUNNELING_MODE(_devicectx_) (TRUE == ((_devicectx_)->sTunnelingModeConfig.bTunnelingMode))

/* DP flags */
typedef uint32               DP_FlagsType;


/* --------------------------------------------------------------------------------------------------------------------
Enumerated types
---------------------------------------------------------------------------------------------------------------------*/
/*! 
 * \b DP_Status
 *
 * Enumeration giving return values from DP function calls.
 *
 */
typedef enum
{
   DP_STATUS_SUCCESS                              = 0x0000,
   DP_STATUS_FAIL,
   DP_STATUS_FAILED_INVALID_INPUT_PARAMETER,
   DP_STATUS_FAILED_TIMEOUT,
   DP_STATUS_FAILED_RESOURCE_FATAL_ERROR,
   DP_STATUS_FAILED_RESOURCE_FAILED,   
   DP_STATUS_FAILED_RESOURCE_NOT_READY,
   DP_STATUS_FAILED_DRIVER_ALREADY_INITIALIZED,
   DP_STATUS_FAILED_DRIVER_NOT_INITIALIZED,
   DP_STATUS_FAILED_NOT_SUPPORTED,
   DP_STATUS_FAILED_PKT_LENGTH_EXCEED,
   DP_STATUS_FAILED_LINK_TRAINING,
   DP_STATUS_FAILED_NAK,
   DP_STATUS_FAILED_AUX_NACK_DEFER,
   DP_STATUS_MAX,
   DP_STATUS_FORCE_32BIT                          = 0x7FFFFFFF
} DP_Status;

/*! 
 * \b DP_LogLevel
 *
 * Enumeration giving DP debug log levels.
 *
 */
typedef enum 
{
  DP_LOGLEVEL_ERROR,
  DP_LOGLEVEL_WARNING,
  DP_LOGLEVEL_INFO,
  DP_LOGLEVEL_TRACE,
} DP_LogLevel;

//-------------------------------------------------------------------------------------------------
//  DP_InterruptType
//
//  @brief
//      DP interrupt type.
//
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
   DP_INTR_TYPE_NONE                           = 0x00000000,
   DP_INTR_TYPE_HPD                            = DP_BIT(1),  /**< Indicates Sink has request via HDP pin. */
   DP_INTR_TYPE_AUX_I2C_DONE                   = DP_BIT(2),  /**< Indicates AUX/I2C transaction is done.  */
   DP_INTR_TYPE_WRONG_ADDRESS                  = DP_BIT(3),  /**< Indicates wrong AUX address was given.  */
   DP_INTR_TYPE_CONSECUTIVE_TIMEOUT            = DP_BIT(4),  /**< AUX/I2C has timed out consecutively.    */
   DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER         = DP_BIT(5),  /**< AUX/I2C has NACK/DEFER consecutively.   */
   DP_INTR_TYPE_WRONG_READDATA_COUNT           = DP_BIT(6),  /**< # of read data bytes is not expected.   */
   DP_INTR_TYPE_AUX_NACK_DURING_I2C            = DP_BIT(7),  /**< AUX NACK`ed during an I2C transaction.  */
   DP_INTR_TYPE_AUX_DEFER_DURING_I2C           = DP_BIT(8),  /**< AUX DEFER`ed during an I2C transaction. */
   DP_INTR_TYPE_PLL_UNLOCK_DET                 = DP_BIT(9),  /**< Indicates PLL in DP PHY has unlocked.   */
   DP_INTR_TYPE_DPPHY_AUX_ERROR                = DP_BIT(10), /**< Indicates DPPHY AUX detected an error.  */
   DP_INTR_TYPE_READY_FOR_VIDEO                = DP_BIT(11), /**< DP HW is ready to receive video.        */
   DP_INTR_TYPE_IDLE_PATTERNS_SENT             = DP_BIT(12), /**< Idle patterns are sent after push idle. */
   DP_INTR_TYPE_FRAME_END                      = DP_BIT(13), /**< Indicate end of a frame.                */
   DP_INTR_TYPE_CRC_UPDATED                    = DP_BIT(14), /**< Indicate MISR registers have new values.*/
   DP_INTR_TYPE_AUX_RX_STOP_ERR                = DP_BIT(15), /**< Indicate STOP pattern error on AUX RX.  */
   DP_INTR_TYPE_AUX_RX_DEC_ERR                 = DP_BIT(16), /**< Indicate Data decode error on AUX RX.   */
   DP_INTR_TYPE_AUX_RX_SYNC_ERR                = DP_BIT(17), /**< Indicate SYNC pattern error on AUX RX.  */
   DP_INTR_TYPE_AUX_RX_ALIGN_ERR               = DP_BIT(18), /**< RX received less than 8 bits data.      */
   DP_INTR_TYPE_AUX_TX_REQ_ERR                 = DP_BIT(19), /**< REQ. signal is late on TX.              */
   DP_INTR_TYPE_ENCRYPTION_READY               = DP_BIT(20), /**< Encryption ready interrupt.             */
   DP_INTR_TYPE_ENCRYPTION_NOT_READY           = DP_BIT(21), /**< Encryption not ready interrupt.         */
   DP_INTR_TYPE_AUTH_SUCCESS                   = DP_BIT(22), /**< HDCP1.3 authentication ready.           */
   DP_INTR_TYPE_AUTH_FAIL                      = DP_BIT(23), /**< HDCP1.3 authentication failed.          */
   DP_INTR_TYPE_HPD_PLUG_INT                   = DP_BIT(24), /**< Indicate cable plug event               */
   DP_INTR_TYPE_HPD_IRQ_INT                    = DP_BIT(25), /**< This event is a Sink to Source interrupt
                                                                  request while the devices are deemed to 
                                                                  be connected.                           */
   DP_INTR_TYPE_HPD_REPLUG_INT                 = DP_BIT(26), /**< This event is a Sink to Source 'Replug' 
                                                                  notification generated to inform the 
                                                                  Source that a broader change has occurred 
                                                                  in the Sink such that the Source needs to 
                                                                  start at the initial connect capability 
                                                                  check of the Sink                       */
   DP_INTR_TYPE_HPD_UNPLUG_INT                 = DP_BIT(27), /**< Indicate cable unplug event             */
   DP_INTR_TYPE_HPD_ALL                        = DP_INTR_TYPE_HPD_IRQ_INT | DP_INTR_TYPE_HPD_REPLUG_INT | DP_INTR_TYPE_HPD_UNPLUG_INT, /* HDP_PLUG_INT is not used */
   DP_INTR_TYPE_MAX,
   DP_INTR_TYPE_FORCE_32BIT                    = 0x7FFFFFFF
} DP_InterruptType;

/* --------------------------------------------------------------------------------------------------------------------
  Defines
---------------------------------------------------------------------------------------------------------------------*/

// Invalid DP mode
#define DP_HOST_MODE_INVALID    (uint32)-1


// Define for all AUX transaction based interrupts to be used by ISR(DPDriver_DecodeAndClear) for interrupt decoding
#define DP_AUX_TRANSACTION_INTR_ALL    (DP_INTR_TYPE_AUX_I2C_DONE              |\
                                        DP_INTR_TYPE_WRONG_ADDRESS             |\
                                        DP_INTR_TYPE_CONSECUTIVE_TIMEOUT       |\
                                        DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER    |\
                                        DP_INTR_TYPE_WRONG_READDATA_COUNT      |\
                                        DP_INTR_TYPE_AUX_NACK_DURING_I2C       |\
                                        DP_INTR_TYPE_AUX_DEFER_DURING_I2C      |\
                                        DP_INTR_TYPE_DPPHY_AUX_ERROR)

// Define for all interrupts that are related to each stream
// TODO, add other stream related interrupts and handling
//    SDP#_COLLISION_INT
//    MST#_ML_FIFO_OVERFLOW_INT
//    MST_DP#_VCPF_SENT_INT
#define DP_STREAM_INTERRUPT_ALL         DP_INTR_TYPE_FRAME_END

// Define the type of interrupt event to pass to DP_Host_SetProperty under DP_SETPROPERTY_SIGNAL_EVENT.
typedef enum
{
  DP_EVENT_NONE                = 0x00000000,
  DP_EVENT_AUX_WAIT            = 0x00000001,    //Signal AUX interrupt event
  DP_EVENT_IRQ_HPD             = 0x00000002,    //Signal IRQ HPD interrupt event
  DP_EVENT_REPLUG_HPD          = 0x00000004,    //Signal replug HPD interrupt event
  DP_EVENT_HPD_IN              = 0x00000008,    //Signal HPD in interrupt event
  DP_EVENT_HPD_OUT             = 0x00000010,    //Signal HPD out interrupt event
  DP_EVENT_FORCE_32BIT         = 0x7FFFFFFF
} DP_Event_Type;


/* --------------------------------------------------------------------------------------------------------------------
  Functions
---------------------------------------------------------------------------------------------------------------------*/

/*********************************************************************************************
*
** FUNCTION: DP_Host_Init()
*/
/*!
* \DESCRIPTION
*        This init function must be called before any host layer functions. 
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Host_Init(void);

/*********************************************************************************************
*
** FUNCTION: DP_Host_Deinit()
*/
/*!
* \DESCRIPTION
*        This deinit function must be called to fully terminate DP host. 
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Host_Deinit();
 
/*********************************************************************************************
*
** FUNCTION: DP_Host_Open()
*/
/*!
* \DESCRIPTION
*        This init function must be called before any other DP function is called 
*
* \param [out]  phHandle        - Pointer to handle of DP Device
* \param [in]   psOpenConfig    - Pointer to host open configuration  
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Host_Open(DP_HandleType               *phHandle,
                        DP_HostOpenConfigType       *psOpenConfig);

/**********************************************************************************************************************

FUNCTION: DP_Host_Power()
   
   This API is called to de-initialize the corresponding resources that is initialized when DP_Open() is called.
   It will return an error if the device handle is invalid. All resources will be de-initialized . User should ensure 
   that no other DP function will be called before another DP_Open() were called. otherwise corresponding error will 
   be returned to the user. Upon an invalid device handle, this call will also return an error.

Parameters:
    hHandle              - [in] handle to DP device 
    bPowerEnable         - [in] Power on/off

Return: 
   DP_Status 

**********************************************************************************************************************/
DP_Status  DP_Host_Power(DP_HandleType hHandle, bool32 bPowerEnable);

/**********************************************************************************************************************

FUNCTION: DP_Host_Close()
   
   This API is called to free the dynamically allocated DP host layer handle, which needs to be kept even after 
   DPDriver_Power Down path.

Parameters:
    hHandle              - [in] handle to DP device 

Return: 
   DP_Status 

**********************************************************************************************************************/
DP_Status  DP_Host_Close(DP_HandleType    hHandle);

/*********************************************************************************************
*
** FUNCTION: DP_Host_Commit()
*/
/*!
* \DESCRIPTION
*  This API allows users to commit all the settings and apply to H/W. 
*
* \param [in]   hHandle           - Handle to DP device
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Host_Commit(DP_HandleType    hHandle);

/*********************************************************************************************
*
** FUNCTION: DP_Host_SetProperty()
*/
/*!
* \DESCRIPTION
*      Allows the user to set the attributes and properties of the DP device
*
* \param [in]   hHandle        - Handle to DP Device
* \param [in]   ePropertyType  - Property ID that requires update
* \param [in]   pPropertyData  - Parameters of the property to be applied
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Host_SetProperty(DP_HandleType                   hHandle,
                               DP_SetPropertyType              ePropertyType,
                               DP_SetPropertyParamsType       *pPropertyData);

/*********************************************************************************************
*
** FUNCTION: DP_Host_GetProperty()
*/
/*!
* \DESCRIPTION
*      Allows the user to query the attributes and properties of the DP device
*
* \param [in]      hHandle        - Handle to DP device
* \param [in]      ePropertyType  - Property ID query
* \param [in/out]  pPropertyData  - Parameters of the property that will be returned
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_Host_GetProperty(DP_HandleType                   hHandle,
                              DP_GetPropertyType              ePropertyType,
                              DP_GetPropertyParamsType       *pPropertyData);

#endif //_DP_HOST_H_
