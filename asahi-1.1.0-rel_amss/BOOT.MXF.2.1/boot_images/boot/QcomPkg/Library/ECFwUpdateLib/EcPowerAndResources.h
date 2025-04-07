/** @file EcPowerAndResources.h

  Header for EC Power and voting related routines.

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------
  2023/03/29     sumesahu    Add support for Power-off EC during off mode charging &
                             enable check for power level.
  2022/07/29     bkulkarn    Initial version
=============================================================================*/

#ifndef _ECPOWERANDRESOURCES_H
#define _ECPOWERANDRESOURCES_H

#include <api/pmic/pm/pm_version.h>
#include <Protocol/EFIPmicGpio.h>
#include "DDITlmm.h"


/* Power resource configurations for ITE8987 on 8380 */
#define PMIC_INDEX_FOR_EC_PON               (PMIC_I)
#define PMIC_GPIO_INDEX_FOR_EC_PON          (EFI_PM_GPIO_6)
#define GPIO_FOR_EC_WRITE_PROT_EN           (234)

/** Function to initialize resource related protocols for EC.
 *
 * @param none
 *
 * @retval status    A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
EcPowerInit();

/** Function Handler to Off Mode charging.
 *
 * @param none
 *
 * @retval status    A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
EcOffModeChargingHandler();

/** Function to check if device is currently in off-mode charging state.
 *
 * @param none
 *
 * @retval status    A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
EcGetOffModeChargingStatus(
  OUT BOOLEAN *bOffModeCharging
  );

/** Function to check if the power level is meets the firmware update threshold creteria.
 *
 * @param none
 *
 * @retval status    A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
EcCheckPowerLevel(
  OUT BOOLEAN *bPowerGood
  );

/**
 * Function to vote for given GPIO with corresponding GPIO_VALUE (LOW/HIGH)
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
  );

#endif
