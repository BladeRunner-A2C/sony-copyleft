# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header $

export BUILD_ASIC=hamoa
export MSM_ID=hamoa
export HAL_PLATFORM=hamoa
export TARGET_FAMILY=hamoa
export CHIPSET=hamoa
export CHIPSET_PMIC=hamoa
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export GENERATE_DEVCFG_MBN_ONLY=true

export LLVM_VERSION=14.0.0

CLANG=/pkg/qct/software/llvm/release/arm/14.0.0/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common.py $@

