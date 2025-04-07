/*=============================================================================
 
  File: hal_dp.c
 
  Source file for DP controller hardware functionality 
   
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


// Defines
// Total (and half) number of time slots 
// availavle for MST within an MTP packet
#define HAL_DP_MST_HALF_SLOT_COUNT 32
#define HAL_DP_MST_FULL_SLOT_COUNT 63

/* Wait for 100 ms to make sure CRC populated after FRAME_END */ 
#define HAL_DP_WAIT_FOR_CRC        100

typedef enum
{
  HAL_DP_TESTPATTERN_NONE                       = 0x00,     /**< Disable Test Pattern               */
  HAL_DP_TESTPATTERN_COUNTER_PATTERN,                       /**< Enable counter pattern             */
  HAL_DP_TESTPATTERN_FIXED_PATTERN,                         /**< Enable fixed pattern               */
  HAL_DP_TESTPATTERN_COLOR_RAMP_64L_64P,                    /**< Enable 64L to 64P pattern          */
  HAL_DP_TESTPATTERN_COLOR_RAMP_64L_256P,                   /**< Enable 64L to 256P pattern         */
  HAL_DP_TESTPATTERN_BLACK_WHITE_VERTICAL_LINES,            /**< Enable black white vertical pattern*/
  HAL_DP_TESTPATTERN_GRAYSCALE_RAMP,                        /**< Enable gray scale pattern          */
  HAL_DP_TESTPATTERN_COLOR_SQUARE,                          /**< Enable color square pattern        */
  HAL_DP_TESTPATTERN_CHECKERED_RECTANGLE_PATTERN,           /**< Enable checked rectangle pattern   */
  HAL_DP_TESTPATTERN_BASIC_COLOR_CHANGING_PATTERN,          /**< Enable basic color changing pattern*/
  HAL_DP_TESTPATTERN_PRBS_PATTERN,                          /**< Enable PRBS pattern                */
  HAL_DP_TESTPATTERN_MAX,
  HAL_DP_TESTPATTERN_FORCE_32BIT = 0x7FFFFFFF
} HAL_DP_TestPatternType;

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
uintPtr HAL_DP_GetRegBaseOffset(DP_ControllerIDType  eControllerId)
{
  uintPtr   uOffset;

  switch (eControllerId)
  {
    case DP_CONTROLLER_ID_DP_0:
    {
      /* DP Alt Mode 0 (DPTX0)*/
      uOffset = 0;
      break;
    }
    case DP_CONTROLLER_ID_DP_1:
    {
      /* DP Alt Mode 1 (DPTX1) */
      uOffset = DPTX_1_AHBCLK_REG_BASE - DPTX_0_AHBCLK_REG_BASE;
      break;
    }
    case DP_CONTROLLER_ID_DP_3:
    {
      /* Primary eDP (DPTX3/eDP) */
      uOffset = DPTX_3_AHBCLK_REG_BASE - DPTX_0_AHBCLK_REG_BASE;
      break;
    }
    case DP_CONTROLLER_ID_DP_2:
    {
      /* DP Alt Mode 2 (DPTX2) */
     uOffset = DPTX_2_AHBCLK_REG_BASE - DPTX_0_AHBCLK_REG_BASE;
      break;
    }
    default:
    {
      //No hardware support for other DP device IDs
      uOffset        = 0;
      break;
    }
  }

  return uOffset;
}

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
                                        DP_StreamIDType      eStreamId)
{
  uintPtr   uOffset     = HAL_DP_GetRegBaseOffset(eControllerId);
  uintPtr   uPclkOffset = 0;

  switch (eStreamId)
  {
  case DP_STREAM_ID_MST1:
    {
      uPclkOffset = DPTX_0_P1CLK_REG_BASE - DPTX_0_P0CLK_REG_BASE;
      break;
    }
  default:
    {
      uPclkOffset = 0;
    }
  }

  return (uOffset + uPclkOffset);
}

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
void HAL_DP_Init(DP_ControllerIDType eControllerId)
{
  if (HAL_DP_ValidateControllerID(eControllerId))
  {
    /* Disable the DP interrupts in the hardware */
    HAL_DP_Interrupt_Disable(eControllerId, HAL_DP_AUX_INTR_ALL, 0);
    HAL_DP_Interrupt_Disable(eControllerId, HAL_DP_INTR_ALL, 0);

    /* Clear the DP interrupts and statuses in the hardware */
    HAL_DP_Interrupt_Clear(eControllerId, HAL_DP_AUX_INTR_ALL, 0);
    HAL_DP_Interrupt_Clear(eControllerId, HAL_DP_INTR_ALL, 0);
  }
}

/****************************************************************************

FUNCTION: HAL_DP_Reset()

   Resets DP HW Block

Parameters: 
   eControllerId     -[in] DP core ID
   uModule           -[in] Which HW module to reset
   uResetFlag        -[in] Reserved

Return:
   HAL_MDSS_ErrorType

****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Reset(DP_ControllerIDType eControllerId,
                                uint32              uModule,
                                uint32              uResetFlag)
{
  if (HAL_DP_ValidateControllerID(eControllerId))
  {
    uint32  uRegVal = 0;
    uintPtr uOffset = HAL_DP_GetRegBaseOffset(eControllerId);

    if (uModule & HAL_DP_MODULE_TYPE_CONTROLLER)
    {
      /* Reset controller */
      uRegVal = in_dword(uOffset + HWIO_DPTX_0_SW_RESET_ADDR);

      if (0 == (uResetFlag & HAL_DP_RESET_FLAG_DEASSERT))
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_SW_RESET, DP_SW_RESET, 1);  
        out_dword(uOffset + HWIO_DPTX_0_SW_RESET_ADDR, uRegVal);
      }

      if (0 == (uResetFlag & HAL_DP_RESET_FLAG_ASSERT))
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_SW_RESET, DP_SW_RESET, 0);  
        out_dword(uOffset + HWIO_DPTX_0_SW_RESET_ADDR, uRegVal);
      }
    }

    if (uModule & HAL_DP_MODULE_TYPE_MAINLINK)
    {
      /*Toggle Reset to Main link Controller*/
      uRegVal = in_dword(uOffset + HWIO_DPTX_0_MAINLINK_CTRL_ADDR);

      if (0 == (uResetFlag & HAL_DP_RESET_FLAG_DEASSERT))
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_MAINLINK_CTRL, SW_MAINLINK_RESET, 1);
        out_dword(uOffset + HWIO_DPTX_0_MAINLINK_CTRL_ADDR, uRegVal);
      }

      if (0 == (uResetFlag & HAL_DP_RESET_FLAG_ASSERT))
      {
        /*Clear Reset*/
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_MAINLINK_CTRL, SW_MAINLINK_RESET, 0);
        out_dword(uOffset + HWIO_DPTX_0_MAINLINK_CTRL_ADDR, uRegVal);
      }
    }

    if (uModule & HAL_DP_MODULE_TYPE_AUX)
    {
      /*Toggle Reset to AUX Controller*/
      uRegVal = in_dword(uOffset + HWIO_DPTX_0_AUX_CTRL_ADDR);

      if (0 == (uResetFlag & HAL_DP_RESET_FLAG_DEASSERT))
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_AUX_CTRL, SW_AUX_RESET, 1);
        out_dword(uOffset + HWIO_DPTX_0_AUX_CTRL_ADDR, uRegVal);
      }

      if (0 == (uResetFlag & HAL_DP_RESET_FLAG_ASSERT))
      {
        /*Clear Reset*/
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_AUX_CTRL, SW_AUX_RESET, 0);
        out_dword(uOffset + HWIO_DPTX_0_AUX_CTRL_ADDR, uRegVal);
      }
    }

    if (uModule & HAL_DP_MODULE_TYPE_PHY)
    {
      if (0 == (uResetFlag & HAL_DP_RESET_FLAG_DEASSERT))
      {
        /*Toggle Reset to DP PHY */
        uRegVal = HWIO_OUT_FLD(0, DPTX_0_PHY_CTRL, SW_RESET, 1);
        out_dword(uOffset + HWIO_DPTX_0_PHY_CTRL_ADDR, uRegVal);
      }

      if (0 == (uResetFlag & HAL_DP_RESET_FLAG_ASSERT))
      {
        /*Clear Reset */
        out_dword(uOffset + HWIO_DPTX_0_PHY_CTRL_ADDR, 0);
      }
    }
  }

  return HAL_MDSS_STATUS_SUCCESS;
}

/****************************************************************************

FUNCTION: HAL_DP_Interrupt_Enable()

   Enables interrupts

Parameters:
   eControllerId              -[in] DP core ID
   eInterruptSrc              -[in] DP interrupt mask to clear
   uEnableFlags               -[in] Reserved

Return: 
   HAL_MDSS_ErrorType

****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Interrupt_Enable(DP_ControllerIDType      eControllerId,
                                           HAL_DP_InterruptType     eInterruptSrc,
                                           uint32                   uEnableFlags)
{
  if (HAL_DP_ValidateControllerID(eControllerId))
  {
    uintPtr uOffset = HAL_DP_GetRegBaseOffset(eControllerId);
    uint32  uRegVal = 0;

    /*******************************************************************************************/
    /*DP_INTERRUPT_STATUS */
    uRegVal = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_ADDR);

    if (eInterruptSrc & HAL_DP_INTR_TYPE_DPPHY_AUX_ERROR)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, DPPHY_AUX_ERROR_MASK, 1);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_PLL_UNLOCK_DET)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, PLL_UNLOCK_DET_MASK, 1);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_AUX_NACK_DURING_I2C)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, AUX_NACK_DURING_I2C_MASK, 1);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_WRONG_READDATA_COUNT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, WRONG_READDATA_COUNT_MASK, 1);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, CONSECUTIVE_NACK_DEFER_MASK, 1);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_CONSECUTIVE_TIMEOUT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, CONSECUTIVE_TIMEOUT_MASK, 1);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_WRONG_ADDRESS)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, WRONG_ADDRESS_MASK, 1);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_AUX_I2C_DONE)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, AUX_I2C_DONE_MASK, 1);
    }

    out_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_ADDR, uRegVal);

    /*******************************************************************************************/
    /*DP_INTERRUPT_STATUS_2 */
    uRegVal = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_2_ADDR);

    if (eInterruptSrc & HAL_DP_INTR_TYPE_SST_FIFO_UNDERFLOW)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, SST_FIFO_UNDERFLOW_MASK, 1);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_CRC_UPDATED)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, CRC_UPDATED_MASK, 1);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_FRAME_END)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, FRAME_END_MASK, 1);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_IDLE_PATTERNS_SENT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, IDLE_PATTERNS_SENT_MASK, 1);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_READY_FOR_VIDEO)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, READY_FOR_VIDEO_MASK, 1);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_ENCRYPTION_READY)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, ENCRYPTION_READY_MASK, 1);
    }

    if (eInterruptSrc & HAL_DP_INTR_TYPE_ENCRYPTION_NOT_READY)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, ENCRYPTION_NOT_READY_MASK, 1);
    }

    if (eInterruptSrc & HAL_DP_INTR_TYPE_AUTH_SUCCESS)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, HDCP_AUTH_SUCCESS_MASK, 1);
    }

    if (eInterruptSrc & HAL_DP_INTR_TYPE_AUTH_FAIL)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, HDCP_AUTH_FAIL_MASK, 1);
    }

    out_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_2_ADDR, uRegVal);

    /*******************************************************************************************/
    /*DP_INTERRUPT_STATUS_3 */
    uRegVal = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_3_ADDR);

    if (eInterruptSrc & HAL_DP_INTR_TYPE_FRAME_END_STREAM1)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_3, DP1_FRAME_END_MASK, 1);
    }

    out_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_3_ADDR, uRegVal);

    /*******************************************************************************************/
    /*DP_DP_HPD_INT_MASK */
    uRegVal = in_dword(uOffset + HWIO_DPTX_0_DP_HPD_INT_MASK_ADDR);

    if (eInterruptSrc & HAL_DP_INTR_TYPE_HPD_PLUG_INT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_HPD_INT_MASK, DP_HPD_PLUG_INT_MASK, 1);
    }

    if (eInterruptSrc & HAL_DP_INTR_TYPE_HPD_IRQ_INT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_HPD_INT_MASK, DP_IRQ_HPD_INT_MASK, 1);
    }

    if (eInterruptSrc & HAL_DP_INTR_TYPE_HPD_REPLUG_INT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_HPD_INT_MASK, DP_HPD_REPLUG_INT_MASK, 1);
    }

    if (eInterruptSrc & HAL_DP_INTR_TYPE_HPD_UNPLUG_INT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_HPD_INT_MASK, DP_HPD_UNPLUG_INT_MASK, 1);
    }

    out_dword(uOffset + HWIO_DPTX_0_DP_HPD_INT_MASK_ADDR, uRegVal);
  }

  return HAL_MDSS_STATUS_SUCCESS;
}


/****************************************************************************

FUNCTION: HAL_DP_Interrupt_Disable()

   Enables interrupts

Parameters:
   eControllerId              -[in] DP core ID
   eInterruptSrc              -[in] DP interrupt mask to disable
   uEnableFlags               -[in] Reserved

Return: 
   HAL_MDSS_ErrorType

****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Interrupt_Disable(DP_ControllerIDType      eControllerId,
                                            HAL_DP_InterruptType     eInterruptSrc,
                                            uint32                   uEnableFlags)
{
  if (HAL_DP_ValidateControllerID(eControllerId))
  {
    uintPtr uOffset = HAL_DP_GetRegBaseOffset(eControllerId);
    uint32  uRegVal = 0;

    /*******************************************************************************************/
    /*DP_INTERRUPT_STATUS */
    uRegVal = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_ADDR);

    if (eInterruptSrc & HAL_DP_INTR_TYPE_DPPHY_AUX_ERROR)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, DPPHY_AUX_ERROR_MASK, 0);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_PLL_UNLOCK_DET)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, PLL_UNLOCK_DET_MASK, 0);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_AUX_NACK_DURING_I2C)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, AUX_NACK_DURING_I2C_MASK, 0);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_WRONG_READDATA_COUNT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, WRONG_READDATA_COUNT_MASK, 0);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, CONSECUTIVE_NACK_DEFER_MASK, 0);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_CONSECUTIVE_TIMEOUT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, CONSECUTIVE_TIMEOUT_MASK, 0);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_WRONG_ADDRESS)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, WRONG_ADDRESS_MASK, 0);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_AUX_I2C_DONE)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, AUX_I2C_DONE_MASK, 0);
    }

    out_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_ADDR, uRegVal);

    /*******************************************************************************************/
    /*DP_INTERRUPT_STATUS_2 */
    uRegVal = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_2_ADDR);

    if (eInterruptSrc & HAL_DP_INTR_TYPE_SST_FIFO_UNDERFLOW)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal , DPTX_0_INTERRUPT_STATUS_2, SST_FIFO_UNDERFLOW_MASK, 0);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_CRC_UPDATED)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal , DPTX_0_INTERRUPT_STATUS_2, CRC_UPDATED_MASK, 0);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_FRAME_END)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal , DPTX_0_INTERRUPT_STATUS_2, FRAME_END_MASK, 0);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_IDLE_PATTERNS_SENT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal , DPTX_0_INTERRUPT_STATUS_2, IDLE_PATTERNS_SENT_MASK, 0);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_READY_FOR_VIDEO)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal , DPTX_0_INTERRUPT_STATUS_2, READY_FOR_VIDEO_MASK, 0);
    }
    if (eInterruptSrc & HAL_DP_INTR_TYPE_ENCRYPTION_READY)
    {
      uRegVal  = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, ENCRYPTION_READY_MASK, 0);
    }

    if (eInterruptSrc & HAL_DP_INTR_TYPE_ENCRYPTION_NOT_READY)
    {
      uRegVal  = HWIO_OUT_FLD(uRegVal , DPTX_0_INTERRUPT_STATUS_2, ENCRYPTION_NOT_READY_MASK, 0);
    }

    if (eInterruptSrc & HAL_DP_INTR_TYPE_AUTH_SUCCESS)
    {
      uRegVal  = HWIO_OUT_FLD(uRegVal , DPTX_0_INTERRUPT_STATUS_2, HDCP_AUTH_SUCCESS_MASK, 0);
    }

    if (eInterruptSrc & HAL_DP_INTR_TYPE_AUTH_FAIL)
    {
      uRegVal  = HWIO_OUT_FLD(uRegVal , DPTX_0_INTERRUPT_STATUS_2, HDCP_AUTH_FAIL_MASK, 0);
    }

    out_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_2_ADDR, uRegVal);

    /*******************************************************************************************/
    /*DP_INTERRUPT_STATUS_3 */
    uRegVal = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_3_ADDR);
  
    if (eInterruptSrc & HAL_DP_INTR_TYPE_FRAME_END_STREAM1)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal , DPTX_0_INTERRUPT_STATUS_3, DP1_FRAME_END_MASK, 0);
    }

    out_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_3_ADDR, uRegVal);
  
    /*******************************************************************************************/
    /*DP_DP_HPD_INT_MASK */
    uRegVal = in_dword(uOffset + HWIO_DPTX_0_DP_HPD_INT_MASK_ADDR);

    if (eInterruptSrc & HAL_DP_INTR_TYPE_HPD_PLUG_INT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_HPD_INT_MASK, DP_HPD_PLUG_INT_MASK, 0);
    }

    if (eInterruptSrc & HAL_DP_INTR_TYPE_HPD_IRQ_INT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_HPD_INT_MASK, DP_IRQ_HPD_INT_MASK, 0);
    }

    if (eInterruptSrc & HAL_DP_INTR_TYPE_HPD_REPLUG_INT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_HPD_INT_MASK, DP_HPD_REPLUG_INT_MASK, 0);
    }

    if (eInterruptSrc & HAL_DP_INTR_TYPE_HPD_UNPLUG_INT)
    {
      uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_HPD_INT_MASK, DP_HPD_UNPLUG_INT_MASK, 0);
    }

    out_dword(uOffset + HWIO_DPTX_0_DP_HPD_INT_MASK_ADDR, uRegVal);
  }

  return HAL_MDSS_STATUS_SUCCESS;
}


/****************************************************************************

FUNCTION: HAL_DP_Interrupt_Clear()

   Clears or Acknowledges the interrupts

Parameters:
   eControllerId              -[in] DP core ID
   eInterruptSrc              -[in] DP interrupt mask to clear
   uClearFlags                -[in] Reserved

Return: 
   HAL_MDSS_ErrorType

****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Interrupt_Clear(DP_ControllerIDType      eControllerId,
                                          HAL_DP_InterruptType     eInterruptSrc,
                                          uint32                   uClearFlags)
{
  if (HAL_DP_ValidateControllerID(eControllerId))
  {
    uintPtr uOffset = HAL_DP_GetRegBaseOffset(eControllerId);

    /*******************************************************************************************/
    /*DP_INTERRUPT_STATUS */
    uint32  uIntrStatusList = (HAL_DP_INTR_TYPE_DPPHY_AUX_ERROR |
      HAL_DP_INTR_TYPE_PLL_UNLOCK_DET |
      HAL_DP_INTR_TYPE_AUX_NACK_DURING_I2C |
      HAL_DP_INTR_TYPE_WRONG_READDATA_COUNT |
      HAL_DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER |
      HAL_DP_INTR_TYPE_CONSECUTIVE_TIMEOUT |
      HAL_DP_INTR_TYPE_WRONG_ADDRESS |
      HAL_DP_INTR_TYPE_AUX_I2C_DONE);

    if (eInterruptSrc & uIntrStatusList)
    {
      /* DP_INTERRUPT_STATUS contains fields for _INT, _MASK and _ACK
         read the register to preserve the _MASK bits
      */
      uint32 uRegVal = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_ADDR);

      if (eInterruptSrc & HAL_DP_INTR_TYPE_DPPHY_AUX_ERROR)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, DPPHY_AUX_ERROR_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_PLL_UNLOCK_DET)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, PLL_UNLOCK_DET_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_AUX_NACK_DURING_I2C)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, AUX_NACK_DURING_I2C_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_WRONG_READDATA_COUNT)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, WRONG_READDATA_COUNT_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, CONSECUTIVE_NACK_DEFER_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_CONSECUTIVE_TIMEOUT)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, CONSECUTIVE_TIMEOUT_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_WRONG_ADDRESS)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, WRONG_ADDRESS_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_AUX_I2C_DONE)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS, AUX_I2C_DONE_ACK, 1);
      }

      out_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_ADDR, uRegVal);
    }

    /*******************************************************************************************/
    /* DP_INTERRUPT_STATUS_2 */
    uIntrStatusList = (HAL_DP_INTR_TYPE_SST_FIFO_UNDERFLOW |
      HAL_DP_INTR_TYPE_CRC_UPDATED |
      HAL_DP_INTR_TYPE_FRAME_END |
      HAL_DP_INTR_TYPE_IDLE_PATTERNS_SENT |
      HAL_DP_INTR_TYPE_READY_FOR_VIDEO |
      HAL_DP_INTR_TYPE_ENCRYPTION_READY |
      HAL_DP_INTR_TYPE_ENCRYPTION_NOT_READY |
      HAL_DP_INTR_TYPE_AUTH_SUCCESS |
      HAL_DP_INTR_TYPE_AUTH_FAIL);

    if (eInterruptSrc & uIntrStatusList)
    {
      /* DP_INTERRUPT_STATUS_2 contains fields for _INT, _MASK and _ACK
         read the register to preserve the _MASK bits
      */
      uint32 uRegVal = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_2_ADDR);

      if (eInterruptSrc & HAL_DP_INTR_TYPE_SST_FIFO_UNDERFLOW)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, SST_FIFO_UNDERFLOW_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_CRC_UPDATED)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, CRC_UPDATED_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_FRAME_END)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, FRAME_END_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_IDLE_PATTERNS_SENT)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, IDLE_PATTERNS_SENT_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_READY_FOR_VIDEO)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, READY_FOR_VIDEO_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_ENCRYPTION_READY)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, ENCRYPTION_READY_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_ENCRYPTION_NOT_READY)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, ENCRYPTION_NOT_READY_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_AUTH_SUCCESS)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, HDCP_AUTH_SUCCESS_ACK, 1);
      }
      if (eInterruptSrc & HAL_DP_INTR_TYPE_AUTH_FAIL)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_2, HDCP_AUTH_FAIL_ACK, 1);
      }

      out_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_2_ADDR, uRegVal);
    }

    /*******************************************************************************************/
    /*DP_INTERRUPT_STATUS_3 */
    uIntrStatusList = (HAL_DP_INTR_TYPE_FRAME_END_STREAM1);

    if (eInterruptSrc & uIntrStatusList)
    {
      /* DP_INTERRUPT_STATUS_3 contains fields for _INT, _MASK and _ACK
         read the register to preserve the _MASK bits
      */
      uint32 uRegVal = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_3_ADDR);

      if (eInterruptSrc & HAL_DP_INTR_TYPE_FRAME_END_STREAM1)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_INTERRUPT_STATUS_3, DP1_FRAME_END_ACK, 1);
      }

      out_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_3_ADDR, uRegVal);
    }

    /*******************************************************************************************/
    /* DP_DP_HPD_INT_ACK */
    uIntrStatusList = (HAL_DP_INTR_TYPE_HPD_PLUG_INT |
      HAL_DP_INTR_TYPE_HPD_IRQ_INT |
      HAL_DP_INTR_TYPE_HPD_REPLUG_INT |
      HAL_DP_INTR_TYPE_HPD_UNPLUG_INT);

    if (eInterruptSrc & uIntrStatusList)
    {
      uint32 uRegVal = 0;

      if (eInterruptSrc & HAL_DP_INTR_TYPE_HPD_PLUG_INT)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_HPD_INT_ACK, DP_HPD_PLUG_INT_ACK, 1);
      }

      if (eInterruptSrc & HAL_DP_INTR_TYPE_HPD_IRQ_INT)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_HPD_INT_ACK, DP_IRQ_HPD_INT_ACK, 1);
      }

      if (eInterruptSrc & HAL_DP_INTR_TYPE_HPD_REPLUG_INT)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_HPD_INT_ACK, DP_HPD_REPLUG_INT_ACK, 1);
      }

      if (eInterruptSrc & HAL_DP_INTR_TYPE_HPD_UNPLUG_INT)
      {
        uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_HPD_INT_ACK, DP_HPD_UNPLUG_INT_ACK, 1);
      }

      out_dword(uOffset + HWIO_DPTX_0_DP_HPD_INT_ACK_ADDR, uRegVal);
    }
  }

  return HAL_MDSS_STATUS_SUCCESS;
}

/****************************************************************************

FUNCTION: HAL_DP_Interrupt_GetStatus()
 
   Returns the interrupts status

Parameters:
   eControllerId              -[in]     DP core ID
   peIntrStatus               -[in/out] Status for each module.
   uGetStatusFlags            -[in]     Reserved

Return: 
   HAL_MDSS_ErrorType

****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Interrupt_GetStatus(DP_ControllerIDType       eControllerId,
                                              HAL_DP_InterruptType     *peIntrStatus,
                                              uint32                    uGetStatusFlags)
{
  if (HAL_DP_ValidateControllerID(eControllerId))
  {
    uintPtr uOffset = HAL_DP_GetRegBaseOffset(eControllerId);
    uint32  uIntReg1 = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_ADDR);
    uint32  uIntReg2 = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_2_ADDR);
    uint32  uIntReg3 = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_3_ADDR);
    uint32  uHalInterrupt = 0;

    if (uIntReg1 & HWIO_DPTX_0_INTERRUPT_STATUS_AUX_I2C_DONE_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_AUX_I2C_DONE;
    }
    if (uIntReg1 & HWIO_DPTX_0_INTERRUPT_STATUS_WRONG_ADDRESS_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_WRONG_ADDRESS;
    }
    if (uIntReg1 & HWIO_DPTX_0_INTERRUPT_STATUS_CONSECUTIVE_TIMEOUT_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_CONSECUTIVE_TIMEOUT;
    }
    if (uIntReg1 & HWIO_DPTX_0_INTERRUPT_STATUS_CONSECUTIVE_NACK_DEFER_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER;
    }
    if (uIntReg1 & HWIO_DPTX_0_INTERRUPT_STATUS_WRONG_READDATA_COUNT_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_WRONG_READDATA_COUNT;
    }
    if (uIntReg1 & HWIO_DPTX_0_INTERRUPT_STATUS_AUX_NACK_DURING_I2C_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_AUX_NACK_DURING_I2C;
    }
    if (uIntReg1 & HWIO_DPTX_0_INTERRUPT_STATUS_PLL_UNLOCK_DET_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_PLL_UNLOCK_DET;
    }
    if (uIntReg1 & HWIO_DPTX_0_INTERRUPT_STATUS_DPPHY_AUX_ERROR_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_DPPHY_AUX_ERROR;
    }

    if (uIntReg2 & HWIO_DPTX_0_INTERRUPT_STATUS_2_READY_FOR_VIDEO_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_READY_FOR_VIDEO;
    }
    if (uIntReg2 & HWIO_DPTX_0_INTERRUPT_STATUS_2_IDLE_PATTERNS_SENT_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_IDLE_PATTERNS_SENT;
    }
    if (uIntReg2 & HWIO_DPTX_0_INTERRUPT_STATUS_2_FRAME_END_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_FRAME_END;
    }
    if (uIntReg2 & HWIO_DPTX_0_INTERRUPT_STATUS_2_CRC_UPDATED_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_CRC_UPDATED;
    }
    if (uIntReg2 & HWIO_DPTX_0_INTERRUPT_STATUS_2_SST_FIFO_UNDERFLOW_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_SST_FIFO_UNDERFLOW;
    }

    if (uIntReg3 & HWIO_DPTX_0_INTERRUPT_STATUS_3_DP1_FRAME_END_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_FRAME_END_STREAM1;
    }

    // HDCP interrupts
    if (uIntReg2 & HWIO_DPTX_0_INTERRUPT_STATUS_2_ENCRYPTION_READY_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_ENCRYPTION_READY;
    }

    if (uIntReg2 & HWIO_DPTX_0_INTERRUPT_STATUS_2_ENCRYPTION_NOT_READY_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_ENCRYPTION_NOT_READY;
    }

    if (uIntReg2 & HWIO_DPTX_0_INTERRUPT_STATUS_2_HDCP_AUTH_SUCCESS_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_AUTH_SUCCESS;
    }

    if (uIntReg2 & HWIO_DPTX_0_INTERRUPT_STATUS_2_HDCP_AUTH_FAIL_INT_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_AUTH_FAIL;
    }

    /*******************************************************************************************/
    /*DP_DP_HPD_INT_STATUS */
    uIntReg1 = in_dword(uOffset + HWIO_DPTX_0_DP_HPD_INT_STATUS_ADDR);

    if (uIntReg1 & HWIO_DPTX_0_DP_HPD_INT_STATUS_DP_HPD_PLUG_INT_STATUS_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_HPD_PLUG_INT;
    }

    if (uIntReg1 & HWIO_DPTX_0_DP_HPD_INT_STATUS_DP_IRQ_HPD_INT_STATUS_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_HPD_IRQ_INT;
    }

    if (uIntReg1 & HWIO_DPTX_0_DP_HPD_INT_STATUS_DP_HPD_REPLUG_INT_STATUS_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_HPD_REPLUG_INT;
    }

    if (uIntReg1 & HWIO_DPTX_0_DP_HPD_INT_STATUS_DP_HPD_UNPLUG_INT_STATUS_BMSK)
    {
      uHalInterrupt |= HAL_DP_INTR_TYPE_HPD_UNPLUG_INT;
    }

    *peIntrStatus = (HAL_DP_InterruptType)uHalInterrupt;
  }

  return HAL_MDSS_STATUS_SUCCESS;
}

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
                                    uint32                uVideoPattern)
{
  HAL_MDSS_ErrorType  eStatus      = HAL_MDSS_STATUS_SUCCESS;
  uintPtr             uPclkOffset  = HAL_DP_GetPixelClkRegBaseOffset(eControllerId, psMainStream->uStreamId);

  if (HAL_DP_TESTPATTERN_NONE == uVideoPattern)
  {
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_BIST_ENABLE_ADDR,       0);
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_TIMING_ENGINE_EN_ADDR,  0);
  }
  else
  {
    uint32 hBlank      = psMainStream->uHsyncBackPorchInPixels + psMainStream->uHsyncPulseInPixels + psMainStream->uHsyncFrontPorchInPixels;
    uint32 vBlank      = psMainStream->uVsyncBackPorchInLines  + psMainStream->uVsyncPulseInLines  + psMainStream->uVsyncFrontPorchInLines;
    uint32 vSyncPeriod = (psMainStream->uVisibleWidthInPixels + hBlank) * (psMainStream->uVisibleHeightInPixels + vBlank); //in number of pixels
    uint32 uRegVal     = 0;

    //program BIST scan type
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_INTF_CONFIG_ADDR, 0);

    //program BIST hsync period and hsync width
    uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_HSYNC_CTL, PULSE_WIDTH, psMainStream->uHsyncPulseInPixels);
    uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_HSYNC_CTL, HSYNC_PERIOD, psMainStream->uVisibleWidthInPixels + hBlank);
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_HSYNC_CTL_ADDR, uRegVal);

    //program BIST vsync period and and vsync width
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_VSYNC_PERIOD_F0_ADDR, vSyncPeriod); //in number of pixels
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_VSYNC_PULSE_WIDTH_F0_ADDR, ((psMainStream->uVisibleWidthInPixels + hBlank) * psMainStream->uVsyncPulseInLines)); //in number of pixels

    //hsync position
    uRegVal = 0;
    uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_DISPLAY_HCTL, DISPLAY_START_X, psMainStream->uHsyncBackPorchInPixels + psMainStream->uHsyncPulseInPixels);
    uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_DISPLAY_HCTL, DISPLAY_END_X,   psMainStream->uVisibleWidthInPixels + psMainStream->uHsyncBackPorchInPixels + psMainStream->uHsyncPulseInPixels - 1);
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_DISPLAY_HCTL_ADDR, uRegVal);

    //vsync position
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_DISPLAY_V_START_F0_ADDR, ((psMainStream->uVsyncBackPorchInLines + psMainStream->uVsyncPulseInLines) *
                                                                (psMainStream->uVisibleWidthInPixels + hBlank) +
                                                                psMainStream->uHsyncBackPorchInPixels +  psMainStream->uHsyncPulseInPixels));
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_DISPLAY_V_END_F0_ADDR, ((psMainStream->uVsyncBackPorchInLines + psMainStream->uVsyncPulseInLines + psMainStream->uVisibleHeightInPixels) *
                                                              (psMainStream->uVisibleWidthInPixels + hBlank) - 1 - psMainStream->uHsyncFrontPorchInPixels));

    //NZ doesn't support interlace mode
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_VSYNC_PERIOD_F1_ADDR,       0);
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_VSYNC_PULSE_WIDTH_F1_ADDR,  0);
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_DISPLAY_V_START_F1_ADDR,    0);
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_DISPLAY_V_END_F1_ADDR,      0);
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_ACTIVE_V_START_F1_ADDR,     0);
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_ACTIVE_V_END_F1_ADDR,       0);

    uRegVal = 0;
    switch (uVideoPattern)
    {
    case   HAL_DP_TESTPATTERN_COUNTER_PATTERN:             uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_TPG_MAIN_CONTROL, COUNTER_PATTERN,             1); break;
    case   HAL_DP_TESTPATTERN_FIXED_PATTERN:               uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_TPG_MAIN_CONTROL, FIXED_PATTERN,               1); break;
    case   HAL_DP_TESTPATTERN_COLOR_RAMP_64L_64P:          uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_TPG_MAIN_CONTROL, COLOR_RAMP_64L_64P,          1); break;
    case   HAL_DP_TESTPATTERN_COLOR_RAMP_64L_256P:         uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_TPG_MAIN_CONTROL, COLOR_RAMP_64L_256P,         1); break;
    case   HAL_DP_TESTPATTERN_BLACK_WHITE_VERTICAL_LINES:  uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_TPG_MAIN_CONTROL, BLACK_WHITE_VERTICAL_LINES,  1); break;
    case   HAL_DP_TESTPATTERN_GRAYSCALE_RAMP:              uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_TPG_MAIN_CONTROL, GRAYSCALE_RAMP,              1); break;
    case   HAL_DP_TESTPATTERN_COLOR_SQUARE:                uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_TPG_MAIN_CONTROL, COLOR_SQUARE,                1); break;
    case   HAL_DP_TESTPATTERN_CHECKERED_RECTANGLE_PATTERN: uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_TPG_MAIN_CONTROL, CHECKERED_RECTANGLE_PATTERN, 1); break;
    case   HAL_DP_TESTPATTERN_BASIC_COLOR_CHANGING_PATTERN:uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_TPG_MAIN_CONTROL, BASIC_COLOR_CHANGING_PATTERN,1); break;
    }
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_TPG_MAIN_CONTROL_ADDR, uRegVal);

    // Setup Format and Color
    uRegVal = 0;
    uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_TPG_VIDEO_CONFIG, BPP, 1);
    uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_P0CLK_TPG_VIDEO_CONFIG, RGB, 1);
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_TPG_VIDEO_CONFIG_ADDR, uRegVal);
  
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_BIST_ENABLE_ADDR,      1);
    out_dword(uPclkOffset + HWIO_DPTX_0_P0CLK_TIMING_ENGINE_EN_ADDR, 1);
  }


  return eStatus;
}

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
                            HAL_HW_VersionType *psDPVersionInfo)
{
  uintPtr uOffset      = HAL_DP_GetRegBaseOffset(eControllerId);
  uint32  uVersionInfo = in_dword(uOffset + HWIO_DPTX_0_HW_VERSION_ADDR);

  if (NULL != psDPVersionInfo)
  {
    psDPVersionInfo->uMajorVersion    = HWIO_GETVAL(DPTX_0_HW_VERSION, uVersionInfo, MAJOR);
    psDPVersionInfo->uMinorVersion    = HWIO_GETVAL(DPTX_0_HW_VERSION, uVersionInfo, MINOR);
    psDPVersionInfo->uReleaseVersion  = HWIO_GETVAL(DPTX_0_HW_VERSION, uVersionInfo, STEP);
  }
}

/****************************************************************************
*
** FUNCTION: HAL_DP_CrossbarConfig()
*/
/*!
* \brief
*     Returns the version information
*
* \param [in] eControllerId  - DP core ID
* \param [in] ePhyId         - DP PHY ID
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_CrossbarConfig(DP_ControllerIDType eControllerId, DP_DeviceIDType ePhyId)
{
  HAL_MDSS_ErrorType eStatus     = HAL_MDSS_STATUS_SUCCESS;
  uint32             uCtrlShift  = 0;
  uint32             uCtrlMask   = 0;
  uint32             uPhyShift   = 0;
  uint32             uPhyMask    = 0;
  uint32             uPrevValue  = HWIO_MDP_DP_PHY_INTF_SELECT_IN;
  uint32             uPrevPhy    = 0;
  uint32             uPrevCtrl   = 0;
  uint32             uCurCtrl    = 0;
  uint32             uCurPhy     = 0;
  uint32             uCurValue   = uPrevValue;

  out_dword(HWIO_MDP_HDMI_DP_CORE_SELECT_ADDR, 0x01);   /* DP Mode */

  switch (eControllerId)
  {
  case DP_CONTROLLER_ID_DP_0:
    uCtrlShift  = HWIO_MDP_DP_PHY_INTF_SELECT_DP_CTRL_INTF_0_SEL_SHFT;
    uCtrlMask   = HWIO_MDP_DP_PHY_INTF_SELECT_DP_CTRL_INTF_0_SEL_BMSK;
    uCurCtrl    = 1;
    break;
  case DP_CONTROLLER_ID_DP_1:
    uCtrlShift  = HWIO_MDP_DP_PHY_INTF_SELECT_DP_CTRL_INTF_1_SEL_SHFT;
    uCtrlMask   = HWIO_MDP_DP_PHY_INTF_SELECT_DP_CTRL_INTF_1_SEL_BMSK;
    uCurCtrl    = 2;
    break;
  default:
    break;
  }

  switch (ePhyId)
  {
  case DP_DEVICE_ID_ALT_MODE_0:
    uPhyShift = HWIO_MDP_DP_PHY_INTF_SELECT_DP_PHY_INTF_0_SEL_SHFT;
    uPhyMask  = HWIO_MDP_DP_PHY_INTF_SELECT_DP_PHY_INTF_0_SEL_BMSK;
    uCurPhy   = 1;
    break;
  case DP_DEVICE_ID_ALT_MODE_1:
    uPhyShift = HWIO_MDP_DP_PHY_INTF_SELECT_DP_PHY_INTF_1_SEL_SHFT;
    uPhyMask  = HWIO_MDP_DP_PHY_INTF_SELECT_DP_PHY_INTF_1_SEL_BMSK;
    uCurPhy   = 2;
    break;
  case DP_DEVICE_ID_ALT_MODE_2:
    uPhyShift = HWIO_MDP_DP_PHY_INTF_SELECT_DP_PHY_INTF_2_SEL_SHFT;
    uPhyMask  = HWIO_MDP_DP_PHY_INTF_SELECT_DP_PHY_INTF_2_SEL_BMSK;
    uCurPhy   = 3; 
    break;
  default:
    break;
  }

  /*
   * If controller & phy are both non-zero then update both fields accordingly
   * If phy is zero, then it's a call to disconnect. Read hw to find which PHY was connected to the controller and
   * clear both those fields.
   */

  if (0 < uCurCtrl)
  {
    // get current value
    uPrevPhy = (uPrevValue & uCtrlMask) >> uCtrlShift;

    // check if different
    if (uCurPhy != uPrevPhy)
    {
      // clear current value
      uCurValue &= ~uCtrlMask;

      // Set new phy
      uCurValue |= (uCurPhy << uCtrlShift);

      if (0 == uCurPhy)
      {
        // Disconnect - Clear previous PHY
        uCurPhy  = uPrevPhy;
        uCurCtrl = 0;
      }
    }

    if (0 < uCurPhy)
    {
      // Get current value
      uPrevCtrl = (uPrevValue & uPhyMask) >> uPhyShift;
      
      // Check if different
      if (uCurCtrl != uPrevCtrl)
      {
        // Clear current value
        uCurValue &= ~uPhyMask;
      
        // Set new Ctrl
        uCurValue |= (uCurCtrl << uPhyShift);
      }
    }
    
    // Program the new value, only if it is different
    if (uCurValue != uPrevValue)
    {
      HWIO_MDP_DP_PHY_INTF_SELECT_OUT(uCurValue);
    }
  }

  return eStatus;
}

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
                           DP_ClockStatusType  *puClockStatus)
{
  uintPtr uOffset         = HAL_DP_GetRegBaseOffset(eControllerId);
  uint32  uClockStatusReg = in_dword(uOffset + HWIO_DPTX_0_CLK_ACTIVE_ADDR);

  *puClockStatus = 0;
  
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_MAIN_LINK_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_MAIN_LINK_CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_IF_LINK_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_IF_LINK_CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_HDCP1P3_LINK_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_HDCP1P3_LINK_CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_HDCP2P2_LINK_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_HDCP2P2_LINK_CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_SDP_LINK_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_SDP_LINK_CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_AUDIO_LINK_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_AUDIO_LINK_CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_P0CLK23_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_P0CLK23_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_P0CLK1_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_P0CLK1_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_P0CLK0_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_P0CLK0_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_P0CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_P0CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_TPG_P0CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_TPG_P0CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_AUX_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_AUX_CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_HDCP_SCLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_HDCP_SCLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_HDCP1P3_SCLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_HDCP1P3_SCLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_CRYPTO_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_CRYPTO_CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_TPG_P1CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_TPG_P1CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_MST_P0CLK0_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_MST_P0CLK0_CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_MST_P1CLK_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_MST_P1CLK_CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_MST_P1CLK0_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_MST_P1CLK0_CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_BIST_MISR40_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_BIST_MISR40_CLK_ACTIVE;
  }
  if (uClockStatusReg & HWIO_DPTX_0_CLK_ACTIVE_MISR_CLK_ACTIVE_BMSK)
  {
    *puClockStatus |= DP_CLOCKSTATUS_MISR_CLK_ACTIVE;
  }

  return;
}

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
* \retval - none
*
****************************************************************************/
void HAL_DP_MSTVCConfig(DP_ControllerIDType         eControllerId,
                        HAL_DP_MSTVCAllocationType *pVCAllocation)
{
  uintPtr uOffset        = HAL_DP_GetRegBaseOffset(eControllerId);
  uint32  uDP0Slot1To32  = 0;
  uint32  uDP0Slot33To63 = 0;
  uint32  uDP1Slot1To32  = 0;
  uint32  uDP1Slot33To63 = 0;
  uint32  uCount         = 0;
  uint32  uSize          = 0;

  if (pVCAllocation->uStream0StartSlot > 0)
  {
    uCount = pVCAllocation->uStream0StartSlot - 1;
    uSize  = uCount + pVCAllocation->uStream0SlotCount;

    for (; (uCount < uSize) && (uCount < HAL_DP_MST_HALF_SLOT_COUNT); uCount++)
    {
      uDP0Slot1To32  |= (1 << uCount);
    }

    for (; (uCount < uSize) && (uCount < HAL_DP_MST_FULL_SLOT_COUNT); uCount++)
    {
      uDP0Slot33To63 |= (1 << uCount);
    }
  }

  if (pVCAllocation->uStream1StartSlot > 0)
  {
    uCount = pVCAllocation->uStream1StartSlot - 1;
    uSize  = uCount + pVCAllocation->uStream1SlotCount;

    for (; (uCount < uSize) && (uCount < HAL_DP_MST_HALF_SLOT_COUNT); uCount++)
    {
      uDP1Slot1To32  |= (1 << uCount);
    }

    for (; (uCount < uSize) && (uCount < HAL_DP_MST_FULL_SLOT_COUNT); uCount++)
    {
      uDP1Slot33To63 |= (1 << uCount);
    }
  }  

  out_dword(uOffset + HWIO_DPTX_0_DP0_TIMESLOT_1_32_ADDR,  uDP0Slot1To32);
  out_dword(uOffset + HWIO_DPTX_0_DP0_TIMESLOT_33_63_ADDR, uDP0Slot33To63);
  out_dword(uOffset + HWIO_DPTX_0_DP1_TIMESLOT_1_32_ADDR,  uDP1Slot1To32);
  out_dword(uOffset + HWIO_DPTX_0_DP1_TIMESLOT_33_63_ADDR, uDP1Slot33To63);

}


/* c * a ^ 1 */
static uint8 Calculate_G0(uint8 uData)
{
  uint8 uG0   = 0;
  uint8 c[4];
  uint8 g[4];
  uint8 i;

  /* Convert to single bit array for multiply */
  for (i = 0; i < 4; i++)
  {
    c[i] = (uData >> i) & 0x01;
  }

  g[0] = c[3];
  g[1] = c[0] ^ c[3];
  g[2] = c[1];
  g[3] = c[2];

  for (i = 0; i < 4; i++)
  {
    uG0 = ((g[i] & 0x01) << i) | uG0;
  }

  return(uG0);
}

/* c * a ^ 4 */
static uint8 Calculate_G1(uint8 uData)
{
  uint8 uG1   = 0;
  uint8 c[4];
  uint8 g[4];
  uint8 i;

  /* Convert to single bit array for multiply */
  for (i = 0; i < 4; i++)
  {
    c[i] = (uData >> i) & 0x01;
  }

  g[0] = c[0] ^ c[3];
  g[1] = c[0] ^ c[1] ^ c[3];
  g[2] = c[1] ^ c[2];
  g[3] = c[2] ^ c[3];

  for (i = 0; i < 4; i++)
  {
    uG1 = ((g[i] & 0x01) << i) | uG1;
  }

  return(uG1);
}

/****************************************************************************
*
** FUNCTION: HAL_DP_SDP_CalulateECC()
*/
/*!
* \brief
*     Calculate ECC for SDP packet.
*
* \param [in]  pData     - Pointer to data word
* \param [in]  uNumByte  - Number of valid bytes in the data word
*
* \retval - ECC value
*
****************************************************************************/
uint8 HAL_DP_SDP_CalculateECC(uint32 * pData, uint8 uNumByte)
{
  uint8 x0            = 0;
  uint8 x1            = 0;
  uint8 ci            = 0;
  uint8 uData         = 0;
  uint8 i             = 0;
  uint8 uNumNibbles   = uNumByte * 2;

  for (i = 0; i < uNumNibbles; i++)
  {
    uData = (*pData >> i * 4) & 0xF;

    ci = uData ^ x1;
    x1 = x0 ^ Calculate_G1(ci);
    x0 = Calculate_G0(ci);
  }

  return x1 | (x0 << 4);
}


/****************************************************************************
*
** FUNCTION: HAL_DP_SDP_Flush()
*/
/*!
* \brief
*     Triggers an asynchronous SDP flush.
*
* \param [in]  eControllerId - DP Core ID
* \param [in]  eStreamId     - Stream ID
*
* \retval - none
*
****************************************************************************/
void HAL_DP_SDP_Flush(DP_ControllerIDType eControllerId, DP_StreamIDType eStreamId)
{
  uintPtr   uOffset     = HAL_DP_GetRegBaseOffset(eControllerId);
  uintPtr   uSDPRegAddr = HWIO_DPTX_0_SDP_CFG3_ADDR;
  uint32    uRegVal     = 0;

  if (DP_STREAM_ID_MST1 == eStreamId)
  {
    uSDPRegAddr    = HWIO_DPTX_0_DP1_SDP_CFG3_ADDR;
  }

  // Toggle SDP
  uRegVal = in_dword(uOffset + uSDPRegAddr);
  uRegVal = HWIO_OUT_FLD(0, DPTX_0_SDP_CFG3, UPDATE_SDP, 1);
  out_dword(uOffset + HWIO_DPTX_0_SDP_CFG3_ADDR, uRegVal);
  uRegVal = HWIO_OUT_FLD(0, DPTX_0_SDP_CFG3, UPDATE_SDP, 0);
  out_dword(uOffset + uSDPRegAddr, uRegVal);
}

/****************************************************************************
*
** FUNCTION: HAL_DP_CRC_Capture()
*/
/*!
* \brief
*     Captures CRC values
*
* \param [in]      eControllerId  - DP core ID
* \param [in/out]  pCRC_R         - CRC value for the red component
* \param [in/out]  pCRC_G         - CRC value for the blue component
* \param [in/out]  pCRC_B         - CRC value for the green component
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_CRC_Capture(DP_ControllerIDType eControllerId, uint16 *pCRC_R, uint16 *pCRC_G, uint16 *pCRC_B)
{
  HAL_MDSS_ErrorType eStatus = HAL_MDSS_STATUS_SUCCESS;
  uint32             uRegVal = 0;
  uintPtr            uOffset = HAL_DP_GetRegBaseOffset(eControllerId);
  
  uRegVal      = in_dword(uOffset + HWIO_DPTX_0_PSR_CRC_RG_ADDR);
  if (NULL != pCRC_R)
  {
    *pCRC_R = HWIO_GETVAL(DPTX_0_PSR_CRC_RG, uRegVal, CRC_R);
  }
  if (NULL != pCRC_G)
  {
    *pCRC_G = HWIO_GETVAL(DPTX_0_PSR_CRC_RG, uRegVal, CRC_G);
  }

  uRegVal      = in_dword(uOffset + HWIO_DPTX_0_PSR_CRC_B_ADDR);
  if (NULL != pCRC_B)
  {
    *pCRC_B = HWIO_GETVAL(DPTX_0_PSR_CRC_B, uRegVal, CRC_B);
  }
  
  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_DP_Enable_DoubleBuffer()
*/
/*!
 \brief
*     Enable double buffering for DP registers
*
* \param [in]      eControllerId  - DP core ID
* \param [in]      bEnable        - TRUE to enable
*
****************************************************************************/
void HAL_DP_Enable_DoubleBuffer(DP_ControllerIDType eControllerId, bool32 bEnable)
{
  uintPtr  uOffset = HAL_DP_GetRegBaseOffset(eControllerId);

  out_dword(uOffset + HWIO_DPTX_0_DB_CTRL_ADDR, (bEnable ? 1 : 0));
}

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
void HAL_DP_Enable_MISR(DP_ControllerIDType eControllerId, bool32 bEnable)
{
  uintPtr  uOffset = HAL_DP_GetRegBaseOffset(eControllerId);

  out_dword(uOffset + HWIO_DPTX_0_MISR_CTRL_ADDR, (bEnable ? 1 : 0));
}

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
HAL_MDSS_ErrorType HAL_DP_Get_Frame_CRC(DP_ControllerIDType eControllerId, uint64 *pCRC)
{
  HAL_MDSS_ErrorType eStatus = HAL_MDSS_STATUS_SUCCESS;
  uintPtr            uOffset = HAL_DP_GetRegBaseOffset(eControllerId);
  uint32             uMISR_Ctrl;
  uint32             uCRC_RG = 0;
  uint32             uCRC_B  = 0;
  uint32             uIntr2;
  uint32             uCnt;
  uint32             uTiming_Eng;

  /*
   * Enable MISR to have FRAME_END generated
   * MISR_FRAME_COUNT determines how many frames to calculate
   * CRC over MISR. This alos means how many FRAME_END will be
   * generated. Since MISR is not exactly enabled at blanking period,
   * most likely the first FRAME_END does not have CRC ready (read as 0).
   * It is sure CRC will be populated at 2nd FRAME_END.
   * Therefore MISR_FRAME_COUNT is set to 2.
   */
  uMISR_Ctrl = in_dword(uOffset + HWIO_DPTX_0_MISR_CTRL_ADDR);
  uMISR_Ctrl = HWIO_OUT_FLD(uMISR_Ctrl, DPTX_0_MISR_CTRL, MISR_ENABLE, 1);
  uMISR_Ctrl = HWIO_OUT_FLD(uMISR_Ctrl, DPTX_0_MISR_CTRL, MISR_FRAME_COUNT, 2);
  uMISR_Ctrl = HWIO_OUT_FLD(uMISR_Ctrl, DPTX_0_MISR_CTRL, MISR_ACTIVE_ONLY, 1);
  out_dword(uOffset + HWIO_DPTX_0_MISR_CTRL_ADDR, uMISR_Ctrl);

  /* start CRC timing engine */
  uTiming_Eng = in_dword(uOffset + HWIO_DPTX_0_P0CLK_TIMING_ENGINE_EN_ADDR);
  uTiming_Eng = HWIO_OUT_FLD(uTiming_Eng, DPTX_0_P0CLK_TIMING_ENGINE_EN, FRAME_CRC_EN, 1);
  out_dword(uOffset + HWIO_DPTX_0_P0CLK_TIMING_ENGINE_EN_ADDR, uTiming_Eng);

  /*
   * Wait for frame_end interrupt 
   * The waiting time is varient since frame time is varient too and 
   * depend on FPS.
   * Frame time is 40ms for 25 FPS frame which mean 80ms waiting time
   * is required since CRC is ready at 2nd FRAME_END.
   * Therefore 100 ms waiting period here is enough to cover it.
   * NOTE: this polling loop will break once CRC captured.
   */ 
  uCnt = HAL_DP_WAIT_FOR_CRC;
  while(uCnt)
  {
     DP_OSAL_SleepMs(1);

     uIntr2 = in_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_2_ADDR);
     if (uIntr2 & HWIO_DPTX_0_INTERRUPT_STATUS_2_FRAME_END_INT_BMSK)
     {
        /* read CRC */
        uCRC_RG    = in_dword(uOffset + HWIO_DPTX_0_PSR_CRC_RG_ADDR);
        uCRC_B     = in_dword(uOffset + HWIO_DPTX_0_PSR_CRC_B_ADDR);

        /* ack to clear frame_end bit */
        uIntr2 = (HWIO_DPTX_0_INTERRUPT_STATUS_2_FRAME_END_ACK_BMSK | HWIO_DPTX_0_INTERRUPT_STATUS_2_CRC_UPDATED_ACK_BMSK);
        out_dword(uOffset + HWIO_DPTX_0_INTERRUPT_STATUS_2_ADDR, uIntr2); 

        if (uCRC_RG != 0)
        {
           uint64 crc = uCRC_RG;
      
           crc <<= 32;
           crc |= (uint64) uCRC_B;
           *pCRC = crc;
           break;
         }
     } 
     uCnt--;
  }

  /* disable MISR */
  uMISR_Ctrl = in_dword(uOffset + HWIO_DPTX_0_MISR_CTRL_ADDR);
  uMISR_Ctrl = HWIO_OUT_FLD(uMISR_Ctrl, DPTX_0_MISR_CTRL, MISR_ENABLE, 0);
  out_dword(uOffset + HWIO_DPTX_0_MISR_CTRL_ADDR, uMISR_Ctrl);

  /* disable CRC and timing engine */
  uTiming_Eng = in_dword(uOffset + HWIO_DPTX_0_P0CLK_TIMING_ENGINE_EN_ADDR);
  uTiming_Eng = HWIO_OUT_FLD(uTiming_Eng, DPTX_0_P0CLK_TIMING_ENGINE_EN, FRAME_CRC_EN, 0);
  out_dword(uOffset + HWIO_DPTX_0_P0CLK_TIMING_ENGINE_EN_ADDR, uTiming_Eng);

  if (uCnt == 0)
  {
    *pCRC = 0;
    eStatus = HAL_MDSS_MDP_STATUS_FAILED;
  }

  return eStatus;
}

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
                                                         bool32              bTunnelingMode)
{
  HAL_MDSS_ErrorType eStatus = HAL_MDSS_STATUS_SUCCESS;
  uintPtr            uOffset = HAL_DP_GetRegBaseOffset(eControllerId);
  uint32             uRegVal = in_dword(uOffset + HWIO_DPTX_0_LINK_INTF_CLK_CTRL_ADDR);
    
  if (bTunnelingMode)
  {
    uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_LINK_INTF_CLK_CTRL, PHY_LINK_INTF_CLK_ON, 0);
  }
  else
  {
    uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_LINK_INTF_CLK_CTRL, PHY_LINK_INTF_CLK_ON, 1);
  }

  out_dword(uOffset + HWIO_DPTX_0_LINK_INTF_CLK_CTRL_ADDR, uRegVal);

  return eStatus;
}

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
                                                     bool32              bTunnelingMode)
{
  HAL_MDSS_ErrorType eStatus = HAL_MDSS_STATUS_SUCCESS;
  uintPtr            uOffset = HAL_DP_GetRegBaseOffset(eControllerId);
  uint32             uRegVal = in_dword(uOffset + HWIO_DPTX_0_DP_USB4_CTRL_ADDR);
    
  if (bTunnelingMode)
  {
    uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_USB4_CTRL, DP_USB4_MODE_ENABLE, 1);
  }
  else
  {
    uRegVal = HWIO_OUT_FLD(uRegVal, DPTX_0_DP_USB4_CTRL, DP_USB4_MODE_ENABLE, 0);
  }

  out_dword(uOffset + HWIO_DPTX_0_DP_USB4_CTRL_ADDR, uRegVal);

  return eStatus;
}

#ifdef __cplusplus
}
#endif

