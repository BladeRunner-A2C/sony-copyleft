/*===========================================================================
                              <QPPC.c>
DESCRIPTION
  This file is header for QPPC structures

INITIALIZATION AND SEQUENCING REQUIREMENTS

  Copyright (c) 2022-23 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
  Qualcomm Confidential and Proprietary

===========================================================================*/

/*===========================================================================
                             Edit History

when       who             what, where, why
--------   ---             -------------------------------------------------
08/09/22   saichait        Initial version
===========================================================================*/

#include "QPPC.h"
#include "string.h"
#include "busywait.h"
#include "DALDeviceId.h"
#include "DDIHWIO.h"
#include "DDIPlatformInfo.h"
#include "npa.h"
#include "DebugLib.h"
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>

/*=========================================================================
      Data
==========================================================================*/
#define QPPC_MAX_CH_DELAY             5000
#define QPPC_PCC_CH_STATUS_POLL_DELAY 1
#define QPPC_IGNORE_PERF_TABLE        1

/*
#ifdef ULOG_RT_PRINTF_0
#undef ULOG_RT_PRINTF_0
#undef ULOG_RT_PRINTF_1
#undef ULOG_RT_PRINTF_2
#undef ULOG_RT_PRINTF_3
#undef ULOG_RT_PRINTF_4
#undef ULOG_RT_PRINTF_5

#define ULOG_RT_PRINTF_0(hlog, msg) DEBUG((EFI_D_WARN, msg))
#define ULOG_RT_PRINTF_1(hlog, msg, a1) DEBUG((EFI_D_WARN, msg, a1))
#define ULOG_RT_PRINTF_2(hlog, msg, a1, a2) DEBUG((EFI_D_WARN, msg, a1, a2))
#define ULOG_RT_PRINTF_3(hlog, msg, a1, a2, a3) DEBUG((EFI_D_WARN, msg, a1, a2, a3))
#define ULOG_RT_PRINTF_4(hlog, msg, a1, a2, a3, a4) DEBUG((EFI_D_WARN, msg, a1, a2, a3, a4))
#define ULOG_RT_PRINTF_5(hlog, msg, a1, a2, a3, a4, a5) DEBUG((EFI_D_WARN, msg, a1, a2, a3, a4, a5))

#endif
*/
extern QPPCBSPType QppcBSP;

/* 
 * Main QPPC Driver context
 */
static QPPCDriverContext QPPCDriverCtxt;

/*=========================================================================
      Macros
==========================================================================*/

#define READ_CP15(reg, var) __asm volatile("mrs %0, "#reg : "=r"(var)); 
#define WRITE_CP15(reg, var) __asm volatile("msr "#reg", %0" : : "r" (var));
// PMCNTENSET_EL0 - need to write 0x80000000
// PMCR_EL0 - need to set to 1
#define TIME_SLOT	524288 // 0x80000 - from SVE code
#define DEVICE_CLOCK_FACTOR	0.03665


/*=========================================================================
    Internal Functions
==========================================================================*/
static void QPPC_CalibrationCB ( void );
static QPPCResult QPPC_InitCalibrationCB ( void );
static void printQPPCFields(QPPC_RegSpaceType *pQPPCReg, uint32_t nCore, uint32_t nFlags);
QPPCResult QPPC_InitCPU(uint32_t nCoreMsk);

/*=========================================================================
**  Function : PCC_SendCommand
** =========================================================================*/

void PCC_ClearCommand
(
  QPPCCoreType  *pCore
)
{
  uint32_t nChStatus;
  /*--------------------------------------------------------------------------------------*/
  /* Get the shared memory Base address defined Per Cpu, in each cluster.                */
  /*--------------------------------------------------------------------------------------*/
  QPPC_GCCSharedMemoryType *pGCCMem =
          (QPPC_GCCSharedMemoryType *) pCore->pHWSubspace->pSharedMemBase;
          
  /*-----------------------------------------------------------------------*/
  /* Variable to read the MailBox channel status.                          */
  /*-----------------------------------------------------------------------*/
  
  QPPC_LOCK(pCore->hLock);
  
  nChStatus = (pGCCMem->nStatus) & 0x1;

  /* Clear channel status */
  if (nChStatus != QPPC_PCC_CH_READY)
  {
    pGCCMem->nStatus |=  QPPC_PCC_CH_READY;
  }
  
  QPPC_FREE(pCore->hLock);

}

/*=========================================================================
**  Function : PCC_SendCommand
** =========================================================================*/

QPPCResult PCC_SendCommand
(
  uint16_t  nCommand, 
  QPPCCoreType  *pCore
)
{
  QPPCResult eResult = QPPC_SUCCESS;
  mbox_ipc_err_type mbox_status = MBOX_IPC_STATUS_FAILURE;
  QPPCDriverContext *pDrvCtxt = QPPC_GetDrvCtxt();
  uint32_t nChStatus, nDelay = QPPC_MAX_CH_DELAY;
  /*--------------------------------------------------------------------------------------*/
  /* Get the shared memory Base address defined Per Cpu, in each cluster.                */
  /*--------------------------------------------------------------------------------------*/
  QPPC_GCCSharedMemoryType *pGCCMem =
          (QPPC_GCCSharedMemoryType *) pCore->pHWSubspace->pSharedMemBase;

  /*-----------------------------------------------------------------------*/
  /* Variable to read the MailBox channel status.                          */
  /*-----------------------------------------------------------------------*/
  
  QPPC_LOCK(pCore->hLock);

  /*-----------------------------------------------------------------------*/
  /* Check whether the channel is free,                                    */
  /* if not wait for the timeout of one second is reached.                 */
  /*-----------------------------------------------------------------------*/
  
  nChStatus = (pGCCMem->nStatus) & 0x1;
  
  while (nChStatus != QPPC_PCC_CH_READY && --nDelay)
  {
    busywait(QPPC_PCC_CH_STATUS_POLL_DELAY);
    nChStatus = (pGCCMem->nStatus) & 0x1;
  }
  
  if (nChStatus != QPPC_PCC_CH_READY)
  {
    ULOG_RT_PRINTF_0(pDrvCtxt->hLog, "PCC channel is not ready, return error \n");
    QPPC_FREE(pCore->hLock);
    
    return QPPC_ERROR;
  }

  ULOG_RT_PRINTF_0(pDrvCtxt->hLog, "PCC channel is Ready.\n");
  
  /*-----------------------------------------------------------------------*/
  /* Update the nCommand bit.                                               */
  /*-----------------------------------------------------------------------*/
  pGCCMem->nCommand = (UINT16) nCommand;

  /*-----------------------------------------------------------------------*/
  /* Mark the channel as busy.                                             */
  /*-----------------------------------------------------------------------*/
  pGCCMem->nStatus = (pGCCMem->nStatus) & 0xFFFE;

  /*-----------------------------------------------------------------------*/
  /* Send the IPC to HW Mailbox driver.                                    */
  /*-----------------------------------------------------------------------*/
  pDrvCtxt->MBoxHandle->MailBoxIPCSend(pCore->MboxHandle,
                              NULL, 0x1, 0, 0, &mbox_status);

  
    /*-----------------------------------------------------------------------*/
  /* Check the nStatus of the ipc transfer to HW MailBox driver.            */
  /*-----------------------------------------------------------------------*/
  if (mbox_status == MBOX_IPC_STATUS_SUCCESS)
  {
    nChStatus = (pGCCMem->nStatus) & 0x1;
    nDelay = QPPC_MAX_CH_DELAY;
    
    while(nChStatus != QPPC_PCC_CH_READY && --nDelay)
    {
      busywait(QPPC_PCC_CH_STATUS_POLL_DELAY);
      nChStatus = (pGCCMem->nStatus) & 0x1;
    }
    
    if (nChStatus == QPPC_PCC_CH_READY)
    {
      eResult = QPPC_SUCCESS;
    }
    else
    {
      ULOG_RT_PRINTF_0(pDrvCtxt->hLog, "PDP is not responding\n");
      /* TBD: Mark channel free if core is not initialized */
      if (!(pCore->nFlags & QPPC_FLAG_CORE_INITIALIZED))
      {
        pGCCMem->nStatus = (pGCCMem->nStatus) | 0x1;
      }
      eResult = QPPC_ERROR;
    }
  }
  else
  {
    DALSYS_LogEvent (
      DALDEVICEID_QPPC, DALSYS_LOGEVENT_ERROR,
      "PCC_SendCommand(): mbox_ipc_send() returned a failed nStatus: %d",
      mbox_status);

    eResult = QPPC_ERROR;
  }
  
  QPPC_FREE(pCore->hLock);
  
	return eResult;
} /* END PCC_SendCommand */

/*=========================================================================
**  Function : QPPC_SetDescreteFreq
** =========================================================================*/
/**
  See QPPC.h
*/

static QPPCResult QPPC_SetDescreteFreq
(
  uint32_t  nCore,
  uint32_t  nFreqHz
)
{
  QPPCDriverContext *pDrvCtxt = QPPC_GetDrvCtxt();
  QPPCCoreType *pCore = NULL;
  QPPC_GCCSharedMemoryType *pGCCMem;
  QPPCResult eResult = QPPC_SUCCESS;
  uint32_t nAbstractRation;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/
  if (nCore > pDrvCtxt->pBSP->nNumCores)
  {
    return QPPC_ERROR_INVALID_PARAMETER;
  }

  pCore = &pDrvCtxt->pBSP->aCores[nCore];

  /* TODO:  return error in Final submissions, */
  if(!(pCore->nFlags & QPPC_FLAG_CORE_INITIALIZED))
  {
    return QPPC_SUCCESS;
  }
  /*--------------------------------------------------------------------------------------*/
  /* Get the shared memory Base address defined Per Cpu, in each cluster.                */
  /*--------------------------------------------------------------------------------------*/
  pGCCMem = (QPPC_GCCSharedMemoryType *)  pCore->pHWSubspace->pSharedMemBase;

  /*-----------------------------------------------------------------------*/
  /* Writing the values in QPPC shared memory registers.                   */
  /*-----------------------------------------------------------------------*/
  nAbstractRation = pGCCMem->QPPCReg.nNominalFrequency / pGCCMem->QPPCReg.nNominalPerformance;
  
  pGCCMem->QPPCReg.nDesiredPerformance = nFreqHz / nAbstractRation;

  /*------------------------------------------------------------------------*/
  /* Check the MailBox channel nStatus and send the IPC to HW Mailbox driver.*/
  /*------------------------------------------------------------------------*/
  eResult = PCC_SendCommand(QPPC_PCC_WRITE_COMMAND, pCore);

  if (eResult != QPPC_SUCCESS)
  {
    DALSYS_LogEvent (
      DALDEVICEID_QPPC,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "PCC_WriteCommand failed.");

    return eResult;
  }

  return QPPC_SUCCESS;

} /* END QPPC_SetDescreteFreq */

/*=========================================================================
**  Function : QPPC_SetDescretePerfLevel
** =========================================================================*/
/**
  See QPPC.h
*/

static QPPCResult QPPC_SetDescretePerfLevel
(
  uint32_t  nCore,
  uint32_t  nPerfLevel
)
{
  QPPCDriverContext *pDrvCtxt = QPPC_GetDrvCtxt();
  QPPCCoreType *pCore = NULL;
  QPPC_GCCSharedMemoryType *pGCCMem;
  QPPCResult eResult = QPPC_SUCCESS;
  uint32_t nAbstractRation;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/
  if (nCore > pDrvCtxt->pBSP->nNumCores)
  {
    return QPPC_ERROR_INVALID_PARAMETER;
  }
  
  pCore = &pDrvCtxt->pBSP->aCores[nCore];
  
  if (nPerfLevel >= pCore->nMaxPerfLevel)
  {
    return QPPC_ERROR_INVALID_PARAMETER;
  }
  
  /* TODO:  return error in Final submissions, */
  if(!(pCore->nFlags & QPPC_FLAG_CORE_INITIALIZED))
  {
    return QPPC_SUCCESS;
  }
  /*--------------------------------------------------------------------------------------*/
  /* Get the shared memory Base address defined Per Cpu, in each cluster.                */
  /*--------------------------------------------------------------------------------------*/
  pGCCMem = (QPPC_GCCSharedMemoryType *)  pCore->pHWSubspace->pSharedMemBase;

  /*-----------------------------------------------------------------------*/
  /* Writing the values in QPPC shared memory registers.                   */
  /*-----------------------------------------------------------------------*/
  nAbstractRation = pGCCMem->QPPCReg.nNominalFrequency / pGCCMem->QPPCReg.nNominalPerformance;

  pGCCMem->QPPCReg.nDesiredPerformance = pGCCMem->QPPCReg.QPPCExt.nPerfFrequency[nPerfLevel] / nAbstractRation;

  /*------------------------------------------------------------------------*/
  /* Check the MailBox channel nStatus and send the IPC to HW Mailbox driver.*/
  /*------------------------------------------------------------------------*/
  eResult = PCC_SendCommand(QPPC_PCC_WRITE_COMMAND, pCore);

  if (eResult != QPPC_SUCCESS)
  {
    DALSYS_LogEvent (
      DALDEVICEID_QPPC,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "PCC_WriteCommand failed.");

    return eResult;
  }
  
  return QPPC_SUCCESS;

} /* END QPPC_SetDescretePerfLevel */

/*=========================================================================
**  Function : QPPC_SetAutonomousPerfLevel
** =========================================================================*/
/**
  See QPPC.h
*/

static QPPCResult QPPC_SetAutonomousPerfLevel
(
  uint32_t  nCore,
  uint32_t  nMinPerfLevel,
  uint32_t  nMaxPerfLevel
)
{
  QPPCDriverContext *pDrvCtxt = QPPC_GetDrvCtxt();
  QPPC_GCCSharedMemoryType *pGCCMem;
  QPPCCoreType  *pCore = NULL;
  QPPCResult eResult = QPPC_SUCCESS;
 
  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/
  if (nCore > pDrvCtxt->pBSP->nNumCores)
  {
    return QPPC_ERROR_INVALID_PARAMETER;
  }
  
  pCore = &pDrvCtxt->pBSP->aCores[nCore];
  pGCCMem = (QPPC_GCCSharedMemoryType *) pCore->pHWSubspace->pSharedMemBase;

  /*-----------------------------------------------------------------------*/
  /* Writing the values in QPPC shared memory registers.                   */
  /*-----------------------------------------------------------------------*/
  pGCCMem->QPPCReg.nMaximumPeformance =
      nMaxPerfLevel;
      
  pGCCMem->QPPCReg.nMinimumPerformance =
      nMinPerfLevel;

  /*------------------------------------------------------------------------*/
  /* Check the MailBox channel nStatus and send the IPC to HW Mailbox driver.*/
  /*------------------------------------------------------------------------*/
  eResult = PCC_SendCommand(QPPC_PCC_WRITE_COMMAND, pCore);
  if (eResult != QPPC_SUCCESS)
  {
    DALSYS_LogEvent (
      DALDEVICEID_QPPC,
      DALSYS_LOGEVENT_FATAL_ERROR,
      "PCC_WriteCommand failed.");

    return eResult;
  }
  
	return QPPC_SUCCESS;
} /* END QPPC_SetAutonomousPerfLevel */


/*=========================================================================
      API Functions
==========================================================================*/
/**
 Description is in QPPC.h
 */

QPPCResult
QPPC_RegisterCallback
(
  PQPPC_CB             pfnCB,
  QPPC_CBData          nData
)
{
  //TO DO: Register a client call back with the QPPC driver.
  return QPPC_SUCCESS;
} /* END QPPC_RegisterCallback */

/**
 Description is in QPPC.h
 */

QPPCResult
QPPC_GetConfig 
(
  QPPCQueryType         eQuery,
  QppcQueryParam        Param,
  QppcQueryResultType   *pnResult
)
{
  QPPCDriverContext  *pDrvCtxt = QPPC_GetDrvCtxt();
  QPPCResult          eResult = QPPC_SUCCESS;
  QPPCCoreType       *pCore = NULL;
  QPPC_GCCSharedMemoryType *pGCCMem;
  uint32_t nPerf;
  UINT64 lmts_counter_pre, lmts_counter_post = 0; 
  volatile static UINT64 lmts_timer_pre, lmts_timer_post = 0; 
  UINT64 val = 1;

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/
  if ((eQuery > QPPC_TOTAL_NUM_OF_QUERIES) || !pnResult)
  {
    return QPPC_ERROR_INVALID_PARAMETER;
  }
  
  if (Param.id.nCoreid >= pDrvCtxt->pBSP->nNumCores)
  {
    return QPPC_ERROR_INVALID_PARAMETER;
  }
  
  if (pDrvCtxt->pBSP->nFlags & QPPC_FLAG_STUB_DRIVER)
  {
    return QPPC_ERROR_UNSUPPORTED;
  }
  
  pCore = &(pDrvCtxt->pBSP->aCores[Param.id.nCoreid]);
  pGCCMem = (QPPC_GCCSharedMemoryType *) pCore->pHWSubspace->pSharedMemBase;

  switch (eQuery)
  {
    case QPPC_QUERY_NUM_PERF_LEVELS:
	    /*-----------------------------------------------------------------------*/
      /* Get the maximum number of perf levels per specific core.              */
      /*-----------------------------------------------------------------------*/
      if(pCore->nFlags & QPPC_FLAG_CORE_INITIALIZED)
      {
        pnResult->Data.nNumPerfLevels = pCore->nMaxPerfLevel;
      }
      else if(pCore->nFlags & QPPC_FLAG_FUSED_OFF_CORE)
      {
        pnResult->Data.nNumPerfLevels = 0;
      }
      /* ondemand initialization of core if it is not Initialized yet */
      else
      {
        ULOG_RT_PRINTF_0(pDrvCtxt->hLog,"core is initializing at on-demand \n");
        QPPC_InitCPU(1 << Param.id.nCoreid);
        if(pCore->nFlags & QPPC_FLAG_CORE_INITIALIZED)
        {
          pnResult->Data.nNumPerfLevels = pCore->nMaxPerfLevel;
        }
        else
        {
          ULOG_RT_PRINTF_0(pDrvCtxt->hLog,"core is failed to initialize at on-demand \n");
          eResult = QPPC_ERROR_NOT_FOUND;
        }
      }
      break;

    case QPPC_QUERY_PERF_LEVEL_FREQ_HZ:

      nPerf = Param.nPerfData.nPerfLevel;
	    /*-----------------------------------------------------------------------*/
      /* Get the Frequency in Hz per specific core.                            */
      /*-----------------------------------------------------------------------*/
      if(pCore->nFlags & QPPC_FLAG_CORE_INITIALIZED)
      {
        pnResult->Data.nPerfLevelFreqHz = pGCCMem->QPPCReg.QPPCExt.nPerfFrequency[nPerf];
      }
      else if(pCore->nFlags & QPPC_FLAG_FUSED_OFF_CORE)
      {
        ULOG_RT_PRINTF_0(pDrvCtxt->hLog," core is fused off");
        pnResult->Data.nPerfLevelFreqHz = 0;
      }
      else
      {
        ULOG_RT_PRINTF_0(pDrvCtxt->hLog," not found...");
        eResult = QPPC_ERROR_NOT_FOUND;
      }
      break;

    case QPPC_QUERY_DFS_ENABLED:

      /*-----------------------------------------------------------------------*/
      /* Get the DFS Enabled/Disabled.                                         */
      /*-----------------------------------------------------------------------*/
      pnResult->Data.bDFSEnabled = true;
      break;

    case QPPC_QUERY_DFS_MODE:

      /*-----------------------------------------------------------------------*/
      /* Get the DFS mode.                                                     */
      /*-----------------------------------------------------------------------*/
      pnResult->Data.nDFSMode = 0;
      break;
      
    case QPPC_QUERY_UPDATE:
      eResult = PCC_SendCommand(QPPC_PCC_READ_COMMAND, pCore);
      printQPPCFields(&pGCCMem->QPPCReg, Param.id.nCoreid, QPPC_IGNORE_PERF_TABLE);
      break;
      
    case QPPC_QUERY_ACTIVE_FREQ:     //To Do QPPC_QUERY_ACTIVE_FREQ
      /*-----------------------------------------------------------------------*/
      /* Get the DFS mode.                                                     */
      /*-----------------------------------------------------------------------*/
      
        WRITE_CP15(PMCR_EL0,val);
        val = 0x80000000;
        WRITE_CP15(PMCNTENSET_EL0, val);
        READ_CP15(CNTPCT_EL0, lmts_timer_pre);
        READ_CP15(PMCCNTR_EL0, lmts_counter_pre);

        while(lmts_timer_post < lmts_timer_pre+TIME_SLOT){
          READ_CP15(CNTPCT_EL0, lmts_timer_post);
        }
        READ_CP15(PMCCNTR_EL0, lmts_counter_post);

        pnResult->Data.nActivePerfFreqHz=(lmts_counter_post-lmts_counter_pre)*DEVICE_CLOCK_FACTOR*1000;
      
      break;
    case QPPC_QUERY_MAX_NUM_CORES:
      
      /*-----------------------------------------------------------------------*/
      /* Get the maximum number of cores present in the device.              */
      /*-----------------------------------------------------------------------*/
      pnResult->Data.nMaxNumCores = pDrvCtxt->pBSP->nNumCores;
      break;

    default:
      eResult = QPPC_ERROR_NOT_FOUND;
      break;
  }

  return eResult;
  
} /* END QPPC_GetConfig */

/**
 Description is in QPPC.h
 */

QPPCResult
QPPC_SetConfig
(
  QPPCConfigType        eConfig,
  QppcConfigParam       configParam,
  uint32_t              *pnResult
)
{
  QPPCResult eResult = QPPC_SUCCESS;
  QPPCDriverContext  *pDrvCtxt = QPPC_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Validate arguments.                                                   */
  /*-----------------------------------------------------------------------*/
  if ((eConfig > QPPC_CONFIG_PARAM_TOTAL_PERF_LEVEL) || !pnResult)
  {
    return QPPC_ERROR_INVALID_PARAMETER;
  }
  
  if (pDrvCtxt->pBSP->nFlags & QPPC_FLAG_STUB_DRIVER)
  {
    return QPPC_ERROR_UNSUPPORTED;
  }

  switch (eConfig)
  {
    case QPPC_CONFIG_PARAM_DISCRETE_PERF_LEVEL:

	  /*-----------------------------------------------------------------------*/
      /* Set the Descrete PerfLevel at which a particular Core needs to run.   */
      /*-----------------------------------------------------------------------*/
      eResult = QPPC_SetDescretePerfLevel(configParam.DescPerfLevel.nCoreid, 
                                          configParam.DescPerfLevel.nPerfLevel);
      if (eResult != QPPC_SUCCESS)
      {
        DALSYS_LogEvent (
          DALDEVICEID_QPPC,
          DALSYS_LOGEVENT_FATAL_ERROR,
          "QPPC_SetDescretePerfLevel failed.");

        return eResult;
      }
      break;

    case QPPC_CONFIG_PARAM_DISCRETE_FREQUENCY:

	  /*-----------------------------------------------------------------------*/
      /* Set the Descrete PerfLevel at which a particular Core needs to run.   */
      /*-----------------------------------------------------------------------*/
      eResult = QPPC_SetDescreteFreq(configParam.DescPerfLevel.nCoreid,
                                          configParam.DescPerfLevel.nFreqHz);
      if (eResult != QPPC_SUCCESS)
      {
        DALSYS_LogEvent (
          DALDEVICEID_QPPC,
          DALSYS_LOGEVENT_FATAL_ERROR,
          "QPPC_SetDescreteFreq failed.");

        return eResult;
      }
      break;

    case QPPC_CONFIG_PARAM_AUTONOMOUS_PERF_LEVEL:

	  /*-----------------------------------------------------------------------*/
      /* Set the Autonomous PerfLevel at which a particular Core needs to run. */
      /*-----------------------------------------------------------------------*/
      eResult = QPPC_SetAutonomousPerfLevel(configParam.AutoPerfLevel.nCoreid,
                                            configParam.AutoPerfLevel.nMinPerfLevel,
                                            configParam.AutoPerfLevel.nMaxPerfLevel);
      if (eResult != QPPC_SUCCESS)
      {
        DALSYS_LogEvent (
          DALDEVICEID_QPPC,
          DALSYS_LOGEVENT_FATAL_ERROR,
          "QPPC_SetAutonomousPerfLevel failed.");

        return eResult;
      }  
      break;

    default:
      *pnResult = 0;
      eResult = QPPC_ERROR_NOT_FOUND;
      break;
  }
  return eResult;
} /* END QPPC_SetConfig */



/*=========================================================================
**  Function : QPPC_GetDrvCtxt
** =========================================================================*/
/**
  See QPPC.h
*/

QPPCDriverContext * QPPC_GetDrvCtxt
(
  void
)
{
  return &QPPCDriverCtxt;

} /* END of QPPC_GetDrvCtxt */


/*=========================================================================
**  Function : Qppc_MapPcctBaseAddr
** =========================================================================*/
/**
  Maps the physical PCCT base address.

  This function maps the physical PCCT base address to
  PCCT object in DriverContext structure.

  @return
  QPPC_SUCCESS -- Initialization was successful.
  QPPC_ERROR -- Initialization failed.

  @dependencies
  None.
*/

static QPPCResult QPPC_InitBases
(
  void
)
{
  QPPCDriverContext  *pDrvCtxt = QPPC_GetDrvCtxt();
  QPPCBaseType        *pBase;
  QPPCResult eResult = QPPC_SUCCESS;
  DalDeviceHandle    *phHWIO = NULL;

  /*-----------------------------------------------------------------------*/
  /* Attach to HWIO.                                                       */
  /*-----------------------------------------------------------------------*/
  pBase = QppcBSP.aPcctBase;
  
  if (pDrvCtxt->pBSP->nFlags & QPPC_FLAG_MAP_PCCT_ADDRESS)
  {
    DAL_DeviceAttach(DALDEVICEID_HWIO, &phHWIO);
    if (phHWIO == NULL)
    {
      ULOG_RT_PRINTF_0(pDrvCtxt->hLog,"Failed to get HWIO handle\n");
      return QPPC_ERROR;
    }
    
    /*-----------------------------------------------------------------------*/
    /* Map QPPC base region                                                  */
    /*-----------------------------------------------------------------------*/
    
    DalHWIO_MapRegionByAddress(
      phHWIO, (uint8 *)pBase->nPhysAddr, (uint8 **)pBase->pnVirtAddr);
      
    if (eResult != QPPC_SUCCESS)
    {
      ULOG_RT_PRINTF_0(pDrvCtxt->hLog,"Failed to map region\n");
      DALSYS_LogEvent(
        DALDEVICEID_QPPC, DALSYS_LOGEVENT_FATAL_ERROR,
        "QPPC_MapPcctBaseAddr failed.");
        return QPPC_ERROR;
    }
    /*------------------------------------------------------------------------*/
    /* Assign the QPPC base region to PCCT object in DriverContext structure. */
    /*------------------------------------------------------------------------*/
    pDrvCtxt->pPCCT = (QPPC_PCCTType *)pBase->pnVirtAddr;
  }
  else
  {
    pDrvCtxt->pPCCT = (QPPC_PCCTType *)pBase->nPhysAddr;
  }
  
  return QPPC_SUCCESS;
} /* END QPPC_MapPcctBaseAddr */

QPPCResult
QPPC_InitCPU
(
  uint32_t nCoreMsk
)
{
  QPPCCoreType    *pCore = NULL;
  QPPCDriverContext *pDrvCtxt = QPPC_GetDrvCtxt();
  QPPCBSPType       *pBSP = pDrvCtxt->pBSP;
  QPPC_PCCTType     *pPcct = pDrvCtxt->pPCCT;
  uint32_t         nCore = 0;
  EFI_STATUS       nStatus = EFI_SUCCESS;
  mbox_ipc_open_config_type       MboxConfig;
  mbox_ipc_err_type Mboxstatus = MBOX_IPC_STATUS_FAILURE;
  QPPCResult       result =0;
  GASType         *pDoorbellReg;
  
  /* Get MBOX Handle if it not initialized */
  if (pDrvCtxt->MBoxHandle == NULL)
  {
    nStatus = gBS->LocateProtocol(&gEfiMBoxIPCProtocolGuid, NULL, (VOID **)&pDrvCtxt->MBoxHandle);
    if (pDrvCtxt->MBoxHandle == NULL || (EFI_SUCCESS != nStatus))
    {
      ULOG_RT_PRINTF_0(pDrvCtxt->hLog,"Failed to get EFI Mailbox handle\n");  
      return QPPC_ERROR;
    }
  }
  /*----------------------------------------------------------------------------------------*/
  /* Iterate through all the cores and store the perf levels supported per core.         */
  /*----------------------------------------------------------------------------------------*/
  for (nCore = 0; nCore < pBSP->nNumCores; nCore++)
  {
    /* Initialize only required cores */
    if ((nCoreMsk & (1 << nCore)) == 0)
    {
      continue;
    }
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog,"QPPC_InitCPU %d \n", nCore);
    /* Map the per core HW Subspace */
    pCore = &pBSP->aCores[nCore];
    pCore->pHWSubspace = &pPcct->HWSubspace[nCore];
    /*--------------------------------------------------------------------------------------*/
    /* Get the shared memory Base address defined Per Cpu, in each cluster.                 */
    /*--------------------------------------------------------------------------------------*/
    QPPC_GCCSharedMemoryType *pGCCMem = 
                    (QPPC_GCCSharedMemoryType *) pCore->pHWSubspace->pSharedMemBase;

    /* This core is fused off */
    if(pGCCMem == NULL)
    {
      pCore->nFlags |= QPPC_FLAG_FUSED_OFF_CORE;
      continue;
    }
    
    /* Create Mutex to synchronize PCCT communication */
    if (DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE,
                         &pCore->hLock, &pCore->LockObj))
    {
      DALSYS_LogEvent(
        DALDEVICEID_QPPC, DALSYS_LOGEVENT_FATAL_ERROR,
        "DALSYS_SyncCreate failed.");

      return QPPC_ERROR;
    }
    /*--------------------------------------------------------------------------------------*/
    /* Get the address of doorbell register space Per Cpu, in each cluster.                 */
    /*--------------------------------------------------------------------------------------*/
    pDoorbellReg = &pCore->pHWSubspace->DoorbellRegister;
    
    /* This is to verify the Doorbell Register address. */
    if (pDoorbellReg->nAddress == 0x0)
    {
      DALSYS_LogEvent(
        DALDEVICEID_QPPC, DALSYS_LOGEVENT_FATAL_ERROR,
        "Address of doorbell register is NULL.");

      continue;
    }
    
    /*
     * Initialize mailbox channel 
     */
    MBOX_IPC_OPEN_CONFIG_INIT(MboxConfig);
    /* TODO: Switch to PCCT based channel opening */
    //MboxConfig.remote_ss = (char *)pCore->szPdpName;
    MboxConfig.name = pCore->szQppcName;
    MboxConfig.notify_rx = NULL;
    MboxConfig.send_timeout = 0;
    MboxConfig.send_address = pDoorbellReg->nAddress;
    
    if(pCore->MboxHandle == NULL)
    {
      pDrvCtxt->MBoxHandle->MailBoxIPCOpen(&MboxConfig, & pCore->MboxHandle, &Mboxstatus);
      if (Mboxstatus != MBOX_IPC_STATUS_SUCCESS)
      {
          ULOG_RT_PRINTF_0(pDrvCtxt->hLog,"Failed to open mailbox channel \n");
          pCore->nFlags = 0;        
          //return QPPC_ERROR;
          continue;
      }
    }    
    /*
     * Send READ command to detect perf level table
     */
    result = PCC_SendCommand(QPPC_PCC_READ_COMMAND, pCore);
    
    if(result == QPPC_SUCCESS)
    {

      ULOG_RT_PRINTF_0(pDrvCtxt->hLog,"============================ \n");
      ULOG_RT_PRINTF_0(pDrvCtxt->hLog,"Dumping QPPC Register Values \n");
      ULOG_RT_PRINTF_0(pDrvCtxt->hLog,"============================ \n");
      
      ULOG_RT_PRINTF_2(pDrvCtxt->hLog,"core %d pGCCMem address 0x%x\n", nCore,  pGCCMem);
      ULOG_RT_PRINTF_0(pDrvCtxt->hLog,"Dumping QPPC Register Values \n");
      printQPPCFields(&pGCCMem->QPPCReg, nCore, 0);

      pCore->nMinPerfLevel = 0;
      pCore->nMaxPerfLevel = pGCCMem->QPPCReg.QPPCExt.nPerfLevels;
      /* TODO: detect it for active core */
      pCore->nActivePerfLevel = 0;
      pCore->nFlags |= QPPC_FLAG_CORE_INITIALIZED;
    }
    /* Core is not not responding, move to next core.*/
    else
    {
      ULOG_RT_PRINTF_1(pDrvCtxt->hLog,"Core  %d is not responding \n", nCore);
      pCore->nMinPerfLevel = 0;
      pCore->nMaxPerfLevel = 0;
      pCore->nActivePerfLevel = 0;
      pCore->nFlags = 0; //Core is not initialized
      /* Reset PCC command channel */
      PCC_ClearCommand(pCore);
    }
  }

  return QPPC_SUCCESS;
} /* END of QPPC_InitDCVS */

/*=========================================================================
**  Function : QPPC_InitPCCT
** =========================================================================*/
static QPPCResult QPPC_InitPCCT
(
  void
)
{
  QPPCDriverContext  *pDrvCtxt = QPPC_GetDrvCtxt();
  QPPC_GCCSharedMemoryType *pGCCMem;
  QPPC_HWCommSubSpaceType *pHWSubspace;
  uint32_t           *pSignature;
  
  /*-----------------------------------------------------------------------*/
  /* QPPC test function to test write/read operations.                     */
  /*-----------------------------------------------------------------------*/
  if (pDrvCtxt->pPCCT == NULL)
  {
    ULOG_RT_PRINTF_0(pDrvCtxt->hLog,"PCCT Init is failed\n"); 
    return QPPC_ERROR;
  }
  
  /*
   * verify PCCT signature.
   */
  pSignature = (uint32_t *)&pDrvCtxt->pPCCT->nSignature;
  
  if (*pSignature != 0x50434300)
  {
    ULOG_RT_PRINTF_0(pDrvCtxt->hLog,"PCC nSignature is not matching \n"); 
    //return QPCC_ERROR;
  }
  
  ULOG_RT_PRINTF_0(pDrvCtxt->hLog, "PCCT Table \n");  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nSignature : 0x%x\n", *pSignature);
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nLength : 0x%x\n", pDrvCtxt->pPCCT->nLength);
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nRevision : 0x%x\n", pDrvCtxt->pPCCT->nRevision);
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nChecksum : 0x%x\n", pDrvCtxt->pPCCT->nChecksum);
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nOEMRevision : 0x%x\n", pDrvCtxt->pPCCT->nOEMRevision);
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nCreatorId : 0x%x\n", pDrvCtxt->pPCCT->nCreatorId);
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nCreatorRevision : 0x%x\n", pDrvCtxt->pPCCT->nCreatorRevision);
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nFlags : 0x%x\n", pDrvCtxt->pPCCT->nFlags);
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "reserved : 0x%x\n", pDrvCtxt->pPCCT->reserved);
   
  for (int i = 0; i < pDrvCtxt->pBSP->nNumCores; i++)
  {
    pHWSubspace = &pDrvCtxt->pPCCT->HWSubspace[i];
    pGCCMem = (QPPC_GCCSharedMemoryType *) pHWSubspace->pSharedMemBase;
    
    /* Map Core HW space */
    pDrvCtxt->pBSP->aCores[i].pHWSubspace = pHWSubspace;
    
    if(pGCCMem == NULL)
    {
      ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "\n\nCPU %d is fused off \n", i);
      continue;
    }
    
    /* Logs all cores PCCT info */
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "\n\nCPU %d PCC Info \n", i);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nType : 0x%x\n", pDrvCtxt->pPCCT->HWSubspace[i].nType);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nLength : 0x%x\n", pDrvCtxt->pPCCT->HWSubspace[i].nLength);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nPlatformInterrupt : 0x%x\n", pDrvCtxt->pPCCT->HWSubspace[i].nPlatformInterrupt);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nPlatformInterruptFlags : 0x%x\n", pDrvCtxt->pPCCT->HWSubspace[i].nPlatformInterruptFlags);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "reserved : 0x%x\n", pDrvCtxt->pPCCT->HWSubspace[i].reserved);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "pSharedMemBase : 0x%x\n", pDrvCtxt->pPCCT->HWSubspace[i].pSharedMemBase);
    
    ULOG_RT_PRINTF_0(pDrvCtxt->hLog, "Dumping Shared memory structure details: \n");    
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nSignature : 0x%x\n", pGCCMem->nSignature);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nCommand : 0x%x\n", pGCCMem->nCommand);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nStatus : 0x%x\n", pGCCMem->nStatus);
    
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nSharedMemLength : 0x%x\n", pDrvCtxt->pPCCT->HWSubspace[i].nSharedMemLength);
    ULOG_RT_PRINTF_5(pDrvCtxt->hLog, "GAS Structure:\n nAddressSpaceId : 0x%x\n nRegisterBitWidth : 0x%x\n nRegisterBitOffset : 0x%x\n nAccessSize : 0x%x\n nAddress : 0x%x\n", 
              pHWSubspace->DoorbellRegister.nAddressSpaceId,
              pHWSubspace->DoorbellRegister.nRegisterBitWidth, 
              pHWSubspace->DoorbellRegister.nRegisterBitOffset, 
              pHWSubspace->DoorbellRegister.nAccessSize, 
              pHWSubspace->DoorbellRegister.nAddress);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nDoorbellPreserve : 0x%x\n", pHWSubspace->nDoorbellPreserve);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nDoorbellWrite : 0x%x\n", pHWSubspace->nDoorbellWrite);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nNominalLatency : 0x%x\n", pHWSubspace->nNominalLatency);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nMaxPeriodicRate : 0x%x\n", pHWSubspace->nMaxPeriodicRate);
    ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nMinTurnaroundTime : 0x%x\n", pHWSubspace->nMinTurnaroundTime);
  }
  
  ULOG_RT_PRINTF_0(pDrvCtxt->hLog, "END of PCCT Table \n");
  
  
  return QPPC_SUCCESS;
}

/*=========================================================================
**  Function : QPPC_CalibrationCB
** =========================================================================*/
static void 
QPPC_CalibrationCB 
(
  void
)
{
  QPPCResult eResult;
  uint32_t nMask = 0, i;
  QPPCDriverContext *pDrvCtxt = QPPC_GetDrvCtxt();
  QPPCBSPType       *pBSP = pDrvCtxt->pBSP;

  /*-----------------------------------------------------------------------*/
  /* Initialize the target specific details and intialize the DCVS mode.                                 */
  /*-----------------------------------------------------------------------*/
  for(i= 0; i < pBSP->nNumCores; i++)
  {
    if(!(pBSP->aCores[i].nFlags & QPPC_FLAG_CORE_ONDEMAND_INIT))
    {
      nMask |= (1 << i);
    }
  }
  
  eResult = QPPC_InitCPU(nMask);

  if (eResult != QPPC_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_QPPC, DALSYS_LOGEVENT_FATAL_ERROR,
      "QPPC_InitTarget failed.");

  }
}

/*=========================================================================
**  Function : QPPC_InitCalibrationCB
** =========================================================================*/
static QPPCResult QPPC_InitCalibrationCB
(
  void
)
{
  /* TODO: Add calibration NPA event registertion. Then call QPPC_CalibrationCallback when
   * event is received */
  QPPC_CalibrationCB();
  
  return QPPC_SUCCESS;
}

/* =========================================================================
**  Function : QPPC_DriverInit
** =========================================================================*/
/**
  Initialize the QPPC driver.

  This function initializes the QPPC driver, it is the main init entry
  point.

  @return
  QPPC_SUCCESS -- Initialization was successful.
  QPPC_ERROR -- Initialization failed.

  @dependencies
  None.
*/
QPPCResult
QPPC_DriverInit
(
  void
)
{
  QPPCDriverContext  *pDrvCtxt = QPPC_GetDrvCtxt();
  QPPCResult           eResult;

  /*-----------------------------------------------------------------------*/
  /* Initialize the log.                                                   */
  /*-----------------------------------------------------------------------*/
  
  ULogFront_RealTimeInit(&pDrvCtxt->hLog, "Qppc Log",
                         QPPC_DEFAULT_LOG_SIZE,
                         ULOG_MEMORY_LOCAL, ULOG_LOCK_OS);

  ULogCore_HeaderSet(pDrvCtxt->hLog,
                     "Content-Type: text/tagged-log-1.0;");
  
  /*-----------------------------------------------------------------------*/
  /* Create the driver synchronization object.                             */
  /*-----------------------------------------------------------------------*/

  if (DAL_SUCCESS != DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE,
                       &pDrvCtxt->hLock, &pDrvCtxt->LockObj))
  {
    DALSYS_LogEvent(
      DALDEVICEID_QPPC, DALSYS_LOGEVENT_FATAL_ERROR,
      "DALSYS_SyncCreate failed.");

    //return QPPC_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Hookup the references.                                             */
  /*-----------------------------------------------------------------------*/ 
  pDrvCtxt->pBSP = &QppcBSP;
  
  if (pDrvCtxt->pBSP->nFlags & QPPC_FLAG_STUB_DRIVER)
  {
    return QPPC_SUCCESS;
  }
  
  /*-----------------------------------------------------------------------*/
  /* Map physical memory to virtual address.                               */
  /*-----------------------------------------------------------------------*/
  eResult = QPPC_InitBases();
  
  if (eResult != QPPC_SUCCESS)
  {
    DALSYS_LogEvent (
      DALDEVICEID_QPPC, DALSYS_LOGEVENT_FATAL_ERROR,
      "QPPC_InitBases failed.");

    return eResult;
  }
  /*-----------------------------------------------------------------------*/
  /* Initialize PCCT.                                                      */
  /*-----------------------------------------------------------------------*/  
  eResult = QPPC_InitPCCT();
  if (eResult != QPPC_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_QPPC, DALSYS_LOGEVENT_FATAL_ERROR,
      "QPPC_InitPCCT failed.");

    return QPPC_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Register for Caliration callback                                      */
  /*-----------------------------------------------------------------------*/ 
  eResult = QPPC_InitCalibrationCB();

  if (eResult != QPPC_SUCCESS)
  {
    DALSYS_LogEvent(
      DALDEVICEID_QPPC, DALSYS_LOGEVENT_FATAL_ERROR,
      "QPPC_InitCalibrationCB failed.");

    return QPPC_ERROR;
  }

  /* TODO : */
  
  
  return QPPC_SUCCESS;
} /* END QPPC_Init */

void printQPPCFields(QPPC_RegSpaceType *pQPPCReg, uint32_t nCore, uint32_t nFlags)
{
  QPPCDriverContext *pDrvCtxt = QPPC_GetDrvCtxt();
  
  if(pQPPCReg == NULL)
  {
    return;
  }
  
  ULOG_RT_PRINTF_0(pDrvCtxt->hLog, "================================================\n");
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "Dumping QPPC registers for core: %d\n", nCore);
  ULOG_RT_PRINTF_0(pDrvCtxt->hLog,  "================================================\n");

  ULOG_RT_PRINTF_1(pDrvCtxt->hLog, "nHighestPerformance : 0x%x\n", pQPPCReg->nHighestPerformance);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nNominalPerformance : 0x%x\n", pQPPCReg->nNominalPerformance);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "lowest_nonlinear_perf : 0x%x\n", pQPPCReg->nLowestNonlinearPerformance);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nLowestPerformance : 0x%x\n", pQPPCReg->nLowestPerformance);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nGuaranteedPerformance : 0x%x\n", pQPPCReg->nGuaranteedPerformance);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nDesiredPerformance : 0x%x\n", pQPPCReg->nDesiredPerformance);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nMinimumPerformance : 0x%x\n", pQPPCReg->nMinimumPerformance);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nMaximumPeformance : 0x%x\n", pQPPCReg->nMaximumPeformance);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nPerformanceReductionTolerance : 0x%x\n", pQPPCReg->nPerformanceReductionTolerance);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nTimeWindow : 0x%x\n", pQPPCReg->nTimeWindow);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nCounterWraparoundTime : 0x%x\n", pQPPCReg->nCounterWraparoundTime);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nReferencePerformanceCounter : 0x%x\n", pQPPCReg->nReferencePerformanceCounter);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nDeliveredPerformanceCounter : 0x%x\n", pQPPCReg->nDeliveredPerformanceCounter);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nPerformanceLimited : 0x%x\n", pQPPCReg->nPerformanceLimited);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nCppcEnable : 0x%x\n", pQPPCReg->nCppcEnable);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nAutonomousSelectionEnable : 0x%x\n", pQPPCReg->nAutonomousSelectionEnable);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nAutonomousActivityWindow : 0x%x\n", pQPPCReg->nAutonomousActivityWindow);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nEnergyPerformancePreference : 0x%x\n", pQPPCReg->nEnergyPerformancePreference);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nReferencePerformance : 0x%x\n", pQPPCReg->nReferencePerformance);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nLowestFrequency : 0x%x\n", pQPPCReg->nLowestFrequency);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nNominalFrequency : 0x%x\n", pQPPCReg->nNominalFrequency);
  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "QPPCExt: \n nPerfLevels : 0x%x\n", pQPPCReg->QPPCExt.nPerfLevels);
  
  if (!(nFlags & QPPC_IGNORE_PERF_TABLE))
  {
    for (int i = 0; i < pQPPCReg->QPPCExt.nPerfLevels; i++)
    {
      ULOG_RT_PRINTF_2(pDrvCtxt->hLog,  "nPerfFrequency[%d] : 0x%x\n", i, pQPPCReg->QPPCExt.nPerfFrequency[i]);
    }
  }  
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "nLimitReason: %d\n", pQPPCReg->QPPCExt.nLimitReason);
  
  ULOG_RT_PRINTF_0(pDrvCtxt->hLog,  "================================================\n");
  ULOG_RT_PRINTF_1(pDrvCtxt->hLog,  "Dumping QPPC registers for core: %d, is Done.\n", nCore);
  ULOG_RT_PRINTF_0(pDrvCtxt->hLog,  "================================================\n");
  
}