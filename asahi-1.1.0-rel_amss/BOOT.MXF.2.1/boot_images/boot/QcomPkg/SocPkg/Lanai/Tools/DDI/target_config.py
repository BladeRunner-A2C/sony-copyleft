
#=============================================================================
# FILE:         target_config.py
#
# OVERVIEW:     DDI related target configuration
#
#               Copyright (c) 2018-2023 Qualcomm Technologies, Inc.
#               All Rights Reserved.
#               Qualcomm Technologies Proprietary and Confidential.
#=============================================================================
#==============================================================================
#                              EDIT HISTORY
#
# when       who       what, where, why
# --------   ---       ----------------------------------------------------------
# 02/04/23   dingtsen   Initial Revision
#
#==============================================================================

import os
#TODO: run-time auto-detect
# GLOBAL VARIABLES
DEFAULT_TARGET = "SM8650"

DDILibTargetSettings = {
    "SM8550" : {
        "topology" : {"NUM_CH" : 4, "NUM_CS" : 2},
        "ProfilePkg" : os.path.join("ssg_tmefwrel","profiles","kailua","kailua_tme_security_profile.xml"),
        "OSPathDSFPkg" : os.path.join("SocPkg","Kailua"),
        "LP5": "LPDDR5",
        "binaries_ordered_by_header_index": [#'DCB_CRC',
                                                    #'DCB_SIZE',
                                                    #'DSF_MAINLINE_VERSION',
                                                    #'DSF_MAJOR_VERSION',
                                                    #'DSF_MINOR_VERSION',
                                                    'DDI_INPUT',
                                                    'RUNTIME',
                                                    'LCP_INPUT_STRUCT',
                                                    'MC_PXI_PRE_TRAINING',
                                                    'MC_PXI_RD',
                                                    'MC_PXI_WR',
                                                    'MC_PXI_RCW',
                                                    'MC_PXI_WRLVL',
                                                    'MC_PXI_CBT',
                                                    'SAVE_RESTORE',
                                                    'TRAINING_PARAMS',
                                                    'MC_STATES',
                                                    'SHUB_STATES',
                                                    'SHRM_STATES',
                                                    'DEFAULT_ALC_POLICY',
                                                    'ALC_TIMINGS',
                                                    'ALC_POLICY_INDEX',
                                                    'PERF_MODE_ALC_POLICY',
                                                    'PMIC_SETTINGS',
                                                    'MIN_DDR_SHUB_RATIO',
                                                    'MIN_SHUB_CP',
                                                    'ECDT_PRE_DEVICE_INIT',
                                                    'ECDT_POST_DEVICE_INIT',
                                                    'DDRSS',
                                                    'NOC',
                                                    'SHRM',
                                                    'SHRM2',
                                                    'MCCC_MSTR',
                                                    'MCCC_SLV',
                                                    'DDRPHY',
                                                    'MC',
                                                    'LLCC',
                                                    'AHB2PHY',
                                                    'SHRM_DUMP'],

        "DCB_MAX_SIZE":((1024*50)+4),
    },
    "SM8650" : {
        "topology" : {"NUM_CH" : 4, "NUM_CS" : 2},
        "ProfilePkg" : os.path.join("ssg_tmefwrel","profiles","lanai","lanai_tme_security_profile.xml"),
        "OSPathDSFPkg" : os.path.join("SocPkg","Lanai"),
        "LP5": "LPDDR5",
        "binaries_ordered_by_header_index":[#'DCB_CRC',
                                                    #'DCB_SIZE',
                                                    #'DSF_MAINLINE_VERSION',
                                                    #'DSF_MAJOR_VERSION',
                                                    #'DSF_MINOR_VERSION',
                                                    'DDI_INPUT',
                                                    'RUNTIME',
                                                    'LCP_INPUT_STRUCT',
                                                    'MC_PXI_PRE_TRAINING',
                                                    'MC_PXI_RD',
                                                    'MC_PXI_WR',
                                                    'MC_PXI_RCW',
                                                    'MC_PXI_WRLVL',
                                                    'MC_PXI_CBT',
                                                    'SAVE_RESTORE',
                                                    'TRAINING_PARAMS',
                                                    'LCP',
                                                    'MC_STATES',
                                                    'SHUB_STATES',
                                                    'SHRM_STATES',
                                                    'DEFAULT_ALC_POLICY',
                                                    'ALC_TIMINGS',
                                                    'ALC_POLICY_INDEX',
                                                    'PERF_MODE_ALC_POLICY',
                                                    'PMIC_SETTINGS',
                                                    'MIN_DDR_SHUB_RATIO',
                                                    'MIN_SHUB_CP',
                                                    'ECDT_PRE_DEVICE_INIT',
                                                    'ECDT_POST_DEVICE_INIT',
                                                    'DDRSS',
                                                    'NOC',
                                                    'SHRM',
                                                    'SHRM2',
                                                    'MCCC_MSTR',
                                                    'MCCC_SLV',
                                                    'DDRPHY',
                                                    'MC',
                                                    'LLCC',
                                                    'AHB2PHY',
                                                    'SHRM_DUMP'],
        "DCB_MAX_SIZE":((1024*50)+4),
    }
}

