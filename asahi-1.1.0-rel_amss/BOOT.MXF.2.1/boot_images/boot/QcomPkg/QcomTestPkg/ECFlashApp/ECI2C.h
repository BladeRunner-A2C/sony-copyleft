/** @file
  I2C Application that communicate with the EC (Embedded Controller).

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

#ifndef _EC_I2C_H
#define _EC_I2C_H

#include "i2c_api.h"
#include <ECLog.h>

/* ITE8987 EC slave address */
#define I2C_EC_SLAVE_ADDRESS                    0x76
#define I2C_PREDEFINE_EC_SLAVE_ADDRESS          0x5B
#define I2C_HID_MODE_EC_SLAVE_ADDRESS           0x3A
#define i2C_HID_DESCRIPTOR                      0x0001
#define I2C_DEFAULT_BUS_FREQ                    400
#define I2C_MAX_CLK_STRETCH_FREQ                500
#define BLOCK_READ_BYTE_MAX                     512
#define BLOCK_WRITE_BYTE_MAX                    512
#define I2C_TIMEOUT_MS                          2500
#define INVALID_CMD                             0

#define WITHOUT_BYTE_CNT                        0
#define WITH_BYTE_CNT                           1
#define STATIC_DAT_LEN                          0
#define DYNAMIC_DAT_LEN                         0
#define WRITE_ONLY                              0

/* Data Size for each command */
#define EC_VERSION_DATA_SIZE                    4 	//[0,1,2] :[Main, Sub, Test] version

//-------------------------------------------------------------------------------------------
// MSM EC I2C command Set
//
// Spec : ITE EC - WoS Platform Firmware Specification v2.4_Beta7.docx
//
// [Important!!] 
// - We only list Flash relevant commands below since ECFlashApp is for flashing purpose.
// - Please review & renew the spec if you plan to make change of the command set
//-------------------------------------------------------------------------------------------
#define LAST_TAG_MUST_STAY_AT_LAST              0xFAFAFAFA 
/**********************ACPI I2C Command (Addr : 0x76)[START]********************************/
// EC Version Command [Start]-----------------------
#define EC_VERSION_CMD_RO                       0x0E000000
// [ADDR_W][0x0E][RS][ADDR_R][BCNT=3][ZZ][YY][XX]
// XX : Main Version
// YY : Sub Version
// ZZ : Test Version

// Write SPI Flash Command (to RAM) [Start]---------------
#define EC_FLASH_BUF_WRITE_CMD_WO               0xA0000000

#define READ_BUFF_512_CMD_RO                    0xA1000000
#define BULK_READ_CMD_RO                        0xA2000000
// Get Checksum Result Command [Start]--------------------
// [Note] : It must perform 0xBB
#define CHECKSUM_RESULT_CMD_RO                  0xA2000000
// [ADDR_W][0xA2][RS][ADDR_R][BCNT = 5][XX][DAT1][DAT2]…[DAT4]
// XX :
#define Checksum_PASS                           0xAC
#define Checksum_FAIL                           0xFA

// Read Designated Area Command (from ROM to RAM) [Start]-
#define READ_ROM_TO_BUFF_512_CMD_RO             0xA7000000

// Write Designated Area Command (to RAM) [Start]---------
#define EC_REGISTER_WRITE_WO                    0xA8000000

// Read Designated Area Command (from RAM) [Start]--------
#define EC_REGISTER_READ_WO                     0xA9000000

// Write SPI Flash Command (from RAM to ROM) [Start]------
#define EC_WRITE_DATABUF_TO_SPI_ROM_CMD_WO      0xAA000000

// Erase Designated Command [Start]-----------------------
#define ERASE_DESIGNATED_CMD_WO                 0xAE000000
// [ADDR_W][0xAE][BCNT=4][XX][BLOCKCNT][SPI Addr_L][SPI Addr_M] [SPI Addr_H]
// XX :
#define CTRL_PATH_EFLASH                        0x4F
#define CTRL_PATH_EXT_FLASH                     0x0F

// SPI Quick Command [Start]------------------------------
#define SPI_QUICK_CMD_WO                        0xAF000000
// [ADDR_W][0xAF][BCNT=1][XX]
// XX :
#define SEL_INT_SPI_FLASH_CMD                   0x1C
#define GET_SPIFLASH_ID_CMD                     0x1D
#define SEL_EXT_SPI_FLASH_CMD                   0x1F
#define ERASE_INT_FLASH_MAINBLK_CMD             0xEE

// EC Mode Command [Start]--------------------------------
#define EC_MODE_CMD_WO                          0xBB000000
// [ADDR_W][0xBB][BCNT=1][XX]
// XX :
#define DIS_MIRROR_CMD                          0x11
#define FORCE_MIRROR_IMMEDIATLY                 0x12
#define FORCE_MIRROR_AFTER_SHUTDOWN             0x13
#define COPY_INT_MBK_TO_P2                      0x15
#define COPY_INT_MBK_TO_P1                      0x16
#define COPY_INT_BBK_TO_P2                      0x17
#define COPY_INT_BBK_TO_P1                      0x18
#define EXIT_BBK_CMD                            0x33
#define ENTRY_PREDEFINE_MODE                    0xB4
#define MCU_RESET_CMD                           0xCC
#define ENTER_BBK_CMD                           0xDC
#define FORCE_SPI_MIRROR_CMD                    0xEB//(Not Supported on Hamoa IT8987 )
#define RUN_CHECKSUM_INT_MAIN_120K              0xED
#define RUN_CHECKSUM_EXT_P1_128K                0xEE
#define RUN_CHECKSUM_EXT_P2_128K                0xEF
#define RUN_CHECKSUM_INT_P1_32K                 0xF0
#define RUN_CHECKSUM_INT_P2_32K                 0xF1
#define RUN_CHECKSUM_INT_P1_ODM                 0xF2
#define RUN_CHECKSUM_INT_P2_ODM                 0xF3

// Check Corrpution Status Command  [Start]---------------
#define CORRUPTION_STATUS_CMD_RO                0xEB000000
// [ADDR_W][0xEB][RS][ADDR_R][BCNT=1][XX]
// XX:
#define BIT0_ACTIVE_BBK_CORRUPTED               0x01
#define BIT1_BACKUP_BBK_CORRUPTED               0x02
#define BIT2_ACTIVE_MBK_CORRUPTED               0x04
#define BIT3_BACKUP_MBK_CORRUPTED               0x08
#define BIT7_DATA_VALID_BIT                     0x80

// Check Corrpution Status Command  [Start]---------------
#define SPI_SERVICE_CMD_RO                      0xEC000000
// [ADDR_W][0xEC][RS][ADDR_R][BCNT=2][XX][YY]
// XX:
#define EC_IN_BBK                               0x0B
#define EC_IN_MBK                               0x0C
#define OPERATION_FAIL                          0xFA
// YY:
#define CTRL_PATH_IS_EFLASH                     0x4F
#define CTRL_PATH_IS_EXT_FLASH                  0x0F

/**********************ACPI I2C Command (Addr : 0x76)[END]********************************/
/**********************Pre-define Command (Addr : 0x5B)[START]****************************/

#define I2EC_ADDRESS_WO                         0x10000000
#define I2EC_DATA_WR                            0x11000000
#define PREDEFINE_CHIP_SELECT_TOGGLE_WO         0x17000000
/**********************Pre-define Command (Addr : 0x5B)[END]******************************/
typedef struct _CMD_CONTEXT
{
  UINT32 cmd;
  UINT8  wCmdLength;
  UINT16 wrDataSize;
  UINT8  withByteCnt;
  UINT8  activeI2cChannel;
}CMD_CONTEXT;

//--------------------------------------------------------------------------------
// Keyboard InputReport
//--------------------------------------------------------------------------------
typedef struct
{
  UINT16 length;
  UINT8  reportID;                      // Report ID // Collection: Keyboard
  UINT8  KeyboardLeftControl : 1;       // Usage 0x000700E0: Keyboard Left Control, Value = 0 to 1
  UINT8  KeyboardLeftShift : 1;         // Usage 0x000700E1: Keyboard Left Shift, Value = 0 to 1
  UINT8  KeyboardLeftAlt : 1;           // Usage 0x000700E2: Keyboard Left Alt, Value = 0 to 1
  UINT8  KeyboardLeftGui : 1;           // Usage 0x000700E3: Keyboard Left GUI, Value = 0 to 1
  UINT8  KeyboardRightControl : 1;      // Usage 0x000700E4: Keyboard Right Control, Value = 0 to 1
  UINT8  KeyboardRightShift : 1;        // Usage 0x000700E5: Keyboard Right Shift, Value = 0 to 1
  UINT8  KeyboardRightAlt : 1;          // Usage 0x000700E6: Keyboard Right Alt, Value = 0 to 1
  UINT8  KeyboardRightGui : 1;          // Usage 0x000700E7: Keyboard Right GUI, Value = 0 to 1
  UINT8  pad_2;                         // Pad
  UINT8  Keyboard_data[6];              // Value = 0 to 255
} InputReport;

//--------------------------------------------------------------------------------
// HidDescriptor
//--------------------------------------------------------------------------------
typedef struct
{
  UINT16 wHidDescLength;
  UINT16 bcdVersion;
  UINT16 wReportDescLength;
  UINT16 wReportDescRegister;
  UINT16 wInputRegister;
  UINT16 wMaxInputLength;
  UINT16 wOutputRegister;
  UINT16 wMaxOutputLength;
  UINT16 wCommandRegister;
  UINT16 wDataRegister;
  UINT16 wVendorID;
  UINT16 wProductID;
  UINT16 wVersionID;
  UINT32 Reserved;
} HidDescriptor;

typedef struct _VERSION_INFO
{
  UINT8 main_ver;
  UINT8 sub_ver;
  UINT8 test_ver;
}VERSION_INFO;

typedef enum Chipset
{
  UNKNOWN_CHIP,
  KODIAK,
  HAMOA,
}Chipset_t;

typedef enum _EC_PROTOCOL_INFO
{
  UNKNOWN_PROTOCOL,
  ACPI_I2C_PROTOCOL,
  RECOVERY_I2C_PROTOCOL,
  MAX_LIMIT_PROTOCOL_INFO
}EC_PROTOCOL_INFO;

typedef struct _EC_DEVICE_CONTEXT
{
  UINT8                     force_fwup;
  UINT8                     fwup;
  UINT8                     need_fw_upgrade;
  UINT8                     fw_size;
  UINT8                     reset_flag;
  UINT8                     *tx_buf;
  UINT8                     *rx_buf;
  UINT8                     buf_size;
  CHAR16                    fw_img_name[256];
  UINTN                     fw_img_name_length;
  EC_PROTOCOL_INFO          activeI2cChannel;                        // Denotes the active protocol selected to communicate with EC.
  byte                      *fw_img_data;                           // Indicates raw EC firmware image contents read from the binary.
  UINTN                     fw_img_data_size;
  byte                      *fw_bbk_blk_data;                       // BOOT BLK FW
  byte                      *fw_main_blk_data;                      // MAIN BLK FW
  UINT8                     fw_status;                              // Indicates if EC is running in Boot block or Main block.
  UINT8                     ctrl_path;                              // Indicates if the flash control is for internal or external (if applicable).
  byte                      erase_blockCount;                       // for AEh command - Erase designated range of external Flash
  unsigned int              erase_sector_size;                      // Indicates the size of each sector to be erased for internal or external flash.
  unsigned int              start_addr;                             // Indicates the start address to erase/update for internal or external flash.
  unsigned int              end_addr;                               // Indicates the end address to erase/update for internal or external flash.
  VOID                      *i2c_handle;                            // Represents the I2C handle open to communicate with EC
  i2c_slave_config          slave_config;                           // Represents the slave address for ACPI over I2C protocol.
  i2c_slave_config          recovery_slave_config;                  // Represents the slave address for Recovery (HW-Predefine) protocol.
  char                      *temp_str;
  VERSION_INFO              on_bin_info;
  VERSION_INFO              on_ic_info;
  UINT8                     slave_addr;                             // Represents the 7bit slave-address applicable for ACPI over I2C protocol.
  UINT8                     recovery_slave_addr;                    // Represents the 7bit slave-address applicable for Recovery/HW-Predefine protocol.
  UINT8                     debug_mask;
  UINT8                     query_version;
  UINT8                     valid_binfile_exist;
  UINT8                     flash_type;
  byte                      *spinor_fw_img_data;
  HidDescriptor             gHidDesc;
  UINT8                     pre_define_update;
  Chipset_t                 Chipset;
  uint16                    ecChipID;
}EC_DEVICE_CONTEXT;

extern CMD_CONTEXT CmdContext[];
extern EC_DEVICE_CONTEXT *deviceContext;
/**
 * Return EFI_STATUS value for i2c_status value
 *
 * @param  I2cStatus               i2c_status value
 * @retval EFI_SUCCESS             I2C_SUCCESS
 * @retval EFI_DEVICE_ERROR        any other i2c failures
 *
**/
EFI_STATUS 
I2cstatusToEfistatus (
    i2c_status I2cstatus
    );

/** I2C_Init: 
 * Initialize I2C CORE PROTOCOL
 * @retval EFI_SUCCESS             I2C_SUCCESS
 * @retval EFI_OUT_OF_RESOURCES    Failed to initialize I2C core
 * @retval EFI_DEVICE_ERROR        ec_device handle NULL
**/
EFI_STATUS 
I2C_Init (void);

/** I2C_DeInit:
 *  De-Initialize I2C CORE PROTOCOL
**/
void 
I2C_DeInit (void);


/* 
    I2C CMD WRITE ONLY PROTOCOL [ADDR][CMD]
    @param  activeI2cChannel        Active I2c Channel
    @param  cmd                     command value 

    @retval EFI_SUCCESS             The I2C command write is executed successfully.
    @retval EFI_DEVICE_ERROR        I2C handler or ec_device handle is NULL.
    @retval EFI_INVALID_PARAMETER   Invalid command value
*/
EFI_STATUS 
i2c_cmd_write_only (
    UINT8 activeI2cChannel,
    UINT8 cmd
    );


/*  I2C DATA READ ONLY PROTOCOL [ADDR] [DATA_LOW][DATA_HIGH]
    @param  activeI2cChannel        Active I2c Channel
    @param  buff                    Pointer to I2C read buffer 
    @param  buff_size               Size of the read buffer.

    @retval EFI_SUCCESS             The I2C read is executed successfully.
    @retval EFI_DEVICE_ERROR        I2C handler is NULL.
    @retval EFI_OUT_OF_RESOURCES    Unable to allocate the requested memory or buff_size out of range
    @retval EFI_INVALID_PARAMETER   Invalid command value
*/
EFI_STATUS 
i2c_data_read_only (
    UINT8 activeI2cChannel,
    void* buff, 
    UINT8 buff_size
    );

/*  I2C WORD READ PROTOCOL [ADDR][CMD] [ADDR] [DATA_LOW][DATA_HIGH]
    @param  activeI2cChannel        Active I2c Channel
    @param  cmd                     I2C command value 
    @param  buff                    Pointer to I2C read buffer 

    @retval EFI_SUCCESS             The I2C word read is executed successfully.
    @retval EFI_DEVICE_ERROR        I2C transferred is failed, ec_device handle or buff NULL.
    @retval EFI_INVALID_PARAMETER   Invalid command value
*/
EFI_STATUS 
i2c_word_read (
    UINT8 activeI2cChannel,
    UINT8 cmd, 
    void* buff
    );


/*   I2C BYTE READ PROTOCOL [ADDR][CMD] [ADDR] [DATA]
    @param  activeI2cChannel        Active I2c Channel
    @param  cmd                     I2C command value 
    @param  buff                    Pointer to I2C read buffer 

    @retval EFI_SUCCESS             The I2C byte read is executed successfully.
    @retval EFI_DEVICE_ERROR        I2C transferred is failed.
    @retval EFI_INVALID_PARAMETER   Invalid command value
*/
EFI_STATUS 
i2c_byte_read (
    UINT8 activeI2cChannel,
    UINT8 cmd, 
    void* buff
    );


/*   I2C BLOCK READ PROTOCOL [ADDR][CMD] [ADDR] [BYTECNT][DATA_0][DATA_1] ... [DATA_N-1]
    @param  cmd                     I2C command
    @param  rbuff                   Pointer to I2C read buffer
    @param  dynamic_datalength      Dynamic Data Length
    @param  cycle_ms                Time taken to read the data from the slave mentioned in milliseconds
    @param  max_retry               No of retry 

    @retval EFI_SUCCESS             The I2C block read is executed successfully.
    @retval EFI_DEVICE_ERROR        I2C transferred is failed.
    @retval EFI_OUT_OF_RESOURCES    Unable to allocate the required memory or buff_size out of range
    @retval EFI_INVALID_PARAMETER   Invalid command value
*/
EFI_STATUS 
i2c_block_read (
    UINT32 cmd,
    void* rbuff,
    UINT8 dynamic_datalength,
    UINT16 cycle_ms,
    UINT8 max_retry
    );

/*  I2C WORD WRITE PROTOCOL [ADDR][CMD] [DATA_LOW] [DATA_HIGH]
    @param  activeI2cChannel        Active I2c Channel
    @param  cmd                     I2C command value 
    @param  buff                    Pointer to I2C write buffer 

    @retval EFI_SUCCESS             The I2C word write is executed successfully.
    @retval EFI_DEVICE_ERROR        I2C transferred is failed.
    @retval EFI_INVALID_PARAMETER   Invalid command value
*/
EFI_STATUS 
i2c_word_write (
    UINT8 activeI2cChannel,
    UINT8 cmd, 
    void* buff
    );

/*   I2C BYTE WRITE PROTOCOL [ADDR][CMD][DATA]
    @param  activeI2cChannel        Active I2c Channel
    @param  cmd                     I2C command value 
    @param  buff                    Pointer to I2C write buffer 

    @retval EFI_SUCCESS             The I2C byte write is executed successfully.
    @retval EFI_DEVICE_ERROR        I2C transferred is failed.
    @retval EFI_INVALID_PARAMETER   Invalid command value
*/
EFI_STATUS 
i2c_byte_write (
    UINT8 activeI2cChannel,
    UINT8 cmd, 
    void* buff
    );
    
/*   I2C BLOCK WRITE PROTOCOL [ADDR][CMD] [BYTECNT][DATA_0][DATA_1] ... [DATA_N-1]
    @param  cmd                       I2C command
    @param  wbuff                     Pointer to I2C write buffer

    @retval EFI_SUCCESS               The I2C block write is executed successfully.
    @retval EFI_DEVICE_ERROR          I2C transferred is failed.
    @retval EFI_OUT_OF_RESOURCES      Unable to allocate the required memory or buff_size out of range
    @retval EFI_INVALID_PARAMETER     Invalid command value
*/
EFI_STATUS 
i2c_block_write (
    UINT32 cmd, 
    void* wbuff,
    UINT16 cycle_ms,
    UINT8 max_retry);

/*  
    I2EC Address Write -> I2EC Data Write
    @param  address           I2C address value 
    @param  data              Data value of size of 1 byte 

    @retval EFI_SUCCESS       The I2C write byte is executed successfully
    @retval EFI_DEVICE_ERROR  I2C transferred is failed.
*/
EFI_STATUS
i2ec_writebyte (
    unsigned int address,
    UINT8 data
);

/*  
    I2EC Address Write -> I2EC Data Read
    @param  address    I2C address value 
    @param  buff       Poniter to the read buffer

    @retval EFI_SUCCESS       The I2C read byte is executed successfully
    @retval EFI_DEVICE_ERROR  I2C transferred is failed.
*/
EFI_STATUS
i2ec_readbyte (
    unsigned int address,
    void* buff
);

/*  
    Pre-define Command Send protocol:
    [S] 0x5B [W] [A] 0x17 [A] S 0x5B [W] [A] 0x18 [A] cmd1 [A] [P]
    @param  cmd                     I2C command value

    @retval EFI_SUCCESS             The I2C predefined write is executed successfully
    @retval EFI_DEVICE_ERROR        I2C transferred is failed.
    @retval EFI_INVALID_PARAMETER   Invalid command value
*/
EFI_STATUS
i2c_predefine_send (
    UINT8 cmd
);

/*  
    Pre-define block read protocol:
    [ADDR] [0x17] [ADDR] [0x18] [CMD] [ADDR] [DATA_0][DATA_1] ... [DATA_N-1]
    S 0x5B [W] [A] 0x17 [A] S 0x5B [W] [A] 0x18 [A] cmd1 [A] S 0x5B [R] payload[0] [A] payload[N] [NA] [P]
    [S] 0x5B [W] [A] 0x17 [A] S 0x5B [W] [A] 0x18 [A] cmd1 [A] [P]
    @param  cmd                     I2C command value
    @param  buff                    Pointer to the read buffer
    @param  buff_size               Read buffer size
    @param cycle_ms                 I2C Timeout value in milliseconds
    @param max_retry                No of retry if in case of failure in transmission 

    @retval EFI_SUCCESS             The I2C predefined block read is executed successfully
    @retval EFI_DEVICE_ERROR        I2C transferred is failed.
    @retval EFI_OUT_OF_RESOURCES    Unable to allocate the required memory or buff_size out of range
    @retval EFI_INVALID_PARAMETER   Invalid command value
*/
EFI_STATUS
i2c_predefine_block_read (
    UINT8 cmd, 
    void* buff, 
    UINT8 buff_size, 
    UINT16 cycle_ms, 
    UINT8 max_retry
    );

/*  
    Pre-define block write protocol:
    [ADDR] [0x17] [ADDR] [0x18] [CMD] [ADDR] [DATA_0][DATA_1] ... [DATA_N-1]
    S 0x5B [W] [A] 0x17 [A] S 0x5B [W] [A] 0x18 [A] cmd1 [A] payload[0] [A] payload[N] [NA] [P]
    [S] 0x5B [W] [A] 0x17 [A] S 0x5B [W] [A] 0x18 [A] cmd1 [A] [P]
    @param  cmd                     I2C command value
    @param  buff                    Pointer to the read buffer
    @param  buff_size               Read buffer size

    @retval EFI_SUCCESS             The I2C predefined block write is executed successfully
    @retval EFI_DEVICE_ERROR        I2C transferred is failed.
    @retval EFI_OUT_OF_RESOURCES    Unable to allocate the required memory or buff_size out of range
    @retval EFI_INVALID_PARAMETER   Invalid command value
*/
EFI_STATUS
i2c_predefine_block_write (
    UINT8 cmd, 
    void* buff, 
    UINT8 buff_size
    );

/*  Pre-define block write protocol:
    [ADDR] [0x17] [ADDR] [0x18] [CMD] [ADDR] [DATA_0][DATA_1] ... [DATA_N-1]
    S 0x5B [W] [A] 0x17 [A] S 0x5B [W] [A] 0x18 [A] cmd1 [A] payload[0] [A] payload[N] [NA] [P]
 
    @param  cmd                     I2C command value
    @param  writeBuf                Pointer to the writeBuf
    @param  writeBufSize            write buffer size
    @param  readBuf                 Pointer to the readBuf
    @param  readBufSize             read buffer size
 
    @retval EFI_SUCCESS             The I2C predefined fast read is executed successfully
    @retval EFI_OUT_OF_RESOURCES    Insufficient buffer size or Unable to allocate resources for necessary buff_size.
    @retval EFI_INVALID_PARAMETER   Invalid command value
*/
EFI_STATUS
i2c_predefine_fast_read (
    UINT8 cmd, 
    void* writeBuf, 
    UINT8 writeBufSize ,
    void* readBuf, 
    UINT8 readBufSize
    );
#endif
