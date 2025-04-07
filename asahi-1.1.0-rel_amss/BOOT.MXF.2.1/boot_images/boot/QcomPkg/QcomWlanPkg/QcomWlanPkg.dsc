#/**
#  Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.

# Copyright (c) 2009 - 2011, Intel Corporation. All rights reserved.<BR>
# This program and the accompanying materials
# are licensed and made available under the terms and conditions of the BSD License
# which accompanies this distribution.  The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN ""AS IS"" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

#/*=============================================================================
#                              EDIT HISTORY
#
# 
#
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
# 26/8/21   zxue     support logfs
# 23/7/21   zxue     add missing copyright
# 14/7/21   zxue     branch for core boot
#
#=============================================================================*/
# **/

[Defines]
  PLATFORM_NAME                  = QcomWlanPkg
  PLATFORM_GUID                  = 5caf62ab-1966-4cd5-8cad-8b7404b8ef81
  PLATFORM_VERSION               = 1.0
  DSC_SPECIFICATION              = 0x00010006
  SUPPORTED_ARCHITECTURES        = X64|AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT

[Components.X64]
  QcomWlanPkg/QcaWifiDxe/QcaWifiDxe.inf
  QcomWlanPkg/WlanSupplicantDxe/WlanSupplicantDxe.inf
  QcomWlanPkg/WlanSupplicantDxe/WlanSupplicantLiteDxe.inf
  QcomWlanPkg/Application/QcaWifiMgr/WifiMgr.inf
[Components.AArch64]
  QcomPkg/QcomWlanPkg/QcaWifiDxe/QcaWifiDxe.inf
  #QcomWlanPkg/WlanSupplicantDxe/WlanSupplicantDxe.inf
  QcomPkg/QcomWlanPkg/WlanSupplicantDxe/WlanSupplicantLiteDxe.inf
  QcomPkg/QcomWlanPkg/Application/QcaWifiMgr/WifiMgr.inf

[LibraryClasses]
  #
  # Entry Point Libraries
  #
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  #
  # Common Libraries
  #
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  RegisterFilterLib|MdePkg\Library\RegisterFilterLibNull\RegisterFilterLibNull.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  NetLib|NetworkPkg/Library/DxeNetLib/DxeNetLib.inf
  #
  # Debug Libraries
  #
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
  EfiFileLib|EmbeddedPkg/Library/EfiFileLib/EfiFileLib.inf
  EblNetworkLib|EmbeddedPkg/Library/EblNetworkLib/EblNetworkLib.inf

  #
  # Openssl dependent libraries (FOR WlanSupplicantDxe)
  #
  OpensslLib|CryptoPkg/Library/OpensslLib/OpensslLib.inf
  BaseCryptLib|CryptoPkg/Library/BaseCryptLib/BaseCryptLib.inf
  IntrinsicLib|CryptoPkg/Library/IntrinsicLib/IntrinsicLib.inf
  RngLib|MdePkg/Library/BaseRngLib/BaseRngLib.inf
 
[BuildOptions]
  