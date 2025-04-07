/**
  @file DBIDump.h
 
  File contains registers used in Sec and MemoryMap.

  Copyright (c) 2012-2020, 2022, 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Confidential and Proprietary.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/13/22  md       Update DBI dump region format.
 01/13/20  am       Add TZBSP_SHARED_IMEM_TZ_AREA_BASE_OFFSET
 10/04/16  ly       Update DBI Dump Table to version 200000 and add more entries
 12/03/14  nk       Changed dump table address to static address 
 06/19/14  shireesh Increased Size of CPU reg to 1KB, Modified code to get DDR memory base at run time.
 05/15/14  shireesh revoved support for SDI dump version 0 and Added support for SDI dump ver 1
 01/15/14  shireesh moved DBI memory region to 64K
 02/11/13   niting  Updated DBI memory region.
 01/30/13   vk      Move dump structures from sec
 01/23/13   nk      Initial Verison.

 =============================================================================*/

/*
Context               Start Offset:        Size (per core/instance):
-------------------------------------------------------------------- 
DbiDumpTable          0x000000             0x908
AppDumpTable          0x000908             0x908
DumpDataTypeTable     0x001210             0x498
--------------------------------------------------------------------
Cores0..12            0x002000             0x800*12=0x6000 
ETB                   0x008000             0x10000  
TMC 0..2              0x018000             0x4000*3=0xC000
RPMh                  0x024000             0xC10000
PMIC                  0xC34000             0x10000
ALLCPUCACHE           0xC44000             2aa000*12=0x1ff8000; round off to 2000000
ALLCLUSTERCACHE	      0x2c44000            2430000*3=0x6c90000; round off to 6D00000
MSM_CPU_DEBUG_DUMP    0x9944000	           0xA00000
CPU_CONTEXT_DUMP      0xA344000            0x390*12 =0x2AC0 ;   0xA(SPECIFIC_INFO) + 0x20(CPU_CONTEXT_DATA)
END                   0xA346AEA 
*/

#ifndef _DBIDUMP_H_
#define _DBIDUMP_H_

#define TZBSP_SHARED_IMEM_TZ_AREA_BASE_OFFSET     (0x734)
#define DBI_SHARED_IMEM_COOKIE_OFFSET             (0x010)
#define NUMBER_OF_CORES                           (12)
#define NUMBER_OF_CLUSTERS                        (3)
#define SDI_DUMP_CORE_AP_REG_SIZE                 (0x800)//per core
#define SDI_DUMP_ETB_DUMP_SIZE                    (0x10000)
#define SDI_DUMP_TMC_DUMP_SIZE                    (0x4000)
#define NUMBER_OF_TMC_DUMP_ENTRIES                (0x3)
#define SDI_RPMH_CODE_RAM_DUMP_SIZE               (0xC10000) // ~12MB
#define SDI_PMIC_DUMP_SIZE                        (0x200000)
#define ALL_CPU_CACHE_SIZE                        (0x2AA000) //per core
#define ALL_CLUSTER_CACHE_SIZE                         (0x2430000) //per cluster
#define MSM_CPU_DEBUG_DUMP_SIZE (0xA00000)
#define SDI_DUMP_CORE_CPU_CONTEXT_SIZE              (0x390)//per core ~ 912 BYTES
#define CPU_CONTEXT_DATA_SIZE					   (0x20)
#define CPU_CONTEXT_SPECIFIC_INFO                  (0x10)

/* Current supported Dump Table Version is 1.5 */
#define DBI_DUMP_TABLE_VERSION                    (0x200000) 

/* 12 CPU reg dump entries;  1 ETB; 3 TMC; 1 RPMh;1 PMIC, 12 CPU_CACHES, 3 CLUSTER_CACHES , 1 CPU_DEBUG_DUMP , 12 CPU context dump entries */
#define NUM_OF_APPS_DUMP_ENTRY                    (0x2E)

#define DBI_DUMP_TABLE_OFFSET           (0x0)
#define DBI_DUMP_TABLE_END_OFFSET       (0x2000)

#define CPU_REG_DUMP_START_OFFSET       DBI_DUMP_TABLE_END_OFFSET
#define CPU_REG_DUMP_END_OFFSET         (CPU_REG_DUMP_START_OFFSET + SDI_DUMP_CORE_AP_REG_SIZE * NUMBER_OF_CORES)

//ETB Dump location offset from DDR base
#define CPU_ETB_DUMP_START_OFFSET      (CPU_REG_DUMP_END_OFFSET)
#define CPU_ETB_DUMP_END_OFFSET        (CPU_REG_DUMP_END_OFFSET + SDI_DUMP_ETB_DUMP_SIZE)

//TMC Dump
#define CPU_TMC_DUMP_START_OFFSET      (CPU_ETB_DUMP_END_OFFSET)
#define CPU_TMC_DUMP_END_OFFSET        (CPU_TMC_DUMP_START_OFFSET + SDI_DUMP_TMC_DUMP_SIZE * NUMBER_OF_TMC_DUMP_ENTRIES)

//RPMh code ram dump
#define RPMH_CODE_RAM_DUMP_START_OFFSET (CPU_TMC_DUMP_END_OFFSET)
#define RPMH_CODE_RAM_DUMP_END_OFFSET   (RPMH_CODE_RAM_DUMP_START_OFFSET + SDI_RPMH_CODE_RAM_DUMP_SIZE)

#define PMIC_DUMP_START_OFFSET         (RPMH_CODE_RAM_DUMP_END_OFFSET)
#define PMIC_DUMP_END_OFFSET           (PMIC_DUMP_START_OFFSET +  SDI_PMIC_DUMP_SIZE)

#define ALL_CPU_CACHE_START_OFFSET     (PMIC_DUMP_END_OFFSET)
#define ALL_CPU_CACHE_END_OFFSET       (ALL_CPU_CACHE_START_OFFSET + ALL_CPU_CACHE_SIZE *  NUMBER_OF_CORES)   

#define ALL_CLUSTERCACHE_START_OFFSET (ALL_CPU_CACHE_END_OFFSET) 
#define ALL_CLUSTERCACHE_END_OFFSET (ALL_CLUSTERCACHE_START_OFFSET + ALL_CLUSTER_CACHE_SIZE * NUMBER_OF_CLUSTERS)

#define MSM_CPU_DEBUG_DUMP_START_OFFSET (ALL_CLUSTERCACHE_END_OFFSET)
#define MSM_CPU_DEBUG_DUMP_END_OFFSET (MSM_CPU_DEBUG_DUMP_START_OFFSET + MSM_CPU_DEBUG_DUMP_SIZE)

#define CPU_CONTEXT_DUMP_START_OFFSET      (MSM_CPU_DEBUG_DUMP_END_OFFSET)
#define CPU_CONTEXT_DUMP_END_OFFSET        (CPU_CONTEXT_DUMP_START_OFFSET + CPU_CONTEXT_SPECIFIC_INFO + CPU_CONTEXT_DATA_SIZE +(SDI_DUMP_CORE_CPU_CONTEXT_SIZE * NUMBER_OF_CORES))



/*
 * DBI DUMP REGION:
 * -DUMPTABLE
 * -APPSTABLE
 * -DUMPTABLENTRYTABLE
 * <hole>
 * -DUMP DATA
 *    CPU REG DUMP Entries (0x0-0x7)
 *    ETB (0xF0)
 *    TMC Entries (0x100-0x102)
 *    RPMh (0xEC)
 *    PMIC (0xE4)
 *    SCAN DUMP Entries (0x130-0x137) 
 *
 * Note: Location of DUMPTABLE is saved to shared IMEM for SDI to use.
 */

/* Generic header for every kind of dump supported */
/* HLOS Dump Structure */
/* Dump Type */
typedef enum
{
  MSM_CPU_REGS_DUMP   = 0x00,
  MSM_CPU_REGS_DUMP2  = 0x10,
  CPU_L1_INST_TLB_DUMP  = 0x20,
  CPU_L1_INST_TLB_DUMP2 = 0x30,
  CPU_L1_DATA_TLB_DUMP  = 0x40,
  CPU_L1_DATA_TLB_DUMP2 = 0x50,
  CPU_L1_ICACHE_DUMP  = 0x60,
  CPU_L1_ICACHE_DUMP2 = 0x70,
  CPU_L1_DCACHE_DUMP  = 0x80,
  CPU_L1_DCACHE_DUMP2 = 0x90,
  CPU_L2_DCACHE_DUMP  = 0xC0,
  CPU_L2_ICACHE_DUMP = CPU_L2_DCACHE_DUMP,
  CPU_L3_CACHE_DUMP = 0xD0,
  CPU_L3_ICACHE_DUMP = CPU_L3_CACHE_DUMP,
  CPU_L3_DCACHE_DUMP = CPU_L3_ICACHE_DUMP,
  _RESERVED1 = 0xE0, // Reserved for OCMEM
  MSM_GENERIC_DUMP = 0xE8,
  MSM_ETB_DUMP = 0xF0, 
  MSM_SWAOETB_DUMP = 0xF1,
  MSM_ETM_DUMP = 0xA0,
  _RESERVED2   = 0xB0,
  MSM_TMC_DUMP = 0x100,
  MSM_LLCC_DUMP = 0x140,
  MSM_DATA_DCC_REG_DUMP = 0xE6,
  MSM_DATA_DCC_SRAM_DUMP = 0xE7,
  MSM_DATA_RPM_CODE_RAM_DUMP = 0xEA,
  MSM_DUMP_DATA_DBGUI_REG = 0xE5,
  MSM_DUMP_DATA_VSENSE = 0xE9,
  MSM_DATA_SCANDUMP = 0xEB,
  MSM_DATA_RPMhDUMP = 0xEC,
  MSM_PMIC_DUMP = 0xE4,
  MSM_POWER_REGS_DUMP = 0xED,
  MSM_CPU_DEBUG_DUMP = 0xEF,
  MSM_DATA_APPS_SCANDUMP = 0x130,
  MSM_L2_TLB_DUMP = 0x120,
  ALL_CPU_CACHES = 0x230,
  ALL_CLUSTER_CACHES = 0x240,
  MSM_CPU_CONTEXT_DUMP = 0x250,
  MSM_MAX_DUMP = 0x300,
  MAX_DUMP_TYPES = 0x7FFFFFFF,
}DUMP_TYPE;


typedef struct
{
  /* Format version of the saved structure */
  UINT32 version;
  /* Magic number */
  UINT32 magic;
  /* Name of the dump. Currently unused */
  CHAR8 name[32];
}DUMP_HEADER_TYPE; 
 

/* Dump data type */
typedef struct
{
  DUMP_HEADER_TYPE header;
  UINT64 start_addr;
  UINT64 len;
}DUMP_DATA_TYPE; 

/* Enums for the various clients in the dump table */
typedef enum
{
  MSM_DUMP_CLIENT_APPS = 0,
  MSM_DUMP_CLIENT_RPM  = 1,
  MSM_DUMP_CLIENT_MPSS = 2, 
  MSM_DUMP_CLIENT_ADSP = 3, 
  MSM_DUMP_CLIENT_WCSS = 4,
  MSM_DUMP_CLIENT_MAX  = 5,
}MSM_DUMP_CLIENTS;

/* Enum for the type of dump entry provided by HLOS */
typedef enum
{
  MSM_DUMP_TYPE_DATA = 0x0,
  MSM_DUMP_TYPE_TABLE = 0x1,
  MSM_DUMP_TYPE_MAX = 0x2
}MSM_DUMP_ENTY_TYPE;


/* Dump entry in the table */
typedef struct
{
    UINT32 id;
    CHAR8 name[32];
    UINT32 type;
    UINT64 start_addr;
}DUMP_ENTRY_TYPE;

/* Dump Table */
typedef struct 
{
  UINT32 Version;
  UINT32 NumEntries;
  DUMP_ENTRY_TYPE Entries[MSM_MAX_DUMP>>4];
}DUMP_TABLE_TYPE;

typedef struct
{
  DUMP_DATA_TYPE DumpDataType[NUM_OF_APPS_DUMP_ENTRY];
}DUMP_DATA_TYPE_TABLE;

#endif /* _DBIDUMP_H_ */

