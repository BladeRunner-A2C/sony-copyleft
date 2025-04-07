/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <qdf/qbase.h>
#include "cfg.h"

#define CFG_KEY_MAX_LEN   256
#define CFG_VALUE_MAX_LEN 256

static const u8 *lskip(const u8 *pos, const u8 *end)
{
    while (pos < end) {
        if (!isspace(*pos))
            break;
        pos++;
    }
    return pos;
}

static void copy_string(const u8 *start, const u8 *end, u8 *value, u16 *value_len)
{
    if (end && ((end - start) < *value_len)) {
        /* right strip */
        do {
            if (!isspace(*(end - 1)))
                break;
            end--;
        } while (end > start);
        memcpy(value, start, (end - start));
        value[end - start] = '\0';
        *value_len = (u16)(end - start);
    }
    else {
        value[0] = '\0';
        *value_len = 0;
    }
}

static const u8 *cfg_skip_comments(const u8 *pos, const u8 *end)
{
    const u8 *comment_start = NULL;

    pos = lskip(pos, end);

    while (pos < end) {
        if (*pos == '#') {
            comment_start = pos;
            pos++;
            continue;
        }
        
        if (*pos == '\n') {
            pos++;
            pos = lskip(pos, end);
            comment_start = NULL;
            continue;
        }

        if (!comment_start)
            break;
        pos++;
    }

    return pos;
}

static const u8 *cfg_find_key(const u8 *pos, const u8 *end, u8 *key, u16 *key_len)
{
    const u8 *key_start = lskip(pos, end);
    const u8 *key_end = key_start;

    while (pos < end) {
        if (*pos == '=') {
            key_end = pos;
            pos++;
            break;
        }
        else if (*pos == '\n') {
            pos++;
            break;
        }
        pos++;
    }

    copy_string(key_start, key_end, key, key_len);

    return pos;
}

static const u8 *cfg_find_value(const u8 *pos, const u8 *end, u8 *value, u16 *value_len)
{
    const u8 *value_start = lskip(pos, end);
    const u8 *value_end = end;
    
    pos = value_start;

    while (pos < end) {
        if (*pos == '\n') {
            value_end = pos;
            pos++;
            break;
        }
        pos++;
    }

    copy_string(value_start, value_end, value, value_len);

    return pos;
}

int cfg_parse(const u8 *data, u32 len, cfg_handler handler, void *ctx)
{
    const u8 *pos = data, *end = data + len;
    u8 key[CFG_KEY_MAX_LEN];
    u8 value[CFG_VALUE_MAX_LEN];
    u16 key_len;
    u16 value_len;

    while (pos < end)
    {
        /* skip comments */
        pos = cfg_skip_comments(pos, end);
        if (pos >= end)
            break;

        /* key */
        key_len = (u16)ARRAY_LENGTH(key);
        pos = cfg_find_key(pos, end, key, &key_len);
        if (!key_len)
            continue;

        /* value */
        value_len = (u16)ARRAY_LENGTH(value);
        pos = cfg_find_value(pos, end, value, &value_len);

        handler(ctx, key, value);
    }

    return 0;
}

static const u8 *expression_find_key(const u8 *pos, const u8 *end, u8 *key, u16 *key_len)
{
    const u8 *key_start = lskip(pos, end);
    const u8 *key_end = key_start;

    while (pos < end) {
        if (*pos == '=') {
            key_end = pos;
            pos++;
            break;
        }
        else if (*pos == '\n') {
            pos++;
            break;
        }
        pos++;
    }

    copy_string(key_start, key_end, key, key_len);

    return pos;
}

static const u8 *expression_find_value(const u8 *pos, const u8 *end, u8 *value, u16 *value_len)
{
    const u8 *value_start = lskip(pos, end);
    const u8 *value_end = end;

    pos = value_start;

    while (pos < end) {
        if ((*pos == ',') ||
            (*pos == '\n')) {
            value_end = pos;
            pos++;
            break;
        }
        pos++;
    }

    copy_string(value_start, value_end, value, value_len);

    return pos;
}

int expression_iterator_next(struct expression_iterator *it)
{
    const u8 *pos = it->expression_next, *end = it->expression_end;

    if (!pos)
        return -EINVAL;

    while (pos < end) {
        /* skip spaces */
        pos = lskip(pos, end);

        /* key */
        it->key_len = (u16)ARRAY_LENGTH(it->key);
        pos = expression_find_key(pos, end, it->key, &it->key_len);
        if (!it->key_len)
            continue;

        /* value */
        it->value_len = (u16)ARRAY_LENGTH(it->value);
        pos = expression_find_value(pos, end, it->value, &it->value_len);

        /* update the position */
        it->expression_next = pos;

        return 0;
    }

    it->expression_next = pos;

    if (it->key_len) {
        memset(it->key, 0, it->key_len);
        it->key_len = 0;
    }

    if (it->value_len) {
        memset(it->value, 0, it->value_len);
        it->value_len = 0;
    }

    return -ENOENT;
}

static const u8 *description_find_expression(const u8 *pos, const u8 *end, struct expression_iterator *it)
{
    const u8 *expression_next, *expression_end;

    while (pos < end) {
        if (!isspace(*pos) && (*pos != '|')) /* skip space and splitter */
            break;
        pos++;
    }
    expression_next = pos;

    while (pos < end) {
        if (*pos == '|')
            break;
        pos++;
    }
    expression_end = pos;
    
    expression_iterator_init(it, expression_next, expression_end);
    return pos;
}

int description_iterator_next(struct description_iterator *it)
{
    const u8 *pos = it->description_next, *end = it->description_end;
    struct expression_iterator *expression_it = &it->expression_it;

    if (!pos)
        return -EINVAL;

    while (pos < end) {
        pos = description_find_expression(pos, end, expression_it);
        if (expression_it->expression_next >= expression_it->expression_end)
            continue;

        it->description_next = pos;
        return 0;
    }

    it->description_next = pos;
    expression_iterator_init(expression_it, NULL, NULL);

    return -ENOENT;
}