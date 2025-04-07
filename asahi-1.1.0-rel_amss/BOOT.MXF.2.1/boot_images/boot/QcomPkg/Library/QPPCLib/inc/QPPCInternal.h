/*===========================================================================
                              <QPPC.c>
DESCRIPTION
  This file is header for QPPC structures as per ACPI CPPC

INITIALIZATION AND SEQUENCING REQUIREMENTS

  Copyright (c) 2022 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
  Qualcomm Confidential and Proprietary

===========================================================================*/

/*===========================================================================
                             Edit History

when       who             what, where, why
--------   ---             -------------------------------------------------
12/06/22   arajashe        Initial version
===========================================================================*/

#ifndef QPPC_INTERNAL_H_
#define QPPC_INTERNAL_H_

#pragma pack(push, 1)

#define QPPC_MAX_CORES              12
#define QPPC_MAX_PERF_LEVELS        16

/*
 * 14.2.1. Generic Communications Channel Command Field
 */
#define QPPC_PCC_READ_COMMAND      0
#define QPPC_PCC_WRITE_COMMAND     1

/* 
 * 14.2.2. Generic Communications Channel Status Field
 */
#define QPPC_PCC_CH_READY          1

typedef struct _QPPC_ExtensionType {
	uint32_t                      nPerfLevels;
	uint64_t                      nPerfFrequency[QPPC_MAX_PERF_LEVELS];
	uint32_t                      nLimitReason;
}QPPC_ExtensionType;

/*
 * 8.4.7.1. _CPC (Continuous Performance Control)
 */
typedef struct _QPPC_RegSpaceType {
	uint32_t                      nHighestPerformance;
	uint32_t                      nNominalPerformance;
	uint32_t                      nLowestNonlinearPerformance;
	uint32_t                      nLowestPerformance;
	uint32_t                      nGuaranteedPerformance; /* not used by MS? */
	uint32_t                      nDesiredPerformance;
	uint32_t                      nMinimumPerformance;
	uint32_t                      nMaximumPeformance;
	uint32_t                      nPerformanceReductionTolerance;
	uint32_t                      nTimeWindow;
	uint32_t                      nCounterWraparoundTime;
	uint64_t                      nReferencePerformanceCounter;
	uint64_t                      nDeliveredPerformanceCounter;
	uint32_t                      nPerformanceLimited;
	uint32_t                      nCppcEnable; /* use as qppc enable? */
	uint32_t                      nAutonomousSelectionEnable;
	uint32_t                      nAutonomousActivityWindow;
	uint32_t                      nEnergyPerformancePreference;
	uint32_t                      nReferencePerformance;
	uint32_t                      nLowestFrequency;
	uint32_t                      nNominalFrequency;
	QPPC_ExtensionType            QPPCExt;
}QPPC_RegSpaceType;

/*
 * 14.2. Generic Communications Channel Shared Memory Region
 */
 
typedef struct _QPPC_GCCSharedMemoryType {
	uint32_t                      nSignature; /* 0x50434300 | (subspace ID) */
	uint16_t                      nCommand;  /* 14.2.1. Generic Communications Channel Command Field */
	uint16_t                      nStatus;  /* 14.2.2. Generic Communications Channel Status Field */
	QPPC_RegSpaceType             QPPCReg; /* Communication space */
}QPPC_GCCSharedMemoryType;

typedef struct _GASType {
	uint8_t                       nAddressSpaceId; /* 0 = system memory */
	uint8_t                       nRegisterBitWidth; /* 64 */
	uint8_t                       nRegisterBitOffset; /* mailbox command register ID */
	uint8_t                       nAccessSize;
	uint64_t                      nAddress; /* mailbox base address */
}GASType;

/*
 * 14.1.4. HW-Reduced Communications Subspace Structure (type 1)
 */
typedef struct _QPPC_HWCommSubSpaceType {
	uint8_t                       nType; /* 1 = HW-reduced type 1 */
	uint8_t                       nLength; /* 62 */
	uint32_t                      nPlatformInterrupt;
	uint8_t                       nPlatformInterruptFlags;
	uint8_t                       reserved;
	uint64_t                      pSharedMemBase; /* pointer to generic_communications_channel_shared_memory */
	uint64_t                      nSharedMemLength; /* sizeof generic_communications_channel_shared_memory */
	GASType                         DoorbellRegister;
	uint64_t                      nDoorbellPreserve;
	uint64_t                      nDoorbellWrite;
	uint32_t                      nNominalLatency;
	uint32_t                      nMaxPeriodicRate;
	uint16_t                      nMinTurnaroundTime;
}QPPC_HWCommSubSpaceType;

/*
 & 14.1. Platform Communications Channel Table
 */
typedef struct _QPPC_PCCTType {
	uint32_t                      nSignature; /* 'PCCT' */
	uint32_t                      nLength;
	uint8_t                       nRevision; /* 2 */
	uint8_t                       nChecksum;
	uint8_t                       nOEMId[6];
	uint8_t                       nOEMTableId[8];
	uint32_t                      nOEMRevision;
	uint32_t                      nCreatorId;
	uint32_t                      nCreatorRevision;
	uint32_t                      nFlags; /* 1 = use interrupt to signal completion */
	uint8_t                       reserved[8];
	QPPC_HWCommSubSpaceType HWSubspace[QPPC_MAX_CORES];
}QPPC_PCCTType;

#pragma pack(pop)

#endif /* QPPC_INTERNAL_H_*/
