# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020,2023 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/pbamanal.aop.ho.5.0.Pinnacle_Base_Build_01_31_2022/aop_proc/build/build_pinnacle.sh#1 $

export BUILD_ASIC=pinnacle
export MSM_ID=pinnacle
export HAL_PLATFORM=pinnacle
export TARGET_FAMILY=pinnacle
export CHIPSET=pinnacle
export CHIPSET_PMIC=pinnacle
export BIN_FOLDER_NAME=sariska
export SECPOLICY='USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN USES_SEC_POLICY_INTEGRITY_CHECK'
export LLVM_VERSION=14.1.0

CLANG=/pkg/qct/software/llvm/release/arm/14.1.0/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common.py $@
