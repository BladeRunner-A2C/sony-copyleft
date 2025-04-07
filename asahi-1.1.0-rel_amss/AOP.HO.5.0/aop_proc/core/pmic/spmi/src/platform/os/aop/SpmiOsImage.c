/**
 * @file:  SpmiOsImage.c
 * 
 * Copyright (c) 2013-2016 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2024/04/01 02:51:58 $
 * $Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/core/pmic/spmi/src/platform/os/aop/SpmiOsImage.c#1 $
 * $Change: 53033171 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 1/20/15  Multiple bus support
 * 11/3/14  Automatic channel assignment
 * 10/1/13  Initial Version
 */

#include "SpmiOs.h"
#include "SpmiInfo.h"
#include "SpmiOsLogs.h"
#include "SpmiOsTarget.h"
#include "SpmiLogs.h"
#include "time_service.h"
#include <string.h>
#include "SpmiBus.h"
#include "vrm_inc.h"
#include "rex.h"

//******************************************************************************
// Global Data
//******************************************************************************

extern SpmiInfo * pSpmiBlockInfo;

rex_crit_sect_type spmiLock;

//ULogHandle spmiLogHandle;

//******************************************************************************
// Public API Functions
//******************************************************************************

boolean SpmiOs_HandleTransactionError(SpmiDevInfo *pDev, Spmi_Result* rslt, PmicArbCmd cmd, 
                                      uint8 slaveId, uint16 address, uint8 tries)
{
    return FALSE;
}

void SpmiOs_Wait(uint32 us)
{
    busywait( us );
}

Spmi_Result SpmiOs_Malloc(uint32 size, void** buf)
{
    *buf = malloc(size);
    if(*buf != NULL) {
        memset( *buf, 0, size );
        return SPMI_SUCCESS;
    }    
    
    return SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED;
}

Spmi_Result SpmiOs_Free(void* buf)
{
    return SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED;
}


uint64 SpmiOs_GetTimeTick(void)
{
    return time_service_now();
}

SpmiOs_ClkStatus SpmiOs_GetSerialClkState(SpmiDevInfo *pDev)
{
    return SPMI_CLK_STATUS_NOT_SUPPORTED;
}

SpmiOs_ClkStatus SpmiOs_GetAhbClkState(SpmiDevInfo *pDev)
{
    return SPMI_CLK_STATUS_NOT_SUPPORTED;
}

Spmi_Result SpmiOs_Lock(void)
{
    Spmi_Result result = SPMI_SUCCESS;

    rex_enter_crit_sect(&spmiLock);

    return result;
}

Spmi_Result SpmiOs_Unlock(void)
{
    Spmi_Result result = SPMI_SUCCESS;

    rex_leave_crit_sect(&spmiLock);

    return result;
}

boolean SpmiOs_UseHwInterface(PmicArbCmd cmd)
{
    boolean hwInterfaceFlag = FALSE;

    return hwInterfaceFlag; 
}

Spmi_Result SpmiOs_ExecuteCommand(PmicArbCmd cmd, Spmi_AccessPriority priority, uint8 vSlaveId, 
                                  uint16 address, uint8* data, uint32 dataLen, uint32* bytesTransacted)
{
   return SPMI_FAILURE_COMMAND_NOT_SUPPORTED;
}
