/** @file
  EC_Upgrade is used to flash/Erase/ the EC firmware to external Flash

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
 04/26/23   chic                Refine i2c_block_read/write to support multiple type payload transaction
 12/08/22   bkulkarn            Update Hamoa EC FW partition size/I2C core instance, code refactoring
 11/14/22   ananns              Added code documentation and function descriptions 
 10/17/21   sumesahu            Initial revision
=============================================================================*/

#ifndef _EC_UPGRADE_H
#define _EC_UPGRADE_H

/* Flash Commands */
#define EC_FLASH_BUF_WRITE_CMD                  0xA0
#define EC_WRITE_DATABUF_TO_SPI_ROM_CMD         0xAA
#define EC_SPI_READ_BUFFER_CMD                  0xA7
#define EC_FLASH_READ_BUF_CMD                   0xA1


/* Status */
#define EC_FW_IN_BOOT_BLK_IDLE                  0x0B
#define EC_FW_IN_MAIN_BLK_IDLE                  0x0C

#define EC_PASS_CHECKSUM                        0xAC
#define EC_FAIL_CHECKSUM                        0xFA

/* Values */
#define _SIZE_1KB                               1024
#define _SIZE_4KB                               (4*_SIZE_1KB)

/* TODO: Need to move to common ECFWUpdateLib with chip/MCU specific handling*/
#define PLATFORM_KODIAK                         0

#if PLATFORM_KODIAK
#define NO_OF_MAIN_BLK                          120
#define FW_SIZE                                 (128 * 1024)
#define EC_VERSION_OFFSET                       (0x7F80)
#else
#define NO_OF_MAIN_BLK                          24
#define FW_SIZE                                 (32 * 1024)
#define EC_VERSION_OFFSET                       (0x7780)
#endif

/* TODO: Read the layout from ec between different platforms instead of hardcoded like below*/
/* Hamoa */
#define STARTUP_BBK_START_ADDR                  (0x00)
#define ACTV_STARTUP_BLK_BUFFER_SIZE            (2*_SIZE_1KB)
#define ACTV_BBK_START_ADDR                     (STARTUP_BBK_START_ADDR + ACTV_STARTUP_BLK_BUFFER_SIZE)
#define ACTV_BOOT_BLK_BUFFER_SIZE               ((8*_SIZE_1KB) - ACTV_STARTUP_BLK_BUFFER_SIZE)
#define ACTV_BBK_END_ADDR                       ((ACTV_BBK_START_ADDR) + (ACTV_BOOT_BLK_BUFFER_SIZE))
#define ACTV_MBK_START_ADDR                     (ACTV_BBK_END_ADDR)
#define ACTV_MAIN_BLK_BUFFER_SIZE               (24*_SIZE_1KB)
#define ACTV_BLK_RESRV_AREA                     (31*_SIZE_1KB)
#define PART_GUARD_PADDING_SIZE                 (_SIZE_1KB)
#define ACTV_AREA_SIZE                          ((STARTUP_BBK_START_ADDR) + (ACTV_STARTUP_BLK_BUFFER_SIZE) + (ACTV_BOOT_BLK_BUFFER_SIZE) + (ACTV_MAIN_BLK_BUFFER_SIZE) + (ACTV_BLK_RESRV_AREA))
#define BKUP_STARTUP_BLK_BUFFER_SIZE            (ACTV_STARTUP_BLK_BUFFER_SIZE)
#define BKUP_BOOT_BLK_BUFFER_SIZE               (ACTV_BOOT_BLK_BUFFER_SIZE)
#define BKUP_MAIN_BLK_BUFFER_SIZE               (ACTV_MAIN_BLK_BUFFER_SIZE)
#define BKUP_STARTUP_BBK_START_ADDR             ((ACTV_AREA_SIZE) + (PART_GUARD_PADDING_SIZE))
#define BKUP_BBK_START_ADDR                     ((BKUP_STARTUP_BBK_START_ADDR) + (BKUP_STARTUP_BLK_BUFFER_SIZE))
#define BKUP_MBK_START_ADDR                     ((BKUP_BBK_START_ADDR) + (BKUP_BOOT_BLK_BUFFER_SIZE))

/* Kodiak */
#define BOOT_BLK_BUFFER_SIZE                    (8*_SIZE_1KB)
#define MAIN_BLK_BUFFER_SIZE                    (NO_OF_MAIN_BLK * _SIZE_1KB) 
#define DB_PADDING_SIZE                         (4*_SIZE_1KB)

#define BOOT_BLK_START_ADDR                     0
#define BOOT_BLK_END_ADDR                       (BOOT_BLK_START_ADDR + BOOT_BLK_BUFFER_SIZE)
#define MAIN_BLK_START_ADDR                     BOOT_BLK_END_ADDR
#define MAIN_BLK_END_ADDR                       (MAIN_BLK_START_ADDR + MAIN_BLK_BUFFER_SIZE)
#define DB_BLK_START_ADDR                       MAIN_BLK_END_ADDR
#define DB_BLK_END_ADDR                         (DB_BLK_START_ADDR + DB_PADDING_SIZE)

#define BOOT_BLK2_START_ADDR                    DB_BLK_END_ADDR
#define BOOT_BLK2_END_ADDR                      (BOOT_BLK2_START_ADDR + BOOT_BLK_BUFFER_SIZE)
#define MAIN_BLK2_START_ADDR                    BOOT_BLK2_END_ADDR
#define MAIN_BLK2_END_ADDR                      (MAIN_BLK2_START_ADDR + MAIN_BLK_BUFFER_SIZE)
#define DB_BLK2_START_ADDR                      MAIN_BLK2_END_ADDR
#define DB_BLK2_END_ADDR                        (DB_BLK2_START_ADDR + DB_PADDING_SIZE)

#define EC_MAX_WRITE_SECTOR_TO_RAM              LIMIT_256B // It is flexible we can select from WRITE_BUF_LIMIT enum
#define EC_MAX_WRITE_SECTOR_TO_FLASH            EC_MAX_WRITE_SECTOR_TO_RAM

#define INT_FLASH_ERASE_SECTOR_SIZE             (1 * 1024)  /** 1K Sector Size for Internal eFlash **/
#define EXT_FLASH_ERASE_SECTOR_SIZE             (4 * 1024)  /** 4K Sector Size for External Flash **/

#define EC_ERASE_ONESHOT_TIME_DELAY             (3 * NO_OF_MAIN_BLK * 1024) //3ms for each SPI erase
#define EC_CHECKSUM_CALC_TIME_DELAY             (1000) //Checksum calculation delay

enum SELECT_FLASH_TYPE
{
  INTERNAL_FLASH = 0,
  INTERNAL_FLASH_P1B,     // Internal Partition: P1 BBK
  INTERNAL_FLASH_P1M,     // Internal Partition: P1 MBK
  INTERNAL_FLASH_P1O,     // Internal Partition: P1 OEM/ODM
  INTERNAL_FLASH_P1P,     // Internal Partition: P1 Partition Guard
  INTERNAL_FLASH_P2B,     // Internal Partition: P2 BBK
  INTERNAL_FLASH_P2M,     // Internal Partition: P2 MBK
  INTERNAL_FLASH_P2BM,    // Internal Partition: P2 BBK + MBK
  INTERNAL_FLASH_P2O,     // Internal Partition: P2 OEM/ODM
  INTERNAL_FLASH_P2NV,    // Internal Partition: P2 EC NV Block
  EXTERNAL_FLASH_P1,      // External Partition: P1
  EXTERNAL_FLASH_P2,      // External Partition: P2
};

enum FW_BLOCK
{
  MAIN_BLK    =   1,
  BOOT_BLK    =   2,
  UNKNOWN_BLK =   0xAA
};

enum WRITE_BUF_LIMIT
{
  LIMIT_32B  = 32,
  LIMIT_64B  = 64,
  LIMIT_128B = 128,
  LIMIT_256B = 256,
  LIMIT_512B = 512,
  MAX_LIMIT  = LIMIT_512B
};

enum FW_CTRL_PATH
{
  INT_FLASH_CTRL_PATH = 0x4F,
  EXT_FLASH_CTRL_PATH = 0x0F,
  UNKNOWN_CTRL_PATH   = 0xFF
};

enum CHECKSUM_RESULT
{
  PASS_CHECKSUM       = 0xAC,
  FAIL_CHECKSUM       = 0xFA,
  UNKNOWN_CHECKSUM    = 0xFF
};

/**
 * @brief Function to send command to process EC Data Bufer to internal eFlash SPI ROM
 *
 * @param buff                   Pointer to buff
 * @param size                   size of the buffer
 *
 * @retval EFI_SUCCESS           EC flash to SPI ROM is successfull 
 * @retval EFI_DEVICE_ERROR      write to EC fails
 * @retval EFI_OUT_OF_RESOURCES  size or buff is out of range 
 */
static 
EFI_STATUS 
EC_Flash_To_SPIROM(
  void* buff, 
  UINT16 size
  );

/**
 * @brief Function to parse the EC FW image
 *
 * @retval EFI_SUCCESS            Parsing of FW image is successfull 
 * @retval EFI_OUT_OF_RESOURCES   ec device or FW image is NULL
 */
EFI_STATUS 
EC_Parse_FW_Image(
  void
  );

/**
 * Function select the External partition P1 or P2
 *
 * @retval EFI_SUCCESS        Selection of Flash is successfull 
 * @retval EFI_DEVICE_ERROR     Block write to EC fails
 * @retval EFI_OUT_OF_RESOURCES  deviceContext is NULL
 */
static 
EFI_STATUS 
EC_Select_SPI_Flash(
  void
  );

/**
 * @brief Function to get the EC Checksum Result
 * 
 * @param timeout_ms             timeout value is used for retry mechanism 
 * 
 * @retval EFI_SUCCESS           checksum is matched successfull 
 * @retval EFI_DEVICE_ERROR      checksum is mismatched 
 */
EFI_STATUS
Wait_For_EC_Checksum_Result(
  unsigned int timeout_ms
  );

/**
 * @brief Function to wait for EC SPI Service
 *   [0xAC]->Read->[XX]
 *   [XX]: AA - EC is in idle.
 *   Others: BUSY
 *
 * @param cycle_ms             Timeout value is used for retry mechanism 
 * @param max_retry            No of retry if incase of failure
 *
 * @retval EFI_SUCCESS        EC BBK/MBK SPI service is idle 
 * @retval EFI_DEVICE_ERROR   EC SPI service is busy and Timed out
 */
static 
EFI_STATUS
Wait_For_EC_SPI_Service(
  UINT16 cycle_ms, 
  UINT8 max_retry
  );

/**
 * @brief Function to check for EC control Path for internal / external flash
 *
 * @retval EFI_SUCCESS        Successfully read the Internal/External flash control path 
 * @retval EFI_DEVICE_ERROR   I2C byte read is failed 
 */
static 
EFI_STATUS 
EC_Check_Control_Path(
  void
  );

/**
 * @brief Function to erase the internal / external flash
 *
 * @retval EFI_SUCCESS       Erase the Internal/External flash is successfull 
 * @retval EFI_DEVICE_ERROR  Wait For EC SPI Service failed 
 */
static 
EFI_STATUS 
EC_Erase_SPI_Flash(
  void
  );

/**
 * @brief Function to write into EC's internal / external flash
 *
 * @retval EFI_SUCCESS        Write to the Internal/External flash is successfull 
 * @retval EFI_OUT_OF_RESOURCES  Wait For EC SPI Service failed  
 * @retval EFI_DEVICE_ERROR  I2C block write is failed
*/
EFI_STATUS 
EC_Write_SPI_Flash(
  void
  );

/**
 * @brief Function to calculate FW checksum [MODE_CMD][BYTECNT1][RUN_CHECKSUM_CMD]
 *
 * @retval EFI_SUCCESS        Successfully queried checksum command for the Internal/External flash
 * @retval EFI_DEVICE_ERROR   I2C block write is failed
 */
static 
EFI_STATUS
EC_Run_Checksum(
  void
  );

/**
 * @brief Function to program the EC firmware
 * 
 * @retval EFI_SUCCESS        EC FW is programmed Successfully
 * @retval EFI_DEVICE_ERROR   EC Select/Erase/Write to SPI Flash is Failed
 */
static 
EFI_STATUS 
EC_Program_Firmware(
  void
  );

/**
 * @brief Function to finalize the reflashing of the EC firmware to internal flash
 *
 * @retval EFI_SUCCESS        EC FW is programmed from external flash to internal flash Successfully
 * @retval EFI_DEVICE_ERROR   EC Run Checksum cmd execution failed
 */
static 
EFI_STATUS 
EC_Finalize_Reflash(
  void
  );

/**
 * @brief Function to reflash the entire MAIN_FW Block image.
 *
 * @retval EFI_SUCCESS             EC refalshing the main firmware block image is successfully 
 * @retval EFI_OUT_OF_RESOURCES    EC Parse/Flashing to Flash is failed
 * @retval EFI_DEVICE_ERROR        Program/Finilize FW Image Failed
 */
EFI_STATUS EC_Reflash(
  void
  );

/**
 * @brief Function to check if EC FW running mode either Boot/Main block/Unknown block mode
 *
 * @retval None
 */
void EC_Check_FW_Status(
  void
  );

/**
 * @brief Function to enabling the flashing process
 *
 * @retval EFI_SUCCESS             EC enable the refalshing process successfully 
 * @retval EFI_OUT_OF_RESOURCES    Error in EC FW status ( Unknown block mode or status is zero) 
 * @retval EFI_DEVICE_ERROR        failed to enter BBK mode
 */
EFI_STATUS
EC_Enable_Flashing(
  void
  );

/**
 * @brief EC Boot Block Entry [EC_MODE_CMD][BYTECNT1[EC_ENTER_BBK_CMD]
 *
 * @retval EFI_SUCCESS           EC entered into Boot Block Mode
 * @retval EFI_DEVICE_ERROR      I2C block write is failed 
 */
EFI_STATUS
EC_Enter_BBK(
  void
  );

/**
 * @brief Function to Exit from EC's boot block.
 * [0xBB][0x00] Exit EC Boot-Block (Normal service loop)
 *
 * @retval EFI_SUCCESS        EC exited from Boot Block Mode
 * @retval EFI_DEVICE_ERROR   I2C block write is failed 
 */
EFI_STATUS
EC_Exit_BBK(
  void
  );

/**
 * @brief Function to erase the designated Flash 
 *
 * @param cycle_ms            Timeout value to support the retry mechanism 
 * @param retry               No of retries
 *
 * @retval EFI_SUCCESS        Erase the designated flash is successfully 
 * @retval EFI_DEVICE_ERROR   I2C block write is Failed
 */
EFI_STATUS 
Erase_Designated_Flash(
  UINT16 cycle_ms,
  UINT8 retry
  );

/**
 * @brief read the designated Flash area
 *
 * @param addr               Address of flash from where we have to read 
 * @param cycle_ms           Timeout value to support the retry mechanism 
 * @param retry              No of retries
 *
 * @retval EFI_SUCCESS       Reading the designated flash is successfully 
 * @retval EFI_DEVICE_ERROR  I2C block read is Failed
 */
EFI_STATUS
Read_Designated_Area(
  unsigned int addr, 
  UINT16 cycle_ms, 
  UINT8 retry
  );

/**
 * @brief Read Corruption status, support in Startup BBK/ BBK /MBK

 * @retval EFI_SUCCESS       Reading Corruption status successfully 
 * @retval EFI_DEVICE_ERROR  I2C block read is Failed
**/
EFI_STATUS
EC_Check_Corruption_Status(
  void
  );

#endif
