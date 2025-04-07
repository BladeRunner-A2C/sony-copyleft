/*! @file PmicGpioProtocol.c 

*  PMIC-GPIO MODULE Stub Code
*  This file contains stub code to support the PMIC GPIO module.
*
* Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved. 
* Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when          who          what, where, why
--------      ---          ------------------------------------------------
12/09/2022    gappalan     New file added
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <Protocol/EFIPmicGpio.h>


/*===========================================================================
                  EXTERNAL FUNCTION DECLARATIONS
===========================================================================*/

/**
  EFI_PmGpioEnable()

  @brief
  Enable implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS
EFIAPI
EFI_PmGpioEnable
(
  IN UINT32                   PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX Gpio, 
  IN BOOLEAN                  Enable
)
{

  return EFI_SUCCESS;
}


/**
  EFI_PmGpioCfgMode()

  @brief
  CfgMode implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS EFIAPI EFI_PmGpioCfgMode
(
  IN UINT32                   PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX Gpio, 
  IN EFI_PM_GPIO_CONFIG_TYPE  GpioConfigType
)
{

  return EFI_SUCCESS;
}


/**
  EFI_PmGpioLevelStatus()

  @brief
  LevelStatus implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS
EFIAPI 
EFI_PmGpioInputLevelStatus
(
  IN  UINT32                   PmicDeviceIndex, 
  IN  EFI_PM_GPIO_PERIPH_INDEX Gpio, 
  OUT EFI_PM_GPIO_LEVEL_TYPE   *GpioLevelStatus
)
{

  return EFI_SUCCESS;
}


/**
  EFI_PmGpioIrqEnable()

  @brief
  GpioIrqEnable implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS 
EFIAPI 
EFI_PmGpioIrqEnable
(
  IN UINT32                   PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX Gpio, 
  IN BOOLEAN                  Enable
)
{

  return EFI_SUCCESS;
}


/**
  EFI_PmGpioIrqClear()

  @brief
  GpioIrqClear implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS 
EFIAPI 
EFI_PmGpioIrqClear
(
  IN UINT32                   PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX Gpio
)
{

  return EFI_SUCCESS;
}


/**
  EFI_PmGpioIrqSetTrigger()

  @brief
  GpioIrqSetTrigger implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS 
EFIAPI 
EFI_PmGpioIrqSetTrigger
(
  IN UINT32                   PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX Gpio, 
  IN EFI_PM_IRQ_TRIGGER_TYPE  Trigger
)
{

  return EFI_SUCCESS;
}


/**
  EFI_PmGpioIrqStatus()

  @brief
  PmGpioIrqStatus implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS 
EFIAPI 
EFI_PmGpioIrqStatus
( 
  IN UINT32                    PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX  Gpio, 
  IN EFI_PM_IRQ_STATUS_TYPE    Type, 
  OUT BOOLEAN                  *Status
)
{

  return EFI_SUCCESS;
}


/**
  EFI_PmGpioSetVoltageSource()

  @brief
  SetVoltageSource implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS 
EFIAPI 
EFI_PmGpioSetVoltageSource
(
  IN UINT32                    PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX  Gpio,
  IN EFI_PM_GPIO_VOLT_SRC_TYPE GpioVoltageSource
)
{

  return EFI_SUCCESS;
}


/**
  EFI_PmGpioSetOutBufCfg()

  @brief
  SetOutBufCfg implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS 
EFIAPI 
EFI_PmGpioSetOutBufCfg
(
  IN UINT32                       PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX     Gpio, 
  IN EFI_PM_GPIO_OUT_BUF_CFG_TYPE GpioOutBufferConfig
)
{

  return EFI_SUCCESS;
}


/**
  EFI_PmGpioSetOutputLevel()

  @brief
  SetOutputLevel implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS 
EFIAPI 
EFI_PmGpioSetOutputLevel
(
  IN UINT32                   PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX Gpio, 
  IN EFI_PM_GPIO_LEVEL_TYPE   GpioLevel
)
{
  return EFI_SUCCESS;
}


/**
  EFI_PmGpioSetOutDrvStr()

  @brief
  SetOutDrvStr implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS
EFIAPI 
EFI_PmGpioSetOutDrvStr
(
  IN UINT32                       PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX     Gpio, 
  IN EFI_PM_GPIO_OUT_DRV_STR_TYPE GpioOutDrvStr
)
{
  return EFI_SUCCESS;
}


/**
  EFI_PmGpioSetOutSrcCfg()

  @brief
  SetOutSrcCfg implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS 
EFIAPI 
EFI_PmGpioSetOutSrcCfg
(
  IN UINT32                   PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX Gpio, 
  IN EFI_PM_GPIO_SRC_CFG_TYPE GpioSource
)
{
  return EFI_SUCCESS;
}


/**
  EFI_PmGpioStatusGet()

  @brief
  StatusGet implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS 
EFIAPI 
EFI_PmGpioStatusGet
(
  IN UINT32                   PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX Gpio, 
  OUT EFI_PM_GPIO_STATUS_TYPE *GpioType
)
{

  return EFI_SUCCESS;
}


/**
  EFI_PmGpioSetPullSel()

  @brief
  SetPullSel implementation of EFI_QCOM_PMIC_GPIO_PROTOCOL
 */
EFI_STATUS 
EFIAPI 
EFI_PmGpioSetPullSel
(
  IN UINT32                      PmicDeviceIndex, 
  IN EFI_PM_GPIO_PERIPH_INDEX    Gpio, 
  IN EFI_PM_GPIO_I_SRC_PULL_TYPE GpioPullType
)
{

  return EFI_SUCCESS;
}


/**
  PMIC GPIO UEFI Protocol implementation
 */
EFI_QCOM_PMIC_GPIO_PROTOCOL PmicGpioProtocolImplementation =
{
  EFI_PMIC_GPIO_REVISION_3, 
  EFI_PmGpioEnable, 
  EFI_PmGpioCfgMode, 
  EFI_PmGpioInputLevelStatus, 
  EFI_PmGpioIrqEnable, 
  EFI_PmGpioIrqClear, 
  EFI_PmGpioIrqSetTrigger, 
  EFI_PmGpioIrqStatus, 
  EFI_PmGpioSetVoltageSource, 
  EFI_PmGpioSetOutBufCfg, 
  EFI_PmGpioSetOutputLevel,
  EFI_PmGpioSetOutDrvStr, 
  EFI_PmGpioSetOutSrcCfg, 
  EFI_PmGpioStatusGet, 
  EFI_PmGpioSetPullSel,
};

