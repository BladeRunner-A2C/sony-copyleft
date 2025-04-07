/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
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
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <qdf/qbase.h>
#include <qdf/cfg.h>
#include <qdf/firmware.h>
#include "internal.h"
#include "mhi.h"

#define SBL_AUTH_FAIL 			  0x0A
#define AMSS_AUTH_FAIL			  0x302E

/* Setup RDDM vector table for RDDM transfer and program RXVEC */
void mhi_rddm_prepare(struct mhi_controller *mhi_cntrl,
		      struct image_info *img_info)
{
    struct mhi_buf *mhi_buf = img_info->mhi_buf;
    struct bhi_vec_entry *bhi_vec = img_info->bhi_vec;
    unsigned int i;

	for (i = 0; i < img_info->entries - 1; i++, mhi_buf++, bhi_vec++) {
		bhi_vec->dma_addr = mhi_buf->aligned_dma_addr;
		bhi_vec->size = mhi_buf->len;
	}
}

void mhi_rddm_set_vector_table(struct mhi_controller *mhi_cntrl)
{
	struct image_info *rddm_image = mhi_cntrl->rddm_image;
	u32 entries = rddm_image->entries;
	struct mhi_buf *last_buf = &rddm_image->mhi_buf[entries - 1];
	void __iomem *base = mhi_cntrl->bhie;
	u32 sequence_id;

	mhi_dbg("BHIe programming for RDDM\n");

	mhi_write_reg(mhi_cntrl, base, BHIE_RXVECADDR_HIGH_OFFS,
		      upper_32_bits(last_buf->aligned_dma_addr));

	mhi_write_reg(mhi_cntrl, base, BHIE_RXVECADDR_LOW_OFFS,
		      lower_32_bits(last_buf->aligned_dma_addr));

	mhi_write_reg(mhi_cntrl, base, BHIE_RXVECSIZE_OFFS, (u32)last_buf->len);

	sequence_id = prandom_u32() & BHIE_RXVECSTATUS_SEQNUM_BMSK;
	if (unlikely(!sequence_id))
		sequence_id = 1;

	mhi_write_reg_field(mhi_cntrl, base, BHIE_RXVECDB_OFFS,
			    BHIE_RXVECDB_SEQNUM_BMSK, BHIE_RXVECDB_SEQNUM_SHFT,
			    sequence_id);

	mhi_dbg("Address: %p and len: 0x%lx sequence: %u\n",
		&last_buf->aligned_dma_addr, last_buf->len, sequence_id);
}

/* Collect RDDM buffer during kernel panic */
static int __mhi_download_rddm_in_panic(struct mhi_controller *mhi_cntrl)
{
	int ret;
	u32 rx_status;
	enum mhi_ee_type ee;
	const u32 delayms = 2;
	u32 retry = (mhi_cntrl->timeout_ms) / delayms;
	const u32 rddm_timeout_ms = 200;
	int rddm_retry = rddm_timeout_ms / delayms;
	void __iomem *base = mhi_cntrl->bhie;

	mhi_dbg("Entered with pm_state:%a dev_state:%a ee:%a\n",
		to_mhi_pm_state_str(mhi_cntrl->pm_state),
		TO_MHI_STATE_STR(mhi_cntrl->dev_state),
		TO_MHI_EXEC_STR(mhi_cntrl->ee));

	/*
	 * This should only be executing during a kernel panic, we expect all
	 * other cores to shutdown while we're collecting RDDM buffer. After
	 * returning from this function, we expect the device to reset.
	 *
	 * Normaly, we read/write pm_state only after grabbing the
	 * pm_lock, since we're in a panic, skipping it. Also there is no
	 * gurantee that this state change would take effect since
	 * we're setting it w/o grabbing pm_lock
	 */
	mhi_cntrl->pm_state = MHI_PM_LD_ERR_FATAL_DETECT;
	/* update should take the effect immediately */
	smp_wmb();

	/*
	 * Make sure device is not already in RDDM. In case the device asserts
	 * and a kernel panic follows, device will already be in RDDM.
	 * Do not trigger SYS ERR again and proceed with waiting for
	 * image download completion.
	 */
	ee = mhi_get_exec_env(mhi_cntrl);
	if (ee != MHI_EE_RDDM) {
		mhi_dbg("Trigger device into RDDM mode using SYS ERR\n");
		mhi_set_mhi_state(mhi_cntrl, MHI_STATE_SYS_ERR);

		mhi_dbg("Waiting for device to enter RDDM\n");
		while (rddm_retry--) {
			ee = mhi_get_exec_env(mhi_cntrl);
			if (ee == MHI_EE_RDDM)
				break;

			mdelay(delayms);
		}

		if (rddm_retry <= 0) {
			/* Hardware reset so force device to enter RDDM */
			mhi_dbg("Did not enter RDDM, do a host req reset\n");
			mhi_write_reg(mhi_cntrl, mhi_cntrl->regs,
				      MHI_SOC_RESET_REQ_OFFSET,
				      MHI_SOC_RESET_REQ);
            mdelay(delayms);
		}

		ee = mhi_get_exec_env(mhi_cntrl);
	}

	mhi_dbg("Waiting for image download completion, current EE: %a\n",
		TO_MHI_EXEC_STR(ee));

	while (retry--) {
		ret = mhi_read_reg_field(mhi_cntrl, base, BHIE_RXVECSTATUS_OFFS,
					 BHIE_RXVECSTATUS_STATUS_BMSK,
					 BHIE_RXVECSTATUS_STATUS_SHFT,
					 &rx_status);
		if (ret)
			return -EIO;

		if (rx_status == BHIE_RXVECSTATUS_STATUS_XFER_COMPL)
			return 0;

        mdelay(delayms);
	}

	ee = mhi_get_exec_env(mhi_cntrl);
	ret = mhi_read_reg(mhi_cntrl, base, BHIE_RXVECSTATUS_OFFS, &rx_status);

	mhi_err("Did not complete RDDM transfer\n");
    mhi_err("Current EE: %a\n", TO_MHI_EXEC_STR(ee));
    mhi_err("RXVEC_STATUS: 0x%x\n", rx_status);

	return -EIO;
}

/* Download RDDM image from device */
int mhi_download_rddm_img(struct mhi_controller *mhi_cntrl, bool in_panic)
{
	void __iomem *base = mhi_cntrl->bhie;
	u32 rx_status;
    int ret;
    enum mhi_ee_type ee;

	if (in_panic || ((ee = mhi_get_exec_env(mhi_cntrl)) != MHI_EE_RDDM))
		return __mhi_download_rddm_in_panic(mhi_cntrl);

	if (mhi_cntrl->ee != ee) {
		mhi_dbg("mhi_cntrl->ee = %d, ee = %d\n", mhi_cntrl->ee, ee);
		mhi_cntrl->ee = ee;
	}
	
	mhi_rddm_set_vector_table(mhi_cntrl);

	mhi_dbg("Waiting for RDDM image download via BHIe\n");

	/* Wait for the image download to complete */
    wait_event_timeout(mhi_cntrl->state_event,
	                 mhi_read_reg_field(mhi_cntrl, base,
					      BHIE_RXVECSTATUS_OFFS,
					      BHIE_RXVECSTATUS_STATUS_BMSK,
					      BHIE_RXVECSTATUS_STATUS_SHFT,
					      &rx_status) || rx_status,
					 MHI_RDDM_POLL_TIMEOUT, 
                     ret);

	DEBUG_PARAMETER(ret);

    mhi_dbg("RDDM image download complete: %d\n", rx_status);
	
	return (rx_status == BHIE_RXVECSTATUS_STATUS_XFER_COMPL) ? 0 : -EIO;
}
EXPORT_SYMBOL_GPL(mhi_download_rddm_img);

static int mhi_fw_load_amss(struct mhi_controller *mhi_cntrl,
			    const struct mhi_buf *mhi_buf)
{
	u32 val;
	void __iomem *base = mhi_cntrl->bhie;
	void __iomem *bhi_base = mhi_cntrl->bhi;
	rwlock_t *pm_lock = &mhi_cntrl->pm_lock;
	u32 tx_status = 0, sequence_id = 0;
    int ret;

	read_lock_bh(pm_lock);
	if (!MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) {
		read_unlock_bh(pm_lock);
		return -EIO;
	}

	mhi_write_reg(mhi_cntrl, base, BHIE_TXVECADDR_HIGH_OFFS,
		      upper_32_bits(mhi_buf->aligned_dma_addr));

	mhi_write_reg(mhi_cntrl, base, BHIE_TXVECADDR_LOW_OFFS,
		      lower_32_bits(mhi_buf->aligned_dma_addr));

	mhi_write_reg(mhi_cntrl, base, BHIE_TXVECSIZE_OFFS, (u32)mhi_buf->len);

	sequence_id = prandom_u32() & BHIE_TXVECSTATUS_SEQNUM_BMSK;
	mhi_write_reg_field(mhi_cntrl, base, BHIE_TXVECDB_OFFS,
			    BHIE_TXVECDB_SEQNUM_BMSK, BHIE_TXVECDB_SEQNUM_SHFT,
			    sequence_id);
	read_unlock_bh(pm_lock);

    /* Wait for the image download to complete */
    wait_event_timeout(mhi_cntrl->state_event,
	                 MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state) || 
	                 mhi_read_reg(mhi_cntrl, bhi_base, BHI_ERRCODE, 
					 	  &val) || (val == AMSS_AUTH_FAIL) ||
					 mhi_read_reg_field(mhi_cntrl, base,
					      BHIE_TXVECSTATUS_OFFS,
					      BHIE_TXVECSTATUS_STATUS_BMSK,
					      BHIE_TXVECSTATUS_STATUS_SHFT,
					      &tx_status) || tx_status,
					 mhi_cntrl->timeout_ms,
                     ret);

	DEBUG_PARAMETER(ret);

  	mhi_dbg("pm_state = %d reg = 0x%x\n", mhi_cntrl->pm_state, val);
	
	if (MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state))
		return -EIO;

	/* If auth fail, SBL will set Hash segment failure in BHI_ERRCODE with Value of 0x302E */
	if (val == AMSS_AUTH_FAIL) {
		mhi_err("AMSS auth fail!!!\n");
		return -EAUTH;
	}
	return (tx_status == BHIE_TXVECSTATUS_STATUS_XFER_COMPL) ? 0 : -EIO;
}
EXPORT_SYMBOL_GPL(mhi_download_amss_image);

static int mhi_fw_load_sbl(struct mhi_controller *mhi_cntrl,
			   dma_addr_t dma_addr,
			   size_t size)
{
	u32 tx_status = 0, val, session_id = 0;
	int i, ret = 0;;
	void __iomem *base = mhi_cntrl->bhi;
	rwlock_t *pm_lock = &mhi_cntrl->pm_lock;
	struct {
		char *name;
		u32 offset;
	} error_reg[] = {
		{ "ERROR_CODE", BHI_ERRCODE },
		{ "ERROR_DBG1", BHI_ERRDBG1 },
		{ "ERROR_DBG2", BHI_ERRDBG2 },
		{ "ERROR_DBG3", BHI_ERRDBG3 },
		{ NULL },
	};

	read_lock_bh(pm_lock);
	if (!MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) {
		read_unlock_bh(pm_lock);
		goto invalid_pm_state;
	}

    mhi_dbg("Starting SBL download via BHI, dma_addr=0x%x, size=%X\n", dma_addr, size);
	mhi_write_reg(mhi_cntrl, base, BHI_STATUS, 0);
	mhi_write_reg(mhi_cntrl, base, BHI_IMGADDR_HIGH,
		      upper_32_bits(dma_addr));
	mhi_write_reg(mhi_cntrl, base, BHI_IMGADDR_LOW,
		      lower_32_bits(dma_addr));
	mhi_write_reg(mhi_cntrl, base, BHI_IMGSIZE, (u32)size);
	session_id = prandom_u32() & BHI_TXDB_SEQNUM_BMSK;
	if (unlikely(!session_id))
		session_id = 1;

	mhi_write_reg(mhi_cntrl, base, BHI_IMGTXDB, session_id);
	read_unlock_bh(pm_lock);

	/* Wait for the image download to complete */
    wait_event_timeout(mhi_cntrl->state_event,
	                 MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state) ||
	                 mhi_read_reg(mhi_cntrl, base, BHI_ERRCODE, 
					 	  &val) || ((val & 0xFF0000) >> 16 == SBL_AUTH_FAIL) ||
					 mhi_read_reg_field(mhi_cntrl, base, BHI_STATUS,
					      BHI_STATUS_MASK, BHI_STATUS_SHIFT,
					      &tx_status) || tx_status,
					 msecs_to_jiffies(mhi_cntrl->timeout_ms),
                     ret);
    mhi_dbg("pm_state = %d reg = 0x%x tx_status = 0x%x\n", mhi_cntrl->pm_state, val, tx_status);
	if (MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state))
		goto invalid_pm_state;

	/* If auth fail, PBL will set BHI_ERRCODE with bit[23:16] as 0x0A.*/
	if ((val & 0xFF0000) >> 16 == SBL_AUTH_FAIL) {
		mhi_err("SBL auth fail!!!\n");
		return -EAUTH;
	}
	
	if (tx_status == BHI_STATUS_ERROR) {
        mhi_dbg("Image transfer failed\n");
		read_lock_bh(pm_lock);
		if (MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) {
			for (i = 0; error_reg[i].name; i++) {
				ret = mhi_read_reg(mhi_cntrl, base,
						   error_reg[i].offset, &val);
				if (ret)
					break;
				mhi_dbg("Reg: %a value: 0x%x\n", error_reg[i].name, val);
			}
		}
		read_unlock_bh(pm_lock);
		goto invalid_pm_state;
	}

	return (!ret) ? -ETIMEDOUT : 0;

invalid_pm_state:

	return -EIO;
}

void mhi_free_bhie_table(struct mhi_controller *mhi_cntrl,
			 struct image_info *image_info)
{
	int i;
	struct mhi_buf *mhi_buf = image_info->mhi_buf;

	for (i = 0; (u32)i < image_info->entries; i++, mhi_buf++)
		mhi_free_coherent(mhi_cntrl, mhi_buf->alloc_size, mhi_buf->buf,
				  mhi_buf->dma_addr, mhi_buf->dma_mapping_addr);

	kfree(image_info->mhi_buf);
	kfree(image_info);
}

int mhi_alloc_bhie_table(struct mhi_controller *mhi_cntrl,
			 struct image_info **image_info,
			 size_t alloc_size)
{
	u32 seg_size = mhi_cntrl->seg_len;
	int segments = (int)DIV_ROUND_UP(alloc_size, seg_size) + 1;
	int i;
	struct image_info *img_info;
	struct mhi_buf *mhi_buf;

	img_info = kzalloc(sizeof(*img_info), GFP_KERNEL);
	if (!img_info)
		return -ENOMEM;

	/* Allocate memory for entries */
	img_info->mhi_buf = kcalloc(segments, sizeof(*img_info->mhi_buf),
				    GFP_KERNEL);
	if (!img_info->mhi_buf)
		goto error_alloc_mhi_buf;

	/* Allocate and populate vector table */
	mhi_buf = img_info->mhi_buf;
	for (i = 0; i < segments; i++, mhi_buf++) {
		u32 vec_size = seg_size;

		/* Vector table is the last entry */
		if (i == segments - 1)
			vec_size = sizeof(struct bhi_vec_entry) * i;

		mhi_buf->len = vec_size;
        mhi_buf->alloc_size = vec_size + BHI_DEFAULT_ALIGNMENT - 1;
		mhi_buf->buf = mhi_alloc_coherent(mhi_cntrl, mhi_buf->alloc_size,
						  &mhi_buf->dma_addr,
						  &mhi_buf->dma_mapping_addr);
        mhi_buf->aligned_dma_addr = ALIGN(mhi_buf->dma_addr, BHI_DEFAULT_ALIGNMENT);
        mhi_buf->aligned_buf = (u8 *)mhi_buf->buf + (mhi_buf->aligned_dma_addr - mhi_buf->dma_addr);

        mhi_dbg("mhi_buf->aligned_dma_addr=0x%x\n", mhi_buf->aligned_dma_addr);
		if (!mhi_buf->buf)
			goto error_alloc_segment;
	}

	img_info->bhi_vec = img_info->mhi_buf[segments - 1].aligned_buf;
	img_info->entries = segments;
	*image_info = img_info;

	return 0;

error_alloc_segment:
	for (--i, --mhi_buf; i >= 0; i--, mhi_buf--)
		mhi_free_coherent(mhi_cntrl, mhi_buf->alloc_size, mhi_buf->buf,
				  mhi_buf->dma_addr, mhi_buf->dma_mapping_addr);

error_alloc_mhi_buf:
	kfree(img_info);

	return -ENOMEM;
}

static void mhi_firmware_copy(struct mhi_controller *mhi_cntrl,
			      struct image_info *img_info,
			      u8* fw_data, u32 fw_size)
{
	size_t remainder = fw_size;
	size_t to_cpy;
	const u8 *buf = fw_data;
	struct mhi_buf *mhi_buf = img_info->mhi_buf;
	struct bhi_vec_entry *bhi_vec = img_info->bhi_vec;

	while (remainder) {
		to_cpy = min(remainder, mhi_buf->len);
		memcpy(mhi_buf->aligned_buf, buf, to_cpy);
		bhi_vec->dma_addr = mhi_buf->aligned_dma_addr;
		bhi_vec->size = to_cpy;

		buf += to_cpy;
		remainder -= to_cpy;
		bhi_vec++;
		mhi_buf++;
	}
}

static int mhi_target_match_expression(struct mhi_controller *mhi_cntrl, struct expression_iterator *it)
{
    const struct pci_device_id *device_id;
    u32 count;
    int ret;

    device_id = pci_get_hardware_id(mhi_cntrl->cntrl_dev);
    if (!device_id) {
        mhi_err("failed to get hardware id\n");
        return -ENODEV;
    }

    count = 0;
    ret = 0;

    while (expression_iterator_next(it) == 0) {
        count++;
        if (strcmp("bus", it->key) == 0) {
            if (strcmp(it->value, "pci") != 0) {
                ret = -EBADF;
                break;
            }
        }
        else if (strcmp("vendor", it->key) == 0) {
            if (strhextou64(it->value) != device_id->vendor) {
                ret = -EBADF;
                break;
            }
        }
        else if (strcmp("device", it->key) == 0) {
            if (strhextou64(it->value) != device_id->device) {
                ret = -EBADF;
                break;
            }
        }
        else if (strcmp("subsystem-vendor", it->key) == 0) {
            if (strhextou64(it->value) != device_id->subsystem_vendor) {
                ret = -EBADF;
                break;
            }
        }
        else if (strcmp("subsystem-device", it->key) == 0) {
            if (strhextou64(it->value) != device_id->subsystem_device) {
                ret = -EBADF;
                break;
            }
        }
        else {
            mhi_warn("unsupported expression: %a=%a\n", it->key, it->value);
            ret = -EBADF;
        }
    }

    if (!count) /* expression is invalid */
        ret = -EBADF;

    return ret;
}

static int mhi_firmware_metadata_match_target(const u8 *name, struct firmware_metadata *metadata, void *ctx)
{
	struct mhi_controller *mhi_cntrl = ctx;
    struct description_iterator it;
    int ret;

    if (!name || !metadata || !mhi_cntrl)
        return -EINVAL;

    /* match target if no description is specified */
    if (!metadata->description) {
        mhi_dbg("match firmware %a(no description): 0\n", name);
        return 0;
    }

    ret = 0;
    description_iterator_init(&it, metadata->description, metadata->description_len);
    
    while (description_iterator_next(&it) == 0) {
        ret = mhi_target_match_expression(mhi_cntrl, &it.expression_it);
        if (!ret)
            break;
    }

    if (SUPPORT_DEBUG_PRINT) {
        u8 description[384] = { 0 };
        memcpy(description, metadata->description, MIN(metadata->description_len, sizeof(description) - 1));
        mhi_dbg("match firmware %a(description: %a): %d\n", name, description, ret);
    }

    return ret;
}

int mhi_request_firmware(struct mhi_controller *mhi_cntrl, struct firmware *fw, const u16 *name)
{
	int ret;
	
	mhi_dbg("try to get matched amss.bin from firmware\n");
	ret = request_firmware_fancily(fw, name, mhi_firmware_metadata_match_target, mhi_cntrl);
	if (ret) {
		mhi_err("failed to load a matched bdf: %d\n", ret);
	}

	return ret;
}

void mhi_fw_load_worker(void *context)
{
	struct mhi_controller *mhi_cntrl = context;
	struct image_info *image_info;
	const u16 *fw_name;
    struct firmware firmware = { 0 };
	size_t size_sbl = 0;
    size_t size_alloc = 0;
    u8 *pre_aligned, *aligned;
    dma_addr_t dma_handle, aligned_dma_addr;
    void *dma_mapping_handle;
	int ret;

	mhi_dbg("Waiting for device to enter PBL from: %a\n", TO_MHI_EXEC_STR(mhi_cntrl->ee));
	
    wait_event_timeout(mhi_cntrl->state_event,
		             MHI_IN_PBL(mhi_cntrl->ee) ||
		             MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state),
		             msecs_to_jiffies(mhi_cntrl->timeout_ms), 
                     ret);

    mhi_dbg("Current EE: %a\n", TO_MHI_EXEC_STR(mhi_cntrl->ee));
	
    if (!ret || MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) {
        mhi_err("Device MHI is not in valid state, ret=%d, pm_state=%u\n", 
            ret, mhi_cntrl->pm_state);
		return;
	}

	/* If device is in pass through, do reset to ready state transition */
	if (mhi_cntrl->ee == MHI_EE_PTHRU)
		goto fw_load_ee_pthru;

	fw_name = (mhi_cntrl->ee == MHI_EE_EDL) ?
		mhi_cntrl->edl_image : mhi_cntrl->fw_image;

	if (!fw_name || (mhi_cntrl->fbc_download && (!mhi_cntrl->sbl_size ||
						     !mhi_cntrl->seg_len))) {
        mhi_err("No firmware image defined or !sbl_size || !seg_len\n");
		return;
	}

    ret = mhi_request_firmware(mhi_cntrl, &firmware, fw_name);
	if (ret) {
        mhi_err("Error loading firmware: 0x%x!!!\n", ret);
		mhi_cntrl->fw_load_fail = ret;
		return;
	}

	size_sbl = (mhi_cntrl->fbc_download) ? mhi_cntrl->sbl_size : firmware.size;

	/* SBL size provided is maximum size, not necessarily the image size */
	if (size_sbl > firmware.size)
		size_sbl = firmware.size;

    size_alloc = size_sbl + BHI_DEFAULT_ALIGNMENT - 1;

    pre_aligned = mhi_alloc_coherent(mhi_cntrl, size_alloc, &dma_handle, &dma_mapping_handle);
	if (!pre_aligned) {
        mhi_err("Error alloc mhi_alloc_coherent!\n");
        release_firmware(&firmware);
		return;
	}

    aligned_dma_addr = ALIGN(dma_handle, BHI_DEFAULT_ALIGNMENT);
    aligned = pre_aligned + (aligned_dma_addr - dma_handle);

	/* Download SBL image */
	memcpy(aligned, firmware.data, size_sbl);
    smp_wmb();

	ret = mhi_fw_load_sbl(mhi_cntrl, aligned_dma_addr, size_sbl);
	mhi_free_coherent(mhi_cntrl, size_alloc, pre_aligned, dma_handle, dma_mapping_handle);

	if (!mhi_cntrl->fbc_download || ret || mhi_cntrl->ee == MHI_EE_EDL) {
        mhi_err("mhi_cntrl->fbc_download = %d ret = %d mhi_cntrl->ee = %d\n", 
            mhi_cntrl->fbc_download, ret, mhi_cntrl->ee);
	}

	/* Error or in EDL mode, we're done */
	if (ret || mhi_cntrl->ee == MHI_EE_EDL)
		goto error_download_fw;

	write_lock_irq(&mhi_cntrl->pm_lock);
	mhi_cntrl->dev_state = MHI_STATE_RESET;
	write_unlock_irq(&mhi_cntrl->pm_lock);

	/*
	 * If we're doing fbc, populate vector tables while
	 * device transitioning into MHI READY state
	 */
	if (mhi_cntrl->fbc_download) {
        WARN_ON(mhi_cntrl->fbc_image);
		ret = mhi_alloc_bhie_table(mhi_cntrl, &mhi_cntrl->fbc_image,
					   firmware.size);
		if (ret) {
			goto error_alloc_fw_table;
		}

		/* Load the firmware into BHIE vec table */
		mhi_firmware_copy(mhi_cntrl, mhi_cntrl->fbc_image, firmware.data, firmware.size);
	}

fw_load_ee_pthru:
	/* Transitioning into MHI RESET->READY state */
	ret = mhi_ready_state_transition(mhi_cntrl);
    mhi_dbg("mhi_ready_state_transition ret = %X\n", ret);
	if (!mhi_cntrl->fbc_download)
		goto error_download_fw;

	if (ret)
		goto error_read;
    /* Wait for the SBL event */
    wait_event_timeout(mhi_cntrl->state_event,
		             mhi_cntrl->ee == MHI_EE_SBL ||
		             MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state),
		             msecs_to_jiffies(mhi_cntrl->timeout_ms),
		             ret);
	
    if (!ret || MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) {
		mhi_err("MHI did not enter SBL\n");
		goto error_read;
	}
	
	/* Start full firmware image download */
	image_info = mhi_cntrl->fbc_image;
	ret = mhi_fw_load_amss(mhi_cntrl,
			       /* Vector table is the last entry */
			       &image_info->mhi_buf[image_info->entries - 1]);
	if (ret) {
		mhi_err("Load amss fail ret = 0x%x\n", ret);
		goto error_read;
	}

    release_firmware(&firmware);
	return;

error_read:
	mhi_free_bhie_table(mhi_cntrl, mhi_cntrl->fbc_image);
	mhi_cntrl->fbc_image = NULL;

error_alloc_fw_table:
	mhi_err("Release fw\n");
error_download_fw:
    release_firmware(&firmware);
	mhi_cntrl->fw_load_fail = ret;
}
