/*
 * wpa_supplicant/hostapd / Debug prints
 * Copyright (c) 2002-2013, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef WPA_DEBUG_H
#define WPA_DEBUG_H

#include "wpabuf.h"

extern int wpa_debug_level;
extern int wpa_debug_show_keys;
extern int wpa_debug_timestamp;
#ifdef CONFIG_DEBUG_SYSLOG
extern int wpa_debug_syslog;
#endif /* CONFIG_DEBUG_SYSLOG */

/* Debugging function - conditional printf and hex dump. Driver wrappers can
 * use these for debugging purposes. */

enum {
	MSG_EXCESSIVE, MSG_MSGDUMP, MSG_DEBUG, MSG_INFO, MSG_WARNING, MSG_ERROR
};

#if defined(CONFIG_NO_STDOUT_DEBUG)

#define wpa_debug_flush() do { } while (0)
#define wpa_debug_print_timestamp() do { } while (0)
#define wpa_printf(args,...) do { } while (0)
#define wpa_hexdump(l,t,b,le) do { } while (0)
#define wpa_hexdump_buf(l,t,b) do { } while (0)
#define wpa_hexdump_key(l,t,b,le) do { } while (0)
#define wpa_hexdump_buf_key(l,t,b) do { } while (0)
#define wpa_hexdump_ascii(l,t,b,le) do { } while (0)
#define wpa_hexdump_ascii_key(l,t,b,le) do { } while (0)
#define wpa_debug_open_file(p) do { } while (0)
#define wpa_debug_close_file() do { } while (0)
#define wpa_debug_setup_stdout() do { } while (0)
#define wpa_dbg(args,...) do { } while (0)

static inline int wpa_debug_reopen_file(void)
{
	return 0;
}

#else /* CONFIG_NO_STDOUT_DEBUG */
#ifdef CONFIG_UEFI
#include <Debug.h>

#if SUPPORT_DEBUG_PRINT

static inline u8 wpa_get_log_output(u32 level)
{
    static u32 llm[] = {
        WLAN_LOG_LEVEL_VERBOSE,
        WLAN_LOG_LEVEL_INFO,
        WLAN_LOG_LEVEL_INFO,
        WLAN_LOG_LEVEL_INFO,
        WLAN_LOG_LEVEL_WARN,
        WLAN_LOG_LEVEL_ERROR
    };
    u32 dbg_level;

    dbg_level = (level < ARRAY_SIZE(llm)) ? llm[level] : WLAN_LOG_LEVEL_VERBOSE;
    return __GlobalLogGetOutput(dbg_level);
}

#define wpa_printf(_level, _fmt, ...) do {                      \
        if ((_level) < wpa_debug_level)                         \
		    break;                                              \
        u8 _output = wpa_get_log_output(_level);                \
        if (_output) {                                          \
            u64 _timestamp = GetTimeInMillisecond();            \
            __GlobalLogAsciiPrintString(_output,                \
                "[%06llu.%03llu] %a(%d):" _fmt "\n",            \
                 _timestamp / 1000, _timestamp % 1000,          \
                 __FUNCTION__, __LINE__, ##__VA_ARGS__);        \
        }                                                       \
    } while (0)

#define _wpa_hexdump(_level, _title, _buf, _len, _show) do {   \
	    if ((_level) < wpa_debug_level)                        \
		    break;                                             \
        u8 _output = wpa_get_log_output(_level);               \
        if (_output) {                                         \
            __GlobalLogPrintBuffer(_output,                    \
            __FUNCTION__, __LINE__,          				   \
            (CONST CHAR8*)_title, (CONST CHAR8*)_buf,          \
            (u32)_len, (u32)_show);                            \
        }                                                      \
    } while (0)

#define wpa_hexdump(_level, _title, _buf, _len)           \
    _wpa_hexdump((_level), (_title), (_buf), (_len), 0);

#define wpa_hexdump_key(_level, _title, _buf, _len)       \
    _wpa_hexdump((_level), (_title), (_buf), (_len), 0);

#define wpa_hexdump_ascii(_level, _title, _buf, _len)     \
    _wpa_hexdump((_level), (_title), (_buf), (_len), 0);

#define wpa_hexdump_ascii_key(_level, _title, _buf, _len)  \
    _wpa_hexdump((_level), (_title), (_buf), (_len), 0);

#define wpa_debug_flush GlobalLogFlush

#endif /* !SUPPORT_DEBUG_PRINT */
#endif /* CONFIG_UEFI */

#ifndef CONFIG_UEFI

int wpa_debug_open_file(const char *path);
int wpa_debug_reopen_file(void);
void wpa_debug_close_file(void);
void wpa_debug_setup_stdout(void);

/**
 * wpa_debug_printf_timestamp - Print timestamp for debug output
 *
 * This function prints a timestamp in seconds_from_1970.microsoconds
 * format if debug output has been configured to include timestamps in debug
 * messages.
 */
void wpa_debug_print_timestamp(void);

/**
 * wpa_printf - conditional printf
 * @level: priority level (MSG_*) of the message
 * @fmt: printf format string, followed by optional arguments
 *
 * This function is used to print conditional debugging and error messages. The
 * output may be directed to stdout, stderr, and/or syslog based on
 * configuration.
 *
 * Note: New line '\n' is added to the end of the text when printing to stdout.
 */
void wpa_printf(int level, const char *fmt, ...)
PRINTF_FORMAT(2, 3);

/**
 * wpa_hexdump - conditional hex dump
 * @level: priority level (MSG_*) of the message
 * @title: title of for the message
 * @buf: data buffer to be dumped
 * @len: length of the buf
 *
 * This function is used to print conditional debugging and error messages. The
 * output may be directed to stdout, stderr, and/or syslog based on
 * configuration. The contents of buf is printed out has hex dump.
 */
void wpa_hexdump(int level, const char *title, const void *buf, size_t len);


#endif

static inline void wpa_hexdump_buf(int level, const char *title,
				   const struct wpabuf *buf)
{
	wpa_hexdump(level, title, buf ? wpabuf_head(buf) : NULL,
		    buf ? wpabuf_len(buf) : 0);
}

static inline void wpa_hexdump_buf_key(int level, const char *title,
				       const struct wpabuf *buf)
{
	wpa_hexdump_key(level, title, buf ? wpabuf_head(buf) : NULL,
			buf ? wpabuf_len(buf) : 0);
}


/*
 * wpa_dbg() behaves like wpa_msg(), but it can be removed from build to reduce
 * binary size. As such, it should be used with debugging messages that are not
 * needed in the control interface while wpa_msg() has to be used for anything
 * that needs to shown to control interface monitors.
 */
#ifdef CONFIG_UEFI
#define wpa_dbg(ctx, level, fmt, ...) wpa_printf(level, fmt, ##__VA_ARGS__)
#else
#define wpa_dbg(args...) wpa_msg(args)
#endif /* CONFIG_UEFI */

#endif /* CONFIG_NO_STDOUT_DEBUG */


#ifdef CONFIG_UEFI
#define wpa_msg(ctx, level, fmt, ...) wpa_printf(level, fmt, ##__VA_ARGS__);
#endif

#ifdef CONFIG_NO_HOSTAPD_LOGGER
#define hostapd_logger(args, ...) do { } while (0)
#define hostapd_logger_register_cb(f) do { } while (0)
#else /* CONFIG_NO_HOSTAPD_LOGGER */
void hostapd_logger(void *ctx, const u8 *addr, unsigned int module, int level,
		    const char *fmt, ...) PRINTF_FORMAT(5, 6);

typedef void (*hostapd_logger_cb_func)(void *ctx, const u8 *addr,
				       unsigned int module, int level,
				       const char *txt, size_t len);

/**
 * hostapd_logger_register_cb - Register callback function for hostapd_logger()
 * @func: Callback function (%NULL to unregister)
 */
void hostapd_logger_register_cb(hostapd_logger_cb_func func);
#endif /* CONFIG_NO_HOSTAPD_LOGGER */

#define HOSTAPD_MODULE_IEEE80211	0x00000001
#define HOSTAPD_MODULE_IEEE8021X	0x00000002
#define HOSTAPD_MODULE_RADIUS		0x00000004
#define HOSTAPD_MODULE_WPA		0x00000008
#define HOSTAPD_MODULE_DRIVER		0x00000010
#define HOSTAPD_MODULE_IAPP		0x00000020
#define HOSTAPD_MODULE_MLME		0x00000040

enum hostapd_logger_level {
	HOSTAPD_LEVEL_DEBUG_VERBOSE = 0,
	HOSTAPD_LEVEL_DEBUG = 1,
	HOSTAPD_LEVEL_INFO = 2,
	HOSTAPD_LEVEL_NOTICE = 3,
	HOSTAPD_LEVEL_WARNING = 4
};


#ifdef CONFIG_DEBUG_SYSLOG

void wpa_debug_open_syslog(void);
void wpa_debug_close_syslog(void);

#else /* CONFIG_DEBUG_SYSLOG */

static inline void wpa_debug_open_syslog(void)
{
}

static inline void wpa_debug_close_syslog(void)
{
}

#endif /* CONFIG_DEBUG_SYSLOG */

#ifdef CONFIG_DEBUG_LINUX_TRACING

int wpa_debug_open_linux_tracing(void);
void wpa_debug_close_linux_tracing(void);

#else /* CONFIG_DEBUG_LINUX_TRACING */

static inline int wpa_debug_open_linux_tracing(void)
{
	return 0;
}

static inline void wpa_debug_close_linux_tracing(void)
{
}

#endif /* CONFIG_DEBUG_LINUX_TRACING */


#ifdef EAPOL_TEST
#define WPA_ASSERT(a)						       \
	do {							       \
		if (!(a)) {					       \
			printf("WPA_ASSERT FAILED '" #a "' "	       \
			       "%s %s:%d\n",			       \
			       __FUNCTION__, __FILE__, __LINE__);      \
			exit(1);				       \
		}						       \
	} while (0)
#elif CONFIG_UEFI
#include <Library/DebugLib.h>
#define WPA_ASSERT(a) ASSERT(a)
#else
#define WPA_ASSERT(a) do { } while (0)
#endif

const char * debug_level_str(int level);
int str_to_debug_level(const char *s);

#endif /* WPA_DEBUG_H */
