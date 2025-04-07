#ifndef PMIC_GLINK_H
#define PMIC_GLINK_H
/******************************************************************************
  @file    pmic_glink.h
  @brief   Glink header file used by PmicGlink

  DESCRIPTION
  Glink header file used by PmicGlink
   
  ---------------------------------------------------------------------------
  Copyright (c) 2018 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
*******************************************************************************
EDIT HISTORY

when           who     what, where, why
--------       ---     -----------------------------------------------------------
03/29/2018     cs      added ucsi interface support.
=============================================================================*/

#include "glink.h"
#include <Protocol/EFIGLink.h>
#include "pmic_glink_msg.h"
#include <Protocol/EFIPmicGlink.h>

/*=============================================================================
  INTERNAL DEFINES
=============================================================================*/

#define PMIC_GLINK_PKT_SIZE             0x1000
#define PMIC_GLINK_RX_FIFO_DEPTH        6
#define PMIC_GLINK_XPORT_NAME           "SMEM"
#define PMIC_GLINK_REMOTE_SS_NAME       "lpass"
#define PMIC_GLINK_COMM_ADSP_PORT_NAME  "PMIC_RTR_ADSP_APPS" /* Port name used to communicate with APSS */
#define PMIC_GLINK_MAX_TYPEC_PORT       4

/*=============================================================================
  INTERNAL TYPEDEF
=============================================================================*/
typedef struct
{
  BOOLEAN IsPMICLINKUP;

  BOOLEAN IsPMICChannelOpen;

  BOOLEAN TxDone;

  BOOLEAN RxNotified;

  BOOLEAN IsBatteryPresent;

  uint32 BatteryCount;

  uint32 BatteryState;

  uint32 BatteryPercentage;

  int32 Ibatt;
  
  uint32 Vbatt;

  uint32 PowerState;

  batt_mngr_charging_source_req_type_e chargingSource;

  int32 BatteryTemperature;

  uint8 UCSIDataBuffer[UCSI_BUFFER_SIZE];

  uint8 USBCDataBuffer[USBC_READ_BUFFER_SIZE];

  boolean UCSIDataIsWritten;

  boolean USBCDataIsWritten;

  boolean SetLoggingProperties;

  boolean GetChargerPDLogs;

  boolean GetQBGDump;

  uint32 BatteryOCV;
  boolean GetChargerPDInitLogs;
  uint32 ChargerVoltage_mV;

  uint32 ChargerCurrent_mA;

  uint32 OemDataBuffer[MAX_OEM_PROPERTY_DATA_SIZE];
  boolean OemDataIsWritten;

  uint32 BatteryPercentage_CentiPct;

}PMIC_GLINK_CONTEXT;


typedef glink_handle_type pmic_glink_handle_t;

typedef void (*pmic_glink_api_t)(glink_handle_type handle,
                                const void *priv, 
                                const void *pkt_priv,
								                const void *ptr, 
								                size_t     size);


/*=============================================================================
                        INTERNAL FUNCTIONS
=============================================================================*/

/*=============================================================================
  FUNCTION  pmic_glink_init
=============================================================================*/

EFI_STATUS pmic_glink_Init(void);

/*=============================================================================
  FUNCTION  pmic_glink_deinit
=============================================================================*/

void pmic_glink_deinit(void);


/*=============================================================================
  FUNCTION  pmic_glink_tx
=============================================================================*/

EFI_STATUS pmic_glink_tx(const void *priv,
                 const void *data, const size_t size);

/*=============================================================================
  FUNCTION  pmic_glink_rx_done
=============================================================================*/

EFI_STATUS pmic_glink_rx_done(const void *data, BOOLEAN refill);

/*=============================================================================
FUNCTION  pmic_glink_sync_send_receive
=============================================================================*/

EFI_STATUS pmic_glink_sync_send_receive(uint32 opcode, void* inputBuffer, size_t inputSize);

/*=============================================================================
FUNCTION  pmic_glink_process_rx_data
=============================================================================*/
EFI_STATUS pmic_glink_process_rx_data(PMIC_GLINK_HEADER_TYPE* rxData, size_t size, uint32* indicationReceived);

EFI_STATUS pmic_glink_get_battery_count(UINT32* batteryCount);

EFI_STATUS pmic_glink_get_battery_status
(
UINT32          battery_index,
EFI_PM_GLINK_BATT_STATUS_INFO *pBattStsInfo
);
EFI_STATUS pmic_glink_get_battery_status_ext(UINT32* battery_ocv);

EFI_STATUS pmic_glink_get_battery_info(UINT32 batteryID);


EFI_STATUS pmic_glink_get_link_status( EFI_PM_GLINK_LINK_STATUS *PmicGLinkStatus);


EFI_STATUS pmic_glink_ucsi_read_buffer(uint8** dataBuffer, uint8 size);

EFI_STATUS pmic_glink_ucsi_write_buffer(uint8* dataBuffer, uint8 size);

EFI_STATUS pmic_glink_usbc_read_buffer(uint8** dataBuffer, uint8 size);

EFI_STATUS pmic_glink_usbc_write_buffer(uint8* dataBuffer, uint8 size);

EFI_STATUS pmic_glink_oem_write_buffer(uint32* dataBuffer, uint32 property_id, uint8 size);

EFI_STATUS pmic_glink_oem_read_buffer(uint32* dataBuffer, uint32 property_id, uint8 size);

EFI_STATUS pmic_glink_oem_write_read_buffer(uint32* dataBuffer, uint8 size);


/*=============================================================================
                        New GLINK INTERNAL DEFINES
=============================================================================*/

#define PMIC_GLINK_CPDLOG_COMM_PORT_NAME  "PMIC_LOGS_ADSP_APPS" /* Port name used to communicate with APSS */

/*=============================================================================
                        New GLINK channel functions
=============================================================================*/

/*=============================================================================
  FUNCTION  pmic_glink_init
=============================================================================*/

EFI_STATUS pmic_glink_cpdlog_Init(void);

/*=============================================================================
  FUNCTION  pmic_glink_deinit
=============================================================================*/

void pmic_glink_cpdlog_deinit(void);


/*=============================================================================
  FUNCTION  pmic_glink_tx
=============================================================================*/

EFI_STATUS pmic_glink_cpdlog_tx(const void *priv,
                 const void *data, const size_t size);

/*=============================================================================
  FUNCTION  pmic_glink_rx_done
=============================================================================*/

EFI_STATUS pmic_glink_cpdlog_rx_done(const void *data, BOOLEAN refill);

/*=============================================================================
FUNCTION  pmic_glink_sync_send_receive
=============================================================================*/

EFI_STATUS pmic_glink_cpdlog_sync_send_receive(uint32 opcode, void* inputBuffer, size_t inputSize);

/*=============================================================================
FUNCTION  pmic_glink_process_rx_data
=============================================================================*/
EFI_STATUS pmic_glink_cpdlog_process_rx_data(PMIC_GLINK_HEADER_TYPE* rxData, size_t size, uint32* indicationReceived);

EFI_STATUS pmic_glink_cpdlog_open(void *context);

EFI_STATUS pmic_glink_cpdlog_get_link_status( EFI_PM_GLINK_LINK_STATUS *PmicGLinkStatus);

EFI_STATUS pmic_glink_cpdlog_set_properties(UINT64 LogCategories, UINT32 LogLevel);

EFI_STATUS pmic_glink_cpdlog_get_buffer(UINT32 LogMaxSize,  CHAR8* ReceivedBuffer);

EFI_STATUS pmic_glink_cpdlog_get_init_buffer(UINT32 LogMaxSize, CHAR8* ReceivedBuffer);

EFI_STATUS pmic_glink_cpdlog_get_qbg_dump(UINT32 *ReceivedQbgDumpSize,UINT32 *ReceivedQbgDump);

EFI_STATUS pmic_glink_get_charger_power(EFI_PM_GLINK_CHARGER_POWER *pChargerPower);


#endif // pmic_GLINK_H
