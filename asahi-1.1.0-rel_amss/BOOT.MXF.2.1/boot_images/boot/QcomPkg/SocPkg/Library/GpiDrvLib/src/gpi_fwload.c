/**
 * @file  gpi_fwload.c
 * @brief Implements the firmware loading procedure for GSI and associated SEs 
 */
/*
===============================================================================

                               Edit History

$Header:

when       who     what, where, why
--------   ---     ------------------------------------------------------------
02/03/23   vs      Added to  retry partition 'qupfw_a' if read of 'qupfw' fails
08/17/22   var     Added error logging support for PIL authentication
10/06/22   STR     Added Support to load firmware from NAND
04/11/17   ts      Created to load qupv3 firmware from flash

===============================================================================
              Copyright (c) 2023 QUALCOMM Technologies, Inc.
                         All Rights Reserved.
            Qualcomm Technologies Proprietary and Confidential.
===============================================================================
*/

#include <Library/UefiBootServicesTableLib.h>
#include <Library/QcomLib.h>
#include <Include/scm_sip_interface.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/BootConfig.h>
#include <Protocol/EFIScm.h>
#include <Protocol/EFINandIo.h>
#include <Library/DebugLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/TzDiag.h>
#include "gpi_ee.h"

#ifndef GPI_NAND_DEVICE_ID
#define GPI_NAND_DEVICE_ID  (0)
#endif

#ifndef QUPFW_PARTITION_NAME
#define QUPFW_PARTITION_NAME "qupfw"
#endif

#ifndef QUPFW_ALT_PARTITION_NAME
#define QUPFW_ALT_PARTITION_NAME "qupfw_a"
#endif






/* partition guid for QUPV3 firmware ELF in UFS */
STATIC EFI_GUID qupv3_fw_elf_partition_guid = { 0x21D1219F, 0x2ED1, 0x4AB4, { 0x93, 0x0A, 0x41, 0xA1, 0x6A, 0xE7, 0x5F, 0x7F } };

/* Global static variables */
STATIC UINT64 ScmParam[SCM_MAX_NUM_PARAMETERS];
STATIC UINT64 ScmResult[SCM_MAX_NUM_RESULTS];
STATIC QCOM_SCM_PROTOCOL * QcomScmProtocol = NULL;  

extern EFI_STATUS  efi_split_elf_file(void *  elf_base, void ** meta_base, void ** prog_base, void *  prog_size);
EFI_STATUS gpi_log_time_ms(CHAR8 *name);

struct gpi_nand_info_type
{
  EFI_NAND_IO_PROTOCOL *nand_io_protocol;
  struct nand_info info;
};


STATIC inline EFI_STATUS gpi_tz_pil_init_id(UINT64 ELFMetaBase)
{
  EFI_STATUS Status = EFI_LOAD_ERROR;

  /* Subsys ID */
  ScmParam[0] = 0x13;
  /* Memory address of ELF meta data */
  ScmParam[1] = ELFMetaBase;

  if (QcomScmProtocol == NULL)
  {
    return Status;
  }

  /*
   * Authenticate ELF meta data with PIL
   */
  Status = QcomScmProtocol->ScmSipSysCall(QcomScmProtocol,
                                 TZ_PIL_INIT_ID,
                                 TZ_PIL_INIT_ID_PARAM_ID,
                                 ScmParam,
                                 ScmResult);

  return Status;
}

STATIC inline EFI_STATUS gpi_tz_pil_mem_id(UINT64 imageBase, UINTN imageSize)
{
  EFI_STATUS Status = EFI_LOAD_ERROR;

  /* Subsys ID */
  ScmParam[0] = 0x13;
  /* Start address of the image to be loaded */
  ScmParam[1] = imageBase; 
  /* Length of the image to be loaded */
  ScmParam[2] = (UINT64)imageSize;

  if (QcomScmProtocol == NULL)
  {
    return Status;
  }

  /*
   * Confirms the memory address to be loaded is different
   * than in the ELF
   */
  Status = QcomScmProtocol->ScmSipSysCall(QcomScmProtocol,
                                 TZ_PIL_MEM_ID,
                                 TZ_PIL_MEM_ID_PARAM_ID,
                                 ScmParam,
                                 ScmResult);
  return Status;
}

STATIC inline EFI_STATUS gpi_tz_pil_auth_reset_id(void)
{
  EFI_STATUS Status = EFI_LOAD_ERROR;

  /* Subsys ID */
  ScmParam[0] = 0x13;

  if (QcomScmProtocol == NULL)
  {
    return Status;
  }

  /*
   * Authenticate and load the image
   */
  Status = QcomScmProtocol->ScmSipSysCall(QcomScmProtocol,
                                 TZ_PIL_AUTH_RESET_ID,
                                 TZ_PIL_AUTH_RESET_ID_PARAM_ID,
                                 ScmParam,
                                 ScmResult);

  return Status;
}

STATIC inline EFI_STATUS gpi_tz_pil_unlock_xpu_id(void)
{
  EFI_STATUS Status = EFI_LOAD_ERROR;

  /* Subsys ID */
  ScmParam[0] = 0x13;

  if (QcomScmProtocol == NULL)
  {
    return Status;
  }

  /*
   * Unlock the XPU and free the memory
   */
  Status = QcomScmProtocol->ScmSipSysCall(QcomScmProtocol,
                                 TZ_PIL_UNLOCK_XPU_ID,
                                 TZ_PIL_UNLOCK_XPU_ID_PARAM_ID,
                                 ScmParam,
                                 ScmResult);
  
  return Status;
}

EFI_STATUS gpi_log_time_ms(CHAR8 *name)
{
#ifdef GPI_FWLOAD_LOGS_ENABLE
  DEBUG((EFI_D_ERROR, "%a = %d\n",name,GetTimerCountms() ));
#endif  
  return EFI_SUCCESS;
}

EFI_STATUS gpi_load_firmware(void)
{
  VOID                    * ElfBase = NULL;
  VOID                    * MetaBase = NULL;
  VOID                    * ProgSegBase = NULL;
  UINT32                    ProgSegSize = 0;
  EFI_BLOCK_IO_PROTOCOL   * pBlkIo;
  UINTN                     ImgSize = 0;
  UINT32                    Attribs = 0;
  HandleInfo                HandleInfoList[4];
  UINT32                    MaxHandles;
  PartiSelectFilter         HandleFilter;
  EFI_STATUS                Status = EFI_SUCCESS;
  NAND_STATUS 				nand_status = NAND_DEVICE_DONE;

  nand_handle_t gpi_nand_handle;
  const char *partition_name =  QUPFW_PARTITION_NAME;
  const char *alt_partition_name= QUPFW_ALT_PARTITION_NAME;
  EFI_NAND_IO_PROTOCOL *proto;
  struct nand_info *gpi_get_info;
  static struct gpi_nand_info_type gpi_nand_info;

  if(boot_from_nand())
  {
  	gpi_log_time_ms("#gpi_load_firmware for NAND function:enter");
		
	memset(&gpi_nand_info, 0, sizeof(gpi_nand_info));

	/* Locate the NAND partition GUID protocol. */
	Status = gBS->LocateProtocol(&gEfiNandIoProtocolGuid,
			NULL, (VOID **) &gpi_nand_info.nand_io_protocol);
	if (Status != EFI_SUCCESS)
	{
		DEBUG(( EFI_D_WARN, "Locate NAND partition GUID protocol Failed\n"));
		return -1;
	}
	proto = gpi_nand_info.nand_io_protocol;
	nand_status = proto->Open(GPI_NAND_DEVICE_ID,
    (const uint8 *)partition_name,&gpi_nand_handle);
	if (nand_status != NAND_DEVICE_DONE)
	{
		DEBUG(( EFI_D_WARN, "GPI NAND Open Failed for qupfw.. trying for qupfw_a..\n"));
    	nand_status = proto->Open(GPI_NAND_DEVICE_ID,(const uint8 *)alt_partition_name,&gpi_nand_handle);
      if (nand_status != NAND_DEVICE_DONE){
        DEBUG(( EFI_D_WARN, "GPI NAND Open Failed for  qupfw_a..\n"));
        return nand_status;
      }
		
	}
	gpi_get_info = &gpi_nand_info.info;
	nand_status = proto->GetInfo(gpi_nand_handle, gpi_get_info);
	if (nand_status != NAND_DEVICE_DONE)
	{
		DEBUG(( EFI_D_WARN, "GPI NAND GetInfo Failed\n"));	
			return nand_status;
	}  
	ImgSize = gpi_get_info->pages_per_block * gpi_get_info->page_size_bytes;
	if(ImgSize == 0)
	{
		DEBUG(( EFI_D_WARN, "Img Size not valid \n"));
		return EFI_OUT_OF_RESOURCES;
	}
	/* Allocate page aligned buffer for ELF buffer from flash */
  	ElfBase = UncachedAllocatePool (ImgSize);
  	if (ElfBase == NULL)
  	{
    	DEBUG(( EFI_D_WARN, "%a: Could not allocate uncached mem\r\n", __func__));
    	return EFI_OUT_OF_RESOURCES;
  	}
	/* Load the ELF image from NAND flash partition to DDR*/
	nand_status = proto->ReadPages(gpi_nand_handle, NAND_ACCESS_MAIN,0,gpi_get_info->pages_per_block, ElfBase, ImgSize);
	if (nand_status != NAND_DEVICE_DONE)
	{
		UncachedFreePool(ElfBase);
		DEBUG(( EFI_D_WARN, "GPI NAND Read Failed \n"));  
		return nand_status;
	}

  }
  else
  {
  	gpi_log_time_ms("#gpi_load_firmware function:enter");
  	/* Select the BlkIo handle that represents the partition by the
   	* referenced GUID type in GPT partition on Non removable media
   	* ie UFS device */
  	Attribs |= BLK_IO_SEL_MEDIA_TYPE_NON_REMOVABLE;
  	Attribs |= BLK_IO_SEL_PARTITIONED_GPT;
  	Attribs |= BLK_IO_SEL_MATCH_PARTITION_TYPE_GUID;

  	MaxHandles = sizeof(HandleInfoList)/sizeof(*HandleInfoList);
  	HandleFilter.PartitionType = &qupv3_fw_elf_partition_guid;
  	HandleFilter.VolumeName = 0;

  	Status = GetBlkIOHandles (Attribs, &HandleFilter, HandleInfoList, &MaxHandles);
  	if (EFI_ERROR (Status))
  	{
    	DEBUG(( EFI_D_WARN, "%a: GetBockIOHandles Failed\r\n", __func__));
    	return Status;
  	}
  	/* Having more than one partition is considered ambiguity, so return
   	* invalid param */
  	if (MaxHandles > 1)
  	{
    	DEBUG(( EFI_D_WARN, "%a: QUPV3 partition handle invalid\r\n", __func__));
    	return EFI_INVALID_PARAMETER;
  	}

  	if (MaxHandles == 0)
  	{
    	DEBUG(( EFI_D_WARN, "%a: QUPV3 ELF partition not found\r\n", __func__));
    	return EFI_NOT_FOUND;
  	}

  	/* Get the Block IO protocol instance from the handle */
  	pBlkIo = HandleInfoList[0].BlkIo;

  	/* Get the partition size and round it up to EFI_PAGE_SIZE */
  	ImgSize = (pBlkIo->Media->LastBlock + 1)* pBlkIo->Media->BlockSize;

  	/* Allocate page aligned buffer for ELF buffer from flash */
  	ElfBase = UncachedAllocatePool (ImgSize);
  	if (ElfBase == NULL)
  	{
    DEBUG(( EFI_D_WARN, "%a: Could not allocate uncached mem\r\n", __func__));
    return EFI_OUT_OF_RESOURCES;
  	}

  	/*
   	* Load the ELF image from flash partition to DDR
   	*/
  	Status = pBlkIo->ReadBlocks (pBlkIo, pBlkIo->Media->MediaId, 0, ImgSize, ElfBase);
  	if (EFI_ERROR (Status))
  	{
  		UncachedFreePool(ElfBase);
    	DEBUG(( EFI_D_WARN, "%a: Could not read ELF from UFS partition\r\n", __func__));
    	return Status;
  	}
  }

  /*
   * This function will take ELF buffer base as input and perform:
   *
   * 1. Parse the ELF buffer
   * 2. Create Meta buffer from the ELF buffer 
   * 3. Provide the base address for program segment within ELF buffer
   */
  Status = efi_split_elf_file(ElfBase, &MetaBase, &ProgSegBase, &ProgSegSize);
  if (EFI_ERROR (Status))
  {
    DEBUG(( EFI_D_WARN, "%a: Failed to parse ELF successfully\r\n", __func__));
    return Status;
  }

  gpi_log_time_ms("#efi_split_elf_file complete"); 
  
  Status = gBS->LocateProtocol (&gQcomScmProtocolGuid, NULL, (VOID**)&QcomScmProtocol);
  if (EFI_ERROR (Status))
  {
    DEBUG(( EFI_D_WARN, "%a: Failed to locate QcomScmProtocol\r\n", __func__));
    return Status;
  }
  gpi_log_time_ms("#gpi_tz_pil_init_start");
  /* TZ PIL init */
  Status = gpi_tz_pil_init_id((UINT64)MetaBase);
  if (EFI_ERROR (Status))
  {
    DEBUG(( EFI_D_WARN, "%a: Failed TZ_PIL_INIT\r\n", __func__));
    TZ_DIAG_LOG(DEFAULT_LOG_ID);
    return Status;
  }
  gpi_log_time_ms("#gpi_tz_pil_init_id complete");
  /*
   * Assign prog seg size till the end of ELF from the first prog seg base.
   * We are calculating this here because, the program segment should start
   * and end at 4K aligned address for XPU protection reasons
   */
  ProgSegSize = (ImgSize - ((uint8 *)ProgSegBase - (uint8 *)ElfBase));

  /* TZ PIL mem */
  Status = gpi_tz_pil_mem_id((UINT64)ProgSegBase, ProgSegSize);
  if (EFI_ERROR (Status))
  {
    DEBUG(( EFI_D_WARN, "%a: Failed TZ_PIL_MEM\r\n", __func__));
    return Status;
  }
  gpi_log_time_ms("#gpi_tz_pil_mem_id complete");
  /* TZ PIL auth reset */
  Status = gpi_tz_pil_auth_reset_id();
  if (EFI_ERROR (Status))
  {
    DEBUG(( EFI_D_WARN, "%a: Failed TZ_PIL_AUTH_RESET\r\n", __func__));
    TZ_DIAG_LOG(DEFAULT_LOG_ID);
    return Status;
  }
  gpi_log_time_ms("#gpi_tz_pil_auth_reset_id complete");
  /* TZ PIL unlock xpu */
  Status = gpi_tz_pil_unlock_xpu_id();
  if (EFI_ERROR (Status))
  {
    DEBUG(( EFI_D_WARN, "%a: Failed TZ_PIL_UNLOCK_XPU\r\n", __func__));
    return Status;
  } 
  gpi_log_time_ms("#gpi_tz_pil_unlock_xpu_id complete");
  
  return Status;
}
