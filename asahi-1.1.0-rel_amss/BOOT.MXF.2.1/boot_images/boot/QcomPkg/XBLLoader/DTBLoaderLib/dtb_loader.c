/**
 * @file dtb_loader.c
 * @brief
 * Source file for XBL loading of DTB files.
 *
 * Copyright 2022-2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc
 *
 */

/*==========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who        what, where, why
--------   ---        ---------------------------------------------------------
09/20/23   tmt        Add support for dtb_test_framework
08/21/23   rama       DTBO buffer overflow check
01/13/23   tmt        CR-3307011 security fixes
12/29/22   sym        use single large buffer to do overlay merge 
10/18/22   tmt        Address security review: fdt_set_blob_handle()
05/04/22   tmt        Initial creation of file, pulling common code out of sbl1_config.c

===========================================================================*/

/*==========================================================================
                             INCLUDE FILES
===========================================================================*/
#include <stdio.h>
#include <limits.h>
#include <boot_error_if.h>
#include <boot_logger.h>
#include <boot_framework.h>
#include <boot_config_context.h>
#include <boot_chipinfo_if.h>
#include <boot_platforminfo_if.h>
#include <cfg_item_config.h>
#include "DTBExtnLib.h"

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

/* These names need to agree with create_xbl_config.json */
#define S_DTB_NAME "pre-ddr"    // S_ short for SRAM
#define D_DTB_NAME "post-ddr"            // D_ short for DRAM

#define Log_BUF_SIZE 80

extern void dtb_test_framework(boot_handle config_context_handle);
typedef enum
{
  DTB_LOADER_PRE_DDR,         /* Pre-DDR load request */
  DTB_LOADER_POST_DDR,        /* Post-DDR load request */
  DTB_LOADER_MAX
} dtb_load_request;

/*==========================================================================
        Function to load DTB from XblConfig
===========================================================================*/
static bl_error_boot_type boot_dtb_load(boot_handle config_context_handle, dtb_load_request pre_or_post)
{

  // DTBExtnLib overhead
  int retValue = 0;
  const void *fdt_handle = NULL;

  // System overhead
  config_status_type cfg_return;
  bl_error_boot_type status = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_if = NULL;

  // chipinfo data collection
  ChipInfoIdType cID = 0;
  ChipInfoVersionType cVersion = 0;
  ChipInfoFamilyType cFamily = 0;
  uint16 ci_version = 0;
  uint64 chipinfo=0LL;
  boot_chipinfo_if_type *chipinfo_if = NULL;

  // platforminfo data collection
  DalPlatformInfoPlatformType pType = 0;
  uint32 pSubtype = 0;
  uint32 pVersion = 0;
  uint32 pOEMVariant = 0;
  uint16 pi_version = 0;
  uint64 platforminfo=0LL;
  boot_platforminfo_if_type *platforminfo_if = NULL;

  // DTBO API parameters
  char *name_starts_with = S_DTB_NAME;
  char *oname_starts_with = S_DTB_NAME;
  cfg_dtbo_state_type state = CFG_GET_INITIALIZED; /* client provides state var to DTBO */
  const void *primary_blob = NULL,      /* DTB, base of merge */
  *dtb_blob = NULL;          /* Always points to current, useable DTB */
  void *overlay_blob = NULL;      /* Overlay DTB, new overlay to merge into base */

  /*Declare Structure and Variable*/
  typedef struct dtb_loader_handle
  {
      uint32 x_handle;        /* XBLConfig Handle */
      uint32 x_size;          /* Size of data referenced by handle */
  }dtb_loader_handle;

  dtb_loader_handle dtb_handle = {0, 0};
  dtb_loader_handle dtbo_handle[ CFG_GET_MAX_DTBO ] = {0};
  volatile uint8_t dtbo_found_count = 0;
  size_t total_blob_size = 0;
  uint32_t largest_overlay_size = 0;

  // Error Message Buffer
  char log_buf[Log_BUF_SIZE];

  do
  {
    /* Acquire Memory Interface */
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (BL_ERR_NONE != status)
      break;
    if (NULL == mem_if)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* Acquire ChipInfo Interface */
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_CHIPINFO_INTERFACE, (void **)&chipinfo_if);
    if (BL_ERR_NONE != status)
      break;
    if (NULL == chipinfo_if)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CHIPINFO_IF, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    /* Acqure ChipInfo Data */
    status = chipinfo_if->get_chipinfo_data(&cID, &cVersion, &cFamily);
    if (BL_ERR_NONE == status)
    {
      ci_version = cVersion >> 16;
      ci_version = (ci_version<<8)|(cVersion & 0x00FF);
      cfg_return = cfg_item_config_create_chipinfo((uint16)cFamily, (uint16)cID, ci_version, &chipinfo);
      if (CONFIG_SUCCESS != cfg_return)
      {
        snprintf(log_buf, Log_BUF_SIZE, "cfg_chipinfo.err[%x]", cfg_return);
        boot_log_message(log_buf);
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_CHIPINFO_FAIL);
        break;
      }
    }
    else
      break;

    if (DTB_LOADER_POST_DDR == pre_or_post)
    {
      /* Acqure PlatformInfo Interface */
      status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_PLATFORMINFO_INTERFACE, (void **)&platforminfo_if);
      if (status != BL_ERR_NONE)
        break;
      if (NULL == platforminfo_if)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_PLATFORMINFO, BL_ERR_INTERFACE_FAILURE);
        break;
      }

      /* Acqure PlatformInfo Data */
      status = platforminfo_if->get_platforminfo_data(&pType, &pSubtype, &pVersion, &pOEMVariant);
      if (BL_ERR_NONE == status)
      {
        pi_version = pVersion >> 16;
        pi_version = (pi_version<<8)|(pVersion & 0x00FF);
        cfg_return = cfg_item_config_create_platforminfo((uint8)pType, pi_version, (uint8)pSubtype, (uint8)pOEMVariant, &platforminfo);
        if (CONFIG_SUCCESS != cfg_return)
        {
          snprintf(log_buf, Log_BUF_SIZE, "cfg_platinfo.err[%x]", cfg_return);
          boot_log_message(log_buf);
          status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_PLATFORMINFO_FAIL);
          break;
        }
      }
      else
        break;

      /* Adjust name_starts_with parameter */
      name_starts_with = D_DTB_NAME;
      oname_starts_with = D_DTB_NAME;
    }

    /* Preliminaries are out of the way */
    /* Step 1: find chip family dtb */

    cfg_return = cfg_item_config_open_first_dtb(chipinfo, platforminfo, name_starts_with, &(dtb_handle.x_handle), &(dtb_handle.x_size));

    if (CONFIG_SUCCESS != cfg_return)
    {
      snprintf(log_buf, Log_BUF_SIZE, "cfg_item_config_open_first_dtb[%s] returned[%x]", name_starts_with, cfg_return);
      boot_log_message(log_buf);
      status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, CONFIG_CHIPFAMILY_DTB_NOTFOUND);
      break;
    }

    total_blob_size = dtb_handle.x_size;

    /*Look for all available overlay blob*/
    for ( ; ; )
    {
        /* avoid buffer overflow if there are more than CFG_GET_MAX_DTBO number of DTBOs*/
        if(dtbo_found_count >= CFG_GET_MAX_DTBO)
        {
          break;
        }
        cfg_return = cfg_item_config_open_next_dtbo(chipinfo, platforminfo, oname_starts_with,  &(dtbo_handle[dtbo_found_count].x_handle), &(dtbo_handle[dtbo_found_count].x_size), &state);
        if (CONFIG_SUCCESS != cfg_return)
        {
          if (CONFIG_DTBO_NOTFOUND == cfg_return)
          {
              break;          /* we are done, no more overlay files */
          }
          else
          {
            snprintf(log_buf, Log_BUF_SIZE, "DTBO: %s* dtbo can't be found[%x]!", oname_starts_with, cfg_return);
            boot_log_message(log_buf);
            status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, cfg_return);
            goto err_exit;
          }
        }

        if (total_blob_size > UINT_MAX - dtbo_handle[dtbo_found_count].x_size)
        {
            status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_IMG_SIZE_TOO_BIG);
            goto err_exit;
        }
        else
        {
            largest_overlay_size = ((largest_overlay_size > dtbo_handle[dtbo_found_count].x_size) ? largest_overlay_size : dtbo_handle[dtbo_found_count].x_size) ;
            total_blob_size += dtbo_handle[dtbo_found_count].x_size ;
            dtbo_found_count++;
        }

    }

    /* Allocate a buffer of total length*/
    status = mem_if->malloc(total_blob_size, (void **)&dtb_blob);
    if (BL_ERR_NONE != status)
    {
     cfg_item_config_close(dtb_handle.x_handle);
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, status);
      goto err_exit;
    }

    /* Read First DTB into local buffer */
    cfg_return = cfg_item_config_read(dtb_handle.x_handle, 0, dtb_handle.x_size, (void *)dtb_blob);
    cfg_item_config_close(dtb_handle.x_handle);
    if (CONFIG_SUCCESS != cfg_return)
    {
      status = mem_if->free((void *)dtb_blob);
      if (BL_ERR_NONE != status)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
        goto err_exit;
      }
      dtb_blob = NULL;
      status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_XCFG_READ_FAIL);
      goto err_exit;
    }

    /* Restrict entry into for loop when there is no DTBO found. */
    if( 0 < dtbo_found_count)
    {

        /* Allocate a Buffer of largest size of all overlay DTBO */
        status = mem_if->malloc(largest_overlay_size, &overlay_blob);
        if (BL_ERR_NONE != status)
        {
            /*Closing all the DTBO handle before exiting */
            for( int index = 0; index < dtbo_found_count; index++ )
            {
                cfg_item_config_close(dtbo_handle[index].x_handle);
            }
            status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, status);
            goto err_exit;
      }

      /* Read DTBO into local buffer */

        /* Setup Overlay/Merge Operation */
        primary_blob = dtb_blob;        /* primary_blob = current base blob */
        dtb_blob = NULL;     /* buffers are handed off, NULL for correct error handling */

        /* Match available dtbo files: SoC and then Platform */
        for( int index = 0; index < dtbo_found_count; index++ )
        {

          /* Read DTBO into local buffer */
          cfg_return = cfg_item_config_read(dtbo_handle[index].x_handle, 0, dtbo_handle[index].x_size, overlay_blob);
          cfg_item_config_close(dtbo_handle[index].x_handle);
          if (CONFIG_SUCCESS != cfg_return)
          {
            status = mem_if->free(overlay_blob);
            if (BL_ERR_NONE != status)
            {
             status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
             goto err_exit;
            }
            overlay_blob = NULL;
            status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_XCFG_READ_FAIL);
            goto err_exit;
          }

          /* Perform Overlay/Merge Operation */
          retValue = fdt_merge_overlay(primary_blob, total_blob_size, overlay_blob, largest_overlay_size, (void *)primary_blob, total_blob_size);
          if (0 != retValue)
          {
            snprintf(log_buf, Log_BUF_SIZE, "fdt merge overlay failed:returned [%d]", retValue);
            boot_log_message(log_buf);
            status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, CONFIG_DTBO_MERGE_FAILED);
            goto err_exit;
          }

        }
        /* Cleanup after Overlay/Merge, prep for next iteration */
        dtb_blob = primary_blob;
        primary_blob = NULL;
        status = mem_if->free(overlay_blob);
        if (BL_ERR_NONE != status)
        {
            status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
            goto err_exit;
        }
        overlay_blob = NULL;
    }

    /* We should have a valid DTB to register with library */
    /* If DEFAULT DTB buffer valid, must free it first */
    retValue = fdt_get_blob_handle(&fdt_handle, DEFAULT_BLOB_ID);
    if (0 == retValue)
    {
      if (NULL != fdt_handle)
      {
        status = mem_if->free((void *)fdt_handle);
        if (BL_ERR_NONE != status)
        {
          status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
          goto err_exit;
        }
      }
      fdt_handle = NULL;
    }

    /* Register new DTB with library */
    retValue = fdt_set_blob_handle(dtb_blob, total_blob_size, DEFAULT_BLOB_ID);
    if (0 != retValue)
    {
      snprintf(log_buf, Log_BUF_SIZE, "fdt_set_blob_handle got an error [%d]", retValue);
      boot_log_message(log_buf);
      status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_FDT_SET_BLOB_FAIL);
      goto err_exit;
    }

    /* skip error checks on good exit */
    status = BL_ERR_NONE;
    break;

err_exit:
    /* Prevent memory leaks: dtb_blob, primary_blob, merge_blob, overlay_blob */
    if (NULL != dtb_blob)
    {
      if (mem_if->free((void *)dtb_blob)!= BL_ERR_NONE)
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
    }
    if (NULL != primary_blob)
    {
      if (mem_if->free((void *)primary_blob)!= BL_ERR_NONE)
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
    }
    if (NULL != overlay_blob)
    {
      if (mem_if->free(overlay_blob)!= BL_ERR_NONE)
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_MEMORY_FREE_FAIL);
    }
  } while (FALSE);

  snprintf(log_buf, Log_BUF_SIZE, "DTB %s Found: [%s][%llx][%llx]", (status ? "Not" : ""), name_starts_with, chipinfo, platforminfo);
  boot_log_message(log_buf);

  if (DTB_LOADER_POST_DDR == pre_or_post) {
    dtb_test_framework(config_context_handle);
  }
  return status;
}

bl_error_boot_type boot_pre_ddr_dtb_load(boot_handle config_context_handle)
{
  return boot_dtb_load(config_context_handle, DTB_LOADER_PRE_DDR);
}

bl_error_boot_type boot_post_ddr_dtb_load(boot_handle config_context_handle)
{
  return boot_dtb_load(config_context_handle, DTB_LOADER_POST_DDR);
}
