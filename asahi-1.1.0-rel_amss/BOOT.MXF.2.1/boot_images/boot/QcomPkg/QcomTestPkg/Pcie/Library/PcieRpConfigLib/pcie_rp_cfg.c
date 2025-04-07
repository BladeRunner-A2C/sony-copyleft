/**
  @file pcie_rp_cfg_data.c
  @brief Pcie Root Port configuration instance for the target

  This file implements QC specific PCIe root port controller configuration
===============================================================================
    Copyright (c) 2020 - 2023 Qualcomm Technologies, Inc.
    All Rights Reserved.
    Confidential and Proprietary - Qualcomm Technologies, Inc.
===============================================================================
*/

#include "pcie_cfg_types.h"

extern pcie_target_config_t kailua_pcie_rp_cfg_data;
extern pcie_target_config_t hamoa_pcie_rp_cfg_data;
extern pcie_target_config_t lanai_pcie_rp_cfg_data;
extern pcie_target_config_t palawan_pcie_rp_cfg_data;


pcie_target_config_t *pcie_tgt_config_ptrs[] =
{
   &lanai_pcie_rp_cfg_data,
   &kailua_pcie_rp_cfg_data,
   &hamoa_pcie_rp_cfg_data,
   &palawan_pcie_rp_cfg_data,
};

uint32 pcie_tgt_config_ptr_cnt = ARRAY_SIZE(pcie_tgt_config_ptrs);


