/**

  This file implements QC specific PCIe root port controller configuration

         Copyright (c) 2020 - 2023 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
==============================================================================
*/

#include "pcie_rp_cfg_svc.h"
#include "pcie_host_log.h"
#include "pcie_osal.h"
#include "string.h"

/* Import our main config data structure in which we will search */
extern pcie_target_config_t* pcie_tgt_config_ptrs[];
extern uint32 pcie_tgt_config_ptr_cnt;

/* Store our selected configuration */
pcie_target_config_t *pcie_selected_config = NULL;

/**
 *  Segments that have been enabled programatically through the api
 *  These takes precedence over the pcie_disable_segment_mask
 *  Additionally, root ports enabled through the api will no longer
 *  be considered hot pluggable even if set as so.
 **/
static uint32 pcie_enable_segment_mask = 0x0;

/* Segments that are disabled programatically through the api */
static uint32 pcie_disable_segment_mask = 0x0;

/* Default enabled segments determined by settings configuration */
static uint32 pcie_default_enable_segment_mask = 0x0;

/* Superset of segment configurations available that can be enabled/disabled */
static uint32 pcie_available_segment_mask = 0x0;

/* Mask of segments that are set as hot pluggable. */
static uint32 pcie_hot_pluggable_segment_mask = 0x0;

/* Enterprise management settings */
static uint32 pcie_entp_enable_segment_mask = 0xFFFF;
static uint32 pcie_entp_mgmt_reg_val = 0xFFFF;

#ifndef MAX_SUPPORTED_PORTS_CFG
#define MAX_SUPPORTED_PORTS_CFG     8
#endif

static const pcie_port_config_t* enabled_ports_config[MAX_SUPPORTED_PORTS_CFG];

typedef enum
{
   CONFIG_ADD     = 0,
   CONFIG_REMOVE  = 1,
   CONFIG_ENABLE  = 2,
   CONFIG_DISABLE = 3,

}cfg_update_option_t;



/******************************************************************************
 *         High level design
 *
 *  The implementation in this file manages the PCIe ports configuration.
 *  At a high level source of the configuration is a super set that can contain
 *  configuration for multiple targets/platforms etc.
 *
 *  During config load operation, the implementation picks the best configuration
 *  available for the current target/platform/chip by filtering.
 *  After picking the configuration set, it caches all the relevant config
 *  in enabled_port_config on a per port basis. Note that some early filtering
 *  is already performed to make sure pick only the relevant configurations based
 *  on some register settings (like 4 Lane config). So those registers need to
 *  be initialized before the load operation.
 *
 *  Additional filtering (ie enable/disable) will be applied on top of the
 *  configurations that's cached. These filterings can be direct enable/disable,
 *  enterprise mgmt controlled etc.
 *
 ******************************************************************************/


/******************************************************************************
 *         Private functions
 ******************************************************************************/
static pcie_status_t map_port_mem_regions (const mem_region_t* port_mem_regions)
{
   int i;
   const mem_region_t* port_mem;

   for (i = 0; i < max_mem_reg; ++i)
   {
      port_mem = &port_mem_regions[i];
      if ((port_mem->pa != 0) && (port_mem->sz != 0))
      {
         if (pcie_osal_mem_region_map (port_mem->pa, port_mem->sz, PCIE_OSAL_MEM_DEVICE, NULL) != 0)
            return PCIE_ERROR;
      }
   }
   return PCIE_SUCCESS;
}

/* Add/Remove from enabled ports config list */
static pcie_status_t
pcie_update_ports_from_list (const pcie_port_config_t* ports_cfg,
                             uint32 cnt, cfg_update_option_t operation)
{
   uint32 i;

   for (i = 0; i < cnt; ++i)
   {
      if (ports_cfg->hw_rp_index < MAX_SUPPORTED_PORTS_CFG)
      {
         if (operation == CONFIG_ADD)
         {
            enabled_ports_config[ports_cfg->hw_rp_index] = ports_cfg;
            pcie_available_segment_mask |= (1 << ports_cfg->hw_rp_index);

            if (map_port_mem_regions (ports_cfg->port_mem_bases) != PCIE_SUCCESS)
            {
               PCIE_HOST_LOG_ERROR ("Mapping failed continuing anyway\n");
               //return PCIE_ERROR;
            }
         }
         else if (operation == CONFIG_REMOVE)
         {
            enabled_ports_config[ports_cfg->hw_rp_index] = NULL;
            pcie_available_segment_mask &= (~(1 << ports_cfg->hw_rp_index));
         }
      }

      ++ports_cfg;
   }
   return PCIE_SUCCESS;
}

uint32 check_reg_val_shift_masked (const pcie_reg_field_val_t* reg_spec)
{
   uint32 rval;
   const uint32* reg_addr;

   /* If Reg_spec is not given then we can consider condition failed
    * might simplify caller's code */
   if (reg_spec == NULL)
      return 0;

   reg_addr = reg_spec->reg_base_addr;
   reg_addr += (reg_spec->reg_offset / sizeof (*reg_spec->reg_base_addr)); // Ptr math

   rval = *reg_addr;

   rval = (rval >> reg_spec->fld_shift);
   rval = (rval & reg_spec->fld_mask);

   return (rval == reg_spec->fld_val);
}

static pcie_status_t pcie_get_target_platform_config (pcie_target_config_t ** target_cfg_ptr)
{
   uint32 chip_id, chip_ver, plat_info, i, chip_family;
   pcie_target_config_t *family_match_cfg = NULL, *id_match_cfg = NULL;
   pcie_target_config_t *best_match_cfg = NULL;
   uint32 cfg_chip_id, cfg_family, cfg_plat_type;

   if (target_cfg_ptr == NULL)
      return PCIE_ERROR;

   if (pcie_get_target_platform_info (&chip_id, &chip_ver, &chip_family, &plat_info) != PCIE_SUCCESS)
      return PCIE_ERROR;

   if ((chip_id == 0) || (chip_family == 0) || (plat_info == 0))
      return PCIE_ERROR;

   /* Search to see if we can find the exact match or best available */
   for (i = 0; i < pcie_tgt_config_ptr_cnt; ++i)
   {
      cfg_chip_id = pcie_tgt_config_ptrs[i]->target_chip_id;
      cfg_family = pcie_tgt_config_ptrs[i]->target_chip_family;
      cfg_plat_type = pcie_tgt_config_ptrs[i]->target_platform_type;

      if ((cfg_chip_id == 0) && (cfg_family == 0))
         continue; // Bad config skip over

      /* If plat info available and not matching continue */
      if ((cfg_plat_type != 0) && (cfg_plat_type != plat_info))
         continue;

      if ((cfg_chip_id == 0) || (cfg_chip_id == PCIE_TARGET_CHIP_ID_IGNORE))
      {
         if (cfg_family == chip_family && family_match_cfg == NULL)
            family_match_cfg = pcie_tgt_config_ptrs[i];
      }
      else if (cfg_plat_type == 0)
      {
         if (cfg_family != 0)
         {
            if ((cfg_chip_id == chip_id) && (cfg_family == chip_family))
            {
               // This would be the best fit, stop search and return
               best_match_cfg = pcie_tgt_config_ptrs[i];
               break;
            }
         }
         else if (cfg_chip_id == chip_id)
            id_match_cfg = pcie_tgt_config_ptrs[i];
      }
   }

   /* If we didn't find the exact match pick the best one */
   if (id_match_cfg != NULL)
      best_match_cfg = id_match_cfg;
   else if (family_match_cfg != NULL)
      best_match_cfg = family_match_cfg;
   else
      return PCIE_ERROR;

   *target_cfg_ptr = best_match_cfg;

   return PCIE_SUCCESS;
}

/******************************************************************************
 *         Public functions
 ******************************************************************************/

/**
 * Retrieve the PCIe configuration based on the current platform, then compile a set of available PCIe segments with a mapping
 * to the correct configuration.
 *
 * In some cases, multiple configurations exist for a single root port when different lane settings are
 * supported. The appropriate lane setting is read from the lane configuration registers and the matching configuration
 * is selected. If the default enable flag is set, that root port will be flagged to later be enabled, unless the disable flag
 * is set for that root port.
 *
 */
pcie_status_t pcie_rp_cfg_load_config (void)
{
   const pcie_port_config_t* ports_cfg;
   const uint32* entp_mgmt_addr;
   const pcie_port_options_config_t * cfg_option_ptr;
   const mem_region_t* map_rgns_p;
   int i;

   if (pcie_selected_config == NULL)
   {
      if ((pcie_get_target_platform_config (&pcie_selected_config) != PCIE_SUCCESS) ||
          (pcie_selected_config == NULL))
      {
         PCIE_HOST_LOG_ERROR ("Target platform config not found...!!\n");
         return PCIE_ERROR;
      }
   }

   /* Map in all the memory regions needed for this selected config */
   if ((pcie_selected_config != NULL) && (pcie_selected_config->common_mem_regions != NULL))
   {
      map_rgns_p = pcie_selected_config->common_mem_regions;
      while (map_rgns_p->pa)
      {
         if (pcie_osal_mem_region_map (map_rgns_p->pa, map_rgns_p->sz, PCIE_OSAL_MEM_DEVICE, NULL) != 0)
         {
            PCIE_HOST_LOG_ERROR ("Region mapping failed %lX %lX...!!\n", map_rgns_p->pa, map_rgns_p->sz);
            return PCIE_ERROR;
         }

         ++map_rgns_p;
      }
   }

   /* If entp mgmt address is available, then cache the value reg */
   entp_mgmt_addr = pcie_selected_config->entp_mgmt_addr;
   if (entp_mgmt_addr)
      pcie_entp_mgmt_reg_val = *entp_mgmt_addr;

   /**
    * Create the list of available segments mapped to their settings.
    * Enable only those that have the default enable flag set, and have not been
    * explicitly disabled.
    **/
   for (i = 0; i < pcie_selected_config->target_port_option_cnt; ++i)
   {
      uint32 add_this_port = 1;
      cfg_option_ptr = &pcie_selected_config->target_port_option_list[i];
      ports_cfg = cfg_option_ptr->ports_config_list;
      uint32 pcie_segment_mask = 1 << ports_cfg->hw_rp_index;

      /* Cache entp mgmt status for this port */
      if (ports_cfg->entp_mgmt_idx < (8 * sizeof(uint32)))
      {
         if ((pcie_entp_mgmt_reg_val & (1 << ports_cfg->entp_mgmt_idx)) == 0)
            pcie_entp_enable_segment_mask &= ~pcie_segment_mask;
      }
      if (cfg_option_ptr->hot_pluggable)
      {
         pcie_hot_pluggable_segment_mask |= pcie_segment_mask;
      }
      if (!cfg_option_ptr->default_enable)
      {
         /**
          * If a select condition exists, this configuration is one of a set that is conditionally selected.
          * If this is not the selected condtion, this configuration will not be added to the available
          * configurations.
          */
         if (cfg_option_ptr->config_select_condition != NULL)
         {
            add_this_port = check_reg_val_shift_masked (cfg_option_ptr->config_select_condition);
         }
      }
      else
      {
         /**
          * If the EFIPciePlatPolicyProtocol has been used to explicitly disable a port,
          * override the default enable flag and do not enable this segment
          */
         pcie_default_enable_segment_mask |= (pcie_segment_mask & ~pcie_disable_segment_mask);
      }

      if (add_this_port)
         pcie_update_ports_from_list (ports_cfg,
                                      *(cfg_option_ptr->ports_config_cnt),
                                      CONFIG_ADD);
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_cfg_reload_config (void)
{
   int i;

   pcie_available_segment_mask = 0;
   pcie_default_enable_segment_mask = 0;
   pcie_hot_pluggable_segment_mask = 0;

   for (i=0; i < ARRAY_SIZE(enabled_ports_config); ++i)
      enabled_ports_config[i] = NULL;

   pcie_rp_cfg_load_config ();

   return PCIE_SUCCESS;
}

#if 0
uint32 pcie_rp_cfg_get_version (void)
{
   if (pcie_selected_config == NULL)
      return 0;

   return pcie_selected_config->config_data_version;
}
#endif

uint32 pcie_rp_cfg_get_max_port_count (void)
{
   if (pcie_selected_config == NULL)
      return 0;

   return pcie_selected_config->max_port_index + 1;
}

uint32 pcie_rp_cfg_get_target_chip_family (void)
{
   if (pcie_selected_config == NULL)
      return -1;

   return pcie_selected_config->target_chip_family;
}

pcie_status_t pcie_rp_cfg_enable_port(uint32 port_index)
{
   pcie_enable_segment_mask |= 1 << port_index;
   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_cfg_disable_port (uint32 port_index)
{
   pcie_disable_segment_mask |= 1 << port_index;
   return PCIE_SUCCESS;
}

pcie_status_t pcie_rp_cfg_disable_ports_mask (uint32 disable_mask)
{
   pcie_disable_segment_mask |= disable_mask;
   return PCIE_SUCCESS;
}

/**
 * For a root port to be considered enabled, there are two prerequisites:
 *    1. A cofiguration exists for this root port, determined by checking pcie_available_segment_mask
 *    2. The root port is enabled through enterprise management
 *
 * In addition, one or both of the following must be true for a root port to be considered enabled:
 *    - The root port has been enabled by default in settings AND has not been disabled through
 *      the EFIPciePlatPolicyProtocol
 *    - The root port has been enabled using EFIPciePlatPolicyProtocol
 *
 * @return the mask of PCIe segments that have been set to be enabled
 */
uint32 pcie_rp_cfg_get_enabled_ports_mask (void)
{
   uint32 enabled_ports;

   enabled_ports = pcie_available_segment_mask;
   enabled_ports &= (pcie_enable_segment_mask |
                     pcie_default_enable_segment_mask);
   enabled_ports &= pcie_entp_enable_segment_mask;

   return enabled_ports;
}

uint32 pcie_rp_is_hot_pluggable (uint32 rp_index)
{
   uint32 this_rp_mask = 1 << rp_index;
   /* If the enable api has been used to enable this root port, override the
      hot pluggable flag. In the case of the segment 3, this is currently how we
      determine whether the use case is sd express, or dGpu
   */
   if ((this_rp_mask & pcie_enable_segment_mask) == 0)
   {
      return this_rp_mask & pcie_hot_pluggable_segment_mask;
   }
   return 0;
}

pcie_status_t pcie_rp_cfg_get_config (uint32 rp_index, const pcie_port_config_t** rp_cfg_ptr)
{
   uint32 segment_mask = 1 << rp_index;
   if ((rp_cfg_ptr == NULL) || (rp_index >= MAX_SUPPORTED_PORTS_CFG))
      return PCIE_INVALID_PARAM;

   *rp_cfg_ptr = NULL;

   if ((pcie_available_segment_mask & segment_mask) == 0)
      return PCIE_NOT_FOUND;

   if ((pcie_entp_enable_segment_mask & segment_mask) == 0)
      return PCIE_DISABLED;

   /* Considered disabled if it has not been explicitly enabled AND the default enable flag has not been set */
   if ((~(pcie_enable_segment_mask | pcie_default_enable_segment_mask )) & segment_mask)
      return PCIE_DISABLED;

   *rp_cfg_ptr = enabled_ports_config[rp_index];

   return PCIE_SUCCESS;
}

pcie_status_t
pcie_rp_cfg_get_hw_config_info (const char * name,
                                const pcie_reg_field_val_t** select_conditional_ptr)
{
   uint32 i;
   const pcie_port_options_config_t * cfg_option_ptr, *new_cfg = NULL;

   if (name == NULL)
      return PCIE_ERROR;

   if (pcie_selected_config == NULL)
   {
      if ((pcie_get_target_platform_config (&pcie_selected_config) != PCIE_SUCCESS) ||
          (pcie_selected_config == NULL))
         return PCIE_ERROR;
   }

   /* Search for the list and get exclusive key */
   for (i = 0; i < pcie_selected_config->target_port_option_cnt; ++i)
   {
      cfg_option_ptr = &pcie_selected_config->target_port_option_list[i];

      if (strcmp (cfg_option_ptr->port_config_name, name) == 0)
      {
//         key = cfg_option_ptr->exclusive_key;
         new_cfg = cfg_option_ptr;
         break;
      }
   }

   /* Note that this setting must be applied before ports can be initialized */
   if ((new_cfg != NULL) && (select_conditional_ptr != NULL))
      *select_conditional_ptr = new_cfg->config_select_condition;

   return PCIE_SUCCESS;
}


