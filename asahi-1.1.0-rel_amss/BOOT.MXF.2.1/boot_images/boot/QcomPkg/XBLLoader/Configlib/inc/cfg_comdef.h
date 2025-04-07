#ifndef CFG_COMDEF_H
#define CFG_COMDEF_H

/*===========================================================================

                 Boot Common Definition Header File

GENERAL DESCRIPTION
  This header file contains common declarations and definitions used
  throughout the boot software.
   
Copyright 2023 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/07/23   yps     Initial revision.

===========================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#include <stdint.h>

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/

/* boot_boolean data type used for boolean variables shared with pbl*/

typedef  unsigned int       boot_boolean;     /* uint32 Boolean value type. */


#define SECTION(__name) __attribute__((section(__name)))

#if (!defined uint8) && (!defined _UINT8_DEFINED)
typedef  unsigned char uint8;
#endif

#if (!defined uint16) && (!defined _UINT16_DEFINED) 
typedef  unsigned short uint16;
#endif

#if (!defined uint32) && (!defined _UINT32_DEFINED)
typedef  unsigned int uint32;
#endif

#if (!defined uint64) && (!defined _UINT64_DEFINED)
typedef  unsigned long long  uint64;
#endif

#ifndef _UINTNT_DEFINED
typedef  unsigned long uintnt;
#endif

#if (!defined boolean) && (!defined _BOOLEAN_DEFINED)
typedef  unsigned char      boolean; 
#endif

#ifndef TRUE 
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif

#ifndef NULL 
#define NULL ((void *) 0)
#endif

#endif /* CFG_COMDEF_H */
