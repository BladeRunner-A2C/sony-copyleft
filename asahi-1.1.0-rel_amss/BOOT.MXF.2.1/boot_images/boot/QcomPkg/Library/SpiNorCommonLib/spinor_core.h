#ifndef __SPINOR_CORE__H
#define __SPINOR_CORE__H
/**********************************************************************
 * spinor_core.h
 *
 * This file provides definitions for the spinor support functions
 *
 * Copyright (c) 2017,2019,2020,2022,2023 Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************/
/*======================================================================

                        EDIT HISTORY FOR MODULE


when        who  what, where, why
----------  ---  -----------------------------------------------
2023-03-20  sc   Remove redundant API to use DT for spinor frequency.
2022-11-14  sc   Add support for multiple spinor slots
2022-06-29  sc   Add Device Tree support
2020-07-23  wek  Use the same error codes on all SPI-NOR dirver files.
2020-04-08  wek  Add SFDP support, Add option for 4-byte address.
2019-03-12  wek  Expose the SPI power state to upper layers.
2017-05-25  md   Initial Release based on SPI-NOR driver from Quartz.


==================================================================*/
#include "spinor_api.h"
#include "spinor_init_config.h"
#include <DTBExtnLib.h>

/* SFDP's Dword 15th Bits[20:22]. QER Field.*/
#define  ENABLE_QUAD_MODE_0  0x0
#define  ENABLE_QUAD_MODE_1  0x1
#define  ENABLE_QUAD_MODE_2  0x2
#define  ENABLE_QUAD_MODE_3  0x3
#define  ENABLE_QUAD_MODE_4  0x4
#define  ENABLE_QUAD_MODE_5  0x5
#define  ENABLE_QUAD_MODE_6  0x6
#define  ENABLE_QUAD_MODE_7  0x7

#define PROG_ERASE_WRITE_BUSY_BMSK   0x01
#define READ_STATUS_BUSY_MASK        0x01
#define STATUS_WR_EN_MASK            0x02 /* Write Enable Latch status */

#define READ_SDR_1_1_1_MODE       0
#define READ_SDR_1_1_4_MODE       1
#define READ_SDR_1_4_4_MODE       2
#define READ_SDR_4_4_4_MODE       3
#define READ_DDR_1_1_1_MODE       4
#define READ_DDR_1_2_2_MODE       5
#define READ_DDR_1_4_4_MODE       6
#define READ_DDR_1_8_8_MODE       7

#define WRITE_SDR_1_1_1_MODE       0
#define WRITE_SDR_1_1_4_MODE       1
#define WRITE_SDR_1_4_4_MODE       2
#define WRITE_SDR_1_1_8_MODE       3
#define WRITE_SDR_1_8_8_MODE       4

#define READ_STATUS_CMD       0x05
#define READ_STATUS_2_CMD     0x3F
#define WRITE_STATUS_2_CMD    0x3E
#define WRITE_ENABLE_CMD      0x06
#define READ_ID_CMD           0x9F
#define READ_SFDP_CMD         0x5A
#define READ_CFG1_CMD         0x35        /* Micron/Spansion: Enable QE */
#define READ_FLAG_STATUS_CMD  0x70
#define READ_SECURITY_CMD     0x2B
#define WRITE_STATUS_CMD      0x01
#define ENTER_4B_ADDR_CMD     0xB7
#define READ_CFG_REG_CMD      0x15

#define MAX_PAGE_PER_WRITE    1
#define WRITE_TIMEOUT         5000000   /*usec unit */
#define ERASE_TIMEOUT         25000000   /*usec unit */
#define READ_TIMEOUT          5000000   /*usec unit */
#define READ_STATUS_TIMEOUT   5000000
#define READ_STATUS_POLLING_USEC  20

#define DEVICE_ID_LEN_IN_BYTES   3

#define BIT_0  0x1
#define BIT_1  0x2
#define BIT_2  0x4
#define BIT_3  0x8
#define BIT_4  0x10
#define BIT_5  0x20
#define BIT_6  0x40
#define BIT_7  0x80

/*Default 4KB Block, 256 bytes per page */
#define PAGES_PER_BLOCK  16
#define PAGE_SIZE_IN_BYTES   256
#define BLOCK_SIZE_IN_BYTES  4096

/* Check for integer overflows */
#define INT_OVERFLOW(x,y) (x + y < x)

#define SPINOR_16MB_IN_BYTES   0x1000000
#define SPINOR_16MB_IN_BLOCKS  0x1000
#define SPINOR_DEVICE_MEM_START_ADDR 0x000

/* Error Check operation types */
#define ERASE_OPERATION   1
#define WRITE_OPERATION   2

#define DEFAULT_QSPI_SDR_8MHZ   8000
#define SPINOR_QSPI_SDR_96MHZ    96000
#define SPINOR_QSPI_DDR_64MHZ    64000

/* Maximum number of spinor slots */
#define SPINOR_MAX_SLOTS  2
#define SPINOR_SLOT_0  0
#define SPINOR_SLOT_1  1

#define SPINOR_ERR_LOG_SIZE  16

/* Flash Error Log */
typedef struct
{
  uint8  spinor_err_index;
  uint16 spinor_err_codes[SPINOR_ERR_LOG_SIZE];
  uint32 read_unaligned_count;
  uint32 write_unaligned_count;
  uint32 spinor_status;
  uint32 vendor_status;
} spinor_logs;

enum enter_4byte_addr_mode
{
  ADDR_4BYTE_NOT_SUPPORTED,
  ADDR_4BYTE_MODE_1, /* issue instruction B7h (preceding write enable not required) */
  ADDR_4BYTE_MODE_2, /* issue write enable instruction 06h, then issue instruction B7h */
  ADDR_4BYTE_MODE_3, /* 8-bit volatile extended address register used to define
                        A[31:24] bits.  Read with instruction C8h.  ... */
  ADDR_4BYTE_MODE_4, /* 8-bit volatile bank register used to define A[30:A24]
                        bits. MSB (bit[7]) is used to enable/disable 4-byte ... */
  ADDR_4BYTE_MODE_5, /* A 16-bit nonvolatile configuration register controls ... */
  ADDR_4BYTE_MODE_6, /* Supports dedicated 4-Byte address instruction set. */
  ADDR_4BYTE_MODE_7, /* Always operates in 4-Byte address mode */
  ADDR_4BYTE_MODE_MAX,
};

/* Device Tree Values */
#define DT_PATH_LEN          48
#define ERASE_POLL_MS        1
#define WRITE_POLL_US        100
#define DEVICE_ID            0xFACEECAF


typedef struct
{
  boolean nor_init_done;
  uint32  erase_timeout;
  uint32  write_timeout;
  uint32  read_status_timeout;
  uint16  status_polling_usec;
  boolean dma_enable;
  uint8   ref_count;
  uint32  slot_no;
  boolean in_use;
  spinor_logs debug_log;
  enum enter_4byte_addr_mode addr_mode_4byte;
  spinor_config_data *config_data;
}spinor_drv_info;

#ifndef TRUE
#define TRUE   1   /* Boolean true value. */
#endif

#ifndef FALSE
#define FALSE  0   /* Boolean false value. */
#endif

#ifndef NULL
#define NULL  0
#endif

/**********************************************************
 * Look up RAM table to find the spinor config info.
 * Save the data in spinor's RAM AON
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @param spinor_config_tbl [IN]
 *   RAM table containing config data for supported spinor devices
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_device_lookup (spinor_handle_t handle, void *spinor_config_tbl);

/**********************************************************
 * Issues WRITE_ENABLE command to SPI NOR device
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @result [OUT]
 *   returns the Read Status Register content after WRITE_ENABLE
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS write_enable (spinor_handle_t handle, uint8 *result);

/**********************************************************
 * Enables Quad Mode
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @qer_mode [IN]
 *   Mode is queried from the sfdp's 15th DWORD. Depending on the mode,
 *   different registers are used to enable the Quad Mode.
 *   Refer to the Standard JEDEC 216A Section 6.4.15 for details.
 *
 * @reg_value [OUT]
 *   Register Value
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS enable_quad_mode (spinor_handle_t handle, uint8 qer_mode);

/**********************************************************
 * Sets 4-byte address mode
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS set_4byte_address_mode(spinor_handle_t handle);

/**********************************************************
 * Read the Flash device ID
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @param device_id [IN/OUT]
 *   Flash NOR Device ID
 *
 * @param device_id_len [IN]
 *   Number of bytes to read
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_core_read_device_id (spinor_handle_t handle, void *device_id, uint8 device_id_len);

/**********************************************************
 * Erases given spinor blocks
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @param start_block [IN]
 *   A starting block for a number of blocks to erase.
 *
 * @param block_count [IN]
 *   Number of blocks to erase
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_core_erase (spinor_handle_t handle, uint32 start_block, uint32 block_count);

/**********************************************************
 * Checks Status of the operation by reading the Status register
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @result [OUT]
 *   Status Register Value
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS check_operation_status (spinor_handle_t handle, uint8 *result);

/**********************************************************
 * De-initializes the spinor nor driver
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_core_deinit (spinor_handle_t handle);

/**********************************************************
 * Erases given spinor blocks
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @param start_block [IN]
 *   A starting block for a number of blocks to erase.
 *
 * @param block_count [IN]
 *   Number of blocks to erase
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_core_erase(spinor_handle_t handle, uint32 start_block, uint32 block_count);

/**********************************************************
 * Erases given spinor blocks in bulk erase blocks size (32KB, 64KB, 512KB ect.
 * or whichever the memory device supports)
 * The following requirments must be met.
 * - The start_block must align to the bulk erase blocks size.
 * - The block_count must align to the bulk erase blocks size.
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @param start_block [IN]
 *   A starting block for a number of blocks to erase.
 *
 * @param block_count [IN]
 *   Number of blocks to erase
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_core_erase_bulk(spinor_handle_t handle, uint32 start_block, uint32 block_count);

/**********************************************************
 * Allows write data to the spinor.
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @param address [IN]
 *   Physical location of the start of the write
 *
 * @param byte_count [IN]
 *   Number of bytes to write data.
 *
 * @buffer [IN]
 *   Data buffer for spinor write operation.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_core_write(spinor_handle_t handle, uint32 address, uint32 byte_count, uint8 *buffer);

/**********************************************************
 * Allows read data from the spinor.
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @param address [IN]
 *   Physical location of the start of the read
 *
 * @param byte_count [IN]
 *   Number of bytes to read data.
 *
 * @buffer [IN]
 *   Data buffer for spinor write operation.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_core_read(spinor_handle_t handle, uint32 address, uint32 byte_count, uint8 *buffer);

/**********************************************************
 * Initializes the spinor driver info structure.
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @param spinor_core_config_data [IN]
 *   config data for the spinor device
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 *********************************************************/
SPINOR_STATUS spinor_drv_info_init (spinor_handle_t handle, spinor_config_data *spinor_core_config_data);

/**********************************************************
 * Initializes the spinor controller HW
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_controller_init (spinor_handle_t handle);

/**********************************************************
 * Initializes the spinor driver.
 * Invokes spinor_core_init() to initialize spinor sub modules
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @param spinor_core_config_data [IN]
 *   config data for the spinor device
 *
 * @param spinor_config_table [IN]
 *   RAM table containing config data for supported spinor devices
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_init(spinor_handle_t handle, void *spinor_config_table, spinor_config_data *spinor_core_config_data);

/**********************************************************
 * De-initializes the spinor driver.
 * Free up resources used by the spinor driver
 *
 * @param handle [IN]
 *   SPINOR interface handle
 * 
 * @return int [OUT]
 *   Result of the operation.
 *
**********************************************************/
SPINOR_STATUS spinor_deinit (spinor_handle_t handle);

/**********************************************************
 * Turn on the SPI clock to operate at max performance.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
**********************************************************/
SPINOR_STATUS spinor_core_perf_mode(void);

/**********************************************************
 * Turn off the SPI clock to save power.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
**********************************************************/
SPINOR_STATUS spinor_core_power_saving_mode(void);

/**********************************************************
 * Update spinor DT structure with default config.
 *
 * @result cfg [OUT]
 *   spinor DT structure
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 *********************************************************/
SPINOR_STATUS spinor_get_dt_default_config (spinor_handle_t handle);

/**********************************************************
 * Update spinor driver info structure with device tree configs.
 *
 * @result cfg [OUT]
 *   spinor driver info to be updated based on DT configs
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 *********************************************************/
SPINOR_STATUS spinor_get_dt_config (spinor_handle_t handle);

#endif /* __SPINOR_CORE__H */
