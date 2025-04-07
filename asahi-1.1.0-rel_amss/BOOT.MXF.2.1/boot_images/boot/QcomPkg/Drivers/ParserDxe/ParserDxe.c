/*===============================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE:         ParserDxe.c
  DESCRIPTION:    
  
  REVISION HISTORY
  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  03/15/23   sc         Separated Mission mode APIs
  05/05/20   yw         initial version
================================================================================*/
#include <Protocol/EFIParser.h>
#include <Library/KernelLib.h>
#include <Library/ParserLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Parserdxe.h>

LockHandle* ParserLockPtr;

/**
  Parser protocol defination
  
**/
STATIC EFI_PARSER_PROTOCOL ParserProtocol =
{
   EFI_PARSER_PROTOCOL_VERSION_V1,
   EFI_Parser_OpenParser,
   EFI_Parser_CloseParser,
   EFI_Parser_EnumKeyValues,
   EFI_Parser_ReopenParser
};

/**
  The Entry Point for parser module. 

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurred when executing this entry point.

**/
 
EFI_STATUS EFIAPI 
ParserDxeEntry
(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
)
{
	EFI_HANDLE Handle = NULL;
    EFI_STATUS Status;
	
	Status = InitLock("ParsrLck", &ParserLockPtr);
	if (EFI_ERROR(Status)) {
		DEBUG ((EFI_D_ERROR, "Failed to init lock\n"));
		goto ParserEntryExit;
	}
	
	Status = gBS->InstallMultipleProtocolInterfaces(
                    &Handle,
                    &gEfiParserProtocolGuid,
                    (VOID **)&ParserProtocol,
                    NULL );
    if (EFI_ERROR(Status)) {
        DEBUG ((EFI_D_ERROR, "Failed to install parser protocol.\n"));
    }
	
ParserEntryExit:
	return Status;
}