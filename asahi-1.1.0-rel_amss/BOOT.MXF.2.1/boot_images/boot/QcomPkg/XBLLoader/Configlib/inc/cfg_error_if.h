#ifndef CFG_ERROR_IF_H
#define CFG_ERROR_IF_H

/*===========================================================================

                 Configlib Error Handler Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for the Configlib
  error handler interface.
    
Copyright 2023 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/07/23   yps     Initial revision.

============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/


/*---------------------------------------------------------------------------
 ERRORS FROM Config LIB
 ---------------------------------------------------------------------------*/
typedef enum
{
  CFG_ERR_NONE,
  CFG_ERR_NULL_PTR_PASSED                     = 0x0001,
  CFG_ERR_MISALIGNMENT                        = 0x0002,
  CFG_ERR_BUFFER_SIZE_TOO_SMALL               = 0x0003,
  CFG_ERR_SUBSYS_BOOT_FAIL                    = 0x0004,
  CFG_ERR_MEMORY_ALLOC_FAIL,
  CFG_ERR_MEMORY_FREE_FAIL,
  CFG_ERR_MAX                                 = 0x7FFF
}cfg_error_type;

#endif
