/*==============================================================================
  FILE:         rsc_hal.c

  OVERVIEW:     This file implements HAL APIs exposed to rsc driver and performs
                actual HW register read and write.

  DEPENDENCIES: The implementation can be SAW/rsc version specific.

                Copyright (c) 2017, 2021 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================*/

#include "rsc_seq_hal.h"
#include "rsc_hal_hwio.h"
#include "HALhwio.h"
#include "api/systemdrivers/busywait.h"

/*===========================================================================
 *                            INTERNAL VARIABLES
 *==========================================================================*/

/**
 * @brief Volatile variable which will be used to read back rsc register
 *        being written to. This is to ensure that write value actually got
 *        propagated to HW.
 */
volatile uint32 rsc_hal_read_back_val;

/*==========================================================================
 *                             INTERNAL MACROS
 *=========================================================================*/

/* Simple Sequence Macros */
#define RSC_HAL_SIMPLE_SEQ_MEM_CMD3_BMSK  0xff000000
#define RSC_HAL_SIMPLE_SEQ_MEM_CMD3_SHFT  0x18
#define RSC_HAL_SIMPLE_SEQ_MEM_CMD2_BMSK  0xff0000
#define RSC_HAL_SIMPLE_SEQ_MEM_CMD2_SHFT  0x10
#define RSC_HAL_SIMPLE_SEQ_MEM_CMD1_BMSK  0xff00
#define RSC_HAL_SIMPLE_SEQ_MEM_CMD1_SHFT  0x8
#define RSC_HAL_SIMPLE_SEQ_MEM_CMD0_BMSK  0xff
#define RSC_HAL_SIMPLE_SEQ_MEM_CMD0_SHFT  0x0

#define RSC_HAL_SIMPLE_CMD_SEQ_REG_SIZE  4
#define RSC_HAL_SIMPLE_CMD_SIZE  1
#define RSC_HAL_SIMPLE_CMDS_PER_REG  (RSC_HAL_SIMPLE_CMD_SEQ_REG_SIZE/RSC_HAL_SIMPLE_CMD_SIZE)

/* Extended Sequence Macros */
#define RSC_HAL_EXTENTED_SEQ_MEM_CMD1_BMSK  0xffff0000
#define RSC_HAL_EXTENDED_SEQ_MEM_CMD1_SHFT  0x10
#define RSC_HAL_EXTENDED_SEQ_MEM_CMD0_BMSK  0xffff
#define RSC_HAL_EXTENDED_SEQ_MEM_CMD0_SHFT  0x0

#define RSC_HAL_EXTENDED_CMD_SEQ_REG_SIZE  4
#define RSC_HAL_EXTENDED_CMD_SIZE  2
#define RSC_HAL_EXTENDED_CMDS_PER_REG  (RSC_HAL_EXTENDED_CMD_SEQ_REG_SIZE/RSC_HAL_EXTENDED_CMD_SIZE)


/* 32 sequence Macros */
#define RSC_HAL_32_SEQ_MEM_CMD0_BMSK  0xffffffff
#define RSC_HAL_32_SEQ_MEM_CMD0_SHFT  0x0

#define RSC_HAL_32_CMD_SEQ_REG_SIZE  4
#define RSC_HAL_32_CMD_SIZE 4
#define RSC_HAL_32_CMDS_PER_REG  (RSC_HAL_32_CMD_SEQ_REG_SIZE/RSC_HAL_32_CMD_SIZE)
/**
 * @brief Macro to readback an rsc register.
 */
#define RSC_HAL_READBACK_REG(base, reg) \
  (rsc_hal_read_back_val = RSC_HWIO_INX(base, reg))

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define HWIO_INF_POLL_STATUS(_reg_, _field_, _status_, _poll_cnt_) \
  do                                                      \
  {                                                       \
    uint32 __cnt__ = 0;                                       \
    busywait(1);                                          \
    if (__cnt__++ > (_poll_cnt_))                         \
    {                                                     \
      break;                                              \
    }                                                     \
  } while (HWIO_INF(_reg_, _field_) != _status_);

#define HWIO_INFI_POLL_STATUS(_reg_, _idx_, _field_, _status_, _poll_cnt_) \
  do                                                      \
  {                                                       \
    uint32 __cnt__ = 0;                                       \
    busywait(1);                                          \
    if (__cnt__++ > (_poll_cnt_))                         \
    {                                                     \
      break;                                              \
    }                                                     \
  } while (HWIO_INFI(_reg_, _idx_, _field_) != _status_);

#define HWIO_INXF_POLL_STATUS(_base_, _reg_, _field_, _status_, _poll_cnt_) \
  do                                                      \
  {                                                       \
    uint32 __cnt__ = 0;                                       \
    busywait(1);                                          \
    if (__cnt__++ > (_poll_cnt_))                         \
    {                                                     \
      break;                                              \
    }                                                     \
  } while (HWIO_INXF(_base_, _reg_, _field_) != _status_);

#define HWIO_INXFI_POLL_STATUS(_base_, _reg_, _idx_, _field_, _status_, _poll_cnt_) \
  do                                                      \
  {                                                       \
    uint32 __cnt__ = 0;                                       \
    busywait(1);                                          \
    if (__cnt__++ > (_poll_cnt_))                         \
    {                                                     \
      break;                                              \
    }                                                     \
  } while (HWIO_INXFI(_base_, _reg_, _idx_, _field_) != _status_);


/*===========================================================================
 *                            EXTERNAL FUNCTIONS
 *==========================================================================*/
/**
 * <!-- rsc_hal_get_major_ver -->
 *
 * @brief Read the major version from RSC_ID register.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return MAJOR_VER field from RSC_ID register.
 */
uint32 rsc_hal_get_major_ver(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_INFI(TITAN_RSCC_RSC_ID_DRVd, 0, MAJOR_VER);
  else 
	return HWIO_INFI(RSCC_RSC_ID_DRVd, 0, MAJOR_VER);
}

/**
 * <!-- rsc_hal_get_minor_ver -->
 *
 * @brief Read the minor version from RSC_ID register.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return MINOR_VER field from RSC_ID register.
 */
uint32 rsc_hal_get_minor_ver(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_INFI(TITAN_RSCC_RSC_ID_DRVd, 0, MINOR_VER);
  else 
	return HWIO_INFI(RSCC_RSC_ID_DRVd, 0, MINOR_VER);
}

/**
 * <!-- rsc_hal_get_step_ver -->
 *
 * @brief Read the step version from RSC_ID register.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return STEP_VER field from RSC_ID register.
 */
uint32 rsc_hal_get_step_ver(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_INFI(TITAN_RSCC_RSC_ID_DRVd, 0, STEP_VER);
  else 
	return HWIO_INFI(RSCC_RSC_ID_DRVd, 0, STEP_VER);
}

/**
 * <!-- rsc_hal_get_solver_cfg -->
 *
 * @brief Read the solver configuration from SOLVER_CONFIG register.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return Returns SOLVER_CONFIG register value.
 */
uint32 rsc_hal_get_solver_cfg(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_INI(TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd, 0);
  else 
	return HWIO_INI(RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd, 0);
}

/**
 * <!-- rsc_hal_get_num_drvs -->
 *
 * @brief Read the number of DRVs from RSC_CONFIG register.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return Returns NUM_DRV field from RSC_CONFIG register.
 */
uint32 rsc_hal_get_num_drvs(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_INFI(TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd, 0, NUM_DRV);
  else 
	return HWIO_INFI(RSCC_RSC_PARAM_RSC_CONFIG_DRVd, 0, NUM_DRV);
}

/**
 * <!-- rsc_hal_get_num_seq_cmd_words -->
 *
 * @brief Read the number of sequence command words from RSC_CONFIG register.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return Returns NUM_SEQ_CMD_WORDS field from RSC_CONFIG register.
 */
uint32 rsc_hal_get_num_seq_cmd_words(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_INFI(TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd, 0, NUM_SEQ_CMD_WORDS);
  else 
	return HWIO_INFI(RSCC_RSC_PARAM_RSC_CONFIG_DRVd, 0, NUM_SEQ_CMD_WORDS);
}

/**
 * <!-- rsc_hal_get_num_ts_events -->
 *
 * @brief Read the number of timestampable events from RSC_CONFIG register.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return Returns NUM_TS_EVENTS field from RSC_CONFIG register.
 */
uint32 rsc_hal_get_num_ts_events(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_INFI(TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd, 0, NUM_TS_EVENTS);
  else 
	return HWIO_INFI(RSCC_RSC_PARAM_RSC_CONFIG_DRVd, 0, NUM_TS_EVENTS);
}

/**
 * <!-- rsc_hal_get_delay_cntr_bitwidth -->
 *
 * @brief Read the size of delay counter from RSC_CONFIG register.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return Returns DELAY_CNTR_BITWIDTH field from RSC_CONFIG register.
 */
uint32 rsc_hal_get_delay_cntr_bitwidth(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_INFI(TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd, 0, DELAY_CNTR_BITWIDTH);
  else 
	return HWIO_INFI(RSCC_RSC_PARAM_RSC_CONFIG_DRVd, 0, DELAY_CNTR_BITWIDTH);
}

/**
 * <!-- rsc_hal_get_parentchild_cfg -->
 *
 * @brief Read the rent/child configuration from PARENTCHILD_CONFIG register.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return Returns the PARENTCHILD_CONFIG register value.
 */
uint32 rsc_hal_get_parentchild_cfg(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_INI(TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd, 0);
  else 
	return HWIO_INI(RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd, 0);
}

/**
 * <!-- rsc_hal_get_status0 -->
 *
 * @brief Read the RSC_STATUS0 register value.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return Returns the RSC_STATUS0 register value.
 */
uint32 rsc_hal_get_status0(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_INI(TITAN_RSCC_RSC_STATUS0_DRVd, 0);
  else 
	return HWIO_INI(RSCC_RSC_STATUS0_DRVd, 0);
}

/**
 * <!-- rsc_hal_get_status1 -->
 *
 * @brief Read the RSC_STATUS1 register value.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return Returns the RSC_STATUS1 register value.
 */
uint32 rsc_hal_get_status1(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_INI(TITAN_RSCC_RSC_STATUS1_DRVd, 0);
  else 
	return HWIO_INI(RSCC_RSC_STATUS1_DRVd, 0);
}

/**
 * <!-- rsc_hal_get_status2 -->
 *
 * @brief Read the RSC_STATUS2 register value.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return Returns the RSC_STATUS2 register value.
 */
uint32 rsc_hal_get_status2(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_INI(TITAN_RSCC_RSC_STATUS2_DRVd, 0);
  else 
	return HWIO_INI(RSCC_RSC_STATUS2_DRVd, 0);
}

/**
 * <!-- rsc_hal_set_ts_unit_owner -->
 *
 * @brief Configure time stamp unit owner TIMESTAMP_UNIT_OWNER`.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param drv_owner: Owner DRV number.
 */
void rsc_hal_set_ts_unit_owner(rsc_handle handle, uint8 drv_owner)
{
  if(rsc_is_cam(handle))
	HWIO_OUT(TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0, drv_owner);
  else 
	HWIO_OUT(RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0, drv_owner);
}

/**
 * <!-- rsc_hal_enable_ts_unit -->
 *
 * @brief Enable/Disable timestamp unit in TIMESTAMP_UNITm_EN_DRVd register.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param unit_num: Unit number to be enable/disable.
 * @param enable: Boolean value either 1 or 0..
 */
void rsc_hal_enable_ts_unit(rsc_handle handle, uint8 unit_num, boolean enable)
{
  if(rsc_is_cam(handle))
	HWIO_OUTFI2(TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd, 0, unit_num, ENABLE, enable);
  else 
	HWIO_OUTFI2(RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd, 0, unit_num, ENABLE, enable);
}

/**
 * <!-- rsc_hal_get_ts_unit_l -->
 *
 * @brief Read timestamp low data from TIMESTAMP_UNITm_TIMESTAMP_L register.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param unit_num: Unit number to be read.
 *
 * @return Returns TS_DATA_L value from TIMESTAMP_UNITm_TIMESTAMP_L register.
 */
uint32 rsc_hal_get_ts_unit_l(rsc_handle handle, uint8 unit_num)
{
  if(rsc_is_cam(handle))
	return HWIO_INFI2(TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd, 0, unit_num, TS_DATA_L);
  else
	return HWIO_INFI2(RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd, 0, unit_num, TS_DATA_L);  
}

/**
 * <!-- rsc_hal_get_ts_unit_h -->
 *
 * @brief Read timestamp low data from TIMESTAMP_UNITm_TIMESTAMP_H register.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param unit_num: Unit number to be read.
 *
 * @return Returns TS_DATA_H value from TIMESTAMP_UNITm_TIMESTAMP_H register.
 */
uint32 rsc_hal_get_ts_unit_h(rsc_handle handle, uint8 unit_num)
{
  if(rsc_is_cam(handle))
	return HWIO_INFI2(TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd, 0, unit_num, TS_DATA_H);
  else
	return HWIO_INFI2(RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd, 0, unit_num, TS_DATA_H); 
}

/**
 * <!-- rsc_hal_get_ts_overflow -->
 *
 * @brief Read timestamp overflow info from  TIMESTAMP_UNITm_OUTPUT register.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param unit_num: Unit number to be read.
 *
 * @return Returns TS_OVERFLOW value from TIMESTAMP_UNITm_OUTPUT register.
 */
uint32 rsc_hal_get_ts_overflow(rsc_handle handle, uint8 unit_num)
{
  if(rsc_is_cam(handle))
	return HWIO_INFI2(TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd, 0, unit_num, TS_OVERFLOW);
  else
	return HWIO_INFI2(RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd, 0, unit_num, TS_OVERFLOW); 
}

/**
 * <!-- rsc_hal_get_ts_valid -->
 *
 * @brief Read timestamp valid info from  TIMESTAMP_UNITm_OUTPUT register.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param unit_num: Unit number to be read.
 *
 * @return Returns TS_VALID value from TIMESTAMP_UNITm_OUTPUT register.
 */
uint32 rsc_hal_get_ts_valid(rsc_handle handle, uint8 unit_num)
{
  if(rsc_is_cam(handle))
	return HWIO_INFI2(TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd, 0, unit_num, TS_VALID);
  else
	return HWIO_INFI2(RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd, 0, unit_num, TS_VALID);
}

/**
 * <!-- rsc_hal_get_seq_override_start_addr_valid -->
 *
 * @brief Read sequence override start address valid info.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return Returns VALID field from SEQ_OVERRIDE_START_ADDR register.
 */
uint32 rsc_hal_get_seq_override_start_addr_valid(rsc_handle handle)
{
  if(rsc_is_cam(handle))
      return HWIO_INF(TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0, VALID);
  else
	  return HWIO_INF(RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0, VALID);
}

/**
 * <!-- rsc_hal_set_seq_override_start_addr_valid -->
 *
 * @brief Set sequence override start address valid field in SEQ_OVERRIDE_START_ADDR.
 *
 * @param rsc_handle: RSC instance's handle.
 */
void rsc_hal_set_seq_override_start_addr_valid(rsc_handle handle, uint8 valid)
{
  if(rsc_is_cam(handle))
	HWIO_OUTF(TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0, VALID, valid);
  else
	HWIO_OUTF(RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0, VALID, valid); 
}

/**
 * <!-- rsc_hal_set_seq_override_start_addr -->
 *
 * @brief Set sequence override start address in SEQ_OVERRIDE_START_ADDR.
 *
 * @param rsc_handle: RSC instance's handle.
 */
void rsc_hal_set_seq_override_start_addr(rsc_handle handle, uint8 addr)
{
  if(rsc_is_cam(handle))
	HWIO_OUTF(TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0, ADDR, addr);
  else
	HWIO_OUTF(RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0, ADDR, addr); 
}

/**
 * <!-- rsc_hal_set_trigger_seq -->
 *
 * @brief Set this register(RSC_SEQ_OVERRIDE_TRIGGER_DRV0) to trigger the sequencer.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param val: write 0 then write 1 to trigger the sequencer to run
 */
void rsc_hal_set_trigger_seq(rsc_handle handle, uint8 val)
{
  if(rsc_is_cam(handle))
	HWIO_OUT(TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0, val);
  else
	HWIO_OUT(RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0, val); 
}

/**
 * <!-- rsc_hal_set_trigger_start_address -->
 *
 * @brief Set start address in RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0 register.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param addr: Sequence address to trigger.
 */
void rsc_hal_set_trigger_start_address(rsc_handle handle, uint16 addr)
{
  if(rsc_is_cam(handle))
	HWIO_OUT(TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0, addr);
  else
	HWIO_OUT(RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0, addr);  
}

/**
 * <!-- rsc_hal_seq_busy -->
 *
 * @brief Return the value to indicates sequencer is busy are not.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return Returns the value whether sequencer busy are not.
 */
uint32 rsc_hal_seq_busy(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_IN(TITAN_RSCC_RSC_SEQ_BUSY_DRV0);
  else
	return HWIO_IN(RSCC_RSC_SEQ_BUSY_DRV0);
}

/**
 * <!-- rsc_hal_get_seq_program_counter -->
 *
 * @brief Return the last command executed by RSC sequencer.
 *
 * @param rsc_handle: RSC instance's handle.
 *
 * @return Returns program counter value from SEQ_PROGRAM_COUNTER_DRV0 register.
 */
uint16 rsc_hal_get_seq_program_counter(rsc_handle handle)
{
  if(rsc_is_cam(handle))
	return HWIO_IN(TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0);
  else
	return HWIO_IN(RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0);  
}

/**
 * <!-- rsc_hal_config_br_addr -->
 *
 * @brief Configure branch adresses in CFG_BR_ADDR register.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param idx: Branch address index [0..3].
 * @param val: Branch address value.
 */
void rsc_hal_config_br_addr(rsc_handle handle, uint32 idx, uint16 val)
{
  if(rsc_is_cam(handle))
    HWIO_OUTI(TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0, idx, val);
  else  
    HWIO_OUTI(RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0, idx, val);
}

/**
 * <!-- rsc_hal_copy_simple_cmd_seq -->
 *
 * @brief Copy simple command (8bit) sequence to RSC sequencer memory.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param start_adr: Address (command index) to start copying at.
 * @param cmds: Array containing commands to be programmed.
 * @param size: Size of above array
 *
 * @return Number of commands copied to actual RSC HW (In successful call
          it must be equal to size).
 */
uint16 rsc_hal_copy_simple_cmd_seq(rsc_handle handle, uint16 start_adr, rsc_cmd_t* cmds, uint16 size)
{
  // Not implemented on Lanai
  return 0;
}

/**
 * <!-- rsc_hal_copy_extended_cmd_seq -->
 *
 * @brief Copy extended command (8bit) sequence to RSC sequencer memory.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param start_adr: Address (command index) to start copying at.
 * @param cmds: Array containing commands to be programmed.
 * @param size: Size of above array
 *
 * @return Number of commands copied to actual RSC HW (In successful call
          it must be equal to size).
 */
uint16 rsc_hal_copy_extended_cmd_seq(rsc_handle handle, uint16 start_adr, rsc_cmd_t* cmds, uint16 size)
{
  // Not implemented on Lanai
  return 0;
}


/**
 * <!-- rsc_hal_copy_32_cmd_seq -->
 *
 * @brief Copy extended command (32bit) sequence to RSC sequencer memory.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param start_adr: Address (command index) to start copying at.
 * @param cmds: Array containing commands to be programmed.
 * @param size: Size of above array
 *
 * @return Number of commands copied to actual RSC HW (In successful call
          it must be equal to size).
 */
uint16 rsc_hal_copy_32_cmd_seq(rsc_handle handle, uint16 start_adr, rsc_cmd_t* cmds, uint16 size)
{
  uint16 max_cmds     = 0;
  uint16 cmds_copied  = 0;
  uint32 mask         = RSC_HAL_32_SEQ_MEM_CMD0_BMSK;
  uint32 val          = 0;
  uint32 addr         = start_adr;
  uint32 i;
  
  if (rsc_is_cam(handle))
  {	 
    //Number of commands not available for CHN TCS Memory

	 for(i = 0; i < size; i++, addr++)
	 {
		if(0 != cmds_copied)
			HWIO_OUTMI(TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0, ((addr-1)/RSC_HAL_32_CMDS_PER_REG), mask, val);
	
	   val =((uint32)(cmds[i]));
       cmds_copied++;
     }

  	 HWIO_OUTMI(TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0, ((addr-1)/RSC_HAL_32_CMDS_PER_REG), mask, val);
  }
  else
  {
  
     max_cmds = rsc_hal_get_num_seq_cmd_words(handle) * RSC_HAL_32_CMDS_PER_REG;
     if((start_adr >= max_cmds) || ((start_adr + size) > max_cmds))
     {
       return cmds_copied;
     }
	 
	 for(i = 0; i < size; i++, addr++)
     {
	   if(0 != cmds_copied)
       {
		   HWIO_OUTMI(RSCC_SEQ_MEM_m_DRV0, ((addr-1)/RSC_HAL_32_CMDS_PER_REG), mask, val);
	   }
	   val =((uint32)(cmds[i]));
       cmds_copied++;
     }

     HWIO_OUTMI(RSCC_SEQ_MEM_m_DRV0, ((addr-1)/RSC_HAL_32_CMDS_PER_REG), mask, val);
  }

  return cmds_copied;
}

/**
 * <!-- rsc_hal_conf_hidden_tcs_owner -->
 *
 * @brief Set the hidden tcs owner as per drv_id.
 *
 * @param rsc_handle: RSC instance's handle.
 */
void rsc_hal_conf_hidden_tcs_owner(rsc_handle handle, uint8 drv_id)
{
  if (rsc_is_cam(handle))
	HWIO_OUTF(TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0, HIDDEN_TCS_PDC_TIMER_DRV_OWNER, drv_id);
  else
	HWIO_OUTF(RSCC_HIDDEN_TCS_CTRL_DRV0, HIDDEN_TCS_PDC_TIMER_DRV_OWNER, drv_id);
}

/**
 * <!-- rsc_hal_pcie_rsc_force_wake -->
 *
 * @brief Force wake the PCIE RSC to be wake.
 *
 * @param rsc_handle: RSC instance's handle.
 * @param enable: Enable/disable the force wake.
 *
 * Blocks until the RSC is awake. This is to ensure that PCIE h/w (PLIM) is not
 * using the RSC sequencer while the sequences are updated.
 */
 
 /*
void rsc_hal_pcie_rsc_force_wake(rsc_handle handle, boolean enable)
{
  int count = 10;

  HWIO_FORCE_WAKE_OUT(rsc_base, enable);
  if (enable)
    HWIO_INXF_POLL_STATUS(rsc_base, FORCE_WAKE_FSM_STATUS, STATUS, 0, count);
}
*/

/**
 * <!-- rsc_hal_set_hidden_tcs_init -->
 *
 * @brief Set Hidden TCS registers for PDC
 * 
 * Program the PDC start address and PDC timer wakeup match value.
 */
void rsc_hal_set_hidden_tcs_init()
{
  HWIO_OUTI(RSCC_HIDDEN_TCS_CMD0_DATA_DRVd,0, 0x80FFFFFF);
  HWIO_OUTI(RSCC_HIDDEN_TCS_CMD1_DATA_DRVd,0, 0xFFFFFFFF);  
  HWIO_OUT(RSCC_HIDDEN_TCS_CMD2_DATA_DRV0, 0x80000021);
}

