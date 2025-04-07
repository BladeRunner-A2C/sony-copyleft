/** @file EcFwUpdateLib.h

  Header for externally-available functions of the EcFwUpdateLib

  Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
when           who         what, where, why
--------       ---         --------------------------------------------------
2022/09/22     bkulkarn    Support for recovery protocol
2022/07/29     sumesahu    Initial version

=============================================================================*/

#ifndef _ECFWUPDATELIB_H
#define _ECFWUPDATELIB_H

#include <Uefi.h>
#include "i2c_api.h"
#include <Library/ECFwUpdateLib/EcFmpLog.h>
#include <Library/ECFwUpdateLib/EcUtils.h>
#include <Library/ECFwUpdateLib/EcUpgrade.h>
#include <Library/ECFwUpdateLib/EcFwFlagsAndStates.h>
#include <Library/ECFwUpdateLib/EcUpdateStateMachine.h>
#include <Library/ECFwUpdateLib/EcRecovery.h>

/* ITE8987 EC slave properties*/
#define I2C_EC_SLAVE_ADDRESS                    0x76
#define I2C_PREDEFINE_EC_SLAVE_ADDRESS          0x5B
#define I2C_HID_MODE_EC_SLAVE_ADDRESS           0x3A
#define I2C_HID_DESCRIPTOR                      0x0001
#define I2C_DEFAULT_BUS_FREQ                    400
#define I2C_MAX_CLK_STRETCH_FREQ                500
#define BLOCK_READ_BYTE_MAX                     512
#define BLOCK_WRITE_BYTE_MAX                    512

/**
 * Return EFI_STATUS value for i2c_status value
 *
 * @param I2cStatus             i2c_status value
 * @retval EFI_SUCCESS          I2C_SUCCESS
 * @retval EFI_DEVICE_ERROR     Any other i2c failures
 *
**/
EFI_STATUS EcI2cStatusToEfiStatus(
  i2c_status I2cStatus
  );

/**
 * The entry Point for Initialize I2C CORE PROTOCOL
 *
 * @param Void
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cInit(void);

/**
 * The entry Point for De-Initialize I2C CORE PROTOCOL
 *
 * @param Void
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cDeInit(void);

/**
 * The entry Point for I2C CMD WRITE ONLY PROTOCOL:
 * [ADDR][CMD]
 *
 * @param cmd                I2c command write transaction
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cCmdWriteOnly(
  UINT8 cmd
  );

/**
 * The entry Point for I2C DATA READ ONLY PROTOCOL:
 * [ADDR] [DATA_LOW][DATA_HIGH]
 *
 * @param buff               Pointer to buffer for holding the read data from slave
 * @param buff_size          Size of the read buffer from slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cDataReadOnly(
  void* buff,
  UINT8 buff_size
  );

/**
 * The entry Point for I2C WORD READ PROTOCOL:
 * [ADDR][CMD] [ADDR] [DATA_LOW][DATA_HIGH]
 *
 * @param cmd               I2C command for reading from slave
 * @param buff              Pointer to buffer for holding the read data from slave
 *
 * @retval EFI_SUCCESS      The entry point is executed successfully.
 * @retval other            Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cWordRead( UINT8 cmd, void* buff);

/**
 * The entry Point for I2C BYTE READ PROTOCOL:
 * [ADDR][CMD] [ADDR] [DATA]
 *
 * @param cmd               I2C command read from slave
 * @param buff              Pointer to buffer for holding the read data from slave
 *
 * @retval EFI_SUCCESS      The entry point is executed successfully.
 * @retval other            Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cByteRead(
  UINT8 cmd,
  void* buff
  );

/**
 * The entry Point for I2C BLOCK READ PROTOCOL:
 * [ADDR][CMD] [ADDR] [BYTECNT][DATA_0][DATA_1] ... [DATA_N-1]
 *
 * @param cmd                I2C command read from slave
 * @param buff               Pointer to buffer for holding the read data from slave
 * @param buff_size          Size of the read buffer from slave
 * @param cycle_ms           Timeout for retry
 * @param max_retry          Maximum retry count
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cBlockRead(
  UINT8 cmd,
  void* buff,
  UINT8 buff_size,
  UINT16 cycle_ms,
  UINT8 max_retry
  );

/**
 * The entry Point for I2C WORD WRITE PROTOCOL:
 * [ADDR][CMD] [DATA_LOW] [DATA_HIGH]
 *
 * @param cmd               I2C command for writing into slave
 * @param buff              Pointer to buffer for holding the write data into slave
 *
 * @retval EFI_SUCCESS      The entry point is executed successfully.
 * @retval other            Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cWordWrite(
  UINT8 cmd,
  void* buff
  );

/**
 * The entry Point for I2C BYTE WRITE PROTOCOL:
 * [ADDR][CMD] [DATA]
 *
 * @param cmd               I2C command for writing into slave
 * @param buff              Pointer Buffer for holding the write data into slave
 *
 * @retval EFI_SUCCESS      The entry point is executed successfully.
 * @retval other            Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cByteWrite(
  UINT8 cmd,
  void* buff
  );

/**
 * The entry Point for I2C BLOCK WRITE PROTOCOL:
 * [ADDR][CMD] [BYTECNT][DATA_0][DATA_1] ... [DATA_N-1]
 *
 * @param cmd                I2C command for writing into slave
 * @param buff               Pointer Buffer for holding the write data into slave
 * @param buff_size          Size of the write buffer to slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cBlockWrite(
  UINT8 cmd,
  void* buff,
  UINT8 buff_size
  );

/**
 * The entry Point for I2C BLOCK WRITE PROTOCOL FOR RAM:
 * [ADDR][CMD] [DATA_0][DATA_1] ... [DATA_N-1]
 *
 * @param cmd                I2C command for writing into slave
 * @param buff               Pointer to buffer for holding the write data into slave
 * @param buff_size          Size of the write buffer to slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cBlockWriteToRam(
  UINT8 cmd,
  void* buff,
  UINT16 buff_size
  );

/**
 * The entry Point for I2EC WRITE BYTE PROTOCOL:
 * [ADDR][CMD][I2EC_ADDRESS_WRITE][ADDR_MSB][ADDR_LSB][I2EC_DATA_WRITE][DATA]
 *
 * @param cmd                I2C command for writing into slave
 * @param address            Address for writing the data payload
 * @param data               Data to be written at a given address.
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcI2EcWriteByte(
    unsigned int address,
    UINT8 data
);

/**
 * The entry Point for I2EC READ BYTE PROTOCOL:
 * [ADDR][CMD][I2EC_ADDRESS_WRITE][ADDR_MSB][ADDR_LSB][I2EC_DATA_READ][DATA]
 *
 * @param cmd                I2C command for writing into slave
 * @param address            Address for writing the data payload
 * @param buffer             Pointer to buffer containing data to be read from given address.
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcI2EcReadByte(
    unsigned int address,
    void* buff
);

/**
 * The entry Point for I2EC PREDEFINE SEND PROTOCOL:
 * [ADDR] [CS] [ADDR] [BLOCK_WRITE_CMD] [A] [SUB_CMD]
 *
 * @param cmd                I2C command for writing into slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcI2cPredefineSend(
    UINT8 cmd
);

/**
 * The entry Point for I2EC PREDEFINE BLOCK READ PROTOCOL:
 * [ADDR] [CS] [ADDR] [BLOCK_WRITE_CMD] [CMD] [ADDR] [DATA_0]..[DATA_N-1]
 *
 * @param cmd                I2C command for reading data from the slave
 * @param buff               Pointer to buffer for holding the read data from the slave
 * @param buff_size          Size of the read buffer from slave
 * @param cycle_ms           Timeout for retry
 * @param max_retry          Maximum retry count
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcI2cPredefineBlockRead(
    UINT8 cmd,
    void* buff,
    UINT8 buff_size,
    UINT16 cycle_ms,
    UINT8 max_retry
  );

/**
 * The entry Point for I2EC PREDEFINE BLOCK WRITE PROTOCOL:
 * [ADDR] [CS] [ADDR] [BLOCK_WRITE_CMD] [CMD] [ADDR] [DATA_0]..[DATA_N-1]
 *
 * @param cmd                I2C command for writing into slave
 * @param buff               Pointer to buffer for holding the write data into slave
 * @param buff_size          Size of the write buffer to slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcI2cPredefineBlockWrite(
  UINT8 cmd,
  void* buff,
  UINT8 buff_size
  );

/**
 * The entry Point for I2EC PREDEFINE FAST READ PROTOCOL:
 * [ADDR] [CS] [ADDR] [BLOCK_WRITE_CMD] [CMD] [ADDR] [DATA_0]..[DATA_N-1]
 *
 * @param cmd                I2C command for reading data from the slave
 * @param writeBuf           Pointer Buffer for holding the write data into slave
 * @param writeBufSize       Size of the write buffer to slave
 * @param readBuf            Pointer to buffer for holding the read data from the slave
 * @param readBufSize        Size of the read buffer from slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcI2cPredefineFastRead(
  UINT8 cmd,
  void* writeBuf,
  UINT8 writeBufSize,
  void* readBuf,
  UINT16 readBufSize
  );

/** Function to vote for resources required for powering on the EC.
 *
 * @param none
 *
 * @retval status    A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
EcPowerOn(void);

#endif //End of _ECFWUPDATELIB_H
