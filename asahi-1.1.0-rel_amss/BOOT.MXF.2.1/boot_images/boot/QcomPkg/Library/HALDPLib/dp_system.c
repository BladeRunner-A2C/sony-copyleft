/*=====================================================================================================
  Copyright (c) 2016-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
====================================================================================================*/
#include "dp_i.h"
#include "dp_system.h"
#include "edid.h"
#include "displayid.h"
#include "dp_spec.h"
#include "dp_dsc.h"
#include "MDPEDID.h"

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------
 * DEFINES
 *----------------------------------------------------------------------------*/

// DP wait time 
#define DP_LINK_STATUS_TIMEOUT_US                                   20000      // 20 ms; workaround value to mitigate issue where HW takes longer than expected to update link status
#define DP_LINK_STATUS_POLL_INTERVAL_US                             1000       // 1 ms
#define DP_HPD_POLL_TIME_MS                                         16         // 16 ms
#define DP_IRQ_EXIT_WAITTIME_MS                                     6000       // 360 frames (@ 60 fps)
#define DP_HPD_ENABLE_WAIT_TIME_MS                                  10         // 10 ms (reduced wait for polling mode, HPD engine not used)
#define EDP_HPD_ENABLE_WAIT_TIME_MS                                 200        // 200 ms (eDP1.3/1.4 spec is < 200ms, eDP1.4a spec is < 80ms)
#define HPD_ENABLE_POLL_INTERVAL_TIME_MS                            10         // 10 ms
#define DP_TUNNELING_HPD_ENABLE_WAIT_TIME_MS                        50         // 50 ms buffer; tunneled HPD packet propagation delay over USB4/TBT3 fabric not deterministic

/* Top level registry paths
*/
#define DP_PAL_REG_IRQPOLLING                                       L"Miniport\\IRQPolling"

/* IRQPolling detection keys
*/
#define DP_PAL_REGKEY_IRQ_POLLING_INTERVAL_MS                       L"IRQPollingIntervalMS"

/* Override link rate
*/
#define DP_PAL_REGKEY_LINKRATE_OVERRIDE                             L"LinkRateOverride1"

/* Default pixel rate
*/
#define DP_DEFAULT_PIXEL_RATE                                       2073600

/* CXO clock 19.2Mhz 
*/
#define DP_CXO_CLOCK_FREQ                                           19200000

/* Data bits transmitted per link clock cycle
*/
#define DP_BITS_PER_LINKCLK_CYCLE                                   8

/* Ratio between link clock to link interface clock, which is hard wired in HW 
*/
#define DP_LINKCLK_LINKINTFCLK_RATIO                                4

/* Bit mask for GPIO status read from ACPI 
*/
#define GPIO_STATUS_BIT_0_MASK                                      0x01
#define GPIO_STATUS_BIT_1_MASK                                      0x02

// Get Clock type for DP controller
#define DP_GETCLOCKTYPE(_id_)                                       (DP_CONTROLLER_ID_MAX > (_id_) ? DP_Clocks_5xx[(_id_)] : MDP_CLOCKTYPE_MAX)


/*------------------------------------------------------------------------------
 * Static data
 *----------------------------------------------------------------------------*/

/* DP controller to clock type map */
static const MDPClockTypes DP_Clocks_5xx[DP_CONTROLLER_ID_MAX] =
{
  MDP_CLOCKTYPE_MAX,        // DP_CONTROLLER_ID_NONE
  MDP_CLOCKTYPE_DP0,        // DP_CONTROLLER_ID_DP_0
  MDP_CLOCKTYPE_DP1,        // DP_CONTROLLER_ID_DP_1
  MDP_CLOCKTYPE_DP2,        // DP_CONTROLLER_ID_DP_2
  MDP_CLOCKTYPE_DP3,		    // DP_CONTROLLER_ID_DP_3
};

/*------------------------------------------------------------------------------
 * Global Data Definitions
 *----------------------------------------------------------------------------*/
const GUID sDisplayGUID[MDP_DISPLAY_MAX] = 
{
  {0xCA1D40E0, 0x525C, 0x4BA2, {0xBE, 0x72, 0xC8, 0x06, 0x38, 0x35, 0x05, 0xA2}},
  {0x787794FA, 0x8475, 0x447E, {0xB5, 0x63, 0xA2, 0x73, 0x41, 0x8B, 0x26, 0x3A}},
  {0x46A2EBD6, 0x84A9, 0x4E78, {0x93, 0x72, 0xE7, 0x8C, 0x8B, 0xF4, 0x69, 0x06}},
  {0x77335CB8, 0xCC94, 0x4AAC, {0x99, 0x0E, 0x13, 0x93, 0xFF, 0x79, 0x3F, 0x87}},
  {0x3A15D818, 0x1C93, 0x483D, {0x8E, 0x06, 0x84, 0xBC, 0x6C, 0x80, 0x25, 0x3C}},
  {0x5F526987, 0x73CE, 0x4940, {0x95, 0x0D, 0x84, 0x2F, 0xA3, 0x79, 0x6E, 0x7A}},
  {0xBE323D9F, 0x1E00, 0x421C, {0x9B, 0x53, 0x19, 0x23, 0xC4, 0xEC, 0x26, 0xFE}},
  {0x95F7546F, 0x2483, 0x4520, {0xA1, 0x1C, 0xE6, 0x42, 0x93, 0xCE, 0x6B, 0xC7}},
};

/*------------------------------------------------------------------------------
 * Local Prototypes
 *----------------------------------------------------------------------------*/
static DP_Status ParkPixelClock(MDP_Display_IDType  eDisplayID,
                                DP_ControllerIDType eControllerID,
                                DP_MSTStreamIDType  eMSTStreamId);

static DP_Status UpdateModeListToDisplayContext(DP_DisplayCtxType *pDisplayCtx,
                                                   EDID_DispModeListType *psModeList,
                                                   EDID_DisplayRangeInfo *pDisplayRangeDesc);

static DP_Status AdjustPreferredMode(uint32 uPreferredModeIndex,
                                        DP_StreamCtxType* pStreamCtx);

static DP_Status FilterDuplicateModes(DP_StreamCtxType* pStreamCtx, DP_DisplayCtxType *pDisplayCtx, EDID_DispModeListType *psModeList);

static EDID_DispModeAttrType* GetPreferredMode(DP_StreamCtxType* pStreamCtx, DP_DisplayCtxType *pDisplayCtx, EDID_DispModeAttrType *pModeA, EDID_DispModeAttrType *pModeB);

static DP_PixelFormatType ConvertQdiPixelFormatToDp(MDP_PixelFormatType eQdiPxlFormat);

static uint64 DP_GetMinValidBw(DP_DeviceCtxType *pDeviceCtx);

static uint32 GetMaxPclkFromModeList(EDID_DispModeListType *pModeList);


/*------------------------------------------------------------------------------
 * Public Functions
 *----------------------------------------------------------------------------*/

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
void DP_OSAL_MemSet(void *pBuffer, uint8 uFillValue, uint32 uSizeInBytes)
{
  MDP_OSAL_MEMSET(pBuffer, uFillValue, uSizeInBytes);
}

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
void DP_OSAL_MemCpy(void *pDst, void *pSrc, uint32 uSizeInBytes)
{
  MDP_OSAL_MEMCPY(pDst, pSrc, uSizeInBytes);
}

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
void DP_OSAL_MemCpyEx(void *pDst, uint32 uDstSize, void *pSrc, uint32 uSrcSize)
{
  MDP_OSAL_MEMCPY(pDst, pSrc, uSrcSize);
}

/**********************************************************************************************************************
*
** FUNCTION: DP_OSAL_SleepMs()
*/
/*!
* \brief
*   The \b DP_OSAL_SleepMs function sleeps for a specific period
*
* \param [in]  uMilliSeconds - Sleep time in millisecond
*
* \retval void
*
**********************************************************************************************************************/
void DP_OSAL_SleepMs(uint32 uMilliSeconds)
{
  MDP_OSAL_DELAYMS(uMilliSeconds);
}

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
void DP_OSAL_SleepUs(uint32 uMicroSeconds)
{
  MDP_OSAL_DELAYUS(uMicroSeconds);
}

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
void DP_OSAL_StallUs(uint32 uMicroSeconds)
{
  MDP_OSAL_DELAYUS(uMicroSeconds);
}

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
                             bool32               bPLLSource)
{
  DP_Status                        eStatus      = DP_STATUS_SUCCESS;
  DP_DisplayCtxType               *pDisplayCtx  = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_DeviceCtxType                *pDeviceCtx;
  DP_StreamCtxType                *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_LinkClockEnable: Unexpected null context.");
  }
  else if ((DP_CONTROLLER_ID_NONE == pDeviceCtx->eControllerID) ||
           (pDeviceCtx->eControllerID >= DP_CONTROLLER_ID_MAX))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_LinkClockEnable: Unexpected Controller ID");
  }
  else
  {
    MDPClockEntry        *pDPExtClock;

    MDPExternalClockEntry sExtClocks[] = 
    {
      {"\0", 0, 0, 0, 0, 0, 0},
      {"\0", 0, 0, 0, 0, 0, 0},
    };

    MDPClockEntry sDP0LinkClocks[] = 
    {
      {"disp_cc_mdss_dptx0_link_clk",                  0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
      {"disp_cc_mdss_dptx0_link_intf_clk",             0, (MDPExternalClockEntry *)&sExtClocks[1], MDP_CLOCKFLAG_EXTERNAL},
      {"\0",                                           0, NULL,                                    0                     }
    };

    MDPClockEntry sDP0LinkClocksTunneled[] = 
    {
      {"disp_cc_mdss_dptx0_link_clk",                  0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
      {"disp_cc_mdss_dptx0_usb_router_link_intf_clk",  0, (MDPExternalClockEntry *)&sExtClocks[1], MDP_CLOCKFLAG_EXTERNAL},
      {"\0",                                           0, NULL,                                    0                     }
    };
    
    MDPClockEntry sDP1LinkClocks[] = 
    {
      {"disp_cc_mdss_dptx1_link_clk",                  0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
      {"disp_cc_mdss_dptx1_link_intf_clk",             0, (MDPExternalClockEntry *)&sExtClocks[1], MDP_CLOCKFLAG_EXTERNAL},
      {"\0",                                           0, NULL,                                    0                     }
    };

    MDPClockEntry sDP1LinkClocksTunneled[] = 
    {
      {"disp_cc_mdss_dptx1_link_clk",                  0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
      {"disp_cc_mdss_dptx1_usb_router_link_intf_clk",  0, (MDPExternalClockEntry *)&sExtClocks[1], MDP_CLOCKFLAG_EXTERNAL},
      {"\0",                                           0, NULL,                                    0                     }
    };
    
    MDPClockEntry  sDP2LinkClocks[] = 
    {
      {"disp_cc_mdss_dptx2_link_clk",                  0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
      {"disp_cc_mdss_dptx2_link_intf_clk",             0, (MDPExternalClockEntry *)&sExtClocks[1], MDP_CLOCKFLAG_EXTERNAL},
      {"\0",                                           0, NULL,                                    0                     }
    };

    MDPClockEntry sDP2LinkClocksTunneled[] = 
    {
      {"disp_cc_mdss_dptx2_link_clk",                  0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
      {"disp_cc_mdss_dptx2_usb_router_link_intf_clk",  0, (MDPExternalClockEntry *)&sExtClocks[1], MDP_CLOCKFLAG_EXTERNAL},
      {"\0",                                           0, NULL,                                    0                     }
    };

    MDPClockEntry  sDP3LinkClocks[] = 
    {
      {"disp_cc_mdss_dptx3_link_clk",                  0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
      {"disp_cc_mdss_dptx3_link_intf_clk",             0, (MDPExternalClockEntry *)&sExtClocks[1], MDP_CLOCKFLAG_EXTERNAL},
      {"\0",                                           0, NULL,                                    0                     }
    };

    switch (pDeviceCtx->eControllerID)
    {
    case DP_CONTROLLER_ID_DP_0:
      {
        if (TRUE == DPHOST_CHECK_DP_TUNNELING_MODE(pDeviceCtx))
        {
          pDPExtClock = &sDP0LinkClocksTunneled[0];
        }
        else
        {
          pDPExtClock = &sDP0LinkClocks[0]; 
        }
        break;
      }
    case DP_CONTROLLER_ID_DP_1:
      {
        if (TRUE == DPHOST_CHECK_DP_TUNNELING_MODE(pDeviceCtx))
        {
          pDPExtClock = &sDP1LinkClocksTunneled[0];
        }
        else
        {
          pDPExtClock = &sDP1LinkClocks[0];
        }
        break;
      }
    case DP_CONTROLLER_ID_DP_3:
      {
        pDPExtClock = &sDP3LinkClocks[0];
        break;
      }
    case DP_CONTROLLER_ID_DP_2:
      {
        if (TRUE == DPHOST_CHECK_DP_TUNNELING_MODE(pDeviceCtx))
        {
          pDPExtClock = &sDP2LinkClocksTunneled[0];
        }
        else
        {
          pDPExtClock = &sDP2LinkClocks[0];
        }
        break;
      }
    default:
      {
        // Default to use DP0 clock resources
        pDPExtClock = &sDP0LinkClocks[0]; 
        break;
      }
    }

    /* Only enable actions are available, turning off the clock should be done from the source PLL
    */
    if (bPLLSource)
    {
      // Gate link interface clock to DP PHY in tunneling mode
      HAL_DP_LinkInterfaceClockGatingEnable(pDeviceCtx->eControllerID, DPHOST_CHECK_DP_TUNNELING_MODE(pDeviceCtx));

      /* Clock source mappings:
       * ---------------------------------------------------------------
       * DP Device | Link clock source       | Link intf clock source 
       * ---------------------------------------------------------------
       * USB0      | dp0_phy_pll_link_clk    | dp0_phy_pll_link_clk
       * USB1      | dp1_phy_pll_link_clk    | dp1_phy_pll_link_clk
       * USB2      | dp2_phy_pll_link_clk    | dp2_phy_pll_link_clk
       * eDP       | dp3_phy_pll_link_clk    | dp3_phy_pll_link_clk
       */
  
      uint32          uClockSource[DP_DEVICE_MAX][5] =
      {
        // Link clock sources, Link intf clock sources
        {0, 0},  // DP_DEVICE_ID_NONE
        {1, 1},  // DP_DEVICE_ID_ALT_MODE_0
        {2, 2},  // DP_DEVICE_ID_ALT_MODE_1
        {3, 3},  // DP_DEVICE_ID_ALT_MODE_2
        {4, 4}   // DP_DEVICE_ID_EDP
      };

      pDPExtClock[0].pExtSrc->uClkSource = uClockSource[pDeviceCtx->eDeviceID][0];
      pDPExtClock[1].pExtSrc->uClkSource = uClockSource[pDeviceCtx->eDeviceID][1];
    
      if (MDP_STATUS_OK != MDPSetupClockList(pDPExtClock))
      {
        DP_LOG_MESSAGE_ERROR("DP_LinkClockEnable: Failed to configure DP link clocks to be sourced from PLL for eControllerID=%d\n", pDeviceCtx->eControllerID);
        eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      }
    }
    else
    {
      if (MDP_STATUS_OK != MDPSetupClockList(pDPExtClock))
      {
        DP_LOG_MESSAGE_ERROR("DP_LinkClockEnable: Failed to configure DP link clocks to be sourced from CXO for eControllerID=%d\n", pDeviceCtx->eControllerID);
        eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      }
    }
  }
  
  return eStatus;
}

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
                              bool32               bPLLSource)
{
  DP_Status                        eStatus      = DP_STATUS_SUCCESS;
  DP_DisplayCtxType               *pDisplayCtx  = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_DeviceCtxType  *pDeviceCtx;
  DP_StreamCtxType  *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_PixelClockEnable: Unexpected null context.");
  }
  else if ((DP_CONTROLLER_ID_NONE == pDeviceCtx->eControllerID) ||
           (pDeviceCtx->eControllerID >= DP_CONTROLLER_ID_MAX))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_PixelClockEnable: Unexpected Controller ID");
  }
  else
  {
    MDPClockEntry     *pDPExtClock;

    /* Only enable actions are available, turning off the clock should be done from the source PLL
    */
    if (bPLLSource)
    {
    /* Clock source mappings:
     * --------------------------------------
     * DP Device | Pixel clock source        
     * --------------------------------------
     * USB0      | dp0_phy_pll_vco_div_clk
     * USB1      | dp1_phy_pll_vco_div_clk
     * USB2      | dp2_phy_pll_vco_div_clk
     * eDP       | dp3_phy_pll_vco_div_clk
     */

    DP_DeviceIDType ePixelClockSourceDeviceID;
    uint32          uClockSource[DP_DEVICE_MAX][5] =
    {
      // Pixel clock source
      {0},  // DP_DEVICE_ID_NONE
      {2},  // DP_DEVICE_ID_ALT_MODE_0
      {4},  // DP_DEVICE_ID_ALT_MODE_1
      {6},  // DP_DEVICE_ID_ALT_MODE_2
      {3}   // DP_DEVICE_ID_EDP
    };

      MDPExternalClockEntry sExtClocks[] = 
      {
        {"\0", 0, 0, 0, 0, 0, 0},
      };

      MDPClockEntry sDP0PixelClocks[] = 
      {
        {"disp_cc_mdss_dptx0_pixel0_clk",     0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
        {"\0",                                0, NULL,                                    0                     }
      };
    
      MDPClockEntry sDP1PixelClocks[] = 
      {
        {"disp_cc_mdss_dptx1_pixel0_clk",     0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
        {"\0",                                0, NULL,                                    0                     }
      };
    
      MDPClockEntry  sDP2PixelClocks[] = 
      {
        {"disp_cc_mdss_dptx2_pixel0_clk",     0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
        {"\0",                                0, NULL,                                    0                     }
      };

      MDPClockEntry  sDP3PixelClocks[] = 
      {
        {"disp_cc_mdss_dptx3_pixel0_clk",     0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
        {"\0",                                0, NULL,                                    0                     }
      };          
    
      // MST case is not handled
      switch (pDeviceCtx->eControllerID)
      {
        case DP_CONTROLLER_ID_DP_0:
        {
          pDPExtClock = &sDP0PixelClocks[0];
          break; 
        }
        case DP_CONTROLLER_ID_DP_1:
        {
          pDPExtClock = &sDP1PixelClocks[0];
          break;
        }
        case DP_CONTROLLER_ID_DP_3:
        {
          pDPExtClock = &sDP3PixelClocks[0];
          break;
        }
        case DP_CONTROLLER_ID_DP_2:
        {
          pDPExtClock = &sDP2PixelClocks[0];
          break;
        }
        default:
        {
          // Default to use DP0 clock resources
          pDPExtClock = &sDP0PixelClocks[0]; 
          break;
        }
      } 

      if (DP_BONDED_MODE_SHARED_RESOURCE_EXTERNAL_PIXEL_CLOCK == pDeviceCtx->sBondedModeConfig.eSharedResourceConfig)
      {
        // If bonded mode configuration is active, the pixel clock is sourced from the vco_div_clk of the master PLL
        // Note: eDP vco_div_clk cannot be configured as pixel clock source for other DP blocks
        if (pDeviceCtx->sBondedModeConfig.eSourceClockDeviceID < DP_DEVICE_MAX)
        {
          ePixelClockSourceDeviceID = pDeviceCtx->sBondedModeConfig.eSourceClockDeviceID;
        }
        else
        {
          ePixelClockSourceDeviceID = 0;
          DP_LOG_MESSAGE_ERROR("DP_PixelClockEnable: Device ID of device sourcing external pixel clock invalid, DP:%d\n", pDeviceCtx->sBondedModeConfig.eSourceClockDeviceID);
        }
      }
      else
      {
        ePixelClockSourceDeviceID = pDeviceCtx->eDeviceID;
      }

      pDPExtClock[0].pExtSrc->uClkSource = uClockSource[ePixelClockSourceDeviceID][0];

      // Pixel clock Dividers - Index 0 in ext resource list for DP
      pDPExtClock[0].pExtSrc->nClkDiv    = pPixClkDivs->uPixelDivider * 2;    // this is a div2x value
      pDPExtClock[0].pExtSrc->uClkPLL_M  = pPixClkDivs->uPixelClk_M;
      pDPExtClock[0].pExtSrc->uClkPLL_N  = pPixClkDivs->uPixelClk_N;
      pDPExtClock[0].pExtSrc->uClkPLL_2D = pPixClkDivs->uPixelClk_2D;

      if (MDP_STATUS_OK != MDPSetupClockList(pDPExtClock))
      {
        DP_LOG_MESSAGE_ERROR("DP_PixelClockEnable: Failed to configure DP pixel clock to be sourced from PLL for eControllerID=%d\n", pDeviceCtx->eControllerID);
        eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      }
    }
    else
    {
      if (DP_STATUS_SUCCESS != (eStatus = ParkPixelClock(pStreamCtx->eDisplayID, pDeviceCtx->eControllerID, pStreamCtx->eMSTStreamId)))
      {
        DP_LOG_MESSAGE_ERROR("DP_PixelClockEnable: Failed to park DP pixel clock for DP Controller=%d, eMSTStreamId=%d, eStatus=%d\n",
                             pDeviceCtx->eControllerID,
                             pStreamCtx->eMSTStreamId,
                             eStatus);
      }
    }
  }
  
  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ParkLinkAndPixelClockSources()

  This function will park the DP link and pixel clock sources to CXO.

Parameters:
  hHandle      -[in]    : Handle to DP device

Return: 
  DP_Status

**********************************************************************************************************************/
DP_Status DP_ParkLinkAndPixelClockSources(DP_HandleType hHandle)
{
  DP_Status          eStatus     = DP_STATUS_SUCCESS;
  DP_DisplayCtxType *pDisplayCtx = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_DeviceCtxType  *pDeviceCtx;
  DP_StreamCtxType  *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ParkLinkAndPixelClockSources: Unexpected null context.");
  }
  else
  {
    DP_MSTStreamIDType eMSTStreamIndex;

    /* Configure the link and pixel clock */
    if (DP_STATUS_SUCCESS != (eStatus = DP_LinkClockEnable(hHandle, FALSE)))
    {
      DP_LOG_MESSAGE_ERROR("DP_ParkLinkAndPixelClockSources: Failed to configure link clock, eStatus=%d", eStatus);
    }
    else
    {
      /* Disable all pixel clocks */
      for (eMSTStreamIndex = DP_MST_STREAM_ID_0; eMSTStreamIndex < DP_MST_STREAM_ID_MAX; eMSTStreamIndex++)
      {
        if (DP_STATUS_SUCCESS != (eStatus = ParkPixelClock(pStreamCtx->eDisplayID, pDeviceCtx->eControllerID, eMSTStreamIndex)))
        {
          DP_LOG_MESSAGE_ERROR("DP_ParkLinkAndPixelClockSources: Failed to disable pixel clock for DP Controller=%d, eMSTStreamId=%d, eStatus=%d",
                               pDeviceCtx->eControllerID,
                               eMSTStreamIndex,
                               eStatus);
        }
      }
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ConfigureAllClocks()

  This function will enable/disable all the DP clocks.

Parameters:
  hHandle      -[in]    : Handle to DP device

Return: 
  DP_Status

**********************************************************************************************************************/
DP_Status DP_ConfigureAllClocks(DP_HandleType hHandle, bool32 bEnable)
{
  DP_Status          eStatus     = DP_STATUS_SUCCESS;
  DP_DisplayCtxType *pDisplayCtx = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_DeviceCtxType  *pDeviceCtx;
  DP_StreamCtxType  *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ConfigureAllClocks: Unexpected null context.");
  }
  else
  {
    MDPClockTypes              eDPClockType     = DP_GETCLOCKTYPE(pDeviceCtx->eControllerID);
    MDPExternalClockEntry     *pDPExtClock      = MDPGetExternalClockEntry(eDPClockType, FALSE);

    if (NULL == pDPExtClock)
    {
      // Ext Resources is disabled for emulation. Warning and then continuing with success.
      DP_LOG_MESSAGE_WARN("DP%d: Invalid external clock entry.\n", pStreamCtx->eDisplayID);
      eStatus = DP_STATUS_SUCCESS;
    }
    if (TRUE == bEnable)
    {
      if (MDP_STATUS_OK != MDPSetupClocks(eDPClockType, NULL))
      {
        DP_LOG_MESSAGE_ERROR("DP%d: Failed to park all DP clocks to CXO.\n", pStreamCtx->eDisplayID);
        eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      }
    }
    else
    {
      if (MDP_STATUS_OK != MDPDisableClocks(eDPClockType))
      {
        DP_LOG_MESSAGE_ERROR("DP%d: Failed to disable all DP clocks.\n", pStreamCtx->eDisplayID);
        eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      }
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_WaitForLinkStatus()
   This function will wait for the main link to reach the specified state.

Parameters:
   hHandle    -[in]    : Handle to DP device
   eLinkState -[in]    : Main link state type

Return: 
   DP_Status

**********************************************************************************************************************/
DP_Status DP_WaitForLinkStatus(DP_HandleType             hHandle,
                               HAL_DP_LinkStatusType     eLinkState)
{
  DP_Status                   eStatus        = DP_STATUS_FAILED_TIMEOUT;
  DP_DisplayCtxType          *pDisplayCtx    = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_DeviceCtxType           *pDeviceCtx     = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  uint32                      i              = 0;
  uint32                      uLinkStatus    = 0;
  uint32                      uPollCount     = (DP_LINK_STATUS_TIMEOUT_US / DP_LINK_STATUS_POLL_INTERVAL_US) + 1;

  if (NULL == pDeviceCtx)
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else 
  {
    for (i = 0; i < uPollCount; ++i)
    {
      uLinkStatus = HAL_DP_Mainlink_Status(pDeviceCtx->eControllerID);

      if (uLinkStatus & eLinkState)
      {
        eStatus = DP_STATUS_SUCCESS;
        break;
      }
      DP_OSAL_SleepUs(DP_LINK_STATUS_POLL_INTERVAL_US);
    }
  }
  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_GetHPDPollTime()
   
   This function will get the user requested HPD polling time

Parameters:

Return: 
   uint32      polling time in ms

**********************************************************************************************************************/
uint32 DP_GetHPDPollTime()
{
  return DP_HPD_POLL_TIME_MS;
}

/**********************************************************************************************************************

FUNCTION: DP_PhyDataPathIsReverse()

   This function will check if the DP PHY datapath is reverse of USB type-C specification

Parameters:
   hHandle    -[in]    : Handle to DP device

Return:
   bool32      TRUE - reverse of spec      FALSE - as per spec

**********************************************************************************************************************/
bool32 DP_PhyDataPathIsReverse(DP_HandleType        hHandle)
{
  bool32               bReverse     = FALSE;
  DP_DisplayCtxType   *pDisplayCtx  = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_DeviceCtxType    *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    DP_LOG_MESSAGE_ERROR("DP_PhyDataPathIsReverse: Unexpected null context.");
  }
  else
  {
    HAL_HW_VersionType   sDPHwVersion = { 0 };

    HAL_DP_ReadVersionInfo(pDeviceCtx->eControllerID, &sDPHwVersion);
    
    if ((1 == sDPHwVersion.uMajorVersion) &&
        (0 == sDPHwVersion.uMinorVersion))
    {
      bReverse = TRUE;
    }
  }

  return bReverse;
}

/**********************************************************************************************************************

FUNCTION: DP_DualPixelModeSupported()
   
  This function will check if Dual pixel mode is supporte.

Parameters:
  hHandle      -[in]    : Handle to DP device

Return: 
  bool32      TRUE - Dual pixel mode     FALSE - Single pixel mode
  
**********************************************************************************************************************/
bool32 DP_DualPixelModeSupported(DP_HandleType        hHandle)
{
  bool32               bDualPixel   = FALSE;
  DP_DisplayCtxType   *pDisplayCtx  = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_DeviceCtxType    *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    DP_LOG_MESSAGE_ERROR("DP_DualPixelModeSupported: Unexpected null context.");
  }
  else
  {
    HAL_HW_VersionType   sDPHwVersion = { 0 };

    HAL_DP_ReadVersionInfo(pDeviceCtx->eControllerID, &sDPHwVersion);
    
    /* 
     * Dual pixel mode is only supported from DP controller version 1.2.
     * Earlier versions only support single pixel per clock mode.
     */
    if ((sDPHwVersion.uMajorVersion >= 1) &&
        (sDPHwVersion.uMinorVersion >= 2))
    {
      bDualPixel = TRUE;
    }
  }

  return bDualPixel;
}

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
                                uint8                   uGpioState)
{
  DP_Status                      eStatus        = DP_STATUS_SUCCESS;

  /* In UEFI DP GPIOs are configured from DP Driver in DPDriver_Open() using ConfigureGPIO() */
  return eStatus;
}
/**********************************************************************************************************************

FUNCTION: DP_CheckConnectionStatus()

   This function will check cable connection status

Parameters:
   hHandle    -[in]    : Handle to DP device

Return:
   DP_Status

**********************************************************************************************************************/
DP_Status DP_CheckConnectionStatus(DP_HandleType        hHandle)
{
  DP_Status                   eStatus           = DP_STATUS_SUCCESS; 
  DP_DisplayCtxType          *pDisplayCtx       = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_DeviceCtxType           *pDeviceCtx;
  DP_StreamCtxType           *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    DP_LOG_MESSAGE_ERROR("DP_CheckConnectionStatus: unexpected null handle ");
    eStatus = DP_STATUS_FAILED_DRIVER_NOT_INITIALIZED;
  }
  else
  {
    if (DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_SIMULATION_MODE))
    {
      TraceInfo(QdiTraceDP, "DP%d: Panel is in simulation mode, ignoring HPD check.", pStreamCtx->eDisplayID);
    }
    else if (DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_HPD_FAILSAFE))
    {
      int32             iTimeout    = EDP_HPD_ENABLE_WAIT_TIME_MS;
      bool32            eConnected  = FALSE;
      DP_HPD_StatusType eHPDStatus  = DP_HPD_STATUS_DISCONNECTED;

      /* According to eDP specification, aux channel will ready once HPD become high
         for eDP poll for HPD to get in connected pending or connected status
       */
      do
      {
        eHPDStatus = HAL_DP_HPD_PanelPlugged(pDeviceCtx->eControllerID);

        if ((DP_HPD_STATUS_CONNECTED == eHPDStatus) ||
            (DP_HPD_STATUS_CONNECT_PENDING == eHPDStatus))
        {
          eConnected = TRUE;
          break;
        }
        else
        {
          DP_OSAL_SleepMs(HPD_ENABLE_POLL_INTERVAL_TIME_MS);
          iTimeout -= HPD_ENABLE_POLL_INTERVAL_TIME_MS;
        }
      } while (iTimeout > 0);

      /* In failure case, logging warning message and continuing */
      if (FALSE == eConnected)
      {
        TraceInfo(QdiTraceDP, "DP%d: Panel HPD never went high after %dms, ignore HPD status.", pStreamCtx->eDisplayID, EDP_HPD_ENABLE_WAIT_TIME_MS);
      }
    }
    else if (DP_DEVICE_MODETYPE_DP == pDeviceCtx->eDeviceDPMode)
    {
      /* According to HPG, HPD IN detection will need up to 100ms, to reduce boot time wait for 10ms only */
      DP_OSAL_SleepMs(DP_HPD_ENABLE_WAIT_TIME_MS);
     
      /* Currently HPD GPIO is not configured in UEFI for mini-DP, so ignore HPD status */
      /* If HPD GPIO is being configured, then set the connection polarity and pin assignment based on the connection status */
      pDeviceCtx->eConnectionPolarity = DP_CONNECTION_POLARITY_POLARITY_DEFAULT;
      pDeviceCtx->ePinAssignment      = DP_CONNECTION_PINASSIGNMENT_DFPD_A;
    }
    else if (0 != DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_ALT_MODE_FIXED_LANE_CONFIGURATION))
    {
      /* Handles the fixed lane configuration case for Alt-mode devices for ex DP-HDMI bridge or customer DP connector */

      DP_HPD_StatusType eHPDStatus = HAL_DP_HPD_PanelPlugged(pDeviceCtx->eControllerID);
      /* According to HPG, HPD IN detection will need up to 100ms, to reduce boot time wait for 10ms only */
      DP_OSAL_SleepMs(DP_HPD_ENABLE_WAIT_TIME_MS);

      if ((DP_HPD_STATUS_CONNECTED == eHPDStatus) ||
          (DP_HPD_STATUS_CONNECT_PENDING == eHPDStatus))
      {
        pDeviceCtx->eConnectionPolarity = DP_CONNECTION_POLARITY_POLARITY_DEFAULT;
        pDeviceCtx->ePinAssignment      = DP_CONNECTION_PINASSIGNMENT_DFPD_C;
      }
      else
      {
        pDeviceCtx->eConnectionPolarity = DP_CONNECTION_STATUS_DISCONNECTED;
        pDeviceCtx->ePinAssignment      = DP_CONNECTION_PINASSIGNMENT_INVALID;
      }
    }
    
    /* The connection parameters for Type C already get updated when we get USBC HPD event. */
    TraceInfo(QdiTraceDP,
              "DP%d: Connection status - polarity:%d, pin_assignment:%d, status:0x%x",
              pStreamCtx->eDisplayID, 
              (uint32)pDeviceCtx->eConnectionPolarity, 
              (uint32)pDeviceCtx->ePinAssignment,
              (uint32)eStatus);
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_SetHostRouterBaseAddress()

   This function will set USB4 Host Router and QMP Phy base addresses

Parameters:

Return:
   DP_Status

**********************************************************************************************************************/
DP_Status DP_SetHostRouterBaseAddress(void)
{
  DP_Status                           eStatus             = DP_STATUS_SUCCESS; 
  MDP_HwPrivateInfo                  *psMDPHwPrivateInfo  = MDP_GETPRIVATEINFO();
  HAL_MDP_SWMappedHWBaseAddressesType sMDSSAddress;

  DISP_OSAL_MemZero(&sMDSSAddress, sizeof(sMDSSAddress));

  if (MDP_STATUS_OK != MDP_HostRouter_QMPPhy_HWIOBaseAddr(psMDPHwPrivateInfo->sEFIChipSetFamily, &sMDSSAddress))
  {
    DP_LOG_MESSAGE_ERROR("DP_SetHostRouterBaseAddress failed ");
    eStatus = DP_STATUS_FAIL;
  }
  else
  {
    // Setup the USB4 and QMP Phy base addresses
    HAL_MDSS_SetBaseAddress(&sMDSSAddress);
  }
  
  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_SetFailSafeEDID()

  This function will generate fail-safe mode EDID and overwrite the device context.

Parameters:
  hHandle  -[in]    : Handle to DP device

Return:
  DP_Status

**********************************************************************************************************************/
DP_Status DP_SetFailSafeEDID(DP_HandleType        hHandle)
{
  DP_Status               eStatus     = DP_STATUS_SUCCESS;
  DP_DisplayCtxType      *pDisplayCtx = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_StreamCtxType       *pStreamCtx  = DPHOST_GET_STREAM_CTX(pDisplayCtx);
  DP_DeviceCtxType       *pDeviceCtx  = DPHOST_GET_DEVICE_CTX(pDisplayCtx);

  if (NULL == pStreamCtx)
  {
    DP_LOG_MESSAGE_ERROR("DP_SetFailSafeEDID() : DP context is NULL pointer\n");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  { 
    EDID_DispModeInfoType sDispModeInfo;

    DISP_OSAL_MemZero(&sDispModeInfo, sizeof(EDID_DispModeInfoType));

    sDispModeInfo.sPanelAttr.ePhysConnect = MDP_DISPLAY_CONNECT_DP;
    
    if (DP_DEVICE_MODETYPE_EDP == pDeviceCtx->eDeviceDPMode)
    {
      // Set default resolution to 720P for eDP only, TU calculate will fail on 640x480. 
      // Todo, update TU calculation code.
      EDIDGetDetailedTiming(EDID_VIDEO_FORMAT_1280x720p60_16_9, &sDispModeInfo);
    }
    else
    {
      EDIDGetDetailedTiming(EDID_VIDEO_FORMAT_640x480p60_4_3, &sDispModeInfo);
    }
    

    /* Initialize EDID table structure */
    EDIDInitialize((MDP_Panel_EDID_Config*)pStreamCtx->auEDIDCache);
    /* Generate Detailed timings from XML data */
    EDIDGenerateDetailedTiming((MDP_Panel_EDID_Config*)pStreamCtx->auEDIDCache, &sDispModeInfo.sPanelAttr);

    /* Generate EDID Checksum */
    EDIDGenerateChecksum((MDP_Panel_EDID_Config*)pStreamCtx->auEDIDCache);

    DISP_OSAL_MemZero(&pStreamCtx->sPanelInfo[0], sizeof(DP_PanelInfoType));

    pStreamCtx->uEDIDDataLength                        = DP_EDID_BLOCK_SIZE;
    pStreamCtx->uNumModes                              = 1;

    pStreamCtx->sPanelInfo[0].uModeIndex               = 0;
    pStreamCtx->sPanelInfo[0].uPclkFreq                = sDispModeInfo.sPanelAttr.uPixelRate;
    pStreamCtx->sPanelInfo[0].uVisibleWidthInPixels    = sDispModeInfo.sPanelAttr.uDisplayWidth;
    pStreamCtx->sPanelInfo[0].uHsyncFrontPorchInPixels = sDispModeInfo.sPanelAttr.sActiveTiming.uHsyncFrontPorchDclk;
    pStreamCtx->sPanelInfo[0].uHsyncBackPorchInPixels  = sDispModeInfo.sPanelAttr.sActiveTiming.uHsyncBackPorchDclk;
    pStreamCtx->sPanelInfo[0].uHsyncPulseInPixels      = sDispModeInfo.sPanelAttr.sActiveTiming.uHsyncPulseWidthDclk;
    pStreamCtx->sPanelInfo[0].uVisibleHeightInPixels   = sDispModeInfo.sPanelAttr.uDisplayHeight;
    pStreamCtx->sPanelInfo[0].uVsyncFrontPorchInLines  = sDispModeInfo.sPanelAttr.sActiveTiming.uVsyncFrontPorchLines;
    pStreamCtx->sPanelInfo[0].uVsyncBackPorchInLines   = sDispModeInfo.sPanelAttr.sActiveTiming.uVsyncBackPorchLines;
    pStreamCtx->sPanelInfo[0].uVsyncPulseInLines       = sDispModeInfo.sPanelAttr.sActiveTiming.uVsyncPulseWidthLines;
    pStreamCtx->sPanelInfo[0].bHSyncActiveLow          = sDispModeInfo.sPanelAttr.sActiveTiming.uHsyncInvertSignal;
    pStreamCtx->sPanelInfo[0].bVSyncActiveLow          = sDispModeInfo.sPanelAttr.sActiveTiming.uVsyncInvertSignal;
    pStreamCtx->sPanelInfo[0].uRefreshRate             = sDispModeInfo.sPanelAttr.uAttrs.sDp.uRefreshRate;
    pStreamCtx->sPanelInfo[0].uAspectRatio             = sDispModeInfo.uAspectRatio;
    pStreamCtx->sPanelInfo[0].bVirtualMode             = TRUE;

    if (DP_DEVICE_MODETYPE_EDP == pDeviceCtx->eDeviceDPMode)
    {
      // Set default resolution to 720P for eDP only, TU calculate will fail on 640x480. 
      // Todo, update TU calculation code.
      pStreamCtx->sPanelInfo[0].eColorFormat           = DP_PIXEL_FORMAT_RGB_888_24BPP;
    }
    else
    {
      pStreamCtx->sPanelInfo[0].eColorFormat           = DP_PIXEL_FORMAT_RGB_666_18BPP;
    }

    TraceInfo(QdiTraceDP, "DP%d: Defaulting to fail-safe mode due to EDID failures", pStreamCtx->eDisplayID);
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ParseEDID()

   This function will parse the EDID info 

Parameters:
   pDisplayCtx  -[in]    : DP Display Context

Return:
   DP_Status

**********************************************************************************************************************/
DP_Status DP_ParseEDID(DP_HandleType        hHandle)
{
  DP_Status               eStatus             = DP_STATUS_SUCCESS; 
  MDP_Status              eLocalStatus        = MDP_STATUS_SUCCESS;
  DP_DisplayCtxType      *pDisplayCtx = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_StreamCtxType       *pStreamCtx  = DPHOST_GET_STREAM_CTX(pDisplayCtx);
  DP_DeviceCtxType       *pDeviceCtx  = DPHOST_GET_DEVICE_CTX(pDisplayCtx);

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    DP_LOG_MESSAGE_ERROR("DP_ParseEDID(): unexpected null handle ");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    DP_HandleType          hEDIDParserHandle   = NULL;

    /* Open handle to EDID parser */
    if (MDP_STATUS_OK != EDID_OpenParser(&hEDIDParserHandle))
    {
      DP_LOG_MESSAGE_ERROR("Failed to open handle to EDID parser");
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
    }
    else
    {
      uint32                          uModeIndex               = 0;
      EDID_ParserContextType         *pEDIDParserContext       = (EDID_ParserContextType*) hEDIDParserHandle;
      
      EDID_DisplayRangeInfo           sDisplayRangeDesc;
      EDID_ParserInfoType             sEDIDInfo;
      EDID_DispModeListType          *psModeList;
      EDID_DispModeListType          *psModeListDSC;
      EDID_DispModeListType          *psModeListNonDSC;
      DisplayId_ParserInfoType        sDisplayIdInfo;
  
      psModeList = DISP_OSAL_Malloc(sizeof(EDID_DispModeListType), MDP_OSAL_COMP_PANEL);

      if (NULL == (psModeListDSC = DISP_OSAL_Malloc(sizeof(EDID_DispModeListType), MDP_OSAL_COMP_PANEL)))
      {
        DP_LOG_MESSAGE_ERROR("Failed to allocate memory for DSC mode list");
        eStatus = DP_STATUS_FAILED_RESOURCE_FATAL_ERROR;
      }
      else if (NULL == (psModeListNonDSC = DISP_OSAL_Malloc(sizeof(EDID_DispModeListType), MDP_OSAL_COMP_PANEL)))
      {
        DP_LOG_MESSAGE_ERROR("Failed to allocate memory for non-DSC mode list");
        eStatus = DP_STATUS_FAILED_RESOURCE_FATAL_ERROR;

        DISP_OSAL_Free(psModeListDSC);
      }
      else
      {
        DISP_OSAL_MemZero((void*)psModeListDSC, sizeof(EDID_DispModeListType));
        DISP_OSAL_MemZero((void*)psModeListNonDSC, sizeof(EDID_DispModeListType));
        DISP_OSAL_MemZero((void *)&sEDIDInfo, sizeof(EDID_ParserInfoType));
        DISP_OSAL_MemZero((void *)&sDisplayRangeDesc, sizeof(EDID_DisplayRangeInfo));

        // Recalculate FEC parameters based on current link rate
        DP_FEC_CalculateParameters(pDisplayCtx);

        // Update max bit depth
        pStreamCtx->uMaxBitDepth      = 8;
        
        /* Copy EDID and other filtering info */
        sEDIDInfo.pEDIDBuffer         = (void *)pStreamCtx->auEDIDCache;
        sEDIDInfo.uEDIDDataLength     = pStreamCtx->uEDIDDataLength;
        sEDIDInfo.uMaxModePixels      = pDeviceCtx->uTotalPixelRate;
        if((pDeviceCtx->eDisplayID == MDP_DISPLAY_PRIMARY)   ||
           (pDeviceCtx->eDisplayID == MDP_DISPLAY_SECONDARY))
        {   
          sEDIDInfo.uMaxModeWidth     = DP_MAX_RESOLUTION_WIDTH;
          sEDIDInfo.uMaxModeHeight    = DP_MAX_RESOLUTION_HEIGHT;
        }
        else
        {
          sEDIDInfo.uMaxModeWidth     = DP_MAX_RESOLUTION_WIDTH_EXTERNAL;
          sEDIDInfo.uMaxModeHeight    = DP_MAX_RESOLUTION_HEIGHT_EXTERNAL;
        }
        sEDIDInfo.uMinModeWidth       = DP_MIN_RESOLUTION_WIDTH;
        sEDIDInfo.uMinModeHeight      = DP_MIN_RESOLUTION_HEIGHT;
        sEDIDInfo.uMaxModeRefreshRate = DP_MAX_REFRESH_RATE_HZ * 1000;
        sEDIDInfo.uMinModeRefreshRate = DP_MIN_REFRESH_RATE_HZ * 1000;        
        sEDIDInfo.uMinBandwidth       = DP_GetMinValidBw(pDeviceCtx);
        sEDIDInfo.uMaxBandwidth       = DP_GetMaxAvailableBw(pDisplayCtx);
        sEDIDInfo.eEDIDSpecType       = EDID_DP_SPEC_TYPE_1_3;
        sEDIDInfo.bEmbeddedDisplay    = (DP_DEVICE_MODETYPE_EDP == pDeviceCtx->eDeviceDPMode) ? TRUE : FALSE;
        sEDIDInfo.pDisplayRangeDesc   = &sDisplayRangeDesc;
        sEDIDInfo.uMinBitsPerColor    = DP_MIN_BPC_SUPPORT;
        sEDIDInfo.uMaxBitsPerColor    = pStreamCtx->uMaxBitDepth;

        //
        // 1. Run the EDID parser with DSC disabled, by default
        //
        sEDIDInfo.fCompressionRatio   = 1.0f;
        // Fetch the list of modes that can be supported without DSC 
        if (MDP_STATUS_OK != (eLocalStatus = EDID_GetModeList(hEDIDParserHandle, &sEDIDInfo, psModeListNonDSC)))
        {
          DP_LOG_MESSAGE_ERROR("DP_ParseSinkEDID: EDID_GetModeList failed with status = %d", eLocalStatus);
        }

        // Get DisplayId block data if present as a part of EDID Extension 
        if (MDP_STATUS_SUCCESS == DisplayId_ParseDID((EDID_ParserContextType*) hEDIDParserHandle, &sDisplayIdInfo))
        {
          // Check if DisplayID extension block has Detailed timing info.
          if (psModeListNonDSC->uNumOfElements < pEDIDParserContext->sDispModeList.uNumOfElements)
          {
            // Copy updated list of modes
            DISP_OSAL_MemCpyEx(psModeListNonDSC, sizeof(EDID_DispModeListType), &pEDIDParserContext->sDispModeList, sizeof(EDID_DispModeListType));
          }
        }

        //
        // 2. Run the EDID parser with DSC enabled, if capable
        //
        if (pStreamCtx->sDSCInfo.bDSCEnabled)
        {
          sEDIDInfo.fCompressionRatio   = 3.75f;

          // Fetch the list of modes that can be supported with DSC enabled
          if (MDP_STATUS_SUCCESS != (eLocalStatus = EDID_GetModeList(hEDIDParserHandle, &sEDIDInfo, psModeListDSC)))
          {
            DP_LOG_MESSAGE_ERROR("DP_ParseSinkEDID: EDID_GetModeList failed with status = %d", eLocalStatus);
          }

          // Since DisplayID is already parsed in non-DSC case, check if it is valid before trying again for DSC
          if ((DISPLAYID_VERSION_INVALID != sDisplayIdInfo.eDIDVersion) &&
              (MDP_STATUS_SUCCESS == DisplayId_ParseDID((EDID_ParserContextType*) hEDIDParserHandle, &sDisplayIdInfo)))
          {
            // Check if DisplayID extension block has Detailed timing info.
            if (psModeListDSC->uNumOfElements < pEDIDParserContext->sDispModeList.uNumOfElements)
            {
              // Copy updated list of modes
              DISP_OSAL_MemCpyEx(psModeListDSC, sizeof(EDID_DispModeListType), &pEDIDParserContext->sDispModeList, sizeof(EDID_DispModeListType));
            }
          }
        }

        //
        // 3. Check the supported modes in each list to decide on DSC state
        //
        psModeList = psModeListNonDSC;
        
        if (psModeListDSC->uNumOfElements > 0)
        {
          // DSC is capable, but decide whether to keep it enabled based on the max BW
          uint32 uMaxModeWithDsc    = GetMaxPclkFromModeList(psModeListDSC);
          uint32 uMaxModeWithoutDsc = GetMaxPclkFromModeList(psModeListNonDSC);
        
          // For normal usage (non-CTS), enable DSC only if required by the highest BW mode 
          pStreamCtx->sDSCInfo.bDSCEnabled = FALSE;
        
          // Compare the highest modes from DSC-enabled and DSC-disabled mode lists
          if (uMaxModeWithDsc > uMaxModeWithoutDsc)
          {
            // There is at least one higher mode which cannot be supported without DSC
            pStreamCtx->sDSCInfo.bDSCEnabled = TRUE;
            psModeList                       = psModeListDSC;
          }
        
          TraceInfo(QdiTraceDP, "DP%i: DP_ParseEDID() : Keeping DSC %s since max mode pclk with DSC=%d and without DSC=%d ", 
                                pStreamCtx->eDisplayID, pStreamCtx->sDSCInfo.bDSCEnabled ? "enabled" : "disabled", 
                                uMaxModeWithDsc, uMaxModeWithoutDsc);
        }

        if (0 == psModeList->uNumOfElements)
        {
          /* If EDID parse failed or mode list is empty, will set EDID to fail-safe mode, 640x480 18bpp */
          eStatus = DP_SetFailSafeEDID(pDisplayCtx);
        }
        else
        {

          // Filter out any modes that the OS graphics stack would consider as duplicate
          FilterDuplicateModes(pStreamCtx, pDisplayCtx, psModeList);
                  
          // Parse EDID for SST case
          // If the mode 0 is already overridden, then don't overwrite it. Add the EDID modes to it.
          UpdateModeListToDisplayContext(pDisplayCtx, psModeList, &sDisplayRangeDesc);

        /* Populate Display Range Descriptor info to Device Context */
          if ((0 != sDisplayRangeDesc.uMaxVRate) && 
              (0 != sDisplayRangeDesc.uMinVRate))
          {
            pDeviceCtx->uMaxRefreshRate = sDisplayRangeDesc.uMaxVRate;
            pDeviceCtx->uMinRefreshRate = sDisplayRangeDesc.uMinVRate;
          }
        } 

        /* Free temp mode list */
        DISP_OSAL_Free(psModeListDSC);
        DISP_OSAL_Free(psModeListNonDSC);

        /* Parse audio info */
        pStreamCtx->uNumberOfAudioModes = 0;

        for (uModeIndex = 0; uModeIndex < MAX_DP_AUDIO_MODE; uModeIndex++)
        {
          pStreamCtx->sAudioModeInfo[uModeIndex].uAudioModeIndex = uModeIndex;

          if (MDP_STATUS_OK != EDID_GetAudioModeInfo(hEDIDParserHandle, pStreamCtx->uModeIndex, &(pStreamCtx->sAudioModeInfo[uModeIndex]), EDID_GET_AUDIO_INSERT_DEFAULT_MODE))
          {
            break;
          }
          else
          {
            pStreamCtx->uNumberOfAudioModes++;
          }
        }

        if(MDP_STATUS_OK == eStatus)
        {
          EDID_VendorInfoType sVendorInfo;

          DISP_OSAL_MemZero((void *)&sVendorInfo, sizeof(EDID_VendorInfoType));

          if (MDP_STATUS_FAILED != EDID_GetVendorInfo(hEDIDParserHandle, &sVendorInfo))
          {
            DISP_OSAL_MemCpyEx(&(pStreamCtx->sVendorInfo), sizeof(DP_VendorInfoType), &sVendorInfo, sizeof(EDID_VendorInfoType));
          }
        }
      }

     /* Close handle to EDID parser */
      EDID_CloseParser(hEDIDParserHandle);
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ReadLinkRateOverride()

  This function will read registry key for maximum link rate override.

Parameters:
  pDisplayCtx  -[in]    : DP Display Context

Return:
  uint32

**********************************************************************************************************************/
uint32 DP_ReadLinkRateOverride(DP_DisplayCtxType    *pDisplayCtx) 
{
  return 0;
}

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
                         bool32             bPlugIn)
{
  return;
}

//-------------------------------------------------------------------------------------------------
//  DP_SetControllerResources
//
//  @brief
//      set resources for chosen controller.
//
//  @params
//      [IN] eDisplayId
//          QDI display ID.
//
//  @return
//      void 
//-------------------------------------------------------------------------------------------------
// 
void DP_SetControllerResources(DP_ControllerIDType eControllerID, MDP_Display_IDType eDisplayID)
{ 
  return;
}

//-------------------------------------------------------------------------------------------------
//  DP_GetMaxPixelRate
//
//  @brief
//      This function gets the total pixel rate.
//
//  @params
//      none
//
//  @return
//      uint32 
//-------------------------------------------------------------------------------------------------
//
uint32 DP_GetMaxPixelRate(void)
{ 
  return DP_MAX_PIXEL_RATE;
}

//-------------------------------------------------------------------------------------------------
//  DP_CreateWorkItem
//
//  @brief
//      Create Work Item from Physical Device Object(PDO) for IRQ HPD worker thread
//
//  @params
//      phHPDWorkItem    -[out]    : pointer to  work item handle
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_CreateWorkItem(DP_HandleType    *phHPDWorkItem)
{
  return DP_STATUS_SUCCESS;
}

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
DP_Status DP_DestroyWorkItem(DP_HandleType    *phHPDWorkItem)
{
  return DP_STATUS_SUCCESS;
}

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
DP_Status DP_LaunchWorkItem(DP_HandleType  hHPDWorkItem, DP_WorkThread pFunction, void *pContext)
{
  return DP_STATUS_SUCCESS;
}

/*------------------------------------------------------------------------------
 * Private Functions
 *----------------------------------------------------------------------------*/

/**********************************************************************************************************************

FUNCTION: ParkPixelClock()
   
  This function will disable the pixel clock based on the controller ID and MST stream ID.

Parameters:
  eDisplayID         -[in]    : DP display ID
  eControllerID      -[in]    : DP controller ID
  eMSTStreamId       -[in]    : MST stream ID

Return: 
  DP_Status

**********************************************************************************************************************/
static DP_Status ParkPixelClock(MDP_Display_IDType  eDisplayID,
                                DP_ControllerIDType eControllerID,
                                DP_MSTStreamIDType  eMSTStreamId)
{
  DP_Status          eStatus      = DP_STATUS_SUCCESS;
  MDPClockEntry     *pDPExtClock  = NULL;

  MDPExternalClockEntry sExtClocks[] = 
  {
    {"\0", 0, 0, 0, 0, 0, 0},
  };

  MDPClockEntry sDP0PixelClocks[] = 
  {
    {"disp_cc_mdss_dptx0_pixel0_clk",     0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
    {"\0",                                0, NULL,                                    0                     }
  };
    
  MDPClockEntry sDP1PixelClocks[] = 
  {
    {"disp_cc_mdss_dptx1_pixel0_clk",     0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
    {"\0",                                0, NULL,                                    0                     }
  };
    
  MDPClockEntry  sEDPPixelClocks[] = 
  {
    {"disp_cc_mdss_dptx3_pixel0_clk",     0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
    {"\0",                                0, NULL,                                    0                     }
  };

  MDPClockEntry  sDP2PixelClocks[] = 
  {
    {"disp_cc_mdss_dptx2_pixel0_clk",     0, (MDPExternalClockEntry *)&sExtClocks[0], MDP_CLOCKFLAG_EXTERNAL},
    {"\0",                                0, NULL,                                    0                     }
  };

  switch (eControllerID)
  {
  case DP_CONTROLLER_ID_DP_0:
    {
      pDPExtClock = &sDP0PixelClocks[0];
      break;
    }
  case DP_CONTROLLER_ID_DP_1:
    {
      pDPExtClock = &sDP1PixelClocks[0];
      break;
    }
  case DP_CONTROLLER_ID_DP_3:
    {
      pDPExtClock = &sEDPPixelClocks[0];
      break;
    }
  case DP_CONTROLLER_ID_DP_2:
    {
      pDPExtClock = &sDP2PixelClocks[0];
      break;
    }
  default:
    {
      break;
    }
  }

  if ((pDPExtClock != NULL) &&
      (MDP_STATUS_OK != MDPSetupClockList(pDPExtClock)))
  {
    DP_LOG_MESSAGE_ERROR("ParkPixelClock: Failed to configure DP pixel clock to be sourced from CXO for eControllerID=%d, eMSTStreamId=%d\n",
                         eControllerID,
                         eMSTStreamId);
    eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
  }
      
  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_GetDisplayContainerGUID()

  This function will read display container GUID from miniport

Parameters:
  pDisplayCtx   -[in]    : DP Display Context
  pGUID         -[out]   : GUID string to be read.
  uGUIDSize     -[in]    : size of GUID string.

Return:
  DP_Status

**********************************************************************************************************************/
DP_Status DP_GetDisplayContainerGUID(DP_DeviceIDType eDeviceID, DP_MSTStreamIDType eMSTStreamId, uint8* pGUID, uint32 uGUIDSize)
{ 
  DP_Status          eStatus    = DP_STATUS_SUCCESS;

  if ((NULL == pGUID)      ||
      (uGUIDSize != sizeof(GUID)))
  {
    DP_LOG_MESSAGE_ERROR("DP_GetDisplayContainerGUID: Invalid input parameters");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    MDP_Display_IDType eDisplayId = DP_GetDisplayMap(eDeviceID, eMSTStreamId);

    pGUID = (uint8 *)&sDisplayGUID[eDisplayId];

    TraceInfo(QdiTraceDP, "DP%d: DP_GetDisplayContainerGUID() eStatus = 0x%x : Display Container GUID {%4x-%2x-%2x-%x%x%x%x%x%x%x%x} ",
      eDeviceID, eStatus, ((GUID*)pGUID)->Data1, ((GUID*)pGUID)->Data2, ((GUID*)pGUID)->Data3,
      ((GUID*)pGUID)->Data4[0], ((GUID*)pGUID)->Data4[1], ((GUID*)pGUID)->Data4[2], ((GUID*)pGUID)->Data4[3], 
      ((GUID*)pGUID)->Data4[4], ((GUID*)pGUID)->Data4[5], ((GUID*)pGUID)->Data4[6], ((GUID*)pGUID)->Data4[7]);
  }
  
  return eStatus;
}

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
uint64 DP_GetMaxAvailableBw(DP_HandleType   hHandle)
{
  DP_DisplayCtxType      *pDisplayCtx = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_StreamCtxType       *pStreamCtx  = DPHOST_GET_STREAM_CTX(pDisplayCtx);
  DP_DeviceCtxType       *pDeviceCtx  = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  uint64                  uMaxBandwidth       = DP_INVALID_BANDWIDTH;
  uint32                  uLinkRateInKhz      = 0;
 
  if ((NULL != pDeviceCtx) &&
      (NULL != pStreamCtx))
  {
    uLinkRateInKhz = DP_GetLinkRate(pDisplayCtx);

    if (FALSE == pDeviceCtx->bMSTEnabled)
    {
      // In SST case, the limiting factor is only the physical link configuration
      // DP uses 8b/10b encoding to transmit 8 bits of data per link clock cycle.
      // BW in bits/s = (link clk in Hz) * (lane count) * (bits per clock)
      uMaxBandwidth = ((uint64)uLinkRateInKhz * 1000) * pDeviceCtx->sSinkDPCDCap.uMaxLaneCount * DP_BITS_PER_LINKCLK_CYCLE; 

      TraceInfo(QdiTraceDP, "DP%d: EDID Filter, available bandwidth: %dMB/s, link rate: %d, effective link rate: %d, lanes: %d",
                pStreamCtx->eDisplayID,
                (uint32)(uMaxBandwidth/DP_MEGA(1)),
                pDeviceCtx->uLinkRateInKhz,
                uLinkRateInKhz,
                pDeviceCtx->uNumLanes);
    }
  }

  return uMaxBandwidth;
}

//--------DP_GetMinValidBw--------------------------------------------------------------------------------------
//  GetMinValidBw
//
//  @brief
//      Calculate the minimum valid BW based on current config
//
//  @params
//      [IN] pDeviceCtx 
//             DP Device Context
//
//  @return
//      uint64 
//-------------------------------------------------------------------------------------------------
//
static uint64 DP_GetMinValidBw(DP_DeviceCtxType *pDeviceCtx)
{
  uint64 uMinBandwidth = 0;

  if (NULL == pDeviceCtx)
  {
    DP_LOG_MESSAGE_ERROR("GetMinValidBw() : Unexpected null context\n");
  }
  else
  {
    // (Mode BW / Total Link BW) ratio >= 1/64, otherwise empty TUs will be present in SST TU transport, which is not supported by DP controller.
    uMinBandwidth = (((uint64)pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz * 1000) * pDeviceCtx->sSinkDPCDCap.uMaxLaneCount * DP_BITS_PER_LINKCLK_CYCLE) / 64;
  }

  return uMinBandwidth;
}

//-------------------------------------------------------------------------------------------------
//   GetMaxPclkFromModeList
//
//  @brief
//       Helper to get the highest pclk from a list of modes
//
//  @params
//      [IN] pModeList
//             List of modes to loop through
//
//  @return
//      Highest pixel rate among all the modes
//-------------------------------------------------------------------------------------------------
//
static uint32 GetMaxPclkFromModeList(EDID_DispModeListType *pModeList)
{
  uint32 uHighestPClk = 0;
  
  for (uint32 uModeIndex = 0; uModeIndex < pModeList->uNumOfElements; uModeIndex++)
  {
    if (pModeList->aDispModeAttr[uModeIndex].sDisplayModeInfo.uPixelRate > uHighestPClk)
    {
      uHighestPClk = pModeList->aDispModeAttr[uModeIndex].sDisplayModeInfo.uPixelRate;
    }
  }

  return uHighestPClk;
}

//-------------------------------------------------------------------------------------------------
//  DP_GetLinkRate
//
//  @brief
//      Get the current supported link rate considering FEC state
//      and accounting for it's overhead
//
//  @params
//      pDisplayCtx  -[in]    : DP Display Context
//
//  @return
//      uint64 
//-------------------------------------------------------------------------------------------------
//
uint32 DP_GetLinkRate(DP_HandleType   hHandle)
{
  DP_DisplayCtxType      *pDisplayCtx = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_StreamCtxType       *pStreamCtx  = DPHOST_GET_STREAM_CTX(pDisplayCtx);
  DP_DeviceCtxType       *pDeviceCtx  = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  uint32                  uLinkRateInKhz      = 0;
 
  if ((NULL != pDeviceCtx) &&
      (NULL != pStreamCtx))
  {
    if (TRUE == pStreamCtx->sDSCInfo.bFECEnabled)
    {
      // Simulated link rate underperformance for maximum bandwidth calculation for both SST and MST.
      uLinkRateInKhz = pStreamCtx->sDSCInfo.uFECLinkClkInKhz;
    }
    else
    {
      uLinkRateInKhz = pDeviceCtx->uLinkRateInKhz;
    }
  }

  return uLinkRateInKhz;
}

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
MDP_Status DP_OSAL_DummySuccess(void *pDummyArg, ...)
{
  return MDP_STATUS_OK;
}

//-------------------------------------------------------------------------------------------------
//   UpdateModeListToDisplayContext
//
//  @brief
//       Add list of parsed display modes to DisplayContext.
//
//  @params
//      [IN] pDisplayCtx 
//             pointer to DP_DisplayCtxType
//      [IN] psModeList
//             pointer to EDID_DispModeListType
//      [IN] pDisplayRangeDesc
//             pointer to EDID_DisplayRangeInfo
//
//  @return
//      DP_Status
//-------------------------------------------------------------------------------------------------
//
static DP_Status UpdateModeListToDisplayContext(DP_DisplayCtxType *pDisplayCtx, EDID_DispModeListType *psModeList, EDID_DisplayRangeInfo *pDisplayRangeDesc)
{
  DP_Status eStatus = DP_STATUS_SUCCESS;

  if ((NULL == pDisplayCtx) ||
      (NULL == psModeList))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("UpdateModeListToDisplayContext failed with status =0x%i", eStatus);
  }
  else 
  {
    DP_StreamCtxType *pStreamCtx          = DPHOST_GET_STREAM_CTX(pDisplayCtx);
    uint32            uModeIndex          = 0;
    uint32            uModeListIndex      = 0;
    uint32            uPreferredModeIndex = 0;

    // Check, for fail Safe mode
    if ((1    == pStreamCtx->uNumModes)                           &&
        (TRUE == pStreamCtx->sPanelInfo[uModeIndex].bVirtualMode) &&
        (0    <  psModeList->uNumOfElements))
    {
      // Clear fail safe mode, as we have valid video mode provided by Panel EDID
      DISP_OSAL_MemZero((void*)& (pStreamCtx->sPanelInfo[uModeIndex]), sizeof(DP_PanelInfoType));

      pStreamCtx->uNumModes = 0;
    }

    uModeIndex     = pStreamCtx->uNumModes;
    uModeListIndex = pStreamCtx->uNumModes;

    // Update number of new modes coming in
    pStreamCtx->uNumModes += (psModeList->uNumOfElements - uModeIndex) ;

    if (pStreamCtx->uNumModes > MAX_DP_PANEL_MODE)
    {
      pStreamCtx->uNumModes = MAX_DP_PANEL_MODE;
    }
  
    while ((uModeIndex     < pStreamCtx->uNumModes) &&
           (uModeListIndex < psModeList->uNumOfElements))
    {
      pStreamCtx->sPanelInfo[uModeIndex].uModeIndex               = uModeIndex;
      pStreamCtx->sPanelInfo[uModeIndex].uPclkFreq                = psModeList->aDispModeAttr[uModeListIndex].sDisplayModeInfo.uPixelRate;
      pStreamCtx->sPanelInfo[uModeIndex].uVisibleWidthInPixels    = psModeList->aDispModeAttr[uModeListIndex].sDisplayModeInfo.uWidthPx;
      pStreamCtx->sPanelInfo[uModeIndex].uHsyncFrontPorchInPixels = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.iHsyncFrontPorchDclk;
      pStreamCtx->sPanelInfo[uModeIndex].uHsyncBackPorchInPixels  = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.iHsyncBackPorchDclk;
      pStreamCtx->sPanelInfo[uModeIndex].uHsyncPulseInPixels      = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.iHsyncPulseWidthDclk;
      pStreamCtx->sPanelInfo[uModeIndex].uHsyncSkewInPixels       = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.iHsyncSkewDclk;
      pStreamCtx->sPanelInfo[uModeIndex].uVisibleHeightInPixels   = psModeList->aDispModeAttr[uModeListIndex].sDisplayModeInfo.uHeightPx;
      pStreamCtx->sPanelInfo[uModeIndex].uVsyncFrontPorchInLines  = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.iVsyncFrontPorchLines;
      pStreamCtx->sPanelInfo[uModeIndex].uVsyncBackPorchInLines   = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.iVsyncBackPorchLines;
      pStreamCtx->sPanelInfo[uModeIndex].uVsyncPulseInLines       = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.iVsyncPulseWidthLines;
      pStreamCtx->sPanelInfo[uModeIndex].bHSyncActiveLow          = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.bIsHsyncActiveLow;
      pStreamCtx->sPanelInfo[uModeIndex].bVSyncActiveLow          = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.bIsVsyncActiveLow;
      pStreamCtx->sPanelInfo[uModeIndex].uHLeftBorderInPixels     = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.iHLeftBorderDClk;
      pStreamCtx->sPanelInfo[uModeIndex].uHRightBorderInPixels    = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.iHRightBorderDClk;
      pStreamCtx->sPanelInfo[uModeIndex].uVTopBorderInLines       = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.iVTopBorderLines;
      pStreamCtx->sPanelInfo[uModeIndex].uVBottomBorderInLines    = psModeList->aDispModeAttr[uModeListIndex].sActiveTimingInfo.iVBottomBorderLines;
      pStreamCtx->sPanelInfo[uModeIndex].uRefreshRate             = psModeList->aDispModeAttr[uModeListIndex].sDisplayModeInfo.uRefreshRate;
      pStreamCtx->sPanelInfo[uModeIndex].bInterlaced              = psModeList->aDispModeAttr[uModeListIndex].sDisplayModeInfo.bInterlaced;
      pStreamCtx->sPanelInfo[uModeIndex].bAudioSupported          = psModeList->aDispModeAttr[uModeListIndex].sDisplayModeInfo.bAudioSupported;
      pStreamCtx->sPanelInfo[uModeIndex].u3DFrameFormat           = psModeList->aDispModeAttr[uModeListIndex].sDisplayModeInfo.e3DFrameFormat;
      pStreamCtx->sPanelInfo[uModeIndex].uAspectRatio             = psModeList->aDispModeAttr[uModeListIndex].sDisplayModeInfo.eAspectRatio;
      pStreamCtx->sPanelInfo[uModeIndex].uRotation                = psModeList->aDispModeAttr[uModeListIndex].sDisplayModeInfo.eRotation;
      pStreamCtx->sPanelInfo[uModeIndex].eColorFormat             = ConvertQdiPixelFormatToDp((MDP_PixelFormatType)psModeList->aDispModeAttr[uModeListIndex].sDisplayModeInfo.eColorFormat);

      // If refresh rate is not our preferred refresh rate, but timing supports refresh rate ranges then adjust the timing to select the prefrerred refresh
      if ((DP_Q16_TO_DECIMAL(pStreamCtx->sPanelInfo[uModeIndex].uRefreshRate) > DP_PREFERRED_REFRESH_RATE_HZ) &&
          (pDisplayRangeDesc->uMinVRate > 0)                                                                   &&
          (pDisplayRangeDesc->uMinVRate  <= DP_PREFERRED_REFRESH_RATE_HZ))
      {
        uint32 uHTotal = pStreamCtx->sPanelInfo[uModeIndex].uVisibleWidthInPixels   + pStreamCtx->sPanelInfo[uModeIndex].uHsyncFrontPorchInPixels +
                         pStreamCtx->sPanelInfo[uModeIndex].uHsyncBackPorchInPixels + pStreamCtx->sPanelInfo[uModeIndex].uHsyncPulseInPixels;
        uint32 uVTotal = pStreamCtx->sPanelInfo[uModeIndex].uVisibleHeightInPixels  + pStreamCtx->sPanelInfo[uModeIndex].uVsyncFrontPorchInLines  +
                         pStreamCtx->sPanelInfo[uModeIndex].uVsyncBackPorchInLines  + pStreamCtx->sPanelInfo[uModeIndex].uVsyncPulseInLines;

        if (uHTotal)
        {
          // Calculate the new VTotal based on the desired refresh rate
          uint32 uNewVtotal = pStreamCtx->sPanelInfo[uModeIndex].uPclkFreq / (DP_PREFERRED_REFRESH_RATE_HZ * uHTotal);

          // Sanity to ensure our new Vtotal is greater than the original VTotal
          if (uNewVtotal > uVTotal)
          {
            // Increase the front porch by the delta and update the new refresh rate keeping pixel clock the same.
            pStreamCtx->sPanelInfo[uModeIndex].uVsyncFrontPorchInLines += (uNewVtotal - uVTotal);
            pStreamCtx->sPanelInfo[uModeIndex].uRefreshRate             = DP_DECIMAL_TO_Q16(DP_PREFERRED_REFRESH_RATE_HZ);
          }
        }
      }

      // Keep track of preferred mode index.
      if (psModeList->aDispModeAttr[uModeListIndex].bPreferredMode) 
      {
        uPreferredModeIndex = (0 == uPreferredModeIndex) ? uModeIndex : uPreferredModeIndex ;
      }

      uModeIndex++;
      uModeListIndex++;
    }

    // Update Preferred Video mode as default mode (Mode 0).
    if ((0                 != uPreferredModeIndex) &&
        (DP_STATUS_SUCCESS != AdjustPreferredMode(uPreferredModeIndex,pStreamCtx)))
    {
      DP_LOG_MESSAGE_ERROR("UpdateModeListToDisplayContext: failed to set preferred mode as default mode.");
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  AdjustPreferredMode
//
//  @brief
//    Updates Mode list to have preferred mode as default video mode (Mode 0).
//
//  @params
//      [IN] pModeInfo
//          Pointer to EDID_DispModeTimingType, which is to be added to mode list.
//      [IN] pEdidSharedData
//          Pointer to EDID_ParserContextType.
//
//  @return
//-------------------------------------------------------------------------------------------------
//
static DP_Status AdjustPreferredMode(uint32 uPreferredModeIndex, DP_StreamCtxType* pStreamCtx)
{
  DP_Status eStatus = DP_STATUS_SUCCESS;

  if (pStreamCtx->uNumModes < uPreferredModeIndex)
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DISP_OSAL_LOGX("AdjustPreferredMode: failed, requested preferred mode (%d) is larger than total number of modes (%d)", uPreferredModeIndex, pStreamCtx->uNumModes);
  }
  else 
  {
    DP_PanelInfoType sPreferredModeInfo;
    uint32           uIndex = uPreferredModeIndex ;

    DISP_OSAL_MemCpyEx(&(sPreferredModeInfo), sizeof(DP_PanelInfoType), &(pStreamCtx->sPanelInfo[uPreferredModeIndex]), sizeof(DP_PanelInfoType));

    // Shift video modes 
    while (0 < uIndex )
    {
      DISP_OSAL_MemCpyEx(&(pStreamCtx->sPanelInfo[uIndex]), sizeof(DP_PanelInfoType), &(pStreamCtx->sPanelInfo[uIndex-1]), sizeof(DP_PanelInfoType));
      pStreamCtx->sPanelInfo[uIndex].uModeIndex++;
      uIndex--;
    }

    // Update preferred video mode index to 0.
    sPreferredModeInfo.uModeIndex = 0;
    DISP_OSAL_MemCpyEx(&(pStreamCtx->sPanelInfo[0]), sizeof(DP_PanelInfoType), &(sPreferredModeInfo), sizeof(DP_PanelInfoType));
  }

  return eStatus;
}

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
int DP_Ceil(double Number)
{
    if (Number >= 0)
    {
        if (Number == (int)Number)
            return (int)Number;
        else
            return (int)Number + 1;
    }
    else
    {
        return (int)Number;
    }
}

//-------------------------------------------------------------------------------------------------
//   FilterDuplicateModes
//
//  @brief
//       Filter out modes that the OS graphics stack would consider as duplicate.
//
//  @params
//      [IN] pStreamCtx
//             ointer to DP_StreamCtxType
//      [IN] pDisplayCtx
//             pointer to DP_DisplayCtxType
//      [IN] psModeList
//             pointer to EDID_DispModeListType
//
//  @return
//      DP_Status
//-------------------------------------------------------------------------------------------------
//
static DP_Status FilterDuplicateModes(DP_StreamCtxType *pStreamCtx, DP_DisplayCtxType *pDisplayCtx, EDID_DispModeListType *psModeList)
{
  DP_Status  eStatus = DP_STATUS_SUCCESS;

  if ((NULL == pStreamCtx) ||
      (NULL == psModeList))
  {
    DP_LOG_MESSAGE_ERROR("FilterDuplicateModes() : DP context is NULL pointer\n");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if ((psModeList->uNumOfElements > 1) &&
           (psModeList->uNumOfElements <= EDID_DISP_MODE_LIST_MAX_NUM))
  {
    bool32                bDeletedModes[EDID_DISP_MODE_LIST_MAX_NUM] = {FALSE};
    EDID_DispModeListType sUpdatedModeList;
 
    // If there are multiple modes with the same resolution and refresh but different blanking,
    // the OS treats them as duplicates and exposes these modes on a FCFS basis. Filter out all
    // modes in the set of duplicates except the one most suitable for end user.

    // For each mode ("mode A") in list:
    for (uint32 uModeAIdx = 0; uModeAIdx < (psModeList->uNumOfElements - 1); uModeAIdx++) 
    {
      // If mode A is not already marked for deletion
      if (!bDeletedModes[uModeAIdx])
      {
        // For each mode ("mode B") succeeding mode A mode in list:
        for (uint32 uModeBIdx = uModeAIdx + 1; uModeBIdx < psModeList->uNumOfElements; uModeBIdx++) 
        {
          // If mode B is not already marked for deletion
          if (!bDeletedModes[uModeBIdx])
          {
            EDID_DispModeAttrType *pModeAInfo = &psModeList->aDispModeAttr[uModeAIdx];
            EDID_DispModeAttrType *pModeBInfo = &psModeList->aDispModeAttr[uModeBIdx];

            // If active width, active height, and refresh rate are the same but pixel clock is different,
            // we have a set of duplicate modes, of which one needs to be filtered out.
            if ((pModeAInfo->sDisplayModeInfo.uWidthPx == pModeBInfo->sDisplayModeInfo.uWidthPx)           &&
                (pModeAInfo->sDisplayModeInfo.uHeightPx == pModeBInfo->sDisplayModeInfo.uHeightPx)         &&
                (((uint32)Q16_CEIL_WHOLE(pModeAInfo->sDisplayModeInfo.uRefreshRate)) == 
                 ((uint32)Q16_CEIL_WHOLE(pModeBInfo->sDisplayModeInfo.uRefreshRate)))                      &&
                (pModeAInfo->sDisplayModeInfo.uPixelRate != pModeBInfo->sDisplayModeInfo.uPixelRate))
            {
              // Get index of least preferred mode (the one to be deleted from the list)
              EDID_DispModeAttrType *pPreferredMode  = GetPreferredMode(pStreamCtx, pDisplayCtx, pModeAInfo, pModeBInfo);

              if (NULL != pPreferredMode)
              {
                EDID_DispModeAttrType *pLeastPreferredMode    = (pModeAInfo == pPreferredMode) ? pModeBInfo : pModeAInfo;
                uint32                 uLeastPreferredModeIdx = (pModeAInfo == pLeastPreferredMode) ? uModeAIdx : uModeBIdx;

                // Mark the mode for deletion
                bDeletedModes[uLeastPreferredModeIdx] = TRUE;

                TraceInfo(QdiTraceDP, "DP%i: FilterDuplicateModes() : Rejecting mode %dx%d with pclk %d KHz. Duplicate of mode %dx%d with pclk %d KHz", 
                                      pStreamCtx->eDisplayID, 
                                      pLeastPreferredMode->sDisplayModeInfo.uWidthPx, 
                                      pLeastPreferredMode->sDisplayModeInfo.uHeightPx,
                                      pLeastPreferredMode->sDisplayModeInfo.uPixelRate,
                                      pPreferredMode->sDisplayModeInfo.uWidthPx,
                                      pPreferredMode->sDisplayModeInfo.uHeightPx,
                                      pPreferredMode->sDisplayModeInfo.uPixelRate);

                // If mode to delete is mode A, break from inner loop
                if (uLeastPreferredModeIdx == uModeAIdx)
                {
                  break;
                }
              }
            }
          }
        }
      }
    }

    DISP_OSAL_MemZero((void*)&sUpdatedModeList, sizeof(EDID_DispModeListType));

    // Generate a new modelist excluding the modes marked for deletion
    for (uint32 uModeIdx = 0; uModeIdx < psModeList->uNumOfElements; uModeIdx++)
    {
      if (!bDeletedModes[uModeIdx])
      {
        DISP_OSAL_MemCpyEx(&sUpdatedModeList.aDispModeAttr[sUpdatedModeList.uNumOfElements], sizeof(EDID_DispModeAttrType), 
                           &psModeList->aDispModeAttr[uModeIdx], sizeof(EDID_DispModeAttrType));

        sUpdatedModeList.uNumOfElements++;
      }
    }

    // Copy the new modelist list to the modelist structure
    DISP_OSAL_MemCpyEx(psModeList, sizeof(EDID_DispModeListType), (void*)&sUpdatedModeList, sizeof(EDID_DispModeListType));
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//   GetPreferredMode
//
//  @brief
//       Given two display modes, identical by the resolution and refresh rate, return the mode
//       most preferable for the end user.
//
//  @params
//      [IN] pModeA
//             Pointer to structure of first mode being compared
//      [IN] pModeB
//             Pointer to structure of second mode being compared
//
//  @return
//      Pointer to the least desired mode between 
//-------------------------------------------------------------------------------------------------
//
static EDID_DispModeAttrType* GetPreferredMode(DP_StreamCtxType      *pStreamCtx,
                                                  DP_DisplayCtxType *pDisplayCtx,
                                                  EDID_DispModeAttrType *pModeA,
                                                  EDID_DispModeAttrType *pModeB)
{

  EDID_DispModeAttrType    *pPrefferedMode  = NULL;
  DP_DeviceCtxType         *pDeviceCtx      = DPHOST_GET_DEVICE_CTX(pDisplayCtx);

  if ((NULL == pStreamCtx) ||
      (NULL == pModeA)     ||
      (NULL == pModeB)     ||
      (NULL == pDeviceCtx))
  {
    DP_LOG_MESSAGE_ERROR("GetPreferredMode() : Unexpected NULL context\n");
  }
  else
  {
    uint32 uBpcModeA    = DPHOST_GETPIXELFMT(ConvertQdiPixelFormatToDp((MDP_PixelFormatType)pModeA->sDisplayModeInfo.eColorFormat)).uBitsPerComponent;
    uint32 uBpcModeB    = DPHOST_GETPIXELFMT(ConvertQdiPixelFormatToDp((MDP_PixelFormatType)pModeB->sDisplayModeInfo.eColorFormat)).uBitsPerComponent;
    uint32 uHblankModeA = pModeA->sActiveTimingInfo.iHsyncBackPorchDclk + pModeA->sActiveTimingInfo.iHsyncPulseWidthDclk + pModeA->sActiveTimingInfo.iHsyncFrontPorchDclk;
    uint32 uHblankModeB = pModeB->sActiveTimingInfo.iHsyncBackPorchDclk + pModeB->sActiveTimingInfo.iHsyncPulseWidthDclk + pModeB->sActiveTimingInfo.iHsyncFrontPorchDclk;
    uint32 uPclkModeA   = pModeA->sDisplayModeInfo.uPixelRate;    // uPixelClk is not populated yet
    uint32 uPclkModeB   = pModeB->sDisplayModeInfo.uPixelRate;

    // Run both the modes through a series of filters and see if one can be eliminated along the way
    if ((pDeviceCtx->sSinkDPCDCap.eRxFeatureEnumList & DP_RX_FEATURE_VSC_SDP_COLORIMETRY) &&
        ((10 == uBpcModeA) ^ (10 == uBpcModeB)))
    {
      // Filter 1: HDR
      // If sink supports HDR, pick the 10-bit mode and reject other one
      // But if both modes are 10-bit need to pass on to more filters below
      pPrefferedMode = (10 == uBpcModeA) ? pModeA : pModeB;
    }
    else if (pModeA->sDisplayModeInfo.bAudioSupported != pModeB->sDisplayModeInfo.bAudioSupported)
    {
      // Filter 2: Audio
      // Prioritize a mode with audio if only one of them has support
      pPrefferedMode = (pModeA->sDisplayModeInfo.bAudioSupported) ? pModeA : pModeB;
    }
    else if ((uHblankModeA != uHblankModeB) &&
             (pStreamCtx->sDSCInfo.bDSCEnabled))    // Check EDID context instead?
    {
      // Filter 3: DSC
      // If DSC is enabled, prefer a mode with higher H-Blank to allow for more SDP
      pPrefferedMode = (uHblankModeA > uHblankModeB) ? pModeA : pModeB;
    }
    else if (uBpcModeA != uBpcModeB)
    {
      // Filter 4: Color Format / Bit Depth
      // Prefer the mode with higher bit depth, if HDR/audio support is same
      pPrefferedMode = (uBpcModeA > uBpcModeB) ? pModeA : pModeB;
    }
    else
    {
      // Filter 5: Finale
      // If none of the above filters could eliminate one mode, choose the one with higher pclk
      pPrefferedMode = (uPclkModeA > uPclkModeB) ? pModeA : pModeB;
    }
  }

  return pPrefferedMode;

}

//-------------------------------------------------------------------------------------------------
//   ConvertDpPixelFormatToQdi
//
//  @brief
//       Helper to convert QDI Pixel Format type to DP Pixel Format type
//
//  @params
//      [IN] eQdiPxlFormat
//             Enum for the QDI pixel format
//
//  @return
//      Corresponding DP Pixel Format if there is a match
//      DP_PIXEL_FORMAT_NONE if there is no match
//-------------------------------------------------------------------------------------------------
//
static DP_PixelFormatType ConvertQdiPixelFormatToDp(MDP_PixelFormatType eQdiPxlFormat)
{
  DP_PixelFormatType eDpPxlFormat;

  switch(eQdiPxlFormat)
  {
    case MDP_PIXEL_FORMAT_RGB_666_18BPP:
    {
      eDpPxlFormat = DP_PIXEL_FORMAT_RGB_666_18BPP;
      break;
    }
    case MDP_PIXEL_FORMAT_RGB_101010_30BPP:
    {
      eDpPxlFormat = DP_PIXEL_FORMAT_RGB_101010_30BPP;
      break;
    }
    default:    // including QDI_PIXEL_FORMAT_RGB_888_24BPP
    {
      eDpPxlFormat = DP_PIXEL_FORMAT_RGB_888_24BPP;
      break;
    }
  }

  return eDpPxlFormat;
}

//-------------------------------------------------------------------------------------------------
//  DP_Strncmp
//
//  @brief
//      This function compares two string until number of chars provided
//
//  @params
//      [IN] _l
//          String 1 pointer
//      [IN] _r
//          String 2 pointer
//      [IN] n
//          size in bytes
//
//  @return
//      0 When success
//-------------------------------------------------------------------------------------------------
//
int32 DP_Strncmp(const uint8 *pStr1, const uint8 *pStr2, uint32 n)
{
  const uint8 *pStr1_local=(void *)pStr1, *pStr2_local=(void *)pStr2;
  
  if (!n--)
  {
    return 0;
  }
  
  for (; *pStr1_local && *pStr2_local && n && *pStr1_local == *pStr2_local ; pStr1_local++, pStr2_local++, n--);
  
  return *pStr1_local - *pStr2_local;
}

#ifdef __cplusplus
}
#endif
