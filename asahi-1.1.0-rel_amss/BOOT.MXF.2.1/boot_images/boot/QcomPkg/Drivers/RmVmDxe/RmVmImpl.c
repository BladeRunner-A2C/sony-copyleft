/**
  @file RmVmImpl.c

  Helper to Implement UEFI Protocol Interface to Gunyah's Resource Manager

  Copyright (c) 2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
**/

/*=============================================================================
                              EDIT HISTORY


when         who      what, where, why
--------   -------    ---------------------------------------------------------
09/06/23   ss       Moving GynhMsgQueueRecieveAsminside loop to improve KPI
04/25/23   kedara   Increase response wait time to ensure msg delivery
04/03/23   kedara   Fix KW errors
02/10/23   kedara   Initial revision
=============================================================================*/


#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIRmVm.h>
#include "RmVmDefsInternal.h"

#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/QcomLib.h>

#include <Protocol/EFIScm.h>
#include <scm_sip_interface.h>

#include <Library/HypDtbo.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DxeServicesTableLib.h>

#include <libfdt.h>
#include <Library/DTBExtnLib.h>
#include <Library/boot_shared_imem_cookie.h>


//-- For Debug --
//#ifdef EFI_D_INFO
//#undef EFI_D_INFO
//#define EFI_D_INFO EFI_D_ERROR
//#endif

extern EFI_STATUS GynhMsgQueueSendAsm (UINT64 MsgQCapID, UINT64 BuffSize,
                                       UINT64 BuffAddr, UINT64 MsgQSendFlags,
                                       UINT64 MsgQResv, UINT64 *Result0, UINT64 *Result1);
                                       
extern EFI_STATUS GynhMsgQueueReceiveAsm (UINT64 MsgQCapID, UINT64 BuffAddr,
                                          UINT64 MaxBuffSize, UINT64 MsgQResv,
                                          UINT64 *Result0, UINT64 *Result1);

#define CAPID_SIZE_BYTES    16
UINT64* CapIdProp = NULL;

//####################################################################################################################
// Hyp DTBO APIs
//####################################################################################################################

/**
  Make ScmSip call and Retrive HypBootInfo.

  Make ScmSip Call to Hyp and retrive and HypBootInfo and map 
  the region into UEFI Page tables.

  @param  pHypBootInfo         Pointer to HypBootInfo Pointer  

  @retval EFI_SUCCESS          RmDtbo Initalised successfully.
  @retval EFI_LOAD_ERROR       Unable to retrive GetHypBootInfo.
**/

STATIC
EFI_STATUS GetHypBootInfo(
  IN HypBootInfoStruct** pHypBootInfo
  )
{
  UINT64 Param[SCM_MAX_NUM_PARAMETERS] = {0};
  UINT64 Results[SCM_MAX_NUM_RESULTS] = {0}; 
  EFI_STATUS Status;
  QCOM_SCM_PROTOCOL *pScmProtocol = 0;  
  Status = gBS->LocateProtocol (&gQcomScmProtocolGuid, 
                                NULL,
                                (VOID**)&pScmProtocol);
  if(Status){
    DEBUG ((EFI_D_ERROR, "Failed to Locate Scm Protocol : %d\n", Status));
    return EFI_LOAD_ERROR;    
  }
  
  Status = pScmProtocol->ScmSipSysCall (pScmProtocol,
                                        HYP_GET_BOOT_INFO_STRUCT, 
                                        HYP_GET_BOOT_INFO_STRUCT_ID_PARAM_ID,
                                        Param,
                                        Results);
  if(Status){
    DEBUG(( EFI_D_ERROR, "ScmSipSysCall() failed, Status = (0x%x)\r\n", Status));
    return EFI_LOAD_ERROR;    
  }
  
  *pHypBootInfo = (HypBootInfoStruct*)Results[1];                                              
  
  Status = gDS->AddMemorySpace (EfiGcdMemoryTypeReserved,
                                (EFI_PHYSICAL_ADDRESS)*pHypBootInfo,
                                SIZE_4KB,
                                EFI_MEMORY_WB);
  if(Status){
    DEBUG(( EFI_D_ERROR, "AddMemorySpace failed, Status = (0x%x)\r\n", Status));
    return EFI_LOAD_ERROR;    
  }
 
  Status = gDS->SetMemorySpaceAttributes ((EFI_PHYSICAL_ADDRESS)*pHypBootInfo,
                                          SIZE_4KB,
                                          EFI_MEMORY_WB);
 
  if(Status){
    DEBUG(( EFI_D_ERROR, "SetMemorySpaceAttributes failed, Status = (0x%x)\r\n", Status));
    return EFI_LOAD_ERROR;    
  }                                          
  
  return EFI_SUCCESS;    
}

/**
  Parse HypBootInfo and retrive RmDtbo Info.

  This function parses the HypBootInfo structure and retrives the 
  RmDtbo Information.

  @param  pHypBootInfo         Pointer to HypBootInfo Pointer  
  @param  RmDtboInfo           Pointer to a DtboInfo structure
                               containing RmDtbo Info 

  @retval EFI_SUCCESS          RmDtbo Initalised successfully.
  @retval EFI_LOAD_ERROR       Unable to Retrive RmDtbo Info.
**/

STATIC
EFI_STATUS GetRmDtboInfo(
  IN HypBootInfoStruct* pHypBootInfo,
  OUT DtboInfoStruct* RmDtboInfo
  )
{
  UINT64 HypDtboBaseAddress = 0;
  UINT64 HypDtboSize = 0;
  
  if(pHypBootInfo->HypBootInfoMagic != HYP_BOOTINFO_MAGIC){
    DEBUG(( EFI_D_ERROR, "Hyp Boot Info Magic Cookie Invalid\r\n"));
    return EFI_LOAD_ERROR;     
  }
  
  if(pHypBootInfo->HlosInfo.NumDtbos != 2){
    DEBUG(( EFI_D_INFO, "Error: Hyp Boot Info must have 2 DTBOs. Hyp Image mismatch\r\n"));
    return EFI_LOAD_ERROR;     
  }
  
  HypDtboBaseAddress = pHypBootInfo->HlosInfo.Info.LinuxAarch64[RMVM_DTBO].DtboBase;
  HypDtboSize = pHypBootInfo->HlosInfo.Info.LinuxAarch64[RMVM_DTBO].DtboSize;
  RmDtboInfo->DtboAddress = (UINT64)AllocateZeroPool(HypDtboSize);
  if (RmDtboInfo->DtboAddress == (UINT64) NULL)
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] Could not allocate memory for DtboAddress Buffer.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  RmDtboInfo->DtboSize = HypDtboSize;
 
  CopyMem((VOID*)RmDtboInfo->DtboAddress, (VOID*)HypDtboBaseAddress, HypDtboSize);
  
  return EFI_SUCCESS;  
}

/**
  Merge RmDtbo Passed by Gunyah and retrive CapId Info into CapIdProp.

  This function  merges the RmDtbo region with Boot DT and retrives
  can stores RM Messege queue CapId in CapIdProp.
  
  @param  RmDtboInfo           Pointer to a DtboInfo structure
                               containing RmDtbo Info 

  @retval EFI_SUCCESS          RmDtbo Initalised successfully.
  @retval EFI_LOAD_ERROR       Unable to Merge DT and retrive CapId.
**/

STATIC
EFI_STATUS MergeRmDtbo(
  IN DtboInfoStruct* RmDtboInfo
  )
{
  EFI_STATUS Status;
  struct boot_shared_imem_cookie_type  *BootSharedImemCookiePtr = NULL;
  
  BootSharedImemCookiePtr = (struct boot_shared_imem_cookie_type *)((UINT64)PcdGet32 (PcdIMemCookiesBase));
  ASSERT (BootSharedImemCookiePtr != NULL);
  
  CONST VOID* DTBBlob   = NULL;
  UINT32      BlobSize  = 0;
  UINT32      MergeSize = 0; 

  DTBBlob   = (VOID *)BootSharedImemCookiePtr->boot_devtree_addr;
  BlobSize  = BootSharedImemCookiePtr->boot_devtree_size;
  MergeSize = BlobSize + RmDtboInfo->DtboSize;
   
  Status = fdt_merge_overlay(DTBBlob,BlobSize,(VOID*)RmDtboInfo->DtboAddress,RmDtboInfo->DtboSize,(VOID*)DTBBlob,MergeSize);
  if(Status){
    DEBUG ((EFI_D_ERROR, "Merge Overlay: %d\n", Status));
    return EFI_LOAD_ERROR;
  }
  
  Status = fdt_check_for_valid_blob(DTBBlob, MergeSize);
  if(Status){
    DEBUG ((EFI_D_ERROR, "fdt_check_for_valid_blob: %d\n", Status));
    return EFI_LOAD_ERROR;
  }
  
  Status = fdt_set_blob_handle(DTBBlob, MergeSize, 0);
  if(Status){
    DEBUG ((EFI_D_ERROR, "fdt_set_blob_handle: %d\n", Status));
    return EFI_LOAD_ERROR;
  }

  fdt_node_handle Node;
  
  Status = fdt_get_node_handle(&Node, DTBBlob, "/hypervisor/qcom,resource-manager-rpc");
  if(Status){
    DEBUG ((EFI_D_ERROR, "fdt_get_node_handle: %d\n", Status));
    return EFI_LOAD_ERROR;
  }
  
  CapIdProp = AllocateZeroPool(CAPID_SIZE_BYTES);
  if (CapIdProp == NULL)
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] Could not allocate memory for CapIdProp.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = fdt_get_uint64_prop_list(&Node,"reg", CapIdProp, CAPID_SIZE_BYTES);
    if(Status){
    DEBUG ((EFI_D_ERROR, "fdt_get_uint64_prop_list: %d\n", Status));
    FreePool(CapIdProp);
    return EFI_LOAD_ERROR;
  }
    
  return EFI_SUCCESS;
}


/**
  Merge RmDtbo Passed by Gunyah and retrive CapId Info into CapIdProp.

  This function makes an ScmSip call to hypervisor to fetch the
  HypBootInfo structure and merges the RmDtbo region with Boot DT.


  @retval EFI_SUCCESS          RmDtbo Initalised successfully.
  @retval EFI_LOAD_ERROR       Merging DTBO and retriving CapId failed.
**/

EFI_STATUS
InitRmDtbo (VOID)
{
  EFI_STATUS Status;
  HypBootInfoStruct* pHypBootInfo = NULL;
  DtboInfoStruct RmDtboInfo = {0};
  Status = GetHypBootInfo (&pHypBootInfo);
  if(Status){
    DEBUG ((EFI_D_ERROR, "GetHypBootInfo Status: %d\n", Status));
    return EFI_LOAD_ERROR;         
  }
  
  Status = GetRmDtboInfo (pHypBootInfo, &RmDtboInfo);
  if(Status){
    DEBUG ((EFI_D_INFO, "GetRmDtboInfo Status: %d\n", Status));
    return EFI_LOAD_ERROR;         
  }
  
  Status = MergeRmDtbo (&RmDtboInfo);
  if(Status){
    DEBUG ((EFI_D_ERROR, "MergeRmDtbo Status: %d\n", Status));
    return EFI_LOAD_ERROR;         
  }
  return EFI_SUCCESS;
}

//####################################################################################################################
// Getter API for CapId
//####################################################################################################################
UINT64* GetCapId (VOID)
{
  return CapIdProp;
}

//####################################################################################################################
// Gunyah Messege Queue APIs
//####################################################################################################################

#define RM_ASM_MAX_NUM_RESULTS 4
  UINT64  ResultsSend[RM_ASM_MAX_NUM_RESULTS];
  UINT64  ResultsRecv[RM_ASM_MAX_NUM_RESULTS];

EFI_STATUS GynhMsgQueueSend(UINT64 MsgQCapID, UINT64 BuffSize, UINT64 BuffAddr, UINT64 MsgQSendFlags, UINT64 MsgQResv)
{
  ResultsSend[0] = 0xAFAF;
  ResultsSend[1] = 0xAFAF;
  
  GynhMsgQueueSendAsm (MsgQCapID, BuffSize, BuffAddr, MsgQSendFlags, MsgQResv, &ResultsSend[0], &ResultsSend[1]);
  DEBUG((EFI_D_INFO, "MsgQ Send Resp Reg x1 = 0x%x \r\n", ResultsSend[1] ));
  
  return ResultsSend[0];
}

#define MSGQ_LOOP_ITER        20
#define MSGQ_STALL_MICROSEC   1000

EFI_STATUS GynhMsgQueueReceive(UINT64 MsgQCapID, UINT64 BuffAddr, UINT64 MaxBuffSize, UINT64 MsgQResv)
{
  ResultsRecv[0] = 0xAFAF;
  ResultsRecv[1] = 0xAFAF;
  
  for(int i = 0;i < MSGQ_LOOP_ITER; i++)
  {
	  GynhMsgQueueReceiveAsm (MsgQCapID, BuffAddr, MaxBuffSize, MsgQResv, &ResultsRecv[0], &ResultsRecv[1]);
	  if(ResultsRecv[0] == 0){
	  	DEBUG((EFI_D_INFO, "MsgQ Recv Resp Reg x1 = 0x%x \r\n", ResultsRecv[1] ));
		break;
	  }
	  else{
	  	gBS->Stall(MSGQ_STALL_MICROSEC);
	  }
  }
 
  return ResultsRecv[0];
}


//####################################################################################################################
// Entry API
//####################################################################################################################

/**
  The user code starts with this function as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI 
GhComInitialize (VOID)
{
  EFI_STATUS  Status;
   
  Status = InitRmDtbo ();
  return Status;
}



