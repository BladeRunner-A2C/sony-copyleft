# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2021,2023 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/kuam.aop.ho.5.0.milos_bsp1/aop_proc/build/build_milos.sh#1 $

export BUILD_ASIC=milos
export MSM_ID=milos
export HAL_PLATFORM=milos
export TARGET_FAMILY=milos
export CHIPSET=milos
export CHIPSET_SVE=milos_sve_needs
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=11.0.4

CLANG=/pkg/qct/software/llvm/release/riscv/11.0.4/ubuntu/bin/clang
#CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@


export BUILD_ASIC=milos
export MSM_ID=milos
export HAL_PLATFORM=milos
export TARGET_FAMILY=milos
export CHIPSET=milos
export CHIPSET_SVE=NA
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=11.0.4

CLANG=/pkg/qct/software/llvm/release/riscv/11.0.4/ubuntu/bin/clang
#CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@
