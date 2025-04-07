# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2021,2023 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/kparsha.aop.ho.5.0.aop50_pakala_base/aop_proc/build/build_pakala.sh#1 $

export BUILD_ASIC=pakala
export MSM_ID=pakala
export HAL_PLATFORM=pakala
export TARGET_FAMILY=pakala
export CHIPSET=pakala
export CHIPSET_SVE=pakala_sve_needs
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=17.0.0

CLANG=/pkg/qct/software/llvm/release/riscv/17.0.0/ubuntu/bin/clang
#CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@


export BUILD_ASIC=pakala
export MSM_ID=pakala
export HAL_PLATFORM=pakala
export TARGET_FAMILY=pakala
export CHIPSET=pakala
export CHIPSET_SVE=NA
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=17.0.0

CLANG=/pkg/qct/software/llvm/release/riscv/17.0.0/ubuntu/bin/clang
#CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@
