/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_PR_DEBUG_H
#define __QDF_PR_DEBUG_H

#include "../Debug.h"

#define pr_debug(fmt, ...) do {                   \
        DbgInfo(fmt, ##__VA_ARGS__);              \
    } while (0)

#define pr_err(fmt, ...) do {                      \
        DbgError(fmt, ##__VA_ARGS__);              \
    } while (0)

#define pr_warn(fmt, ...) do {                     \
        DbgWarn(fmt, ##__VA_ARGS__);               \
    } while (0)

#define pr_info(fmt, ...) do {                     \
        DbgInfo(fmt, ##__VA_ARGS__);               \
    } while (0)

#define pr_verb(fmt, ...) do {                     \
        DbgVerbose(fmt, ##__VA_ARGS__);            \
    } while (0)

#define pr_raw_err(fmt, ...) do {                            \
        DbgRaw(WLAN_LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__);    \
    } while (0)

#define pr_raw_dbg(fmt, ...) do {                             \
        DbgRaw(WLAN_LOG_LEVEL_INFO, fmt, ##__VA_ARGS__);      \
    } while (0)

#define pr_array(_msg, _buf, _len, _max_len)       \
    DbgDump(_msg, _buf, _len, _max_len)

#endif // !__QDF_PR_DEBUG_H

