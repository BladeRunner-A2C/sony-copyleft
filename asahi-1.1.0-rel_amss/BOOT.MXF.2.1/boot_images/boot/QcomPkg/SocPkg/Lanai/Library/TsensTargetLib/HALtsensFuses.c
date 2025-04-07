/*============================================================================
  FILE:         HALtsensFuses.c

  OVERVIEW:     Implementation of the TSENS HAL for reading fuses

  DEPENDENCIES: None

                Copyright (c) 2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary.
============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "HALhwio.h"
#include "HALhwioTsensFuses.h"
#include "HALtsens.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Char data
 * -------------------------------------------------------------------------*/

/* ============================================================================
**
**  HAL_tsens_UseRedundant
**
**  Description:
**    Whether or not to use the redundant region
**
**  Parameters:
**    None
**
**  Return: TRUE: use redundant char data
**
**  Dependencies: None
**
** ========================================================================= */
boolean HAL_tsens_UseRedundant(void)
{
   return FALSE;
}

/* ============================================================================
**
**  HAL_tsens_CalSelect
**
**  Description:
**    Determines whether there is 1) no cal data 2) single point cal data or
**    3) two point cal data
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**
**  Return: HAL_tsens_Calibration (not calibrated, one point, or two point)
**
**  Dependencies: None
**
** ========================================================================= */
HAL_tsens_Calibration HAL_tsens_CalSelect(boolean bUseRedundant)
{
   /* TSENS_CAL_SEL
    * 0: not calibrated
    * 1: slope & offset truncated 3 bits (1 offset bit == 8 codes)
    * 2: offset
    * 3: slope & offset
    * 4: slope & offset (SW compatible with method 3)
    * 5: new method (treated as uncalibrated until defined)
    * 6: slope & offset truncated 1 bit (1 offset bit == 2 codes)
    * 7: new method (treated as uncalibrated until defined)
    */
   if (!bUseRedundant)
   {
      switch (HWIO_INF(QFPROM_CORR_CALIBRATION_ROW29_MSB, TSENS_CAL_SEL))
      {
         case 1:
            return HAL_TSENS_CAL_SLOPE_OFFSET_TRUNCATED_3;
         case 2:
            return HAL_TSENS_CAL_OFFSET;
         case 3:
            return HAL_TSENS_CAL_OFFSET_SLOPE;
         case 4:
            return HAL_TSENS_CAL_OFFSET_SLOPE;
         case 6:
            return HAL_TSENS_CAL_SLOPE_OFFSET_TRUNCATED_1;
         default:
            return HAL_TSENS_CAL_NOT_CALIBRATED;
      }
   }

   return HAL_TSENS_CAL_NOT_CALIBRATED;
}

/* ============================================================================
**
**  HAL_tsens_PartialGoodsEnabled
**
**  Description:
**    Determines whether or not partial goods encoding has been enabled
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**
**  Return: TRUE / FALSE
**
**  Dependencies: None
**
** ========================================================================= */
boolean HAL_tsens_PartialGoodsEnabled(boolean bUseRedundant)
{
   return FALSE;
}

/* ============================================================================
**
**  HAL_tsens_GetBase1
**
**  Description:
**    Gets the Tsens base for cal point 1
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**    uController - which controller
**
**  Return: adc code
**
**  Dependencies: None
**
** ========================================================================= */
uint32 HAL_tsens_GetBase1(boolean bUseRedundant, uint32 uController)
{
   if (!bUseRedundant)
   {
      switch (uController)
      {
         case 0:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW25_LSB, TSENS_C0_BASE0);
         case 1:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW25_LSB, TSENS_C1_BASE0_0) | (HWIO_INF(QFPROM_CORR_CALIBRATION_ROW25_MSB, TSENS_C1_BASE0_9_1) << 1);
         case 2:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW25_MSB, TSENS_C2_BASE0);
         default:
            break;
      }
   }

   return 0;
}

/* ============================================================================
**
**  HAL_tsens_GetBase2
**
**  Description:
**    Gets the Tsens base for cal point 2
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**    uController - which controller
**
**  Return: adc code
**
**  Dependencies: None
**
** ========================================================================= */
uint32 HAL_tsens_GetBase2(boolean bUseRedundant, uint32 uController)
{
   if (!bUseRedundant)
   {
      switch (uController)
      {
         case 0:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW25_LSB, TSENS_C0_BASE1);
         case 1:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW25_MSB, TSENS_C1_BASE1);
         case 2:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW25_MSB, TSENS_C2_BASE1_2_0) | (HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_LSB, TSENS_C2_BASE1_9_3) << 3);
         default:
            break;
      }
   }

   return 0;
}

/* ============================================================================
**
**  HAL_tsens_GetOffset
**
**  Description:
**    Gets Tsens uSensor offset for cal point 1
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**    uint32 uFuseIdx
**
**  Return: offset from base
**
**  Dependencies: None
**
** ========================================================================= */
uint32 HAL_tsens_GetOffset(boolean bUseRedundant, uint32 uFuseIdx)
{
   if (!bUseRedundant)
   {
      switch (uFuseIdx)
      {
         case 0:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_LSB, TSENS0_C0_OFFSET);
         case 1:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_LSB, TSENS1_C0_OFFSET);
         case 2:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_LSB, TSENS2_C0_OFFSET);
         case 3:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_LSB, TSENS3_C0_OFFSET);
         case 4:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_LSB, TSENS4_C0_OFFSET);
         case 5:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_MSB, TSENS5_C0_OFFSET);
         case 6:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_MSB, TSENS6_C0_OFFSET);
         case 7:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_MSB, TSENS7_C0_OFFSET);
         case 8:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_MSB, TSENS8_C0_OFFSET);
         case 9:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_MSB, TSENS9_C0_OFFSET);
         case 10:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_MSB, TSENS10_C0_OFFSET);
         case 11:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW26_MSB, TSENS11_C0_OFFSET_1_0) | (HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_LSB, TSENS11_C0_OFFSET_4_2) << 2);
         case 12:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_LSB, TSENS12_C0_OFFSET);
         case 13:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_LSB, TSENS13_C0_OFFSET);
         case 14:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_LSB, TSENS14_C0_OFFSET);
         case 15:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_LSB, TSENS15_C1_OFFSET);
         case 16:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_LSB, TSENS16_C1_OFFSET);
         case 17:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_LSB, TSENS17_C1_OFFSET_3_0) | (HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_MSB, TSENS17_C1_OFFSET_4) << 4);
         case 18:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_MSB, TSENS18_C1_OFFSET);
         case 19:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_MSB, TSENS19_C1_OFFSET);
         case 20:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_MSB, TSENS20_C1_OFFSET);
         case 21:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_MSB, TSENS21_C1_OFFSET);
         case 22:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_MSB, TSENS22_C1_OFFSET);
         case 23:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_MSB, TSENS23_C1_OFFSET);
         case 24:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW27_MSB, TSENS24_C1_OFFSET_0) | (HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_LSB, TSENS24_C1_OFFSET_4_1) << 1);
         case 25:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_LSB, TSENS25_C1_OFFSET);
         case 26:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_LSB, TSENS26_C1_OFFSET);
         case 27:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_LSB, TSENS27_C1_OFFSET);
         case 28:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_LSB, TSENS28_C1_OFFSET);
         case 29:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_LSB, TSENS29_C1_OFFSET);
         case 30:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_LSB, TSENS30_C1_OFFSET_2_0) | (HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_MSB, TSENS30_C1_OFFSET_4_3) << 3);
         case 31:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_MSB, TSENS31_C2_OFFSET);
         case 32:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_MSB, TSENS32_C2_OFFSET);
         case 33:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_MSB, TSENS33_C2_OFFSET);
         case 34:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_MSB, TSENS34_C2_OFFSET);
         case 35:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_MSB, TSENS35_C2_OFFSET);
         case 36:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW28_MSB, TSENS36_C2_OFFSET);
         case 37:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW29_LSB, TSENS37_C2_OFFSET);
         case 38:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW29_LSB, TSENS38_C2_OFFSET);
         case 39:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW29_LSB, TSENS39_C2_OFFSET);
         case 40:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW29_LSB, TSENS40_C2_OFFSET);
         case 41:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW29_LSB, TSENS41_C2_OFFSET);
         case 42:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW29_LSB, TSENS42_C2_OFFSET);
         case 43:
            return HWIO_INF(QFPROM_CORR_CALIBRATION_ROW29_LSB, TSENS43_C2_OFFSET_1_0) | (HWIO_INF(QFPROM_CORR_CALIBRATION_ROW29_MSB, TSENS43_C2_OFFSET_4_2) << 2);
         default:
            break;
      }
   }

   return 0;
}

