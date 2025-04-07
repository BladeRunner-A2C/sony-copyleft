/** @file
  Contains routines for flashing & updating ITE Embedded Controller (EC)

Copyright (c) 2021-2023 Qualcomm Technologies Inc. All rights reserved.
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*=============================================================================
                              EDIT HISTORY

 when       who                 what, where, why
 --------   ---                 ----------------------------------------------------------
 05/05/23   ananns              Corrected the logic to update EC firmware using -U option
 04/26/23   chic                Refine i2c_block_read/write to support multiple type payload transaction
 03/03/23   bkulkarn            Switch to EfiShellProtocol to resolve UEFI panic for long filename
 12/08/22   bkulkarn            Update Hamoa EC FW partition size/I2C core instance, code refactoring
 11/14/22   ananns              Added code documentation and function descriptions
 10/17/21   sumesahu            Initial revision
=============================================================================*/

#ifndef _EC_FLASH_APP_H_
#define _EC_FLASH_APP_H_

/* System Specific Headers */
#include <Library/UefiLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/Shell.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* EC Specific Headers */
#include <ECI2C.h>
#include <ECLog.h>
#include <ECUpgrade.h>
#include <ECPredefine.h>

/* Sleep */
#define SleepMs(time_in_ms) gBS->Stall(time_in_ms)
#define TRANSFER_DELAY 5000
#include "BuildVersion.h"
#define BUFFER_SIZE 0x8000


/* I2C Slave Device Types */
#define SLAVE_TYPE_NORM                         0 //normal addressed slaves
#define SLAVE_TYPE_REG                          1 //register addressed slaves
#define SLAVE_TYPE_MEM                          2 //memory addressed slaves

/* Delay Values */
#define STALL_MS                                5000
#define Delay_TIME_MS                           2500
#define TIME_1MS                                1000
#define TIME_5MS                                5000
#define TIME_10MS                               10000
#define TIME_30MS                               30000
#define TIME_50MS                               50000
#define TIME_100MS                              100000
#define TIME_200MS                              200000
#define TIME_300MS                              300000
#define TIME_500MS                              500000
#define TIME_2SEC                               2000000
#define TIME_4SEC                               4000000
#define TIME_8SEC                               8000000
/* ITE8987 EC VERSION */

// Get High Bytes
#define HIGH_BYTE(WORD16) (((WORD16) & 0xFF00) >> 8)
// Get Low Bytes
#define LOW_BYTE(WORD16)  (((WORD16) & 0x00FF))
// COMMANDS
#define RESET_CMD_HIGH 0x01
#define RESET_CMD_LOW 0x00
#define ENABLE_CMD_HIGH 0x08
#define ENABLE_CMD_LOW 0x00

#define _CMD_SPI_READ_ID            0xE6
#define _EXTERNAL_SPI               0x0F

EFI_STATUS Check_OnIC_EC_Version(void);

/**
  Convert Ascii code to Unicode

  @param AStr             Pointer to Ascii string
  @param Size             size of the Ascii code
  @param UStr             Pointer to Unicode string

**/
void
AsciiToUnicode(
  CHAR8  *AStr,
  UINTN  Size,
  CHAR16  *UStr
  );

/**
  @brief Reads the EC Firmware and store into a buffer

  @param fileName               Pointer to the filename

  @retval EFI_SUCCESS           Reading the EC file to buffer is successfull
  @retval EFI_OUT_OF_RESOURCES  FilenameSize is out of range  or unable to allocate the memory
  @retval EFI_VOLUME_CORRUPTED  File buffer size is zero
  @retval EFI_INVALID_PARAMETER FileName/deviceContext handle is empty
**/
EFI_STATUS
ReadECFirmwareToBuffer(
  CHAR16 *fileName
  );

/**
  Check On binary EC version

  @retval EFI_SUCCESS           Checking OnBinary EC version is successfull
  @retval EFI_ABORTED           No FW binary data is present
  @retval EFI_OUT_OF_RESOURCES  Unable to allocate the memory
  @retval EFI_INVALID_PARAMETER deviceContext handle is NULL
**/
EFI_STATUS
Check_OnBinary_EC_Version(void);

/**
  Function to check if the EC firmware versions are different

  @retval TRUE  - On IC and binary EC versions are same.
  @retval FALSE - On IC and binary EC versions are different.

**/ 
BOOLEAN
IsFwVersionDiff(void);


/**
  Check On IC EC version

  @retval EFI_SUCCESS -  OnIC EC version is successfull
  @retval EFI_DEVICE_ERROR  I2C block read is failed
**/
EFI_STATUS
Check_OnIC_EC_Version(void);

/**
  Write to EC register

  @param reg                EC register value of type UINT16
  @param data               Data value of type UINT8

  @retval EFI_SUCCESS -     Write to the EC reigster is successfull
  @retval EFI_DEVICE_ERROR  I2C block write is failed
**/
EFI_STATUS
Write_EC_Register(
  UINT16 reg,
  UINT8 data
  );

/**
  Read from the EC register

  @param reg                    EC register value of type UINT16
  @param length                 Length no of bytes need to read from EC

  @retval EFI_SUCCESS -         Read from the EC reigster is successfull
  @retval EFI_DEVICE_ERROR      I2C block write is failed
  @retval EFI_OUT_OF_RESOURCES  Unable to allocate the memory
**/
EFI_STATUS
Read_EC_Register(
  UINT16 reg,
  UINT8 length
  );

/**
  Device Initialization

  @retval EFI_SUCCESS -         I2C core initialization is successfull
  @retval EFI_OUT_OF_RESOURCES  Unable to allocate the memory
  @retval EFI_DEVICE_ERROR      I2C core initialization is failed
**/
EFI_STATUS
DeviceInit(void);

/**
  OP CommandParser

  @retval wBuff - Convert String to hex value
**/
UINT8
OPCommandParser(
  int i,
  CHAR8  **Argv
  );

/**
  EraseDesignated CommandParser
**/
void
EraseDesignatedCommandParser(
  int i,
  CHAR8  **Argv
  );

/**
  Show the command usage
**/
void ShowUsage(void);

/**
  EC Flash App main

  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS -  EC flashing is successfull
**/
EFI_STATUS
EFIAPI
ECFlashAppMain (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );

/* HID functions */

/**
  Reset the device

  @param i2c_handle     Pointer to i2c handle
  @param cfg            Pointer to i2c config

  @retval EFI_SUCCESS             Reset completed successfully.
  @retval EFI_INVALID_PARAMETER   I2C handle is not confiured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.
**/
EFI_STATUS
ResetDevice(
  IN VOID * i2c_handle,
  IN i2c_slave_config cfg
  );

/**
  Get the input report from the device

  @param i2c_handle     Pointer to i2c handle
  @param cfg            Pointer to i2c config

  @retval EFI_SUCCESS             Input report retrieval completed successfully.
  @retval EFI_INVALID_PARAMETER   I2C handle is not confiured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.
**/
EFI_STATUS
GetInputReport(
  IN VOID * i2c_handle,
  IN i2c_slave_config cfg,
  OUT InputReport* gReportDesc
  );

/**
  Get report descriptor from HID compliant device

  @param i2c_handle     Pointer to i2c handle
  @param cfg            Pointer to i2c config

  @retval EFI_SUCCESS             Report descriptor retrieved successfully.
  @retval EFI_INVALID_PARAMETER   I2C handle is not confiured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.
**/
EFI_STATUS
ReadReportDescriptor(
  IN VOID * i2c_handle,
  IN i2c_slave_config cfg,
  OUT UINT8* ReportDesc
  );

/**
  Parse report descriptor from HID compliant device

  @param ReportDesc     Pointer to report descriptor

  @retval EFI_SUCCESS             Report descriptor parsed successfully.
  @retval EFI_DEVICE_ERROR        Device is not valid.
**/
EFI_STATUS
ParseReportDescriptor(
  IN UINT8 * ReportDesc,
  OUT UINT8 * ReportID
  );

/**
  Get HID descriptor from HID compliant device

  @param i2c_handle     Pointer to i2c handle
  @param cfg            Pointer to i2c config

  @retval EFI_SUCCESS             HID descriptor retrieved successfully.
  @retval EFI_INVALID_PARAMETER   I2C handle is not confiured properly.
  @retval EFI_DEVICE_ERROR        Device did not respond.
**/
EFI_STATUS
ReadHidDescriptor(
  IN VOID * i2c_handle,
  IN i2c_slave_config cfg
  );

#endif
