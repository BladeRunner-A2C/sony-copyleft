#/** @file ThirdPartyPkg.dsc
# ThirdParty Drivers package.
#
# Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.
# This program and the accompanying materials
# are licensed and made available under the terms and conditions of the BSD License
# which accompanies this distribution.  The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
#**/
#
#==============================================================================

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = ThirdPartyPkg
  PLATFORM_GUID                  = A8E92D05-01D5-4EE5-A6Ed-374B89F7F447
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = QcomPkg/ThirdPartyPkg/ThirdPartyPkg.fdf

[Defines.AARCH64]
  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/ThirdParty

[LibraryClasses.common]
  
[LibraryClasses.common.UEFI_APPLICATION]


[LibraryClasses.AARCH64]

[BuildOptions.AARCH64]
  GCC:*_*_*_ARCHCC_FLAGS  == -fno-common -mtune=cortex-a53 -include $(WORKSPACE)/QcomPkg/Include/Library/DebugLib.h -DQCOM_EDK2_PATCH
  GCC:*_*_*_ARCHPP_FLAGS  == -include $(WORKSPACE)/QcomPkg/Include/Library/DebugLib.h -DQCOM_EDK2_PATCH
  
!if $(PRODMODE) == "PRODMODE"
  RVCT:*_*_*_CC_FLAGS = -DPRODMODE
  GCC:*_*_*_CC_FLAGS = -DPRODMODE
!endif


################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
  #
  # Thirdparty Drivers
  #
  QcomPkg/ThirdPartyPkg/HelloWorld/HelloWorld.inf