/*=============================================================================

                       MAILBOX CONFIG


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
#include "mbox_internal.h"

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/

/*=============================================================================
                       LOCAL DATA DECLARATIONS
=============================================================================*/

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/

/*=============================================================================

                     GLOBAL FUNCTION DEFINATION
                     
=============================================================================*/

/*=============================================================================
  FUNCTION  mbox_cfg_get_remote_id_from_addr
=============================================================================*/
uint8 mbox_cfg_get_remote_id_from_addr(UINT64 address, mbox_dir_type dir)
{
  uint8 idx;
  UINT64 l_addr, h_addr;
  
  for (idx = 0; idx < MBOX_NUM_REMOTES; idx++)
  {
    if(dir == MBOX_DIR_TX)
    {
  	  l_addr    = mbox_cfgs[idx].tx.base_addr.pa;
  	  h_addr    = l_addr + mbox_cfgs[idx].tx.base_addr.size;
    }
    else
    {
  	  l_addr    = mbox_cfgs[idx].rx.base_addr.pa;
  	  h_addr    = l_addr + mbox_cfgs[idx].rx.base_addr.size;
    }
	
	if((l_addr < address) && (h_addr > address))
	{
	  return idx;
	}
  }
  return MBOX_INVALID_REM_ID;
}

/*=============================================================================
  FUNCTION  mbox_cfg_get_ch_id_from_addr
=============================================================================*/
uint8 mbox_cfg_get_ch_id_from_addr(UINT64 address, mbox_dir_type dir, uint8 remote_id)
{
  uint8 id;
  UINT64 pa;
  UINT32 cmd_offset;
  
  if(dir == MBOX_DIR_TX)
  {
	pa         = mbox_cfgs[remote_id].tx.base_addr.pa;
	cmd_offset = mbox_cfgs[remote_id].tx.cmd_offset;
  }
  else
  {
	pa         = mbox_cfgs[remote_id].rx.base_addr.pa;
	cmd_offset = mbox_cfgs[remote_id].rx.cmd_offset;
  }
  
  if(address >= (pa + cmd_offset))
  {
    cmd_offset = (uint32)(address - (pa + cmd_offset));
    id = (uint8)(cmd_offset / MBOX_CMD_REG_SIZE);
  }
  else
  {
	return MBOX_INVALID_CH_ID;
  }

  if((dir == MBOX_DIR_TX) & (id >= MBOX_IPC_NUM_TX_CHS))
  {
	return MBOX_INVALID_CH_ID;
  }
  
  if((dir == MBOX_DIR_RX) & (id >= MBOX_IPC_NUM_RX_CHS))
  {
	return MBOX_INVALID_CH_ID;
  }
  
  return id;
}

/*=============================================================================
  FUNCTION  mbox_cfg_init
=============================================================================*/
mbox_cfg_type *mbox_cfg_init(void)
{
  uint8 idx;
  
  for (idx = 0; idx < MBOX_NUM_REMOTES; idx++)
  {
    
    if (mbox_cfgs[idx].tx.base_addr.sec_access)
    {
      mbox_cfgs[idx].tx.base_addr.va = (void *)(uintptr_t)mbox_cfgs[idx].tx.base_addr.pa;
    }
    else
    {
      mbox_cfgs[idx].tx.base_addr.va = mbox_os_io_region_map(mbox_cfgs[idx].tx.base_addr.pa,
                                                             mbox_cfgs[idx].tx.base_addr.size);
    }
    
    if (mbox_cfgs[idx].tx.base_addr.va == NULL)
    {
      MBOX_OS_LOG_FATAL("mbox_cfg_init: TX IO mapping failed! remote:%d, addr=0x%lx, size=0x%lx.",
              idx, mbox_cfgs[idx].tx.base_addr.pa, mbox_cfgs[idx].tx.base_addr.size);
    }

    if (mbox_cfgs[idx].rx.base_addr.sec_access)
    {
      mbox_cfgs[idx].rx.base_addr.va = (void *)(uintptr_t)mbox_cfgs[idx].rx.base_addr.pa;
    }
    else
    {
      mbox_cfgs[idx].rx.base_addr.va = mbox_os_io_region_map(mbox_cfgs[idx].rx.base_addr.pa,
                                                             mbox_cfgs[idx].rx.base_addr.size);
    }
    
    if (mbox_cfgs[idx].rx.base_addr.va == NULL)
    {
      MBOX_OS_LOG_FATAL("mbox_cfg_init: RX IO mapping failed! remote:%d, addr=0x%lx, size=0x%lx.",
              idx, mbox_cfgs[idx].rx.base_addr.pa, mbox_cfgs[idx].rx.base_addr.size);
    }
  }
  
  return mbox_cfgs;
}

