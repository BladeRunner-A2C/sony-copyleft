/*=============================================================================

                       MAILBOX OS UEFI


 Copyright (c) 2022-2023 QUALCOMM Technologies, Incorporated.
 All rights reserved.
 Qualcomm Confidential and Proprietary

=============================================================================*/

/*=============================================================================
                         EDIT HISTORY FOR FILE

$Header:  $
=============================================================================*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include "mbox_os_utils.h"
#include "DALSys.h"
#include <Library/BaseLib.h>
#include <Protocol/EFIScm.h>
#include <scm_sip_interface.h>
#include <PiDxe.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DxeServicesTableLib.h>

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/

/*=============================================================================
                       LOCAL DATA DEFINATION
=============================================================================*/
static QCOM_SCM_PROTOCOL *mbox_os_scm_prot = NULL;

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/
extern EFI_GUID gQcomScmProtocolGuid;

/*=============================================================================

                     LOCAL FUNCTION DEFINATION
                     
=============================================================================*/

/*=============================================================================
FUNCTION  
=============================================================================*/


/*=============================================================================

                     GLOBAL FUNCTION DEFINATION
                     
=============================================================================*/

/*=============================================================================
  FUNCTION  mbox_os_init
=============================================================================*/
boolean mbox_os_init(void)
{
  EFI_STATUS status = EFI_DEVICE_ERROR;

  /*Locate QCOM_SCM_PROTOCOL.*/
  status = gBS->LocateProtocol(&gQcomScmProtocolGuid, NULL,
                               (VOID **)&mbox_os_scm_prot);
  if (EFI_SUCCESS != status)
  {
    MBOX_OS_LOG_ERR("mbox_os_init: Failed to locate SCM protocol for Mailbox %d\n", status);
    return FALSE;
  }

  if (NULL == mbox_os_scm_prot)
  {
    MBOX_OS_LOG_ERR("mbox_os_init: ScmProtocol NULL, status:%d\n", status);
    return FALSE;
  }

  return TRUE;
}

/*=============================================================================
  FUNCTION  mbox_os_calloc
=============================================================================*/
/**
  Dynamically allocate a region of memory from the heap and initialize with
  the zeroes.  The region should be freed using \c mbox_os_free
  when no longer used.

  @param[in]  size   The number of bytes to be allocated.

  @return    The pointer to the region of memory that was allocated.
             NULL if the allocation failed.
*/
/*=========================================================================*/
void *mbox_os_calloc(size_t size)
{
  void *pMem;

  EFI_STATUS efiStatus;
  efiStatus = gBS->AllocatePool( EfiBootServicesData, size, &pMem );
  if (EFI_SUCCESS != efiStatus)
  {
    return NULL;
  }
  else
  {
    memset( pMem, 0, size );
    return pMem;
  }
}

/*=============================================================================
  FUNCTION  mbox_os_free
=============================================================================*/
void mbox_os_free(void *mem)
{
  gBS->FreePool(mem);
}

/*=============================================================================
  FUNCTION  mbox_os_string_compare
=============================================================================*/
/**
  Compares two strings.

  @param[in] s1     String 1
  @param[in] s2     String 2

  @return
  0 if strings are identical, non-zero otherwise
*/
/*==========================================================================*/
INT32 mbox_os_string_compare( const char *s1, const char *s2 )
{
  return AsciiStrCmp( s1, s2);
}

/*=============================================================================
  FUNCTION  mbox_os_string_copy
=============================================================================*/
/**
  Copies the source string into the destination buffer until
  size is reached, or until a '\0' is encountered.  If valid,
  the destination string will always be NULL deliminated.

  @param[in] dst    The destination string, contents will be updated.
  @param[in] src    The source string
  @param[in] size   The maximum copy size (size of dst)

  @return
  The destination string pointer, dst.
*/
/*==========================================================================*/
char *mbox_os_string_copy( char *dst, const char *src, uint32 size )
{
  unsigned int sz;

  if( size && dst && src )
  {

      sz = strlen(src) + 1;

      if(sz > size)
      {
        DALSYS_memcpy(dst, src, size-1);
        dst[size-1] = '\0';
      }
      else
      {
        DALSYS_memcpy(dst, src, sz);
      }
  }
  else
  {
      dst = NULL;
  }

  return dst;
}

/*=============================================================================
  FUNCTION  mbox_os_reg_read
=============================================================================*/
boolean mbox_os_reg_read(void *reg_addr, uint32 *pval)
{
  *pval = in_dword(reg_addr);
  return TRUE;
}

/*=============================================================================
  FUNCTION  mbox_os_reg_write
=============================================================================*/
boolean mbox_os_reg_write(void *reg_addr, uint32 val)
{
  out_dword(reg_addr, val);
  
  return TRUE;
}

/*=============================================================================
  FUNCTION  mbox_os_scm_read
=============================================================================*/
boolean mbox_os_scm_read(uint64 pa, uint32 *pval)
{
  EFI_STATUS status = EFI_DEVICE_ERROR;
  uint64 Params[SCM_MAX_NUM_PARAMETERS] = {0};
  uint64 Results[SCM_MAX_NUM_RESULTS] = {0};

  if (NULL == mbox_os_scm_prot || !pa || !pval)
  {
    return FALSE;
  }

  Params[0] = pa;

  //Make ScmSipSysCall
  status = mbox_os_scm_prot->ScmSipSysCall(mbox_os_scm_prot,
                     TZ_IO_ACCESS_READ_ID,
                     TZ_IO_ACCESS_READ_ID_PARAM_ID,
                     Params,
                     Results);

  if (status != EFI_SUCCESS )
  {
    MBOX_OS_LOG_ERR("mbox_os_scm_read: ScmSipSysCall failed for TZ_IO_ACCESS_READ_ID, status = (0x%x)\r\n", status);
    return FALSE;
  }
  
  *pval = (uint32)Results[1];
  return TRUE;
}

/*=============================================================================
  FUNCTION  mbox_os_scm_write
=============================================================================*/
boolean mbox_os_scm_write(uint64 pa, uint32 val)
{
  EFI_STATUS status = EFI_DEVICE_ERROR;
  uint64 Params[SCM_MAX_NUM_PARAMETERS] = {0};
  uint64 Results[SCM_MAX_NUM_RESULTS] = {0};

  if (NULL == mbox_os_scm_prot || !pa || !val)
  {
    return FALSE;
  }

  Params[0] = pa;
  Params[1] = val;

  //Make ScmSipSysCall
  status = mbox_os_scm_prot->ScmSipSysCall(mbox_os_scm_prot,
                     TZ_IO_ACCESS_WRITE_ID,
                     TZ_IO_ACCESS_WRITE_ID_PARAM_ID,
                     Params,
                     Results);

  if (status != EFI_SUCCESS )
  {
    MBOX_OS_LOG_ERR("mbox_os_scm_write: ScmSipSysCall failed for TZ_IO_ACCESS_WRITE_ID, status = (0x%x)\r\n", status);
    return FALSE;
  }
  return TRUE;
}

/*=============================================================================
  FUNCTION  mbox_os_mutex_init
=============================================================================*/
void mbox_os_mutex_init(mbox_os_mutex_type *cs)
{
  InitRecursiveLock("mbox", (LockHandle**)cs);
}

/*=============================================================================
  FUNCTION  mbox_os_mutex_deinit
=============================================================================*/
void mbox_os_mutex_deinit(mbox_os_mutex_type *cs)
{
  DestroyLock(*cs);
}

/*=============================================================================
  FUNCTION  mbox_os_mutex_acquire
=============================================================================*/
void mbox_os_mutex_acquire(mbox_os_mutex_type *cs)
{
  AcquireLock(*cs);
}

/*=============================================================================
  FUNCTION  mbox_os_mutex_release
=============================================================================*/
void mbox_os_mutex_release(mbox_os_mutex_type *cs)
{
  ReleaseLock(*cs);
}

/*=============================================================================
  FUNCTION  mbox_os_intr_reg
=============================================================================*/
boolean mbox_os_intr_reg
(
  mbox_os_intr_type   *intr, 
  mbox_os_isr_cb_type isr,
  void                *priv
)
{
  if (intr == NULL)
  {
    return FALSE;
  }
  
  if (RegisterThrCtxtIntrHandler(intr->intr_num, (ThrCtxtIntrHandler)isr, priv) == EFI_SUCCESS)
  {
    ConfigureInterrupt(intr->intr_num, intr->intr_cfg, priv);
    UnmaskInterrupt(intr->intr_num);
    return TRUE;
  }
  
  return FALSE;
}

/*=============================================================================
  FUNCTION  mbox_os_intr_done
=============================================================================*/
void mbox_os_intr_done
(
  mbox_os_intr_type *intr
)
{
  UnmaskInterrupt(intr->intr_num);
}

/*=============================================================================
  FUNCTION  mbox_os_io_region_map
=============================================================================*/
void *mbox_os_io_region_map(uint64 pa, uint32 size)
{
  EFI_STATUS status = 0;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR descriptor;
 
  /* Both memprop options can by satisfied by UC MMIO space type */
  status = gDS->GetMemorySpaceDescriptor(pa, &descriptor);
  if (EFI_ERROR(status))
  {
     MBOX_OS_LOG_ERR("mbox_os_io_region_map: Cannot get memory descriptor status:%d", status);
     return NULL;
  }

  if (descriptor.GcdMemoryType != EfiGcdMemoryTypeMemoryMappedIo)
  {
    if (descriptor.GcdMemoryType != EfiGcdMemoryTypeNonExistent)
    {
      status = gDS->RemoveMemorySpace(pa, size);
      MBOX_OS_LOG_DBG("mbox_os_io_region_map: Region is being remapped to correct type pa:0x%lx", pa);
    }

    status = gDS->AddMemorySpace(EfiGcdMemoryTypeMemoryMappedIo,
                                pa, size, EFI_MEMORY_UC);
    if (EFI_ERROR(status))
    {
      MBOX_OS_LOG_ERR("mbox_os_io_region_map: Unable to add memory space: addr=0x%lx, size=0x%lx", pa, size);
      return NULL;
    }

    status = gDS->SetMemorySpaceAttributes(pa, size, EFI_MEMORY_UC);
    if (EFI_ERROR(status))
    {
      MBOX_OS_LOG_ERR("mbox_os_io_region_map: Fail to set memory attibute: addr=0x%lx, size=0x%lx", pa, size);
      return NULL;
    }
  }
  return (void *)(uintptr_t)pa;
}

