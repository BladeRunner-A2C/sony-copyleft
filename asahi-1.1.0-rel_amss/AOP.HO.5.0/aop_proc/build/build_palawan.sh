# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2021,2023 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/avadrav.aop.ho.5.0.palawan_buildinfra_new/aop_proc/build/build_palawan.sh#1 $

export BUILD_ASIC=palawan
export MSM_ID=palawan
export HAL_PLATFORM=palawan
export TARGET_FAMILY=palawan
export CHIPSET=palawan
export CHIPSET_SVE=palawan_sve_needs
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=11.0.4

CLANG=/pkg/qct/software/llvm/release/riscv/11.0.4/ubuntu/bin/clang
#CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@


export BUILD_ASIC=palawan
export MSM_ID=palawan
export HAL_PLATFORM=palawan
export TARGET_FAMILY=palawan
export CHIPSET=palawan
export CHIPSET_SVE=NA
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=11.0.4

CLANG=/pkg/qct/software/llvm/release/riscv/11.0.4/ubuntu/bin/clang
#CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@
