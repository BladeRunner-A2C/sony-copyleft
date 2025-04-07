#ifndef __TARGET_H__
#define __TARGET_H__
/*
====================================================================================
*/
/**
  @file target.h
  
  Reference chip release:
    SDM8250 (Kona) [kona_v1.0_p3q2r17.8_MTO]
 
  Target specifid defines
*/
/*
  ==================================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Proprietary and Confidential.
  ===========================================================================
  01/17/19    ly   Initial version 
  ===========================================================================
*/
//
// Flag to enable for external releases
//
// #define EXTERNAL_RELEASE

typedef struct key_val{
	uint32_t key;
	uint64_t val;
} key_val;

typedef struct freq_info{
  key_val* freq_table;
  uint32_t freq_table_size;
}freq_info;

freq_info GetSHUBFreqInfo();
freq_info GetDDRFreqInfo();

#define PIMEM_RESERVED_BASE 0x1C1F8000
#define BCM_VOTE_TABLE_ADDR 0xBA20000
#define RPMH_ADDR_OFFSET    0x50000

#define ARC_RM0_CX	"cx.lvl"
#define ARC_RM7_DDRSS	"ddr.lvl"
	
//Note: bcm_vote_table needs AC approval
//For now, without AC approval, instead of querying BCM vote table, just hard-coded proxy votes value

#define DDR_FREQ_ENTRY_NUM 14
#define SHUB_FREQ_ENTRY_NUM 7

//
//AOP msg ram layout
//
#define AOP_SS_MSG_RAM_BASE 		0x0C300000
#define AOP_SS_MSG_RAM_DRV11_BASE 	0x0C3B0000
#define AOP_SS_MSG_RAM_DRV15_BASE 	0x0C3F0000

#define AOP_SS_MSG_RAM_DRV11_SIZE 	1024
#define AOP_SS_MSG_RAM_DRV15_SIZE 	1024

//
//Offset to HW blocks base
//

//This is register to read back SHUB perf level
#define GCC_RPMH_SHUB_CMD_DFSR_OFFSET 	0x00083024

//This is register to read back DDR clk, it is offset to MCCC_MCCC_MSTR base
#define MCCC_CLK_PERIOD_PERIOD_OFFSET	0x50
	

//DDR PWRS
#define LP4 4
#define LP5 5

#define OSU_PWRS_STATUS_OFFSET 			0x6420
#define DDRPHY_SPMPSI_SPM_PSI0_STA_OFFSET 	0x316EC

//XO control
#define PHY0_XO_CBCR_OFFSET 0x11C
#define PHY1_XO_CBCR_OFFSET 0x128

// Performance Monitor Unit (PMU)
#define PMCR_E                  (1 << 0) 
#define PMCNTENSET_EL0_ENABLE   (1<<31) 
#define PMEVTYPER_EVTCOUNT_MASK 0x3FF
#define DTLB_WALK_EVT			0x0034

// Unusable Memory Region
#define UNUSABLE_DDR_START      0x80000000
#define UNUSABLE_DDR_END        0x80600000
#define NUM_OF_CPU_CLUSTERS 4

//These are registers for LLCC TRP ECC STATUS
#define LLCC_TRP_ECC_ERROR_STATUS1_OFFSET      0x20348

#ifdef CEDROS
	#define LLCC_CHANNEL_NUMBER 2
	//These are registers for LLCC DRP ECC STATUS
	#define LLCC_DRP_CH0_ECC_ERROR_STATUS1_OFFSET  0x2048
#elif defined(LAHAINA) 
	#define LLCC_CHANNEL_NUMBER 4
	//These are registers for LLCC DRP ECC STATUS
	#define LLCC_DRP_CH0_ECC_ERROR_STATUS1_OFFSET  0x42048
#elif defined(WAIPIO) 
	#define LLCC_CHANNEL_NUMBER 4
	//These are registers for LLCC DRP ECC STATUS
	#define LLCC_DRP_CH0_ECC_ERROR_STATUS1_OFFSET  0x52048
#elif defined(DEFAULT)
	#define LLCC_CHANNEL_NUMBER 4
	//These are registers for LLCC DRP ECC STATUS
	#define LLCC_DRP_CH0_ECC_ERROR_STATUS1_OFFSET  0x52048
#endif

#endif /* __TARGET_H__ */
