/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
 
// SPDX-License-Identifier: ISC
/*
 * Copyright(c) 2018-2020 The Linux Foundation.All rights reserved.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 26/9/21   zxue		handle irq with budget
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <qdf/qbase.h>
#include <qdf/sk_buff.h>
#include <qdf/pci.h>
#include "mhi.h"
#include "internal.h"

/* EFI access offset directly */
#define MHI_BASE_OFFSET(B) (u32)((u8*)(B) - (u8*)0)

int __must_check mhi_read_reg(struct mhi_controller *mhi_cntrl,
			      void __iomem *base, u32 offset, u32 *out)
{
	u32 tmp = pci_read32(mhi_cntrl->cntrl_dev, MHI_BASE_OFFSET(base) + offset);

	/* If there is any unexpected value, query the link status */
	if (PCI_INVALID_READ(tmp) &&
	    mhi_cntrl->link_status(mhi_cntrl))
		return -EIO;

	*out = tmp;
	return 0;
}

int __must_check mhi_read_reg_field(struct mhi_controller *mhi_cntrl,
				    void __iomem *base, u32 offset,
				    u32 mask, u32 shift, u32 *out)
{
	u32 tmp;
	int ret;

	ret = mhi_read_reg(mhi_cntrl, base, offset, &tmp);
	if (ret)
		return ret;

	*out = (tmp & mask) >> shift;
	return 0;
}

void mhi_write_reg(struct mhi_controller *mhi_cntrl, void __iomem *base,
		   u32 offset, u32 val)
{
    pci_write32(mhi_cntrl->cntrl_dev, MHI_BASE_OFFSET(base) + offset, val);
}

void mhi_write_reg_field(struct mhi_controller *mhi_cntrl, void __iomem *base,
			 u32 offset, u32 mask, u32 shift, u32 val)
{
	int ret;
	u32 tmp;

	ret = mhi_read_reg(mhi_cntrl, base, offset, &tmp);
	if (ret)
		return;

	tmp &= ~mask;
	tmp |= (val << shift);
	mhi_write_reg(mhi_cntrl, base, offset, tmp);
}

void mhi_memset_reg(struct mhi_controller *mhi_cntrl,
    void __iomem *base, u32 offset, u8 c, u32 size)
{
    u32 dest = MHI_BASE_OFFSET(base) + offset;

    while (size--) {
        pci_write8(mhi_cntrl->cntrl_dev, dest, c);
        dest++;
   }
}

void mhi_write_db(struct mhi_controller *mhi_cntrl, void __iomem *db_addr,
		  dma_addr_t db_val)
{
	mhi_write_reg(mhi_cntrl, db_addr, 4, upper_32_bits(db_val));
	mhi_write_reg(mhi_cntrl, db_addr, 0, lower_32_bits(db_val));
}


void mhi_db_brstmode(struct mhi_controller *mhi_cntrl,
		     struct db_cfg *db_cfg,
		     void __iomem *db_addr,
		     dma_addr_t db_val)
{
	if (db_cfg->db_mode) {
		db_cfg->db_val = db_val;
		mhi_write_db(mhi_cntrl, db_addr, db_val);
		db_cfg->db_mode = 0;
	}
}

void mhi_db_brstmode_disable(struct mhi_controller *mhi_cntrl,
			     struct db_cfg *db_cfg,
			     void __iomem *db_addr,
			     dma_addr_t db_val)
{
	db_cfg->db_val = db_val;
	mhi_write_db(mhi_cntrl, db_addr, db_val);
}

void mhi_ring_er_db(struct mhi_event *mhi_event)
{
	struct mhi_ring *ring = &mhi_event->ring;

	mhi_event->db_cfg.process_db(mhi_event->mhi_cntrl, &mhi_event->db_cfg,
				     ring->db_addr, *ring->ctxt_wp);
}

void mhi_ring_cmd_db(struct mhi_controller *mhi_cntrl, struct mhi_cmd *mhi_cmd)
{
	dma_addr_t db;
	struct mhi_ring *ring = &mhi_cmd->ring;

	db = ring->iommu_base + ((u8 *)ring->wp - (u8 *)ring->base);
	*ring->ctxt_wp = db;
	mhi_write_db(mhi_cntrl, ring->db_addr, db);
}

void mhi_ring_chan_db(struct mhi_controller *mhi_cntrl,
		      struct mhi_chan *mhi_chan)
{
	struct mhi_ring *ring = &mhi_chan->tre_ring;
	dma_addr_t db;

	db = ring->iommu_base + ((u8 *)ring->wp - (u8 *)ring->base);
	*ring->ctxt_wp = db;
	mhi_chan->db_cfg.process_db(mhi_cntrl, &mhi_chan->db_cfg,
				    ring->db_addr, db);
}
enum mhi_ee_type mhi_get_exec_env(struct mhi_controller *mhi_cntrl)
{
	u32 exec;
	int ret = mhi_read_reg(mhi_cntrl, mhi_cntrl->bhi, BHI_EXECENV, &exec);

	return (ret) ? MHI_EE_MAX : exec;
}

enum mhi_state mhi_get_mhi_state(struct mhi_controller *mhi_cntrl)
{
	u32 state;
	int ret = mhi_read_reg_field(mhi_cntrl, mhi_cntrl->regs, MHISTATUS,
				     MHISTATUS_MHISTATE_MASK,
				     MHISTATUS_MHISTATE_SHIFT, &state);
	return ret ? MHI_STATE_MAX : state;	
}


int mhi_map_single_no_bb(struct mhi_controller *mhi_cntrl,
			 struct mhi_buf_info *buf_info)
{
    u32 ret = pci_dma_map_single(mhi_cntrl->cntrl_dev,
        buf_info->v_addr, (u32)buf_info->len, buf_info->dir,
        &buf_info->p_addr, &buf_info->p_mapping_addr);

	return ret;
}

int mhi_map_single_use_bb(struct mhi_controller *mhi_cntrl,
			  struct mhi_buf_info *buf_info)
{
	void *buf = mhi_alloc_coherent(mhi_cntrl, buf_info->len,
        &buf_info->p_addr, &buf_info->p_mapping_addr);

	if (!buf)
		return -ENOMEM;

	if (buf_info->dir == DMA_TO_DEVICE)
		memcpy(buf, buf_info->v_addr, buf_info->len);

	buf_info->bb_addr = buf;

	return 0;
}

void mhi_unmap_single_no_bb(struct mhi_controller *mhi_cntrl,
			    struct mhi_buf_info *buf_info)
{
    pci_dma_unmap_single(mhi_cntrl->cntrl_dev, buf_info->p_addr, buf_info->p_mapping_addr,
        (u32)buf_info->len, buf_info->dir);
}

void mhi_unmap_single_use_bb(struct mhi_controller *mhi_cntrl,
			     struct mhi_buf_info *buf_info)
{
	if (buf_info->dir == DMA_FROM_DEVICE)
		memcpy(buf_info->v_addr, buf_info->bb_addr, buf_info->len);

	mhi_free_coherent(mhi_cntrl, buf_info->len, buf_info->bb_addr,
			  buf_info->p_addr, buf_info->p_mapping_addr);
}

static int get_nr_avail_ring_elements(struct mhi_controller *mhi_cntrl,
				      struct mhi_ring *ring)
{
	u64 nr_el;

	if (ring->wp < ring->rp) {
		nr_el = (((u8*)ring->rp - (u8*)ring->wp) / ring->el_size) - 1;
	} else {
		nr_el = ((u8*)ring->rp - (u8*)ring->base) / ring->el_size;
		nr_el += (((u8*)ring->base + ring->len - (u8*)ring->wp) /
			  ring->el_size) - 1;
	}

	return (int)nr_el;
}

static void *mhi_to_virtual(struct mhi_ring *ring, dma_addr_t addr)
{
	return (u8 *)ring->base + (addr - ring->iommu_base);
}


static void mhi_add_ring_element(struct mhi_controller *mhi_cntrl,
				 struct mhi_ring *ring)
{
	ring->wp = (u8 *)ring->wp + ring->el_size;
	if ((u8 *)ring->wp >= ((u8 *)ring->base + ring->len))
		ring->wp = ring->base;
	/* smp update */
	smp_wmb();
}

static void mhi_del_ring_element(struct mhi_controller *mhi_cntrl,
				 struct mhi_ring *ring)
{
	ring->rp = (u8 *)ring->rp + ring->el_size;
	if ((u8 *)ring->rp >= ((u8 *)ring->base + ring->len))
		ring->rp = ring->base;
	/* smp update */
	smp_wmb();
}

int mhi_destroy_device(struct mhi_device *mhi_dev, void *data)
{
	//struct mhi_device *mhi_dev;
	struct mhi_controller *mhi_cntrl;

	//if (dev->bus != &mhi_bus_type)
	//	return 0;

	//mhi_dev = to_mhi_device(dev);
	mhi_cntrl = mhi_dev->mhi_cntrl;

	/* Only destroy virtual devices thats attached to bus */
	if (mhi_dev->dev_type == MHI_DEVICE_CONTROLLER)
		return 0;

	mhi_dbg("destroy device for chan:%a\n", mhi_dev->chan_name);

	/* Notify the client and remove the device from MHI bus */
	//device_del(dev);
	//put_device(dev);
    mhi_del_device(mhi_cntrl, mhi_dev);

	return 0;
}

static void mhi_notify(struct mhi_device *mhi_dev, enum mhi_callback cb_reason)
{
	struct mhi_driver *mhi_drv;

	if (!mhi_dev->driver)
		return;

    mhi_drv = mhi_dev->driver;

	if (mhi_drv->status_cb)
		mhi_drv->status_cb(mhi_dev, cb_reason);
}


/* Bind MHI channels to MHI devices */
void mhi_create_devices(struct mhi_controller *mhi_cntrl)
{
	struct mhi_chan *mhi_chan;
	struct mhi_device *mhi_dev;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;
	int i;

    mhi_dbg("mhi_cntrl->max_chan=%u\n", mhi_cntrl->max_chan);

	mhi_chan = mhi_cntrl->mhi_chan;
	for (i = 0; (u32)i < mhi_cntrl->max_chan; i++, mhi_chan++) {
		if (!mhi_chan->configured || mhi_chan->mhi_dev ||
		    !(mhi_chan->ee_mask & BIT(mhi_cntrl->ee)))
			continue;
		mhi_dev = mhi_alloc_device(mhi_cntrl);
		if (!mhi_dev)
			return;

		mhi_dev->dev_type = MHI_DEVICE_XFER;
		switch (mhi_chan->dir) {
		case DMA_TO_DEVICE:
			mhi_dev->ul_chan = mhi_chan;
			mhi_dev->ul_chan_id = mhi_chan->chan;
			break;
		case DMA_FROM_DEVICE:
			/* We use dl_chan as offload channels */
			mhi_dev->dl_chan = mhi_chan;
			mhi_dev->dl_chan_id = mhi_chan->chan;
			break;
		default:
			mhi_err("Direction not supported\n");
			//put_device(&mhi_dev->dev);
			return;
		}

		//get_device(&mhi_dev->dev);
		mhi_chan->mhi_dev = mhi_dev;

		/* Check next channel if it matches */
		if ((u32)(i + 1) < mhi_cntrl->max_chan && mhi_chan[1].configured) {
			if (!strcmp(mhi_chan[1].name, mhi_chan->name)) {
				i++;
				mhi_chan++;
				if (mhi_chan->dir == DMA_TO_DEVICE) {
					mhi_dev->ul_chan = mhi_chan;
					mhi_dev->ul_chan_id = mhi_chan->chan;
				} else {
					mhi_dev->dl_chan = mhi_chan;
					mhi_dev->dl_chan_id = mhi_chan->chan;
				}
				//get_device(&mhi_dev->dev);
				mhi_chan->mhi_dev = mhi_dev;
			}
		}

		/* Channel name is same for both UL and DL */
		mhi_dev->chan_name = mhi_chan->name;
		//dev_set_name(&mhi_dev->dev, "%04x_%s", mhi_chan->chan,
		//	  mhi_dev->chan_name);

		/* Init wakeup source if available */
		if (mhi_dev->dl_chan && mhi_dev->dl_chan->wake_capable) {
			//device_init_wakeup(&mhi_dev->dev, true);
		}

        mhi_add_device(mhi_cntrl, mhi_dev);
		//ret = device_add(&mhi_dev->dev);
		//if (ret) {
		//	  put_device(&mhi_dev->dev);
		//}
	}
}

int mhi_irq_handler(int irq_number, int budget, void *dev)
{
	struct mhi_event *mhi_event = dev;
	struct mhi_controller *mhi_cntrl = mhi_event->mhi_cntrl;
	struct mhi_event_ctxt *er_ctxt =
		&mhi_cntrl->mhi_ctxt->er_ctxt[mhi_event->er_index];
	struct mhi_ring *ev_ring = &mhi_event->ring;
	void *dev_rp = mhi_to_virtual(ev_ring, er_ctxt->rp);

	/* Only proceed if event ring has pending events */
	if (ev_ring->rp == dev_rp)
		return 0;

	/* For client managed event ring, notify pending data */
	if (mhi_event->cl_manage) {
		struct mhi_chan *mhi_chan = mhi_event->mhi_chan;
		struct mhi_device *mhi_dev = mhi_chan->mhi_dev;
		if (mhi_dev)
			mhi_notify(mhi_dev, MHI_CB_PENDING_DATA);
	} else {
		mhi_event->task(mhi_event);
	}

	return 1;
}

#if 0

int mhi_intvec_threaded_handler(int irq_number, int budget, void *dev)
{
	struct mhi_controller *mhi_cntrl = dev;
	enum mhi_state state = MHI_STATE_MAX;
	enum mhi_pm_state pm_state = 0;
	enum mhi_ee_type ee = 0;

	write_lock_irq(&mhi_cntrl->pm_lock);
	if (MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) {
		state = mhi_get_mhi_state(mhi_cntrl);
		ee = mhi_cntrl->ee;
		mhi_cntrl->ee = mhi_get_exec_env(mhi_cntrl);
	}

	if (state == MHI_STATE_SYS_ERR) {
		mhi_err("System error detected\n");
		pm_state = mhi_tryset_pm_state(mhi_cntrl,
					       MHI_PM_SYS_ERR_DETECT);
	}
	write_unlock_irq(&mhi_cntrl->pm_lock);

	/* If device in RDDM don't bother processing SYS error */
	if (mhi_cntrl->ee == MHI_EE_RDDM) {
		if (mhi_cntrl->ee != ee) {
			mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_EE_RDDM);
			wake_up_all(&mhi_cntrl->state_event);
		}
		goto exit_intvec;
	}

	if (pm_state == MHI_PM_SYS_ERR_DETECT) {
		wake_up_all(&mhi_cntrl->state_event);

		/* For fatal errors, we let controller decide next step */
		if (MHI_IN_PBL(ee))
			mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_FATAL_ERROR);
		else
			schedule_work(&mhi_cntrl->syserr_worker);
	}

exit_intvec:
	return 1;
}

int mhi_intvec_handler(int irq_number, int budget, void *dev)
{
	struct mhi_controller *mhi_cntrl = dev;

	/* Wake up events waiting for state change */
	wake_up_all(&mhi_cntrl->state_event);

	return 1;
}

#endif

static void mhi_recycle_ev_ring_element(struct mhi_controller *mhi_cntrl,
					struct mhi_ring *ring)
{
	dma_addr_t ctxt_wp;

    mhi_verb("Old -> ring->wp=0x%p, ring->rp=0x%p\n", ring->wp, ring->rp);

	/* Update the WP */
	ring->wp = (u8 *)ring->wp + ring->el_size;
	ctxt_wp = *ring->ctxt_wp + ring->el_size;

	if ((u8 *)ring->wp >= ((u8 *)ring->base + ring->len)) {
		ring->wp = ring->base;
		ctxt_wp = ring->iommu_base;
	}

	*ring->ctxt_wp = ctxt_wp;

	/* Update the RP */
	ring->rp = (u8 *)ring->rp + ring->el_size;
	if ((u8 *)ring->rp >= ((u8 *)ring->base + ring->len))
		ring->rp = ring->base;

    mhi_verb("New -> ring->wp=0x%p, ring->rp=0x%p\n", ring->wp, ring->rp);

	/* Update to all cores */
	smp_wmb();
}

static int parse_xfer_event(struct mhi_controller *mhi_cntrl,
			    struct mhi_tre *event,
			    struct mhi_chan *mhi_chan)
{
	struct mhi_ring *buf_ring, *tre_ring;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;
	struct mhi_result result;
	unsigned long flags = 0;
	u32 ev_code;

	ev_code = MHI_TRE_GET_EV_CODE(event);
	buf_ring = &mhi_chan->buf_ring;
	tre_ring = &mhi_chan->tre_ring;

	result.transaction_status = (ev_code == MHI_EV_CC_OVERFLOW) ?
		-EOVERFLOW : 0;

	/*
	 * If it's a DB Event then we need to grab the lock
	 * with preemption disabled and as a write because we
	 * have to update db register and there are chances that
	 * another thread could be doing the same.
	 */
	if (ev_code >= MHI_EV_CC_OOB)
		write_lock_irqsave(&mhi_chan->lock, flags);
	else
		read_lock_bh(&mhi_chan->lock);

	if (mhi_chan->ch_state != MHI_CH_STATE_ENABLED)
		goto end_process_tx_event;

	switch (ev_code) {
	case MHI_EV_CC_OVERFLOW:
	case MHI_EV_CC_EOB:
	case MHI_EV_CC_EOT:
	{
		dma_addr_t ptr = MHI_TRE_GET_EV_PTR(event);
		struct mhi_tre *local_rp, *ev_tre;
		void *dev_rp;
		struct mhi_buf_info *buf_info;
		u16 xfer_len;

		/* Get the TRB this event points to */
		ev_tre = mhi_to_virtual(tre_ring, ptr);

		dev_rp = ev_tre + 1;
		if ((u8 *)dev_rp >= ((u8 *)tre_ring->base + tre_ring->len))
			dev_rp = tre_ring->base;

		result.dir = mhi_chan->dir;

		local_rp = tre_ring->rp;
		while (local_rp != dev_rp) {
			buf_info = buf_ring->rp;
			/* If it's the last TRE, get length from the event */
			if (local_rp == ev_tre)
				xfer_len = MHI_TRE_GET_EV_LEN(event);
			else
				xfer_len = (u16)buf_info->len;

			/* Unmap if it's not pre-mapped by client */
			if (likely(!buf_info->pre_mapped))
				mhi_cntrl->unmap_single(mhi_cntrl, buf_info);

			result.buf_addr = buf_info->cb_buf;
			result.bytes_xferd = xfer_len;
			mhi_del_ring_element(mhi_cntrl, buf_ring);
			mhi_del_ring_element(mhi_cntrl, tre_ring);
			local_rp = tre_ring->rp;

			/* notify client */
			mhi_chan->xfer_cb(mhi_chan->mhi_dev, &result);

			if (mhi_chan->dir == DMA_TO_DEVICE)
				atomic_dec(&mhi_cntrl->pending_pkts);

			/*
			 * Recycle the buffer if buffer is pre-allocated,
			 * if there is an error, not much we can do apart
			 * from dropping the packet
			 */
			if (mhi_chan->pre_alloc) {
				if (mhi_queue_buf(mhi_chan->mhi_dev,
						  mhi_chan->dir,
						  buf_info->cb_buf,
						  buf_info->len, MHI_EOT)) {
                    mhi_dbg("Error recycling buffer for chan:%d\n",
						mhi_chan->chan);
					pci_mem_free(mhi_cntrl->cntrl_dev, buf_info->len, buf_info->cb_buf);
				}
			}
		}
		break;
	} /* CC_EOT */
	case MHI_EV_CC_OOB:
	case MHI_EV_CC_DB_MODE:
	{
		unsigned long local_flags;

		mhi_chan->db_cfg.db_mode = 1;
		read_lock_irqsave(&mhi_cntrl->pm_lock, local_flags);
		if (tre_ring->wp != tre_ring->rp &&
		    MHI_DB_ACCESS_VALID(mhi_cntrl)) {
			mhi_ring_chan_db(mhi_cntrl, mhi_chan);
		}
		read_unlock_irqrestore(&mhi_cntrl->pm_lock, local_flags);
		break;
	}
	case MHI_EV_CC_BAD_TRE:
	default:
        mhi_err("Unknown event 0x%x\n", ev_code);
		break;
	} /* switch(MHI_EV_READ_CODE(EV_TRB_CODE,event)) */

end_process_tx_event:
	if (ev_code >= MHI_EV_CC_OOB)
		write_unlock_irqrestore(&mhi_chan->lock, flags);
	else
		read_unlock_bh(&mhi_chan->lock);

	return 0;
}

static int parse_rsc_event(struct mhi_controller *mhi_cntrl,
			   struct mhi_tre *event,
			   struct mhi_chan *mhi_chan)
{
	struct mhi_ring *buf_ring, *tre_ring;
	struct mhi_buf_info *buf_info;
	struct mhi_result result;
	int ev_code;
	u32 cookie; /* offset to local descriptor */
	u16 xfer_len;

	buf_ring = &mhi_chan->buf_ring;
	tre_ring = &mhi_chan->tre_ring;

	ev_code = MHI_TRE_GET_EV_CODE(event);
	cookie = MHI_TRE_GET_EV_COOKIE(event);
	xfer_len = MHI_TRE_GET_EV_LEN(event);

	/* Received out of bound cookie */
	WARN_ON(cookie >= buf_ring->len);

	buf_info = (void *)((u8*)buf_ring->base + cookie);

	result.transaction_status = (ev_code == MHI_EV_CC_OVERFLOW) ?
		-EOVERFLOW : 0;
	result.bytes_xferd = xfer_len;
	result.buf_addr = buf_info->cb_buf;
	result.dir = mhi_chan->dir;

	read_lock_bh(&mhi_chan->lock);

	if (mhi_chan->ch_state != MHI_CH_STATE_ENABLED)
		goto end_process_rsc_event;

	WARN_ON(!buf_info->used);

	/* notify the client */
	mhi_chan->xfer_cb(mhi_chan->mhi_dev, &result);

	/*
	 * Note: We're arbitrarily incrementing RP even though, completion
	 * packet we processed might not be the same one, reason we can do this
	 * is because device guaranteed to cache descriptors in order it
	 * receive, so even though completion event is different we can re-use
	 * all descriptors in between.
	 * Example:
	 * Transfer Ring has descriptors: A, B, C, D
	 * Last descriptor host queue is D (WP) and first descriptor
	 * host queue is A (RP).
	 * The completion event we just serviced is descriptor C.
	 * Then we can safely queue descriptors to replace A, B, and C
	 * even though host did not receive any completions.
	 */
	mhi_del_ring_element(mhi_cntrl, tre_ring);
	buf_info->used = false;

end_process_rsc_event:
	read_unlock_bh(&mhi_chan->lock);

	return 0;
}

static void mhi_process_cmd_completion(struct mhi_controller *mhi_cntrl,
				       struct mhi_tre *tre)
{
	dma_addr_t ptr = MHI_TRE_GET_EV_PTR(tre);
	struct mhi_cmd *cmd_ring = &mhi_cntrl->mhi_cmd[PRIMARY_CMD_RING];
	struct mhi_ring *mhi_ring = &cmd_ring->ring;
	struct mhi_tre *cmd_pkt;
	struct mhi_chan *mhi_chan;
	u32 chan;

	cmd_pkt = mhi_to_virtual(mhi_ring, ptr);

	chan = MHI_TRE_GET_CMD_CHID(cmd_pkt);
	mhi_chan = &mhi_cntrl->mhi_chan[chan];
	write_lock_bh(&mhi_chan->lock);
	mhi_chan->ccs = MHI_TRE_GET_EV_CODE(tre);
	complete(&mhi_chan->completion);
	write_unlock_bh(&mhi_chan->lock);

	mhi_del_ring_element(mhi_cntrl, mhi_ring);

    mhi_dbg("chan=%u done\n", chan);
}

int mhi_process_ctrl_ev_ring(struct mhi_controller *mhi_cntrl,
			     struct mhi_event *mhi_event,
			     u32 event_quota)
{
	struct mhi_tre *dev_rp, *local_rp;
	struct mhi_ring *ev_ring = &mhi_event->ring;
	struct mhi_event_ctxt *er_ctxt =
		&mhi_cntrl->mhi_ctxt->er_ctxt[mhi_event->er_index];
	struct mhi_chan *mhi_chan;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;
	u32 chan;
	int count = 0;

	/*
	 * This is a quick check to avoid unnecessary event processing
	 * in case MHI is already in error state, but it's still possible
	 * to transition to error state while processing events
	 */
	if (unlikely(MHI_EVENT_ACCESS_INVALID(mhi_cntrl->pm_state)))
		return -EIO;

	dev_rp = mhi_to_virtual(ev_ring, er_ctxt->rp);
	local_rp = ev_ring->rp;

	while (dev_rp != local_rp) {
		enum mhi_pkt_type type = MHI_TRE_GET_EV_TYPE(local_rp);

        mhi_dbg("dev_rp=0x%p, local_rp=0x%p\n", dev_rp, local_rp);

		switch (type) {
		case MHI_PKT_TYPE_BW_REQ_EVENT:
		{
			struct mhi_link_info *link_info;

			link_info = &mhi_cntrl->mhi_link_info;
			write_lock_irq(&mhi_cntrl->pm_lock);
			link_info->target_link_speed =
				MHI_TRE_GET_EV_LINKSPEED(local_rp);
			link_info->target_link_width =
				MHI_TRE_GET_EV_LINKWIDTH(local_rp);
			write_unlock_irq(&mhi_cntrl->pm_lock);
            mhi_dbg("Received BW_REQ event\n");
			mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_BW_REQ);
			break;
		}
		case MHI_PKT_TYPE_STATE_CHANGE_EVENT:
		{
			enum mhi_state new_state;

			new_state = MHI_TRE_GET_EV_STATE(local_rp);

			mhi_dbg("State change event to state: %a\n", TO_MHI_STATE_STR(new_state));

			switch (new_state) {
			case MHI_STATE_M0:
				mhi_pm_m0_transition(mhi_cntrl);
				break;
			case MHI_STATE_M1:
				mhi_pm_m1_transition(mhi_cntrl);
				break;
			case MHI_STATE_M3:
				mhi_pm_m3_transition(mhi_cntrl);
				break;
			case MHI_STATE_SYS_ERR:
            {
				enum mhi_pm_state new_pm_state;

                mhi_dbg("System error detected\n");
				write_lock_irq(&mhi_cntrl->pm_lock);
                new_pm_state = mhi_tryset_pm_state(mhi_cntrl,
							MHI_PM_SYS_ERR_DETECT);
				write_unlock_irq(&mhi_cntrl->pm_lock);
				if (new_pm_state == MHI_PM_SYS_ERR_DETECT)
                    schedule_work(&mhi_cntrl->syserr_worker);
				break;
			}
			default:
				mhi_err("Invalid state: %a\n", TO_MHI_STATE_STR(new_state));
			}

			break;
		}
		case MHI_PKT_TYPE_CMD_COMPLETION_EVENT:
			mhi_process_cmd_completion(mhi_cntrl, local_rp);
			break;
		case MHI_PKT_TYPE_EE_EVENT:
		{
			enum dev_st_transition st = DEV_ST_TRANSITION_MAX;
			enum mhi_ee_type event = MHI_TRE_GET_EV_EXECENV(local_rp);

			mhi_err("Received EE event: %a\n", TO_MHI_EXEC_STR(event));
			switch (event) {
			case MHI_EE_SBL:
				st = DEV_ST_TRANSITION_SBL;
				break;
			case MHI_EE_WFW:
			case MHI_EE_AMSS:
				st = DEV_ST_TRANSITION_MISSION_MODE;
				break;
			case MHI_EE_RDDM:
				mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_EE_RDDM);
				write_lock_irq(&mhi_cntrl->pm_lock);
				mhi_cntrl->ee = event;
				write_unlock_irq(&mhi_cntrl->pm_lock);
				wake_up_all(&mhi_cntrl->state_event);
				break;
			default:
                mhi_err("Unhandled EE event: 0x%x\n", type);
			}
			if (st != DEV_ST_TRANSITION_MAX)
				mhi_queue_state_transition(mhi_cntrl, st);

			break;
		}
		case MHI_PKT_TYPE_TX_EVENT:
			chan = MHI_TRE_GET_EV_CHID(local_rp);
			mhi_chan = &mhi_cntrl->mhi_chan[chan];
			parse_xfer_event(mhi_cntrl, local_rp, mhi_chan);
			event_quota--;
			break;
		default:
            mhi_err("Unhandled event type: %d\n", type);
			break;
		}

		mhi_recycle_ev_ring_element(mhi_cntrl, ev_ring);
		local_rp = ev_ring->rp;
		dev_rp = mhi_to_virtual(ev_ring, er_ctxt->rp);
		count++;
	}

	read_lock_bh(&mhi_cntrl->pm_lock);
	if (likely(MHI_DB_ACCESS_VALID(mhi_cntrl)))
		mhi_ring_er_db(mhi_event);
	read_unlock_bh(&mhi_cntrl->pm_lock);

	return count;
}

int mhi_process_data_event_ring(struct mhi_controller *mhi_cntrl,
				struct mhi_event *mhi_event,
				u32 event_quota)
{
	struct mhi_tre *dev_rp, *local_rp;
	struct mhi_ring *ev_ring = &mhi_event->ring;
	struct mhi_event_ctxt *er_ctxt =
		&mhi_cntrl->mhi_ctxt->er_ctxt[mhi_event->er_index];
	int count = 0;
	u32 chan;
	struct mhi_chan *mhi_chan;

	if (unlikely(MHI_EVENT_ACCESS_INVALID(mhi_cntrl->pm_state))) {
		mhi_err("No EV access, PM_STATE:%s\n",
			to_mhi_pm_state_str(mhi_cntrl->pm_state));
		return -EIO;
	}

	dev_rp = mhi_to_virtual(ev_ring, er_ctxt->rp);
	local_rp = ev_ring->rp;

	mhi_dbg("dev_rp=0x%p, local_rp=0x%p\n", dev_rp, local_rp);
	
	while (dev_rp != local_rp && event_quota > 0) {
		enum mhi_pkt_type type = MHI_TRE_GET_EV_TYPE(local_rp);

		if (likely(type == MHI_PKT_TYPE_TX_EVENT)) {
			chan = MHI_TRE_GET_EV_CHID(local_rp);

			if (chan >= mhi_cntrl->max_chan) {
				mhi_err("invalid channel id %u\n", chan);
				goto next_er_element;
			}

			mhi_chan = &mhi_cntrl->mhi_chan[chan];
			parse_xfer_event(mhi_cntrl, local_rp, mhi_chan);
			event_quota--;
		}

next_er_element:
		mhi_recycle_ev_ring_element(mhi_cntrl, ev_ring);
		local_rp = ev_ring->rp;
		dev_rp = mhi_to_virtual(ev_ring, er_ctxt->rp);
		count++;
	}
	read_lock_bh(&mhi_cntrl->pm_lock);
	if (likely(MHI_DB_ACCESS_VALID(mhi_cntrl)))
		mhi_ring_er_db(mhi_event);
	read_unlock_bh(&mhi_cntrl->pm_lock);

	mhi_dbg("exit er_index:%u\n", mhi_event->er_index);

	return count;
}

void mhi_ev_task(struct mhi_event *data)
{
	struct mhi_event *mhi_event = (struct mhi_event *)data;
	struct mhi_controller *mhi_cntrl = mhi_event->mhi_cntrl;

	/* process all pending events */
	spin_lock_bh(&mhi_event->lock);
	mhi_event->process_event(mhi_cntrl, mhi_event, U32_MAX);
	spin_unlock_bh(&mhi_event->lock);
}

void mhi_ctrl_ev_task(struct mhi_event *data)
{
	struct mhi_event *mhi_event = (struct mhi_event *)data;
	struct mhi_controller *mhi_cntrl = mhi_event->mhi_cntrl;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;
	enum mhi_state state;
	enum mhi_pm_state pm_state = 0;
	int ret;

	/*
	 * We can check PM state w/o a lock here because there is no way
	 * PM state can change from reg access valid to no access while this
	 * thread being executed.
	 */
	if (!MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) {
		/*
		 * We may have a pending event but not allowed to
		 * process it since we are probably in a suspended state,
		 * so trigger a resume.
		 */
		mhi_cntrl->runtime_get(mhi_cntrl);
		mhi_cntrl->runtime_put(mhi_cntrl);

		return;
	}

	/* Process ctrl events events */
	ret = mhi_event->process_event(mhi_cntrl, mhi_event, U32_MAX);

	/*
	 * We received an IRQ but no events to process, maybe device went to
	 * SYS_ERR state? Check the state to confirm.
	 */
	if (!ret) {
		write_lock_irq(&mhi_cntrl->pm_lock);
		state = mhi_get_mhi_state(mhi_cntrl);
		if (state == MHI_STATE_SYS_ERR) {
            mhi_dbg("System error detected\n");
			pm_state = mhi_tryset_pm_state(mhi_cntrl,
						       MHI_PM_SYS_ERR_DETECT);
		}
		write_unlock_irq(&mhi_cntrl->pm_lock);
        if (pm_state == MHI_PM_SYS_ERR_DETECT) {
            schedule_work(&mhi_cntrl->syserr_worker);
        }
	}
}

static bool mhi_is_ring_full(struct mhi_controller *mhi_cntrl,
			     struct mhi_ring *ring)
{
	void *tmp = (u8 *)ring->wp + ring->el_size;

	if ((u8 *)tmp >= ((u8 *)ring->base + ring->len))
		tmp = ring->base;

	return (tmp == ring->rp);
}

int mhi_queue_skb(struct mhi_device *mhi_dev, enum dma_data_direction dir,
		  struct sk_buff *skb, size_t len, enum mhi_flags mflags)
{
	struct mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	struct mhi_chan *mhi_chan = (dir == DMA_TO_DEVICE) ? mhi_dev->ul_chan :
							     mhi_dev->dl_chan;
	struct mhi_ring *tre_ring = &mhi_chan->tre_ring;
	struct mhi_ring *buf_ring = &mhi_chan->buf_ring;
	struct mhi_buf_info *buf_info;
	struct mhi_tre *mhi_tre;
	int ret;

	/* If MHI host pre-allocates buffers then client drivers cannot queue */
	if (mhi_chan->pre_alloc)
		return -EINVAL;

	if (mhi_is_ring_full(mhi_cntrl, tre_ring))
		return -ENOMEM;

    mhi_dbg("queue a packet: skb=0x%p, len=%u\n", skb, skb->len);

	read_lock_bh(&mhi_cntrl->pm_lock);
	if (unlikely(MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state))) {
		read_unlock_bh(&mhi_cntrl->pm_lock);
		return -EIO;
	}

	/* we're in M3 or transitioning to M3 */
	if (MHI_PM_IN_SUSPEND_STATE(mhi_cntrl->pm_state)) {
		mhi_cntrl->runtime_get(mhi_cntrl);
		mhi_cntrl->runtime_put(mhi_cntrl);
	}

	/* Toggle wake to exit out of M2 */
	mhi_cntrl->wake_toggle(mhi_cntrl);

	/* Generate the TRE */
	buf_info = buf_ring->wp;

	buf_info->v_addr = skb->data;
	buf_info->cb_buf = skb;
	buf_info->wp = tre_ring->wp;
	buf_info->dir = mhi_chan->dir;
	buf_info->len = len;
	ret = mhi_cntrl->map_single(mhi_cntrl, buf_info);
	if (ret)
		goto map_error;

	mhi_tre = tre_ring->wp;

	mhi_tre->ptr = MHI_TRE_DATA_PTR(buf_info->p_addr);
	mhi_tre->dword[0] = MHI_TRE_DATA_DWORD0(buf_info->len);
	mhi_tre->dword[1] = MHI_TRE_DATA_DWORD1(1, 1, 0, 0);

	/* increment WP */
	mhi_add_ring_element(mhi_cntrl, tre_ring);
	mhi_add_ring_element(mhi_cntrl, buf_ring);

	if (mhi_chan->dir == DMA_TO_DEVICE)
		atomic_inc(&mhi_cntrl->pending_pkts);

	if (likely(MHI_DB_ACCESS_VALID(mhi_cntrl))) {
		read_lock_bh(&mhi_chan->lock);
		mhi_ring_chan_db(mhi_cntrl, mhi_chan);
		read_unlock_bh(&mhi_chan->lock);
	}

	read_unlock_bh(&mhi_cntrl->pm_lock);

	return 0;

map_error:
	read_unlock_bh(&mhi_cntrl->pm_lock);

	return ret;
}
EXPORT_SYMBOL_GPL(mhi_queue_skb);

#if 0
int mhi_queue_dma(struct mhi_device *mhi_dev, enum dma_data_direction dir,
		  struct mhi_buf *mhi_buf, size_t len, enum mhi_flags mflags)
{
	struct mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	struct mhi_chan *mhi_chan = (dir == DMA_TO_DEVICE) ? mhi_dev->ul_chan :
							     mhi_dev->dl_chan;
	struct device *dev = &mhi_cntrl->mhi_dev->dev;
	struct mhi_ring *tre_ring = &mhi_chan->tre_ring;
	struct mhi_ring *buf_ring = &mhi_chan->buf_ring;
	struct mhi_buf_info *buf_info;
	struct mhi_tre *mhi_tre;

	/* If MHI host pre-allocates buffers then client drivers cannot queue */
	if (mhi_chan->pre_alloc)
		return -EINVAL;

	if (mhi_is_ring_full(mhi_cntrl, tre_ring))
		return -ENOMEM;

	read_lock_bh(&mhi_cntrl->pm_lock);
	if (unlikely(MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state))) {
		mhi_err("MHI is not in activate state, PM state: %a\n",
			to_mhi_pm_state_str(mhi_cntrl->pm_state));
		read_unlock_bh(&mhi_cntrl->pm_lock);

		return -EIO;
	}

	/* we're in M3 or transitioning to M3 */
	if (MHI_PM_IN_SUSPEND_STATE(mhi_cntrl->pm_state)) {
		mhi_cntrl->runtime_get(mhi_cntrl);
		mhi_cntrl->runtime_put(mhi_cntrl);
	}

	/* Toggle wake to exit out of M2 */
	mhi_cntrl->wake_toggle(mhi_cntrl);

	/* Generate the TRE */
	buf_info = buf_ring->wp;
	WARN_ON(buf_info->used);
	buf_info->p_addr = mhi_buf->aligned_dma_addr;
	buf_info->pre_mapped = true;
	buf_info->cb_buf = mhi_buf;
	buf_info->wp = tre_ring->wp;
	buf_info->dir = mhi_chan->dir;
	buf_info->len = len;

	mhi_tre = tre_ring->wp;

	mhi_tre->ptr = MHI_TRE_DATA_PTR(buf_info->p_addr);
	mhi_tre->dword[0] = MHI_TRE_DATA_DWORD0(buf_info->len);
	mhi_tre->dword[1] = MHI_TRE_DATA_DWORD1(1, 1, 0, 0);

	/* increment WP */
	mhi_add_ring_element(mhi_cntrl, tre_ring);
	mhi_add_ring_element(mhi_cntrl, buf_ring);

	if (mhi_chan->dir == DMA_TO_DEVICE)
		atomic_inc(&mhi_cntrl->pending_pkts);

	if (likely(MHI_DB_ACCESS_VALID(mhi_cntrl))) {
		read_lock_bh(&mhi_chan->lock);
		mhi_ring_chan_db(mhi_cntrl, mhi_chan);
		read_unlock_bh(&mhi_chan->lock);
	}

	read_unlock_bh(&mhi_cntrl->pm_lock);

	return 0;
}
EXPORT_SYMBOL_GPL(mhi_queue_dma);
#endif

int mhi_gen_tre(struct mhi_controller *mhi_cntrl, struct mhi_chan *mhi_chan,
		void *buf, void *cb, size_t buf_len, enum mhi_flags flags)
{
	struct mhi_ring *buf_ring, *tre_ring;
	struct mhi_tre *mhi_tre;
	struct mhi_buf_info *buf_info;
	int eot, eob, chain, bei;
	int ret;

	buf_ring = &mhi_chan->buf_ring;
	tre_ring = &mhi_chan->tre_ring;

	buf_info = buf_ring->wp;
	buf_info->v_addr = buf;
	buf_info->cb_buf = cb;
	buf_info->wp = tre_ring->wp;
	buf_info->dir = mhi_chan->dir;
	buf_info->len = buf_len;

	ret = mhi_cntrl->map_single(mhi_cntrl, buf_info);
	if (ret)
		return ret;

	eob = !!(flags & MHI_EOB);
	eot = !!(flags & MHI_EOT);
	chain = !!(flags & MHI_CHAIN);
	bei = !!(mhi_chan->intmod);

	mhi_tre = tre_ring->wp;
	mhi_tre->ptr = MHI_TRE_DATA_PTR(buf_info->p_addr);
	mhi_tre->dword[0] = MHI_TRE_DATA_DWORD0(buf_len);
	mhi_tre->dword[1] = MHI_TRE_DATA_DWORD1(bei, eot, eob, chain);

	/* increment WP */
	mhi_add_ring_element(mhi_cntrl, tre_ring);
	mhi_add_ring_element(mhi_cntrl, buf_ring);

	return 0;
}

int mhi_queue_buf(struct mhi_device *mhi_dev, enum dma_data_direction dir,
		  void *buf, size_t len, enum mhi_flags mflags)
{
	struct mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	struct mhi_chan *mhi_chan = (dir == DMA_TO_DEVICE) ? mhi_dev->ul_chan :
							     mhi_dev->dl_chan;
	struct mhi_ring *tre_ring;
	unsigned long flags;
	int ret;

	/*
	 * this check here only as a guard, it's always
	 * possible mhi can enter error while executing rest of function,
	 * which is not fatal so we do not need to hold pm_lock
	 */
	if (unlikely(MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)))
		return -EIO;

	tre_ring = &mhi_chan->tre_ring;
	if (mhi_is_ring_full(mhi_cntrl, tre_ring))
		return -ENOMEM;

	ret = mhi_gen_tre(mhi_cntrl, mhi_chan, buf, buf, len, mflags);
	if (unlikely(ret))
		return ret;

	read_lock_irqsave(&mhi_cntrl->pm_lock, flags);

	/* we're in M3 or transitioning to M3 */
	if (MHI_PM_IN_SUSPEND_STATE(mhi_cntrl->pm_state)) {
		mhi_cntrl->runtime_get(mhi_cntrl);
		mhi_cntrl->runtime_put(mhi_cntrl);
	}

	/* Toggle wake to exit out of M2 */
	mhi_cntrl->wake_toggle(mhi_cntrl);

	if (mhi_chan->dir == DMA_TO_DEVICE)
		atomic_inc(&mhi_cntrl->pending_pkts);

	if (likely(MHI_DB_ACCESS_VALID(mhi_cntrl))) {
		unsigned long iflags;

		read_lock_irqsave(&mhi_cshan->lock, iflags);
		mhi_ring_chan_db(mhi_cntrl, mhi_chan);
		read_unlock_irqrestore(&mhi_chan->lock, iflags);
	}

	read_unlock_irqrestore(&mhi_cntrl->pm_lock, flags);

	return 0;
}

EXPORT_SYMBOL_GPL(mhi_queue_buf);

int mhi_send_cmd(struct mhi_controller *mhi_cntrl,
		 struct mhi_chan *mhi_chan,
		 enum mhi_cmd_type cmd)
{
	struct mhi_tre *cmd_tre = NULL;
	struct mhi_cmd *mhi_cmd = &mhi_cntrl->mhi_cmd[PRIMARY_CMD_RING];
	struct mhi_ring *ring = &mhi_cmd->ring;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;
	int chan = 0;

    mhi_dbg("cmd=%u\n", cmd);

	if (mhi_chan)
		chan = mhi_chan->chan;

	spin_lock_bh(&mhi_cmd->lock);
	if (!get_nr_avail_ring_elements(mhi_cntrl, ring)) {
		spin_unlock_bh(&mhi_cmd->lock);
		return -ENOMEM;
	}

	/* prepare the cmd tre */
	cmd_tre = ring->wp;
	switch (cmd) {
	case MHI_CMD_RESET_CHAN:
		cmd_tre->ptr = MHI_TRE_CMD_RESET_PTR;
		cmd_tre->dword[0] = MHI_TRE_CMD_RESET_DWORD0;
		cmd_tre->dword[1] = MHI_TRE_CMD_RESET_DWORD1(chan);
		break;
	case MHI_CMD_START_CHAN:
		cmd_tre->ptr = MHI_TRE_CMD_START_PTR;
		cmd_tre->dword[0] = MHI_TRE_CMD_START_DWORD0;
		cmd_tre->dword[1] = MHI_TRE_CMD_START_DWORD1(chan);
		break;
	default:
		mhi_err("Command not supported\n");
		break;
	}

	/* queue to hardware */
	mhi_add_ring_element(mhi_cntrl, ring);
	read_lock_bh(&mhi_cntrl->pm_lock);
	if (likely(MHI_DB_ACCESS_VALID(mhi_cntrl)))
		mhi_ring_cmd_db(mhi_cntrl, mhi_cmd);
	read_unlock_bh(&mhi_cntrl->pm_lock);
	spin_unlock_bh(&mhi_cmd->lock);

	return 0;
}

static void __mhi_unprepare_channel(struct mhi_controller *mhi_cntrl,
				    struct mhi_chan *mhi_chan)
{
	int ret;
	unsigned long time_left;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;

	mhi_dbg("Entered: unprepare channel:%d\n", mhi_chan->chan);

	/* no more processing events for this channel */
	mutex_lock(&mhi_chan->mutex);
	write_lock_irq(&mhi_chan->lock);
	if (mhi_chan->ch_state != MHI_CH_STATE_ENABLED) {
		write_unlock_irq(&mhi_chan->lock);
		mutex_unlock(&mhi_chan->mutex);
		return;
	}

	mhi_chan->ch_state = MHI_CH_STATE_DISABLED;
	write_unlock_irq(&mhi_chan->lock);

	reinit_completion(&mhi_chan->completion);
	read_lock_bh(&mhi_cntrl->pm_lock);
	if (MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) {
		read_unlock_bh(&mhi_cntrl->pm_lock);
		goto error_invalid_state;
	}

	mhi_cntrl->wake_toggle(mhi_cntrl);
	read_unlock_bh(&mhi_cntrl->pm_lock);

	mhi_cntrl->runtime_get(mhi_cntrl);
	mhi_cntrl->runtime_put(mhi_cntrl);
	ret = mhi_send_cmd(mhi_cntrl, mhi_chan, MHI_CMD_RESET_CHAN);
	if (ret)
		goto error_invalid_state;

	/* even if it fails we will still reset */
	time_left = wait_for_completion_timeout(&mhi_chan->completion,
				mhi_cntrl->timeout_ms);
	if (!time_left || mhi_chan->ccs != MHI_EV_CC_SUCCESS)
		mhi_err("Failed to receive cmd completion, still resetting\n");

error_invalid_state:
	if (!mhi_chan->offload_ch) {
		mhi_reset_chan(mhi_cntrl, mhi_chan);
		mhi_deinit_chan_ctxt(mhi_cntrl, mhi_chan);
	}
	mhi_dbg("chan:%d successfully resetted\n", mhi_chan->chan);
	mutex_unlock(&mhi_chan->mutex);
}

int mhi_prepare_channel(struct mhi_controller *mhi_cntrl,
			struct mhi_chan *mhi_chan)
{
	int ret = 0;
	unsigned long time_left;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;

	mhi_dbg("Preparing channel: %d\n", mhi_chan->chan);

	if (!(BIT(mhi_cntrl->ee) & mhi_chan->ee_mask)) {
		mhi_err("Current EE: %a Required EE Mask: 0x%x for chan: %a\n",
			TO_MHI_EXEC_STR(mhi_cntrl->ee), mhi_chan->ee_mask,
			mhi_chan->name);
		return -ENOTCONN;
	}

	mutex_lock(&mhi_chan->mutex);

	/* If channel is not in disable state, do not allow it to start */
	if (mhi_chan->ch_state != MHI_CH_STATE_DISABLED) {
		ret = -EIO;
		mhi_dbg("channel: %d is not in disabled state\n",
			mhi_chan->chan);
		goto error_init_chan;
	}

	/* Check of client manages channel context for offload channels */
	if (!mhi_chan->offload_ch) {
		ret = mhi_init_chan_ctxt(mhi_cntrl, mhi_chan);
		if (ret)
			goto error_init_chan;
	}

	reinit_completion(&mhi_chan->completion);
	read_lock_bh(&mhi_cntrl->pm_lock);
	if (MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) {
		read_unlock_bh(&mhi_cntrl->pm_lock);
		ret = -EIO;
		goto error_pm_state;
	}

	mhi_cntrl->wake_toggle(mhi_cntrl);
	read_unlock_bh(&mhi_cntrl->pm_lock);
	mhi_cntrl->runtime_get(mhi_cntrl);
	mhi_cntrl->runtime_put(mhi_cntrl);

	ret = mhi_send_cmd(mhi_cntrl, mhi_chan, MHI_CMD_START_CHAN);
	if (ret)
		goto error_pm_state;

	time_left = wait_for_completion_timeout(&mhi_chan->completion,
				mhi_cntrl->timeout_ms);
	if (!time_left || mhi_chan->ccs != MHI_EV_CC_SUCCESS) {
		ret = -EIO;
		goto error_pm_state;
	}

	write_lock_irq(&mhi_chan->lock);
	mhi_chan->ch_state = MHI_CH_STATE_ENABLED;
	write_unlock_irq(&mhi_chan->lock);

	/* Pre-allocate buffer for xfer ring */
	if (mhi_chan->pre_alloc) {
		int nr_el = get_nr_avail_ring_elements(mhi_cntrl,
						       &mhi_chan->tre_ring);
		size_t len = mhi_cntrl->buffer_len;

		while (nr_el--) {
			void *buf;

			buf = pci_mem_alloc(mhi_cntrl->cntrl_dev, len);
			if (!buf) {
				ret = -ENOMEM;
				goto error_pre_alloc;
			}

			/* Prepare transfer descriptors */
			ret = mhi_gen_tre(mhi_cntrl, mhi_chan, buf, buf,
					  len, MHI_EOT);
			if (ret) {
                pci_mem_free(mhi_cntrl->cntrl_dev, len, buf);
				goto error_pre_alloc;
			}
		}

		read_lock_bh(&mhi_cntrl->pm_lock);
		if (MHI_DB_ACCESS_VALID(mhi_cntrl)) {
			read_lock_irq(&mhi_chan->lock);
			mhi_ring_chan_db(mhi_cntrl, mhi_chan);
			read_unlock_irq(&mhi_chan->lock);
		}
		read_unlock_bh(&mhi_cntrl->pm_lock);
	}

	mutex_unlock(&mhi_chan->mutex);

	mhi_dbg("Chan: %d successfully moved to start state\n",
		mhi_chan->chan);

	return 0;

error_pm_state:
	if (!mhi_chan->offload_ch)
		mhi_deinit_chan_ctxt(mhi_cntrl, mhi_chan);

error_init_chan:
	mutex_unlock(&mhi_chan->mutex);

	return ret;

error_pre_alloc:
	mutex_unlock(&mhi_chan->mutex);
	__mhi_unprepare_channel(mhi_cntrl, mhi_chan);

	return ret;
}

static void mhi_mark_stale_events(struct mhi_controller *mhi_cntrl,
				  struct mhi_event *mhi_event,
				  struct mhi_event_ctxt *er_ctxt,
				  int chan)

{
	struct mhi_tre *dev_rp, *local_rp;
	struct mhi_ring *ev_ring;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;
	unsigned long flags;

	mhi_dbg("Marking all events for chan: %d as stale\n", chan);

	ev_ring = &mhi_event->ring;

	/* mark all stale events related to channel as STALE event */
	spin_lock_irqsave(&mhi_event->lock, flags);
	dev_rp = mhi_to_virtual(ev_ring, er_ctxt->rp);

	local_rp = ev_ring->rp;
	while (dev_rp != local_rp) {
		if (MHI_TRE_GET_EV_TYPE(local_rp) == MHI_PKT_TYPE_TX_EVENT &&
		    chan == (int)MHI_TRE_GET_EV_CHID(local_rp))
			local_rp->dword[1] = MHI_TRE_EV_DWORD1(chan,
					MHI_PKT_TYPE_STALE_EVENT);
		local_rp++;
		if (local_rp == (void *)((u8 *)ev_ring->base + ev_ring->len))
			local_rp = ev_ring->base;
	}

	mhi_dbg("Finished marking events as stale events\n");
	spin_unlock_irqrestore(&mhi_event->lock, flags);
}

static void mhi_reset_data_chan(struct mhi_controller *mhi_cntrl,
				struct mhi_chan *mhi_chan)
{
	struct mhi_ring *buf_ring, *tre_ring;
	struct mhi_result result;

	/* Reset any pending buffers */
	buf_ring = &mhi_chan->buf_ring;
	tre_ring = &mhi_chan->tre_ring;
	result.transaction_status = -ENOTCONN;
	result.bytes_xferd = 0;
	while (tre_ring->rp != tre_ring->wp) {
		struct mhi_buf_info *buf_info = buf_ring->rp;

		if (mhi_chan->dir == DMA_TO_DEVICE)
			atomic_dec(&mhi_cntrl->pending_pkts);

		if (!buf_info->pre_mapped)
			mhi_cntrl->unmap_single(mhi_cntrl, buf_info);

		mhi_del_ring_element(mhi_cntrl, buf_ring);
		mhi_del_ring_element(mhi_cntrl, tre_ring);

		if (mhi_chan->pre_alloc) {
			pci_mem_free(mhi_cntrl->cntrl_dev, buf_info->len, buf_info->cb_buf);
		} else {
			result.buf_addr = buf_info->cb_buf;
			mhi_chan->xfer_cb(mhi_chan->mhi_dev, &result);
		}
	}
}

void mhi_reset_chan(struct mhi_controller *mhi_cntrl, struct mhi_chan *mhi_chan)
{
	struct mhi_event *mhi_event;
	struct mhi_event_ctxt *er_ctxt;
	int chan = mhi_chan->chan;

	/* Nothing to reset, client doesn't queue buffers */
	if (mhi_chan->offload_ch)
		return;

	read_lock_bh(&mhi_cntrl->pm_lock);
	mhi_event = &mhi_cntrl->mhi_event[mhi_chan->er_index];
	er_ctxt = &mhi_cntrl->mhi_ctxt->er_ctxt[mhi_chan->er_index];

	mhi_mark_stale_events(mhi_cntrl, mhi_event, er_ctxt, chan);

	mhi_reset_data_chan(mhi_cntrl, mhi_chan);

	read_unlock_bh(&mhi_cntrl->pm_lock);
}

/* Move channel to start state */
int mhi_prepare_for_transfer(struct mhi_device *mhi_dev)
{
	int ret, dir;
	struct mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	struct mhi_chan *mhi_chan;

	for (dir = 0; dir < 2; dir++) {
		mhi_chan = dir ? mhi_dev->dl_chan : mhi_dev->ul_chan;
		if (!mhi_chan)
			continue;

		ret = mhi_prepare_channel(mhi_cntrl, mhi_chan);
		if (ret)
			goto error_open_chan;
	}

	return 0;

error_open_chan:
	for (--dir; dir >= 0; dir--) {
		mhi_chan = dir ? mhi_dev->dl_chan : mhi_dev->ul_chan;
		if (!mhi_chan)
			continue;

		__mhi_unprepare_channel(mhi_cntrl, mhi_chan);
	}

	return ret;
}
EXPORT_SYMBOL_GPL(mhi_prepare_for_transfer);

void mhi_unprepare_from_transfer(struct mhi_device *mhi_dev)
{
	struct mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	struct mhi_chan *mhi_chan;
	int dir;

	for (dir = 0; dir < 2; dir++) {
		mhi_chan = dir ? mhi_dev->ul_chan : mhi_dev->dl_chan;
		if (!mhi_chan)
			continue;

		__mhi_unprepare_channel(mhi_cntrl, mhi_chan);
	}
}
EXPORT_SYMBOL_GPL(mhi_unprepare_from_transfer);

int mhi_poll(struct mhi_device *mhi_dev, u32 budget)
{
	struct mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	struct mhi_chan *mhi_chan = mhi_dev->dl_chan;
	struct mhi_event *mhi_event = &mhi_cntrl->mhi_event[mhi_chan->er_index];
	int ret;

	spin_lock_bh(&mhi_event->lock);
	ret = mhi_event->process_event(mhi_cntrl, mhi_event, budget);
	spin_unlock_bh(&mhi_event->lock);

	return ret;
}
EXPORT_SYMBOL_GPL(mhi_poll);
