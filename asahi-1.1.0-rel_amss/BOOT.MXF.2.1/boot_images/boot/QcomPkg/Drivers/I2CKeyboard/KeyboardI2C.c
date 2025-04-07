/** @file
  Keyboard I2C is used to support the I2C block read and write functionality

Copyright (c) 2022 Qualcomm Technologies Inc. All rights reserved.
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
 10/17/22   ananns    Added code documentation and function descriptions
 10/13/22   sumesahu  Initial revision
=============================================================================*/


#include "KeyboardI2C.h"

/**
 * I2C BLOCK WRITE PROTOCOL [ADDR][CMD] [BYTECNT][DATA_0][DATA_1] ... [DATA_N-1]
 *
 * @param i2c_handle         Pointer to i2c handle
 * @param cfg                Pointer to i2c config
 * @param buff               Pointer Buffer for holding the write data to slave
 * @param buff_size          Size of the write buffer to slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval EFI_OUT_OF_RESOURCES  Insufficient buffer size or Unable to allocate resources for necessary buff_size.
 *
 **/
EFI_STATUS 
i2ckb_block_write(
  IN VOID * i2c_handle, 
  IN i2c_slave_config cfg, 
  void* buff,
  UINT8 buff_size
  )
{
    KB_TRACE();
    i2c_status i2c_sts = I2C_SUCCESS;
    EFI_STATUS status = EFI_SUCCESS;

    UINT8 *wdBuf = NULL;;
    UINT32 bytes_written = 0;
    i2c_descriptor buffer_desc[1] = {{0}};

    if(buff_size <= 0)
    {
        KB_E("- Error in buffer Size criteria:[%d]!!\n", buff_size);
        status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    wdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * buff_size);
    if (wdBuf == NULL) {
        KB_E("- Failed to Allocate from Pool!!\n");
        status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    /* Fill the descriptor */
    CopyMem(&(wdBuf[0]), buff, buff_size);
    buffer_desc[0].buffer = wdBuf;
    buffer_desc[0].length = buff_size;
    buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;


    KB_D( "Dumping write block buffer[%d]:", buff_size);
    for (int i = 0 ; i < buff_size; i++)
    {
        KB_P( " 0x%x, ",wdBuf[i]);
    }
    KB_P( " \n ");

    i2c_sts = i2c_transfer(
                    i2c_handle, 
                    &cfg, 
                    buffer_desc, 
                    1, 
                    NULL, 
                    NULL, 
                    0, 
                    &bytes_written
                    );

    if (I2C_SUCCESS != i2c_sts)
    {
        KB_E("- Failed to transfer I2C. Error = %d\n", i2c_sts);
        status = I2cStatusToEfiStatus(i2c_sts);
        goto FreeMemory;
    }

    KB_D( "Total bytes written is %d\n", bytes_written);

FreeMemory:
  if (wdBuf != NULL) {
    FreePool(wdBuf);
    wdBuf = NULL;
  }
	  

Exit:
    return status;
}

/**
 * The entry Point for I2C BLOCK READ PROTOCOL [ADDR][CMD] [ADDR] [BYTECNT][DATA_0][DATA_1] ... [DATA_N-1]
 *
 * @param i2c_handle         Pointer to i2c handle
 * @param cfg                Pointer to i2c config
 * @param cmd                I2C Command read from slave
 * @param buff               Pointer Buffer for holding the read data from slave
 * @param buff_size          Size of the read buffer from slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval EFI_OUT_OF_RESOURCES  Insufficient buffer size.
 * @retval EFI_DEVICE_ERROR  i2c_handle is NULL.
 *
 **/
EFI_STATUS
i2ckb_block_read(
  IN VOID * i2c_handle, 
  IN i2c_slave_config cfg, 
  void *cmd, 
  void* buff, 
  UINT8 buff_size
  )
{
  EFI_STATUS status = EFI_SUCCESS;
  UINT8 wdBuf[2] = {0};
  UINT32 bytes_read = 0;
  i2c_descriptor buffer_desc[2] = {{0}};

  KB_TRACE();

  if (buff_size <= 0)
  {
    KB_E("- Error in buffer Size criteria:[%d]!!\n", buff_size);
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  if (i2c_handle == NULL)
  {
    KB_E("- i2c_handle NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  // set up transfer list
  CopyMem(&(wdBuf[0]), cmd, 2);
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = 2;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  buffer_desc[1].buffer = buff;
  buffer_desc[1].length = buff_size;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP;

  KB_D("- Sending read block request with CMD 0x%x \r\n", cmd);
  status = i2c_transfer(
                  i2c_handle, 
                  &(cfg), 
                  buffer_desc, 
                  2, 
                  NULL, 
                  NULL, 
                  3000, 
                  &bytes_read
                  );

  if (status != EFI_SUCCESS)
  {
    status = I2cStatusToEfiStatus(status);
    goto Exit;
  }

  KB_D( "Total bytes read: %d\n", bytes_read);

Exit:
  return status;
}


/**
 * Return EFI_STATUS value for i2c_status value
 *
 * @param I2cStatus     i2c_status value
 * @retval EFI_SUCCESS             I2C_SUCCESS
 * @retval EFI_DEVICE_ERROR        any other i2c failures
 *
**/
EFI_STATUS I2cStatusToEfiStatus(i2c_status I2cStatus)
{
  EFI_STATUS status = EFI_SUCCESS;
  KB_TRACE();

  // Convert from i2c_status to EFI_STATUS
  switch (I2cStatus) {
  case I2C_SUCCESS:
  case I2C_TRANSFER_COMPLETED:
    status = EFI_SUCCESS;
    break;

  case I2C_ERROR_INVALID_PARAMETER:
    status = EFI_INVALID_PARAMETER;
    goto ErrorCase;

  case I2C_ERROR_BUS_NOT_IDLE:
    KB_E(" I2C_ERROR_BUS_NOT_IDLE\n");
    goto ErrorCase;
  case I2C_ERROR_MEM_ALLOC_FAIL:
    KB_E(" I2C_ERROR_MEM_ALLOC_FAIL\n");\
    goto ErrorCase;

  case I2C_ERROR_TRANSFER_TIMEOUT:
    KB_E(" I2C_ERROR_TRANSFER_TIMEOUT\n");
    goto ErrorCase;

  case I2C_ERROR_HANDLE_ALLOCATION:
    KB_E(" I2C_ERROR_HANDLE_ALLOCATION\n");
    goto ErrorCase;

  case I2C_ERROR_ARBITRATION_LOST:
    KB_E(" I2C_ERROR_ARBITRATION_LOST\n");
    goto ErrorCase;

  case I2C_ERROR_START_STOP_UNEXPECTED:
    KB_E(" I2C_ERROR_START_STOP_UNEXPECTED\n");
    goto ErrorCase;

  case I2C_ERROR_DATA_NACK:
    KB_E(" I2C_ERROR_DATA_NACK\n");
    goto ErrorCase;

  case I2C_ERROR_ADDR_NACK:
    KB_E(" I2C_ERROR_ADDR_NACK\n");

  default:
    KB_E(" I2C_ERROR device is not functional\n");
    status = EFI_DEVICE_ERROR;
    break;

  ErrorCase:
    status = EFI_DEVICE_ERROR;
  }

  return status;
}