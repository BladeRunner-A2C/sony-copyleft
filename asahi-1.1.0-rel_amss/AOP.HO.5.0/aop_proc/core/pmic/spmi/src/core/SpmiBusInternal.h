/*
  @brief: This module provides an internal the interface to the 
  SPMI bus driver software.
  
  Copyright (c) 2015 by Qualcomm Technologies Incorporated. All Rights Reserved. 
  
  $DateTime: 2024/04/01 02:51:58 $
  $Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/core/pmic/spmi/src/core/SpmiBusInternal.h#1 $
  $Change: 53033171 $ 
  
                               Edit History
  Date      Description
  --------  -------------------------------------------------------------------
  11/10/15  Initial Version
*/
#ifndef SPMIBUSINTERNAL_H
#define SPMIBUSINTERNAL_H

#include "SpmiTypes.h"
#include "SpmiInfo.h"

//******************************************************************************
// Macros / Definitions / Constants
//******************************************************************************

#define NUM_DEBUG_TRANSACTIONS 3
#define NUM_DEBUG_FAILURES 1

typedef enum {
    NOT_SET,
    STARTED,
    FINISHED,
} BusDbgState;

typedef struct {
    uint8 busId;
    uint8 sid;
    uint16 pid;
    uint8 data0;
    Spmi_Result result;
    PmicArbCmd cmd;
    uint8 dataLen;
    uint64 startTime;
    uint32 duration;
    uint8 tries;
    BusDbgState state;
} BusDbgInfo;

typedef struct {
    uint8 busId;
    uint16 channel;
    uint8 mask;
    uint64 startTime;
    uint32 duration;
} IsrDbgInfo;

typedef struct _SpmiBusIsrConfig
{
    SpmiIsr isr;
    const void* ctx;
    uint8 bid;
    uint16 chan;
    uint8 mask;
    uint16 id;
    struct _SpmiBusIsrConfig* next;
} SpmiBusIsrConfig;


typedef struct {
    BusDbgInfo info;
    PmicArbHwStatus hwStatus;
} BusErrDbgInfo;

typedef struct
{
    uint8 busIdx;
    uint8 errorIdx;
    uint8 isrIdx;
    BusDbgInfo busTrans[NUM_DEBUG_TRANSACTIONS];
    BusErrDbgInfo errorTrans[NUM_DEBUG_FAILURES];
    IsrDbgInfo isrTrans[NUM_DEBUG_TRANSACTIONS];
    boolean syncFlag;
} SpmiBusDebugInfo;

typedef struct 
{
    boolean initialized;
    uint16  uid;
    SpmiBusIsrConfig*** isrTable;
    SpmiBusDebugInfo debug;
    SpmiInfo        *pSpmiInfo;
} SpmiDrv;

//******************************************************************************
// Public API Functions
//******************************************************************************

/**
 * @brief Get the SPMI bus information structure
 *
 * This function gets the internal SPMI bus information 
 * structure.
 * 
 * @param[in] vSlaveId   Virtual slave Id of the device (see 
 *                       SpmiEncodeVSid)
 * 
 * @return Pointer to the device info structure, or 
 *         NULL on errror
 */
SpmiDevInfo* SpmiBus_GetDevInfo(uint8 vSlaveId);

/**
 * @brief Get the SPMI bus information structure
 *
 * This function gets the internal SPMI bus information 
 * structure.
 * 
 * @return Pointer to the device info structure, or 
 *         NULL on errror
 */
SpmiInfo* SpmiBus_GetInfo(void);

#endif
