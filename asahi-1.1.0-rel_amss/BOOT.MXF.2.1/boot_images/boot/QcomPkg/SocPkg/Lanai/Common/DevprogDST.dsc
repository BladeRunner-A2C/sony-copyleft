#==============================================================================
# @file DevprogDST.dsc
# Lanai Device Programmer
#
# Copyright 2023 Sony Corporation.
# All rights, including trade secret rights, reserved.
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

  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Lanai$(VAR)/DevprogDST

!include QcomPkg/SocPkg/Lanai/Common/TargetCommon.dsc.inc
[BuildOptions]
   GCC:*_*_*_CC_FLAGS = -DBOOT_RAMDUMP_ENABLE
################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
  QcomPkg/DevPrg/DevPrgDST.inf {
     <LibraryClasses>
      BootMemMapLib|QcomPkg/SocPkg/Library/BootMemMapLib/RamdumpMemMapLib.inf
      XBLLoaderArchLib|QcomPkg/SocPkg/Library/XBLLoaderArchLib/XBLLoaderArchNonSecureLib.inf
      ChipInfoImageLib|QcomPkg/Library/ChipInfoLib/ChipInfoLoader.inf
      ConfigContextLib|QcomPkg/LoaderFramework/ConfigContext/ConfigContext.inf
      ProcLib|QcomPkg/Library/ProcLib/ProcLib.inf
      ExtDriversNonSecureLib|QcomPkg/XBLLoader/ExtDrivers/ExtDriversNonSecure.inf
      LoggerLib|QcomPkg/LoaderFramework/Logger/Logger.inf
	    NandCommonLib|QcomPkg/Library/NullLibs/NandLibNull/NandLibNull.inf
	    NandHalLib|QcomPkg/Library/NullLibs/NandLibNull/NandLibNull.inf
	    QpicLib|QcomPkg/Library/NullLibs/QpicLibNull/QpicLibLoader.inf
      PCIeInitLib|QcomPkg/SocPkg/Library/PCIeInitLib/PCIeInitLib.inf
      PmicLib|QcomPkg/SocPkg/Lanai/Library/PmicLib/PmicLib.inf
      PmicLoaderLib|QcomPkg/SocPkg/Lanai/Library/PmicLib/loader/PmicLoaderNoChgrLib.inf
      QusbLdrLib|QcomPkg/SocPkg/Lanai/Library/QusbLdrLib/QusbLdrLib.inf
      #QusbLdrLib|QcomPkg/Library/NullLibs/QusbLdrLibNull/QusbLdrLibNull.inf
      UsbSharedLib|QcomPkg/SocPkg/Lanai/Library/UsbSharedLib/UsbSharedLibLoader.inf
      #UsbSharedLib|QcomPkg/Library/NullLibs/UsbSharedLibNull/UsbSharedLibLoaderNull.inf

      HashLib|QcomPkg/Library/HashLib_loader/HashLibHw_loader.inf
      UCLib|SecPkg/Library/UCLib_devprog/UCLib_devprog.inf
      CryptoLib|QcomPkg/Library/CryptoLib/CryptoLib.inf
      RamdumpheapLib|QcomPkg/Library/HeapLib/ramdumpheap.inf
      ErrorHandlerLib|QcomPkg/Library/ErrorHandlerLib/ErrorHandlerEl1Lib.inf
      CpuInitLib|QcomPkg/SocPkg/Library/CpuInitLib/EL1CpuInitLib.inf
      VectorTable|QcomPkg/SocPkg/Library/VectorTable/VectorTableEL1.inf
      LoggerUartLib|QcomPkg/XBLLoader/LoggerUart/LoggerUart.inf
      MhiDevProgDeviceLib|QcomPkg/Library/NullLibs/MHILibNull/MhiDevProgDeviceLibNull.inf
      DevPrgLib|QcomPkg/Library/DevPrgLib/DevPrgDSTLib.inf
      DevPrgBuffersLib|QcomPkg/Library/DevPrgLib/DevPrgBuffersDDRLib.inf
      RamInit|QcomPkg/XBLLoader/RamInit/RamInit.inf

      <PcdsFixedAtBuild>
        gQcomTokenSpaceGuid.SDCCDmaEnabled|TRUE
        gQcomTokenSpaceGuid.SDCCSdhciEnable|TRUE
        # SDCCEmmcSpeedMode = 3 to indicate HS mode for SD card
        gQcomTokenSpaceGuid.SDCCEmmcSpeedMode|3
   }

[BuildOptions]
  GCC:*_*_AARCH64_ARCHCC_FLAGS  = -DFEATURE_DEVICEPROGRAMMER_IMAGE
  GCC:*_*_AARCH64_ARCHPP_FLAGS  = -DFEATURE_DEVICEPROGRAMMER_IMAGE

