#==============================================================================
# @file TargetCommon.dsc.inc
# Milos Loader images common libraries.
#
# Copyright (c) 2017 - 2023, 2024 Qualcomm Technologies, Inc. All rights reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc
# Portions Copyright (c) 2009 - 2010, Apple Inc. All rights reserved.
# This program and the accompanying materials
# are licensed and made available under the terms and conditions of the BSD License
# which accompanies this distribution.  The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#==============================================================================


!include QcomPkg/SocPkg/Common/Common.dsc.inc
!include QcomPkg/SocPkg/Milos/$(VAR)/Variant.dsc.inc
[LibraryClasses.common]
  BamSettingsLib|QcomPkg/Library/NullLibs/BamTargetLibNull/BamTargetLibNull.inf
  MemoryAllocationLib|QcomPkg/Library/LdrAllocPg/LdrAllocPg.inf
  UartSettingsLib|QcomPkg/SocPkg/Milos/Settings/UART/UartSettingsLib.inf
  
  DALGenLibLoader|QcomPkg/SocPkg/Milos/Settings/DALConfig/DALGenLibLoader_LA.inf
  DALConfigLoaderLib|QcomPkg/SocPkg/Milos/Settings/DALConfig/DALConfigLoaderLib_LA.inf
  
  DTBExtnLib|QcomPkg/Library/DTBExtnLib/DTBExtnLib.inf
  DTBLoaderLib|QcomPkg/XBLLoader/DTBLoaderLib/DTBLoaderLib.inf
  
  SpiNorCommonLib|QcomPkg/Library/NullLibs/SpiNorCommonLibNull/SpiNorCommonNullLib.inf
  UfsTargetBootLib|QcomPkg/SocPkg/Milos/Library/UfsTargetLib/UfsTargetBootLib.inf
  UfsTargetJtagLib|QcomPkg/SocPkg/Milos/Library/UfsTargetLib/UfsTargetJtagLib.inf
  IcbCfgLib|QcomPkg/Library/ICBLib/ICBLib.inf
  
  #PlatformInfoTargetLib|QcomPkg/SocPkg/Milos/Library/PlatformInfoTargetLib/PlatformInfoTargetLib.inf
  #ChipInfoTargetLib|QcomPkg/SocPkg/Milos/Library/ChipInfoTargetLib/ChipInfoTargetLib.inf
  ChipInfoXblConfigLib|QcomPkg/Library/NullLibs/ChipInfoXblConfigLibNull/ChipInfoXblConfigLibNull.inf

  ChipInfoTargetLib|QcomPkg/Library/NullLibs/ChipInfoTargetLibNull/ChipInfoTargetLibNull.inf
  OEMInfoLib|QcomPkg/Library/NullLibs/OEMInfoLibNull/OEMInfoLibNull.inf 
  TLMMTargetLib|QcomPkg/SocPkg/Milos/Library/TLMMTargetLib/TLMMTargetLib.inf
  
  ClockTargetLib|QcomPkg/SocPkg/Milos/Library/ClockTargetLib/ClockTargetLib.inf
  BootPblSharedDataLib|QcomPkg/SocPkg/Library/BootPblSharedDataLib/boot_pbl_v2/BootPblSharedDataLib.inf
  SmemLib|QcomPkg/Library/SmemLib/SmemLibXBLLoaderCommon.inf

 QusbTargetLib|QcomPkg/SocPkg/Milos/Library/QusbTargetLib/QusbTargetLib.inf
 #QusbTargetLib|QcomPkg/Library/NullLibs/QusbTargetLibNull/QusbTargetLibNull.inf
 QusbDciCommonLib|QcomPkg/SocPkg/Milos/Library/QusbDciCommonLib/QusbDciCommonLib.inf
 #QusbDciCommonLib|QcomPkg/Library/NullLibs/QusbDciCommonLibNull/QusbDciCommonLibNull.inf

 TsensTargetLib|QcomPkg/SocPkg/Milos/Library/TsensTargetLib/TsensTargetLib.inf
 #TsensTargetLib|QcomPkg/Library/NullLibs/TsensTargetLibNull/TsensTargetLibNull.inf


 #ButtonsBootLib|QcomPkg/SocPkg/Milos/Library/ButtonsTargetLib/ButtonsBootLib.inf
 ButtonsBootLib|QcomPkg/Library/NullLibs/ButtonsBootLibNull/ButtonsBootLibNull.inf

 SdccTargetLib|QcomPkg/SocPkg/Milos/Library/SdccTargetLib/SdccLoaderTargetLib.inf
 SdccClockLib|QcomPkg/SocPkg/Milos/Library/SdccClockLib/SdccLoaderClockLib.inf

  #SPMILib|QcomPkg/SocPkg/Milos/Library/SPMILib/SPMILib.inf
  SPMILib|QcomPkg/Library/NullLibs/SPMILibNull/SPMILibNull.inf
  SPMILibDebugNull|QcomPkg/Library/NullLibs/SPMILibNull/SPMILibDebugNull.inf


 #CPRTargetLib|QcomPkg/Library/NullLibs/PowerLibNull/CprLibNull.inf
 CPRTargetLib|QcomPkg/SocPkg/Milos/Library/CPRTargetLib/Loader/CPRTargetLib.inf

 #RailwayTargetLib|QcomPkg/Library/NullLibs/RailwayLibNull/RailwayLibNull.inf
 RailwayTargetLib|QcomPkg/SocPkg/Milos/Library/RailwayTargetLib/RailwayTargetLib.inf

  I2CFWImageLib|QcomPkg/SocPkg/Milos/Settings/I2C/I2CFWImageLib.inf
  SPIFWImageLib|QcomPkg/SocPkg/Milos/Settings/SPI/SPIFWImageLib.inf
  EUDTargetLib|QcomPkg/Library/NullLibs/EudTargetLibNull/EUDTargetLibNull.inf

  RMBLib|QcomPkg/SocPkg/Library/RMBLib/RMBLib.inf
  FdtLib|EmbeddedPkg/Library/FdtLib/FdtLib.inf
  
  MediaInitializationLib|QcomPkg/XBLLoader/MediaInitializationLib/MediaInitialization.inf

[BuildOptions.AARCH64]
  GCC:*_*_AARCH64_ARCHCC_FLAGS  == -Oz -mllvm -inline-threshold-multicaller-size=20 -mtune=cortex-a53 -DMDEPKG_NDEBUG -DQCOM_EDK2_PATCH -DFEATURE_SET_IMEM_SECURE_REG_RD_ONLY $(FEATURE_FLAGS) -I$(WORKSPACE)/QcomPkg/SocPkg/Include -I$(WORKSPACE)/QcomPkg/SocPkg/Milos/Include -include $(WORKSPACE)/QcomPkg/SocPkg/Milos/Include/Target_cust.h -include $(WORKSPACE)/QcomPkg/SocPkg/Milos/Include/pbl_bl_shared_target_specific_enum.h
  GCC:*_*_AARCH64_ARCHPP_FLAGS  == -DMDEPKG_NDEBUG -DQCOM_EDK2_PATCH -DFEATURE_SET_IMEM_SECURE_REG_RD_ONLY $(FEATURE_FLAGS) -I$(WORKSPACE)/QcomPkg/SocPkg/Include -I$(WORKSPACE)/QcomPkg/SocPkg/Milos/Include -include $(WORKSPACE)/QcomPkg/SocPkg/Milos/Include/Target_cust.h -include $(WORKSPACE)/QcomPkg/SocPkg/Milos/Include/pbl_bl_shared_target_specific_enum.h

!if $(PRODMODE) == "PRODMODE"
  GCC:*_*_*_CC_FLAGS = -DPRODMODE
!endif


[PcdsFeatureFlag.common]
[PcdsFixedAtBuild.common]
  gQcomTokenSpaceGuid.PcdQTimerAC_BasePhys|0x17420000      # APSS_QTMR0_QTMR_AC
  gQcomTokenSpaceGuid.PcdQTimerV1BasePhys|0x17421000       # APSS_QTMR0_F0V1_QTMR_V1
  gQcomTokenSpaceGuid.PcdQTimerV2BasePhys|0x17422000       # APSS_QTMR0_F0V2_QTMR_V2
  gQcomTokenSpaceGuid.PcdSmemBaseAddress|0x81D00000        #64-bit smem addr
