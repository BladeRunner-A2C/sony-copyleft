/** @file
  Header file for I2C block read and write functionality

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
 10/17/22   sumesahu  Initial revision
=============================================================================*/


#include "KeyboardLog.h"
#include "i2c_api.h"
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>

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
  );


/**
 * Return EFI_STATUS value for i2c_status value
 *
 * @param I2cStatus     i2c_status value
 * @retval EFI_SUCCESS             I2C_SUCCESS
 * @retval EFI_DEVICE_ERROR        any other i2c failures
 *
**/
EFI_STATUS
I2cStatusToEfiStatus(
  i2c_status I2cStatus
);

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
  );

