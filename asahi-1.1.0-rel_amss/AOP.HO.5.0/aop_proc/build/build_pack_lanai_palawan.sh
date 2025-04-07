# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020,2023 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/pbamanal.aop.ho.5.0.Pinnacle_Base_Build_01_31_2022/aop_proc/build/build_pinnacle.sh#1 $

export BUILD_ASIC=lanai
export MSM_ID=lanai
export HAL_PLATFORM=lanai
export TARGET_FAMILY=lanai
export CHIPSET=lanai
export CHIPSET_SVE=lanai_sve_needs
export SPF_RISCV=true
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=11.0.4

CLANG=/pkg/qct/software/llvm/release/riscv/11.0.4/ubuntu/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@


export BUILD_ASIC=lanai
export MSM_ID=lanai
export HAL_PLATFORM=lanai
export TARGET_FAMILY=lanai
export CHIPSET=lanai
export CHIPSET_SVE=NA
export SPF_RISCV=true
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=11.0.4

CLANG=/pkg/qct/software/llvm/release/riscv/11.0.4/ubuntu/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@

export BUILD_ASIC=palawan
export MSM_ID=palawan
export HAL_PLATFORM=palawan
export TARGET_FAMILY=palawan
export CHIPSET=palawan
export CHIPSET_SVE=palawan_sve_needs
export SPF_RISCV=true
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=11.0.4

CLANG=/pkg/qct/software/llvm/release/riscv/11.0.4/ubuntu/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@


export BUILD_ASIC=palawan
export MSM_ID=palawan
export HAL_PLATFORM=palawan
export TARGET_FAMILY=palawan
export CHIPSET=palawan
export CHIPSET_SVE=NA
export SPF_RISCV=true
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=11.0.4

CLANG=/pkg/qct/software/llvm/release/riscv/11.0.4/ubuntu/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common_riscv.py $@

cd ../../ #To change working directory to base

mkdir HY11_1

cp -rf aop_proc HY11_1/

./aop_proc/build/build_packed_riscv.sh lanai