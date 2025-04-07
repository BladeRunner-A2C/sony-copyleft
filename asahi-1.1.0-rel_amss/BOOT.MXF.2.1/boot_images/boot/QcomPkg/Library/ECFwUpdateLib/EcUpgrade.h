/** @file EcUpgrade.h

  Header for EC FW specific upgrade routines.

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------
  2023/04/28     ananns      Renamed function name from EcFirmwareRollback to EcFirmwareSync
  2023/03/29     sumesahu    Add support for Power-off EC during off mode charging &
                             enable check for power level.
  2023/03/13     bkulkarn    Migrate FmpDevicePkg to latest EDK2 version that 
                             is getting integrated by UEFI team
  2023/02/04     sumesahu    FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine
                             and code refactoring
  2023/01/11     ananns      Added EC_FW_BLOCK_SIZE macro for EC firmware size validation  
  2022/12/08     bkulkarn    Update Hamoa EC FW partition size/I2C core instance, code refactoring
  2022/09/22     bkulkarn    Changes to support A/B partition update & recovery protocol
  2022/07/29     sumesahu    Initial version
=============================================================================*/


#ifndef _ECUPGRADE_H
#define _ECUPGRADE_H

/* Flash Commands */
#define EC_SPI_SERVICE_CMD                      0xEC
#define EC_MODE_CMD                             0xBB
#define COPY_INT_P1MBK_TO_P2                    0x15
#define COPY_INT_P2MBK_TO_P1                    0x16
#define COPY_INT_P1BBK_TO_P2                    0x17
#define COPY_INT_P2BBK_TO_P1                    0x18
#define ENTRY_PREDEFINE_MODE                    0xB4
#define RUN_CHECKSUM_INT_P1_32K                 0xF0
#define RUN_CHECKSUM_INT_P2_32K                 0xF1
#define RUN_CHECKSUM_INT_P1_ODM                 0xF2
#define RUN_CHECKSUM_INT_P2_ODM                 0xF3
#define ENTER_BBK_CMD                           0xDC
#define EXIT_BBK_CMD                            0x33
#define MCU_RESET_CMD                           0xCC
#define FORCE_SPI_MIRROR_CMD                    0xEB
#define RUN_INT_MBK_CHECKSUM_CMD                0xED
#define RUN_INT_ACTIVE_CHECKSUM_CMD             0xF0
#define RUN_INT_BACKUP_CHECKSUM_CMD             0xF1
#define RUN_EXT_1ST_PARTITION_CHECKSUM_CMD      0xEE
#define RUN_EXT_2ND_PARTITION_CHECKSUM_CMD      0xEF
#define BULK_READ_CMD                           0xA2
#define EC_SPI_QUICK_CMD                        0xAF
#define GET_SPIFLASH_ID_CMD                     0x1D
#define SEL_INT_SPI_FLASH_CMD                   0x1C
#define SEL_EXT_SPI_FLASH_CMD                   0x1F
#define ERASE_INT_FLASH_MAINBLK_CMD             0xEE
#define ERASE_INT_FLASH_MBK_CMD                 0xEA
#define ERASE_EXT_ACTIVE_PARTITION_CMD          0xEB
#define ERASE_EXT_BACKUP_PARTITION_CMD          0xED
#define EC_ACPI_MIRROR_ONCE_CMD                 0x11
#define EC_ACPI_FORCE_MIRROR_IMMEDIATE_CMD      0x12
#define EC_ACPI_FORCE_MIRROR_AFTER_SHUTDOWN_CMD 0x13
#define EC_ACPI_Int2Ext_SPI_COPY_CMD            0x14
#define EC_SPI_ROM_SELECTION_CMD                0xB9
#define EC_ERASE_DESIGNATED_FLASH_AREA_CMD      0xAE
#define EC_FLASH_BUF_WRITE_CMD                  0xA0
#define EC_WRITE_DATABUF_TO_SPI_ROM_CMD         0xAA
#define EC_DEVICE_ID_CMD                        0x06
#define EC_CORRUPTION_STATUS_CMD                0xEB

// [TBD]: Below commands need to be supported in Boot-block and aligned with EC spec after confirmation from vendor.
#define EC_VALIDATE_BOOT_BLOCK_CMD              0xF5

/* Status */
#define EC_FW_IN_BOOT_BLK_IDLE                  0x0B
#define EC_FW_IN_MAIN_BLK_IDLE                  0x0C

#define EC_PASS_CHECKSUM                        0xAC
#define EC_FAIL_CHECKSUM                        0xFA
#define EC_FV_VERSION_LEN                       11

/* Values */
#define _SIZE_1KB                               (1024)
#define _SIZE_4KB                               (4*_SIZE_1KB)

#define PLATFORM_KODIAK                         0
#define PLATFORM_HAMOA                          1

#if PLATFORM_KODIAK
#define MAIN_BLK_SIZE                           120
#define FW_SIZE                                 (128 * 1024)
#define EC_VERSION_OFFSET                       (0x7F80)
#else
#define MAIN_BLK_SIZE                           24
#define FW_SIZE                                 (32 * 1024)
#define EC_VERSION_OFFSET                       (0x7780)
#endif

#define IT8987_7280                             (FALSE)
#define IT8987_8380                             (TRUE)
#define EC_WRITE_PROT_EN                        (FALSE)

#if IT8987_7280
#define DEFAULT_EC_FW_VERSION                   0x00000000
#define DEFAULT_EC_FW_LOWEST_SUPPORTED_VERSION  0x20000001                                    // Base EC FW version
#define BOOT_BLK_BUFFER_SIZE                    (8*_SIZE_1KB)
#define MAIN_BLK_BUFFER_SIZE                    (MAIN_BLK_SIZE*_SIZE_1KB)
#define DB_PADDING_SIZE                         (4*_SIZE_1KB)
#define BOOT_BLK_START_ADDR                     (0)
#define BOOT_BLK_END_ADDR                       (BOOT_BLK_START_ADDR + BOOT_BLK_BUFFER_SIZE)
#define MAIN_BLK_START_ADDR                     (BOOT_BLK_END_ADDR)
#define MAIN_BLK_END_ADDR                       (MAIN_BLK_START_ADDR + MAIN_BLK_BUFFER_SIZE)
#define DB_BLK_START_ADDR                       (MAIN_BLK_END_ADDR)
#define DB_BLK_END_ADDR                         (DB_BLK_START_ADDR + DB_PADDING_SIZE)
#define BOOT_BLK2_START_ADDR                    (DB_BLK_END_ADDR)
#define BOOT_BLK2_END_ADDR                      (BOOT_BLK2_START_ADDR + BOOT_BLK_BUFFER_SIZE)
#define MAIN_BLK2_START_ADDR                    (BOOT_BLK2_END_ADDR)
#define MAIN_BLK2_END_ADDR                      (MAIN_BLK2_START_ADDR + MAIN_BLK_BUFFER_SIZE)
#define DB_BLK2_START_ADDR                      (MAIN_BLK2_END_ADDR)
#define DB_BLK2_END_ADDR                        (DB_BLK2_START_ADDR + DB_PADDING_SIZE)
#define EC_MAX_WRITE_SECTOR_TO_RAM              (LIMIT_256B)
#define EC_MAX_WRITE_SECTOR_TO_FLASH            (EC_MAX_WRITE_SECTOR_TO_RAM)
#define EC_ERASE_ONESHOT_TIME_DELAY             (3 * 120 * 1024)                                // 3ms for each SPI erase
#define EFLASH_ADDR_START                       0x0
#define EFLASH_ADDR_END                         0x20000                                         // 128K total FW size
#else
#define DEFAULT_EC_FW_VERSION                   0x00000000
#define DEFAULT_EC_FW_LOWEST_SUPPORTED_VERSION  0x00000002                                      // Base EC FW version
#define BOOT_BLK_BUFFER_SIZE                    (8*_SIZE_1KB)
#define MAIN_BLK_BUFFER_SIZE                    (24*_SIZE_1KB)
#define EC_FW_BLOCK_SIZE                        ((BOOT_BLK_BUFFER_SIZE) + (MAIN_BLK_BUFFER_SIZE))
#define PG_BLK_BUFFER_SIZE                      (1*_SIZE_1KB)
#define EC_NV_BLK_BUFFER_SIZE                   (1*_SIZE_1KB)
#define OEM_BUFFER_SIZE                         (31*_SIZE_1KB)
#define ACTIVE_BBK_START_ADDR                   (0)
#define ACTIVE_BBK_END_ADDR                     (ACTIVE_BBK_START_ADDR + BOOT_BLK_BUFFER_SIZE)
#define BOOT_BLK_START_ADDR                     (ACTIVE_BBK_START_ADDR)                          // For compatibility
#define BOOT_BLK_END_ADDR                       (ACTIVE_BBK_END_ADDR)
#define ACTIVE_MBK_START_ADDR                   (BOOT_BLK_END_ADDR)
#define ACTIVE_MBK_END_ADDR                     (ACTIVE_MBK_START_ADDR + MAIN_BLK_BUFFER_SIZE)
#define MAIN_BLK_START_ADDR                     (ACTIVE_MBK_START_ADDR)
#define MAIN_BLK_END_ADDR                       (ACTIVE_MBK_END_ADDR)                            // For compatibility
#define ACTIVE_OEM_START_ADDR                   (ACTIVE_MBK_END_ADDR)
#define ACTIVE_OEM_END_ADDR                     (ACTIVE_OEM_START_ADDR + OEM_BUFFER_SIZE)
#define PG_BLK_START_ADDR                       (ACTIVE_OEM_END_ADDR)
#define PG_BLK_END_ADDR                         (ACTIVE_OEM_END_ADDR + PG_BLK_BUFFER_SIZE)
#define BACKUP_BBK_START_ADDR                   (PG_BLK_END_ADDR)
#define BACKUP_BBK_END_ADDR                     (PG_BLK_END_ADDR + BOOT_BLK_BUFFER_SIZE)
#define BOOT_BLK2_START_ADDR                    (BACKUP_BBK_START_ADDR)
#define BOOT_BLK2_END_ADDR                      (BACKUP_BBK_END_ADDR)                            // For compatibility
#define BACKUP_MBK_START_ADDR                   (BACKUP_BBK_END_ADDR)
#define BACKUP_MBK_END_ADDR                     (BACKUP_MBK_START_ADDR + MAIN_BLK_BUFFER_SIZE)
#define MAIN_BLK2_START_ADDR                    (BACKUP_MBK_START_ADDR)                          // For compatibility
#define MAIN_BLK2_END_ADDR                      (BACKUP_MBK_END_ADDR)
#define BACKUP_OEM_START_ADDR                   (BACKUP_MBK_END_ADDR)
#define BACKUP_OEM_END_ADDR                     (BACKUP_OEM_START_ADDR + OEM_BUFFER_SIZE)
#define EC_NV_BLK_START_ADDR                    (BACKUP_OEM_END_ADDR)
#define EC_NV_BLK_END_ADDR                      (EC_NV_BLK_START_ADDR + EC_NV_BLK_BUFFER_SIZE)
#define EC_MAX_WRITE_SECTOR_TO_RAM              (LIMIT_256B)
#define EC_MAX_WRITE_SECTOR_TO_FLASH            (EC_MAX_WRITE_SECTOR_TO_RAM)
#define EC_ERASE_ONESHOT_TIME_DELAY             (3 * 24 * 1024)                                   // 3ms for each SPI erase
#define EFLASH_ADDR_START                       0x0
#define EFLASH_ADDR_END                         0x8000                                            // 32K total FW size
#endif

#define INT_FLASH_ERASE_SECTOR_SIZE             (1 * 1024)                                        // 1K Sector Size for Internal eFlash
#define EXT_FLASH_ERASE_SECTOR_SIZE             (4 * 1024)                                        // 4K Sector Size for External Flash
#define EC_CHECKSUM_CALC_TIME_DELAY             (1000)                                            // Checksum calculation delay

/* I2C Slave Device Types */
#define SLAVE_TYPE_NORM                         0
#define SLAVE_TYPE_REG                          1
#define SLAVE_TYPE_MEM                          2
#define EC_REGISTER_WRITE                       0xA8
#define EC_REGISTER_READ                        0xA9

/* Delay Values */
#define TIME_1MS                                (1000)
#define TIME_5MS                                (5000)
#define TIME_10MS                               (10000)
#define TIME_20MS                               (20000)
#define TIME_30MS                               (30000)
#define TIME_50MS                               (50000)
#define TIME_100MS                              (100000)
#define TIME_200MS                              (200000)
#define TIME_300MS                              (300000)
#define TIME_500MS                              (500000)
#define TIME_1SEC                               (1000000)
#define TIME_2SEC                               (2000000)
#define TIME_5SEC                               (5000000)
#define TIME_8SEC                               (8000000)
#define TIME_10SEC                              (10000000)
#define RETRY_250                               (250)
#define CYCLE_5MS                               (5)

/* ITE8987 EC VERSION */
#define EC_VERSION_CMD                          0x0D
#define EC_VERSION_BLK_READ_CMD                 0x0E
#define EC_FULL_VERSION_BLK_READ_CMD            0x0F
#define EC_VERSION_DATA_SIZE                    4                                                     // [0,1,2,3] :[ByteCount, Test, Sub, Main] version
#define EC_FULL_VERSION_DATA_SIZE               7                                                     // [0-2]: Fv, [3-5]: LsFv

#define EC_FW_UPDATE_ATTEMPT_COUNT_MAX          (4)

#define SleepMs(time_in_ms)                     gBS->Stall(time_in_ms)
#define BUFFER_SIZE                             0x8000

// EC Firmware update specific result values
typedef enum _EC_FW_UPDATE_RESULT
{
  EC_FW_UPDATE_SUCCESS,
  EC_FW_UPDATE_FAIL,
}EC_FW_UPDATE_RESULT;

typedef enum _FW_BLOCK
{
  MAIN_BLK    =   1,
  BOOT_BLK    =   2,
  UNKNOWN_BLK =   0xAA
}FW_BLOCK;

typedef enum _WRITE_BUF_LIMIT
{
  LIMIT_32B  = 32,
  LIMIT_64B  = 64,
  LIMIT_128B = 128,
  LIMIT_256B = 256,
  LIMIT_512B = 512,
  MAX_LIMIT  = LIMIT_512B
}WRITE_BUF_LIMIT;

typedef enum _FW_CTRL_PATH
{
  INT_FLASH_P1_CTRL_PATH = 0x3F,
  INT_FLASH_P2_CTRL_PATH = 0x2F,
  INT_FLASH_CTRL_PATH = 0x4F,
  EXT_FLASH_CTRL_PATH = 0x0F,
  UNKNOWN_CTRL_PATH   = 0xFF
}FW_CTRL_PATH;

typedef enum _EC_CHECKSUM_RESULT
{
  PASS_CHECKSUM       = 0xAC,
  FAIL_CHECKSUM       = 0xFA,
  UNKNOWN_CHECKSUM    = 0xFF
}EC_CHECKSUM_RESULT;

typedef struct _EC_DEVICE_INFO
{
  UINT16            chipID;
  unsigned char     flash_id[3];
}EC_DEVICE_INFO;

typedef enum _EC_FLASH_PARTITION_INFO
{
  UNKNOWN_FLASH_INFO = 0x0,
  INTERNAL_FLASH,                       // Indicates undivided internal flash.
  INTERNAL_FLASH_P1,                    // Indicates first partition within internal flash.
  INTERNAL_FLASH_P2,                    // Indicates second partition within internal flash.
  INTERNAL_FLASH_MBK_P1,                // Indicates main block of first partition within internal flash.
  INTERNAL_FLASH_MBK_P2,                // Indicates main block of second partition within internal flash.
  INTERNAL_FLASH_BBK_P1,                // Indicates boot block of second partition within internal flash.
  INTERNAL_FLASH_BBK_P2,                // Indicates boot block of second partition within internal flash.
  INTERNAL_FLASH_OEM_P1,                // Indicates OEM/ODM block of first partition within internal flash.
  INTERNAL_FLASH_PGUARD_P1,             // Indicates Partition Guard block of first partition within internal flash.
  INTERNAL_FLASH_NV,                    // Indicates NV block after second partition within internal flash.
  INTERNAL_FLASH_OEM_P2,                // Indicates OEM/ODM block of second partition within internal flash.
  EXTERNAL_FLASH_P1,                    // Indicates first partition within external flash.
  EXTERNAL_FLASH_P2,                    // Indicates second partition within external flash.
  MAX_LIMIT_FLASH_INFO
}EC_FLASH_PARTITION_INFO;

typedef enum _EC_PROTOCOL_INFO
{
  UNKNOWN_PROTOCOL,
  ACPI_I2C_PROTOCOL,
  RECOVERY_I2C_PROTOCOL,
  MAX_LIMIT_PROTOCOL_INFO
}EC_PROTOCOL_INFO;

typedef struct _EC_DEVICE_CONTEXT
{
  UINT32                    on_ic_fw_version;                       /// Indicates current EC Firmware version.
  UINT32                    on_ic_lowest_supported_fw_version;      /// Indicates current lowest supported EC Firmware version.
  UINT32                    on_bin_fw_version;                      /// Indicates EC Firmware version present on binary.
  UINT32                    on_bin_lowest_supported_fw_version;     /// Indicates lowest supported EC Firmware version present on binary.
  UINT32                    on_nv_fw_version;                       /// Indicates EC Firmware version cached into NV.
  UINT32                    on_nv_lowest_supported_fw_version;      /// Indicates lowest supported EC Firmware version cached into NV.
  UINTN                     fw_img_data_size;                       /// Indicates EC Firmware image size read from the binary.
  unsigned int              erase_sector_size;                      /// Indicates the size of each sector to be erased for internal or external flash.
  unsigned int              start_addr;                             /// Indicates the start address to erase/update for internal or external flash.
  unsigned int              end_addr;                               /// Indicates the end address to erase/update for internal or external flash.
  VOID                      *i2c_handle;                            /// Represents the I2C handle open to communicate with EC
  i2c_slave_config          slave_config;                           /// Represents the slave address for ACPI over I2C protocol.
  i2c_slave_config          recovery_slave_config;                  /// Represents the slave address for Recovery (HW-Predefine) protocol.
  VERSION_INFO              on_bin_lsfv_info;                       /// Structure to denote on binary lowest support EC Firmware version contents.
  VERSION_INFO              on_ic_lsfv_info;                        /// Structure to denote the current lowest support EC Firmware version contents.
  VERSION_INFO              on_bin_fv_info;                         /// Structure to denote on binary EC Firmware version contents.
  VERSION_INFO              on_ic_fv_info;                          /// Structure to denote current EC Firmware version contents.
  VERSION_INFO              on_ic_bbk_fv_info;                          /// Structure to denote current EC Firmware version contents.
  VERSION_INFO              on_nv_fv_info;                          /// Structure to denote EC Firmware version contents cachced into NV.
  VERSION_INFO              on_nv_lsfv_info;                        /// Structure to denote the lowest supported EC Firmware version contents cachced into NV.
  EC_DEVICE_INFO            register_info;                          /// Structure to denote EC specific register information.
  EC_FLASH_PARTITION_INFO   flash_type;                             /// Represents the flash type selected (internal/external as applicable)
  EC_FLASH_PARTITION_INFO   partition_to_update;                    /// Points to the partition chosen to be updated after evaluating firmware checksum.
  EC_PROTOCOL_INFO          active_protocol;                        /// Denotes the active protocol selected to communicate with EC.
  EC_CHECKSUM_RESULT        active_checksum_result;                 /// Stores the checksum result calculated on current EC firmware partition.
  byte                      *fw_img_data;                           /// Indicates raw EC firmware image contents read from the binary.
  byte                      *fw_bbk_blk_data;                       /// Indicates raw Boot Block Firmware section contents
  byte                      *fw_main_blk_data;                      /// Indicates raw Main Block Firmware section contents
  CHAR8                     fw_status;                              /// Indicates if EC is running in Boot block or Main block.
  UINT8                     ctrl_path;                              /// Indicates if the flash control is for internal or external (if applicable).
  byte                      erase_blockCount;                       /// Indicates the number of blocks to be erased for internal or external flash.
  UINT8                     code_mirror_tag;                        /// Indicates the partition used to mirror EC Firmware from external to internal flash (if applicable).
  UINT16                    ec_device_id;                           /// Indicates unique device-id corresponding to EC Hardware on the given QCOM chipset.
  UINT8                     slave_addr;                             /// Represents the 7bit slave-address applicable for ACPI over I2C protocol.
  UINT8                     recovery_slave_addr;                    /// Represents the 7bit slave-address applicable for Recovery/HW-Predefine protocol.
  UINT8                     valid_rawbuff_exist;                    /// Denotes if the raw EC Firmware binary contents are valid
  UINT8                     is_fw_update_done;                      /// Denotes if the EC Firmware is updated using the FMP state machine.
  UINT8                     is_device_init_done;                    /// Denotes the EC device related initialization status.
  UINT8                     is_device_active;                       /// Denotes if the EC device is active through ACPI over I2C protocol.
  UINT8                     is_recovery_active;                     /// Denotes if the EC recovery path is active through HW pre-define protocol.
  UINT8                     is_fw_corrupted;                        /// Indicates if the EC FW is corrupted or not.
  UINT8                     corruption_status;                      /// Indicates health status of all the Partitions.
}EC_DEVICE_CONTEXT;

/**
 * @brief The entry Point for EC Initialize device and its associated context.
 *
 * @param Void
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcInitializeDevice(void);

/**
 * @brief The entry Point for EC De-initialize device and its associated context.
 *
 * @param Void
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcDeInitializeDevice(void);

/**
 * @brief Function to check the EC FW status
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcCheckFwStatus(void);

/**
 * @brief Function to erase designated region within internal/external flash
 *
 * @param cycle_ms  Sleep time for EC SPI service
 * @param retry     Max retry for EC SPI service
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcEraseDesignatedFlash(
  UINT16 cycle_ms,
  UINT8 retry
);

/**
 * @brief Function to enter into the EC boot block: [EC_MODE_CMD][BYTECNT1[EC_ENTER_BBK_CMD] Entry EC Boot-Block
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcEnterBBK(void);

/**
 * @brief Function to exit out of the EC Boot Block.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcExitBBK(void);

/**
 * @brief Function to enable EC flashing process.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
EcEnableFlashing();

/**
 * @brief Entry point to parse and flash the EC firmware image
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcReflashFirmware(void);

/**
 * @brief Entry point to parse and flash the EC firmware image,
 * using ACPI over I2C protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcReflashUsingACPII2C();

/**
 * @brief Function to copy firmware from internal flash to selected external flash partition.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcInt2ExtSPICopy(void);

/**
 * @brief Function to request issuing H/W based force code mirror operation.
 *
 * @param forceMirrorCommand  Command to issue H/W force-code mirror operation
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcForceMirror(
  UINT8 forceMirrorCommand
);

/**
  @brief Callback funtion to report the process of the EC Firmware update.
  Wrap the caller's version in this so that progress from the device lib is within the expected range.

  @param[in]  Completion    A value between 1 and 100 indicating the current completion
  progress of the firmware update. Completion progress is
  reported as from 1 to 100 percent. A value of 0 is used by
  the driver to indicate that progress reporting is not supported.

  @retval EFI_SUCCESS       SetImage() continues to do the callback if supported.
  @retval other             SetImage() discontinues the callback and completes
  the update and returns.
**/
EFI_STATUS
EFIAPI
EcFwUpdateProgress (
  IN  UINTN Completion
);

/**
 * @brief Function to handle operations to be done post the firmware update.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcPostFwUpdate();


/**
 * @briefFunction to wait for Firmware to Enter into Main Block (MBK)
 *
 * @param   cycle_ms         Each cycle sleep time.
 * @param   max_retyr        Num of maximum retries.
 *
 * @retval status            A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
WaitForEnterIntoMainBlock(
  UINT16 cycle_ms,
  UINT8 max_retry
);

/**
 * @briefFunction to wait for Firmware to Enter into Boot Block (MBK)
 *
 * @param   cycle_ms         Each cycle sleep time.
 * @param   max_retyr        Num of maximum retries.
 *
 * @retval status            A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
WaitForEnterIntoBootBlock(
  UINT16 cycle_ms,
  UINT8 max_retry
);

/**
 * @brief Function to check the firmware control path
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcCheckControlPath(void);

/**
 * @brief Function to wait for EC SPI service
 *
 * @param cycle_ms      Sleep time before each i2c transaction
 * @param max_retry     Maximum retry before failure
 *
 * @retval status       A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
WaitForEcSpiService(UINT16 cycle_ms, UINT8 max_retry);

/**
 * @brief Function to trigger EC Checksum operation: [EC_MODE_CMD][BYTECNT1][RUN_MAIN_CHECKSUM_CMD] Entry EC Boot-Block
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRunChecksum(EC_FLASH_PARTITION_INFO flashType);

/**
 * @brief Function to wait for EC checksum result
 *
 * @param timeout_ms         Wait for the timeout
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
WaitForEcChecksumResult(unsigned int timeout_ms);

/**
 * @brief Function to Recover/Copy/Rollback th FW content from one partition 
 * to another partition.
 * COPY_INT_P1MBK_TO_P2 implies copy FW content from P1MBK to P2MBK
 * COPY_INT_P2MBK_TO_P1 implies copy FW content from P2MBK to P1MBK
 *
 * @param wdBuf      Direction to copy FW content from one partition to another.
 * @param flash_type Implies partition flash Type in internal eFlash of EC
 *
 * @retval status    A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcFirmwareSync(
  UINT8 wdBuf,
  EC_FLASH_PARTITION_INFO flash_type
  );

#endif
