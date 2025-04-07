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
 9/26/21   zxue     handle irq with budget
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include "mhi.h"
#include "internal.h"



/*
 * Not all MHI state transitions are synchronous. Transitions like Linkdown,
 * SYS_ERR, and shutdown can happen anytime asynchronously. This function will
 * transition to a new state only if we're allowed to.
 *
 * Priority increases as we go down. For instance, from any state in L0, the
 * transition can be made to states in L1, L2 and L3. A notable exception to
 * this rule is state DISABLE.  From DISABLE state we can only transition to
 * POR state. Also, while in L2 state, user cannot jump back to previous
 * L1 or L0 states.
 *
 * Valid transitions:
 * L0: DISABLE <--> POR
 *     POR <--> POR
 *     POR -> M0 -> M2 --> M0
 *     POR -> FW_DL_ERR
 *     FW_DL_ERR <--> FW_DL_ERR
 *     M0 <--> M0
 *     M0 -> FW_DL_ERR
 *     M0 -> M3_ENTER -> M3 -> M3_EXIT --> M0
 * L1: SYS_ERR_DETECT -> SYS_ERR_PROCESS --> POR
 * L2: SHUTDOWN_PROCESS -> DISABLE
 * L3: LD_ERR_FATAL_DETECT <--> LD_ERR_FATAL_DETECT
 *     LD_ERR_FATAL_DETECT -> SHUTDOWN_PROCESS
 */
static struct mhi_pm_transitions const dev_state_transitions[] = {
	/* L0 States */
	{
		MHI_PM_DISABLE,
		MHI_PM_POR
	},
	{
		MHI_PM_POR,
		MHI_PM_POR | MHI_PM_DISABLE | MHI_PM_M0 |
		MHI_PM_SYS_ERR_DETECT | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT | MHI_PM_FW_DL_ERR
	},
	{
		MHI_PM_M0,
		MHI_PM_M0 | MHI_PM_M2 | MHI_PM_M3_ENTER |
		MHI_PM_SYS_ERR_DETECT | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT | MHI_PM_FW_DL_ERR
	},
	{
		MHI_PM_M2,
		MHI_PM_M0 | MHI_PM_SYS_ERR_DETECT | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT
	},
	{
		MHI_PM_M3_ENTER,
		MHI_PM_M3 | MHI_PM_SYS_ERR_DETECT | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT
	},
	{
		MHI_PM_M3,
		MHI_PM_M3_EXIT | MHI_PM_SYS_ERR_DETECT |
		MHI_PM_SHUTDOWN_PROCESS | MHI_PM_LD_ERR_FATAL_DETECT
	},
	{
		MHI_PM_M3_EXIT,
		MHI_PM_M0 | MHI_PM_SYS_ERR_DETECT | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT
	},
	{
		MHI_PM_FW_DL_ERR,
		MHI_PM_FW_DL_ERR | MHI_PM_SYS_ERR_DETECT |
		MHI_PM_SHUTDOWN_PROCESS | MHI_PM_LD_ERR_FATAL_DETECT
	},
	/* L1 States */
	{
		MHI_PM_SYS_ERR_DETECT,
		MHI_PM_SYS_ERR_PROCESS | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT
	},
	{
		MHI_PM_SYS_ERR_PROCESS,
		MHI_PM_POR | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT
	},
	/* L2 States */
	{
		MHI_PM_SHUTDOWN_PROCESS,
		MHI_PM_DISABLE | MHI_PM_LD_ERR_FATAL_DETECT
	},
	/* L3 States */
	{
		MHI_PM_LD_ERR_FATAL_DETECT,
		MHI_PM_LD_ERR_FATAL_DETECT | MHI_PM_SHUTDOWN_PROCESS
	},
};

#define PCIE_SOC_GLOBAL_RESET (0x3008)
#define PCIE_SOC_GLOBAL_RESET_V 1

#define PCIE_REMAP_1M_BAR_CTRL (0x310c)

#define WLAON_WARM_SW_ENTRY (0x1f80504)

#define MAX_UNWINDOWED_ADDRESS 0x80000
#define WINDOW_ENABLE_BIT 0x40000000
#define WINDOW_REG_ADDRESS 0x310C
#define WINDOW_SHIFT 19
#define WINDOW_VALUE_MASK 0x3F
#define WINDOW_START MAX_UNWINDOWED_ADDRESS
#define WINDOW_RANGE_MASK 0x7FFFF

/* EFI access offset directly */
#define MHI_BASE_OFFSET(B) (u32)((u8*)(B) - (u8*)0)

static inline void mhi_reg_select_window(
    struct mhi_controller *mhi_cntrl, 
    void __iomem *io_addr, u32 offset)
{
	u32 window = (offset >> WINDOW_SHIFT) & WINDOW_VALUE_MASK;

	pci_write32(mhi_cntrl->cntrl_dev, 
        MHI_BASE_OFFSET(io_addr) + PCIE_REMAP_1M_BAR_CTRL, 
        WINDOW_ENABLE_BIT | window);
}

u32 mhi_reg_read_remap(struct mhi_controller *mhi_cntrl,
		       void __iomem *io_addr,
		       uintptr_t io_offset, u32 *val)
{
	//mhi_check_assert_wake(mhi_dev_ctxt, io_offset);

	if (io_offset < MAX_UNWINDOWED_ADDRESS) {
		*val = pci_read32(mhi_cntrl->cntrl_dev, MHI_BASE_OFFSET(io_addr) + io_offset);
	} else {
		mhi_reg_select_window(mhi_cntrl, io_addr, io_offset);
		*val = pci_read32(mhi_cntrl->cntrl_dev, MHI_BASE_OFFSET(io_addr) + WINDOW_START +
				(io_offset & WINDOW_RANGE_MASK));
	}
	return 0;
	//mhi_check_deassert_wake(mhi_dev_ctxt, io_offset);
}

void mhi_reg_write_remap(struct mhi_controller *mhi_cntrl,
			 void __iomem *io_addr,
			 uintptr_t io_offset, u32 val)
{
	//mhi_check_assert_wake(mhi_dev_ctxt, io_offset);

	if (io_offset < MAX_UNWINDOWED_ADDRESS) {
        pci_write32(mhi_cntrl->cntrl_dev, MHI_BASE_OFFSET(io_addr) + io_offset, val);
	} else {
		mhi_reg_select_window(mhi_cntrl, io_addr, io_offset);
        pci_write32(mhi_cntrl->cntrl_dev, MHI_BASE_OFFSET(io_addr) + WINDOW_START +
				(io_offset & WINDOW_RANGE_MASK), val);
	}

	//mhi_check_deassert_wake(mhi_dev_ctxt, io_offset);
}

void mhi_set_pcie_mhictrl_reset(struct mhi_controller *mhi_cntrl)
{
	u32 val;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;

	mhi_reg_read_remap(mhi_cntrl,
			   mhi_cntrl->regs,
			   MHISTATUS, &val);
	mhi_dbg("MHISTATUS 0x%x\n", val);

	/* Observed on Hastings that after SOC_GLOBAL_RESET, MHISTATUS
	 * has SYSERR bit set and thus need to set MHICTRL_RESET
	 * to clear SYSERR.
	 */
	mhi_reg_write_remap(mhi_cntrl,
			    mhi_cntrl->regs,
			    MHICTRL, MHICTRL_RESET_MASK);

	mdelay(10);
}

void mhi_set_pcie_soc_global_reset(struct mhi_controller *mhi_cntrl)
{
	u32 val;
	u32 delay;

	mhi_reg_read_remap(mhi_cntrl,
			   mhi_cntrl->regs,
			   PCIE_SOC_GLOBAL_RESET, &val);
	val |= PCIE_SOC_GLOBAL_RESET_V;
	mhi_reg_write_remap(mhi_cntrl,
			    mhi_cntrl->regs,
			    PCIE_SOC_GLOBAL_RESET, val);

	/* TODO: exact time to sleep is uncertain */
	delay = 10;
	mdelay(delay);

	/* Need to toggle V bit back otherwise stuck in reset status */
	val &= ~PCIE_SOC_GLOBAL_RESET_V;
	mhi_reg_write_remap(mhi_cntrl,
			    mhi_cntrl->regs,
			    PCIE_SOC_GLOBAL_RESET, val);

	mdelay(delay);
}

void mhi_reset_pcie_txvecdb(struct mhi_controller *mhi_cntrl)
{
	mhi_reg_write_remap(mhi_cntrl,
			    mhi_cntrl->regs,
			    PCIE_TXVECDB, 0);
}

void mhi_reset_pcie_txvecstatus(struct mhi_controller *mhi_cntrl)
{
	mhi_reg_write_remap(mhi_cntrl,
			    mhi_cntrl->regs,
			    PCIE_TXVECSTATUS, 0);
}

void mhi_reset_pcie_rxvecdb(struct mhi_controller *mhi_cntrl)
{
	mhi_reg_write_remap(mhi_cntrl,
			    mhi_cntrl->regs,
			    PCIE_RXVECDB, 0);
}

void mhi_reset_pcie_rxvecstatus(struct mhi_controller *mhi_cntrl)
{
	mhi_reg_write_remap(mhi_cntrl,
			    mhi_cntrl->regs,
			    PCIE_RXVECSTATUS, 0);
}

void mhi_set_wlaon_sw_entry(struct mhi_controller *mhi_cntrl)
{
	u32 val;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;

	mhi_reg_read_remap(mhi_cntrl,
			   mhi_cntrl->regs,
			   WLAON_WARM_SW_ENTRY, &val);
	mhi_dbg("WLAON_WARM_SW_ENTRY 0x%x\n", val);

	mhi_reg_write_remap(mhi_cntrl,
			    mhi_cntrl->regs,
			    WLAON_WARM_SW_ENTRY, 0);

	mdelay(10);
	mhi_reg_read_remap(mhi_cntrl,
			   mhi_cntrl->regs,
			   WLAON_WARM_SW_ENTRY, &val);
    mhi_dbg("WLAON_WARM_SW_ENTRY 0x%x\n", val);
}

void mhi_pcie_sw_reset(struct mhi_controller *mhi_cntrl)
{
	/* Following are needed to unload and reload wlan driver
	 * dynamically without the need to ubplug/plug the device.
	 *
	 * txvecdb, txvecstatus, rxvecdb and rxvecstatus registers
	 * are not cleared upon global reset. Thus reset here per
	 * FW suggestions.
	 *
	 * WLAON domain is cleared to prevent Q6 from going warm
	 * boot path and enter dead loop.
	 *
	 * gloabl reset is triggered to reset SoC and SoC will be
	 * in PBL state then.
	 */
	mhi_reset_pcie_txvecdb(mhi_cntrl);
	mhi_reset_pcie_txvecstatus(mhi_cntrl);
	mhi_reset_pcie_rxvecdb(mhi_cntrl);
	mhi_reset_pcie_rxvecstatus(mhi_cntrl);
	mhi_set_wlaon_sw_entry(mhi_cntrl);
	mhi_set_pcie_soc_global_reset(mhi_cntrl);
	mhi_set_pcie_mhictrl_reset(mhi_cntrl);
}

enum mhi_pm_state __must_check mhi_tryset_pm_state(struct mhi_controller *mhi_cntrl,
						   enum mhi_pm_state state)
{
	unsigned long cur_state = mhi_cntrl->pm_state;
    int index = find_last_bit(&cur_state, 32);

	if (unlikely(index >= ARRAY_SIZE(dev_state_transitions)))
		return cur_state;

	if (unlikely((u32)(dev_state_transitions[index].from_state) != cur_state))
		return cur_state;

	if (unlikely(!(dev_state_transitions[index].to_states & state)))
		return cur_state;

	mhi_cntrl->pm_state = state;
	return mhi_cntrl->pm_state;
}

void mhi_set_mhi_state(struct mhi_controller *mhi_cntrl, enum mhi_state state)
{
	if (state == MHI_STATE_RESET) {
		mhi_write_reg_field(mhi_cntrl, mhi_cntrl->regs, MHICTRL,
				    MHICTRL_RESET_MASK, MHICTRL_RESET_SHIFT, 1);
	} else {
		mhi_write_reg_field(mhi_cntrl, mhi_cntrl->regs, MHICTRL,
				    MHICTRL_MHISTATE_MASK,
				    MHICTRL_MHISTATE_SHIFT, state);
	}
}

/* NOP for backward compatibility, host allowed to ring DB in M2 state */
static void mhi_toggle_dev_wake_nop(struct mhi_controller *mhi_cntrl)
{
}

static void mhi_toggle_dev_wake(struct mhi_controller *mhi_cntrl)
{
	mhi_cntrl->wake_get(mhi_cntrl, false);
	mhi_cntrl->wake_put(mhi_cntrl, true);
}

/* Handle device ready state transition */
int mhi_ready_state_transition(struct mhi_controller *mhi_cntrl)
{
	void __iomem *base = mhi_cntrl->regs;
	struct mhi_event *mhi_event;
	enum mhi_pm_state cur_state;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;
	u32 reset = 1, ready = 0;
	int ret, i;

	/* Wait for RESET to be cleared and READY bit to be set by the device */
    wait_event_timeout(mhi_cntrl->state_event,
		             MHI_PM_IN_FATAL_STATE(mhi_cntrl->pm_state) ||
			         mhi_read_reg_field(mhi_cntrl, base, MHICTRL,
					      MHICTRL_RESET_MASK,
					      MHICTRL_RESET_SHIFT, &reset) ||
			         mhi_read_reg_field(mhi_cntrl, base, MHISTATUS,
					      MHISTATUS_READY_MASK,
					      MHISTATUS_READY_SHIFT, &ready) ||
			         (!reset && ready),
		             msecs_to_jiffies(mhi_cntrl->timeout_ms),
		             ret);

	/* Check if device entered error state */
	if (MHI_PM_IN_FATAL_STATE(mhi_cntrl->pm_state)) {
        mhi_err("Device link is not accessible\n");
		return -EIO;
	}

	/* Timeout if device did not transition to ready state */
	if (reset || !ready) {
        mhi_err("Device Ready timeout reset = %x, ready = %x\n", reset, ready);
		return -ETIMEDOUT;
	}

    mhi_dbg("Device in READY State\n");
	write_lock_irq(&mhi_cntrl->pm_lock);
	cur_state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_POR);
	mhi_cntrl->dev_state = MHI_STATE_READY;
	write_unlock_irq(&mhi_cntrl->pm_lock);

	if (cur_state != MHI_PM_POR) {
		mhi_err("Error moving to state %a from %a\n", 
		          to_mhi_pm_state_str(MHI_PM_POR), to_mhi_pm_state_str(cur_state));
		return -EIO;
	}

	read_lock_bh(&mhi_cntrl->pm_lock);
	if (!MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) {
        mhi_err("Device registers not accessible\n");
		goto error_mmio;
	}

	/* Configure MMIO registers */
	ret = mhi_init_mmio(mhi_cntrl);
	if (ret) {
        mhi_err("Error configuring MMIO registers\n");
		goto error_mmio;
	}

	/* Add elements to all SW event rings */
	mhi_event = mhi_cntrl->mhi_event;
	for (i = 0; i < (int)mhi_cntrl->total_ev_rings; i++, mhi_event++) {
		struct mhi_ring *ring = &mhi_event->ring;

		/* Skip if this is an offload or HW event */
		if (mhi_event->offload_ev || mhi_event->hw_ring)
			continue;

		ring->wp = (u8*)ring->base + ring->len - ring->el_size;
		*ring->ctxt_wp = ring->iommu_base + ring->len - ring->el_size;
		/* Update all cores */
		smp_wmb();

		/* Ring the event ring db */
		spin_lock_irq(&mhi_event->lock);
		mhi_ring_er_db(mhi_event);
		spin_unlock_irq(&mhi_event->lock);
	}

	/* Set MHI to M0 state */
	mhi_set_mhi_state(mhi_cntrl, MHI_STATE_M0);
	read_unlock_bh(&mhi_cntrl->pm_lock);

	return 0;

error_mmio:
	read_unlock_bh(&mhi_cntrl->pm_lock);

	return -EIO;
}

int mhi_pm_m0_transition(struct mhi_controller *mhi_cntrl)
{
	enum mhi_pm_state cur_state;
	struct mhi_chan *mhi_chan;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;
	int i;

	write_lock_irq(&mhi_cntrl->pm_lock);
	mhi_cntrl->dev_state = MHI_STATE_M0;
	cur_state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_M0);
	write_unlock_irq(&mhi_cntrl->pm_lock);
	if (unlikely(cur_state != MHI_PM_M0)) {
        mhi_err("Unable to transition to M0 state, cur_state=%u\n", cur_state);
		return -EIO;
	}

	/* Wake up the device */
	read_lock_bh(&mhi_cntrl->pm_lock);
	mhi_cntrl->wake_get(mhi_cntrl, true);

	/* Ring all event rings and CMD ring only if we're in mission mode */
	if (MHI_IN_MISSION_MODE(mhi_cntrl->ee)) {
		struct mhi_event *mhi_event = mhi_cntrl->mhi_event;
		struct mhi_cmd *mhi_cmd =
			&mhi_cntrl->mhi_cmd[PRIMARY_CMD_RING];

		for (i = 0; i < (int)mhi_cntrl->total_ev_rings; i++, mhi_event++) {
			if (mhi_event->offload_ev)
				continue;

			spin_lock_irq(&mhi_event->lock);
			mhi_ring_er_db(mhi_event);
			spin_unlock_irq(&mhi_event->lock);
		}

		/* Only ring primary cmd ring if ring is not empty */
		spin_lock_irq(&mhi_cmd->lock);
		if (mhi_cmd->ring.rp != mhi_cmd->ring.wp)
			mhi_ring_cmd_db(mhi_cntrl, mhi_cmd);
		spin_unlock_irq(&mhi_cmd->lock);
	}

	/* Ring channel DB registers */
	mhi_chan = mhi_cntrl->mhi_chan;
	for (i = 0; i < (int)mhi_cntrl->max_chan; i++, mhi_chan++) {
		struct mhi_ring *tre_ring = &mhi_chan->tre_ring;

		write_lock_irq(&mhi_chan->lock);
		if (mhi_chan->db_cfg.reset_req)
			mhi_chan->db_cfg.db_mode = true;

		/* Only ring DB if ring is not empty */
		if (tre_ring->base && tre_ring->wp  != tre_ring->rp)
			mhi_ring_chan_db(mhi_cntrl, mhi_chan);
		write_unlock_irq(&mhi_chan->lock);
	}

	mhi_cntrl->wake_put(mhi_cntrl, false);
	read_unlock_bh(&mhi_cntrl->pm_lock);
	wake_up_all(&mhi_cntrl->state_event);

	return 0;
}

/*
 * After receiving the MHI state change event from the device indicating the
 * transition to M1 state, the host can transition the device to M2 state
 * for keeping it in low power state.
 */
void mhi_pm_m1_transition(struct mhi_controller *mhi_cntrl)
{
	enum mhi_pm_state state;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;

	write_lock_irq(&mhi_cntrl->pm_lock);
	state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_M2);
	if (state == MHI_PM_M2) {
		mhi_set_mhi_state(mhi_cntrl, MHI_STATE_M2);
		mhi_cntrl->dev_state = MHI_STATE_M2;

		write_unlock_irq(&mhi_cntrl->pm_lock);
        wake_up_all(&mhi_cntrl->state_event);

		/* If there are any pending resources, exit M2 immediately */
		if (unlikely(atomic_read(&mhi_cntrl->pending_pkts) ||
			     atomic_read(&mhi_cntrl->dev_wake))) {
			mhi_dbg("Exiting M2, pending_pkts: %d dev_wake: %d\n",
				atomic_read(&mhi_cntrl->pending_pkts),
				atomic_read(&mhi_cntrl->dev_wake));
			read_lock_bh(&mhi_cntrl->pm_lock);
			mhi_cntrl->wake_get(mhi_cntrl, true);
			mhi_cntrl->wake_put(mhi_cntrl, true);
			read_unlock_bh(&mhi_cntrl->pm_lock);
		} else {
			mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_IDLE);
		}
	} else {
		write_unlock_irq(&mhi_cntrl->pm_lock);
	}
}

/* MHI M3 completion handler */
int mhi_pm_m3_transition(struct mhi_controller *mhi_cntrl)
{
	enum mhi_pm_state state;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;

	write_lock_irq(&mhi_cntrl->pm_lock);
	mhi_cntrl->dev_state = MHI_STATE_M3;
	state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_M3);
	write_unlock_irq(&mhi_cntrl->pm_lock);
	if (state != MHI_PM_M3) {
		mhi_err("Unable to transition to M3 state\n");
		return -EIO;
	}

    wake_up_all(&mhi_cntrl->state_event);

	return 0;
}

/* Handle device Mission Mode transition */
static int mhi_pm_mission_mode_transition(struct mhi_controller *mhi_cntrl)
{
	struct mhi_event *mhi_event;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;
	int i, ret;

	mhi_dbg("Processing Mission Mode transition\n");

	write_lock_irq(&mhi_cntrl->pm_lock);
    if (MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) {
        mhi_cntrl->ee = mhi_get_exec_env(mhi_cntrl);
        mhi_dbg("mhi_cntrl->ee=%u\n", mhi_cntrl->ee);
    }
	write_unlock_irq(&mhi_cntrl->pm_lock);

	if (!MHI_IN_MISSION_MODE(mhi_cntrl->ee)) {
		mhi_err("Invalid EE for Mission Mode: %s\n",
			TO_MHI_EXEC_STR(mhi_cntrl->ee));
		return -EIO;
    }

	mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_EE_MISSION_MODE);

    wake_up_all(&mhi_cntrl->state_event);

	/* Force MHI to be in M0 state before continuing */
	ret = __mhi_device_get_sync(mhi_cntrl);
	if (ret)
		return ret;

	read_lock_bh(&mhi_cntrl->pm_lock);

	if (MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) {
		ret = -EIO;
		goto error_mission_mode;
	}

	/* Add elements to all HW event rings */
	mhi_event = mhi_cntrl->mhi_event;
	for (i = 0; i < (int)mhi_cntrl->total_ev_rings; i++, mhi_event++) {
		struct mhi_ring *ring = &mhi_event->ring;

		if (mhi_event->offload_ev || !mhi_event->hw_ring)
			continue;

		ring->wp = (u8*)(ring->base) + ring->len - ring->el_size;
		*ring->ctxt_wp = ring->iommu_base + ring->len - ring->el_size;
		/* Update to all cores */
		smp_wmb();

		spin_lock_irq(&mhi_event->lock);
		if (MHI_DB_ACCESS_VALID(mhi_cntrl))
			mhi_ring_er_db(mhi_event);
		spin_unlock_irq(&mhi_event->lock);
	}

	read_unlock_bh(&mhi_cntrl->pm_lock);

	/*
	 * The MHI devices are only created when the client device switches its
	 * Execution Environment (EE) to either SBL or AMSS states
	 */
	mhi_create_devices(mhi_cntrl);

	read_lock_bh(&mhi_cntrl->pm_lock);

error_mission_mode:
	mhi_cntrl->wake_put(mhi_cntrl, false);
	read_unlock_bh(&mhi_cntrl->pm_lock);

	return ret;
}

/* Handle SYS_ERR and Shutdown transitions */
static void mhi_pm_disable_transition(struct mhi_controller *mhi_cntrl,
				      enum mhi_pm_state transition_state)
{
	enum mhi_pm_state cur_state, prev_state;
	struct mhi_event *mhi_event;
	struct mhi_cmd_ctxt *cmd_ctxt;
	struct mhi_cmd *mhi_cmd;
	struct mhi_event_ctxt *er_ctxt;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;
    struct mhi_device *mhi_dev, *tmp;
	int ret, i;

    mhi_dbg("Transitioning from PM state: %a to: %a\n",
		to_mhi_pm_state_str(mhi_cntrl->pm_state),
		to_mhi_pm_state_str(transition_state));

	/* We must notify MHI control driver so it can clean up first */
	if (transition_state == MHI_PM_SYS_ERR_PROCESS) {
		/*
		 * If controller supports RDDM, we do not process
		 * SYS error state, instead we will jump directly
		 * to RDDM state
		 */
		if (mhi_cntrl->rddm_image) {
            mhi_err("Controller supports RDDM, so skip SYS_ERR\n");
            mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_EE_RDDM);
			return;
		}
		mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_SYS_ERROR);
	}

	mutex_lock(&mhi_cntrl->pm_mutex);
	write_lock_irq(&mhi_cntrl->pm_lock);
	prev_state = mhi_cntrl->pm_state;
	cur_state = mhi_tryset_pm_state(mhi_cntrl, transition_state);
	if (cur_state == transition_state) {
		mhi_cntrl->ee = MHI_EE_DISABLE_TRANSITION;
		mhi_cntrl->dev_state = MHI_STATE_RESET;
	}
	write_unlock_irq(&mhi_cntrl->pm_lock);

    /* Wake up threads waiting for state transition */
    wake_up_all(&mhi_cntrl->state_event);
	
	if (cur_state != transition_state) {
		mhi_err("Failed to transition to state: %a from: %a\n",
			to_mhi_pm_state_str(transition_state),
			to_mhi_pm_state_str(cur_state));
		mutex_unlock(&mhi_cntrl->pm_mutex);
		return;
	}

	/*
	 * Trigger MHI RESET so that the device will not access host memory.
	 * skip MHI reset if device is in RDDM.
	 */
	if (MHI_REG_ACCESS_VALID(prev_state) &&
		(mhi_cntrl->rddm_image &&
		mhi_get_exec_env(mhi_cntrl) != MHI_EE_RDDM)) {
		u32 in_reset = MAX_UINT32;
		unsigned long timeout = msecs_to_jiffies(mhi_cntrl->timeout_ms);

		mhi_dbg("Triggering MHI Reset in device\n");
		mhi_set_mhi_state(mhi_cntrl, MHI_STATE_RESET);

		/* Wait for the reset bit to be cleared by the device */
        wait_event_timeout(mhi_cntrl->state_event,
		             MHI_PM_IN_FATAL_STATE(mhi_cntrl->pm_state) ||
		             mhi_read_reg_field(mhi_cntrl,
								    mhi_cntrl->regs,
								    MHICTRL,
								    MHICTRL_RESET_MASK,
								    MHICTRL_RESET_SHIFT,
								    &in_reset) || !in_reset,
		             timeout,
		             ret);
		
        if ((!ret || in_reset) && cur_state == MHI_PM_SYS_ERR_PROCESS) {
			mhi_err("Device failed to exit MHI Reset state\n");
			mutex_unlock(&mhi_cntrl->pm_mutex);
			return;
		}
		/*
		 * Device will clear BHI_INTVEC as a part of RESET processing,
		 * hence re-program it
		 */
		//mhi_write_reg(mhi_cntrl, mhi_cntrl->bhi, BHI_INTVEC, 0);
	}

	mhi_dbg("Waiting for all pending event ring processing to complete\n");
	mhi_event = mhi_cntrl->mhi_event;
	for (i = 0; (u32)i < mhi_cntrl->total_ev_rings; i++, mhi_event++) {
		if (mhi_event->offload_ev)
			continue;
		//tasklet_kill(&mhi_event->task);
        mhi_irq_handler(mhi_cntrl->irq[mhi_event->irq], INT_MAX, mhi_event);
	}

	/* Release lock and wait for all pending threads to complete */
	mutex_unlock(&mhi_cntrl->pm_mutex);
	mhi_dbg("Waiting for all pending threads to complete\n");
    wake_up_all(&mhi_cntrl->state_event);
	
    mhi_dbg("Reset all active channels and remove MHI devices\n");
	//device_for_each_child(mhi_cntrl->cntrl_dev, NULL, mhi_destroy_device);
    list_for_each_entry_safe(mhi_dev, tmp, &mhi_cntrl->mhi_dev_list, 
        struct mhi_device, node) {
        mhi_destroy_device(mhi_dev, NULL);
    }
    
    /* drain any pending rx */
    poll_irqs(16);

	mutex_lock(&mhi_cntrl->pm_mutex);

	WARN_ON(atomic_read(&mhi_cntrl->dev_wake));
	WARN_ON(atomic_read(&mhi_cntrl->pending_pkts));

	/* Reset the ev rings and cmd rings */
	mhi_dbg("Resetting EV CTXT and CMD CTXT\n");
	mhi_cmd = mhi_cntrl->mhi_cmd;
	cmd_ctxt = mhi_cntrl->mhi_ctxt->cmd_ctxt;
	for (i = 0; i < NR_OF_CMD_RINGS; i++, mhi_cmd++, cmd_ctxt++) {
		struct mhi_ring *ring = &mhi_cmd->ring;

		ring->rp = ring->base;
		ring->wp = ring->base;
		cmd_ctxt->rp = cmd_ctxt->rbase;
		cmd_ctxt->wp = cmd_ctxt->rbase;
	}

	mhi_event = mhi_cntrl->mhi_event;
	er_ctxt = mhi_cntrl->mhi_ctxt->er_ctxt;
	for (i = 0; i < (int)mhi_cntrl->total_ev_rings; i++, er_ctxt++,
		     mhi_event++) {
		struct mhi_ring *ring = &mhi_event->ring;

		/* Skip offload events */
		if (mhi_event->offload_ev)
			continue;

		ring->rp = ring->base;
		ring->wp = ring->base;
		er_ctxt->rp = er_ctxt->rbase;
		er_ctxt->wp = er_ctxt->rbase;
	}

	if (cur_state == MHI_PM_SYS_ERR_PROCESS) {
		mhi_ready_state_transition(mhi_cntrl);
	} else {
		/* Move to disable state */
		write_lock_irq(&mhi_cntrl->pm_lock);
		cur_state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_DISABLE);
		write_unlock_irq(&mhi_cntrl->pm_lock);
		if (unlikely(cur_state != MHI_PM_DISABLE))
		    mhi_err("Error moving from PM state: %a to: %a\n",
				to_mhi_pm_state_str(cur_state),
				to_mhi_pm_state_str(MHI_PM_DISABLE));
	}
	
    mhi_dbg("Exiting with PM state: %a, MHI state: %a\n",
		to_mhi_pm_state_str(mhi_cntrl->pm_state),
		TO_MHI_STATE_STR(mhi_cntrl->dev_state));

	mutex_unlock(&mhi_cntrl->pm_mutex);
}

/* Queue a new work item and schedule work */
int mhi_queue_state_transition(struct mhi_controller *mhi_cntrl,
			       enum dev_st_transition state)
{
	struct state_transition *item = kmalloc(sizeof(*item), GFP_ATOMIC);
	
	unsigned long flags;

	if (!item)
		return -ENOMEM;

	item->state = state;
	spin_lock_irqsave(&mhi_cntrl->transition_lock, flags);
	list_add_tail(&item->node, &mhi_cntrl->transition_list);
	spin_unlock_irqrestore(&mhi_cntrl->transition_lock, flags);

	schedule_work(&mhi_cntrl->st_worker);

	return 0;
}


/* SYS_ERR worker */
void mhi_pm_sys_err_worker(void *context)
{
	struct mhi_controller *mhi_cntrl = context;

	mhi_pm_disable_transition(mhi_cntrl, MHI_PM_SYS_ERR_PROCESS);
}


/* Device State Transition worker */
void mhi_pm_st_worker(void *context)
{
	struct state_transition *itr, *tmp;
    struct mhi_controller *mhi_cntrl = context;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;

    list_for_each_entry_safe(itr, tmp, 
        &mhi_cntrl->transition_list, struct state_transition, node) {
        list_del(&itr->node);

		mhi_dbg("Handling state transition: %a\n", TO_DEV_STATE_TRANS_STR(itr->state));

		switch (itr->state) {
		case DEV_ST_TRANSITION_PBL:
			write_lock_irq(&mhi_cntrl->pm_lock);
			if (MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) {
				mhi_cntrl->ee = mhi_get_exec_env(mhi_cntrl);
				mhi_dbg("mhi_cntrl->ee = %X\n", mhi_cntrl->ee);
			} else {
                mhi_dbg("MHI_REG_ACCESS_VALID NONONO!\n");
			}
			write_unlock_irq(&mhi_cntrl->pm_lock);
            if (MHI_IN_PBL(mhi_cntrl->ee))
                wake_up_all(&mhi_cntrl->state_event);
			break;
		case DEV_ST_TRANSITION_SBL:
			write_lock_irq(&mhi_cntrl->pm_lock);
			mhi_cntrl->ee = MHI_EE_SBL;
			write_unlock_irq(&mhi_cntrl->pm_lock);
			/*
			 * The MHI devices are only created when the client
			 * device switches its Execution Environment (EE) to
			 * either SBL or AMSS states
			 */
			mhi_create_devices(mhi_cntrl);
			break;
		case DEV_ST_TRANSITION_MISSION_MODE:
			mhi_pm_mission_mode_transition(mhi_cntrl);
			break;
		case DEV_ST_TRANSITION_READY:
			mhi_ready_state_transition(mhi_cntrl);
			break;
		default:
			break;
		}
		kfree(itr);
	}
}

int __mhi_device_get_sync(struct mhi_controller *mhi_cntrl)
{
    int ret = 1;

	/* Wake up the device */
	read_lock_bh(&mhi_cntrl->pm_lock);
	mhi_cntrl->wake_get(mhi_cntrl, true);
	if (MHI_PM_IN_SUSPEND_STATE(mhi_cntrl->pm_state)) {
		//pm_wakeup_event(&mhi_cntrl->mhi_dev->dev, 0);
		mhi_cntrl->runtime_get(mhi_cntrl);
		mhi_cntrl->runtime_put(mhi_cntrl);
	}
	read_unlock_bh(&mhi_cntrl->pm_lock);
	/* TODOTODO: Will NOT poll the IRQ for dead-loop issue, will try to start a Timer to check the IRQ.*/
#if 0
    wait_event_timeout(mhi_cntrl->state_event,
		             mhi_cntrl->pm_state == MHI_PM_M0 ||
		             MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state),
		             mhi_cntrl->timeout_ms,
		             ret);

    mhi_dbg("mhi_cntrl->pm_state=%x\n", mhi_cntrl->pm_state);
#endif

	if (!ret || MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) {
		read_lock_bh(&mhi_cntrl->pm_lock);
		mhi_cntrl->wake_put(mhi_cntrl, false);
		read_unlock_bh(&mhi_cntrl->pm_lock);
		return -EIO;
	}

	return 0;
}

/* Assert device wake db */
static void mhi_assert_dev_wake(struct mhi_controller *mhi_cntrl, bool force)
{
	unsigned long flags;

	/*
	 * If force flag is set, then increment the wake count value and
	 * ring wake db
	 */
	if (unlikely(force)) {
		spin_lock_irqsave(&mhi_cntrl->wlock, flags);
		atomic_inc(&mhi_cntrl->dev_wake);
		if (MHI_WAKE_DB_FORCE_SET_VALID(mhi_cntrl->pm_state) &&
		    !mhi_cntrl->wake_set) {
			mhi_write_db(mhi_cntrl, mhi_cntrl->wake_db, 1);
			mhi_cntrl->wake_set = true;
		}
		spin_unlock_irqrestore(&mhi_cntrl->wlock, flags);
	} else {
		/*
		 * If resources are already requested, then just increment
		 * the wake count value and return
		 */
		if (likely(atomic_add_unless(&mhi_cntrl->dev_wake, 1, 0)))
			return;

		spin_lock_irqsave(&mhi_cntrl->wlock, flags);
		if ((atomic_inc_return(&mhi_cntrl->dev_wake) == 1) &&
		    MHI_WAKE_DB_SET_VALID(mhi_cntrl->pm_state) &&
		    !mhi_cntrl->wake_set) {
			mhi_write_db(mhi_cntrl, mhi_cntrl->wake_db, 1);
			mhi_cntrl->wake_set = true;
		}
		spin_unlock_irqrestore(&mhi_cntrl->wlock, flags);
	}
}

/* De-assert device wake db */
static void mhi_deassert_dev_wake(struct mhi_controller *mhi_cntrl,
				  bool override)
{
	unsigned long flags;

	/*
	 * Only continue if there is a single resource, else just decrement
	 * and return
	 */
	if (likely(atomic_add_unless(&mhi_cntrl->dev_wake, -1, 1)))
		return;

	spin_lock_irqsave(&mhi_cntrl->wlock, flags);
	if ((atomic_dec_return(&mhi_cntrl->dev_wake) == 0) &&
	    MHI_WAKE_DB_CLEAR_VALID(mhi_cntrl->pm_state) && !override &&
	    mhi_cntrl->wake_set) {
		mhi_write_db(mhi_cntrl, mhi_cntrl->wake_db, 0);
		mhi_cntrl->wake_set = false;
	}
	spin_unlock_irqrestore(&mhi_cntrl->wlock, flags);
}

int mhi_async_power_up(struct mhi_controller *mhi_cntrl)
{
	enum mhi_ee_type current_ee;
	enum dev_st_transition next_state;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;
	u32 val;
	int ret;
	
    mhi_dbg("Requested to power ON\n");


	if (mhi_cntrl->nr_irqs < mhi_cntrl->total_ev_rings)
		return -EINVAL;

	/* Supply default wake routines if not provided by controller driver */
	if (!mhi_cntrl->wake_get || !mhi_cntrl->wake_put ||
	    !mhi_cntrl->wake_toggle) {
		mhi_cntrl->wake_get = mhi_assert_dev_wake;
		mhi_cntrl->wake_put = mhi_deassert_dev_wake;
		mhi_cntrl->wake_toggle = (mhi_cntrl->db_access & MHI_PM_M2) ?
			mhi_toggle_dev_wake_nop : mhi_toggle_dev_wake;
	}

	mutex_lock(&mhi_cntrl->pm_mutex);
	mhi_cntrl->pm_state = MHI_PM_DISABLE;

	if (!mhi_cntrl->pre_init) {
		/* Setup device context */
		ret = mhi_init_dev_ctxt(mhi_cntrl);
		if (ret)
			goto error_dev_ctxt;
	}

	ret = mhi_init_irq_setup(mhi_cntrl);
	if (ret)
		goto error_setup_irq;

	/* Setup BHI offset & INTVEC */
	write_lock_irq(&mhi_cntrl->pm_lock);
	ret = mhi_read_reg(mhi_cntrl, mhi_cntrl->regs, BHIOFF, &val);
	if (ret) {
		write_unlock_irq(&mhi_cntrl->pm_lock);
		goto error_bhi_offset;
	}

	mhi_cntrl->bhi = (u8*)mhi_cntrl->regs + val;
    mhi_err("BHIOFF=0x%x\n", val);

	current_ee = mhi_get_exec_env(mhi_cntrl);
	if (!MHI_IN_PBL(current_ee)) {
		mhi_err("MHI Error state %d\n", current_ee);
		mhi_pcie_sw_reset(mhi_cntrl);
	}

	/* Setup BHIE offset */
	if (mhi_cntrl->fbc_download) {
		ret = mhi_read_reg(mhi_cntrl, mhi_cntrl->regs, BHIEOFF, &val);
		if (ret) {
			write_unlock_irq(&mhi_cntrl->pm_lock);
			mhi_err("Error reading BHIE offset\n");
			goto error_bhi_offset;
		}

		mhi_cntrl->bhie = (u8*)mhi_cntrl->regs + val;
	}

    // DONOT use the IRQ will check
	//mhi_write_reg(mhi_cntrl, mhi_cntrl->bhi, BHI_INTVEC, 0);
	mhi_cntrl->pm_state = MHI_PM_POR;
    mhi_cntrl->ee = MHI_EE_MAX;
    current_ee = mhi_get_exec_env(mhi_cntrl);
	write_unlock_irq(&mhi_cntrl->pm_lock);

	/* Confirm that the device is in valid exec env */
	if (!MHI_IN_PBL(current_ee) && current_ee != MHI_EE_AMSS) {
        mhi_err("Not a valid EE for power on\n");
		ret = -EIO;
		goto error_bhi_offset;
	}

	/* Transition to next state */
	next_state = MHI_IN_PBL(current_ee) ?
        DEV_ST_TRANSITION_PBL : DEV_ST_TRANSITION_READY;
    if (next_state == DEV_ST_TRANSITION_PBL) {
        mhi_queue_state_transition(mhi_cntrl, next_state);
        schedule_work(&mhi_cntrl->fw_worker);
    }
    else {
        mhi_queue_state_transition(mhi_cntrl, next_state);
    }

	mutex_unlock(&mhi_cntrl->pm_mutex);

	mhi_dbg("Power on setup success\n");

	return 0;

error_bhi_offset:
	mhi_deinit_free_irq(mhi_cntrl);

error_setup_irq:
	if (!mhi_cntrl->pre_init)
		mhi_deinit_dev_ctxt(mhi_cntrl);

error_dev_ctxt:
    mhi_dbg("Unlock pm_mutex");
	mutex_unlock(&mhi_cntrl->pm_mutex);

	return ret;
}
EXPORT_SYMBOL_GPL(mhi_async_power_up);

void mhi_power_down(struct mhi_controller *mhi_cntrl, bool graceful)
{
	enum mhi_pm_state cur_state;
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;

	/* If it's not a graceful shutdown, force MHI to linkdown state */
	if (!graceful) {
		mutex_lock(&mhi_cntrl->pm_mutex);
		write_lock_irq(&mhi_cntrl->pm_lock);
		cur_state = mhi_tryset_pm_state(mhi_cntrl,
						MHI_PM_LD_ERR_FATAL_DETECT);
		write_unlock_irq(&mhi_cntrl->pm_lock);
		mutex_unlock(&mhi_cntrl->pm_mutex);
		if (cur_state != MHI_PM_LD_ERR_FATAL_DETECT)
		    mhi_err("Failed to move to state: %a from: %a\n",
				to_mhi_pm_state_str(MHI_PM_LD_ERR_FATAL_DETECT),
				to_mhi_pm_state_str(mhi_cntrl->pm_state));
	}
	mhi_pm_disable_transition(mhi_cntrl, MHI_PM_SHUTDOWN_PROCESS);
	mhi_pcie_sw_reset(mhi_cntrl);
	mhi_deinit_free_irq(mhi_cntrl);

	mhi_cntrl->fw_load_fail = 0;

	if (!mhi_cntrl->pre_init) {
		/* Free all allocated resources */
		if (mhi_cntrl->fbc_image) {
			mhi_free_bhie_table(mhi_cntrl, mhi_cntrl->fbc_image);
			mhi_cntrl->fbc_image = NULL;
		}
		mhi_deinit_dev_ctxt(mhi_cntrl);
	}
}
EXPORT_SYMBOL_GPL(mhi_power_down);

int mhi_sync_power_up(struct mhi_controller *mhi_cntrl)
{
	int ret = mhi_async_power_up(mhi_cntrl);

	if (ret)
		return ret;

    wait_event_timeout(mhi_cntrl->state_event,
		             MHI_IN_MISSION_MODE(mhi_cntrl->ee) ||
		             MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state) ||
		             mhi_cntrl->fw_load_fail,
		             msecs_to_jiffies(mhi_cntrl->timeout_ms),
		             ret);

    mhi_dbg("Current EE=%u fw_load_fail = 0x%x\n", mhi_get_exec_env(mhi_cntrl), mhi_cntrl->fw_load_fail);
	if (mhi_cntrl->fw_load_fail) {
		return mhi_cntrl->fw_load_fail;
	}

	return (MHI_IN_MISSION_MODE(mhi_cntrl->ee)) ? 0 : -EIO;
}
EXPORT_SYMBOL(mhi_sync_power_up);

int mhi_force_rddm_mode(struct mhi_controller *mhi_cntrl)
{
	//struct device *dev = &mhi_cntrl->mhi_dev->dev;
	int ret = 0;

	/* Check if device is already in RDDM */
	if (mhi_cntrl->ee == MHI_EE_RDDM)
		return 0;

	mhi_dbg("Triggering SYS_ERR to force RDDM state\n");
	mhi_set_mhi_state(mhi_cntrl, MHI_STATE_SYS_ERR);

	/* Wait for RDDM event */
    wait_event_timeout(mhi_cntrl->state_event,
		             mhi_cntrl->ee == MHI_EE_RDDM,
		             msecs_to_jiffies(mhi_cntrl->timeout_ms),
		             ret);

    ret = ret ? 0 : -EIO;

	return ret;
}
EXPORT_SYMBOL_GPL(mhi_force_rddm_mode);

void mhi_device_get(struct mhi_device *mhi_dev)
{
	struct mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;

	mhi_dev->dev_wake++;
	read_lock_bh(&mhi_cntrl->pm_lock);
	mhi_cntrl->wake_get(mhi_cntrl, true);
	read_unlock_bh(&mhi_cntrl->pm_lock);
}
EXPORT_SYMBOL_GPL(mhi_device_get);

int mhi_device_get_sync(struct mhi_device *mhi_dev)
{
	struct mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	int ret;

	ret = __mhi_device_get_sync(mhi_cntrl);
	if (!ret)
		mhi_dev->dev_wake++;

	return ret;
}
EXPORT_SYMBOL_GPL(mhi_device_get_sync);

void mhi_device_put(struct mhi_device *mhi_dev)
{
	struct mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;

	mhi_dev->dev_wake--;
	read_lock_bh(&mhi_cntrl->pm_lock);
	if (MHI_PM_IN_SUSPEND_STATE(mhi_cntrl->pm_state)) {
		mhi_cntrl->runtime_get(mhi_cntrl);
		mhi_cntrl->runtime_put(mhi_cntrl);
	}

	mhi_cntrl->wake_put(mhi_cntrl, false);
	read_unlock_bh(&mhi_cntrl->pm_lock);
}
EXPORT_SYMBOL_GPL(mhi_device_put);
