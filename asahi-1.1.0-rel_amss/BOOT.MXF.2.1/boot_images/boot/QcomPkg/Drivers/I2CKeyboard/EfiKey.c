/** @file
  I2C Keyboard Driver that manages I2C keyboard and produces Simple Text Input
  Protocol and Simple Text Input Ex Protocol.

Copyright (c) 2018 - 2020, 2022-2023 Qualcomm Technologies Inc. All rights reserved.
Portions Copyright (c) 2004 - 2012, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*=============================================================================
                              EDIT HISTORY

 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 04/23/23   ananns   Reading Inputregister after reset command issued as per I2C HID Enum Sequence
 03/29/23   sumesahu Add support for Power-off EC during off mode charging &
                     enable check for power level.
 03/06/23   bkulkarn Revert log level from ERROR to INFO to avoid flooding during PXE Boot
 02/23/23   bkulkarn Support to query & update EC device status in NV and code refactoring
 12/31/22   rgotur   I2C keyboard Inbox support and Device tree integration
 11/16/22   bkulkarn Changes to power-on EC till EDK2/FmpDevicePkg dependencies are resolved
 11/10/22   ananns   Added fix for Platform check
 10/17/22   ananns   Enabled CAP's Lock LED and Long Key Press functionality and ported I2C block read and write for Kodiak, Poipu and Hamoa
 04/06/22   sumesahu Added fix for I2C Timeout, HID init sequence and I2C flags for Kodiak CLS
 03/10/20   c_shimpi Added Suport for Rennell CLS
 05/27/19   ssumit   i2c_open deadlock FIX with other minor changes
 04/05/19   ssumit   KW error, boot time optimization
 02/19/19   ssumit   Optimization to check Platform and reduce load time
 11/01/18   ssumit   Adding support for Poipu CLS
 05/05/17   ltg      Added bug fixes and enable command
 03/13/17   ltg      Initial revision for UEFI I2C Keyboard Driver
=============================================================================*/

#include <string.h>
#include "EfiKey.h"
#include "Keyboard.h"
#include "KeyboardI2C.h"
#include "I2CClientLib.h"
#include <Library/QcomLib.h>
#include <Library/ECFwUpdateLib.h>
#include <Protocol/EFITlmm.h>
#include <Protocol/EFIChargerEx.h>
#include <Protocol/EFIPlatformInfo.h>

EFI_TLMM_PROTOCOL    *gTLMMProtocol = NULL;

#define QCOM_KEYBOARD_DEVICE_GUID \
    { 0xE7F58A0E, 0xBED2, 0x4B5A, { 0xBB, 0x43, 0x8A, 0xB2, 0x3D, 0xD0, 0xE2, 0xB0} }

#define I2CKB_NODE_NAME      "i2ckb"

I2CCLIENT_DEVICE_INFO* gI2cKbDtconfig = NULL;
i2c_slave_config gSlaveCfg = {0};
GPIO_SETTINGS gClientGpioCfg = {0};
UINT8 gHidDescAddrHigh = 0;
UINT8 gHidDescAddrLow = 0;
UINT8 gLongKeyPressCount = 0;
UINT32 gGpioInitInterval = 0;

#pragma pack(1)
typedef struct
{
  VENDOR_DEVICE_PATH             VendorDevicePath;
  EFI_DEVICE_PATH_PROTOCOL       End;
} EFI_KEYBOARD_DEVICE_PATH;
#pragma pack()

typedef struct
{
  EFI_HANDLE      ImageHandle;
  I2C_KB_DEV      kbddevice;
} KBD_INIT_CONFIG;

int is_kbd_up = 0;
 EFI_KEYBOARD_DEVICE_PATH KeyboardDxeDevicePath =
 {
   {
     {
       HARDWARE_DEVICE_PATH,
       HW_VENDOR_DP,
       {
         (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
         (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
       }
     },
     QCOM_KEYBOARD_DEVICE_GUID
   },
   {
     END_DEVICE_PATH_TYPE,
     END_ENTIRE_DEVICE_PATH_SUBTYPE,
     {
       (UINT8) (END_DEVICE_PATH_LENGTH),
       (UINT8) ((END_DEVICE_PATH_LENGTH) >> 8)
     }
   }
 };

HidDescriptor gHidDesc = {0};

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------

/**
  Debug function to print out buffer of size length

  @param buffer     pointer to buffer
  @param length     number of bytes in buffer to print

  @retval None
**/
VOID i2c_test_hex_dump (IN UINT8 *buffer, IN UINT32 length)
{
  UINT32 size = 0;

  DEBUG((EFI_D_INFO, "[I2CKeyboard] i2c_test_hex_dump [ENTRY] \n"));

  if (!buffer)
  {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] i2c_test_hex_dump [EXIT], buffer == NULL \n"));
    return ;
  }

  for (size = 0; size < length; size++)
  {
    if (!(size & 7))
    {
      DEBUG((EFI_D_INFO, "\n"));
    }
    DEBUG((EFI_D_INFO, "%02x ", buffer[size]));
  }

  DEBUG((EFI_D_INFO, "\n[I2CKeyboard] i2c_test_hex_dump [EXIT] \n"));
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
// HID FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------
/**
  Reset the device

  @param i2c_handle             Pointer to i2c handle
  @param cfg                    Pointer to i2c config

  @retval EFI_SUCCESS             Reset completed successfully.
  @retval EFI_INVALID_PARAMETER   I2C handle is not configured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.
**/
EFI_STATUS ResetDevice(IN VOID * i2c_handle, IN i2c_slave_config cfg)
{
  EFI_STATUS status = EFI_SUCCESS;
  UINT8 wrBuf[4] = {0,};

  DEBUG((EFI_D_INFO, "[I2CKeyboard] ResetDevice [ENTRY] \n"));

  if (!i2c_handle)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] ResetDevice [EXIT], i2c_handle is null\n"));
    status = I2cStatusToEfiStatus(I2C_ERROR_INVALID_PARAMETER);
    goto Error;
  }

  // Send Power command
  wrBuf[0] = LOW_BYTE(gHidDesc.wCommandRegister);
  wrBuf[1] = HIGH_BYTE(gHidDesc.wCommandRegister);
  wrBuf[2] = POWER_CMD_LOW;
  wrBuf[3] = POWER_CMD_HIGH;
  status = i2ckb_block_write(i2c_handle, cfg, wrBuf, 4);
  if (EFI_ERROR(status))
  {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] ResetDevice [EXIT],i2c_transfer failed: Status=%d.\r\n", status));
    goto Error;
  }

  //reset the wrbuf
  memset(wrBuf, 0, 4);

  // Send Reset command
  wrBuf[0] = LOW_BYTE(gHidDesc.wCommandRegister);
  wrBuf[1] = HIGH_BYTE(gHidDesc.wCommandRegister);
  wrBuf[2] = RESET_CMD_LOW;
  wrBuf[3] = RESET_CMD_HIGH;
  status = i2ckb_block_write(i2c_handle, cfg, wrBuf, 4);
  if (EFI_ERROR(status))
  {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] ResetDevice [EXIT],i2c_transfer failed, Status=%d.\r\n", status));
    goto Error;
  }

Error:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] ResetDevice [EXIT] Status=%d.\r\n", status));
  return status;
}

/**
  Get the input report from the device

  @param i2c_handle     Pointer to i2c handle
  @param cfg            Pointer to i2c config

  @retval EFI_SUCCESS             Input report retrieval completed successfully.
  @retval EFI_INVALID_PARAMETER   I2C handle is not configured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.
**/
EFI_STATUS GetInputReport(IN VOID * i2c_handle, IN i2c_slave_config cfg, OUT InputReport* gReportDesc)
{
  UINT8 *rdBuf = NULL;
  EFI_STATUS status = EFI_SUCCESS;

  if (!i2c_handle)
  {
    status = I2cStatusToEfiStatus(I2C_ERROR_INVALID_PARAMETER);
    DEBUG((EFI_D_WARN, "[I2CKeyboard] GetInputReport [EXIT], i2c_handle is null\n"));
    goto Error;
  }

  if (!gReportDesc)
  {
    status = I2cStatusToEfiStatus(I2C_ERROR_INVALID_PARAMETER);
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] GetInputReport [EXIT], gReportDesc is null\n"));
    goto Error;
  }

  rdBuf = (UINT8 *)AllocateZeroPool((gHidDesc.wMaxInputLength + 2) * sizeof(rdBuf[0]));
  if (!rdBuf)
  {
    status = EFI_OUT_OF_RESOURCES;
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] \
      GetInputReport [EXIT], Failed to allocate memory.\n"));
    goto Error;
  }

  status = i2ckb_block_read(
    i2c_handle,
    cfg,
    (UINT8 *)&(gHidDesc.wInputRegister),
    rdBuf,
    gHidDesc.wMaxInputLength+2
    );
  if (EFI_ERROR(status))
  {
    KB_E(" EcI2cBlockRead(wInputRegister) failed with %r!\n", status);
    goto Error;
  }

  // if length > 0, copy report, otherwise copy zeroes
  if (rdBuf[0] != 0x0)
  {
    CopyMem(gReportDesc, rdBuf, sizeof(InputReport));
  }
  else
  {
    SetMem(gReportDesc, sizeof(InputReport), 0);
  }

Error:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] GetInputReport [EXIT] Status=%d.\r\n", status));

  if (rdBuf)
  {
    FreePool(rdBuf);
    rdBuf = NULL;
  }

  return status;
}

/**
  Get report descriptor from HID compliant device

  @param i2c_handle     Pointer to i2c handle
  @param cfg            Pointer to i2c config

  @retval EFI_SUCCESS             Report descriptor retrieved successfully.
  @retval EFI_INVALID_PARAMETER   I2C handle is not confiured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.
**/
EFI_STATUS ReadReportDescriptor(IN VOID * i2c_handle, IN i2c_slave_config cfg, OUT UINT8* ReportDesc)
{
  EFI_STATUS status = EFI_SUCCESS;
  UINT8      *rdBuf  = NULL;

  DEBUG((EFI_D_INFO, "[I2CKeyboard] ReadReportDescriptor [ENTRY] \n"));

  rdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * gHidDesc.wReportDescLength);
  if (!rdBuf)
  {
    status = EFI_OUT_OF_RESOURCES;
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] AllocateZeroPool failed!!\n"));
    goto Error;
  }

  if (!i2c_handle)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] ReadReportDescriptor [EXIT], i2c_handle is null\n"));
    status = I2cStatusToEfiStatus(I2C_ERROR_INVALID_PARAMETER);
    goto Error;
  }

  status = i2ckb_block_read(
    i2c_handle, cfg,
    (UINT8 *)&(gHidDesc.wReportDescRegister),
    rdBuf,
    gHidDesc.wReportDescLength
    );
  if (EFI_ERROR(status))
  {
    KB_E(" EcI2cBlockRead(wInputRegister) failed with %r!\n", status);
    goto Error;
  }

  // if length > 0, copy report, otherwise copy zeroes
  if (rdBuf[0] != 0x0)
  {
    CopyMem(ReportDesc, rdBuf, sizeof(ReportDesc));
  }

Error:
  if (rdBuf)
  {
    gBS->FreePool(rdBuf);
    rdBuf = NULL;
  }
  DEBUG((EFI_D_INFO, "[I2CKeyboard] ReadReportDescriptor [EXIT] Status=%d.\r\n", status));
  return status;
}

/**
  Parse report descriptor from HID compliant device

  @param ReportDesc     Pointer to report descriptor

  @retval EFI_SUCCESS             Report descriptor parsed successfully.
  @retval EFI_DEVICE_ERROR        Device is not valid.
**/
EFI_STATUS
ParseReportDescriptor( IN UINT8 * ReportDesc, OUT UINT8 * ReportID)
{
  UINT8         temp_report_id = 0;
  EFI_STATUS    status = EFI_SUCCESS;

  /* below values are based on HID Device Class Definition */
  UINT8 keyboard_header [4] = {0x5, 0x1, 0x9, 0x6};
  UINT8 report_id_key [1] = {0x85};

  DEBUG((EFI_D_INFO, "[I2CKeyboard] ParseReportDescriptor [ENTRY] \n"));
  // search report descriptor for Keyboard usage page
  for (int i = 0; i < gHidDesc.wReportDescLength-3; i+=2)
  {
    if (CompareMem(ReportDesc+i, keyboard_header, 4) == 0)
    {
      // search for report ID
      for (int j = i+4; j < gHidDesc.wReportDescLength-1; j+=2)
      {
        if (CompareMem(ReportDesc+j, report_id_key, 1) == 0)
        {
          temp_report_id = ReportDesc[j+1];
          CopyMem(ReportID, &temp_report_id, 1);
          goto Exit;
        }
      }
      DEBUG((EFI_D_WARN, "[I2CKeyboard] Could not find report ID for keyboard.\n"));
    }
  }

  status =  EFI_DEVICE_ERROR;

Exit:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] ParseReportDescriptor [EXIT] \n"));
  return status;
}

/**
  Get HID descriptor from HID compliant device

  @param i2c_handle     Pointer to i2c handle
  @param cfg            Pointer to i2c config

  @retval EFI_SUCCESS             HID descriptor retrieved successfully.
  @retval EFI_INVALID_PARAMETER   I2C handle is not configured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.
**/
EFI_STATUS ReadHidDescriptor(IN VOID * i2c_handle, IN i2c_slave_config cfg)
{
  EFI_STATUS status = EFI_SUCCESS;
  UINT8 rdBuf[HID_DESC_LENGTH] = {0};
  UINT8 wdBuf[2] = {0};

  DEBUG((EFI_D_INFO, "[I2CKeyboard] ReadHidDescriptor [ENTRY] \n"));

  if (!i2c_handle)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] ReadHidDescriptor [EXIT] i2c_handle is null\n"));
    status = I2cStatusToEfiStatus(I2C_ERROR_INVALID_PARAMETER);
    goto Error;
  }

  wdBuf[0] = gHidDescAddrLow;
  wdBuf[1] = gHidDescAddrHigh;
  status = i2ckb_block_read(
    i2c_handle,
    cfg,
    wdBuf,
    rdBuf,
    HID_DESC_LENGTH
    );
  if (EFI_ERROR(status))
  {
    KB_E(" EcI2cBlockRead(wInputRegister) failed with %r!\n", status);
    goto Error;
  }

  // if length > 0, copy report, otherwise copy zeroes
  if (rdBuf[0] != 0x0)
  {
    CopyMem(&gHidDesc, rdBuf, sizeof(gHidDesc));
  }
  else
  {
    SetMem(&gHidDesc, sizeof(gHidDesc), 0);
  }

Error:

  DEBUG((EFI_D_INFO, "[I2CKeyboard] ReadHidDescriptor [EXIT] Status=%d.\r\n", status));
  return status;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
// QUEUE FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------
/**
  Check whether the EFI key buffer is empty.

  @param Queue     Pointer to instance of EFI_KEY_QUEUE.

  @retval TRUE    The EFI key buffer is empty.
  @retval FALSE   The EFI key buffer isn't empty.
**/
BOOLEAN
IsEfiKeyQueueEmpty (
  IN  EFI_KEY_QUEUE         *Queue
  )
{
  DEBUG((EFI_D_INFO, "[I2CKeyboard] IsEfiKeyQueueEmpty [ENTRY] \n"));
  ASSERT (Queue != NULL);
  DEBUG((EFI_D_INFO, "[I2CKeyboard] IsEfiKeyQueueEmpty [EXIT] \n"));
  return (BOOLEAN) (Queue->Head == Queue->Tail);
}

/**
  Read & remove one key data from the EFI key buffer.

  @param Queue     Pointer to instance of EFI_KEY_QUEUE.
  @param KeyData   Receive the key data.

  @retval EFI_SUCCESS   The key data is popped successfully.
  @retval EFI_NOT_READY There is no key data available.
**/
EFI_STATUS
PopEfiKeyQueue (
  IN  EFI_KEY_QUEUE         *Queue,
  OUT EFI_KEY_DATA          *KeyData OPTIONAL
  )
{
  EFI_STATUS status = EFI_SUCCESS;

  DEBUG((EFI_D_INFO, "[I2CKeyboard] PopEfiKeyQueue [ENTRY] \n"));

  if (!Queue)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] PopEfiKeyQueue [EXIT], Queue == NULL\n"));
    status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  if (IsEfiKeyQueueEmpty (Queue))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] PopEfiKeyQueue [EXIT] IsEfiKeyQueueEmpty (Queue)\n"));
    status = EFI_NOT_READY;
    goto Exit;
  }

  // Check for null input
  if (!KeyData)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] PopEfiKeyQueue KeyData == NULL [EXIT] \n"));
    status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  // Retrieve and remove the values
  if (KeyData != NULL)
  {
    CopyMem (KeyData, &Queue->Buffer[Queue->Head], sizeof (EFI_KEY_DATA));
  }
  Queue->Head = (Queue->Head + 1) % KEYBOARD_EFI_KEY_MAX_COUNT;

Exit:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] PopEfiKeyQueue [EXIT] \n"));
  return status;
}

/**
  Push one key data to the EFI key buffer.

  @param Queue     Pointer to instance of EFI_KEY_QUEUE.
  @param KeyData   The key data to push.
**/
VOID
PushEfiKeyQueue (
  IN  EFI_KEY_QUEUE         *Queue,
  IN  EFI_KEY_DATA          *KeyData
  )
{
  DEBUG((EFI_D_INFO, "[I2CKeyboard] PushEfiKeyQueue [ENTRY] \n"));
  // Check for null input
  if (Queue == NULL || KeyData == NULL)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] PushEfiKeyQueue [EXIT], (Queue == NULL || KeyData == NULL)\n"));
    return ;
  }

  if ((Queue->Tail + 1) % KEYBOARD_EFI_KEY_MAX_COUNT == Queue->Head)
  {
    // If Queue is full, pop the one from head.
    PopEfiKeyQueue (Queue, NULL);
  }

  CopyMem (&Queue->Buffer[Queue->Tail], KeyData, sizeof (EFI_KEY_DATA));
  Queue->Tail = (Queue->Tail + 1) % KEYBOARD_EFI_KEY_MAX_COUNT;

  DEBUG((EFI_D_INFO, "[I2CKeyboard] PushEfiKeyQueue [EXIT] \n"));
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
// SIMPLE TEXT INPUT PROTOCOL FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------

/**
  Resets the input device hardware.

  The Reset() function resets the input device hardware. As part
  of initialization process, the firmware/device will make a quick
  but reasonable attempt to verify that the device is functioning.
  If the ExtendedVerification flag is TRUE the firmware may take
  an extended amount of time to verify the device is operating on
  reset. Otherwise the reset operation is to occur as quickly as
  possible. The hardware verification process is not defined by
  this specification and is left up to the platform firmware or
  driver to implement.

  @param This                 A pointer to the EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL instance.

  @param ExtendedVerification Indicates that the driver may perform a more exhaustive
                              verification operation of the device during reset.

  @retval EFI_SUCCESS         The device was reset.
  @retval EFI_DEVICE_ERROR    The device is not functioning correctly and could not be reset.

**/
EFI_STATUS
EFIAPI
I2CKeyboardReset (
  IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
  IN BOOLEAN                         ExtendedVerification
  )
{
  I2C_KB_DEV *I2CKeyboardDevice = NULL;
  EFI_STATUS Status = EFI_SUCCESS;

  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReset [ENTRY] \n"));

  if (!This)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] Invalid This handle!\n"));
    Status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  I2CKeyboardDevice = I2C_KB_DEV_FROM_THIS (This);

  if (!I2CKeyboardDevice)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] I2CKeyboardReset [EXIT], I2CKeyboardDevice == NULL\n"));
    Status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  if (ExtendedVerification == TRUE)
  {
    Status = ResetDevice(
      I2CKeyboardDevice->I2CHandle,
      I2CKeyboardDevice->I2CConfig);
    if (EFI_ERROR(Status))
    {
      DEBUG((EFI_D_ERROR, "[I2CKeyboard] ResetDevice was unsuccessful: %d\n", Status));
      goto Exit;
    }
  }

  //
  // Clear KeyCode and EfiKey Buffers
  //
  I2CKeyboardDevice->KeyCodeQueue.Head  = 0;
  I2CKeyboardDevice->KeyCodeQueue.Tail  = 0;
  I2CKeyboardDevice->EfiKeyQueue.Head   = 0;
  I2CKeyboardDevice->EfiKeyQueue.Tail   = 0;

  //
  // Reset the status indicators
  //
  I2CKeyboardDevice->CapsLock   = FALSE;
  I2CKeyboardDevice->NumLock    = FALSE;
  I2CKeyboardDevice->ScrollLock = FALSE;
  I2CKeyboardDevice->LeftCtrl   = FALSE;
  I2CKeyboardDevice->RightCtrl  = FALSE;
  I2CKeyboardDevice->LeftAlt    = FALSE;
  I2CKeyboardDevice->RightAlt   = FALSE;
  I2CKeyboardDevice->LeftShift  = FALSE;
  I2CKeyboardDevice->RightShift = FALSE;
  I2CKeyboardDevice->LeftLogo   = FALSE;
  I2CKeyboardDevice->RightLogo  = FALSE;
  I2CKeyboardDevice->Menu       = FALSE;
  I2CKeyboardDevice->SysReq     = FALSE;

  I2CKeyboardDevice->IsSupportPartialKey = FALSE;

Exit:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReset [EXIT] Status=%d.\r\n", Status));
  return EFI_SUCCESS;
}

/**
  Internal function to read the next keystroke from the keyboard buffer.

  @param  I2CKeyboardDevice       I2C keyboard's private structure.
  @param  KeyData                 A pointer to buffer to hold the keystroke
                                  data for the key that was pressed.
  @retval EFI_SUCCESS             The keystroke information was returned.
  @retval EFI_NOT_READY           There was no keystroke data availiable.
  @retval EFI_DEVICE_ERROR        The keystroke information was not returned due to
                                  hardware errors.
  @retval I2C_ERROR_INVALID_PARAMETER   KeyData is NULL.
  @retval Others                  Fail to translate keycode into EFI_INPUT_KEY

**/
EFI_STATUS
I2CKeyboardReadKeyStrokeWorker (
  IN OUT I2C_KB_DEV                 *I2CKeyboardDevice,
     OUT EFI_KEY_DATA               *KeyData
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;

  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReadKeyStrokeWorker [ENTRY] \n"));

  if ((!I2CKeyboardDevice) ||
    (!KeyData))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] I2CKeyboardReadKeyStrokeWorker [EXIT], I2CKeyboardDevice == NULL || KeyData == NULL)\n"));
    Status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  if (IsEfiKeyQueueEmpty(&I2CKeyboardDevice->EfiKeyQueue))
  {
    DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReadKeyStrokeWorker [EXIT], (IsEfiKeyQueueEmpty(&I2CKeyboardDevice->EfiKeyQueue))\n"));
    Status =  EFI_NOT_READY;
    goto Exit;
  }

  Status = PopEfiKeyQueue (&I2CKeyboardDevice->EfiKeyQueue, KeyData);

Exit:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReadKeyStrokeWorker [EXIT] Status=%d.\r\n", Status));
  return Status;
}

/**
  Reads the next keystroke from the input device.

  @param  This                 The EFI_SIMPLE_TEXT_INPUT_PROTOCOL instance.
  @param  Key                  A pointer to a buffer that is filled in with the keystroke
                               information for the key that was pressed.

  @retval EFI_SUCCESS          The keystroke information was returned.
  @retval EFI_NOT_READY        There was no keystroke data availiable.
  @retval EFI_DEVICE_ERROR     The keystroke information was not returned due to
                               hardware errors.

**/
EFI_STATUS
EFIAPI
I2CKeyboardReadKeyStroke (
  IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
  OUT EFI_INPUT_KEY                    *Key
  )
{
  I2C_KB_DEV   *I2CKeyboardDevice = NULL;
  EFI_STATUS   Status = EFI_SUCCESS;
  EFI_KEY_DATA KeyData = {0};

  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReadKeyStroke [ENTRY] \n"));

  if ((!This) ||
    (!Key))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] I2CKeyboardReadKeyStroke [EXIT], (I2CKeyboardDevice == NULL || Key == NULL)\n"));
    Status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  I2CKeyboardDevice = I2C_KB_DEV_FROM_THIS (This);

  /* 
   * TODO: Below condition is treated as error, while log is retained at INFO. 
   * Changing to WARN/ERR will flood the UEFI logs. 
   * Error condition might need to be split-up for better logging.
   */
  Status = I2CKeyboardReadKeyStrokeWorker (I2CKeyboardDevice, &KeyData);
  if (EFI_ERROR (Status))
  {
    DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReadKeyStroke [EXIT], I2CKeyboardReadKeyStrokeWorker (I2CKeyboardDevice, &KeyData) \n"));
    goto Exit;
  }

  CopyMem(
    Key,
    &KeyData.Key,
    sizeof (EFI_INPUT_KEY)
    );

Exit:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardReadKeyStroke I2CKeyboardReadKeyStrokeWorker [EXIT] \n"));
  return Status;
}

/**
  Event notification function registered for EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.WaitForKeyEx
  and EFI_SIMPLE_TEXT_INPUT_PROTOCOL.WaitForKey.

  @param  Event        Event to be signaled when a key is pressed.
  @param  Context      Points to I2C_KB_DEV instance.

**/
VOID
EFIAPI
I2CKeyboardWaitForKey (
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  )
{
  I2C_KB_DEV  *I2CKeyboardDevice = NULL;
  EFI_KEY_DATA KeyData = {0};

  I2CKeyboardDevice = (I2C_KB_DEV *) Context;
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardWaitForKey [ENTRY] \n"));
  ASSERT (I2CKeyboardDevice != NULL);

  if(!IsEfiKeyQueueEmpty (&I2CKeyboardDevice->EfiKeyQueue))
  {
    CopyMem (
      &KeyData,
      &(I2CKeyboardDevice->EfiKeyQueue.Buffer[I2CKeyboardDevice->EfiKeyQueue.Head]),
      sizeof (EFI_KEY_DATA)
      );
    gBS->SignalEvent (Event);
  }
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardWaitForKey [EXIT] \n"));
}

/**
  Function to read the TLMM GPIO status

  @param  GpioValue     Pointer to hold the TLMM GPIO value
  @retval EFI_STATUS    Status value indicating the result of operation.

**/
EFI_STATUS ReadKbGpioStatus(UINT32 *GpioValue)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (!GpioValue)
  {
    Status = EFI_DEVICE_ERROR;
    DEBUG((EFI_D_ERROR, "%a: Invalid GpioValue handle \n!", __func__));
    goto Exit;
  }

  Status = gTLMMProtocol->GpioIn(
    (UINT32)EFI_GPIO_CFG(gClientGpioCfg.GpioPin,
     gClientGpioCfg.FunctionSelect,
     gClientGpioCfg.Direction,
     gClientGpioCfg.Pull,
     gClientGpioCfg.DriveStrength),
     GpioValue);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "%a: TLMM GPIO read failed\r\n", __func__));
    goto Exit;
  }

Exit:
  return Status;
}

/**
  Function to configure the TLMM GPIO

  @retval EFI_STATUS    Status value indicating the result of operation.

**/
EFI_STATUS ConfigKbGpio()
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = gTLMMProtocol->ConfigGpio(
    (UINT32)EFI_GPIO_CFG(gClientGpioCfg.GpioPin,
      gClientGpioCfg.FunctionSelect,
      gClientGpioCfg.Direction,
      gClientGpioCfg.Pull,
      gClientGpioCfg.DriveStrength),
      gClientGpioCfg.Enable);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "%a: TLMM GPIO setup failed\r\n", __func__));
    goto Exit;
  }

Exit:
  return Status;
}

/**
  Read the input report when Keyboard interrupt is asserted

  @param  I2CKeyboardDevice             The I2C_KB_DEV instance.
  @param  gReportDesc                   Pointer to InputReport

  @retval EFI_SUCCESS                   Sucessfully read Input report
  @retval EFI_INVALID_PARAMETER         I2CKeyboardDevice/gReportDesc is NULL.
  @retval EFI_OUT_OF_RESOURCES          Device did not have input report

**/
EFI_STATUS 
ReadInputReport(
  IN I2C_KB_DEV * I2CKeyboardDevice,
  OUT InputReport* gReportDesc
  )
{
  EFI_STATUS        Status = EFI_SUCCESS;
  uint32            uGpio_Int_Value = 0;

  if (gReportDesc == NULL)
  {
    DEBUG((EFI_D_ERROR , "[I2CKeyboard] ReportDesc is NULL \n"));
    Status = EFI_INVALID_PARAMETER ;
    goto Exit;
  }

  if (I2CKeyboardDevice == NULL)
  {
    DEBUG((EFI_D_ERROR , "[I2CKeyboard] I2CKeyboardDevice is NULL \n"));
    Status = EFI_INVALID_PARAMETER ;
    goto Exit;
  }

  Status = ReadKbGpioStatus(&uGpio_Int_Value);
  if (Status == EFI_SUCCESS)
  {
    // Check Keyboard Interrupt(KB_INT) GPIO Pin value. In case of No key is pressed then GPIO will be HIGH
    if (uGpio_Int_Value == GPIO_HIGH_VALUE)
    {
      DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardTimerHandler [Input not from kbd] \n"));
      Status = EFI_OUT_OF_RESOURCES;
      goto Exit;
    }
  }

  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardTimerHandler [Input from kbd] \n"));

  SetMem(
    gReportDesc, 
    sizeof(InputReport), 
    0);

  I2CKeyboardDevice->LeftCtrl = FALSE;
  I2CKeyboardDevice->LeftShift = FALSE;
  I2CKeyboardDevice->LeftAlt = FALSE;
  I2CKeyboardDevice->LeftLogo = FALSE;
  I2CKeyboardDevice->RightCtrl = FALSE;
  I2CKeyboardDevice->RightShift = FALSE;
  I2CKeyboardDevice->RightAlt = FALSE;
  I2CKeyboardDevice->RightLogo = FALSE;

  Status = GetInputReport(
    I2CKeyboardDevice->I2CHandle, 
    I2CKeyboardDevice->I2CConfig, 
    gReportDesc
    );

  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] I2CKeyboardTimerHandler [EXIT], GetInputReport Failed \n"));
    goto Exit;
  }

Exit:
  return Status;
}

/**
  Timer event handler: read a series of KeyCodes from I2C
  and put them into memory KeyCode buffer.
  it read as much KeyCodes to either fill
  the memory buffer or empty the keyboard buffer.

  @param Event       The timer event
  @param Context     A I2C_KB_DEV pointer

**/
VOID
EFIAPI
I2CKeyboardTimerHandler
(
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  I2C_KB_DEV        *I2CKeyboardDevice = NULL;
  EFI_STATUS        Status = EFI_SUCCESS;
  EFI_KEY_DATA      KeyData = {0};
  InputReport       gReportDesc = {};
  UINTN             Index = 0;
  UINT8             Index2 = 0;
  BOOLEAN           KeyPress = FALSE;
  UINT8             *CurKeyCodeBuffer = NULL;
  UINT8             *OldKeyCodeBuffer = NULL;

  if (!is_kbd_up)
  {
    DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardTimerHandler is_kbd_up is 0 \n"));
    Status = EFI_NOT_READY;
    goto Exit;
  }

  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardTimerHandler [ENTRY] \n"));

  I2CKeyboardDevice = (I2C_KB_DEV *) Context;

  Status = ReadInputReport(I2CKeyboardDevice, &gReportDesc );
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardTimerHandler [EXIT], ReadInputReport Failed \n"));
    goto Exit;
  }

  if (gReportDesc.length == 0x0)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] I2CKeyboardTimerHandler [EXIT], gReportDesc.length is 0\n"));
    goto Exit;
  }

  // reject any reports that do not come from our device, specified by report ID
  if (gReportDesc.reportID != I2CKeyboardDevice->ReportID)
  {
    DEBUG((EFI_D_ERROR, "Mismatch DescReportID: 0x%x KBReportId:0x%x\n", gReportDesc.reportID, I2CKeyboardDevice->ReportID));
    goto Exit;
  }

  CurKeyCodeBuffer  = gReportDesc.Keyboard_data;
  OldKeyCodeBuffer  = I2CKeyboardDevice->LastKeyCodeArray;


  if (!I2CKBD_VALID_KEYCODE (CurKeyCodeBuffer[0]))
  {
    //Key press is released and Reset the gLongKeyPressCount
    gLongKeyPressCount = 0;
  }

  // Handle normal key's pressing situation
  KeyPress = FALSE;
  for (Index = 0; Index < 6; Index++)
  {
    if (!I2CKBD_VALID_KEYCODE (CurKeyCodeBuffer[Index]))
    {
      continue;
    }
    //
    // For any key in current keycode buffer, if it is not in old keycode buffer,
    // then it is pressed. Otherwise, it is not pressed.
    //
    KeyPress = TRUE;
    for (Index2 = Index; Index2 < 6; Index2++)
    {
      if (!I2CKBD_VALID_KEYCODE (OldKeyCodeBuffer[Index2]))
      {
        continue;
      }

      if (CurKeyCodeBuffer[Index] == OldKeyCodeBuffer[Index2])
      {
        KeyPress = FALSE;
        //Index 0 has long press keycode data then increment the gLongKeyPressCount by 1
        if (Index == 0)
        {
          gLongKeyPressCount++;
        }

        // Sample the Long key press data for 2 times and enable the LongKeyPress as true
        if (gLongKeyPressCount > 2)
        {
          gLongKeyPressCount = 0;
          KeyPress = TRUE;
        }
        break;
      }
    }

    if (KeyPress)
    {
      if (gReportDesc.KeyboardLeftControl == 0x1)
      {
        I2CKeyboardDevice->LeftCtrl = TRUE;
      }
      if (gReportDesc.KeyboardLeftShift == 0x1)
      {
        I2CKeyboardDevice->LeftShift = TRUE;
      }
      if (gReportDesc.KeyboardLeftAlt == 0x1)
      {
        I2CKeyboardDevice->LeftAlt = TRUE;
      }
      if (gReportDesc.KeyboardLeftGui == 0x1)
      {
        I2CKeyboardDevice->LeftLogo = TRUE;
      }
      if (gReportDesc.KeyboardRightControl == 0x1)
      {
        I2CKeyboardDevice->RightCtrl = TRUE;
      }
      if (gReportDesc.KeyboardRightShift == 0x1)
      {
        I2CKeyboardDevice->RightShift = TRUE;
      }
      if (gReportDesc.KeyboardRightAlt == 0x1)
      {
        I2CKeyboardDevice->RightAlt = TRUE;
      }
      if (gReportDesc.KeyboardRightGui == 0x1)
      {
        I2CKeyboardDevice->RightLogo = TRUE;
      }

      // Translate saved keycode into EFI_INPUT_KEY
      Status = KeyCodeToEfiInputKey (
        I2CKeyboardDevice,
        CurKeyCodeBuffer[Index],
        &KeyData);
      if (EFI_ERROR (Status))
      {
        DEBUG((EFI_D_ERROR, "[I2CKeyboard] I2CKeyboardTimerHandler [EXIT], KeyCodeToEfiInputKey Failed \n"));
        goto Exit;
      }
      PushEfiKeyQueue (&I2CKeyboardDevice->EfiKeyQueue, &KeyData);
    }
  }

  // Update LastKeycodeArray buffer in the I2CKeyboardDevice data structure.
  for (Index = 0; Index < 6; Index++) {
    I2CKeyboardDevice->LastKeyCodeArray[Index] = CurKeyCodeBuffer[Index];
  }

Exit:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] I2CKeyboardTimerHandler [EXIT] \n"));
}

/**
  Free the waiting key notify list.

  @param ListHead  Pointer to list head

  @retval I2C_ERROR_INVALID_PARAMETER  ListHead is NULL
  @retval EFI_SUCCESS            Sucess to free NotifyList
**/
EFI_STATUS
KbdFreeNotifyList (
  IN OUT LIST_ENTRY           *ListHead
  )
{
  EFI_STATUS                        status = EFI_SUCCESS;
  KEYBOARD_CONSOLE_IN_EX_NOTIFY     *NotifyNode = NULL;

  if (!ListHead)
  {
    status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  while (!IsListEmpty (ListHead))
  {
    NotifyNode = CR (
      ListHead->ForwardLink,
      KEYBOARD_CONSOLE_IN_EX_NOTIFY,
      NotifyEntry,
      I2C_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE);
    RemoveEntryList (ListHead->ForwardLink);
    gBS->FreePool (NotifyNode);
  }

Exit:
  return status;
}

/**
  Check whether the pressed key matches a registered key or not.

  @param  RegsiteredData    A pointer to keystroke data for the key that was registered.
  @param  InputData         A pointer to keystroke data for the key that was pressed.

  @retval TRUE              Key pressed matches a registered key.
  @retval FLASE             Key pressed does not matches a registered key.

**/
BOOLEAN
IsKeyRegistered (
  IN EFI_KEY_DATA  *RegisteredData,
  IN EFI_KEY_DATA  *InputData
  )
{
  ASSERT (RegisteredData != NULL && InputData != NULL);

  if ((RegisteredData->Key.ScanCode    != InputData->Key.ScanCode) ||
      (RegisteredData->Key.UnicodeChar != InputData->Key.UnicodeChar))
  {
    return FALSE;
  }

  // Assume KeyShiftState/KeyToggleState = 0 in Registered key data means these state could be ignored.
  if ((RegisteredData->KeyState.KeyShiftState != 0) &&
      (RegisteredData->KeyState.KeyShiftState != InputData->KeyState.KeyShiftState))
  {
    return FALSE;
  }

  if ((RegisteredData->KeyState.KeyToggleState != 0) &&
      (RegisteredData->KeyState.KeyToggleState != InputData->KeyState.KeyToggleState))
  {
    return FALSE;
  }

  return TRUE;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
// SIMPLE TEXT INPUT EX PROTOCOL FUNCTIONS
// ----------------------------------------------------------------------------------------------------------------------------------------------------------

/**
  Resets the input device hardware.

  The Reset() function resets the input device hardware. As part
  of initialization process, the firmware/device will make a quick
  but reasonable attempt to verify that the device is functioning.
  If the ExtendedVerification flag is TRUE the firmware may take
  an extended amount of time to verify the device is operating on
  reset. Otherwise the reset operation is to occur as quickly as
  possible. The hardware verification process is not defined by
  this specification and is left up to the platform firmware or
  driver to implement.

  @param This                 A pointer to the EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL instance.

  @param ExtendedVerification Indicates that the driver may perform a more exhaustive
                              verification operation of the device during reset.

  @retval EFI_SUCCESS         The device was reset.
  @retval EFI_DEVICE_ERROR    The device is not functioning correctly and could not be reset.

**/
EFI_STATUS
EFIAPI
I2CKeyboardResetEx (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN BOOLEAN                            ExtendedVerification
  )
{
  EFI_STATUS                Status = EFI_SUCCESS;
  I2C_KB_DEV                *I2CKeyboardDevice = NULL;

  if (!This)
  {
    DEBUG((EFI_D_WARN, "[I2CKeyboard] I2CKeyboardResetEx This == NULL)\n"));
    Status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  I2CKeyboardDevice = TEXT_INPUT_EX_I2C_KB_DEV_FROM_THIS (This);
  if (I2CKeyboardDevice == NULL)
  {
    Status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  Status = I2CKeyboardDevice->SimpleInput.Reset (&I2CKeyboardDevice->SimpleInput, ExtendedVerification);

Exit:
  return Status;
}

/**
  Reads the next keystroke from the input device.

  @param  This                   Protocol instance pointer.
  @param  KeyData                A pointer to a buffer that is filled in with the keystroke
                                 state data for the key that was pressed.

  @retval EFI_SUCCESS            The keystroke information was returned.
  @retval EFI_NOT_READY          There was no keystroke data available.
  @retval EFI_DEVICE_ERROR       The keystroke information was not returned due to
                                 hardware errors.
  @retval I2C_ERROR_INVALID_PARAMETER  KeyData is NULL.

**/
EFI_STATUS
EFIAPI
I2CKeyboardReadKeyStrokeEx (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
  OUT EFI_KEY_DATA                      *KeyData
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;
  I2C_KB_DEV    *I2CKeyboardDevice = NULL;

  if ((!This) ||
    (!KeyData))
  {
    Status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  I2CKeyboardDevice = TEXT_INPUT_EX_I2C_KB_DEV_FROM_THIS (This);

  Status = I2CKeyboardReadKeyStrokeWorker (I2CKeyboardDevice, KeyData);

Exit:
  return Status;
}

/**
  Set certain state for the input device.

  @param  This                    Protocol instance pointer.
  @param  KeyToggleState          A pointer to the EFI_KEY_TOGGLE_STATE to set the
                                  state for the input device.

  @retval EFI_SUCCESS             The device state was set appropriately.
  @retval EFI_DEVICE_ERROR        The device is not functioning correctly and could
                                  not have the setting adjusted.
  @retval EFI_UNSUPPORTED         The device does not support the ability to have its state set.
  @retval I2C_ERROR_INVALID_PARAMETER   KeyToggleState is NULL.

**/
EFI_STATUS
EFIAPI
I2CKeyboardSetState (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN EFI_KEY_TOGGLE_STATE               *KeyToggleState
  )
{
  I2C_KB_DEV                            *I2CKeyboardDevice = NULL;
  EFI_STATUS                            Status = EFI_SUCCESS;

  if ((!This) ||
    (!KeyToggleState))
  {
    Status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  I2CKeyboardDevice = TEXT_INPUT_EX_I2C_KB_DEV_FROM_THIS (This);

  if ((*KeyToggleState & EFI_TOGGLE_STATE_VALID) != EFI_TOGGLE_STATE_VALID)
  {
    Status = EFI_UNSUPPORTED;
    goto Exit;
  }

  I2CKeyboardDevice->ScrollLock   = FALSE;
  I2CKeyboardDevice->NumLock  = FALSE;
  I2CKeyboardDevice->CapsLock     = FALSE;
  I2CKeyboardDevice->IsSupportPartialKey = FALSE;

  if ((*KeyToggleState & EFI_SCROLL_LOCK_ACTIVE) == EFI_SCROLL_LOCK_ACTIVE)
  {
    I2CKeyboardDevice->ScrollLock = TRUE;
  }
  if ((*KeyToggleState & EFI_NUM_LOCK_ACTIVE) == EFI_NUM_LOCK_ACTIVE)
  {
    I2CKeyboardDevice->NumLock = TRUE;
  }
  if ((*KeyToggleState & EFI_CAPS_LOCK_ACTIVE) == EFI_CAPS_LOCK_ACTIVE)
  {
    I2CKeyboardDevice->CapsLock = TRUE;
  }
  if ((*KeyToggleState & EFI_KEY_STATE_EXPOSED) == EFI_KEY_STATE_EXPOSED)
  {
    I2CKeyboardDevice->IsSupportPartialKey = TRUE;
  }

  if (EFI_ERROR (Status))
  {
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

Exit:
  return Status;
}

/**
  Register a notification function for a particular keystroke for the input device.

  @param  This                        Protocol instance pointer.
  @param  KeyData                     A pointer to a buffer that is filled in with the keystroke
                                      information data for the key that was pressed.
  @param  KeyNotificationFunction     Points to the function to be called when the key
                                      sequence is typed specified by KeyData.
  @param  NotifyHandle                Points to the unique handle assigned to the registered notification.

  @retval EFI_SUCCESS                 The notification function was registered successfully.
  @retval EFI_OUT_OF_RESOURCES        Unable to allocate resources for necessary data structures.
  @retval I2C_ERROR_INVALID_PARAMETER       KeyData or NotifyHandle or KeyNotificationFunction is NULL.

**/
EFI_STATUS
EFIAPI
I2CKeyboardRegisterKeyNotify (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN  EFI_KEY_DATA                       *KeyData,
  IN  EFI_KEY_NOTIFY_FUNCTION            KeyNotificationFunction,
  OUT VOID                               **NotifyHandle
  )
{
  EFI_STATUS                        Status = EFI_SUCCESS;
  I2C_KB_DEV                        *I2CKeyboardDevice = NULL;
  LIST_ENTRY                        *Link = NULL;
  KEYBOARD_CONSOLE_IN_EX_NOTIFY     *CurrentNotify = NULL;
  KEYBOARD_CONSOLE_IN_EX_NOTIFY     *NewNotify = NULL;

  if ((!KeyData) ||
    (!NotifyHandle ) ||
    (!KeyNotificationFunction ) ||
    (!This))
  {
    Status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  I2CKeyboardDevice = TEXT_INPUT_EX_I2C_KB_DEV_FROM_THIS (This);

  // Return EFI_SUCCESS if the (KeyData, NotificationFunction) is already registered.
  for (Link = I2CKeyboardDevice->NotifyList.ForwardLink; Link != &I2CKeyboardDevice->NotifyList; Link = Link->ForwardLink)
  {
    CurrentNotify = CR (
      Link,
      KEYBOARD_CONSOLE_IN_EX_NOTIFY,
      NotifyEntry,
      I2C_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE
      );
    if (IsKeyRegistered (&CurrentNotify->KeyData, KeyData))
    {
      if (CurrentNotify->KeyNotificationFn == KeyNotificationFunction)
      {
        *NotifyHandle = CurrentNotify;
        Status = EFI_SUCCESS;
        goto Exit;
      }
    }
  }

  // Allocate resource to save the notification function
  NewNotify = (KEYBOARD_CONSOLE_IN_EX_NOTIFY *) AllocateZeroPool (sizeof (KEYBOARD_CONSOLE_IN_EX_NOTIFY));
  if (NewNotify == NULL)
  {
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  NewNotify->Signature         = I2C_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE;
  NewNotify->KeyNotificationFn = KeyNotificationFunction;
  CopyMem (&NewNotify->KeyData, KeyData, sizeof (EFI_KEY_DATA));
  InsertTailList (&I2CKeyboardDevice->NotifyList, &NewNotify->NotifyEntry);

  *NotifyHandle                = NewNotify;
  Status                       = EFI_SUCCESS;

Exit:
  return Status;
}

/**
  Remove a registered notification function from a particular keystroke.

  @param  This                      Protocol instance pointer.
  @param  NotificationHandle        The handle of the notification function being unregistered.

  @retval EFI_SUCCESS              The notification function was unregistered successfully.
  @retval I2C_ERROR_INVALID_PARAMETER    The NotificationHandle is invalid

**/
EFI_STATUS
EFIAPI
I2CKeyboardUnregisterKeyNotify (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN VOID                         *NotificationHandle
  )
{
  EFI_STATUS                            Status = EFI_SUCCESS;
  I2C_KB_DEV                            *I2CKeyboardDevice = NULL;
  LIST_ENTRY                            *Link = NULL;
  KEYBOARD_CONSOLE_IN_EX_NOTIFY         *CurrentNotify = NULL;

  if ((!This ) ||
    (!NotificationHandle))
  {
    Status = I2C_ERROR_INVALID_PARAMETER;
    goto Exit;
  }

  I2CKeyboardDevice = TEXT_INPUT_EX_I2C_KB_DEV_FROM_THIS (This);

  for (Link = I2CKeyboardDevice->NotifyList.ForwardLink;
    Link != &I2CKeyboardDevice->NotifyList;
    Link = Link->ForwardLink
    )
  {
    CurrentNotify = CR (
      Link,
      KEYBOARD_CONSOLE_IN_EX_NOTIFY,
      NotifyEntry,
      I2C_KB_CONSOLE_IN_EX_NOTIFY_SIGNATURE
      );
    if (CurrentNotify == NotificationHandle)
    {
      // Remove the notification function from NotifyList and free resources
      RemoveEntryList (&CurrentNotify->NotifyEntry);
      gBS->FreePool (CurrentNotify);
      Status = EFI_SUCCESS;
      goto Exit;
    }
  }

  // Can not find the specified Notification Handle
  Status = I2C_ERROR_INVALID_PARAMETER;

Exit:
  return Status;
}

/**
  Keyboard Init function for I2C keyboard initialization.

  @param Event       The timer event
  @param Context     EFI_HANDLE

**/
VOID
EFIAPI
I2CKeyboardInit (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS        Status = EFI_SUCCESS;
  UINT8             ReportID = 0;
  UINT8             *ReportDesc = NULL;
  KBD_INIT_CONFIG   *kbd_config = NULL;
  InputReport       gReportDesc = {0xFFFF};
  UINT32            Count50us = 0;

  ReportDesc = (UINT8 *)AllocateZeroPool (sizeof (UINT8) * (gHidDesc.wReportDescLength +1));
  if (!ReportDesc)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] AllocateZeroPool failed!\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Error;
  }

  kbd_config = (KBD_INIT_CONFIG *) Context;

  Status = ReadHidDescriptor(kbd_config->kbddevice.I2CHandle, gSlaveCfg);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] ReadHidDescriptor was unsuccessful: %d\n", Status));
    goto Error;
  }

  ZeroMem (kbd_config->kbddevice.LastKeyCodeArray, sizeof (UINT8) * 6);
  InitializeListHead (&kbd_config->kbddevice.NotifyList);
  is_kbd_up = 1;

  // Reset Keyboard Device exhaustively.
  Status = kbd_config->kbddevice.SimpleInputEx.Reset (
    &kbd_config->kbddevice.SimpleInputEx,
    TRUE
    );

  if (EFI_ERROR (Status))
  {
    gBS->UninstallMultipleProtocolInterfaces (
      kbd_config->ImageHandle,
      &gEfiSimpleTextInProtocolGuid,
      &kbd_config->kbddevice.SimpleInput,
      &gEfiSimpleTextInputExProtocolGuid,
      &kbd_config->kbddevice.SimpleInputEx,
      &gEfiDevicePathProtocolGuid,
      &KeyboardDxeDevicePath,
      NULL
      );
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] %a Exit Reset failed \r\n", __FUNCTION__));
    goto Error;
  }

  /*
    Considering, EC Keyboard interrupt pulse width duration of around 100us
    After issuing the reset command, EC will assert the interrupt within 200us
    Wait for 2 millisecond to Allowing EC device to perform keyboard 
    controller to reset and stable(to issue an interrupt to MSM).
  */
  while (Count50us <= RESET_SEQ_TIMEOUT_MS_COUNT)
  {
    /*
      Since, Interrupt pulse duration of 100us sampling the interrupt line for every 50us delay,
      to capture the Interrupt pulse.
    */
    SleepUs(SLEEP_50_US);
    
    Count50us++;

    Status = ReadInputReport(
      &kbd_config->kbddevice, 
      &gReportDesc
      );
    if (Status == EFI_SUCCESS)
    {
      DEBUG((EFI_D_INFO, "[I2CKeyboard] EC KB controller is stable after the reset command! :%d\n", Count50us));
      break;
    }
  }

  if (gReportDesc.length != 0x0)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] EC KB controller is not stable !\n"));
    Status = EFI_DEVICE_ERROR;
    goto Error;
  }

  Status = ReadReportDescriptor(
    kbd_config->kbddevice.I2CHandle, 
    gSlaveCfg, 
    ReportDesc
    );
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] ReadReportDescriptor() failed with %r\n", Status));
    goto Error;
  }

  Status = ParseReportDescriptor(
    ReportDesc, 
    &ReportID
    );
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] ParseReportDescriptor() failed with %r\n", Status));
    goto Error;
  }

  kbd_config->kbddevice.ReportID = ReportID;

Error:
  if (!ReportDesc)
  {
    gBS->FreePool(ReportDesc);
  }
  DEBUG((EFI_D_INFO, "[I2CKeyboard] %a Exit \r\n", __FUNCTION__));
  gBS->CloseEvent (Event );
}

/**
 * @brief Entrypoint of I2C Keyboard Driver.
 *
 * This function is the entrypoint of I2C Keyboard Driver.
 * Queries the EC device status from NV before initializing HID I2C protocol.
 * This function produces Simple Text Input Protocol and Simple Text Input Ex Protocol,
 * initializes the keyboard device, and submit Asynchronous Interrupt Transfer to manage
 * this keyboard device.
 *
 * @param  ImageHandle       The firmware allocated handle for the EFI image.
 * @param  SystemTable       A pointer to the EFI System Table.
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 */
EFI_STATUS
EFIAPI
I2CKeyboardEntryPoint(
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                        Status = EFI_SUCCESS;
  EFI_EVENT                         TimerEvent = NULL;
  KBD_INIT_CONFIG                   *i2c_kbd_config = NULL;
  EFI_EVENT                         WaitForKeyEvent;
  UINT8                             ReportID = 0;
  UINT8                             DeviceStatus = 0;
  i2c_instance                      I2cInstance = 0;

  /*
   * Failing to read device statys NV is treated as success,
   * to ensure I2C KB driver is attempted for load.
   */
  Status = GetNvEcDeviceStatus(&DeviceStatus);
  if (EFI_SUCCESS == Status)
  {
    if (!DeviceStatus)
    {
      DEBUG((EFI_D_ERROR,"[I2CKeyboard] EC device is inactive, exiting!\n"));
      Status = EFI_NOT_READY;
      goto Error;
    }
  }
  else
  {
    DEBUG((EFI_D_WARN,"[I2CKeyboard] GetNvEcDeviceStatus() failed with %r, ignoring and proceeding\n", Status));
    Status = EFI_SUCCESS;
  }

  gI2cKbDtconfig = I2CClientInitDT(I2CKB_NODE_NAME);
  if (NULL == gI2cKbDtconfig)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] Device tree not found for I2C Keyboard!\r\n"));
    Status = EFI_DEVICE_ERROR;
    goto Error;
  }

  Status = I2CClientGetSlaveCfg(I2CKB_NODE_NAME, &gSlaveCfg);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR,"[I2CKeyboard] I2CClientGetSlaveCfg() failed with %r\n", Status));
    goto Error;
  }

  Status = I2CClientGetI2cInstance(I2CKB_NODE_NAME, &I2cInstance);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR,"[I2CKeyboard] I2CClientGetI2cInstance() failed with %r\n", Status));
    goto Error;
  }

  Status = I2CClientGetHidDescCfg(I2CKB_NODE_NAME,
    &gHidDescAddrHigh,
    &gHidDescAddrLow);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR,"[I2CKeyboard] I2CClientGetHidDescCfg() failed with %r\n", Status));
    goto Error;
  }

  // Allocate private data
  i2c_kbd_config = AllocateZeroPool (sizeof(KBD_INIT_CONFIG));
  if (i2c_kbd_config == NULL)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] AllocateZeroPool failed!\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto Error;
  }

  i2c_kbd_config->ImageHandle = ImageHandle;

  // Initialize TLMM
  Status = gBS->LocateProtocol(
    &gEfiTLMMProtocolGuid,
    NULL,
    (void**)&gTLMMProtocol);
  if (EFI_ERROR (Status))
  {
    DEBUG ((EFI_D_ERROR, "[I2CKeyboard] %a: LocateProtocol(gEfiTLMMProtocolGuid) failed 0x%x\r\n",
    __FUNCTION__, Status));
    goto Error;
  }

  if (gTLMMProtocol == NULL)
  {
    DEBUG ((EFI_D_ERROR, "[I2CKeyboard] Error locating TLMM protocol %x\r\n", Status));
    Status = EFI_UNSUPPORTED;
    goto ErrorFreeList;
  }

  // Initialize the I2C Core
  Status = i2c_open(
    (i2c_instance) (I2cInstance),
    &(i2c_kbd_config->kbddevice.I2CHandle));
  if (EFI_ERROR (Status))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] i2c_open() failed with %r\n", Status));
    goto Error;
  }

  // Init TLMM/PMIC resources in PowerOn sequence as mentioned in device tree
  Status = I2CClientPowerOn(I2CKB_NODE_NAME);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] I2CClientPowerOn() failed with %r\n", Status));
    goto Error;
  }

  // Configure nINT so it can be read later
  Status = I2CClientGetGpioCfg(I2CKB_NODE_NAME, &gClientGpioCfg);
  if (EFI_SUCCESS == Status)
  {
    Status = ConfigKbGpio();
    if (EFI_ERROR(Status))
    {
      DEBUG((EFI_D_ERROR, "[I2CKeyboard] I2CClientGetGpioCfg() failed with %r\n", Status));
      goto Error;
    }
  }

  // Setup the device instance
  i2c_kbd_config->kbddevice.Signature                         = I2C_KB_DEV_SIGNATURE;
  i2c_kbd_config->kbddevice.ReportID                          = ReportID;
  i2c_kbd_config->kbddevice.I2CConfig                         = gSlaveCfg;
  (i2c_kbd_config->kbddevice.SimpleInput).Reset               = I2CKeyboardReset;
  (i2c_kbd_config->kbddevice.SimpleInput).ReadKeyStroke       = I2CKeyboardReadKeyStroke;

  (i2c_kbd_config->kbddevice.SimpleInputEx).Reset               = I2CKeyboardResetEx;
  (i2c_kbd_config->kbddevice.SimpleInputEx).ReadKeyStrokeEx     = I2CKeyboardReadKeyStrokeEx;
  (i2c_kbd_config->kbddevice.SimpleInputEx).SetState            = I2CKeyboardSetState;
  (i2c_kbd_config->kbddevice.SimpleInputEx).RegisterKeyNotify   = I2CKeyboardRegisterKeyNotify;
  (i2c_kbd_config->kbddevice.SimpleInputEx).UnregisterKeyNotify = I2CKeyboardUnregisterKeyNotify;

  ZeroMem(
    i2c_kbd_config->kbddevice.LastKeyCodeArray,
    sizeof(UINT8)*6);

  InitializeListHead(&i2c_kbd_config->kbddevice.NotifyList);

  // Setup a periodic timer, used for reading keystrokes at a fixed interval
  Status = gBS->CreateEvent (
    EVT_TIMER | EVT_NOTIFY_SIGNAL,
    TPL_CALLBACK,
    I2CKeyboardTimerHandler,
    &i2c_kbd_config->kbddevice,
    &i2c_kbd_config->kbddevice.TimerEvent
    );
  if (EFI_ERROR (Status))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] Error setting up Timer %d\n", Status));
    goto ErrorFreeList;
  }

  Status = gBS->SetTimer(
    i2c_kbd_config->kbddevice.TimerEvent,
    TimerPeriodic,
    KEYBOARD_TIMER_INTERVAL);

  /*
   * Setup the WaitForKey event
   * The callback will be called anytime something is waiting on 'WaitForKey'
   * and the event is not signalled.
   */
  Status = gBS->CreateEvent (
    EVT_NOTIFY_WAIT,
    TPL_CALLBACK,
    I2CKeyboardWaitForKey,
    &i2c_kbd_config->kbddevice,
    &WaitForKeyEvent
    );
  if (EFI_ERROR (Status))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] Error setting up WaitForKey %d\n", Status));
    goto ErrorFreeList;
  }

  i2c_kbd_config->kbddevice.SimpleInput.WaitForKey = WaitForKeyEvent;
  i2c_kbd_config->kbddevice.SimpleInputEx.WaitForKeyEx = WaitForKeyEvent;

  // Install protocol interfaces for the keyboard device.
  Status = gBS->InstallMultipleProtocolInterfaces (
    &(i2c_kbd_config->ImageHandle),
    &gEfiSimpleTextInProtocolGuid,
    &i2c_kbd_config->kbddevice.SimpleInput,
    &gEfiSimpleTextInputExProtocolGuid,
    &i2c_kbd_config->kbddevice.SimpleInputEx,
    &gEfiDevicePathProtocolGuid,
    &KeyboardDxeDevicePath,
    NULL
    );
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] Error installing simpletext protocol %d\n", Status));
    goto ErrorFreeList;
  }

  Status = gBS->CreateEvent (
    EVT_TIMER | EVT_NOTIFY_SIGNAL,
    TPL_CALLBACK,
    I2CKeyboardInit,
    i2c_kbd_config,
    &TimerEvent
    );
  if (EFI_ERROR (Status))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] Error setting up Timer %d\n", Status));
    goto ErrorFreeList;
  }

  Status = I2CClientGetGpioInitInterval(I2CKB_NODE_NAME, &gGpioInitInterval);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR,"[I2CKeyboard] I2CClientGetGpioInitInterval() failed with %r\n", Status));
    goto Error;
  }

  Status = gBS->SetTimer(
    TimerEvent,
    TimerPeriodic,
    (gGpioInitInterval));

  goto Exit;

ErrorFreeList:
  KbdFreeNotifyList (&i2c_kbd_config->kbddevice.NotifyList);


Error:

  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] Error starting keyboard %r\n", Status));
  }

  if (i2c_kbd_config)
  {
    if ((&(i2c_kbd_config->kbddevice) != NULL) &&
        (i2c_kbd_config->kbddevice.SimpleInput.WaitForKey != NULL))
    {
      gBS->CloseEvent(i2c_kbd_config->kbddevice.SimpleInput.WaitForKey);
    }
    if ((&(i2c_kbd_config->kbddevice) != NULL) &&
        (i2c_kbd_config->kbddevice.TimerEvent != NULL))
    {
      gBS->CloseEvent(i2c_kbd_config->kbddevice.TimerEvent);
    }
    if ((&(i2c_kbd_config->kbddevice) != NULL) &&
        (i2c_kbd_config->kbddevice.SimpleInputEx.WaitForKeyEx != NULL))
    {
      gBS->CloseEvent(i2c_kbd_config->kbddevice.SimpleInputEx.WaitForKeyEx);
    }
    if (&i2c_kbd_config->kbddevice != NULL)
    {
      gBS->FreePool(&i2c_kbd_config->kbddevice);
    }
    if (&i2c_kbd_config->ImageHandle != NULL)
    {
      gBS->FreePool(&i2c_kbd_config->ImageHandle);
    }
  }
  Status = I2CClientDeInitDT(gI2cKbDtconfig);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] I2CClientDeInitDT() failed with %r\n", Status));
  }

Exit:
  DEBUG((EFI_D_INFO, "[I2CKeyboard]  %a Exit \r\n", __FUNCTION__));
  return Status;
}

/**
  Sends the output Report Request

  @param  I2CKeyboardDevice  The I2C_KB_DEV instance.
  @param  Led                Led data

  @retval EFI_SUCCESS             Output report sent successfully.
  @retval EFI_INVALID_PARAMETER   I2C handle is not configured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.

**/
EFI_STATUS
SetOutputReport (
  IN  I2C_KB_DEV    *I2cKeyboardDevice,
  IN  VOID          *Led
  )
{
  EFI_STATUS        Status = EFI_SUCCESS;
  UINT8             wrBuf[6] = {0};
  i2c_descriptor    write_desc = {0};

  DEBUG((EFI_D_INFO, "[I2CKeyboard] SetOutputReport [ENTRY] \n"));

  if (!I2cKeyboardDevice)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] SetOutputReport, i2c_handle is null\n"));
    Status = I2cStatusToEfiStatus(I2C_ERROR_INVALID_PARAMETER);
    goto Error;
  }

  wrBuf[0] = LOW_BYTE(gHidDesc.wOutputRegister);
  wrBuf[1] = HIGH_BYTE(gHidDesc.wOutputRegister);
  wrBuf[2] = 0x04;//length-byte lsb (Length feild include 2 bytes of length + 1 byte of Report id + 1 byte of LED data)
  wrBuf[3] = 0x00;//length-byte msb
  wrBuf[4] = I2cKeyboardDevice->ReportID;
  wrBuf[5] = *((UINT8 *)Led);/*LED data*/


  write_desc.buffer = wrBuf; // Assigning Write buffer address
  write_desc.length = 6; // Size of the wrBuf
  write_desc.flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  Status = i2ckb_block_write(
    I2cKeyboardDevice->I2CHandle,
    I2cKeyboardDevice->I2CConfig,
    wrBuf,
    6
    );
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] i2ckb_block_write() failed with %r \n", Status));
    goto Error;
  }

Error:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] SetOutputReport exited with %r \n", Status));

  return Status;
}

/**
  Sets I2C keyboard LED state.

  @param  I2CKeyboardDevice  The I2C_KB_DEV instance.

  @retval EFI_SUCCESS             Keyboard LED is lighten successfully.
  @retval EFI_INVALID_PARAMETER   I2C handle is not confiured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.

**/
EFI_STATUS
SetKeyboardLED (
  IN  I2C_KB_DEV    *I2CKeyboardDevice
  )
{
  KEYBOARD_LED_MAP  Led = {0};
  EFI_STATUS        Status = EFI_SUCCESS;

  DEBUG((EFI_D_INFO, "[I2CKeyboard] SetKeyboardLED [ENTRY] \n"));
  if (!I2CKeyboardDevice)
  {
    DEBUG((EFI_D_ERROR, "[I2CKeyboard] SetKeyboardLED, i2c_handle is null\n"));
    Status = I2cStatusToEfiStatus(I2C_ERROR_INVALID_PARAMETER);
    goto Error;
  }

  // Set each field in Led map.
  Led.KeyboardNumLock    = (UINT8)((I2CKeyboardDevice->NumLock) ? 1 : 0);
  Led.KeyboardCapsLock   = (UINT8)((I2CKeyboardDevice->CapsLock) ? 1 : 0);
  Led.KeyboardScrollLock = (UINT8) ((I2CKeyboardDevice->ScrollLock) ? 1 : 0);
  Led.Resrvd             = 0;

  // Call Set_Report Request to lighten the LED.
  Status = SetOutputReport(I2CKeyboardDevice,(UINT8 *)&Led);

Error:
  DEBUG((EFI_D_INFO, "[I2CKeyboard] SetKeyboardLED exited with %r \n", Status));
  return Status;
}
