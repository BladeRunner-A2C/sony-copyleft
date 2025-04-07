/** @file UefiPlatCfg.c
  Pareser for UEFI platform configuration data.

  Copyright (c) 2012-2019, 2021-2023 Qualcomm Technologies, Inc.  All
  Rights Reserved. Qualcomm Technologies Proprietary and
  Confidential.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why

 --------   ---     -----------------------------------------------------------
 05/09/23   rbv     Parse MemMap and RegMap info from DT instead of FV
 02/27/23   bxr     Added MemoryMap and RegisterMap overlap check.
 02/15/23   rk      Added support for marking memory segments for PASR feature.
 07/21/21   cm      Added NoMap as BuildHob option.
 07/09/21   md      Added functions to detect overlap memory regions in the ram
                    partition table defined hole, function to convert the avail
                    Reserv Mem region to conventional memory
 03/22/19   md      Added HobOnlyNoCacheSetting HOB option parsing.
 09/11/18   md      Added support to create hole at the start of DDR memory.
 07/12/17   vk      Fix FD DEP
 09/09/16   vk      Add MMU lib
 06/28/16   bh      No longer assume config file is first in FV0
 02/18/16   bh      Update memory map parsing and non-FD bank parsing
 11/10/15   vk      Initialize globals explicitly for RAM load
 10/14/15   vk      Add NULL Check
 04/17/15   vk      Move to start initially from RAM partition entry with FD
 03/02/15   vk      Updates to parserlib
 10/18/14   jb      Allocate only memory map type
 10/30/14   vk      New cfg file
 04/10/14   niting  Fixed warnings
 11/26/13   vk      Update GetDDRInfo to use UINTN
 11/15/13   vk      Add ReInitCache return value check
 10/18/13   vk      Update MemRegionInfo struct members, Fix AllocMemNoFree
 10/16/13   vk      Change MemBaseOffset to MemBase, MemSize
 05/17/13   vk      Initialize cache early
 05/14/13   vk      Add processing for write-through cache setting
 04/13/13   plc     Check fuse for number of CPUs, if indicated in CFG file
 03/14/13   vk      AllocPool to AllocPages - mark as EfiBootServiceData
 02/11/13   niting  Add support for HW chip version based config items
 02/06/13   vk      Add error check for debug message
 02/01/13   vk      Common Sec, text based cfg file params
 01/17/13   vk      Add ConfigTable
 01/17/13   vk      Add UefiCfgLib and lablels to memory table
 11/21/12   niting  Added uefiplat.cfg for memory map configuration
 11/19/12   niting  Initial revision.

=============================================================================*/

#include <PiPei.h>
#include <UefiPlatCfg.h>
#include <PrePiFvFileIo.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/PrePiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ArmMmuLib.h>

#include <Library/ParserLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiCfgLib.h>
#include <Include/UefiInfoBlk.h>
#include <Library/RamPartitionTableLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/SortLib.h>

#include <SecDtb.h>
#include <Library/QcomBaseLib.h>

#define MAX_MEMORY_REGIONS      74

#define ROUND_TO_PAGE(x, y)  (((x) + (y)) & (~(y)))

#define DEFAULT_MEMORY_REGIONS  64
#define UEFIPLATCFG_FILE        "uefiplat.cfg"

/* Refer to TLMM_TLMM_HW_REVISION_NUMBER register definition */
#define HW_REVNUM_REG_PARTNUM_BMASK  0x0FFFF000
#define HW_REVNUM_REG_PARTNUM_SHIFT  12

#define ENABLE_DT_PERF  1

#ifdef ENABLE_DT_PERF
#define DT_PERF  EFI_D_WARN
#else
#define DT_PERF  EFI_D_INFO
#endif

/* Defined in LD script */
extern UINT64  EndOfText;

STATIC MemRegionInfo  *mMemRegions = NULL;
STATIC UINTN          mNumMemRegions = 0;
STATIC UINTN          NumMemoryMapRegion = 0;
STATIC UINT64         mMemMapLow = 0, mMemMapHigh = 0;
STATIC BOOLEAN        isMemMapHighNoMap = FALSE;

STATIC ConfigPair     *ConfigTable = NULL;
STATIC UINTN          ConfigTableEntryCount = 0;
STATIC UINT8          *FreeBufferPtr, *EndPtr;
STATIC UINT32         *ChipIDReg = NULL;
STATIC UINT64         PasrSupportMemoryStart = 0;

typedef struct
{
  UINT64      MemBase;   // Offset to DDR memory base
  UINT64      MemSize;   // Size (in bytes) of the memory region
  CHAR16      Name[MAX_MEM_LABEL_NAME];   // Region Name in ASCII  
}SortMemRegInfo;

EFI_STATUS
EFIAPI
InitCache (
  IN MemRegionInfo  *pMemRegions,
  IN UINTN          RegionsCnt
  );

UefiInfoBlkType *
GetInfoBlock (
  VOID
  );

VOID
InitGlobals (
  VOID
  )
{
  mMemRegions           = NULL;
  mNumMemRegions        = 0;
  mMemMapLow            = 0xFFFFFFFFFFFFFFFFULL;
  mMemMapHigh           = 0;
  ConfigTable           = NULL;
  ConfigTableEntryCount = 0;
  FreeBufferPtr         = NULL;
  EndPtr                = NULL;
  ChipIDReg             = NULL;
  isMemMapHighNoMap     = FALSE;
}

/**
  Allocates and zeros a buffer.

  @param  AllocationSize        The number of bytes to allocate and zero.

  @return A pointer to the allocated buffer or NULL if allocation fails.

**/
VOID *EFIAPI
AllocateZeroPool (
  IN UINTN  AllocationSize
  )
{
  VOID  *Memory;

  Memory = AllocatePages (EFI_SIZE_TO_PAGES (AllocationSize));
  if (Memory != NULL) {
    ZeroMem (Memory, AllocationSize);
  }

  return Memory;
}

/* NOTE: We do not free this memory */
STATIC VOID *
AllocMemNoFree (
  UINTN  Size
  )
{
  UINT8  *AllocatedPtr;

  if (Size == 0) {
    return NULL;
  }

  if (Size >= EFI_PAGE_SIZE) {
    return AllocateZeroPool (Size);
  }

  if (FreeBufferPtr == NULL) {
    if ((FreeBufferPtr = AllocateZeroPool (EFI_PAGE_SIZE)) == NULL) {
      DEBUG ((EFI_D_WARN, "MemoryAlloc failed\n"));
      return NULL;
    }

    EndPtr = FreeBufferPtr + EFI_PAGE_SIZE;
  }

  Size = (Size + 3) & (~3);
  if (FreeBufferPtr + Size > EndPtr) {
    if ((FreeBufferPtr = AllocateZeroPool (EFI_PAGE_SIZE)) == NULL) {
      DEBUG ((EFI_D_WARN, "MemoryAlloc failed\n"));
      ASSERT (FreeBufferPtr != NULL);
      return NULL;
    }

    EndPtr = FreeBufferPtr + EFI_PAGE_SIZE;
  }

  AllocatedPtr   = FreeBufferPtr;
  FreeBufferPtr += Size;
  return AllocatedPtr;
}


#define MIN_SUPPORTED_VERSION  3

STATIC VOID EFIAPI
ProcessConfigTokens (
  UINT8  *Section,
  UINT8  *Key,
  UINT8  *Value
  )
{
  CHAR8  *mKey            = (CHAR8 *)Key;
  CHAR8  *mValue          = (CHAR8 *)Value;
  UINTN  MaxMemoryRegions = 0;

  if (AsciiStrCmp (mKey, "Version") == 0) {
    if (AsciiStrDecimalToUintn (mValue) < MIN_SUPPORTED_VERSION) {
      DEBUG ((EFI_D_ERROR, "Unsupported config file version!\n"));
      CpuDeadLoop ();
      return; /* For KW */
    }
  } else if (AsciiStrCmp (mKey, "MaxMemoryRegions") == 0) {
    MaxMemoryRegions = AsciiStrDecimalToUintn (mValue);

    /* Allocate memory regions */
    if (mMemRegions == NULL) {
      UINTN  AllocSz = 0;
      AllocSz     = MaxMemoryRegions * sizeof (MemRegionInfo);
      mMemRegions = (MemRegionInfo *)AllocMemNoFree (AllocSz);

      if (mMemRegions == NULL) {
        DEBUG ((EFI_D_ERROR, "Unable to allocate memory for memory table!\n"));
        ASSERT (mMemRegions != NULL);
        CpuDeadLoop ();
        return; /* For KW */
      }

      /* Initialize */
      SetMem (mMemRegions, AllocSz, 0);
      mNumMemRegions = 0;
    }
  }

  return;
}

STATIC VOID EFIAPI
ParseConfigParameters (
  UINT8  *Section,
  UINT8  *Key,
  UINT8  *Value
  )
{
  STATIC UINTN  MaxConfigParameters;

  CHAR8  *mKey   = (CHAR8 *)Key;
  CHAR8  *mValue = (CHAR8 *)Value;

  /* Allocate only once */
  if (ConfigTable == NULL) {
    if (AsciiStrCmp (mKey, "ConfigParameterCount") == 0) {
      UINTN  AllocSz = 0;

      MaxConfigParameters = AsciiStrDecimalToUintn (mValue);
      DEBUG ((EFI_D_INFO, "MaxConfigParameters = %d\r\n", MaxConfigParameters));

      AllocSz     = MaxConfigParameters * sizeof (ConfigPair);
      ConfigTable = AllocMemNoFree (AllocSz);
      if (ConfigTable == NULL) {
        DEBUG ((EFI_D_ERROR, "Failed to allocate enough memory for config table \n"));
        ASSERT (ConfigTable != NULL);
        return; /* For KW*/
      }

      SetMem (ConfigTable, AllocSz, 0);
    }
  } else {
    /* Process only max number of entries provided in cfg file */
    if ((ConfigTableEntryCount > MaxConfigParameters) || (MaxConfigParameters == 0)) {
      DEBUG ((EFI_D_ERROR, "Config file has more entries than specified max value\n"));
      ASSERT (MaxConfigParameters != 0);
      ASSERT (ConfigTableEntryCount < MaxConfigParameters);
      return; /* For KW */
    }

    ConfigTable[ConfigTableEntryCount].Key   = AllocMemNoFree (AsciiStrLen (mKey)+1);
    ConfigTable[ConfigTableEntryCount].Value = AllocMemNoFree (AsciiStrLen (mValue)+1);

    AsciiStrCpyS (ConfigTable[ConfigTableEntryCount].Key, AsciiStrLen (mKey)+1, mKey);
    AsciiStrCpyS (ConfigTable[ConfigTableEntryCount].Value, AsciiStrLen (mValue)+1, mValue);

    ConfigTableEntryCount++;
  }

  return;
}

/**
  Mark BuildHobOption for memory segment exceeding PasrSupportMemoryStart boundary.

  @param  EntryCount             Number of memmory segments/ partitions in EntryTable
  @param  EntryTable             Array of memory region/segments which should be parsed.
								 

  @retval EFI_SUCCESS            Successfully updated the entries with MemBase > PasrSupportMemoryStart
  @retval EFI_INVALID_PARAMETER  Value pointed by EntryTable is NULL
**/

EFI_STATUS UpdatePasrDisabledMemoryRegions(
          UINTN                 EntryCount,
          MemRegionInfo         *EntryTable
          )
{
  UINTN  i = 0;

  if((EntryTable == NULL))
  {
    // Invalid memory type specified
    return EFI_INVALID_PARAMETER;
  }
  /*
   * Get the boundary above which PASR feature for DDR should be turned off
   * for off mode charge condition.
   */
  if(PasrSupportMemoryStart != 0)
  {
    for(i = 0; i < EntryCount; i++)
    {
      if(EntryTable[i].MemBase >= PasrSupportMemoryStart) 
      {
        // This memory segment is violating the Pasr boundary. Print message.
        DEBUG((EFI_D_INFO, "UpdatePasrDisabledMemoryRegions:Memory Segment %s has Membase(0x%lx) > PasrSupportMemoryStart(0x%lx)\n",
                             EntryTable[i].Name, EntryTable[i].MemBase, PasrSupportMemoryStart));
        // If reached here then user wants to update BuildHobOption.
        EntryTable[i].BuildHobOption = HobOnlyNoCacheSetting;
      }
    }
  }
  return EFI_SUCCESS;
}

STATIC INTN MemEntryCompare(const void *Left, const void *Right)
{
  SortMemRegInfo *LeftEntry  = (SortMemRegInfo *)Left;
  SortMemRegInfo *RightEntry = (SortMemRegInfo *)Right;

  if (LeftEntry->MemBase != RightEntry->MemBase)
    return (INTN)(LeftEntry->MemBase - RightEntry->MemBase);
  else
    return (INTN)(LeftEntry->MemSize - RightEntry->MemSize);
}

STATIC void ValidateEntry(SortMemRegInfo *sort)
{
  UINTN  num;

  //sort in increasing order
  PerformQuickSort (sort, mNumMemRegions, sizeof(SortMemRegInfo), (SORT_COMPARE) MemEntryCompare);
  
  //check overlap
  for (num = 1; num < mNumMemRegions; num++)
  {
    if (sort[num].MemBase < (sort[num-1].MemBase + sort[num-1].MemSize))
    {
      DEBUG((EFI_D_ERROR,"MemRegion \"%s\" (0x%x) and \"%s\" (0x%x) are overlapping in cfg\n", sort[num].Name, sort[num].MemBase, sort[num-1].Name, sort[num-1].MemBase));
      ASSERT(FALSE);
    }
  }
}

STATIC void CheckOverlap()
{
  UINTN    i;
  SortMemRegInfo  *SortPtr = NULL;

  SortPtr = (SortMemRegInfo *) AllocateZeroPool (mNumMemRegions * sizeof(SortMemRegInfo));
  if (SortPtr == NULL)
  {
    DEBUG ((EFI_D_ERROR, "MemoryAlloc failed\n"));
    ASSERT (SortPtr != NULL);
  }
    
  for (i = 0; i < mNumMemRegions; i++)
  {
    SortPtr[i].MemBase = mMemRegions[i].MemBase;
    SortPtr[i].MemSize = mMemRegions[i].MemSize;
    AsciiStrToUnicodeStrS (mMemRegions[i].Name, SortPtr[i].Name, MAX_MEM_LABEL_NAME);
  }    

  ValidateEntry (SortPtr);

  if (SortPtr)
  {
    FreePool(SortPtr);
    SortPtr = NULL;
  }
}


/**
  This function parses given memory map node and updates the MemRegion struct.

  @param  Node                  Pointer to FdtNodeHandle for Memory/Register Map Entry.
  @param  MemRegion             Pointer to mMemRegion Table Member to be updated.
  
  @retval EFI_SUCCESS           All the Entries of MemRegion is updated.
  @retval EFI_LOAD_ERROR        One of the query to DTB failed and MemRegion is not fully updated.

**/
STATIC EFI_STATUS
EFIAPI
GetMemoryMapOfNode (
  FdtNodeHandle *Node,
  MemRegionInfo *MemRegion
)
{

  EFI_STATUS Status;
  Status = fdt_get_reg(Node,NULL,0,2,2,&MemRegion->MemBase,&MemRegion->MemSize);  
  if(Status){
      DEBUG ((EFI_D_ERROR, "fdt_get_reg: %d\n", Status));
      Status = EFI_LOAD_ERROR;
      return Status;
  }

  Status = fdt_get_string_prop_list(Node,"MemLabel",(CHAR8*)&(MemRegion->Name), MAX_MEM_LABEL_NAME);
  if(Status){
    DEBUG ((EFI_D_ERROR, "fdt_get_string_prop_list MemLabel: %d\n", Status));
    Status = EFI_LOAD_ERROR;
    return Status;
  }

  Status = fdt_get_uint8_prop(Node,"BuildHob",(UINT8*)&MemRegion->BuildHobOption);
  if(Status){
      DEBUG ((EFI_D_ERROR, "fdt_get_uint8_prop BuildHob: %d\n", Status));
      Status = EFI_LOAD_ERROR;
      return Status;
  }

  Status = fdt_get_uint8_prop(Node,"ResourceType",(UINT8*)&MemRegion->ResourceType);
  if(Status){
      DEBUG ((EFI_D_ERROR, "fdt_get_uint8_prop ResourceType: %d\n", Status));
      Status = EFI_LOAD_ERROR;
      return Status;
  }

  Status = fdt_get_uint8_prop(Node,"MemoryType",(UINT8*)&MemRegion->MemoryType);
  if(Status){
      DEBUG ((EFI_D_ERROR, "fdt_get_uint8_prop MemoryType: %d\n", Status));
      Status = EFI_LOAD_ERROR;
      return Status;
  }

  Status = fdt_get_uint8_prop(Node,"CacheAttributes",(UINT8*)&MemRegion->CacheAttributes);
  if(Status){
      DEBUG ((EFI_D_ERROR, "fdt_get_uint8_prop CacheAttributes: %d\n", Status));
      Status = EFI_LOAD_ERROR;
      return Status;
  }

  Status = fdt_get_uint32_prop(Node,"ResourceAttribute",(UINT32*)&MemRegion->ResourceAttribute);
  if(Status){
      DEBUG ((EFI_D_ERROR, "fdt_get_uint32_prop ResourceAttribute: %d\n", Status));
      Status = EFI_LOAD_ERROR;
      return Status;
  }

  
  return EFI_SUCCESS;
}

/**
  This function parses device tree and updates all the memory map entries 
  into mMemRegion Structure and the count of entries into mNumMemRegions.

  @retval EFI_SUCCESS           mMemRegion Structure is updated with all the memory map entries from DT.
  @retval EFI_LOAD_ERROR        Failed to update all the memory map entries to mMemRegionStruct.

**/
STATIC EFI_STATUS
EFIAPI
ParseMemoryMapEntriesFromDT (
  VOID 
)
{  
  FdtNodeHandle Node;
  EFI_STATUS Status;
  UINTN MemEntryCount = 0;

  //Check if the mMemRegions is Empty and assign space as per number of mNumMemRegions
  if (mMemRegions == NULL) {                  
    mMemRegions =  (MemRegionInfo *)AllocMemNoFree (sizeof(MemRegionInfo) * MAX_MEMORY_REGIONS);   
    if (mMemRegions == NULL) {
      DEBUG ((EFI_D_ERROR, "Unable to allocate memory for memory table!\n"));
      ASSERT (mMemRegions != NULL);
      CpuDeadLoop ();
      return EFI_LOAD_ERROR; /* For KW */
    }
    SetMem (mMemRegions, sizeof(MemRegionInfo) * MAX_MEMORY_REGIONS, 0);   
  }

  FdtNodeHandle *CachedMmapNode = NULL;
 
  Status = SecFdtGetNodeHandle(&Node,"/soc/memorymap/");
  if (Status){
    DEBUG ((EFI_D_ERROR, "SecFdtGetNodeHandle: %d\n", Status));
    goto ErrorExit;
  }  

  Status = fdt_get_count_of_subnodes(&Node,(UINT32*)&MemEntryCount);  
  if (Status){
    DEBUG ((EFI_D_ERROR, "fdt_get_count_of_subnodes: %d\n", Status));
    goto ErrorExit;
  }  
  
  CachedMmapNode = (FdtNodeHandle*)AllocatePool(sizeof(FdtNodeHandle) * MemEntryCount);
   
  Status = fdt_get_cache_of_subnodes(&Node,CachedMmapNode,(UINT32)MemEntryCount);
    if (Status){
      DEBUG ((EFI_D_ERROR, "fdt_get_cache_of_subnodes: %d\n", Status));
      goto ErrorExit;
   }    

  //Fill the table by looping through the entries     
  for(UINT8 i = 0;i < MemEntryCount;i++) {
    Status = GetMemoryMapOfNode(&CachedMmapNode[i],&mMemRegions[i]);
    if(Status){
      DEBUG ((EFI_D_ERROR, "GetMemoryMapOfNode Failed\n"));
      goto ErrorExit;      
    }
  }

  mNumMemRegions = MemEntryCount;  

  return EFI_SUCCESS;  

ErrorExit:
  DEBUG ((EFI_D_ERROR, "Failed ParseMemoryMapEntriesFromDT\r\n"));
  CpuDeadLoop ();
  return EFI_LOAD_ERROR;
  
}


/**
  This function parses device tree and updates all the register map entries 
  into mMemRegion Structure and update mNumMemRegions count.

  @retval EFI_SUCCESS           mMemRegion Structure is updated with all the register map entries from DT.
  @retval EFI_LOAD_ERROR        Failed to update all the register map entries to mMemRegionStruct.

**/
STATIC EFI_STATUS
EFIAPI
ParseRegisterMapEntriesFromDT (
  VOID 
)
{
  
  FdtNodeHandle Node;
  EFI_STATUS Status;
  UINTN RegisterEntryCount = 0;

  //Check if the mMemRegions is Empty and assign space as per number of mNumMemRegions
  if (mMemRegions == NULL) {                  
    mMemRegions =  (MemRegionInfo *)AllocMemNoFree (sizeof(MemRegionInfo) * MAX_MEMORY_REGIONS);   
    if (mMemRegions == NULL) {
      DEBUG ((EFI_D_ERROR, "Unable to allocate memory for memory table!\n"));
      ASSERT (mMemRegions != NULL);
      CpuDeadLoop ();
      return EFI_LOAD_ERROR; /* For KW */
    }
    SetMem (mMemRegions, sizeof(MemRegionInfo) * MAX_MEMORY_REGIONS, 0);   
  }

  FdtNodeHandle *CachedMmapNode = NULL;
  
  Status = SecFdtGetNodeHandle(&Node,"/soc/registermap/");
  if (Status){
    DEBUG ((EFI_D_ERROR, "SecFdtGetNodeHandle: %d\n", Status));
    goto ErrorExit;
  }  
  
  Status = fdt_get_count_of_subnodes(&Node,(UINT32*)&RegisterEntryCount);  
  if (Status){
    DEBUG ((EFI_D_ERROR, "fdt_get_count_of_subnodes: %d\n", Status));
    goto ErrorExit;
  }  
  
  CachedMmapNode = (FdtNodeHandle*)AllocatePool(sizeof(FdtNodeHandle) * RegisterEntryCount);
   
  Status = fdt_get_cache_of_subnodes(&Node,CachedMmapNode,(UINT32)RegisterEntryCount);
    if (Status){
      DEBUG ((EFI_D_ERROR, "fdt_get_cache_of_subnodes: %d\n", Status));
      goto ErrorExit;
   }  
  
  //Fill the table by looping through the entries 
  for(UINT8 i = 0;i < RegisterEntryCount;i++) {

    Status = GetMemoryMapOfNode(&CachedMmapNode[i],&mMemRegions[mNumMemRegions]);
    mNumMemRegions++;
    if(Status){
      DEBUG ((EFI_D_ERROR, "GetMemoryMapOfNode: %d\n", Status));
      goto ErrorExit;      
    }      
  }

  return EFI_SUCCESS;  

ErrorExit:
  DEBUG ((EFI_D_ERROR, "Failed ParseMemoryMapEntriesFromDT\r\n"));
  CpuDeadLoop ();
  return EFI_LOAD_ERROR;

}



STATIC VOID
GetCfgMemMapBounds (
  VOID
  )
{
  UINT64  Start, End;
  UINTN   i = 0;

  for (i = 0; i < mNumMemRegions; i++) {
    Start = mMemRegions[i].MemBase;
    End   = Start + mMemRegions[i].MemSize;
    if (Start < mMemMapLow) {
      mMemMapLow = Start;
    }

    if (End > mMemMapHigh) {
      mMemMapHigh       = End;
      isMemMapHighNoMap = FALSE;
      if (mMemRegions[i].BuildHobOption == NoMap) {
        isMemMapHighNoMap = TRUE;
      }
    }
  }
}

EFI_STATUS
AddNonFdRegions (
  UINTN            EntryCount,
  MemRegionInfo    *EntryTable,
  UefiInfoBlkType  *UefiInfoBlkPtr
  )
{
  UINT64  RegionEndAddr = 0;
  UINT64  DDRMemSize    = 0;
  UINTN   i             = 0;

  for (i = 0; i < EntryCount; i++) {
    DDRMemSize += EntryTable[i].MemSize;

    RegionEndAddr = EntryTable[i].MemBase +  EntryTable[i].MemSize;
    if ((EntryTable[i].MemBase < mMemMapHigh) && (RegionEndAddr >= mMemMapLow)) {
      continue;
    }

    // Update segment properties which are common to all cases.
    AsciiStrCpyS (mMemRegions[mNumMemRegions].Name, MAX_MEM_LABEL_NAME, EntryTable[i].Name);
    mMemRegions[mNumMemRegions].ResourceType      = EntryTable[i].ResourceType;
    mMemRegions[mNumMemRegions].ResourceAttribute = EntryTable[i].ResourceAttribute;
    mMemRegions[mNumMemRegions].MemoryType        = EntryTable[i].MemoryType;
    mMemRegions[mNumMemRegions].CacheAttributes   = EntryTable[i].CacheAttributes;
    
    /*
     * Check if any segment starts below PasrSupportMemoryStart boundary but
     * extends beyond PasrSupportMemoryStart boundary. If this is the case  
     * then break it in two segments. One segment within PasrSupportMemoryStart
     * boundary with given attributes. Second segment starting at PasrSupportMemoryStart
     * and with BuildHobOption = HobOnlyNoCacheSetting
     */
    if ((PasrSupportMemoryStart != 0 ) &&
        (EntryTable[i].MemBase < PasrSupportMemoryStart) && (RegionEndAddr >= PasrSupportMemoryStart))
    {

      DEBUG((EFI_D_ERROR,"AddNonFdRegions:Memory region extending beyond 4GB found. Performing splitting of region\n"));
      //Entry with Membase <4GB and EndAddress > 4GB found. Split this segment

      mMemRegions[mNumMemRegions].MemBase           = EntryTable[i].MemBase;
      /*
       * This memory region should end at the PasrSupportMemoryStart boundary. 
       * Hence calculate the size till PasrSupportMemoryStart limit.
       */
      mMemRegions[mNumMemRegions].MemSize           = (PasrSupportMemoryStart - EntryTable[i].MemBase);
      mMemRegions[mNumMemRegions].BuildHobOption    = EntryTable[i].BuildHobOption;

      mNumMemRegions++;

      //Create the second segment for memory region > PasrSupportMemoryStart
      // This memory region should begin at the PasrSupportMemoryStart and end at original end address.
      mMemRegions[mNumMemRegions].MemBase           = PasrSupportMemoryStart;
      mMemRegions[mNumMemRegions].MemSize           = (RegionEndAddr - PasrSupportMemoryStart);
      // Update the BuildHobOption as HobOnlyNoCacheSetting to allow for Pasr disable feature.
      mMemRegions[mNumMemRegions].BuildHobOption    = HobOnlyNoCacheSetting;

      mNumMemRegions++;
    }
    else
    {
      mMemRegions[mNumMemRegions].MemBase           = EntryTable[i].MemBase;
      mMemRegions[mNumMemRegions].MemSize           = EntryTable[i].MemSize;
      mMemRegions[mNumMemRegions].BuildHobOption    = EntryTable[i].BuildHobOption;

      mNumMemRegions++;
    }
  }

  UefiInfoBlkPtr->DDRMemSize = DDRMemSize;

  return EFI_SUCCESS;
}

EFI_STATUS
AddNonFdRegionRemainder (
  UefiInfoBlkType  *UefiInfoBlkPtr
  )
{
  MemRegionInfo  FdRegion;
  MemRegionInfo  NonFdRegion;
  UINT64         RegionEndAddr = 0;
  EFI_STATUS     Status;
  UINT64         UefiFdBase = FixedPcdGet64 (PcdEmbeddedFdBaseAddress);

  Status = GetPartitionEntryByAddr (UefiFdBase, &FdRegion);
  if (EFI_ERROR (Status)) {
    return EFI_LOAD_ERROR;
  }

  Status = GetPartitionEntryByAddr (mMemMapHigh, &NonFdRegion);
  if (EFI_ERROR (Status)) {
    /*Todo : need to check further on other cases*/
    if ((Status == EFI_NOT_FOUND) && isMemMapHighNoMap) {
      return EFI_SUCCESS;
    }

    return EFI_LOAD_ERROR;
  }

  if (FdRegion.MemBase == NonFdRegion.MemBase) {
    return EFI_SUCCESS;
  }

  RegionEndAddr = NonFdRegion.MemBase +  NonFdRegion.MemSize;

  AsciiStrCpyS (mMemRegions[mNumMemRegions].Name, MAX_MEM_LABEL_NAME, NonFdRegion.Name);

  mMemRegions[mNumMemRegions].MemBase           = mMemMapHigh;
  mMemRegions[mNumMemRegions].MemSize           = (RegionEndAddr - mMemMapHigh);
  mMemRegions[mNumMemRegions].BuildHobOption    = NonFdRegion.BuildHobOption;
  mMemRegions[mNumMemRegions].ResourceType      = NonFdRegion.ResourceType;
  mMemRegions[mNumMemRegions].ResourceAttribute = NonFdRegion.ResourceAttribute;
  mMemRegions[mNumMemRegions].MemoryType        = NonFdRegion.MemoryType;
  mMemRegions[mNumMemRegions].CacheAttributes   = NonFdRegion.CacheAttributes;

  mNumMemRegions++;

  return EFI_SUCCESS;
}

EFI_STATUS
AddFdRegionRemainder (
  UefiInfoBlkType  *UefiInfoBlkPtr
  )
{
  MemRegionInfo  FdRegion;
  UINT64         RegionEndAddr = 0;
  EFI_STATUS     Status;
  UINT64         UefiFdBase = FixedPcdGet64 (PcdEmbeddedFdBaseAddress);

  Status = GetPartitionEntryByAddr (UefiFdBase, &FdRegion);
  if (EFI_ERROR (Status)) {
    return EFI_LOAD_ERROR;
  }

  UefiInfoBlkPtr->FdMemBase = FdRegion.MemBase;
  RegionEndAddr             = FdRegion.MemBase +  FdRegion.MemSize;

  // TODO: Make sure we set to BsData and switch to conventional later in DXE
  if (mMemMapLow > FdRegion.MemBase) {
    AsciiStrCpyS (mMemRegions[mNumMemRegions].Name, MAX_MEM_LABEL_NAME, FdRegion.Name);

    mMemRegions[mNumMemRegions].MemBase           = FdRegion.MemBase;
    mMemRegions[mNumMemRegions].MemSize           = (mMemMapLow - FdRegion.MemBase);
    mMemRegions[mNumMemRegions].BuildHobOption    = FdRegion.BuildHobOption;
    mMemRegions[mNumMemRegions].ResourceType      = FdRegion.ResourceType;
    mMemRegions[mNumMemRegions].ResourceAttribute = FdRegion.ResourceAttribute;
    mMemRegions[mNumMemRegions].MemoryType        = FdRegion.MemoryType;
    mMemRegions[mNumMemRegions].CacheAttributes   = FdRegion.CacheAttributes;

    mNumMemRegions++;
  }

  if (mMemMapHigh < RegionEndAddr) {
    AsciiStrCpyS (mMemRegions[mNumMemRegions].Name, MAX_MEM_LABEL_NAME, FdRegion.Name);

    mMemRegions[mNumMemRegions].MemBase           = mMemMapHigh;
    mMemRegions[mNumMemRegions].MemSize           = (RegionEndAddr - mMemMapHigh);
    mMemRegions[mNumMemRegions].BuildHobOption    = FdRegion.BuildHobOption;
    mMemRegions[mNumMemRegions].ResourceType      = FdRegion.ResourceType;
    mMemRegions[mNumMemRegions].ResourceAttribute = FdRegion.ResourceAttribute;
    mMemRegions[mNumMemRegions].MemoryType        = FdRegion.MemoryType;
    mMemRegions[mNumMemRegions].CacheAttributes   = FdRegion.CacheAttributes;

    mNumMemRegions++;
  }

  return EFI_SUCCESS;
}

STATIC EFI_STATUS EFIAPI
UpdateDynamicMemoryRegions (
  VOID
  )
{
  MemRegionInfo  RamPartTableEntry[RAM_NUM_PART_ENTRIES];
  UINTN          RamPartTableEntryCount = RAM_NUM_PART_ENTRIES;
  UINT32         MemRgnCnt;
  EFI_STATUS     Status;

  Status = GetRamPartitions (&RamPartTableEntryCount, &RamPartTableEntry[0]);
  if (Status != EFI_SUCCESS) {
    ASSERT (Status == EFI_SUCCESS);
    return Status;
  }

  /* Parse through the memory region and check for the region with AddDynamicMem one */
  for (MemRgnCnt = 0; MemRgnCnt < mNumMemRegions; MemRgnCnt++) {
    BUILD_HOB_OPTION_TYPE  HobValue = mMemRegions[MemRgnCnt].BuildHobOption;
    if (HobValue == AddDynamicMem) {
      /* Check if the RamPartitiontable hole is less than carved out */
      for (UINT32 i = 0; i < RamPartTableEntryCount; i++) {
        UINT64  RamPartitionEntryEndAddress = RamPartTableEntry[i].MemBase + RamPartTableEntry[i].MemSize;
        if (mMemRegions[MemRgnCnt].MemBase == RamPartitionEntryEndAddress) {
          /* Update if requred pMemRegion size and allocate rest of the reserved memory space as Conventional memory */
          UINT64  HoleSize = RamPartTableEntry[i+1].MemBase - RamPartitionEntryEndAddress;
          if (HoleSize < mMemRegions[MemRgnCnt].MemSize) {
            /* Update MemRegion size and attributes */
            mMemRegions[MemRgnCnt].MemBase           = mMemRegions[MemRgnCnt].MemBase + HoleSize;
            mMemRegions[MemRgnCnt].MemSize           = mMemRegions[MemRgnCnt].MemSize - HoleSize;
            mMemRegions[MemRgnCnt].BuildHobOption    = (BUILD_HOB_OPTION_TYPE)AddMem;
            mMemRegions[MemRgnCnt].ResourceType      = EFI_RESOURCE_SYSTEM_MEMORY;
            mMemRegions[MemRgnCnt].ResourceAttribute = SYSTEM_MEMORY_RESOURCE_ATTR_SETTINGS_CAPABILITIES;
            mMemRegions[MemRgnCnt].MemoryType        = (EFI_MEMORY_TYPE)EfiConventionalMemory;
            mMemRegions[MemRgnCnt].CacheAttributes   = (ARM_MEMORY_REGION_ATTRIBUTES)ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN;
          }

          break;
        }
      }
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UpdateSystemMemoryRegions (
  VOID
  )
{
  EFI_STATUS       Status;
  MemRegionInfo    EntryList[RAM_NUM_PART_ENTRIES];
  UINTN            EntryCount = RAM_NUM_PART_ENTRIES;
  UefiInfoBlkType  *UefiInfoBlkPtr;

  UefiInfoBlkPtr = GetInfoBlock ();

  Status = GetRamPartitions (&EntryCount, &EntryList[0]);
  if (Status != EFI_SUCCESS) {
    ASSERT (Status == EFI_SUCCESS);
    return Status;
  }
  /*
   * For enabling Pasr support to reduce DDR power consumption,
   * DDR memory segments with MemBase > PasrSupportMemoryStart 
   * should be marked with BuildHobOption = HobOnlyNoCacheSetting.
   * Here RamPartitions are read in Entrylist. Hence check 
   * whether any segment has MemBase > PasrSupportMemoryStart.
   * For segment with MemBase < PasrSupportMemoryStart but segment
   * EndAddress extending beyond PasrSupportMemoryStart, this is
   * handled in AddNonFdRegions().
   */

  /*
   * Get the boundary above which PASR feature for DDR should be turned off
   * for off mode charge condition. This is defined in uefiplat.cfg file.
   */
  if (PasrSupportMemoryStart != 0)
  {
   /*
    * Call function to update segements with MemRegionInfo.MemBase > PasrSupportMemoryStart.
    * BuildHobOption should be updated to HobOnlyNoCacheSetting. 
    */
    UpdatePasrDisabledMemoryRegions(EntryCount, &EntryList[0]);
  }

  Status = AddNonFdRegions (EntryCount, &EntryList[0], UefiInfoBlkPtr);
  if (Status != EFI_SUCCESS) {
    ASSERT (Status == EFI_SUCCESS);
    return Status;
  }

  Status = AddFdRegionRemainder (UefiInfoBlkPtr);
  if (Status != EFI_SUCCESS) {
    ASSERT (Status == EFI_SUCCESS);
    return Status;
  }

  Status = AddNonFdRegionRemainder (UefiInfoBlkPtr);
  if (Status != EFI_SUCCESS) {
    ASSERT (Status == EFI_SUCCESS);
    return Status;
  }

  Status = UpdateDynamicMemoryRegions ();
  if (Status != EFI_SUCCESS) {
    ASSERT (Status == EFI_SUCCESS);
    return Status;
  }

  return Status;
}

EFI_STATUS EFIAPI
InitCacheWithMemoryRegions (
  VOID
  )
{
  /* Initialize cache with new memory map */
  if (InitCache (mMemRegions, mNumMemRegions) != EFI_SUCCESS) {
    return EFI_LOAD_ERROR;
  }

  return EFI_SUCCESS;
}

EFI_STATUS EFIAPI
SetFdDep (
  VOID
  )
{
  EFI_STATUS     Status = EFI_UNSUPPORTED;
  MemRegionInfo  MemRegion,StackRegion;
  UINT64         AddrEndOfText;
  UINT64         TextSegmentBase = 0, TextSegmentSize = 0;
  UINT64         NonTextSegmentBase = 0, NonTextSegmentSize = 0;

  /* Look for "UEFI FD" memory region in config file */
  Status = GetMemRegionInfoByName ("UEFI_FD", &MemRegion);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "ERROR: UEFI FD region not present in cfg file !\n"));
    return EFI_UNSUPPORTED;
  }

  AddrEndOfText      = (UINT64)&EndOfText;
  TextSegmentBase    = MemRegion.MemBase;
  TextSegmentSize    = ROUND_TO_PAGE ((AddrEndOfText - MemRegion.MemBase), (SIZE_4KB-1));
  NonTextSegmentBase = ROUND_TO_PAGE (AddrEndOfText, (SIZE_4KB-1));
  NonTextSegmentSize = MemRegion.MemSize - TextSegmentSize;

 /*Arm Spec and CPU team suggests invalidating by MVA(invalidate prticular region) is preferred instead by SetWay(invalidate cache line where that data present).
   So we are replacing Cache invalidation from Setway to MVA(Modified Virtual Address ).In this context, we replaced required area invalidations to MVA, due to stack region
   is not invalidated we are seeing garbage data (execution is jumping to wrong location due to wrong values) in Stack area..So we are explicitly invalidating stack. */


  WriteBackInvalidateDataCacheRange((VOID *)TextSegmentBase, TextSegmentSize);
  WriteBackInvalidateDataCacheRange((VOID *)NonTextSegmentBase, NonTextSegmentSize);
  Status = GetMemRegionInfoByName("UEFI_Stack", &StackRegion);
  if (Status != EFI_SUCCESS)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: UEFI Stack region not present in cfg file !\n"));
    return EFI_UNSUPPORTED;
  }
  WriteBackInvalidateDataCacheRange((VOID *)StackRegion.MemBase, StackRegion.MemSize);

  ArmInvalidateInstructionCache ();

  ArmDisableMmu ();

  /* Set RO for Sec text segment */
  Status = ArmSetMemoryRegionReadOnly (TextSegmentBase, TextSegmentSize);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "RO: 0x%016lx--0x%016lx [Failed]\n", TextSegmentBase, TextSegmentSize));
    return Status;
  }

  /* Set XN for Sec data segment */
  Status = ArmSetMemoryRegionNoExec (NonTextSegmentBase, NonTextSegmentSize);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "XN: 0x%016lx--0x%016lx [Failed]\n", NonTextSegmentBase, NonTextSegmentSize));
    return Status;
  }

  ArmEnableMmu ();

  return Status;
}

STATIC VOID EFIAPI
ParseChipIDConfigParameters (
  UINT8  *Section,
  UINTN  SectionOffset,
  UINT8  *TokenPtrArray[],
  UINTN  MaxTokens
  )
{
  UINTN  ChipIDConfigNum, ChipIDVal;
  UINTN  Index = 0;

  if ((TokenPtrArray[0] == NULL) || (TokenPtrArray[1] == NULL) || (TokenPtrArray[2] == NULL)) {
    return;
  }

  if (ChipIDReg == NULL) {
    /* Find ChipID_RegAddr config item */
    for (Index = 0; Index < ConfigTableEntryCount; Index++) {
      if (AsciiStrCmp (ConfigTable[Index].Key, "ChipID_RegAddr") == 0) {
        break;
      }
    }

    if (Index < ConfigTableEntryCount) {
      ChipIDReg = (UINT32 *)AsciiStrHexToUintn (ConfigTable[Index].Value);
      DEBUG ((EFI_D_INFO, "ChipID_RegAddr = 0x%08x\r\n", ChipIDReg));
    } else {
      DEBUG ((EFI_D_WARN, "ChipID address uninitialized. Could not parse config item\r\n"));
      return;
    }
  }

  ChipIDConfigNum = AsciiStrHexToUintn ((CHAR8 *)TokenPtrArray[0]);
  ChipIDVal       = *ChipIDReg;
  ChipIDVal       = ((HW_REVNUM_REG_PARTNUM_BMASK & ChipIDVal) >> HW_REVNUM_REG_PARTNUM_SHIFT);

  /* Check if ChipID matches */
  if (ChipIDConfigNum == ChipIDVal) {
    /* Find existing config item */
    for (Index = 0; Index < ConfigTableEntryCount; Index++) {
      if (AsciiStrCmp (ConfigTable[Index].Key, (CHAR8 *)TokenPtrArray[1]) == 0) {
        break;
      }
    }

    if (Index < ConfigTableEntryCount) {
      /* replace existing item */
      ConfigTable[Index].Value = AllocMemNoFree (AsciiStrLen ((CHAR8 *)TokenPtrArray[2])+1);
      AsciiStrCpyS (ConfigTable[Index].Value, AsciiStrLen ((CHAR8 *)TokenPtrArray[2])+1, (CHAR8 *)TokenPtrArray[2]);
    }
  }
}

EFI_STATUS
EFIAPI
LoadAndParsePlatformCfg (
  VOID
  )
{
  EFI_STATUS  Status;
  INTN        MemParserDesc = 0;
  UINT8       *CfgBuffer    = NULL;
  UINTN       FileSize      = 0;
  UINT32      MemParseSt = 0, MemParseEnd = 0,
              RegParseSt = 0, RegParseEnd = 0;
  
  InitGlobals ();

  Status = LoadFileFromFV0 (UEFIPLATCFG_FILE, &CfgBuffer, &FileSize);

  if (EFI_ERROR (Status) || (CfgBuffer == NULL) || (FileSize == 0)) {
    Status = EFI_LOAD_ERROR;
    goto ErrorExit;
  }

  MemParserDesc = OpenParser (CfgBuffer, FileSize, NULL);
  if (MemParserDesc < 0) {
    Status = EFI_LOAD_ERROR;
    goto ErrorExit;
  }

  /* Reset Global for RAM load */
  mMemRegions    = NULL;
  mNumMemRegions = 0;

  MemParseSt = GetTimerCountms();
  Status = ParseMemoryMapEntriesFromDT();
  MemParseEnd = GetTimerCountms();
  if(Status) {
    Status = EFI_LOAD_ERROR;
    goto ErrorExit;
  }  
  
  NumMemoryMapRegion = mNumMemRegions;

  GetCfgMemMapBounds ();

  // UpdateSystemMemoryRegions();

  RegParseSt = GetTimerCountms();
  Status = ParseRegisterMapEntriesFromDT();
  RegParseEnd = GetTimerCountms();
  if(Status) {
    Status = EFI_LOAD_ERROR;
    goto ErrorExit;
  }  

  CheckOverlap();

  MemParserDesc = ReopenParser (MemParserDesc);
  if (MemParserDesc < 0) {
    Status = EFI_LOAD_ERROR;
    goto ErrorExit;
  }

  /* Reset for RAM load */
  ConfigTable           = NULL;
  ConfigTableEntryCount = 0;
  if (EnumKeyValues (MemParserDesc, (UINT8 *)"ConfigParameters", ParseConfigParameters) < 0) {
    Status = EFI_LOAD_ERROR;
    goto ErrorExit;
  }

  MemParserDesc = ReopenParser (MemParserDesc);
  if (MemParserDesc < 0) {
    Status = EFI_LOAD_ERROR;
    goto ErrorExit;
  }

  if (EnumCommaDelimSectionItems (MemParserDesc, (UINT8 *)"ChipIDConfig", ParseChipIDConfigParameters) < 0) {
    Status = EFI_LOAD_ERROR;
    goto ErrorExit;
  }

  CloseParser (MemParserDesc);

  DEBUG ((DT_PERF, " ParseMemoryMapEntriesFromDT    [%3d] ms\n", (MemParseEnd - MemParseSt)));
  DEBUG ((DT_PERF, " ParseRegisterMapEntriesFromDT  [%3d] ms\n", (RegParseEnd - RegParseSt)));

  return EFI_SUCCESS;

ErrorExit:
  DEBUG ((EFI_D_ERROR, "Failed LoadAndParsePlatformCfg\r\n"));
  CpuDeadLoop ();
  return Status;
}

/* Gets the Memory Map that was parsed from the platform cfg file */
EFI_STATUS EFIAPI
GetMemRegionCfgInfo (
  MemRegionInfo  **MemoryRegions,
  UINTN          *NumMemoryRegions
  )
{
  if ((MemoryRegions == NULL) || (NumMemoryRegions == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  *MemoryRegions    = mMemRegions;
  *NumMemoryRegions = mNumMemRegions;

  return EFI_SUCCESS;
}

/* Gets the configuration parameters parsed from config file */
EFI_STATUS EFIAPI
GetConfigTable (
  ConfigPair  **ConfigTblPtr,
  UINTN       *ConfigCnt
  )
{
  if ((ConfigTblPtr == NULL) || (ConfigCnt == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  *ConfigTblPtr = ConfigTable;
  *ConfigCnt    = ConfigTableEntryCount;

  return EFI_SUCCESS;
}

/* Check if there is a region defined in uefiplat that overlaps with a hole in rampartition table */

/*********************************************************************************************
  Ram Partition 1        Ram Partition 2                                 Ram Partition 3
  -------------        --------------------------------                -------------------------

Mem Region 1              2    3     4           5              6               7                  8
      -----             ----- ----- -----     --------       --------------    ------          --------------
      No Overlap           No Overlap         No Overlap       Overlap         No Overlap       Overlap

************************************************************************************************/
EFI_STATUS EFIAPI
ValidateParsedMemoryRegions (
  )
{
  MemRegionInfo  RamPartTableEntry[RAM_NUM_PART_ENTRIES];
  UINTN          RamPartTableEntryCount = RAM_NUM_PART_ENTRIES;
  UINT8          NoOverlap              = 0;
  EFI_STATUS     Status;

  Status = GetRamPartitions (&RamPartTableEntryCount, &RamPartTableEntry[0]);
  if (Status != EFI_SUCCESS) {
    ASSERT (Status == EFI_SUCCESS);
    return Status;
  }

  /*
   * Get the boundary above which PASR feature for DDR should be turned off
   * for off mode charge condition.
   */
  PasrSupportMemoryStart  = FixedPcdGet64(PcdPasrSupportMemoryStart);

  for (UINT32 j = 0; j < NumMemoryMapRegion; j++) {
    NoOverlap = 0;

    /* This first cond added for the hole that is carved out in uefiplat.cfg for converting it to Conventional Memory
           and NoMap is not needed to be checked for overlap in RamPartitionTable */
    if ((mMemRegions[j].BuildHobOption == AddDynamicMem) || (mMemRegions[j].BuildHobOption == NoMap)) {
      continue;
    }

    /*
     * Test whether the memory segements are exceeding PasrSupportMemoryStart limit
     */
    if((PasrSupportMemoryStart != 0) &&
       ((mMemRegions[j].MemBase > PasrSupportMemoryStart) ||
	     ((mMemRegions[j].MemBase + mMemRegions[j].MemSize) > PasrSupportMemoryStart)))
    {
      DEBUG((EFI_D_ERROR, "ValidateParsedMemoryRegions:Memory Segment %s has exceeds PasrSupportMemory limit(0x%lx).\n",
                             mMemRegions[j].Name, PasrSupportMemoryStart));
    }

    for (UINT32 i = 0; i < RamPartTableEntryCount; i++) {
      if ((mMemRegions[j].MemBase >= RamPartTableEntry[i].MemBase) &&
          ((mMemRegions[j].MemBase +  mMemRegions[j].MemSize-1) >= RamPartTableEntry[i].MemBase) &&
          (mMemRegions[j].MemBase < (RamPartTableEntry[i].MemBase + RamPartTableEntry[i].MemSize)) &&
          ((mMemRegions[j].MemBase + mMemRegions[j].MemSize-1) < (RamPartTableEntry[i].MemBase + RamPartTableEntry[i].MemSize))
          )
      {
        /* The region lies in the usable rampartition table range and there is no overlap in the hole region defined by RamPartition table*/
        NoOverlap = 1;
        break;
      }
    }

    if (NoOverlap != 1) {
      DEBUG ((EFI_D_ERROR, "Memory region %s carved out in a hole defined by RAM partition table !\n", mMemRegions[j].Name));
      return EFI_INVALID_PARAMETER;
    }
  }

  return EFI_SUCCESS;
}
