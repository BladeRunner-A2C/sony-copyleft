#ifndef SCM_QSEE_INTERFACE_H
#define SCM_QSEE_INTERFACE_H

/**
   @file scm_qsee_interface.h
   @brief Provide the SYSCALL API infrastructure
*/

/*===========================================================================
   Copyright (c) 2014 - 2018, 2020, 2023 Qualcomm Technologies, Inc.
   All rights reserved.
   Confidential and Proprietary - Qualcomm Technologies, Inc.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE


when       who      what, where, why
--------   ---      -------------------------------------------------------
02/07/23   shl      use UINTN to merge 32 and 64 data type
02/05/23   ojasvi   Changed to include correct header(32/ 64) based on ARMV7_32/ ARMV8_32 flag.
10/26/20   shl      Changed to 64 bit to align with TZ syscall structures
05/03/18   pranavj  Ported SHMBridge changes to Poipu
09/04/14   sm       Initial version.

===========================================================================*/

/** Maximum character string for applications */

#define QSEE_MAX_NAME_SIZE         32
#define VM_PERM_X 0x1
#define VM_PERM_W 0x2
#define VM_PERM_R 0x4

#define __attribute__(x)
#pragma pack(push, 1)
typedef struct qsee_app_start_req_s
{
  UINTN mdt_len;                    /**< Combined length of the ELF
                                          and all program headers. */
  UINTN img_len;                    /**< Combined length of all the
                                          loadable segments. */
  UINTN pa;                         /**< PA points to the region
                                          where the application and
                                          the headers are located as
                                          described in Elf32_Ehdr and
                                          Elf32_Phdr. */
  char   app_name[QSEE_MAX_NAME_SIZE]; 
                                     /**< Name of the application. */
} __attribute__ ((packed)) qsee_app_start_req_t;

typedef struct qsee_app_shutdown_req_s
{
  UINT32                     app_id;      /**< Application shutdown-specific
                                               request. */
} __attribute__ ((packed)) qsee_app_shutdown_req_t;

typedef struct qsee_app_lookup_req_s
{
  char                       app_name[QSEE_MAX_NAME_SIZE];
                                           /**< Application
                                                lookup-specific
                                                request. */
} __attribute__ ((packed)) qsee_app_lookup_req_t;

typedef struct qsee_apps_region_notificaton_s
{

  UINTN  applications_region_addr;
  UINTN  applications_region_size; 
} __attribute__ ((packed)) qsee_apps_region_notification_t;

typedef struct qsee_register_log_buffer_s
{

  UINTN  log_buffer_addr;
  UINTN  log_buffer_size; 
} __attribute__ ((packed)) qsee_register_log_buffer_t;

typedef struct qsee_load_serv_image_s
{

  UINTN  mdt_len;
  UINTN  img_len;
  UINTN  pa;
} __attribute__ ((packed)) qsee_load_serv_image_t;

typedef struct qsee_provision_rpmb_key_req_s
{
  UINT32 key_type;
} __attribute__ ((packed)) qsee_provision_rpmb_key_req_t;

#pragma pack(pop)
#endif
