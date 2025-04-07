@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2021 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/dev/aop.ho/5.0/kuam.aop.ho.5.0.milos_bsp1/aop_proc/build/build_milos.bat#1 $

SET BUILD_ASIC=milos
SET MSM_ID=milos
SET HAL_PLATFORM=milos
SET TARGET_FAMILY=milos
SET CHIPSET=milos
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

SET LLVM_VERSION=11.0.4
SET CLANG_VERSION=11.0.4
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common_riscv.py %*

