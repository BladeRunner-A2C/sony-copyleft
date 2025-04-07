/*
===========================================================================
*/
/**
  @file 

*/
/*
  ====================================================================

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  10/24/17  IH      Initial revision.

  ====================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/
#ifndef SWSYS_ENV_UEFI_SYSINFO_H
#define SWSYS_ENV_UEFI_SYSINFO_H
/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

bool swsys_init_sysinfo_uefi(void);

bool swsys_get_serial_number_uefi(uint64_t *serial_number);

bool swsys_get_chip_id_uefi(char* chip_id, uint32_t size);
bool swsys_get_chip_version_uefi(uint32_t *chip_version);

bool swsys_get_processor_name_uefi(char *processor_name, uint32_t size);

bool swsys_get_device_id_uefi(uint8_t *buf, uint32_t size);
#endif