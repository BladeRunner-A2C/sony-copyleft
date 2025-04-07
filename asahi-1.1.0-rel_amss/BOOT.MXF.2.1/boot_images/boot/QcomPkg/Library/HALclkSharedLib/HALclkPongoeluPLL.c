/*
==============================================================================

FILE:         HALclkPongoeluPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Pongoelu PLL control.
  These PLLs are of the Pongoelu PLL variety.

==============================================================================

                             Edit History

$Header:

when       who     what, where, why
--------   ---     -----------------------------------------------------------
04/17/23   saurku      Created

==============================================================================
    Copyright (c) 2023 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "HALhwio.h"
#include "HALclkGenericPLL.h"
#include "HALclkPongoeluPLL.h"
#include "HALclkInternal.h"

/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Definitions
** ==========================================================================*/


/*
 * HAL_CLK_PLL_MODE_*
 *
 * Definitions for configuring the PLLn_MODE register.
 */
#define HAL_CLK_PLL_MODE_ACTIVE  \
  (HWIO_FMSK(PLL_MODE, PLL_LOCK_DET)  | \
   HWIO_FMSK(PLL_MODE, PLL_RESET_N))
   
/*
 * HAL_CLK_LOCK_TIMEOUT_US
 *
 * Timeout in usec for PLL_LOCK_DET to get set.
 * For Pongoelu, this is 50us worst-case lock time.  However, when
 * the PLL is sourced from RO, it may take longer for initial lock, 
 * up to 1.5 ms.
 */
#define HAL_CLK_LOCK_TIMEOUT_US 1500

/* ============================================================================
**    Functions Prototypes
** ==========================================================================*/

static boolean HAL_clk_PongoeluPLLEnable           ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceDisableModeType eMode, void *pData );
static void    HAL_clk_PongoeluPLLDisable          ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceDisableModeType eMode, void *pData );
static boolean HAL_clk_PongoeluPLLIsEnabled        ( HAL_clk_SourceDescType *pSource );
static void    HAL_clk_PongoeluPLLConfig           ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceConfigType eConfig );
static boolean HAL_clk_PongoeluPLLConfigPLL        ( HAL_clk_SourceDescType *pSource, const HAL_clk_PLLConfigType *pmConfig, HAL_clk_SourceConfigMode eMode );
static void    HAL_clk_PongoeluPLLDetectPLLConfig  ( HAL_clk_SourceDescType *pSource, HAL_clk_PLLConfigType *pmConfig );
static boolean HAL_clk_PongoeluPLLIsPLLConfigEqual ( const HAL_clk_PLLConfigType *pConfigA, const HAL_clk_PLLConfigType *pConfigB );
static boolean HAL_clk_PongoeluPLLIsCalibrated     ( HAL_clk_SourceDescType *pSource );
static boolean HAL_clk_PongoeluPLLSetCalConfig     ( HAL_clk_SourceDescType *pSource, const HAL_clk_PLLConfigType *pmConfig );
static void    HAL_clk_PongoeluPLLSetRegSettings   ( HAL_clk_SourceDescType *pSource, const HAL_clk_SourceRegSettingsType *pmSettings );

/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clk_PongoeluPLLControl
 *
 * Control function array for the Pongoelu PLLs.
 */
HAL_clk_SourceControlType HAL_clk_PongoeluPLLControl =
{
  .Enable           = HAL_clk_PongoeluPLLEnable,
  .Disable          = HAL_clk_PongoeluPLLDisable,
  .IsEnabled        = HAL_clk_PongoeluPLLIsEnabled,
  .Config           = HAL_clk_PongoeluPLLConfig,
  .ConfigPLL        = HAL_clk_PongoeluPLLConfigPLL,
  .DetectPLLConfig  = HAL_clk_PongoeluPLLDetectPLLConfig,
  .IsPLLConfigEqual = HAL_clk_PongoeluPLLIsPLLConfigEqual,
  .IsCalibrated     = HAL_clk_PongoeluPLLIsCalibrated,
  .SetCalConfig     = HAL_clk_PongoeluPLLSetCalConfig,
  .SetRegSettings   = HAL_clk_PongoeluPLLSetRegSettings,

};


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_PongoeluPLLPostDivToHW
**
** ======================================================================== */

static uint32_t HAL_clk_PongoeluPLLPostDivToHW (uint32_t nDivider)
{
  switch (nDivider)
  {
    case 0:
    case 1:   return 0; /* Divide-by-1 */
    case 2:   return 1; /* Divide-by-2 */
    case 4:   return 3; /* Divide-by-4 */
    case 8:   return 2; /* Divide-by-8 */
    default:
      return 0;
  }

} /* END HAL_clk_PongoeluPLLPostDivToHW */


/* ===========================================================================
**  HAL_clk_PongoeluPLLPostDivFromHW
**
** ======================================================================== */

static uint32_t HAL_clk_PongoeluPLLPostDivFromHW (uint32_t nDivider)
{
  switch (nDivider)
  {
    case 0:   return 1; /* Divide-by-1 */
    case 1:   return 2; /* Divide-by-2 */
    case 2:   return 8; /* Divide-by-8 */
    case 3:   return 4; /* Divide-by-4 */
    default:
      return 1;
   }
} /* END HAL_clk_PongoeluPLLPostDivFromHW */



/* ===========================================================================
**  HAL_clk_PongoeluPLLEnable
**
** ======================================================================== */

static boolean HAL_clk_PongoeluPLLEnable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  boolean     bResult;

  /*
   * Check if PLL is already enabled and return
   */
  if (HAL_clk_PongoeluPLLIsEnabled(pSource))
  {
    return TRUE;
  }

  /*
   * Set the PLL opmode to run mode.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pSource, HAL_PLL_OPMODE_RUN);
  
  /*
   * Take PLL out of reset, which will switch to configured OPMODE.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_RESET_N, 1);

  /*
   * Wait for the PLL to lock within the timeout period.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
      HWIO_FMSK(PLL_MODE, PLL_LOCK_DET),
      HAL_CLK_LOCK_TIMEOUT_US);

  /*
   * Return immediately if the lock detect failed.
   */
  if (!bResult)
  {
    return FALSE;
  }
  
  /*
   * Enable the PLL outputs.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_OUTCTRL, 1);

  return TRUE;

} /* END HAL_clk_PongoeluPLLEnable */


/* ===========================================================================
**  HAL_clk_PongoeluPLLDisable
**
** ======================================================================== */

static void HAL_clk_PongoeluPLLDisable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  /*
   * Disable the PLL outputs.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_OUTCTRL, 0);

  /*
   * Wait 2 ticks of the output main clock.
   */
  HAL_clk_BusyWait(1);
  
  /*
   * Disable the PLL.
   */
  if (eMode == HAL_CLK_SOURCE_DISABLE_MODE_STANDBY)
  {
    HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pSource, HAL_PLL_OPMODE_STANDBY);
  }
  else
  {
    HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pSource, HAL_PLL_OPMODE_STANDBY);
    HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_RESET_N, 0);
  }

} /* END HAL_clk_PongoeluPLLDisable */


/* ===========================================================================
**  HAL_clk_PongoeluPLLIsEnabled
**
** ======================================================================== */

static boolean HAL_clk_PongoeluPLLIsEnabled
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32_t nModeVal;

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pSource);

  /*
   * Check whether the PLL is enabled.
   */
  return ((nModeVal & HAL_CLK_PLL_MODE_ACTIVE) == HAL_CLK_PLL_MODE_ACTIVE);

} /* END HAL_clk_PongoeluPLLIsEnabled */


/* ===========================================================================
**  HAL_clk_PongoeluPLLConfig
**
** ======================================================================== */

static void HAL_clk_PongoeluPLLConfig
(
  HAL_clk_SourceDescType   *pSource,
  HAL_clk_SourceConfigType  eConfig
)
{
  /*
   * Take action.
   */
  switch (eConfig)
  {
    case HAL_CLK_CONFIG_PLL_TEST_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_TEST_EN, 0);
      break;

    case HAL_CLK_CONFIG_PLL_TEST_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_TEST_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_EVEN_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_EVEN_EN, 0);
      break;

    case HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_MAIN_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_MAIN_EN, 0);
      break;

    default:
      break;
  }

} /* END HAL_clk_PongoeluPLLConfig */


/* ===========================================================================
**  HAL_clk_PongoeluPLLConfigPLLNormal
**
** ======================================================================== */

static boolean HAL_clk_PongoeluPLLConfigPLLNormal
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  uint32_t nUserVal;
  boolean     bPLLEnabled = FALSE;


  /*
   * Check PLL mode.
   */
  bPLLEnabled = HAL_clk_PongoeluPLLIsEnabled(pSource);

  /*
   * Disable the PLL.
   */
  if (bPLLEnabled)
  {
    HAL_clk_PongoeluPLLDisable(pSource, HAL_CLK_SOURCE_DISABLE_MODE_NORMAL, NULL);
  }

  /* Automatically switch between XO bypass and internally generated clock */
  HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL_U, pSource, XO_CLK_AT_OUT, 0x1);

  /*
   * Program L values.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pSource, pConfig->nL);
  
  /*
   * Turn off the output.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_OUTCTRL, 0);

  
  /*
   * XO must be made available
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_CAL_XO_PRESENT, 0x1);

  
  while ( HAL_CLK_PLL_HWIO_INF(PLL_MODE, pSource, PLL_IN_CALIBRATION) != 0 );
 
  /*
   * Get the CONFIG value and clear out fields we will configure.
   */
  nUserVal  =  HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pSource);
  nUserVal &= ~HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO_MAIN);
  nUserVal &= ~HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO_EVEN);

  /*
   * Program the post-div value.
   */
  nUserVal |= HWIO_FVAL(PLL_USER_CTL, POST_DIV_RATIO_MAIN,
    HAL_clk_PongoeluPLLPostDivToHW(pConfig->PostDivs.Pongoelu.nMain));

  nUserVal |= HWIO_FVAL(PLL_USER_CTL, POST_DIV_RATIO_EVEN,
    HAL_clk_PongoeluPLLPostDivToHW(pConfig->PostDivs.Pongoelu.nEven));

  /*
   * Enable MAIN_OUT_ENA bit.
   */
  nUserVal |= HWIO_FMSK(PLL_USER_CTL, PLLOUT_MAIN_EN);

  /*
   * Finally program the USER_CTL register.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL, pSource, nUserVal);


  /*
   * Enable the PLL if it was on before.
   */
  if (bPLLEnabled)
  {
    HAL_clk_PongoeluPLLEnable(pSource, HAL_CLK_SOURCE_DISABLE_MODE_NORMAL, NULL);
  }

  return TRUE;

} /* END HAL_clk_PongoeluPLLConfigPLLNormal */


/* ===========================================================================
**  HAL_clk_PongoeluPLLConfigPLLSlew
**
**  Returns:
**    boolean - TRUE if successfully configured.
**              FALSE if unable to detect that the PLL successfully locked.
** ======================================================================== */

static boolean HAL_clk_PongoeluPLLConfigPLLSlew
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  /*
   * No slewing ability.
   */
  return FALSE;

} /* END HAL_clk_PongoeluPLLConfigPLLSlew */


/* ===========================================================================
**  HAL_clk_PongoeluPLLConfigPLL
**
** ======================================================================== */

static boolean HAL_clk_PongoeluPLLConfigPLL
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig,
  HAL_clk_SourceConfigMode     eMode
)
{
  boolean bResult = FALSE;

  switch (eMode)
  {
    case HAL_CLK_SOURCE_CONFIG_MODE_NORMAL:
      bResult = HAL_clk_PongoeluPLLConfigPLLNormal(pSource, pConfig);
      break;
    case HAL_CLK_SOURCE_CONFIG_MODE_SLEW:
      bResult = HAL_clk_PongoeluPLLConfigPLLSlew(pSource, pConfig);
      break;
    default:
      bResult = FALSE;
      break;
  }

  return bResult;

} /* END HAL_clk_PongoeluPLLConfigPLL */


/* ===========================================================================
**  HAL_clk_PongoeluPLLDetectPLLConfig
**
** ======================================================================== */

static void HAL_clk_PongoeluPLLDetectPLLConfig
(
  HAL_clk_SourceDescType *pSource,
  HAL_clk_PLLConfigType  *pConfig
)
{
  uint32_t nConfigVal;
  uint32_t nPostDiv;

  /*
   * Clear all config values not modified in this function.
   * PLL Does not Support Fractional/Alpha Mode.
   */
  pConfig->nMode = 0;
  pConfig->nFracVal = 0;
  pConfig->eFracMode = HAL_CLK_PLL_FRAC_MODE_UNKNOWN;

  /*
   * Read current L-Val
   */
  pConfig->nL = HAL_CLK_PLL_HWIO_IN(PLL_L_VAL, pSource);

  /*
   * Determine the oscillator source.
   */
  pConfig->nSource = 0;

  nConfigVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pSource);

  /*
   * No pre-divider.
   */
  pConfig->nPreDiv = 0;

  /*
   * Main divider.
   */
  nPostDiv  = ((nConfigVal & HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO_MAIN))
                          >> HWIO_SHFT(PLL_USER_CTL, POST_DIV_RATIO_MAIN));
  nPostDiv = HAL_clk_PongoeluPLLPostDivFromHW(nPostDiv);
  pConfig->PostDivs.Pongoelu.nMain = nPostDiv;

  /*
   * Even divider.
   */
  nPostDiv  = ((nConfigVal & HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO_EVEN))
                          >> HWIO_SHFT(PLL_USER_CTL, POST_DIV_RATIO_EVEN));
  nPostDiv = HAL_clk_PongoeluPLLPostDivFromHW(nPostDiv);
  pConfig->PostDivs.Pongoelu.nEven = nPostDiv;

} /* END HAL_clk_PongoeluPLLDetectPLLConfig */


/* ===========================================================================
**  HAL_clk_PongoeluPLLIsPLLConfigEqual
**
** ======================================================================== */

static boolean HAL_clk_PongoeluPLLIsPLLConfigEqual
(
  const HAL_clk_PLLConfigType  *pConfigA,
  const HAL_clk_PLLConfigType  *pConfigB
)
{
  uint32_t nMainDivA, nMainDivB;
  uint32_t nEvenDivA, nEvenDivB;

  if (HAL_clk_GenericIsPLLConfigEqual(pConfigA, pConfigB))
  {
    /* Treat div-0 and div-1 as the same thing. */
    nMainDivA = MAX(1, pConfigA->PostDivs.Pongoelu.nMain);
    nMainDivB = MAX(1, pConfigB->PostDivs.Pongoelu.nMain);
    nEvenDivA = MAX(1, pConfigA->PostDivs.Pongoelu.nEven);
    nEvenDivB = MAX(1, pConfigB->PostDivs.Pongoelu.nEven);

    if (nMainDivA == nMainDivB && nEvenDivA == nEvenDivB)
    {
      return TRUE;
    }
  }

  return FALSE;

} /* END HAL_clk_PongoeluPLLIsPLLConfigEqual */


/* ===========================================================================
**  HAL_clk_PongoeluPLLIsCalibrated
**
** ======================================================================== */

static boolean HAL_clk_PongoeluPLLIsCalibrated
(
  HAL_clk_SourceDescType *pSource
)
{
  /* No calibration supported */
  
  return TRUE;

} /* HAL_clk_PongoeluPLLIsCalibrated */


/* ===========================================================================
**  HAL_clk_PongoeluPLLSetCalConfig
**
** ======================================================================== */

static boolean HAL_clk_PongoeluPLLSetCalConfig
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  /* No calibration supported */
  return TRUE;

} /* HAL_clk_PongoeluPLLSetCalConfig */


/* ===========================================================================
**  HAL_clk_PongoeluPLLSetRegSettings
**
** ======================================================================== */

static void HAL_clk_PongoeluPLLSetRegSettings
(
  HAL_clk_SourceDescType              *pSource,
  const HAL_clk_SourceRegSettingsType *pmSettings
)
{
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL,    pSource, pmSettings->nConfigCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL_U,  pSource, pmSettings->nConfigCtl1);
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL_U1, pSource, pmSettings->nConfigCtl2);
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL_U2, pSource, pmSettings->nConfigCtl3);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL,      pSource, pmSettings->nTestCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_U,    pSource, pmSettings->nTestCtl1);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_U1,   pSource, pmSettings->nTestCtl2);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_U2,   pSource, pmSettings->nTestCtl3);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_U3,   pSource, pmSettings->nTestCtl4);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL,      pSource, pmSettings->nUserCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U,    pSource, pmSettings->nUserCtl1);

} /* END HAL_clk_PongoeluPLLSetRegSettings */




