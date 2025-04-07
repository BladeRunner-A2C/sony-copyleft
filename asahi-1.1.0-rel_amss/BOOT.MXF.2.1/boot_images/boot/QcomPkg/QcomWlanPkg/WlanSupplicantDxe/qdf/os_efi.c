/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/RngLib.h>
#include <Protocol/Rng.h>

#include "utils/includes.h"
#include "utils/common.h"

void *os_malloc(size_t size)
{
	return AllocateZeroPool(size);
}

void os_free(void *ptr)
{
    if (ptr == NULL)
        return;

	FreePool(ptr);
}

void *os_realloc(void *ptr, size_t size)
{
    return ReallocatePool(size, size, ptr);
}

int os_get_time(struct os_time *t)
{
    t->sec = 0;
    t->usec = 0;
    return 0;
}

char *os_readfile(const char *name, size_t *len)
{
    return NULL;
}


int os_mktime(int year, int month, int day, int hour, int min, int sec,
        os_time_t *t)
{
	// not supported yet
	*t = 0;
	return 0;
}

int os_get_reltime(struct os_reltime *t)
{
	// not supported yet.
	os_memset(t, 0, sizeof(*t));
	return -1;
}

int os_get_random(unsigned char *buf, size_t len)
{
	static EFI_RNG_PROTOCOL *Rng = NULL;
	EFI_STATUS Status;
    BOOLEAN IsRandom;
    UINT64 TempRand[2];

    do {
	    if (!Rng) {
		    Status = gBS->LocateProtocol(&gEfiRngProtocolGuid, NULL, (VOID **)&Rng);
		    if (EFI_ERROR(Status)) {
                break;
		    }
	    }

	    Status = Rng->GetRNG(Rng, NULL, (UINTN)len, (UINT8 *)buf);
	    if (EFI_ERROR (Status)) {
            break;
	    }

        return 0;
    } while (0);

    while (len > 0) {
        IsRandom = GetRandomNumber128(TempRand);
        if (!IsRandom) {
            return -1;
        }
        if (len >= sizeof(TempRand)) {
            WriteUnaligned64((UINT64 *)buf, TempRand[0]);
            buf += sizeof(UINT64);
            WriteUnaligned64((UINT64 *)buf, TempRand[1]);
            buf += sizeof(UINT64);
            len -= sizeof(TempRand);
        }
        else {
            CopyMem(buf, TempRand, len);
            len = 0;
        }
    }

	return 0;
}

void *os_memdup(const void *src, size_t len)
{
    void *data = os_malloc(len);

	if (data && src)
		os_memcpy(data, src, len);
	return data;
}

const char *os_compatible_format(const char *fmt, char *newfmt, int newlen)
{
    const char *in = fmt;
    char *out = newfmt, *oend = newfmt + newlen;
    int modified = 0;
    int in_modifier = 0;
    char c;

    do {
        c = *in++;

        if (c == '%') {
            in_modifier = 1;
        }
        else if (in_modifier) {
            in_modifier = 0; 

            /* convert "%s" -> "%a" */
            if (c == 's') {
                *out++ = 'a';
                modified = 1;
                continue;
            }
            /* continue normally */
        }

        *out++ = c;
    } while (c && out < oend);

    return (modified && (out < oend)) ? newfmt : fmt;
}

int os_snprintf(char *str, size_t size, const char *fmt, ...)
{
    char newfmt[384];
    va_list marker;
    u64 length;

    /* Convert the message to an ASCII String */
    va_start(marker, fmt);
    length = AsciiVSPrint(str, size, 
        os_compatible_format(fmt, newfmt, sizeof(newfmt)), marker);
    va_end(marker);

    return (int)length;
}