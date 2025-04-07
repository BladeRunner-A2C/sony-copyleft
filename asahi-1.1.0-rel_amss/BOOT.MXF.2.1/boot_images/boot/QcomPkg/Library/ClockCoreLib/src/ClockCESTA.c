/*
===========================================================================
*/
/**
  @file ClockCESTA.c

  Implementation file for the CESTA clock
*/
/*
  ====================================================================

  Copyright (c) 2022-2023 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: 
  $DateTime: 
  $Author: 

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockDriver.h"
#include "ClockCESTA.h"
#include "HALclk.h"
#include "cmd_db.h"
#include "pwr_utils_lvl.h"


/* =========================================================================
**  Function : Clock_InitCESTAInstance
** =========================================================================*/
ClockResult Clock_InitCESTAInstance
(
  const ClockCESTA* pCESTA
)
{
  ClockDrvCtxt            *pDrvCtxt  = Clock_GetDrvCtxt();
  uint32_t                 rail_addr, nSeqCount, nBranchCount, nRegCount;
  int                      hlvl, mapped_lvl;
  uintnt                   nSeqAddr, nBranchAddr, nRegAddr; 
  const ClockCESTARegType *pRegVal;  
        
  /* 
   * Program the Sequencer 
   */
  for(nSeqCount = 0; nSeqCount < pCESTA->nNumSequence; nSeqCount++)
  {
    nSeqAddr = pCESTA->nSequenceAddr + (4*nSeqCount);
    outpdw(nSeqAddr, pCESTA->aSequence[nSeqCount]);
  }
      
  /* 
   * Program the Branch Sequence 
   */
  for(nBranchCount = 0; nBranchCount < pCESTA->nNumBranches; nBranchCount++)
  {
    nBranchAddr = pCESTA->nBranchAddr + (4*nBranchCount);
    outpdw(nBranchAddr, pCESTA->aBranches[nBranchCount]);
  }
      
  /* 
   * Program the reg values 
   */ 
  for(nRegCount = 0; nRegCount < pCESTA->nNumRegVals; nRegCount++)
  {
    pRegVal = &pCESTA->aRegVals[nRegCount];
    nRegAddr = pRegVal->nAddr;
    switch(pRegVal->eType)
    {
      case CESTA_REG_RAW:
        outpdw(nRegAddr, pRegVal->Data.nVal);
        break;
          
      case CESTA_REG_CMD_DB_ADDR:
        rail_addr = cmd_db_query_addr(pRegVal->Data.CmdDB.szName);
        if(rail_addr == 0)
        {
          ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
            "Clock_InitCESTA: Rail address Lookup failed, Rail is %s", pRegVal->Data.CmdDB.szName);
          return CLOCK_ERROR;
        }
        outpdw(nRegAddr, rail_addr + pRegVal->Data.CmdDB.nOffset);            
        break;
          
      case CESTA_REG_HLVL:
        hlvl = pwr_utils_hlvl_named_resource(pRegVal->Data.VLVL.szRail,
                                             pRegVal->Data.VLVL.nVLVL, 
                                            &mapped_lvl);
        if(hlvl < 0)
        {
          ULOG_RT_PRINTF_3(pDrvCtxt->hClockLog,
            "Clock_InitCESTA: HLVL is %d, Rail is %s, SW VLVL is %d", 
            hlvl, pRegVal->Data.VLVL.szRail, pRegVal->Data.VLVL.nVLVL);
          return CLOCK_ERROR;
        }
        outpdw(nRegAddr, hlvl);
        break;
          
      default:
        ULOG_RT_PRINTF_1(pDrvCtxt->hClockLog,
          "Clock_InitCESTA: RegVal eType does not exist, eType is %d \n", pRegVal->eType);
        return CLOCK_ERROR;
    }
  }   
  
  return CLOCK_SUCCESS;
} /* END Clock_InitCESTAInstance */


/* =========================================================================
**  Function : Clock_CESTAEnableDependencies
** =========================================================================*/
ClockResult Clock_CESTAEnableDependencies(const ClockCESTA* pCESTA)
{
  ClockDrvCtxt            *pDrvCtxt  = Clock_GetDrvCtxt();
  ClockIdType              clock_id;
  int32_t                  nDepCount;
  
  if(pCESTA)
  {
    if(pCESTA->aClockDeps)
    {
      for(nDepCount = 0; nDepCount < pCESTA->nNumClockDeps; nDepCount++)
      {
        if(CLOCK_SUCCESS != Clock_GetId(pDrvCtxt->hClient, pCESTA->aClockDeps[nDepCount], &clock_id))
        {
          return CLOCK_ERROR;
        }
        if(CLOCK_SUCCESS != Clock_EnableClock(pDrvCtxt->hClient, clock_id))
        {
          return CLOCK_ERROR;
        }       
      }
    } 
  }
  
  return CLOCK_SUCCESS;
} /* END Clock_CESTAEnableDependencies */


/* =========================================================================
**  Function : Clock_CESTADisableDependencies
** =========================================================================*/
ClockResult Clock_CESTADisableDependencies(const ClockCESTA* pCESTA)
{
  ClockDrvCtxt            *pDrvCtxt  = Clock_GetDrvCtxt();
  ClockIdType              clock_id;
  int32_t                  nDepCount;
  
  if(pCESTA)
  {
    if(pCESTA->aClockDeps)
    {
      for(nDepCount = pCESTA->nNumClockDeps - 1; nDepCount >= 0; nDepCount--)
      {
        if(CLOCK_SUCCESS != Clock_GetId(pDrvCtxt->hClient, pCESTA->aClockDeps[nDepCount], &clock_id))
        {
          return CLOCK_ERROR;
        }
        if(CLOCK_SUCCESS != Clock_DisableClock(pDrvCtxt->hClient, clock_id))
        {
          return CLOCK_ERROR;
        }       
      }
    } 
  }
  
  return CLOCK_SUCCESS;
} /* END Clock_CESTADisableDependencies */


/* =========================================================================
**  Function : Clock_InitCESTA
** =========================================================================*/
/**
  Initialize CESTA instances

  This function initializes the CESTA instances that are set 
  to be configured by default

  @return
  CLOCK_SUCCESS -- Initialization was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/
ClockResult Clock_InitCESTA()
{
  ClockDrvCtxt*         pDrvCtxt = Clock_GetDrvCtxt();
  ClockResult           eResult  = CLOCK_SUCCESS;
  const ClockCESTA     *pCESTA;
  uint32_t              nCount, nSrcCount;
  ClockSourceNodeType  *pSource;
  
  /* 
   * Short circuit if no CESTA instance 
   */
  if(!pDrvCtxt->pBSP->aCESTA)
  {
    return CLOCK_SUCCESS;
  }
  
  for(nCount = 0; nCount < pDrvCtxt->pBSP->nNumCESTA; nCount++)
  {
    pCESTA = pDrvCtxt->pBSP->aCESTA[nCount]; 
    eResult = Clock_CESTAEnableDependencies(pCESTA);
    if(CLOCK_SUCCESS != eResult)
    {
      return CLOCK_ERROR;
    }
  }
  
  for(nCount = 0; nCount < pDrvCtxt->pBSP->nNumCESTA; nCount++)
  {
    pCESTA = pDrvCtxt->pBSP->aCESTA[nCount]; 
    if(pCESTA->nFlags & CLOCK_CESTA_FLAG_DEFAULT_ENABLE)
    {
      eResult = Clock_InitCESTAInstance(pCESTA);
      if(CLOCK_SUCCESS != eResult)
      {
        return CLOCK_ERROR;
      }
    }
  }
  
  /* 
   * Set up PLL for one time settings and calibration 
   */ 
  for(nSrcCount = 0; nSrcCount < pDrvCtxt->pBSP->nNumSources; nSrcCount++)
  {
    pSource = pDrvCtxt->pBSP->aSources[nSrcCount];
    if(CLOCK_FLAG_IS_SET(pSource, CESTA_CONTROLLED))
    {
      if(FALSE == HAL_clk_IsSourceEnabled(&pSource->HALSource))
      {
        /* Enable PLL */
        if(CLOCK_SUCCESS != Clock_EnableSourceInternal(pDrvCtxt->hClient, pSource, CLOCK_FLAG_IS_SET(pSource, SUPPRESSIBLE)))
        {
          return CLOCK_ERROR;
        }
        /* Disable PLL after CESTA settings */
        if(CLOCK_SUCCESS != Clock_DisableSourceInternal(pDrvCtxt->hClient, pSource, CLOCK_FLAG_IS_SET(pSource, SUPPRESSIBLE)))
        {
          return CLOCK_ERROR;
        }       
      }
    }
  }  
  
  for(nCount = 0; nCount < pDrvCtxt->pBSP->nNumCESTA; nCount++)
  {
    pCESTA = pDrvCtxt->pBSP->aCESTA[nCount]; 
    eResult = Clock_CESTADisableDependencies(pCESTA);
    if(CLOCK_SUCCESS != eResult)
    {
      return CLOCK_ERROR;
    }
  }
  
  return CLOCK_SUCCESS;
} /* END Clock_InitCESTA */

