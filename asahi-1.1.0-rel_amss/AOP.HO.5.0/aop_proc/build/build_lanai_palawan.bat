@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2021 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/dev/aop.ho/5.0/avadrav.aop.ho.5.0.palawan_tip_10_16_rumi_flags/aop_proc/build/build_lanai.bat#1 $

SET BUILD_ASIC=lanai
SET MSM_ID=lanai
SET HAL_PLATFORM=lanai
SET TARGET_FAMILY=lanai
SET CHIPSET=lanai
SET CHIPSET_SVE=lanai_sve_needs
SET SPF_RISCV=true
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

SET LLVM_VERSION=11.0.4
SET CLANG_VERSION=11.0.4
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common_riscv.py %*

SET BUILD_ASIC=lanai
SET MSM_ID=lanai
SET HAL_PLATFORM=lanai
SET TARGET_FAMILY=lanai
SET CHIPSET=lanai
SET CHIPSET_SVE=NA
SET SPF_RISCV=true
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

SET LLVM_VERSION=11.0.4
SET CLANG_VERSION=11.0.4
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common_riscv.py %*

SET BUILD_ASIC=palawan
SET MSM_ID=palawan
SET HAL_PLATFORM=palawan
SET TARGET_FAMILY=palawan
SET CHIPSET=palawan
SET CHIPSET_SVE=palawan_sve_needs
SET SPF_RISCV=true
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

SET LLVM_VERSION=11.0.4
SET CLANG_VERSION=11.0.4
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common_riscv.py %*

SET BUILD_ASIC=palawan
SET MSM_ID=palawan
SET HAL_PLATFORM=palawan
SET TARGET_FAMILY=palawan
SET CHIPSET=palawan
SET CHIPSET_SVE=NA
SET SPF_RISCV=true
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

SET LLVM_VERSION=11.0.4
SET CLANG_VERSION=11.0.4
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\riscv32-unknown-elf\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common_riscv.py %*