/*===========================================================================
                              <QPPC.h>
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
08/09/22   arajashe        Initial version
===========================================================================*/
#ifndef __QPPC_H__
#define __QPPC_H__

#include "stdint.h"
#include "stdbool.h"
#include "QPPCTypes.h"
#include "QPPCInternal.h"
#include "DALSys.h"
#include "Protocol/EFIMBoxIPC.h"
#include "ULogFront.h"
#include "voltage_level.h"
#include "npa.h"

/*=========================================================================
      Macro Definitions
==========================================================================*/

/*
 * Default size of the BIST ULOG log buffer.
 *
 * NOTE: The log size should be specified in powers of 2.
 */
#define QPPC_DEFAULT_LOG_SIZE         4096
#define SIZEOF_ARRAY(a) (sizeof((a))/sizeof((a)[0]))

/*
 * QPPC driver flags
 */
#define QPPC_FLAG_MAP_PCCT_ADDRESS   (1 << 0)
#define QPPC_FLAG_FUSED_OFF_CORE     (1 << 1)
#define QPPC_FLAG_CORE_INITIALIZED   (1 << 2)
#define QPPC_FLAG_STUB_DRIVER        (1 << 3)
#define QPPC_FLAG_CORE_ONDEMAND_INIT (1 << 4)

/**
 * NPA client name used for internal qppc driver clients.
 */
#define QPPC_NPA_CLIENT_NAME  "qppc"

/**
 * Macro lock the mutex.
 */
#define QPPC_LOCK(hLock) DALSYS_SyncEnter(hLock)

/**
 * Macro to free the mutex.
 */
#define QPPC_FREE(hLock) DALSYS_SyncLeave(hLock)

/*
 * QPPCBase
 *
 * Structure for a register base mapping.
 *
 * nPhysAddr  - Physical address to be mapped.
 * nSize      - Size of region to be mapped.
 * pnVirtAddr - Mapped virtual address.
 */
typedef struct QPPCBase
{
  uintptr_t                     nPhysAddr;          /*< Physical address to be mapped */
  uint32_t                      nSize;              /*< Size of region to be mapped */
  uintptr_t                     *pnVirtAddr;        /*< Mapped virtual address */
} QPPCBaseType;

/*
 * QPPCCoreType
 * Structure contain per core context
 */
typedef struct
{
  const char                    *szQppcName;
  const char                    *szPdpName;
  uint32_t             		      nFlags;             /* Per core flags */
  QPPC_HWCommSubSpaceType      *pHWSubspace;      /* HW space */
  uint32_t             		      nMinPerfLevel;      /* Minimum perf level supported */
  uint32_t             		      nMaxPerfLevel;      /* Max number of perf levels enabled by PDP */
  uint32_t             		      nActivePerfLevel;   /* Perf-Level at which a core is running */
  uint32_t                      nAck;               /* wait for read ack */
  mbox_ipc_handle_type 		      MboxHandle;         /* Per core mailbox channel */
  mbox_ipc_rx_notification_cb   MboxCb;             /* per core PDP2AP callack */
  DALSYSSyncObj                 LockObj;            /*< Sync object storage */
  DALSYSSyncHandle              hLock;              /*< Handle to our mutex for Serializing Core functionality */
} QPPCCoreType;

typedef struct _QPPCBSPType
{
  QPPCBaseType                  *aPcctBase;				 /* Array of QPPC base address. */
  uint16_t                      nBases;            /* Number of clusters present in this target. */
  QPPCCoreType                  *aCores;            /* Array of Clusters. */
  uint16_t                      nNumCores;         /* Number of clusters present in this target. */
  uint32_t                      nFlags;            /* per core flags */
  bool                          bDCVSEnabled;      /* DCVS enable / disable state */
  uint32_t                      nDCVSMode;         /* DCVS mode  */
  uint8_t                       nMaxNumCore;       /* Total number of CPU's */
}QPPCBSPType;


typedef struct _QPPCDriverContext
{
  DALSYSSyncObj                 LockObj;                 /* Sync object storage */
  DALSYSSyncHandle              hLock;                   /* Handle to our mutex for Serializing Core functionality */
  ULogHandle                    hLog;                    /* Handle to our ULOG log */
  ULogHandle                    hBISTLog;                /* Handle to our BIST ULOG log */
  uint32_t                      nBISTLogSize;            /* Size of the BIST ULOG log */
  bool                          bBISTEnabled;            /* Flag used to enable the BIST */                                
  uint32_t                      nFlags;                  /* Global flags */
  QPPCBSPType                   *pBSP;                   /* Allocate dynamically based on number of physical CPUs */
  EFI_MBOX_IPC_PROTOCOL         *MBoxHandle;             /* EFI Mailbox handle */
  QPPC_PCCTType                  *pPCCT;                  /* PCCT Table */
}QPPCDriverContext;

/** 
  Register client callback function with QPPC

  @param[in]  pfnCB                 Pointer to callback function.
  @param[in]  nData                 Callback data.

  @par Description
  This function takes callback function pointer and callback data from user and register 
  it with QPPC driver. QPPC driver will invoke callback function when certain events 
  need to process from client.

  @return
  QPPC_SUCCESS       -- Function completed successfully. \n
  QPPC_ERROR         -- Error occurred during the operation.
*/
QPPCResult
QPPC_RegisterCallback (
  PQPPC_CB 				pfnCB,
  QPPC_CBData 			Data
);

/** 
  Query specific data available in PCCT table.

  @param[in]  eQuery                Query type.
  @param[in]  Param                 Query parameters.
  @param[out] pnResult              Query results.

  @par Description
  This function parse PCCT table and get specific configuration queried by user then it return
  query specific data to user.

  @return
  QPPC_SUCCESS        -- Function completed successfully. \n
  QPPC_ERROR          -- Error occurred during the operation.
*/
QPPCResult
QPPC_GetConfig (
  QPPCQueryType         eQuery,
  QppcQueryParam        Param,
  QppcQueryResultType   *pnResult
);

/** 
  Set specific configuration in QPPC.

  @param[in]  eConfig               Set configuration type.
  @param[in]  Param                 configuration parameters.
  @param[out] pnResult              cnfiguration results (optional).

  @par Description
  This function set specific configuration in PCCT table and notify respective PDP
  to process the configuration change.

  @return
  QPPC_SUCCESS        -- Function completed successfully. \n
  QPPC_ERROR          -- Error occurred during the operation.
*/
QPPCResult
QPPC_SetConfig(
  QPPCConfigType        eConfig,
  QppcConfigParam       Param,
  uint32_t              *pnResult
);

/*=========================================================================
**  Function : QPPC_GetDrvCtxt
** =========================================================================*/
/**
  Returns driver context.

  This function is used to get the driver context.


  @return
  Pointer to QPPC driver context.

  @dependencies
  None.
*/

QPPCDriverContext * QPPC_GetDrvCtxt
(
  void
);

/** 
  Initialize QPPC Library

  @param None

  @par Description
  This function fetch PCCT table from shared memory and establish connection with mailbox
  driver for each core.

  @return
  QPPC_SUCCESS        -- Function completed successfully. \n
  QPPC_ERROR          -- Error occurred during the operation.
*/
QPPCResult
QPPC_DriverInit(
  void
);

#endif
