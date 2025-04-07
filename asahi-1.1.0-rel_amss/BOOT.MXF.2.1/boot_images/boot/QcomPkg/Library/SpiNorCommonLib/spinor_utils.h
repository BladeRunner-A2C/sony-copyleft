#ifndef __SPINOR_UTILS__H
#define __SPINOR_UTILS__H
/**********************************************************************
 * spinor_utils.h
 *
 * This file provides definitions for the spinor support functions
 *
 * Copyright (c) 2017-2020,2022,2023 Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************/
/*======================================================================

                        EDIT HISTORY FOR MODULE


when        who  what, where, why
----------  ---  -----------------------------------------------
2022-11-18  sc   Update driver to utilize spinor handle.
2020-07-23  wek  Use the same error codes on all SPI-NOR dirver files.
2019-03-15  wek  Update the handle validate functions
2018-07-31  wek  Add Access control to write/erase
2017-05-25  md   Initial Release based on SPI-NOR driver from Quartz.

==================================================================*/
#include "spinor_api.h"
#include "spinor_core.h"

/* Check for integer overflows */
#define INT_OVERFLOW(x,y) (x + y < x)

/**********************************************************
 * Logs error codes. Circular log buffer. The err_index can be used
 * as the index to the most recent error code
 *
 * @param spinor_err_log [IN]
 *   log buffer
 *
 * @param code [IN]
 *   Error code
 *
 **********************************************************/
void spinor_log (spinor_logs *spinor_err_log, uint16 code);

/**********************************************************
 * Flash delay in uint of micro seconds
 *
 * @param usec_delay [IN]
 *   Number of micro seconds delay.
 *
 **********************************************************/
void spinor_udelay (uint32 usec_delay);

/**********************************************************
 * Sends SPI command to read register
 *
 * @handle [IN]
 *   SPINOR interface handle
 * 
 * @reg_opcode [IN]
 *   Register Opcode
 *
 * @len [IN]
 *   How many bytes to read
 *
 * @reg_value [OUT]
 *   Register content returned
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS read_spi (spinor_handle_t handle, uint8 reg_opcode, uint8 len, uint8 *reg_value);

/**********************************************************
 * Sends SPI command to write register
 *
 * @handle [IN]
 *   SPINOR interface handle
 * 
 * @reg_addr [IN]
 *   Register Opcode
 *
 * @len [IN]
 *   How many bytes to write
 *
 * @reg_value [OUT]
 *   Register Value
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS write_spi (spinor_handle_t handle, uint8 reg_opcode, uint8 len, uint8 *reg_value);

/**********************************************************
 * Look up table to find the spinor config info.
 *
 * @param handle [IN]
 *   SPINOR interface handle
 *
 * @param spinor_config_tbl [IN]
 *   Table containing config data for supported spinor devices
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_device_lookup (spinor_handle_t handle, void *spinor_config_tbl);

/**********************************************************
 * Validates the input parameters for spinor Erase
 *
 * @param parti_handle [IN]
 *   SPINOR interface handle
 *
 * @param start_block [IN]
 *   Block offset from the start of the partition/image.
 *
 * @param block_count [IN]
 *   Number of blocks to perform the erase operations.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_erase_parameters_validation (uint8 *parti_handle,
                uint32 start_block, uint32 block_count);

/**********************************************************
 * Validates the Read/Write input parameters
 *
 * @param parti_handle [IN]
 *   SPINOR interface handle
 *
 * @param byte_offset [IN]
 *   Byte offset from the start of the partition/image.
 *
 * @param byte_count [IN]
 *   Number of bytes to perform the read/write operations.
 *
 * @buffer [IN]
 *   Data buffer for the read/write operation.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_rw_parameters_validation (uint8 *parti_handle,
                uint32 byte_offset, uint32 byte_count, void *buffer);

/**********************************************************
 * Verifies if access is allowed to the given region.
 *
 * @param handle [IN]
 *   SPINOR interface handle
 *
 * @param byte_offset [IN]
 *   First block of the region to access.
 *
 * @param block_count [IN]
 *   Number of blocks to be accessed.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_io_access_validation (spinor_handle_t handle, uint32 start_block, uint32 block_count);

/**********************************************************
 * Verifies if access is allowed to the given region.
 *
 * @param handle [IN]
 *   SPINOR interface handle
 *
 * @param byte_offset [IN]
 *   Byte offset from the start of the access region.
 *
 * @param byte_count [IN]
 *   Number of bytes to be accessed.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_io_byte_access_validation (spinor_handle_t handle, uint32 byte_offset, uint32 byte_count);

#endif /* __SPINOR_UTILS__H */
