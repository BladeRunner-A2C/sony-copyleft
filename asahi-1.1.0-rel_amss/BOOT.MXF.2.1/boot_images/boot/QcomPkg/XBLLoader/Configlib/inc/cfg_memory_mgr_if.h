#ifndef CFG_MEMORY_MGR_IF_H
#define CFG_MEMORY_MGR_IF_H
/*===========================================================================

                    BOOT MEMORY MGR IF DEFINITIONS

DESCRIPTION
  Contains definition for memory manager 

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2011-2012, 2014, 2017, 2018, 2021 Qualcomm Technologies, Inc.
All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/08/21   tmt     Port to QDSP -> ConfigLib
08/02/19   ep      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "cfg_error_if.h"
#include "cfg_comdef.h"


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

typedef struct cfg_memory_mgr_if_type
{
    cfg_error_type (*malloc)(uint32 dwSize, void **ppMem);
    cfg_error_type (*memalign)(uint32 dwSize, uint32 alignment, void **ppMem);
    cfg_error_type (*free)(void *pmem);
} cfg_memory_mgr_if_type;

extern cfg_memory_mgr_if_type cfg_mem_if;

#endif /* BOOT_MEMORY_MGR_IF_H */
