/*
===========================================================================
*/
/**
  @file swsys_env_uefi_clk_switch.h

*/
/*
  ====================================================================

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  06/14/17   jh      Initial revision.

  ====================================================================
*/

#ifndef SWSYS_ENV_UEFI_CLK_SWITCH_H
#define SWSYS_ENV_UEFI_CLK_SWITCH_H

#include "../swsys_env.h"
#include <Protocol/EFINpa.h>
#include <stdbool.h>


typedef struct swsys_ddrinfo_t {
  uint8_t Type;
  uint8_t Manufacturer;
  uint8_t NumChannels;
  uint32_t Density;
} swsys_ddrinfo_t;

void init_ddr_info();
void init_shub_info();
EFI_STATUS swsys_npa_init(void);
npa_client_handle swsys_npa_request_node(const char *client_name, unsigned int client_value, void *client_ref);
void swsys_npa_destroy_node(npa_client_handle client);
void swsys_npa_issue_vector_request(npa_client_handle client, unsigned int num_elems, npa_resource_state *vector);
void swsys_init_ddr_clk_uefi(uint32_t init_freq_khz, uint32_t display_mode);
void swsys_deinit_ddr_clk_uefi();
uint8_t swsys_get_ddr_freq_table_uefi(uint32_t *freq_list);
uint32_t swsys_switch_ddr_clk_uefi(uint32_t freq_khz);
bool swsys_read_ddr_clk_uefi(uint32_t* freq_khz);
uint32_t swsys_get_max_enabled_ddr_freq(void);

void swsys_init_shub_clk_uefi(uint32_t init_freq_khz, uint32_t display_mode);
void swsys_deinit_shub_clk_uefi();
uint32_t swsys_switch_shub_clk_uefi(uint32_t freq_khz);
uint8_t swsys_get_shub_freq_table_uefi(uint32_t *freq_list);
bool swsys_read_shub_clk_uefi(uint32_t* freq_khz);

void swsys_init_cpu_clk_uefi();
void swsys_deinit_cpu_clk_uefi();
uint32_t swsys_switch_cpu_clk_uefi(uint32_t cluster, uint32_t freq_khz);
uint32_t swsys_cpu_available_clks_uefi(uint32_t cluster, uint32_t* freq_tbl);
bool swsys_read_cpu_clk_uefi(uint32_t cluster, uint32_t* freq_khz);

void swsys_icb_post_init(void);
void swsys_vote_for_quest(void);
void swsys_remove_vote_for_quest(void);
EFI_STATUS swsys_ddr_setlowbandwidth(void);
void swsys_get_DDR_info(swsys_ddrinfo_t *ddr_info);
void * swsys_map_hw_block(char* hw_block_name);
#endif // SWSYS_ENV_UEFI_FLASH_H
