/**
 *   @file OEMInfoImage.c
 *
 *   Abstraction layer for image-specific dependencies.
 **/

/*
 *====================================================================
 *
 *     Copyright (c) 2023, 2024 Qualcomm Technologies, Inc. All rights reserved.
 *     Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 *====================================================================
 *
 *
 *====================================================================
 */

#include <stdint.h>
#include <stdlib.h>
#include "OEMInfoInternal.h"
#include "DALSysTypes.h"
#include "DALSys.h"

void *OEMInfo_malloc(size_t size)
{
    void *buf = NULL;
    DALResult eResult = DALSYS_Malloc(size, &buf);
    if (eResult != DAL_SUCCESS)
    {
        buf = NULL;
    }
    return buf;
}


void OEMInfo_free(void *pMem)
{
    // While DALSYS_Free can fail if pMem doesn't point to a region
    // owned by DALSYS, there's nothing we can do if it fails.
    // Ignore the return value.
    DALSYS_Free(pMem);
}

void *OEMInfo_memset(void *str, int c, size_t n)
{
    return DALSYS_memset(str, c, n);
}
