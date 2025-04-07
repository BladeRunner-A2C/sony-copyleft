#ifndef BOOT_TARGET_PARTITIONS_H
#define BOOT_TARGET_PARTITIONS_H

/*=============================================================================   

Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.

===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who       what, where, why
 --------   ---       -----------------------------------------------------------
 11/06/23   amaji     Added SBL1_PARTITION id for blockdev,image set A
 03/08/23   suhas     Updated BootPartitionLib with missing partitions
 03/04/23   ng        Added entry for ABL_SW
 03/03/23   ng        Added entry for DMA_GSIFW
 03/02/23   yps       Added CDT partition ID for blockdev
 01/13/23   suhas     Initial Release 
=============================================================================*/


#include <boot_partition.h>
#include <MIbib.h>


const storage_set_t partition_definitions[] =
  {
#ifdef FLASHLESS_ENABLED
    /* USB FLASHLESS SAHARA IDs */
    {
      .media_family = BOOT_MEDIA_FAMILY_FLASHLESS,
      .image_sets = 
      {
        /* Image set A */
        {
          .image_set_valid = TRUE,
          .partition_entries = 
          {
            {.partition_entry_valid = TRUE, .partition_id = ACDB_PARTITION_SAHARAID},                // ACDB_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = AOP_PARTITION_SAHARAID},                 // AOP_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = AOP_CONFIG_PARTITION_SAHARAID},          // AOP_CONFIG_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = APDP_PARTITION_SAHARAID},                // APDP_PARTITION
            {.partition_entry_valid = FALSE},                                                        // CDT_PARTITION
            {.partition_entry_valid = FALSE},                                                        // CPUCP_DTB_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = CPUCPFW_PARTITION_SAHARAID},             // CPUCPFW_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = DDR_TRAINING_PARTITION_SAHARAID},        // DDR_TRAINING_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = EFS1_PARTITION_SAHARAID},                // EFS1_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = EFS2_PARTITION_SAHARAID},                // EFS2_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = EFS3_PARTITION_SAHARAID},                // EFS3_PARTITION
            {.partition_entry_valid = FALSE},                                                        // IPA_PARTITION
            {.partition_entry_valid = FALSE,},                                                       // KERNEL_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = MISC_OEM_PARTITION_SAHARAID},            // MISC_OEM_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = MISC_QTI_PARTITION_SAHARAID},            // MISC_QTI_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = Q6_MPSS_PARTITION_SAHARAID},             // Q6_MPSS_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = Q6_MPSS_DTB_CONFIG_PARTITION_SAHARAID},  // Q6_MPSS_DTB_CONFIG_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QHEE_PARTITION_SAHARAID},                // QHEE_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = TZ_PARTITION_SAHARAID},                  // TZ_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QSEE_DEVCFG_PARTITION_SAHARAID},         // QSEE_DEVCFG_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QUANTUM_PARTITION_SAHARAID},             // QUANTUM_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QUEST_PARTITION_SAHARAID},               // QUEST_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QUPFW_PARTITION_SAHARAID},               // QUPFW_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = SEC_PARTITION_SAHARAID},                 // SEC_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = SHRM_PARTITION_SAHARAID},                // SHRM_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = TN_PARTITION_SAHARAID},                  // TN_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = TOOLS_PARTITION_SAHARAID},               // TOOLS_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = UEFI_PARTITION_SAHARAID},                // UEFI_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = XBL_CONFIG_PARTITION_SAHARAID},          // XBL_CONFIG_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = XBL_RAMDUMP_PARTITION_SAHARAID},         // XBL_RAMDUMP_PARTITION
            {.partition_entry_valid = FALSE},                                                        // RECOVERY_INFO_PARTITION
            {.partition_entry_valid = FALSE},                                                        // SBL1_PARTITION
            {.partition_entry_valid = FALSE},                                                        // TRAIL_BOOT_INFO_PARTITION
            {.partition_entry_valid = FALSE},                                                        // XBL_LOGS_PARTITION
            {.partition_entry_valid = FALSE},                                                        // XBL_TEST_MODE_PARTITION
            {.partition_entry_valid = FALSE},                                                        // RAM_DUMP_PARTITION,
            {.partition_entry_valid = FALSE},                                                        // SD_DUMP_PARTITION,
            {.partition_entry_valid = FALSE},                                                        // NVME_DUMP_PARTITION,
            {.partition_entry_valid = FALSE},                                                        // SMSS_PARTITION
            {.partition_entry_valid = FALSE},                                                        // PARTITION_TABLE_RESTORE_PARTITION
            {.partition_entry_valid = FALSE},                                                        // DMA_GSIFW_PARTITION
            {.partition_entry_valid = FALSE},                                                        // ABL_SW_PARTITION
            {.partition_entry_valid = FALSE}                                                         // DDR_DEBUG_PARTITION
          }
        },

        /* Image set B */
        {
          .image_set_valid = FALSE
        }        
      }
    },
#endif


#ifdef BLOCKDEV_ENABLED
    /* eMMC Coldplug GUIDs */
    {
      .media_family = BOOT_MEDIA_FAMILY_BLOCK,
      .image_sets = 
      {
        /* Image set A */
        {
          .image_set_valid = TRUE,
          .partition_entries =
          {
            {.partition_entry_valid = FALSE},                                                        // ACDB_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = AOP_PARTITION_GUID},                     // AOP_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = AOP_CONFIG_PARTITION_GUID},              // AOP_CONFIG_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = APDP_PARTITION_GUID},                    // APDP_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = CDT_PARTITION_GUID},                     // CDT_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = CPUCP_DTB_PARTITION_GUID},               // CPUCP_DTB_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = CPUCPFW_PARTITION_GUID},                 // CPUCPFW_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = DDR_TRAINING_PARTITION_GUID},            // DDR_TRAINING_PARTITION
            {.partition_entry_valid = FALSE},                                                        // EFS1_PARTITION
            {.partition_entry_valid = FALSE},                                                        // EFS2_PARTITION
            {.partition_entry_valid = FALSE},                                                        // EFS3_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = IPA_PARTITION_GUID},                     // IPA_PARTITION
            {.partition_entry_valid = FALSE},                                                        // KERNEL_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = MISC_OEM_PARTITION_GUID},                // MISC_OEM_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = MISC_QTI_PARTITION_GUID},                // MISC_QTI_PARTITION
            {.partition_entry_valid = FALSE},                                                        // Q6_MPSS_PARTITION
            {.partition_entry_valid = FALSE},                                                        // Q6_MPSS_DTB_CONFIG_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QHEE_PARTITION_GUID},                    // QHEE_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QSEE_PARTITION_GUID},                    // QSEE_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QSEE_DEVCFG_PARTITION_GUID},             // QSEE_DEVCFG_PARTITION
            {.partition_entry_valid = FALSE},                                                        // QUANTUM_PARTITION
            {.partition_entry_valid = FALSE},                                                        // QUEST_PARTITION
            {.partition_entry_valid = FALSE},                                                        // QUPFW_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = SEC_PARTITION_GUID},                     // SEC_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = SHRM_PARTITION_GUID},                    // SHRM_PARTITION
            {.partition_entry_valid = FALSE},                                                        // TN_PARTITION
            {.partition_entry_valid = FALSE},                                                        // TOOLS_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = UEFI_PARTITION_GUID},                    // UEFI_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = XBL_CONFIG_PARTITION_GUID},              // XBL_CONFIG_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = XBL_RAMDUMP_PARTITION_GUID},             // XBL_RAMDUMP_PARTITION
            {.partition_entry_valid = FALSE},                                                        // RECOVERY_INFO_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = SBL1_PARTITION_GUID},                    // SBL1_PARTITION
            {.partition_entry_valid = FALSE},                                                        // TRAIL_BOOT_INFO_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = XBL_LOGS_PARTITION_GUID},                // XBL_LOGS_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = XBL_TEST_MODE_PARTITION_GUID},           // XBL_TEST_MODE_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = RAM_DUMP_PARTITION_GUID},                // RAM_DUMP_PARTITION,
            {.partition_entry_valid = TRUE, .partition_id = SD_DUMP_PARTITION_GUID},                 // SD_DUMP_PARTITION,
            {.partition_entry_valid = FALSE},                                                        // NVME_DUMP_PARTITION,
            {.partition_entry_valid = FALSE},                                                        // SMSS_PARTITION
            {.partition_entry_valid = FALSE},                                                        // PARTITION_TABLE_RESTORE_PARTITION
            {.partition_entry_valid = FALSE},                                                        // DMA_GSIFW_PARTITION
            {.partition_entry_valid = FALSE},                                                        // ABL_SW_PARTITION
            {.partition_entry_valid = FALSE}                                                         // DDR_DEBUG_PARTITION
          }
        },

        /* Image set B */
        {
          .image_set_valid = FALSE,
          .partition_entries = 
          {
            {.partition_entry_valid = FALSE},                                                        // ACDB_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = AOP_RECOVERY_PARTITION_GUID},            // AOP_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = AOP_CONFIG_RECOVERY_PARTITION_GUID},     // AOP_CONFIG_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = APDP_RECOVERY_PARTITION_GUID},           // APDP_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = CDT_RECOVERY_PARTITION_GUID},            // CDT_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = CPUCP_DTB_RECOVERY_PARTITION_GUID},      // CPUCP_DTB_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = CPUCPFW_RECOVERY_PARTITION_GUID},        // CPUCPFW_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = DDR_TRAINING_RECOVERY_PARTITION_GUID},   // DDR_TRAINING_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // EFS1_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // EFS2_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // EFS3_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // IPA_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // KERNEL_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = MISC_OEM_RECOVERY_PARTITION_GUID},       // MISC_OEM_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = MISC_QTI_RECOVERY_PARTITION_GUID},       // MISC_QTI_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // Q6_MPSS_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // Q6_MPSS_DTB_CONFIG_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QHEE_RECOVERY_PARTITION_GUID},           // QHEE_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QSEE_RECOVERY_PARTITION_GUID},           // QSEE_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QSEE_DEVCFG_RECOVERY_PARTITION_GUID},    // QSEE_DEVCFG_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // QUANTUM_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // QUEST_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // QUPFW_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = SEC_RECOVERY_PARTITION_GUID},            // SEC_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = SHRM_RECOVERY_PARTITION_GUID},           // SHRM_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // TN_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // TOOLS_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // UEFI_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = XBL_CONFIG_RECOVERY_PARTITION_GUID},     // XBL_CONFIG_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = XBL_RAMDUMP_RECOVERY_PARTITION_GUID},    // XBL_RAMDUMP_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // RECOVERY_INFO_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = SBL1_RECOVERY_PARTITION_GUID},           // SBL1_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = TRAIL_BOOT_INFO_PARTITION_GUID},         // TRAIL_BOOT_INFO_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = XBL_LOGS_PARTITION_GUID},                // XBL_LOGS_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = XBL_TEST_MODE_PARTITION_GUID},           // XBL_TEST_MODE_RECOVERY_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = RAM_DUMP_PARTITION_GUID},                // RAM_DUMP_PARTITION,
            {.partition_entry_valid = TRUE, .partition_id = SD_DUMP_PARTITION_GUID},                 // SD_DUMP_PARTITION,
            {.partition_entry_valid = FALSE},                                                        // NVME_DUMP_PARTITION,
            {.partition_entry_valid = TRUE, .partition_id = SMSS_RECOVERY_PARTITION_GUID},           // SMSS_RECOVERY_PARTITION
            {.partition_entry_valid = FALSE},                                                        // PARTITION_TABLE_RESTORE_PARTITION
            {.partition_entry_valid = FALSE},                                                        // DMA_GSIFW_PARTITION
            {.partition_entry_valid = FALSE},                                                        // ABL_SW_PARTITION
            {.partition_entry_valid = FALSE}                                                         // DDR_DEBUG_PARTITION
          }
        }
      }
    },
#endif


#ifdef PAGEDEV_ENABLED
    /* NAND Partition Strings */
    {
      .media_family = BOOT_MEDIA_FAMILY_PAGE,
      .image_sets = 
      {
        /* Image set A */
        {
          .image_set_valid = TRUE,
          .partition_entries =
          {

            {.partition_entry_valid = FALSE},                                                        // ACDB_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = AOP_PARTITION_STRING},                   // AOP_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = AOP_CONFIG_PARTITION_STRING},            // AOP_CONFIG_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = APDP_PARTITION_STRING},                  // APDP_PARTITION
            {.partition_entry_valid = FALSE},                                                        // CDT_PARTITION
            {.partition_entry_valid = FALSE},                                                        // CPUCP_DTB_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = CPUCPFW_PARTITION_STRING},               // CPUCPFW_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = DDR_TRAINING_PARTITION_STRING},          // DDR_TRAINING_PARTITION
            {.partition_entry_valid = FALSE},                                                        // EFS1_PARTITION
            {.partition_entry_valid = FALSE},                                                        // EFS2_PARTITION
            {.partition_entry_valid = FALSE},                                                        // EFS3_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = IPA_PARTITION_STRING},                   // IPA_PARTITION
            {.partition_entry_valid = FALSE},                                                        // KERNEL_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = MISC_OEM_PARTITION_STRING},              // MISC_OEM_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = MISC_QTI_PARTITION_STRING},              // MISC_QTI_PARTITION
            {.partition_entry_valid = FALSE},                                                        // Q6_MPSS_PARTITION
            {.partition_entry_valid = FALSE},                                                        // Q6_MPSS_DTB_CONFIG_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QHEE_PARTITION_STRING},                  // QHEE_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QSEE_PARTITION_STRING},                  // QSEE_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = QSEE_DEVCFG_PARTITION_STRING},           // QSEE_DEVCFG_PARTITION
            {.partition_entry_valid = FALSE},                                                        // QUANTUM_PARTITION
            {.partition_entry_valid = FALSE},                                                        // QUEST_PARTITION
            {.partition_entry_valid = FALSE},                                                        // QUPFW_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = SEC_PARTITION_STRING},                   // SEC_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = SHRM_PARTITION_STRING},                  // SHRM_PARTITION
            {.partition_entry_valid = FALSE},                                                        // TN_PARTITION
            {.partition_entry_valid = FALSE},                                                        // TOOLS_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = UEFI_PARTITION_STRING},                  // UEFI_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = XBL_CONFIG_PARTITION_STRING},            // XBL_CONFIG_PARTITION
            {.partition_entry_valid = TRUE, .partition_id = XBL_RAMDUMP_PARTITION_STRING},           // XBL_RAMDUMP_PARTITION
            {.partition_entry_valid = FALSE},                                                        // RECOVERY_INFO_PARTITION
            {.partition_entry_valid = FALSE},                                                        // SBL1_PARTITION
            {.partition_entry_valid = FALSE},                                                        // TRAIL_BOOT_INFO_PARTITION
            {.partition_entry_valid = FALSE},                                                        // XBL_LOGS_PARTITION
            {.partition_entry_valid = FALSE},                                                        // XBL_TEST_MODE_PARTITION
            {.partition_entry_valid = FALSE},                                                        // RAM_DUMP_PARTITION,
            {.partition_entry_valid = FALSE},                                                        // SD_DUMP_PARTITION,
            {.partition_entry_valid = FALSE},                                                        // NVME_DUMP_PARTITION,
            {.partition_entry_valid = FALSE},                                                        // SMSS_PARTITION
            {.partition_entry_valid = FALSE},                                                        // PARTITION_TABLE_RESTORE_PARTITION
            {.partition_entry_valid = FALSE},                                                        // DMA_GSIFW_PARTITION
            {.partition_entry_valid = FALSE},                                                        // ABL_SW_PARTITION
            {.partition_entry_valid = FALSE}                                                         // DDR_DEBUG_PARTITION
          }
        },

        /* Image set B */
        {
          .image_set_valid = FALSE
        } 
      }
    }
#endif    
  };


#endif // BOOT_TARGET_PARTITIONS_H

