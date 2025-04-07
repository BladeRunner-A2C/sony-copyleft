# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2022 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/kparsha.aop.ho.5.0.aop50_0degc/aop_proc/build/build_milos_devcfg.sh#1 $

export BUILD_ASIC=milos
export MSM_ID=milos
export HAL_PLATFORM=milos
export TARGET_FAMILY=milos
export CHIPSET=milos
export CHIPSET_PMIC=milos
export CHIPSET_SVE=NA
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export GENERATE_DEVCFG_MBN_ONLY=true

export LLVM_VERSION=11.0.4

CLANG=/pkg/qct/software/llvm/release/riscv/11.0.4/ubuntu/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@
