/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 17/11/21  zxue     support multiple expressions in a description
 26/8/21   zxue     support HSP2.1
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_CFG_H
#define __QDF_CFG_H

#include <qdf/qbase.h>

/* configuration parser */
typedef void(*cfg_handler)(void *ctx, const u8 *key, const u8 *value);

int cfg_parse(const u8 *data, u32 len, cfg_handler handler, void *ctx);


/* expression iterator to parse the expression like:
 * "bus=pci,qmi-chip-id=1,qmi-board-id=6,vendor=17cb,device=1103,subsystem-vendor=xxxx,subsystem-device=xxxx"
 */
struct expression_iterator {
    const u8 *expression_next;
    const u8 *expression_end;
    u16 key_len;
    u16 value_len;
    u8 key[64];
    u8 value[128];
};

static inline void expression_iterator_init(
    struct expression_iterator *it, 
    const u8 *expression_next, const u8 *expression_end)
{
    it->expression_next = expression_next;
    it->expression_end = expression_end;
    it->key_len = 0;
    it->value_len = 0;

    memset(it->key, 0, sizeof(it->key));
    memset(it->value, 0, sizeof(it->value));
}

int expression_iterator_next(struct expression_iterator *it);

/* description iterator to parse the description like:
 * "<expression>|<expression>"
 */
struct description_iterator {
    const u8 *description_next;
    const u8 *description_end;
    struct expression_iterator expression_it;
};

static inline void description_iterator_init(
    struct description_iterator *it,
    const u8 *description, u16 description_len)
{
    it->description_next = description;
    it->description_end = description + description_len;

    expression_iterator_init(&it->expression_it, NULL, NULL);
}

int description_iterator_next(struct description_iterator *it);
#endif // !__QDF_CFG_H

