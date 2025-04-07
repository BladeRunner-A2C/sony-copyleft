/*============================================================================
  @file  WINACPIUPDATE_H
  @brief AcpiPlatfrom Callback functions for chipinfo 
  Copyright (c) 2015-2016,2018,2020,2022,2023 by Qualcomm Technologies, Inc. All Rights Reserved.         
============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 12/22/22  vbu      Added partial goods support for Hamoa
 06/11/20  rchriste Added partial binning support for MK
 02/27/18  ltg      Added devices for Poipu
 08/4/16   vahidd   Intial Draft for Patching MADT tables.
=============================================================================*/


#ifndef WINACPIUPDATE_H
#define WINACPIUPDATE_H

#include <HALhwio.h>
#include "PlatformInfoHWIO.h"
#include "CoreTopology.h"

/**
Device node information.
*/
#define EFI_DEVICE_GPU "\\_SB.GPU0._STA"
#define EFI_DEVICE_Video "NULL"
#define EFI_DEVICE_Camera "\\_SB.CAMP._STA"
#define EFI_DEVICE_Display "NULL"
#define EFI_DEVICE_Audio "NULL"
#define EFI_DEVICE_Modem "NULL"
#define EFI_DEVICE_WLAN "NULL"
#define EFI_DEVICE_COMP "\\_SB.NSP0._STA"
#define EFI_DEVICE_SENSORS "NULL"
#define EFI_DEVICE_NPU "NULL"
#define EFI_DEVICE_SPSS "NULL"
#define EFI_DEVICE_NAV "NULL"
#define EFI_DEVICE_COMPUTE_1 "NULL"
#define EFI_DEVICE_DISPLAY_1 "NULL"
#define EFI_DEVICE_NSP "NULL"

char * DEVICE_LIST[EFI_WIN_ACPI_PART_MAX] = {
    EFI_DEVICE_GPU,
    EFI_DEVICE_Video,
    EFI_DEVICE_Camera,
    EFI_DEVICE_Display,
    EFI_DEVICE_Audio,
    EFI_DEVICE_Modem,
    EFI_DEVICE_WLAN,
    EFI_DEVICE_COMP,
	EFI_DEVICE_SENSORS,
	EFI_DEVICE_NPU,
	EFI_DEVICE_SPSS,
	EFI_DEVICE_NAV,
	EFI_DEVICE_COMPUTE_1,
	EFI_DEVICE_DISPLAY_1,
	EFI_DEVICE_NSP
};

#define GPU_FUSE_MASK 0x1
#define Video_FUSE_MASK 0x2
#define Camera_FUSE_MASK 0x4
#define Display_FUSE_MASK 0x8
#define Audio_FUSE_MASK 0x10
#define Modem_FUSE_MASK 0x20
#define WLAN_FUSE_MASK 0x40
#define COMP_FUSE_MASK 0x80
#define SENSORS_FUSE_MASK 0x100
#define NPU_FUSE_MASK 0x200
#define SPSS_FUSE_MASK 0x400
#define NAV_FUSE_MASK 0x800
#define COMPUTE_1_FUSE_MASK 0x1000
#define DISPLAY_1_FUSE_MASK 0x2000
#define NSP_FUSE_MASK 0x4000

#define SOC_RUMI_AND_NON_GPU 0x40000001
#define SOC_PLATFORM_AND_GPU_MASK 0x50000003

#define RUMI_NO_GPU_CHECK() ((HWIO_IN(TCSR_SOC_EMULATION_TYPE) & SOC_PLATFORM_AND_GPU_MASK) == SOC_RUMI_AND_NON_GPU)

/**
Global variables
*/
static EFI_ACPI_SDT_PROTOCOL *gAcpiSdt = NULL;
static EFI_CHIPINFO_PROTOCOL *pChipInfoProtocol = NULL;

static UINT32 defectivePartsBitMask = 0x0;
static UINT32 defectivePartsFuseMask = 0x0;

UINT32 CORETOPOLOGY_MAX_CPUS_PER_CLUSTER[CORETOPOLOGY_MAX_NUM_OF_CLUSTERS] = {
	MAX_CPUS_CLS0,
	MAX_CPUS_CLS1,
	MAX_CPUS_CLS2
};

UINT32 CORETOPOLOGY_LOGICAL_CPU_START_IDX[CORETOPOLOGY_MAX_NUM_OF_CLUSTERS] = {
	LOGICAL_START_IDX_CLS0,
	LOGICAL_START_IDX_CLS1,
	LOGICAL_START_IDX_CLS2
};

char *CPU_LIST[] = {
	EFI_DEVICE_CPU1,
	EFI_DEVICE_CPU2,
	EFI_DEVICE_CPU3,
	EFI_DEVICE_CPU0,
	EFI_DEVICE_CPU4,
	EFI_DEVICE_CPU5,
	EFI_DEVICE_CPU6,
	EFI_DEVICE_CPU7,
	EFI_DEVICE_CPU8,
	EFI_DEVICE_CPU9,
	EFI_DEVICE_CPU10,
	EFI_DEVICE_CPU11
};

char * CLUSTER_LIST[CORETOPOLOGY_MAX_NUM_OF_CLUSTERS]  = {
	EFI_DEVICE_CLS0,
	EFI_DEVICE_CLS1,
	EFI_DEVICE_CLS2
};

#endif
