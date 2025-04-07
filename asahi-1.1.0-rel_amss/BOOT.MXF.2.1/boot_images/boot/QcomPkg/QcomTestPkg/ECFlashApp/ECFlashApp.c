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


#include <ECFlashApp.h>
#include <ECI2C.h>
#include <ECLog.h>

EFI_SHELL_PROTOCOL      *mShellProtocol = NULL;

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
  )
{
  UINTN Idx = 0;

  while (AStr[Idx] != 0)
  {
    UStr[Idx] = (CHAR16) AStr[Idx];
    if (Idx == Size)
    {
      break;
    }
    Idx++;
  }
  UStr[Idx] = 0;
}

/**
 * @brief Get shell protocol.
 *
 * @return Pointer to shell protocol.
**/
EFI_SHELL_PROTOCOL *
GetShellProtocol(
  VOID
  )
{
  EFI_STATUS    status = EFI_SUCCESS;

  if (mShellProtocol == NULL)
  {
    status = gBS->LocateProtocol(
        &gEfiShellProtocolGuid,
        NULL,
        (VOID **) &mShellProtocol
        );
    if (EFI_ERROR (status))
    {
      mShellProtocol = NULL;
      EC_E("Failed to locate shell protocol!\n");
      goto Exit;
    }
  }

Exit:
  return mShellProtocol;
}

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
  )
{
  EFI_STATUS            status = EFI_SUCCESS;
  EFI_SHELL_PROTOCOL    *shellProtocol = NULL;
  SHELL_FILE_HANDLE     handle = NULL;
  UINTN                 tempBufferSize = 0;
  UINT64                fileSize = 0;
  VOID                  *tempBuffer = NULL;

  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  EC_TRACE();

  if (!fileName)
  {
    EC_E("Invalid filename!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  shellProtocol = GetShellProtocol();
  if (!shellProtocol)
  {
    EC_E("Failed to locate Shell protocol!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = shellProtocol->OpenFileByName(
    fileName,
    &handle,
    EFI_FILE_MODE_READ
    );
  if (EFI_ERROR (status))
  {
    EC_E("OpenFileByName() failed with %r\n", status);
    goto Exit;
  }

  status = shellProtocol->GetFileSize(
    handle,
    &fileSize);
  if (EFI_ERROR(status))
  {
    EC_E("GetFileSize() failed with %r\n", status);
    goto Exit;
  }

  tempBufferSize = (UINTN) fileSize;

  tempBuffer = AllocateZeroPool(tempBufferSize);
  if (!tempBuffer)
  {
    status = EFI_OUT_OF_RESOURCES;
    EC_E("Failed to allocate memory of %d bytes\n", tempBufferSize);
    goto Exit;
  }

  status = shellProtocol->ReadFile(
    handle,
    &tempBufferSize,
    tempBuffer
    );
  if (EFI_ERROR (status))
  {
    EC_E("ReadFile() failed with %r\n", status);
    goto Exit;
  }

  deviceContext->fw_img_data_size = tempBufferSize;
  EC_I("Bin File Size: %d\n", deviceContext->fw_img_data_size);

  deviceContext->fw_img_data = (byte *)AllocateZeroPool(
    sizeof(byte) * deviceContext->fw_img_data_size
    );

  if (!deviceContext->fw_img_data)
  {
    status = EFI_OUT_OF_RESOURCES;
    EC_E("Failed to allocate memory of %d bytes\n", deviceContext->fw_img_data_size);
    goto Exit;
  }

  CopyMem(
   deviceContext->fw_img_data,
   &(tempBuffer[0]),
   tempBufferSize
   );

  if ('E' != deviceContext->fw_img_data[EC_VERSION_OFFSET])
  {
    status = EFI_DEVICE_ERROR;
    EC_E("FW binary is not copied properly, aborting update!\n");
    goto Exit;
  }

  EC_I("FW binary is copied properly\n");

Exit:

  if (handle)
  {
    shellProtocol->CloseFile(handle);
    handle = NULL;
  }

  if (tempBuffer)
  {
    FreePool(tempBuffer);
    tempBuffer = NULL;
  }

  return status;
}

/**
  Check On binary EC version

  @retval EFI_SUCCESS           Checking OnBinary EC version is successfull
  @retval EFI_ABORTED           No FW binary data is present
  @retval EFI_OUT_OF_RESOURCES  Unable to allocate the memory
  @retval EFI_INVALID_PARAMETER deviceContext handle is NULL
**/
EFI_STATUS
Check_OnBinary_EC_Version(void)
{
  EFI_STATUS    Status = EFI_SUCCESS;
  CHAR8         *tempStr = NULL;
  char          *ver_start_pos = NULL;  // Version start address
  char          *ver_end_pos = NULL;   // Version end address
  int           i = 0, ec_ver_addr=0;

  if (!deviceContext)
  {
    EC_E("- deviceContext NULL!!\n");
    Status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext->fw_img_data)
  {
    EC_E("Error. No fw bin data present!!\n");
    Status = EFI_ABORTED;
    goto Exit;
  }

  EC_TRACE();

  tempStr = (CHAR8 *)AllocateZeroPool(BUFFER_SIZE);
  if (!tempStr)
  {
    EC_E("Failed to allocation requested memory!!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  CopyMem(
    tempStr,
    deviceContext->fw_img_data,
    BUFFER_SIZE
    );

  EC_I("Size of bin file=%dKB\n", (deviceContext->fw_img_data_size/1024));

  if (tempStr[EC_VERSION_OFFSET] == 'E')
  {
    EC_I("FW binary is copied properly\n");
  }
  else
  {
    EC_E("FW binary not copied properly. Aborting update!\n");
    Status = EFI_ABORTED;
    goto Exit;
  }

  /*
   * Eliminate Null characters in the binary file
   * just to automatically find the "EC Ver:" string
   */
  for (i=0;i<BUFFER_SIZE;i++)
  {
    if (tempStr[i]=='\0')
    {
      tempStr[i]='_';
    }
  }

  ver_start_pos = strstr( tempStr,"EC VER:" );
  if ((ver_start_pos != NULL) &&
    (tempStr+BUFFER_SIZE-ver_start_pos)>=15)
  {
    ec_ver_addr =  ver_start_pos - tempStr + strlen("EC VER:");
    ver_end_pos = strchr(&(tempStr[ec_ver_addr]),'$');

    EC_D( "Length of EC version:%ld\n", ver_end_pos - ver_start_pos);

    /* Overall Length of string "EC VER:00:01:00T1" is 17 bytes */
    if ((ver_end_pos != NULL) &&
      (((ver_end_pos - ver_start_pos) >= 15) ||
      ((ver_end_pos - ver_start_pos) <= 18)))
    {
      deviceContext->on_bin_info.main_ver  =  (tempStr[ec_ver_addr+0] - '0')*10 + (tempStr[ec_ver_addr+1] - '0');
      deviceContext->on_bin_info.sub_ver   =  (tempStr[ec_ver_addr+3] - '0')*10 + (tempStr[ec_ver_addr+4] - '0');
      deviceContext->on_bin_info.test_ver  =  (tempStr[ec_ver_addr+6] - '0')*10 + (tempStr[ec_ver_addr+7] - '0');

      if (deviceContext->query_version)
      {
        EC_I("========On Binary EC FW Version=======\n");
        EC_I("MainVersion=%d\n", deviceContext->on_bin_info.main_ver);
        EC_I("SubVersion=%d\n" , deviceContext->on_bin_info.sub_ver);
        EC_I("TestVersion=%d\n", deviceContext->on_bin_info.test_ver);
        EC_I("===================================\n");
      }
    }
  }

Exit:
  if (tempStr)
  {
    FreePool(tempStr);
    tempStr = NULL;
  }
  return Status;
}

/**
  Function to check if the EC firmware versions are different

  @retval FALSE  - On IC and binary EC versions are same.
  @retval TRUE - On IC and binary EC versions are different.

**/ 
BOOLEAN
IsFwVersionDiff(void)
{
  BOOLEAN result = FALSE;
  
  if (!deviceContext)
  {
    result = FALSE;
    EC_E("- deviceContext is NULL!!\n");
    goto Exit;
  }

  if ((deviceContext->on_ic_info.main_ver == deviceContext->on_bin_info.main_ver) &&
    (deviceContext->on_ic_info.sub_ver == deviceContext->on_bin_info.sub_ver) &&
    (deviceContext->on_ic_info.test_ver == deviceContext->on_bin_info.test_ver))
  {
    EC_D("Both FW's are same!!\n");
    result = FALSE;
  }
  else
  {
    EC_I("Both FW's are not same!!\n");
    result = TRUE;
  }

Exit:
  return result;
}

/**
  Check On IC EC version

  @retval EFI_SUCCESS -  OnIC EC version is successfull
  @retval EFI_DEVICE_ERROR  I2C block read is failed
  @retval EFI_INVALID_PARAMETER  deviceContext handle is NULL
**/
EFI_STATUS
Check_OnIC_EC_Version(void)
{
  EFI_STATUS  Status                                  = EFI_SUCCESS;
  uint8       rdBuf[EC_VERSION_DATA_SIZE]             = {0xff, 0xff, 0xff, 0xff};

  if (!deviceContext)
  {
    EC_E("- deviceContext NULL!!\n");
    Status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  /* Verify EC Version with Block Read Protocol */
  /*This command support in both BLK & MLK EC code*/
  Status = i2c_block_read (
    EC_VERSION_CMD_RO,
    rdBuf,
    STATIC_DAT_LEN,
    30,
    3);
  if (EFI_ERROR(Status))
  {
    EC_E("Check_OnIC_EC_Version() failed with %r\n", Status);
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  deviceContext->on_ic_info.main_ver = (rdBuf[2]& 0x0F) + (((rdBuf[2] >> 4) & 0x0F) * 10);
  deviceContext->on_ic_info.sub_ver  = (rdBuf[1]& 0x0F) + (((rdBuf[1] >> 4) & 0x0F) * 10);
  deviceContext->on_ic_info.test_ver = (rdBuf[0]& 0x0F) + (((rdBuf[0] >> 4) & 0x0F) * 10);

  EC_I("========On IC EC FW Version=======\n");
  EC_I("MainVersion = %d \n", deviceContext->on_ic_info.main_ver);
  EC_I("SubVersion  = %d \n", deviceContext->on_ic_info.sub_ver);
  EC_I("TestVersion = %d \n", deviceContext->on_ic_info.test_ver);
  EC_I("===============================\n\n");

  if ((0xff == rdBuf[0]) &&
     (0xff == rdBuf[1]) &&
     (0xff == rdBuf[2]))
  {
    EC_E("i2c_block_read for ec version Failed!!\n");
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_D( " i2c_block_read for ec version Success!!\n");

Exit:
  return Status;
}

int isspace(int c)
{
  return c == ' ' || (unsigned)c-'\t' < 5;
}
int isdigit(int c)
{
  return (unsigned)c-'0' < 10;
}

int atoi(const char *s)
{
  int n=0, neg=0;
  while (isspace(*s))
  {
    s++;
  }
  switch (*s) 
  {
    case '-': neg=1;
    case '+': s++;
  }
  /* Compute n as a negative number to avoid overflow on INT_MIN */
  while (isdigit(*s))
  {
    n = 10*n - (*s++ - '0');
  }
  return neg ? n : -n;
}

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
  )
{
  EFI_STATUS  Status    = EFI_SUCCESS;
  UINT8       wdBuf[3]  = { reg & 0xFF, (reg >> 8) & 0xFF, data};

  Status = i2c_block_write (
    EC_REGISTER_WRITE_WO,
    wdBuf,
    0,
    0);
  if (EFI_ERROR(Status))
  {
    EC_E("Write_EC_Register() failed with %r\n", Status);
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

Exit:
  return Status;
}

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
    )
{
  EFI_STATUS  Status    = EFI_SUCCESS;
  UINT8       wdBuf[3]  = { reg & 0xFF, (reg >> 8) & 0xFF, length};
  UINT8       *rdBuf    = NULL;

  Status = i2c_block_write (
    EC_REGISTER_READ_WO,
    wdBuf,
    0,
    0);
  if (EFI_ERROR(Status))
  {
    EC_E("- Read_EC_Register() failed with %r\n", Status);
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  SleepMs(1000);

  rdBuf = AllocateZeroPool(sizeof (UINT8) * length);
  if (rdBuf == NULL)
  {
    EC_E("Failed during memory allocation!!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  Status = i2c_block_read (
    BULK_READ_CMD_RO,
    rdBuf,
    (length+1),
    0,
    0);
  
  if (EFI_ERROR(Status))
  {
    EC_E("- Read_EC_Register() failed with %r\n", Status);
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_I("- Values[%d]:", length);
  for(int i = 0; i< length; i++)
  {
    AsciiPrint("0x%x, ", (UINT8)rdBuf[i]);
  }
  AsciiPrint("\n");

Exit:
  if (rdBuf)
  {
    FreePool(rdBuf);
    rdBuf = NULL;
  }
  return Status;
}

/**
  Device Initialization

  @retval EFI_SUCCESS -         I2C core initialization is successfull
  @retval EFI_OUT_OF_RESOURCES  Unable to allocate the memory
  @retval EFI_DEVICE_ERROR      I2C core initialization is failed
**/
EFI_STATUS
DeviceInit(void)
{
  EFI_STATUS Status = EFI_SUCCESS;

  deviceContext = AllocateZeroPool(sizeof (EC_DEVICE_CONTEXT));
  if (deviceContext == NULL)
  {
    EC_E("Failed during memory allocation!!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  deviceContext->slave_addr           = I2C_EC_SLAVE_ADDRESS;
  deviceContext->recovery_slave_addr  = I2C_PREDEFINE_EC_SLAVE_ADDRESS;
  deviceContext->activeI2cChannel     = ACPI_I2C_PROTOCOL;
  /* I2C Core Initialization */
  Status = I2C_Init();
  if (EFI_ERROR(Status))
  {
    EC_E("I2C_Init() failed with %r\n", Status);
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

Exit:
  return Status;
}

/**
  OP CommandParser

  @retval wBuff - Convert String to hex value
**/
UINT8
OPCommandParser(
  int i,
  CHAR8  **Argv
  )
{
  CHAR8 *ArgStr = NULL;
  UINT8 wBuff   = 0;

  ArgStr = Argv[i];
  if (!strcmp("DM",ArgStr))
  {
    wBuff = DIS_MIRROR_CMD;
  }
  else if (!strcmp("EMI",ArgStr))
  {
    wBuff = FORCE_MIRROR_IMMEDIATLY;
  }
  else if (!strcmp("EMS",ArgStr))
  {
    wBuff = FORCE_MIRROR_AFTER_SHUTDOWN;
  }
  else if (!strcmp("IMC12",ArgStr))
  {
    wBuff = COPY_INT_MBK_TO_P2;
  }
  else if (!strcmp("IMC21",ArgStr))
  {
    wBuff = COPY_INT_MBK_TO_P1;
  }
  else if (!strcmp("IBC12",ArgStr))
  {
    wBuff = COPY_INT_BBK_TO_P2;
  }
  else if (!strcmp("IBC21",ArgStr))
  {
    wBuff = COPY_INT_BBK_TO_P1;
  }
  else if (!strcmp("ENBBK",ArgStr))
  {
    wBuff = ENTER_BBK_CMD;
  }
  else if (!strcmp("DISBBK",ArgStr))
  {
    wBuff = EXIT_BBK_CMD;
  }
  else if (!strcmp("RCIP1",ArgStr))
  {
    wBuff = RUN_CHECKSUM_INT_P1_32K;
  }
  else if (!strcmp("RCIP2",ArgStr))
  {
    wBuff = RUN_CHECKSUM_INT_P2_32K;
  }
  else if (!strcmp("RCXP1",ArgStr))
  {
    wBuff = RUN_CHECKSUM_EXT_P1_128K;
  }
  else if (!strcmp("RCXP2",ArgStr))
  {
    wBuff = RUN_CHECKSUM_EXT_P2_128K;
  }

  return wBuff;
}

/**
  EraseDesignated CommandParser
**/
void
EraseDesignatedCommandParser(
  int i,
  CHAR8  **Argv
  )
{
  CHAR8 *ArgStr = NULL;
  ArgStr = Argv[i];
  if (!strcmp("IP1B",ArgStr))
  {
    deviceContext->ctrl_path = INT_FLASH_CTRL_PATH;
    deviceContext->flash_type = INTERNAL_FLASH_P1B;
  }
  else if (!strcmp("IP2B",ArgStr))
  {
    deviceContext->ctrl_path = INT_FLASH_CTRL_PATH;
    deviceContext->flash_type = INTERNAL_FLASH_P2B;
  }
  else if (!strcmp("IP1M",ArgStr))
  {
    deviceContext->ctrl_path = INT_FLASH_CTRL_PATH;
    deviceContext->flash_type = INTERNAL_FLASH_P1M;
  }
  else if (!strcmp("IP2M",ArgStr))
  {
    deviceContext->ctrl_path = INT_FLASH_CTRL_PATH;
    deviceContext->flash_type = INTERNAL_FLASH_P2M;
  }
  else if (!strcmp("IP2BM",ArgStr))
  {
    deviceContext->ctrl_path = INT_FLASH_CTRL_PATH;
    deviceContext->flash_type = INTERNAL_FLASH_P2BM;
  }
  else if (!strcmp("XP1BM",ArgStr))
  {
    deviceContext->ctrl_path = EXT_FLASH_CTRL_PATH;
    deviceContext->flash_type = EXTERNAL_FLASH_P1;
  }
  else if (!strcmp("XP2BM",ArgStr))
  {
    deviceContext->ctrl_path = EXT_FLASH_CTRL_PATH;
    deviceContext->flash_type = EXTERNAL_FLASH_P2;
  }

  ArgStr = Argv[i+1];
  if (!strcmp("P",ArgStr))
  {
    deviceContext->fwup = 1;
  }
  else
  {
    deviceContext->fwup = 0;
  }
  //TODO : Replace with the new define command to hide the belowing flash information
  //TODO : Read platform/chip information to decide capabilities of supporting External/Internal Flash
  switch (deviceContext->flash_type)
  {
    case INTERNAL_FLASH_P1B:
      deviceContext->erase_blockCount = 6;//6k
      deviceContext->start_addr = ACTV_BBK_START_ADDR;
      break;
    case INTERNAL_FLASH_P2B:
      deviceContext->erase_blockCount = 8;//8k
      deviceContext->start_addr = BKUP_STARTUP_BBK_START_ADDR;
      break;
    case INTERNAL_FLASH_P1M:
      deviceContext->erase_blockCount = 24;//24k
      deviceContext->start_addr = ACTV_MBK_START_ADDR;
      break;
    case INTERNAL_FLASH_P2M:
      deviceContext->erase_blockCount = 24;//24k
      deviceContext->start_addr = BKUP_MBK_START_ADDR;
      break;
    case INTERNAL_FLASH_P2BM:
      deviceContext->erase_blockCount = 32;//32k
      deviceContext->start_addr = BKUP_STARTUP_BBK_START_ADDR;
      break;
    case EXTERNAL_FLASH_P1:
    case EXTERNAL_FLASH_P2:
      EC_E(" - Not support Erasing External SPINOR!!\n");
      break;
  }
}

/**
  Show the command usage
**/
void ShowUsage(void)
{
  EC_I("==============================================================================================\n");
  EC_I("=     ECFlash UEFI APP for Firmware Upgrade                                                   \n");
  EC_I("=     Copyright (c) %a  Technologies Incorporated.                                            \n", Tool_Vendor);
  EC_I("=                 All Rights Reserved.                                                        \n");
  EC_I("=                             --%a                                                            \n", __DATE__);
  EC_I("=  ECFlashApp.efi [-options] xxxx.bin                                                         \n");
  EC_I("=  [-options]:                                                                                \n");
  EC_I("=   -D      Enable Debug Logs                                                                 \n");
  EC_I("=   -V      Print EC Version                                                                  \n");
  EC_I("=   -F      Force fw upgrade                                                                  \n");
  EC_I("=   -U      Firmware upgrade                                                                  \n");
  EC_I("=   -PL     Platform                                                                          \n");
  EC_I("=   -ER     Erase Designated Flash Area                                                       \n");
  EC_I("=   -SI     Select Internal Flash Type [Default]                                              \n");
  EC_I("=   -SE1    Select External Flash Type - Partition 1                                          \n");
  EC_I("=   -SE2    Select External Flash Type - Partition 2                                          \n");
  EC_I("=   -SE12   Select External Flash Type - Partition 1 & 2                                      \n");
  EC_I("=   -OP     Mode Switching/ Mirror/ Run Checksum/ Firmware Sync                               \n");
  EC_I("=   -CR     Check Overall Corrpution Status                                                   \n");
  EC_I("=   -CKSM   Get Checksum result                                                               \n");
  EC_I("=   -DM     Disable EC Code Mirror                                                            \n");
  EC_I("=   -EM     Enable EC Code Mirror                                                             \n");
  EC_I("=   -W      Write value to EC register using ACPI I2C protocol                                \n");
  EC_I("=   -R      Read value from EC register using ACPI I2C protocol                               \n");
  EC_I("=   -PR     FW update using H/W pre-define protocol                                           \n");
  EC_I("=   -P-REG  Read/Write EC Registers using H/W pre-define protocol                             \n");
  EC_I("=   -P-FL   Enter/Exit Follow Mode(pre-define protocol)                                       \n");
  EC_I("=  Example: ECFlashApp.efi -V  xxxx.bin         [Check Fw version]                            \n");
  EC_I("=  Example: ECFlashApp.efi -SI -U xxxx.bin      [Firmware Update Int. flash(ACPI I2C)]        \n");
  EC_I("=  Example: ECFlashApp.efi -SI -F -U xxxx.bin   [Force Firmware Update Int. flash(ACPI I2C)]  \n");
  EC_I("=  Example: ECFlashApp.efi -PR xxxx.bin         [Firmware Update int. flash(Pre-define)]      \n");
  EC_I("=  Example: ECFlashApp.efi -R  0x03 3           [Read reg(via acpi_i2c): 0x03  size:3]        \n");
  EC_I("=  Example: ECFlashApp.efi -W  0x05 5           [Write reg(via acpi_i2c):0x05  data:5]        \n");
  EC_I("=  Example: ECFlashApp.efi -EM                  [Enable EC Code Mirror]                       \n");
  EC_I("=  Example: ECFlashApp.efi -OP RIP1             [Run Internal Flash P1 Checksum]              \n");
  EC_I("=  Example: ECFlashApp.efi -OP RXP2             [Run External Flash P2 Checksum]              \n");
  EC_I("=  Example: ECFlashApp.efi -ER IP1M E           [Erase Internal P1 Main Code]                 \n");
  EC_I("=  Example: ECFlashApp.efi -ER IP1M P xxxx.bin  [Erase & Program Internal P1M]                \n");
  EC_I("=  Example: ECFlashApp.efi -P-REG 0x2000 W 0x88 [Write reg(via pre-define):0x2000 = 0x88]     \n");
  EC_I("=  Example: ECFlashApp.efi -P-REG 0x2000 R      [Read reg(via pre-define):0x2000]             \n");
  EC_I("==============================================================================================\n");
}

/**
  EC Flash App main

  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS -     EC flashing is successfull
**/
EFI_STATUS
EFIAPI
ECFlashAppMain(
  EFI_HANDLE  ImageHandle,
  EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                  Status = EFI_SUCCESS;
  UINTN                       Argc;
  CHAR8                     **Argv;
  int                         i = 0;
  UINT16                      buffu16 = 0;

  Status = GetCmdLineArgs (
    ImageHandle,
    &Argc,
    &Argv);
  if (EFI_ERROR(Status) ||
    (Argc == 0))
  {
    EC_E("GetCmdLineArgs() failed with %r\n", Status);
    return Status;
  }

  if (Argc == 1)
  {
    ShowUsage();
    goto Exit;
  }

  Status = DeviceInit();
  if (EFI_ERROR(Status))
  {
    EC_E("DeviceInit failed with %r\n", Status);
    goto Exit;
  }

  // Default configure for internal e-flash
  deviceContext->start_addr = MAIN_BLK_START_ADDR;
  deviceContext->flash_type = INTERNAL_FLASH;
  deviceContext->ctrl_path  = INT_FLASH_CTRL_PATH;

  for (i=1;i < Argc;i++)
  {
    if (!strcmp("-D",Argv[i]) || !strcmp("-d",Argv[i]))
    {
      deviceContext->debug_mask=ENABLE_LOGS;  // Enable logs
    }

    if (!strcmp("-V",Argv[i]) || !strcmp("-v",Argv[i]))
    {
      deviceContext->query_version = 1;
    }

    if (!strcmp("-F",Argv[i]) || !strcmp("-f",Argv[i]))
    {
      deviceContext->force_fwup = 1;
    }

    if (!strcmp("-U",Argv[i]) || !strcmp("-u",Argv[i]))
    {
      deviceContext->fwup = 1;
    }

    // I2C Write Operation inside the statement [START]
    UINT8 *wtBuf=NULL;
    wtBuf = AllocateZeroPool(sizeof (UINT8) * 256);
    if (wtBuf == NULL)
    {
      EC_E("wtBuf Memory Allocation failed ");
      Status = EFI_OUT_OF_RESOURCES;
      goto Exit;
    }

    if (!strcmp("-OP",Argv[i]) || !strcmp("-op",Argv[i]))
    {
      i++;
      wtBuf[0] = OPCommandParser(i,Argv);
      i2c_block_write (
        EC_MODE_CMD_WO,
        &(wtBuf[0]),
        0,
        0);

      if ((wtBuf[0] == 0xF0) ||
        (wtBuf[0] == 0xF1) ||
        ((wtBuf[0]>= 0x15) && (wtBuf[0]<= 0x18)))
      {
        wtBuf[0] = 0;
        wtBuf[1] = 0;
        buffu16 = 0;
        do
        {
          i2c_block_read (
            SPI_SERVICE_CMD_RO,
            wtBuf,
            STATIC_DAT_LEN,
            0,
            0);
          EC_I("time taken : %d ms, wtBuf[0] = 0x%x \r",(buffu16*100), wtBuf[0]);
          gBS->Stall(100*1000);//100ms
          buffu16++;
        }while ((wtBuf[0] != 0x0B) &&
         (wtBuf[0] != 0x0C) &&
          (buffu16 < 40));
      }
    }

    if (!strcmp("-P-REG",Argv[i]))
    {// [-p-REG] [REGISTERS_ADDR] [Write/Read] [Data]
      i++;
      buffu16 = (UINT16) AsciiStrHexToUintn (*(Argv + i));
      wtBuf[0] = (UINT8) (buffu16 >> 8);
      wtBuf[1] = (UINT8) (buffu16);

      EC_I("REG 0x%x_%x ", wtBuf[0],wtBuf[1]);
      //[0x5B][0x10][0x20][0x00]// read register offset 0x2000
      i2c_block_write (
        I2EC_ADDRESS_WO,
        &(wtBuf[0]),
        0,
        0);
      
      i++;
      if (!strcmp("W",Argv[i]))
      {//Write Data to Register
        i++;
        wtBuf[0] = (UINT8) AsciiStrHexToUintn (*(Argv + i));
        EC_I("WriteData : 0x%x \n",wtBuf[0]);
        //[0x5B][0x11][XX]// XX : bytes value for the spefici REG
        i2c_block_write (
          I2EC_DATA_WR,
          &(wtBuf[0]),
          0,
          0);
      }
      else
      {//Read Data from Register
        i2c_block_read (
          I2EC_DATA_WR,
          &(wtBuf[0]),
          STATIC_DAT_LEN,
          0,
          0);
        EC_I("ReadData : 0x%x\n",wtBuf[0]);

      }
    }
    if (!strcmp("-P-FL",Argv[i]))
    {
      i2c_block_write (
        PREDEFINE_CHIP_SELECT_TOGGLE_WO,
        &(wtBuf[0]),
        0,
        0);
    }
    
    if (!strcmp("-DM",Argv[i]) || !strcmp("-dm",Argv[i]))
    {
      wtBuf[0] = DIS_MIRROR_CMD;
      Status = i2c_block_write (
        EC_MODE_CMD_WO,
        &(wtBuf[0]),
        0,
        0);
      if (EFI_ERROR(Status))
      {
        EC_E("Disable Mirror failed with %r\n", Status);
        goto Exit;
      }
    }

    if (!strcmp("-EM",Argv[i]) || !strcmp("-em",Argv[i]))
    {
      wtBuf[0] = FORCE_MIRROR_IMMEDIATLY;
      Status = i2c_block_write (
        EC_MODE_CMD_WO,
        &(wtBuf[0]),
        0,
        0);
      if (EFI_ERROR(Status))
      {
        EC_E("Enable Mirror failed with %r\n", Status);
        goto Exit;
      }
    }

    FreePool(wtBuf);

    // I2C Write Operation inside the statement [END]

    // I2C Read Operation inside the statement [START]
    UINT8 *rdBuf=NULL;
    rdBuf = AllocateZeroPool(sizeof (UINT8) * 256);
    if (rdBuf == NULL)
    {
      EC_E("rdBuf Memory Allocation failed ");
      Status = EFI_OUT_OF_RESOURCES;
      goto Exit;
    }

    if (!strcmp("-CKSM",Argv[i]) || !strcmp("-cksm",Argv[i]))
    {//0xA2 read
      Status = Wait_For_EC_Checksum_Result(100);
      if (EFI_ERROR(Status))
      {
        EC_E("Wait_For_EC_Checksum_Result() failed with %r\n", Status);
        goto Exit;
      }
    }
    FreePool(rdBuf);
    // I2C Read Operation inside the statement [END]

    if (!strcmp("-CR",Argv[i]) || !strcmp("-cr",Argv[i]))
    {
      Status = EC_Check_Corruption_Status();
      if (EFI_ERROR(Status))
      {
        EC_E("EC_Check_Corruption_Status() failed with%r\n", Status);
        goto Exit;
      }
    }
    if (!strcmp("-ER",Argv[i]) || !strcmp("-er",Argv[i]))
    {//[-ER][Flash Type][Prgram after Erase]
      i++;
      EraseDesignatedCommandParser(i,Argv);
    }

    if (!strcmp("-SI",Argv[i]) || !strcmp("-si",Argv[i]))
    {
      deviceContext->flash_type = INTERNAL_FLASH;
    }

    if (!strcmp("-SE1",Argv[i]) || !strcmp("-se1",Argv[i]))
    {
      deviceContext->flash_type = EXTERNAL_FLASH_P1;
      deviceContext->ctrl_path  = EXT_FLASH_CTRL_PATH;
    }

    if (!strcmp("-SE2",Argv[i]) || !strcmp("-se2",Argv[i]))
    {
      deviceContext->flash_type = EXTERNAL_FLASH_P2;
      deviceContext->ctrl_path  = EXT_FLASH_CTRL_PATH;
    }

    if (!strcmp("-PR",Argv[i]) || !strcmp("-pr",Argv[i]))
    {
      deviceContext->pre_define_update = 1;
    }

    if (!strcmp("-R",Argv[i]) || !strcmp("-r",Argv[i]))
    {
      if (((i+1) < Argc) &&
        ((i+2) <= Argc))
      {
        long reg = 0, size = 0;
        reg  = strtol(Argv[i+1], NULL, 16);

        if (reg <= 0)
        {
          EC_E("Invalid cmd , cmd=0x%x\n", reg);
          goto Exit;
        }

        size = atoi(Argv[i+2]);
        if ((size <= 0) ||
          (size > 255))
        {
          EC_E("Invalid size argument,size=%d\n", size);
          goto Exit;
        }

        EC_I("reg=0x%x, size=%d\n", reg, size);
        Status = Read_EC_Register((UINT16)reg, (UINT8)size);
        if (EFI_ERROR(Status))
        {
          EC_E("Read_EC_Register failed with %r\n", Status);
          goto Exit;
        }
      }
      else
      {
        EC_E("Insufficient argument for -R option\n\n");
        SleepMs(1000);
        ShowUsage();
      }
      goto Exit;
    }

    if (!strcmp("-W",Argv[i]) ||
      !strcmp("-w",Argv[i]))
    {
      if (((i+1) < Argc) &&
        ((i+2) <= Argc))
      {
        long reg, data;
        reg  = strtol(Argv[i+1], NULL, 16);
        data = atoi(Argv[i+2]);
        if ((reg <= 0) ||
          (data <= 0))
        {
          EC_E("Invalid cmd & size argument, cmd=0x%x, data=%d\n", reg, data);
          goto Exit;
        }

        EC_I("reg=0x%x, data=%d\n", reg, data);

        Status = Write_EC_Register((UINT16)reg, (UINT8)data);
        if (Status != EFI_SUCCESS)
        {
          EC_E("Write_EC_Register() failed with %r\n", Status);
          goto Exit;
        }
      }
      else
      {
        EC_E("Insufficient argument for -W option\n\n");
        SleepMs(1000);
        ShowUsage();
      }
      goto Exit;
    }
  }

  if ((NULL != Argv[i-1]) &&
    (NULL != strstr(Argv[i-1], ".bin")))
  {
    deviceContext->fw_img_name_length = ((AsciiStrLen (Argv[i-1]) + 1) * sizeof (CHAR16));

    if (deviceContext->fw_img_name_length> 255)
    {
      EC_E("Invalid size argument,size=%d\n", deviceContext->fw_img_name_length);
      Status = EFI_INVALID_PARAMETER;
      goto Exit;
    }

    AsciiStrToUnicodeStrS(
      Argv[i-1],
      deviceContext->fw_img_name,
      deviceContext->fw_img_name_length);

    deviceContext->valid_binfile_exist = 1;

    EC_E("Bin File Name: %s\n", deviceContext->fw_img_name);
  }

  if (deviceContext->valid_binfile_exist)
  {
    Status = ReadECFirmwareToBuffer(deviceContext->fw_img_name);
    if (EFI_ERROR(Status))
    {
      EC_E("ReadECFirmwareToBuffer() failed with %r\n", Status);
      goto Exit;
    }

    Status = Check_OnBinary_EC_Version();
    if (EFI_ERROR(Status))
    {
      EC_E("Check_OnBinary_EC_Version() failed with %r\n", Status);
      goto Exit;
    }
  }

  if (deviceContext->pre_define_update)
  {
    Status = EcPredefineUpdateMain();
    if (EFI_ERROR(Status))
    {
      EC_E("EcPredefineUpdateMain() failed with %r\n", Status);
    }
    else
    {
      EC_I("Updated EC Firmware using I2C H/W protocol successfully!\n");
    }
    goto Exit;
  }

  /* Check Fw flash status */
  EC_Check_FW_Status();
  if (deviceContext->erase_blockCount)
  {
    EC_I("Erasing flash - path : %xh, start_addr : %xh, block_count : %d \n",
      deviceContext->ctrl_path,
      deviceContext->start_addr,
      deviceContext->erase_blockCount);

    //Jump to BBK if we're about to erase internal MBK
    if (EC_Enable_Flashing())
    {
      EC_E("- EC_Enable_Flashing Failed!!\n");
    }

    if (!Erase_Designated_Flash(2000, 5))
    {
      EC_I("- Erasing Success!!\n");
    }

  if ((deviceContext->fw_status == BOOT_BLK) &&
    (deviceContext->fwup) &&
    (deviceContext->valid_binfile_exist))
    {
      deviceContext->erase_sector_size = ((deviceContext->ctrl_path == EXT_FLASH_CTRL_PATH) ?
        EXT_FLASH_ERASE_SECTOR_SIZE : INT_FLASH_ERASE_SECTOR_SIZE);
      Status = EC_Parse_FW_Image();
      if (EFI_ERROR(Status))
      {
        EC_E("EC_Parse_FW_Image() failed with %r\n", Status);
        goto Exit;
      }
      Status = EC_Write_SPI_Flash();
      if (EFI_ERROR(Status))
      {
        EC_E("EC_Write_SPI_Flash() failed with %r\n", Status);
        goto Exit;
      }
      deviceContext->fwup = 0;
    }
    deviceContext->erase_blockCount = 0;
    EC_I("- Flash Type ID : %d is Erased then Program Successfuly!!\n",deviceContext->flash_type);
    goto Exit;
  }

  EC_I(" - Slave Address is 0x%x \n", deviceContext->slave_config.slave_address);

  if ((deviceContext->fw_status == BOOT_BLK) &&
    (deviceContext->fwup) &&
    (deviceContext->valid_binfile_exist))
  {
    EC_I("Already in BOOT BLK Area. Programming FLASH.\n");
    if (EC_Reflash() == EFI_SUCCESS)
    {
      EC_I("EC Reflash Success!!\n");
    }
    else
    {
      EC_E("EC Reflash Failed!!\n");
      goto Exit;
    }
  }

  Status = Check_OnIC_EC_Version();
  if (EFI_ERROR(Status))
  {
    EC_E("Check_OnIC_EC_Version failed with %r\n", Status);
    goto Exit;
  }

  if ((deviceContext->valid_binfile_exist) &&
    (IsFwVersionDiff()))
  {
    EC_I("========FW Version Mismatch=======\n");
    EC_I("FW MainVersion [IC=%d,  BIN=%d] \n",
      deviceContext->on_ic_info.main_ver,
      deviceContext->on_bin_info.main_ver);
    EC_I("FW SubVersion  [IC=%d,  BIN=%d]\n",
      deviceContext->on_ic_info.sub_ver,
      deviceContext->on_bin_info.sub_ver);
    EC_I("FW TestVersion [IC=%d,  BIN=%d]\n",
      deviceContext->on_ic_info.test_ver,
      deviceContext->on_bin_info.test_ver);
    EC_I("===================================\n");
    EC_E("Needs EC FW Upgrade!!\n");

    deviceContext->need_fw_upgrade = 1;
  }

  if (((deviceContext->force_fwup) ||
    (deviceContext->need_fw_upgrade)) &&
    ((deviceContext->fwup) &&
    (deviceContext->valid_binfile_exist)))
  {
    EC_I("Programming FLASH.....\n");
    if (!EC_Reflash())
    {
      EC_D("EC Reflash Success!!\n");
    }
  }

Exit:

  I2C_DeInit();

  if (deviceContext)
  {
    if (deviceContext->fw_img_data != NULL)
    {
      FreePool(deviceContext->fw_img_data);
      deviceContext->fw_img_data = NULL;
    }
    FreePool(deviceContext);
    deviceContext = NULL;
  }
  return Status;
}
