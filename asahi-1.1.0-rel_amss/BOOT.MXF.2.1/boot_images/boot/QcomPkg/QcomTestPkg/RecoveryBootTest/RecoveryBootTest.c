/** @file RecoveryBootTest.c
   
  Recovery Boot Test

  Copyright (c) 2023, Qualcomm Technologies, Inc. All rights reserved.
  
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/17/23   vk      Initial Revision.

=============================================================================*/
#include <Uefi.h>
#include <RecoveryBootInfoLib.h>
#include <Library/UefiLib.h>
#include <Library/QcomLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/EfiFileLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Guid/FileSystemVolumeLabelInfo.h>
#include <Protocol/BlockIo.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/LoadedImage.h>
#include <Library/ParserLib.h>
#include <Protocol/EFIRng.h>
#include <recovery_boot_info.h>

STATIC UINT32 DefaultOption = 0;
STATIC UINT32 EraseOption = 1;
STATIC UINT32 BootSelect = BOOT_SET_INVALID;
STATIC UINT32 ImageSetStatus = 0;

VOID LogRecoveryInfo (VOID)
{
  recovery_boot_status rstatus;
  recovery_boot_info_type *recovery_boot_info_ptr;

  rstatus = rbi_get_recovery_boot_info (&recovery_boot_info_ptr);

  DEBUG ((EFI_D_ERROR, "recoveryinfo status                 = 0x%x\n\n", rstatus));

  DEBUG ((EFI_D_ERROR, "recoveryinfo->magic_cookie          = 0x%lx\n", recovery_boot_info_ptr->magic_cookie));
  DEBUG ((EFI_D_ERROR, "recoveryinfo->version               = 0x%lx\n", recovery_boot_info_ptr->version));
  DEBUG ((EFI_D_ERROR, "recoveryinfo->image_set_status      = 0x%lx\n", recovery_boot_info_ptr->image_set_status));
  DEBUG ((EFI_D_ERROR, "recoveryinfo->boot_set->magic       = 0x%x\n",  recovery_boot_info_ptr->boot_set.magic));
  DEBUG ((EFI_D_ERROR, "recoveryinfo->boot_set.selected_set = 0x%x\n",  recovery_boot_info_ptr->boot_set.selected_set));
  DEBUG ((EFI_D_ERROR, "recoveryinfo->rcrc                  = 0x%lx\n", recovery_boot_info_ptr->recovery_boot_info_crc));
  DEBUG ((EFI_D_ERROR, "recoveryinfo->rcrc magic            = 0x%lx\n", recovery_boot_info_ptr->recovery_boot_info_crc_enable_magic));
}

EFI_STATUS
ProcessCommand (UINTN Argc, CHAR8** Argv)
{
  CHAR8 *CmdStr, *ArgStr = NULL;

  CmdStr = Argv[0];
  --Argc;

  if (Argc)
    ArgStr = Argv[1];

#if 1
  AsciiPrint ("Processing Cmd: %a", CmdStr);
  if (ArgStr)
     AsciiPrint (", Arg: %a", ArgStr);
  AsciiPrint ("\r\n");
#endif

  if (AsciiStriCmp ((CHAR8*)CmdStr, "-BSA") == 0)
  {
    BootSelect = BOOT_SET_A;
  }
  else if (AsciiStriCmp ((CHAR8*)CmdStr, "-BSB") == 0)
  {
    BootSelect = BOOT_SET_B;
  }
  else if (AsciiStriCmp ((CHAR8*)CmdStr, "-E") == 0)
  {
    EraseOption = 1;
  }
  else if (AsciiStriCmp ((CHAR8*)CmdStr, "-I") == 0)
  {
   ImageSetStatus = 1;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
ParseCommandLine (EFI_HANDLE *ImageHandle)
{
  EFI_STATUS Status = EFI_INVALID_PARAMETER;  
  UINTN      Argc = 0;
  CHAR8      **Argv;

  if(EFI_ERROR(GetCmdLineArgs (*ImageHandle, &Argc, &Argv)))
    return EFI_INVALID_PARAMETER;

  if (Argv != NULL)
  {
    /* Check if the app was launched by shell and the Cmd str is actually the
     * Cmd app name itself, ie it would be "cmd" or "cmd.efi", then again process
     * to split, this is because Ebl doesn't pass the name of app, but shell does
     * other methods could yeild mixed results (like BDS launching apps via Menu, etc) */
    if ((AsciiStriCmp (Argv[0], "RecoveryBootTest") == 0) ||
        (AsciiStriCmp (Argv[0], "RecoveryBootTest.efi") == 0))
    {
      --Argc;
      if (Argc == 0)
      {
        FreePool (Argv);
        AsciiPrint ("No Command to process... \r\n");
        return EFI_SUCCESS;
      }
      ++Argv;
    }
  }

  if ((Argc != 0) && (Argv != NULL))
    Status = ProcessCommand (Argc, Argv);

  return Status;
}

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
RecoveryBootTestMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS Status = EFI_LOAD_ERROR;
  recovery_boot_status rstatus = RBI_SUCCESS;

  uint8 partition_present = FALSE;
  uint8 boot_select_enabled = FALSE;
  uint32 selected_boot_set = FALSE;
  uint32 bootable_set = 0;
  uint32 failed_image_set = 0;

  DEBUG ((EFI_D_ERROR, "RecoveryBootTest\n"));
  
  Status = ParseCommandLine (&ImageHandle);
  if (Status != EFI_SUCCESS)
  {
    /* No arguments provided choose an option */
    DefaultOption = 1;
  }

  rstatus |= recoveryinfo_partition_present (&partition_present);

  if (DefaultOption)
  {
    LogRecoveryInfo();
    DEBUG ((EFI_D_ERROR, "rbi_reset\n"));
    rstatus |= rbi_reset ();
    LogRecoveryInfo();
   
    LogRecoveryInfo();
    DEBUG ((EFI_D_ERROR, "rbi_mark_set_failed\n"));
    rstatus |= rbi_mark_set_failed (failed_image_set);
    LogRecoveryInfo();

    
    DEBUG ((EFI_D_ERROR, "rbi_is_boot_select_enabled\n"));
    rstatus |= rbi_is_boot_select_enabled (&boot_select_enabled);
    DEBUG ((EFI_D_ERROR, "rbi_is_boot_select_enabled = %x 0x\n", rstatus));

    rstatus |= rbi_set_boot_select_set (selected_boot_set);
    DEBUG ((EFI_D_ERROR, "rbi_set_boot_select_set = %x 0x\n", rstatus));
    LogRecoveryInfo();

    rstatus |= rbi_get_boot_set (&bootable_set);
    DEBUG ((EFI_D_ERROR, "rbi_get_boot_set = %x 0x\n", rstatus));

    DEBUG ((EFI_D_ERROR, "rbi_reset\n"));
    rstatus |= rbi_reset ();
    LogRecoveryInfo();
  }

  if (BootSelect != BOOT_SET_INVALID)
  {
    rstatus = rbi_set_boot_select_set (BootSelect);
    DEBUG ((EFI_D_ERROR, "rbi_set_boot_select_set = %x 0x\n", rstatus));
    LogRecoveryInfo();
  }
  
  if (EraseOption == 1)
  {
    DEBUG ((EFI_D_ERROR, "rbi_reset\n"));
    rstatus = rbi_reset ();
    LogRecoveryInfo();
  }


  if (rstatus == RBI_SUCCESS)
    Status = EFI_SUCCESS;
  else
    Status = EFI_LOAD_ERROR;

  return Status;
}
