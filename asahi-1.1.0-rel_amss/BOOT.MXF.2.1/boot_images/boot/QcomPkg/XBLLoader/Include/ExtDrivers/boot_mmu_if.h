#ifndef BOOT_MMU_IF_H
#define BOOT_MMU_IF_H
/*===========================================================================

                    BOOT MMU IF DEFINITIONS

DESCRIPTION
  Contains definition for mmu if 

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
02/15/23   ck      Renamed to boot_mmu_if
05/21/20   rama    Initial Revision
===========================================================================*/

#include <Library/ArmMmuLib.h>
#include <ArmMmuLibEfiAttributesMap.h>


typedef struct boot_mmu_if_type
{
  EFI_STATUS (*ArmConfigureMmu)(ARM_MEMORY_REGION_DESCRIPTOR * MemoryTable,
                                void ** TranslationTableBase OPTIONAL,
                                UINTN * TranslationTableSize);

  EFI_STATUS (*ArmSetMemoryAttributes)(EFI_PHYSICAL_ADDRESS Address,
                                       UINT64 Length,
                                       UINT64 Attributes);
} boot_mmu_if_type;

extern boot_mmu_if_type mmu_if;


#endif /* BOOT_MMU_IF_H */
