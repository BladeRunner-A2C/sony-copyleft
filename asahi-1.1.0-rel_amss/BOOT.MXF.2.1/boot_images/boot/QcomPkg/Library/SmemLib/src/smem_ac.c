/*=============================================================================

                        SMEM ACCESS CONTROL

 Copyright (c)  2021, 2023 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/02/16   ar      Initial version
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <comdef.h>
#include <seclib_ac.h>

#include "smem_type.h"
#include "smem_toc.h"
#include "smem_internal.h"
#include "smem_os.h"
#include "smem_target.h"
#include "smem_xbl_config.h"
/*===========================================================================
                      TYPE DEFINITIONS
===========================================================================*/
/* Typical size of SMEM is either 2MB or 1MB */
#define SMEM_AC_MAX_ALLOWED_SMEM_SIZE (0x000200000) /* 2MB  */
#define SMEM_AC_MIN_ALLOWED_SMEM_SIZE (0x000003000) /* 12KB */
#define SMEM_AC_MIN(a, b)             ((a) < (b) ? (a) : (b))
#define SMEM_AC_MAX(a, b)             ((a) > (b) ? (a) : (b))
#define SMEM_AC_PAGE_ALIGN_MASK       (0x00000FFF)
#define SMEM_AC_MIN_NUM_PARTITIONS    (2)

#define SMEM_AC_ERROR(...)             SMEM_OS_LOG_ERR(__VA_ARGS__)
#define SMEM_AC_FATAL(...)             SMEM_OS_LOG_FATAL(__VA_ARGS__)

#ifndef UINT_MAX
#define UINT_MAX 0xFFFFFFFF
#endif

/*=============================================================================
                       PUBLIC/GLOBAL DATA DEFINATIONS
=============================================================================*/
/* smem_targ_info_ptr and smem_targ_info_addr are initialized smem_targ_init() */
#if defined(MPROC_BOOT_PROC) 
extern smem_targ_info_type *smem_targ_info_ptr;
extern uint64              smem_targ_info_addr;
#endif /* MPROC_BOOT_PROC */

/* Flag is set to TRUE when access permissions are applied for SMEM partitions */
boolean smem_init_partitions_completed = FALSE;

/*===========================================================================
                      EXTERN FUNCTION PROTOTYPE
===========================================================================*/
extern ACSecDomainId smem_ac_host_to_vm_get(smem_host_type host);

/*===========================================================================
                      FUNCTION DEFINITIONS
===========================================================================*/
/*===========================================================================
FUNCTION      smem_ac_add
===========================================================================*/
/**
  Returns the sum of two inputs.
  This function does ERR_FATAL when integer overflows while doing addition.

  @param[in]  a   First input number.
  @param[in]  b   Second input number.

  @return
  Sum of inputs.
*/
/*=========================================================================*/
static uint32 smem_ac_add(uint32 a, uint32 b)
{
  if (a > (UINT_MAX - b))
  {
    SMEM_AC_FATAL(2, "Integer overflow while doing addition(0x%X, 0x%X).", a, b);
  }
  return (a + b);
}

/*===========================================================================
FUNCTION      smem_ac_add64
===========================================================================*/
/**
  Returns the sum of two 64bit inputs.
  This function does ERR_FATAL when 64bit integer overflows while doing addition.

  @param[in]  a   First input number.
  @param[in]  b   Second input number.

  @return
  Sum of inputs.
*/
/*=========================================================================*/
static uint64 smem_ac_add64(uint64 a, uint64 b)
{
  if (a > (UINT64_MAX - b))
  {
    SMEM_AC_FATAL(4, "Integer overflow while doing addition(0x%08X%08X, 0x%08X%08X).", 
            (uint32)(a >> 32), (uint32)a, (uint32)(b >> 32), (uint32)b);
  }
  return (a + b);
}

/*===========================================================================
FUNCTION      smem_ac_mul
===========================================================================*/
/**
  Returns the multiplication of two inputs.
  This function does ERR_FATAL when integer overflows while doing addition.

  @param[in]  a   First input number.
  @param[in]  b   Second input number.

  @return
  multiplication of inputs.
*/
/*=========================================================================*/
static uint32 smem_ac_mul(uint32 a, uint32 b)
{
  if (b == 0)
  {
    return 0;
  }

  if (a > (UINT_MAX / b))
  {
    SMEM_AC_FATAL(2, "Integer overflow while doing multiplication(0x%X, 0x%X).", a, b);
  }
  return (a * b);
}

/*===========================================================================
FUNCTION      smem_ac_parts_overlapped
===========================================================================*/
/**
  Check if partitions are overlapped.
  Note: Partition sizes should not zero.

  @param[in]  part0_start   First partition start.
  @param[in]  part0_end     First partition end.
  @param[in]  part1_start   Second partition start.
  @param[in]  part1_end     Second partition end.

  @return
  TRUE, if partitions overlapped. Otherwise FALSE.
*/
/*=========================================================================*/
static boolean smem_ac_parts_overlapped
(
  uint32 part0_start,
  uint32 part0_end,
  uint32 part1_start,
  uint32 part1_end
)
{
  uint32 max_start = SMEM_AC_MAX(part0_start, part1_start);
  uint32 min_end   = SMEM_AC_MIN(part0_end, part1_end);

  if (min_end >= max_start)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/*===========================================================================
FUNCTION      smem_ac_perms_set
===========================================================================*/
/**
  Sets permission to SMEM partition.

  @param[in] smem_phys_base   SMEM physical base address.
  @param[in] part_offset      SMEM partition offset.
  @param[in] part_size        SMEM partition size.
  @param[in] hosts_perm    Hosts permission for toc_entry partition.

  @return
  None
*/
/*=========================================================================*/
static void smem_ac_perms_set
(
  uint64 smem_phys_base,
  uint32 part_offset,
  uint32 part_size,
  uint32              hosts_perm[SMEM_NUM_HOSTS]
)
{
#ifdef MPROC_BOOT_PROC /* MPROC_BOOT_PROC */
  ACSecDomainPerm               dest_list[SMEM_NUM_HOSTS];
  uint64                        start_addr;
  uint64                        end_addr;
  int                           err_code;
#endif
  uint16                        host;
  ACxPUPermission               permissions;
  uint32                        num_dests;

  memset(dest_list, 0, sizeof(dest_list));
  memset(&start_addr, 0, sizeof(start_addr));
  memset(&end_addr, 0, sizeof(end_addr));

  num_dests = 0;

  for (host = 0; host < SMEM_NUM_HOSTS; host++)
  {
    if ((hosts_perm[host]            == 0) ||
        (smem_ac_host_to_vm_get(host) == AC_SD_END_MARKER))
    {
      continue;
    }

    permissions = 0;
    if (hosts_perm[host] & SMEM_TOC_ENTRY_FLAGS_ENABLE_READ_PROTECTION)
    {
      permissions |= AC_READ_ONLY;
    }
    if (hosts_perm[host] & SMEM_TOC_ENTRY_FLAGS_ENABLE_WRITE_PROTECTION)
    {
      permissions |= AC_READ_WRITE;
    }
    if (permissions == 0)
    {
      continue;
    }
#ifdef MPROC_BOOT_PROC
    dest_list[num_dests].sdId     = smem_ac_host_to_vm_get(host);
    dest_list[num_dests].perm = permissions;
#endif
    if (dest_list[num_dests].sdId == AC_SD_AP_NSEC || dest_list[num_dests].sdId == AC_SD_AP_SEC)
	{
		dest_list[num_dests].lock = true;
	}
    num_dests++;
  }

  if (num_dests == 0)
  {
    /* No hosts needs set access control for this pertition */
    return;
  }

#ifdef MPROC_BOOT_PROC
  start_addr = smem_ac_add64(smem_phys_base, part_offset);
  end_addr = smem_ac_add64(start_addr, part_size);

  /* call API to map XPU partition */
  err_code = ACxBLSCxPUProtectRegion(start_addr,
                        end_addr,
                        &dest_list[0],
                        num_dests,
                        false);
  if (err_code != 0)
  {
    SMEM_AC_FATAL(1, "XBL Permissions assign failed with err=%d", err_code);
  }
#endif
}

/*===========================================================================
FUNCTION      smem_ac_ssr_smem_dump_allow
===========================================================================*/
/**
  Checks whether it is secure device and debug enabled or not. 
  For SSR SMEM dump collection APPS should have read permission to the 
  non-APPS SMEM partitions only for non-secure device and secure device 
  with debug enabled.

  @param
  None
  
  @return
  TRUE, if SSR SMEM dump collection is allowed. Otherwise returns FALSE.
  
*/
/*=========================================================================*/
static boolean smem_ac_ssr_smem_dump_allow(void)
{
  /* Currently disabled for Wildcat since APPS is not registering with the 
     PIL framework to dump SMEM in case of any image's SSR */
  return FALSE;
}

/*===========================================================================
FUNCTION      smem_ac_hosts_perm
===========================================================================*/
/**
  Get the hosts permissions for a SMEM partition.

  @param[in]  toc_entry     Partition entry in TOC
  @param[out] hosts_perm    Hosts permission for toc_entry partition

  @return
  Returns hosts permission for toc_entry partition in hosts_perm.
*/
/*=========================================================================*/
static void smem_ac_hosts_perm
(
  smem_toc_entry_type *toc_entry,
  uint32              hosts_perm[SMEM_NUM_HOSTS]
)
{
  smem_host_type host0 = (smem_host_type)toc_entry->host0;
  smem_host_type host1 = (smem_host_type)toc_entry->host1;
  uint16 host;
  uint32 permissions;

  /* Initialize the hosts permission table */
  memset(hosts_perm, 0, sizeof(uint32) * SMEM_NUM_HOSTS);

  /* If size is 0, there is no partition to configure */
  if (!toc_entry->size)
  {
    return;
  }

  permissions = toc_entry->flags & SMEM_TOC_ENTRY_FLAGS_ENABLE_RW_PROTECTION;

  if ((host0 == SMEM_INVALID_HOST && host1 == SMEM_INVALID_HOST) ||
      (host0 == SMEM_COMMON_HOST  && host1 == SMEM_COMMON_HOST))
  {
    /* Partition is either legacy or common or TOC partition */
    for (host = 0; host < SMEM_NUM_HOSTS; host++)
    {
      hosts_perm[host] = permissions;
    }
  }
  else if (host0 != SMEM_INVALID_HOST && host0 < SMEM_NUM_HOSTS &&
           host1 != SMEM_INVALID_HOST && host1 < SMEM_NUM_HOSTS)
  {
    hosts_perm[host0] = permissions;
    hosts_perm[host1] = permissions;

#ifndef SMEM_TZ_HOST_NOT_SUPPORTED
    /* TZ should have permission to MPSS-SPSS partition */
    if ((host0 == SMEM_MODEM && host1 == SMEM_SPSS_SP) ||
        (host1 == SMEM_MODEM && host0 == SMEM_SPSS_SP))
    {
      hosts_perm[SMEM_TZ] = permissions;
    }
#endif /* SMEM_TZ_HOST_NOT_SUPPORTED */
  }
  
  if (hosts_perm[SMEM_TME] == 0 &&
      hosts_perm[SMEM_MODEM] == 0 &&
	  hosts_perm[SMEM_SPSS_SP] == 0 &&
	  hosts_perm[SMEM_RPM] == 0)
  {
    for (host = 0; host < SMEM_NUM_HOSTS; host++)
    {
      hosts_perm[host] = 0;
    }
  }

  /* Add APSS to list of VMs for RO access */
  if ((TRUE == smem_ac_ssr_smem_dump_allow()) &&
      (hosts_perm[SMEM_APPS] == 0))
  {
    hosts_perm[SMEM_APPS] = SMEM_TOC_ENTRY_FLAGS_ENABLE_READ_PROTECTION;
  }
}

/*===========================================================================
FUNCTION      smem_ac_hosts_validate
===========================================================================*/
/**
  Validate SMEM partition's hosts.

  @param[in]  toc_entry     SMEM TOC partition entry.

  @return
  TRUE, if hosts are valid. Otherwise FALSE.
*/
/*=========================================================================*/
static boolean smem_ac_hosts_validate
(
  smem_toc_entry_type *toc_entry
)
{
  /* Both hosts either SMEM_INVALID_HOST/SMEM_COMMON_HOST or less then SMEM_NUM_HOSTS */
  if ((toc_entry->host0 == SMEM_INVALID_HOST) && (toc_entry->host1 == SMEM_INVALID_HOST))
  {
    return TRUE;
  }
  else if ((toc_entry->host0 == SMEM_COMMON_HOST) && (toc_entry->host1 == SMEM_COMMON_HOST))
  {
    return TRUE;
  }
  else if ((toc_entry->host0 < SMEM_NUM_HOSTS) && (toc_entry->host1 < SMEM_NUM_HOSTS))
  {
    return TRUE;
  }
  else
  {
    SMEM_AC_ERROR(3, "SMEM TOC entry has invalid hosts, entry=0x%08X, host0=%d, "
          "host1=%d.", toc_entry, toc_entry->host0, toc_entry->host1);
    return FALSE;
  }
}

/*===========================================================================
FUNCTION      smem_ac_toc_entry_validate
===========================================================================*/
/**
  Verifies the SMEM TOC partition entry.

  @param[in] toc_header    SMEM TOC header address.
  @param[in] toc_entry     SMEM TOC partition entry.
  @param[in] entry_indx    SMEM TOC entry index.
  @param[in] smem_size     SMEM size.

  @return
  Returns True if TOC entry is valid otherwise returns False.
*/
/*=========================================================================*/
static boolean smem_ac_toc_entry_validate
(
  smem_toc_type       *toc_header,
  smem_toc_entry_type *toc_entry,
  uint32              entry_indx,
  uint32              smem_size
)
{
  uint32 other_entry_indx;
  uint32 part_end_offset;

  /* First TOC partition entry should be TOC itself */
  if (entry_indx == 0)
  {
    if ((toc_entry->offset != (smem_size - SMEM_TOC_SIZE)) ||
        (toc_entry->size   != SMEM_TOC_SIZE)                               ||
        (toc_entry->flags  != SMEM_TOC_ENTRY_FLAGS_ENABLE_READ_PROTECTION) ||
        (toc_entry->host0  != SMEM_INVALID_HOST)                           ||
        (toc_entry->host1  != SMEM_INVALID_HOST))
    {
      SMEM_AC_ERROR(1, "SMEM TOC partition entry is invalid, toc_entry=0x%08X", toc_entry);
      return FALSE;
    }
  }
  else
  {
    /* Partition size should not be zero and it should be multiples of 4KB */
    if ((toc_entry->size == 0) ||
        ((toc_entry->size & SMEM_AC_PAGE_ALIGN_MASK) != 0))
    {
      SMEM_AC_ERROR(1, "SMEM TOC entry size is invalid, toc_entry=0x%08X", toc_entry);
      return FALSE;
    }

    if ((toc_entry->offset > (smem_size - SMEM_TOC_SIZE)) ||
        (toc_entry->size   > (smem_size - SMEM_TOC_SIZE)) ||
        (smem_ac_add(toc_entry->offset, toc_entry->size) > (smem_size - SMEM_TOC_SIZE)))
    {
      SMEM_AC_ERROR(1, "SMEM TOC entry out of SMEM, toc_entry=0x%08X", toc_entry);
      return FALSE;
    }

    if (!smem_ac_hosts_validate(toc_entry))
    {
      return FALSE;
    }
  }

  part_end_offset = smem_ac_add(toc_entry->offset, toc_entry->size) - 1;

  /* Check for partition overlaps with other partitions */
  for (other_entry_indx = entry_indx + 1; other_entry_indx < toc_header->num_entries; other_entry_indx++)
  {
    smem_toc_entry_type *other_toc_entry = &toc_header->entry[other_entry_indx];

    if (other_toc_entry->size == 0)
    {
      SMEM_AC_ERROR(1, "SMEM TOC entry size is not valid, other_toc_entry=0x%08X",
            other_toc_entry);
      return FALSE;
  }

    if (smem_ac_parts_overlapped(toc_entry->offset,  part_end_offset, other_toc_entry->offset, 
                          smem_ac_add(other_toc_entry->offset, other_toc_entry->size) - 1))
  {
      SMEM_AC_ERROR(2, "SMEM TOC partitions are overlapped, toc_entry=0x%08X, "
            "other_toc_entry=0x%08X.", toc_entry, other_toc_entry);
      return FALSE;
    }
  }

    return TRUE;
}

/*===========================================================================
FUNCTION      smem_toc_validate
===========================================================================*/
/**
  Verifies the SMEM TOC.

  @param[in] smem_base         SMEM virtual base address.
  @param[in] smem_phys_base    SMEM physical base address.
  @param[in] smem_size         SMEM size.
  @param[in] max_toc_size      Max SMEM TOC size allowed.

  @return
  Returns True if TOC is valid, otherwise returns False.
*/
/*=========================================================================*/
static boolean smem_toc_validate
(
  uint8   *smem_base,
  uint64  smem_phys_base,
  uint32  smem_size,
  uint32  max_toc_size
)
{
  smem_toc_type *toc_header;
  uint32        total_toc_size;
  uint32        entry_indx;
  uint32        total_prtn_size;

  /* Last 4KB of SMEM is the TOC.
   * It starts with header anf followed by partition entries */
  toc_header = (smem_toc_type *)(smem_base + smem_size - SMEM_TOC_SIZE);

  /* Check the TOC has been initalized or not */
  if (toc_header->identifier != SMEM_TOC_IDENTIFIER)
  {
    SMEM_AC_ERROR(2, "SMEM TOC is not initalized. size=0x%08X, TOC_ID=0x%08X.",
            smem_size, toc_header->identifier);
    return FALSE;
  }

  /* Validated the TOC header */
  if (toc_header->version != SMEM_TOC_VERSION)
  {
    SMEM_AC_ERROR(2, "SMEM TOC version is not supported. version=0x%08X, "
        "supported_version=0x%08X.", toc_header->version, SMEM_TOC_VERSION);
    return FALSE;
  }

  /* Validate the num_entries */
  if (toc_header->num_entries < SMEM_AC_MIN_NUM_PARTITIONS)
  {
    SMEM_AC_ERROR(2, "SMEM TOC %d is the least expected num of partition entries, current %d.",
        SMEM_AC_MIN_NUM_PARTITIONS, toc_header->num_entries);
    return FALSE;
  }
  
  /* Validate the total TOC size needed */
  total_toc_size = smem_ac_mul(toc_header->num_entries, sizeof(smem_toc_entry_type));
  total_toc_size = smem_ac_add(sizeof(smem_toc_type), total_toc_size);
  if (total_toc_size > max_toc_size)
  {
    SMEM_AC_ERROR(1, "SMEM TOC invalid num_entries=0x%08X.", toc_header->num_entries);
    return FALSE;
  }

  /* Validate the TOC partition entries */
  for (total_prtn_size = 0, entry_indx = 0; entry_indx < toc_header->num_entries; entry_indx++)
  {
    smem_toc_entry_type *toc_entry = &toc_header->entry[entry_indx];

    if (!smem_ac_toc_entry_validate(toc_header, toc_entry, entry_indx, smem_size))
    {
      return FALSE;
    }

    /* Keep track of running total of partition sizes */
    total_prtn_size = smem_ac_add(total_prtn_size, toc_entry->size);

    /* Make sure sum of all partitions is not greater than
     * smem_size  */
    if (total_prtn_size > smem_size)
  {
      SMEM_AC_ERROR(1, "End of SMEM reached at %d bytes.", total_prtn_size);
      return FALSE;
    }
  }

    return TRUE;
}

/*===========================================================================
FUNCTION      smem_ac_targ_info_validate
===========================================================================*/
/**
  Verifies the SMEM target info.
  It also cross checks the smem_phys_base and smem_size before and after applying
  the access protection to TOC.
  It maps the SMEM physical base to virtual address.

  @param[in]    targ_info_ptr         SMEM target info virtual address.
  @param[in]    targ_info_addr        SMEM target info physical address.
  @param[inout] smem_phys_base_ptr    SMEM base physical address.
  @param[inout] smem_size_ptr         SMEM size.
  @param[out]   smem_base_ptr         SMEM base virtual address.

  @return
  Returns True if SMEM target info is valid, otherwise returns False.
*/
/*=========================================================================*/
static boolean smem_ac_targ_info_validate
(
  smem_targ_info_type *targ_info_ptr,
  uint64              targ_info_addr,
  uint64              *smem_phys_base_ptr,
  uint32              *smem_size_ptr,
  uint8               **smem_base_ptr
)
{
  uint32 smem_size;
  uint64 smem_phys_base;
  uint64 toc_phys_base;
  uint64 toc_phys_end;

  if ((targ_info_addr == 0) || (targ_info_ptr == NULL))
  {
    SMEM_AC_ERROR(3, "Invalid smem_targ_info_addr=0x%08X%08X or smem_targ_info_ptr=0x%08X.",
            (uint32)(targ_info_addr >> 32), targ_info_addr, targ_info_ptr);
    return FALSE;
  }

  /* Validate SMEM target info is part of HLOS owned DDR region before applying the protection */
  /*if (*smem_size_ptr == 0)
  {
    if (!tzbsp_is_hlos_range(smem_targ_info_ptr, sizeof(smem_targ_info_type)))
    {
      SMEM_AC_ERROR(3, "SMEM target info is not in HLOS owned DDR region. " 
            "smem_targ_info_addr=0x%08X%08X, size=0x%08X.", (uint32)(smem_targ_info_addr >> 32),
            (uint32)smem_targ_info_addr, sizeof(smem_targ_info_type));
      return FALSE;
    }
  }*/

  /* Validate the SMEM Target info */
  if (targ_info_ptr->identifier != SMEM_TARG_INFO_IDENTIFIER)
  {
    SMEM_AC_ERROR(1, "Invalid smem_targ_info identifier=0x%08X.",
        targ_info_ptr->identifier);
    return FALSE;
  }

  smem_phys_base = targ_info_ptr->smem_base_phys_addr;
  smem_size      = targ_info_ptr->smem_size;

  /* Check for size bounds */
  if ((smem_size > SMEM_AC_MAX_ALLOWED_SMEM_SIZE) || 
      (smem_size < SMEM_AC_MIN_ALLOWED_SMEM_SIZE))
  {
    SMEM_AC_ERROR(1, "SMEM size is invalid %d.", smem_size);
    return FALSE;
  }

  /* Check SMEM target info is part of SMEM TOC partition */
  toc_phys_end  = smem_ac_add64(smem_phys_base, smem_size);
  toc_phys_base = toc_phys_end - SMEM_TOC_SIZE;
  if ((targ_info_addr <= toc_phys_base) ||
      (smem_ac_add64(targ_info_addr, sizeof(smem_targ_info_type)) > toc_phys_end))
  {
    SMEM_AC_ERROR(2, "SMEM targ info is not present in the SMEM TOC partition " \
            "smem_targ_info_addr=0x%08X%08X.", (uint32)(targ_info_addr >> 32), (uint32)targ_info_addr);
    return FALSE;
  }

  /* Validation SMEM base before applying access permissions */
  if (*smem_size_ptr == 0)
  {
    uint8 *smem_base;

    /* Map the SMEM base physical address to virtual address */
    smem_base = (uint8 *)smem_os_map_base_va((void *)(uintptr_t)smem_phys_base, smem_size);
    if (smem_base == NULL)
    {
      SMEM_AC_ERROR(3, "SMEM base addr=0x%08X%08X, size=%d memory mapping failed.",
            (uint32)(smem_phys_base >> 32), (uint32)smem_phys_base, smem_size);
      return FALSE;
    }
    
    /* Validate the SMEM region points to HLOS owned DDR region */
    /*if (!tzbsp_is_hlos_range(smem_base, smem_size))
    {
      SMEM_AC_ERROR(3, "SMEM region is not in HLOS owned DDR region. "
          "smem_phys_base=0x%08X%08X, smem_size=0x%08X.", (uint32)(smem_phys_base >> 32), 
          (uint32)smem_phys_base, smem_size);
      return FALSE;
    }*/

    /* Update the return values */
    *smem_phys_base_ptr = smem_phys_base;
    *smem_size_ptr      = smem_size;
    *smem_base_ptr      = smem_base;
  }
  else
  {
    uint64 earlier_base = *smem_phys_base_ptr;
    uint64 earlier_size = *smem_size_ptr;
    
    /* Validation after applying access permissions */
    if ((earlier_base != smem_phys_base) ||
        (earlier_size != smem_size))
    {
      SMEM_AC_ERROR(6, "SMEM targ info not matching earlier_base=0x%08X%08X, "
            "earlier_size==0x%X new_base=0x%08X%08X, new_size==0x%X.", 
            (uint32)(earlier_base >> 32), (uint32)earlier_base, (uint32)earlier_size,
            (uint32)(smem_phys_base >> 32), (uint32)smem_phys_base, (uint32)smem_size);
    return FALSE;
  }
  }

  return TRUE;
}


/*===========================================================================
FUNCTION      smem_ac_xbl_validate
===========================================================================*/
/**
  Verifies the SMEM target info and SMEM TOC. Returns the SMEM base
  physical address, SMEM size and SMEM base virtual address.

  @param[out]   smem_phys_base_ret   Returns SMEM base physical address.
  @param[in]    smem_size_ret        Returns SMEM size.

  @return
  Returns SMEM base virtual if validation success otherwise returns NULL.
*/
/*=========================================================================*/
#ifdef MPROC_BOOT_PROC
static uint8 *smem_ac_xbl_validate
(
  uint64 *smem_phys_base_ret,
  uint32 *smem_size_ret
)
{
  uint8  *smem_base;
  uint32 smem_size;
  uint64 smem_phys_base;
  uint32 hosts_perm[SMEM_NUM_HOSTS];
  smem_host_type smem_host;
  boolean result;

  smem_phys_base = 0;
  smem_size      = 0;
  smem_base      = NULL;

  /* Initialize the OS specific functionality */
  smem_os_init();

  /* Initialize the target specific functionality */
  smem_targ_init();

  /* Validate the SMEM target info.
   * smem_targ_info_ptr and smem_targ_info_addr are initalized in smem_targ_init */
  result = smem_ac_targ_info_validate(smem_targ_info_ptr,
                                      smem_targ_info_addr,
                                      &smem_phys_base,
                                      &smem_size,
                                      &smem_base);
  if (result == FALSE)
  {
    return NULL;
  }
  /*smem_phys_base = smem_targ_info_ptr->smem_base_phys_addr;
  smem_size  = smem_targ_info_ptr->smem_size;
  smem_base      = (uint8 *)smem_os_map_base_va((void *)(uintptr_t)smem_phys_base, smem_size);*/

  /* Apply Read only permission for SMEM TOC partition */
  for (smem_host = 0; smem_host < SMEM_NUM_HOSTS; smem_host++)
  {
    hosts_perm[smem_host] = SMEM_TOC_ENTRY_FLAGS_ENABLE_READ_PROTECTION;
  }

  smem_ac_perms_set(smem_phys_base,
                    smem_size - SMEM_TOC_SIZE,
                    SMEM_TOC_SIZE,
                    hosts_perm);

  /* Validate the SMEM target info again */
  result = smem_ac_targ_info_validate(smem_targ_info_ptr,
                                      smem_targ_info_addr,
                                      &smem_phys_base,
                                      &smem_size,
                                      &smem_base);
  if (result == FALSE)
  {
    return NULL;
  }
  
  /* Validate the SMEM TOC */
  result = smem_toc_validate(smem_base, smem_phys_base, smem_size,
              smem_targ_info_addr - (smem_phys_base + smem_size - SMEM_TOC_SIZE));
  if (result == FALSE)
  {
    return NULL;
  }

  /* Return the SMEM base physical address and SMEM size */
  if (smem_size_ret)
  {
    *smem_size_ret = smem_size;
  }
  if (smem_phys_base_ret)
  {
    *smem_phys_base_ret = smem_phys_base;
  }

  return smem_base;
}
#endif /* MPROC_BOOT_PROC */

/*===========================================================================
FUNCTION      smem_init_partitions
===========================================================================*/
/**
  Parses the shared memory table of contents (SMEM TOC) and enables XPU
  protection on regions of SMEM in TZ.

  @return
  none.
*/
/*=========================================================================*/
void smem_init_partitions(void)
{
  smem_toc_type       *toc_header;
  uint8               *smem_base;
  uint64        smem_phys_base;
  uint32              smem_size;
  uint32        entry_indx;
  
  smem_base = smem_ac_xbl_validate(&smem_phys_base, &smem_size);
  if (smem_base == NULL)
  {
    SMEM_AC_FATAL(0, "smem_ac_validate failed!");
    return;
  }

  /* Point to start of TOC */
  toc_header = (smem_toc_type *)(smem_base + smem_size - SMEM_TOC_SIZE);

  /* Apply access permissions for every SMEM partition.
   * Skip TOC partition, as permissions already applied */
  for (entry_indx = 1; entry_indx < toc_header->num_entries; entry_indx++)
    {
    smem_toc_entry_type *toc_entry = &toc_header->entry[entry_indx];
    uint32              hosts_perm[SMEM_NUM_HOSTS];

    /* Get hosts permissions for this partition */
    smem_ac_hosts_perm(toc_entry, hosts_perm);

    /* Set permissions */
    smem_ac_perms_set(smem_phys_base, toc_entry->offset, toc_entry->size, hosts_perm);
  }
  
  smem_init_partitions_completed = TRUE;
}
