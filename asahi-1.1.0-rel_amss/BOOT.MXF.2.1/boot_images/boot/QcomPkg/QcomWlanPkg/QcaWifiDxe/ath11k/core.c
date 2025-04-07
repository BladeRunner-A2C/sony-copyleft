/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

// SPDX-License-Identifier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#include <qdf/firmware.h>
#include "core.h"
#include "dp_tx.h"
#include "dp_rx.h"
#include "debug.h"
#include "hif.h"
#include "mac.h"
#include "reg.h"

unsigned int ath11k_debug_mask = (unsigned int)ATH11K_DBG_ANY & ~(ATH11K_DBG_DATA | ATH11K_DBG_PKT);

static const struct ath11k_hw_params ath11k_hw_params_list[] = {
#if SUPPORT_HARDWARE_HST6390
	{
		.name = "hst6390",
		.dev_id = ATH11K_HW_QCA6390,
		.single_pdev_only = true,
		.hw_ops = &qca6390_ops,
		.regs = &qca6390_regs,
		.host_ce_config = ath11k_host_ce_config_qca6x90,
		.ce_count = 9,
		.target_ce_config = ath11k_target_ce_config_wlan_qca6x90,
		.target_ce_count = 9,
		.svc_to_ce_map = ath11k_target_service_to_ce_map_wlan_qca6x90,
		.svc_to_ce_map_len = 14,
		.hw_values = &qca6x90_values,
		.srng_params = &ath11k_hw_srng_qca6x90,
		.misc_caps = MISC_CAPS_HOST2FW_RXBUF_RING |
			     MISC_CAPS_TCL_0_ONLY |
			     MISC_CAPS_IDLE_PS_SUPP,
		.misc_regs = &qca6390_misc_regs,
		.vdev_start_delay = true,
		.disable_pktlog = false,
		.channel_num_war = true,
		.band_2g_fake = true,
		.v2_map_support = false,
		.host2fw_rxbuf_ring = true,
		.rxdma1_enable = false,
		.cut_off_power = true,
		.hal_desc_sz = sizeof(struct hal_rx_desc_qca6390),
		.ring_hmap = HAL_HASH_ROUTING_RING_SW1 << 0 |\
			     HAL_HASH_ROUTING_RING_SW2 << 3 |\
			     HAL_HASH_ROUTING_RING_SW3 << 6 |\
			     HAL_HASH_ROUTING_RING_SW4 << 9 |\
			     HAL_HASH_ROUTING_RING_SW1 << 12 |\
			     HAL_HASH_ROUTING_RING_SW2 << 15 |\
			     HAL_HASH_ROUTING_RING_SW3 << 18 |\
			     HAL_HASH_ROUTING_RING_SW4 << 21,
		.fw_wmi_diag_event = false,
		.fw_sram_start = FW_SRAM_START_QCA6390,
		.fw_sram_end = FW_SRAM_END_QCA6390,
		.rddm_size = 0x400000,
	},
#endif
	{
		.name = "qca6490/hw1.1",
		.dev_id = ATH11K_HW_QCA6490_HW11,
		//.internal_sleep_clock = true,
		.single_pdev_only = true,
		.hw_ops = &qca6490_ops,
		.regs = &qca6490_regs,
		.host_ce_config = ath11k_host_ce_config_qca6x90,
		.ce_count = 9,
		.target_ce_config = ath11k_target_ce_config_wlan_qca6x90,
		.target_ce_count = 9,
		.svc_to_ce_map = ath11k_target_service_to_ce_map_wlan_qca6x90,
		.svc_to_ce_map_len = 14,
		.hw_values = &qca6x90_values,
		.srng_params = &ath11k_hw_srng_qca6x90,
		.misc_caps = MISC_CAPS_HOST2FW_RXBUF_RING |
					 MISC_CAPS_TCL_0_ONLY,
		.misc_regs = &qca6490_misc_regs,
		.rxdma1_enable = false,
		//.num_rxmda_per_pdev = 2,
		.vdev_start_delay = true,
		.disable_pktlog = false,
		.channel_num_war = true,
		.band_2g_fake = true,
		.host2fw_rxbuf_ring = true,
		.cut_off_power = true,
		//.v2_map_support = false,
		//.shadow_support = true,
		//.shadow_support_fix = false,
		.hal_desc_sz = sizeof(struct hal_rx_desc_qca6490),
		.ring_hmap = HAL_HASH_ROUTING_RING_SW1 << 0 |\
			     HAL_HASH_ROUTING_RING_SW2 << 4 |\
			     HAL_HASH_ROUTING_RING_SW3 << 8 |\
			     HAL_HASH_ROUTING_RING_SW4 << 12 |\
			     HAL_HASH_ROUTING_RING_SW1 << 16 |\
			     HAL_HASH_ROUTING_RING_SW2 << 20 |\
			     HAL_HASH_ROUTING_RING_SW3 << 24 |\
			     HAL_HASH_ROUTING_RING_SW4 << 28,
		.fw_wmi_diag_event = true,
		.fw_sram_start = FW_SRAM_START_QCA6490,
		.fw_sram_end = FW_SRAM_END_QCA6490,
		.rddm_size = 0x400000,
 	},
 	{
		.name = "qca6490/hw2.0",
		.dev_id = ATH11K_HW_QCA6490_HW20,
		//.internal_sleep_clock = true,
		.single_pdev_only = true,
		.hw_ops = &qca6490_ops,
		.regs = &qca6490_regs,
		.host_ce_config = ath11k_host_ce_config_qca6x90,
		.ce_count = 9,
		.target_ce_config = ath11k_target_ce_config_wlan_qca6x90,
		.target_ce_count = 9,
		.svc_to_ce_map = ath11k_target_service_to_ce_map_wlan_qca6x90,
		.svc_to_ce_map_len = 14,
		.hw_values = &qca6x90_values,
		.srng_params = &ath11k_hw_srng_qca6x90,
		.misc_caps = MISC_CAPS_HOST2FW_RXBUF_RING |
					 MISC_CAPS_TCL_0_ONLY,
		.misc_regs = &qca6490_misc_regs,
		.rxdma1_enable = false,
		//.num_rxmda_per_pdev = 2,
		.vdev_start_delay = true,
		.disable_pktlog = false,
		.channel_num_war = true,
		.band_2g_fake = true,
		.host2fw_rxbuf_ring = true,
		.cut_off_power = true,
		//.v2_map_support = false,
		//.shadow_support = true,
		//.shadow_support_fix = false,
		.hal_desc_sz = sizeof(struct hal_rx_desc_qca6490),
		.ring_hmap = HAL_HASH_ROUTING_RING_SW1 << 0 |\
			     HAL_HASH_ROUTING_RING_SW2 << 4 |\
			     HAL_HASH_ROUTING_RING_SW3 << 8 |\
			     HAL_HASH_ROUTING_RING_SW4 << 12 |\
			     HAL_HASH_ROUTING_RING_SW1 << 16 |\
			     HAL_HASH_ROUTING_RING_SW2 << 20 |\
			     HAL_HASH_ROUTING_RING_SW3 << 24 |\
			     HAL_HASH_ROUTING_RING_SW4 << 28,
		.fw_wmi_diag_event = true,
		.fw_sram_start = FW_SRAM_START_QCA6490,
		.fw_sram_end = FW_SRAM_END_QCA6490,
		.rddm_size = 0x400000,
 	},
};

/* Map from pdev index to hw mac index */
u8 ath11k_core_get_hw_mac_id(struct ath11k_base *ab, int pdev_idx)
{
	switch (pdev_idx) {
	case 0:
		return 0;
	case 1:
		return 2;
	case 2:
		return 1;
	default:
		ath11k_warn(ab, "Invalid pdev idx %d\n", pdev_idx);
		return ATH11K_INVALID_HW_MAC_ID;
	}
}

static int ath11k_core_create_board_name(struct ath11k_base *ab, char *name,
					 size_t name_len)
{
	/* Note: bus is fixed to ahb. When other bus type supported,
	 * make it to dynamic.
	 */
	(void)scnprintf(name, name_len,
        "bus=ahb,qmi-chip-id=%d,qmi-board-id=%d",
        ab->qmi.target.chip_id,
        ab->qmi.target.board_id);

	ath11k_dbg(ab, ATH11K_DBG_BOOT, "boot using board name '%a'\n", name);

	return 0;
}

void ath11k_core_stop(struct ath11k_base *ab)
{
    ath11k_info(ab, "dev_flags=0x%x\n", ab->dev_flags);

    poll_irqs(16);

	if (!test_bit(ATH11K_FLAG_CRASH_FLUSH, &ab->dev_flags))
		ath11k_qmi_firmware_stop(ab);

	ath11k_hif_stop(ab);
	ath11k_wmi_detach(ab);
	ath11k_dp_pdev_reo_cleanup(ab);

	/* De-Init of components as needed */
}

static int ath11k_core_soc_create(struct ath11k_base *ab)
{
	int ret;
	unsigned long time_left;

	ret = ath11k_qmi_init_service(ab);
	if (ret) {
		ath11k_err(ab, "failed to initialize qmi :%d\n", ret);
		return ret;
	}

	ret = ath11k_debug_soc_create(ab);
	if (ret) {
		ath11k_err(ab, "failed to create ath11k debugfs\n");
		goto err_qmi_deinit;
	}

	ret = ath11k_hif_power_up(ab);
	if (ret) {
		ath11k_err(ab, "failed to power up :%d\n", ret);
		goto err_debugfs_reg;
	}

    time_left = wait_for_completion_timeout(&ab->hw_mode_ready, 30000);
	if (!time_left) {
        ath11k_err(ab, "wait HW mode ready timeout\n");
		ret = -ETIMEDOUT;
		goto err_debugfs_reg;
	}

	return 0;

err_debugfs_reg:
	ath11k_debug_soc_destroy(ab);
err_qmi_deinit:
	ath11k_qmi_deinit_service(ab);
	return ret;
}

static void ath11k_core_soc_destroy(struct ath11k_base *ab)
{
	ath11k_debug_soc_destroy(ab);
	ath11k_dp_free(ab);
	ath11k_reg_free(ab);
	ath11k_qmi_deinit_service(ab);
}

static int ath11k_core_pdev_create(struct ath11k_base *ab)
{
	int ret;
	bool normal_mode = ab->fw_mode == ATH11K_FIRMWARE_MODE_NORMAL;

	if (normal_mode &&
	    !test_bit(ATH11K_FLAG_MAC_STARTING, &ab->dev_flags)) {
		ret = ath11k_debug_pdev_create(ab);
		if (ret) {
			ath11k_err(ab, "failed to create core pdev debugfs: %d\n", ret);
			return ret;
		}

		ret = ath11k_mac_register(ab);
		if (ret) {
			ath11k_err(ab, "failed register the radio with mac80211: %d\n",
				   ret);
			goto err_pdev_debug;
		}
	}

	ret = ath11k_dp_pdev_alloc(ab);
	if (ret) {
		ath11k_err(ab, "failed to attach DP pdev: %d\n", ret);
		goto err_mac_unregister;
	}

	return 0;

err_mac_unregister:
	if (normal_mode)
		ath11k_mac_unregister(ab);

err_pdev_debug:
	if (normal_mode)
		ath11k_debug_pdev_destroy(ab);

	return ret;
}

static int ath11k_core_pdev_suspend(struct ath11k_base *ab)
{
	struct ath11k *ar;
	int i, ret = 0;

	for (i = 0; i < (int)ab->num_radios; i++) {
		ar = ab->pdevs[i].ar;
		ret = ath11k_wmi_pdev_suspend(ar, WMI_PDEV_SUSPEND_AND_DISABLE_INTR, i);
		if (ret) {
			ath11k_err(ab, "failed to suspend pdev: %d\n", ret);
			return ret;
		}
	}
	return ret;
}

static void ath11k_core_pdev_destroy(struct ath11k_base *ab)
{
	ath11k_mac_unregister(ab);
	if (test_bit(ATH11K_FLAG_MAC_STOPPED, &ab->dev_flags))
		return;
	ath11k_core_pdev_suspend(ab);
	ath11k_hif_irq_disable(ab);
	ath11k_dp_pdev_free(ab);
	ath11k_debug_pdev_destroy(ab);
}

static int ath11k_core_start(struct ath11k_base *ab,
			     enum ath11k_firmware_mode mode)
{
	int ret;

	ret = ath11k_qmi_firmware_start(ab, mode);
	if (ret) {
		ath11k_err(ab, "failed to attach wmi: %d\n", ret);
		return ret;
	}
    else {
        ath11k_info(ab, "ath11k_qmi_firmware_start: %d\n", ret);
    }

	ret = ath11k_wmi_attach(ab);
	if (ret) {
		ath11k_err(ab, "failed to attach wmi: %d\n", ret);
		goto err_firmware_stop;
    }
    else {
        ath11k_info(ab, "ath11k_wmi_attach: %d\n", ret);
    }

	ret = ath11k_htc_init(ab);
	if (ret) {
		ath11k_err(ab, "failed to init htc: %d\n", ret);
		goto err_wmi_detach;
	}
    else {
        ath11k_info(ab, "ath11k_htc_init: %d\n", ret);
    }

	ret = ath11k_hif_start(ab);
	if (ret) {
		ath11k_err(ab, "failed to start HIF: %d\n", ret);
		goto err_wmi_detach;
	}
    else {
        ath11k_info(ab, "ath11k_hif_start: %d\n", ret);
    }

	ret = ath11k_htc_wait_target(&ab->htc);
	if (ret) {
		ath11k_err(ab, "failed to connect to HTC: %d\n", ret);
		goto err_hif_stop;
	}
    else {
        ath11k_info(ab, "ath11k_htc_wait_target: %d\n", ret);
    }

	ret = ath11k_dp_htt_connect(&ab->dp);
	if (ret) {
		ath11k_err(ab, "failed to connect to HTT: %d\n", ret);
		goto err_hif_stop;
	}
    else {
        ath11k_info(ab, "ath11k_dp_htt_connect: %d\n", ret);
    }

	ret = ath11k_wmi_connect(ab);
	if (ret) {
		ath11k_err(ab, "failed to connect wmi: %d\n", ret);
		goto err_hif_stop;
	}
    else {
        ath11k_info(ab, "ath11k_wmi_connect: %d\n", ret);
    }
    
	ret = ath11k_htc_start(&ab->htc);
	if (ret) {
		ath11k_err(ab, "failed to start HTC: %d\n", ret);
		goto err_hif_stop;
	}
    else {
        ath11k_info(ab, "ath11k_htc_start: %d\n", ret);
    }

	ret = ath11k_wmi_wait_for_service_ready(ab);
	if (ret) {
		ath11k_err(ab, "failed to receive wmi service ready event: %d\n",
			   ret);
		goto err_hif_stop;
	}
    else {
        ath11k_info(ab, "ath11k_wmi_wait_for_service_ready: %d\n", ret);
    }

	ret = ath11k_mac_allocate(ab);
	if (ret) {
		ath11k_err(ab, "failed to create new hw device with mac80211 :%d\n",
			   ret);
		goto err_hif_stop;
	}
    else {
        ath11k_info(ab, "ath11k_mac_allocate: %d\n", ret);
    }

	ath11k_dp_pdev_pre_alloc(ab);

    ret = ath11k_dp_pdev_reo_setup(ab);
	if (ret) {
		ath11k_err(ab, "failed to initialize reo destination rings: %d\n", ret);
		goto err_mac_destroy;
	}
    else {
        ath11k_info(ab, "ath11k_dp_pdev_reo_setup: %d\n", ret);
    }

	ret = ath11k_wmi_cmd_init(ab);
	if (ret) {
		ath11k_err(ab, "failed to send wmi init cmd: %d\n", ret);
		goto err_reo_cleanup;
	}
    else {
        ath11k_info(ab, "ath11k_wmi_cmd_init: %d\n", ret);
    }

	ret = ath11k_wmi_wait_for_unified_ready(ab);
	if (ret) {
		ath11k_err(ab, "failed to receive wmi unified ready event: %d\n",
			   ret);
		goto err_reo_cleanup;
	}
    else {
        ath11k_info(ab, "ath11k_wmi_wait_for_unified_ready: %d\n", ret);
    }

	// put hardware to DBS mode
	if (ab->hw_params.single_pdev_only) {
        reinit_completion(&ab->hw_mode_ready);
		ret = ath11k_wmi_set_hw_mode(ab, ab->wmi_ab.preferred_hw_mode);
		if (ret) {
			ath11k_err(ab, "failed to send dbs mode: %d\n", ret);
			goto err_hif_stop;
		}
        else {
            ath11k_info(ab, "ath11k_wmi_set_hw_mode: %d\n", ret);
        }
	}

	ret = ath11k_dp_tx_htt_h2t_ver_req_msg(ab);
	if (ret) {
		ath11k_err(ab, "failed to send htt version request message: %d\n",
			   ret);
		goto err_reo_cleanup;
	}
    else {
        ath11k_info(ab, "ath11k_dp_tx_htt_h2t_ver_req_msg: %d\n", ret);
    }

	return 0;

err_reo_cleanup:
	ath11k_dp_pdev_reo_cleanup(ab);
err_mac_destroy:
	ath11k_mac_destroy(ab);
err_hif_stop:
	ath11k_hif_stop(ab);
err_wmi_detach:
	ath11k_wmi_detach(ab);
err_firmware_stop:
	ath11k_qmi_firmware_stop(ab);

	return ret;
}

static int ath11k_core_send_default_sar_limit(struct ath11k_base *ab)
{
#define DEFAULT_SAR_LIMIT_NUM_ROWS	2

	int i, ret = 0;
	struct ath11k *ar;
	struct wmi_sar_limit_cmd_params sar_limit;
	struct sar_limit_cmd_row sar_limit_row_list[DEFAULT_SAR_LIMIT_NUM_ROWS];

	memset(&sar_limit, 0, sizeof(struct wmi_sar_limit_cmd_params));
	memset(sar_limit_row_list, 0, sizeof(struct sar_limit_cmd_row) * DEFAULT_SAR_LIMIT_NUM_ROWS);

	sar_limit_row_list[0].chain_id = 0;
	sar_limit_row_list[0].limit_value = 0;
	sar_limit_row_list[0].validity_bitmap = WMI_SAR_CHAIN_ID_VALID_MASK;

	sar_limit_row_list[1].chain_id = 1;
	sar_limit_row_list[1].limit_value = 0;
	sar_limit_row_list[1].validity_bitmap = WMI_SAR_CHAIN_ID_VALID_MASK;

	sar_limit.sar_enable = WMI_SAR_FEATURE_ON_SAR_V2_0;
	sar_limit.num_limit_rows = DEFAULT_SAR_LIMIT_NUM_ROWS;
	sar_limit.commit_limits = 1;
	sar_limit.sar_limit_row_list = sar_limit_row_list;

	for (i = 0; i < (int)ab->num_radios; i++) {
		ar = ab->pdevs[i].ar;
		ret = ath11k_wmi_send_sar_limit(ar, &sar_limit);
	}

	return ret;
}

int ath11k_core_qmi_firmware_ready(struct ath11k_base *ab)
{
	int ret;

    /* clean up the cache */
    flush_firmware_cache();

    ath11k_info(ab, "ath11k_core_qmi_firmware_ready !!!\n");
	ret = ath11k_ce_init_pipes(ab);
	if (ret) {
		ath11k_err(ab, "failed to initialize CE: %d\n", ret);
		return ret;
	}
    else {
        ath11k_info(ab, "ath11k_ce_init_pipes ret = %d\n", ret);
    }

	ret = ath11k_dp_alloc(ab);
	if (ret) {
		ath11k_err(ab, "failed to init DP: %d\n", ret);
		return ret;
	}
    else {
        ath11k_info(ab, "ath11k_dp_alloc ret = %d\n", ret);
    }

	mutex_lock(&ab->core_lock);
	ret = ath11k_core_start(ab, ab->fw_mode);
	if (ret) {
		ath11k_err(ab, "failed to start core: %d\n", ret);
		goto err_dp_free;
	}
    else {
        ath11k_info(ab, "ath11k_core_start ret = %d\n", ret);
    }

	ret = ath11k_core_pdev_create(ab);
	if (ret) {
		ath11k_err(ab, "failed to create pdev core: %d\n", ret);
		goto err_core_stop;
	}
    else {
        ath11k_info(ab, "ath11k_core_pdev_create ret = %d\n", ret);
    }

	ath11k_hif_irq_enable(ab);

	ret = ath11k_core_send_default_sar_limit(ab);
	if (ret) {
		ath11k_err(ab, "failed to send default sar limit: %d\n", ret);
		goto err_core_stop;
	}
	
	mutex_unlock(&ab->core_lock);

	if (test_bit(ATH11K_FLAG_MAC_STARTING, &ab->dev_flags)) {
        ath11k_info(ab, "ab->dev_flags = 0x%x\n", ab->dev_flags);
		complete(&ab->fw_mac_restart);
	}

	return 0;

err_core_stop:
	ath11k_core_stop(ab);
	ath11k_mac_destroy(ab);
err_dp_free:
	ath11k_dp_free(ab);
	mutex_unlock(&ab->core_lock);
	return ret;
}

static void ath11k_update_11d(void *context)
{
	struct ath11k_base *ab = context;
	struct ath11k *ar;
	struct ath11k_pdev *pdev;
	struct wmi_set_current_country_params set_current_param;
	int ret, i;

	memcpy(&set_current_param.alpha2, &ab->new_alpha2, 2);

	ath11k_dbg(ab, ATH11K_DBG_WMI, "update 11d new cc %c%c\n",
		   set_current_param.alpha2[0],
		   set_current_param.alpha2[1]);

	for (i = 0; i < (int)ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;

		ret = ath11k_wmi_send_set_current_country_cmd(ar, &set_current_param);
		if (ret)
			ath11k_warn(ar->ab,
				    "pdev id %d failed set current country code: %d\n",
				    i, ret);
	}
}

#if 0
static int ath11k_core_reconfigure_on_crash(struct ath11k_base *ab)
{
	int ret;

	mutex_lock(&ab->core_lock);
	ath11k_hif_irq_disable(ab);
	ath11k_dp_pdev_free(ab);
	ath11k_hif_stop(ab);
	ath11k_wmi_detach(ab);
	ath11k_dp_pdev_reo_cleanup(ab);
	mutex_unlock(&ab->core_lock);

	ath11k_dp_free(ab);
	ath11k_hal_srng_deinit(ab);

	ab->free_vdev_map = (1LL << (ab->num_radios * TARGET_NUM_VDEVS)) - 1;

	ret = ath11k_hal_srng_init(ab);
	if (ret)
		return ret;

	clear_bit(ATH11K_FLAG_CRASH_FLUSH, &ab->dev_flags);

	ret = ath11k_core_qmi_firmware_ready(ab);
	if (ret)
		goto err_hal_srng_deinit;

	clear_bit(ATH11K_FLAG_RECOVERY, &ab->dev_flags);

	return 0;

err_hal_srng_deinit:
	ath11k_hal_srng_deinit(ab);
	return ret;
}

void ath11k_core_halt(struct ath11k *ar)
{
	struct ath11k_base *ab = ar->ab;

	lockdep_assert_held(&ar->conf_mutex);

	ar->num_created_vdevs = 0;

	ath11k_mac_scan_finish(ar);
	ath11k_mac_peer_cleanup_all(ar);
	cancel_delayed_work_sync(&ar->scan.timeout);
	cancel_work_sync(&ar->regd_update_work);

	rcu_assign_pointer(ab->pdevs_active[ar->pdev_idx], NULL);
	synchronize_rcu();
	list_init_head(&ar->arvifs);
	idr_init(&ar->txmgmt_idr);
}

static void ath11k_core_restart(struct work_struct *work)
{
	struct ath11k_base *ab = container_of(work, struct ath11k_base, restart_work);
	struct ath11k *ar;
	struct ath11k_pdev *pdev;
	int i, ret = 0;

	spin_lock_bh(&ab->base_lock);
	ab->stats.fw_crash_counter++;
	spin_unlock_bh(&ab->base_lock);

	for (i = 0; i < ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		if (!ar || ar->state == ATH11K_STATE_OFF ||
		    ar->state == ATH11K_STATE_TM)
			continue;

		ieee80211_stop_queues(ar->hw);
		ath11k_mac_drain_tx(ar);
		complete(&ar->scan.started);
		complete(&ar->scan.completed);
		complete(&ar->peer_assoc_done);
		complete(&ar->install_key_done);
		complete(&ar->vdev_setup_done);
		complete(&ar->bss_survey_done);

		wake_up(&ar->dp.tx_empty_waitq);
		idr_for_each(&ar->txmgmt_idr,
			     ath11k_mac_tx_mgmt_pending_free, ar);
		idr_destroy(&ar->txmgmt_idr);
	}

	wake_up(&ab->wmi_ab.tx_credits_wq);
	wake_up(&ab->peer_mapping_wq);

	ret = ath11k_core_reconfigure_on_crash(ab);
	if (ret) {
		ath11k_err(ab, "failed to reconfigure driver on crash recovery\n");
		return;
	}

	for (i = 0; i < ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		if (!ar || ar->state == ATH11K_STATE_OFF)
			continue;

		mutex_lock(&ar->conf_mutex);

		switch (ar->state) {
		case ATH11K_STATE_ON:
			ar->state = ATH11K_STATE_RESTARTING;
			ath11k_core_halt(ar);
			ieee80211_restart_hw(ar->hw);
			break;
		case ATH11K_STATE_OFF:
			ath11k_warn(ab,
				    "cannot restart radio %d that hasn't been started\n",
				    i);
			break;
		case ATH11K_STATE_RESTARTING:
			break;
		case ATH11K_STATE_RESTARTED:
			ar->state = ATH11K_STATE_WEDGED;
			/* fall through */
		case ATH11K_STATE_WEDGED:
			ath11k_warn(ab,
				    "device is wedged, will not restart radio %d\n", i);
			break;
		case ATH11K_STATE_TM:
			ath11k_warn(ab, "fw mode reset done radio %d\n", i);
			complete(&ar->fw_mode_reset);
			break;
		}
		mutex_unlock(&ar->conf_mutex);
	}
	complete(&ab->driver_recovery);
}
#endif

static void ath11k_core_reset(void *context)
{
	struct ath11k_base *ab = context;

	/* clean up the cache */
    flush_firmware_cache();

	ath11k_hif_power_down(ab);
	ath11k_qmi_free_resource(ab);
	ath11k_hif_power_up(ab);

	ath11k_dbg(ab, ATH11K_DBG_BOOT, "reset started\n");
}

static int ath11k_init_hw_params(struct ath11k_base *ab)
{
	const struct ath11k_hw_params *hw_params = NULL;
	int i;

	for (i = 0; i < ARRAY_SIZE(ath11k_hw_params_list); i++) {
		hw_params = &ath11k_hw_params_list[i];

		if (hw_params->dev_id == ab->hw_rev)
			break;
	}

	if (i == ARRAY_SIZE(ath11k_hw_params_list)) {
		ath11k_err(ab,
			   "Unsupported hardware version: 0x%x\n", ab->hw_rev);
		return -EINVAL;
	}

	ab->hw_params = *hw_params;

	ath11k_dbg(ab, ATH11K_DBG_BOOT, "Hardware name %a\n",
		   ab->hw_params.name);

	return 0;
}

int ath11k_core_pre_init(struct ath11k_base *ab)
{
	int ret;

	ret = ath11k_init_hw_params(ab);
	if (ret) {
		ath11k_err(ab, "failed to get hw params: %d\n", ret);
		return ret;
	}

	return 0;
}

EXPORT_SYMBOL(ath11k_core_pre_init);

int ath11k_core_init(struct ath11k_base *ab)
{
	int ret;

	ret = ath11k_core_soc_create(ab);
	if (ret) {
		ath11k_err(ab, "failed to create soc core: %d\n", ret);
		return ret;
	}

	return 0;
}
EXPORT_SYMBOL(ath11k_core_init);

void ath11k_core_deinit(struct ath11k_base *ab)
{
	mutex_lock(&ab->core_lock);

	ath11k_core_pdev_destroy(ab);
	if (!test_bit(ATH11K_FLAG_MAC_STOPPED, &ab->dev_flags))
		ath11k_core_stop(ab);

	mutex_unlock(&ab->core_lock);

	ath11k_hif_power_down(ab);
	ath11k_mac_destroy(ab);
	ath11k_core_soc_destroy(ab);
}
EXPORT_SYMBOL(ath11k_core_deinit);

struct ath11k_base *ath11k_core_alloc(pci_dev_handle dev, size_t priv_size)
{
	struct ath11k_base *ab;

	ab = kzalloc(sizeof(*ab) + priv_size, GFP_KERNEL);
	if (!ab)
		return NULL;

    /* intialize the debug mask */
    if (cfg_is_ath_debug_mask_valid())
        ath11k_debug_mask = cfg_get_ath_debug_mask();
	
	init_completion(&ab->driver_recovery);

	//ab->workqueue = create_singlethread_workqueue("ath11k_wq");
	//if (!ab->workqueue)
	//	goto err_sc_free;

	mutex_init(&ab->core_lock);
	spin_lock_init(&ab->base_lock);
	mutex_init(&ab->vdev_id_11d_lock);

	list_init_head(&ab->peers);
	init_waitqueue_head(&ab->peer_mapping_wq);
	init_waitqueue_head(&ab->wmi_ab.tx_credits_wq);
	//INIT_WORK(&ab->restart_work, ath11k_core_restart);
	init_work(&ab->update_11d_work, ath11k_update_11d, ab);
	init_work(&ab->reset_work, ath11k_core_reset, ab);
	//timer_setup(&ab->rx_replenish_retry, ath11k_ce_rx_replenish_retry, 0);
    init_delayed_work(&ab->rx_replenish_retry, ath11k_ce_rx_replenish_retry, ab);
	ab->dev = dev;

	return ab;

//err_sc_free:
	//kfree(ab);
	
	//return NULL;
}
EXPORT_SYMBOL(ath11k_core_alloc);

void ath11k_core_free(struct ath11k_base *ab)
{
    flush_firmware_cache();
	
    kfree(ab);
}
EXPORT_SYMBOL(ath11k_core_free);

