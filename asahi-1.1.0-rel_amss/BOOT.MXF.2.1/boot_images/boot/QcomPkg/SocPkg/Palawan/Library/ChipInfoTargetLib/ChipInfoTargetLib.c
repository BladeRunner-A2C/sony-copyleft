/*==============================================================================
  @file ChipInfoTargetLib.c

  ChipInfo functions for the XBL Loader ChipInfo Driver.

================================================================================
  Copyright (c) 2017, 2019, 2023 Qualcomm Technologies, Inc. All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
================================================================================

  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Waipio/Library/ChipInfoTargetLib/ChipInfoTargetLib.c#1 $
  $DateTime: 2020/06/24 18:36:20 $
  $Author: pwbldsvc $

==============================================================================*/

/*==============================================================================
      Include Files
==============================================================================*/
#include "ChipInfoHWIO.h"
#include "ChipInfoLocal.h"
#include "HALhwio.h"
#include <Library/CacheMaintenanceLib.h>

/*==============================================================================
**  Macros
**============================================================================*/

/**
 * Chipset-specific numbers of cores and clusters.
 * CHIPINFO_NUM_CLUSTERS is different from
 * ChipInfoDefs.h/CHIPINFO_MAX_CPU_CLUSTERS since the latter is a global
 * maximum across all supported chips, while the former only applies to
 * the current chip.
 */
#define CHIPINFO_NUM_CLUSTERS                    1

/**
 * The QTV fuses contain a bitmask of all the disabled bins,
 * with bit0 = Bin A, bit1 = Bin B, etc. If Bins A and B are both disabled,
 * the fuses would hold 0b0011. Bins A through D are supported.
 * This macro expects uppercase letters only. It will be used to mask the
 * contents of the QTV fuses to identify the blown fuses.
 */
#define CHIPINFO_SUBBIN_GROUP(x)                       0x1 << ((char)(x) - 'A')

uint32 aCPUClusters[CHIPINFO_NUM_CLUSTERS] = { 0 };


/*==============================================================================
**  Functions
**============================================================================*/
void ChipInfo_UpdateDisabledCPUsToDDRLocation(void)
{

  /* As there is no chipinfo driver in cpucp and cpusys-vm images
   * storing the disabled CPUs info at 0x81CF4000 which is used by cpucp and cpusys-vm
   * This is a 4k region with all masters read-only permissions reserved for Palawan
   * Flush the cache content DDR otherwise cpucp/cpu-sys-vm may see the stale data
   */
  outpdw(0x81CF4000, aCPUClusters[0]);
  
  WriteBackInvalidateDataCacheRange((void*)0x81cf4000, 0x1000);
}

/*==============================================================================
  FUNCTION      ChipInfo_InitChipset

  DESCRIPTION   Chipset-specific initialization sequences, including reading
                PTE fuses to determine which parts are disabled

==============================================================================*/
void ChipInfo_InitChipset(ChipInfoCtxtType *pChipInfoCtxt)
{

  uint32 DisabledBins;
  uint32 SubBinValue;

  if (pChipInfoCtxt == NULL)
  {
    return;
  }

  pChipInfoCtxt->nNumClusters = CHIPINFO_NUM_CLUSTERS;
  pChipInfoCtxt->aCPUClusters = aCPUClusters;

  /* Check which bins have been marked "disabled" */
  DisabledBins = HWIO_INF(QFPROM_CORR_QC_SPARE_0_ROW0_LSB, PARTIAL_BIN);

  /* Check the sub-bins of bins marked "disabled" for more detailed information */
  /*
   * Group A: CPUSS
   *
   * SUB_BINA[0] - Gold+ SS disabled
   * SUB_BINA[1] - Gold SS disabled
   * SUB_BINA[2] - Any silver (other than silver0 disabled)
   *                NOTE: Silver 0 is never disabled since
   *                      it's the boot core. It can't be
   *                      disabled given that the chip has
   *                      booted up to this point.
   * SUB_BINA[3] - Reserved
   * SUB_BINA[4] - sub-binning for bin A enabled. If sub-binning disabled, mark all
   *                gold cores as disabled like with previous targets.
   */
  if (DisabledBins & CHIPINFO_SUBBIN_GROUP('A') &&
      pChipInfoCtxt->nNumClusters > 0)
  {
    pChipInfoCtxt->aCPUClusters[0] = HWIO_INF(QFPROM_CORR_QC_SPARE_0_ROW0_MSB, SUBBINA_CORE);
  }


    /*
   * Group B: Multimedia
   *  SUB_BINB[0] - GPU disabled
   *  SUB_BINB[1] - Video disabled
   *  SUB_BINB[2] - Camera disabled
   *  SUB_BINB[3] - Display disabled
   *  SUB_BINB[4] - sub-binning for bin B enabled.
     */

  if (DisabledBins & CHIPINFO_SUBBIN_GROUP('B'))
  {
    SubBinValue = HWIO_INF(QFPROM_CORR_QC_SPARE_0_ROW0_LSB, SUBBINB); 
    
    if (SubBinValue & 0x1 << 0) pChipInfoCtxt->aDisabledFeatures[CHIPINFO_PART_GPU] = 1; 
    if (SubBinValue & 0x1 << 1) pChipInfoCtxt->aDisabledFeatures[CHIPINFO_PART_VIDEO] = 1; 
    pChipInfoCtxt->aDisabledFeatures[CHIPINFO_PART_CAMERA] = HWIO_INF(QFPROM_CORR_QC_SPARE_0_ROW1_LSB, CAMERA_UNSUPPORTED_FEATURE);
    if (SubBinValue & 0x1 << 3) pChipInfoCtxt->aDisabledFeatures[CHIPINFO_PART_DISPLAY] = 1; 
  }

  /*
   * Group C: Modem
   *
   * SUB_BINC[0] - Modem disabled
   * SUB_BINC[1] - WLAN  disabled 
   * SUB_BINC[2] - NAV   disabled
   * SUB_BINC[3] - Reserved
   * SUB_BINC[4] - sub-binning for bin C enabled.
   * But currently in Divar using SUB_BINC[1] is  reserved. 
   * If SUB_BINC[4] = 0 or SUB_BINC[2]= 1 or SUB_BINC[0] = 1 then SW interprets 
   * MODEM is disabled
   */
  if (DisabledBins & CHIPINFO_SUBBIN_GROUP('C'))
  {
    SubBinValue = HWIO_INF(QFPROM_CORR_QC_SPARE_0_ROW0_LSB, SUBBINC); 

    pChipInfoCtxt->aDisabledFeatures[CHIPINFO_PART_MODEM] = HWIO_INF(QFPROM_CORR_QC_SPARE_0_ROW1_MSB, MODEM_UNSUPPORTED_FEATURE);
    if (SubBinValue & 0x1 << 1) pChipInfoCtxt->aDisabledFeatures[CHIPINFO_PART_WLAN] = 1;
    if (SubBinValue & 0x1 << 2) pChipInfoCtxt->aDisabledFeatures[CHIPINFO_PART_NAV] = 1;
  }


    /*
   * Group D: Others
   * SUB_BIND[0] - NSP disabled (NSP == CDSP with an integrated NPU)
   * SUB_BIND[1] - Sensors disabled
   * SUB_BIND[2] - Audio disabled
   * SUB_BIND[3] - EVA disabled
   * SUB_BIND[4] - sub-binning for bin D enabled.
     */

  if (DisabledBins & CHIPINFO_SUBBIN_GROUP('D'))
  {
    SubBinValue = HWIO_INF(QFPROM_CORR_QC_SPARE_0_ROW0_LSB, SUBBIND); 
   
    pChipInfoCtxt->aDisabledFeatures[CHIPINFO_PART_NSP] = HWIO_INF(QFPROM_CORR_QC_SPARE_0_ROW1_LSB, NSP_UNSUPPORTED_FEATURE);
    if (SubBinValue & 0x1 << 1) pChipInfoCtxt->aDisabledFeatures[CHIPINFO_PART_SENSORS] = 1;
    if (SubBinValue & 0x1 << 2) pChipInfoCtxt->aDisabledFeatures[CHIPINFO_PART_AUDIO] = 1;
    if (SubBinValue & 0x1 << 3) pChipInfoCtxt->aDisabledFeatures[CHIPINFO_PART_EVA] = 1;
  }
}

