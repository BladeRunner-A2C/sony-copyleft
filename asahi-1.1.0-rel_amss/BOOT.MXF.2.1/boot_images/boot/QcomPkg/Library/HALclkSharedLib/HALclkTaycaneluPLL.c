/*
==============================================================================

FILE:         HALclkTaycaneluPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Taycanelu PLL control.
  These PLLs are of the Taycanelu PLL variety.

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

#include "stdbool.h"
#include "stdint.h"
#include "HALhwio.h"
#include "HALclkGenericPLL.h"
#include "HALclkTaycaneluPLL.h"
#include "HALclkInternal.h"
#include "HALclkGeneric.h"


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
#define HAL_CLK_LOCK_TIMEOUT_US 1000

/*
 * CLOCK_WAIT_FOR_PLL_LOCK
 *
 * Flag for whether to wait for the PLL to lock or not.
 */
#define CLOCK_WAIT_FOR_PLL_LOCK TRUE

/*
 * Number of status registers.
 *
 */
#define HAL_CLK_PLL_NUM_STATUS_REGS 32

/* ============================================================================
**    Functions Prototypes
** ==========================================================================*/

static boolean HAL_clk_TaycaneluPLLEnable           ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceDisableModeType eMode, void *pData );
static void HAL_clk_TaycaneluPLLDisable          ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceDisableModeType eMode, void *pData );
static boolean HAL_clk_TaycaneluPLLIsEnabled        ( HAL_clk_SourceDescType *pSource );
static void HAL_clk_TaycaneluPLLConfig           ( HAL_clk_SourceDescType *pSource, HAL_clk_SourceConfigType eConfig );
static boolean HAL_clk_TaycaneluPLLConfigPLL        ( HAL_clk_SourceDescType *pSource, const HAL_clk_PLLConfigType *pmConfig, HAL_clk_SourceConfigMode eMode );
static void HAL_clk_TaycaneluPLLDetectPLLConfig  ( HAL_clk_SourceDescType *pSource, HAL_clk_PLLConfigType *pmConfig );
static boolean HAL_clk_TaycaneluPLLEnableVote       ( HAL_clk_SourceDescType *pSource );
static void HAL_clk_TaycaneluPLLDisableVote      ( HAL_clk_SourceDescType *pSource );
static boolean HAL_clk_TaycaneluPLLIsVoteEnabled    ( HAL_clk_SourceDescType *pSource );
static boolean HAL_clk_TaycaneluPLLIsPLLConfigEqual ( const HAL_clk_PLLConfigType *pConfigA, const HAL_clk_PLLConfigType *pConfigB );
static boolean HAL_clk_TaycaneluPLLIsCalibrated     ( HAL_clk_SourceDescType *pSource );
static boolean HAL_clk_TaycaneluPLLSetCalConfig     ( HAL_clk_SourceDescType *pSource, const HAL_clk_PLLConfigType *pmConfig );
static void HAL_clk_TaycaneluPLLSetRegSettings   ( HAL_clk_SourceDescType *pSource, const HAL_clk_SourceRegSettingsType *pmSettings );


/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clk_TaycaneluPLLControl
 *
 * Control function array for the Taycanelu PLLs.
 */
HAL_clk_SourceControlType HAL_clk_TaycaneluPLLControl =
{
  .Enable           = HAL_clk_TaycaneluPLLEnable,
  .Disable          = HAL_clk_TaycaneluPLLDisable,
  .IsEnabled        = HAL_clk_TaycaneluPLLIsEnabled,
  .Config           = HAL_clk_TaycaneluPLLConfig,
  .ConfigPLL        = HAL_clk_TaycaneluPLLConfigPLL,
  .DetectPLLConfig  = HAL_clk_TaycaneluPLLDetectPLLConfig,
  .EnableVote       = HAL_clk_TaycaneluPLLEnableVote,
  .DisableVote      = HAL_clk_TaycaneluPLLDisableVote,
  .IsVoteEnabled    = HAL_clk_TaycaneluPLLIsVoteEnabled,
  .IsPLLConfigEqual = HAL_clk_TaycaneluPLLIsPLLConfigEqual,
  .IsCalibrated     = HAL_clk_TaycaneluPLLIsCalibrated,
  .SetCalConfig     = HAL_clk_TaycaneluPLLSetCalConfig,
  .SetRegSettings   = HAL_clk_TaycaneluPLLSetRegSettings,
};

/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

/* ===========================================================================
**  HAL_clk_TaycaneluPLLEnableVote
**
** ======================================================================== */

static boolean HAL_clk_TaycaneluPLLEnableVote
(
  HAL_clk_SourceDescType *pSource
)
{
  uint32_t nVal;
  boolean     bResult = TRUE;

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

} /* END HAL_clk_TaycaneluPLLEnableVote */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLDisableVote
**
** ======================================================================== */

static void HAL_clk_TaycaneluPLLDisableVote
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
    nVal = inpdw(pSource->VoterRegister.nAddr) & ~pSource->VoterRegister.nMask;
    outpdw(pSource->VoterRegister.nAddr, nVal);
  }

} /* END HAL_clk_TaycaneluPLLDisableVote */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLIsVoteEnabled
**
** ======================================================================== */

static boolean HAL_clk_TaycaneluPLLIsVoteEnabled
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

} /* END HAL_clk_TaycaneluPLLIsVoteEnabled */


/* ===========================================================================
**  _HAL_clk_TaycaneluPLLEnable
**
**  Internal helper function to enable a given PLL.
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean _HAL_clk_TaycaneluPLLEnable
(
  HAL_clk_SourceDescType *pSource,
  boolean                    bWaitForLock
)
{
  boolean bResult;

  /*
   * Set desired operational mode.
   * This field is ignored when the PLL is in FSM mode.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pSource, HAL_PLL_OPMODE_RUN);

  /*
   * Take PLL out of reset, which will switch to configured OPMODE.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_RESET_N, 1);

  /*
   * Wait for the PLL to lock if needed.
   */
  if (bWaitForLock)
  {
    bResult =
      HAL_clk_ValidateRegSetTimeout(
        HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
        HWIO_FMSK(PLL_MODE, PLL_LOCK_DET),
        HAL_CLK_LOCK_TIMEOUT_US);
    if (!bResult)
    {
      return FALSE;
    }
  }

  /*
   * Enable the PLL outputs.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_OUTCTRL, 1);

  return TRUE;

} /* END _HAL_clk_TaycaneluPLLEnable */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLEnable
**
**  The appropriate enable mode is executed based on the eMode parameter.
**
**  Returns:
**    boolean - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_TaycaneluPLLEnable
(
  HAL_clk_SourceDescType        *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  return _HAL_clk_TaycaneluPLLEnable(pSource, CLOCK_WAIT_FOR_PLL_LOCK);

} /* END of HAL_clk_TaycaneluPLLEnable */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLDisable
**
**  The appropriate disable mode is executed based on the eMode argument.
**
** ======================================================================== */

static void HAL_clk_TaycaneluPLLDisable
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
    HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_RESET_N, 0);
  }

} /* END HAL_clk_TaycaneluPLLDisable */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLIsEnabled
**
** ======================================================================== */

static boolean HAL_clk_TaycaneluPLLIsEnabled
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

} /* END HAL_clk_TaycaneluPLLIsEnabled */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLConfig
**
** ======================================================================== */

static void HAL_clk_TaycaneluPLLConfig
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
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_ODD_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_ODD_OUTPUT_DISABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_ODD_EN, 0);
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

} /* END HAL_clk_TaycaneluPLLConfig */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLConfigPLLSlew
**
**  Returns:
**    boolean - TRUE if successfully configured.
**           FALSE if unable to detect that the PLL successfully locked.
** ======================================================================== */

static boolean HAL_clk_TaycaneluPLLConfigPLLSlew
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig,
  boolean                         bTriggerUpdate
)
{
  uint32_t nUserVal;
  boolean     bResult;
  
  if ( HAL_CLK_PLL_HWIO_INF(PLL_L_VAL, pSource, PLL_L_VAL) == pConfig->nL )
  {
    return TRUE;
  }

  /*
   * Program L value.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_L_VAL, pSource, PLL_L_VAL, pConfig->nL);

  /*
   * Program fractional value.
   */
  nUserVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pSource);
  if (pConfig->eFracMode == HAL_CLK_PLL_FRAC_MODE_MN)
  {
    nUserVal |= HWIO_FMSK(PLL_USER_CTL, FRAC_FORMAT_SEL);
  }
  else
  {
    /* Default to Alpha */
    nUserVal &= ~HWIO_FMSK(PLL_USER_CTL, FRAC_FORMAT_SEL);
  }

  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL, pSource, nUserVal);
  HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_VAL, pSource, pConfig->nFracVal);

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

} /* END HAL_clk_TaycaneluPLLConfigPLLSlew */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLConfigPLLNormal
**
**  Returns:
**    boolean - TRUE if successfully configured. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_TaycaneluPLLConfigPLLNormal
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  uint32_t nUserVal;
  uint32_t nOddDiv, nEvenDiv;
  boolean     bPLLInFSMMode, bPLLInReset;

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
    HAL_clk_TaycaneluPLLDisable(pSource, HAL_CLK_SOURCE_DISABLE_MODE_NORMAL, NULL);
  }

  /*
   * Program L value.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_L_VAL, pSource, PLL_L_VAL, pConfig->nL);

  /*
   * Program fractional value.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_VAL, pSource, pConfig->nFracVal);

  nUserVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pSource);
  if (pConfig->eFracMode == HAL_CLK_PLL_FRAC_MODE_MN)
  {
    nUserVal |= HWIO_FMSK(PLL_USER_CTL, FRAC_FORMAT_SEL);
  }
  else
  {
    /* Default to Alpha. */
    nUserVal &= ~HWIO_FMSK(PLL_USER_CTL, FRAC_FORMAT_SEL);
  }  

  /*
   * Get the CONFIG value and clear out fields we will configure.
   */
  nUserVal &= ~(HWIO_FMSK(PLL_USER_CTL, PRE_DIV_RATIO) |
                HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO_ODD) |
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
  nOddDiv = pConfig->PostDivs.Taycanelu.nOdd;
  nEvenDiv = pConfig->PostDivs.Taycanelu.nEven;
  if (nEvenDiv > 0)
  {
    nEvenDiv--;
  }
  if (nOddDiv > 0)
  {
    nOddDiv--;
  }
  nUserVal |= HWIO_FVAL(PLL_USER_CTL, POST_DIV_RATIO_ODD, nOddDiv);
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
   _HAL_clk_TaycaneluPLLEnable(pSource, !bPLLInFSMMode);
  }

  return TRUE;

} /* END HAL_clk_TaycaneluPLLConfigPLLNormal */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLConfigPLL
**
**  Returns:
**    boolean - TRUE if successfully configured. FALSE otherwise.
** ======================================================================== */

static boolean HAL_clk_TaycaneluPLLConfigPLL
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
    bResult = HAL_clk_TaycaneluPLLConfigPLLNormal(pSource, pConfig);
  }
  else if(eMode == HAL_CLK_SOURCE_CONFIG_MODE_SLEW)
  {
    bResult = HAL_clk_TaycaneluPLLConfigPLLSlew(pSource, pConfig, TRUE);
  }
  else if (eMode == HAL_CLK_SOURCE_CONFIG_MODE_PENDING)
  {
    bResult = HAL_clk_TaycaneluPLLConfigPLLSlew(pSource, pConfig, FALSE);
  }

  return bResult;

} /* END HAL_clk_TaycaneluPLLConfigPLL */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLDetectPLLConfig
**
** ======================================================================== */

static void HAL_clk_TaycaneluPLLDetectPLLConfig
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
   * The Taycanelu architecture abstracts the VCO logic away from the user so just
   * default this to the first VCO for initialization purposes.
   */
  pConfig->nMode = HAL_CLK_PLL_HWIO_INF(PLL_USER_CTL_U, pSource, BB_MODE);

  /*
   * Read L value.
   */
  pConfig->nL = HAL_CLK_PLL_HWIO_INF(PLL_L_VAL, pSource, PLL_L_VAL);

  /*
   * Read fractional value.
   */
  nRegVal = HAL_CLK_PLL_HWIO_INF(PLL_ALPHA_VAL, pSource, PLL_ALPHA_VAL);
  pConfig->nFracVal = nRegVal;

  /*
   * Detect fractional mode.
   */
  if (HAL_CLK_PLL_HWIO_INF(PLL_USER_CTL, pSource, FRAC_FORMAT_SEL))
  {
    pConfig->eFracMode = HAL_CLK_PLL_FRAC_MODE_MN;
  }
  else
  {
    pConfig->eFracMode = HAL_CLK_PLL_FRAC_MODE_ALPHA;
  }

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
  pConfig->PostDivs.Taycanelu.nEven =
    HAL_CLK_PLL_HWIO_INFV(PLL_USER_CTL, pSource, POST_DIV_RATIO_EVEN, nRegVal)
    + 1;

  pConfig->PostDivs.Taycanelu.nOdd =
    HAL_CLK_PLL_HWIO_INFV(PLL_USER_CTL, pSource, POST_DIV_RATIO_ODD, nRegVal)
    + 1;

} /* END HAL_clk_TaycaneluPLLDetectPLLConfig */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLIsPLLConfigEqual
**
** ======================================================================== */

static boolean HAL_clk_TaycaneluPLLIsPLLConfigEqual
(
  const HAL_clk_PLLConfigType *pConfigA,
  const HAL_clk_PLLConfigType *pConfigB
)
{
  uint32_t nEvenDivA, nEvenDivB;
  uint32_t nOddDivA, nOddDivB;

  if (HAL_clk_GenericIsPLLConfigEqual(pConfigA, pConfigB))
  {
    /* Treat div-0 and div-1 as the same thing. */
    nEvenDivA = MAX(1, pConfigA->PostDivs.Taycanelu.nEven);
    nEvenDivB = MAX(1, pConfigB->PostDivs.Taycanelu.nEven);
    nOddDivA  = MAX(1, pConfigA->PostDivs.Taycanelu.nOdd);
    nOddDivB  = MAX(1, pConfigB->PostDivs.Taycanelu.nOdd);

    if (nEvenDivA == nEvenDivB && nOddDivA  == nOddDivB)
    {
      return TRUE;
    }
  }

  return FALSE;

} /* END HAL_clk_TaycaneluPLLIsPLLConfigEqual */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLIsCalibrated
**
** ======================================================================== */

static boolean HAL_clk_TaycaneluPLLIsCalibrated
(
  HAL_clk_SourceDescType *pSource
)
{
  /*
   * Taycanelu PLLs have a dedicated bit in PLL_MODE to indicate calibration.
   */
  return !HAL_CLK_PLL_HWIO_INF(PLL_MODE, pSource, PCAL_NOT_DONE);

} /* HAL_clk_TaycaneluPLLIsCalibrated */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLSetCalConfig
**
** ======================================================================== */

static boolean HAL_clk_TaycaneluPLLSetCalConfig
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pConfig
)
{
  HAL_CLK_PLL_HWIO_OUTF(PLL_L_VAL, pSource, PROCESS_CAL_L_VAL, pConfig->nL);
  return TRUE;

} /* HAL_clk_TaycaneluPLLSetCalConfig */


/* ===========================================================================
**  HAL_clk_TaycaneluPLLSetRegSettings
**
** ======================================================================== */

static void HAL_clk_TaycaneluPLLSetRegSettings
(
  HAL_clk_SourceDescType              *pSource,
  const HAL_clk_SourceRegSettingsType *pmSettings
)
{
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL,    pSource, pmSettings->nConfigCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL_U,  pSource, pmSettings->nConfigCtl1);
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL_U1, pSource, pmSettings->nConfigCtl2);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL,      pSource, pmSettings->nTestCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_U,    pSource, pmSettings->nTestCtl1);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL,      pSource, pmSettings->nUserCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U,    pSource, pmSettings->nUserCtl1);

} /* END HAL_clk_TaycaneluPLLSetRegSettings */


