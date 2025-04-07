/** @file
ButtonsLib.c

Button driver is responsible for detecting key press/release through PMIC HW
and service. It implements the interfaces of simple text input protocol.

This file is platform dependent, it supports ButtonsDxe based on the platform.

Copyright (c) 2012-2022 Qualcomm Technologies, Inc. All rights reserved.
Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
EDIT HISTORY

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who      what, where, why
--------   ---      ----------------------------------------------------------
10/19/18   px       Fix the combo key not able to detect issue
01/22/17   ma       Clamshell support 845
09/13/16   ma       Support QRD845
04/04/16   ma       Change GPIO PULL UP source to VIN0
02/04/16   ma       Port to 845
=============================================================================*/

#include <Base.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PcdLib.h>
#include <Library/ButtonsLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/OfflineCrashDump.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIPmicGpio.h>
#include "ButtonsDtParser.h"
#include <Protocol/EFITlmm.h>

#define NUMBER_OF_KEYS                   5

// SDAM storage location for the button press
#define BUTTONS_LIB_SDAM_PMIDX           0
#define BUTTONS_LIB_SDAM_NUM             2
#define BUTTONS_LIB_SDAM_ADDR            76

#define TLMM_GPIO                        0
#define PMIC_GPIO                        1

// Platform Key Map Index 
#define PWR                              0x0
#define VOL_UP                           0x1
#define VOL_DOWN                         0x2
#define HOME                             0x3 
#define CAMERA                           0x4 

#define KEY_RESERVED                     0

#define BTN_DT_IDX                       0
#define BTN_DT_GPIO_TYPE_IDX             1
#define BTN_DT_PMIC_IDX                  2
#define BTN_DT_GPIO_NUM_IDX              3
#define BTN_DT_SRC_PULL_IDX              4
#define BTN_DT_VOL_SRC_IDX               5
#define BTN_DT_OUT_BUT_STRNTH_IDX        6
#define BTN_DT_SRC_IDX                   7

typedef struct
{
   UINT8 ButtonIdx;
   UINT8 GpioType;
   UINT8 PmicIndex;
   UINT8 GpioNumber;
   UINT8 PullSource;
   UINT8 VoltageSource;
   UINT8 OutBufStrength;
   UINT8 Source;
}BtnGpioCfg;

// DT Mapping between GPIO configs and Platform Key maps 
UINT8 PF_DT_KEY_MAP_IDX[NUMBER_OF_KEYS] = {VOL_UP, HOME, CAMERA, PWR, VOL_DOWN};

const char *Err_Msg[] = {
   "VOL+",
   "Home",
   "Camera"
   "PWR",
   "VOL-"
};

extern EFI_QCOM_PMIC_GPIO_PROTOCOL *PmicGpioProtocol;
extern EFI_GUID gQcomTokenSpaceGuid;

EFI_TLMM_PROTOCOL *TlmmProtocol = NULL;

extern KEY_TYPE KeyMap[NUMBER_OF_KEYS];

static ButtonDtGpioConfig *ButtonDtGpioCfg = NULL;

UINT16 g_sdam_pmic_idx = BUTTONS_LIB_SDAM_PMIDX;
UINT16 g_sdam_number = BUTTONS_LIB_SDAM_NUM;
UINT16 g_sdam_address = BUTTONS_LIB_SDAM_ADDR;

/**
Enable the GPIO for Input

@param  GpioNumber               GPIO Number
@retval EFI_SUCCESS              Enable successful
@retval non EFI_SUCCESS          Enable failed

**/
EFI_STATUS EnablePmicInput ( BtnGpioCfg *Cfg )
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(PmicGpioProtocol)
  {
     Status |= PmicGpioProtocol->CfgMode(Cfg->PmicIndex,
                                         Cfg->GpioNumber,
                                         EFI_PM_GPIO_DIG_IN);
    
    Status |= PmicGpioProtocol->SetVoltageSource(Cfg->PmicIndex,
                                                Cfg->GpioNumber,
                                                Cfg->VoltageSource);

    Status |= PmicGpioProtocol->PullSel(Cfg->PmicIndex,
                                        Cfg->GpioNumber,
                                        Cfg->PullSource);

     if ( EFI_ERROR (Status) )
     {
         DEBUG(( EFI_D_ERROR, "EnableInput: ConfigDigitalInput failed Status = (0x%x)\r\n", Status));
         return Status;
     }
  }

   return Status;
}

EFI_STATUS
EnableTlmmInput ( BtnGpioCfg *Cfg )
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (TlmmProtocol == NULL) 
  {
    Status = gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (void **)&TlmmProtocol);
    if (Status != EFI_SUCCESS )
    {
      DEBUG(( EFI_D_ERROR, "ButtonsTargetLib: Failed to locate Tlmm Protocol, Status =  (0x%x)\r\n", Status ));
      return Status;
    }
  }

  Status = TlmmProtocol->ConfigGpio((UINT32)EFI_GPIO_CFG(Cfg->GpioNumber,
                                                         Cfg->Source,
                                                         Cfg->VoltageSource,
                                                         Cfg->PullSource,
                                                         Cfg->OutBufStrength), TLMM_GPIO_ENABLE);
  if ( Status != EFI_SUCCESS ) 
  {
    DEBUG((EFI_D_ERROR, "ButtonsTargetLib: Configure GPIO %d failed!\n", Cfg->GpioNumber));
    return Status;
  }


   return Status;
}

/**
Initialize all button GPIOs on PMIC/TLMM for input based
on platform

@param  None
@retval EFI_SUCCESS              Configuration successful
@retval non EFI_SUCCESS          Configuration failed

**/
EFI_STATUS ConfigureButtonGPIOs ( VOID )
{
   EFI_STATUS Status = EFI_SUCCESS;
   BtnGpioCfg GpioCfg = {0};
   int i;

   ButtonDtGpioCfg = (ButtonDtGpioConfig *)ButtonDtGetNode(BUTTON_DT_NODE_GPIO_CONFIG);

   if ((ButtonDtGpioCfg != NULL) && (ButtonDtGpioCfg->ButtonGpioCfg != NULL) &&
      (ButtonDtGpioCfg->ButtonGpioCfgCount > 0))
   {
      for(i = 0; i < ButtonDtGpioCfg->ButtonGpioCfgCount; i++)
      {
         GpioCfg.ButtonIdx = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_IDX];
         GpioCfg.GpioType = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_GPIO_TYPE_IDX];
         GpioCfg.PmicIndex = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_PMIC_IDX];
         GpioCfg.GpioNumber = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_GPIO_NUM_IDX];
         GpioCfg.PullSource = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_SRC_PULL_IDX];
         GpioCfg.VoltageSource = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_VOL_SRC_IDX];
         GpioCfg.OutBufStrength = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_OUT_BUT_STRNTH_IDX];
         GpioCfg.Source = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_SRC_IDX];

         if(KeyMap[PF_DT_KEY_MAP_IDX[GpioCfg.ButtonIdx]] != KEY_RESERVED)
         {
            if(GpioCfg.GpioType == PMIC_GPIO)
            {
               Status = EnablePmicInput(&GpioCfg);
            }
            else if(GpioCfg.GpioType == TLMM_GPIO)
            {
               Status = EnableTlmmInput(&GpioCfg);
            }
            else
            {
               Status = EFI_UNSUPPORTED;
               DEBUG(( EFI_D_ERROR, "ConfigureButtonGPIOs: GPIO Type Not Supported for %s button, status = (0x%x)\r\n", Err_Msg[GpioCfg.ButtonIdx], Status));
               return Status;
            }

            if ( EFI_ERROR (Status) )
            {
               DEBUG(( EFI_D_ERROR, "ConfigureButtonGPIOs: EnableInput failed for %s button, Status = (0x%x)\r\n", Status, Err_Msg[GpioCfg.ButtonIdx]));
               return Status;
            }
         }
         else
         {
            DEBUG(( EFI_D_WARN, "ConfigureButtonGPIOs: Button %s not supported on the plaform\r\n", Err_Msg[GpioCfg.ButtonIdx]));
         }
      
      }
   }
   else
   {
      DEBUG( (EFI_D_ERROR, "Configure: Buttons gpio dt config parsing failed, status = (0x%x)\r\n", Status) );
      return EFI_INVALID_PARAMETER;
   }

   return Status;

}


/**
Read gpio status on PMIC.

@param  GpioNumber               GPIO number..
@param  pGpioButtonPressed       Pointer storing the value of button activity (press).

@retval EFI_SUCCESS              Retrieve status successfully
@retval non EFI_SUCCESS          Retrieve status failed

**/
EFI_STATUS ReadGpioStatus( UINT16 KeyIndex, BOOLEAN *pGpioButtonPressed )
{
   EFI_STATUS Status = EFI_SUCCESS;
   BOOLEAN GpioStatus = FALSE;
   UINT32 TlmmGpioStatus = 0;
   BtnGpioCfg GpioCfg = {0};

   if (ButtonDtGpioCfg == NULL)
   {
      ButtonDtGpioCfg = (ButtonDtGpioConfig *)ButtonDtGetNode(BUTTON_DT_NODE_GPIO_CONFIG);
   }

   if ((ButtonDtGpioCfg == NULL) || (ButtonDtGpioCfg->ButtonGpioCfgCount == 0) || 
      (ButtonDtGpioCfg->ButtonGpioCfg == NULL))
   {
      Status = EFI_INVALID_PARAMETER;
      DEBUG( (EFI_D_ERROR, "ReadGpioStatus: Buttons Gpio dt config parsing failed, status = (0x%x)\r\n", Status) );
      return EFI_INVALID_PARAMETER;
   }

   GpioCfg.GpioType = ButtonDtGpioCfg->ButtonGpioCfg[KeyIndex * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_GPIO_TYPE_IDX];
   GpioCfg.PmicIndex = ButtonDtGpioCfg->ButtonGpioCfg[KeyIndex * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_PMIC_IDX];
   GpioCfg.GpioNumber = ButtonDtGpioCfg->ButtonGpioCfg[KeyIndex * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_GPIO_NUM_IDX];
   GpioCfg.PullSource = ButtonDtGpioCfg->ButtonGpioCfg[KeyIndex * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_SRC_PULL_IDX];
   GpioCfg.VoltageSource = ButtonDtGpioCfg->ButtonGpioCfg[KeyIndex * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_VOL_SRC_IDX];
   GpioCfg.OutBufStrength = ButtonDtGpioCfg->ButtonGpioCfg[KeyIndex * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_OUT_BUT_STRNTH_IDX];

   // Detect if key is supported
   if (KeyMap[PF_DT_KEY_MAP_IDX[KeyIndex]] == KEY_RESERVED) {
      return EFI_NOT_FOUND;
   }

   // Check if Gpio type is PMIC or TLMM GPIO
   if (GpioCfg.GpioType == TLMM_GPIO) 
   {
     if (TlmmProtocol != NULL)
     {
       Status = TlmmProtocol->GpioIn((UINT32)EFI_GPIO_CFG(GpioCfg.GpioNumber,
                                                         0,
                                                         GpioCfg.VoltageSource,
                                                         GpioCfg.PullSource,
                                                         GpioCfg.OutBufStrength), &TlmmGpioStatus);
       if ( EFI_ERROR (Status) )
       {
          DEBUG(( EFI_D_ERROR, "ReadGpioStatus: GpioIn failed Status = (0x%x)\r\n", Status));
       }
       else
       {
          *pGpioButtonPressed = ( TlmmGpioStatus == GPIO_HIGH_VALUE ) ? TRUE : FALSE;
       }
     }
   }
   else 
   {
      if(PmicGpioProtocol)
      {
         Status = PmicGpioProtocol->IrqStatus( GpioCfg.PmicIndex,
                                            (EFI_PM_GPIO_PERIPH_INDEX)(GpioCfg.GpioNumber),
                                            EFI_PM_IRQ_STATUS_RT,
                                            &GpioStatus
                                          );
         if ( EFI_ERROR (Status) )
         {
            DEBUG(( EFI_D_ERROR, "ReadGpioStatus: IrqStatus failed Status = (0x%x)\r\n", Status));
         }
         else
         {
            // this is because we initially have pull-ups on the GPIOs
            *pGpioButtonPressed =  ( GpioStatus == TRUE ) ? FALSE : TRUE;
         }
      }
   }

   return Status;
}


