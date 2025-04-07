import os
import sys
if os.name == 'nt':
   sys.path.append(r'\\ben\coreplatform_pcie\autogen')
else:
   sys.path.append(r'/prj/qct/coreplatform/pcie/autogen')
import pcie_gen_bsp

# Folder Config (relative to this script's location in the build)
[lanai_folder, tools] = os.path.split(os.getcwd())
tgt_output_folder = lanai_folder
core_output_folder = lanai_folder

# Global Config
image = 'uefi'

# List of Common Modules
common_modules = []

# List of all modules to include in the FLAT file
all_modules = common_modules + [
   'PCIE.*'
]

# Chip Config
chip_configs = [
   {
      'tag': 'v1',
      'alias': 'lanai_1.0',
      'release': 'latest',
      'modules': all_modules,
      'mem-map-name': 'ARM_ADDRESS_FILE_SW',
      'skip-if-exists': True,
   },
]

# HSR Config
hsr_configs = [
   # Segment 0
   {
      'tag': 'pcie_3x2',
      'hsr-name': 'PCIe Gen3 2-lane PHY (n4)',
      'chip-alias': 'lanai_1.0',
      'release': 'latest',
      'skip-if-exists': True,
   },

   # Segment 1
   {
      'tag': 'pcie_4x2',
      'hsr-name': 'QMP PCIe 4.0 PHY HSR for n4',
      'chip-alias': 'lanai_1.0',
      'release': 'latest',
      'skip-if-exists': True,
   },
]

# HWIO Header Config
hwio_configs = [

   # 3x2 - Segment 0
   {
      'chip-config-tag': 'v1',
      'hwio-config': {
         'filename': os.path.relpath(os.path.join(tgt_output_folder, 'pcie_hwio_3x2.h')),
         'modules': ['PCIE0_.*', 'PCIE_GEN3X2_0.*'],
         'module-filter-exclude': {
            'PCIE0.*': ['.*_MHI'],
            'PCIE_GEN3X2.*': ['.*TYPE0_.*', '.*DMA_.*'],
            'PCIE_GEN3X2_0_DWC_PCIE_DM_IATU': ['.*TYPE0_.*', '.*DMA_.*'],
            'PCIE_GEN3X2_0_PCIE_DBI': ['.*TYPE0_.*', '.*DMA_.*'],
            'PCIE_GEN3X2_0_PCIE_ELBI': ['.*TYPE0_.*', '.*DMA_.*'],
         },
         'output-fvals': True,
         'output-phys': False,
         'output-offsets': True,
         'explicit-addressing': ['PCIE.*'],
         'prefix-overrides': {
            'PCIE0_CM_PCIE': 'PCIE_',
            'PCIE0_PCIE_MHI': '',
            'PCIE0_PCIE_PARF': '',
            'PCIE0_PCS_COM_PCS_COM_PCIE3_PCS_COM': 'PCS_COM_',
            'PCIE0_PCS_INTGEN_PCS_INTGEN_PCIE3_PCS_DEBUG_INTGEN': 'PCS_INTGEN_',
            'PCIE0_PCS_LANE0_PCS_LANE0_PCIE3_PCS_LANE': 'PCS_LANE0_PCS_LANE_',
            'PCIE0_PCS_LANE0_PCS_LANE0_PCIE3_PCS_PCIE_LANE': 'PCS_LANE0_',
            'PCIE0_PCS_LANE1_PCS_LANE1_PCIE3_PCS_LANE': 'PCS_LANE1_PCS_LANE_',
            'PCIE0_PCS_LANE1_PCS_LANE1_PCIE3_PCS_PCIE_LANE': 'PCS_LANE1_',
            'PCIE0_PCS_PCIE_PCS_PCIE_PCIE3_PCS_PCIE': 'PCS_PCIE_',
            'PCIE0_QSERDES_PLL_QSERDES_PLL_PCIE3_QMP_PLL': 'QSERDES_PLL_',
            'PCIE0_QSERDES_RX0_QSERDES_RX0_PCIE3_QMP_RX': 'QSERDES_RX0_',
            'PCIE0_QSERDES_RX1_QSERDES_RX1_PCIE3_QMP_RX': 'QSERDES_RX1_',
            'PCIE0_QSERDES_TX0_QSERDES_TX0_PCIE3_QMP_TX': 'QSERDES_TX0_',
            'PCIE0_QSERDES_TX1_QSERDES_TX1_PCIE3_QMP_TX': 'QSERDES_TX1_',
            'PCIE_GEN3X2_0_DWC_PCIE_DM_IATU': 'PCIE_',
            'PCIE_GEN3X2_0_PCIE_DBI': 'PCIE_',
            'PCIE_GEN3X2_0_PCIE_ELBI': '',
         },
         'explicit-addressing-references': [
            ('PCIE0.*', 'PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2'),
            ('PCIE_GEN3X2_0.*', 'PCIE_GEN3X2_0_PCIE_WRAPPER_AXI_G3X2'),
         ],
         'create-array': [
            ['IATU_\w+_0', {'array_offset': 0x200, 'max_index': 8, 'arg': 'a', 'arg_pos': -1}],
         ],
      }
   },

   # 4x2 - Segment 1
   {
      'chip-config-tag': 'v1',
      'hwio-config': {
         'filename': os.path.relpath(os.path.join(tgt_output_folder, 'pcie_hwio_4x2.h')),
         'modules': ['PCIE1_.*', 'PCIE_GEN4X2_1.*'],
         'module-filter-exclude': {
            'PCIE1.*': ['.*_MHI'],
            'PCIE_GEN4X2_.*': ['.*TYPE0_.*', '.*DMA_.*'],
            'PCIE_GEN4X2_1_DWC_PCIE_DM_IATU': ['.*TYPE0_.*', '.*DMA_.*'],
            'PCIE_GEN4X2_1_PCIE_DBI': ['.*TYPE0_.*', '.*DMA_.*'],
            'PCIE_GEN4X2_1_PCIE_ELBI': ['.*TYPE0_.*', '.*DMA_.*'],
         },
         'output-fvals': True,
         'output-phys': False,
         'output-offsets': True,
         'explicit-addressing': ['PCIE.*'],
         'prefix-overrides': {
            'PCIE1_CM_PCIE': 'PCIE_',
            'PCIE1_PCIE_MHI': '',
            'PCIE1_PCIE_PARF': '',
            'PCIE1_PCIE4_PCS_COM_PCIE4_PCS_COM_PCIE4_PCS_COM': 'PCIE4_PCS_COM_',
            'PCIE1_PCIE4_PCS_LANE0_PCIE4_PCS_LANE0_PCIE4_PCS_LANE': 'PCIE4_PCS_LANE0_PCS_LANE_',
            'PCIE1_PCIE4_PCS_LANE0_PCIE4_PCS_LANE0_PCIE4_PCS_PCIE_LANE': 'PCIE4_PCS_LANE0_',
            'PCIE1_PCIE4_PCS_LANE1_PCIE4_PCS_LANE1_PCIE4_PCS_LANE': 'PCIE4_PCS_LANE1_PCS_LANE_',
            'PCIE1_PCIE4_PCS_LANE1_PCIE4_PCS_LANE1_PCIE4_PCS_PCIE_LANE': 'PCIE4_PCS_LANE1_',
            'PCIE1_PCIE4_PCS_PCIE_PCIE4_PCS_PCIE_PCIE4_PCS_PCIE': 'PCIE4_PCS_PCIE_',
            'PCIE1_QSERDES_LN_SHRD_QSERDES_LN_SHRD_PCIE4_QMP_LN_SHRD': 'QSERDES_LN_SHRD_',
            'PCIE1_QSERDES_PLL_QSERDES_PLL_PCIE4_QMP_PLL': 'QSERDES_PLL_',
            'PCIE1_QSERDES_RX0_QSERDES_RX0_PCIE4_QMP_RX': 'QSERDES_RX0_',
            'PCIE1_QSERDES_RX1_QSERDES_RX1_PCIE4_QMP_RX': 'QSERDES_RX1_',
            'PCIE1_QSERDES_TX0_QSERDES_TX0_PCIE4_QMP_TX': 'QSERDES_TX0_',
            'PCIE1_QSERDES_TX1_QSERDES_TX1_PCIE4_QMP_TX': 'QSERDES_TX1_',
            'PCIE_GEN4X2_1_DWC_PCIE_DM_IATU': 'PCIE_',
            'PCIE_GEN4X2_1_PCIE_DBI': 'PCIE_',
            'PCIE_GEN4X2_1_PCIE_ELBI': '',
         },
         'explicit-addressing-references': [
            ('PCIE1.*', 'PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2'),
            ('PCIE_GEN4x2_1.*', 'PCIE_GEN4X2_1_PCIE_WRAPPER_AXI_G4X2'),
         ],
         'create-array': [
            ['IATU_\w+_0', {'array_offset': 0x200, 'max_index': 8, 'arg': 'a', 'arg_pos': -1}],
         ],
      }
   },
]

phy_cfg_mask_3x2 = [

   # Any combination (in pairs) of the following keys can be used:
   #
   #   'register': 'HSR Register Name',
   #   'match': 'Comment line text to match'
   #   'exclude': Value independent. Excludes if key included.

   {
      'register': 'PCS_COM_SW_RESET',
      'exclude': True,
   },
   {
      'register': 'PCS_COM_START_CONTROL',
      'exclude': True,
   },
   {
      'register': 'QSERDES_PLL_SSC_EN_CENTER',
      'match': 'Downspread SSC enabled',
   },
   {
      'register': 'QSERDES_PLL_SSC_PER1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_SSC_PER2',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_SSC_STEP_SIZE1_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_SSC_STEP_SIZE2_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_SSC_STEP_SIZE1_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_SSC_STEP_SIZE2_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_SYSCLK_EN_SEL',
      'match': 'select SE cmos clock input',
   },
   {
      'register': 'QSERDES_PLL_BG_TIMER',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_LOCK_CMP1_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_LOCK_CMP2_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_LOCK_CMP1_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_LOCK_CMP2_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DEC_START_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DEC_START_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DIV_FRAC_START1_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DIV_FRAC_START2_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DIV_FRAC_START3_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DIV_FRAC_START1_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DIV_FRAC_START2_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DIV_FRAC_START3_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_RX0_GM_CAL',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_TX0_RES_CODE_LANE_OFFSET_RX',
      'match': 'value for Lanai',
   },
   {
      'register': 'QSERDES_TX0_RES_CODE_LANE_OFFSET_TX',
      'match': 'value for Lanai',
   },
   {
      'register': 'QSERDES_RX1_GM_CAL',
      'match': 'value for others',
   },

   {
      'register': 'QSERDES_TX1_RES_CODE_LANE_OFFSET_RX',
      'match': 'value for Lanai',
   },
   {
      'register': 'QSERDES_TX1_RES_CODE_LANE_OFFSET_TX',
      'match': 'value for Lanai',
   },
   {
      'register': 'PCS_LANE1_INSIG_SW_CTRL2',
      'match': '2-lane mode',
   },
   {
      'register': 'PCS_LANE1_INSIG_MX_CTRL2',
      'match': '2-lane mode',
   },

]

# Config Masks
phy_cfg_mask_4x2 = [

   # Any combination (in pairs) of the following keys can be used:
   #
   #   'register': 'HSR Register Name',
   #   'match': 'Comment line text to match'
   #   'exclude': Value independent. Excludes if key included.

   {
      'register': 'PCIE4_PCS_COM_SW_RESET',
      'exclude': True,
   },
   {
      'register': 'PCIE4_PCS_COM_START_CONTROL',
      'exclude': True,
   },
   {
      'register': 'QSERDES_TX0_RES_CODE_LANE_OFFSET_TX',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX0_GM_CAL',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX0_RX_MODE_RATE2_B0',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX0_RX_MODE_RATE2_B1',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX0_RX_MODE_RATE2_B2',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX0_RX_MODE_RATE2_B4',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX0_RX_MODE_RATE3_B0',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX0_RX_MODE_RATE3_B1',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX0_RX_MODE_RATE3_B2',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_TX1_RES_CODE_LANE_OFFSET_TX',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX1_GM_CAL',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX1_RX_MODE_RATE2_B0',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX1_RX_MODE_RATE2_B1',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX1_RX_MODE_RATE2_B2',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX1_RX_MODE_RATE2_B4',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX1_RX_MODE_RATE3_B0',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX1_RX_MODE_RATE3_B1',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_RX1_RX_MODE_RATE3_B2',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_LN_SHRD_RX_MODE_RATE_0_1_B0',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_LN_SHRD_RX_MODE_RATE_0_1_B4',
      'match': 'value for others',
   },
   {
      'register': 'QSERDES_PLL_SSC_STEP_SIZE1_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_SSC_STEP_SIZE2_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_LOCK_CMP1_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_LOCK_CMP2_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DEC_START_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DIV_FRAC_START1_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DIV_FRAC_START2_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DIV_FRAC_START3_MODE1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_SSC_STEP_SIZE1_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_SSC_STEP_SIZE2_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_LOCK_CMP1_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_LOCK_CMP2_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DEC_START_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DIV_FRAC_START1_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DIV_FRAC_START2_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_DIV_FRAC_START3_MODE0',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_BG_TIMER',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_SSC_EN_CENTER',
      'match': 'Downspread SSC enabled',
   },
   {
      'register': 'QSERDES_PLL_SSC_PER1',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_SSC_PER2',
      'match': '38.4'
   },
   {
      'register': 'QSERDES_PLL_SYSCLK_EN_SEL',
      'match': 'select SE cmos clock input',
   },
   {
      'register': 'PCIE4_PCS_COM_FLL_CNTRL2',
      'match': 'value for half frequency',
   },
   {
      'register': 'PCIE4_PCS_COM_FLL_CNT_VAL_L',
      'match': 'value for half frequency',
   },
   {
      'register': 'PCIE4_PCS_COM_FLL_CNT_VAL_H_TOL',
      'match': 'value for half frequency',
   },
   {
      'register': 'PCIE4_PCS_PCIE_INT_AUX_CLK_CONFIG1',
      'match': 'Lanai',
   },
   {
      'register': 'PCIE4_PCS_COM_PCS_TX_RX_CONFIG1',
      'match': 'set Pinf RTB depth to 5',
   },
   {
      'register': 'PCIE4_PCS_LANE0_OUTSIG_MX_CTRL2',
      'match': 'Link partner Tx Preset adjusted during RxEq training',
   },
   {
      'register': 'PCIE4_PCS_LANE1_OUTSIG_MX_CTRL2',
      'match': 'Link partner Tx Preset adjusted during RxEq training',
   },
   {
      'register': 'PCIE4_PCS_LANE1_INSIG_SW_CTRL2',
      'match': '2-lane mode',
   },
   {
      'register': 'PCIE4_PCS_LANE1_INSIG_MX_CTRL2',
      'match': '2-lane mode',
   },
]

# PHY Settings Generation Config
phy_settings_configs = [
   # Segment 0
   {
      'phy_cfg_mask': phy_cfg_mask_3x2,
      'phy_prefix': 'PCIE0_',
      'hsr-config-tag': 'pcie_3x2',
      'chip-config-tag': 'v1',
      'filename': os.path.relpath(os.path.join(core_output_folder, 'rp_cfg_0.c')),
      'struct_name': 'port_0_phy_init_seq',
      'mode': 'RC',
      'sheet_names': ['tsmcn4 PCIe RC Seq',],
      'ignore_writing_por_value': False,
      'image': image,
   },

   # Segment 1
   {
      'phy_cfg_mask': phy_cfg_mask_4x2,
      'phy_prefix': 'PCIE1_',
      'hsr-config-tag': 'pcie_4x2',
      'chip-config-tag': 'v1',
      'filename': os.path.relpath(os.path.join(core_output_folder, 'rp_cfg_1.c')),
      'struct_name': 'port_1_phy_init_seq',
      'mode': 'RC',
      'sheet_names': ['tsmcn4 PCIe RC Cfg Seq',],
      'ignore_writing_por_value': False,
      'image': image,
   },
]

# Summary configuration dictionary
config = {
   'chip-configs': chip_configs,
   'hwio-configs': hwio_configs,
   'hsr-configs': hsr_configs,
   'phy-settings-configs': phy_settings_configs,
}

try:
   pcie_gen_bsp.gen_bsp(config)

except Exception as x:
   print('Failed to generate BSP')
   print(x)

# input only works in python3 and raw_input only works in python2
try:
    input = raw_input
except NameError:
    pass

input('Done - press Enter to exit')
