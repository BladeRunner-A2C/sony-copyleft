# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020,2023 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/kuam.aop.ho.5.0.camano_buil_support_fix/aop_proc/build/build_camano.sh#1 $

export BUILD_ASIC=camano
export MSM_ID=camano
export HAL_PLATFORM=camano
export TARGET_FAMILY=camano
export CHIPSET=camano
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=14.0.0

CLANG=/pkg/qct/software/llvm/release/arm/14.0.0/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common.py $@

