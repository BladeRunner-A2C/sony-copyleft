/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include "Dev.h"
#include "Diagnostics.h"

extern EFI_DRIVER_BINDING_PROTOCOL gQcWlanDrvBinding;
extern EFI_QCWLAN_DEVICE_CONTEXT gWlanDriverContext;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_DRIVER_DIAGNOSTICS2_PROTOCOL gWlanUefiDiagnostics2 = {
  (EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS) QcWlanRunDiagnostics,
  "en"
};

EFI_STATUS 
EFIAPI
QcWlanRunDiagnostics (
	IN  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL  *This,
	IN  EFI_HANDLE                        ControllerHandle,
	IN  EFI_HANDLE                        ChildHandle,       OPTIONAL
	IN  EFI_DRIVER_DIAGNOSTIC_TYPE        DiagnosticType,
	IN  CHAR8                             *Language,
	OUT EFI_GUID                          **ErrorType,
	OUT UINTN                             *BufferSize,
	OUT CHAR16                            **Buffer
  	)
{
	EFI_STATUS  Status;
	EFI_QCWLAN_DEVICE_CONTEXT *Dev = &gWlanDriverContext;
	CHAR8       *SupportedLanguages;
	BOOLEAN     Rfc4646Language;
	BOOLEAN     Found;
	UINTN       Index;

	//
	// Check whether the driver load succ
	//
	if (Dev->Started == DEV_START_INIT)  {
		DbgError("UEFI Wlan is not ready.\n");
		return EFI_NOT_READY;
	}
	
	if (Dev->Started == DEV_START_FW_FAIL)  {
		DbgError("UEFI Wlan load fw fail\n");
		return EFI_LOAD_ERROR;
	}
	
	//
	// Make sure this driver is currently managing ControllerHandle
	//
	Status = EfiTestManagedDevice (
				 ControllerHandle,
				 gQcWlanDrvBinding.DriverBindingHandle,
				 &gEfiPciIoProtocolGuid
				 );
	if (EFI_ERROR (Status)) {
		DbgError("Test ControllerHandle fail Status = %r\n", Status);
		return Status;
	}

	//
  	// If ChildHandle is not NULL, then make sure this driver produced ChildHandle
  	//
	if (ChildHandle != NULL) {
	Status = EfiTestChildHandle (
				ControllerHandle,
				ChildHandle,
				&gEfiPciIoProtocolGuid
				);
		if (EFI_ERROR (Status)) {
			DbgError("Test ChildHandle fail Status = %r\n", Status);
			return Status;
		}
	}

	//
	// Check input parameters
	//
	if (Language == NULL || ErrorType == NULL ||
	  	BufferSize == NULL || Buffer == NULL ||
	  	(DiagnosticType >= EfiDriverDiagnosticTypeMaximum)) {
	  	DbgError("Invalid para Language = 0x%x, ErrorType = 0x%x BufferSize = 0x%x Buffer = 0x%x DiagnosticType = %d\n",
			Language, ErrorType, BufferSize, Buffer, DiagnosticType);
		return EFI_INVALID_PARAMETER;
	}
	
	//
	// Make sure Language is in the set of Supported Languages
	//
	SupportedLanguages = This->SupportedLanguages;
	Rfc4646Language = (BOOLEAN)(This == &gWlanUefiDiagnostics2);
	Found = FALSE;
	while (*SupportedLanguages != 0) {
		if (Rfc4646Language) {
		  for (Index = 0; SupportedLanguages[Index] != 0 && SupportedLanguages[Index] != ';'; Index++);
		  if ((AsciiStrnCmp (SupportedLanguages, Language, Index) == 0) &&
		      (Language[Index] == 0)) {
		    Found = TRUE;
		    break;
		  }
		  SupportedLanguages += Index;
		  for (; *SupportedLanguages != 0 && *SupportedLanguages == ';'; SupportedLanguages++);
		} else {
		  if (CompareMem (Language, SupportedLanguages, 3) == 0) {
		    Found = TRUE;
		    break;
		  }
		  SupportedLanguages += 3;
		}
	}

	//
	// If Language is not a member of SupportedLanguages, then return EFI_UNSUPPORTED
	//
	if (!Found) {
		DbgError("Language is not a member of SupportedLanguages.");
		return EFI_UNSUPPORTED;
	}

	if (ChildHandle == NULL) {
		//
		// Perform Diagnostics Algorithm on the bus controller specified
		// by ControllerHandle for the type of diagnostics requested in
		// DiagnosticsType
		//
		// Return results in ErrorType, Buffer, and BufferSize
		//
		// If Diagnostics Algorithm fails, then return EFI_DEVICE_ERROR
		//
	} else {
		//
		// Perform Diagnostics Algorithm on child controller specified
		// by ChildHandle for the type of diagnostics requested in
		// DiagnosticsType
		//
		// Return results in ErrorType, Buffer, and BufferSize
		//
		// If Diagnostics Algorithm fails, then return EFI_DEVICE_ERROR
		//
	}

	return EFI_SUCCESS;
}

