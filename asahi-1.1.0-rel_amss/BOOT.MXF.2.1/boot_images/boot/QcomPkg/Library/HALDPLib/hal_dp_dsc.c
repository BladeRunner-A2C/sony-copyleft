/*=============================================================================
 
  File: hal_dp_mainlink.c
 
  Source file for DP AUX Main link functionality 
   
  Copyright (c) 2016-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/


/*------------------------------------------------------------------------------
 * Include Files
 *----------------------------------------------------------------------------*/
#include "hal_dp_i.h"

#ifdef __cplusplus
extern "C" {
#endif


/* Ceil function to round off to the nearest interger */
#define DP_CEILF(_x_, _y_)        (((double)(_x_) + ((double)(_y_)-1)) / (double)(_y_))

#define EOL_BYTE_NUM_B2_MASK     0x4

/* -----------------------------------------------------------------------
** Public Functions
** ----------------------------------------------------------------------- */

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
                         HAL_DP_PPSConfigType *psPPSConfig)
{
  uintPtr   uOffset         = HAL_DP_GetRegBaseOffset(eControllerId);
  uintPtr   uPPSRegOffset   = uOffset;
  uintPtr   uFlushRegAddr   = HWIO_DPTX_0_DP_FLUSH_ADDR;
  uint32    uDataByte       = 0;
  uint8     uParityByte     = 0;
  uint32    uHBVal          = 0;
  uint32    uPBVal          = 0;
  uint32    uRegVal         = 0;
  uint8     uPBList[32];
  uint32    i;
  uint32    j;
  uint8    *puData;

  puData = psPPSConfig->puPPSBuffer;

  // Adjust the offset for stream 1
  if (DP_STREAM_ID_MST1 == psPPSConfig->uStreamId)
  {
    uPPSRegOffset += (HWIO_DPTX_0_DP1_PPS_HB_0_3_ADDR - HWIO_DPTX_0_PPS_HB_0_3_ADDR);
    uFlushRegAddr  = HWIO_DPTX_0_DP1_FLUSH_ADDR;
  }

  uHBVal     = in_dword(uPPSRegOffset + HWIO_DPTX_0_PPS_HB_0_3_ADDR);
  uPBVal     = in_dword(uPPSRegOffset + HWIO_DPTX_0_PPS_PB_0_3_ADDR);

  uDataByte   = 0;
  uHBVal      = HWIO_OUT_FLD(uHBVal, DPTX_0_PPS_HB_0_3, PPS_HB0, uDataByte);
  uParityByte = HAL_DP_SDP_CalculateECC(&uDataByte, 1);
  uPBVal      = HWIO_OUT_FLD(uPBVal, DPTX_0_PPS_PB_0_3, PPS_PB0, uParityByte);

  uDataByte   = 0x10;
  uHBVal     = HWIO_OUT_FLD(uHBVal, DPTX_0_PPS_HB_0_3, PPS_HB1, uDataByte);
  uParityByte = HAL_DP_SDP_CalculateECC(&uDataByte, 1);
  uPBVal      = HWIO_OUT_FLD(uPBVal, DPTX_0_PPS_PB_0_3, PPS_PB1, uParityByte);

  uDataByte   = 0x7f;
  uHBVal     = HWIO_OUT_FLD(uHBVal, DPTX_0_PPS_HB_0_3, PPS_HB2, uDataByte);
  uParityByte = HAL_DP_SDP_CalculateECC(&uDataByte, 1);
  uPBVal      = HWIO_OUT_FLD(uPBVal, DPTX_0_PPS_PB_0_3, PPS_PB2, uParityByte);

  uDataByte   = 0;
  uHBVal     = HWIO_OUT_FLD(uHBVal, DPTX_0_PPS_HB_0_3, PPS_HB3, uDataByte);
  uParityByte = HAL_DP_SDP_CalculateECC(&uDataByte, 1);
  uPBVal      = HWIO_OUT_FLD(uPBVal, DPTX_0_PPS_PB_0_3, PPS_PB3, uParityByte);

  out_dword(uPPSRegOffset + HWIO_DPTX_0_PPS_HB_0_3_ADDR, uHBVal);
  out_dword(uPPSRegOffset + HWIO_DPTX_0_PPS_PB_0_3_ADDR, uPBVal);

  /*
  * pps_0 to pps_87: 88 bytes of data
  * pps_88 to pps_127 are all 0
  */
  for (i = 0; i < 32; i++)    /* total 88 data bytes */
  {
     uDataByte = 0;

     if (i < 22)
     {
       for (j = 0; j < 4; j++)
       {
          uDataByte |= (*puData << (j * 8));
          puData++;
       }
     }

     uPBList[i] = HAL_DP_SDP_CalculateECC(&uDataByte, 4);
     out_dword(uPPSRegOffset + HWIO_DPTX_0_PPS_PPS_0_3_ADDR + (4 * (uint64)i), uDataByte);
  }

  /*
  * 1 parity byte for every 4 data byte
  * 22 parity bytes derived from above
  * 4 parity bytes per register
  * 6 registers with two 0 parity bytes paded
  * however dp control have 7 registers, each register contains 4 parity bytes 
  */
  puData = uPBList;
  for (i = 0; i < 7; i++)    /* 7 register of 28 parity bytes */
  {
     uDataByte = 0;
     for (j = 0; j < 4; j++)
     {
        uDataByte |= (*puData << (j * 8));
        puData++;
     }

     out_dword(uPPSRegOffset + HWIO_DPTX_0_PPS_PB_4_7_ADDR + (4 * (uint64)i), uDataByte);
  }

  // Flush PPS
  uRegVal = HWIO_OUT_FLD(0, DPTX_0_DP_FLUSH, PPS_FLUSH, 1);
  out_dword(uOffset + uFlushRegAddr, uRegVal);

  // Flush SDP
  HAL_DP_SDP_Flush(eControllerId, psPPSConfig->uStreamId);
  
}

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetDSCConfig()
   
   This API set the DSC configuration 

Parameters: 
   eControllerId              -[in] DP core ID
   psDSCConfig              -[in] Pointer to DSC configurations structure.

Return:  
   None

**********************************************************************************************************************/
void HAL_DP_SetDSCConfig(DP_ControllerIDType     eControllerId,
                         HAL_DP_DSCConfigType   *psDSCConfig)
{
  uint32  uRegVal         = 0;
  uintPtr uOffset         = HAL_DP_GetRegBaseOffset(eControllerId);
  uintPtr uPclkOffset     = HAL_DP_GetPixelClkRegBaseOffset(eControllerId,  psDSCConfig->uStreamId);
  uintPtr uCompModeOffset = HWIO_DPTX_0_COMPRESSION_MODE_CTRL_ADDR;
  uint32  uChunkSize      = 0;
  uint32  uEOLByteNum     = 0;
  uint32  uSlicesPerLine  = 0;
  uint32  uNumerator      = psDSCConfig->uDTONumerator;
  uint32  uDenominator    = psDSCConfig->uDTODenominator;
  uint32  uTargetBpp      = 0;
  uint32  uBeInLane       = psDSCConfig->uBeInLane;

  // DSC
  if (TRUE == psDSCConfig->bCompressed) 
  {
    uTargetBpp     = psDSCConfig->uTargetBppUncompressed / psDSCConfig->uCompressionRatio;
    uChunkSize     = (uint32)DP_CEILF((double)psDSCConfig->uSliceWidth * (float)uTargetBpp,  8.0);
    uEOLByteNum    = uChunkSize % 6;

    if (psDSCConfig->uSlicesPerLine > 0)
    {
      uSlicesPerLine = psDSCConfig->uSlicesPerLine - 1;
    }
  }

  if (DP_STREAM_ID_MST1 == psDSCConfig->uStreamId)
  {
    uCompModeOffset = HWIO_DPTX_0_DP1_COMPRESSION_MODE_CTRL_ADDR;
  }

  /* Compression Mode */
  uRegVal = in_dword(uOffset + uCompModeOffset);
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_COMPRESSION_MODE_CTRL, BYTE_COUNT, uChunkSize);
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_COMPRESSION_MODE_CTRL, SLICES_PER_LINE, uSlicesPerLine);
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_COMPRESSION_MODE_CTRL, EOL_BYTE_NUM_B1_B0, uEOLByteNum);
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_COMPRESSION_MODE_CTRL, EOL_BYTE_NUM_B2, (uEOLByteNum & EOL_BYTE_NUM_B2_MASK));
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_COMPRESSION_MODE_CTRL, BE_IN_LANE, 0xA);
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_COMPRESSION_MODE_CTRL, EN, ((TRUE == psDSCConfig->bCompressed) ? 1 : 0));
  out_dword(uOffset + uCompModeOffset, uRegVal);

  /* DSC DTO */
  uRegVal = in_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_DSC_DTO_ADDR);
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_DSC_DTO, NUMERATOR, uNumerator);
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_DSC_DTO, DENOMINATOR, uDenominator);
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_COMPRESSION_MODE_CTRL, BE_IN_LANE, uBeInLane);
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_DSC_DTO, DTO_EN, ((TRUE == psDSCConfig->bCompressed) ? 1 : 0));
  out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_DSC_DTO_ADDR, uRegVal);

  /* DSC DTO COUNT */
  uRegVal = in_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_DSC_DTO_COUNT_ADDR);
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_DSC_DTO_COUNT, PIXEL_COUNT_PER_LINE, psDSCConfig->uCompressedPixelsPerLine - 1);
  out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_DSC_DTO_COUNT_ADDR, uRegVal);
}

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
                         bool32                 bTunneledMode)
{
  uint32  uRegVal         = 0;
  uintPtr uOffset         = HAL_DP_GetRegBaseOffset(eControllerId);

  if (bTunneledMode)
  {
    out_dword(uOffset + HWIO_DPTX_0_DP_SST_OPCODE2_ADDR,     0x0100FEFD);
    out_dword(uOffset + HWIO_DPTX_0_DP_FEC_EN_SEQ0_ADDR,     0x55555555);
    out_dword(uOffset + HWIO_DPTX_0_DP_FEC_EN_SEQ1_ADDR,     0x55555555);
    out_dword(uOffset + HWIO_DPTX_0_DP_FEC_EN_SEQ2_ADDR,     0x55555555);
    out_dword(uOffset + HWIO_DPTX_0_DP_FEC_EN_DIS_SEQ3_ADDR, 0xFFFFFF55);
    out_dword(uOffset + HWIO_DPTX_0_DP_FEC_DIS_SEQ4_ADDR,    0xFFFFFFFF);
    out_dword(uOffset + HWIO_DPTX_0_DP_FEC_DIS_SEQ5_ADDR,    0xFFFFFFFF);
    out_dword(uOffset + HWIO_DPTX_0_DP_FEC_DIS_SEQ6_ADDR,    0x009CFFFF);
  }
  else
  {
    out_dword(uOffset+ HWIO_DPTX_0_DP_SST_OPCODE2_ADDR,      0x3C00FEFD);
    out_dword(uOffset+ HWIO_DPTX_0_DP_FEC_EN_SEQ0_ADDR,      0xFEFEFE3C);
    out_dword(uOffset+ HWIO_DPTX_0_DP_FEC_EN_SEQ1_ADDR,      0xFE3CF7F7);
    out_dword(uOffset+ HWIO_DPTX_0_DP_FEC_EN_SEQ2_ADDR,      0xF7F73CFE);
    out_dword(uOffset+ HWIO_DPTX_0_DP_FEC_EN_DIS_SEQ3_ADDR,  0xF7F73C3C);
    out_dword(uOffset+ HWIO_DPTX_0_DP_FEC_DIS_SEQ4_ADDR,     0x3CFEFEF7);
    out_dword(uOffset+ HWIO_DPTX_0_DP_FEC_DIS_SEQ5_ADDR,     0xFE3CF7F7);
    out_dword(uOffset+ HWIO_DPTX_0_DP_FEC_DIS_SEQ6_ADDR,     0x009C3CFE);
  }

  /* Configure FEC */
  uRegVal = in_dword(uOffset + HWIO_DPTX_0_MAINLINK_CTRL_ADDR);
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_MAINLINK_CTRL, FEC_SEQ_MODE, ((TRUE == bEnable) ? 1 : 0));
  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_MAINLINK_CTRL, FEC_EN, ((TRUE == bEnable) ? 1 : 0));
  out_dword(uOffset + HWIO_DPTX_0_MAINLINK_CTRL_ADDR, uRegVal);
}

#ifdef __cplusplus
}
#endif

