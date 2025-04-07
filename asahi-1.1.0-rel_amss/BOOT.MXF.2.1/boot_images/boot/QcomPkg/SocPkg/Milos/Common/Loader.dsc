#==============================================================================
# @file Loader.dsc
# Milos Loader package.
#
# Copyright (c) 2019-2023, 2024 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#==============================================================================

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = MilosPkg
  PLATFORM_GUID                  = AA99686E-4D75-3829-5220-F4874BA2F216
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  SUPPORTED_ARCHITECTURES        = ARM|AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT

  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Milos$(VAR)/Loader

  SECLIB_ENABLED                 = TRUE

!include QcomPkg/SocPkg/Milos/Common/TargetCommon.dsc.inc

[BuildOptions]
   GCC:*_*_*_CC_FLAGS = -I$(WORKSPACE)/QcomPkg/Milos/Include/xbl_sc_cust.h
################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
  QcomPkg/XBLLoader/XBLLoader.inf {
    <LibraryClasses>
     ArmLib|ArmPkg/Library/ArmLib/ArmBaseLib.inf
     BlockDevLib|QcomPkg/XBLLoader/BlockDev/BlockDev.inf

     ChipInfoImageLib|QcomPkg/Library/ChipInfoLib/ChipInfoLoader.inf
     ChipInfoXblConfigLib|QcomPkg/Library/ChipInfoLib/ChipInfoXblConfigLib.inf
     CPUCPInitLib|QcomPkg/SocPkg/Library/CPUCPInitLib/CPUCPInitLib.inf

     # EUD Libraries
     EUDLoaderLib|QcomPkg/Library/EudLib/EUDLoaderLib.inf
     #EUDTargetLib|QcomPkg/SocPkg/Milos/Library/EUDTargetLib/EUDTargetLib.inf
	 EUDTargetLib|QcomPkg/SocPkg/Library/EUDTargetLib/EUDTargetLib.inf

     BootUtilLib|QcomPkg/XBLLoader/BootUtil/BootUtil.inf
     BootMemMapLib|QcomPkg/SocPkg/Library/BootMemMapLib/BootMemMapLib.inf
     CpuInitLib|QcomPkg/SocPkg/Library/CpuInitLib/EL3CpuInitLib.inf
     CPUInfoLib|QcomPkg/Library/CPUInfoLib/CPUInfoLib.inf

     
     TLMMTargetLib|QcomPkg/SocPkg/Milos/Library/TLMMTargetLib/TLMMTargetLib.inf
     OEMInfoLib|QcomPkg/Library/OEMInfoLib/OEMInfoLib.inf 

     ConfigContextLib|QcomPkg/LoaderFramework/ConfigContext/ConfigContext.inf
     ProcessConfigLib|QcomPkg/LoaderFramework/ProcessConfig/ProcessConfig.inf
     DevPrgDLib|QcomPkg/Library/NullLibs/DevPrgDLibNull/DevPrgDLibNull.inf
     DevPrgLLib|QcomPkg/Library/NullLibs/DevPrgLLibNull/DevPrgLLibNull.inf
     ElfLoaderLib|QcomPkg/LoaderFramework/ElfLoader/ElfLoader.inf
     ExtDriversSecureLib|QcomPkg/XBLLoader/ExtDrivers/ExtDriversSecure.inf
     ErrorHandlerLib|QcomPkg/Library/ErrorHandlerLib/ErrorHandlerEl3Lib.inf
     HashLib|QcomPkg/Library/NullLibs/HashLibNull/HashLibSwNull.inf
     HobLib|EmbeddedPkg/Library/PrePiHobLib/PrePiHobLib.inf
     BootheapLib|QcomPkg/Library/HeapLib/bootheap.inf
     LoaderAptLib|QcomPkg/Library/NullLibs/LoaderAptLibNull/LoaderAptLibNull.inf
     LoaderInterfaceLib|QcomPkg/LoaderFramework/BootLoaderInterface/LoaderInterface.inf
     LoggerLib|QcomPkg/LoaderFramework/Logger/Logger.inf
     LoggerMhiLib|QcomPkg/XBLLoader/LoggerMhi/LoggerMhi.inf
     LoggerUartLib|QcomPkg/XBLLoader/LoggerUart/LoggerUart.inf
	   MbnLoaderLib|QcomPkg/LoaderFramework/MbnLoader/MBNloader.inf
     MediaInterfaceLib|QcomPkg/XBLLoader/MediaInterface/MediaInterface.inf
     MemoryMgrLib|QcomPkg/XBLLoader/MemoryMgr/MemoryMgr.inf
     PCIeInitLib|QcomPkg/SocPkg/Library/PCIeInitLib/PCIeInitLib.inf

     #PmicPsiLib|QcomPkg/SocPkg/Milos/Library/PmicLib/loader/PmicPsiLib.inf
     #PmicLib|QcomPkg/SocPkg/Milos/Library/PmicLib/PmicLib.inf
     #PmicLoaderLib|QcomPkg/SocPkg/Milos/Library/PmicLib/loader/PmicLoaderLib.inf
     PmicLib|QcomPkg/Library/NullLibs/PmicLibNull/PmicLibNull.inf
     PmicLoaderLib|QcomPkg/Library/NullLibs/PmicLibNull/PmicLoaderLibNull.inf

     PrePiHobListPointerLib|QcomPkg/Library/PrePiHobListPointerLib/PrePiHobListPointerLib.inf
     ProcLib|QcomPkg/Library/ProcLib/ProcLib.inf
     QcomBaseLib|QcomPkg/Library/QcomBaseLib/QcomBaseLib.inf
     QusbLdrLib|QcomPkg/SocPkg/Milos/Library/QusbLdrLib/QusbLdrLib.inf
     #QusbLdrLib|QcomPkg/Library/NullLibs/QusbLdrLibNull/QusbLdrLibNull.inf
     UsbSharedLib|QcomPkg/SocPkg/Milos/Library/UsbSharedLib/UsbSharedLibLoader.inf
     #UsbSharedLib|QcomPkg/Library/NullLibs/UsbSharedLibNull/UsbSharedLibLoaderNull.inf
     SdccCommonLib|QcomPkg/Library/NullLibs/SdccLibNull/SdccCommonLibNull.inf
     SdccTargetLib|QcomPkg/Library/NullLibs/SdccLibNull/SdccTargetLibNull.inf
     SdccClockLib|QcomPkg/Library/NullLibs/SdccLibNull/SdccLoaderClockLibNull.inf
     VSenseTargetLib|QcomPkg/Library/NullLibs/VSenseTargetLibNull/VSenseTargetLibNull.inf
     TimerLib|QcomPkg/LoaderFramework/Timer/Timer.inf
     StorageProfileLib|QcomPkg/Library/StorageCommonLib/StorageProfile.inf
     StorageBootCommonLib|QcomPkg/Library/StorageCommonLib/StorageLoaderCommon.inf
     WhitelistLib|QcomPkg/XBLLoader/WhitelistLib/WhitelistLib.inf
     BootModeInterfaceLib|QcomPkg/XBLLoader/BootModeInterface/BootModeInterface.inf
     BootExitLib|QcomPkg/XBLLoader/BootExitLib/BootExitLib.inf
     BlacklistLib|QcomPkg/XBLLoader/BlacklistLib/BlacklistLib.inf
     MinidumpLib|QcomPkg/Library/MinidumpLib/MinidumpLibLoader.inf
     CdtLib|QcomPkg/XBLLoader/CdtLib/CdtLib.inf
     BootSmemLib|QcomPkg/XBLLoader/BootSmem/BootSmem.inf
     RamInit|QcomPkg/XBLLoader/RamInit/RamInit.inf
     RamPartitionLib|QcomPkg/XBLLoader/RamPartition/RamPartition.inf
     DloadDumpLib|QcomPkg/XBLLoader/DloadDump/DloadDump.inf
     VectorTable|QcomPkg/SocPkg/Library/VectorTable/VectorTableEL3.inf
     XBLLoaderLib|QcomPkg/SocPkg/Library/XBLLoaderLib/XBLLoaderLib_SM.inf
     XBLLoaderArchLib|QcomPkg/SocPkg/Library/XBLLoaderArchLib/XBLLoaderArchSecureLib.inf

     #XcfgLoaderElf|QcomPkg/XBLLoader/XBLConfig/XcfgLoaderElfLib.inf
     XBLTestModeLib|QcomPkg/SocPkg/Library/XBLTestModeLib/XBLTestModeLib.inf
     WatchDogTimerLib|QcomPkg/SocPkg/Library/WatchDogTimerLib/WatchDogTimerLib.inf
     BootCrashdump|QcomPkg/XBLLoader/BootCrashdump/BootCrashdump.inf
     DDITargetLib|QcomPkg/SocPkg/Milos/Library/DDITargetLib/DDITargetLib.inf
     #DDITargetLib|QcomPkg/Library/NullLibs/DDITargetLibNull/DDITargetLibNull.inf
     
     SecLib|SecPkg/Library/SecLib/SecLib.inf
     SecTargetLib|SecPkg/Library/SecTargetLib/chipsets/Milos/SecTargetLib.inf
     DbgInfoLib|SecPkg/Library/dbginfolib/build/DbgInfoLib.inf
     ACLib|SecPkg/Library/ACLib/ACLib.inf
     ACConfigDataLib|SecPkg/Library/ACConfigDataLib/milos/ACConfigDataLib.inf
     UCLib|SecPkg/Library/UCLib_loader/UCLib_loader.inf
     # TSENS Libraries
     TsensLoaderLib|QcomPkg/Library/TsensLib/TsensLoaderLib.inf
     #TsensLoaderLib|QcomPkg/Library/NullLibs/TsensLoaderLibNull/TsensLoaderLibNull.inf
     BootTempCheckLib|QcomPkg/Library/BootTempCheckLib/BootTempCheckLib.inf
     SmemImageLib|QcomPkg/SocPkg/Milos/Library/SmemImageLib/SmemImageLib.inf
     #SmemImageLib|QcomPkg/Library/NullLibs/SmemImageLibNull/SmemImageLibNull.inf
     SmemLib|QcomPkg/Library/SmemLib/SmemLibXBLLoader.inf
     TmeCom|TmePkg/Library/TmeCom/TmeCom.inf
     LogsToMediaLib|QcomPkg/XBLLoader/LogsToMediaLib/LogsToMediaLib.inf

     BootHwLib|QcomPkg/SocPkg/Library/BootHwLib/BootHwSMLib.inf
      #This PCD values should match with the ones defined in boot_sbl_shared.h for sbl_build_type.
      <PcdsFixedAtBuild>
        gQcomTokenSpaceGuid.PcdBuildType|0x0
        gQcomTokenSpaceGuid.SDCCDmaEnabled|TRUE
        gQcomTokenSpaceGuid.SDCCSdhciEnable|TRUE
        gQcomTokenSpaceGuid.SDCCEmmcSpeedMode|0
  }
