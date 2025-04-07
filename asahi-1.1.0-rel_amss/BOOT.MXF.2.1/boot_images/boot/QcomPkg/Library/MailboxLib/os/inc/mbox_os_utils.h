#ifndef MBOX_OS_UTILS_H
#define MBOX_OS_UTILS_H
/*=============================================================================

                       MAILBOX OS


 Copyright (c) 2023 QUALCOMM Technologies, Incorporated.
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
#include <Uefi.h>
#include "stdlib.h"
#include <stdarg.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/KernelLib.h>
#include <Library/QcomLib.h>
#include <string.h>
#include "com_dtypes.h"
#include "DALSys.h"
#include "HALhwio.h"

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/
#ifdef FEATURE_MBOX_DBG
#define MBOX_OS_LOG_DBG(fmt, ...)    DEBUG((EFI_D_ERROR, fmt " ****\n", __VA_ARGS__))
#else
#define MBOX_OS_LOG_DBG(fmt, ...) \
  do \
  { \
  } while(0)
#endif

#define MBOX_OS_LOG_INFO(fmt, ...)   DEBUG((EFI_D_INFO, fmt " ****\n", __VA_ARGS__))
#define MBOX_OS_LOG_ERR(fmt, ...)    DEBUG((EFI_D_ERROR,fmt " ****\n", __VA_ARGS__))
#define MBOX_OS_LOG_FATAL(fmt, ...)  DEBUG((EFI_D_ERROR, fmt " ****\n", __VA_ARGS__))

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/
typedef void* mbox_os_mutex_type; 

typedef struct
{
  uint32          intr_num;
  enum IntrConfig intr_cfg;
} mbox_os_intr_type;
typedef void (*mbox_os_isr_cb_type)(void *priv);

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/

/*=============================================================================

                     PUBLIC FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
  FUNCTION  mbox_os_init
=============================================================================*/
boolean mbox_os_init(void);

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
void *mbox_os_calloc(size_t size);

/*=============================================================================
  FUNCTION  mbox_os_free
=============================================================================*/
void mbox_os_free(void *mem);

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
int mbox_os_string_compare(const char *s1, const char *s2);

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
char *mbox_os_string_copy(char *dst, const char *src, uint32 size);

/*=============================================================================
  FUNCTION  mbox_os_reg_read
=============================================================================*/
boolean mbox_os_reg_read(void *reg_addr, uint32 *pval);

/*=============================================================================
  FUNCTION  mbox_os_reg_write
=============================================================================*/
boolean mbox_os_reg_write(void *reg_addr, uint32 val);

/*=============================================================================
  FUNCTION  mbox_os_scm_read
=============================================================================*/
boolean mbox_os_scm_read(UINT64 pa, uint32 *pval);

/*=============================================================================
  FUNCTION  mbox_os_scm_write
=============================================================================*/
boolean mbox_os_scm_write(UINT64 pa, uint32 val);

/*=============================================================================
  FUNCTION  mbox_os_mutex_init
=============================================================================*/
void mbox_os_mutex_init(mbox_os_mutex_type *cs);

/*=============================================================================
  FUNCTION  mbox_os_mutex_deinit
=============================================================================*/
void mbox_os_mutex_deinit(mbox_os_mutex_type *cs);

/*=============================================================================
  FUNCTION  mbox_os_mutex_acquire
=============================================================================*/
void mbox_os_mutex_acquire(mbox_os_mutex_type *cs);

/*=============================================================================
  FUNCTION  mbox_os_mutex_release
=============================================================================*/
void mbox_os_mutex_release(mbox_os_mutex_type *cs);

/*=============================================================================
  FUNCTION  mbox_os_intr_reg
=============================================================================*/
boolean mbox_os_intr_reg
(
  mbox_os_intr_type   *intr, 
  mbox_os_isr_cb_type isr,
  void                *priv
);

/*=============================================================================
  FUNCTION  mbox_os_intr_done
=============================================================================*/
void mbox_os_intr_done
(
  mbox_os_intr_type   *intr
);

/*=============================================================================
  FUNCTION  mbox_os_io_region_map
=============================================================================*/
void *mbox_os_io_region_map(uint64 pa, uint32 size);

#endif /* MBOX_OS_UTILS_H */
