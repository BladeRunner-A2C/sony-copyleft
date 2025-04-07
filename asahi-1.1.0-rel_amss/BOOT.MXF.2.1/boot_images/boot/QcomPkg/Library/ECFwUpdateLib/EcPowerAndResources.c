/** @file EcPowerAndResources.c

  Provides EC power and voting related routines.

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights
  Reserved. Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------
  2023/03/29     sumesahu    Add support for Power-off EC during off mode charging &
                             enable check for power level.
  2023/02/04     sumesahu    FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine
                             and code refactoring
  2022/12/08     bkulkarn    Update Hamoa EC FW partition size/I2C core instance, code refactoring
  2022/11/22     bkulkarn    Support to detect off-mode charging
  2022/09/22     sumesahu    Support for power related changes
  2022/07/29     bkulkarn    Initial version
=============================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomLib.h>
#include <Library/ECFwUpdateLib.h>
#include <Library/ECFwUpdateLib/EcPowerAndResources.h>
#include <Protocol/EFIChargerEx.h>
#include <Protocol/EFIPlatformInfo.h>
#include "DDITlmm.h"
#include "DALSys.h"

extern EC_DEVICE_CONTEXT *deviceContext;

static EFI_QCOM_PMIC_GPIO_PROTOCOL *gPmicGpioProtocol = NULL;
static EFI_CHARGER_EX_PROTOCOL     *gChargerExProtocol = NULL;

#define MINIMUM_BATTERY_CHARGE_PERCENT      (25)

/**
 * Function to check if device is currently in off-mode charging state.
 *
 * @param pOffModeCharging          Pointer to stor ethe off mode charging status value.
 *
 * @retval EFI_SUCCESS              Device is not in off-mode charging.
 & @retval EFI_OUT_OF_RESOURCES     Device is in off-mode charging.
 **/
EFI_STATUS
EcGetOffModeChargingStatus(
  OUT BOOLEAN *pOffModeCharging
)
{
  EFI_STATUS                status = EFI_SUCCESS;

  if ((NULL == gChargerExProtocol) ||
      (NULL == gChargerExProtocol->IsOffModeCharging))
  {
    EC_E("gChargerExProtocol handle is invalid\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!pOffModeCharging)
  {
    EC_E("pOffModeCharging is NULL!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  status = gChargerExProtocol->IsOffModeCharging(pOffModeCharging);
  if (EFI_ERROR(status))
  {
    EC_E("IsOffModeCharging failed with %r\n", status);
    goto Exit;
  }

  if (TRUE == (*pOffModeCharging))
  {
    EC_W("Device is in off-mode charging\n");
  }
  else
  {
    EC_I("Device is not in off-mode charging\n");
  }

Exit:
  return status;
}

/**
 * Function to initialize resource related protocols for EC.
 *
 * @param none
 *
 * @retval status    A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
EcPowerInit()
{
  EFI_STATUS    status = EFI_SUCCESS;

  status = gBS->LocateProtocol(
    &gQcomPmicGpioProtocolGuid,
    NULL,
    (VOID **)&gPmicGpioProtocol
    );
  EC_ERROR_HANDLER(status, LocateProtocol, Exit);

  status = gBS->LocateProtocol(
    &gChargerExProtocolGuid,
    NULL,
    (void**)&gChargerExProtocol
    );
  EC_ERROR_HANDLER(status, LocateProtocol, Exit);

 Exit:
  return status;
}

/**
 * Function Handler to Off Mode charging.
 *
 * @param none
 *
 * @retval status    A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
EcOffModeChargingHandler()
{
  EFI_STATUS                        status = EFI_SUCCESS;
  EFI_PLATFORMINFO_PLATFORM_TYPE    platformType = EFI_PLATFORMINFO_TYPE_UNKNOWN;
  BOOLEAN                           bOffModeChargingStatus = FALSE;

  EC_TRACE();

  if (!gPmicGpioProtocol)
  {
    status = EFI_DEVICE_ERROR;
    EC_E("gPmicGpioProtocol handle is invalid!\n");
    goto Exit;
  }

  status = GetPlatformType(&platformType);
  EC_ERROR_HANDLER(status, GetPlatformType, Exit);

  if (EFI_PLATFORMINFO_TYPE_RUMI == platformType)
  {
    EC_E("Detected RUMI platform, skip powering on EC!\n", status);
    status = EFI_UNSUPPORTED;
    goto Exit;
  }

  status = EcGetOffModeChargingStatus(&bOffModeChargingStatus);
  EC_ERROR_HANDLER(status, EcGetOffModeChargingStatus, Exit);

  if (TRUE == bOffModeChargingStatus)
  {
    status  = gPmicGpioProtocol->CfgMode(PMIC_INDEX_FOR_EC_PON, PMIC_GPIO_INDEX_FOR_EC_PON, EFI_PM_GPIO_DIG_OUT);
    status |= gPmicGpioProtocol->SetVoltageSource(PMIC_INDEX_FOR_EC_PON, PMIC_GPIO_INDEX_FOR_EC_PON, EFI_PM_GPIO_VIN0);
    status |= gPmicGpioProtocol->SetOutBufCfg(PMIC_INDEX_FOR_EC_PON, PMIC_GPIO_INDEX_FOR_EC_PON, EFI_PM_GPIO_OUT_BUF_CFG_CMOS);
    status |= gPmicGpioProtocol->SetOutDrvStr(PMIC_INDEX_FOR_EC_PON, PMIC_GPIO_INDEX_FOR_EC_PON, EFI_PM_GPIO_OUT_DRV_STR_HIGH);
    status |= gPmicGpioProtocol->SetOutSrcCfg(PMIC_INDEX_FOR_EC_PON, PMIC_GPIO_INDEX_FOR_EC_PON, EFI_PM_GPIO_SRC_GND);
    status |= gPmicGpioProtocol->SetOutputLevel(PMIC_INDEX_FOR_EC_PON, PMIC_GPIO_INDEX_FOR_EC_PON, EFI_PM_GPIO_LEVEL_LOW);
    status |= gPmicGpioProtocol->Enable(PMIC_INDEX_FOR_EC_PON, PMIC_GPIO_INDEX_FOR_EC_PON, TRUE);
    EC_ERROR_HANDLER(status, EcOffModeChargingHandler, Exit);
  }

Exit:
  if ((status == EFI_SUCCESS) &&
    (TRUE == bOffModeChargingStatus))
  {
    status = EFI_OUT_OF_RESOURCES;
  }
  return status;
}

/**
 * Determine if the battery power levels have sufficient power
 * to permit firmware update to proceed based on the pre-condition
 * checks required for firmware update.
 *
 * @param bPowerGood    - TRUE : Sufficient power to proceed with firmware update.
 *                        FALSE: Insufficient power to proceed with firmware update.
 * @retval status       A EFI_STATUS indicating result of the operation.
 */
EFI_STATUS
EcCheckPowerLevel(
  OUT BOOLEAN *bPowerGood
)
{
  EFI_STATUS                        status = EFI_SUCCESS;
  EFI_PLATFORMINFO_PLATFORM_TYPE    platformType = EFI_PLATFORMINFO_TYPE_UNKNOWN;
  UINT32                            currentSOC = 0;

  if (!bPowerGood)
  {
    status = EFI_INVALID_PARAMETER;
    EC_E("Invalid bPowerGood handle!\n");
    goto Exit;
  }

  status = GetPlatformType(&platformType);
  EC_ERROR_HANDLER(status, GetPlatformType, Exit);

  if ((EFI_PLATFORMINFO_TYPE_MTP == platformType) ||
    (EFI_PLATFORMINFO_TYPE_CDP == platformType) ||
    (platformType == EFI_PLATFORMINFO_TYPE_IDP))
  {
    *bPowerGood = TRUE;
    goto Exit;
  }

  if (!gChargerExProtocol)
  {
    EC_E("gChargerExProtocol handle is NULL\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!(gChargerExProtocol->GetChargingStatus))
  {
    EC_E("gChargerExProtocol->GetChargingStatus handle is NULL\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  
  // Get current state of charge
  status = gChargerExProtocol->GetChargingStatus(
    &currentSOC,
    NULL);
  EC_ERROR_HANDLER(status, GetChargingStatus, Exit);

  EC_W("Current battery capacity: %d\n", currentSOC);

  if (currentSOC < MINIMUM_BATTERY_CHARGE_PERCENT)
  {
    *bPowerGood = FALSE;
  }
  else
  {
    *bPowerGood = TRUE;
  }

Exit:
  return status;
}

/**
 * Function to vote for given TLMM GPIO with corresponding GPIO_VALUE (LOW/HIGH)
 *
 * @param gpio_num          Indicates the GPIO-number to be updated.
 * @param gpio_value        Indicates the GPIO-value to be updated for given GPIO.
 *
 * @retval status           A EFI_STATUS indicating result of the operation.
 */
EFI_STATUS
EcWriteGpio (
  UINT8 gpioNumber,
  DALGpioValueType gpioValue
  )
{
  EFI_STATUS        status = EFI_SUCCESS;
  DALResult         result = DAL_ERROR;
  DalDeviceHandle*  tlmmHandle = NULL;

  /* Create a DAL-formatted GPIO configuration for */
  DALGpioSignalType config = (DALGpioSignalType)DAL_GPIO_CFG(
    gpioNumber,
    0,
    DAL_GPIO_OUTPUT,
    DAL_GPIO_NO_PULL,
    DAL_GPIO_4MA);

  /* Initialize DALSYS and attach to the DAL TLMM driver. */
  DALSYS_InitMod(NULL);

  result = DAL_DeviceAttach(
    DALDEVICEID_TLMM,
    &tlmmHandle);
  if ((DAL_ERROR == result) ||
      (NULL == tlmmHandle))
  {
    EC_E("Fail to Initialize and attach DAL TLMM driver", result);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  /* Configure the GPIO. */
  result = DalTlmm_ConfigGpio(
    tlmmHandle,
    config,
    DAL_TLMM_GPIO_ENABLE);
  if (DAL_SUCCESS == result)
  {
    /* Drive the GPIO based on gpio_value. */
    result = DalTlmm_GpioOut(
        tlmmHandle,
        config,
        gpioValue);
    if (DAL_SUCCESS != result)
    {
      EC_E("DalTlmm_GpioOut() failed with %d\n", result);
      status = EFI_DEVICE_ERROR;
      goto Exit;
    }
  }
  else
  {
    EC_E("DalTlmm_ConfigGpio() failed with %d\n", result);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

Exit:
  if (tlmmHandle)
  {
    result = DAL_DeviceDetach(tlmmHandle);
    if (DAL_SUCCESS != result)
    {
      EC_E("DAL_DeviceDetach() failed with %d\n", result);
      status = EFI_DEVICE_ERROR;  
    }
    tlmmHandle = NULL;
  }
  return status;
}
