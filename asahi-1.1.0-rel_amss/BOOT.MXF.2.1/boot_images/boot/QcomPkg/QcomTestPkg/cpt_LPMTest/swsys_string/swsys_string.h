/*
===========================================================================
*/
/**
  @file swsys_string.h

*/
/*
  ====================================================================

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  06/14/17   jh      Initial revision.

  ====================================================================
*/

#ifndef SWSYS_STRING_H
#define SWSYS_STRING_H

#define BITOP(a,b,op) \
 ((a)[(size_t)(b)/(8*sizeof *(a))] op (size_t)1<<((size_t)(b)%(8*sizeof *(a))))

// changes the string to lowercase in-place
void swsys_string_tolower_inplace(char* str);

// changes the string to lowercase in-place
void swsys_string_toupper_inplace(char* str);

// these strict parsers will return true if parsing was successful, and out
// will point to the parsed value. Strings should only contain the value.
// If any illegal characters are found, then the parsing will fail.
bool swsys_strtoi32_strict(char* str, int32_t* out, int32_t base);
bool swsys_strtoi64_strict(char* str, int64_t* out, int32_t base);
bool swsys_strtou32_strict(char* str, uint32_t* out, int32_t base);
bool swsys_strtou64_strict(char* str, uint64_t* out, int32_t base);
bool swsys_strtof_strict(char* str, float* out);
bool swsys_strtod_strict(char* str, double* out);

// strings can be 'true', 't' or '1' for true, 'false', 'f', or '0' for false.
// strings are parsed in case-insensitive way, so 'TruE' will be true.
bool swsys_strtob_strict(char* str, bool* out);

// case-insensitive strcmp
int32_t swsys_strcicmp(const char* str1, const char* str2);

// to_replace must have the same size as replace_with
bool swsys_str_replace_first(
    char* str,
    const char* to_replace,
    const char* replace_with);
bool swsys_str_replace_all(
    char* str,
    const char* to_replace,
    const char* replace_with);

size_t swsys_strspn(const char* s, const char* c);
char* swsys_strtok(char*restrict s, const char*restrict sep);

#endif // SWSYS_STRING_H
