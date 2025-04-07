@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2020 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/dev/aop.ho/5.0/kparsha.aop.ho.5.0.aop50_0degc/aop_proc/build/build_camano_devcfg.bat#1 $

SET BUILD_ASIC=palawan
SET MSM_ID=palawan
SET HAL_PLATFORM=palawan
SET TARGET_FAMILY=palawan
SET CHIPSET=palawan
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
SET GENERATE_DEVCFG_MBN_ONLY=true

SET LLVM_VERSION=11.0.4
SET CLANG_VERSION=11.0.4
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common_riscv.py %*
