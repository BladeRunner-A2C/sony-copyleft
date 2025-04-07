/*
 * Copyright (c) 2020-2021, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 18/11/21  zxue     refine code
 17/9/21   zxue     disable load fw from amssall.bin
 6/9/21    zxue     fix parasoft issue
 1/9/21    zxue     fix KW issue
 26/8/21   zxue     support HSP2.1
 30/7/21   zxue     support fw boot recovery
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <qdf/qbase.h>
#include <qdf/file.h>
#include <qdf/pr_debug.h>
#include <xz/xz.h>
#include <crypto/sha256.h>
#include <Config.h>
#include "firmware.h"


#define SUPPORT_QCWLAN_FW_RAW     1
#define SUPPORT_QCWLAN_FW_XZ      1
#define SUPPORT_QCWLAN_FW_FV      1

#if SUPPORT_QCOM_PARTITION
#define SUPPORT_QCWLAN_FW_PART    1
#endif

#define SUPPORT_QCWLAN_XZFW_V1    0              /* v1 is only needed for x86 */
#define SUPPORT_QCWLAN_XZFW_HASH_VERIFICATION 1  /* hash verification is disabled for x86 */

extern EFI_GUID gEfiQcWlanXzfw1Guid;
extern EFI_GUID gEfiQcWlanXzfwPartitionGuid;
extern EFI_GUID gEfiQcWlanXzfwPartitionBakGuid;

/* Default filename for compressed firmware file */
#define AMSS_ALL_BIN_FILE L"amssall.bin"

#if SUPPORT_QCWLAN_XZFW_V1
/* QCWLAN_XZFW1 */
const static u8 MAGIC_QCWLAN_XZFW_V1[12] = { 
    'Q', 'C', 'W', 'L', 'A', 'N', '_', 'X', 'Z', 'F', 'W', '1' };
#endif /* !SUPPORT_QCWLAN_XZFW_V1 */

/* QCWLAN_XZFW2 */
const static u8 MAGIC_QCWLAN_XZFW_V2[12] = {
    'Q', 'C', 'W', 'L', 'A', 'N', '_', 'X', 'Z', 'F', 'W', '2' };


struct partition_info {
	u64 last_error;
    u8 next;
    GUID *list[2];
};

/* cache the xz firmare to avoid read files multiple times */
static struct {
    void *data;
    u64 size;
	bool read_from_partition; //Use FreePages() to free the memory for partition case
	
	/* partition information */
    struct partition_info pi;
} __g_amss_all_cache = {
    .data = NULL,
    .size = 0,
    .read_from_partition = false,
    .pi = {
    	.last_error = 0,
        .next = 0,
        .list = { &gEfiQcWlanXzfwPartitionGuid, &gEfiQcWlanXzfwPartitionBakGuid }
    }
};

/* QCWLAN compressed firmware header */
#pragma pack(1)
struct qcwlan_xzfw_hdr {
    u8 magic[12];
    u16 version;           /* reserved */
    u16 n_metadata_desc;   /* number of the metadata descriptors */
    u8 name[32];           /* name */
    u32 compressed_size;   /* compressed size */
    u32 uncompressed_size; /* uncompressed size */
};

struct metadata_desc {
    u16 id;
    u16 len;
};

enum metadata_type {
    METADATA_SHA256_HASH = 1,
    METADATA_DESCRIPTION = 2
};

#pragma pack()

#if SUPPORT_QCWLAN_XZFW_HASH_VERIFICATION

static int sha256_hash1(u8 *buf, u64 buf_size, struct sha256_hash_info *hash_info)
{
    static const u16 SHA256_HASH1_METHOD = 1;
    static const u32 SHA256_HASH1_BLOCK_SIZE = 8 * 1024;
    static const u8 SHA256_HASH1_OBFUSCATED_CODE[][16] = {
        { 0xEC, 0x94, 0x9F, 0x5A, 0xE7, 0x80, 0x48, 0xA0, 0xB7, 0x2C, 0xA0, 0x21, 0xD1, 0x72, 0xF5, 0xDE },
        { 0x37, 0x6B, 0xD2, 0x8E, 0xE2, 0xE4, 0x4D, 0x87, 0x89, 0xC3, 0x06, 0x16, 0xA6, 0xC6, 0x16, 0xFB },
        { 0x02, 0xD3, 0x90, 0x28, 0x06, 0x01, 0x40, 0xD5, 0xAA, 0x4D, 0x40, 0xD6, 0x63, 0x0A, 0x2A, 0x3F },
    };

    struct sha256_state ctx;
    u32 big_block_num = (u32)((buf_size + SHA256_HASH1_BLOCK_SIZE - 1) / SHA256_HASH1_BLOCK_SIZE) - 1;
    u32 last_block_size = (u32)(buf_size - SHA256_HASH1_BLOCK_SIZE * big_block_num);
    u64 i;
    int ret;

    do {
        sha256_init(&ctx);
        for (i = 0; i < big_block_num; i++) {
            if (sha256_process(&ctx, &buf[i * SHA256_HASH1_BLOCK_SIZE], SHA256_HASH1_BLOCK_SIZE)) {
                ret = -ENOEXEC;
                break;
            }

            if (sha256_process(&ctx, SHA256_HASH1_OBFUSCATED_CODE[i % 3], 
                sizeof(SHA256_HASH1_OBFUSCATED_CODE[0]))) {
                ret = -ENOEXEC;
                break;
            }
        }

        if (last_block_size) {
            if (sha256_process(&ctx, &buf[i * SHA256_HASH1_BLOCK_SIZE], last_block_size)) {
                ret = -ENOEXEC;
                break;
            }
            if (sha256_process(&ctx, SHA256_HASH1_OBFUSCATED_CODE[i % 3], 
                sizeof(SHA256_HASH1_OBFUSCATED_CODE[0]))) {
                ret = -ENOEXEC;
                break;
            }
        }

        if (sha256_done(&ctx, hash_info->values)) {
            ret = -ENOEXEC;
            break;
        }

        hash_info->method = SHA256_HASH1_METHOD;
        ret = 0;
    } while (0);

    if (ret) {
        pr_err("failed to calculate the hash: %d\n", ret);
    }
    else {
        pr_debug("hash method: %d\n", hash_info->method);
        pr_array("hash digest: ", hash_info->values, sizeof(hash_info->values), 0);
    }

    return ret;
}

static int __validate_firmware_hash(struct firmware *fw, const struct sha256_hash_info *hash_info)
{
    struct sha256_hash_info calculated_hash_info = { 0 };
    int ret = 0;

    do {
        ret = sha256_hash1(fw->data, fw->size, &calculated_hash_info);
        if (ret) {
            pr_err("failed to calculate the sha256 hash\n");
            break;
        }
        if (memcmp(&calculated_hash_info, hash_info, sizeof(calculated_hash_info)) != 0) {
            pr_err("sha256 hash is mismatched\n");
            ret = -EAUTH;
            break;
        }

        pr_debug("validate firmware hash success\n");
    } while (0);

    return ret;
}

#endif /* SUPPORT_QCWLAN_XZFW_HASH_VERIFICATION */

static int __uncompress_firmware_xz(struct firmware *fw, const u8 *buf, u64 buf_size, u32 uncompressed_size)
{
    struct xz_dec *xz_ctx;
    struct xz_buf xz_buf = { 0 };
    enum xz_ret xz_ret;
    u8 *uncompressed_data;
    int ret;

    uncompressed_data = AllocateZeroPool(uncompressed_size);
    if (!uncompressed_data) {
        return -ENOMEM;
    }

    do {
        xz_crc32_init();
        xz_ctx = xz_dec_init(XZ_SINGLE, 0);
        if (xz_ctx == NULL) {
            pr_err("XZ failed to initialize\n");
            ret = -ENOEXEC;
            break;
        }

        xz_buf.in = buf;
        xz_buf.in_size = buf_size;
        xz_buf.out = uncompressed_data;
        xz_buf.out_size = uncompressed_size;

        xz_ret = xz_dec_run(xz_ctx, &xz_buf);
        if (xz_ret != XZ_STREAM_END) {
            pr_err("Failed to decompress FW file (%d)\n", xz_ret);
            ret = -ENOEXEC;
            break;
        }

        xz_dec_end(xz_ctx);

        fw->data = uncompressed_data;
        fw->size = uncompressed_size;
        uncompressed_data = NULL;
        ret = 0;
    } while (0);

    if (uncompressed_data)
        FreePool(uncompressed_data);

    return ret;
}

static int __parse_firmware_metadata(
    const struct metadata_desc *metadata_desc_list, u16 n_metadata_desc, 
    const u8 *buf, u64 size, 
    struct firmware_metadata *metadata)
{
    const u8 *pos = buf;
    u64 remain_size = size;
    const struct metadata_desc *metadata_desc;
    u16 i;
    int ret = 0;

    metadata->begin = pos;
    metadata->description = NULL;
    metadata->description_len = 0;
    metadata->hash_info = NULL;

    for (i = 0; i < n_metadata_desc; i++) {
        metadata_desc = &metadata_desc_list[i];
        if ((metadata_desc->len <= 0) ||
            (remain_size < metadata_desc->len)) {
            ret = -EFTYPE;
            pr_err("invalid metadata desc or insufficient buffer: metadata_desc->len %u, remain_size %llu\n", 
                metadata_desc->len, remain_size);
            break;
        }

        switch (metadata_desc->id) {
        case METADATA_SHA256_HASH:
            metadata->hash_info = (const struct sha256_hash_info *)pos;
            break;
        case METADATA_DESCRIPTION:
            metadata->description = pos;
            metadata->description_len = metadata_desc->len;
            break;
        default:
            pr_warn("ignore unsupported metadata id %d\n", metadata_desc->id);
            break;
        }

        pos += metadata_desc->len;
        remain_size -= metadata_desc->len;
    }

    metadata->end = pos;

    return ret;
}

static int __request_firmware_xz(
    struct firmware *fw, u8 *buf, u64 buf_size, const u8 *name,
    validate_firmware_metata_routine validate_metadata, void *validate_ctx)
{
    const u8 *pos = buf, *data = NULL;
    u64 remain_size = buf_size;
    struct qcwlan_xzfw_hdr *xzfw_hdr = NULL;

    const struct metadata_desc *metadata_desc_list = NULL;
    static const struct metadata_desc local_metadata_descs[] = {
        { .id = METADATA_SHA256_HASH, .len = sizeof(struct sha256_hash_info) },
    };
    u16 n_metadata_desc = 0;
    struct firmware_metadata metadata = { 0 };

    int ret;

    do {
        /* read the header */
        if (remain_size < sizeof(*xzfw_hdr)) {
            ret = -EFTYPE;
            break;
        }
        xzfw_hdr = (void *)pos;
        pos += sizeof(*xzfw_hdr);
        remain_size -= sizeof(*xzfw_hdr);

        /* validate the header */
        if (memcmp(xzfw_hdr->magic, MAGIC_QCWLAN_XZFW_V2, sizeof(MAGIC_QCWLAN_XZFW_V2)) == 0) {
            if (xzfw_hdr->n_metadata_desc) {
                if (remain_size < sizeof(struct metadata_desc) * xzfw_hdr->n_metadata_desc) {
                    ret = -EFTYPE;
                    pr_err("Invalid QCLWAN_XZFW_V2 format\n");
                    break;
                }
                metadata_desc_list = (const struct metadata_desc *)pos;
                n_metadata_desc = xzfw_hdr->n_metadata_desc;

                pos += n_metadata_desc * sizeof(struct metadata_desc);
                remain_size -= n_metadata_desc * sizeof(struct metadata_desc);
            }
            /* for backward compatibility */
            else {
                metadata_desc_list = local_metadata_descs;
                n_metadata_desc = ARRAY_LENGTH(local_metadata_descs);
            }

            pr_debug("found firmware %a with QCLWAN_XZFW_V2 format\n", xzfw_hdr->name);
        }
#if SUPPORT_QCWLAN_XZFW_V1
        else if (memcmp(xzfw_hdr->magic, MAGIC_QCWLAN_XZFW_V1, sizeof(MAGIC_QCWLAN_XZFW_V1)) == 0) {
            pr_debug("found firmware %a with QCLWAN_XZFW_V1 format\n", xzfw_hdr->name);
        }
#endif
        else {
            ret = -EFTYPE;
            pr_err("Unsupported firmware format\n");
            break;
        }

        /* parse the metadata */
        if (n_metadata_desc > 0) {
            ret = __parse_firmware_metadata(metadata_desc_list, n_metadata_desc, pos, remain_size, &metadata);
            if (ret)
                break;
            pos = metadata.end;
            remain_size -= (metadata.end - metadata.begin);
        }

        /* cache the data position */
        if (remain_size < xzfw_hdr->compressed_size) {
            ret = -EFTYPE;
            pr_err("invalid firmware data\n");
            break;
        }
        data = pos;
        pos += xzfw_hdr->compressed_size;
        remain_size -= xzfw_hdr->compressed_size;

        /* validate the name */
        if (strcmp((const char*)xzfw_hdr->name, (const char*)name) != 0) {
            continue;
        }

        /* validate the medata */
        if (n_metadata_desc) {
            if (!metadata.hash_info) {
                ret = -EFTYPE;
                pr_err("hash is required for QCLWAN_XZFW_V2 firmware\n");
                break;
            }
            if (validate_metadata && validate_metadata(name, &metadata, validate_ctx)) {
               continue;
            }
        }

        ret = __uncompress_firmware_xz(fw, data, 
            xzfw_hdr->compressed_size, xzfw_hdr->uncompressed_size);
        if (ret)
            break;
        
#if SUPPORT_QCWLAN_XZFW_HASH_VERIFICATION
        if (metadata.hash_info) {
            ret = __validate_firmware_hash(fw, metadata.hash_info);
        }
#endif

        break;

    } while (1);

    return ret;
}

static int request_firmware_xzbin(struct firmware *fw, const u8 *name,
    validate_firmware_metata_routine validate_metadata, void *validate_ctx)
{
    u8 *buf = NULL;
    u64 buf_size = 0;
    int ret;

    /* get xzbin from cache firstly */
    if (__g_amss_all_cache.data) {
        buf = __g_amss_all_cache.data;
        buf_size = __g_amss_all_cache.size;
    }
    else {
        ret = fread(AMSS_ALL_BIN_FILE, &buf, &buf_size);
        if (ret)
            return ret;

        __g_amss_all_cache.data = buf;
        __g_amss_all_cache.size = buf_size;
		__g_amss_all_cache.read_from_partition = false;
    }

    return __request_firmware_xz(fw, buf, buf_size, name, validate_metadata, validate_ctx);
}

static int request_firmware_raw(struct firmware *fw, const u16 *name)
{
    u8 *buf = NULL;
    u64 buf_size = 0;
    int ret;

    ret = fread(name, &buf, &buf_size);
    if (ret)
        return ret;

    fw->data = buf;
    fw->size = (u32)buf_size;

    return 0;
}

static int request_firmware_fv(struct firmware *fw, const u8 *name,
    validate_firmware_metata_routine validate_metadata, void *validate_ctx)
{
    u8 *buf;
    u64 buf_size;
    int ret;

    /* get xz buffer from cache firstly */
    if (__g_amss_all_cache.data) {
        buf = __g_amss_all_cache.data;
        buf_size = __g_amss_all_cache.size;
    }
    else {
        ret = fvread_section(&gEfiQcWlanXzfw1Guid, &buf, &buf_size);
        if (ret)
            return ret;

        __g_amss_all_cache.data = buf;
        __g_amss_all_cache.size = buf_size;
    }

    return __request_firmware_xz(fw, buf, buf_size, name, validate_metadata, validate_ctx);
}

static int fv_read_next_partition(struct partition_info *pi, void *data, u64 *size)
{
    int ret = 0;

    do {
        if (pi->next >= ARRAY_LENGTH(pi->list)) {
            ret = -ENOENT;
            break;
        }

        ret = fv_read_from_partition(pi->list[pi->next++], NULL, data, size, 0);
		
		/* success and break */
        if (!ret)
            break;

		/* if read partition-A error, will save the error code and report to upper layer */
		if (ret && pi->next < ARRAY_LENGTH(pi->list)) {
			pi->last_error = ret;
		}

        /* fail and continue */
        pr_err("failed to read partition %d: %d\n", pi->next - 1, ret);
    } while (1);

    return ret;
}

static int request_firmware_partition(struct firmware *fw, const u8 *name,
    validate_firmware_metata_routine validate_metadata, void *validate_ctx)
{
    u8 *buf;
    u64 buf_size;
    int ret;

    do {
        /* get xz buffer from cache firstly */
        if (__g_amss_all_cache.data) {
            buf = __g_amss_all_cache.data;
            buf_size = __g_amss_all_cache.size;
        }
        else {
            ret = fv_read_next_partition(&__g_amss_all_cache.pi, &buf, &buf_size);
            if (ret)
                break;

            __g_amss_all_cache.read_from_partition = true;
            __g_amss_all_cache.data = buf;
            __g_amss_all_cache.size = buf_size;
        }

        ret = __request_firmware_xz(fw, buf, buf_size, name, validate_metadata, validate_ctx);
        if (!ret)
            break;

        /* fail and continue */
        free_firmware_cache();
    } while (1);

    return ret;
}

int request_firmware_fancily(
    struct firmware *fw, const u16 *name, 
    validate_firmware_metata_routine validate_metadata, void *validate_ctx)
{
    u8 xzname[32] = { 0 };
    int ret;

    ret = strncpy_s_c((char *)xzname, sizeof(xzname), name);
    if (ret)
        return ret;

#if SUPPORT_QCWLAN_FW_XZ
    pr_debug("get firmware %a from xz compressed file\n", xzname);
    ret = request_firmware_xzbin(fw, xzname, validate_metadata, validate_ctx);
    if (!ret) {
        pr_debug("request firmare success\n");
        return 0;
    }
#endif /* !SUPPORT_QCWLAN_FW_XZ */

#if SUPPORT_QCWLAN_FW_RAW
    pr_debug("get firmware %a from original elf file\n", xzname);
    ret = request_firmware_raw(fw, name);
    if (!ret) {
        pr_debug("request firmare success\n");
        return 0;
    }
#endif /* !SUPPORT_QCWLAN_FW_RAW */

#if SUPPORT_QCWLAN_FW_FV
    pr_debug("get firmware %a from all firmware volumes\n", name);
    ret = request_firmware_fv(fw, xzname, validate_metadata, validate_ctx);
    if (!ret) {
        pr_debug("request firmare success\n");
        return 0;
    }
#endif /* !SUPPORT_QCWLAN_FW_FV */

#if SUPPORT_QCWLAN_FW_PART
		pr_debug("get firmware %a from all firmware partition\n", name);
		ret = request_firmware_partition(fw, xzname, validate_metadata, validate_ctx);
		if (!ret) {
			pr_debug("request firmare success\n");
			return 0;
		}
#endif


    pr_err("request firmare %a failed: %d\n", xzname, ret);
    return ret;
}

void release_firmware(struct firmware *fw)
{
    FreePool(fw->data);
    fw->data = NULL;
    fw->size = 0;
}

void free_firmware_cache(void)
{
    if (__g_amss_all_cache.data) {
		if (__g_amss_all_cache.read_from_partition)
			gBS->FreePages((EFI_PHYSICAL_ADDRESS)__g_amss_all_cache.data, EFI_SIZE_TO_PAGES(__g_amss_all_cache.size));
		else
            FreePool(__g_amss_all_cache.data);
		
        __g_amss_all_cache.data = NULL;
        __g_amss_all_cache.size = 0;

        pr_debug("cached amss all data freed\n");
    }
}

typedef enum
{
  BOOT_RECOVERY_ERROR_NONE,
  BOOT_RECOVERY_SMEM_UNINITIALIZED_VARIABLE,
  BOOT_RECOVERY_SMEM_BUFFER_SIZE_TOO_SMALL
}boot_recovery_status;

#if SUPPORT_RECOVERY_FROM_PARTITION
extern 
boot_recovery_status boot_recovery_add_recovery_info(u8 *partition_id, u8 *recovery_partition_id, u64 last_reported_errorcode, u32 flags);

void
add_firmware_recovery_info()
{
	boot_recovery_status status;
    struct partition_info *pi = &__g_amss_all_cache.pi;

    if (__g_amss_all_cache.data && 
        (pi->next == ARRAY_LENGTH(pi->list))) {
        pr_err("++update bad and good partition to SMEM\n");
        status = boot_recovery_add_recovery_info(
						(u8 *)(pi->list[0]), 		/*Original Bad partition */
						(u8 *)(pi->list[1]),		/*Backup, Good partition*/
						pi->last_error,				/*Load fail from Partition-A */
						1);							/*Partition-A corrupted*/
		if (status != BOOT_RECOVERY_ERROR_NONE ) {
			pr_err("++ Good & Corrupted partition update to SMEM failed\n");
		}
    }
}
#endif

void flush_firmware_cache(void)
{
#if SUPPORT_RECOVERY_FROM_PARTITION
	add_firmware_recovery_info();
#endif

    free_firmware_cache();
}
