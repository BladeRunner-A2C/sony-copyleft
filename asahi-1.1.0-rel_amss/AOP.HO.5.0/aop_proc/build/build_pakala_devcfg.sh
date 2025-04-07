# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2022 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/kparsha.aop.ho.5.0.aop50_0degc/aop_proc/build/build_lanai_devcfg.sh#1 $

export BUILD_ASIC=pakala
export MSM_ID=pakala
export HAL_PLATFORM=pakala
export TARGET_FAMILY=pakala
export CHIPSET=pakala
export CHIPSET_PMIC=pakala
export CHIPSET_SVE=NA
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export GENERATE_DEVCFG_MBN_ONLY=true

export LLVM_VERSION=17.0.0

CLANG=/pkg/qct/software/llvm/release/riscv/17.0.0/ubuntu/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@
