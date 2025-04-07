/*! \file */

/*
===========================================================================

FILE:         hal_mdp_pingpong.c

DESCRIPTION: Manages the MDP (Display) Pingpong blocks

===========================================================================
  Copyright (c) 2012-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
===========================================================================
*/

#include "hal_mdp_i.h"
#include "hal_mdp_osal.h"

#ifdef __cplusplus
extern "C" {
#endif

/*=========================================================================
     Default Defines
==========================================================================*/

// PPB latency lines
#define MDP_PPB_LATENCY_LINES                            (4)

// PPB fifo entry size, ie. pixel per FIFO entry  
#define MDP_PPB_FIFO_ENTRY_SIZE                          (4)



/****************************************************************************
*
** FUNCTION: HAL_MDP_Get_PingPong_BaseOffset()
*/
/*!
* \brief
*     Returns offset of the pingpong block
*
* \param [in] ePingPongId    - pingpong block ID (none, 0, 1, 2)
*
* \retval uintPtr
*
****************************************************************************/
static uintPtr HAL_MDP_Get_PingPong_BaseOffset(HAL_MDP_PingPongId  ePingPongId)
{
   uintPtr   uRegOffset  = 0x0;

   if((HAL_MDP_PINGPONG_NONE        == ePingPongId) ||
      (HAL_MDP_PINGPONG_MAX         <= ePingPongId))
   {
      HAL_MDP_ASSERT();
   }
   else
   {
      uRegOffset = uMDPPingPongRegBaseOffset[ePingPongId];
   }
   return uRegOffset;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_PingPong_GetStateInfo()
*/
/*!
* \brief
*     Returns the current state (active/idle) of the given ping-pong id
*
* \param [in]   ePingPongId      - Pingpong block id
* \param [out]  pbActive         - TRUE : Module is active
* \param [in]   uFlags           - Reserved
*
* \retval NONE
*
****************************************************************************/
static void HAL_MDP_PingPong_GetStateInfo(HAL_MDP_PingPongId     ePingPongId,
                                          bool32                *pbActive,
                                          uint32                 uFlags)
{
   uint32                        uRegValue         = 0x00;
   HAL_MDP_ModuleStatusRegInfo  *psModuleRegInfo   = NULL;

   *(pbActive)  = FALSE;  // Initial state

   psModuleRegInfo = (HAL_MDP_ModuleStatusRegInfo  *)pgsMdpHwInfo->gpsModuleStatusRegInfo[HAL_MDP_MODULE_PINGPONG];

   if(NULL != psModuleRegInfo)
   {
      uRegValue   = in_dword(MDSS_REG_BASE + psModuleRegInfo[ePingPongId].uRegAddress);

      if(0x00 != (uRegValue & psModuleRegInfo[ePingPongId].uBitFieldMask) )
      {
         *(pbActive)  = TRUE;        // Module is in active state
      }
   }
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_PingPong_DitherConfig()
*/
/*!
* \brief
*     Set up configurations for ping-pong dither module
*
* \param [in]   ePingPongId       - Ping-Pong ID
* \param [in]   psDitherConfig    - Dither configuration information
*
* \retval NONE
*
****************************************************************************/
static void HAL_MDP_PingPong_DitherConfig(HAL_MDP_PingPongId                 ePingPongId,
                                          HAL_MDP_PingPong_DitherConfigType *psDitherConfig)
{
  uintPtr  uRegisterOffset   = 0;
  uint32   uDsppOpModeInfo   = 0;
  uint32   uDitherBitDepth   = 0;

  // Extract the base address to program the HW registers
  uRegisterOffset  = HAL_MDP_Get_PingPong_BaseOffset(ePingPongId);

  uDsppOpModeInfo  = in_dword(HWIO_MDP_PPB_0_DITHER_OP_MODE_ADDR + uRegisterOffset);

  // Dither is only for RGB destination with lower color depth than RGB888
  if (TRUE == psDitherConfig->bEnable) 
  {

    uDitherBitDepth = HWIO_OUT_FLD(uDitherBitDepth,
      MDP_PPB_0_DITHER_BITDEPTH,
      C0_BITS,
      psDitherConfig->sDitherBitDepth.uColor0);

    uDitherBitDepth = HWIO_OUT_FLD(uDitherBitDepth,
      MDP_PPB_0_DITHER_BITDEPTH,
      C1_BITS,
      psDitherConfig->sDitherBitDepth.uColor1);

    uDitherBitDepth = HWIO_OUT_FLD(uDitherBitDepth,
      MDP_PPB_0_DITHER_BITDEPTH,
      C2_BITS,
      psDitherConfig->sDitherBitDepth.uColor2);

    if (psDitherConfig->eDitherType == HAL_MDP_DITHER_TYPE_TEMPORAL)
    {
      uDitherBitDepth = HWIO_OUT_FLD(uDitherBitDepth,
        MDP_PPB_0_DITHER_BITDEPTH,
        TEMPORAL_DITHER_EN,
        1);
    }
    else
    {
      uDitherBitDepth = HWIO_OUT_FLD(uDitherBitDepth,
        MDP_PPB_0_DITHER_BITDEPTH,
        TEMPORAL_DITHER_EN,
        0);
    }

    out_dword(HWIO_MDP_PPB_0_DITHER_BITDEPTH_ADDR + uRegisterOffset, uDitherBitDepth);

    // Dither matrix
    if (NULL != psDitherConfig->pDitherMatrix)
    {
      out_dword(HWIO_MDP_PPB_0_DITHER_MATRIX_ROW0_ADDR + uRegisterOffset, psDitherConfig->pDitherMatrix->uRow0Value);    // ROW#0
      out_dword(HWIO_MDP_PPB_0_DITHER_MATRIX_ROW1_ADDR + uRegisterOffset, psDitherConfig->pDitherMatrix->uRow1Value);    // ROW#1
      out_dword(HWIO_MDP_PPB_0_DITHER_MATRIX_ROW2_ADDR + uRegisterOffset, psDitherConfig->pDitherMatrix->uRow2Value);    // ROW#2
      out_dword(HWIO_MDP_PPB_0_DITHER_MATRIX_ROW3_ADDR + uRegisterOffset, psDitherConfig->pDitherMatrix->uRow3Value);    // ROW#3
    }

    uDsppOpModeInfo  = HWIO_OUT_FLD(uDsppOpModeInfo,
      MDP_PPB_0_DITHER_OP_MODE,
      DITHER_EN,
      1);
  }
  else
  {
    uDsppOpModeInfo  = HWIO_OUT_FLD(uDsppOpModeInfo,
      MDP_PPB_0_DITHER_OP_MODE,
      DITHER_EN,
      0);
  }

  out_dword(HWIO_MDP_PPB_0_DITHER_OP_MODE_ADDR + uRegisterOffset, uDsppOpModeInfo);
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_PingPong_GetInterfaceID()
*/
/*!
* \brief
*     Finds interface id attached to a given ping pong block
*
* \param [in]   ePingPongId      - pingpong block id
* \param [out]  pInterfaceId     - interface id
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_MDP_PingPong_GetInterfaceID(HAL_MDP_PingPongId ePingPongId, HAL_MDP_InterfaceId *pInterfaceId)
{
   uint32                 uInterfaceID;
   HAL_MDSS_ErrorType     eStatus      = HAL_MDSS_MDP_STATUS_FAILED;

   // Find interface ID
   for (uInterfaceID = HAL_MDP_INTERFACE_0; uInterfaceID <= HAL_MDP_GET_PHYSICAL_INTERFACE_COUNT(); uInterfaceID++) 
   {
       uintPtr              uRegOffset   = uMDPPhyInterfaceRegBaseOffset[uInterfaceID];
       uint32               uRegVal      = in_dword(HWIO_MDP_INTF_0_MUX_ADDR + uRegOffset);
       HAL_MDP_PingPongId   ePPID        = HAL_MDP_PINGPONG_NONE;

       // Read attached ping pong block to interface 
       uint32   uPingPongSel = HWIO_GETVAL(MDP_INTF_0_MUX, uRegVal, SEL); 

       // Map from register value to HAL_MDP_PingPongId
       switch(uPingPongSel)
       {
           case 0x0:
           {   
               ePPID = HAL_MDP_PINGPONG_0;
               break;
           }
           case 0x1:
           {   
               ePPID = HAL_MDP_PINGPONG_1;
               break;
           }
           case 0x2:
           {   
               ePPID = HAL_MDP_PINGPONG_2;
               break;
           }
           case 0x3:
           {   
               ePPID = HAL_MDP_PINGPONG_3;
               break;
           }
           case 0x4:
           {   
               ePPID = HAL_MDP_PINGPONG_4;
               break;
           }
           case 0x5:
           {   
               ePPID = HAL_MDP_PINGPONG_5;
               break;
           }
           default:
              break;
          
       }

       if (ePPID == ePingPongId)
       {
           // If execution reach here, it means valid interface ID found. Terminate the loop
          *pInterfaceId  = uInterfaceID;
           eStatus       = HAL_MDSS_STATUS_SUCCESS;
           break;
       }
   }

   return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_PingPong_FIFOSizeConfig()
*/
/*!
* \brief
*     Set FIFO size limit value
*
* \param [in]   ePingPongId           - pingpong block id
* \param [in]   pPingPingFIFOSize     - pingpong FIFO size limit
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
static HAL_MDSS_ErrorType HAL_MDP_PingPong_FIFOSizeConfig(HAL_MDP_PingPongId ePingPongId, HAL_MDP_PingPongBufferSizeLimitType* pPingPingBufferSize)
{
  HAL_MDSS_ErrorType eStatus = HAL_MDSS_STATUS_SUCCESS;
  uint32             uRegVal;
  uint32             uPPBSize;


  /* Limit the number of latency lines to match exactly what is needed to avoid overfilling the fifo with a long fetches.
     Set PPB size limit, setting to panel_width * latnecy_lines / (PPB FIFP entry size (4 pixel per entry) * Mixer#)   */
  uPPBSize = pPingPingBufferSize->uDisplayWidth * MDP_PPB_LATENCY_LINES / MDP_PPB_FIFO_ENTRY_SIZE;
  if (2 == pPingPingBufferSize->uNumMixers)
  {
    uPPBSize = uPPBSize >> 1;
  }
  
  switch (ePingPongId)
  {
    case HAL_MDP_PINGPONG_0:
    {
      uRegVal = in_dword(HWIO_MDP_PPB01_FIFO_SIZE_ADDR);
      uRegVal = HWIO_OUT_FLD(uRegVal, MDP_PPB01_FIFO_SIZE, PPB0_FIFO_SIZE, uPPBSize);
      out_dword(HWIO_MDP_PPB01_FIFO_SIZE_ADDR, uRegVal);
      break;
    }
    case HAL_MDP_PINGPONG_1:
    {
      uRegVal = in_dword(HWIO_MDP_PPB01_FIFO_SIZE_ADDR);
      uRegVal = HWIO_OUT_FLD(uRegVal, MDP_PPB01_FIFO_SIZE, PPB1_FIFO_SIZE, uPPBSize);
      out_dword(HWIO_MDP_PPB01_FIFO_SIZE_ADDR, uRegVal);
      break;
    }
    case HAL_MDP_PINGPONG_2:
    {
      uRegVal = in_dword(HWIO_MDP_PPB23_FIFO_SIZE_ADDR);
      uRegVal = HWIO_OUT_FLD(uRegVal, MDP_PPB23_FIFO_SIZE, PPB2_FIFO_SIZE, uPPBSize);
      out_dword(HWIO_MDP_PPB23_FIFO_SIZE_ADDR, uRegVal);
      break;
    }
    case HAL_MDP_PINGPONG_3:
    {
      uRegVal = in_dword(HWIO_MDP_PPB23_FIFO_SIZE_ADDR);
      uRegVal = HWIO_OUT_FLD(uRegVal, MDP_PPB23_FIFO_SIZE, PPB3_FIFO_SIZE, uPPBSize);
      out_dword(HWIO_MDP_PPB23_FIFO_SIZE_ADDR, uRegVal);
      break;
    }
    case HAL_MDP_PINGPONG_4:
    {
      uRegVal = in_dword(HWIO_MDP_PPB45_FIFO_SIZE_ADDR);
      uRegVal = HWIO_OUT_FLD(uRegVal, MDP_PPB45_FIFO_SIZE, PPB4_FIFO_SIZE, uPPBSize);
      out_dword(HWIO_MDP_PPB45_FIFO_SIZE_ADDR, uRegVal);
      break;
    }
    case HAL_MDP_PINGPONG_5:
    {
      uRegVal = in_dword(HWIO_MDP_PPB45_FIFO_SIZE_ADDR);
      uRegVal = HWIO_OUT_FLD(uRegVal, MDP_PPB45_FIFO_SIZE, PPB5_FIFO_SIZE, uPPBSize);
      out_dword(HWIO_MDP_PPB45_FIFO_SIZE_ADDR, uRegVal);
      break;
    }
    default:
    {
      eStatus = HAL_MDSS_STATUS_FAILED_NOT_SUPPORTED;
      break;
    }
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_PingPong_Setup()
*/
/*!
* \brief
*     Set up configurations for a particular pingpong block
*
* \param [in]   ePingPongId      - pingpong block id
* \param [in]   pPingPongConfig  - Configuration for the selected pingpong block
* \param [in]   uSetupFlags      - Reserved.
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_PingPong_Setup(HAL_MDP_PingPongId             ePingPongId,
                                          HAL_MDP_PingPongConfigType     *pPingPongConfig,
                                          uint32                         uSetupFlags)
{
   HAL_MDSS_ErrorType      eStatus  = HAL_MDSS_STATUS_SUCCESS;

   if((ePingPongId >= HAL_MDP_PINGPONG_0) && ((uint32)ePingPongId <= HAL_MDP_GET_PINGPONG_COUNT()))
   {
      // Dithering
      if(NULL != pPingPongConfig->pDitherConfig)
      {
         HAL_MDP_PingPong_DitherConfig(ePingPongId, pPingPongConfig->pDitherConfig);
      }

      // PPB size limit
      if (NULL != pPingPongConfig->pPingPingBufferSize)
      {
        HAL_MDP_PingPong_FIFOSizeConfig(ePingPongId, pPingPongConfig->pPingPingBufferSize);
      }
   }
   else
   {
      eStatus = HAL_MDSS_STATUS_FAILED_INVALID_INPUT_PARAMETER;
   }

   return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_PingPong_GetProperty()
*/
/*!
* \brief
*     Retrieve information for a particular pingpong block
*
* \param [in]   ePingPongId           - pingpong block id
* \param [out]  pPingPongInfoData     - Info data
* \param [in]   uGetPropertyFlags     - Reserved
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_PingPong_GetProperty(HAL_MDP_PingPongId                   ePingPongId,
                                                HAL_MDP_PingPongInfoParamsType       *pPingPongInfoData,
                                                uint32                               uGetPropertyFlags)
{
   HAL_MDSS_ErrorType   eStatus  = HAL_MDSS_STATUS_SUCCESS;

   // Refresh rate info, it will be deprecated in future revisions
   if (NULL != pPingPongInfoData->pFrameRefreshInfo)
   {
      HAL_MDP_InterfaceInfoParamsType           sInterfaceInfo;
      HAL_MDP_Interface_FrameRefreshInfoType    sFrameRefreshInfo; 
      HAL_MDP_InterfaceId                       eInterfaceId           = HAL_MDP_INTERFACE_NONE;
            
      MDSS_OSAL_MEMZERO(&sInterfaceInfo, sizeof(HAL_MDP_InterfaceInfoParamsType));
      MDSS_OSAL_MEMZERO(&sFrameRefreshInfo, sizeof(HAL_MDP_Interface_FrameRefreshInfoType));

      sInterfaceInfo.pFrameRefreshInfo     = &sFrameRefreshInfo;
      sInterfaceInfo.eInterfaceMode        = HAL_MDP_INTERFACE_MODE_COMMAND;

      // Find interface id of corresponding pingpong id, and query interface
      if (HAL_MDSS_STATUS_SUCCESS == HAL_MDP_PingPong_GetInterfaceID(ePingPongId, &eInterfaceId))
      {
          HAL_MDP_Interface_GetProperty(eInterfaceId, &sInterfaceInfo, 0x00);

          // Copy from Interface structure to Pinpong structure
          pPingPongInfoData->pFrameRefreshInfo->uCurrentFrameCnt = sFrameRefreshInfo.uCurrentFrameCnt;
          pPingPongInfoData->pFrameRefreshInfo->uCurrentLineCnt  = sFrameRefreshInfo.uCurrentLineCnt;
      }
   }

   // Engine status info, it will be deprecated in future revisions
   if (NULL != pPingPongInfoData->pEngineStatus)
   {
       HAL_MDP_InterfaceInfoParamsType         sInterfaceInfo;
       HAL_MDP_Interface_EngineStatusType      sEngineStatus; 
       HAL_MDP_InterfaceId                     eInterfaceId      = HAL_MDP_INTERFACE_NONE;

       MDSS_OSAL_MEMZERO(&sInterfaceInfo, sizeof(HAL_MDP_InterfaceInfoParamsType));
       MDSS_OSAL_MEMZERO(&sEngineStatus, sizeof(HAL_MDP_Interface_EngineStatusType));

       sInterfaceInfo.pEngineStatus         = &sEngineStatus;
       sInterfaceInfo.eInterfaceMode        = HAL_MDP_INTERFACE_MODE_COMMAND;

       // Find interface id of corresponding pingpong id, and query interface
       if (HAL_MDSS_STATUS_SUCCESS == HAL_MDP_PingPong_GetInterfaceID(ePingPongId, &eInterfaceId))
       {
           HAL_MDP_Interface_GetProperty(eInterfaceId, &sInterfaceInfo, 0x00);
           
           // Copy from Interface structure to Pinpong structure
           pPingPongInfoData->pEngineStatus->bIsEngineOn = sEngineStatus.bIsEngineOn;
       }
   }

   // Module active/idle state
   if(NULL != pPingPongInfoData->pbActive)
   {
      HAL_MDP_PingPong_GetStateInfo(ePingPongId, pPingPongInfoData->pbActive, 0x00);
   }

   return eStatus;
}

#ifdef __cplusplus
}
#endif
