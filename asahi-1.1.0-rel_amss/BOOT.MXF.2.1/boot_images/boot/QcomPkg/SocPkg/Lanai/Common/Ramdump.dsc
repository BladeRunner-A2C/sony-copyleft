#==============================================================================
# @file Loader.dsc
# Lanai Loader package.
#
# Copyright (c) 2017 - 2023 Qualcomm Technologies, Inc. All rights reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#==============================================================================

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = LanaiPkg
  PLATFORM_GUID                  = AA99686E-4D75-3829-5220-F4874BA2F216
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT

  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Lanai$(VAR)/RamDump

!include QcomPkg/SocPkg/Lanai/Common/TargetCommon.dsc.inc
[BuildOptions]
   GCC:*_*_*_CC_FLAGS = -DBOOT_RAMDUMP_ENABLE -DENABLE_LOGS_TO_MEDIA
################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
#
# SEC
#
  QcomPkg/XBLRamDump/XBLRamDump.inf {
    <LibraryClasses>
      BootMemMapLib|QcomPkg/SocPkg/Library/BootMemMapLib/RamdumpMemMapLib.inf
      XBLRamDumpLib|QcomPkg/SocPkg/Library/XBLRamDumpLib/XBLRamDumpLib.inf
      XBLLoaderArchLib|QcomPkg/SocPkg/Library/XBLLoaderArchLib/XBLLoaderArchNonSecureLib.inf
      IpaTargetLib|QcomPkg/Library/NullLibs/IpaTargetLibNull/IpaTargetLibNull.inf
      SdccCommonLib|QcomPkg/Library/SdccCommonLib/SdccCommonRamdumpLib.inf
      ChipInfoImageLib|QcomPkg/Library/ChipInfoLib/ChipInfoRamdump.inf
      ChipInfoSKULib|QcomPkg/Library/NullLibs/ChipInfoSKULibNull/ChipInfoSKULibNull.inf
      ConfigContextLib|QcomPkg/LoaderFramework/ConfigContext/ConfigContext.inf
      ProcLib|QcomPkg/Library/ProcLib/ProcLib.inf
      TlmmLib|QcomPkg/Library/TlmmLib/TlmmLib.inf
      IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
      DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
      ClockTargetLib|QcomPkg/SocPkg/Lanai/Library/ClockTargetLib/ClockRamDumpLib.inf
      WhitelistLib|QcomPkg/XBLLoader/WhitelistLib/WhitelistLib.inf
      WatchDogTimerLib|QcomPkg/SocPkg/Library/WatchDogTimerLib/WatchDogTimerLib.inf

      DisplayLib|QcomPkg/Library/DisplayLib/DisplayLib.inf
      DevPrgDLib|QcomPkg/Library/NullLibs/DevPrgDLibNull/DevPrgDLibNull.inf
      DevPrgLLib|QcomPkg/Library/NullLibs/DevPrgLLibNull/DevPrgLLibNull.inf
      HALDSILib|QcomPkg/Library/HALDSILib/HALDSILib.inf
      HALEDPLib|QcomPkg/Library/HALDPLib/HALDPLibStub.inf
      ExternalDisplayLib|QcomPkg/Library/ExternalDisplayLib/ExternalDisplayLibStub.inf
      ExtDriversNonSecureLib|QcomPkg/XBLLoader/ExtDrivers/ExtDriversNonSecure.inf
      HALMDSSLib|QcomPkg/Library/HALMDSSLib/HALMDSS10xx.inf
      LoggerLib|QcomPkg/LoaderFramework/Logger/Logger.inf
      LoggerMhiLib|QcomPkg/XBLLoader/LoggerMhi/LoggerMhi.inf
      MDPLibBoot|QcomPkg/Library/MDPLib/MDPLibBoot.inf
      MDPPlatformLibBoot|QcomPkg/SocPkg/Lanai/Library/MDPPlatformLibBoot/MDPPlatformLibBoot.inf
      DTBExtnLib|QcomPkg/Library/DTBExtnLib/DTBExtnLib.inf

      PlatformInfoLoaderLib|QcomPkg/Library/PlatformInfoLib/PlatformInfoRamDump.inf


      PmicLib|QcomPkg/SocPkg/Lanai/Library/PmicLib/PmicLib.inf
      PmicLoaderLib|QcomPkg/SocPkg/Lanai/Library/PmicLib/loader/PmicRamDump.inf
      PmicPsiLib|QcomPkg/SocPkg/Lanai/Library/PmicLib/loader/PmicPsiLib.inf

      QusbLdrLib|QcomPkg/SocPkg/Lanai/Library/QusbLdrLib/QusbLdrLib.inf
      #QusbLdrLib|QcomPkg/Library/NullLibs/QusbLdrLibNull/QusbLdrLibNull.inf
      QusbTargetLib|QcomPkg/SocPkg/Lanai/Library/QusbTargetLib/QusbTargetLib.inf
      #QusbTargetLib|QcomPkg/Library/NullLibs/QusbTargetLibNull/QusbTargetLibNull.inf
      QusbDciCommonLib|QcomPkg/SocPkg/Lanai/Library/QusbDciCommonLib/QusbDciCommonLib.inf
      #QusbDciCommonLib|QcomPkg/Library/NullLibs/QusbDciCommonLibNull/QusbDciCommonLibNull.inf

	  UsbSharedLib|QcomPkg/SocPkg/Lanai/Library/UsbSharedLib/UsbSharedLibRamdump.inf
      #UsbSharedLib|QcomPkg/Library/NullLibs/UsbSharedLibNull/UsbSharedLibLoaderNull.inf
	  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
	  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
	  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
	  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
	  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
	  I2CApiLib|QcomPkg/Library/I2CApiLib/I2CApiLib.inf

      RamInit|QcomPkg/XBLLoader/RamInit/RamInit.inf
      UCLib|SecPkg/Library/UCLib_ramdump/UCLib_ramdump.inf
      HashLib|QcomPkg/Library/HashLib_loader/HashLibHw_loader.inf
      RamdumpheapLib|QcomPkg/Library/HeapLib/ramdumpheap.inf
      I2CLib|QcomPkg/Library/I2CLib/I2CLibLoader.inf
      PCIeInitLib|QcomPkg/SocPkg/Library/PCIeInitLib/PCIeInitLib.inf
      HfatDevLib|QcomPkg/XBLLoader/HfatDev/HfatDev.inf
      SaharaDispatchTableLib|QcomPkg/XBLLoader/SaharaDispatchTable/SaharaDispatchTable.inf
      SaharaCommandHandlerLib|QcomPkg/XBLLoader/SaharaCommandHandler/SaharaCommandHandler.inf
      MinidumpLib|QcomPkg/Library/MinidumpLib/MinidumpLibLoader.inf
      RamdumpTableLib|QcomPkg/XBLLoader/RamdumpTable/RamdumpTable.inf
      RamdumpTableTarget|QcomPkg/SocPkg/Library/RamdumpTableTargetLib/RamdumpTableSM.inf
      BlacklistLib|QcomPkg/XBLLoader/BlacklistLib/BlacklistLib.inf

      ErrorHandlerLib|QcomPkg/Library/ErrorHandlerLib/ErrorHandlerEl1Lib.inf
      CpuInitLib|QcomPkg/SocPkg/Library/CpuInitLib/EL1CpuInitLib.inf
      VectorTable|QcomPkg/SocPkg/Library/VectorTable/VectorTableEL1.inf
      LoggerUartLib|QcomPkg/XBLLoader/LoggerUart/LoggerUart.inf
      
      CPRTargetLib|QcomPkg/Library/NullLibs/PowerLibNull/CprLibNull.inf
      RailwayTargetLib|QcomPkg/Library/NullLibs/RailwayLibNull/RailwayLibNull.inf

      <PcdsFixedAtBuild>
        gQcomTokenSpaceGuid.SDCCDmaEnabled|TRUE
        gQcomTokenSpaceGuid.SDCCSdhciEnable|TRUE
        gQcomTokenSpaceGuid.SDCCEmmcSpeedMode|0
  }

