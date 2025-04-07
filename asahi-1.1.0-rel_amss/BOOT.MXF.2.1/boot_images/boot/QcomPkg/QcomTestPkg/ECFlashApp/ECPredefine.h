/** @file
   Header file to erase/update/verify internal e-flash using H/W predefine protocol.

Copyright (c) 2022-2023 Qualcomm Technologies Inc. All rights reserved.
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
 04/26/23  chic                 Refine i2c_block_read/write to support multiple type payload transaction
 12/08/22  bkulkarn             Update Hamoa EC FW partition size/I2C core instance, code refactoring
 11/14/22  ananns               Added code documentation and function descriptions
 8/17/22   bkulkarn             Initial revision
=============================================================================*/

#ifndef _EC_PREDEFINE_H
#define _EC_PREDEFINE_H
#include <ECLog.h>

#define EFLASH_CMD_BYTE_PROGRAM         0x02
#define EFLASH_CMD_WRITE_DISABLE        0x04
#define EFLASH_CMD_READ_STATUS          0x05
#define EFLASH_CMD_WRITE_ENABLE         0x06
#define EFLASH_CMD_FAST_READ            0x0B
#define EFLASH_CMD_CHIP_ERASE           0x60
#define EFLASH_CMD_READ_ID              0x9F
#define EFLASH_CMD_AAI_WORD_PROGRAM     0xAD
#define EFLASH_CMD_SECTOR_ERASE         0xD7
#define EFLASH_CMD_CHIP_SELECT          0x17
#define EFLASH_CMD_BLOCK_WRITE          0x18

#define SPIROM_BUSY_BIT                 0x01
#define SPIROM_WRITE_ENABLE_BIT         0x02

#define EFLASH_ADDR_START               0x0
#define EFLASH_ADDR_END                 0x8000
#define EC_WRITE_MAX_BYTES_TO_EFLASH    256

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
 * @brief Perform EC H/W reset
 *
 * @param None
 *
 * @retval EFI_SUCCESS         EC predefine reset is successfully.
 * @retval EFI_NOT_READY       I2C transfer is failed
 * @retval EFI_DEVICE_ERROR    Nothing is written to device
 */
EFI_STATUS
EcPredefineReset(void);

/**
 * @brief Checks EC H/W Predefine status
 *
 * @param cycleMs                Timeout value to support retry mechanism
 * @param maxAttempt             No of retry attempt
 * @param checkBit               check for the predefine status bit
 * @param checkValue             Ethier it can be 0 or 1
 *
 * @retval EFI_SUCCESS           EC predefine status read is successfully.
 * @retval EFI_DEVICE_ERROR      I2C predefined block read is failed
 */
EFI_STATUS
EcPredefineStatus(
  UINT16 cycleMs,
  UINT8 maxAttempt,
  UINT8 checkBit,
  UINT8 checkValue);

/**
 * @brief Function to get the EC internal Flash ID
 *
 * @param None
 *
 * @retval EFI_SUCCESS           Reading EC predefine Flash ID is successfully.
 * @retval EFI_DEVICE_ERROR      I2C predefined block read is failed
 */
EFI_STATUS
EcPredefineGetFlashID(void);

/**
 * @brief EC H/W Predefine Chip erase
 *
 * @param None
 *
 * @retval EFI_SUCCESS           EC flash chip erase is successfully.
 * @retval EFI_DEVICE_ERROR      I2C predefined write is failed
 */
EFI_STATUS
EcPredefineChipErase(void);

/**
 * @brief EC H/W Predefine sector erase
 *
 * @param None
 *
 * @retval EFI_SUCCESS           EC flash sector erase is successfully.
 * @retval EFI_DEVICE_ERROR      I2C predefined write is failed
 */
EFI_STATUS
EcPredefineErase(void);

/**
 * @brief EC H/W Predefine program the flash
 *
 * @param None
 *
 * @retval EFI_SUCCESS           Programming the EC flash is successfully.
 * @retval EFI_DEVICE_ERROR      I2C predefined write is failed
 * @retval EFI_INVALID_PARAMETER Invalid EC FW image
 */
EFI_STATUS
EcPredefineProgram(void);

/**
 * @brief EC H/W Predefine prepare the flash
 *
 * @param None
 *
 * @retval EFI_SUCCESS           Programming the EC flash is successfully.
 * @retval EFI_DEVICE_ERROR      I2C init/ write byte/mismatch flash ID is failed
 */
EFI_STATUS
EcPredefinePrepare(void);

/**
 * @brief Entry function to handle H/W predefine based FW update:
 *  1. Prepare for pre-define update.
 *  2. Erase the e-flash.
 *  3. Program the e-flash.
 *  4. Verify the update.
 *  5. Perform EC reset.
 *
 * @retval EFI_STATUS   A EFI_STATUS value indicating result of the operation.
 */
EFI_STATUS
EcPredefineUpdateMain();

#endif
