#!/usr/bin/env python

DB_OVERRIDE = {
  'GCC': {
    'cbc': {
      'gcc_aggre_usb3_prim_axi_clk': {'func_group': 'usb30_prim'},
      'gcc_aggre_ufs_phy_axi_clk': {'func_group': 'ufs_phy'},
      'gcc_cfg_noc_usb3_prim_axi_clk': {'func_group': 'usb30_prim'},
    },
    'gdsc': {
      'gcc_ufs_mem_phy_gdsc': {'func_group': 'ufs_phy'},
    },
  },
  'TCSR_CC': {
    'cbc': {
      'tcsr_ufs_clkref_en': {'func_group': 'ufs_phy'},
      'tcsr_usb3_clkref_en': {'func_group': 'usb30_prim'},
    },
  },
}


CLOCK_FLAGS = {
  'gcc_gpll0':                   ['DO_NOT_DISABLE'],
  'gcc_ufs_phy_rx_symbol_0_clk': ['NO_POLL_AFTER_ENABLE'],
  'gcc_ufs_phy_rx_symbol_1_clk': ['NO_POLL_AFTER_ENABLE'],
  'gcc_ufs_phy_tx_symbol_0_clk': ['NO_POLL_AFTER_ENABLE'],
  'gcc_usb3_prim_phy_pipe_clk':  ['NO_POLL_AFTER_ENABLE'],
}

CLOCK_FLAGS_HAL = {
  '.*': ['!DIVIDER_SUPPORTS_HID'],
}

FUNC_GROUPS = [
  'core',
  'boot_rom',
  'ddrss',
  'qspi',
  'sdcc.*',
  'ufs_phy',
  'usb30_prim',
]

RAMDUMP_FUNC_GROUPS = [
  'ufs_phy',
  'sdcc.*',
  'usb30_prim',
]

source_freq_format = """\
  {{{{ {{{{ {ALPHA}, HAL_CLK_PLL_FRAC_MODE_{FRACMODE}, {POST:<30}, {L:<4} }}}}, {{VERSION}}}}}},
"""

domain_freq_format = """\
  {{{{ {FREQ:>10}, {VREG:<30} {{{{ {SEL:<6} {DIV:<6} {M:<6} {N:<6} {DFS:<4} }}}}, {SOURCE:<45} {SOURCE_FREQ_IDX:<20}, {{VERSION}} }}}},  {COMMENT}
"""

HAL_CONTROL = {
  'apss_cc_gold_pll':      'HAL_clk_ZondaoleV2PLLControl',
  'apss_cc_gold_plus_pll': 'HAL_clk_ZondaoleV2PLLControl',
  'apss_cc_l3_pll':        'HAL_clk_ZondaoleV2PLLControl',
  'apss_cc_silver_pll':    'HAL_clk_ZondaoleV2PLLControl',
  'aoss_cc_pll1':          'HAL_clk_PongooleLanaiPLLControl',
}

CLOCKDRIVERGEN_CONFIG = {
  'target': 'lanai',
  'filter_warning': 'sw',
  'db_override' : DB_OVERRIDE,

  'generators': [
    {
      'type': 'dalclock',
      'output_dir': 'image/Loader',
      'options': {
        'clock_flags': CLOCK_FLAGS,
        'clock_flags_hal': CLOCK_FLAGS_HAL,
        'hal_ctl_structs': HAL_CONTROL,
        'env': ['boot'],
        'explicit_ownership': True,
        'ignore_env_for_pll_settings': True,
        'include_all_freqs': ['.*sdc.*'],
        'include_boot_enable_list': True,
        'include_ClockBSPExtern.h': True,
        'include_debug_mux': False,
        'include_default_freqs': False,
        'include_domain_array': False,
        'include_init_domains': True,
        'include_fmax': False,
        'include_HALclkTest.c': False,
        'include_only_fmax': {'.*': ['nominal']},
        'include_only_freqs': {
          '.*qup.*wrap._s.*': [7372800, 14745600, 19200000, 48000000],
          'gcc_config_noc_clk_src': [19200000, 75000000],
          'gcc_memnoc_clk_src': [806000000, 933000000, 1066000000],
        },
        'include_pllout_hw_ctl': True,
        'include_power_domains': False,
        'include_source_map': False,
        'include_source_name': False,
        'include_unique_id': False,
        'include_voltage_control': False,
        'include_xo_voting': False,
        'no_static_scope': ['.*'],
        'include_master_enums': True,
        'include_clock_groups': FUNC_GROUPS,
        'include_clocks': ['.*qup.*_s._.*', 'gcc_memnoc_clk', 'gcc_shrm_clk'],
        'source_freq_config_format': source_freq_format,
        'domain_freq_config_format': domain_freq_format,
        'include_control': ['source'],
        'include_bcrs': False,
        'source_enums': True,
        'detect_configs': False,
        'pll_disable_mode': None,
        'flat_structs': True,
      },
    },
    {
      'type': 'dalclock',
      'output_dir': 'image/RamDump',
      'options': {
        'clock_flags': CLOCK_FLAGS,
        'clock_flags_hal': CLOCK_FLAGS_HAL,
        'env': 'ramdump',
        'explicit_ownership': True,
        'include_source_map': False,
        'include_fmax': False,
        'include_source_name': False,
        'include_debug_mux': False,
        'include_HALclkTest.c': False,
        'include_unique_id': False,
        'include_voltage_control': False,
        'include_xo_voting': False,
        'include_divider':['.*disp_cc.*'],
        'source_freq_config_format': source_freq_format,
        'domain_freq_config_format': domain_freq_format,
        'include_only_freqs': {'.*qup.*wrap._s.*': [7372800, 14745600, 19200000, 48000000]},
        'include_clock_groups': RAMDUMP_FUNC_GROUPS,
        'include_control': ['source'],
        'include_bcrs': False,
        'source_enums': True,
        'detect_configs': False,
        'pll_disable_mode': None,
        'flat_structs': True,
      },
    },
  ],
}


if __name__ == "__main__":
  import sys, os
  from subprocess import call

  if os.name == 'nt':
    clockdrivergen_path = r'\\ben\corebsp_labdata_0001\sysdrv\clockdrivergen\bin\clockdrivergen.py'
  else:
    clockdrivergen_path = r'/prj/qct/corebsp_labdata_0001/sysdrv/clockdrivergen/bin/clockdrivergen.py'

  call(['python3', clockdrivergen_path, '--cfg', __file__] + sys.argv[1:])

