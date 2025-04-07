/** @file RmVmTest.c
   
  Tests for Resource Manager Interface APIs.

  Copyright (c) 2023 Qualcomm Technologies Inc. All rights reserved.


**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/25/23   kedara  Added updates for MEM_SHARE_RM_VMID
 02/17/23   kedara  Initial Revision.

=============================================================================*/

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/TestInterface.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/EFIRmVm.h>

#define MEM_SHARE_RM_VMID   255
#define HLOS_VMID           3
#define MEMPARCEL_LABEL     0xEABE

EFI_STATUS ValidateGetVmId (VOID)
{
  EFI_STATUS  Status;
  EFI_RMVM_PROTOCOL    *RmVmProtocol = NULL; 
  VOID *RxBuffer = NULL;
  UINT32 RxBufferSize = 0;

  AsciiPrint("\n\n------ Test: Validate VmGetID ------\n");
  Status = gBS->LocateProtocol(&gEfiRmVmProtocolGuid, NULL, (void**)&RmVmProtocol);
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_WARN, "[RmVmTest] RmVmProtocol not found \n"));
    return Status;
  }
  
  DEBUG ((EFI_D_WARN, "VMID:                 0x%x\r\n", HLOS_VMID ));  
  Status = RmVmProtocol->VmGetID(RmVmProtocol, HLOS_VMID, &RxBuffer, &RxBufferSize);
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_WARN, "[RmVmTest] VmGetID Failed 0x%x \n", Status));
    return Status;
  }
  else
    AsciiPrint("VmGetID Success\n");  

  return EFI_SUCCESS;  
}

//#############################################################################

EFI_STATUS ValidateMemTest (VOID)
{
  EFI_STATUS  Status;
  EFI_RMVM_PROTOCOL    *RmVmProtocol = NULL; 
  
  VOID *MemDonateBuff = NULL;
  UINT32 RmTestMemHandle = 0, *CheckPtr;
  RmMemAcl *RmTestAclDesc = NULL;
  RmMemSgl *RmTestSglDesc = NULL;

  AsciiPrint("\n\n------ Test: Validate MemDonate ------\n");  
  Status = gBS->LocateProtocol(&gEfiRmVmProtocolGuid, NULL, (void**)&RmVmProtocol);
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_WARN, "[RmVmTest] RmVmProtocol not found \n"));
    return Status;
  }
   
  MemDonateBuff = AllocatePages(SIZE_2MB/EFI_PAGE_SIZE);
  ASSERT (MemDonateBuff != NULL);  

  CheckPtr = (UINT32 *)MemDonateBuff;
  *CheckPtr = 0xFACE;

  RmTestAclDesc = AllocateZeroPool(MAX_RPC_BUFF_SIZE_BYTES); 
  ASSERT (RmTestAclDesc != NULL);  
  
  RmTestSglDesc = AllocateZeroPool(MAX_RPC_BUFF_SIZE_BYTES);
  ASSERT (RmTestSglDesc != NULL);  

  RmTestAclDesc->acl_entries_count = 1;
  RmTestAclDesc->AclEntries[0].vmid = MEM_SHARE_RM_VMID;
  RmTestAclDesc->AclEntries[0].rights = (RM_ACL_PERM_READ|RM_ACL_PERM_WRITE|RM_ACL_PERM_EXEC);
  
  RmTestSglDesc->sgl_entries_count = 1;
  RmTestSglDesc->SglEntries[0].BaseAddr = (UINT64)MemDonateBuff;
  RmTestSglDesc->SglEntries[0].Size = SIZE_2MB;

  DEBUG ((EFI_D_WARN, "Buffer Address:       0x%x\r\n", MemDonateBuff ));
  DEBUG ((EFI_D_WARN, "Buffer Size:          0x%x\r\n", SIZE_2MB ));

  AsciiPrint("Value at 0x%x (updated before MemDonate): 0x%x\n", CheckPtr, *CheckPtr);
  
  Status = RmVmProtocol->MemDonate (RmVmProtocol,
                                    RM_MEM_TYPE_NORMAL_MEMORY,    // Mem_Type
                                    RM_MEM_SHARE_FLAG_SANITIZE,   // Flags
                                    MEMPARCEL_LABEL,              // Label
                                    RmTestAclDesc,                // AclPtr
                                    RmTestSglDesc,                // SglPtr
                                    NULL,                         // AttrPtr
                                    HLOS_VMID,                    // SrcVmid
                                    MEM_SHARE_RM_VMID,            // Dest Vmid
                                    &RmTestMemHandle              // MemHandle
                                   );
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_WARN, "[RmVmTest] MemDonate Failed 0x%x \n", Status));
    return Status;
  }
  else
    AsciiPrint("MemDonate call Success. Memhandle 0x%x\n", RmTestMemHandle);

  AsciiPrint("Updating 0x%x to value : 0xDEAD\n\n", CheckPtr);
  AsciiPrint("-- For successful MemDonate invocation expect an exception at this point --\n\n");
  
  *CheckPtr = 0xDEAD;
  
  return EFI_SUCCESS;    
}

//#############################################################################


EFI_STATUS ValidateFwSetVmFirmware (VOID)
{
  EFI_STATUS  Status;
  EFI_RMVM_PROTOCOL    *RmVmProtocol = NULL; 
  
  VOID *MemDonateBuff = NULL;
  UINT32 RmTestMemHandle = 0;
  RmMemAcl *RmTestAclDesc = NULL;
  RmMemSgl *RmTestSglDesc = NULL;

  AsciiPrint("\n\n------ Test: Validate Validate FwSetVmFirmware ------\n");  
  Status = gBS->LocateProtocol(&gEfiRmVmProtocolGuid, NULL, (void**)&RmVmProtocol);
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_WARN, "[RmVmTest] RmVmProtocol not found \n"));
    return Status;
  }
   
  MemDonateBuff = AllocatePages(SIZE_2MB/EFI_PAGE_SIZE);
  ASSERT (MemDonateBuff != NULL);  

  RmTestAclDesc = AllocateZeroPool(MAX_RPC_BUFF_SIZE_BYTES); 
  ASSERT (RmTestAclDesc != NULL);  
  
  RmTestSglDesc = AllocateZeroPool(MAX_RPC_BUFF_SIZE_BYTES);
  ASSERT (RmTestSglDesc != NULL);  

  RmTestAclDesc->acl_entries_count = 1;
  RmTestAclDesc->AclEntries[0].vmid = MEM_SHARE_RM_VMID;
  RmTestAclDesc->AclEntries[0].rights = (RM_ACL_PERM_READ|RM_ACL_PERM_WRITE|RM_ACL_PERM_EXEC);
  
  RmTestSglDesc->sgl_entries_count = 1;
  RmTestSglDesc->SglEntries[0].BaseAddr = (UINT64)MemDonateBuff;
  RmTestSglDesc->SglEntries[0].Size = SIZE_2MB;

  DEBUG ((EFI_D_WARN, "Buffer Address:       0x%x\r\n", MemDonateBuff ));
  DEBUG ((EFI_D_WARN, "Buffer Size:          0x%x\r\n", SIZE_2MB ));
  
  Status = RmVmProtocol->MemDonate (RmVmProtocol,
                                    RM_MEM_TYPE_NORMAL_MEMORY,    // Mem_Type
                                    0,                            // Flags
                                    MEMPARCEL_LABEL,              // Label
                                    RmTestAclDesc,                // AclPtr
                                    RmTestSglDesc,                // SglPtr
                                    NULL,                         // AttrPtr
                                    HLOS_VMID,                    // SrcVmid
                                    MEM_SHARE_RM_VMID,            // Dest Vmid
                                    &RmTestMemHandle              // MemHandle
                                   );
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_WARN, "[RmVmTest] MemDonate Failed 0x%x \n", Status));
    return Status;
  }
  else
    AsciiPrint("MemDonate call Success. Memhandle 0x%x\n\n", RmTestMemHandle);

  Status = RmVmProtocol->FwSetVmFirmware (RmVmProtocol,
                                    RM_VM_AUTH_ANDROID_PVM,       // Auth
                                    RmTestMemHandle,              // MemHandle
                                    0,                            // FwOffset
                                    SIZE_1MB                      // FwSize
                                  );
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_WARN, "[RmVmTest] FwSetVmFirmware Failed 0x%x \n", Status));
    return Status;
  }
  else
    AsciiPrint("FwSetVmFirmware call Success. \n");

  
  return EFI_SUCCESS;    
}

//#############################################################################


EFI_STATUS ValidateFwMilestone (VOID)
{
  EFI_STATUS  Status;
  EFI_RMVM_PROTOCOL    *RmVmProtocol = NULL; 

  AsciiPrint("\n\n------ Test: Validate FwMilestone ------\n");
  Status = gBS->LocateProtocol(&gEfiRmVmProtocolGuid, NULL, (void**)&RmVmProtocol);
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_WARN, "[RmVmTest] RmVmProtocol not found \n"));
    return Status;
  }
  
  Status = RmVmProtocol->SetFwMilestone(RmVmProtocol);
  if (Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_WARN, "[RmVmTest] FwMilestone Failed 0x%x \n", Status));
    return Status;
  }
  else
    AsciiPrint("FwMilestone Success\n");  

  return EFI_SUCCESS;  
}

//#############################################################################

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status;
 
  Status = ValidateGetVmId();
  if (Status != EFI_SUCCESS)
     DEBUG ((EFI_D_ERROR, "Error in ValidateGetVmId: %d\r\n", Status));

  Status = ValidateFwSetVmFirmware();
  if (Status != EFI_SUCCESS)
     DEBUG ((EFI_D_ERROR, "Error in ValidateFwSetVmFirmware: %d\r\n", Status));

  Status = ValidateMemTest();
  if (Status != EFI_SUCCESS)
     DEBUG ((EFI_D_ERROR, "Error in ValidateMemTest: %d\r\n", Status));

  Status = ValidateFwMilestone();
  if (Status != EFI_SUCCESS)
     DEBUG ((EFI_D_ERROR, "Error in ValidateFwMilestone: %d\r\n", Status));
 
  
  return Status;
}
