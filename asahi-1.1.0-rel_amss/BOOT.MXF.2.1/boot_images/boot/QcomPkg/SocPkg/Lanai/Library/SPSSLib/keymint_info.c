/** @file
                        keymint_info.c

  This files contains the main internal functions that are used for sharing
  Keymint Info with SPU.

  Copyright (c) 2022-2023, Copyright Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/

/*=============================================================================
                EDIT HISTORY


 when       who    what, where, why
 --------   ---    ----------------------------------------------------------
 02/16/23   eb     Adjustments to reuse ABL structs and VBH
 11/24/22   eb     Initial version

=============================================================================*/

#include <HALhwio.h>
#include "HALbootHWIO.h"

#include <Library/QcomBaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>

#include <Protocol/Hash2.h>
#include <Protocol/EFISPSS.h>



/*===========================================================================*/
/*                  DEFINES                                                  */
/*===========================================================================*/

#define NUMBER_OF_WONCE_REGISTERS      16
#define WONCE_REGISTERS_DEFAULT_VALUE  0xFFFFFFFF

/* Magic number for Keymint_info_struct header*/
#define KEYMINT_INFO_MAGIC             0xFADEC0DE
#define KEYMINT_INFO_STRUCT_VERSION    0x0

/*===========================================================================*/
/*                  STRUCTS                                                  */
/*===========================================================================*/

typedef struct Keymint_info_struct_t {
  uint32_t start_magic_number;
  uint32_t struct_size;
  uint32_t offset;
  KeymintSharedInfoStruct keymint_shared_info;
  uint32_t end_magic_number;
} __attribute__((packed)) Keymint_info_struct;

/*===========================================================================*/
/*                  FUNCTION DECLARATIONS                                    */
/*===========================================================================*/

static EFI_STATUS keymint_info_write_to_wonce_regs(const EFI_HASH2_OUTPUT* Hash2Output, const UINTN hash_size);
static EFI_STATUS keymint_info_write_to_pil_region(const Keymint_info_struct* keymint_info);

EFI_STATUS keymint_info_install_protocol_interface();
EFI_STATUS EFIAPI keymint_info_share_with_spu(const KeymintSharedInfoStruct* keymint_shared_info );

/*===========================================================================*/
/*                  GLOBAL VARIABLES                                         */
/*===========================================================================*/

uint64_t pil_region_start_addr;
uint64_t pil_region_size;

// SPSS Protocol
QCOM_SPSS_PROTOCOL QCOMSPSSProtocol = {keymint_info_share_with_spu};

/*===========================================================================*/
/*                  FUNCTION DEFINITIONS                                    */
/*===========================================================================*/

EFI_STATUS keymint_info_write_to_wonce_regs(const EFI_HASH2_OUTPUT* Hash2Output, const UINTN hash_size)
{
  if(Hash2Output == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  uint32_t* hash_addr = (uint32_t*)(Hash2Output);
  uint32_t offset = 0;

  // Make sure the won't be an overflow
  if(hash_size / sizeof(uint32_t) > NUMBER_OF_WONCE_REGISTERS) {
    return EFI_BAD_BUFFER_SIZE;
  }

  // Only need 8 WONCE registers for the hash
  // Write hash to first 8 registers
  for(; offset < hash_size / sizeof(uint32_t); offset++) {
    out_dword(HWIO_TCSR_SYSTEM_IMAGES_HASH_0_ADDR + (sizeof(uint32_t)*offset), hash_addr[offset]);
  }

  // Write default value to rest of WONCE registers - request from Access Control in order to 'block' registers
  for(; offset < NUMBER_OF_WONCE_REGISTERS; offset++) {
    out_dword(HWIO_TCSR_SYSTEM_IMAGES_HASH_0_ADDR + (sizeof(uint32_t)*offset), WONCE_REGISTERS_DEFAULT_VALUE);
  }

  return EFI_SUCCESS;
}


EFI_STATUS keymint_info_write_to_pil_region(const Keymint_info_struct* keymint_info)
{
  if(keymint_info == NULL){
    return EFI_INVALID_PARAMETER;
  }

  // Write Boot Info to PIL region for SPU to read
  uintptr_t pil_addr = (pil_region_start_addr + pil_region_size - keymint_info->struct_size);
  CopyMem((void*)pil_addr, (CONST UINT8 *)keymint_info, keymint_info->struct_size);
  return EFI_SUCCESS;
}


EFI_STATUS EFIAPI keymint_info_share_with_spu(const KeymintSharedInfoStruct* keymint_shared_info)
{
  if(keymint_shared_info == NULL){
    return EFI_INVALID_PARAMETER;
  }

  uint32_t keymint_shared_info_struct_size = keymint_shared_info->BootInfo.Size + 
                                             keymint_shared_info->BootInfo.Offset +
                                             keymint_shared_info->RootOfTrust.RotSize +
                                             keymint_shared_info->RootOfTrust.RotOffset +
                                             sizeof(KMSetVbhReq);  

  if(keymint_shared_info->BootInfo.Version != KEYMINT_INFO_STRUCT_VERSION ||
     keymint_shared_info_struct_size != sizeof(KeymintSharedInfoStruct)) {
        return EFI_INCOMPATIBLE_VERSION;
  }

  EFI_STATUS status = EFI_DEVICE_ERROR;

  Keymint_info_struct* keymint_info = AllocateZeroPool(sizeof(Keymint_info_struct));
  if (keymint_info == NULL)
  {
    DEBUG((EFI_D_ERROR, "SPSSDxe:: %a MALLOC error. \r\n", __FUNCTION__));
    return EFI_OUT_OF_RESOURCES;
  }

  uint32_t copy_length = CopyMemS(&(keymint_info->keymint_shared_info),
                              sizeof(KeymintSharedInfoStruct),
                              keymint_shared_info,
                              keymint_shared_info_struct_size);

  if(copy_length != keymint_shared_info_struct_size) {
        status = EFI_BAD_BUFFER_SIZE;
        DEBUG((EFI_D_ERROR,
              "SPSSDxe:: %a CopyMemS of abl_keymint_shared_info failed! status: %r \r\n",
              __FUNCTION__,
              status ));
        goto exit;
  }

  keymint_info->start_magic_number = KEYMINT_INFO_MAGIC;  // Change magic number if struct changes
  keymint_info->end_magic_number = keymint_info->start_magic_number;
  keymint_info->offset = sizeof(keymint_info->start_magic_number) +
                         sizeof(keymint_info->struct_size) +
                         sizeof(keymint_info->offset);
  keymint_info->struct_size = keymint_info->offset +
                              keymint_shared_info_struct_size +
                              sizeof(keymint_info->end_magic_number);

  //Generating Hash on Boot Info so SPU can authenticate the data in PIL region
  EFI_HASH2_PROTOCOL *pEfiHash2Protocol = NULL;
  EFI_GUID *HashAlgorithm = &gEfiHashAlgorithmSha256Guid;
  EFI_HASH2_OUTPUT Hash2Output;
  UINTN hash_size = SHA256_SIZE;

  status = gBS->LocateProtocol(&gEfiHash2ProtocolGuid, NULL, (VOID **)&pEfiHash2Protocol);
  if (status != EFI_SUCCESS) {
    DEBUG((EFI_D_ERROR,
          "SPSSDxe:: %a LocateProtocol unsuccessful! status: %r \r\n",
          __FUNCTION__,
          status ));
    goto exit;
  }

  status = pEfiHash2Protocol->HashInit(pEfiHash2Protocol, HashAlgorithm);
  if (status != EFI_SUCCESS) {
    DEBUG((EFI_D_ERROR,
          "SPSSDxe:: %a HashInit unsuccessful! status:  %r \r\n",
          __FUNCTION__,
          status ));
    goto exit;
  }

  status = pEfiHash2Protocol->HashUpdate(pEfiHash2Protocol,
                                         (UINT8 *)(((UINT8 *)keymint_info) + keymint_info->offset),
                                         keymint_shared_info_struct_size);

  if (EFI_SUCCESS != status) {
    DEBUG((EFI_D_ERROR,
          "SPSSDxe:: %a HashUpdate unsuccessful! status:  %r \r\n",
          __FUNCTION__,
          status ));
    goto exit;
  }

  status = pEfiHash2Protocol->HashFinal(pEfiHash2Protocol, &Hash2Output);
  if (EFI_SUCCESS != status) {
    DEBUG((EFI_D_ERROR,
          "SPSSDxe:: %a HashFinal unsuccessful! status:  %r \r\n",
          __FUNCTION__,
          status ));
    goto exit;
  }
  

  status = keymint_info_write_to_wonce_regs(&Hash2Output, hash_size);
  if (status != EFI_SUCCESS) {
    DEBUG((EFI_D_ERROR,
          "SPSSDxe:: %a keymint_info_write_to_wonce_regs failed! status: %r \r\n",
          __FUNCTION__,
          status ));
    goto exit;
  }

  status = keymint_info_write_to_pil_region(keymint_info);
  if (status != EFI_SUCCESS) {
    DEBUG((EFI_D_ERROR,
          "SPSSDxe:: %a keymint_info_write_to_pil_region failed! status: %r \r\n",
          __FUNCTION__,
          status ));
    goto exit;
  }
  
  status = EFI_SUCCESS;

  exit:
    FreePool(keymint_info);
    return status;
}

// Add callback function for ABL code
EFI_STATUS keymint_info_install_protocol_interface()
{
  EFI_STATUS Status;
  EFI_HANDLE Handle = NULL;

  Status = gBS->InstallMultipleProtocolInterfaces(
      &Handle, &gEfiQcomSPSSProtocolGuid,
      (VOID **)&QCOMSPSSProtocol, NULL);

  return Status;
}