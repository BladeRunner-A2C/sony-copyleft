/**
 * @file dtb_test_create_dtb.c
 * @brief
 * DTB Tests: Read/Write DTB on-the-fly
 *
 * Copyright 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc
 *
 */

/*==========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who        what, where, why
--------   ---        ---------------------------------------------------------
09/19/23   tmt        Initial creation of file

===========================================================================*/

/*==========================================================================
                             INCLUDE FILES
===========================================================================*/


#include <stdio.h>

#include "boot_config_context.h"
#include "boot_logger.h"

#include "DTBExtnLib.h"
/* Until these APIs are "published" must access private library header */
#include "../../Library/DTBExtnLib/create-dtb-apis.h"


/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

// buffer used for printing
#define BUF_SIZE 0x100
static char buffer[BUF_SIZE];

// Max size of DTB created in WriteDTBOnTheFly
#define DTB_SIZE 4096
static char dbuf[DTB_SIZE];

/*===============================================
        Function to write DTB on the fly
=================================================*/
void WriteDTBOnTheFly(boot_handle config_context_handle)
{
	bl_error_boot_type ret_value = BL_ERR_NONE;		// Contains return value of used functions
	fdt_node_handle node;							// Contains current node
	int offset;										// Contains offset of current node children
	int len;										// Contains length of property to write

	boot_log_message("start WriteDTBOnTheFly\n");
	node.blob = dbuf;
	node.offset = -1;

	// Add empty tree to node blob
	ret_value = fdt_add_tree(&node, DTB_SIZE);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_tree [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	// Add node to empty tree + recording offset
	ret_value = fdt_add_node(&node, "level1", &offset);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_node(level1) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}
	node.offset = offset;

	// Adding properties to current node (level1)
	len = 1;
	uint8_t u8 = 8;
	uint16_t u16 = 16;
	uint32_t u32 = 32;
	uint64_t u64 = 64;
	char *s = "str";

	ret_value = fdt_add_prop_list_u8(&node, "U8", &u8, len);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_prop_list_u8(U8) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	ret_value = fdt_add_prop_list_u16(&node, "U16", &u16, len);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_prop_list_u16(U16) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	ret_value = fdt_add_prop_list_u32(&node, "U32", &u32, len);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_prop_list_u32(U32) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	ret_value = fdt_add_prop_list_u64(&node, "U64", &u64, len);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_prop_list_u64(U64) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	ret_value = fdt_add_prop_list_string(&node, "String", s, 4);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_prop_list_string(str) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	// Establishing property values for level2
	len = 8;
	uint8_t u8_arr[] = {0, 1, 2, 3, 4, 5, 6, 7};
	uint16_t u16_arr[] = {10, 11, 12, 13, 14, 15, 16, 17};
	uint32_t u32_arr[] = {110, 111, 112, 113, 114, 115, 116, 117};
	uint64_t u64_arr[] = {1110, 1111, 1112, 1113, 1114, 1115, 1116, 1117};
	char s_arr[] = { 'a', 'b', 'c', '\0', 'd', 'e', 'f', '\0', 'g', 'h', 'i', '\0' };

	// Add subnode to current node in tree (level1) + recording offset
	ret_value = fdt_add_node(&node, "level2", &offset);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_node(level2) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}
	node.offset = offset;

	// Adding properties to current node (level2)
	ret_value = fdt_add_prop_list_u8(&node, "U8-list", u8_arr, len);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_prop_list_u8(U8-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	ret_value = fdt_add_prop_list_u16(&node, "U16-list", u16_arr, len);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_prop_list_u16(U16-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	ret_value = fdt_add_prop_list_u32(&node, "U32-list", u32_arr, len);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_prop_list_u32(U32-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	ret_value = fdt_add_prop_list_u64(&node, "U64-list", u64_arr, len);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_prop_list_u64(U64-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	ret_value = fdt_add_prop_list_string(&node, "String-list", s_arr, 12);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_prop_list_string(s_arr) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	// SET DTB HANDLE
	ret_value = fdt_set_blob_handle((void *)node.blob, DTB_SIZE, 1);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_add_prop_list_string(s_arr) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

err_exit:
	return;
}

/*===============================================
        Function to read DTB on the fly
=================================================*/

void ReadDTBOnTheFly(boot_handle config_context_handle)
{
  
	bl_error_boot_type bl_ret_value = BL_ERR_NONE;	// Contains return value of used funtions
	int ret_value;									// DTB return values
	fdt_node_handle node;							// Contains current node
	const void *blob = NULL;						// Contains node blob

	void *ptr;										// Stores value of string and list properties
	uint32_t size;	

	// Contain respective property values
	uint8_t val8, *u8_list = NULL;
	uint16_t val16, *u16_list = NULL;
	uint32_t val32, *u32_list = NULL;
	uint64_t val64, *u64_list = NULL;
	char l1s[4];
	char *string_list = NULL;

	// Variables for malloc
	boot_memory_mgr_if_type *mem_if = NULL;

	// Get pointer for malloc + error checking
	bl_ret_value = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
	if (BL_ERR_NONE != bl_ret_value) {
		snprintf(buffer, BUF_SIZE, "boot_config_context_get_ptr(MEMORY_MGR_INTERFACE) [%d]\n", bl_ret_value);
		boot_log_message(buffer);
		ret_value = bl_ret_value;
		goto err_exit;
	}

	if (NULL == mem_if) {
		boot_log_message("mem_if == NULL\n");
		bl_ret_value = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
		ret_value = bl_ret_value;
		goto err_exit;
	}

	boot_log_message("start ReadDTBOnTheFly\n");

	// GET DTB HANDLE
	ret_value = fdt_get_blob_handle(&blob, 1);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_blob_handle(1) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	// READ DTB
	ret_value = fdt_get_node_handle(&node, blob, "/level1");
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_node_handle(/level1) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	ret_value = fdt_get_uint8_prop(&node, "U8", &val8);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_uint8_prop(U8) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	} else {
		snprintf(buffer, BUF_SIZE, "U8[%hhd]\n", val8);
		boot_log_message(buffer);
	}

	ret_value = fdt_get_uint16_prop(&node, "U16", &val16);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_uint16_prop(U16) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	} else {
		snprintf(buffer, BUF_SIZE, "U16[%hd]\n", val16);
		boot_log_message(buffer);
	}

	ret_value = fdt_get_uint32_prop(&node, "U32", &val32);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_uint32_prop(U32) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	} else {
		snprintf(buffer, BUF_SIZE, "U32[%hd]\n", val32);
		boot_log_message(buffer);
	}

	ret_value = fdt_get_uint64_prop(&node, "U64", &val64);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_uint64_prop(U64) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	} else {
		snprintf(buffer, BUF_SIZE, "U64[%hd]\n", val64);
		boot_log_message(buffer);
	}

	ret_value = fdt_get_prop_size(&node, "String", &size);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_prop_size(String) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	ret_value = fdt_get_string_prop_list(&node, "String", l1s, size);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_string_prop_list(String) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	} else {
		snprintf(buffer, BUF_SIZE, "String[%s]\n", (char *)l1s);
		boot_log_message(buffer);
	}

	// GET DTB HANDLE
	ret_value = fdt_get_node_handle(&node, blob, "/level1/level2");
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_node_handle(/level1/level2) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	/* Read U8-list */
	ret_value = fdt_get_prop_size(&node, "U8-list", &size);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_prop_size(U8-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	bl_ret_value = mem_if->malloc(size, (void **)&ptr);
	if (BL_ERR_NONE != ret_value) {
		snprintf(buffer, BUF_SIZE, "malloc(U8-list) [%d]\n", bl_ret_value);
		boot_log_message(buffer);
		ret_value = bl_ret_value;
		goto err_exit;
	} else {
		u8_list = (uint8_t *)ptr;
	}

	ret_value = fdt_get_uint8_prop_list(&node, "U8-list", u8_list, size);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_uint8_prop_list(U8-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	} else {
		snprintf(buffer, BUF_SIZE, "U8-list[%hhd]..[%hhd]..[%hhd]..[%hhd]..[%hhd]..[%hhd]..[%hhd]..[%hhd]\n",
			u8_list[0], u8_list[1], u8_list[2], u8_list[3], u8_list[4], u8_list[5], u8_list[6], u8_list[7]);
		boot_log_message(buffer);
	}

	/* Read U16-list */
	ret_value = fdt_get_prop_size(&node, "U16-list", &size);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_prop_size(U16-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	bl_ret_value = mem_if->malloc(size, (void **)&ptr);
	if (BL_ERR_NONE != ret_value) {
		snprintf(buffer, BUF_SIZE, "malloc(U8-list) [%d]\n", bl_ret_value);
		boot_log_message(buffer);
		ret_value = bl_ret_value;
		goto err_exit;
	} else {
		u16_list = (uint16_t *)ptr;
	}

	ret_value = fdt_get_uint16_prop_list(&node, "U16-list", u16_list, size);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_uint_prop_list(U16-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	} else {
		snprintf(buffer, BUF_SIZE, "U16-list[%hd]..[%hd]..[%hd]..[%hd]..[%hd]..[%hd]..[%hd]..[%hd]\n",
			u16_list[0], u16_list[1], u16_list[2], u16_list[3], u16_list[4], u16_list[5], u16_list[6], u16_list[7]);
		boot_log_message(buffer);
	}

	/* Read U32-list */
	ret_value = fdt_get_prop_size(&node, "U32-list", &size);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_prop_size(U32-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	bl_ret_value = mem_if->malloc(size, (void **)&ptr);
	if (BL_ERR_NONE != ret_value) {
		snprintf(buffer, BUF_SIZE, "malloc(U32-list) [%d]\n", bl_ret_value);
		boot_log_message(buffer);
		ret_value = bl_ret_value;
		goto err_exit;
	} else {
		u32_list = (uint32_t *)ptr;
	}

	ret_value = fdt_get_uint32_prop_list(&node, "U32-list", u32_list, size);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_uint32_prop_list(U32-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	} else {
		snprintf(buffer, BUF_SIZE, "U32-list[%d]..[%d]..[%d]..[%d]..[%d]..[%d]..[%d]..[%d]\n",
			u32_list[0], u32_list[1], u32_list[2], u32_list[3], u32_list[4], u32_list[5], u32_list[6], u32_list[7]);
		boot_log_message(buffer);
	}

	/* Read U64-list */
	ret_value = fdt_get_prop_size(&node, "U64-list", &size);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_prop_size(U64-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	bl_ret_value = mem_if->malloc(size, (void **)&ptr);
	if (BL_ERR_NONE != ret_value) {
		snprintf(buffer, BUF_SIZE, "malloc(U64-list) [%d]\n", bl_ret_value);
		boot_log_message(buffer);
		ret_value = bl_ret_value;
		goto err_exit;
	} else {
		u64_list = (uint64_t *)ptr;
	}

	ret_value = fdt_get_uint64_prop_list(&node, "U64-list", u64_list, size);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_uint64_prop_list(U64-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	} else {
		snprintf(buffer, BUF_SIZE, "U64-list[%d]..[%d]..[%d]..[%d]..[%d]..[%d]..[%d]..[%d]\n",
			u64_list[0], u64_list[1], u64_list[2], u64_list[3], u64_list[4], u64_list[5], u64_list[6], u64_list[7]);
		boot_log_message(buffer);
	}

	/* Read String-list */
	ret_value = fdt_get_prop_size(&node, "String-list", &size);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_prop_size(String-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	}

	bl_ret_value = mem_if->malloc(size, (void **)&ptr);
	if (BL_ERR_NONE != ret_value) {
		snprintf(buffer, BUF_SIZE, "malloc(String-list) [%d]\n", bl_ret_value);
		boot_log_message(buffer);
		ret_value = bl_ret_value;
		goto err_exit;
	} else {
		string_list = (char *)ptr;
	}

	ret_value = fdt_get_string_prop_list(&node, "String-list", string_list, size);
	if (ret_value) {
		snprintf(buffer, BUF_SIZE, "fdt_get_string_prop_list(String-list) [%d]\n", ret_value);
		boot_log_message(buffer);
		goto err_exit;
	} else {
		snprintf(buffer, BUF_SIZE, "String-list[%c%c%c]..[%c%c%c]..[%c%c%c]\n", 
			string_list[0], string_list[1], string_list[2],
			string_list[4], string_list[5], string_list[6],
			string_list[8], string_list[9], string_list[10]);
		boot_log_message(buffer);
	}

err_exit:
	if (u8_list) ret_value = mem_if->free((void *)u8_list);
	if (u16_list) ret_value = mem_if->free((void *)u16_list);
	if (u32_list) ret_value = mem_if->free((void *)u32_list);
	if (u64_list) ret_value = mem_if->free((void *)u64_list);
	if (string_list) ret_value = mem_if->free((void *)string_list);

}

