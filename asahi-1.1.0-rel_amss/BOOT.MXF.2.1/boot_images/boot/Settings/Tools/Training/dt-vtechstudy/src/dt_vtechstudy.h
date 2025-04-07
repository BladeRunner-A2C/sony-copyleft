/* FILE: dt_vtechstudy.h
 * 
 * DESCRIPTION: Common header file for the various lessons
 * 
 */

#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>

#include "libfdt.h"

#define DTB_LINE_BUF_SIZE 0x100		/* size of buffer(s) used for output */

/* Error codes added by QC to augment FdtLib code */
#define FDT_ERR_QC_NOERROR 0
#define FDT_ERR_QC_NULLPTR 1000
#define FDT_ERR_QC_BUF2SMALL 1002
#define FDT_ERR_QC_BAD_SELECTOR 1017
#define FDT_ERR_QC_FDTLIB_ERROR 1018

#define ROOT_OFFSET 0		/* offset for root node in DTB */

/* sample code pulled from sources that used these macros */
#define SNPRINTF snprintf
#define PUTS puts

#define PTR_CHECK(ptr) do { \
	if (NULL == ptr) return -FDT_ERR_QC_NULLPTR; \
} while(0)

#define TIMESTAMP(ts) do { \
	gettimeofday(ts, NULL); \
} while (0)

/* Config settings for library, controls debug output */
typedef struct {
        int     client;
        int     trace;
        int     verbose;
} Config;
extern Config dtb_config;

typedef struct {
	char *name;		/* property name */
	char format;	/* property data type: b=8-bits, h=16-bits, w=32-bits, d=64-bits */
} property;

/* defines size (bytes) of each native data type in DTB */
typedef enum dt_data_type {
	dt_uint8 = 1,
	dt_uint16 = 2,
	dt_uint32 = 4,
	dt_uint64 = 8
} dt_data_type;

/* allows single variable to hold any data type */
typedef union dt_ptr_type {
	uint8_t  *u8;
	uint16_t *u16;
	uint32_t *u32;
	uint64_t *u64;
} dt_ptr_type;

/* shared entry-points */

/* from dt_vtechstudy.c */
extern char *strError(int error);
extern int time_delta(struct timeval *tv_s, struct timeval *tv_e);
extern int fdt_check_for_valid_blob(const void *blob, size_t bsize);

/* from DTBHexDump.c */
extern void dtb_hex_dump(char *title, void *addr, int length);

/* from main.c */
extern void read_blob(char *fn, void **blob, size_t *b_size);
extern void write_blob(char *fn, void *blob, size_t b_size);

/* entry-point for each lesson/example, reference in main.c */
extern int example(void *blob, size_t size);
