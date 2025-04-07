#===========================================================================
#
#  @file bcm_hwio.py
#
#  ===========================================================================
#
#  Copyright (c) 2022 Qualcomm Technologies, Inc.
#  All rights reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================
#
#  $Header: //components/rel/aop.ho/4.0/aop_proc/core/systemdrivers/icb/src/palima/bcm_hwio.py#1 $
#  $DateTime: 2021/11/04 23:45:10 $
#  $Author: pwbldsvc $
#
#  ===========================================================================

_header = """
#include <HALhwio.h>
#include <msmhwiobase.h>
"""
_modules = ['.*RPMH_BCM.*']

#_trailer = """"""

# ============================================================================
# HWIO_REGISTER_FILES
# ============================================================================

HWIO_REGISTER_FILES = [
  {
    'filename': 'bcm_hwio.h',
    'modules': _modules,
         'module-filter-exclude': {
         'RPMH': ['CD0_CPn','CD1_CPn','CD2_CPn','CD3_CPn','CD4_CPn',
                  'CD5_CPn','CD6_CPn','CD7_CPn','CD8_CPn','CD9_CPn',
                  'CD10_CPn','CD11_CPn','CD12_CPn','CD13_CPn','CD14_CPn',
                  'CD15_CPn'],
         },
    'create-array': [
      [ 'CD_TH_CD0_CPn',
        { 'array_offset': 0x40, 'max_index': 15, 'arg': 'm', 'arg_pos': 8 } ],
      [ 'TCS_CFG_VOTE_DATA_CD0_CPn',
        { 'array_offset': 0x40, 'max_index': 15, 'arg': 'm', 'arg_pos': 20 } ],
    ],
    'map-type': 'physical',
    'check-sizes': True,
    'check-for-overlaps': True,
    'header': _header,
    'ignore-prefixes':True,
  },
  { u'filename': u'bcm_ext_hwio.h',
    u'header': u'#include "msmhwiobase.h"\n#include "HALhwio.h"',
    u'module-filter-exclude': { },
    u'module-filter-include': { u'GCC_CLK_CTL_REG': [ u'MMNOC',
                                                      u'GDS_HW_CTRL_SW'],
                                u'TCSR_TCSR_REGS' : [ u'TCSR_TIMEOUT_INTR_CH2_CH4_OR_CH6_STATUS']},
    u'modules': [u'GCC_CLK_CTL_REG',
                 u'TCSR_TCSR_REGS']
  },
]

# ============================================================================
# Main
#
# Entry point when invoking this directly.
# ============================================================================

if __name__ == "__main__":
  import sys, os
  from subprocess import call

  flat_path = '../../../../Tools/hwio/ARM_ADDRESS_FILE_SW.FLAT'
  if os.name == 'nt':
    hwio_path = r'\\ben\corebsp_labdata_0001\sysdrv\hwio\legacy\HWIOGen.py'
  else:
    hwio_path = r'/net/ben/vol/eng_asw_labdata_0001/corebsp_labdata_0001/sysdrv/hwio/legacy/HWIOGen.py'

  call(['python', hwio_path, '--cfg', __file__, '--flat', flat_path] + sys.argv[1:])
