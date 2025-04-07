#ifndef BOOT_PARTITION_H
#define BOOT_PARTITION_H


/*=============================================================================
                     Boot Partition

GENERAL DESCRIPTION
  This file contains the implementation for the boot-specific partition 
  creation information.

Copyright 2022 - 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================
                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
05/05/23   ds           Pakala SOCCP loading changes
04/15/23   digants      Added SOCCP IDs
03/31/23   sp           Added UEFI_RECOVERY_PARTITION_GUID
03/23/23   suhas        Added entry for DDR_DEBUG_PARTITION
03/03/23   ng           Added entry for ABL_SW and updated Kernel partition
03/03/23   ng           Added entry for DMA_GSIFW
03/02/23   yps          Added CDT partition ID
01/26/23   suhas        Updated GUIDs and interface for BootPartitionLib
12/12/22   suhas        Initial revision.
=============================================================================*/


#include "boot_error_if.h"
#include "boot_media_types.h"


/*=============================================================================
LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.
=============================================================================*/
#define BL_ERR_BOOT_PARTITION_MEDIA_FAMILY_NOT_FOUND       (BL_ERR_CUSTOM_ERRORS_START + 0)
#define BL_ERR_BOOT_PARTITION_IMAGE_SET_NOT_ENABLED        (BL_ERR_CUSTOM_ERRORS_START + 1)
#define BL_ERR_BOOT_PARTITION_PARTITION_ENTRY_NOT_ENABLED  (BL_ERR_CUSTOM_ERRORS_START + 2)
#define BL_ERR_BOOT_PARTITION_MEMSCPY_ERROR                (BL_ERR_CUSTOM_ERRORS_START + 3)

#define PARTITION_ID_MAX_LENGTH 16

/* Defining Sahara IDs for Flashless devices */
#define ACDB_PARTITION_SAHARAID                    {ACDB_IMG}                                                                                    // ACDB_PARTITION
#define AOP_PARTITION_SAHARAID                     {AOP_IMG}                                                                                     // AOP_PARTITION
#define AOP_CONFIG_PARTITION_SAHARAID              {AOP_CONFIG_IMG}                                                                              // AOP_CONFIG_PARTITION
#define APDP_PARTITION_SAHARAID                    {APDP_IMG}                                                                                    // APDP_PARTITION
#define CPUCP_DTB_PARTITION_SAHARAID               {CPUCP_DTB_IMG}                                                                               // CPUCP_DTB_PARTITION
#define CPUCPFW_PARTITION_SAHARAID                 {CPUCPFW_IMG}                                                                                 // CPUCPFW_PARTITION
#define DDR_TRAINING_PARTITION_SAHARAID            {TRDATA_IMG}                                                                                  // DDR_TRAINING_PARTITION
#define EFS1_PARTITION_SAHARAID                    {RAMFS1_IMG}                                                                                  // EFS1_PARTITION
#define EFS2_PARTITION_SAHARAID                    {RAMFS2_IMG}                                                                                  // EFS2_PARTITION
#define EFS3_PARTITION_SAHARAID                    {BACKUP_RAMFS_IMG}                                                                            // EFS3_PARTITION
#define MISC_OEM_PARTITION_SAHARAID                {OEM_MISC_IMG}                                                                                // MISC_OEM_PARTITION
#define MISC_QTI_PARTITION_SAHARAID                {QTI_MISC_IMG}                                                                                // MISC_QTI_PARTITION
#define Q6_MPSS_PARTITION_SAHARAID                 {DSP1_IMG}                                                                                    // Q6_MPSS_PARTITION
#define Q6_MPSS_DTB_CONFIG_PARTITION_SAHARAID      {DSP1_DTB_IMG}                                                                                // Q6_MPSS_DTB_CONFIG_PARTITION
#define QHEE_PARTITION_SAHARAID                    {QHEE_IMG}                                                                                    // QHEE_PARTITION
#define QSEE_PARTITION_SAHARAID                    {QSEE_IMG}                                                                                    // QSEE_PARTITION
#define QSEE_DEVCFG_PARTITION_SAHARAID             {QSEE_DEVCFG_IMG}                                                                             // QSEE_DEVCFG_PARTITION
#define QUANTUM_PARTITION_SAHARAID                 {QUANTUM_IMG}                                                                                 // QUANTUM_PARTITION
#define QUEST_PARTITION_SAHARAID                   {QUEST_IMG}                                                                                   // QUEST_PARTITION
#define QUPFW_PARTITION_SAHARAID                   {QUP_FW_IMG}                                                                                  // QUPFW_PARTITION
#define SEC_PARTITION_SAHARAID                     {SEC_IMG}                                                                                     // SEC_PARTITION
#define SHRM_PARTITION_SAHARAID                    {SHRM_IMG}                                                                                    // SHRM_PARTITION
#define TN_PARTITION_SAHARAID                      {APPS_IMG}                                                                                    // TN_PARTITION
#define TZ_PARTITION_SAHARAID                      {TZ_IMG}                                                                                      // TZ_PARTITION
#define TOOLS_PARTITION_SAHARAID                   {TOOLS_IMG}                                                                                   // TOOLS_PARTITION
#define UEFI_PARTITION_SAHARAID                    {APPSBL_IMG}                                                                                  // UEFI_PARTITION
#define XBL_CONFIG_PARTITION_SAHARAID              {XBL_CONFIG_IMG}                                                                              // XBL_CONFIG_PARTITION
#define XBL_RAMDUMP_PARTITION_SAHARAID             {XBL_RAMDUMP_IMG}                                                                             // XBL_RAMDUMP_PARTITION
#define DMA_GSIFW_PARTITION_SAHARAID               {DMA_GSIFW_IMG}                                                                               // DMA_GSIFW_PARTITION
#define ABL_SW_PARTITION_SAHARAID                  {ABL_IMG}                                                                                     // ABL_SW_PARTITION
#define KERNEL_PARTITION_SAHARAID                  {HLOS_IMG}                                                                                    // KERNEL_PARTITION

/* Defining GUIDs for Blockdev devices */
#define ACDB_PARTITION_GUID                    {0x88, 0x24, 0xF8, 0x66, 0xB6, 0x7D, 0xAA, 0x4D, 0xBF, 0x6F, 0xAF, 0xB0, 0x85, 0x6A, 0x78, 0x58}  // ACDB_PARTITION
#define AOP_PARTITION_GUID                     {0xA5, 0x90, 0x9E, 0xD6, 0xAB, 0x4C, 0x71, 0x00, 0xF6, 0xDF, 0xAB, 0x97, 0x7F, 0x14, 0x1A, 0x7F}  // AOP_PARTITION
#define AOP_CONFIG_PARTITION_GUID              {0x34, 0xF2, 0x12, 0x3D, 0x82, 0xC8, 0x46, 0x4B, 0xA2, 0x0C, 0x17, 0xD5, 0x2C, 0x8F, 0xC0, 0x3D}  // AOP_CONFIG_PARTITION
#define APDP_PARTITION_GUID                    {0xA2, 0x8D, 0xE9, 0xE6, 0x2A, 0xE2, 0x12, 0x4D, 0xAB, 0x33, 0x16, 0x9E, 0x7D, 0xEA, 0xA5, 0x07}  // APDP_PARTITION
#define CDT_PARTITION_GUID                     {0X5f, 0x20, 0x9F, 0xA1, 0xD8, 0xCC, 0x6D, 0x4B, 0x8F, 0x1E, 0x2D, 0x9B, 0xC2, 0x4C, 0xFF, 0xB1} // CDT_PARTITION
#define CPUCP_DTB_PARTITION_GUID               {0xBC, 0x18, 0x60, 0x6C, 0xBE, 0x4F, 0xC5, 0x40, 0xB1, 0x48, 0x4B, 0xCB, 0x1D, 0xB2, 0x37, 0x48}  // CPUCP_DTB_PARTITION
#define CPUCPFW_PARTITION_GUID                 {0xBD, 0x15, 0x86, 0x1E, 0x8C, 0x6D, 0xAD, 0x41, 0xB3, 0xEA, 0x50, 0xE8, 0xBF, 0x40, 0xE4, 0x3F}  // CPUCPFW_PARTITION
#define DDR_TRAINING_PARTITION_GUID            {0x9C, 0xC1, 0xA0, 0x20, 0x6A, 0x28, 0xFA, 0x42, 0x9C, 0xE7, 0xF6, 0x4C, 0x32, 0x26, 0xA7, 0x94}  // DDR_TRAINING_PARTITION
#define DDR_DEBUG_PARTITION_GUID               {0x5E, 0x20, 0x58, 0x2D, 0x35, 0xBA, 0xF9, 0x4B, 0xB6, 0xC1, 0xC6, 0xFD, 0xC8, 0x0A, 0x37, 0x3B}  // DDR_DEBUG_PARTITION
#define IPA_PARTITION_GUID                     {0xA3, 0xC9, 0x6C, 0xDA, 0x29, 0x5A, 0xC6, 0x4D, 0xA0, 0xC2, 0x27, 0x3B, 0x5D, 0x66, 0x5D, 0x29}  // IPA_PARTITION
#define MISC_OEM_PARTITION_GUID                {0x36, 0xA4, 0x26, 0xE1, 0x7E, 0x75, 0xD0, 0x42, 0x8D, 0x19, 0x0F, 0x36, 0x2F, 0x7A, 0x62, 0xB8}  // MISC_OEM_PARTITION
#define MISC_QTI_PARTITION_GUID                {0x05, 0x6F, 0x6C, 0x84, 0x46, 0xEB, 0x0A, 0x4C, 0xA1, 0xA3, 0x36, 0x48, 0xEF, 0x3F, 0x9D, 0x0E}  // MISC_QTI_PARTITION
#define QHEE_PARTITION_GUID                    {0x89, 0xA6, 0xA6, 0xE1, 0x8D, 0x0C, 0xC6, 0x4C, 0xB4, 0xE8, 0x55, 0xA4, 0x32, 0x0F, 0xBD, 0x8A}  // QHEE_PARTITION
#define QSEE_PARTITION_GUID                    {0x7F, 0xAA, 0x53, 0xA0, 0xB8, 0x40, 0x1C, 0x4B, 0xBA, 0x08, 0x2F, 0x68, 0xAC, 0x71, 0xA4, 0xF4}  // QSEE_PARTITION
#define QSEE_DEVCFG_PARTITION_GUID             {0x16, 0x4B, 0x5D, 0xF6, 0x3D, 0x34, 0x25, 0x4E, 0xAA, 0xFC, 0xBE, 0x99, 0xB6, 0x55, 0x6A, 0x6D}  // QSEE_DEVCFG_PARTITION
#define SEC_PARTITION_GUID                     {0xEF, 0xC7, 0xCF, 0x76, 0x9D, 0x03, 0x2C, 0x4E, 0xB8, 0x1E, 0x4D, 0xD8, 0xC2, 0xCB, 0x2A, 0x93}  // SEC_PARTITION
#define SHRM_PARTITION_GUID                    {0x22, 0xCA, 0x74, 0xCB, 0x0D, 0x2F, 0x82, 0x4B, 0xA1, 0xD6, 0xC4, 0x21, 0x3F, 0x34, 0x8D, 0x73}  // SHRM_PARTITION
#define UEFI_PARTITION_GUID                    {0xCD, 0xFD, 0x0F, 0x40, 0xE0, 0x22, 0xE7, 0x47, 0x9A, 0x23, 0xF1, 0x6E, 0xD9, 0x38, 0x23, 0x88}  // UEFI_PARTITION
#define XBL_CONFIG_PARTITION_GUID              {0xE4, 0x5A, 0x32, 0x5A, 0x76, 0x42, 0x6D, 0xB6, 0x0A, 0xDD, 0x34, 0x94, 0xDF, 0x27, 0x70, 0x6A}  // XBL_CONFIG_PARTITION
#define XBL_RAMDUMP_PARTITION_GUID             {0x97, 0xF1, 0x82, 0x03, 0x1F, 0xE4, 0x84, 0x4E, 0xB1, 0x8B, 0x0B, 0x56, 0x4A, 0xEA, 0xD8, 0x75}  // XBL_RAMDUMP_PARTITION
#define SBL1_PARTITION_GUID                    {0x2C, 0xBA, 0xA0, 0xDE, 0xDD, 0xCB, 0x05, 0x48, 0xB4, 0xF9, 0xF4, 0x28, 0x25, 0x1C, 0x3E, 0x98}  // SBL1_PARTITION
#define XBL_LOGS_PARTITION_GUID                {0x66, 0xCB, 0xEE, 0xF7, 0x1A, 0x78, 0x9A, 0x43, 0x89, 0x55, 0x70, 0xE1, 0x2E, 0xD4, 0xA7, 0xA0}  // XBL_LOGS_PARTITION
#define XBL_TEST_MODE_PARTITION_GUID           {0xB9, 0xD2, 0xFD, 0x91, 0xD3, 0x8E, 0x76, 0x41, 0xBC, 0x42, 0x26, 0x0F, 0x2E, 0x34, 0xD0, 0x4A}  // XBL_TEST_MODE_PARTITION
#define RAM_DUMP_PARTITION_GUID                {0x23, 0xB3, 0xC9, 0x66, 0xFC, 0xF7, 0xB6, 0x48, 0xBF, 0x96, 0x6F, 0x32, 0xE3, 0x35, 0xA4, 0x28}  // RAM_DUMP_PARTITION
#define SD_DUMP_PARTITION_GUID                 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // SD_DUMP_PARTITION
#define NVME_DUMP_PARTITION_GUID               {0x28, 0x73, 0x2A, 0xC1, 0x1F, 0xF8, 0xD2, 0x11, 0xBA, 0x4B, 0x00, 0xA0, 0xC9, 0x3E, 0xC9, 0x3B}  // NVME_DUMP_PARTITION
#define SMSS_PARTITION_GUID                    {0xD2, 0x6D, 0x2E, 0xDF, 0x6D, 0x29, 0xAA, 0x4C, 0x86, 0x7B, 0x2E, 0x92, 0xE2, 0xF9, 0xB6, 0xC3}  // SMSS_PARTITION
#define SOCCP_PARTITION_GUID                   {0x79, 0x99, 0xBA, 0xF4, 0x9E, 0x18, 0x40, 0x73, 0x98, 0x7B, 0x2A, 0xC6, 0x61, 0x35, 0x3F, 0x9F}  // SOCCP_PARTITION
#define SOCCP_DEBUG_PARTITION_GUID             {0x95, 0x82, 0x5E, 0xE7, 0x01, 0xDD, 0x4A, 0x7C, 0xA9, 0xEE, 0x8C, 0x37, 0xB9, 0x97, 0xFE, 0xC4}  // SOCCP_DEBUG_PARTITION
#define SOCCP_DCD_PARTITION_GUID               {0xD6, 0x7C, 0xC9, 0x1F, 0xB8, 0x8A, 0x43, 0xFA, 0x9B, 0x3A, 0x12, 0xEF, 0x5A, 0x18, 0x92, 0xDC}  // SOCCP_DCD_PARTITION
#define XBL_CONFIG_RECOVERY_PARTITION_GUID     {0xEA, 0xE0, 0x62, 0xF4, 0x0E, 0xA2, 0x10, 0x4B, 0x86, 0x7A, 0x2D, 0x44, 0x55, 0x36, 0x65, 0x48}  // XBL_CONFIG_RECOVERY_PARTITION
#define APPSBL_PARTITION_GUID                  {0xCD, 0xFD, 0x0F, 0x40, 0xE0, 0x22, 0xE7, 0x47, 0x9A, 0x23, 0xF1, 0x6E, 0xD9, 0x38, 0x23, 0x88}  // APPSBL_PARTIITON
#define SBL1_RECOVERY_PARTITION_GUID           {0xA3, 0xF1, 0x3D, 0x7A, 0x1A, 0xA3, 0x4D, 0x45, 0xBD, 0x78, 0xDF, 0x25, 0x9E, 0xD4, 0x86, 0xBE}  // SBL1_RECOVERY_PARTITION
#define QSEE_RECOVERY_PARTITION_GUID           {0x16, 0xEA, 0x32, 0xC8, 0x0D, 0x8B, 0x98, 0x43, 0xA6, 0x7B, 0xEB, 0xB3, 0x0E, 0xF9, 0x8E, 0x7E}  // QSEE_RECOVERY_PARTITION
#define APPSBL_RECOVERY_PARTITION_GUID         {0x5B, 0x4B, 0x23, 0x9F, 0xFB, 0x0E, 0x13, 0x43, 0x8E, 0x4C, 0x0A, 0xF1, 0xF6, 0x05, 0x53, 0x6B}  // APPSBL_RECOVERY_PARTITION
#define PMIC_RECOVERY_PARTITION_GUID           {0xD9, 0x7C, 0xBD, 0xD9, 0xBA, 0xB1, 0x3B, 0x4F, 0xA6, 0xCE, 0x0E, 0x34, 0x8A, 0x11, 0x16, 0xE9}  // PMIC_RECOVERY_PARTITION
#define RPM_RECOVERY_PARTITION_GUID            {0x14, 0x44, 0x80, 0xB7, 0x65, 0x8E, 0x1D, 0x4A, 0x93, 0xFD, 0x9D, 0x9B, 0xF5, 0x62, 0x13, 0x06}  // RPM_RECOVERY_PARTITION
#define ABL_RECOVERY_PARTITION_GUID            {0xE6, 0x78, 0x62, 0xDC, 0x99, 0x07, 0x16, 0x46, 0xBD, 0x72, 0x28, 0xD6, 0x0D, 0x15, 0x92, 0x1C}  // ABL_RECOVERY_PARTITION
#define SHRM_RECOVERY_PARTITION_GUID           {0x00, 0x6C, 0xFD, 0x39, 0xEB, 0x49, 0xD1, 0x6B, 0x68, 0x99, 0x2F, 0xB8, 0x49, 0xDD, 0x4F, 0x75}  // SHRM_RECOVERY_PARTITION
#define AOP_RECOVERY_PARTITION_GUID            {0x4C, 0x7C, 0xB2, 0xB8, 0x5B, 0x4B, 0xB2, 0x8A, 0x50, 0x2F, 0xA7, 0x92, 0xB5, 0x90, 0xA8, 0x96}  // AOP_RECOVERY_PARTITION
#define AOP_CONFIG_RECOVERY_PARTITION_GUID     {0xD4, 0x6C, 0x03, 0x77, 0xD5, 0x03, 0xBB, 0x42, 0x8E, 0xD1, 0x37, 0xE5, 0xA8, 0x8B, 0xAA, 0x34}  // AOP_CONFIG_RECOVERY_PARTITION
#define CPUCPFW_RECOVERY_PARTITION_GUID        {0xFB, 0x11, 0x11, 0x6C, 0x54, 0x53, 0xDE, 0x41, 0xAC, 0x17, 0x5B, 0x6E, 0x54, 0x2B, 0xE8, 0x36}  // CPUCPFW_RECOVERY_PARTITION
#define CDT_RECOVERY_PARTITION_GUID            {0x9C, 0xFA, 0xE6, 0x9B, 0xA7, 0xC5, 0xAA, 0x4B, 0x97, 0x40, 0x8D, 0x93, 0xC5, 0x08, 0x4B, 0xD9}  // CDT_RECOVERY_PARTITION
#define DDR_TRAINING_RECOVERY_PARTITION_GUID   {0xF3, 0x4E, 0xA5, 0x78, 0xD7, 0xD7, 0x18, 0x45, 0x91, 0xD5, 0x1E, 0x97, 0x2C, 0x82, 0xB2, 0x82}  // DDR_TRAINING_RECOVERY_PARTITION
#define APDP_RECOVERY_PARTITION_GUID           {0x8D, 0x19, 0x0F, 0x11, 0x74, 0x81, 0x93, 0x41, 0x9A, 0xF1, 0x5D, 0xA9, 0x4C, 0xDC, 0x59, 0xC9}  // APDP_RECOVERY_PARTITION
#define RAM_DUMP_RECOVERY_PARTITION_GUID       {0xF3, 0x13, 0xB7, 0x91, 0x22, 0x0F, 0x16, 0x49, 0x96, 0x60, 0xB9, 0x6E, 0xF7, 0x16, 0x47, 0x57}  // RAM_DUMP_RECOVERY_PARTITION
#define MISC_OEM_RECOVERY_PARTITION_GUID       {0xCD, 0x3E, 0x3E, 0x3E, 0x12, 0xC5, 0x95, 0x4F, 0x91, 0x44, 0x60, 0x63, 0x82, 0x6A, 0x89, 0x70}  // MISC_OEM_RECOVERY_PARTITION
#define MISC_QTI_RECOVERY_PARTITION_GUID       {0x21, 0x8B, 0x0C, 0xD3, 0xD9, 0xDD, 0xB6, 0x45, 0x8D, 0xE0, 0x31, 0x65, 0xD3, 0x43, 0x95, 0xC9}  // MISC_QTI_RECOVERY_PARTITION
#define QSEE_DEVCFG_RECOVERY_PARTITION_GUID    {0xE7, 0x34, 0x95, 0x16, 0x09, 0x78, 0x40, 0x42, 0x97, 0x63, 0x0B, 0xA5, 0xDC, 0x37, 0xB5, 0xFF}  // QSEE_DEVCFG_RECOVERY_PARTITION
#define SEC_RECOVERY_PARTITION_GUID            {0xEF, 0xC7, 0xCF, 0x76, 0x9D, 0x03, 0x2C, 0x4E, 0xB8, 0x1E, 0x4D, 0xD8, 0xC2, 0xCB, 0x2A, 0x93}  // SEC_RECOVERY_PARTITION
#define QHEE_RECOVERY_PARTITION_GUID           {0xA0, 0xEC, 0x45, 0xCB, 0x4E, 0x50, 0xBB, 0x42, 0x91, 0xBA, 0xC9, 0xB3, 0x23, 0x6F, 0x6A, 0x6E}  // QHEE_RECOVERY_PARTITION
#define SMSS_RECOVERY_PARTITION_GUID           {0x51, 0x6B, 0xF5, 0xFD, 0x7E, 0xD6, 0x81, 0x40, 0xA4, 0xE2, 0x97, 0x5A, 0x09, 0x97, 0x20, 0x0D}  // SMSS_RECOVERY_PARTITION
#define XBL_RAMDUMP_RECOVERY_PARTITION_GUID    {0xF6, 0x8B, 0x60, 0xFF, 0xDF, 0xAE, 0x84, 0x40, 0xBE, 0xC5, 0xC9, 0x2A, 0xB4, 0xE4, 0x53, 0x4D}  // XBL_RAMDUMP_RECOVERY_PARTITION
#define CPUCP_DTB_RECOVERY_PARTITION_GUID      {0x2B, 0x3A, 0x21, 0x57, 0xDE, 0x39, 0x84, 0x41, 0x97, 0xDE, 0x64, 0x5D, 0x37, 0x91, 0x3E, 0x4E}  // CPUCP_DTB_RECOVERY_PARTITION
#define DDR_CAL_RECOVERY_PARTITION_GUID        {0xDD, 0x8E, 0x19, 0xCB, 0xBD, 0x9E, 0xA1, 0x48, 0x9B, 0xB6, 0xBB, 0x31, 0x94, 0xBF, 0x2E, 0x51}  // DDR_CAL_RECOVERY_PARTITION
#define RECOVERY_INFO_PARTITION_GUID           {0x91, 0xB3, 0x74, 0x73, 0x1C, 0x29, 0xFA, 0x49, 0xAB, 0xC2, 0x04, 0x63, 0xAB, 0x5F, 0x71, 0x3F}  // RECOVERY_INFO_PARTITION
#define TRAIL_BOOT_INFO_PARTITION_GUID         {0xBA, 0xF9, 0x34, 0x53, 0xCE, 0x02, 0x09, 0x46, 0x90, 0x81, 0x2E, 0xC3, 0x9D, 0xCD, 0x6A, 0xC6}  // TRAIL_BOOT_INFO_PARTITION
#define PARTITION_TABLE_RESTORE_PARTITION_GUID {0x3B, 0x8C, 0x2E, 0x45, 0x7F, 0xB6, 0x66, 0x4C, 0x80, 0xD9, 0xAD, 0x45, 0x7F, 0x74, 0xCB, 0x0A}  // PARTITION_TABLE_RESTORE_PARTITION
#define DMA_GSIFW_PARTITION_GUID               {0X73, 0X83, 0X67, 0XF3, 0X4F, 0X23, 0X02, 0X4C, 0X9D, 0XE5, 0X15, 0X8A, 0X6F, 0X4B, 0XAB, 0X94}  // DMA_GSIFW_PARTITION 
#define ABL_SW_PARTITION_GUID                  {0XA1, 0X28, 0X69, 0XBD, 0XE0, 0X4C, 0X38, 0XA0, 0x4F, 0x3A, 0x14, 0x95, 0xE3, 0xED, 0xDF, 0xFB}  // ABL_SW_PARTITION 
#define UEFI_RECOVERY_PARTITION_GUID           {0x5B, 0x4B, 0x23, 0x9F, 0xFB, 0x0E, 0x13, 0x43, 0x8E, 0x4C, 0x0A, 0xF1, 0xF6, 0x05, 0x53, 0x6B}  // UEFI_RECOVERY_PARTITION
#define SOCCP_RECOVERY_PARTITION_GUID          {0xB8, 0x42, 0xFD, 0xD7, 0x8E, 0xD5, 0x4D, 0xAA, 0xA7, 0x55, 0xD0, 0xB4, 0x3F, 0xFF, 0x21, 0xE6}  // SOCCP_RECOVERY_PARTITION
#define SOCCP_DEBUG_RECOVERY_PARTITION_GUID    {0x88, 0xCE, 0x4B, 0x5F, 0x61, 0x6E, 0x45, 0x49, 0xB8, 0x75, 0x56, 0x5D, 0xAD, 0x98, 0x49, 0x51}  // SOCCP_DEBUG_RECOVERY_PARTITION
#define SOCCP_DCD_RECOVERY_PARTITION_GUID      {0xBF, 0x79, 0x5A, 0x2C, 0xF2, 0xEA, 0x41, 0x10, 0x85, 0xEA, 0x95, 0xCC, 0x43, 0xFE, 0x15, 0x32}  // SOCCP_DCD_RECOVERY_PARTITION


/* Defining Strings for Pagedev devices */
#define ACDB_PARTITION_STRING                    "acdb"                                                                                          // ACDB_PARTITION
#define AOP_PARTITION_STRING                     "aop"                                                                                           // AOP_PARTITION
#define AOP_CONFIG_PARTITION_STRING              "aop_devcfg"                                                                                    // AOP_CONFIG_PARTITION
#define APDP_PARTITION_STRING                    "apdp"                                                                                          // APDP_PARTITION
#define CDT_PARTITION_STRING                     "cdt"                                                                                           // CDT_PARTITION
#define CPUCP_DTB_PARTITION_STRING               "cpucp_dtb"                                                                                     // CPUCP_DTB_PARTITION
#define CPUCPFW_PARTITION_STRING                 "cpucpfw"                                                                                       // CPUCPFW_PARTITION
#define DDR_TRAINING_PARTITION_STRING            "ddr"                                                                                           // DDR_TRAINING_PARTITION
#define IPA_PARTITION_STRING                     "ipa_fw"                                                                                        // IPA_PARTITION
#define MISC_OEM_PARTITION_STRING                "multi_oem"                                                                                     // MISC_OEM_PARTITION
#define MISC_QTI_PARTITION_STRING                "multi_qti"                                                                                     // MISC_QTI_PARTITION
#define Q6_MPSS_PARTITION_STRING                 "qdsp"                                                                                          // Q6_MPSS_PARTITION
#define Q6_MPSS_DTB_CONFIG_PARTITION_STRING      "qdsp_dtb"                                                                                      // Q6_MPSS_DTB_CONFIG_PARTITION
#define QHEE_PARTITION_STRING                    "qhee"                                                                                          // QHEE_PARTITION
#define QSEE_PARTITION_STRING                    "tz"                                                                                            // QSEE_PARTITION
#define QSEE_DEVCFG_PARTITION_STRING             "tz_devcfg"                                                                                     // QSEE_DEVCFG_PARTITION
#define QUANTUM_PARTITION_STRING                 "quantum"                                                                                       // QUANTUM_PARTITION
#define QUEST_PARTITION_STRING                   "quest"                                                                                         // QUEST_PARTITION
#define QUPFW_PARTITION_STRING                   "qup_fw"                                                                                        // QUPFW_PARTITION
#define SEC_PARTITION_STRING                     "sec"                                                                                           // SEC_PARTITION
#define SHRM_PARTITION_STRING                    "shrm"                                                                                          // SHRM_PARTITION
#define TN_PARTITION_STRING                      "apps"                                                                                          // TN_PARTITION
#define TOOLS_PARTITION_STRING                   "tools"                                                                                         // TOOLS_PARTITION
#define UEFI_PARTITION_STRING                    "uefi"                                                                                          // UEFI_PARTITION
#define XBL_CONFIG_PARTITION_STRING              "xbl_config"                                                                                    // XBL_CONFIG_PARTITION
#define XBL_RAMDUMP_PARTITION_STRING             "xbl_ramdump"                                                                                   // XBL_RAMDUMP_PARTITION
#define RECOVERY_INFO_PARTITION_STRING           "recoveryinfo"                                                                                  // RECOVERY_INFO_PARTITION
#define TRAIL_BOOT_INFO_PARTITION_STRING         "trial_boot_info"                                                                               // TRAIL_BOOT_INFO_PARTITION
#define XBL_TEST_MODE_PARTITION_STRING           "xbl_sc_tm"                                                                                     // XBL_TEST_MODE_PARTITION
#define DMA_GSIFW_PARTITION_STRING               "dma_gsi"                                                                                       // DMA_GSIFW_PARTITION
#define ABL_SW_PARTITION_STRING                  "abl_sw"                                                                                        // ABL_SW_PARTITION
#define KERNEL_PARTITION_STRING                  "hlos"                                                                                          // KERNEL_PARTITION
 
static uint32 internal_image_set_status [BOOT_MEDIA_FAMILY_MAX] = {0};


typedef enum
{
  ACDB_PARTITION = 0,
  AOP_PARTITION,
  AOP_CONFIG_PARTITION,
  APDP_PARTITION,
  CDT_PARTITION,
  CPUCP_DTB_PARTITION,
  CPUCPFW_PARTITION,
  DDR_TRAINING_PARTITION,
  EFS1_PARTITION,
  EFS2_PARTITION,
  EFS3_PARTITION,
  IPA_PARTITION,
  KERNEL_PARTITION,
  MISC_OEM_PARTITION,
  MISC_QTI_PARTITION,
  Q6_MPSS_PARTITION,
  Q6_MPSS_DTB_CONFIG_PARTITION,
  QHEE_PARTITION,
  QSEE_PARTITION,
  QSEE_DEVCFG_PARTITION,
  QUANTUM_PARTITION,
  QUEST_PARTITION,
  QUPFW_PARTITION,
  SEC_PARTITION,
  SHRM_PARTITION,
  TN_PARTITION,
  TOOLS_PARTITION,
  UEFI_PARTITION,
  XBL_CONFIG_PARTITION,
  XBL_RAMDUMP_PARTITION,
  RECOVERY_INFO_PARTITION,
  SBL1_PARTITION,
  TRAIL_BOOT_INFO_PARTITION,
  XBL_LOGS_PARTITION,
  XBL_TEST_MODE_PARTITION,
  RAM_DUMP_PARTITION,
  SD_DUMP_PARTITION,
  NVME_DUMP_PARTITION,
  SMSS_PARTITION,
  PARTITION_TABLE_RESTORE_PARTITION,
  DMA_GSIFW_PARTITION,
  ABL_SW_PARTITION,
  DDR_DEBUG_PARTITION,
  SOCCP_PARTITION,
  SOCCP_DEBUG_PARTITION,
  SOCCP_DCD_PARTITION,
  MAX_PARTITION
} boot_partition_t;


typedef enum
{
  IMAGE_SET_A = 0,
  IMAGE_SET_B,
  IMAGE_SET_MAX
} boot_image_set_t;


typedef struct
{
  boot_boolean partition_entry_valid;
  uint8 partition_id[PARTITION_ID_MAX_LENGTH];
} partition_entry_t;


typedef struct
{
  boot_boolean image_set_valid;
  partition_entry_t partition_entries[MAX_PARTITION];
} image_set_t;


typedef struct
{
  boot_media_family media_family;
  image_set_t image_sets[IMAGE_SET_MAX];
} storage_set_t;


bl_error_boot_type get_partition_id_by_partition(boot_media_family media_family,
                                                 boot_image_set_t image_set,
                                                 boot_partition_t partition,
                                                 const uint8 ** result_partition_id,
                                                 uint8 * result_partition_id_size);


bl_error_boot_type get_image_set(boot_media_family media_family,
                                 boot_image_set_t image_set,
                                 const image_set_t ** result_image_set,
                                 uint32 * result_image_set_size);


bl_error_boot_type get_storage_set(boot_media_family media_family,
                                   const storage_set_t ** result_storage_set,
                                   uint32 * result_storage_set_size);


bl_error_boot_type boot_partition_enable_image_set(boot_media_family media_family,
                                                   boot_image_set_t image_set);


bl_error_boot_type boot_partition_disable_image_set(boot_media_family media_family,
                                                    boot_image_set_t image_set);


bl_error_boot_type boot_partition_enable_all_image_sets(boot_media_family media_family);


bl_error_boot_type boot_partition_disable_all_image_sets(boot_media_family media_family);


/* Interface for boot_partition */
typedef struct
{
  bl_error_boot_type (*get_partition_id_by_partition)(boot_media_family media_family,
                                                      boot_image_set_t image_set,
                                                      boot_partition_t partition,
                                                      const uint8 ** result_partition_id,
                                                      uint8 * result_partition_id_size);

  bl_error_boot_type (*get_image_set)(boot_media_family media_family,
                                      boot_image_set_t image_set,
                                      const image_set_t ** result_image_set,
                                      uint32 * result_image_set_size);

  bl_error_boot_type (*get_storage_set)(boot_media_family media_family,
                                        const storage_set_t ** result_storage_set,
                                        uint32 * result_storage_set_size);

  bl_error_boot_type (*boot_partition_enable_image_set)(boot_media_family media_family,
                                                        boot_image_set_t image_set);

  bl_error_boot_type (*boot_partition_disable_image_set)(boot_media_family media_family,
                                                         boot_image_set_t image_set);


  bl_error_boot_type (*boot_partition_enable_all_image_sets)(boot_media_family media_family);


  bl_error_boot_type (*boot_partition_disable_all_image_sets)(boot_media_family media_family);

} boot_partition_if_type;

extern boot_partition_if_type partition_if;

#endif // BOOT_PARTITION_H
