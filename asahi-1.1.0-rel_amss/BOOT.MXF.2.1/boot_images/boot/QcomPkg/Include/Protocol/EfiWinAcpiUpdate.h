/**
@file  EFIWinAcpiUpdate.h
@brief Win DSDT Update UEFI Protocol definitions.
*/
/*=============================================================================
Copyright (c) 2016-2023 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when         who     what, where, why
--------     ---     -----------------------------------------------------------
03/16/2023   vb      Additional partial good fixes support for Hamoa
12/22/2022   vbu     Added partial goods support for Hamoa
02/27/2018   ltg     Added Poipu related changes
02/17/2017   vinitb  Added qccdi option related changes
01/30/2017   vinitb  Added sensors/gpu option related changes
09/12/2016   ltg     Updated as per new design
09/08/2016   mfc     Initial revision

=============================================================================*/

#ifndef __EFI_WIN_ACPI_UPDATE_H__
#define __EFI_WIN_ACPI_UPDATE_H__

/*===========================================================================
INCLUDE FILES
===========================================================================*/

/*===========================================================================
MACRO DECLARATIONS
===========================================================================*/
/** @ingroup efi_WIN_ACPI_UPDATE_constants
Protocol version. */
#define EFI_WIN_ACPI_UPDATE_PROTOCOL_REVISION 0x0000000000010001

/* Protocol GUID definition */
#define EFI_WIN_ACPI_UPDATE_PROTOCOL_GUID \
        {0x9349b7b6, 0xb924, 0x4321, {0x8e, 0x6d, 0x5, 0x6b, 0x3f, 0xfa, 0xc3, 0x80 }}

/*===========================================================================
EXTERNAL VARIABLES
===========================================================================*/
/** @cond */
/* External reference to the WinAcpiUpdate Protocol GUID. */
extern EFI_GUID gEfiWinAcpiUpdateProtocolGuid;

/*===========================================================================
TYPE DEFINITIONS
===========================================================================*/
/* Protocol declaration */
typedef struct _EFI_WIN_ACPI_UPDATE_PROTOCOL EFI_WIN_ACPI_UPDATE_PROTOCOL;
/** @endcond */

/** @cond */
/** Type definition for the #EFI_WIN_ACPI_TYPE enumeration. */
typedef enum _EFI_WIN_ACPI_PART_TYPE EFI_WIN_ACPI_PART_TYPE;
/** @endcond */
/**
Feature information. The information is part of the input
to SETDEFECTIVEPARTSVARIABLE API.
*/
enum _EFI_WIN_ACPI_PART_TYPE
{
    EFI_WIN_ACPI_PART_GPU = 0,
    EFI_WIN_ACPI_PART_Video,
    EFI_WIN_ACPI_PART_Camera,
    EFI_WIN_ACPI_PART_Display,
    EFI_WIN_ACPI_PART_Audio,
    EFI_WIN_ACPI_PART_Modem,
    EFI_WIN_ACPI_PART_WLAN,
    EFI_WIN_ACPI_PART_COMP,
	EFI_WIN_ACPI_PART_Sensors,
	EFI_WIN_ACPI_PART_NPU,
	EFI_WIN_ACPI_PART_SPSS,
	EFI_WIN_ACPI_PART_NAV,
	EFI_WIN_ACPI_PART_COMPUTE_1,
	EFI_WIN_ACPI_PART_DISPLAY_1,
	EFI_WIN_ACPI_PART_NSP,
    EFI_WIN_ACPI_PART_MAX
};

/*===========================================================================
FUNCTION DEFINITIONS
===========================================================================*/
/* EFI_SETDEFECTIVEPARTSVARIABLE */
/** @ingroup efi_setdefectivepartsvariable
@par Summary
This API saves the local configuration mask to a UEFI variable.
Reboot is requried to take the configuration into effect.

@param[in]  This              Pointer to the WIN_ACPI_UPDATE_PROTOCOL instance.

@par Description
This function saves the local configuration bit mask to the UEFI variable.

@return
EFI_SUCCESS           -- Function completed successfully. \n
EFI_XXXX              -- Other errors; refer to @xhyperref{R1,[R1]} for
details.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_SETDEFECTIVEPARTSVARIABLE)(
    IN  EFI_WIN_ACPI_UPDATE_PROTOCOL        *This,
    IN  EFI_WIN_ACPI_PART_TYPE              Part_Type,
    IN  BOOLEAN                             Enable
);

/* EFI_GETDEFECTIVEPARTSVARIABLE */
/** @ingroup efi_getdefectivepartsvariable
@par Summary
This API copies the local configuration mask to input pointer passed by caller.

@param[in]  This              Pointer to the WIN_ACPI_UPDATE_PROTOCOL instance.
@param[out] dpBitMask         Pointer to the UINT32 variable to save local configuration mask.

@par Description
This API copies the local configuration mask to input pointer passed by caller.

@return
EFI_SUCCESS           -- Function completed successfully. \n
EFI_XXXX              -- Other errors; refer to @xhyperref{R1,[R1]} for
details.
*/
typedef
EFI_STATUS
(EFIAPI *EFI_GETDEFECTIVEPARTSVARIABLE)(
    IN  EFI_WIN_ACPI_UPDATE_PROTOCOL        *This,
    OUT UINT32             					*dpBitMask
);

/*===========================================================================
PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_win_acpi_update_protocol
@par Summary
EFI_WIN_ACPI_UPDATE_PROTOCOL Protocol interface.
*/
struct _EFI_WIN_ACPI_UPDATE_PROTOCOL {
    UINT64							Revision;
    EFI_SETDEFECTIVEPARTSVARIABLE	SetDefectivePartsVariable;
    EFI_GETDEFECTIVEPARTSVARIABLE	GetDefectivePartsVariable;
};

#endif	/* __EFI_WIN_ACPI_UPDATE_H__ */
