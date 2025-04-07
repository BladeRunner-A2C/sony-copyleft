/**@file DbiDumpLib.c

  Copyright (c) 2016-2018, 2020-2022, 2023 Qualcomm Technologies Inc. All rights reserved.<BR>

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 
 --------   ---     -----------------------------------------------------------
 01/13/20   am      Write the DBI dump table size to shared imem
 06/13/16   vk      Initial version
=============================================================================*/

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ArmLib.h>
#include <Library/IoLib.h>
#include <Protocol/DebugSupport.h>

#include <Include/UefiInfoBlk.h>
#include <Library/SerialPortShLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/DbiDumpLib.h>
#include <Library/DBIDump_WP.h>
#include <Library/CookieLib.h>
#include <Library/WatchdogLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/TzRuntimeLib.h>
#include <boot_minidump.h>

UINT64 DBIDumpTableInfo[3];
extern EFI_GUID gDBIDumpTableInfoHobGuid;

extern
VOID *
EFIAPI
BuildGuidDataHob (
  IN CONST EFI_GUID              *Guid,
  IN VOID                        *Data,
  IN UINTN                       DataLength
  );


#define ARRAY_LENGTH(a) (sizeof(a) / sizeof((a)[0]))

VOID
SetupDBIDumpTable ()
{
   EFI_STATUS Status = EFI_SUCCESS;
   UINTN SMEMWriteAddrForSize = 0;
   UINTN SMEMWriteAddrForAddr = 0;
   UINT32 i;
   UINT32 running_index = 0;
//   UINT32 NumCores = 0;
   UINT32 SkipDBISetup = 0;
   UINT32 SharedIMEMBaseAddr = 0;
   UINT64 MemoryBase;
   MemRegionInfo DBIDumpRegionInfo;
   UINT64 DBIDumpTableAddress = 0;
   UINT64 DBIDumpTableSize    = 0;
   UINT64 DBIDumpTableAssign  = 1; 
   
   Status = GetMemRegionInfoByName("DBI_Dump", &DBIDumpRegionInfo);
   if (Status != EFI_SUCCESS)
   {
      DEBUG((EFI_D_ERROR, " Could not find the DBI Dump region .\r\n"));
      return;
   }
   if (DBIDumpRegionInfo.MemBase == 0 || DBIDumpRegionInfo.MemSize == 0) 
   {
      DEBUG((EFI_D_ERROR, " DBI Dump region is invalid .\r\n"));
      return;
   }
   MemoryBase = DBIDumpRegionInfo.MemBase;
   
   /* Zero-out DBI Dump Region. Commented out due to the extra time it takes. */
   //memset((void *)DBIDumpRegionInfo.MemBase, 0x0, DBIDumpRegionInfo.MemSize); 
   
   DUMP_TABLE_TYPE *DbiDumpTable = (DUMP_TABLE_TYPE*)(MemoryBase + DBI_DUMP_TABLE_OFFSET);
   DUMP_TABLE_TYPE *AppDumpTable = (DUMP_TABLE_TYPE*)(MemoryBase + DBI_DUMP_TABLE_OFFSET + sizeof(DUMP_TABLE_TYPE));
   DUMP_DATA_TYPE_TABLE *DumpDataTypeTable = (DUMP_DATA_TYPE_TABLE*)(MemoryBase + DBI_DUMP_TABLE_OFFSET + 2*sizeof(DUMP_TABLE_TYPE));
   
   if (DbiDumpTable == NULL)
   {
      DEBUG ((EFI_D_ERROR, "ERROR: DBI Dump table not setup\r\n"));
      return;
   }
   
   Status = GetConfigValue("SkipDBISetup", (UINT32*)&SkipDBISetup);
   if ((Status == EFI_SUCCESS) && (SkipDBISetup == 1)) {
      return;
   }

   
//   Status = GetConfigValue("NumCpus", (UINT32*)&NumCores);
//   if (Status != EFI_SUCCESS)
//   {
//      DEBUG(( EFI_D_ERROR, "Could not NumCpus uefiplat.cfg Defaulting to 8 cores , Status = (0x%x)\r\n", Status));
//      NumCores = 0x08;
//   }
   
   /* Fill out the top level DbiDumpTable version and entries*/
   DbiDumpTable->Version    =    DBI_DUMP_TABLE_VERSION;
   DbiDumpTable->NumEntries =    0x1;
   
   /* Fill out the second level APP dump table */
   AppDumpTable->Version     =   DBI_DUMP_TABLE_VERSION;
   AppDumpTable->NumEntries  =   NUM_OF_APPS_DUMP_ENTRY;
   
   DbiDumpTable->Entries[0].id         = MSM_DUMP_CLIENT_APPS;
   DbiDumpTable->Entries[0].type       = MSM_DUMP_TYPE_TABLE;
   DbiDumpTable->Entries[0].start_addr = (UINT64)AppDumpTable; 
   
   DEBUG ((EFI_D_INFO, "NumCores : %d \n", NUMBER_OF_CORES));
   
   /* Populate CPU REG Dump entries */
   for (i=0; i < NUMBER_OF_CORES ; i++)
   {
      DumpDataTypeTable->DumpDataType[i].header.version = 0x0;
      DumpDataTypeTable->DumpDataType[i].header.magic   = 0x0;
      DumpDataTypeTable->DumpDataType[i].start_addr     = MemoryBase + CPU_REG_DUMP_START_OFFSET + i * SDI_DUMP_CORE_AP_REG_SIZE;
      DumpDataTypeTable->DumpDataType[i].len            = SDI_DUMP_CORE_AP_REG_SIZE;
      AppDumpTable->Entries[i].id                       = MSM_CPU_REGS_DUMP + i;
      AppDumpTable->Entries[i].type                     = MSM_DUMP_TYPE_DATA;
      AppDumpTable->Entries[i].start_addr               = (UINT64)(&DumpDataTypeTable->DumpDataType[i]); 
   }
   running_index += NUMBER_OF_CORES;

   /* Fill in ETB entry */
   DumpDataTypeTable->DumpDataType[running_index].header.version = 0x0;
   DumpDataTypeTable->DumpDataType[running_index].header.magic   = 0x0;
   DumpDataTypeTable->DumpDataType[running_index].start_addr     = MemoryBase + CPU_REG_DUMP_END_OFFSET;
   DumpDataTypeTable->DumpDataType[running_index].len            = SDI_DUMP_ETB_DUMP_SIZE;
   AppDumpTable->Entries[running_index].id                       = MSM_SWAOETB_DUMP;
   AppDumpTable->Entries[running_index].type                     = MSM_DUMP_TYPE_DATA;
   AppDumpTable->Entries[running_index].start_addr               = (UINT64)(&DumpDataTypeTable->DumpDataType[running_index]);
   running_index += 1;

   /* Fill in TMC entries */
   for (i=0; i < NUMBER_OF_TMC_DUMP_ENTRIES ; i++)
   {
      DumpDataTypeTable->DumpDataType[running_index + i].header.version = 0x0;
      DumpDataTypeTable->DumpDataType[running_index + i].header.magic   = 0x0;
      DumpDataTypeTable->DumpDataType[running_index + i].start_addr     = MemoryBase + CPU_TMC_DUMP_START_OFFSET + i * SDI_DUMP_TMC_DUMP_SIZE;
      DumpDataTypeTable->DumpDataType[running_index + i].len            = SDI_DUMP_TMC_DUMP_SIZE;
      AppDumpTable->Entries[running_index + i].id                       = MSM_TMC_DUMP + i;
      AppDumpTable->Entries[running_index + i].type                     = MSM_DUMP_TYPE_DATA;
      AppDumpTable->Entries[running_index + i].start_addr               = (UINT64)(&DumpDataTypeTable->DumpDataType[running_index + i]); 
   }
   running_index += NUMBER_OF_TMC_DUMP_ENTRIES;
  
   /* Fill in RPMh CODE RAM DUMP entry */
   DumpDataTypeTable->DumpDataType[running_index].header.version = 0x0;
   DumpDataTypeTable->DumpDataType[running_index].header.magic   = 0x0;
   DumpDataTypeTable->DumpDataType[running_index].start_addr     = MemoryBase + RPMH_CODE_RAM_DUMP_START_OFFSET;
   DumpDataTypeTable->DumpDataType[running_index].len            = SDI_RPMH_CODE_RAM_DUMP_SIZE;
   AppDumpTable->Entries[running_index].id                       = MSM_DATA_RPMhDUMP;
   AppDumpTable->Entries[running_index].type                     = MSM_DUMP_TYPE_DATA;
   AppDumpTable->Entries[running_index].start_addr               = (UINT64)(&DumpDataTypeTable->DumpDataType[running_index]);
   running_index += 1;

   /* Fill in PMIC dump entry */
   DumpDataTypeTable->DumpDataType[running_index].header.version = 0x0;
   DumpDataTypeTable->DumpDataType[running_index].header.magic   = 0x0;
   DumpDataTypeTable->DumpDataType[running_index].start_addr     = MemoryBase + PMIC_DUMP_START_OFFSET;
   DumpDataTypeTable->DumpDataType[running_index].len            = SDI_PMIC_DUMP_SIZE;
   AppDumpTable->Entries[running_index].id                       = MSM_PMIC_DUMP;
   AppDumpTable->Entries[running_index].type                     = MSM_DUMP_TYPE_DATA;
   AppDumpTable->Entries[running_index].start_addr               = (UINT64)(&DumpDataTypeTable->DumpDataType[running_index]);
   running_index += 1;

   /* ALL CPU CACHE Dump is per core */
   for (i=0; i < NUMBER_OF_CORES ; i++)
   {
      DumpDataTypeTable->DumpDataType[running_index + i].header.version = 0x0;
      DumpDataTypeTable->DumpDataType[running_index + i].header.magic   = 0x0;
      DumpDataTypeTable->DumpDataType[running_index + i].start_addr     = MemoryBase + ALL_CPU_CACHE_START_OFFSET + i * ALL_CPU_CACHE_SIZE;
      DumpDataTypeTable->DumpDataType[running_index + i].len            = ALL_CPU_CACHE_SIZE;
      AppDumpTable->Entries[running_index + i].id                       = ALL_CPU_CACHES + i;
      AppDumpTable->Entries[running_index + i].type                     = MSM_DUMP_TYPE_DATA;
      AppDumpTable->Entries[running_index + i].start_addr               = (UINT64)(&DumpDataTypeTable->DumpDataType[running_index + i]);
   }
   running_index += NUMBER_OF_CORES;


   for (i=0; i < NUMBER_OF_CLUSTERS ; i++)
   {
      DumpDataTypeTable->DumpDataType[running_index + i].header.version = 0x0;
      DumpDataTypeTable->DumpDataType[running_index + i].header.magic   = 0x0;
      DumpDataTypeTable->DumpDataType[running_index + i].start_addr     = MemoryBase + ALL_CLUSTERCACHE_START_OFFSET + i * ALL_CLUSTER_CACHE_SIZE;
      DumpDataTypeTable->DumpDataType[running_index + i].len            = ALL_CLUSTER_CACHE_SIZE;
      AppDumpTable->Entries[running_index + i].id                       = ALL_CLUSTER_CACHES + i;
      AppDumpTable->Entries[running_index + i].type                     = MSM_DUMP_TYPE_DATA;
      AppDumpTable->Entries[running_index + i].start_addr               = (UINT64)(&DumpDataTypeTable->DumpDataType[running_index + i]); 
   }
   running_index += NUMBER_OF_CLUSTERS;

   DumpDataTypeTable->DumpDataType[running_index].header.version = 0x0;
   DumpDataTypeTable->DumpDataType[running_index].header.magic   = 0x0;
   DumpDataTypeTable->DumpDataType[running_index].start_addr     = MemoryBase + MSM_CPU_DEBUG_DUMP_START_OFFSET;
   DumpDataTypeTable->DumpDataType[running_index].len            = MSM_CPU_DEBUG_DUMP_SIZE;
   AppDumpTable->Entries[running_index].id                       = MSM_CPU_DEBUG_DUMP;
   AppDumpTable->Entries[running_index].type                     = MSM_DUMP_TYPE_DATA;
   AppDumpTable->Entries[running_index].start_addr               = (UINT64)(&DumpDataTypeTable->DumpDataType[running_index]);
   running_index += 1;

   /* Populate CPU_Context Dump entries */
   
   DumpDataTypeTable->DumpDataType[running_index].header.version = 0x0;
   DumpDataTypeTable->DumpDataType[running_index].header.magic   = 0x0;
   DumpDataTypeTable->DumpDataType[running_index].start_addr     = MemoryBase + CPU_CONTEXT_DUMP_START_OFFSET ;
   DumpDataTypeTable->DumpDataType[running_index].len            = (SDI_DUMP_CORE_CPU_CONTEXT_SIZE * NUMBER_OF_CORES) + CPU_CONTEXT_DATA_SIZE + CPU_CONTEXT_SPECIFIC_INFO;
   AppDumpTable->Entries[running_index].id                       = MSM_CPU_CONTEXT_DUMP;
   AppDumpTable->Entries[running_index].type                     = MSM_DUMP_TYPE_DATA;
   AppDumpTable->Entries[running_index].start_addr               = (UINT64)(&DumpDataTypeTable->DumpDataType[running_index]); 
   
   running_index += 1;



   // LA calls into this function in SEC where NumCores is 0x4
   ASSERT(running_index <= NUM_OF_APPS_DUMP_ENTRY);

   /* Set the IMEM Cookie with the address to the DbiDumpTable */
   Status = GetConfigValue ("SharedIMEMBaseAddr", (UINT32 *)&SharedIMEMBaseAddr); 
   if ((Status != EFI_SUCCESS) || (SharedIMEMBaseAddr == 0))
   {
      DEBUG ((EFI_D_ERROR, "Unable to get SharedIMEMBaseAddr from uefiplat!\n"));
      return;
   } 

   // Write the table size to shared imem + 0x734 as TZ checks for size during ramdump collection
   /* TODO: Fix this when Shared IMEM table is fixed to support 64-bit addressing */
   SMEMWriteAddrForSize = (UINTN) SharedIMEMBaseAddr + TZBSP_SHARED_IMEM_TZ_AREA_BASE_OFFSET;
   DBIDumpTableSize = (UINTN) DBIDumpRegionInfo.MemSize;
   
   /* TODO: Fix this when Shared IMEM table is fixed to support 64-bit addressing */
   SMEMWriteAddrForAddr = (UINTN) SharedIMEMBaseAddr + DBI_SHARED_IMEM_COOKIE_OFFSET;
   //ASSERT((UINTN) DbiDumpTable < 0xFFFFFFFF);
   DBIDumpTableAddress = ((UINTN)DbiDumpTable & 0xFFFFFFFF);
   
   DBIDumpTableInfo[0] = DBIDumpTableAssign;
   DBIDumpTableInfo[1] = DBIDumpTableAddress;
   DBIDumpTableInfo[2] = DBIDumpTableSize;
   
#ifndef ENABLE_STANDALONE 
   Status = TzFastcall(
       TZ_DUMP_ASSIGN_DUMP_TABLE_REGION,
       TZ_DUMP_ASSIGN_DUMP_TABLE_REGION_PARAM_ID,
       DBIDumpTableInfo,
       ARRAY_LENGTH(DBIDumpTableInfo)
       ); 
	   
#endif
   if(Status == EFI_UNSUPPORTED)
   {
     DEBUG((EFI_D_INFO, " TZ Dump Table region assignment SCM call not suppported, Status =  (0x%x)\r\n", Status));
     /* Write to the shared IMEM region directly */
     MmioWrite32(SMEMWriteAddrForSize, DBIDumpTableSize);
     MmioWrite32(SMEMWriteAddrForAddr, DBIDumpTableAddress);
   }
   if (Status == EFI_DEVICE_ERROR)
      /* SMC call supported but failed due to invalid argument. */
      DEBUG((EFI_D_ERROR, "DBI Dump table region assignment by TZ failed due to invalid argument or some other reason"));	

   /* Share DBI DumpTable Info with EnvDxe in post sec stage so that UEFI DBI Dump region can be deregistered */
   BuildGuidDataHob (&gDBIDumpTableInfoHobGuid, DBIDumpTableInfo, sizeof(DBIDumpTableInfo));

	/* add minidump region in boot sub-system minidump table */
	if(!boot_add_minidump_region (MD_SS_BOOT, "MEMDUMP", (UINT64)DBIDumpRegionInfo.MemBase, (UINT64)DBIDumpRegionInfo.MemSize))
	{
		DEBUG ((EFI_D_WARN, "MEMDUMP region could not be added to Minidump table \r\n"));
	}
}  


EFI_STATUS
InitDbiDump(VOID)
{
   EFI_STATUS Status;

   SetupDBIDumpTable();

   Status = SetDLOADCookie();
   if (Status != EFI_SUCCESS ) 
     DEBUG((EFI_D_ERROR, "ERROR: Failed to set DLOAD cookie\n"));

   return Status;
}

EFI_STATUS
SaveUefiContext (EFI_SYSTEM_CONTEXT SystemContext)
{
  UefiInfoBlkType* UefiInfoBlkPtr;
  
  UefiInfoBlkPtr = GetInfoBlkPtr();
  if (UefiInfoBlkPtr == NULL) {
    DEBUG((EFI_D_ERROR, "ERROR: Failed to get UefiInfoBlk!\n"));
    return EFI_DEVICE_ERROR;
  }

  /* TODO: add handling for ARM */
  UefiInfoBlkPtr->CrashContext = (VOID*)SystemContext.SystemContextAArch64;
  return EFI_SUCCESS;
}

