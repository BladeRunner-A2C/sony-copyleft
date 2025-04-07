/**
 * @file  SpNvmDxe.c 
 *  
 * Dxe driver for SP NVM in UEFI  
 */

/*=============================================================================
 Copyright (c) 2020-2022 Qualcomm Technologies, Incorporated.
 All rights reserved.
 Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                    EDIT HISTORY FOR FILE


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 12/31/22   vp      Sample code for retrieving SPU health
 12/27/22   gn      Removing SpNvm Protocol implementation for ChargerDxe
 07/29/21   vp      Logging improvements
 05/17/21   sn      Register chargerapp LPMExit cb only when real battery is present
 04/19/21   av      Open sTPM nvm channel only if TPM type is sTPM
 02/26/21   sn      Ignore charging status when platform type is CDP or RUMI
 02/11/21   sn      Delay sp_nvm init based on charging status
 02/08/21   vp      Fix stpm channel name
 05/30/20   ll      initial release
=============================================================================*/

/*===========================================================================
                    INCLUDE FILES                                            
===========================================================================*/
#include "osCommon.h"
#include "nvm_main.h"
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include "QcomLib.h"
#include <Library/QcomBaseLib.h> 
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <stdio.h>
#include <Include/Lpm.h>

/** Protocol Dependencies */
#include <Protocol/EFIChargerEx.h>
#include <Protocol/ReportStatusCodeHandler.h>
#include <Protocol/EFITpmControl.h>
#include <Protocol/EFISpcom.h>

/* Enable to run code that invokes SPU health API as the very last 
   thing in the Dxe entry funtion */
#undef RUN_SPU_HEALTH_SAMPLE_CODE

/*===========================================================================
                    GLOBAL VARIABLE DECLARATIONS                              
===========================================================================*/
UINT32 tpmType = None;

/*===========================================================================
                    LOCAL VARIABLE DECLARATIONS                              
===========================================================================*/

const char *supportedAppNamesSTPM[] = {
    "sp_nvm",
    "stpm_lite_msft",
};

const int spss_nvm_app_names_stpm_count_ = 2;

const char *supportedAppNames[] = {
    "sp_nvm",
};

const int spss_nvm_app_names_count_ = 1;

/* Exit Boot Services vars */
extern EFI_GUID gEfiEventExitBootServicesGuid;
EFI_EVENT SpNvmExitBSEvent = (EFI_EVENT)NULL;

#define EFI_FAILURE (80)

/*===========================================================================*/
/*                  FUNCTIONS PROTOTYPES                                     */
/*===========================================================================*/

STATIC EFI_STATUS SpNvmRegisterLPMCb(BOOLEAN register_Lpm);
STATIC EFI_STATUS SpNvmLPMCb (
    IN EFI_STATUS_CODE_TYPE     CodeType,
    IN EFI_STATUS_CODE_VALUE    Value,
    IN UINT32                   Instance,
    IN EFI_GUID                 *CallerId,
    IN EFI_STATUS_CODE_DATA     *Data OPTIONAL
    );
STATIC VOID SpNvmExitBSCb(EFI_EVENT event,void *context);
STATIC EFI_STATUS SpNvmRegisterEBSCb(VOID);
/*===========================================================================
                    EXTERNAL FUNCTION DEFINITIONS                                     
===========================================================================*/
/**
 * Entry point for the SP NVM Dxe driver.
 * Initialize SpNvm Module. Calls startRoutine for each channel/apps
 * (nvm_main.cpp: nvm_main(appNames[], apps_num))
 *
 * 
 * @return Standard EFI error codes
 */
EFI_STATUS
sp_nvm_entry_point (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS                status                   = EFI_SUCCESS;
  EFI_CHARGER_EX_PROTOCOL   *pChargerExProtocol      = NULL;
  EFI_CHARGER_EX_FLASH_INFO sPowerTypeInfo           = {0};
  BOOLEAN bBatteryPresent                            = FALSE;
  UINT32                    tpmState                 = None;
  QCOM_TPM_CONTROL_PROTOCOL *pQcomTpmControlProtocol = NULL;

  fileSystemInit();

  if (EFI_SUCCESS != gBS->LocateProtocol( &gQcomTpmControlProtocolGuid,
                                          NULL,
                                             (VOID **)&pQcomTpmControlProtocol ))
  {
     // Unable to locate TpmControl protocol
     LOGE("%a: Unable to locate tpm control protocol\r\n", __func__);    
     return EFI_NOT_FOUND;
  }

  if (EFI_SUCCESS != pQcomTpmControlProtocol->GetTpmStateAndType( pQcomTpmControlProtocol, 
                                                                  &tpmState, 
                                                                     &tpmType ))
  {
     LOGE("%a: Unable to get TPM type\r\n", __func__);    
     return EFI_NOT_FOUND;
  }

   //locate ChargerEx protocol to get charging status
  if (EFI_SUCCESS != gBS->LocateProtocol(&gChargerExProtocolGuid,
                                  NULL,
                                  (void**)&pChargerExProtocol))
  {
     // Unable to locate charger protocol
     LOGE("%a: Unable to locate charger protocol\r\n", __func__);
     return EFI_NOT_FOUND;
  }
  
  status = pChargerExProtocol->IsPowerOk(EFI_CHARGER_EX_POWER_FLASH_BATTERY_VOLTAGE_TYPE, &sPowerTypeInfo);
  
  if(EFI_UNSUPPORTED == status )
  {
      //ChargerDxe does not support battery status query for CDP and RUMI
      //platform types. For such platforms, proceed with initialisation
      //ignoring the charging/battery status
      if(tpmType == sTPM)
      {
          status = nvm_main (supportedAppNamesSTPM, spss_nvm_app_names_stpm_count_);
      }
      else
      {
          status = nvm_main (supportedAppNames, spss_nvm_app_names_count_);
      }
      LOGI("%a: SpNvm_init success\r\n", __func__);
	  goto exit_out;
  }
   
  if (EFI_SUCCESS != status)
  {
      // Unable to get the status
      LOGE("%a: Unable to get the IsPowerOk status\r\n", __func__);
      return EFI_FAILURE;
  }

  status = pChargerExProtocol->GetBatteryPresence(&bBatteryPresent);
  if(status != EFI_SUCCESS )
  {
      //Unable to get the status
      LOGE("%a: Unable to get GetBatteryPresence status: %d\r\n", __func__, status);
      return  EFI_FAILURE;
  }
  if(bBatteryPresent == FALSE)
  {
      //Battery is not present ,don't proceed further
      LOGE("%a: Battery is not present Do not proceed SPNVM_init \r\n", __func__);
      return EFI_FAILURE;
  }
  else
  {
      if(sPowerTypeInfo.bCanFlash == TRUE)
      {
          //if we reach here battery is present with charging status is above thresholds.
          //or Fake battery i.e Device is debug board platform
          LOGI("%a: proceed secnvm init\r\n", __func__);
          if(tpmType == sTPM)
          {
              status = nvm_main (supportedAppNamesSTPM, spss_nvm_app_names_stpm_count_);
          }
          else
          {
              status = nvm_main (supportedAppNames, spss_nvm_app_names_count_);
          }
          goto exit_out;
      }
      else
      {
          //Battery is present and Charging status is below threshold. Register for LPM events
          //ChargerApp broadcast LPM events when real battery is present
          status = SpNvmRegisterLPMCb(TRUE);
          if(status != EFI_SUCCESS)
          {
              LOGE("Register for LPM events Failed,Status :%d\r\n",status);
              return status;  
          }
          status = SpNvmRegisterEBSCb();
          if(status != EFI_SUCCESS)
          {
              LOGE("Register for ExitBootServices event Failed,Status :%d\r\n",status);
              return status;
          }
          LOGI("Charging status less than thresholds, SPNVMdxe Register for LPM,EBS events Success\r\n");
      }
  }
exit_out:
#ifdef RUN_SPU_HEALTH_SAMPLE_CODE
  if(status == EFI_SUCCESS)
  {
     struct sp_health_status_data status_data           = {0};
	 sp_health_status_t           health_status_param   = SP_HEALTH_ARI_MODE;
     EFI_SPCOM_PROTOCOL          *spcom_protocol_health = NULL;
	 
     if(EFI_SUCCESS == gBS->LocateProtocol (&gEfiSpcomProtocolGuid, NULL, (void**) &(spcom_protocol_health)))
     {
        if(EFI_SUCCESS == spcom_protocol_health->CheckSPHealth(health_status_param, &status_data))
		{
           LOGE("ARI mode [%d]\n", status_data.ari_lifecycle_state);
           LOGE("FIPS enabled [%d]\n", status_data.fips_enabled);
           LOGE("FIPS self test passed [%d]\n", status_data.fips_self_test_passed);
           LOGE("Sensors calibrated [%d]\n", status_data.sensors_calibrated);
           LOGE("POR indicator [0x%x]\n", status_data.por_indicator);
           LOGE("POR counter [0x%x]\n", status_data.por_data.por_counter);
           LOGE("Normal Boot Count Since POR [0x%x]\n", status_data.por_data.normal_boot_count_since_por);
           LOGE("Commit Count Since POR [0x%x]\n", status_data.por_data.commit_count_since_por);
           LOGE("Aux data0 [0x%x]\n", status_data.aux_data0);
           LOGE("Aux data1 [0x%x]\n", status_data.aux_data1);
           LOGE("Aux data2 [0x%x]\n", status_data.aux_data2);
           LOGE("Aux data3 [0x%x]\n", status_data.aux_data3);
           LOGE("ARI Fuse gauge percent [%d]\n", status_data.ari_fuse_gauge);
		}
		else
        {
           LOGE("CheckSPHealth failed");
		}
	 }
  }
#endif
  return status;
}

/** 
  SpNvmRegisterLPMCb
  
  @brief
  Register/Un-register for LPM Events
*/
EFI_STATUS SpNvmRegisterLPMCb(BOOLEAN register_Lpm)
{
  EFI_STATUS               Status                 = EFI_SUCCESS;
  EFI_RSC_HANDLER_PROTOCOL *pRscHandlerProtocol   = NULL;

  Status = gBS->LocateProtocol(&gEfiRscHandlerProtocolGuid, NULL, (VOID **) &pRscHandlerProtocol);
  
  if((EFI_SUCCESS == Status) && (pRscHandlerProtocol != NULL))
  {
     if(register_Lpm == TRUE)
     {
        Status = pRscHandlerProtocol->Register(SpNvmLPMCb, TPL_CALLBACK);
     }
     else
     {
        Status = pRscHandlerProtocol->Unregister(SpNvmLPMCb); 
     }
  }
  else
  {
     LOGE("%a: Locate protocol Failed,Status:%d\r\n", __func__, Status); 
  }
  return Status;
}

/** 
  SpNvmLPMCb
  
  @brief
  LPM callback Function ,processing LPM_EXIT event
*/
EFI_STATUS
EFIAPI SpNvmLPMCb (
  IN EFI_STATUS_CODE_TYPE   CodeType,
  IN EFI_STATUS_CODE_VALUE  Value,
  IN UINT32                 Instance,
  IN EFI_GUID               *CallerId,
  IN EFI_STATUS_CODE_DATA   *Data
  )
{
  LPM_EVENT_EXT_DATA * pLpmEventData = NULL;
  BOOLEAN              bMatch        = FALSE;
  EFI_STATUS           Status        = EFI_UNSUPPORTED;

  if (((CodeType & EFI_STATUS_CODE_TYPE_MASK) == EFI_PROGRESS_CODE ) &&
      (Data != NULL))
  {
    pLpmEventData = (LPM_EVENT_EXT_DATA*)( Data + 1);

      bMatch = CompareGuid(&(pLpmEventData->CalleeGuid), &gEfiClockProtocolGuid);
    if (bMatch == TRUE)
    {
      switch (pLpmEventData->LPMState)
      {
        case LPM_EXIT:
               LOGI("%a: LPM_EXIT Received,proceed sec_nvm Init\r\n", __func__);
               if(tpmType == sTPM)
               {
                 Status = nvm_main (supportedAppNamesSTPM, spss_nvm_app_names_stpm_count_);
               }
               else
               {
                 Status = nvm_main (supportedAppNames, spss_nvm_app_names_count_);
               }
        break;
        default:
               LOGE("%a: Invalid LPM State\r\n", __func__);
        break;
      }
    }
  }

  return Status;
}

/** 
  SpNvmRegisterEBSCb
  
  @brief
  Register for BootServices Exit event.
*/
STATIC EFI_STATUS SpNvmRegisterEBSCb(VOID)
{
   //Register to Exit Boot Service Event
   return gBS->CreateEventEx (EVT_NOTIFY_SIGNAL,
                      TPL_CALLBACK,
                      SpNvmExitBSCb,
                      NULL,
                      &gEfiEventExitBootServicesGuid,
                      &SpNvmExitBSEvent);
}

/** 
  SpNvmExitBSCb
  
  @brief
  Exit BootServices event cb.
*/
STATIC VOID SpNvmExitBSCb (
  EFI_EVENT        Event,
  VOID             *Context
  )
{
   EFI_STATUS           Status       = EFI_FAILURE;

   Status = SpNvmRegisterLPMCb(FALSE); 
   if(Status != EFI_SUCCESS)
   {
      LOGE("%a:UnRegister for LPM events Failed,Status: %d\r\n",__func__,Status);  
   }
   LOGI("%a: Received ExitBS cb and UnRegister for LPMcb success:%d\r\n",__func__);
}
