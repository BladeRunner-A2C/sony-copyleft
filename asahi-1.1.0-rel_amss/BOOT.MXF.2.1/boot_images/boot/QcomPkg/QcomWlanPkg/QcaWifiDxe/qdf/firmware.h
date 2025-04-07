/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 6/9/21    zxue     fix parasoft issue
 26/8/21   zxue     support HSP2.1
 30/7/21   zxue     support fw boot recovery
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_FIRMWARE_H
#define __QDF_FIRMWARE_H

#include <qdf/qbase.h>

#pragma pack(1)

struct sha256_hash_info {
    u16 method;
    u8 values[32];
};

#pragma pack()

struct firmware {
    u32 size;
    void *data;
};

struct firmware_metadata {
    const struct sha256_hash_info *hash_info;
    const u8 *description;
    u16 description_len;

    const u8 *begin;
    const u8 *end;
};

typedef int (*validate_firmware_metata_routine)(const u8 *name, struct firmware_metadata *metadata, void *ctx);

int request_firmware_fancily(struct firmware *fw, const u16 *name, 
    validate_firmware_metata_routine validate_metadata, void *validate_ctx);

static inline int request_firmware(struct firmware *fw, const u16 *name) 
{
    return request_firmware_fancily(fw, name, NULL, NULL);
}

void release_firmware(struct firmware *fw);

void flush_firmware_cache(void);
void free_firmware_cache(void);

#endif /* __QDF_FIRMWARE_H */