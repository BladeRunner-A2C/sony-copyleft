/**
 *
 * @file Trackpad.c
 *
 * @brief Only Enables resources required for trackpad fucntionality. UEFI trackpad functionality not enabled
 *
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 */

/*=============================================================================
                              EDIT HISTORY


 when         who      what, where, why
 --------     ---      ----------------------------------------------------------
 10/15/22    rgotur   I2C Trackpad Inbox support and Device tree integration
 08/23/22    rgotur   Initial revision for UEFI I2C Trackpad Driver
=============================================================================*/

#include "Trackpad.h"
#include "I2CClientLib.h"

#include <Protocol/EFITlmm.h>
#include <Protocol/EFIChargerEx.h>
#include <Library/QcomLib.h>

#define  I2CTP_CFG_DT_PATH      "i2ctp"

I2CCLIENT_DEVICE_INFO     *gI2cTpDtconfig;
  

/* 	 */
EFI_STATUS I2CTpGetChargerPowerStatus(void)
{
  EFI_STATUS                Status            = EFI_SUCCESS;
  BOOLEAN                   bOffModeCharging   = FALSE;
  EFI_CHARGER_EX_PROTOCOL   *ChargerExProtocol = NULL;

  Status = gBS->LocateProtocol(&gChargerExProtocolGuid,
                                NULL,
                                (void**)&ChargerExProtocol);

  if ((ChargerExProtocol != NULL && ChargerExProtocol->IsOffModeCharging != NULL) &&
      ((EFI_SUCCESS != Status)                                                 ||
      (EFI_SUCCESS != ChargerExProtocol->IsOffModeCharging(&bOffModeCharging))))
  {
    // Unable to locate charger protocol, just continue with power okay status
    Status = EFI_SUCCESS;  
    DEBUG ((EFI_D_ERROR, "%a: ChargerExProtocol = 0x%x,  bOffModeCharging = %d\r\n", __func__, *ChargerExProtocol, bOffModeCharging));
  }
  else if (TRUE  == bOffModeCharging)
  {
    // off mode charging
    Status = EFI_OUT_OF_RESOURCES;
  }
  else
  {
    // Charger power status is ok
    Status = EFI_SUCCESS;
  }

  return Status;
}

/**
  Entrypoint of I2C Trackpad Driver.

  This function is the entrypoint of I2C Trackpad Driver.
  Enables resources required for trackpad fucntionality. UEFI trackpad functionality not enabled
  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
I2CTrackpadEntryPoint(
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS        Status      = EFI_SUCCESS;
  VOID              *I2CHandle  = NULL;
  i2c_instance      I2cInstance = 0;
  i2c_slave_config  gSlaveCfg   = {0};
  
  gI2cTpDtconfig = I2CClientInitDT(I2CTP_CFG_DT_PATH);
  if(NULL == gI2cTpDtconfig)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] Error Parsing device tree\r\n"));
    Status = EFI_DEVICE_ERROR;
  }

  Status = I2CClientGetI2cInstance(I2CTP_CFG_DT_PATH, &I2cInstance);
  if(EFI_ERROR (Status))
  {
    DEBUG((EFI_D_ERROR,"[I2CTrackPad] Failed to get I2C Instance. Status=%r\n", Status));
    return Status;
  }

  Status = I2CClientGetSlaveCfg(I2CTP_CFG_DT_PATH, &gSlaveCfg);
  if(EFI_ERROR (Status))
  {
    DEBUG((EFI_D_ERROR,"[I2CTrackPad] Failed to get I2C slave cfg. Status=%r\n", Status));
    return Status;
  }

  //Check power status
  Status = I2CTpGetChargerPowerStatus();
  if(EFI_ERROR (Status))
  {
    DEBUG((EFI_D_WARN, "[I2CTrackPad] %a in off mode charging. Exiting. \r\n", __FUNCTION__));
    return Status;
  }
  
  /* Initialize dummy I2C handle for I2C instance query*/
  I2CHandle = (VOID *)sizeof(VOID);
  /* Initialize the I2C Core  */
  i2c_status istatus = I2C_SUCCESS;
  istatus = i2c_open(I2cInstance, &I2CHandle);
  if (I2C_SUCCESS != istatus)
  {
    DEBUG((EFI_D_ERROR, "[I2CTrackPad] Failed to initialize I2C. Error = %d\n", istatus));
    goto ErrorExit;
  }
  
  //Init TLMM/PMIC resources in PowerOn sequence as mentioned in device tree
  Status = I2CClientPowerOn(I2CTP_CFG_DT_PATH);
  if(EFI_ERROR (Status))
  {
    DEBUG((EFI_D_ERROR, "[I2CTrackpad] Error Initializing Trackpad reources. Status = %r\n", Status));
    goto ErrorExit;
  }

  //
  // Error handler
  //
ErrorExit:
  Status = I2CClientDeInitDT(gI2cTpDtconfig);
  if (EFI_ERROR(Status)) 
  {
    DEBUG((EFI_D_WARN, "[I2CTrackpad] Failed to Deinit Client resource. Status = %r\n", Status));
  }
  
  DEBUG((EFI_D_INFO, "[I2CTrackPad]  %a Exit \r\n", __FUNCTION__));
  return Status;
}