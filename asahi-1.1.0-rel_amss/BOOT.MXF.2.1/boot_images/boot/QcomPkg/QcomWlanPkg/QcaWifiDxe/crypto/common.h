/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/*
 * wpa_supplicant/hostapd / common helper functions, etc.
 * Copyright (c) 2002-2007, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef COMMON_H
#define COMMON_H

#include <qdf/base_type.h>


 /* Macros for handling unaligned memory accesses */

static inline u16 WPA_GET_BE16(const u8 *a)
{
    return (a[0] << 8) | a[1];
}

static inline void WPA_PUT_BE16(u8 *a, u16 val)
{
    a[0] = (u8)(val >> 8);
    a[1] = (u8)(val & 0xff);
}

static inline u16 WPA_GET_LE16(const u8 *a)
{
    return (a[1] << 8) | a[0];
}

static inline void WPA_PUT_LE16(u8 *a, u16 val)
{
    a[1] = (u8)(val >> 8);
    a[0] = (u8)(val & 0xff);
}

static inline u32 WPA_GET_BE32(const u8 *a)
{
    return ((u32)a[0] << 24) | (a[1] << 16) | (a[2] << 8) | a[3];
}

static inline void WPA_PUT_BE32(u8 *a, u32 val)
{
    a[0] = (val >> 24) & 0xff;
    a[1] = (val >> 16) & 0xff;
    a[2] = (val >> 8) & 0xff;
    a[3] = val & 0xff;
}

static inline u32 WPA_GET_LE32(const u8 *a)
{
    return ((u32)a[3] << 24) | (a[2] << 16) | (a[1] << 8) | a[0];
}

static inline void WPA_PUT_LE32(u8 *a, u32 val)
{
    a[3] = (val >> 24) & 0xff;
    a[2] = (val >> 16) & 0xff;
    a[1] = (val >> 8) & 0xff;
    a[0] = val & 0xff;
}

static inline u64 WPA_GET_BE64(const u8 *a)
{
    return (((u64)a[0]) << 56) | (((u64)a[1]) << 48) |
        (((u64)a[2]) << 40) | (((u64)a[3]) << 32) |
        (((u64)a[4]) << 24) | (((u64)a[5]) << 16) |
        (((u64)a[6]) << 8) | ((u64)a[7]);
}

static inline void WPA_PUT_BE64(u8 *a, u64 val)
{
    a[0] = (u8)(val >> 56);
    a[1] = (u8)(val >> 48);
    a[2] = (u8)(val >> 40);
    a[3] = (u8)(val >> 32);
    a[4] = (u8)(val >> 24);
    a[5] = (u8)(val >> 16);
    a[6] = (u8)(val >> 8);
    a[7] = (u8)(val & 0xff);
}

static inline u64 WPA_GET_LE64(const u8 *a)
{
    return (((u64)a[7]) << 56) | (((u64)a[6]) << 48) |
        (((u64)a[5]) << 40) | (((u64)a[4]) << 32) |
        (((u64)a[3]) << 24) | (((u64)a[2]) << 16) |
        (((u64)a[1]) << 8) | ((u64)a[0]);
}

static inline void WPA_PUT_LE64(u8 *a, u64 val)
{
    a[7] = (u8)(val >> 56);
    a[6] = (u8)(val >> 48);
    a[5] = (u8)(val >> 40);
    a[4] = (u8)(val >> 32);
    a[3] = (u8)(val >> 24);
    a[2] = (u8)(val >> 16);
    a[1] = (u8)(val >> 8);
    a[0] = (u8)(val & 0xff);
}

#endif