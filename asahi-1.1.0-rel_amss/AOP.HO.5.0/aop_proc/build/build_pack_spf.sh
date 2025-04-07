# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020,2023 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/pbamanal.aop.ho.5.0.Pinnacle_Base_Build_01_31_2022/aop_proc/build/build_pinnacle.sh#1 $

export BUILD_ASIC=kailua
export MSM_ID=kailua
export HAL_PLATFORM=kailua
export TARGET_FAMILY=kailua
export CHIPSET=kailua
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export SPF=true
export LLVM_VERSION=14.0.0

CLANG=/pkg/qct/software/llvm/release/arm/14.0.0/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common.py $@

export BUILD_ASIC=camano
export MSM_ID=camano
export HAL_PLATFORM=camano
export TARGET_FAMILY=camano
export CHIPSET=camano
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export SPF=true
export LLVM_VERSION=14.0.0

CLANG=/pkg/qct/software/llvm/release/arm/14.0.0/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common.py $@

cd ../../
#Copying HY11_1 directory moved from pack file to here
mkdir HY11_1

cp -rf aop_proc HY11_1/

./aop_proc/build/build_packed.sh kailua

