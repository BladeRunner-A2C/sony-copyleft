#ifndef BOOT_CACHE_IF_H
#define BOOT_CACHE_IF_H
/*===========================================================================

                    BOOT CACHE IF DEFINITIONS

DESCRIPTION
  Contains definition for cache if 

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020, 2023 by QUALCOMM Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/15/23   ck      Renamed to boot_cache_if
05/21/20   rama    Initial revision
===========================================================================*/


typedef struct boot_cache_if_type
{
  void (*InvalidateInstructionCache)(void);
  void* (*InvalidateInstructionCacheRange)(void* Address, UINTN Length);
  void (*WriteBackInvalidateDataCache)(void);
  void* (*WriteBackInvalidateDataCacheRange)(void* Address, UINTN Length);
  void (*WriteBackDataCache)(void);
  void* (*WriteBackDataCacheRange)(void* Address, UINTN Length);
  void (*InvalidateDataCache)(void);
  void* (*InvalidateDataCacheRange)(void* Address, UINTN Length);
} boot_cache_if_type;

extern boot_cache_if_type cache_if;


#endif /* BOOT_CACHE_IF_H */
