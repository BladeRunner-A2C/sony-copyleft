/*===========================================================================
                              <QPPC_dev_test.c>
DESCRIPTION
  This file is the dev test file to test the QPPC read write api's from UEFI side
  and to read the PCC information from PCCT for all the CPU's.

INITIALIZATION AND SEQUENCING REQUIREMENTS

  Copyright (c) 2022 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
  Qualcomm Confidential and Proprietary

===========================================================================*/

/*===========================================================================
                             Edit History

when       who             what, where, why
--------   ---             -------------------------------------------------
28/10/22   saichait        Initial version
===========================================================================*/
#include "QPPC.h"
#include "busywait.h"

volatile int qppcTestFailed = 1;

volatile uint32_t gnCluster = 0, gMaxCores = 12;

extern QPPCBSPType QppcBSP;

/*-----------------------------------------------------------------------*/
/* QPPC test function to test write/read operations.                     */
/*-----------------------------------------------------------------------*/

void QPPC_BIST()
{
  uint32_t nResult;
  QppcQueryParam eQueryParam;
  QppcConfigParam eQppcConfig;
  QPPCResult eResult;
  QppcQueryResultType nQueryRes;
  volatile uint32_t nCore, nFreq;
  //QPPCDriverContext  *pDrvCtxt = QPPC_GetDrvCtxt();
  
  //if (!pDrvCtxt->bBISTEnabled)
  //{
  //  return;
  //}
  
  DEBUG((EFI_D_WARN, "Start PCC Testing... \n"));

  for (nCore = 0; nCore < gMaxCores; nCore++)
  {   
    eQueryParam.id.nCoreid = nCore;
    QPPC_GetConfig(QPPC_QUERY_NUM_PERF_LEVELS, eQueryParam, &nQueryRes);
    
    DEBUG((EFI_D_WARN, "core %d maximum num Of Perf levels are %d.\n", nCore, nQueryRes.Data.nNumPerfLevels));
    
    for (nFreq=4; nFreq < 7; nFreq++)
    {
      
      eQppcConfig.DescPerfLevel.nCoreid = nCore;
      eQppcConfig.DescPerfLevel.nPerfLevel = nFreq;
          
      DEBUG((EFI_D_WARN, "Writing perf level %d to CPU %d.\n", nFreq, nCore));
      
      eResult = QPPC_SetConfig(QPPC_CONFIG_PARAM_DISCRETE_PERF_LEVEL, eQppcConfig, &nResult);
      
      if (eResult != QPPC_SUCCESS)
      {
        DEBUG((EFI_D_WARN, "Write command Failed, stopping the test.\n"));
        
        while(qppcTestFailed)
        {
        }
      }
      
      busywait(5000000);
      
      eQueryParam.id.nCoreid = nCore;
      eResult = QPPC_GetConfig(QPPC_QUERY_UPDATE, eQueryParam, &nQueryRes);
      
      if (eResult != QPPC_SUCCESS)
      {
        DEBUG((EFI_D_WARN, "Read command Failed, stopping the test.\n"));
        
        while(qppcTestFailed)
        {
        }
      }

    }
  }
}
