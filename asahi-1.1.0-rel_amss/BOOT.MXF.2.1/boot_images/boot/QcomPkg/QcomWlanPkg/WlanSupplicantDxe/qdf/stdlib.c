/*
 * Copyright (c) 2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <qdf/pr_debug.h>
#include "stdinc.h"

#ifndef memcpy
void *memcpy(void *d, const void *s, size_t n)
{
    return CopyMem(d, s, (UINTN)n);
}
#endif

#ifndef memset
void *memset(void *s, int ch, size_t n)
{
    return SetMem(s, n, (UINT8)ch);
}
#endif

int __isspace(int c)
{
    return c == ' ' || (unsigned)c - '\t' < 5;
}

int __atoi(const char *str)
{
    int ret;
    bool negative = false;

    while (__isspace((const unsigned char)*str))
        ++str;

    if (*str == '+') {
        negative = false;
        ++str;
    }
    else if (*str == '-') {
        negative = true;
        ++str;
    }
	
    ret = (int)AsciiStrDecimalToUintn(str);
    if (negative) {
        ret = -ret;
    }

    return ret;
}

int __sscanf(const char *str, const char *format, ...)
{
    int *num;
    va_list ap;
    int cp_len;
    char copy[10] = { 0 };

    if (AsciiStrLen(format) != 3 || format[0] != '%' || format[2] != 'd') {
        return -1;
    }

    va_start(ap, format);
    num = va_arg(ap, int *);
    va_end(ap);

    cp_len = format[1] - '0';
    CopyMem(copy, str, cp_len);
    copy[cp_len] = '\0';

    *num = __atoi(copy);
    return 1;
}