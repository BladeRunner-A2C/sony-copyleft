# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020,2023 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/build/build_kapiti.sh#1 $

export BUILD_ASIC=kapiti
export MSM_ID=kapiti
export HAL_PLATFORM=kapiti
export TARGET_FAMILY=kapiti
export CHIPSET=kapiti
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=14.0.0

CLANG=/pkg/qct/software/llvm/release/arm/14.0.0/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python3 ./build_common.py $@

