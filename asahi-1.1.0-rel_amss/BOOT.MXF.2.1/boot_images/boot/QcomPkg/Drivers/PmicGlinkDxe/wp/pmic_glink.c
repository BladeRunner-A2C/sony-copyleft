/******************************************************************************
  @file    pmic_glink.c
  @brief   Glink communication layer between ChargerPD and APPS

  DESCRIPTION
  Implemetnation of communication layer between ChargerPD and APPS

  ---------------------------------------------------------------------------
  Copyright (c) 2018 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
  *******************************************************************************
  EDIT HISTORY

  when           who     what, where, why
  --------       ---     -----------------------------------------------------------
  03/07/2018     cs      added ucsi interface support.
=============================================================================*/

// always include this header file at the top

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomLib.h>
#include "Library/SerialPortShLib.h"
#include <Library/QcomTargetLib.h>
#include <api/pmic/pm/pm_uefi.h>
#include <Library/QcomBaseLib.h>
#include <PrintShLib.h>

#include <Library/TimerLib.h>

#include <Library/BaseMemoryLib.h>
#include "string.h"

#include "pmic_glink.h"
//#include "pmic_glink_msg.h"

// glink handle instance
static glink_handle_type pmic_glink_handle;
static glink_open_config_type pmic_glink_cfg_ptr;
static EFI_GLINK_PROTOCOL* g_pmic_glink_protocol;
static glink_link_id_type pmic_glink_id;
static PMIC_GLINK_CONTEXT  pmic_glink_context = { 0 };


#define PMIC_GLINK_MAX_WAIT_COUNT    200//200
#define PMIC_GLINK_WAIT_TIME         1000 * 10//1000 //10 msec
#define PMIC_GLINK_CONNECT_MAX_WAIT_COUNT    1000//1000

//TODO WILL GET FROM APSD LATER
#define DESIGNED_FULL_CAPACITY       51000 //mWh
#define KELVIN_ZERO                  273

static UINT32 pmic_glink_latest_full_capacity = DESIGNED_FULL_CAPACITY;


EFI_STATUS pmic_glink_open(void *context);

static UINT64  GlinkCalculateTimeStampMSec()
{
  UINTN  CpuFrequency = 0;
  UINT64 TotalTicks = 0;
  UINT64 Seconds =0;

  /* Debug Print CPU Frequncey */
  TotalTicks   = GetPerformanceCounter();
  /* Debug Print CPU Frequncey */
  CpuFrequency = GetPerformanceCounterProperties(NULL, NULL);
  Seconds = MultU64x32(TotalTicks, 1000000);
  Seconds = DivU64x32(Seconds, CpuFrequency);
  Seconds /= 1000;

  return Seconds;
}

/* ============================================================================
**  Function : GlinkLocateProtocol
** ========================================================================== */
/**
@brief
GlinkLocateProtocol function locates the glink protocol.
*/
EFI_STATUS GlinkLocateProtocol(void)
{
  EFI_STATUS  Status = EFI_SUCCESS;

  if (g_pmic_glink_protocol == NULL)
  {
    Status = gBS->LocateProtocol(&gEfiGLINKProtocolGuid,
      NULL, (VOID**)&g_pmic_glink_protocol);
  }

  return Status;
}

/*=============================================================================
  FUNCTION pmic_glink_state_change
  =============================================================================*/

static void pmic_glink_state_change
(
glink_handle_type         handle,
const void                *priv,
glink_channel_event_type  event
)
{
  glink_err_type          ret = GLINK_STATUS_FAILURE;
  UINT32 i = 0;
  EFI_STATUS status = EFI_SUCCESS;

  DEBUG((EFI_D_WARN, "pmic_glink_state_change:: got state_change event = %d  \r\n", event));
  if (GLINK_CONNECTED == event)
  {
    pmic_glink_context.IsPMICChannelOpen = TRUE;
    DEBUG((EFI_D_WARN, "pmic_glink_state_change:: IsPMICChannelOpen = %d  \r\n", pmic_glink_context.IsPMICChannelOpen));
    // initialize the rx buffer pool with rx buffers
    for (i = 0; i < PMIC_GLINK_RX_FIFO_DEPTH; i++)
    {
      status = g_pmic_glink_protocol->GlinkQueueRxIntent(pmic_glink_handle, (void*)(&pmic_glink_context), PMIC_GLINK_PKT_SIZE, &ret);
      if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret))
      {
        DEBUG((EFI_D_WARN, "pmic_glink_state_change:: queue Rx Intent failed. status = %r \r\n", status));
        //return EFI_DEVICE_ERROR;
      }
      else
      {
        DEBUG((EFI_D_WARN, "pmic_glink_state_change:: queue Rx Intent success. status = %r \r\n", status));
      }
    }
  }
  else
  {
    pmic_glink_context.IsPMICChannelOpen = FALSE;
    if (event == GLINK_LOCAL_DISCONNECTED)
    {
      //error msg
      DEBUG((EFI_D_WARN, "pmic_glink_state_change:: glink channel local disconnected.  \r\n"));
    }
    else
    {
      g_pmic_glink_protocol->GlinkClose(pmic_glink_handle, &ret);
    }

  }
}

/*=============================================================================
  FUNCTION pmic_glink_rx_done
  =============================================================================*/

EFI_STATUS pmic_glink_rx_done(const void *data, BOOLEAN refill)
{
  glink_err_type  ret;
  EFI_STATUS status = EFI_SUCCESS;
  if (g_pmic_glink_protocol == NULL)
  {
    return EFI_DEVICE_ERROR;
  }
  status = g_pmic_glink_protocol->GlinkRxDone(pmic_glink_handle, data, refill, &ret);

  if (EFI_ERROR(status) || (GLINK_STATUS_SUCCESS != ret))
  {
    //chargerPD todo error msg
    DEBUG((EFI_D_WARN, "pmic_glink_rx_done:: failure status = %x, glink_ret = %d.  \r\n", status, ret));
    return EFI_DEVICE_ERROR;

  }
  return status;
}

/*=============================================================================
  FUNCTION pmic_glink_deinit
  =============================================================================*/

void pmic_glink_deinit(void)
{
  UINT8 count = 0;
  glink_err_type ret;
  EFI_STATUS status = EFI_SUCCESS;
  
  if (g_pmic_glink_protocol == NULL)
  {
    return;
  }
  if (pmic_glink_context.IsPMICChannelOpen)
  {
    g_pmic_glink_protocol->GlinkClose(pmic_glink_handle, &ret);
	if (ret) 
	{
      DEBUG((EFI_D_WARN, "pmic_glink_deinit:: failure glink_ret = %d.  \r\n", ret));
      return;
    }    
    status = g_pmic_glink_protocol->GlinkRxPoll(pmic_glink_handle, &ret);

    while (count < PMIC_GLINK_MAX_WAIT_COUNT)
    {
      gBS->Stall(PMIC_GLINK_WAIT_TIME);

      if (!pmic_glink_context.IsPMICChannelOpen && GLINK_STATUS_SUCCESS == ret && EFI_SUCCESS == status)
      {
        break;
      }
      status = g_pmic_glink_protocol->GlinkRxPoll(pmic_glink_handle, &ret);
      count++;
    }
    if (pmic_glink_context.IsPMICChannelOpen)
    {
      DEBUG((EFI_D_WARN, "pmic_glink_open:: GlinkClose failed. Polling timeout.\r\n"));
      return;
    }
  }
  //chargerpd todo find out when to call this deregister.
  g_pmic_glink_protocol->GlinkDeregisterLinkStateCB(pmic_glink_id.handle, &ret);

}

/*=============================================================================
  FUNCTION pmic_glink_notify_rx
  =============================================================================*/

static void pmic_glink_notify_rx
(
glink_handle_type handle,     /* handle for the glink channel */
const void        *priv,      /* priv client data passed in glink_open */
const void        *pkt_priv,  /* private client data assiciated with the
                                 rx intent that client queued earlier */
const void        *ptr,       /* pointer to the received buffer */
size_t            size,       /* size of the packet */
size_t            intent_used /* size of the intent used for this packet */
)
{
  uint32 indicationType = 0;

  (void)pmic_glink_process_rx_data((PMIC_GLINK_HEADER_TYPE*)ptr, size, &indicationType);
  switch (indicationType)
  {
  case 0x81:
    //check battery count again
    break;
  case 0x80: //get battery status, or //ucsi notification
    break;
  case 0x82: //battery health changed.
    break;
  case 0:
  default:
    pmic_glink_context.RxNotified = TRUE;
    break;
  }
}

static void pmic_glink_Link_State_NotifCb(glink_link_info_type *link_info, void *priv)
{
  EFI_STATUS status = EFI_SUCCESS;

  if (AsciiStrLen(PMIC_GLINK_REMOTE_SS_NAME) == AsciiStrLen(link_info->remote_ss) ||
    0 == AsciiStrnCmp(PMIC_GLINK_REMOTE_SS_NAME, link_info->remote_ss, AsciiStrLen(link_info->remote_ss)))
  {
    /* Process the notification */
    if (GLINK_LINK_STATE_UP == link_info->link_state)
    {
      DEBUG((EFI_D_WARN, "pmic_glink_Link_State_NotifCb:: GLINK_LINK_STATE_UP remote ss = %a transport name = %a \r\n", status, link_info->remote_ss, link_info->xport));
      pmic_glink_context.IsPMICLINKUP = TRUE;
    }
    else if (GLINK_LINK_STATE_DOWN == link_info->link_state)
    {
      //send signal to exit thread
      pmic_glink_context.IsPMICLINKUP = FALSE;
    }
    else
    {
      //
    }
  }
  else
  {
    //DEBUG((EFI_D_WARN, "pmic_glink_Link_State_NotifCb:: remote ss = %s transport name = %s IGNORE \r\n", status, link_info->remote_ss, link_info->xport));
    return;
  }
}

/*===========================================================================
FUNCTION  glinkTestTxNotificationCb
===========================================================================*/
/**
glinkTestTxNotificationCb

@param[in] handle

@return
*/
/*==========================================================================*/
void pmic_glink_notify_tx_done(glink_handle_type handle,
  const void        *priv,
  const void        *pkt_priv,
  const void        *ptr,
  size_t            size)
{
  pmic_glink_context.TxDone = TRUE;
}


/*=============================================================================
FUNCTION pmic_glink_open
=============================================================================*/

EFI_STATUS pmic_glink_open(void *context)
{
  glink_err_type         ret;
  UINT8                  count = 0;
  EFI_STATUS             status = EFI_SUCCESS;

  if (NULL == g_pmic_glink_protocol)
  {
    return EFI_DEVICE_ERROR;
  }

  status = g_pmic_glink_protocol->GlinkOpen(&pmic_glink_cfg_ptr, &pmic_glink_handle, &ret);
  if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret))
  {
    DEBUG((EFI_D_WARN, "pmic_glink_open:: GlinkOpen failed\r\n"));
    return EFI_DEVICE_ERROR;
  }
  
  while (count < PMIC_GLINK_CONNECT_MAX_WAIT_COUNT )
  {
    status = g_pmic_glink_protocol->GlinkRxPoll(pmic_glink_handle, &ret);
	
    if (pmic_glink_context.IsPMICChannelOpen && GLINK_STATUS_SUCCESS == ret && EFI_SUCCESS == status)
    {
      break;
    }

    gBS->Stall(PMIC_GLINK_WAIT_TIME);

    count++;
  }
  DEBUG((EFI_D_WARN, "pmic_glink_open:: count = %d times\r\n", count));
  if (!pmic_glink_context.IsPMICChannelOpen)
  {
	DEBUG((EFI_D_WARN, "pmic_glink_open:: GlinkOpen failed. Polling timeout.\r\n"));
    return EFI_DEVICE_ERROR;
  }

  return status;
}

/*=============================================================================
  FUNCTION pmic_glink_Init
  =============================================================================*/

EFI_STATUS pmic_glink_Init(void)
{
  EFI_STATUS status = EFI_SUCCESS;
  glink_err_type ret = GLINK_STATUS_FAILURE;
  UINT8 count = 0;//, i = 0;

  DEBUG((EFI_D_WARN, "pmic_glink_Init:: start.  time at %lld ms\r\n", GlinkCalculateTimeStampMSec()));
  status = GlinkLocateProtocol();
  if (EFI_ERROR(status))
  {
    return status;
  }
  memset(&pmic_glink_cfg_ptr, 0, sizeof(glink_open_config_type));
  pmic_glink_cfg_ptr.name = PMIC_GLINK_COMM_ADSP_PORT_NAME;
  pmic_glink_cfg_ptr.remote_ss = PMIC_GLINK_REMOTE_SS_NAME;
  pmic_glink_cfg_ptr.transport = PMIC_GLINK_XPORT_NAME;
  pmic_glink_cfg_ptr.notify_rx = pmic_glink_notify_rx;
  pmic_glink_cfg_ptr.notify_tx_done = pmic_glink_notify_tx_done;
  pmic_glink_cfg_ptr.notify_state = pmic_glink_state_change;

  GLINK_LINK_ID_STRUCT_INIT(pmic_glink_id);
  pmic_glink_id.version = GLINK_LINK_ID_VER;
  pmic_glink_id.xport = pmic_glink_cfg_ptr.transport;
  pmic_glink_id.remote_ss = pmic_glink_cfg_ptr.remote_ss;
  pmic_glink_id.link_notifier = pmic_glink_Link_State_NotifCb;
  pmic_glink_id.handle = NULL;

  pmic_glink_context.IsPMICLINKUP = FALSE;
  pmic_glink_context.IsPMICChannelOpen = FALSE;

  /*Register link state callback*/
  status = g_pmic_glink_protocol->GlinkRegisterLinkStateCB(&pmic_glink_id, (void*)(&pmic_glink_context), &ret);
  if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret))
  {
    DEBUG((EFI_D_WARN, "pmic_glink_Init:: registerLinkStateCB failed status = %x, glinkRet = %d. \r\n", status, ret));
    return EFI_DEVICE_ERROR;

  }

  glink_link_state_type link_state = GLINK_LINK_STATE_DOWN;

  while (count < PMIC_GLINK_CONNECT_MAX_WAIT_COUNT )
  {
    status = g_pmic_glink_protocol->GlinkLinkStatePoll(pmic_glink_id.handle, &link_state, &ret);

    if (pmic_glink_context.IsPMICLINKUP && GLINK_LINK_STATE_UP == link_state && GLINK_STATUS_SUCCESS == ret && EFI_SUCCESS == status)
    {
      DEBUG((EFI_D_WARN, "pmic_glink_Init:: glink is up.  time at %lld ms\r\n", GlinkCalculateTimeStampMSec()));
      break;
    }

    gBS->Stall(PMIC_GLINK_WAIT_TIME);

    count++;
  }

  DEBUG((EFI_D_WARN, "pmic_glink_Init:: count = %d \r\n", count));

  if (!pmic_glink_context.IsPMICLINKUP)
  {
    DEBUG((EFI_D_WARN, "pmic_glink_Init:: wait for glink up in wait timed out. \r\n"));
    return EFI_DEVICE_ERROR;
  }

  status = pmic_glink_open(NULL);
  if (EFI_SUCCESS != status)
  {
    DEBUG((EFI_D_WARN, "pmic_glink_Init:: open glink channel failed during Init %r \r\n", status));
  }
  else
  {
    DEBUG((EFI_D_WARN, "pmic_glink_Init:: open glink channel success. time at %lld ms\r\n", GlinkCalculateTimeStampMSec()));
  }

  return status;
}



/*=============================================================================
  FUNCTION pmic_glink_tx
  =============================================================================*/

EFI_STATUS pmic_glink_tx(const void *priv,
  const void *data, const size_t size)
{
  glink_err_type         ret;
  EFI_STATUS status = EFI_SUCCESS;
  UINT8 count = 0, i = 0;

  if (NULL == g_pmic_glink_protocol)
  {
    return EFI_DEVICE_ERROR;
  }
  pmic_glink_context.TxDone = FALSE;
  for(i = 0; i < PMIC_GLINK_MAX_WAIT_COUNT; i++)
  {
    glink_err_type         rxpoll_ret;
    status = g_pmic_glink_protocol->GlinkTx(pmic_glink_handle, priv, data, size, 0, &ret);
    if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret))
    {
      gBS->Stall(PMIC_GLINK_WAIT_TIME);
      g_pmic_glink_protocol->GlinkRxPoll(pmic_glink_handle, &rxpoll_ret);
      //chargerPD todo error msg
      DEBUG((EFI_D_ERROR, "pmic_glink_sync_send_receive:: glink tx failed status = %r.ret = %d \r\n", status, ret));
    }
    else
    {
      break;
    }    
  }
  if ((EFI_ERROR(status)) || (GLINK_STATUS_SUCCESS != ret)) { return EFI_DEVICE_ERROR;}

  while (count < PMIC_GLINK_MAX_WAIT_COUNT)
  {
    gBS->Stall(PMIC_GLINK_WAIT_TIME);

	  status = g_pmic_glink_protocol->GlinkRxPoll(pmic_glink_handle, &ret);
	
    if (pmic_glink_context.TxDone && GLINK_STATUS_SUCCESS == ret && EFI_SUCCESS == status)
    {
      break;
    }
    count++;
  }

  if (!pmic_glink_context.TxDone)
  {
    DEBUG((EFI_D_ERROR, "pmic_glink_sync_send_receive:: glink tx done timed out\r\n"));
    return EFI_DEVICE_ERROR;
  }

  return status;
}


/*=============================================================================
FUNCTION  pmic_glink_sync_send_receive
=============================================================================*/

EFI_STATUS pmic_glink_sync_send_receive(uint32 opcode, void* inputBuffer, size_t inputSize)
{
  EFI_STATUS status = EFI_SUCCESS;
  glink_err_type         ret;
  uint32                 count = 0;
  EFI_TPL                OrigTPL;

  /* Raise TPL to avoid interrupt */
  OrigTPL = gBS->RaiseTPL(TPL_CALLBACK);
  
  if(pmic_glink_context.IsPMICChannelOpen == TRUE)
  {
    pmic_glink_context.RxNotified = FALSE;
    //send the inputBuffer
    status = pmic_glink_tx(&pmic_glink_context, inputBuffer, inputSize);

    if (EFI_ERROR(status))
    {
      DEBUG((EFI_D_WARN, "pmic_glink_sync_send_receive:: glink tx failed status = %r.  \r\n", status));
	  goto Exit;
    }
    while (count < PMIC_GLINK_MAX_WAIT_COUNT)
    {
      gBS->Stall(PMIC_GLINK_WAIT_TIME);
      if (!(pmic_glink_context.IsPMICLINKUP) || !(pmic_glink_context.IsPMICChannelOpen))
      {
        DEBUG((EFI_D_WARN, "pmic_glink_sync_send_receive:: glink disconnected isPmicLinkUp = %d, isPmicChannelOpen = %d.  \r\n", pmic_glink_context.IsPMICLINKUP, pmic_glink_context.IsPMICChannelOpen));
        status = EFI_DEVICE_ERROR;
        break;
      }
	  
      status = g_pmic_glink_protocol->GlinkRxPoll(pmic_glink_handle, &ret);
	  
      if (pmic_glink_context.RxNotified && GLINK_STATUS_SUCCESS == ret && EFI_SUCCESS == status)
      {
        break;
      }
      count++;
    }
    if (!pmic_glink_context.RxNotified)
    {
      DEBUG((EFI_D_ERROR, "pmic_glink_sync_send_receive:: wait for Rx Notification timed out. \r\n"));
      status = EFI_DEVICE_ERROR;
    }

    pmic_glink_context.RxNotified = FALSE;
  }

  Exit: 
    gBS->RestoreTPL(OrigTPL);
    return status;
}

/*=============================================================================
  FUNCTION wmi_process_rx_data
  =============================================================================*/

EFI_STATUS pmic_glink_process_rx_data(PMIC_GLINK_HEADER_TYPE* rxData, size_t size, uint32* indicationReceived)
{
  EFI_STATUS             status = EFI_SUCCESS;

  if ((NULL == g_pmic_glink_protocol ) || (rxData == NULL) || (indicationReceived == NULL))
  {
    return EFI_DEVICE_ERROR;
  }

  if (rxData->msg_owner == PMIC_GLINK_MSG_OWNER_CHARGER)
  {
    DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for battery manager.  \r\n"));
    //handle battmngr requests
    switch (rxData->opcode)
    {
    case BATT_MNGR_GET_BATT_ID_REQ:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for opcode = %d.  \r\n", BATT_MNGR_GET_BATT_ID_REQ));
      if (size == sizeof(batt_mngr_get_batt_id_resp_msg))
      {
        batt_mngr_get_batt_id_resp_msg* battIDResp = (batt_mngr_get_batt_id_resp_msg*)rxData;
        if (battIDResp != NULL)
        {
          pmic_glink_context.BatteryCount = battIDResp->battery_id;
        }
      }

      break;
    case BATT_MNGR_GET_CHARGER_STATUS_REQ:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for opcode = %d.  \r\n", BATT_MNGR_GET_CHARGER_STATUS_REQ));
      if (size == sizeof(batt_mngr_get_charger_status_resp_msg))
      {
        batt_mngr_get_charger_status_resp_msg* chargerStatus = (batt_mngr_get_charger_status_resp_msg*)rxData;
        if (chargerStatus != NULL)
        {
          static UINT32 previous_remaining_cap = 0;
          pmic_glink_context.chargingSource = chargerStatus->charging_source;
          pmic_glink_context.BatteryState = chargerStatus->battery_state;
          if(pmic_glink_latest_full_capacity == 0 )
          {
            //use previous value
            pmic_glink_context.BatteryPercentage = 5;
            pmic_glink_context.BatteryPercentage_CentiPct = 500;
            DEBUG((EFI_D_ERROR, "pmic_glink_process_rx_data:: latest full capacity is 0,.  \r\n"));
          }
          else
          {
            /* code */
            if(chargerStatus->capacity == 0) 
            { 
              chargerStatus->capacity = previous_remaining_cap; 
            }
            else
            {
              previous_remaining_cap = chargerStatus->capacity;
            }
            
          pmic_glink_context.BatteryPercentage = (chargerStatus->capacity * 100) / pmic_glink_latest_full_capacity;
          pmic_glink_context.BatteryPercentage_CentiPct = (chargerStatus->capacity * 10000) / pmic_glink_latest_full_capacity;
          }          
          pmic_glink_context.Vbatt = chargerStatus->battery_voltage;
          DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data::rate = %d mW, vbatt = %d mV, remaining_capacity = %d mWh  \r\n", chargerStatus->rate, pmic_glink_context.Vbatt, chargerStatus->capacity));
          if (pmic_glink_context.Vbatt != 0)
          {
            INT32 tempIBatt = chargerStatus->rate * 1000;
            pmic_glink_context.Ibatt = tempIBatt / (INT32)pmic_glink_context.Vbatt;
          }
          pmic_glink_context.PowerState = chargerStatus->power_state;
          pmic_glink_context.BatteryTemperature = (int32)((chargerStatus->battery_temperature) / 10 - KELVIN_ZERO);
        }
      }
      break;
    case BATT_MNGR_NOTIFY_IND:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for notification.  \r\n"));
      if (size == sizeof(batt_mngr_notify_ind_msg))
      {
        batt_mngr_notify_ind_msg* notification = (batt_mngr_notify_ind_msg*)rxData;
        if (notification != NULL)
        {
          *indicationReceived = notification->notification;
        }
      }
      break;
    case BATT_MNGR_GET_BATTERY_INFORMATION_REQ:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for BATT_MNGR_GET_BATTERY_INFORMATION_REQ.  \r\n"));
      if (size == sizeof(batt_mngr_get_battery_information_resp_msg))
      {
        batt_mngr_get_battery_information_resp_msg* batteryInfo = (batt_mngr_get_battery_information_resp_msg*)rxData;
        if (batteryInfo != NULL && (batteryInfo->last_full_capacity != 0))
        {
          pmic_glink_latest_full_capacity = batteryInfo->last_full_capacity;
          DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data::actual_full_capacity = %d mWh \r\n", pmic_glink_latest_full_capacity));
        }
      }
      break;
    case BATT_MNGR_POWER_SUPPLY_GET_REQ:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for BATT_MNGR_POWER_SUPPLY_GET_REQ.  \r\n"));
      if (size == sizeof(power_supply_property_resp_msg))
      {
        power_supply_property_resp_msg* power_supply_msg = (power_supply_property_resp_msg*)rxData;
        if(power_supply_msg != NULL)
        {
          if(power_supply_msg->property_id == POWER_SUPPLY_OCV)
          {
            pmic_glink_context.BatteryOCV = power_supply_msg->value / 1000; //in mv       
          }
        }
      }
      break;    
    case BATT_MNGR_GET_CHARGER_POWER_REQ:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for BATT_MNGR_GET_CHARGER_POWER_REQ \r\n"));
      if (size == sizeof(battman_get_charger_power_resp_msg))  
      {
        battman_get_charger_power_resp_msg* chg_pwr_msg = (battman_get_charger_power_resp_msg*)rxData;
        if(chg_pwr_msg != NULL && chg_pwr_msg->return_code == 0)
        {
          pmic_glink_context.chargingSource = chg_pwr_msg->charging_source;
          pmic_glink_context.ChargerVoltage_mV = chg_pwr_msg->voltage_mv;
          pmic_glink_context.ChargerCurrent_mA = chg_pwr_msg->current_ma;
        }
      }
      break;
    default:
      status = EFI_INVALID_PARAMETER;
      break;
    }
  }
  else if (rxData->msg_owner == PMIC_GLINK_MSG_OWNER_USB_TYPE_C)
  {
    //handle pd requests
    DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data usb type c.  \r\n"));
    switch (rxData->opcode)
    {
    case UCSI_READ_BUFFER_REQ:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for opcode = %d.  \r\n", UCSI_READ_BUFFER_REQ));
      if (size == sizeof(ucsi_read_buffer_resp_msg))
      {
        ucsi_read_buffer_resp_msg* respMsg = (ucsi_read_buffer_resp_msg*)rxData;
        if (respMsg != NULL)
        {
          memscpy(pmic_glink_context.UCSIDataBuffer, UCSI_BUFFER_SIZE, respMsg->read_buffer, UCSI_BUFFER_SIZE);
        }
      }
      break;
    case UCSI_WRITE_BUFFER_REQ:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for opcode = %d.  \r\n", UCSI_WRITE_BUFFER_REQ));
      if (size == sizeof(ucsi_usbc_write_buffer_resp_msg))
      {
        ucsi_usbc_write_buffer_resp_msg* respMsg = (ucsi_usbc_write_buffer_resp_msg*)rxData;
        if (respMsg != NULL && respMsg->return_code == 0)
        {
          pmic_glink_context.UCSIDataIsWritten = TRUE;
        }
      }
      break;
    case UCSI_NOTIFY_IND:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for opcode = %d.  \r\n", UCSI_NOTIFY_IND));
      ucsi_notify_ind_msg* UCSINotify = (ucsi_notify_ind_msg*)rxData;
      if (UCSINotify != NULL)
      {
        *indicationReceived = UCSINotify->notification;
      }
      break;
    default:
      break;
    }
  }  
  else if (rxData->msg_owner == PMIC_GLINK_MSG_OWNER_USBC_PAN)
  {        
    DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data usbc pan.  \r\n"));
    switch (rxData->opcode)
    {
    case USBC_CMD_READ_REQ:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for opcode = %d.  \r\n", USBC_CMD_READ_REQ));
      if (size == sizeof(usbc_read_buffer_resp_msg))
      {
        usbc_read_buffer_resp_msg* respMsg = (usbc_read_buffer_resp_msg*)rxData;
        if (respMsg != NULL)
        {
          memscpy(pmic_glink_context.USBCDataBuffer, USBC_READ_BUFFER_SIZE, respMsg->read_buffer, USBC_READ_BUFFER_SIZE);
        }
      }
      break;
    case USBC_CMD_WRITE_REQ:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for opcode = %d.  \r\n", USBC_CMD_WRITE_REQ));
      if (size == sizeof(ucsi_usbc_write_buffer_resp_msg))
      {
        ucsi_usbc_write_buffer_resp_msg* respMsg = (ucsi_usbc_write_buffer_resp_msg*)rxData;
        if (respMsg != NULL && respMsg->return_code == 0)
        {
          pmic_glink_context.USBCDataIsWritten = TRUE;
        }
      }
      break;
    default:
      break;
    }
  }
  else if (rxData->msg_owner == PMIC_GLINK_MSG_OWNER_OEM)
  {
    //handle pd requests
    DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data OEM.  \r\n"));
    switch (rxData->opcode)
    {
    case OEM_OPCODE_READ_BUFFER:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for opcode = %d.  \r\n", OEM_OPCODE_READ_BUFFER));
      if (size == sizeof(battman_oem_read_buffer_resp_msg))
      {
        battman_oem_read_buffer_resp_msg* respMsg = (battman_oem_read_buffer_resp_msg*)rxData;
        if (respMsg != NULL && respMsg->data_size)
        {
          memscpy(pmic_glink_context.OemDataBuffer, sizeof(respMsg->data_buffer), respMsg->data_buffer, sizeof(respMsg->data_buffer));
        }
      }
      break;
    case OEM_OPCODE_WRITE_BUFFER:
      DEBUG((EFI_D_INFO, "pmic_glink_process_rx_data:: got rx data for opcode = %d.  \r\n", OEM_OPCODE_WRITE_BUFFER));
      if (size == sizeof(batt_mngr_generic_resp_msg))
      {
        batt_mngr_generic_resp_msg * respMsg = (batt_mngr_generic_resp_msg*)rxData;
        if (respMsg != NULL && respMsg->return_status == 0)
        {
          pmic_glink_context.OemDataIsWritten = TRUE;
        }
      }
      break;
    case OEM_OPCODE_SEND_RECEIVE_BUFFER:
      DEBUG((EFI_D_WARN, "pmic_glink_process_rx_data:: got rx data for opcode = 0x%x.  \r\n", OEM_OPCODE_SEND_RECEIVE_BUFFER));
      if (size == sizeof(battman_oem_send_receive_req_resp_msg))
      {
        battman_oem_send_receive_req_resp_msg* respMsg = (battman_oem_send_receive_req_resp_msg*)rxData;
        if (respMsg != NULL && respMsg->data_size)
        {
          pmic_glink_context.OemDataIsWritten = TRUE;
          memscpy(pmic_glink_context.OemDataBuffer, sizeof(respMsg->oem_buffer), respMsg->oem_buffer, sizeof(respMsg->oem_buffer));
        }
      }
    default:
      break;
    }
  }  
  else
  {
    //not correct msg owner
    DEBUG((EFI_D_WARN, "pmic_glink_process_rx_data:: got rx data of unknown owner.  \r\n"));
  }
  
  //rx done to free evt_buf and requeue rx intent.
  status |= pmic_glink_rx_done(rxData, TRUE);

  return status;
}

EFI_STATUS pmic_glink_get_battery_info(UINT32 batteryID)
{
  EFI_STATUS status = EFI_SUCCESS;
  batt_mngr_get_battery_information_req_msg reqMsg = { { 0 }, 0 };

  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_CHARGER;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = BATT_MNGR_GET_BATTERY_INFORMATION_REQ;
  reqMsg.battery_id = batteryID;  
  status = pmic_glink_sync_send_receive(BATT_MNGR_GET_BATTERY_INFORMATION_REQ, &reqMsg, sizeof(batt_mngr_get_battery_information_req_msg));
  return status;
}

EFI_STATUS pmic_glink_get_battery_count(UINT32* batteryCount)
{
  EFI_STATUS status = EFI_SUCCESS;
  batt_mngr_get_batt_id_resp_msg reqMsg = { { 0 }, 0};


  if (batteryCount == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_CHARGER;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = BATT_MNGR_GET_BATT_ID_REQ;
  reqMsg.battery_id = 0;
  status = pmic_glink_sync_send_receive(BATT_MNGR_GET_BATT_ID_REQ, &reqMsg, sizeof(batt_mngr_get_batt_id_resp_msg));
  if (EFI_SUCCESS == status)
  {
    *batteryCount = pmic_glink_context.BatteryCount;
    DEBUG((EFI_D_WARN, "pmic_glink_get_battery_count:: battery Count = %d.  \r\n", *batteryCount));
  }
  return status;
}

EFI_STATUS pmic_glink_get_battery_status(UINT32 battery_index, EFI_PM_GLINK_BATT_STATUS_INFO *pBattStsInfo)
{
  EFI_STATUS status = EFI_SUCCESS;
  batt_mngr_get_charger_status_req_msg reqMsg = { { 0 }, 0 };


  if (pBattStsInfo == NULL)
    return EFI_INVALID_PARAMETER;

  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_CHARGER;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = BATT_MNGR_GET_CHARGER_STATUS_REQ;
  reqMsg.battery_id = battery_index;

  status = pmic_glink_sync_send_receive(BATT_MNGR_GET_CHARGER_STATUS_REQ, &reqMsg, sizeof(batt_mngr_get_charger_status_req_msg));
  if (EFI_SUCCESS == status)
  { 
    pBattStsInfo->StateOfCharge = pmic_glink_context.BatteryPercentage;
    pBattStsInfo->StateOfChargeCentiPct = pmic_glink_context.BatteryPercentage_CentiPct;
    pBattStsInfo->ChargeCurrent = pmic_glink_context.Ibatt;
    pBattStsInfo->BatteryVoltage = pmic_glink_context.Vbatt;
    pBattStsInfo->BatteryTemperature = pmic_glink_context.BatteryTemperature;
    pBattStsInfo->PowerState = pmic_glink_context.PowerState;
    pBattStsInfo->ChargingSource = (EFI_PMIC_GLINK_CHARGING_SOURCE)pmic_glink_context.chargingSource;
  }
  return status;

}

EFI_STATUS pmic_glink_get_battery_status_ext(UINT32* battery_ocv)
{
  EFI_STATUS status = EFI_SUCCESS;
  power_supply_property_req_msg reqMsg = { 0 };
  
  if (battery_ocv == NULL)
    return EFI_INVALID_PARAMETER;
  
  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_CHARGER;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = BATT_MNGR_POWER_SUPPLY_GET_REQ;
  reqMsg.property_id = POWER_SUPPLY_OCV;
  status = pmic_glink_sync_send_receive(BATT_MNGR_POWER_SUPPLY_GET_REQ, &reqMsg, sizeof(power_supply_property_req_msg));

  if (EFI_SUCCESS != status)
  {
    return status;
  }
  *battery_ocv = pmic_glink_context.BatteryOCV;
  return status;
}
EFI_STATUS pmic_glink_get_link_status(  EFI_PM_GLINK_LINK_STATUS *PmicGLinkStatus)
{
  if(NULL == PmicGLinkStatus)
    return EFI_INVALID_PARAMETER;

  PmicGLinkStatus->IsPMICChannelOpen = pmic_glink_context.IsPMICChannelOpen;

  return EFI_SUCCESS;
}

EFI_STATUS pmic_glink_ucsi_read_buffer(uint8** dataBuffer, uint8 size)
{
  EFI_STATUS status = EFI_SUCCESS;
  ucsi_read_buffer_resp_msg reqMsg = { { 0 }};


  if (dataBuffer == NULL || *dataBuffer == NULL)
    return EFI_INVALID_PARAMETER;

  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_USB_TYPE_C;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = UCSI_READ_BUFFER_REQ;

  status = pmic_glink_sync_send_receive(PMIC_GLINK_MSG_TYPE_REQ_RESP, &reqMsg, sizeof(ucsi_read_buffer_resp_msg));
  if (EFI_SUCCESS == status)
  {
    memscpy(*dataBuffer, UCSI_BUFFER_SIZE, pmic_glink_context.UCSIDataBuffer, UCSI_BUFFER_SIZE);
  }
  return status;

}

EFI_STATUS pmic_glink_ucsi_write_buffer(uint8* dataBuffer, uint8 size)
{
  EFI_STATUS status = EFI_SUCCESS;
  ucsi_write_buffer_req_msg reqMsg = { { 0 }, { 0 }, 0 };


  if (dataBuffer == NULL || size < UCSI_BUFFER_SIZE)
    return EFI_INVALID_PARAMETER;
  pmic_glink_context.UCSIDataIsWritten = FALSE;
  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_USB_TYPE_C;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = UCSI_WRITE_BUFFER_REQ;
  memscpy(reqMsg.write_buffer, UCSI_BUFFER_SIZE, dataBuffer, UCSI_BUFFER_SIZE);
  status = pmic_glink_sync_send_receive(PMIC_GLINK_MSG_TYPE_REQ_RESP, &reqMsg, sizeof(ucsi_write_buffer_req_msg));
  if (EFI_SUCCESS == status && pmic_glink_context.UCSIDataIsWritten)
    return status;
  else
    return EFI_DEVICE_ERROR;
}

EFI_STATUS pmic_glink_usbc_read_buffer(uint8** dataBuffer, uint8 size)
{
  EFI_STATUS status = EFI_SUCCESS;
  usbc_read_buffer_resp_msg reqMsg = { { 0 }};


  if (dataBuffer == NULL || *dataBuffer == NULL)
    return EFI_INVALID_PARAMETER;

  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_USBC_PAN;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = USBC_CMD_READ_REQ;
  status = pmic_glink_sync_send_receive(PMIC_GLINK_MSG_TYPE_REQ_RESP, &reqMsg, sizeof(usbc_read_buffer_resp_msg));
  if (EFI_SUCCESS == status)
  {
    memscpy(*dataBuffer, USBC_READ_BUFFER_SIZE, pmic_glink_context.USBCDataBuffer, USBC_READ_BUFFER_SIZE);
  }
  return status;

}

EFI_STATUS pmic_glink_usbc_write_buffer(uint8* dataBuffer, uint8 size)
{
  EFI_STATUS status = EFI_SUCCESS;
  usbc_write_buffer_req_msg reqMsg = { { 0 }, { 0 }, 0 };


  if (dataBuffer == NULL || size < USBC_WRITE_BUFFER_SIZE)
    return EFI_INVALID_PARAMETER;
  pmic_glink_context.USBCDataIsWritten = FALSE;
  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_USBC_PAN;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = USBC_CMD_WRITE_REQ;
  memscpy(reqMsg.write_buffer, USBC_WRITE_BUFFER_SIZE, dataBuffer, USBC_WRITE_BUFFER_SIZE);
  status = pmic_glink_sync_send_receive(PMIC_GLINK_MSG_TYPE_REQ_RESP, &reqMsg, sizeof(usbc_write_buffer_req_msg));
  if (EFI_SUCCESS == status && pmic_glink_context.USBCDataIsWritten)
    return status;
  else
    return EFI_DEVICE_ERROR;
}
EFI_STATUS pmic_glink_get_charger_power(EFI_PM_GLINK_CHARGER_POWER *pChargerPower)
{
  EFI_STATUS status = EFI_SUCCESS;
  battman_get_charger_power_req_msg reqMsg = { { 0 } };


  if (pChargerPower == NULL)
    return EFI_INVALID_PARAMETER;

  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_CHARGER;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = BATT_MNGR_GET_CHARGER_POWER_REQ;

  status = pmic_glink_sync_send_receive(BATT_MNGR_GET_CHARGER_POWER_REQ, &reqMsg, sizeof(battman_get_charger_power_req_msg));
  if (EFI_SUCCESS == status)
  { 
    pChargerPower->charging_source = (EFI_PMIC_GLINK_CHARGING_SOURCE)pmic_glink_context.chargingSource;
    pChargerPower->voltage_mv = pmic_glink_context.ChargerVoltage_mV;
    pChargerPower->current_ma = pmic_glink_context.ChargerCurrent_mA;

  }
  return status;

}

EFI_STATUS pmic_glink_oem_read_buffer(uint32* dataBuffer, uint32 property_id, uint8 size)
{
  EFI_STATUS status = EFI_SUCCESS;
  battman_oem_read_buffer_req_msg reqMsg = { { 0 }, 0, 0};

  if (dataBuffer == NULL || size > MAX_OEM_PROPERTY_DATA_SIZE)
    return EFI_INVALID_PARAMETER;

  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_OEM;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = OEM_OPCODE_READ_BUFFER;
  reqMsg.oem_property_id = property_id;
  reqMsg.data_size = size;

  status = pmic_glink_sync_send_receive(PMIC_GLINK_MSG_TYPE_REQ_RESP, &reqMsg, sizeof(battman_oem_read_buffer_req_msg));
  if (EFI_SUCCESS == status)
  {
    memscpy(dataBuffer, sizeof(pmic_glink_context.OemDataBuffer), pmic_glink_context.OemDataBuffer, sizeof(pmic_glink_context.OemDataBuffer));
  }
  return status;

}

EFI_STATUS pmic_glink_oem_write_buffer(uint32* dataBuffer, uint32 property_id, uint8 size)
{
  EFI_STATUS status = EFI_SUCCESS;
  battman_oem_write_buffer_req_msg reqMsg = { { 0 }, 0,{ 0 }, 0};

  if (dataBuffer == NULL || size > MAX_OEM_PROPERTY_DATA_SIZE)
    return EFI_INVALID_PARAMETER;

  pmic_glink_context.OemDataIsWritten = FALSE;

  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_OEM;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = OEM_OPCODE_WRITE_BUFFER;
  reqMsg.oem_property_id = property_id;
  reqMsg.data_size = size;

  memscpy(reqMsg.data_buffer, sizeof(reqMsg.data_buffer), dataBuffer, sizeof(reqMsg.data_buffer));
  status = pmic_glink_sync_send_receive(PMIC_GLINK_MSG_TYPE_REQ_RESP, &reqMsg, sizeof(battman_oem_write_buffer_req_msg));
  if (EFI_SUCCESS == status && pmic_glink_context.OemDataIsWritten)
    return status;
  else
    return EFI_DEVICE_ERROR;
}

EFI_STATUS pmic_glink_oem_write_read_buffer(uint32* dataBuffer, uint8 size)
{
  EFI_STATUS status = EFI_SUCCESS;

  if (dataBuffer == NULL || size > MAX_OEM_PROPERTY_DATA_SIZE)
    return EFI_INVALID_PARAMETER;

  battman_oem_send_receive_req_resp_msg reqMsg = { { 0 }, 0, {0}};
  //need adsp change
  reqMsg.header.msg_owner = PMIC_GLINK_MSG_OWNER_OEM;
  reqMsg.header.msg_type = PMIC_GLINK_MSG_TYPE_REQ_RESP;
  reqMsg.header.opcode = OEM_OPCODE_SEND_RECEIVE_BUFFER;
  reqMsg.data_size = size;

  memscpy(reqMsg.oem_buffer, sizeof(reqMsg.oem_buffer), dataBuffer, sizeof(reqMsg.oem_buffer));

  status = pmic_glink_sync_send_receive(PMIC_GLINK_MSG_TYPE_REQ_RESP, &reqMsg, sizeof(battman_oem_send_receive_req_resp_msg));

  if (EFI_SUCCESS == status && pmic_glink_context.OemDataIsWritten)
  {
    memset(dataBuffer, 0, MAX_OEM_PROPERTY_DATA_SIZE * sizeof(uint32));
    memscpy(dataBuffer, sizeof(pmic_glink_context.OemDataBuffer), pmic_glink_context.OemDataBuffer, sizeof(pmic_glink_context.OemDataBuffer));
  }
  else
    return EFI_DEVICE_ERROR;

  return status;
}

