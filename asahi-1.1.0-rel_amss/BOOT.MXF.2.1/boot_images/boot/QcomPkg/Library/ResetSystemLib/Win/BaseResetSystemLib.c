/** @file
  Reset System Library instance

  Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ResetSystemLib.h>
#include <Library/SerialPortShLib.h>

#include <Library/CookieLib.h>
#include <Library/SDILib.h>

#include <Guid/EventGroup.h>


#define STR_RESET_PLAT_SPECIFIC_EDL                    L"EDL"
#define STR_RESET_PLAT_SPECIFIC_TESTONLY_WARM_RESET    L"WARM_TEST_RESET"


//--------------------------------------------------------------------------
// PSCI Defines 
//--------------------------------------------------------------------------
extern int reset_psci_call(long arg0);

#define PSCI_SYSTEM_OFF   0x84000008
#define PSCI_SYSTEM_RESET 0x84000009
#define SMC_WARM_RESET    0xC3000922

EFI_STATUS EFIAPI PreReset ();




/**
  Updates NV Variables to keep track of the number of resets
  and shutdowns.

**/
EFI_STATUS
EFIAPI
UpdateNVVariables ( VOID )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINTN DataSize;
  UINT32 VarData;
  
  DataSize = sizeof(VarData);

  if (!EfiAtRuntime())
  {
    Status = gRT->GetVariable (L"BSPowerCycles", 
                               &gQcomTokenSpaceGuid, 
                               NULL,
                               &DataSize, 
                               &VarData);

    if (Status != EFI_SUCCESS)
      VarData = 0;

    VarData++;
    DataSize = sizeof(VarData);

    Status = gRT->SetVariable (L"BSPowerCycles", 
                               &gQcomTokenSpaceGuid, 
                               (EFI_VARIABLE_NON_VOLATILE | 
                                EFI_VARIABLE_BOOTSERVICE_ACCESS),
                               DataSize, 
                               &VarData);
  }
  
  return Status;
}


/**
  Function that needs to be called just before
  Reset.
  
**/
EFI_STATUS
EFIAPI
PreReset ()
{
  
  volatile UINT32 count = 0;
  UpdateNVVariables();

  /* Delay loop required for proper reset/shutdown */
  if (EfiAtRuntime())
  {
    while (count < 0x1000000)
    {
      count++;
    }
  }
  else
  {
    /* Flush the buffer to serial port and enable
	   * synchronous transfer */
    SerialPortFlush ();
    EnableSynchronousSerialPortIO ();
    gBS->Stall(300); /* 300 uSeconds*/
  }
  
  return EFI_SUCCESS;
}


/**
  Shuts down EFI boot environment and frees up memory. 
   
**/
VOID
ShutdownEfi (
  VOID
  )
{
  EFI_STATUS              Status;
  UINTN                   MemoryMapSize = 0;
  EFI_MEMORY_DESCRIPTOR   *MemoryMap = NULL;
  UINTN                   MapKey = 0;
  UINTN                   DescriptorSize = 0;
  UINT32                  DescriptorVersion = 0;
  UINTN                   Pages;

  /* Contents of this function doesn't work in runtime */
  if (EfiAtRuntime() != 0)
    return;

  PreReset();
    
  /* Wait until all the data from UART FIFO is drained */
  DEBUG((EFI_D_WARN, "\n"));

  do {
    Status = gBS->GetMemoryMap (
                    &MemoryMapSize,
                    MemoryMap,
                    &MapKey,
                    &DescriptorSize,
                    &DescriptorVersion
                    );
    if (Status == EFI_BUFFER_TOO_SMALL) {
      Pages = EFI_SIZE_TO_PAGES (MemoryMapSize) + 1;
      MemoryMap = AllocatePages (Pages);
      MemoryMapSize = EFI_PAGES_TO_SIZE(Pages);

      /*
       * Get System MemoryMap
       */
      Status = gBS->GetMemoryMap (
                      &MemoryMapSize,
                      MemoryMap,
                      &MapKey,
                      &DescriptorSize,
                      &DescriptorVersion
                      );
      /* Don't do anything between the GetMemoryMap() and ExitBootServices() */
      if (!EFI_ERROR (Status)) {
        if (EFI_ERROR (Status)) {
          FreePages (MemoryMap, Pages);
          MemoryMap = NULL;
          MemoryMapSize = 0;
        }
      }
    }
  } while (EFI_ERROR (Status));

  /* Clean and invalidate caches */
  //WriteBackInvalidateDataCache();
  //InvalidateInstructionCache();

  /* Turn off caches and MMU */
  //ArmDisableDataCache ();
  //ArmDisableInstructionCache ();
  //ArmDisableMmu ();
}

EFI_STATUS
EFIAPI
PlatformSpecificReset(UINTN DataSize, CHAR16 *ResetData)
{
  EFI_STATUS Status = EFI_SUCCESS;

  // Perform hard reset if no parameters provided
  if ((ResetData == NULL) || (DataSize == 0)) {
      ShutdownEfi ();
      return reset_psci_call(PSCI_SYSTEM_RESET);
  }
  
  if (StrCmp(STR_RESET_PLAT_SPECIFIC_EDL, ResetData) == 0)
  {
    //Set EDL cookie and perform warm reset
    Status = ClearDLOADCookie();
    
    if (Status != EFI_SUCCESS)
    {
       DEBUG ((EFI_D_ERROR, "ERROR: ClearDLOADCookie Status: 0x%08x\n", Status));
    }
    
    Status = SetEDLCookie();
  
    if (Status != EFI_SUCCESS)
    {
       DEBUG ((EFI_D_ERROR, "ERROR: SetEDLCookie Status: 0x%08x\n", Status));
    }
    
    Status = SDIDisableAndReset();
    
    if (Status != EFI_SUCCESS)
    {
       DEBUG ((EFI_D_ERROR, "ERROR: SDIDisableAndReset Status: 0x%08x\n", Status));
    }
    
    ShutdownEfi ();
    reset_psci_call(SMC_WARM_RESET);
    
    if (Status != EFI_SUCCESS)
    {
       DEBUG ((EFI_D_INFO, "ERROR: PSCI Call Status: 0x%08x\n", Status));
    }
  }
  
  return Status;
}


/**
  This function causes a system-wide reset (cold reset), in which
  all circuitry within the system returns to its initial state. This type of reset
  is asynchronous to system operation and operates without regard to
  cycle boundaries.

  If this function returns, it means that the system does not support cold reset.
**/
VOID
EFIAPI
ResetCold (
  VOID
  )
{
  if(EfiAtRuntime())
    return;
  ShutdownEfi ();
  reset_psci_call(PSCI_SYSTEM_RESET);
}

/**
  This function causes a system-wide initialization (warm reset), in which all processors
  are set to their initial state. Pending cycles are not corrupted.

  If this function returns, it means that the system does not support warm reset.
**/
VOID
EFIAPI
ResetWarm (
  VOID
  )
{
  if(EfiAtRuntime())
    return;
  ShutdownEfi ();
  reset_psci_call(PSCI_SYSTEM_RESET);
}

/**
  This function causes the system to enter a power state equivalent
  to the ACPI G2/S5 or G3 states.

  If this function returns, it means that the system does not support shut down reset.
**/
VOID
EFIAPI
ResetShutdown (
  VOID
  )
{
  if(EfiAtRuntime())
    return;
  ShutdownEfi ();
  reset_psci_call(PSCI_SYSTEM_OFF);
}

/**
  This function causes a systemwide reset. The exact type of the reset is
  defined by the EFI_GUID that follows the Null-terminated Unicode string passed
  into ResetData. If the platform does not recognize the EFI_GUID in ResetData
  the platform must pick a supported reset type to perform.The platform may
  optionally log the parameters from any non-normal reset that occurs.

  @param[in]  DataSize   The size, in bytes, of ResetData.
  @param[in]  ResetData  The data buffer starts with a Null-terminated string,
                         followed by the EFI_GUID.
**/
VOID
EFIAPI
ResetPlatformSpecific (
  IN UINTN  DataSize,
  IN VOID   *ResetData
  )
{
  //ResetCold ();
  
  if(EfiAtRuntime())
    return;
  if (ResetData !=NULL)
    PlatformSpecificReset(DataSize, ResetData);
  else
    PlatformSpecificReset(DataSize, NULL);
}

/**
  The ResetSystem function resets the entire platform.

  @param[in] ResetType      The type of reset to perform.
  @param[in] ResetStatus    The status code for the reset.
  @param[in] DataSize       The size, in bytes, of ResetData.
  @param[in] ResetData      For a ResetType of EfiResetCold, EfiResetWarm, or EfiResetShutdown
                            the data buffer starts with a Null-terminated string, optionally
                            followed by additional binary data. The string is a description
                            that the caller may use to further indicate the reason for the
                            system reset.
**/
VOID
EFIAPI
ResetSystem (
  IN EFI_RESET_TYPE  ResetType,
  IN EFI_STATUS      ResetStatus,
  IN UINTN           DataSize,
  IN VOID            *ResetData OPTIONAL
  )
{
  /*This function is not called from anywhere from MdePkg driver*/
  ASSERT(FALSE);
}


