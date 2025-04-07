/*
==============================================================================

FILE:         HALclkRivianeluPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Rivian Elu PLL control.
  These PLLs are of the Rivian Elu PLL variety.

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
#include "HALclkRivianeluPLL.h"
#include "HALclkInternal.h"


/* ============================================================================
**    Definitions
** ==========================================================================*/

/*
 * HAL_CLK_PLL_MODE_ACTIVE
 */
#define HAL_CLK_PLL_MODE_ACTIVE  \
  (HWIO_FMSK(PLL_MODE, PLL_LOCK_DET)  | \
   HWIO_FMSK(PLL_MODE, PLL_RESET_N))

/*
 * HAL_CLK_LOCK_TIMEOUT_US
 *
 * Timeout in US for PLL_LOCK_DET to get set.
 */
#define HAL_CLK_LOCK_TIMEOUT_US 50

/*
 * CLOCK_WAIT_FOR_PLL_LOCK
 *
 * Flag for whether to wait for the PLL to lock or not.
 */
#define CLOCK_WAIT_FOR_PLL_LOCK TRUE

/* ============================================================================
**    Functions Prototypes
** ==========================================================================*/

static boolean HAL_clkRivianeluPLLEnable           ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceDisableModeType eMode, void *pData );
static void    HAL_clkRivianeluPLLDisable          ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceDisableModeType eMode, void *pData );
static boolean HAL_clkRivianeluPLLIsEnabled        ( HAL_clk_SourceDescType *pSource );
static void    HAL_clkRivianeluPLLConfig           ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceConfigType eConfig );
static boolean HAL_clkRivianeluPLLConfigPLL        ( HAL_clk_SourceDescType *pSource, const HAL_clk_PLLConfigType *pmConfig, HAL_clk_SourceConfigMode eMode );
static void    HAL_clkRivianeluPLLDetectPLLConfig  ( HAL_clk_SourceDescType *pSource, HAL_clk_PLLConfigType *pmConfig );
static boolean HAL_clkRivianeluPLLEnableVote       ( HAL_clk_SourceDescType *pSource );
static void    HAL_clkRivianeluPLLDisableVote      ( HAL_clk_SourceDescType *pSource );
static boolean HAL_clkRivianeluPLLIsVoteEnabled    ( HAL_clk_SourceDescType *pSource );
static boolean HAL_clkRivianeluPLLIsPLLConfigEqual ( const HAL_clk_PLLConfigType *pConfigA, const HAL_clk_PLLConfigType *pConfigB );
static boolean HAL_clkRivianeluPLLIsCalibrated     ( HAL_clk_SourceDescType *pSource );
static boolean HAL_clkRivianeluPLLSetCalConfig     ( HAL_clk_SourceDescType *pSource, const HAL_clk_PLLConfigType *pmConfig );
static void    HAL_clkRivianeluPLLSetRegSettings   ( HAL_clk_SourceDescType *pSource, const HAL_clk_SourceRegSettingsType *pmSettings );

/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clkRivianeluPLLControl
 *
 * Control function array for the Rivian ole PLLs.
 */
HAL_clk_SourceControlType HAL_clkRivianeluPLLControl =
{
  .Enable           = HAL_clkRivianeluPLLEnable,
  .Disable          = HAL_clkRivianeluPLLDisable,
  .IsEnabled        = HAL_clkRivianeluPLLIsEnabled,
  .Config           = HAL_clkRivianeluPLLConfig,
  .ConfigPLL        = HAL_clkRivianeluPLLConfigPLL,
  .DetectPLLConfig  = HAL_clkRivianeluPLLDetectPLLConfig,
  .EnableVote       = HAL_clkRivianeluPLLEnableVote,
  .DisableVote      = HAL_clkRivianeluPLLDisableVote,
  .IsVoteEnabled    = HAL_clkRivianeluPLLIsVoteEnabled,
  .IsPLLConfigEqual = HAL_clkRivianeluPLLIsPLLConfigEqual,
  .IsCalibrated     = HAL_clkRivianeluPLLIsCalibrated,
  .SetCalConfig     = HAL_clkRivianeluPLLSetCalConfig,
  .SetRegSettings   = HAL_clkRivianeluPLLSetRegSettings,
};

/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

/* ===========================================================================
**  HAL_clkRivianeluPLLEnableVote
**
** ======================================================================== */

static boolean HAL_clkRivianeluPLLEnableVote
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32_t nVal;
  boolean  bResult = TRUE;

  if ( pSource->VoterRegister.nAddr != 0 )
  {
    /*
     * Set the appropriate bit.
     */
    nVal = inpdw(pSource->VoterRegister.nAddr) | pSource->VoterRegister.nMask;
    outpdw(pSource->VoterRegister.nAddr, nVal);

    /*
     * Wait for the PLL to go active during the 15 us timeout period.
     */
    bResult =
      HAL_clk_ValidateRegSetTimeout(
        HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
        HAL_CLK_PLL_MODE_ACTIVE,
        HAL_CLK_LOCK_TIMEOUT_US);
  }

  return bResult;

} /* END HAL_clkRivianeluPLLEnableVote */


/* ===========================================================================
**  HAL_clkRivianeluPLLDisableVote
**
** ======================================================================== */

static void HAL_clkRivianeluPLLDisableVote
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32_t nVal;

  if ( pSource->VoterRegister.nAddr != 0 )
  {
    /*
     * Clear the appropriate bit.
     */
    nVal = inpdw(pSource->VoterRegister.nAddr) & (~pSource->VoterRegister.nMask);
    outpdw(pSource->VoterRegister.nAddr, nVal);
  }

} /* END HAL_clkRivianeluPLLDisableVote */


/* ===========================================================================
**  HAL_clkRivianeluPLLIsVoteEnabled
**
** ======================================================================== */

static boolean HAL_clkRivianeluPLLIsVoteEnabled
(
  HAL_clk_SourceDescType *pSource
)
{
  /*
   * Check the appropriate bit.
   */
  if (inpdw(pSource->VoterRegister.nAddr) & pSource->VoterRegister.nMask)
  {
    return TRUE;
  }

  return FALSE;

} /* END HAL_clkRivianeluPLLIsVoteEnabled */


/* ===========================================================================
**  HAL_clkRivianeluPLLEnable
**
**  The appropriate enable mode is executed based on the eMode parameter.
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clkRivianeluPLLEnable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  uint32_t nModeVal;
  boolean  bResult;

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pSource);

  /*
   * Assert PLL bypass.
   * This latches L value.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_BYPASSNL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);
  
   /*
   * Assert the reset_n field to put the PLL in standby state.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_RESET_N);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);

  /*
   * Set OPMODE to Run State
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pSource, HAL_PLL_OPMODE_RUN);
 
  /*
   * Wait for the PLL to lock during the 15 us timeout period.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
      HWIO_FMSK(PLL_MODE, PLL_LOCK_DET),
      HAL_CLK_LOCK_TIMEOUT_US);

  /*
   * Return immediately if the lock failed.
   */
  if (!bResult)
  {
    ERR_FATAL("HAL_clkRivianeluPLLEnableNormal Lock Failure", 0, 0, 0);
    return FALSE;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pSource);

  /*
   * Assert the output control field.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);

  return TRUE;

} /* END of HAL_clkRivianeluPLLEnable */


/* ===========================================================================
**  HAL_clkRivianeluPLLDisable
**
**  The appropriate disable mode is executed based on the eMode argument.
**
** ======================================================================== */

static void HAL_clkRivianeluPLLDisable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  uint32_t  nModeVal;

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pSource);
  
   /*
   * Put the PLL in reset mode
   */
  nModeVal |= (HWIO_FMSK(PLL_MODE, PLL_RESET_N) |
                HWIO_FMSK(PLL_MODE, PLL_BYPASSNL));
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);

  /*
   * Wait 2 ticks of the output main clock.
   */
  HAL_clk_BusyWait(1);

  /*
   * De-assert the PLL mode.
   */
  nModeVal &= ~HWIO_PLL_MODE_RMSK; 
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);
  
} /* END HAL_clkRivianeluPLLDisable */


/* ===========================================================================
**  HAL_clkRivianeluPLLIsEnabled
**
** ======================================================================== */

static boolean HAL_clkRivianeluPLLIsEnabled
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

} /* END HAL_clkRivianeluPLLIsEnabled */


/* ===========================================================================
**  HAL_clkRivianeluPLLConfig
**
** ======================================================================== */

static void HAL_clkRivianeluPLLConfig
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
    case HAL_CLK_CONFIG_PLL_FSM_MODE_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, ENABLE_VOTE_RUN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_FSM_MODE_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, ENABLE_VOTE_RUN, 0);
      break;

    case HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_EVEN_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_EVEN_EN, 0);
      break;

    case HAL_CLK_CONFIG_PLL_ODD_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_AUX_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_ODD_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_AUX_EN, 0);
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

} /* END HAL_clkRivianeluPLLConfig */


/* ===========================================================================
**  HAL_clkRivianeluPLLConfigPLLSlew
**
**  Returns:
**    boolean - TRUE if successfully configured.
**           FALSE if unable to detect that the PLL successfully locked.
** ======================================================================== */

static boolean HAL_clkRivianeluPLLConfigPLLSlew
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig,
  boolean                      bTriggerUpdate
)
{
  boolean  bResult;

  /*
   * Program L value.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_L_VAL, pSource, PLL_L_VAL, pConfig->nL);

  /*
   * Check if the update will be triggered later.
   */
  if (bTriggerUpdate != TRUE)
  {
    return TRUE;
  }

  /*
   * Latch in the new configuration values.
   * Trigger latch of new configuration using async update handshake
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_LATCH_INPUT, 0x1);

  /*
   * Poll PLL_MODE[PLL_ACK_LATCH] until high.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
      HWIO_FMSK(PLL_MODE, PLL_ACK_LATCH),
      HAL_CLK_LOCK_TIMEOUT_US);
  if (bResult != TRUE)
  {
    return bResult;
  }

  /*
   * Clear PLL_MODE[PLL_LATCH_INPUT] equal to zero.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_LATCH_INPUT, 0x0);

  /*
   * Poll PLL_MODE[PLL_ACK_LATCH] until low.
   */
  bResult =
    HAL_clk_ValidateRegClearTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
      HWIO_FMSK(PLL_MODE, PLL_ACK_LATCH),
      HAL_CLK_LOCK_TIMEOUT_US);
  if (bResult != TRUE)
  {
    return bResult;
  }

  /*
   * Wait 11 ticks of PLL ref_clk (@ XO, this is 570 ns) for the PLL to change.
   * if it is going to do so.  However, if the frequency change is small,
   * PLL_LOCK_DET will remain at one.
   */
  HAL_clk_BusyWait(1);

  /*
   * Wait for the PLL to lock during the timeout period.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
      HWIO_FMSK(PLL_MODE, PLL_LOCK_DET),
      HAL_CLK_LOCK_TIMEOUT_US);

  return bResult;

} /* END HAL_clkRivianeluPLLConfigPLLSlew */


/* ===========================================================================
**  HAL_clkRivianeluPLLConfigPLLNormal
**
**  Returns:
**    boolean - TRUE if successfully configured. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clkRivianeluPLLConfigPLLNormal
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  uint32_t nUserVal;
  uint32_t nAuxDiv, nEvenDiv;
  boolean  bPLLInFSMMode, bPLLInReset;

  /*
   * Check PLL mode.
   */
  bPLLInFSMMode = HAL_CLK_PLL_HWIO_INF(PLL_USER_CTL, pSource, ENABLE_VOTE_RUN);
  bPLLInReset = !HAL_CLK_PLL_HWIO_INF(PLL_MODE, pSource, PLL_RESET_N);

  /*
   * Disable the PLL if already out of reset.
   */
  if (!bPLLInReset)
  {
    HAL_clkRivianeluPLLDisable(pSource, HAL_CLK_SOURCE_DISABLE_MODE_NORMAL, NULL);
  }

  /*
   * Program L value.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_L_VAL, pSource, PLL_L_VAL, pConfig->nL);

  /*
   * Get the CONFIG value and clear out fields we will configure.
   */
  nUserVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pSource);
  nUserVal &= ~(HWIO_FMSK(PLL_USER_CTL, PRE_DIV_RATIO) |
                HWIO_FMSK(PLL_USER_CTL_U, POST_DIV_RATIO_AUX) |
                HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO_EVEN));

  /*
   * Program the pre-div value (div-1 to div-8).
   */
  if (pConfig->nPreDiv <= 8 && pConfig->nPreDiv > 0)
  {
    nUserVal |= HWIO_FVAL(PLL_USER_CTL, PRE_DIV_RATIO, (pConfig->nPreDiv - 1));
  }

  /*
   * Program the post-div values.
   */
  nAuxDiv = pConfig->PostDivs.Rivianelu.nAux;
  nEvenDiv = pConfig->PostDivs.Rivianelu.nEven;
  if (nEvenDiv > 0)
  {
    nEvenDiv--;
  }
  nUserVal |= HWIO_FVAL(PLL_USER_CTL_U, POST_DIV_RATIO_AUX, nAuxDiv);
  nUserVal |= HWIO_FVAL(PLL_USER_CTL, POST_DIV_RATIO_EVEN, nEvenDiv);

  /*
   * Finally program the USER_CTL register.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL, pSource, nUserVal);

  /*
   * For FSM, set the rest_n to bring the PLL out of reset as part of the 
   * steps to enable FSM mode.  This is a one-time programming.
   */
  if (bPLLInFSMMode)
  {
    HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_RESET_N, 1);
  }

  /*
   * Enable the PLL if it was on before.
   * Don't wait for the PLL to lock if it's in FSM mode since
   * the PLL_OUTCTRL won't toggle absent client voting.
   */
  if (!bPLLInReset)
  {
   HAL_clkRivianeluPLLEnable(pSource, !bPLLInFSMMode, NULL);
  }

  return TRUE;

} /* END HAL_clkRivianeluPLLConfigPLLNormal */


/* ===========================================================================
**  HAL_clkRivianeluPLLConfigPLL
**
**  Returns:
**    boolean - TRUE if successfully configured. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clkRivianeluPLLConfigPLL
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig,
  HAL_clk_SourceConfigMode     eMode
)
{
  boolean bResult = FALSE;

  /*
   * Program the appropriate config sequence.
   */
  if (eMode == HAL_CLK_SOURCE_CONFIG_MODE_NORMAL)
  {
    bResult = HAL_clkRivianeluPLLConfigPLLNormal(pSource, pConfig);
  }
  else if(eMode == HAL_CLK_SOURCE_CONFIG_MODE_SLEW)
  {
    bResult = HAL_clkRivianeluPLLConfigPLLSlew(pSource, pConfig, TRUE);
  }
  else if (eMode == HAL_CLK_SOURCE_CONFIG_MODE_PENDING)
  {
    bResult = HAL_clkRivianeluPLLConfigPLLSlew(pSource, pConfig, FALSE);
  }

  return bResult;

} /* END HAL_clkRivianeluPLLConfigPLL */


/* ===========================================================================
**  HAL_clkRivianeluPLLDetectPLLConfig
**
** ======================================================================== */

static void HAL_clkRivianeluPLLDetectPLLConfig
(
  HAL_clk_SourceDescType *pSource,
  HAL_clk_PLLConfigType  *pConfig
)
{
  uint32_t nRegVal;

  /*
   * Clear all config values not modified in this function.
   */
  pConfig->nFracVal = 0;

  /*
   * Read L value.
   */
  pConfig->nL = HAL_CLK_PLL_HWIO_INF(PLL_L_VAL, pSource, PLL_L_VAL);

  /*
   * No reference clock mux, so default to 0.
   */
  pConfig->nSource = 0;

  /*
   * Read USER_CTL register.
   */
  nRegVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pSource);

  /*
   * Get the pre divider.
   */
  pConfig->nPreDiv =
    HAL_CLK_PLL_HWIO_INFV(PLL_USER_CTL, pSource, PRE_DIV_RATIO, nRegVal) + 1;

  /*
   * Get the post divider.
   */
  pConfig->PostDivs.Rivianelu.nEven =
    HAL_CLK_PLL_HWIO_INFV(PLL_USER_CTL, pSource, POST_DIV_RATIO_EVEN, nRegVal)
    + 1;

  pConfig->PostDivs.Rivianelu.nAux =
    HAL_CLK_PLL_HWIO_INFV(PLL_USER_CTL_U, pSource, POST_DIV_RATIO_AUX, nRegVal);

  /*
   * Add 1 for case where field is 0.  Otherwise leave as is.
   */
  if (pConfig->PostDivs.Rivianelu.nAux == 0)
  {
    pConfig->PostDivs.Rivianelu.nAux++;
  }

} /* END HAL_clkRivianeluPLLDetectPLLConfig */


/* ===========================================================================
**  HAL_clkRivianeluPLLIsPLLConfigEqual
**
** ======================================================================== */

static boolean HAL_clkRivianeluPLLIsPLLConfigEqual
(
  const HAL_clk_PLLConfigType *pConfigA,
  const HAL_clk_PLLConfigType *pConfigB
)
{
  uint32_t nEvenDivA, nEvenDivB;
  uint32_t nAuxDivA, nAuxDivB;

  if (HAL_clk_GenericIsPLLConfigEqual(pConfigA, pConfigB))
  {
    /* Treat div-0 and div-1 as the same thing. */
    nEvenDivA = MAX(1, pConfigA->PostDivs.Rivianelu.nEven);
    nEvenDivB = MAX(1, pConfigB->PostDivs.Rivianelu.nEven);
    nAuxDivA  = MAX(1, pConfigA->PostDivs.Rivianelu.nAux);
    nAuxDivB  = MAX(1, pConfigB->PostDivs.Rivianelu.nAux);

    if (nEvenDivA == nEvenDivB && nAuxDivA  == nAuxDivB)
    {
      return TRUE;
    }
  }

  return FALSE;

} /* END HAL_clkRivianeluPLLIsPLLConfigEqual */


/* ===========================================================================
**  HAL_clkRivianeluPLLIsCalibrated
**
** ======================================================================== */

static boolean HAL_clkRivianeluPLLIsCalibrated
(
  HAL_clk_SourceDescType *pSource
)
{
  return TRUE;
} /* HAL_clkRivianeluPLLIsCalibrated */


/* ===========================================================================
**  HAL_clkRivianeluPLLSetCalConfig
**
** ======================================================================== */

static boolean HAL_clkRivianeluPLLSetCalConfig
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  return TRUE;
} /* HAL_clkRivianeluPLLSetCalConfig */


/* ===========================================================================
**  HAL_clkRivianeluPLLEnableNormal
**
**  PLL initial bringup.
**  When in the off state, the bias is off and draws no power.
**  This procedure results in calibration being performed.
**
**  This procedure applies only to Rivian PLL type.
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clkRivianeluPLLEnableNormal
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32_t nModeVal;
  boolean  bResult;

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pSource);

  /*
   * Assert PLL bypass.
   * This latches L value.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_BYPASSNL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);
  
   /*
   * Assert the reset_n field to put the PLL in standby state.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_RESET_N);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);

  /*
   * Set OPMODE to Run State
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pSource, HAL_PLL_OPMODE_RUN);
 
  /*
   * Wait for the PLL to lock during the 15 us timeout period.
   */
  bResult =
    HAL_clk_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
      HWIO_FMSK(PLL_MODE, PLL_LOCK_DET),
      HAL_CLK_LOCK_TIMEOUT_US);

  /*
   * Return immediately if the lock failed.
   */
  if (!bResult)
  {
    ERR_FATAL("HAL_clkRivianeluPLLEnableNormal Lock Failure", 0, 0, 0);
    return FALSE;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pSource);

  /*
   * Assert the output control fiel d.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);

  return TRUE;

} /* END HAL_clkRivianeluPLLEnableNormal */


/* ===========================================================================
**  HAL_clkRivianeluPLLDisableToStandby
**
**  PLL shutdown to standby state.
**  This procedure leaves the bias on:
**    skips calibration when enabling via HAL_clkRivianeluPLLEnableFromStandby.
**    draws 75-100 micro amps while in standby mode.
**
**  This procedure applies only to Rivian PLL type.
**
** ======================================================================== */

static void HAL_clkRivianeluPLLDisableToStandby
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32_t  nModeVal;

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pSource);
  
  /*
   * Put the PLL in reset mode
   */
  nModeVal |= (HWIO_FMSK(PLL_MODE, PLL_RESET_N));
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);

  /*
   * Wait 2 ticks of the output main clock.
   */
  HAL_clk_BusyWait(1);

  /*
   * Set OPMODE to Standby State
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pSource, HAL_PLL_OPMODE_STANDBY);
  
} /* END HAL_clkRivianeluPLLDisableToStandby */



/* ===========================================================================
**  HAL_clkRivianeluPLLSetRegSettings
**
** ======================================================================== */

static void HAL_clkRivianeluPLLSetRegSettings
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
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL,      pSource, pmSettings->nUserCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U,    pSource, pmSettings->nUserCtl1);
} /* END HAL_clkRivianeluPLLSetRegSettings */



