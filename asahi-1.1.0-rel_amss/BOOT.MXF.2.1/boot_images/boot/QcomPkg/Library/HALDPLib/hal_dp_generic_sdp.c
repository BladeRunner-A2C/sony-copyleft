/*=============================================================================

File: hal_dp_generic_sdp.c

Source file for DP generic sdp functionality.

Copyright (c) 2019-2023 Qualcomm Technologies, Inc.
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

/*------------------------------------------------------------------------------
* Private Functions
*----------------------------------------------------------------------------*/

/****************************************************************************
** FUNCTION: get_generic_payload_offset()
*/
/*!
* \brief
*     Retrieve the offset of the payload registers for each generic index
*     and stream id from the first generic payload register on stream 0.
*
* \param [in] uGenericIndex - Generic Index to get the offset for.
* \param [in] uStreamId     - DP stream index to get the offset for.
*
* \retval uintPtr of offset from first generic payload register.
****************************************************************************/
static uintPtr get_generic_payload_offset(uint32 uGenericIndex, DP_MSTStreamIDType eStreamId)
{
    uintPtr uOffset;
    if (DP_MST_STREAM_ID_0 == eStreamId)
    {
      switch(uGenericIndex)
      {
      case 0:
        uOffset = 0; // base offset from HWIO_DPTX_0_GENERIC0_0_ADDR
        break;
      case 1:
        uOffset = HWIO_DPTX_0_GENERIC1_0_ADDR - HWIO_DPTX_0_GENERIC0_0_ADDR;
        break;
      case 2:
        uOffset = HWIO_DPTX_0_GENERIC2_0_ADDR - HWIO_DPTX_0_GENERIC0_0_ADDR;
        break;
      default:
        uOffset = 0; // Other Generic SDP not supported
      }
    }
    else if (DP_MST_STREAM_ID_1 == eStreamId)
    {
      switch(uGenericIndex)
      {
      case 0:
        uOffset = HWIO_DPTX_0_DP1_GENERIC0_0_ADDR - HWIO_DPTX_0_GENERIC0_0_ADDR;
        break;
      case 1:
        uOffset = HWIO_DPTX_0_DP1_GENERIC1_0_ADDR - HWIO_DPTX_0_GENERIC0_0_ADDR;
        break;
      case 2:
        uOffset = HWIO_DPTX_0_DP1_GENERIC2_0_ADDR - HWIO_DPTX_0_GENERIC0_0_ADDR;
        break;
      default:
        uOffset = 0; // Other Generic SDP not supported
      }
    }
    else
    {
      uOffset = 0; // Other Stream ID not supported
    }
    return uOffset;
}

/****************************************************************************
** FUNCTION: get_generic_cfg0_enable_shft()
*/
/*!
* \brief
*     Retrieve the shift amount to create a bitmask to enable each generic
*     SDP in the SDP_CFG registers.
*
* \param [in] uGenericIndex  - Generic index to get the shift amount for.
*
* \retval uint32 shift amount to create a bitmask to enable the generic SDP
****************************************************************************/
static uint32 get_generic_cfg0_enable_shft(uint32 uGenericIndex)
{
    uint32 uSHFT;
    switch(uGenericIndex)
    {
    case 0:
      uSHFT = HWIO_DPTX_0_SDP_CFG_GEN0_SDP_EN_SHFT;
      break;
    case 1:
      uSHFT = HWIO_DPTX_0_SDP_CFG_GEN1_SDP_EN_SHFT;
      break;
    case 2:
      uSHFT = HWIO_DPTX_0_SDP_CFG_GEN2_SDP_EN_SHFT;
      break;
    default:
      uSHFT = HWIO_DPTX_0_SDP_CFG_GEN0_SDP_EN_SHFT; // Other Generic SDP not supported
    }
    return uSHFT;
}

/****************************************************************************
** FUNCTION: get_generic_cfg2_sdpsize_shft()
*/
/*!
* \brief
*     Retrieve the shift amount to create a bitmask to configure a generic
*     SDP size in the SDP_CFG2 registers.
*
* \param [in] uGenericIndex  - Generic index to get the shift amount for.
*
* \retval uint32 shift amount to create a bitmask to configure SDP size
****************************************************************************/
static uint32 get_generic_cfg2_sdpsize_shft(uint32 uGenericIndex)
{
    uint32 uSHFT;
    switch(uGenericIndex)
    {
    case 0:
      uSHFT = HWIO_DPTX_0_SDP_CFG2_GENERIC0_SDPSIZE_SHFT;
      break;
    case 1:
      uSHFT = HWIO_DPTX_0_SDP_CFG2_GENERIC1_SDPSIZE_SHFT;
      break;
    case 2:
      uSHFT = HWIO_DPTX_0_SDP_CFG2_GENERIC2_SDPSIZE_SHFT;
      break;
    default:
      uSHFT = HWIO_DPTX_0_SDP_CFG2_GENERIC0_SDPSIZE_SHFT; // Other Generic SDP not supported
    }
    return uSHFT;
}

/****************************************************************************
** FUNCTION: get_generic_cfg0_enable_shft
*/
/*!
* \brief
*     Retrieve the offset to the SDP_CFG0, SDP_CFG2 registers for each DP stream
*     both registers are the same offset for eachother, so they can use
*     the same offset for the stream.
*
* \param [in] eStreamId  - Stream ID to get the offset for.
* \retval uintPtr offset from stream 0 for SDP_CFG register.
****************************************************************************/
static uintPtr get_stream_cfg02_offset(DP_MSTStreamIDType eStreamId)
{
    uintPtr uOffset;
    switch(eStreamId)
    {
    case DP_STREAM_ID_MST0:
      uOffset = 0;
      break;
    case DP_STREAM_ID_MST1:
      uOffset = HWIO_DPTX_0_DP1_SDP_CFG_ADDR - HWIO_DPTX_0_SDP_CFG_ADDR;
      break;
    default:
      uOffset = 0; // Other Stream ids not supported
    }
    return uOffset;
}

/*------------------------------------------------------------------------------
* Public Functions
*----------------------------------------------------------------------------*/

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
                              bool32               bEnable)
{
  if (HAL_DP_ValidateControllerID(eControllerId))
  {
    uint32  uRegVal;
    uintPtr uCtrlOffset         = HAL_DP_GetRegBaseOffset(eControllerId); // Offset for DP controller register set
    uintPtr uStreamCtrl02Offset = get_stream_cfg02_offset(eStreamId);     // Offset from sdp_cfg(2) for MST streams
    uint32  uSDPEnableBit       = bEnable ? 1 : 0;

    // Bit set/reset for the enable bit in SDP_CFG
    uRegVal  = in_dword(uCtrlOffset + uStreamCtrl02Offset + HWIO_DPTX_0_SDP_CFG_ADDR);
    uRegVal &= ~(1 << get_generic_cfg0_enable_shft(uGenericIndex));
    uRegVal |= uSDPEnableBit << get_generic_cfg0_enable_shft(uGenericIndex);
    out_dword(uCtrlOffset + uStreamCtrl02Offset + HWIO_DPTX_0_SDP_CFG_ADDR, uRegVal);
  }
}


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
                              HAL_DP_GenericSDPConfigType *psGenericSDPCfg)
{
  if (HAL_DP_ValidateControllerID(eControllerId))
  {
    uintPtr uCtrlOffset           = HAL_DP_GetRegBaseOffset(eControllerId);
    uintPtr uGenericPayloadOffset = get_generic_payload_offset(uGenericIndex, eStreamId);
    uintPtr uStreamCtrl02Offset   = get_stream_cfg02_offset(eStreamId);
    uint32  uSDPSizeBit           = (psGenericSDPCfg->uPayloadBytes > 16) ? 1 : 0;
    uint32  uDataIndex            = 0;

    // Num payload registers that need to be cleared, 16/32 bytes correspond to 4/8 registers respectively
    uint32  uPayloadZeroRegisters = (psGenericSDPCfg->uPayloadBytes > 16) ? 8 : 4; // Num payload registers to zero out
    // Num payload registers for packet, registers are 4 bytes
    uint32  uPayloadRegisters     = HAL_CEIL(psGenericSDPCfg->uPayloadBytes, 4);

    uint32  uRegVal;
    uint32  dataByte;
    uint8   parityByte;
    uint32  uReg;
    uint32  uByte;

    // Set size of packet (16/32 bytes) (Bit set/reset for SDP_CFG2 generic size bit)
    uRegVal = in_dword(uCtrlOffset + uStreamCtrl02Offset + HWIO_DPTX_0_SDP_CFG2_ADDR);
    uRegVal &= ~(1 << get_generic_cfg2_sdpsize_shft(uGenericIndex));
    uRegVal |= uSDPSizeBit << get_generic_cfg2_sdpsize_shft(uGenericIndex);
    out_dword(uCtrlOffset + uStreamCtrl02Offset + HWIO_DPTX_0_SDP_CFG2_ADDR, uRegVal);

    // fill Generic<id>_0 Register with HB0 PB0 HB1 PB1
    uRegVal = 0; // Every value is updated in this register

    dataByte   = psGenericSDPCfg->uHB0;
    parityByte = HAL_DP_SDP_CalculateECC(&dataByte, 1);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_GENERIC0_0, HB0, dataByte);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_GENERIC0_0, PB0, parityByte);
    dataByte   = psGenericSDPCfg->uHB1;
    parityByte = HAL_DP_SDP_CalculateECC(&dataByte, 1);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_GENERIC0_0, HB1, dataByte);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_GENERIC0_0, PB1, parityByte);

    out_dword(uCtrlOffset + uGenericPayloadOffset + HWIO_DPTX_0_GENERIC0_0_ADDR, uRegVal);

    // fill Generic<id>_1 Register with HB2 PB2 HB3 PB3
    uRegVal    = 0; // Every value is updated in this register

    dataByte   = psGenericSDPCfg->uHB2;
    parityByte = HAL_DP_SDP_CalculateECC(&dataByte, 1);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_GENERIC0_1, HB2, dataByte);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_GENERIC0_1, PB2, parityByte);
    dataByte   = psGenericSDPCfg->uHB3;
    parityByte = HAL_DP_SDP_CalculateECC(&dataByte, 1);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_GENERIC0_1, HB3, dataByte);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_GENERIC0_1, PB3, parityByte);

    out_dword(uCtrlOffset + uGenericPayloadOffset + HWIO_DPTX_0_GENERIC0_1_ADDR, uRegVal);

    uDataIndex = 0;
    // Fill Generic<id> payload registers for the bytes we do have, zero missing bytes
    for (uReg = 0; uReg < uPayloadRegisters; uReg++)
    {
      uRegVal = 0;
      for (uByte = 0; uByte < 4; uByte++)
      {
        if (uDataIndex < psGenericSDPCfg->uPayloadBytes)
        {
          uRegVal |= psGenericSDPCfg->pSDPPayload[uDataIndex] << (8 * uByte);
          uDataIndex++;
        }
      }
      out_dword(uCtrlOffset + uGenericPayloadOffset + HWIO_DPTX_0_GENERIC0_2_ADDR + (4 * (uint64)uReg), uRegVal);
    }

    // Continue where we left off and zero remaining registers to 16/32 bytes
    uRegVal = 0;
    for (; uReg < uPayloadZeroRegisters; uReg++)
    {
      out_dword(uCtrlOffset + uGenericPayloadOffset + HWIO_DPTX_0_GENERIC0_2_ADDR + (4 * (uint64)uReg), uRegVal);
    }
  }
}

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
                          bool32               bEnable)
{
  if (HAL_DP_ValidateControllerID(eControllerId))
  {
    uint32  uRegVal;
    uintPtr uCtrlOffset         = HAL_DP_GetRegBaseOffset(eControllerId); // Offset for DP controller register set
    uint32  uSDPEnableBit       = bEnable ? 1 : 0;

    // Bit set/reset for the enable bit in CONFIGURATION_CTRL for the particular stream
    if (DP_MST_STREAM_ID_1 == eStreamId) 
    {
      uRegVal = in_dword(uCtrlOffset + HWIO_DPTX_0_DP1_CONFIGURATION_CTRL_ADDR);
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_CONFIGURATION_CTRL, SEND_VSC, uSDPEnableBit);
      out_dword(uCtrlOffset + HWIO_DPTX_0_DP1_CONFIGURATION_CTRL_ADDR, uRegVal);
    }
    else
    {
      uRegVal = in_dword(uCtrlOffset + HWIO_DPTX_0_CONFIGURATION_CTRL_ADDR);
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_CONFIGURATION_CTRL, SEND_VSC, uSDPEnableBit);
      out_dword(uCtrlOffset + HWIO_DPTX_0_CONFIGURATION_CTRL_ADDR, uRegVal);
    }
    
  }
}
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
* \param [in] eControllerId         - Controller to configure
* \param [in] eStreamId             - Stream to configure
* \param [in] psVSCSDPCfg           - VSC SDP configuration
*
* \retval void
*
****************************************************************************/

void HAL_DP_VSCSDP_Config(DP_ControllerIDType      eControllerId,
                          DP_MSTStreamIDType       eStreamId,
                          HAL_DP_VSCSDPConfigType *psVSCSDPCfg)
{
  if (HAL_DP_ValidateControllerID(eControllerId))
  {
    uintPtr uCtrlOffset           = HAL_DP_GetRegBaseOffset(eControllerId);
    uintPtr uVSCPayloadOffset;
    uintPtr uStreamCtrl02Offset   = get_stream_cfg02_offset(eStreamId);
    uint32  uSDPSizeBit           = (psVSCSDPCfg->uPayloadBytes > 16) ? 1 : 0;
    uint32  uRegVal;
    uint32  dataByte;
    uint8   parityByte;
    
    // Set size of packet (16/32 bytes) (Bit set/reset for SDP_CFG2 generic size bit)
    uRegVal = in_dword(uCtrlOffset + uStreamCtrl02Offset + HWIO_DPTX_0_SDP_CFG2_ADDR);
    uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_SDP_CFG2, VSC_SDPSIZE, uSDPSizeBit);

    out_dword(uCtrlOffset + uStreamCtrl02Offset + HWIO_DPTX_0_SDP_CFG2_ADDR, uRegVal);

    // fill VSC<id>_0 Register with HB0 PB0 HB1 PB1
    uRegVal           = 0; // Every value is updated in this register
    uVSCPayloadOffset = (0 == eStreamId) ? 0 : (HWIO_DPTX_0_DP1_VSC_HB0_PB0_HB1_PB1_ADDR - HWIO_DPTX_0_VSC_HB0_PB0_HB1_PB1_ADDR); // stream offset

    dataByte   = psVSCSDPCfg->uHB0;
    parityByte = HAL_DP_SDP_CalculateECC(&dataByte, 1);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_VSC_HB0_PB0_HB1_PB1, HB0, dataByte);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_VSC_HB0_PB0_HB1_PB1, PB0, parityByte);
    dataByte   = psVSCSDPCfg->uHB1;
    parityByte = HAL_DP_SDP_CalculateECC(&dataByte, 1);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_VSC_HB0_PB0_HB1_PB1, HB1, dataByte);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_VSC_HB0_PB0_HB1_PB1, PB1, parityByte);
    
    out_dword(uCtrlOffset + uVSCPayloadOffset + HWIO_DPTX_0_VSC_HB0_PB0_HB1_PB1_ADDR, uRegVal);
    
    // fill VSC<id>_1 Register with HB2 PB2 HB3 PB3
    uRegVal           = 0; // Every value is updated in this register
    uVSCPayloadOffset = (0 == eStreamId) ? 0 : (HWIO_DPTX_0_DP1_VSC_HB2_PB2_HB3_PB3_ADDR - HWIO_DPTX_0_VSC_HB2_PB2_HB3_PB3_ADDR); // stream offset

    dataByte   = psVSCSDPCfg->uHB2;
    parityByte = HAL_DP_SDP_CalculateECC(&dataByte, 1);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_VSC_HB2_PB2_HB3_PB3, HB2, dataByte);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_VSC_HB2_PB2_HB3_PB3, PB2, parityByte);
    dataByte   = psVSCSDPCfg->uHB3;
    parityByte = HAL_DP_SDP_CalculateECC(&dataByte, 1);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_VSC_HB2_PB2_HB3_PB3, HB3, dataByte);
    uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_VSC_HB2_PB2_HB3_PB3, PB3, parityByte);

    out_dword(uCtrlOffset + uVSCPayloadOffset + HWIO_DPTX_0_VSC_HB2_PB2_HB3_PB3_ADDR, uRegVal);

    // Payload byte 16, 17 and 18 are used for send VSC SDP
    if (psVSCSDPCfg->uPayloadBytes >= 18)
    {
      uRegVal = 0;

      uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_VSC_DB16_DB17_DB18_PB8, DB16, psVSCSDPCfg->pSDPPayload[16]);
      uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_VSC_DB16_DB17_DB18_PB8, DB17, psVSCSDPCfg->pSDPPayload[17]);
      uRegVal    = HWIO_OUT_FLD(uRegVal, DPTX_0_VSC_DB16_DB17_DB18_PB8, DB18, psVSCSDPCfg->pSDPPayload[18]);
      out_dword(uCtrlOffset + uVSCPayloadOffset + HWIO_DPTX_0_VSC_DB16_DB17_DB18_PB8_ADDR, uRegVal);
    }
  }
}

#ifdef __cplusplus
}
#endif
