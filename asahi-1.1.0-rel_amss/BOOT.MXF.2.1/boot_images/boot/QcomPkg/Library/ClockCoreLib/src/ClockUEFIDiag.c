/*
===========================================================================
*/
/**
  @file ClockUEFIDiag.c

  UEFI BDS Menu and other diagnostic functions.
*/
/*
  ====================================================================

  Copyright (c) 2020,2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ==================================================================== */
/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/08/18   op      Remove dumping clocks'state to file
03/14/17   op      Enable Clocks' state File Logging

===========================================================================*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockDriver.h"
#include <Library/BaseLib.h>


#define CLK_NAME_SZ 50

/*=========================================================================
      Functions
==========================================================================*/
/**
 * @brief This is to convert numerical voltage request level value to their string equivalent. 
 * 
 */
CHAR8* vreglevelToString
(
  uint32 vreglevelInInt
)
{
  CHAR8* result = "";
  
  if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_OFF)               result = "OFF";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_RET)          result = "RET";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_MIN_SVS)      result = "MIN_SVS";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_LOW_SVS_D1)   result = "LOW_SVS_D1";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_LOW_SVS)      result = "LOW_SVS";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_LOW_SVS_L1)   result = "LOW_SVS_L1";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_LOW_SVS_L2)   result = "LOW_SVS_L2";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_SVS)          result = "SVS";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_SVS_L0)       result = "SVS_L0";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_SVS_L1)       result = "SVS_L1";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_SVS_L2)       result = "SVS_L2";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_NOM)          result = "NOM";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_NOM_L1)       result = "NOM_L1";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_NOM_L2)       result = "NOM_L2";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_TUR)          result = "TUR";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_TUR_L0)       result = "TUR_L0";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_TUR_L1)       result = "TUR_L1";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_TUR_L2)       result = "TUR_L2";
  else if(vreglevelInInt == RAIL_VOLTAGE_LEVEL_TUR_L3)       result = "TUR_L3";
  else if(vreglevelInInt == RAIL_VOLTAGE_SUPER_TURBO)        result = "SUPER_TURBO";
  else if(vreglevelInInt == RAIL_VOLTAGE_SUPER_TURBO_NO_CPR) result = "SUPER_TURBO_NO_CPR";

  return result;
}

ClockResult Clock_LogStateToUart
(
  ClockDrvCtxt        *pDrvCtxt,
  uint32               nFlags
)
  {
  ClockBSPType                *pBSP = pDrvCtxt->pBSP;
  ClockNodeType               *pClock;
  ClockPowerDomainNodeType    *pPowerDomain;
  uint32                       i,  nFreqHzConfig, nRefCount;
  const char                  *szSource;
  CHAR16                       sUnicodeName[50];

  DEBUG(( EFI_D_ERROR, "CLOCK \t\t\t\t\t\t REF COUNT FREQ CONFIG VOLTAGE \t SOURCE \r\n"));

  /*------------------------------------------------------------------------*/
  /* Log clock state.                                                       */
  /*------------------------------------------------------------------------*/
  //status = Clock_aClocksRequiredOn(pDrvCtxt);
  for (i = 0; i < pBSP->nNumClocks; i++)
  {
    pClock = &pBSP->aClocks[i];
    nFreqHzConfig = 0;
    nRefCount = 0;
    
    /*
     * Get Reference Count.
     */
      nRefCount = CLOCK_REF_COUNT_TOTAL(pClock);
    

    /*
     * Get frequency. Its a software detected frequency it may or may not match
     * hardware calculated frequency.
     */
    if (pClock->pDomain->pActiveMuxConfig != NULL)
    {
      nFreqHzConfig = pClock->pDomain->pActiveMuxConfig->nFreqHz;
    }

    /*
     * Get source.
     */
    if (pClock->pDomain->pSource)
    {
      szSource = pClock->pDomain->pSource->szName;
    }
    else
    {
      szSource = "";
    }

    /*
     * Log results.
     */
   
      AsciiStrToUnicodeStrS(pClock->szName,sUnicodeName, CLK_NAME_SZ);
      DEBUG(( EFI_D_ERROR,"%-55s,",sUnicodeName));

      DEBUG(( EFI_D_ERROR, "%-3u,%-12u,",
        nRefCount, nFreqHzConfig));
		
	  AsciiStrToUnicodeStrS(vreglevelToString(pClock->pDomain->VRegRequest.eVRegLevel),sUnicodeName, CLK_NAME_SZ);	
      DEBUG(( EFI_D_ERROR,"%-7s,",sUnicodeName));
      AsciiStrToUnicodeStrS(szSource, sUnicodeName, CLK_NAME_SZ);
      DEBUG(( EFI_D_ERROR,"%-5s\n",sUnicodeName));
    
  }

  /*------------------------------------------------------------------------*/
  /* Log power domain state.                                                */
  /*------------------------------------------------------------------------*/

  DEBUG(( EFI_D_ERROR, "\n"));
  DEBUG(( EFI_D_ERROR, "\n"));
  DEBUG(( EFI_D_ERROR, " POWER DOMAIN \t\t\t\t  REF COUNT \r\n"));

  for (i = 0; i < pBSP->nNumPowerDomains; i++)
  {
    pPowerDomain = &pBSP->aPowerDomains[i];
    
    AsciiStrToUnicodeStrS(pPowerDomain->szName,sUnicodeName, CLK_NAME_SZ);
    DEBUG(( EFI_D_ERROR, " %-45s,%-3u \n",sUnicodeName, (CLOCK_REF_COUNT_TOTAL(pPowerDomain))));
  }

  return CLOCK_SUCCESS;

} /* END Clock_LogStateUart */


