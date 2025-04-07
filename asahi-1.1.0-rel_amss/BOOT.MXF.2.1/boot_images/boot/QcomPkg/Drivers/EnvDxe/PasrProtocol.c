/** @file
                    PasrProtocol.c

  Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 05/09/23    sree    Add partition  length check while setting memory attribute
 04/10/23    rk      Added Remap Event related changes
 02/15/23    rk      initial version
=============================================================================*/

#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIDDRGetConfig.h>
#include <Protocol/EFIPasr.h>
#include <Protocol/EFIRamPartition.h>
#include <Library/MemoryAllocationLib.h>
#include <ArmMmuLibEfiAttributesMap.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/ArmMmuLib.h>

#define NUM_OF_BLOCKS   0x01    /* Number of blocks to be configured for PASR feature*/
#define KB              (1024UL)
#define MB              (1024UL*1024UL)
#define GB              (1024UL*1024UL*1024UL)

/*Event for signalling*/
VOID       *PasrProtocolNotificationToken  = NULL;
EFI_EVENT  PasrProtocolNotificationEvent   = (EFI_EVENT)NULL;

VOID       *RemapEventNotificationToken   = NULL;
EFI_EVENT  RemapEventNotificationEvent    = (EFI_EVENT)NULL;

/* Event Guids*/
extern EFI_GUID  gEfiRemapEventGuid;

STATIC UINT64      PasrSupportMemoryStart = 0;
/**
  This function is the callback handler for Pasr protocol notification.
  As part of this callback , firmware will call EFI_PasrConfig().

  @param    Event   Pointer to this event
  @param    Context Event handler private data
 **/

VOID
EFIAPI
PasrProtocolEnabledCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS              Status               = EFI_NOT_STARTED;
  EFI_PASR_PROTOCOL       *EfiPasrProtocol     = NULL;
  PASR_BLOCK              PasrEnableBlock;
  EFI_STATUS              DdrInfoStatus        = EFI_NOT_FOUND;
  DDR_REGIONS_ENTRY       DdrRegionsInfo;
  UINTN                   i = 0;
  EFI_DDRGETINFO_PROTOCOL *pDDRGetInfoProtocol = NULL;

  DdrInfoStatus = gBS->LocateProtocol(&gEfiDDRGetInfoProtocolGuid, NULL, (VOID**)&pDDRGetInfoProtocol);
  if (EFI_ERROR(DdrInfoStatus) || (NULL == &pDDRGetInfoProtocol))
  {
    DEBUG((EFI_D_ERROR, "Locate EFI_DDRGETINFO_PROTOCOL failed, Status = (0x%x)\n", DdrInfoStatus));
    return;
  }

  DdrInfoStatus = pDDRGetInfoProtocol->GetDDRMappedRegions(pDDRGetInfoProtocol, &DdrRegionsInfo);
  if (EFI_ERROR (DdrInfoStatus))
  {
    DEBUG((EFI_D_WARN, "Failed to get DDR Regions Data, Status = (0x%x)\n", DdrInfoStatus));
    return;
  }

  /*
   * Get the boundary above which PASR feature for DDR should be turned off
   * for off mode charge condition.
   */
  PasrSupportMemoryStart  = FixedPcdGet64(PcdPasrSupportMemoryStart);

  /*
   * If PasrSupportMemoryStart == 0, then either this value is not being read from PCD file
   * or this feature is not enabled for this target. In either of this case Pasr mode should not
   * be enabled/configured.
   */
  if (PasrSupportMemoryStart == 0)
  {
    DEBUG((EFI_D_INFO, "PasrProtocolEnabledCallback: Either Pasr feature is disabled or cannot read PasrSupportMemoryStart.\n"));
    return;
  }
  // PasrSupportMemoryStart is nonzero. Proceed to configure Pasr.
  Status = gBS->LocateProtocol( &gEfiPasrProtocolGuid, NULL, (VOID **)&EfiPasrProtocol);
  if((EFI_SUCCESS != EFI_SUCCESS) || (NULL == EfiPasrProtocol))
  {
    DEBUG((EFI_D_ERROR,"PasrDxe protocol cannot be located with error 0x%x.\n",Status));
    return;
  }

  /*
  * Total DDR size is returned in DDR_REGIONS_ENTRY via ddr_rank0/1_size.
  * ddr_rank0/1_size returns size in MB. Hence to calculate actual size
  * multiple by "MB" i.e. (1024*1024) to get size in bytes.
  * For calculating the size of segment for PASR disablement,
  * substract "PasrStartMemoryStart" from the total size.
  * PasrStartMemoryStart is a configurable parameter which defines the memory
  * address above which PASR feature is eanbled. The memory below this address
  * should not disabled. The memory below "PasrStartMemoryStart" is used for 
  * running uefi images.
  */
  PasrEnableBlock.Size = (((DdrRegionsInfo.ddr_rank0_size + DdrRegionsInfo.ddr_rank1_size) * (MB)) 
                        - (PasrSupportMemoryStart));
  /*
  * To get the start address for the memory segment for which PASR should be
  * enbaled , DDR_REGIONS_ENTRY -> DDR_REGIONS_STRUCT_ENTRY should be parsed.
  * Segments which have start_address > PasrSupportMemoryStart should be 
  * configured for Pasr. Hence parse DDR_REGIONS_ENTRY -> DDR_REGIONS_STRUCT_ENTRY
  * for such memory segments.
  */
  for(i = 0; i < MAX_DDR_REGIONS; i++)
  {
    /*
    * If for this ddr_region->start_address > PasrSupportMemoryStart, then
    * this segment should be configured for Pasr feature.
    */
    if(DdrRegionsInfo.ddr_region[i].start_address > PasrSupportMemoryStart)
    {
      PasrEnableBlock.Address = DdrRegionsInfo.ddr_region[i].start_address;
      DEBUG((EFI_D_INFO,"PASR condition met for ddr_region[%d].start_address = 0x%lx.\n",
                          i, DdrRegionsInfo.ddr_region[i].start_address));
      //Segement exceeding PasrSupportMemoryStart limit found. Break the loop.
      break;
    }
    
  }
  /*
    * Call PASRConfig for the current segment which has exceeded the
    * "PasrSupportMemoryStart" threshold. PasrEnableBlock has the 
    * required information for this segment.
    */
  Status = EfiPasrProtocol->PASRConfig(EfiPasrProtocol, NUM_OF_BLOCKS, &PasrEnableBlock);
  if(Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_ERROR,"PasrDxe config failed. Status = 0x%x.\n", Status));
  }
  return;
}

/**
  This function is the callback handler for remap event notification.
  Remap event is striggered by chargerDxe to indicate that Pasr feature
  is not to be activated.
  As part of this callback, firmware will remap memory segments which were
  considered to be candidates for Pasr feature. And their memory attributes
  were not set up for normal use.

  @param    Event   Pointer to this event
  @param    Context Event handler private data
 **/

VOID
EFIAPI
RemapEventNotifyCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_RAMPARTITION_PROTOCOL *pRamPartProtocol      = NULL;
  RamPartitionEntry         *pRamPartitions        = NULL;
  UINT32                    NumPartitions          = 0;
  UINT64                    PasrSupportMemoryStart = FixedPcdGet64(PcdPasrSupportMemoryStart);
  EFI_STATUS                Status                 = EFI_NOT_STARTED;
  UINTN                     i                      = 0;
  if ((!EFI_ERROR(gBS->LocateProtocol(&gEfiRamPartitionProtocolGuid, NULL, (VOID**)&pRamPartProtocol))) &&
    (&pRamPartProtocol != NULL))
  {
    //Get RAM partitions.
    Status = pRamPartProtocol->GetRamPartitions (pRamPartProtocol, NULL, &NumPartitions);
    if (Status == EFI_BUFFER_TOO_SMALL)
    {
      pRamPartitions = AllocatePool (NumPartitions * sizeof (RamPartitionEntry));

      if ((pRamPartitions != NULL) &&
        (!EFI_ERROR (pRamPartProtocol->GetRamPartitions (pRamPartProtocol, pRamPartitions, &NumPartitions))) &&
        (NumPartitions >= 1))                      
      {
        for(i = 0; i < NumPartitions; i++)
        {
          //For memory segements exceeding PasrSupportMemoryStart, remap them.
          if((pRamPartitions[i].Base > PasrSupportMemoryStart) ||
            ((pRamPartitions[i].Base + pRamPartitions[i].AvailableLength) > PasrSupportMemoryStart))
          {
            //Setting the memory segment attributes to Write Back (Xn).
            if(pRamPartitions[i].AvailableLength != 0)
            	Status = ArmSetMemoryAttributes(pRamPartitions[i].Base, pRamPartitions[i].AvailableLength, EFI_ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN);
            //TODO:Invalidate cache for the memory segments with ArmCleanInvalidateDataCacheEntryByMVA. Increased boot time. Disabled
            //InvalidateDataCacheRange((VOID*) pRamPartitions[i].Base, pRamPartitions[i].AvailableLength);
          }
        }
      }
      else
      {
        DEBUG ((EFI_D_WARN, "RemapEventNotifyCallback:AllocatePool or GetRampartition failed\n"));
      }

      //Free up the allocated pages.
      if (pRamPartitions != NULL) 
      {
        FreePool(pRamPartitions);
      }
    }
  }
  else
  {
    DEBUG ((EFI_D_WARN, "RemapEventNotifyCallback:Cannot process remap event callback\n"));
  }
  Status = gBS->CloseEvent (RemapEventNotificationEvent);
}

/**
 Register callback for PASR Protocol notification
*/

EFI_STATUS
RegisterPasrProtocol (
  VOID
  )
{
  EFI_STATUS  Status = EFI_NOT_STARTED;

  // Set up to be notified when the Pasr protocol is installed.
  Status = gBS->CreateEvent (EVT_NOTIFY_SIGNAL, TPL_CALLBACK, PasrProtocolEnabledCallback, NULL, &PasrProtocolNotificationEvent);
  ASSERT_EFI_ERROR (Status);

  Status = gBS->RegisterProtocolNotify (&gEfiPasrProtocolGuid, PasrProtocolNotificationEvent, (VOID *)&PasrProtocolNotificationToken);
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
 Register for remap event notification
*/
EFI_STATUS
RegisterRemapEvent(
  VOID
  )
{
  EFI_STATUS  Status = EFI_NOT_STARTED;
  // Set up to be notified when remap event is triggered by chargerDxe.
  Status = gBS->CreateEventEx (EVT_NOTIFY_SIGNAL, TPL_CALLBACK, RemapEventNotifyCallback, NULL, &gEfiRemapEventGuid, &RemapEventNotificationEvent);
  return Status;
}
