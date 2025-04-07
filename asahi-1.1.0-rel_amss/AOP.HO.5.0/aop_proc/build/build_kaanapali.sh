# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2021,2023 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/kparsha.aop.ho.5.0.aop50_kaanapali_base/aop_proc/build/build_kaanapali.sh#1 $

export BUILD_ASIC=kaanapali
export MSM_ID=kaanapali
export HAL_PLATFORM=kaanapali
export TARGET_FAMILY=kaanapali
export CHIPSET=kaanapali
export CHIPSET_SVE=kaanapali_sve_needs
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=17.0.0

CLANG=/pkg/qct/software/llvm/release/riscv/17.0.0/ubuntu/bin/clang
#CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@


export BUILD_ASIC=kaanapali
export MSM_ID=kaanapali
export HAL_PLATFORM=kaanapali
export TARGET_FAMILY=kaanapali
export CHIPSET=kaanapali
export CHIPSET_SVE=NA
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=17.0.0

CLANG=/pkg/qct/software/llvm/release/riscv/17.0.0/ubuntu/bin/clang
#CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@
