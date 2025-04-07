#ifndef MBOX_CFG_H
#define MBOX_CFG_H
/*=============================================================================

                       MAILBOX CFG


 Copyright (c) 2023 QUALCOMM Technologies, Incorporated.
 All rights reserved.
 Qualcomm Confidential and Proprietary

=============================================================================*/

/*=============================================================================
                         EDIT HISTORY FOR FILE
$Header:  $
=============================================================================*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include "mbox_os_utils.h"

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/
#define MBOX_NUM_REMOTES		   4
#define MBOX_IPC_NUM_CHS          16
#define MBOX_IPC_NUM_TX_CHS       16
#define MBOX_IPC_NUM_RX_CHS       64
#define MBOX_CMD_REG_SIZE          8

#define MBOX_INVALID_CH_ID         0x000000FF
#define MBOX_INVALID_REM_ID        0x000000FF
#define MBOX_RX_CMND_MASK          0xFFFFFFFFFFFFFFFF

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/
typedef struct
{
  uint64 pa;           /* */
  uint8  *va;          /* */
  uint8  sec_access;   /* */
  uint32 size;
} mbox_base_addr_type;

typedef struct
{
  mbox_base_addr_type base_addr;
  uint32              idr_offset;   /* idr reg offset */
  uint32              cmd_offset;   /* cmnd reg offset */
} mbox_tx_cfg_type;

typedef struct
{
  mbox_base_addr_type base_addr;
  uint32              idr_offset;   /* idr reg offset */
  uint32              cmd_offset;   /* cmnd reg offset */
  uint32              map_offset;   /* Offset of where the MAP registers start, from IDR */
  uint32              stat_offset;  /* Offset of where the STATUS registers start, from IDR */
  uint32              clear_offset; /* Offset of where the CLEAR registers start, from IDR */
  uint32              en_offset;    /* Offset of EN (ENable) registers from IDR */
  mbox_os_intr_type   irq;          /* Interrupt vector */
} mbox_rx_cfg_type;

typedef struct
{
  uint32           max_chs;
  mbox_tx_cfg_type tx;
  mbox_rx_cfg_type rx;
} mbox_cfg_type;

typedef struct{
  char     *ch_name;
  uint8    tx_ch_id;
  uint8    rx_ch_id;
}mbox_ch_cfg_type;

typedef enum {
  MBOX_DIR_TX = 0,
  MBOX_DIR_RX = 1
}mbox_dir_type;

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/
extern mbox_ch_cfg_type mbox_ipc_channels[MBOX_NUM_REMOTES][MBOX_IPC_NUM_CHS];
extern mbox_cfg_type mbox_cfgs[MBOX_NUM_REMOTES];

/*=============================================================================

                     PUBLIC FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
  FUNCTION  mbox_cfg_init
=============================================================================*/
mbox_cfg_type *mbox_cfg_init(void);
void mbox_cfg_get_mask(uint32 remote_id, uint64 *ch_mask);
uint8 mbox_cfg_get_ch_id_from_addr(UINT64 address, mbox_dir_type dir, uint8 remote_id);
uint8 mbox_cfg_get_remote_id_from_addr(UINT64 address, mbox_dir_type dir);
#endif /* MBOX_CFG_H */
