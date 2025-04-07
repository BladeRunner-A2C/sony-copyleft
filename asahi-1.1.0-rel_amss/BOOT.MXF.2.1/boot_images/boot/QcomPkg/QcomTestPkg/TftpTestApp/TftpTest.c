/** @file TftpTest.c
   
  Tests for image download via TFTP.

  Copyright (c) 2012-2023, Qualcomm Technologies, Inc. All rights reserved.
  
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/27/12   pbi     Updated for timetick changes 
 04/10/12   jz      Fixed klockwork warnings
 01/20/12   jz      Created
=============================================================================*/

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/TestInterface.h>
#include <string.h>

#include <Protocol/PxeBaseCode.h>
#include <Library/BaseLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/QcomLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/EfiFileLib.h>


#define ALIGN_UP_SZ(x,y)    (((x) + ((y) - 1)) & ~((y) - 1))

void CopyMem (void* dst, void* src, uint32 size){
  memcpy (dst, src, size);
}


/**
  Entry point for the application

  @param[in] ImageHandle    Image handle 
  @param[in] SystemTable    Pointer to the System Table
  
  @retval EFI_SUCCESS       Execution successful
  @retval other             Error occurred

**/
EFI_STATUS
EFIAPI
TftpEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                            Status;
  EFI_PXE_BASE_CODE_PROTOCOL            *Pxe;
  EFI_PXE_BASE_CODE_TFTP_OPCODE         Operation;
  VOID                                  *BufferPtr = NULL;
  BOOLEAN                               Overwrite = FALSE;
  UINT64                                BufferSize;
  UINTN                                 BlockSize = 4094; //1428;
  EFI_IP_ADDRESS                        ServerIp;
  UINT8                                 Filename[32];
  EFI_PXE_BASE_CODE_MTFTP_INFO          *Info = NULL;
  BOOLEAN                               DontUseBuffer = FALSE;
  UINT32 starting_tick,ending_tick;
  
  TEST_START("TFTP");


  Status = gBS->LocateProtocol (&gEfiPxeBaseCodeProtocolGuid, NULL, (VOID **)&Pxe);
  if (EFI_ERROR(Status)) {
    AsciiPrint("Failed to locate PxeBaseCodeProtocol, Status: %d\n", Status);
    return Status;
  }

  Status = Pxe->Start (Pxe, FALSE);
  if (EFI_ERROR(Status) && (Status != EFI_ALREADY_STARTED)) {
    AsciiPrint("Failed to enable PXE, Status: %d\n", Status);
    return Status;
  }

  Status = Pxe->Dhcp(Pxe, TRUE);
  if (EFI_ERROR(Status)) {
    AsciiPrint("Failed to complete DHCP, Status: %d\n", Status);
    return Status;
  }

  CopyMem (&ServerIp, Pxe->Mode->DhcpAck.Dhcpv4.BootpSiAddr, sizeof (EFI_IPv4_ADDRESS));
  if(ServerIp.v4.Addr[0] == 0) 
    CopyMem (&ServerIp.v4, Pxe->Mode->DhcpAck.Dhcpv4.DhcpOptions+5, sizeof (EFI_IPv4_ADDRESS));

  CopyMem (Filename, Pxe->Mode->DhcpAck.Dhcpv4.BootpBootFile, sizeof(Filename));
  
  // Get the file size from server
  Operation = EFI_PXE_BASE_CODE_TFTP_GET_FILE_SIZE;
  DontUseBuffer = TRUE;

  Status = Pxe->Mtftp (
                  Pxe,
                  Operation,
                  BufferPtr,
                  Overwrite,
                  &BufferSize,
                  &BlockSize,
                  &ServerIp,
                  Filename,
                  Info,
                  DontUseBuffer
                  );

  if (EFI_ERROR(Status)) {
    AsciiPrint("Failed to get file size, Status: %d\n", Status);
    return Status;
  }

  // Read the file from server
  Operation = EFI_PXE_BASE_CODE_TFTP_READ_FILE;
  DontUseBuffer = FALSE;

  UINT32 ElfSizeAligned = ALIGN_UP_SZ(BufferSize, EFI_PAGE_SIZE);
  BufferPtr = (UINT8*)AllocatePages(ElfSizeAligned/EFI_PAGE_SIZE); 
  if (BufferPtr == NULL){
   AsciiPrint("Failed with out of resouce\n");
   return RETURN_OUT_OF_RESOURCES;
  }

  // Get the tick count at the start of the event
  starting_tick = GetTimerCountms();

  Status = Pxe->Mtftp (
                  Pxe,
                  Operation,
                  BufferPtr,
                  Overwrite,
                  &BufferSize,
                  &BlockSize,
                  &ServerIp,
                  Filename,
                  Info,
                  DontUseBuffer
                  );

  // Get the tick count at the end of the event
  ending_tick = GetTimerCountms();
    
  if (EFI_ERROR(Status))
  {
    AsciiPrint("TFTP failed, Status: %d\n", Status);
  }
  else
  {
    AsciiPrint("TFTP succeeded, operation: %d, filename: %a, size: %ld, time taken: [%5d] ms\n",
               Operation, Filename, BufferSize, ending_tick - starting_tick);
  }

  Pxe->Stop(Pxe);

  if (BufferPtr != NULL) {
    FreePages(BufferPtr,ElfSizeAligned/EFI_PAGE_SIZE);
  }

  TestStatus("TFTP", Status);
  TEST_STOP("TFTP");
  return Status;
}
