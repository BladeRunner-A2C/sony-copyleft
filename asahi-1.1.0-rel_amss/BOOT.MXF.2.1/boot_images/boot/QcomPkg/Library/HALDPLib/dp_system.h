#ifndef _DP_SYSTEM_H_
#define _DP_SYSTEM_H_
/*! \file */
/*=====================================================================================================
 
  File: dp_system.h
 
  Header file for DP system level utility functions 
   
  Copyright (c) 2016-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
====================================================================================================*/
#include "MDPSystem.h"
#include "dp_host.h"
#include "dp_types.h"
#include "hal_dp.h"
#include "MDPLib_i.h"
#include "displayid.h"

/* --------------------------------------------------------------------------------------------------------------------
  Defines
---------------------------------------------------------------------------------------------------------------------*/


/* Convenience macro to print file name and line number in debug messages
*/
#define DP_LOG_MESSAGE_ERROR(fmt, ...)     MDP_Log_Message(MDP_LOGLEVEL_ERROR, fmt, ##__VA_ARGS__)
#define DP_LOG_MESSAGE_WARN(fmt,  ...)     MDP_Log_Message(MDP_LOGLEVEL_WARN, fmt, ##__VA_ARGS__)
#define DP_LOG_MESSAGE_INFO(fmt,  ...)     MDP_Log_Message(MDP_LOGLEVEL_INFO, fmt, ##__VA_ARGS__)
#define DP_LOG_MESSAGE_TRACE(fmt, ...)     MDP_Log_Message(MDP_LOGLEVEL_INFO, fmt, ##__VA_ARGS__)

#define TraceInfo(flags, fmt, ...)         MDP_Log_Message(MDP_LOGLEVEL_INFO, fmt"\n", ##__VA_ARGS__)
#define TraceVerb(flags, fmt, ...)         MDP_Log_Message(MDP_LOGLEVEL_INFO, fmt"\n", ##__VA_ARGS__)

#define HAL_DP_SLEEP_US(_DelayUs_)         DP_OSAL_SleepUs(_DelayUs_)
#define HAL_DP_SLEEP_MS(_Delayms_)         DP_OSAL_SleepMs(_Delayms_)
#define HAL_DP_STALL_US(_DelayUs_)         DP_OSAL_SleepUs(_DelayUs_)

#define DISP_OSAL_Malloc(x1, x2)                              MDP_OSAL_CALLOC(x1)
#define DISP_OSAL_Free(x1)                                    MDP_OSAL_FREE(x1)
#define DISP_OSAL_MemZero(x1, x2)                             MDP_OSAL_MEMZERO(x1, x2)
#define DISP_OSAL_MemSet(x1, x2, x3)                          MDP_OSAL_MEMSET(x1, x2, x3)
#define DISP_OSAL_MemCpy(x1, x2, x3)                          MDP_OSAL_MEMCPY(x1, x2, x3)
#define DISP_OSAL_MemCpyEx(x1, l1, x2, l2)                    MDP_OSAL_MEMCPY(x1, x2, l2)
#define DISP_OSAL_StrCmpSb(x1, x2, x3)                        strcmp((const char *)x1, (const char *)x2)

#define DISP_OSAL_LOG(fmt, ...)                               MDP_Log_Message(MDP_LOGLEVEL_ERROR, fmt, ##__VA_ARGS__)
#define DISP_OSAL_LOG1(fmt, ...)                              MDP_Log_Message(MDP_LOGLEVEL_ERROR, fmt, ##__VA_ARGS__)
#define DISP_OSAL_LOGX(fmt, ...)                              MDP_Log_Message(MDP_LOGLEVEL_ERROR, fmt, ##__VA_ARGS__)
#define DISP_OSAL_LOG_WARN(fmt, ...)                          MDP_Log_Message(MDP_LOGLEVEL_WARN, fmt, ##__VA_ARGS__)
#define DISP_OSAL_LOG_WARN1(fmt, ...)                         MDP_Log_Message(MDP_LOGLEVEL_WARN, fmt, ##__VA_ARGS__)
#define DISP_OSAL_LOG_WARNX(fmt, ...)                         MDP_Log_Message(MDP_LOGLEVEL_WARN, fmt, ##__VA_ARGS__)
#define DISP_OSAL_LOG_INFO(fmt, ...)                          MDP_Log_Message(MDP_LOGLEVEL_INFO, fmt, ##__VA_ARGS__) 

#define DISP_OSAL_WaitEvent(x1, x2)                           DP_OSAL_DummySuccess(NULL, x1, x2)
#define DISP_OSAL_ResetEvent(x1)                              DP_OSAL_DummySuccess(NULL, x1) 
#define DISP_OSAL_AcquireLockEvent(x1, x2)                    DP_OSAL_DummySuccess(NULL, x1, x2) 
#define DISP_OSAL_ReleaseLockEvent(x1)                        DP_OSAL_DummySuccess(NULL, x1) 
#define DISP_OSAL_CreateLockEvent(x1, x2)                     DP_OSAL_DummySuccess(NULL, x1, x2)   
#define DISP_OSAL_DestroyLockEvent(x1)                        DP_OSAL_DummySuccess(NULL, x1)  
#define DISP_OSAL_CreateEvent(x1, x2)                         DP_OSAL_DummySuccess(NULL, x1, x2)
#define DISP_OSAL_SetEvent(x1)                                DP_OSAL_DummySuccess(NULL, x1)  
#define DISP_OSAL_DestroyEvent(x1)                            DP_OSAL_DummySuccess(NULL, x1)

#define DISP_OSAL_GetTimeEx()                                 MDP_GetTimerCountMS()

#define DISP_OSAL_EVENTLOG4(fmt, ...)
#define DISP_OSAL_EVENTLOG3(fmt, ...)

#define DISP_OSAL_StallUs(_DelayUs_)                          DP_OSAL_SleepUs(_DelayUs_)
#define DISP_OSAL_SleepMs(_DelayMs_)                          DP_OSAL_SleepMs(_DelayMs_)

/* Memory barrier macro, create a CPU memory barrier to ensure all commands prior to this are completed */
#define DP_OSAL_MB                         (KeMemoryBarrier)

/* Get the MIN of two values */
#define DP_MIN(a,b)                                  (((a) > (b)) ? (b) : (a))

/* Get the MAX of two values */
#define DP_MAX(a,b)                                  (((a) > (b)) ? (a) : (b))

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)                    ((void)(P))
#endif

/* DP work item function type, launched by DP_LaunchWorkItem */
typedef void (DP_WorkThread)(void *pDeviceObject, void *pContext);

/*---------------------------------------------------------------------------------------------------------------------
  Flags
---------------------------------------------------------------------------------------------------------------------*/
/* 
 * DP_MainClockConfig Flags
 */


/*---------------------------------------------------------------------------------------------------------------------
  Functions
---------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************

FUNCTION: DP_LinkClockEnable()
   
  This function will set up the DP link clocks.

Parameters:
  hHandle      -[in]    : Handle to DP device
  bPLLSource   -[in]    : TRUE: main clock sourcing from DP PLL, FALSE: main clock sourcing from CXO

Return: 
  DP_Status

**********************************************************************************************************************/
DP_Status DP_LinkClockEnable(DP_HandleType        hHandle,
                             bool32               bPLLSource);

/**********************************************************************************************************************

FUNCTION: DP_PixelClockEnable()
   
  This function will set up the DP pixel clocks; must be called after MND have been calculated.

Parameters:
  hHandle      -[in]    : Handle to DP device
  pPixClkDivs  -[in]    : Pointer to Pixel clock divider info.
  bPLLSource   -[in]    : TRUE: main clock sourcing from DP PLL, FALSE: main clock sourcing from CXO

Return: 
  DP_Status

**********************************************************************************************************************/
DP_Status DP_PixelClockEnable(DP_HandleType        hHandle,
                              DP_PixelClk_Info    *pPixClkDivs,
                              bool32               bPLLSource);

/**********************************************************************************************************************

FUNCTION: DP_ParkLinkAndPixelClockSources()
   
  This function will park the DP link and pixel clock sources to CXO.

Parameters:
  hHandle      -[in]    : Handle to DP device

Return: 
  DP_Status

**********************************************************************************************************************/
DP_Status DP_ParkLinkAndPixelClockSources(DP_HandleType hHandle);

/**********************************************************************************************************************

FUNCTION: DP_ConfigureAllClocks()

  This function will enable/disable all the DP clocks.

Parameters:
  hHandle      -[in]    : Handle to DP device

Return: 
  DP_Status

**********************************************************************************************************************/
DP_Status DP_ConfigureAllClocks(DP_HandleType hHandle, bool32 bEnable);

/**********************************************************************************************************************

FUNCTION: DP_WaitForLinkStatus()
   This function will wait for the main link to reach the specified state

Parameters:
   hHandle    -[in]    : Handle to DP device
   eLinkState -[in]    : Main link state type

Return: 
   DP_Status

**********************************************************************************************************************/
DP_Status DP_WaitForLinkStatus(DP_HandleType           hHandle,
                               HAL_DP_LinkStatusType   eLinkState);

/**********************************************************************************************************************

FUNCTION: DP_GetHPDPollTime()
   
  This function will get the user requested HPD polling time in ms

Parameters:

Return: 
  DP_Status

**********************************************************************************************************************/
uint32 DP_GetHPDPollTime();

/**********************************************************************************************************************

FUNCTION: DP_PhyDataPathIsReverse()
   
  This function will check if the DP PHY data path is reverse of USB type-C specification

Parameters:
  hHandle      -[in]    : Handle to DP device

Return: 
  bool32      TRUE - reverse of spec      FALSE - as per spec 
  
**********************************************************************************************************************/
bool32 DP_PhyDataPathIsReverse(DP_HandleType        hHandle);

/**********************************************************************************************************************

FUNCTION: DP_DualPixelModeSupported()
   
  This function will check if Dual pixel mode is supported.

Parameters:
  hHandle      -[in]    : Handle to DP device

Return: 
  bool32      TRUE - Dual pixel mode     FALSE - Single pixel mode
  
**********************************************************************************************************************/
bool32 DP_DualPixelModeSupported(DP_HandleType        hHandle);

/**********************************************************************************************************************

FUNCTION: DP_ConfigureGPIOState()

  This function will set GPIO resource state to specified level

Parameters:
  hHandle           -[in]    : Handle to DP device
  eGpioResourceType -[in]    : GPIO resource type
  uGpioState        -[in]    : GPIO level, low (0) or high (1)

Return:
  DP_Status

**********************************************************************************************************************/
DP_Status DP_ConfigureGPIOState(DP_HandleType           hHandle,
                                DP_GPIOResourceType     eGpioResourceType,
                                uint8                   uGpioState);

/**********************************************************************************************************************

FUNCTION: DP_CheckConnectionStatus()

  This function will check cable connection status

Parameters:
  hHandle    -[in]    : Handle to DP device

Return:
  DP_Status

**********************************************************************************************************************/
DP_Status DP_CheckConnectionStatus(DP_HandleType        hHandle);

/**********************************************************************************************************************

FUNCTION: DP_SetHostRouterBaseAddress()

   This function will set host router and qmp phy base address

Parameters:

Return:
   DP_Status

**********************************************************************************************************************/
DP_Status DP_SetHostRouterBaseAddress(void);

/**********************************************************************************************************************
*
** FUNCTION: DP_OSAL_MemSet()
*/
/*!
* \brief
*   The \b MDSS_OSAL_MemSet function fills the buffer with the uFillValue
*
* \param [in]   pBuffer           - Input buffer pointer
* \param [in]   uFillValue        - Value to be filled into the buffer
* \param [in]   uSizeInBytes      - Buffer size to be filled
*
* \return void
*
**********************************************************************************************************************/
void DP_OSAL_MemSet(void *pBuffer, uint8 uFillValue, uint32 uSizeInBytes);

/**********************************************************************************************************************
*
** FUNCTION: DP_OSAL_MemCpy()
*/
/*!
* \brief
*   The \b DP_OSAL_MemCpy function copies bytes from one buffer to another
*
* \param [in]   pDst             - a pointer to where you want the function to copy the data
* \param [in]   pSrc             - a pointer to the buffer that you want to copy data from
* \param [in]   uSizeInBytes     - the number of bytes to copy
*
* \return void
*
**********************************************************************************************************************/
void DP_OSAL_MemCpy(void *pDst, void *pSrc, uint32 uSizeInBytes);

/**********************************************************************************************************************
*
** FUNCTION: DP_OSAL_MemCpyEx()
*/
/*!
* \brief
*   The \b DP_OSAL_MemCpy function copies bytes from one buffer to another with ranges 
*
* \param [in]   pDst             - a pointer to where you want the function to copy the data
* \param [in]   uDstSize         - the size of the destination buffer in bytes
* \param [in]   pSrc             - a pointer to the buffer that you want to copy data from
* \param [in]   uSrcSize         - the size of the source buffer in bytes
*
* \return void
*
**********************************************************************************************************************/
void DP_OSAL_MemCpyEx(void *pDst, uint32 uDstSize, void *pSrc, uint32 uSrcSize);

/**********************************************************************************************************************
*
** FUNCTION: DP_OSAL_SleepMs()
*/
/*!
* \brief
*   The \b DP_OSAL_SleepMs function sleeps for a specific period
*
* \param [in]  uMilliSeconds - sleep time in millisecond
*
* \retval void
*
**********************************************************************************************************************/
void DP_OSAL_SleepMs(uint32 uMilliSeconds);

/**********************************************************************************************************************
*
** FUNCTION: DP_OSAL_SleepUs()
*/
/*!
* \brief
*   The \b DP_OSAL_SleepUs function sleeps for a specific period
*
* \param [in]  uMicroSeconds - sleep time in microsecond
*
* \retval void
*
**********************************************************************************************************************/
void DP_OSAL_SleepUs(uint32 uMicroSeconds);

/**********************************************************************************************************************
*
** FUNCTION: DP_OSAL_StallUs()
*/
/*!
* \brief
*   The \b DP_OSAL_StallUs function stall for a specific period
*
* \param [in]  uMicroSeconds - stall time in microsecond
*
* \retval void
*
**********************************************************************************************************************/
void DP_OSAL_StallUs(uint32 uMicroSeconds);

/**********************************************************************************************************************

FUNCTION: DP_ParseEDID()

  This function will parse the EDID info 

Parameters:
  hHandle    -[in]    : Handle to DP device

Return:
  DP_Status

**********************************************************************************************************************/
DP_Status DP_ParseEDID(DP_HandleType   hHandle);

/**********************************************************************************************************************

FUNCTION: DP_SetFailSafeEDID()

  This function will generate fail-safe mode EDID and overwrite the device context.

Parameters:
  hHandle    -[in]    : Handle to DP device

Return:
  DP_Status

**********************************************************************************************************************/
DP_Status DP_SetFailSafeEDID(DP_HandleType   hHandle);

//-------------------------------------------------------------------------------------------------
//  DP_SoftHPDInterrupt
//
//  @brief
//      Generate soft HPD plug/unplug interrupt for a display
//
//  @params
//      [IN] eDisplayId
//          QDI display ID.
//      [IN] bPlugIn
//          TRUE: HPD in, FALSE: HPD out.
//
//  @return
//      void.
//-------------------------------------------------------------------------------------------------
//
void DP_SoftHPDInterrupt(MDP_Display_IDType eDisplayId, 
                         bool32             bPlugIn);
 
//-------------------------------------------------------------------------------------------------
//  DP_GetMaxPixelRate
//
//  @brief
//      Gets the max pixel rate
//
//  @params
//      none
//
//  @return
//      uint32.
//-------------------------------------------------------------------------------------------------
//
uint32 DP_GetMaxPixelRate(void);


//-------------------------------------------------------------------------------------------------
//  DP_CreateWorkItem
//
//  @brief
//      Create Work Item from Physical Device Object(PDO) for IRQ HPD worker thread
//
//  @params
//      phHPDWorkItem    -[out]    : pointer to work item handle
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_CreateWorkItem(DP_HandleType    *phHPDWorkItem);


//-------------------------------------------------------------------------------------------------
//  DP_DestroyWorkItem
//
//  @brief
//      Destroy Work Item from PDO
//
//  @params
//      phHPDWorkItem    -[in/out]    : pointer to work item handle
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_DestroyWorkItem(DP_HandleType    *phHPDWorkItem);

//-------------------------------------------------------------------------------------------------
//  DP_LaunchWorkItem
//
//  @brief
//      Launch Work thread to handle HPD event
//
//  @params
//       hHPDWorkItem    -[in]    : Handle to DP work item
//       pFunction       -[in]    : Function pointer to worker thread
//       pContext        -[in]    : pointer to context of DP work item.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_LaunchWorkItem(DP_HandleType  hHPDWorkItem, DP_WorkThread pFunction, void *pContext);


//-------------------------------------------------------------------------------------------------
//  DP_GetDisplayContainerGUID
//
//  @brief
//       Get Display container GUID from miniport driver.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context handle.
//      [out] pGUID
//          GUID string to be read.
//      [IN] uGUIDSize
//          size of GUID string.
//
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
DP_Status DP_GetDisplayContainerGUID(DP_DeviceIDType eDeviceID, DP_MSTStreamIDType eMSTStreamId, uint8* pGUID, uint32 uGUIDSize);


//-------------------------------------------------------------------------------------------------
//  DP_GetMaxAvailableBw
//
//  @brief
//      Calculate the max capable BW based on current config
//
//  @params
//      pDisplayCtx  -[in]    : DP Display Context
//
//  @return
//      uint64 
//-------------------------------------------------------------------------------------------------
//
uint64 DP_GetMaxAvailableBw(DP_HandleType   hHandle);

//-------------------------------------------------------------------------------------------------
//  DP_GetLinkRate
//
//  @brief
//      Get the current link rate supported considering FEC state
//      and accounting for its overhead
//
//  @params
//      pDisplayCtx  -[in]    : DP Display Context
//
//  @return
//      uint64 
//-------------------------------------------------------------------------------------------------
//
uint32 DP_GetLinkRate(DP_HandleType   hHandle);

//-------------------------------------------------------------------------------------------------
//  DP_OSAL_DummySuccess
//
//  @brief
//      Dummy success function for DISP_OSAL_...() calls
//
//  @params
//      pDummyArg  -[in]    : Dummy parametr
//
//  @return
//      uint64 
//-------------------------------------------------------------------------------------------------
//
MDP_Status DP_OSAL_DummySuccess(void *pDummyArg, ...);

//-------------------------------------------------------------------------------------------------
//  DP_Ceil
//
//  @brief
//      This function will get the Ceiling of double value.
//
//  @params
//      [IN] dNumber
//          Take Ceiling of this number
//
//  @return
//      int32.
//-------------------------------------------------------------------------------------------------
//
int DP_Ceil(double Number);

//-------------------------------------------------------------------------------------------------
//  DP_Strncmp
//
//  @brief
//      This function will get the Ceiling of double value.
//
//  @params
//      [IN] pStr1
//          String 1 pointer
//      [IN] pStr2
//          String 2 pointer
//      [IN] n
//          size in bytes
//
//  @return
//      0 When success
//-------------------------------------------------------------------------------------------------
//
int32 DP_Strncmp(const uint8 *pStr1, const uint8 *pStr2, uint32 n);

#endif //_DP_SYSTEM_H_
