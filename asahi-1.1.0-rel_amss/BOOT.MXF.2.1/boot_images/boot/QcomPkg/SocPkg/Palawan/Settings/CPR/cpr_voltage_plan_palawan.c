/*******************************************************************************
 *
 * Copyright (c) 2024 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * THIS IS AUTO-GENERATED CPR CONFIG FILE FOR palawan.
 *
 * DateTime: 2024/04/03 06:42:37
 *
 *******************************************************************************/
#include "cpr_data.h"
#include "cpr_image_target_init.h"
#include "cpr_target_hwio.h"


//hash value of Voltage Plan file (extracted all cell values)
static char voltage_plan_hash_value[] = "AE15B084116370D2697DB104A1813977";


/*******************************************************************************
********************************************************************************
**
** Voltage Plan Data
**
********************************************************************************
********************************************************************************/

static cpr_fuse_data  fuses_0 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_margin_cfg margins_224090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -9000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   -5000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_11315010313 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  182 },
                                      { .ro =  9, .quotient =  185 },
                                      { .ro = 14, .quotient =  286 },
                                      { .ro = 15, .quotient =  183 } },
};


static cpr_fuse_data  fuses_4437284000 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_218090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -19000, .closedLoop =   45000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   -7000, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3204587272 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  297 },
                                      { .ro =  9, .quotient =  301 },
                                      { .ro = 15, .quotient =  301 } },
};


static cpr_fuse_data  fuses_7324319380 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_152090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -34000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -30000, .closedLoop =   33000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_4106946757 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  403 },
                                      { .ro =  9, .quotient =  410 },
                                      { .ro = 15, .quotient =  415 } },
};


static cpr_fuse_data  fuses_2731049041 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION12, CPR0_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_296090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -15000, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -23000, .closedLoop =   37000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_6619612078 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  505 },
                                      { .ro =  9, .quotient =  511 },
                                      { .ro = 15, .quotient =  512 } },
};


static cpr_fuse_data  fuses_6208117669 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR0_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_206090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -43000, .closedLoop =   45000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -55000, .closedLoop =   32000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_6177773018 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  601 },
                                      { .ro =  9, .quotient =  619 },
                                      { .ro = 15, .quotient =  626 } },
};


static cpr_fuse_data  fuses_2880129911 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR0_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_192090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -40000, .closedLoop =   46000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -52000, .closedLoop =   21000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_2370680913 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  684 },
                                      { .ro =  9, .quotient =  711 },
                                      { .ro = 15, .quotient =  724 } },
};


static cpr_fuse_data  fuses_1200101346 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR0_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_144090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -63000, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -63000, .closedLoop =   10000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_5173431276 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  821 },
                                      { .ro =  9, .quotient =  860 },
                                      { .ro = 15, .quotient =  888 } },
};


static cpr_fuse_data  fuses_4099729697 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR0_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_kv_cfg  kvs_6066767871 =
{
    .count = 4,
    .kvs   = (cpr_kv[]) { { .ro =  8, .kv =  294 },
                                { .ro =  9, .kv =  296 },
                                { .ro = 14, .kv =  322 },
                                { .ro = 15, .kv =  307 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_17679667341 =
{
    .modesCount      = 8,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_6066767871,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 352000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_4437284000, .quotients = &quotients_11315010313, .margins = &margins_224090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_7324319380, .quotients = &quotients_3204587272, .margins = &margins_218090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_2731049041, .quotients = &quotients_4106946757, .margins = &margins_152090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_6208117669, .quotients = &quotients_6619612078, .margins = &margins_296090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_2880129911, .quotients = &quotients_6177773018, .margins = &margins_206090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  688000, .freq =       0, .interplEnabled = 30} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_1200101346, .quotients = &quotients_2370680913, .margins = &margins_192090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  716000, .freq =       0, .interplEnabled = 57} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_4099729697, .quotients = &quotients_5173431276, .margins = &margins_144090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_version  ver_ANY_1_0_1_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(1,0), .max = CPR_CHIPINFO_VERSION(1,255) };


static cpr_margin_cfg margins_356090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -8000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   32000, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3497487807 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  230 } },
};


static cpr_fuse_data  fuses_4861723185 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR2_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_368090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    4000, .closedLoop =   75000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   24000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3672117569 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  286 } },
};


static cpr_fuse_data  fuses_3647994843 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR2_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_370090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -6000, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   24000, .closedLoop =   65000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3785471894 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  414 } },
};


static cpr_fuse_data  fuses_3193954134 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR2_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR2_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_294090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -21000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    5000, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_57719879 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  543 } },
};


static cpr_fuse_data  fuses_316863594 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR2_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_305090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -23000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   10000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_683300777 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  594 } },
};


static cpr_fuse_data  fuses_5447391691 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR2_TARG_VOLT_SVSL2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR2_TARG_VOLT_OFFSET_SVSL2) } } },
};


static cpr_margin_cfg margins_354090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -26000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_3897927467 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  645 } },
};


static cpr_fuse_data  fuses_1795303972 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR2_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_323090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -35000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   45000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_2896600840 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  764 } },
};


static cpr_fuse_data  fuses_2251246530 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR2_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_249090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -39000, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -30000, .closedLoop =   25000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_1240774937 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  866 } },
};


static cpr_fuse_data  fuses_4044750710 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR2_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_125090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -33000, .closedLoop =   49000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -60000, .closedLoop =  -15000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_175100294 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient = 1037 } },
};


static cpr_fuse_data  fuses_6549929555 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR2_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR2_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_margin_cfg margins_179090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -33000, .closedLoop =   49000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -46000, .closedLoop =    5000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_536090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   38000, .closedLoop =  114000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   10000, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_4163065587 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR2_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR2_TARG_VOLT_OFFSET_TURL2) } } },
};


static cpr_margin_cfg margins_624090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   38000, .closedLoop =  114000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   38000, .closedLoop =   85000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_3645704597 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR2_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR2_TARG_VOLT_OFFSET_TURL3) } } },
};


static cpr_kv_cfg  kvs_13312145833 =
{
    .count = 6,
    .kvs   = (cpr_kv[]) { { .ro =  3, .kv =  336 },
                                { .ro =  6, .kv =  314 },
                                { .ro =  7, .kv =  424 },
                                { .ro = 10, .kv =  407 },
                                { .ro = 14, .kv =  322 },
                                { .ro = 15, .kv =  308 } },
};


/*
 * GFX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_31134772738 =
{
    .modesCount      = 12,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_13312145833,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L0,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L2,
                                                    CPR_VOLTAGE_MODE_TURBO_L3 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_4861723185, .quotients = &quotients_3497487807, .margins = &margins_356090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  516000, .freq =  255000, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =  180000, .fuses = &fuses_3647994843, .quotients = &quotients_3672117569, .margins = &margins_368090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  528000, .freq =  435000, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =   65000, .fuses = &fuses_3193954134, .quotients = &quotients_3785471894, .margins = &margins_370090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  540000, .freq =  500000, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =  133000, .fuses = &fuses_316863594, .quotients = &quotients_57719879, .margins = &margins_294090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  596000, .freq =  633000, .interplEnabled = 71} } },

        // SVS_L2
        {.fref = 704000, .freqDelta =   51000, .fuses = &fuses_5447391691, .quotients = &quotients_683300777, .margins = &margins_305090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  612000, .freq =  684000, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =   52000, .fuses = &fuses_1795303972, .quotients = &quotients_3897927467, .margins = &margins_354090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  632000, .freq =  736000, .interplEnabled = 15} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =   99000, .fuses = &fuses_2251246530, .quotients = &quotients_2896600840, .margins = &margins_323090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  660000, .freq =  835000, .interplEnabled = 41} } },

        // TURBO
        {.fref = 800000, .freqDelta =   65000, .fuses = &fuses_4044750710, .quotients = &quotients_1240774937, .margins = &margins_249090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  688000, .freq =  900000, .interplEnabled = 63} } },

        // TURBO_L0
        {.fref = 856000, .freqDelta =   50000, .fuses = &fuses_6549929555, .quotients = &quotients_175100294, .margins = &margins_125090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  732000, .freq =  950000, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =   50000, .fuses = &fuses_6549929555, .quotients = &quotients_175100294, .margins = &margins_179090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  732000, .freq = 1000000, .interplEnabled = 0} } },

        // TURBO_L2
        {.fref = 856000, .freqDelta =  100000, .fuses = &fuses_4163065587, .quotients = &quotients_175100294, .margins = &margins_536090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  732000, .freq = 1100000, .interplEnabled = 0} } },

        // TURBO_L3
        {.fref = 856000, .freqDelta =   52000, .fuses = &fuses_3645704597, .quotients = &quotients_175100294, .margins = &margins_624090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  732000, .freq = 1152000, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_90 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


static cpr_margin_cfg margins_10004 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -10000, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_2495965546 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR3_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_2244135014 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR3_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_876138120 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR3_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * VDDA Voltage Plan
 */
static cpr_voltage_plan voltage_plan_13614602658 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_MIN_SVS,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 352000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // MIN_SVS
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_90,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 704000, .freqDelta =       0, .fuses = &fuses_2495965546, .quotients = NULL, .margins = &margins_10004,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  688000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_90,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_2244135014, .quotients = NULL, .margins = &margins_10004,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_90,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 892000, .freqDelta =       0, .fuses = &fuses_876138120, .quotients = NULL, .margins = &margins_10004,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  892000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_90,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =       0, .floor =       0, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_fuse_data  fuses_1214727534 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_324090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   53000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   49000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_8980688263 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  423 },
                                      { .ro =  5, .quotient =  433 },
                                      { .ro = 12, .quotient =  837 },
                                      { .ro = 15, .quotient =  437 } },
};


static cpr_fuse_data  fuses_6216256256 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR4_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_fuse_data  fuses_184945056 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_376090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   62000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_7991708629 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  580 },
                                      { .ro =  5, .quotient =  586 },
                                      { .ro = 12, .quotient = 1133 },
                                      { .ro = 15, .quotient =  599 } },
};


static cpr_fuse_data  fuses_1683797650 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR4_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_margin_cfg margins_458090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   65000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_9663451565 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  580 },
                                      { .ro =  5, .quotient =  586 },
                                      { .ro = 11, .quotient = 1441 },
                                      { .ro = 12, .quotient = 1133 },
                                      { .ro = 15, .quotient =  599 } },
};


static cpr_fuse_data  fuses_3363652595 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR4_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR4_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_424090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -15000, .closedLoop =   65000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -15000, .closedLoop =   62000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_13644073477 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  626 },
                                      { .ro =  5, .quotient =  631 },
                                      { .ro = 11, .quotient = 1529 },
                                      { .ro = 12, .quotient = 1221 },
                                      { .ro = 14, .quotient =  804 },
                                      { .ro = 15, .quotient =  646 } },
};


static cpr_fuse_data  fuses_3662504792 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR4_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_474090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   69000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   68000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7767440343 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  684 },
                                      { .ro =  5, .quotient =  711 },
                                      { .ro = 11, .quotient = 1649 },
                                      { .ro = 12, .quotient = 1355 },
                                      { .ro = 14, .quotient =  890 },
                                      { .ro = 15, .quotient =  738 } },
};


static cpr_fuse_data  fuses_6008565036 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR4_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR4_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_430090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =   70000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -20000, .closedLoop =   65000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_11351112513 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  801 },
                                      { .ro =  5, .quotient =  804 },
                                      { .ro = 11, .quotient = 1850 },
                                      { .ro = 12, .quotient = 1546 },
                                      { .ro = 14, .quotient =  991 },
                                      { .ro = 15, .quotient =  830 } },
};


static cpr_fuse_data  fuses_5309333480 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR4_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR4_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_kv_cfg  kvs_10553381205 =
{
    .count = 6,
    .kvs   = (cpr_kv[]) { { .ro =  4, .kv =  296 },
                                { .ro =  5, .kv =  301 },
                                { .ro = 11, .kv =  581 },
                                { .ro = 12, .kv =  572 },
                                { .ro = 14, .kv =  323 },
                                { .ro = 15, .kv =  311 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_22477442505 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_10553381205,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 524000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  524000, .floor =  524000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_1214727534, .quotients = NULL, .margins = &margins_90,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  716000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_6216256256, .quotients = &quotients_8980688263, .margins = &margins_324090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_184945056, .quotients = NULL, .margins = &margins_90,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L2
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_1683797650, .quotients = &quotients_7991708629, .margins = &margins_376090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3363652595, .quotients = &quotients_9663451565, .margins = &margins_458090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_3662504792, .quotients = &quotients_13644073477, .margins = &margins_424090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  752000, .freq =       0, .interplEnabled = 33} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_6008565036, .quotients = &quotients_7767440343, .margins = &margins_474090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_5309333480, .quotients = &quotients_11351112513, .margins = &margins_430090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_fuse_data  fuses_3592987974 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_344090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_5587347753 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR5_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR5_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_fuse_data  fuses_2937316597 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR5_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_364090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_2096845498 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR5_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_margin_cfg margins_428090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   57000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   57000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_4809315519 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR5_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR5_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_390090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -15000, .closedLoop =   55000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -15000, .closedLoop =   55000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_1883620139 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR5_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_fuse_data  fuses_1162609838 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR5_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR5_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_364091 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =   51000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -20000, .closedLoop =   51000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_5693064382 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR5_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR5_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_kv_cfg  kvs_11342356683 =
{
    .count = 6,
    .kvs   = (cpr_kv[]) { { .ro =  4, .kv =  296 },
                                { .ro =  5, .kv =  301 },
                                { .ro = 11, .kv =  581 },
                                { .ro = 12, .kv =  572 },
                                { .ro = 14, .kv =  323 },
                                { .ro = 15, .kv =  310 } },
};


/*
 * MXC Voltage Plan
 */
static cpr_voltage_plan voltage_plan_21306516993 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_11342356683,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 524000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  524000, .floor =  524000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_3592987974, .quotients = NULL, .margins = &margins_90,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  716000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_5587347753, .quotients = &quotients_8980688263, .margins = &margins_344090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_2937316597, .quotients = NULL, .margins = &margins_90,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L2
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_2096845498, .quotients = &quotients_7991708629, .margins = &margins_364090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4809315519, .quotients = &quotients_9663451565, .margins = &margins_428090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_1883620139, .quotients = &quotients_13644073477, .margins = &margins_390090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  752000, .freq =       0, .interplEnabled = 33} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_1162609838, .quotients = &quotients_7767440343, .margins = &margins_428090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_5693064382, .quotients = &quotients_11351112513, .margins = &margins_364091,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_5004 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -15000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_3701143162 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR6_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_margin_cfg margins_4 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -20000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -20000, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_3402849139 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR6_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * LPI_MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_12304353501 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 524000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  552000, .floor =  524000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_90,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_90,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_90,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_90,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3701143162, .quotients = NULL, .margins = &margins_5004,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_3402849139, .quotients = NULL, .margins = &margins_4,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_310090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =       0, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_15349037847 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  345 },
                                      { .ro =  6, .quotient =  237 },
                                      { .ro = 10, .quotient =  249 },
                                      { .ro = 12, .quotient =  492 },
                                      { .ro = 14, .quotient =  230 },
                                      { .ro = 15, .quotient =  142 } },
};


static cpr_fuse_data  fuses_6033624882 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR7_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_227090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =    3000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   10000, .closedLoop =   32000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_16014405175 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  415 },
                                      { .ro =  6, .quotient =  298 },
                                      { .ro = 10, .quotient =  323 },
                                      { .ro = 12, .quotient =  583 },
                                      { .ro = 14, .quotient =  286 },
                                      { .ro = 15, .quotient =  183 } },
};


static cpr_fuse_data  fuses_2813987257 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_199090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -15000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =    8000, .closedLoop =   28000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_12332223049 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  554 },
                                      { .ro =  6, .quotient =  427 },
                                      { .ro = 10, .quotient =  494 },
                                      { .ro = 12, .quotient =  753 },
                                      { .ro = 14, .quotient =  414 },
                                      { .ro = 15, .quotient =  301 } },
};


static cpr_fuse_data  fuses_4335291917 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_112090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -46000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -40000, .closedLoop =   20000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3510451032 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  689 },
                                      { .ro =  6, .quotient =  555 },
                                      { .ro = 14, .quotient =  543 } },
};


static cpr_fuse_data  fuses_3732569836 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_213090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -43000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -32000, .closedLoop =   25000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_3003848603 =
{
    .count = 2,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  803 },
                                      { .ro =  6, .quotient =  659 } },
};


static cpr_fuse_data  fuses_3376468245 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR7_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_204090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -44000, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -34000, .closedLoop =   16000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_1998726999 =
{
    .count = 2,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  997 },
                                      { .ro =  6, .quotient =  875 } },
};


static cpr_fuse_data  fuses_4764881353 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR7_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR7_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_11860701951 =
{
    .count = 6,
    .kvs   = (cpr_kv[]) { { .ro =  3, .kv =  334 },
                                { .ro =  6, .kv =  315 },
                                { .ro = 10, .kv =  409 },
                                { .ro = 12, .kv =  411 },
                                { .ro = 14, .kv =  324 },
                                { .ro = 15, .kv =  313 } },
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_11125400189 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_11860701951,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 352000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_6033624882, .quotients = &quotients_15349037847, .margins = &margins_310090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  520000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 576000, .freqDelta =       0, .fuses = &fuses_2813987257, .quotients = &quotients_16014405175, .margins = &margins_227090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 624000, .freqDelta =       0, .fuses = &fuses_4335291917, .quotients = &quotients_12332223049, .margins = &margins_199090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 680000, .freqDelta =       0, .fuses = &fuses_3732569836, .quotients = &quotients_3510451032, .margins = &margins_112090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_3376468245, .quotients = &quotients_3003848603, .margins = &margins_213090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  664000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4764881353, .quotients = &quotients_1998726999, .margins = &margins_204090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  720000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_238090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -4000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   -4000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_11757521726 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  219 },
                                      { .ro =  8, .quotient =  139 },
                                      { .ro =  9, .quotient =  142 },
                                      { .ro = 14, .quotient =  230 } },
};


static cpr_fuse_data  fuses_3432308697 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR1_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR1_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_240090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -9000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   -5000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_13615445468 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  272 },
                                      { .ro =  8, .quotient =  182 },
                                      { .ro =  9, .quotient =  185 },
                                      { .ro = 14, .quotient =  286 } },
};


static cpr_fuse_data  fuses_2941192896 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR1_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_248090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -11000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   -3000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_8653970376 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  554 },
                                      { .ro =  6, .quotient =  427 },
                                      { .ro = 12, .quotient =  753 },
                                      { .ro = 14, .quotient =  414 } },
};


static cpr_fuse_data  fuses_7162440877 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR1_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR1_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_166090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -34000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -22000, .closedLoop =   36000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_6934214257 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  689 },
                                      { .ro =  6, .quotient =  555 },
                                      { .ro = 12, .quotient =  914 },
                                      { .ro = 14, .quotient =  543 } },
};


static cpr_fuse_data  fuses_3736573214 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR1_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_316090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -23000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   -7000, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7787670893 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  803 },
                                      { .ro =  6, .quotient =  659 },
                                      { .ro = 12, .quotient = 1059 },
                                      { .ro = 14, .quotient =  645 } },
};


static cpr_fuse_data  fuses_2539577410 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR1_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR1_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_284090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -25000, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -21000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7514223009 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  908 },
                                      { .ro =  6, .quotient =  775 },
                                      { .ro = 12, .quotient = 1177 },
                                      { .ro = 14, .quotient =  764 } },
};


static cpr_fuse_data  fuses_5304261981 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR1_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR1_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_kv_cfg  kvs_12331205623 =
{
    .count = 7,
    .kvs   = (cpr_kv[]) { { .ro =  3, .kv =  334 },
                                { .ro =  5, .kv =  309 },
                                { .ro =  6, .kv =  314 },
                                { .ro =  8, .kv =  297 },
                                { .ro =  9, .kv =  302 },
                                { .ro = 12, .kv =  410 },
                                { .ro = 14, .kv =  323 } },
};


/*
 * MSS Voltage Plan
 */
static cpr_voltage_plan voltage_plan_11216123064 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_12331205623,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_3432308697, .quotients = &quotients_11757521726, .margins = &margins_238090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_2941192896, .quotients = &quotients_13615445468, .margins = &margins_240090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_7162440877, .quotients = &quotients_8653970376, .margins = &margins_248090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3736573214, .quotients = &quotients_6934214257, .margins = &margins_166090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_2539577410, .quotients = &quotients_7787670893, .margins = &margins_316090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_5304261981, .quotients = &quotients_7514223009, .margins = &margins_284090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  688000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_215090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -17000, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -16000, .closedLoop =   39000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_16512307913 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  345 },
                                      { .ro =  6, .quotient =  237 },
                                      { .ro =  8, .quotient =  139 },
                                      { .ro =  9, .quotient =  142 },
                                      { .ro = 14, .quotient =  230 },
                                      { .ro = 15, .quotient =  142 } },
};


static cpr_fuse_data  fuses_782121761 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION28, CPR9_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION31, CPR9_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_223090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -13000, .closedLoop =   46000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -12000, .closedLoop =   43000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_17317289554 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  415 },
                                      { .ro =  6, .quotient =  298 },
                                      { .ro =  8, .quotient =  182 },
                                      { .ro =  9, .quotient =  185 },
                                      { .ro = 14, .quotient =  286 },
                                      { .ro = 15, .quotient =  183 } },
};


static cpr_fuse_data  fuses_369505750 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION30, CPR9_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_173090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -27000, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -22000, .closedLoop =   26000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_4346522865 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR9_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION30, CPR9_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_129090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -30000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -29000, .closedLoop =   19000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_1567852918 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION29, CPR9_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_315090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -31000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =   -6000, .closedLoop =   53000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_3875469081 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR9_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION29, CPR9_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_321090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -11000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -22000, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_2215691680 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION29, CPR9_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_275090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -8000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -23000, .closedLoop =   34000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_5159979341 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  997 },
                                      { .ro =  6, .quotient =  875 },
                                      { .ro = 12, .quotient = 1278 },
                                      { .ro = 14, .quotient =  866 } },
};


static cpr_fuse_data  fuses_2737306148 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION29, CPR9_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_185090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -27000, .closedLoop =   47000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -46000, .closedLoop =    7000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_5120286518 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient = 1146 },
                                      { .ro =  6, .quotient = 1027 },
                                      { .ro = 12, .quotient = 1430 },
                                      { .ro = 14, .quotient = 1037 } },
};


static cpr_fuse_data  fuses_5967927017 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR9_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR9_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_kv_cfg  kvs_10232347347 =
{
    .count = 7,
    .kvs   = (cpr_kv[]) { { .ro =  3, .kv =  334 },
                                { .ro =  6, .kv =  314 },
                                { .ro =  8, .kv =  295 },
                                { .ro =  9, .kv =  297 },
                                { .ro = 12, .kv =  411 },
                                { .ro = 14, .kv =  323 },
                                { .ro = 15, .kv =  308 } },
};


/*
 * NSP Voltage Plan
 */
static cpr_voltage_plan voltage_plan_12384832881 =
{
    .modesCount      = 8,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_10232347347,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_782121761, .quotients = &quotients_16512307913, .margins = &margins_215090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_369505750, .quotients = &quotients_17317289554, .margins = &margins_223090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4346522865, .quotients = &quotients_8653970376, .margins = &margins_173090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1567852918, .quotients = &quotients_6934214257, .margins = &margins_129090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  624000, .freq =       0, .interplEnabled = 40} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_3875469081, .quotients = &quotients_7787670893, .margins = &margins_315090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_2215691680, .quotients = &quotients_7514223009, .margins = &margins_321090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  688000, .freq =       0, .interplEnabled = 30} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_2737306148, .quotients = &quotients_5159979341, .margins = &margins_275090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  716000, .freq =       0, .interplEnabled = 57} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_5967927017, .quotients = &quotients_5120286518, .margins = &margins_185090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_237090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =   -9000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -16000, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_11113658126 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  142 },
                                      { .ro = 14, .quotient =  230 },
                                      { .ro = 15, .quotient =  142 } },
};


static cpr_fuse_data  fuses_3901141997 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR8_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR8_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_margin_cfg margins_167090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -17000, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -24000, .closedLoop =   27000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_7318203771 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  185 },
                                      { .ro = 14, .quotient =  286 },
                                      { .ro = 15, .quotient =  183 } },
};


static cpr_fuse_data  fuses_2964503462 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR8_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_margin_cfg margins_179091 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -15000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -22000, .closedLoop =   25000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_4757831813 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  301 },
                                      { .ro = 14, .quotient =  414 },
                                      { .ro = 15, .quotient =  301 } },
};


static cpr_fuse_data  fuses_3586405317 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR8_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION27, CPR8_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_135090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -42000, .closedLoop =   45000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -53000, .closedLoop =   35000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_2701963025 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  410 },
                                      { .ro = 14, .quotient =  543 },
                                      { .ro = 15, .quotient =  415 } },
};


static cpr_fuse_data  fuses_3580562569 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR8_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_215091 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -39000, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -46000, .closedLoop =   25000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7303729120 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  511 },
                                      { .ro = 14, .quotient =  645 },
                                      { .ro = 15, .quotient =  512 } },
};


static cpr_fuse_data  fuses_3279492350 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR8_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR8_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_quotient_cfg  quotients_5942957097 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  619 },
                                      { .ro = 14, .quotient =  764 },
                                      { .ro = 15, .quotient =  626 } },
};


static cpr_fuse_data  fuses_2628446287 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR8_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_97090 = {
    .count = 3,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 0, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 1, .cprRevMax = 1, .openLoop =  -72000, .closedLoop =   43000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 2, .cprRevMax = 2, .openLoop =  -87000, .closedLoop =   10000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_3576402732 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  711 },
                                      { .ro = 14, .quotient =  866 },
                                      { .ro = 15, .quotient =  724 } },
};


static cpr_fuse_data  fuses_1829879262 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION25, CPR8_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION26, CPR8_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_4055158797 =
{
    .count = 3,
    .kvs   = (cpr_kv[]) { { .ro =  9, .kv =  300 },
                                { .ro = 14, .kv =  323 },
                                { .ro = 15, .kv =  311 } },
};


/*
 * MM Voltage Plan
 */
static cpr_voltage_plan voltage_plan_13995125003 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_4055158797,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_3901141997, .quotients = &quotients_11113658126, .margins = &margins_237090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_2964503462, .quotients = &quotients_7318203771, .margins = &margins_167090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_3586405317, .quotients = &quotients_4757831813, .margins = &margins_179091,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3580562569, .quotients = &quotients_2701963025, .margins = &margins_135090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_3279492350, .quotients = &quotients_7303729120, .margins = &margins_215091,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_2628446287, .quotients = &quotients_5942957097, .margins = &margins_215091,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  688000, .freq =       0, .interplEnabled = 54} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_1829879262, .quotients = &quotients_3576402732, .margins = &margins_97090,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_2053 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 1, .vpIdMax = 1,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


/*
 * WMSS_CX_1 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_7505828871 =
{
    .modesCount      = 4,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2053,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  612000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 588000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2053,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 668000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2053,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  724000, .floor =  596000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2053,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  868000, .floor =  712000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * WMSS_MX_1 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_4951874247 =
{
    .modesCount      = 2,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 488000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  488000, .floor =  488000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 850000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2053,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  912000, .floor =  850000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * NAV_LDO Voltage Plan
 */
static cpr_voltage_plan voltage_plan_3863315186 =
{
    .modesCount      = 1,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * Aging configs
 */

static cpr_aging_cfg  aging_cfg_cx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 10,
    .kv                   = 110,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8B4C & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 10, (1<<17) | (1<<16) | (1<<15) | (1<<14) | (1<<13) | (1<<12) | (1<<11) | (1<<10)} } }
};


static cpr_aging_cfg  aging_cfg_gfx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 0,
    .kv                   = 110,
    .scalingFactor        = 15,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8B60 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<7) | (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0)} } }
};


static cpr_aging_cfg  aging_cfg_mx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 1,
    .kv                   = 112,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BAC & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 6, (1<<13) | (1<<12) | (1<<11) | (1<<10) | (1<<9) | (1<<8) | (1<<7) | (1<<6)} } }
};


static cpr_aging_cfg  aging_cfg_lpi_cx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 3,
    .kv                   = 119,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8B7C & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 6, (1<<13) | (1<<12) | (1<<11) | (1<<10) | (1<<9) | (1<<8) | (1<<7) | (1<<6)} } }
};


static cpr_aging_cfg  aging_cfg_mss =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_NOMINAL_L1,
    .sensorID             = 10,
    .kv                   = 124,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8B4C & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<31) | (1<<30) | (1<<29) | (1<<28) | (1<<27) | (1<<26) | (1<<25) | (1<<24)} } }
};


static cpr_aging_cfg  aging_cfg_nsp =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 0,
    .kv                   = 111,
    .scalingFactor        = 15,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8B90 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 10, (1<<17) | (1<<16) | (1<<15) | (1<<14) | (1<<13) | (1<<12) | (1<<11) | (1<<10)} } }
};


static cpr_aging_cfg  aging_cfg_mm =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 0,
    .kv                   = 118,
    .scalingFactor        = 15,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8B88 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 0, (1<<7) | (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0)} } }
};


/*
 * Versioned Voltage Plans
 */

static cpr_versioned_voltage_plan cx_vvp = {
    .rail     = CPR_RAIL_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_17679667341 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_cx
};


static cpr_versioned_voltage_plan gfx_vvp = {
    .rail     = CPR_RAIL_GFX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_31134772738 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_gfx
};


static cpr_versioned_voltage_plan vdda_vvp = {
    .rail     = CPR_RAIL_VDDA,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_13614602658 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan mx_vvp = {
    .rail     = CPR_RAIL_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_22477442505 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mx
};


static cpr_versioned_voltage_plan mxc_vvp = {
    .rail     = CPR_RAIL_MXC,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_21306516993 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_mx_vvp = {
    .rail     = CPR_RAIL_LPI_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_12304353501 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_cx_vvp = {
    .rail     = CPR_RAIL_LPI_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_11125400189 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_lpi_cx
};


static cpr_versioned_voltage_plan mss_vvp = {
    .rail     = CPR_RAIL_MSS,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_11216123064 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mss
};


static cpr_versioned_voltage_plan nsp_vvp = {
    .rail     = CPR_RAIL_NSP,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_12384832881 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_nsp
};


static cpr_versioned_voltage_plan mm_vvp = {
    .rail     = CPR_RAIL_MM,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_13995125003 },
     },
    .count    = 1,
    .agingCfg = &aging_cfg_mm
};


static cpr_versioned_voltage_plan wmss_cx_1_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_1,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_7505828871 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_2_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_2,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_7505828871 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_mx_1_vvp = {
    .rail     = CPR_RAIL_WMSS_MX_1,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_4951874247 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_mx_2_vvp = {
    .rail     = CPR_RAIL_WMSS_MX_2,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_4951874247 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan nav_ldo_vvp = {
    .rail     = CPR_RAIL_NAV_LDO,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_3863315186 },
     },
    .count    = 1,
    .agingCfg = NULL
};

/*******************************************************************************
********************************************************************************
**
** Enablement Config Data
**
********************************************************************************
********************************************************************************/

/*
 * CPR Controller Thread Config
 */

static cpr_hal_thread_cfg mss_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27 },
    .sensorsCount = 28,
};


static cpr_hal_thread  mss_thread = {
    .id   = 0,
    .cfg  = &mss_thread_cfg,
};


static cpr_hal_thread_cfg cx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42 },
    .sensorsCount = 43,
};


static cpr_hal_thread  cx_thread = {
    .id   = 0,
    .cfg  = &cx_thread_cfg,
};


static cpr_hal_thread_cfg gfx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 },
    .sensorsCount = 24,
};


static cpr_hal_thread  gfx_thread = {
    .id   = 0,
    .cfg  = &gfx_thread_cfg,
};


static cpr_hal_thread_cfg lpi_cx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3 },
    .sensorsCount = 4,
};


static cpr_hal_thread  lpi_cx_thread = {
    .id   = 0,
    .cfg  = &lpi_cx_thread_cfg,
};


static cpr_hal_thread_cfg mm_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27 },
    .sensorsCount = 28,
};


static cpr_hal_thread  mm_thread = {
    .id   = 0,
    .cfg  = &mm_thread_cfg,
};


static cpr_hal_thread_cfg mx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84 },
    .sensorsCount = 85,
};


static cpr_hal_thread  mx_thread = {
    .id   = 0,
    .cfg  = &mx_thread_cfg,
};


static cpr_hal_thread_cfg mxc_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46 },
    .sensorsCount = 47,
};


static cpr_hal_thread  mxc_thread = {
    .id   = 0,
    .cfg  = &mxc_thread_cfg,
};


static cpr_hal_thread_cfg nsp_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9 },
    .sensorsCount = 10,
};


static cpr_hal_thread  nsp_thread = {
    .id   = 0,
    .cfg  = &nsp_thread_cfg,
};


/*
 * CPR Controller Config
 */

static cpr_hal_controller_cfg cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 13,
    .sensorsTotal        = 28,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  cpr3_controller = {
    .base                = 0x2b580000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &mss_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg cx_cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 12,
    .sensorsTotal        = 43,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = (uint8[]){ 0,1,2,3,4,5,6,14,26,30,32,33,34 },
    .disableSensorsCount = 13,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  cx_cpr3_controller = {
    .base                = 0x628000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &cx_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &cx_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg gpu_cpr_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 19,
    .sensorsTotal        = 24,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  gpu_cpr_controller = {
    .base                = 0x3d9a000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &gpu_cpr_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &gfx_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg lpass_cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 13,
    .sensorsTotal        = 4,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  lpass_cpr3_controller = {
    .base                = 0x6e70000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &lpass_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &lpi_cx_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg mmcx_cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 13,
    .sensorsTotal        = 28,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  mmcx_cpr3_controller = {
    .base                = 0x630000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &mmcx_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &mm_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg mx_cpr3_controller_cfg = {
    .stepQuotMin         = 7,
    .stepQuotMax         = 13,
    .sensorsTotal        = 85,
    .bypassSensors       = (uint8[]){ 24,25,31,32,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84 },
    .bypassSensorsCount  = 51,
    .disableSensors      = (uint8[]){ 16,19,20,21,22 },
    .disableSensorsCount = 5,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  mx_cpr3_controller = {
    .base                = 0x638000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &mx_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &mx_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg mxc_cpr3_controller_cfg = {
    .stepQuotMin         = 7,
    .stepQuotMax         = 13,
    .sensorsTotal        = 47,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  mxc_cpr3_controller = {
    .base                = 0x62c000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &mxc_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &mxc_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg nsp_cx_cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 13,
    .sensorsTotal        = 10,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  nsp_cx_cpr3_controller = {
    .base                = 0x63c000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &nsp_cx_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &nsp_thread },
    .threadsCount        = 1,
};


/*
 * HAL Rail Config
 */

static cpr_rail cpr_rail_cx_cfg = {
    .id               = CPR_RAIL_CX,
    .name             = "CX",
    .hal              = { .controller = &cx_cpr3_controller, .thread = &cx_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_gfx_cfg = {
    .id               = CPR_RAIL_GFX,
    .name             = "GFX",
    .hal              = { .controller = &gpu_cpr_controller, .thread = &gfx_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_lpi_cx_cfg = {
    .id               = CPR_RAIL_LPI_CX,
    .name             = "LPI_CX",
    .hal              = { .controller = &lpass_cpr3_controller, .thread = &lpi_cx_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_lpi_mx_cfg = {
    .id               = CPR_RAIL_LPI_MX,
    .name             = "LPI_MX",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_mm_cfg = {
    .id               = CPR_RAIL_MM,
    .name             = "MM",
    .hal              = { .controller = &mmcx_cpr3_controller, .thread = &mm_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_mss_cfg = {
    .id               = CPR_RAIL_MSS,
    .name             = "MSS",
    .hal              = { .controller = &cpr3_controller, .thread = &mss_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_mx_cfg = {
    .id               = CPR_RAIL_MX,
    .name             = "MX",
    .hal              = { .controller = &mx_cpr3_controller, .thread = &mx_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_mxc_cfg = {
    .id               = CPR_RAIL_MXC,
    .name             = "MXC",
    .hal              = { .controller = &mxc_cpr3_controller, .thread = &mxc_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_nav_ldo_cfg = {
    .id               = CPR_RAIL_NAV_LDO,
    .name             = "NAV_LDO",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_nsp_cfg = {
    .id               = CPR_RAIL_NSP,
    .name             = "NSP",
    .hal              = { .controller = &nsp_cx_cpr3_controller, .thread = &nsp_thread },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_vdda_cfg = {
    .id               = CPR_RAIL_VDDA,
    .name             = "VDDA",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_wmss_cx_1_cfg = {
    .id               = CPR_RAIL_WMSS_CX_1,
    .name             = "WMSS_CX_1",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_wmss_cx_2_cfg = {
    .id               = CPR_RAIL_WMSS_CX_2,
    .name             = "WMSS_CX_2",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_wmss_mx_1_cfg = {
    .id               = CPR_RAIL_WMSS_MX_1,
    .name             = "WMSS_MX_1",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


static cpr_rail cpr_rail_wmss_mx_2_cfg = {
    .id               = CPR_RAIL_WMSS_MX_2,
    .name             = "WMSS_MX_2",
    .hal              = { .controller = NULL, .thread = NULL },
    .interruptId      = 0,
    .settleModes      = NULL,
    .settleModesCount = 0,
};


/*
 * Rail Enablement Config
 */

static cpr_enablement cpr_rail_cx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_CX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_gfx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_GFX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_lpi_cx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_LPI_CX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_lpi_mx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_LPI_MX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mm_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MM,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_mss_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MSS,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_mx_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MX,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mxc_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MXC,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_nav_ldo_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_NAV_LDO,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_nsp_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_NSP,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_vdda_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_VDDA,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_wmss_cx_1_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_CX_1,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_2_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_CX_2,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_mx_1_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_MX_1,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_mx_2_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_MX_2,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_misc_cfg misc_cfg = {
    .cprRev = {.count = 1, .data = (struct raw_fuse_data[]) { {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } }
};


cpr_settings cpr_settings_palawan =
{
    .hashValue        = voltage_plan_hash_value,

    .railVVPs         = (cpr_versioned_voltage_plan*[]) { &cx_vvp, &gfx_vvp, &lpi_cx_vvp, &lpi_mx_vvp, &mm_vvp, &mss_vvp, &mx_vvp, &mxc_vvp, &nav_ldo_vvp, &nsp_vvp, &vdda_vvp, &wmss_cx_1_vvp, &wmss_cx_2_vvp, &wmss_mx_1_vvp, &wmss_mx_2_vvp },
    .rails            = (cpr_rail*[]) { &cpr_rail_cx_cfg, &cpr_rail_gfx_cfg, &cpr_rail_lpi_cx_cfg, &cpr_rail_lpi_mx_cfg, &cpr_rail_mm_cfg, &cpr_rail_mss_cfg, &cpr_rail_mx_cfg, &cpr_rail_mxc_cfg, &cpr_rail_nav_ldo_cfg, &cpr_rail_nsp_cfg, &cpr_rail_vdda_cfg, &cpr_rail_wmss_cx_1_cfg, &cpr_rail_wmss_cx_2_cfg, &cpr_rail_wmss_mx_1_cfg, &cpr_rail_wmss_mx_2_cfg },
    .railsCount       = 15,

    .controllers      = (cpr_hal_controller*[]) { &cpr3_controller, &cx_cpr3_controller, &gpu_cpr_controller, &lpass_cpr3_controller, &mmcx_cpr3_controller, &mx_cpr3_controller, &mxc_cpr3_controller, &nsp_cx_cpr3_controller },
    .controllersCount = 8,

    .enablements      = (cpr_enablement*[]) { &cpr_rail_cx_enablement_1_0_1_255, &cpr_rail_gfx_enablement_1_0_1_255, &cpr_rail_lpi_cx_enablement_1_0_1_255, &cpr_rail_lpi_mx_enablement_1_0_1_255, &cpr_rail_mm_enablement_1_0_1_255, &cpr_rail_mss_enablement_1_0_1_255, &cpr_rail_mx_enablement_1_0_1_255, &cpr_rail_mxc_enablement_1_0_1_255, &cpr_rail_nav_ldo_enablement_1_0_1_255, &cpr_rail_nsp_enablement_1_0_1_255, &cpr_rail_vdda_enablement_1_0_1_255, &cpr_rail_wmss_cx_1_enablement_1_0_1_255, &cpr_rail_wmss_cx_2_enablement_1_0_1_255, &cpr_rail_wmss_mx_1_enablement_1_0_1_255, &cpr_rail_wmss_mx_2_enablement_1_0_1_255 },
    .enablementsCount = 15,

    .miscCfg          = &misc_cfg,
};

