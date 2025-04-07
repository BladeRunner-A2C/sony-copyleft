#==============================================================================
# @file Variant.dscinc
# Palawan LAA Variant Libraries
#
# Copyright (c) 2017, 2021-2022, 2023 Qualcomm Technologies, Inc. All rights reserved.
# Portions Copyright (c) 2009 - 2010, Apple Inc. All rights reserved.
# This program and the acompanying materials
# are licensed and made available under the terms and conditions of the BSD License
# which accompanies this distribution.  The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#==============================================================================

[BuildOptions]
  GCC:*_*_*_CC_FLAGS = -DBLOCKDEV_ENABLED

[LibraryClasses.common]
 DDRTargetLib|QcomPkg/SocPkg/Palawan/Library/DDRTargetLib/DDRTargetLib.inf
 #DDRTargetLib|QcomPkg/Library/NullLibs/DDRTargetLibNull/DDRTargetLibNull.inf
 DSFTargetLib|QcomPkg/SocPkg/Palawan/Library/DSFTargetLib/DSFTargetLib.inf
 #DDITargetLib|QcomPkg/SocPkg/Palawan/Library/DDITargetLib/DDITargetLib.inf
 DDRSdiLib|QcomPkg/SocPkg/Palawan/Library/DDRTargetLib/DDRSdiLib.inf
 DDRFwLib|QcomPkg/SocPkg/Palawan/Library/DSFTargetLib/DDRFwLib.inf
 DDRFwSdiLib|QcomPkg/SocPkg/Palawan/Library/DSFTargetLib/DDRFwSdiLib.inf
 
