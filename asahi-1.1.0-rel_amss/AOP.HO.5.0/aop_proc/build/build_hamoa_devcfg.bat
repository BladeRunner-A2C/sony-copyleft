@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2020 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header $

SET BUILD_ASIC=hamoa
SET MSM_ID=hamoa
SET HAL_PLATFORM=hamoa
SET TARGET_FAMILY=hamoa
SET CHIPSET=hamoa
SET CHIPSET_PMIC=hamoa
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
SET GENERATE_DEVCFG_MBN_ONLY=true

SET LLVM_VERSION=14.0.0
SET CLANG_VERSION=14.0.0
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*
