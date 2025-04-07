/*
==============================================================================

FILE:         HALclk.c

DESCRIPTION:
  Common code for the clock HAL module.

==============================================================================
            Copyright (c) 2012 - 2020 QUALCOMM Technologies, Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/
#include "stdint.h"
#include "HALclkXBLInternal.h"
#include <HALhwio.h>
#include "busywait.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/

/* ============================================================================
**    Typedefs
** ==========================================================================*/

/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

/* ===========================================================================
**  HAL_clk_EnableSource
**
** ======================================================================== */

boolean HAL_clk_EnableSource
(
  HAL_clk_SourceDescType *pSource,
  HAL_clk_SourceDisableModeType  eMode,
  void                          *pData
)
{
  if (pSource != NULL &&
      pSource->pmControl != NULL &&
      pSource->pmControl->Enable != NULL)
  {
    return pSource->pmControl->Enable(pSource, eMode, pData);
  }

  return FALSE;

} /* END HAL_clk_EnableSource */


/* ===========================================================================
**  HAL_clk_EnableSourceVote
**
** ======================================================================== */

boolean HAL_clk_EnableSourceVote
(
  HAL_clk_SourceDescType *pSource
)
{
  if (pSource != NULL &&
      pSource->pmControl != NULL &&
      pSource->pmControl->EnableVote != NULL)
  {
    return pSource->pmControl->EnableVote(pSource);
  }

  return FALSE;

} /* END HAL_clk_EnableSourceVote */


/* ===========================================================================
**  HAL_clk_ConfigSource
**
** ======================================================================== */

void HAL_clk_ConfigSource
(
  HAL_clk_SourceDescType *pSource,
  HAL_clk_SourceConfigType eConfig
)
{
  /*
   * Configure the source if possible.
   */
  if (pSource != NULL &&
      pSource->pmControl != NULL &&
      pSource->pmControl->Config != NULL)
  {
    pSource->pmControl->Config(pSource, eConfig);
  }

} /* END HAL_clk_ConfigSource */


/* ===========================================================================
**  HAL_clk_ConfigPLL
**
** ======================================================================== */

boolean HAL_clk_ConfigPLL
(
  HAL_clk_SourceDescType *pSource,
  const HAL_clk_PLLConfigType *pConfig,
  HAL_clk_SourceConfigMode     eMode
)
{
  /*
   * Configure the source if possible.
   */
  if (pSource != NULL &&
      pSource->pmControl != NULL &&
      pSource->pmControl->ConfigPLL != NULL)
  {
    return pSource->pmControl->ConfigPLL(pSource, pConfig, eMode);
  }

  return FALSE;

} /* END HAL_clk_ConfigPLL */


/* ===========================================================================
**  HAL_clk_IsSourceEnabled
**
** ======================================================================== */

boolean HAL_clk_IsSourceEnabled
(
  HAL_clk_SourceDescType *pSource
)
{
  /*
   * Invoke the callback.
   */
  if (pSource != NULL &&
      pSource->pmControl != NULL &&
      pSource->pmControl->IsEnabled != NULL)
  {
    return pSource->pmControl->IsEnabled(
      pSource);
  }

  return FALSE;

} /* END HAL_clk_IsSourceEnabled */


/* ===========================================================================
**  HAL_clk_ValidateRegSetTimeout
**
** ======================================================================== */

boolean HAL_clk_ValidateRegSetTimeout
(
  uintnt    nAddr,
  uint32_t  nMask,
  uint32_t  nTimeoutUS
)
{
  /*
   * Wait for the register field to set during the timeout period.
   */
  do
  {
    if (in_dword_masked(nAddr, nMask))
    {
      return TRUE;
    }
    /*
     * Wait 1 us between each register read.
     */
    else
    {
      busywait(1);
    }
  }

  /*
   * nTimeoutUS is post-decremented to guarantee that we waited up to
   * the original nTimeoutUS value.
   */
  while(nTimeoutUS--);

  return FALSE;

} /* END HAL_clk_ValidateRegSetTimeout */


boolean HAL_clk_SetSourceCalConfig
(
  HAL_clk_SourceDescType      *pSource,
  const HAL_clk_PLLConfigType *pmConfig
)
{
  if (pSource                           != NULL &&
      pSource->pmControl                != NULL &&
      pSource->pmControl->SetCalConfig  != NULL)
  {
    return pSource->pmControl->SetCalConfig(pSource, pmConfig);
  }

  return FALSE;
}


void HAL_clk_SetSourceRegSettings
(
  HAL_clk_SourceDescType              *pSource,
  const HAL_clk_SourceRegSettingsType *pmSettings
)
{
  if (pSource                               != NULL &&
      pSource->pmControl                    != NULL &&
      pSource->pmControl->SetRegSettings    != NULL)
  {
    pSource->pmControl->SetRegSettings(pSource, pmSettings);
  }
}
