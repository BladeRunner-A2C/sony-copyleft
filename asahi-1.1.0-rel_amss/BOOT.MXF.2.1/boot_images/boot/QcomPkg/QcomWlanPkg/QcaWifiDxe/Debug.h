/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
 
/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 18/11/21  zxue     refine code
 19/10/21  zxue     refine code and remove the diag log
 6/9/21    zxue     fix parasoft issue
 26/8/21   zxue     support logfs
 3/8/21    zxue     enable serial log output in debug version
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __DEBUG_H
#define __DEBUG_H

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/LoadedImage.h>
#include <qdf/file.h>
#include <qdf/smbios.h>
#include "Config.h"
#include "Utils.h"

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

#define ENALBE_LOGFILE_TIMELY_FLUSH  0

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

typedef enum {
    WLAN_DEBUG_DATA = 0x00000001,
} WLAN_DEBUG_MASK;

typedef struct {
    UINT8               LogLevel[WLAN_LOG_OUTPUT_MAX];
    UINT8               LogFlush;
    EFI_QDF_FILE_HANDLE LogFile;
    UINT64              LogFileWriteSize;

#if SUPPORT_WMI_DIAG_LOG
    EFI_QDF_FILE_HANDLE WmiFile;          // Using WMI Event to save the fw logs
    UINT64              WmiFileWriteSize;
#endif

    CHAR16 CfgPartition[32];
    struct {
        UINT32 DebugMaskValid : 1;
        UINT32 CountryCodeValid : 1;
        UINT32 LogPartitionValid : 1;

        UINT64 DebugMask;
        UINT8  CountryCode[4];
        CHAR16 LogPartition[32];
    } Cfg;

#if SUPPORT_SMBIOS_CFG
	SMBIOS_CFG SmbiosCfg;
#endif
} LoggingContext;

extern LoggingContext gLoggingContext;

VOID GlobalLoggingContextInitialize(
    IN EFI_LOADED_IMAGE_PROTOCOL *Image);

VOID GlobalLoggingContextUninitialize(VOID);

VOID GlobalLoggingFirmwareTraceInitialize(VOID);

VOID GlobalLoggingFirmwareTraceUninitialize(VOID);

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

#define DbgTxRxInfo(_Format, ...) do {                                   \
        if ((gLoggingContext.Cfg.DebugMask >> 32) & WLAN_DEBUG_DATA) {   \
            GlobalLogWrite(WLAN_LOG_LEVEL_INFO, "%a(%d): " _Format,      \
                  __FUNCTION__, __LINE__, ##__VA_ARGS__);                \
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
#define DbgTxRxInfo(...) (VOID)sizeof(UINT8)

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

// ----------------------------
// Configuration

static inline UINT8 CfgIsCountryCodeValid(VOID)
{
    return (UINT8)gLoggingContext.Cfg.DebugMaskValid;
}

static inline CONST UINT8 *CfgGetCountryCode(VOID)
{
    return gLoggingContext.Cfg.CountryCode;
}

/* ath pci driver usage */

static inline u8 cfg_is_ath_debug_mask_valid(VOID)
{
    return (u8)gLoggingContext.Cfg.DebugMaskValid;
}

static inline u32 cfg_get_ath_debug_mask(VOID)
{
    return (u32)gLoggingContext.Cfg.DebugMask;
}

static inline u32 cfg_is_ath_6G_disabled(VOID)
{
#if SUPPORT_SMBIOS_CFG
    /* 
	    Configure 11ac/ax:
	    Bit 0: 1: Disable 11ac/0: Enable 11ac
	    Bit 1: 1: Disable 11ax/0: Enable 11ax
	    Bit 2: 1: Enable 11ax for Ukraine/0: Disable 11ax for Ukraine if the value of Bit1 is 0
	    Bit 3: 1: Forcedly disable 6Ghz band/0: Follow the current driver setting-------------- [Support]                  
	    Bit 4: 1: Forcedly disable 5.9GHz band/ 0: Follow the current driver setting
	*/
    return((gLoggingContext.SmbiosCfg.ACAXCfg >> 3) & 1);
#else
    return 0;
#endif
}

/* dump files */

static inline int fdump(const u16 *filename, u8 *buffer, u64 *buffersize)
{
    EFI_STATUS Status = QdfWriteFile(gLoggingContext.Cfg.LogPartition, (CONST CHAR16 *)filename,
        (VOID *)buffer, (UINTN *)buffersize);
    return efi_status_to_errno(Status);
}

static inline int fdump_segments(const u16 *filename, struct segment *segments)
{
    EFI_STATUS Status = QdfWriteFileSegments(gLoggingContext.Cfg.LogPartition, (CONST CHAR16 *)filename,
        (struct Segment *)segments);
    return efi_status_to_errno(Status);
}

#endif // !__DEBUG_H

