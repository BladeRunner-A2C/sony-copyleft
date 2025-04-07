/*
===========================================================================
*/
/**
  @file swsys_env_uefi_tsens.c

*/
/*
  ====================================================================

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  10/30/17   IH      Added LMH control functions enabling algorithm and setting runtime profile
  06/14/17   jh      Initial revision.

  ====================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>

#include "swsys_env_uefi_tsens.h"
#include "../swsys_logger/swsys_logger.h"
#include <Protocol/EFITsens.h>
#include <Protocol/EFIScm.h>

#include <Include/scm_sip_interface.h>

/*=========================================================================
      Definitions
==========================================================================*/
#define LMH_RUNTIME_PROFILE_ID          1
#define LMH_BOOT_PROFILE_ID             0

#define SCM_MAX_NUM_PARAMETERS          10
#define SCM_MAX_NUM_RESULTS             4

#define TZ_LMH_DCVSH_CONFIG_ID  TZ_SYSCALL_CREATE_SMC_ID(TZ_OWNER_SIP, TZ_SVC_LMH, 0x10)

#define TZ_LMH_DCVSH_CONFIG_PARAM_ID \
  TZ_SYSCALL_CREATE_PARAM_ID_5( \
      TZ_SYSCALL_PARAM_TYPE_BUF_RO, \
      TZ_SYSCALL_PARAM_TYPE_VAL, \
      TZ_SYSCALL_PARAM_TYPE_VAL, \
      TZ_SYSCALL_PARAM_TYPE_VAL, \
      TZ_SYSCALL_PARAM_TYPE_VAL \
      )

//NODE
#define DCVSH_NODE  0x44435653
#define DCVSH_ENABLE                0x454e424c /*ENBL*/
#define LLMCPSILVER 0x6370302d
#define LLMCPGOLD   0x6370312d
#define DCVSH_THERMAL_ALGO          0x54484d4c /*THRM*/

#define GET_PROFILE_REQ_SIZE (10*(sizeof(uint32_t)))
#define CHANGE_PROFILE_REQ_SIZE (sizeof(uint64_t))
/*=========================================================================
      Variables
==========================================================================*/
EFI_TSENS_PROTOCOL *Tsens = NULL;

QCOM_SCM_PROTOCOL  *QcomSCM = NULL;

typedef struct {
  uint32_t            SmcId;
  uint32_t            ParamId;
  uint64_t            Parameters[SCM_MAX_NUM_PARAMETERS];
  uint64_t            Results[SCM_MAX_NUM_RESULTS];
} sip_syscall_req_t;
/* =========================================================================
**  Functions
** =========================================================================*/
uint64_t tsens_pause_group = 0;

void swsys_clear_tsens_pause_time(void){
    tsens_pause_group = 0;
    swsys_debug("Clear Tsens pause group\n");
}

void swsys_set_tsens_pause_time(uint64_t pause_time){
    tsens_pause_group = pause_time;
    swsys_debug("Set Tsens pause group value to %ld\n",tsens_pause_group);
}

uint64_t swsys_get_tsens_pause_time(void){
    swsys_debug("Return Tsens pause group value %ld\n",tsens_pause_group);
    return tsens_pause_group;
}

bool swsys_init_tsens_uefi()
{
  EFI_STATUS status = EFI_SUCCESS;
  if(Tsens) {
    return status;
  }
  status = gBS->LocateProtocol(&gEfiTsensProtocolGuid,
                               NULL,
                               (VOID **)&Tsens);
  if (status != EFI_SUCCESS)
  {
    swsys_error("ERROR: Tsens protocol load failed\n");
    return false;
  }

  swsys_debug("Tsens protocol loaded\n");
  return true;
}

bool swsys_read_tsens_sensor_uefi(uint32_t sensor_id, int32_t* ret_val)
{
  EFI_STATUS status = EFI_SUCCESS;

  status = Tsens->GetTemp(sensor_id, ret_val);
  if (status != EFI_SUCCESS)
  {
    if (status == EFI_UNSUPPORTED)
    {
      swsys_error("ERROR: Tsens sensor 0x%x is dead\n", sensor_id);
    }
    else
    {
      swsys_error("ERROR: Tsens protocol GetTemp failed for sensor 0x%x\n", sensor_id);
      return false;
    }
  }

  return true;
}

bool swsys_read_max_tsens_sensor_uefi(int32_t* ret_val)
{
  EFI_STATUS status = EFI_SUCCESS;

  status = Tsens->GetMaxTemp(ret_val);
  if (status != EFI_SUCCESS)
  {
    if (status == EFI_UNSUPPORTED)
    {
      swsys_error("ERROR: Max Tsens not supported\n");
    }
    else
    {
      swsys_error("ERROR: Tsens protocol GetMaxTemp failed\n");
      return false;
    }
  }

  return true;
}

bool swsys_get_num_of_tsens_sensors_uefi(uint32_t* ret_val)
{
  EFI_STATUS status = EFI_SUCCESS;

  status = Tsens->GetNumSensors(ret_val);
  if (status != EFI_SUCCESS)
  {
    if (status == EFI_UNSUPPORTED)
    {
      swsys_error("ERROR: Numb of Tsens not supported\n");
    }
    else
    {
      swsys_error("ERROR: Tsens protocol GetNumSensors failed\n");
      return false;
    }
  }

  return true;
}

bool init_SCM()
{
  EFI_STATUS status = EFI_SUCCESS;

  status = gBS->LocateProtocol(&gQcomScmProtocolGuid,
                               NULL,
                               (VOID **)&QcomSCM);
  if ((status != EFI_SUCCESS) || (QcomSCM == NULL))
  {
    swsys_error("ERROR: SCM protocol load failed\n");
    return false;
  }
  return true;
}

int set_LMH_profile(uint64_t profile)
{
  EFI_STATUS status = EFI_SUCCESS;
  sip_syscall_req_t   sipReq = {0};

  tz_lmh_change_profile_req_t *tzReq;
  tz_syscall_rsp_t            *tzRes;

  if (!QcomSCM) {
    swsys_error("QcomSCM protocol not initialized\n");
    return 0;
  }
  
  sipReq.SmcId = TZ_LMH_CHANGE_PROFILE_ID;
  sipReq.ParamId = TZ_LMH_CHANGE_PROFILE_PARAM_ID;
  
  tzReq = (tz_lmh_change_profile_req_t *)sipReq.Parameters;
  tzRes = (tz_syscall_rsp_t *) sipReq.Results;
  tzReq->profile = profile;

  status = QcomSCM->ScmSipSysCall(QcomSCM, sipReq.SmcId, sipReq.ParamId, sipReq.Parameters, sipReq.Results);

  if (status == EFI_SUCCESS)
  {
    if(tzRes->status == 1) {
      swsys_error("LMH profile changed to %d successfully!\n", profile);
      return 1;
    }
  }
  swsys_info("ERROR status: %d: set_LMH_profile\n", status);
  return 0;
}

int set_LMH_dcvsh(uint32_t node_id, uint32_t algo, uint32_t action, uint32_t val)
{
  EFI_STATUS status = EFI_SUCCESS;
  sip_syscall_req_t   sipReq = {0};
  uint32_t *payload = (uint32_t*)UncachedAllocatePool(sizeof(uint32_t) * 5); 

  tz_syscall_rsp_t            *tzRes;

  if (!QcomSCM) {
    swsys_error("QcomSCM protocol not initialized\n", val);
    return -1;
  }
  sipReq.SmcId = TZ_LMH_DCVSH_CONFIG_ID;
  sipReq.ParamId = TZ_LMH_DCVSH_CONFIG_PARAM_ID;
  
  if (payload) {
	  payload[0] = algo;
      payload[1] = 0;
      payload[2] = action;
      payload[3] = 1;
      payload[4] = val;
  }
  else{
	  return -1;
  }
  tzRes = (tz_syscall_rsp_t *) sipReq.Results;
  sipReq.Parameters[0] = (uint64_t)payload;
  sipReq.Parameters[1] = sizeof(uint32_t) * 5;
  sipReq.Parameters[2] = DCVSH_NODE;
  sipReq.Parameters[3] = node_id;
  sipReq.Parameters[4] = 0;

  status = QcomSCM->ScmSipSysCall(QcomSCM, sipReq.SmcId, sipReq.ParamId, sipReq.Parameters, sipReq.Results);

  if (status == EFI_SUCCESS)
  {
    if(tzRes->status == 1) {
      swsys_error("LMH dcvsh set - %d\n", val);
      return 1;
    }
  } else {
    swsys_error("ERROR status: %d: set_LMH_dcvsh\n", status);
  }
  return 0;
}

bool swsys_set_lmh_runtime_profile_uefi() 
{
  int no_error;

  if (!QcomSCM) {
    init_SCM();
  }
  set_LMH_dcvsh(LLMCPSILVER, DCVSH_THERMAL_ALGO, DCVSH_ENABLE, 1);
  set_LMH_dcvsh(LLMCPGOLD  , DCVSH_THERMAL_ALGO, DCVSH_ENABLE, 1);
  no_error = set_LMH_profile(LMH_RUNTIME_PROFILE_ID);
  if(no_error) {
    return true;
  }
  return false;
}

