/********************************************************************
 * Copyright (c) 2019, 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *********************************************************************/

#ifndef __MEM_MANAGER_H__
#define __MEM_MANAGER_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "object.h"

typedef struct
{
   void*     addr;
   size_t    len;
   uint32_t  perm;                                // IMemRegion permissions
} MemObjInfo;

enum MemManagerErrorCodes
{
   MM_OK = 0,
   MM_ERROR,
   MM_ERROR_LOCKED,                              // Memory object in use
   MM_ERROR_NAMO,                                // Not a memory object
   MM_ERROR_EXISTS,                              // Memory exists & doesnt match
};


/**
 * @note Called as part of the SMCInvoke initialization.
 * The MemManager is added as object 0 in the ObjectTable.
 */
int32_t MemManager_ctor( Object *obj );


/**
 * This attempts to release all resources, if any memory region is retained
 * (except the initial reference obtained during the add function) the
 * operation will fail.
 *
 * @note All possible regions are released and the MemManager is removed from
 * the ObjectTable.
 *
 * @return
 *   MM_REGION_LOCKED
 *      if any of the assigned memory regions are "busy",
 *      not destructive if this is the case.
 */
int32_t MemManager_dtor( void );


/**
 * Assigns a memory region to the memory manager and returns a shared memory
 * object corresponding to this region
 *
 * It's assumed that the region is owned by the HLOS VM and has rw permissions
 *
 * pa must be 4K aligned, and szie must be 4K multiples
 *
 */
int32_t MemManager_add( void *addr, size_t size, uint32_t perm, Object *memObj );


/**
 * Maps and locks a memory object, i.e. guarantees that the principal information
 * does not change during the lifespan of the map object.
 */
int32_t MemManager_mapObject( Object memObj, Object *mapObj );


/**
 * Returns the current information for the specified obj,
 * works on both memory objects and map objects.
 */
int32_t MemManager_getInfo( Object obj, MemObjInfo *info );


#endif // __MEM_MANAGER_H__
