/** @file
ButtonsBootLib.c

Boot Button driver is responsible for detecting key press/release through PMIC HW
and service. The key press is recorded into SMEM so UEFI can read it back.


Copyright (c) 2019-2022, 2023 Qualcomm Technologies, Inc. All rights reserved.
Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
EDIT HISTORY

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when        who      what, where, why
----------  ---      ----------------------------------------------------------
2019-10-07  rh       Create a BOOT version of the ButtonsLib
=============================================================================*/

#include <Base.h>
#include <stdio.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>

#include <api/pmic/pm/pm_version.h>
#include <api/pmic/pm/pm_pon.h>
#include <api/pmic/pm/pm_gpio.h>
#include <api/pmic/pm/pm_resources_and_types.h>
#include <api/pmic/pm/pm_sdam.h>
#include <smem.h>
#include "busywait.h"

#include "boot_logger.h"

#include "ButtonsDtParser.h"

#include <DDITlmm.h>

static uint8 g_ButtonsBootLibKeyCode;

DalDeviceHandle * tlmm_handle;

/* Error message wrapper */
#define STATUS_MSG_LEN 300
#define STATUS_MSG_HEAD_LEN 5
static char status_message[STATUS_MSG_LEN + STATUS_MSG_HEAD_LEN]="BTN: ";

#define log_message(...)      \
  snprintf((status_message+STATUS_MSG_HEAD_LEN), STATUS_MSG_LEN,__VA_ARGS__); \
  boot_log_message(status_message);

#define SDAM3_MEM_076                    76

#define NUMBER_OF_KEYS                   5

// Buttons Bit map
#define POWER_BUTTON_BMAP                (1 << 0)
#define VOLUME_UP_BUTTON_BMAP            (1 << 1)
#define VOLUME_DN_BUTTON_BMAP            (1 << 2)
#define HOME_BUTTON_BMAP                 (1 << 3)

// GPIO Numbers
#define VOLUME_UP_BUTTON_GPIO            PM_GPIO_6

#define GPIO_PM_DEVICE_INDEX             1

// Button Index 
#define VOL_UP_BTN_IDX                   0

#define TLMM_GPIO                        0
#define PMIC_GPIO                        1

#define TLMM_GPIO_CFG(gpio, func, dir, pull, drive) \
         (((gpio) & 0x3FF)<< 4 | \
          ((func) & 0xF)|        \
          ((dir)  & 0x1) << 14|  \
          ((pull) & 0x3) << 15|  \
          ((drive)& 0xF) << 17| 0x20000000)

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

static UINT8 KeyMap[NUMBER_OF_KEYS] = {0};

typedef struct
{
   UINT8 ButtonIdx;
   UINT8 GpioType;
   UINT8 PmicIndex;
   UINT8 GpioNumber;
   UINT8 IsSourcePulls;
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

static ButtonDtGpioConfig *ButtonDtGpioCfg = NULL;

/**
Enable the GPIO for Input
**/
pm_err_flag_type BootEnablePmicInput (BtnGpioCfg *Cfg)
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;

   Status |= pm_gpio_cfg_mode(Cfg->PmicIndex,
                              Cfg->GpioNumber,
                              PM_GPIO_DIG_IN);

   Status |= pm_gpio_set_voltage_source(Cfg->PmicIndex,
                                        Cfg->GpioNumber,
                                        Cfg->VoltageSource);

   Status |= pm_gpio_set_out_drv_str(Cfg->PmicIndex,
                                     Cfg->GpioNumber,
                                     Cfg->OutBufStrength);

   Status |= pm_gpio_set_out_src_cfg(Cfg->PmicIndex,
                                     Cfg->GpioNumber,
                                     Cfg->Source);

   Status |= pm_gpio_set_pull_sel(Cfg->PmicIndex,
                                  Cfg->GpioNumber,
                                  Cfg->IsSourcePulls);

   if ( Status != PM_ERR_FLAG_SUCCESS ) {
       log_message ("Error enabling GPIO lines");
       return Status;
   }

   return Status;
}

pm_err_flag_type
BootEnableTlmmInput ( BtnGpioCfg *Cfg )
{
   DALResult result = DAL_ERROR;
   DALGpioEnableType dal_enable = DAL_TLMM_GPIO_ENABLE;

   if(tlmm_handle)
   {
      result = DalTlmm_ConfigGpio(tlmm_handle, (UINT32)TLMM_GPIO_CFG(Cfg->GpioNumber,
                                                                     Cfg->Source,
                                                                     Cfg->VoltageSource,
                                                                     Cfg->IsSourcePulls,
                                                                     Cfg->OutBufStrength), dal_enable);
   }

   if (result != DAL_SUCCESS) 
   {
      log_message ("ButtonsBootLib: Configure GPIO for TLMM failed!");
   }

   return result;
}

static pm_err_flag_type
BootGetSupportedKeys( VOID )
{
   ButtonDtPfKeyMapsConfig *PfDtKeyMaps = NULL;
   int i;

   PfDtKeyMaps = (ButtonDtPfKeyMapsConfig *)ButtonDtGetNode(BUTTON_DT_NODE_PF_KEY_MAP_CONFIG);

   if ((PfDtKeyMaps == NULL) || (PfDtKeyMaps->PfKeyMapsCount > NUMBER_OF_KEYS) ||
      (PfDtKeyMaps->PfKeyMapsConfig == NULL))
   {
      log_message("Key Maps dt config parsing failed");
      return PM_ERR_FLAG_INVALID_PARAMETER;
   }

   for (i = 0; i < PfDtKeyMaps->PfKeyMapsCount; i++) 
   {
      KeyMap[i] = PfDtKeyMaps->PfKeyMapsConfig[i];    
   }

   return PM_ERR_FLAG_SUCCESS;
}


/**
Initialize all button GPIOs on PMIC/TLMM for input based
on platform
**/
pm_err_flag_type BootConfigureButtonGPIOs ( VOID )
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;
   BtnGpioCfg GpioCfg = {0};
   int i;

   ButtonDtGpioCfg = (ButtonDtGpioConfig *)ButtonDtGetNode(BUTTON_DT_NODE_GPIO_CONFIG);

   if ((ButtonDtGpioCfg != NULL) && (ButtonDtGpioCfg->ButtonGpioCfg != NULL) &&
      (ButtonDtGpioCfg->ButtonGpioCfgCount > 0))
   {
      if (BootGetSupportedKeys() != PM_ERR_FLAG_SUCCESS)
      {
         log_message ("Buttons not supported on this platform");
         return PM_ERR_FLAG_INVALID_PARAMETER;
      }

      for(i = 0; i < ButtonDtGpioCfg->ButtonGpioCfgCount; i++)
      {
         GpioCfg.ButtonIdx = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_IDX];
         GpioCfg.GpioType = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_GPIO_TYPE_IDX];
         GpioCfg.PmicIndex = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_PMIC_IDX];
         GpioCfg.GpioNumber = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_GPIO_NUM_IDX];
         GpioCfg.IsSourcePulls = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_SRC_PULL_IDX];
         GpioCfg.VoltageSource = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_VOL_SRC_IDX];
         GpioCfg.OutBufStrength = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_OUT_BUT_STRNTH_IDX];
         GpioCfg.Source = ButtonDtGpioCfg->ButtonGpioCfg[i * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_SRC_IDX];

         if(KeyMap[PF_DT_KEY_MAP_IDX[GpioCfg.ButtonIdx]] != KEY_RESERVED)
         {
            if(GpioCfg.GpioType == PMIC_GPIO)
            {
               Status = BootEnablePmicInput(&GpioCfg);
            }
            else if(GpioCfg.GpioType == TLMM_GPIO)
            {
               Status = BootEnableTlmmInput(&GpioCfg);
            }
            else
            {
               log_message ("GPIO Type Not Supported for %s btn", Err_Msg[GpioCfg.ButtonIdx]);
               return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
            }

            if( Status != PM_ERR_FLAG_SUCCESS )
            {
               log_message ("Error enabling GPIO lines for %s btn", Err_Msg[GpioCfg.ButtonIdx]);
               return Status;
            }
         }
         else
         {
            log_message ("Button %s not supported on the plaform", Err_Msg[GpioCfg.ButtonIdx]);
         }
      }
   }
   else
   {
      log_message ("Buttons Dt Configs Parsing failed");
      return PM_ERR_FLAG_INVALID_PARAMETER;
   }

   return Status;
}


/**
Read gpio status on PMIC.
**/
pm_err_flag_type BootReadGpioStatus( BtnGpioCfg *Cfg, BOOLEAN *pGpioButtonPressed )
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;
   BOOLEAN GpioStatus = FALSE;

   Status = pm_gpio_irq_status( Cfg->PmicIndex,
                                (pm_gpio_perph_index)(Cfg->GpioNumber),
                                PM_IRQ_STATUS_RT,
                                &GpioStatus
                               );

   if ( Status != PM_ERR_FLAG_SUCCESS ) {
       log_message ("Error getting GPIO status, GPIO %d", Cfg->GpioNumber + 1);
   } else {
       // this is because we initially have pull-ups on the GPIOs
       *pGpioButtonPressed =  ( GpioStatus == TRUE ) ? FALSE : TRUE;
   }

   return Status;
}

pm_err_flag_type BootPollPowerKey(BOOLEAN *pPowerKey)
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;

   Status = pm_pon_irq_status(0, PM_PON_IRQ_KPD_PWR_N_DEB, PM_IRQ_STATUS_RT, pPowerKey);

   if ( Status != PM_ERR_FLAG_SUCCESS ) {
      log_message ("Error getting PWR button status");
   }
   return Status;
}

pm_err_flag_type BootPollVolDwnKey(BOOLEAN *pKey)
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;

   Status = pm_pon_irq_status(0, PM_PON_IRQ_RESIN_N_DEB, PM_IRQ_STATUS_RT, pKey);

   if ( Status != PM_ERR_FLAG_SUCCESS ) {
      log_message ("Error getting VOL- button status");
   }
   return Status;
}

/* Public API, capture button status */
void CaptureBootButtonsState(VOID)
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;
   BOOLEAN KeyState = FALSE;
   uint8 ButtonsBitMap = 0;
   BtnGpioCfg GpioCfg = {0};

   Status = BootConfigureButtonGPIOs ();
   if (Status != PM_ERR_FLAG_SUCCESS) {
      log_message ("Error configure buttons GPIO");
      return;
   }
   /* Wait for pull up after GPIO configuration */
   busywait(200);

   Status = BootPollVolDwnKey(&KeyState);
   ButtonsBitMap |= KeyState ? VOLUME_DN_BUTTON_BMAP : 0;

   Status |= BootPollPowerKey(&KeyState);
   ButtonsBitMap |= KeyState ? POWER_BUTTON_BMAP : 0;

   if ((ButtonDtGpioCfg != NULL) && (ButtonDtGpioCfg->ButtonGpioCfg != NULL) &&
      (ButtonDtGpioCfg->ButtonGpioCfgCount > 0))
   {
      GpioCfg.PmicIndex = ButtonDtGpioCfg->ButtonGpioCfg[VOL_UP_BTN_IDX * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_PMIC_IDX];
      GpioCfg.GpioNumber = ButtonDtGpioCfg->ButtonGpioCfg[VOL_UP_BTN_IDX * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_GPIO_NUM_IDX];
      Status |= BootReadGpioStatus(&GpioCfg, &KeyState);
   }
   else
   {
      Status |= PM_ERR_FLAG_INVALID_PARAMETER;
   }

   ButtonsBitMap |= KeyState ? VOLUME_UP_BUTTON_BMAP : 0;

   if (Status != PM_ERR_FLAG_SUCCESS) {
      log_message ("Error reading button status, Error code %d", Status);
   } else {
      /* Write the content of ButtonBitMap into shared memory */
      g_ButtonsBootLibKeyCode = ButtonsBitMap;
   }

   /* Save the result to the SDAM also */
   Status = pm_sdam_mem_write(PMIC_A, PM_SDAM_3, SDAM3_MEM_076, 1, &g_ButtonsBootLibKeyCode);
   if (Status != PM_ERR_FLAG_SUCCESS) {
      log_message ("Error writing to SDAM");
   }
}

/* Public API, Return button status */
int32 BootButtonsStateRead(uint32 *ButtonState)
{
   pm_err_flag_type Status = PM_ERR_FLAG_SUCCESS;
   BOOLEAN KeyState = FALSE;
   uint32 ButtonsBitMap = 0;
   BtnGpioCfg GpioCfg = {0};

   if (ButtonState == NULL) {
      return -1;
   }

   Status = BootPollVolDwnKey(&KeyState);
   ButtonsBitMap |= KeyState ? VOLUME_DN_BUTTON_BMAP : 0;

   Status |= BootPollPowerKey(&KeyState);
   ButtonsBitMap |= KeyState ? POWER_BUTTON_BMAP : 0;

   if (ButtonDtGpioCfg == NULL)
   {
      ButtonDtGpioCfg = (ButtonDtGpioConfig *)ButtonDtGetNode(BUTTON_DT_NODE_GPIO_CONFIG);
   }

   if ((ButtonDtGpioCfg != NULL) && (ButtonDtGpioCfg->ButtonGpioCfg != NULL) &&
      (ButtonDtGpioCfg->ButtonGpioCfgCount > 0))
   {
      GpioCfg.PmicIndex = ButtonDtGpioCfg->ButtonGpioCfg[VOL_UP_BTN_IDX * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_PMIC_IDX];
      GpioCfg.GpioNumber = ButtonDtGpioCfg->ButtonGpioCfg[VOL_UP_BTN_IDX * BTN_DT_GPIO_CONFIG_ITEM_SIZE + BTN_DT_GPIO_NUM_IDX];
      Status |= BootReadGpioStatus(&GpioCfg, &KeyState);
   }
   else
   {
      Status |= PM_ERR_FLAG_INVALID_PARAMETER;
   }
   ButtonsBitMap |= KeyState ? VOLUME_UP_BUTTON_BMAP : 0;

   *ButtonState = ButtonsBitMap;

   if (Status == PM_ERR_FLAG_SUCCESS) {
      return 0;
   } else {
      return -1;
   }
}
