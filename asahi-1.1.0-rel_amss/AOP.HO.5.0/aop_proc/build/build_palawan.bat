@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2021 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/dev/aop.ho/5.0/avadrav.aop.ho.5.0.palawan_buildinfra_new/aop_proc/build/build_palawan.bat#1 $

SET BUILD_ASIC=palawan
SET MSM_ID=palawan
SET HAL_PLATFORM=palawan
SET TARGET_FAMILY=palawan
SET CHIPSET=palawan
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

SET LLVM_VERSION=11.0.4
SET CLANG_VERSION=11.0.4
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common_riscv.py %*

