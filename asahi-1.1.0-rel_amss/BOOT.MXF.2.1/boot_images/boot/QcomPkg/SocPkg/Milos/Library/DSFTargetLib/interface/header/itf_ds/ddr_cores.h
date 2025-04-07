#ifndef __DDR_CORES_H__
#define __DDR_CORES_H__

/*******************************************************************************
 QUALCOMM Proprietary Design Data
 Copyright (c) 2014,2018,2022 Qualcomm Technologies Incorporated.
 All rights reserved.
 ******************************************************************************/
/*==============================================================================
                              EDIT HISTORY
$Header: //components/dev/core.boot/6.1/mmohamme.core.boot.6.1.Ln_initialDSF/QcomPkg/SocPkg/Kailua/Library/DSFTargetLib/interface/header/itf_ds/ddr_cores.h#1 $
$DateTime: 2022/03/29 12:10:05 $
$Author: mmohamme $
==============================================================================*/

// Core Version
#define TARGET_CORE_ARCH_SHIFT  24
#define TARGET_CORE_MAJOR_SHIFT 16
#define TARGET_CORE_MINOR_SHIFT 8

#define TARGET_CORE_VER(arch, major, minor, patch) \
( \
    (arch << TARGET_CORE_ARCH_SHIFT) | \
    (major << TARGET_CORE_MAJOR_SHIFT) | \
    (minor << TARGET_CORE_MINOR_SHIFT) | \
    patch \
)


#endif /* __DDR_CORES_H__ */
