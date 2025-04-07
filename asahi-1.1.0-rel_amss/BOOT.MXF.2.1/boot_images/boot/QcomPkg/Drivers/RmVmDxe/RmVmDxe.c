/**
  @file RmVmDxe.c

  Implementation of a UEFI Protocol Interface to Gunyah's Resource Manager

  Copyright (c) 2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
**/

/*=============================================================================
                              EDIT HISTORY


when         who      what, where, why
--------   -------    ---------------------------------------------------------
04/21/23   kedara   hyp assign vmid updates, fix message size calc, update checks
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
#include <Library/MemoryAllocationLib.h>

#include <Library/UncachedMemoryAllocationLib.h>
#include <scm_sip_interface.h>
#include <Protocol/EFIScm.h>
#include <Library/BaseMemoryLib.h>

#define ACL_ENTRIES 1

#define MEM_SHARE_RM_VMID             255
#define HYP_ASSIGN_RESV_VMID           58
#define HYP_ASSIGN_RM_VMID             61
#define MAX_HYP_ASSIGN_VMID_CAP       128

//-- For Debug --
//#ifdef  EFI_D_INFO
//#undef  EFI_D_INFO
//#define EFI_D_INFO EFI_D_ERROR
//#endif

extern UINT64* CapIdProp;
extern EFI_STATUS GynhMsgQueueSend(UINT64 MsgQCapID,UINT64 BuffSize,UINT64 BuffAddr,UINT64 MsgQSendFlags,UINT64 MsgQResv);
extern EFI_STATUS GynhMsgQueueReceive(UINT64 MsgQCapID, UINT64 BuffAddr, UINT64 MaxBuffSize, UINT64 MsgQResv);
extern EFI_STATUS GhComInitialize (VOID);

// Sequence number tracker for messages
UINT16 gSeqNo = 0;

EFI_STATUS
PrintRmVmHeader (VOID* RmVmHdrBuffer)
{
  RmMsgHeader *RmHdrPtr = NULL;
  
  if(RmVmHdrBuffer == NULL )
  {
    DEBUG((EFI_D_ERROR, "PrintRmVmHeader: NULL Params passed\n"));
    return EFI_INVALID_PARAMETER;
  }
  
  RmHdrPtr = (RmMsgHeader *)RmVmHdrBuffer;
  
  DEBUG ((EFI_D_INFO, "RmHeader Version:      0x%x\r\n", RmHdrPtr->Version ));
  DEBUG ((EFI_D_INFO, "RmHeader HeaderWords:  0x%x\r\n", RmHdrPtr->HeaderWords ));
  DEBUG ((EFI_D_INFO, "RmHeader MessageType:  0x%x\r\n", RmHdrPtr->MessageType ));
  DEBUG ((EFI_D_INFO, "RmHeader Fragments:    0x%x\r\n", RmHdrPtr->Fragments ));
  DEBUG ((EFI_D_INFO, "RmHeader SeqNo:        0x%x\r\n", RmHdrPtr->SeqNo ));
  DEBUG ((EFI_D_INFO, "RmHeader MessageId:    0x%x\r\n", RmHdrPtr->MessageId ));
  
  return EFI_SUCCESS;
}

/**
  Generate RM Message Header for input buffer.

**/
EFI_STATUS
FormatRmVmHeader (VOID* RmVmHdrBuffer, UINT32 MessageId, UINT32 *HeaderSize)
{
  RmMsgHeader *RmHdrPtr = NULL;
  
  if(RmVmHdrBuffer == NULL || HeaderSize == NULL )
  {
    DEBUG((EFI_D_ERROR, "FormatRmVmHeader: NULL Params passed\n"));
    return EFI_INVALID_PARAMETER;
  }
  
  RmHdrPtr = (RmMsgHeader *)RmVmHdrBuffer;
  
  RmHdrPtr->Version     = RM_HEADER_API_VERSION;
  RmHdrPtr->HeaderWords = RM_HEADER_WORDS;
  RmHdrPtr->MessageType = RM_HEADER_MESSAGE_TYPE_REQ;
  RmHdrPtr->SeqNo       = gSeqNo++;
  RmHdrPtr->MessageId   = MessageId;
  
  *HeaderSize = sizeof (RmMsgHeader);
  
  return EFI_SUCCESS;
}

/* ============================================================================
**  Function : EFI_RM_VM_GET_ID
** ============================================================================
*/
/** @ingroup efi_rm_vm_get_id
  @par Summary
  Call into Resource Manager to get VM's identification 

  @param[in]      This               Pointer to the EFI_RMVM_PROTOCOL instance.
  @param[in]      VmID               VmID to query
  @param[OUT]     DataBuff           Data buffer with response
  @param[OUT]     DataBuffSize       Buffer size

  @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_NOT_READY         -- Protocol Dependencies not satisfied. \n
*/

EFI_STATUS
EFIAPI EFI_VmGetID(
   IN  EFI_RMVM_PROTOCOL    *This,
   IN  UINT16               VmID,
   OUT VOID                 **DataBuff,
   OUT UINT32               *DataBuffSize
   )
{
  EFI_STATUS  Status;
  RmHdrAndShortData1 getVmIDMsg = {0};
  UINT32 MessageSize = 0;
  RmStdResp* RxBuffer = NULL;
 
  DEBUG((EFI_D_INFO, "[RmVmDxe]: VmGetID Invoked\n"));
  
  ASSERT (((DataBuff != NULL) && (DataBuffSize != NULL)));

  FormatRmVmHeader (&getVmIDMsg, RM_VM_GET_ID, &MessageSize);

  getVmIDMsg.Data1 = VmID;

  DEBUG ((EFI_D_INFO, "MsgQ Send Buffer:\r\n"));  
  PrintRmVmHeader (&getVmIDMsg);
  
  Status = GynhMsgQueueSend(CapIdProp[0],sizeof(getVmIDMsg), (UINT64)&getVmIDMsg,
                            RM_MESG_QUEUE_SEND_FLAG_PUSH, RM_MESG_QUEUE_RESERVED_FIELD);

  if(Status != EFI_SUCCESS )
  {
    DEBUG((EFI_D_ERROR, "GynhMsgQueueSend error: 0x%x \n", Status));
    return Status;
  }

  *DataBuff = AllocateZeroPool(MAX_RPC_BUFF_SIZE_BYTES);
  if(*DataBuff == NULL)
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] Could not allocate memory for DataBuff.\n"));
    return EFI_OUT_OF_RESOURCES;
  }
  *DataBuffSize = MAX_RPC_BUFF_SIZE_BYTES;
  
  Status = GynhMsgQueueReceive(CapIdProp[1],(UINT64)*DataBuff,MAX_RPC_BUFF_SIZE_BYTES,
                               RM_MESG_QUEUE_RESERVED_FIELD);  

  DEBUG ((EFI_D_INFO, "\nMsgQ Receive Buffer:\r\n"));    
  PrintRmVmHeader (*DataBuff);

  RxBuffer = (RmStdResp*)(*DataBuff);
  if (Status == EFI_SUCCESS && RxBuffer->ErrorCode != RM_STATUS_SUCCESS )
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] VmGetID RM RPC error 0x%x \n", RxBuffer->ErrorCode));
    Status = EFI_INVALID_PARAMETER;
  }
  
  return Status;
}


/* ============================================================================
**  Function : HypAssignMem
** ============================================================================
*/
/** @ingroup HypAssignMem
  @par Summary
  perform SCM call to TZ/HYP to assign permissions to manage access to memory
  buffer by different VMIDs

  @param[in]      AclPtr       List of VMID and permissions.
  @param[in]      SglPtr       List of memory carveouts.
  @param[in]      SrcVmID      Source VMID of memory region.

  @return
  EFI_SUCCESS           -- Function completed successfully, Else error code. \n
*/
EFI_STATUS
EFIAPI HypAssignMem(
  IN  RmMemAcl            *AclPtr,
  IN  RmMemSgl            *SglPtr,
  IN  UINT32              SrcVmID
  )
{
  EFI_STATUS                    Status = EFI_SUCCESS;

  hyp_memprot_assign_t          *pScmParam = NULL;
  hyp_memprot_ipa_info_t        *pIPAinfolist = NULL;
  UINT32                        *pSourceVMlist = NULL, index =0;
  hyp_memprot_dstVM_perm_info_t *pDestVMlist = NULL;
  UINT32                         pDestVMlistSize = 0, pIPAinfolistSize = 0;
  
  // As SCM Expects in/out param
  UINT64                        Parameters[SCM_MAX_NUM_PARAMETERS] = {0};
  UINT64                        Results[SCM_MAX_NUM_RESULTS] = {0};
  
  QCOM_SCM_PROTOCOL             *pQcomScmProtocol = NULL;
  tz_common_rsp_t               *SysCallRsp = (tz_common_rsp_t*)Results;
  
  if(AclPtr == NULL || SglPtr == NULL)
  {
    DEBUG((EFI_D_ERROR, "HypAssignMem: NULL Params passed\n"));
    return EFI_INVALID_PARAMETER;
  }  

  Status = gBS->LocateProtocol(&gQcomScmProtocolGuid, NULL, (void**)&pQcomScmProtocol);
  if ((Status != EFI_SUCCESS) || (pQcomScmProtocol == NULL))
  {
    DEBUG((EFI_D_ERROR, "failed to get QcomScm protocol, Error [0x%x]\n",Status));
    return EFI_NOT_FOUND;
  } 

  // cast the scm parameters to a hyp_memprot_assign_t pointer so its
  // easier and readable to fill up scm arguments.
  pScmParam = (hyp_memprot_assign_t *)&Parameters[0];

  // Set shared buffer address and size
  pIPAinfolistSize = SglPtr->sgl_entries_count * sizeof(hyp_memprot_ipa_info_t);
  pIPAinfolist = UncachedAllocateZeroPool (pIPAinfolistSize);
  if (pIPAinfolist == NULL)
  {
    DEBUG((EFI_D_ERROR, "Error: pIPAinfolist memory alloc failure\n"));       
    goto ErrorExit;
  }
  
  DEBUG ((EFI_D_INFO, "IPAinfolist entries:      %d\r\n", SglPtr->sgl_entries_count ));
  for (index =0; index < SglPtr->sgl_entries_count; index++)
  {
    pIPAinfolist[index].IPAaddr = (SglPtr->SglEntries[index]).BaseAddr;
    pIPAinfolist[index].IPAsize = (SglPtr->SglEntries[index]).Size;
    
    DEBUG ((EFI_D_INFO, "IPAinfolist[%d] IPAaddr:   0x%x\r\n", index, pIPAinfolist[index].IPAaddr));
    DEBUG ((EFI_D_INFO, "IPAinfolist[%d] IPAsize:   0x%x\r\n", index, pIPAinfolist[index].IPAsize));
  }

  // Source VM
  pSourceVMlist = UncachedAllocateZeroPool(sizeof(UINT32));
  if (pSourceVMlist == NULL)
  {
    DEBUG((EFI_D_ERROR, "Error: pSourceVMlist memory alloc failure\n"));
    goto ErrorExit;
  }
  *pSourceVMlist = SrcVmID;
  
  // Set Destination VM info list
  pDestVMlistSize = AclPtr->acl_entries_count *
                   sizeof(hyp_memprot_dstVM_perm_info_t);
  pDestVMlist = UncachedAllocateZeroPool (pDestVMlistSize);
  if (pDestVMlist == NULL)
  {
    DEBUG((EFI_D_ERROR, "Error: pDestVMlist memory alloc failure\n"));
    goto ErrorExit;
  }
  
  DEBUG ((EFI_D_INFO, "\nDestVMlist entries:        %d\r\n", AclPtr->acl_entries_count ));
  for (index =0; index < AclPtr->acl_entries_count; index++)
  {
    /* Re-Map VMID's for hyp_assign similar to HLOS. Hyp assign does not support vmid's greater
       than 128, And all such IDs need to be remapped to specific ID of 58. For RM New ID of
       61 is being allocated for hyp assign.
    */
    if((AclPtr->AclEntries[index]).vmid == MEM_SHARE_RM_VMID)
    {
      pDestVMlist[index].dstVM     = HYP_ASSIGN_RM_VMID;
      DEBUG((EFI_D_INFO, "HypAssignMem: RM DstVM updated to %d \n", HYP_ASSIGN_RM_VMID));      
    }
    else if((AclPtr->AclEntries[index]).vmid >= MAX_HYP_ASSIGN_VMID_CAP)
    {
      pDestVMlist[index].dstVM     = HYP_ASSIGN_RESV_VMID;
      DEBUG((EFI_D_INFO, "HypAssignMem: RM DstVM updated to %d \n", HYP_ASSIGN_RESV_VMID));      
    }
    else
      pDestVMlist[index].dstVM     = (AclPtr->AclEntries[index]).vmid;

    pDestVMlist[index].dstVMperm = (AclPtr->AclEntries[index]).rights;
    
    DEBUG ((EFI_D_INFO, "DestVMlist[%d] dstVM:       0x%x\r\n", index, pDestVMlist[index].dstVM ));
    DEBUG ((EFI_D_INFO, "DestVMlist[%d] dstVMperm:   0x%x\r\n", index, pDestVMlist[index].dstVMperm ));
  }

  // Setup SCM parameters
  pScmParam->IPAinfolist = (UINT64) pIPAinfolist;
  pScmParam->IPAinfolistsize = pIPAinfolistSize;

  pScmParam->sourceVMlist = (UINT64) pSourceVMlist;
  pScmParam->srcVMlistsize = sizeof(UINT32);

  pScmParam->destVMlist = (UINT64) pDestVMlist;
  pScmParam->destVMlistsize = pDestVMlistSize;

  pScmParam->spare = 0;

  // Do the SCM call to TZ/HYP
  SetMem(&Results[0], sizeof(Results),0);
  Status = pQcomScmProtocol->ScmSipSysCall(pQcomScmProtocol,
                                          HYP_MEM_PROTECT_ASSIGN,
                                          HYP_MEM_PROTECT_ASSIGN_PARAM_ID,
                                          Parameters, Results);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "ScmSipSysCall() failed, Error [0x%x]\n", Status));     
    goto ErrorExit;
  }

  if (SysCallRsp->common_rsp.status != 1)
  {
    DEBUG((EFI_D_ERROR, "ScmSipSysCall() failed, common_rsp.status [0x%x]\n", SysCallRsp->common_rsp.status));
    goto ErrorExit;
  }

  if (SysCallRsp->ret != 0)
  {
    DEBUG((EFI_D_ERROR, "ScmSipSysCall() failed, rsp.ret [0x%x]\n", SysCallRsp->ret));
    goto ErrorExit;
  }

  // Free mem allocations
  UncachedFreePool(pScmParam);
  UncachedFreePool(pIPAinfolist);
  UncachedFreePool(pSourceVMlist);
  UncachedFreePool(pDestVMlist);

  return Status;

ErrorExit:
  if (pScmParam)
      UncachedFreePool(pScmParam);
  if (pIPAinfolist)
      UncachedFreePool(pIPAinfolist);
  if (pSourceVMlist)
      UncachedFreePool(pSourceVMlist);
  if (pDestVMlist)
      UncachedFreePool(pDestVMlist);
      
  return EFI_DEVICE_ERROR;    
}


/* ============================================================================
**  Function : MemShare
** ============================================================================
*/
/** @ingroup MemShare
  @par Summary
  Implement memory management operation from one VM to another

  @param[in]      This          Pointer to the EFI_RMVM_PROTOCOL instance.
  @param[in]      MemType       Type of memory parcel, Normal Vs IO.
  @param[in]      Flags         Memparcel flags eg sanitize, finalize bits.
  @param[in]      Label         Value to be used as a label for memparcel
  @param[in]      AclPtr        Pointer to access control vmid list.
  @param[in]      SglPtr        Pointer to scatter gather list for memory regions.
  @param[in]      AttrPtr       Pointer to list of attributes for destn VMIDs.
  @param[in]      SrcVmid       Vmid of the source VM, eg HLOS VMID.
  @param[in]      DestVmid      VMID of the destination VM to whom the parcel is donated.
  @param[in]      MemMessageId  RM Memory operation message ID (donate/Lend/Share ...).
  @param[OUT]     MemHandle     Pointer to Memory parcel handle.

  @return
  EFI_SUCCESS           -- Function completed successfully, Else error code. \n
*/
EFI_STATUS
EFIAPI MemShare(
   IN  EFI_RMVM_PROTOCOL    *This,
   IN  UINT8                MemType,
   IN  UINT8                Flags,
   IN  UINT32               Label,
   IN  RmMemAcl             *AclPtr,
   IN  RmMemSgl             *SglPtr,
   IN  RmMemAttributes      *AttrPtr,
   IN  UINT16               SrcVmid,
   IN  UINT16               DestVmid,
   IN  UINT32               MemMessageId,
   OUT UINT32               *MemHandle
   )
{
  EFI_STATUS Status = EFI_SUCCESS;
  VOID *TxBuffer = NULL;
  UINT32 MessageSize = 0;
  UINT16 index = 0;
  RmMemShareResp *RmMemRespBuff = NULL;

  UINT8* TempMsgOffset = NULL;  
  RmMemShareDescPartial *MemSharePtr = NULL;
  RmMemAcl              *TemAclPtr = NULL;
  RmMemSgl              *TemSglPtr = NULL;
  RmMemAttributes       *TemAttrPtr = NULL;

  DEBUG ((EFI_D_INFO, "[RmVmDxe]: MemShare Invoked\n"));

  if(AclPtr == NULL || SglPtr == NULL || 
     MemHandle == NULL || MemMessageId == 0)
  {
    DEBUG((EFI_D_ERROR, "MemShare: NULL Params passed\n"));
    return EFI_INVALID_PARAMETER;
  }

  // ++TODO++: Calculate BufferSize by going over ACL, SGL, ATTR list sizes. For now assume all will 
  // fit in 240 bytes else need to fragment

  TxBuffer = AllocateZeroPool (MAX_RPC_BUFF_SIZE_BYTES);
  if (TxBuffer == NULL)
  {
    Status = EFI_OUT_OF_RESOURCES;
    DEBUG((EFI_D_ERROR, "[RmVmDxe] Could not allocate memory for MsgQ transmit Buffer. Status = 0x%x.\n", Status));
    return Status;    
  }
  MemSharePtr= (RmMemShareDescPartial *)TxBuffer;
  FormatRmVmHeader (TxBuffer, MemMessageId, &MessageSize);
  
  MemSharePtr->MemType = MemType;
  MemSharePtr->Flags   = Flags;
  MemSharePtr->Label   = Label;
  
  TemAclPtr = &MemSharePtr->AcList;
  
  TemAclPtr->acl_entries_count = AclPtr->acl_entries_count;
  for (index =0; index < AclPtr->acl_entries_count; index++)
  {
    TemAclPtr->AclEntries[index].vmid = AclPtr->AclEntries[index].vmid;
    TemAclPtr->AclEntries[index].rights = AclPtr->AclEntries[index].rights;
  }
  
  TempMsgOffset = (UINT8*)((UINTN)(&TemAclPtr->AclEntries[(index-1)].reserved));
  TempMsgOffset++;
  
  TemSglPtr = (RmMemSgl *)TempMsgOffset;
  TemSglPtr->sgl_entries_count = SglPtr->sgl_entries_count;
  for (index =0; index < TemSglPtr->sgl_entries_count; index++)
  {
    TemSglPtr->SglEntries[index].BaseAddr = SglPtr->SglEntries[index].BaseAddr;
    TemSglPtr->SglEntries[index].Size = SglPtr->SglEntries[index].Size;
  }

  TempMsgOffset = (UINT8*)((UINTN)(&TemSglPtr->SglEntries[(index-1)].Size));
  TempMsgOffset += sizeof((TemSglPtr->SglEntries[(index-1)].Size));
  
  TemAttrPtr = (RmMemAttributes *)TempMsgOffset;
  TemAttrPtr->attr_entries_count = 0;
 
  TempMsgOffset = (UINT8*)((UINTN)(&TemAttrPtr->reserved));
  TempMsgOffset += sizeof(TemAttrPtr->reserved);
  
  //Total message size will never exceed UINT32 range
  MessageSize = (UINT32)((UINTN)TempMsgOffset - (UINTN)TxBuffer);

  DEBUG ((EFI_D_INFO, "MsgQ Send Buffer:\r\n"));  
  PrintRmVmHeader (MemSharePtr); 
  DEBUG((EFI_D_INFO, "MessageSize bytes: %d \n", MessageSize));
    
  Status = GynhMsgQueueSend( CapIdProp[0], MessageSize, (UINT64)MemSharePtr, 
                             RM_MESG_QUEUE_SEND_FLAG_PUSH, RM_MESG_QUEUE_RESERVED_FIELD);
  
  if(Status != EFI_SUCCESS )
  {
    DEBUG((EFI_D_ERROR, "GynhMsgQueueSend error: 0x%x \n", Status));
    return Status;
  }
  
  RmMemRespBuff = AllocateZeroPool(MAX_RPC_BUFF_SIZE_BYTES);
  if (RmMemRespBuff == NULL)
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] Could not allocate memory for RmMemRespBuff.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = GynhMsgQueueReceive(CapIdProp[1],(UINT64)RmMemRespBuff, 
                              MAX_RPC_BUFF_SIZE_BYTES, RM_MESG_QUEUE_RESERVED_FIELD);  

  // ++TODO++ : Check msgQ x0 register Val, as to whether the receive operation succeeded
  // might as well check the message size to be equal to 0xC

  if ((RmMemRespBuff->StdResp).ErrorCode != RM_STATUS_SUCCESS )
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] MemShare RM RPC error 0x%x \n", (RmMemRespBuff->StdResp).ErrorCode));
    Status = EFI_INVALID_PARAMETER;
    *MemHandle = 0x0;
  }
  else
  {
    *MemHandle = RmMemRespBuff->MemHandle;
  }
 
  DEBUG ((EFI_D_INFO, "\nMsgQ Receive Buffer:\r\n"));  
  PrintRmVmHeader (RmMemRespBuff); 
  
  /*Free transmit, receive buffers since they are no longer needed */
  FreePool(TxBuffer);
  FreePool(RmMemRespBuff);
  
  return Status;
}

/* ============================================================================
**  Function : EFI_RM_MEM_DONATE
** ============================================================================
*/
/** @ingroup efi_rm_mem_donate
  @par Summary
  Donate memory from one VM to another

  @param[in]      This        Pointer to the EFI_RMVM_PROTOCOL instance.
  @param[in]      MemType     Type of memory parcel, Normal Vs IO.
  @param[in]      Flags       Memparcel flags eg sanitize, finalize bits.
  @param[in]      Label       Value to be used as a label for memparcel
  @param[in]      AclPtr      Pointer to access control vmid list.
  @param[in]      SglPtr      Pointer to scatter gather list for memory regions.
  @param[in]      AttrPtr     Pointer to list of attributes for destn VMIDs.
  @param[in]      SrcVmid     Vmid of the source VM, eg HLOS VMID.
  @param[in]      DestVmid    VMID of the destination VM to whom the parcel is donated.
  @param[OUT]     MemHandle   Pointer to Memory parcel handle.

  @return
  EFI_SUCCESS           -- Function completed successfully, Else error code. \n
*/

EFI_STATUS
EFIAPI EFI_MemDonate(
   IN  EFI_RMVM_PROTOCOL  *This,
   IN  UINT8              MemType,
   IN  UINT8              Flags,
   IN  UINT32             Label,
   IN  RmMemAcl           *AclPtr,
   IN  RmMemSgl           *SglPtr,
   IN  RmMemAttributes    *AttrPtr,
   IN  UINT16             SrcVmid,
   IN  UINT16             DestVmid,
   OUT UINT32             *MemHandle
   )
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(AclPtr == NULL || SglPtr == NULL || MemHandle == NULL)
  {
    DEBUG((EFI_D_ERROR, "EFI_MemDonate: NULL Params passed\n"));
    return EFI_INVALID_PARAMETER;
  }
  
  if (AclPtr->acl_entries_count != ACL_ENTRIES)
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] MemDonate Error: ACL entries count expected to be %d\n",ACL_ENTRIES));
    return EFI_INVALID_PARAMETER;    
  }  
  
  Status = HypAssignMem (AclPtr, SglPtr, SrcVmid);
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] Hyp Assign Error: Status = 0x%x.\n", Status));
    return Status;
  }
  
  Status = MemShare (This, MemType, Flags, Label,
                     AclPtr, SglPtr, AttrPtr, SrcVmid, DestVmid,
                     RM_MEM_DONATE_ID, MemHandle );
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] MemDonate Error: Status = 0x%x.\n", Status));
  }
    return Status;
}

/* ============================================================================
**  Function : EFI_RM_FW_SET_VM_FIRMWARE
** ============================================================================
*/
/** @ingroup efi_rm_fw_set_vm_firmware
  @par Summary
  Call into Resource Manager to set invoke message FW_SET_VM_FIRMWARE 

  @param[in]      This    Pointer to the EFI_RMVM_PROTOCOL instance.

  @return
  EFI_SUCCESS             -- Function completed successfully. \n
  EFI_NOT_READY           -- Protocol Dependencies not satisfied. \n
*/
EFI_STATUS
EFIAPI EFI_FwSetVmFirmware(
   IN EFI_RMVM_PROTOCOL       *This,
   IN  UINT16                 Auth,
   IN  UINT32                 MemHandle,
   IN  UINT64                 FwOffset,
   IN  UINT64                 FwSize
   )
{
  EFI_STATUS Status = EFI_SUCCESS;
  FwSetVmFirmware *SetVmFwMsgPtr = NULL;
  UINT32 MessageSize = 0;
  RmStdResp* RxBuffer = NULL;
  
  DEBUG((EFI_D_INFO, "[RmVmDxe]: FwSetVmFirmware Invoked\n"));
  
  SetVmFwMsgPtr = (FwSetVmFirmware *)AllocateZeroPool (sizeof(FwSetVmFirmware));
  if (SetVmFwMsgPtr == NULL)
  {
    Status = EFI_OUT_OF_RESOURCES;
    DEBUG((EFI_D_ERROR, "[RmVmDxe] Could not allocate memory for MsgQ transmit Buffer. Status = 0x%x.\n", Status));
    return Status;    
  }

  FormatRmVmHeader (SetVmFwMsgPtr, RM_FW_SET_VM_FIRMWARE_ID, &MessageSize);  
  SetVmFwMsgPtr->AuthMechanism = Auth;
  SetVmFwMsgPtr->MemHandle = MemHandle;
  SetVmFwMsgPtr->FwOffset = FwOffset;
  SetVmFwMsgPtr->FwSize = FwSize;

  DEBUG ((EFI_D_INFO, "MsgQ Send Buffer:\r\n"));  
  PrintRmVmHeader (SetVmFwMsgPtr);
  DEBUG ((EFI_D_INFO, "SetVmFwMsg AuthMechanism:  0x%x\r\n", SetVmFwMsgPtr->AuthMechanism ));
  DEBUG ((EFI_D_INFO, "SetVmFwMsg MemHandle:      0x%x\r\n", SetVmFwMsgPtr->MemHandle ));
  DEBUG ((EFI_D_INFO, "SetVmFwMsg FwOffset:       0x%x\r\n", SetVmFwMsgPtr->FwOffset));
  DEBUG ((EFI_D_INFO, "SetVmFwMsg FwSize:         0x%x\r\n", SetVmFwMsgPtr->FwSize ));
  
  Status = GynhMsgQueueSend(CapIdProp[0],sizeof(FwSetVmFirmware),(UINT64)SetVmFwMsgPtr,
                               RM_MESG_QUEUE_SEND_FLAG_PUSH, RM_MESG_QUEUE_RESERVED_FIELD);
  if(Status != EFI_SUCCESS )
  {
    DEBUG((EFI_D_ERROR, "GynhMsgQueueSend error: 0x%x \n", Status));
    return Status;
  }
  
  RxBuffer = AllocateZeroPool(MAX_RPC_BUFF_SIZE_BYTES);
  if (RxBuffer == NULL)
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] Could not allocate memory for RxBuffer.\n"));
    return EFI_OUT_OF_RESOURCES;
  }
  
  Status = GynhMsgQueueReceive(CapIdProp[1],(UINT64)RxBuffer ,MAX_RPC_BUFF_SIZE_BYTES,
                               RM_MESG_QUEUE_RESERVED_FIELD);    
                               
  DEBUG ((EFI_D_INFO, "\nMsgQ Receive Buffer:\r\n"));
  PrintRmVmHeader (RxBuffer);
  
  if (Status == EFI_SUCCESS && RxBuffer->ErrorCode != RM_STATUS_SUCCESS )
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] FwSetVmFirmware RM RPC error 0x%x \n", RxBuffer->ErrorCode));
    Status = EFI_INVALID_PARAMETER;
  }
  
  FreePool(SetVmFwMsgPtr);
  FreePool(RxBuffer);
  
  return Status;
}


/* ============================================================================
**  Function : EFI_RM_FW_MILESTONE
** ============================================================================
*/
/** @ingroup efi_rm_fw_milestone
  @par Summary
  Call into Resource Manager to set FW milestone

  @param[in]      This               Pointer to the EFI_RMVM_PROTOCOL instance.

  @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_NOT_READY         -- Protocol Dependencies not satisfied. \n
*/
EFI_STATUS
EFIAPI EFI_SetFwMilestone(
   IN EFI_RMVM_PROTOCOL       *This
   )
{
  EFI_STATUS  Status;
  RmMsgHeader FwMilestoneRmHdr = {0};
  UINT32 MessageSize = 0;
  RmStdResp* RxBuffer = NULL;
  
  DEBUG((EFI_D_INFO, "[RmVmDxe]: FwMilestone Invoked\n"));
  
  FormatRmVmHeader (&FwMilestoneRmHdr, RM_FW_MILESTONE_ID, &MessageSize);

  DEBUG ((EFI_D_INFO, "MsgQ Send Buffer:\r\n"));  
  PrintRmVmHeader (&FwMilestoneRmHdr);
  
  Status = GynhMsgQueueSend(CapIdProp[0],sizeof(FwMilestoneRmHdr),(UINT64)&FwMilestoneRmHdr,
                               RM_MESG_QUEUE_SEND_FLAG_PUSH, RM_MESG_QUEUE_RESERVED_FIELD);
  if(Status != EFI_SUCCESS )
  {
    DEBUG((EFI_D_ERROR, "GynhMsgQueueSend error: 0x%x \n", Status));
    return Status;
  }
  
  RxBuffer = (RmStdResp*) AllocateZeroPool(MAX_RPC_BUFF_SIZE_BYTES);
  if (RxBuffer == NULL)
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] Could not allocate memory for RxBuffer.\n"));
    return EFI_OUT_OF_RESOURCES;
  }
  
  Status = GynhMsgQueueReceive(CapIdProp[1],(UINT64)RxBuffer ,MAX_RPC_BUFF_SIZE_BYTES,
                               RM_MESG_QUEUE_RESERVED_FIELD);    
                               
  DEBUG ((EFI_D_INFO, "\nMsgQ Receive Buffer:\r\n"));
  PrintRmVmHeader (RxBuffer);

  if (Status == EFI_SUCCESS && RxBuffer->ErrorCode != RM_STATUS_SUCCESS )
  {
    DEBUG((EFI_D_ERROR, "[RmVmDxe] SetFwMilestone RM RPC error 0x%x \n", RxBuffer->ErrorCode));
    Status = EFI_INVALID_PARAMETER;
  }
 
  
  return Status;
}



STATIC EFI_RMVM_PROTOCOL RmVmProtocol = 
{
  EFI_RMVM_PROTOCOL_REVISION,
  EFI_VmGetID,
  EFI_MemDonate,
  EFI_FwSetVmFirmware,
  EFI_SetFwMilestone,
};

/**
  The Entry Point for RmVmDxe.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurred when executing this entry point.

**/

EFI_STATUS
EFIAPI
RmVmDxeInitialize
(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_HANDLE  handle = NULL;	

  Status = GhComInitialize();
  
  if(Status == EFI_SUCCESS)
  {
    // Install Protocol only in case of successful initialization
    Status = gBS->InstallMultipleProtocolInterfaces(
                    &handle,
                    &gEfiRmVmProtocolGuid,
                    (VOID **)&RmVmProtocol,
                    NULL );
    DEBUG((EFI_D_ERROR, "RmVmProtocol Installed \r\n"));                    
  }
  else
  {
    DEBUG((EFI_D_INFO, "Error: Gunyah interface init error: %r \r\n", Status));
    DEBUG((EFI_D_INFO, "Skipping RmVmProtocol Install \r\n"));
  }

  return EFI_SUCCESS;
}
