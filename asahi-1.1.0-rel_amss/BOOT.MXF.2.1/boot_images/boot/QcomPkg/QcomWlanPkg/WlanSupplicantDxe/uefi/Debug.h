/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __DEBUG_H
#define __DEBUG_H

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/LoadedImage.h>
#include <qdf/file.h>
#include "Utils.h"

#ifndef SUPPORT_DEBUG_PRINT
#define SUPPORT_DEBUG_PRINT 1
#endif

#define ENALBE_LOGFILE_TIMELY_FLUSH  0

// Specifiy the log level
// Set the value to 0 to disable the log
#if SUPPORT_SERIAL_PORT_DEBUG
#define WLAN_LOG_OUPUT_CONSOLE_LEVEL 0
#define WLAN_LOG_OUPUT_FILE_LEVEL    0
#define WLAN_LOG_OUPUT_SERIAL_LEVEL  1
#else
#define WLAN_LOG_OUPUT_CONSOLE_LEVEL 1
#define WLAN_LOG_OUPUT_FILE_LEVEL    3
#define WLAN_LOG_OUPUT_SERIAL_LEVEL  0
#endif

typedef enum {
    WLAN_LOG_LEVEL_NONE    = 0, 
    WLAN_LOG_LEVEL_ERROR   = 1,
    WLAN_LOG_LEVEL_WARN    = 2,
    WLAN_LOG_LEVEL_INFO    = 3,
    WLAN_LOG_LEVEL_VERBOSE = 4
} WLAN_LOG_LEVEL_TYPE;

typedef enum {
    WLAN_LOG_OUTPUT_CONSOLE = 0,
    WLAN_LOG_OUTPUT_FILE = 1,
    WLAN_LOG_OUTPUT_SERIAL = 2, 
    WLAN_LOG_OUTPUT_MAX
} WLAN_LOG_OUTPUT_TYPE;

typedef struct {
    UINT8               LogLevel[WLAN_LOG_OUTPUT_MAX];
    UINT8               LogFlush;
    EFI_QDF_FILE_HANDLE LogFile;
    UINT64              LogFileWriteSize;

    CHAR16 CfgPartition[32];
    struct {
        UINT32 LogPartitionValid : 1;

        CHAR16 LogPartition[32];
    } Cfg;
} LoggingContext;

extern LoggingContext gLoggingContext;

VOID GlobalLoggingContextInitialize(
    IN EFI_LOADED_IMAGE_PROTOCOL *Image);

VOID GlobalLoggingContextUninitialize(VOID);

#if SUPPORT_DEBUG_PRINT

STATIC inline UINT8
__GlobalLogGetOutput(UINT32 Level)
{
    UINT8 OutputBits = 0;
    if ((gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_CONSOLE]) &&
        (Level <= gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_CONSOLE]))
        OutputBits |= (1 << WLAN_LOG_OUTPUT_CONSOLE);

    if ((gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_FILE]) &&
        gLoggingContext.LogFile &&
        (Level <= gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_FILE])) {
        EFI_TPL PreviousTpl;
        PreviousTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
        gBS->RestoreTPL(PreviousTpl);
        if (PreviousTpl <= TPL_CALLBACK) {
            OutputBits |= (1 << WLAN_LOG_OUTPUT_FILE);
        }
    }

    if ((gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_SERIAL]) &&
        (Level <= gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_SERIAL]))
        OutputBits |= (1 << WLAN_LOG_OUTPUT_SERIAL);

    return OutputBits;
}

VOID __GlobalLogPrintString(UINT8 Output, CONST CHAR8 *Format, ...);
VOID __GlobalLogPrintBuffer(UINT8 Output,
    CONST CHAR8 *Function, UINT32 Line, CONST CHAR8 *Message,
    CONST CHAR8 *Buffer, UINT32 BufferSize, UINT32 MaxPrintSize);

VOID __GlobalLogAsciiPrintString(UINT8 Output, CONST CHAR8 *Format, ...);

VOID GlobalLogFlush(VOID);

#define GlobalLogWrite(_Level, _Format, ...) do {                        \
    UINT8 _Output = __GlobalLogGetOutput(_Level);                        \
    if (_Output) {                                                       \
        MILLISECOND_TYPE _Timestamp = GetTimeInMillisecond();            \
        __GlobalLogPrintString(_Output, "[%06llu.%03llu] " _Format,      \
            _Timestamp / 1000, _Timestamp % 1000, ##__VA_ARGS__);        \
    }                                                                    \
  } while (0)

#define DbgPrint(_Format, ...) do {                                      \
        GlobalLogWrite(WLAN_LOG_LEVEL_ERROR, "%a(%d): " _Format "\n",    \
              __FUNCTION__, __LINE__, ##__VA_ARGS__);                    \
    } while (0)

#define DbgError(_Format, ...) do {                                      \
    GlobalLogWrite(WLAN_LOG_LEVEL_ERROR, "%a(%d): " _Format,             \
              __FUNCTION__, __LINE__, ##__VA_ARGS__);                    \
    } while (0)

#define DbgWarn(_Format, ...) do {                                       \
        GlobalLogWrite(WLAN_LOG_LEVEL_WARN, "%a(%d): " _Format,          \
              __FUNCTION__, __LINE__, ##__VA_ARGS__);                    \
    } while (0)

#define DbgInfo(_Format, ...) do {                                       \
        GlobalLogWrite(WLAN_LOG_LEVEL_INFO, "%a(%d): " _Format,          \
              __FUNCTION__, __LINE__, ##__VA_ARGS__);                    \
    } while (0)

#define DbgVerbose(_Format, ...) do {                                    \
        GlobalLogWrite(WLAN_LOG_LEVEL_VERBOSE, "%a(%d): " _Format,       \
              __FUNCTION__, __LINE__, ##__VA_ARGS__);                    \
    } while (0)

#define DbgRaw(_Level, _Format, ...) do {                                \
       GlobalLogWrite(_Level, _Format, ##__VA_ARGS__);                   \
    } while (0)


#define DbgDump(_Message, _Buffer, _BufferSize, _MaxPrintSize)   do {    \
        UINT8 _Output = __GlobalLogGetOutput(WLAN_LOG_LEVEL_INFO);       \
        if (_Output) {                                                   \
            __GlobalLogPrintBuffer(_Output,                              \
                __FUNCTION__, __LINE__,                                  \
                (CONST CHAR8 *)_Message, (CONST CHAR8 *)_Buffer,         \
                _BufferSize, _MaxPrintSize);                             \
        }                                                                \
    } while (0)

#define DbgFlush GlobalLogFlush

#else // !SUPPORT_DEBUG_PRINT

#define DbgPrint(...) (VOID)sizeof(UINT8)
#define DbgError(...) (VOID)sizeof(UINT8)
#define DbgWarn(...) (VOID)sizeof(UINT8)
#define DbgInfo(...) (VOID)sizeof(UINT8)
#define DbgVerbose(...) (VOID)sizeof(UINT8)
#define DbgRaw(...) (VOID)sizeof(UINT8)
#define DbgFlush() (VOID)sizeof(UINT8)
#define DbgDump(Message, Buffer, Length, MaxLength) (VOID)sizeof(UINT8)

#endif // SUPPORT_DEBUG_PRINT

VOID GlobalLogSetFlushFrequency(UINT32 Frequency);
VOID GlobalLogSetLogLevel(WLAN_LOG_OUTPUT_TYPE Type, UINT8 Level);

#define TO_STRING1(X) #X
#define TO_STRING(X)  TO_STRING1(X)

STATIC inline UINT8 _WarnOn(UINT8 Condition, CONST UINT8 *Function, UINT32 Line, CONST UINT8 *Message)
{
    if (Condition) {
        DbgRaw(WLAN_LOG_LEVEL_WARN, "%a(%u): WARN: %a\n", Function, Line, Message);
    }
    return (Condition);
}

#define WARN_ON(C) _WarnOn((UINT8)(!!(C)), (CONST UINT8 *)__FUNCTION__, __LINE__, (CONST UINT8 *)TO_STRING(C))

#ifndef STATIC_ASSERT
#define STATIC_ASSERT(Expression, Message)
#endif

#define BUILD_BUG_ON(condition)                   \
    STATIC_ASSERT(!(condition), "BUILD_BUG_ON failed: " #condition)

STATIC UINT8 _WarnOnOnce(UINT8 Condition, CONST UINT8 *Function, UINT32 Line, CONST UINT8 *Message)
{
    STATIC BOOLEAN Warned = 0;

    if (Condition && !Warned) {
        Warned = 1;
        DbgRaw(WLAN_LOG_LEVEL_WARN, "%a(%u): WARN: %a\n", Function, Line, Message);
    }
    return (Condition);
}

#define WARN_ON_ONCE(C) _WarnOnOnce((UINT8)(!!(C)), (CONST UINT8 *)__FUNCTION__, __LINE__, (CONST UINT8 *)TO_STRING(C))

#define WARN(condition, format, ...)  do {                                           \
        if (condition)                                                               \
		    DbgWarn("WARN(" TO_STRING(condition) "): " format "\n", ##__VA_ARGS__);  \
    } while(0)

#define DEBUG_PARAMETER(_P) (void)(_P)

#if SUPPORT_DEBUG_PRINT
#define SUPP_DBG(_fmt, ...) DbgInfo(_fmt "\n", ##__VA_ARGS__)
#define SUPP_WRN(_fmt, ...) DbgWarn(MSG_WARNING, _fmt "\n", ##__VA_ARGS__)
#define SUPP_ERR(_fmt, ...) DbgError(MSG_ERROR, _fmt "\n", ##__VA_ARGS__)
#else
#define SUPP_DBG(_fmt, ...) (VOID)sizeof(UINT8)
#define SUPP_WRN(_fmt, ...) (VOID)sizeof(UINT8)
#define SUPP_ERR(_fmt, ...) (VOID)sizeof(UINT8)
#endif

#endif // !__DEBUG_H

