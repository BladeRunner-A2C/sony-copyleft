/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include "Debug.h"
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <qdf/cfg.h>

#define DEBUG_LOG_FILE_NAME          L"WlanSupplicantDxe.log"
#define DEBUG_LOG_FILE_BACKUP_NAME   L"WlanSupplicantDxe.log.bak"
#define DEBUG_LOG_FILE_MAX_SIZE      (1024*1024*1024*2ULL)

#define CFG_FILE_NAME                L"WlanSupplicantDxe.cfg"

STATIC CONST CHAR16 *DEFAULT_CFG_PARTITIONS[] = {
    L"",
    L"LOGFS:\\",
};
extern EFI_BOOT_SERVICES *gBS;
extern const char *os_compatible_format(const char *fmt, char *newfmt, int newlen);

LoggingContext gLoggingContext = {
    .LogLevel = { WLAN_LOG_OUPUT_CONSOLE_LEVEL, WLAN_LOG_OUPUT_FILE_LEVEL, WLAN_LOG_OUPUT_SERIAL_LEVEL },
    .LogFile = NULL,
    .LogFlush = ENALBE_LOGFILE_TIMELY_FLUSH,
};

STATIC
VOID
GlobalHandleConfiguration(VOID *Ctx, CONST u8 *SKey, CONST u8 *SValue)
{
    CONST CHAR8* Key = (CONST CHAR8*)SKey;
	CONST CHAR8* Value = (CONST CHAR8*)SValue;
    DbgError("%a=%a\n", Key, Value);

    if (AsciiStriCmp("ConsoleLogLevel", Key) == 0) {
        gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_CONSOLE] = (UINT8)AsciiStrDecimalToUintn(Value);
        return;
    }

    if (AsciiStriCmp("FileLogLevel", Key) == 0) {
        gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_FILE] = (UINT8)AsciiStrDecimalToUintn(Value);
        return;
    }
    if (AsciiStriCmp("FileLogFlush", Key) == 0) {
        GlobalLogSetFlushFrequency((UINT32)AsciiStrDecimalToUintn(Value));
        return;
    }

    if (AsciiStriCmp("SerialLogLevel", Key) == 0) {
        gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_SERIAL] = (UINT8)AsciiStrDecimalToUintn(Value);
        return;
    }
}

STATIC
VOID
GlobalApplyConfiguration(VOID)
{
    EFI_STATUS Status;
    UINT8 *CfgData;
    UINTN CfgSize;
    UINT32 i;

    // Read configuration file
    for (i = 0; i < ARRAY_SIZE(DEFAULT_CFG_PARTITIONS); i++) {
        Status = QdfReadFile(DEFAULT_CFG_PARTITIONS[i], CFG_FILE_NAME, (VOID **)&CfgData, &CfgSize);
        if (EFI_ERROR(Status)) {
			DbgError("Configuration file '%s%s' is not available.\n", DEFAULT_CFG_PARTITIONS[i], CFG_FILE_NAME);
            continue;
        }

        // Save the path
        StrCpyS(gLoggingContext.CfgPartition, ARRAY_SIZE(gLoggingContext.CfgPartition),
            DEFAULT_CFG_PARTITIONS[i]);

        // Parse and apply the configuration
        cfg_parse(CfgData, (u32)CfgSize, GlobalHandleConfiguration, NULL);
        FreePool(CfgData);

        break;
    }
	
	// Use the first configured partition as default when no configuration file is found
	if (i == ARRAY_SIZE(DEFAULT_CFG_PARTITIONS)) {
	    StrCpyS(gLoggingContext.CfgPartition, ARRAY_SIZE(gLoggingContext.CfgPartition),
            DEFAULT_CFG_PARTITIONS[0]);
	}

    // Default log files are on the same partition with configuration file
    if (!gLoggingContext.Cfg.LogPartitionValid) {
        Status = StrnCpyS(gLoggingContext.Cfg.LogPartition, ARRAY_SIZE(gLoggingContext.Cfg.LogPartition),
            gLoggingContext.CfgPartition, ARRAY_SIZE(gLoggingContext.CfgPartition));
        gLoggingContext.Cfg.LogPartitionValid = !EFI_ERROR(Status);
    }
}

STATIC
EFI_STATUS
GlobalLoggingOpenFile(
    CONST CHAR16 *FileName, 
    CONST CHAR16 *BackupFileName, 
    EFI_QDF_FILE_HANDLE *FileHandle)
{
    EFI_STATUS Status;

    QdfRenameFile(gLoggingContext.Cfg.LogPartition, FileName, BackupFileName);

    Status = QdfOpenFile(gLoggingContext.Cfg.LogPartition, FileName,
        EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,
        FileHandle);

    return Status;
}

// FileTrace
EFI_STATUS GlobalLoggingInitializeFileTrace(VOID)
{
    EFI_STATUS Status = EFI_SUCCESS;

    if (!gLoggingContext.LogFile) {
        Status = GlobalLoggingOpenFile(DEBUG_LOG_FILE_NAME, DEBUG_LOG_FILE_BACKUP_NAME, 
            &gLoggingContext.LogFile);
        if (EFI_ERROR(Status)) {
            DbgError("Fail to open log file: %r\n", Status);
        }
    }
    
    return Status;
}

VOID GlobalLoggingUninitializeFileTrace(VOID)
{
    if (gLoggingContext.LogFile != NULL) {
        QdfFileClose(gLoggingContext.LogFile);
        gLoggingContext.LogFile = NULL;
        gLoggingContext.LogFileWriteSize = 0;
    }
}

VOID GlobalLoggingContextInitialize(
    IN EFI_LOADED_IMAGE_PROTOCOL *Image)
{
#if SUPPORT_DEBUG_PRINT
    GlobalApplyConfiguration();
    if (gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_FILE]) {
        GlobalLoggingInitializeFileTrace();
    }
#endif
}

VOID GlobalLoggingContextUninitialize(VOID)
{
#if SUPPORT_DEBUG_PRINT
    GlobalLoggingUninitializeFileTrace();
#endif
}

VOID GlobalLogSetFlushFrequency(UINT32 Frequency)
{
    gLoggingContext.LogFlush = (Frequency >= 1);
}

VOID GlobalLogSetLogLevel(WLAN_LOG_OUTPUT_TYPE Type, UINT8 Level)
{
#if SUPPORT_DEBUG_PRINT
    if (Type == WLAN_LOG_OUTPUT_CONSOLE) {
        gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_CONSOLE] = Level;
        return;
    }
    if (Type == WLAN_LOG_OUTPUT_FILE) {
        EFI_TPL PreviousTpl;

        /* Validate the TPL */
        PreviousTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
        gBS->RestoreTPL(PreviousTpl);
        if (PreviousTpl > TPL_CALLBACK) {
            DbgError("Failed to set file log level: %r\n", EFI_ACCESS_DENIED);
            return;
        }

        /* Update level */
        gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_FILE] = Level;
        if (gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_FILE]) {
            GlobalLoggingInitializeFileTrace();
        }
        else {
            GlobalLoggingUninitializeFileTrace();
        }
        return;
    }
    if (Type == WLAN_LOG_OUTPUT_SERIAL) {
        gLoggingContext.LogLevel[WLAN_LOG_OUTPUT_SERIAL] = Level;
        return;
    }
#endif
}

#if SUPPORT_DEBUG_PRINT

#define MAX_BUFFER_STR_LENGTH 48

STATIC VOID __GlobalLogPrintMessage(UINT8 Output, CONST CHAR8 *Message, UINTN Length)
{
    if (Output & (1 << WLAN_LOG_OUTPUT_CONSOLE)) {
        AsciiPrint(Message);
    }

    if (Output & (1 << WLAN_LOG_OUTPUT_FILE)) {
        QdfFileWrite(gLoggingContext.LogFile, (VOID *)Message, &Length);
        if (gLoggingContext.LogFlush) {
            QdfFileFlush(gLoggingContext.LogFile);
        }
        gLoggingContext.LogFileWriteSize += Length;
        if (gLoggingContext.LogFileWriteSize >= DEBUG_LOG_FILE_MAX_SIZE) {
            GlobalLoggingUninitializeFileTrace();
            GlobalLoggingInitializeFileTrace();
        }
    }

    if (Output & (1 << WLAN_LOG_OUTPUT_SERIAL)) {
        DebugPrint(EFI_D_ERROR, Message);
    }
}

VOID __GlobalLogPrintString(UINT8 Output, CONST CHAR8 *Format, ...)
{
    CHAR8 Message[512];
    UINTN Length;
    VA_LIST Marker;

    // Convert the message to an ASCII String
    VA_START(Marker, Format);
    Length = AsciiVSPrint(Message, sizeof(Message), Format, Marker);
    VA_END(Marker);

    __GlobalLogPrintMessage(Output, Message, Length);
}

VOID __GlobalLogAsciiPrintString(UINT8 Output, CONST CHAR8 *Format, ...)
{
    CHAR8 Message[512];
    CHAR8 NewFormat[384];
    UINTN Length;
    VA_LIST Marker;

    // Convert the message to an ASCII String
    VA_START(Marker, Format);
    Length = AsciiVSPrint(Message, sizeof(Message),
        os_compatible_format(Format, NewFormat, sizeof(NewFormat)), Marker);
    VA_END(Marker);

    __GlobalLogPrintMessage(Output, Message, Length);
}

VOID __GlobalLogPrintBuffer(UINT8 Output,
    CONST CHAR8 *Function, UINT32 Line, CONST CHAR8 *Message,
    CONST CHAR8 *Buffer, UINT32 BufferSize, UINT32 MaxPrintSize)
{
    CONST STATIC CHAR8 FormatString[] = "%02X ";
    CONST UINT32 MAX_STRING_END_POSITION = MAX_BUFFER_STR_LENGTH - (sizeof(FormatString) * 2);

    UINT32 i;
    CHAR8 Temp[MAX_BUFFER_STR_LENGTH + 1];
    UINTN Position = 0;
    UINT32 PrintSize = (MaxPrintSize > 0) ? MIN(MaxPrintSize, BufferSize) : BufferSize;
    MILLISECOND_TYPE Timestamp = GetTimeInMillisecond();

    __GlobalLogPrintString(Output,
        "[%06llu.%03llu] %a(%u): %a<%d BYTES FROM 0x%p(%u)>\n",
        Timestamp / 1000, Timestamp % 1000,
        Function, Line, Message ? Message : "PRINT ",
        PrintSize, Buffer, BufferSize);

    for (i = 0; i < PrintSize; i++) {
        UINTN CharsWritten;

        CharsWritten = AsciiSPrint(&Temp[Position],
            MAX_BUFFER_STR_LENGTH - Position, FormatString, (UINT8)Buffer[i]);
        Position += CharsWritten;

        if (Position >= MAX_STRING_END_POSITION) {
            Temp[Position] = 0;
            __GlobalLogPrintString(Output, "[%06llu.%03llu] %a(%u): %a\n",
                Timestamp / 1000, Timestamp % 1000, Function, Line, Temp);
            Position = 0;
        }
    }

    if (Position && (Position < MAX_STRING_END_POSITION)) {
        Temp[Position] = 0;
        __GlobalLogPrintString(Output, "[%06llu.%03llu] %a(%u): %a\n",
            Timestamp / 1000, Timestamp % 1000, Function, Line, Temp);
    }
}

#endif


VOID GlobalLogFlush(VOID)
{
    EFI_TPL PreviousTpl;

    PreviousTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
    gBS->RestoreTPL(PreviousTpl);

    if (PreviousTpl <= TPL_CALLBACK) {
#if SUPPORT_DEBUG_PRINT
        if (gLoggingContext.LogFile) {
            QdfFileFlush(gLoggingContext.LogFile);
        }
#endif
    }
}
