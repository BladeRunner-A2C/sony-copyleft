/** @file DTBExtnLib_node.c
  FdtLib (edk2) Extended APIs

  Copyright (c) 2021-2023 Qualcomm Technologies, Inc. All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc
 
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/21/23   tmt     EDK2 Patch: only include "libfdt.h"
 07/25/23   sym     Zero out the buffer after any error
 01/13/23   tmt     CR-3307011 security fixes
 11/14/22   sym     Add success(No Error) Macro
 09/09/22   sym     Aligned function's parameters to that of called fdtlib functions
 8/17/22    sym     Add new format type i|I in fdt_get_prop_values_of_node
 7/20/22    sym     Include the fdt_get_blob_handle API feature here to make that API optional or obsolete
 10/12/21   tmt     Add cache API and support for uint16 type in get_prop_values_of_node API
 09/28/21   tmt     Remove name from node_handle
 06/25/21   tmt     Update fdt_node_cmp to ignore name field
 04/22/21   tmt     New APIs: fdt_node_copy, fdt_node_cmp
 03/24/21   tmt     Update parameter type for qdsp6 compatibility
 02/17/21   tmt     Error checking clean-up, ensure when error detected API returns
 01/07/21   tmt     All node APIs in this file

=============================================================================*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/

#include <stdint.h>

#include "libfdt.h"

#include "DTBExtnLib.h"
#include "DTBInternals.h"
#include "DTBExtnLib_env.h"

/*=========================================================================
     Default Defines
==========================================================================*/

/*=========================================================================
     Local Static Variables
==========================================================================*/

/*=========================================================================
     Globals
==========================================================================*/

/*=========================================================================
      Public APIs
==========================================================================*/

/**
 * fdt_get_node_handle - return node_handle
 * @node: pointer to fdt_node_handle object
 * @blob: pointer to the device tree blob
 * @name: pointer to node name (string)
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 * 
 * FdtLib calls:
 *   int fdt_path_offset(const void *fdt, const char *path);
 */
int fdt_get_node_handle(fdt_node_handle *node, const void *blob, char *name)
{
	int offset;						/* FdtLib: return offset value */
	int ret_value = FDT_ERR_QC_NOERROR;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(name);

	/* Include the fdt_get_blob_handle API feature here to make that API optional or obsolete*/
	if(NULL == blob) {
		ret_value = fdt_get_blob_handle(&blob, DEFAULT_BLOB_ID);
		if(ret_value != FDT_ERR_QC_NOERROR) {
			return ret_value;
		}
	}
	node->blob = blob;

	offset = fdt_path_offset(node->blob, name);
	if (offset >= 0)
		node->offset = offset;
	else {
		if (dtb_config.verbose) {
			SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "BAD offset[%d]", offset);
			PUTS(ibuffer);
		}
		ret_value = offset;
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%s][%d]", __func__, ret_value, name, node->offset);
		PUTS(ibuffer);
	}
	
	return ret_value;
}

/**
 * fdt_get_phandle_node - return phandle fdt_node_handle
 * @node: pointer to fdt_node_handle object
 * @phandle: phandle reference in blob
 * @pnode: pointer to fdt_node_handle for new phandle node
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 * 
 * FdtLib calls:
 *   int fdt_node_offset_by_phandle(const void *fdt, uint32_t phandle);
 */
int fdt_get_phandle_node(fdt_node_handle *node, uint32_t phandle, fdt_node_handle *pnode)
{
	int offset;						/* FdtLib: return offset value */
	int ret_value = FDT_ERR_QC_NOERROR;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(pnode);

	offset = fdt_node_offset_by_phandle(node->blob, phandle);
	if (offset < 0) {
		if (dtb_config.verbose) {
			SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "BAD phandle[%d]", offset);
			PUTS(ibuffer);
		}
		ret_value = offset;
	} else {
		pnode->offset = offset;
		pnode->blob = node->blob;
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%d]", __func__, ret_value, phandle);
		PUTS(ibuffer);
	}

	return ret_value;
}

/**
 * fdt_get_parent_node - return parent node fdt_node_handle
 * @node: pointer to fdt_node_handle object
 * @pnode: pointer to fdt_node_handle for new parent node
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 * 
 * FdtLib calls:
 *   int fdt_parent_offset(const void *fdt, int nodeoffset);
 */
int fdt_get_parent_node(fdt_node_handle *node, fdt_node_handle *pnode)
{
	int offset;						/* FdtLib: return offset value */
	int ret_value = FDT_ERR_QC_NOERROR;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(pnode);

	offset = fdt_parent_offset(node->blob, node->offset);
	if (offset < 0) {
		if (dtb_config.verbose) {
			SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "BAD parent[%d]", offset);
			PUTS(ibuffer);
		}
		pnode->blob = NULL;
		pnode->offset = offset;
		ret_value = offset;
	} else {
		pnode->offset = offset;
		pnode->blob = node->blob;
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%d]", __func__, ret_value, offset);
		PUTS(ibuffer);
	}

	return ret_value;
}

/**
 * fdt_node_cmp - compare 2 fdt_node_handle_objects
 * @node_a: pointer to fdt_node_handle object A
 * @node_b: pointer to fdt_node_handle object B
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 */
int fdt_node_cmp(fdt_node_handle *node_a, fdt_node_handle *node_b)
{
	int ret_value = FDT_ERR_QC_NOERROR;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node_a);
	PTR_CHECK(node_b);

	if (!((node_a->blob == node_b->blob) && (node_a->offset == node_b->offset))) {
		ret_value = -FDT_ERR_QC_NODE_DIFFERENT;

		if (dtb_config.verbose) {
			SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "nodes are different[%p].[%p]", node_a, node_b);
			PUTS(ibuffer);
		}
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%p].[%p]", __func__, ret_value, node_a, node_b);
		PUTS(ibuffer);
	}

	return ret_value;
}

/**
 * fdt_node_copy - copy fdt_node_handle_object
 * @dst: pointer to destination fdt_node_handle object
 * @src: pointer to source fdt_node_handle object
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 */
int fdt_node_copy(fdt_node_handle *dst, fdt_node_handle *src)
{
	int ret_value = FDT_ERR_QC_NOERROR;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(dst);
	PTR_CHECK(src);
	
	dst->blob = src->blob;
	dst->offset = src->offset;

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%p].[%p]", __func__, ret_value, dst, src);
		PUTS(ibuffer);
	}

	return ret_value;
}

/**
 * fdt_get_prop_values_size_of_node - return required buffer size to hold all properties of node
 * @node: pointer to fdt_node_handle object
 * @size: pointer to uint32 to hold buffer size (in bytes)
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 * 
 * FdtLib calls:
 *   macro: fdt_for_each_property_offset(int, const void *, int)
 *   const void *fdt_getprop_by_offset(const void *fdt, int offset, const char **namep, int *lenp);
 */
int fdt_get_prop_values_size_of_node(fdt_node_handle *node, uint32_t *size)
{
	int property;						/* FdtLib: property iterator */
	int len;							/* FdtLib: return errors & size */
	const char *pname;					/* FdtLib: return name */
	const struct fdt_property *fdtp;	/* FdtLib: return raw prop data */
	int ret_value = FDT_ERR_QC_NOERROR;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(size);

	*size = 0;

	fdt_for_each_property_offset(property, node->blob, node->offset) {
		fdtp = fdt_getprop_by_offset(node->blob, property, &pname, &len);
		if ((NULL == fdtp) || (len < 0)) {
			if (dtb_config.verbose) {
				SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Err[%d].Prop[%s]", len, pname);
				PUTS(ibuffer);
			}
			LEN_ERROR_CHECK(len);
			break;
		} else {
			if (dtb_config.trace) {
				SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s] has size [%d]", pname, len);
				PUTS(ibuffer);
			}
			*size += len;
		}
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%d]", __func__, ret_value, (fdt32_t)*size);
		PUTS(ibuffer);
	}

	return ret_value;
}

/**
 * fdt_get_prop_values_of_node - return packed buffer of all properties of node
 * @node: pointer to fdt_node_handle object
 * @format: required for endianess, [b|B] = string/byte,
 *                                  [h|H] = half-word (16),
 *                                  [w|W] = word (32),
 *                                  [d|D] = double-word (64)
 *									[i|I] = ignore the property
 * @packed_prop_values: buffer pointer to hold packed node properties
 * @size: buffer size (in bytes)
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 * 
 * FdtLib calls:
 *   macro: fdt_for_each_property_offset(int, const void *, int)
 *   const void *fdt_getprop_by_offset(const void *fdt, int offset, const char **namep, int *lenp);
 *   const void *fdt_getprop(const void *fdt, int nodeoffset, const char *name, int *lenp);
 *   static inline uint32_t fdt32_to_cpu(fdt32_t x)
 *   static inline uint64_t fdt64_to_cpu(fdt64_t x)
 * NOTE: Must refer header info availble in DTBExtnLib.h for this API
 */

int fdt_get_prop_values_of_node(fdt_node_handle *node, char *format, void *packed_prop_values, uint32_t size)
{
	int property;						/* FdtLib: property iterator */
	int len;							/* FdtLib: return errors & size */
	const char *pname;					/* FdtLib: return name */
	const struct fdt_property *fdtp;	/* FdtLib: return raw prop data */
	int ret_value = FDT_ERR_QC_NOERROR;

	uint32_t i=0, j;					/* indexes & loop counters */
	uint32_t count = 0;					/* running count of copied data */
	char *dwalk;						/* walking pointer in destination buffer */
	const void *swalk;					/* source buffer (set for each property) */
	uint8_t  *d8,  *s8;					/* used for uint8_t  copies */
	uint16_t *d16, *s16;				/* used for uint16_t copies */
	uint32_t *d32, *s32;				/* used for uint32_t copies */
	uint64_t *d64, *s64;				/* used for uint64_t copies */

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(format);
	PTR_CHECK(packed_prop_values);
	dwalk = packed_prop_values;			/* init destination buffer ptr */

	fdt_for_each_property_offset(property, node->blob, node->offset) {
		/*Ignore the propert*/
		if( 'i' == format[i] || 'I' == format[i] ) {
			/*Increase the format[ ] index count by 1 and skip the extraction of that property.*/
			i++;
			continue;

		} else {
			/* step 1: get name of property, used by step 2 */
			fdtp = fdt_getprop_by_offset(node->blob, property, &pname, &len);
			if ((NULL == fdtp) || (len <= 0)) {
				if (dtb_config.verbose) {
					SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Err[%d].Index[%d]", len, i);
					PUTS(ibuffer);
				}
				LEN_ERROR_CHECK(len);
				goto exit;
			} else {
				/* step 2: get actual property */
				/* This step is required because fdt_getprop_by_offset() doesn't appear to work as documented */
				/* This is easy to see by printing out the fdt_property structure returned */
				/* The property name is always correct and so can be used in this call to get actual data */
				swalk = fdt_getprop(node->blob, node->offset, pname, &len);
				if ((NULL == swalk) || (len < 0)) {
					if (dtb_config.verbose) {
						SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "src[%p] is NULL or Error[%d]", swalk, len);
						PUTS(ibuffer);
					}
					LEN_ERROR_CHECK(len);
					goto exit;
				} else if (0 == len) {
					/* property has empty value so nothing to copy */
					/* normally this isn't an error, but this API has to error at this point */
					/* client is expecting a value in a packed struct and there is no value */
					if (dtb_config.verbose) {
						ret_value = -FDT_ERR_QC_NILVALUE;
						SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Property[%s] has no value in DTB[%d]", pname, ret_value);
						PUTS(ibuffer);
						goto exit;
					}
				} else {
					/* property has value to copy to destination */
					if (count >= size) {
						/* count of data items copied so far has filled buffer */
						ret_value = -FDT_ERR_QC_TRUNCATED;
						goto exit;
					}
					if (len > (size-count)) {
						/* size of new data to copy will overflow buffer */
						ret_value = -FDT_ERR_QC_OVERFLOW;
						goto exit;
					}
					switch (format[i]) {
						case 'b':
						case 'B':
							/* byte format for this property (8-bit) */
							d8 = (uint8_t *)dwalk;
							s8 = (uint8_t *)swalk;
							for (j=0; j<len; j++)
								d8[j] = s8[j];
							break;

						case 'h':
						case 'H':
							/* half-word format for this property (16-bit) */
							d16 = (uint16_t *)dwalk;
							s16 = (uint16_t *)swalk;
							for (j=0; j<len/2; j++)
								d16[j] = fdt16_to_cpu(s16[j]);
							break;

						case 'w':
						case 'W':
							/* word format for this property (32-bit) */
							d32 = (uint32_t *)dwalk;
							s32 = (uint32_t *)swalk;
							for (j=0; j<len/4; j++)
								d32[j] = fdt32_to_cpu(s32[j]);
							break;

						case 'd':
						case 'D':
							/* double-word format for this property (64-bit) */
							d64 = (uint64_t *)dwalk;
							s64 = (uint64_t *)swalk;
							for (j=0; j<len/8; j++)
								d64[j] = fdt64_to_cpu(s64[j]);
							break;

						default:
							if (dtb_config.verbose) {
								SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%d] BAD format [%c]", i, format[i]);
								PUTS(ibuffer);
							}
							ret_value = -FDT_ERR_QC_BADFORMAT;
							goto exit;
					}
					count += len;		/* update running total of copied data */
					dwalk += len;		/* update destination walking pointer */
				}
				i++;	/* increment format[] index */
			}
		}
	}

exit:
	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%s]", __func__, ret_value, format);
		PUTS(ibuffer);
	}
	if(ret_value && (size > 0))
	{
		memset(packed_prop_values, 0, size);
	}
	return ret_value;
}

/**
 * fdt_get_prop_names_size_of_node - return required buffer size to hold all property names in node
 * @node: pointer to fdt_node_handle object
 * @size: pointer to uint32 to hold buffer size (in bytes)
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 * 
 * FdtLib calls:
 *   macro: fdt_for_each_property_offset(int, const void *, int)
 *   const void *fdt_getprop_by_offset(const void *fdt, int offset, const char **namep, int *lenp);
 */
int fdt_get_prop_names_size_of_node(fdt_node_handle *node, uint32_t *size)
{
	int property;						/* FdtLib: property iterator */
	int len;							/* FdtLib: return errors & size */
	const char *pname;					/* FdtLib: return name */
	const struct fdt_property *fdtp;	/* FdtLib: return raw prop data */
	int ret_value = FDT_ERR_QC_NOERROR;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(size);

	*size = 0;

	fdt_for_each_property_offset(property, node->blob, node->offset) {
		fdtp = fdt_getprop_by_offset(node->blob, property, &pname, &len);
		if ((NULL == fdtp) || (len < 0)) {
			if (dtb_config.verbose) {
				SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Err[%d].Prop[%s]", len, pname);
				PUTS(ibuffer);
			}
			LEN_ERROR_CHECK(len);
			break;
		} else
			*size += strlen(pname)+1;
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%d]", __func__, ret_value, (fdt32_t)*size);
		PUTS(ibuffer);
	}

	return ret_value;
}

/**
 * fdt_get_prop_names_of_node - return buffer of all property names in node
 * @node: pointer to fdt_node_handle object
 * @prop_names: buffer pointer to hold all property names
 * @size: pointer to uint32 to hold buffer size (in bytes)
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 * 
 * FdtLib calls:
 *   macro: fdt_for_each_property_offset(int, const void *, int)
 *   const void *fdt_getprop_by_offset(const void *fdt, int offset, const char **namep, int *lenp);
 */
int fdt_get_prop_names_of_node(fdt_node_handle *node, char *prop_names, uint32_t size)
{
	int property;						/* FdtLib: property iterator */
	int len;							/* FdtLib: return errors & size */
	const char *pname;					/* FdtLib: return name */
	const struct fdt_property *fdtp;	/* FdtLib: return raw prop data */
	int ret_value = FDT_ERR_QC_NOERROR;
	
	int tlen, running_count = 0;
	char *walk = prop_names;
	uint16_t i;			/* index into names[] KW doesn't like 32-bits */

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(prop_names);

	fdt_for_each_property_offset(property, node->blob, node->offset) {
		fdtp = fdt_getprop_by_offset(node->blob, property, &pname, &len);
		if ((NULL == fdtp) || (len < 0)) {
			if (dtb_config.verbose) {
				SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "Err[%d].Prop[%s]", len, pname);
				PUTS(ibuffer);
			}
			LEN_ERROR_CHECK(len);
			break;
		} else {
			len = strlen(pname);
			if (len < INT_MAX)
				tlen = len + 1;	/* include '\0' on end */
			else {
				ret_value = -FDT_ERR_QC_OVERFLOW;
				break;
			}
			if (tlen <= (size-running_count)) {
				for (i=0; i<tlen; i++)
					walk[i] = pname[i];
				walk += tlen;
				running_count += tlen;
			} else {
				ret_value = FDT_ERR_QC_TRUNCATED;
				break;
			}
		}
	}
	if ((FDT_ERR_QC_NOERROR == ret_value) && (size > 0))
		prop_names[size-1] = '\0';		/* ensure buffer is null-terminated */

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%d]", __func__, ret_value, (fdt32_t)size);
		PUTS(ibuffer);
	}

	return ret_value;
}

/**
 * fdt_get_count_of_subnodes - return count of all subnodes of node
 * @node: pointer to fdt_node_handle object
 * @count: pointer to uint32 to hold count of subnodes
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 * 
 * FdtLib calls:
 *   macro: fdt_for_each_subnode(int, const void *, int)
 */
int fdt_get_count_of_subnodes(fdt_node_handle *node, uint32_t *count)
{
	int subnode;				/* FdtLib: subnode iterator */

	uint32_t i = 0;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(count);

	fdt_for_each_subnode(subnode, node->blob, node->offset) {
		i++;
	}
	*count = i;

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%d].[%d]",
			__func__, 0, node->offset, (fdt32_t)*count);
		PUTS(ibuffer);
	}

	return FDT_ERR_QC_NOERROR;
}

/**
 * fdt_get_cache_of_subnodes - return cache of all subnodes of node
 * @node: pointer to fdt_node_handle object
 * @cache: pointer to fdt_node_handle array of size @count
 * @count: uint32 to hold count of subnodes
 * 
 * Performance Impact: This API is added specifically to address a
 *                     known performance issue.  When a node has sub-nodes
 *                     this API returns an array of fdt_node_handles
 *                     with the DTB offset for each sub-node, so no string
 *                     lookup of the sub-node is required.
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 * 
 * FdtLib calls:
 *   macro: fdt_for_each_subnode(int, const void *, int)
 */
int fdt_get_cache_of_subnodes(fdt_node_handle *node, fdt_node_handle *cache, uint32_t count)
{
	int subnode;				/* FdtLib: subnode iterator */

	uint32_t i = 0;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(cache);

	fdt_for_each_subnode(subnode, node->blob, node->offset) {
		cache[i].blob = node->blob;
		cache[i].offset = subnode;
		i++;
		if (i >= count)
			break;
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%d].[%d]",
			__func__, 0, node->offset, (fdt32_t)count);
		PUTS(ibuffer);
	}

	return FDT_ERR_QC_NOERROR;
}

/**
 * fdt_get_size_of_subnode_names - return size of subnode names
 * @node: pointer to fdt_node_handle object
 * @names: pointer to uint32_t array to hold sizes
 * @count: uint32 to hold count of array items
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 * 
 * FdtLib calls:
 *   macro: fdt_for_each_subnode(int, const void *, int)
 *   const char *fdt_get_name(const void *fdt, int nodeoffset, int *lenp);
 */
int fdt_get_size_of_subnode_names(fdt_node_handle *node, uint32_t *names, uint32_t count)
{
	int subnode;				/* FdtLib: subnode iterator */
	int len;					/* FdtLib: return errors & size */
	int ret_value = FDT_ERR_QC_NOERROR;

	uint16_t i = 0;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(names);

	if (count == 0) {
		ret_value = -FDT_ERR_QC_NILVALUE;
	} else {
		fdt_for_each_subnode(subnode, node->blob, node->offset) {
			(void)fdt_get_name(node->blob, subnode, &len);
			if (len >= 0) {
				names[i] = len + 1;	/* name + '\0' */
			} else {
				LEN_ERROR_CHECK(len);
				break;
			}
			if (i++ >= count) {
				ret_value = FDT_ERR_QC_TRUNCATED;
				break;
			}
		}
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%d].[%d]",
			__func__, ret_value, node->offset, (fdt32_t)count);
		PUTS(ibuffer);
	}

	return ret_value;
}


/**
 * fdt_get_subnode_names - return buffer of all subnode names
 * @node: pointer to fdt_node_handle object
 * @prop_names: buffer pointer to hold all subnode names
 * @size: pointer to uint32 to hold buffer size (in bytes)
 *
 * returns: FDT_ERR_QC_NOERROR (success) else error indicator
 * 
 * FdtLib calls:
 *   macro: fdt_for_each_subnode(int, const void *, int)
 *   const char *fdt_get_name(const void *fdt, int nodeoffset, int *lenp);
 */
int fdt_get_subnode_names(fdt_node_handle *node, void *names, uint32_t size)
{
	int subnode;				/* FdtLib: subnode iterator */
	int len;					/* FdtLib: return errors & size */
	const char *name;			/* FdtLib: return raw prop data */
	int ret_value = FDT_ERR_QC_NOERROR;

	uint16_t i;
	int tlen;
	int running_count = 0;
	char *walk = (char *)names;

	#ifdef INSTRUMENTATION
	char ibuffer[DTB_LINE_BUF_SIZE];
	#endif

	PTR_CHECK(node);
	PTR_CHECK(names);

	running_count = 0;
	fdt_for_each_subnode(subnode, node->blob, node->offset) {
		name = fdt_get_name(node->blob, subnode, &len);
		if ((NULL == name) || (len < 0)) {
			LEN_ERROR_CHECK(len);
			break;
		}

		if (len < INT_MAX)
			tlen = len + 1;	/* include '\0' on end */
		else {
			ret_value = -FDT_ERR_QC_OVERFLOW;
			break;
		}

		if (tlen <= (size-running_count)) {
			for (i=0; i<tlen; i++)
				walk[i] = name[i];
			running_count += tlen;
			walk += tlen;
		} else {
			ret_value = -FDT_ERR_QC_BUF2SMALL;
			break;
		}
	}

	if (dtb_config.trace) {
		SNPRINTF(ibuffer, DTB_LINE_BUF_SIZE, "[%s][%d].[%d]",
			__func__, ret_value, (fdt32_t)size);
		PUTS(ibuffer);
	}

	return ret_value;
}
