/*=============================================================================

                       MAILBOX DRV


 Copyright (c) 2022-2023 QUALCOMM Technologies, Incorporated.
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
#include "mbox_internal.h"
#include "mbox_cfg.h"

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/

/*=============================================================================
                       LOCAL DATA DEFINATION
=============================================================================*/
static mbox_cfg_type *mbox_drv_cfg = NULL;

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/


/*=============================================================================

                     LOCAL FUNCTION DEFINATION
                     
=============================================================================*/

/*=============================================================================
  FUNCTION  mbox_drv_reg_read
=============================================================================*/
static void mbox_drv_reg_read
(
  mbox_base_addr_type *base_addr,
  uint32              reg_offset,
  uint32              *val
)
{
  boolean status;

  if (base_addr->sec_access)
  {
    status = mbox_os_scm_read(base_addr->pa + reg_offset, val);
  }
  else
  {
    status = mbox_os_reg_read(base_addr->va + reg_offset, val);
  }
  
  if (status == FALSE)
  {
    MBOX_OS_LOG_FATAL("mbox_drv_reg_read: Register read failed sec_access:%d, "
          "pa_base:0x%X, reg_offset:0x%X\n", base_addr->sec_access, 
          base_addr->pa, reg_offset);
    *val = 0;
  }
}

/*=============================================================================
  FUNCTION  mbox_drv_reg_write
=============================================================================*/
static void mbox_drv_reg_write
(
  mbox_base_addr_type *base_addr,
  uint32              reg_offset,
  uint32              val
)
{
  boolean status;
  
  if (base_addr->sec_access)
  {
    status = mbox_os_scm_write(base_addr->pa + reg_offset, val);
  }
  else
  {
    status = mbox_os_reg_write(base_addr->va + reg_offset, val);
  }
  
  if (status == FALSE)
  {
    MBOX_OS_LOG_FATAL("mbox_drv_reg_write: Register write failed sec_access:%d, "
          "pa_base:0x%X, reg_offset:0x%X, val:0x%X\n", 
          base_addr->sec_access, base_addr->pa, reg_offset, val);
  }
}

/*=============================================================================
  FUNCTION  mbox_drv_reg_read64
=============================================================================*/
static void mbox_drv_reg_read64
(
  mbox_base_addr_type *base_addr,
  uint32              reg_offset,
  uint64              *val
)
{
  mbox_drv_reg_read(base_addr, reg_offset, (uint32*)val);
  mbox_drv_reg_read(base_addr, reg_offset + 4, ((uint32*)val) + 1);
}

/*=============================================================================
  FUNCTION  mbox_drv_reg_write64
=============================================================================*/
static void mbox_drv_reg_write64
(
  mbox_base_addr_type *base_addr,
  uint32              reg_offset,
  uint64              val
)
{
  mbox_drv_reg_write(base_addr, reg_offset, (uint32)val);
  mbox_drv_reg_write(base_addr, reg_offset + 4, (uint32)(val >> 32));
}

/*=============================================================================
  FUNCTION  mbox_drv_isr
=============================================================================*/
static void mbox_drv_isr(void *priv)
{
  mbox_rx_cfg_type *rx;
  uint8 remote_id = (uint8)(uintptr_t)priv;
  uint64 intr_status;
  uint8 idx;
  
  if (remote_id >= MBOX_NUM_REMOTES)
  {
    return;
  }
  
  rx = &mbox_drv_cfg[remote_id].rx;
  
  MBOX_OS_LOG_DBG("mbox_drv_isr: remote_id:%d.", remote_id);

  /* Read status and clear status */
  mbox_drv_reg_read64(&rx->base_addr, rx->stat_offset, &intr_status);
  mbox_drv_reg_write64(&rx->base_addr, rx->clear_offset, intr_status);
  
  MBOX_OS_LOG_DBG("mbox_drv_isr: remote_id:%d, intr_status:0x%X.", remote_id, intr_status);

  for (idx = 0; idx < 47; idx++)
  {
    uint32 message = 0;
    
    if (intr_status & ((uint64)1 << idx))
    {
      /* Due to H/W bug, only _1 register used for the 32-bit data */  
      mbox_drv_reg_read(&rx->base_addr, rx->cmd_offset + (idx * 8) + 4, &message);
      mbox_ipc_ch_rx_cb(remote_id, idx, message);
    }
  }

  mbox_os_intr_done(&rx->irq);
}

/*=============================================================================

                     GLOBAL FUNCTION DEFINATION
                     
=============================================================================*/

/*=============================================================================
  FUNCTION  mbox_drv_init
=============================================================================*/
mbox_status_type mbox_drv_init(void)
{
  boolean status;
  uint8 remote_idx;
  
  MBOX_OS_LOG_DBG("mbox_drv_init: Status:%d.", 0);

  mbox_drv_cfg = mbox_cfg_init();
  if (mbox_drv_cfg == NULL)
  {
    MBOX_OS_LOG_ERR("mbox_drv_init: Config failed status:%d.", MBOX_STATUS_DRV_FAILURE);
    return MBOX_STATUS_DRV_FAILURE;
  }
  
  for (remote_idx = 0; remote_idx < MBOX_NUM_REMOTES; remote_idx++)
  {
    mbox_rx_cfg_type *rx = &mbox_drv_cfg[remote_idx].rx;
    
    /* Disable all RXs */
    mbox_drv_reg_write64(&rx->base_addr, rx->en_offset, 0);

    /* Clear pending status */
    mbox_drv_reg_write64(&rx->base_addr, rx->clear_offset, 0);
    
    /* Clear the mapping */
    mbox_drv_reg_write64(&rx->base_addr, rx->map_offset, 0);

    /* Register interrupt 
	   TODO: if registering with same vector number fatals or ignores */
    status  = mbox_os_intr_reg(&rx->irq, mbox_drv_isr, (void *)(uintptr_t)remote_idx);
    if (status == FALSE)
    {
      MBOX_OS_LOG_ERR("mbox_drv_init: Interrupt register remote_idx:%d", remote_idx);
    }

    /* Configure mapping */
    mbox_drv_reg_write64(&rx->base_addr, rx->map_offset, MBOX_RX_CMND_MASK);
  }

  MBOX_OS_LOG_DBG("mbox_drv_init: Completed status:%d.", 0);
  return MBOX_STATUS_SUCCESS;
}

/*=============================================================================
  FUNCTION  mbox_drv_ch_enable
=============================================================================*/
mbox_status_type mbox_drv_ch_enable(uint8 remote_id, uint8 ch_id)
{
  mbox_rx_cfg_type *rx;
  uint64 en_reg;
  
  rx = &mbox_drv_cfg[remote_id].rx;
  
  mbox_drv_reg_read64(&rx->base_addr, rx->en_offset, &en_reg);
  en_reg |= (uint64)1 << ch_id;
  mbox_drv_reg_write64(&rx->base_addr, rx->en_offset, en_reg);

  return MBOX_STATUS_SUCCESS;
}

/*=============================================================================
  FUNCTION  mbox_drv_ch_disable
=============================================================================*/
mbox_status_type mbox_drv_ch_disable(uint8 remote_id, uint8 ch_id)
{
  mbox_rx_cfg_type *rx;
  uint64 en_reg;
  
  rx = &mbox_drv_cfg[remote_id].rx;
  
  mbox_drv_reg_read64(&rx->base_addr, rx->en_offset, &en_reg);
  en_reg &= ~((uint64)1 << ch_id);
  mbox_drv_reg_write64(&rx->base_addr, rx->en_offset, en_reg);
  
  return MBOX_STATUS_SUCCESS;
}

/*=============================================================================
  FUNCTION  mbox_drv_ch_tx
=============================================================================*/
mbox_status_type mbox_drv_ch_tx(uint8 remote_id, uint8 ch_id, uint32 message)
{
  mbox_tx_cfg_type *tx;
  
  tx = &mbox_drv_cfg[remote_id].tx;
  
  /* Due to H/W bug, we're writing only _1 register with the 32-bit data */  
  mbox_drv_reg_write(&tx->base_addr, tx->cmd_offset + (ch_id * 8) + 4, message);

  MBOX_OS_LOG_DBG("mbox_drv_ch_tx: Completed remote_id:%d, ch_id:%d, message:0x%X.", remote_id, ch_id, message);
  return MBOX_STATUS_SUCCESS;
}