/**
 @file PcieAcpiUpdate.c

  Implements update to ACPI platform variable based on the results of link
  training.

  Copyright (c) 2018-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

**/


/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ----    ----------------------------------------------------------
 12/18/20   yg      Migrated to new interface
 10/23/18   tselvam Initial version for PCI ACPI platform configuration
=============================================================================*/

#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIAcpiPlatform.h>
#include <Library/PcieConfigLib.h>
#include <Library/DebugLib.h>
#include <Guid/Acpi.h>
#include <IndustryStandard/Acpi.h>

/* PCIe Library macros used by ACPI module within the Lib */
#define AML_32_BIT_VAR_SIZE      0xA
/* Round off the root port index in range 0 to 9 */
#define INT_TO_ASCII(x)          (48 + ((x)%10))
#define ASCII_TO_INT(x)          (((x) - 48)%10)

#define PRP_SIGNATURE            (SIGNATURE_32('0', 'P', 'R', 'P'))
/*===========================================================================*/
/*                             PRE PROCESSORS                                */
/*===========================================================================*/
/*===========================================================================*/
/*                           FUNCTION DEFINITION                             */
/*===========================================================================*/

/***************************************************************************//**
 * @fn PcieConfigLibAmlVarPRPxUpdateCallback
 * @brief Update AML variable
 *
 * This is the callback function to modify ACPI variable
 * PRPx, where x denotes root hw port index 0,1,2...9
 * This function modifies the contents of PRPx variable to 'TRUE' if the link
 * training passed else assign 'FALSE'
 *
 * @param[in][out] AmlVariableBuffer Encoded AML variable buffer
 * @param[in] AmlVariableBufferSize  Size of the AML variable buffer.

 * @retval EFI_SUCCESS  The entry point is executed successfully.
 * @retval other        Some error occurred when executing this entry point.
 ******************************************************************************/
EFI_STATUS EFIAPI PcieConfigLibAmlVarPRPxUpdateCallback (
  IN OUT VOID         **AmlVariableBuffer,
  IN UINTN            AmlVariableBufferSize
  )
{
  AmlVariableEncoding *  VarEncoding;
  UINT8 DecodedPortIndex = 0;
  UINT32 PRPSignature = 0;

  /*
   * Sometimes accessing an invalid buffer caused data abort, so
   * check for the buffer size to be expected 10 bytes, if not return gracefully
   */
  if (AmlVariableBufferSize != AML_32_BIT_VAR_SIZE)
  {
    DEBUG((EFI_D_WARN, "%a: Invalid buffer size for PRPn.\r\n", __func__));
    return EFI_INVALID_PARAMETER;
  }

  /*
   * Check for NULL on buffer
   */
  if ((AmlVariableBuffer == NULL) || (*AmlVariableBuffer == NULL))
  {
    DEBUG((EFI_D_WARN, "%a: Invalid buffer address for PRPn.\r\n", __func__));
    return EFI_INVALID_PARAMETER;
  }

  /*
   * Assign the pointer that points the buffer to Variable encoding data
   * structure to meaningfully access the members
   */
  VarEncoding =  (AmlVariableEncoding *)*AmlVariableBuffer;

  /*
   * Make sure the variable Name carries the first three letters "PRP"
   * as expected by UEFI and stuff the fourth letter with '0'
   * to compare with predefined signature to make sure we are dealing
   * with right PRPn variable before decoding Root port index from
   * AML variable name passed by ACPIPlatformDxe
   */
  PRPSignature = SIGNATURE_32('0',
                              VarEncoding->AmlVariableName[2],
                              VarEncoding->AmlVariableName[1],
                              VarEncoding->AmlVariableName[0]);

  if ( PRPSignature != PRP_SIGNATURE)
  {
    DEBUG((EFI_D_ERROR, "%a: Invalid Variable.\r\n", __func__));
    return EFI_INVALID_PARAMETER;
  }

  /*
   * If the signature matches, convert the last character to numerics
   * from ASCII
   */
  DecodedPortIndex = ASCII_TO_INT(VarEncoding->AmlVariableName[3]);

  DEBUG ((EFI_D_INFO, "Enabled PCI %d in ACPI\r\n", DecodedPortIndex));

  /* Port selection is already filtered while registering based on link up
   * result, so no more need for confirmation on the port is required.
   * Assign a simple BOOLEAN TRUE/FALSE value to the AML variabe to
   * indicate the state of link training on this root port
   */
  *(UINT32 *)((CHAR8 *)(*AmlVariableBuffer) + AML_NAMESPACE_HEADER_SIZE) = TRUE;

  return EFI_SUCCESS;
}

/***************************************************************************//**
 * @fn PcieConfigLibSetACPIPlatCallback
 * @brief Sets call back with ACPIPlatformDxe
 *
 * Sets up ACPI callback with ACPI Platform to update PRPx AML variable
 *
 * @param[in] HwPortIndex, Index of root port as defined by IPCAT
 *
 * @return EFI_SUCCESS or appropriate error value
 ******************************************************************************/
EFI_STATUS PcieConfigLibSetACPIPlatCallback (UINT32 HwPortIndex)
{
  EFI_QCOM_ACPIPLATFORM_PROTOCOL *pEfiAcpiPlatformProtocol = NULL;
  /*
   * create an AML variable to register for using the standard signature "PRP"
   * and the root port index to which this variable belongs to by converting
   * the incoming root port index to an ASCII value
   */
  CHAR8 AmlVariablePRPx[AML_NAMESTRING_LENGTH] = {'P', 'R', 'P',
                                                  INT_TO_ASCII(HwPortIndex)};
  EFI_STATUS  Status;

  /*
   * Locate the AcpiPlatform protocol
   */
  Status = gBS->LocateProtocol(&gQcomAcpiPlatformProtocolGuid,
                              NULL, (VOID**) &pEfiAcpiPlatformProtocol);
  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_WARN, "%a: Locate ACPI Protocol failed, Status = (0x%p)\r\n",
                       __func__, Status));
    goto Exit;
  }

  Status = pEfiAcpiPlatformProtocol->AmlVariableRegister(
             pEfiAcpiPlatformProtocol, AmlVariablePRPx,
             GETMODE_PREFIX, NULL, PcieConfigLibAmlVarPRPxUpdateCallback);

  if (EFI_ERROR(Status))
  {
    DEBUG((EFI_D_WARN, "%a: PRP%u variable callback register failed, Status = (0x%x)\r\n",
                      __func__, HwPortIndex, Status));
    goto Exit;
  }

Exit:
  return Status;
}
