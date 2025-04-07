/** @file EcRecovery.h

  Header for routines to erase/update/verify internal flash using H/W predefine protocol.

  Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------
  2022/07/29     bkulkarn    Initial version
=============================================================================*/

#ifndef _ECRECOVERY_H
#define _ECRECOVERY_H

#define I2EC_ADDRESS_WRITE                  0x10
#define I2EC_DATA_READ_OR_WRITE             0x11
#define EFLASH_CMD_BYTE_PROGRAM             0x02
#define EFLASH_CMD_WRITE_DISABLE            0x04
#define EFLASH_CMD_READ_STATUS              0x05
#define EFLASH_CMD_WRITE_ENABLE             0x06
#define EFLASH_CMD_FAST_READ                0x0B
#define EFLASH_CMD_CHIP_ERASE               0x60
#define EFLASH_CMD_READ_ID                  0x9F
#define EFLASH_CMD_AAI_WORD_PROGRAM         0xAD
#define EFLASH_CMD_SECTOR_ERASE             0xD7
#define EFLASH_CMD_CHIP_SELECT              0x17
#define EFLASH_CMD_BLOCK_WRITE              0x18

#define EFLASH_RESET_PATTERN1               0x5A
#define EFLASH_RESET_PATTERN2               0xA5

#define SPIROM_BUSY_BIT                     0x01
#define SPIROM_WRITE_ENABLE_BIT             0x02

#define EC_WRITE_MAX_BYTES_TO_EFLASH        256
#define EC_READ_MAX_BYTES_FROM_EFLASH       256

// ITE8987 Chip registers
#define HOST_FLASH_CTRL_3_REG_ADDR          0x1063
#define SLAVE_FIFO_CTRL_REG_ADDR            0x1059
#define SLAVE_A_FIFO_CTRL_REG_ADDR          0x1C5E
#define SHARED_MEMORY_CTRL_STS_REG_ADDR     0x1020
#define HOST_CTRL_2_REG_ADDR                0x1036
#define GEN_CTRL_22_REG_ADDR                0x16E7
#define RESET_STS_REG_ADDR                  0x2006
#define EC_CHIPID1_REG_ADDR                 0x2000
#define EC_CHIPID2_REG_ADDR                 0x2001

/**
 * Entry function to handle H/W predefine based FW update:
 *  - Erase the e-flash.
 *  - Program the e-flash.
 *  - Verify the update.
 *  - Perform EC reset.
 *
 * The caller of this function should either perform the predefine H/W init
 * or ensure its not required.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcReFlashUsingRecovery();

/**
 * Entry function to perform the required initialization of H/W,
 * to enable recovery/pre-define protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryInit();

/**
 * Entry function to read the EC Chip ID registers using recovery protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryGetChipID();
/**
 * Entry function to trigger reset operation using recovery protocol
 *
 * @param None
 *
 * @retval status       A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryReset();

/**
 * Entry function to read the command completion status using recovery protocol.
 *
 * @param cycleMs       Value indicating delay in ms per iteration.
 * @param maxAttempt    Value indicating max number of retries to be done.
 * @param checkBit      Mask to be used to evaluate the read status.
 * @param checkValue    Value indicating expectation of the masked evaluation
 *                        0: To evaluate if masked bit to be cleared in the read status.
 *                        1: To evaluate if masked bit to be set in the read status.
 *
 * @retval status       A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryCmdStatus(
  UINT16 cycleMs,
  UINT8 maxAttempt,
  UINT8 checkBit,
  UINT8 checkValue);

/**
 * Entry function to read the EC flash ID registers using recovery protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryGetFlashID();

/**
 * Entry function to read the EC firmware using recovery protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryVerify();

/**
 * Entry function to erase the EC firmware on hardware using recovery protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryErase();

/**
 * Entry function to program/write the EC firmware to hardware.
 * to enable recovery/pre-define protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryWrite();

#endif
