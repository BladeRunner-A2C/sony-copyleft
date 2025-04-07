/*******************************************************************************
 *
 * Copyright (c) 2024 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * THIS IS AUTO-GENERATED CPR CONFIG FILE FOR lanai.
 *
 * DateTime: 2024/04/03 06:29:28
 *
 *******************************************************************************/
#include "cpr_data.h"
#include "cpr_image_target_init.h"
#include "cpr_target_hwio.h"


//hash value of Voltage Plan file (extracted all cell values)
static char voltage_plan_hash_value[] = "F5D8BF91EB445459F4FE00F215C5AE4F";


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


static cpr_margin_cfg margins_151040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    4000, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_11315010313 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  182 },
                                      { .ro =  9, .quotient =  185 },
                                      { .ro = 14, .quotient =  286 },
                                      { .ro = 15, .quotient =  183 } },
};


static cpr_fuse_data  fuses_2960628641 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_LSVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION5, CPR0_TARG_VOLT_OFFSET_LSVS) } } },
};


static cpr_margin_cfg margins_173040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_3903873997 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  298 },
                                      { .ro =  9, .quotient =  302 },
                                      { .ro = 15, .quotient =  301 } },
};


static cpr_fuse_data  fuses_8073949460 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION5, CPR0_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_149040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_6021411618 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  404 },
                                      { .ro =  9, .quotient =  410 },
                                      { .ro = 15, .quotient =  415 } },
};


static cpr_fuse_data  fuses_2199882008 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION5, CPR0_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_169040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   -8000, .closedLoop =   50000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_6971872036 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  505 },
                                      { .ro =  9, .quotient =  511 },
                                      { .ro = 15, .quotient =  513 } },
};


static cpr_fuse_data  fuses_5150927558 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION5, CPR0_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_151041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -16000, .closedLoop =   45000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7402694220 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  601 },
                                      { .ro =  9, .quotient =  619 },
                                      { .ro = 15, .quotient =  627 } },
};


static cpr_fuse_data  fuses_1822939800 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION5, CPR0_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_181040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   -8000, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_608733415 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  684 },
                                      { .ro =  9, .quotient =  711 },
                                      { .ro = 15, .quotient =  725 } },
};


static cpr_fuse_data  fuses_2663925107 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION5, CPR0_TARG_VOLT_OFFSET_TUR_4_3), CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_OFFSET_TUR_2_0) } } },
};


static cpr_margin_cfg margins_165040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -16000, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_6330710590 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  822 },
                                      { .ro =  9, .quotient =  861 },
                                      { .ro = 15, .quotient =  889 } },
};


static cpr_fuse_data  fuses_2190787618 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_kv_cfg  kvs_34282829421 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  293 },
                                { .ro =  9, .kv =  296 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  312 },
                                { .ro = 15, .kv =  306 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_22645813518 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_34282829421,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  480000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_2960628641, .quotients = &quotients_11315010313, .margins = &margins_151040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_8073949460, .quotients = &quotients_3903873997, .margins = &margins_173040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_2199882008, .quotients = &quotients_6021411618, .margins = &margins_149040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_5150927558, .quotients = &quotients_6971872036, .margins = &margins_169040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_1822939800, .quotients = &quotients_7402694220, .margins = &margins_151041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  688000, .freq =       0, .interplEnabled = 30} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_2663925107, .quotients = &quotients_608733415, .margins = &margins_181040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 57} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_2190787618, .quotients = &quotients_6330710590, .margins = &margins_165040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  904000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_version  ver_ANY_1_0_1_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(1,0), .max = CPR_CHIPINFO_VERSION(1,255) };


static cpr_margin_cfg margins_197040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   20000, .closedLoop =   70000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_8944658826 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  220 },
                                      { .ro =  8, .quotient =  140 },
                                      { .ro =  9, .quotient =  143 },
                                      { .ro = 14, .quotient =  230 } },
};


static cpr_fuse_data  fuses_771147252 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION6, CPR1_TARG_VOLT_LSVSD1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION7, CPR1_TARG_VOLT_OFFSET_LSVSD1) } } },
};


static cpr_margin_cfg margins_229040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   28000, .closedLoop =   82000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_13615445468 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  5, .quotient =  272 },
                                      { .ro =  8, .quotient =  182 },
                                      { .ro =  9, .quotient =  185 },
                                      { .ro = 14, .quotient =  286 } },
};


static cpr_fuse_data  fuses_484694388 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION7, CPR1_TARG_VOLT_OFFSET_LSVS) } } },
};


static cpr_margin_cfg margins_175040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   65000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_7395994418 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  554 },
                                      { .ro =  6, .quotient =  427 },
                                      { .ro = 12, .quotient =  753 },
                                      { .ro = 14, .quotient =  415 } },
};


static cpr_fuse_data  fuses_4914851277 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION6, CPR1_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION7, CPR1_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_163040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    4000, .closedLoop =   61000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9749052530 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  690 },
                                      { .ro =  6, .quotient =  556 },
                                      { .ro = 12, .quotient =  915 },
                                      { .ro = 14, .quotient =  543 } },
};


static cpr_fuse_data  fuses_4266840937 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION7, CPR1_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_253040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   20000, .closedLoop =   78000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_3880931186 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  804 },
                                      { .ro =  6, .quotient =  659 },
                                      { .ro = 12, .quotient = 1059 },
                                      { .ro = 14, .quotient =  646 } },
};


static cpr_fuse_data  fuses_4586955106 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION6, CPR1_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION7, CPR1_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_271040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   24000, .closedLoop =   85000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_10299494829 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  908 },
                                      { .ro =  6, .quotient =  776 },
                                      { .ro = 12, .quotient = 1177 },
                                      { .ro = 14, .quotient =  765 } },
};


static cpr_fuse_data  fuses_5794072534 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION6, CPR1_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION6, CPR1_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_kv_cfg  kvs_34315280920 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  339 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =  289 },
                                { .ro =  6, .kv =  322 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  247 },
                                { .ro =  9, .kv =  252 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  391 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  322 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * MSS Voltage Plan
 */
static cpr_voltage_plan voltage_plan_10193013177 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_34315280920,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_771147252, .quotients = &quotients_8944658826, .margins = &margins_197040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_484694388, .quotients = &quotients_13615445468, .margins = &margins_229040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4914851277, .quotients = &quotients_7395994418, .margins = &margins_175040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_4266840937, .quotients = &quotients_9749052530, .margins = &margins_163040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_4586955106, .quotients = &quotients_3880931186, .margins = &margins_253040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_5794072534, .quotients = &quotients_10299494829, .margins = &margins_271040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  840000, .floor =  688000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_159040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    4000, .closedLoop =   54000, .agingOffset =   -5000, .sltOffset =  -30000, .maxFloorToCeil =  36000 } }
};


static cpr_quotient_cfg  quotients_3497487807 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  230 } },
};


static cpr_fuse_data  fuses_3614278808 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION8, CPR2_TARG_VOLT_LSVSD1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR2_TARG_VOLT_OFFSET_LSVSD2) } } },
};


static cpr_fuse_data  fuses_4635129203 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION8, CPR2_TARG_VOLT_LSVSD1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR2_TARG_VOLT_OFFSET_LSVSD1) } } },
};


static cpr_margin_cfg margins_177040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   61000, .agingOffset =   -5000, .sltOffset =  -30000, .maxFloorToCeil =  36000 } }
};


static cpr_quotient_cfg  quotients_3672117569 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  286 } },
};


static cpr_fuse_data  fuses_4116866377 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION8, CPR2_TARG_VOLT_LSVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR2_TARG_VOLT_OFFSET_LSVSD0) } } },
};


static cpr_fuse_data  fuses_3828349999 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION8, CPR2_TARG_VOLT_LSVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR2_TARG_VOLT_OFFSET_LSVS) } } },
};


static cpr_margin_cfg margins_209040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   -4000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  36000 } }
};


static cpr_quotient_cfg  quotients_2527495936 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  415 } },
};


static cpr_fuse_data  fuses_7074131739 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION8, CPR2_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR2_TARG_VOLT_OFFSET_LSVSL1) } } },
};


static cpr_margin_cfg margins_233040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    4000, .closedLoop =   66000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  36000 } }
};


static cpr_fuse_data  fuses_4848331721 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION8, CPR2_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR2_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_263040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   16000, .closedLoop =   75000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  36000 } }
};


static cpr_quotient_cfg  quotients_57719879 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  543 } },
};


static cpr_fuse_data  fuses_5332814068 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION10, CPR2_TARG_VOLT_OFFSET_SVSL0_4_3), CPR_FUSE_MAPPING(CALIBRATION9, CPR2_TARG_VOLT_OFFSET_SVSL0_2_0) } } },
};


static cpr_fuse_data  fuses_3596718600 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR2_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_245040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   70000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  36000 } }
};


static cpr_quotient_cfg  quotients_1606248255 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  595 } },
};


static cpr_fuse_data  fuses_1624585772 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR2_TARG_VOLT_OFFSET_SVSL2) } } },
};


static cpr_margin_cfg margins_255040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   12000, .closedLoop =   73000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  36000 } }
};


static cpr_quotient_cfg  quotients_1901917841 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  646 } },
};


static cpr_fuse_data  fuses_1874113817 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION8, CPR2_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR2_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_219040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   61000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  36000 } }
};


static cpr_quotient_cfg  quotients_3684806558 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  765 } },
};


static cpr_fuse_data  fuses_2852343916 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR2_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_189040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -12000, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  36000 } }
};


static cpr_quotient_cfg  quotients_1056147855 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient =  867 } },
};


static cpr_fuse_data  fuses_350880800 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR2_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_margin_cfg margins_137040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -36000, .closedLoop =   38000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  36000 } }
};


static cpr_quotient_cfg  quotients_2597374999 =
{
    .count = 1,
    .quots = (cpr_quotient[]) { { .ro = 14, .quotient = 1038 } },
};


static cpr_fuse_data  fuses_3028917449 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION8, CPR2_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR2_TARG_VOLT_OFFSET_TURL1_4_1), CPR_FUSE_MAPPING(CALIBRATION8, CPR2_TARG_VOLT_OFFSET_TURL1_0) } } },
};


static cpr_margin_cfg margins_347040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   36000, .closedLoop =  107000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  36000 } }
};


static cpr_fuse_data  fuses_5104359456 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION8, CPR2_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION11, CPR2_TARG_VOLT_OFFSET_LSVSD3) } } },
};


static cpr_kv_cfg  kvs_36959987898 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  318 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * GFX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_29842248182 =
{
    .modesCount      = 14,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_36959987898,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D2,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D0,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L0,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L2 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D2
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_3614278808, .quotients = &quotients_3497487807, .margins = &margins_159040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  500000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_4635129203, .quotients = &quotients_3497487807, .margins = &margins_159040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  500000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D0
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_4116866377, .quotients = &quotients_3672117569, .margins = &margins_177040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_3828349999, .quotients = &quotients_3672117569, .margins = &margins_177040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_L1
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_7074131739, .quotients = &quotients_2527495936, .margins = &margins_209040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  540000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4848331721, .quotients = &quotients_2527495936, .margins = &margins_233040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  540000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L0
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_5332814068, .quotients = &quotients_57719879, .margins = &margins_263040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  592000, .freq =       0, .interplEnabled = 56} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3596718600, .quotients = &quotients_57719879, .margins = &margins_263040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  592000, .freq =       0, .interplEnabled = 56} } },

        // SVS_L2
        {.fref = 704000, .freqDelta =       0, .fuses = &fuses_1624585772, .quotients = &quotients_1606248255, .margins = &margins_245040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  768000, .floor =  604000, .freq =       0, .interplEnabled = 78} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_1874113817, .quotients = &quotients_1901917841, .margins = &margins_255040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  624000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_2852343916, .quotients = &quotients_3684806558, .margins = &margins_219040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  652000, .freq =       0, .interplEnabled = 30} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_350880800, .quotients = &quotients_1056147855, .margins = &margins_189040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  664000, .freq =       0, .interplEnabled = 57} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_3028917449, .quotients = &quotients_2597374999, .margins = &margins_137040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  680000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L2
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_5104359456, .quotients = &quotients_2597374999, .margins = &margins_347040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  944000, .floor =  720000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_97960 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -25000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_402154350 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION11, CPR3_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_2297807466 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION11, CPR3_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_929810572 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION11, CPR3_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * VDDA Voltage Plan
 */
static cpr_voltage_plan voltage_plan_9513415475 =
{
    .modesCount      = 4,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  480000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 704000, .freqDelta =       0, .fuses = &fuses_402154350, .quotients = NULL, .margins = &margins_97960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  824000, .floor =  688000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_2297807466, .quotients = NULL, .margins = &margins_97960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 892000, .freqDelta =       0, .fuses = &fuses_929810572, .quotients = NULL, .margins = &margins_97960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  892000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_336146 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   36000, .closedLoop =   90000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 15, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_1099241495 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR4_TARG_VOLT_OFFSET_LSVS) } } },
};


static cpr_margin_cfg margins_452146 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   36000, .closedLoop =   92000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 15, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_4845889024 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  423 },
                                      { .ro =  5, .quotient =  433 },
                                      { .ro = 15, .quotient =  438 } },
};


static cpr_fuse_data  fuses_2566715939 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION12, CPR4_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR4_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_344146 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 15, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_3692827744 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR4_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_360146 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 15, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_8059555480 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  580 },
                                      { .ro =  5, .quotient =  586 },
                                      { .ro = 14, .quotient =  754 },
                                      { .ro = 15, .quotient =  599 } },
};


static cpr_fuse_data  fuses_7463472135 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION12, CPR4_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR4_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_364146 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 15, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_7460766021 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  625 },
                                      { .ro =  5, .quotient =  630 },
                                      { .ro = 14, .quotient =  802 },
                                      { .ro = 15, .quotient =  646 } },
};


static cpr_fuse_data  fuses_3714880379 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR4_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_376146 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 15, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_4307232162 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  684 },
                                      { .ro =  5, .quotient =  711 },
                                      { .ro = 14, .quotient =  891 },
                                      { .ro = 15, .quotient =  739 } },
};


static cpr_fuse_data  fuses_4944263889 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION12, CPR4_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR4_TARG_VOLT_OFFSET_TUR_4), CPR_FUSE_MAPPING(CALIBRATION12, CPR4_TARG_VOLT_OFFSET_TUR_3_0) } } },
};


static cpr_margin_cfg margins_384146 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 15, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_10440236678 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  801 },
                                      { .ro =  5, .quotient =  805 },
                                      { .ro = 14, .quotient =  992 },
                                      { .ro = 15, .quotient =  830 } },
};


static cpr_fuse_data  fuses_9750937326 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION12, CPR4_TARG_VOLT_TURL1_5_1), CPR_FUSE_MAPPING(CALIBRATION11, CPR4_TARG_VOLT_TURL1_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION12, CPR4_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_kv_cfg  kvs_31236039632 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =  307 },
                                { .ro =  5, .kv =  308 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  324 },
                                { .ro = 15, .kv =  320 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_20132411682 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_31236039632,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_1099241495, .quotients = NULL, .margins = &margins_336146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_2566715939, .quotients = &quotients_4845889024, .margins = &margins_452146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3692827744, .quotients = NULL, .margins = &margins_344146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_7463472135, .quotients = &quotients_8059555480, .margins = &margins_360146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  804000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_3714880379, .quotients = &quotients_7460766021, .margins = &margins_364146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  752000, .freq =       0, .interplEnabled = 33} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4944263889, .quotients = &quotients_4307232162, .margins = &margins_376146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_9750937326, .quotients = &quotients_10440236678, .margins = &margins_384146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 884000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  884000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_fuse_data  fuses_3870908746 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR5_TARG_VOLT_OFFSET_LSVS) } } },
};


static cpr_fuse_data  fuses_5271816984 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR5_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR5_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_520146 = {
    .count = 2,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =  100000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 15, .openLoop =       0, .closedLoop =  100000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_2547962100 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR5_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_fuse_data  fuses_989128134 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR5_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR5_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_fuse_data  fuses_4921925484 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR5_TARG_VOLT_OFFSET_NOML1_4), CPR_FUSE_MAPPING(CALIBRATION14, CPR5_TARG_VOLT_OFFSET_NOML1_3_0) } } },
};


static cpr_fuse_data  fuses_5522319568 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR5_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR5_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_fuse_data  fuses_4462090729 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR5_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR5_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_kv_cfg  kvs_31165930585 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =  306 },
                                { .ro =  5, .kv =  308 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  324 },
                                { .ro = 15, .kv =  319 } },
};


/*
 * MXC Voltage Plan
 */
static cpr_voltage_plan voltage_plan_28440627091 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_31165930585,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_3870908746, .quotients = NULL, .margins = &margins_336146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_5271816984, .quotients = &quotients_4845889024, .margins = &margins_452146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_2547962100, .quotients = NULL, .margins = &margins_520146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_989128134, .quotients = &quotients_8059555480, .margins = &margins_360146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  804000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_4921925484, .quotients = &quotients_7460766021, .margins = &margins_364146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  752000, .freq =       0, .interplEnabled = 33} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_5522319568, .quotients = &quotients_4307232162, .margins = &margins_376146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_4462090729, .quotients = &quotients_10440236678, .margins = &margins_384146,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 884000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  884000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_57960 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =      0 } }
};


static cpr_fuse_data  fuses_4554665296 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR6_TARG_VOLT_NOM_5), CPR_FUSE_MAPPING(CALIBRATION15, CPR6_TARG_VOLT_NOM_4_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_3013494642 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR6_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


/*
 * LPI_MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_3795520164 =
{
    .modesCount      = 4,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  508000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_4554665296, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  808000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_3013494642, .quotients = NULL, .margins = &margins_57960,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_157040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_12229234843 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  346 },
                                      { .ro =  6, .quotient =  238 },
                                      { .ro = 10, .quotient =  250 },
                                      { .ro = 12, .quotient =  493 },
                                      { .ro = 14, .quotient =  230 },
                                      { .ro = 15, .quotient =  142 } },
};


static cpr_fuse_data  fuses_2756292206 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR7_TARG_VOLT_LSVSD1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR7_TARG_VOLT_OFFSET_LSVSD1) } } },
};


static cpr_quotient_cfg  quotients_15391863872 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  416 },
                                      { .ro =  6, .quotient =  298 },
                                      { .ro = 10, .quotient =  324 },
                                      { .ro = 12, .quotient =  583 },
                                      { .ro = 14, .quotient =  286 },
                                      { .ro = 15, .quotient =  183 } },
};


static cpr_fuse_data  fuses_3644735612 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR7_TARG_VOLT_OFFSET_LSVS) } } },
};


static cpr_margin_cfg margins_101040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -16000, .closedLoop =   40000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_11795859785 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  554 },
                                      { .ro =  6, .quotient =  427 },
                                      { .ro = 10, .quotient =  495 },
                                      { .ro = 12, .quotient =  753 },
                                      { .ro = 14, .quotient =  415 },
                                      { .ro = 15, .quotient =  301 } },
};


static cpr_fuse_data  fuses_5681147202 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR7_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR7_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_77040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -24000, .closedLoop =   32000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_6610317539 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  690 },
                                      { .ro =  6, .quotient =  556 },
                                      { .ro = 14, .quotient =  543 } },
};


static cpr_fuse_data  fuses_968304464 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR7_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_121040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -24000, .closedLoop =   34000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_2995036363 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  804 },
                                      { .ro =  6, .quotient =  659 },
                                      { .ro = 14, .quotient =  646 } },
};


static cpr_fuse_data  fuses_10782504736 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR7_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR7_TARG_VOLT_OFFSET_NOM_4_2), CPR_FUSE_MAPPING(CALIBRATION16, CPR7_TARG_VOLT_OFFSET_NOM_1_0) } } },
};


static cpr_margin_cfg margins_145040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -20000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_6704326363 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  998 },
                                      { .ro =  6, .quotient =  876 },
                                      { .ro = 14, .quotient =  867 } },
};


static cpr_fuse_data  fuses_6367697809 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR7_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR7_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_34521582299 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  337 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  314 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =  397 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  423 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  324 },
                                { .ro = 15, .kv =  260 } },
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_13135399991 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_34521582299,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  480000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_2756292206, .quotients = &quotients_12229234843, .margins = &margins_157040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_3644735612, .quotients = &quotients_15391863872, .margins = &margins_151040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_5681147202, .quotients = &quotients_11795859785, .margins = &margins_101040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_968304464, .quotients = &quotients_6610317539, .margins = &margins_77040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_10782504736, .quotients = &quotients_2995036363, .margins = &margins_121040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_6367697809, .quotients = &quotients_6704326363, .margins = &margins_145040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_133040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9285019288 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  143 },
                                      { .ro = 14, .quotient =  230 },
                                      { .ro = 15, .quotient =  142 } },
};


static cpr_fuse_data  fuses_1971023638 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR8_TARG_VOLT_LSVSD1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR8_TARG_VOLT_OFFSET_LSVSD1) } } },
};


static cpr_margin_cfg margins_147040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_7318203771 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  185 },
                                      { .ro = 14, .quotient =  286 },
                                      { .ro = 15, .quotient =  183 } },
};


static cpr_fuse_data  fuses_367765764 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR8_TARG_VOLT_OFFSET_LSVS) } } },
};


static cpr_margin_cfg margins_125040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   -8000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_6067380037 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  302 },
                                      { .ro = 14, .quotient =  415 },
                                      { .ro = 15, .quotient =  301 } },
};


static cpr_fuse_data  fuses_4126344066 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR8_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR8_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_quotient_cfg  quotients_2701963025 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  410 },
                                      { .ro = 14, .quotient =  543 },
                                      { .ro = 15, .quotient =  415 } },
};


static cpr_fuse_data  fuses_3800534059 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR8_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_quotient_cfg  quotients_5659979452 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  511 },
                                      { .ro = 14, .quotient =  646 },
                                      { .ro = 15, .quotient =  513 } },
};


static cpr_fuse_data  fuses_3029499953 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR8_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR8_TARG_VOLT_OFFSET_NOM_4), CPR_FUSE_MAPPING(CALIBRATION18, CPR8_TARG_VOLT_OFFSET_NOM_3_0) } } },
};


static cpr_margin_cfg margins_135040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -24000, .closedLoop =   41000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_1629828152 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  9, .quotient =  711 },
                                      { .ro = 14, .quotient =  867 },
                                      { .ro = 15, .quotient =  725 } },
};


static cpr_fuse_data  fuses_6797178944 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR8_TARG_VOLT_TUR_5_1), CPR_FUSE_MAPPING(CALIBRATION17, CPR8_TARG_VOLT_TUR_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR8_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_31821170317 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =  287 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  323 },
                                { .ro = 15, .kv =  297 } },
};


/*
 * MM Voltage Plan
 */
static cpr_voltage_plan voltage_plan_12693550707 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_31821170317,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_1971023638, .quotients = &quotients_9285019288, .margins = &margins_133040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_367765764, .quotients = &quotients_7318203771, .margins = &margins_147040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4126344066, .quotients = &quotients_6067380037, .margins = &margins_125040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3800534059, .quotients = &quotients_2701963025, .margins = &margins_77040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_3029499953, .quotients = &quotients_5659979452, .margins = &margins_121040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_6797178944, .quotients = &quotients_1629828152, .margins = &margins_135040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_187040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   16000, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_4371080360 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR9_TARG_VOLT_LSVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR9_TARG_VOLT_OFFSET_LSVS) } } },
};


static cpr_quotient_cfg  quotients_6431369933 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  298 },
                                      { .ro =  9, .quotient =  302 },
                                      { .ro = 14, .quotient =  415 },
                                      { .ro = 15, .quotient =  301 } },
};


static cpr_fuse_data  fuses_5561308613 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR9_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR9_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_fuse_data  fuses_1254753393 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR9_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_183040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =    8000, .closedLoop =   69000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_406483250 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR9_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_margin_cfg margins_249040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   16000, .closedLoop =   78000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_8112939948 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR9_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR9_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_margin_cfg margins_325040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   40000, .closedLoop =  104000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_8624803768 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  998 },
                                      { .ro =  6, .quotient =  876 },
                                      { .ro = 12, .quotient = 1278 },
                                      { .ro = 14, .quotient =  867 } },
};


static cpr_fuse_data  fuses_6855959073 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR9_TARG_VOLT_OFFSET_TUR_4_1), CPR_FUSE_MAPPING(CALIBRATION20, CPR9_TARG_VOLT_OFFSET_TUR_0) } } },
};


static cpr_margin_cfg margins_285040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   24000, .closedLoop =   92000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_7894698577 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient = 1147 },
                                      { .ro =  6, .quotient = 1027 },
                                      { .ro = 12, .quotient = 1430 },
                                      { .ro = 14, .quotient = 1038 } },
};


static cpr_fuse_data  fuses_1151843220 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR9_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_margin_cfg margins_139040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -32000, .closedLoop =   47000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_quotient_cfg  quotients_10362235092 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient = 1392 },
                                      { .ro =  6, .quotient = 1276 },
                                      { .ro = 12, .quotient = 1677 },
                                      { .ro = 14, .quotient = 1307 } },
};


static cpr_fuse_data  fuses_6088960319 =
{
    .volt       = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR9_TARG_VOLT_TURL3_5_3), CPR_FUSE_MAPPING(CALIBRATION19, CPR9_TARG_VOLT_TURL3_2_0) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR9_TARG_VOLT_OFFSET_TURL3) } } },
};


static cpr_kv_cfg  kvs_40190351245 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  309 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  301 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  260 },
                                { .ro =  9, .kv =  266 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  335 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  314 },
                                { .ro = 15, .kv =  272 } },
};


/*
 * NSP Voltage Plan
 */
static cpr_voltage_plan voltage_plan_19674933115 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_40190351245,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L3,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_4371080360, .quotients = &quotients_11315010313, .margins = &margins_187040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_5561308613, .quotients = &quotients_6431369933, .margins = &margins_149040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_1254753393, .quotients = &quotients_9749052530, .margins = &margins_173040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 40} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_406483250, .quotients = &quotients_3880931186, .margins = &margins_183040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  660000, .freq =       0, .interplEnabled = 72} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_8112939948, .quotients = &quotients_10299494829, .margins = &margins_249040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  832000, .floor =  688000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_6855959073, .quotients = &quotients_8624803768, .margins = &margins_325040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  716000, .freq =       0, .interplEnabled = 15} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_1151843220, .quotients = &quotients_7894698577, .margins = &margins_285040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 40} } },

        // TURBO_L3
        {.fref = 988000, .freqDelta =       0, .fuses = &fuses_6088960319, .quotients = &quotients_10362235092, .margins = &margins_139040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling = 1052000, .floor =  856000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 1052000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling = 1052000, .floor = 1052000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_125041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_8455054266 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =   98 },
                                      { .ro =  9, .quotient =  101 },
                                      { .ro = 14, .quotient =  175 },
                                      { .ro = 15, .quotient =  101 } },
};


static cpr_fuse_data  fuses_3454963964 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR10_TARG_VOLT_LSVSD2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR10_TARG_VOLT_OFFSET_LSVSD2) } } },
};


static cpr_margin_cfg margins_205040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   24000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_12179171910 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  8, .quotient =  140 },
                                      { .ro =  9, .quotient =  143 },
                                      { .ro = 14, .quotient =  230 },
                                      { .ro = 15, .quotient =  142 } },
};


static cpr_fuse_data  fuses_3923351171 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR10_TARG_VOLT_LSVSD1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR10_TARG_VOLT_OFFSET_LSVSD1) } } },
};


static cpr_margin_cfg margins_241040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   32000, .closedLoop =   86000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_1998330183 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR10_TARG_VOLT_OFFSET_LSVS) } } },
};


static cpr_margin_cfg margins_269040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   40000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_fuse_data  fuses_2564581670 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR10_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR10_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_margin_cfg margins_295040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   36000, .closedLoop =   91000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_2114091967 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR10_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_margin_cfg margins_355040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   56000, .closedLoop =  111000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_fuse_data  fuses_6450194824 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION22, CPR10_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 2, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR10_TARG_VOLT_OFFSET_NOM_4_3), CPR_FUSE_MAPPING(CALIBRATION22, CPR10_TARG_VOLT_OFFSET_NOM_2_0) } } },
};


static cpr_kv_cfg  kvs_40562695449 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  342 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  322 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  234 },
                                { .ro =  9, .kv =  239 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  400 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  304 },
                                { .ro = 15, .kv =  244 } },
};


/*
 * NSP2 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_10362258973 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_40562695449,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D2,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D2
        {.fref = 516000, .freqDelta =       0, .fuses = &fuses_3454963964, .quotients = &quotients_8455054266, .margins = &margins_125041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  616000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_3923351171, .quotients = &quotients_12179171910, .margins = &margins_205040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_1998330183, .quotients = &quotients_11315010313, .margins = &margins_241040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_2564581670, .quotients = &quotients_6431369933, .margins = &margins_269040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_2114091967, .quotients = &quotients_9749052530, .margins = &margins_295040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_6450194824, .quotients = &quotients_3880931186, .margins = &margins_355040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  840000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 840000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  840000, .floor =  840000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_2040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


/*
 * WMSS_CX_1 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_6968967943 =
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
        {.fref = 556000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  612000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 588000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 668000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  724000, .floor =  596000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  868000, .floor =  712000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * WMSS_MX_1 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_4508525342 =
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
        {.fref = 850000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
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


static cpr_margin_cfg margins_596283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =    4000, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    4000, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =    4000, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =    4000, .closedLoop =   55000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_780283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   16000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   16000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   16000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_588283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =    4000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    4000, .closedLoop =   60000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   -4000, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   -4000, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_812283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   12000, .closedLoop =   70000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   12000, .closedLoop =   70000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   -4000, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   -4000, .closedLoop =   54000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_508283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =  -16000, .closedLoop =   46000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =  -16000, .closedLoop =   46000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =  -32000, .closedLoop =   30000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =  -32000, .closedLoop =   30000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_636283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   -4000, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   -4000, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =  -28000, .closedLoop =   38000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =  -28000, .closedLoop =   38000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_556283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   -4000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   -4000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =  -44000, .closedLoop =   24000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =  -44000, .closedLoop =   24000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_35157096729 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  287 },
                                { .ro =  9, .kv =  291 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  306 },
                                { .ro = 15, .kv =  301 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_15700114200 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_35157096729,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  480000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_2960628641, .quotients = &quotients_11315010313, .margins = &margins_596283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_8073949460, .quotients = &quotients_3903873997, .margins = &margins_780283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_2199882008, .quotients = &quotients_6021411618, .margins = &margins_588283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_5150927558, .quotients = &quotients_6971872036, .margins = &margins_812283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_1822939800, .quotients = &quotients_7402694220, .margins = &margins_508283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  688000, .freq =       0, .interplEnabled = 30} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_2663925107, .quotients = &quotients_608733415, .margins = &margins_636283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 57} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_2190787618, .quotients = &quotients_6330710590, .margins = &margins_556283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 904000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  904000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_version  ver_ANY_2_0_2_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(2,0), .max = CPR_CHIPINFO_VERSION(2,255) };


static cpr_margin_cfg margins_700283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   16000, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   16000, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   16000, .closedLoop =   62000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_556284 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =       0, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =       0, .closedLoop =   52000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_588284 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =       0, .closedLoop =   56000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_412283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =  -16000, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =  -16000, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =  -16000, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =  -16000, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_772283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =       0, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =       0, .closedLoop =   59000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_884283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   77000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   16000, .closedLoop =   77000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =       0, .closedLoop =   61000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =       0, .closedLoop =   61000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_35457071690 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  333 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =  281 },
                                { .ro =  6, .kv =  316 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  239 },
                                { .ro =  9, .kv =  247 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  387 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  316 },
                                { .ro = 15, .kv =    0 } },
};


/*
 * MSS Voltage Plan
 */
static cpr_voltage_plan voltage_plan_8853821055 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_35457071690,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_771147252, .quotients = &quotients_8944658826, .margins = &margins_700283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_484694388, .quotients = &quotients_13615445468, .margins = &margins_556284,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4914851277, .quotients = &quotients_7395994418, .margins = &margins_588284,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_4266840937, .quotients = &quotients_9749052530, .margins = &margins_412283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_4586955106, .quotients = &quotients_3880931186, .margins = &margins_772283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_5794072534, .quotients = &quotients_10299494829, .margins = &margins_884283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  840000, .floor =  688000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_262040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =  100000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_174040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   56000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_182040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   60000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_184040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   61000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_190040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   64000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_194040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =   66000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_kv_cfg  kvs_35361964539 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =  301 },
                                { .ro =  5, .kv =  303 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  319 },
                                { .ro = 15, .kv =  314 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_24781091016 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_35361964539,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 700000, .freqDelta =       0, .fuses = &fuses_1099241495, .quotients = NULL, .margins = &margins_262040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  700000, .floor =  700000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_2566715939, .quotients = &quotients_4845889024, .margins = &margins_174040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  732000, .floor =  700000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 732000, .freqDelta =       0, .fuses = &fuses_3692827744, .quotients = NULL, .margins = &margins_262040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  732000, .floor =  732000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_7463472135, .quotients = &quotients_8059555480, .margins = &margins_182040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  804000, .floor =  736000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_3714880379, .quotients = &quotients_7460766021, .margins = &margins_184040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  736000, .freq =       0, .interplEnabled = 33} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4944263889, .quotients = &quotients_4307232162, .margins = &margins_190040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  784000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_9750937326, .quotients = &quotients_10440236678, .margins = &margins_194040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  788000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 884000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  884000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_296040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   32000, .closedLoop =  101000, .agingOffset =       0, .sltOffset =  -15000, .maxFloorToCeil =  24000 } }
};


static cpr_kv_cfg  kvs_34322440479 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =  300 },
                                { .ro =  5, .kv =  302 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  319 },
                                { .ro = 15, .kv =  314 } },
};


/*
 * MXC Voltage Plan
 */
static cpr_voltage_plan voltage_plan_24902461435 =
{
    .modesCount      = 10,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_34322440479,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L2,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  680000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_3870908746, .quotients = NULL, .margins = &margins_262040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  716000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_5271816984, .quotients = &quotients_4845889024, .margins = &margins_174040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_2547962100, .quotients = NULL, .margins = &margins_262040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_989128134, .quotients = &quotients_8059555480, .margins = &margins_182040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  804000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_4921925484, .quotients = &quotients_7460766021, .margins = &margins_184040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  752000, .freq =       0, .interplEnabled = 33} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_5522319568, .quotients = &quotients_4307232162, .margins = &margins_190040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_4462090729, .quotients = &quotients_10440236678, .margins = &margins_194040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L2
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_4462090729, .quotients = &quotients_10440236678, .margins = &margins_296040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  916000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 916000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  916000, .floor =  916000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_175041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =   12000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_157041 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =  -16000, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_36191321710 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  330 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  309 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =    0 },
                                { .ro = 10, .kv =  389 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  417 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  318 },
                                { .ro = 15, .kv =  254 } },
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_16257604244 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_36191321710,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref =      0, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  480000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_2756292206, .quotients = &quotients_12229234843, .margins = &margins_157040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_3644735612, .quotients = &quotients_15391863872, .margins = &margins_175041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_5681147202, .quotients = &quotients_11795859785, .margins = &margins_125040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_968304464, .quotients = &quotients_6610317539, .margins = &margins_77040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_10782504736, .quotients = &quotients_2995036363, .margins = &margins_121040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_6367697809, .quotients = &quotients_6704326363, .margins = &margins_157041,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_460283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   -4000, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   -4000, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   -4000, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   -4000, .closedLoop =   42000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_524283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =       0, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =       0, .closedLoop =   48000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_460284 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   -8000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   -8000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   -8000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   -8000, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_284283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =  -24000, .closedLoop =   30000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =  -24000, .closedLoop =   30000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =  -24000, .closedLoop =   30000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =  -24000, .closedLoop =   30000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_460285 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =  -28000, .closedLoop =   34000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =  -28000, .closedLoop =   34000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =  -28000, .closedLoop =   34000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =  -28000, .closedLoop =   34000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_108283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =  -28000, .closedLoop =   38000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =  -28000, .closedLoop =   38000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =  -92000, .closedLoop =  -26000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =  -92000, .closedLoop =  -26000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_34257665555 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =    0 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =    0 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =    0 },
                                { .ro =  9, .kv =  283 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =    0 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  316 },
                                { .ro = 15, .kv =  291 } },
};


/*
 * MM Voltage Plan
 */
static cpr_voltage_plan voltage_plan_13404261639 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_34257665555,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_1971023638, .quotients = &quotients_9285019288, .margins = &margins_460283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_367765764, .quotients = &quotients_7318203771, .margins = &margins_524283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4126344066, .quotients = &quotients_6067380037, .margins = &margins_460284,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3800534059, .quotients = &quotients_2701963025, .margins = &margins_284283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_3029499953, .quotients = &quotients_5659979452, .margins = &margins_460285,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  776000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_6797178944, .quotients = &quotients_1629828152, .margins = &margins_108283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_740283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   16000, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   16000, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   16000, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   16000, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
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


static cpr_fuse_data  fuses_1888412113 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR9_TARG_VOLT_LSVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR9_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_quotient_cfg  quotients_9113335701 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  554 },
                                      { .ro =  6, .quotient =  427 },
                                      { .ro = 12, .quotient =  754 },
                                      { .ro = 14, .quotient =  415 } },
};


static cpr_margin_cfg margins_684283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =    8000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    8000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =    8000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =    8000, .closedLoop =   64000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_592283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   -3000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   -3000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   -3000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   -3000, .closedLoop =   58000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_716283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =    2000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    2000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =  -14000, .closedLoop =   47000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =  -14000, .closedLoop =   47000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_944283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   23000, .closedLoop =   87000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   23000, .closedLoop =   87000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   -1000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   -1000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_672283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =    3000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =    3000, .closedLoop =   63000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =  -21000, .closedLoop =   39000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =  -21000, .closedLoop =   39000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_564283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   -8000, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   -8000, .closedLoop =   67000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =  -48000, .closedLoop =   27000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =  -48000, .closedLoop =   27000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_36257955438 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  308 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  297 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  254 },
                                { .ro =  9, .kv =  262 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  332 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  309 },
                                { .ro = 15, .kv =  266 } },
};


/*
 * NSP Voltage Plan
 */
static cpr_voltage_plan voltage_plan_28516786506 =
{
    .modesCount      = 10,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_36257955438,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1,
                                                    CPR_VOLTAGE_MODE_TURBO_L3,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_1888412113, .quotients = &quotients_17317289554, .margins = &margins_740283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_4371080360, .quotients = &quotients_17317289554, .margins = &margins_740283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_5561308613, .quotients = &quotients_9113335701, .margins = &margins_588284,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_0, .quotients = &quotients_9749052530, .margins = &margins_684283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 40} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_406483250, .quotients = &quotients_3880931186, .margins = &margins_592283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  796000, .floor =  660000, .freq =       0, .interplEnabled = 72} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_8112939948, .quotients = &quotients_10299494829, .margins = &margins_716283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  832000, .floor =  688000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_6855959073, .quotients = &quotients_8624803768, .margins = &margins_944283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  888000, .floor =  716000, .freq =       0, .interplEnabled = 15} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_1151843220, .quotients = &quotients_7894698577, .margins = &margins_672283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 40} } },

        // TURBO_L3
        {.fref = 988000, .freqDelta =       0, .fuses = &fuses_6088960319, .quotients = &quotients_10362235092, .margins = &margins_564283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling = 1052000, .floor =  856000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 1052000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling = 1052000, .floor = 1052000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_492283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =       0, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =       0, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =       0, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =       0, .closedLoop =   44000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_12286047345 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  280 },
                                      { .ro =  6, .quotient =  182 },
                                      { .ro =  8, .quotient =   98 },
                                      { .ro =  9, .quotient =  101 },
                                      { .ro = 14, .quotient =  175 },
                                      { .ro = 15, .quotient =  101 } },
};


static cpr_margin_cfg margins_812284 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   24000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   24000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   24000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   24000, .closedLoop =   72000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_8654532549 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  346 },
                                      { .ro =  6, .quotient =  238 },
                                      { .ro = 12, .quotient =  493 },
                                      { .ro = 14, .quotient =  230 } },
};


static cpr_margin_cfg margins_932283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   32000, .closedLoop =   83000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   32000, .closedLoop =   83000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   32000, .closedLoop =   83000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   32000, .closedLoop =   83000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_quotient_cfg  quotients_9268682324 =
{
    .count = 4,
    .quots = (cpr_quotient[]) { { .ro =  3, .quotient =  415 },
                                      { .ro =  6, .quotient =  298 },
                                      { .ro = 12, .quotient =  584 },
                                      { .ro = 14, .quotient =  287 } },
};


static cpr_margin_cfg margins_1020283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   40000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   40000, .closedLoop =   96000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   32000, .closedLoop =   88000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   32000, .closedLoop =   88000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  24000 } }
};


static cpr_margin_cfg margins_940283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   20000, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   20000, .closedLoop =   76000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   12000, .closedLoop =   68000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   12000, .closedLoop =   68000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_margin_cfg margins_1244283 = {
    .count = 4,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 1, .openLoop =   48000, .closedLoop =  106000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 4, .cprRevMax = 4, .openLoop =   48000, .closedLoop =  106000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 2, .cprRevMax = 3, .openLoop =   32000, .closedLoop =   90000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 },
                                  { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 5, .cprRevMax = 15, .openLoop =   32000, .closedLoop =   90000, .agingOffset =  -15000, .sltOffset =  -10000, .maxFloorToCeil =  32000 } }
};


static cpr_kv_cfg  kvs_31983448070 =
{
    .count = 16,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =    0 },
                                { .ro =  1, .kv =    0 },
                                { .ro =  2, .kv =    0 },
                                { .ro =  3, .kv =  328 },
                                { .ro =  4, .kv =    0 },
                                { .ro =  5, .kv =    0 },
                                { .ro =  6, .kv =  298 },
                                { .ro =  7, .kv =    0 },
                                { .ro =  8, .kv =  184 },
                                { .ro =  9, .kv =  192 },
                                { .ro = 10, .kv =    0 },
                                { .ro = 11, .kv =    0 },
                                { .ro = 12, .kv =  397 },
                                { .ro = 13, .kv =    0 },
                                { .ro = 14, .kv =  306 },
                                { .ro = 15, .kv =  192 } },
};


/*
 * NSP2 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_8588767687 =
{
    .modesCount      = 7,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_31983448070,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D2,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_SUPER_TURBO_NO_CPR },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D2
        {.fref = 516000, .freqDelta =       0, .fuses = &fuses_3454963964, .quotients = &quotients_12286047345, .margins = &margins_492283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  616000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_3923351171, .quotients = &quotients_8654532549, .margins = &margins_812284,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_1998330183, .quotients = &quotients_9268682324, .margins = &margins_932283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  676000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_2564581670, .quotients = &quotients_9113335701, .margins = &margins_1020283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  740000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_2114091967, .quotients = &quotients_9749052530, .margins = &margins_940283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  752000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_6450194824, .quotients = &quotients_3880931186, .margins = &margins_1244283,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  840000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // SUPER_TURBO_NO_CPR
        {.fref = 840000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  840000, .floor =  840000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * Aging configs
 */

static cpr_aging_cfg  aging_cfg_cx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 31,
    .kv                   = 117,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C2A00 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<2) | (1<<1) | (1<<0)},
                                 {QFPROM_CORR_REG_BASE | (0x221C29FC & (QFPROM_CORR_REG_BASE_SIZE - 1)), 27, (1<<31) | (1<<30) | (1<<29) | (1<<28) | (1<<27)} } }
};


static cpr_aging_cfg  aging_cfg_mss =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_NOMINAL_L1,
    .sensorID             = 10,
    .kv                   = 131,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C2A08 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<0)},
                                 {QFPROM_CORR_REG_BASE | (0x221C2A04 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 25, (1<<31) | (1<<30) | (1<<29) | (1<<28) | (1<<27) | (1<<26) | (1<<25)} } }
};


static cpr_aging_cfg  aging_cfg_gfx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 21,
    .kv                   = 117,
    .scalingFactor        = 15,
    .marginLimit          = 15000,
    .bypassSensorIDs      = (uint8[]) {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33},
    .bypassSensorIDsCount = 33,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C2A14 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 5, (1<<12) | (1<<11) | (1<<10) | (1<<9) | (1<<8) | (1<<7) | (1<<6) | (1<<5)} } }
};


static cpr_aging_cfg  aging_cfg_mx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L1,
    .sensorID             = 21,
    .kv                   = 119,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 9, (1<<16) | (1<<15) | (1<<14) | (1<<13) | (1<<12) | (1<<11) | (1<<10) | (1<<9)} } }
};


static cpr_aging_cfg  aging_cfg_lpi_cx =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 3,
    .kv                   = 128,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C2A2C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 23, (1<<30) | (1<<29) | (1<<28) | (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23)} } }
};


static cpr_aging_cfg  aging_cfg_mm =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO,
    .sensorID             = 16,
    .kv                   = 126,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = NULL,
    .bypassSensorIDsCount = 0,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 1, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C2A34 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 21, (1<<28) | (1<<27) | (1<<26) | (1<<25) | (1<<24) | (1<<23) | (1<<22) | (1<<21)} } }
};


static cpr_aging_cfg  aging_cfg_nsp =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_TURBO_L3,
    .sensorID             = 0,
    .kv                   = 94,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = (uint8[]) {1, 2, 3, 4, 5, 6, 7},
    .bypassSensorIDsCount = 7,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C2A40 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0)},
                                 {QFPROM_CORR_REG_BASE | (0x221C2A3C & (QFPROM_CORR_REG_BASE_SIZE - 1)), 29, (1<<31) | (1<<30) | (1<<29)} } }
};


static cpr_aging_cfg  aging_cfg_nsp2 =
{
    .cprRevMinToRun       = 0,
    .modeToRun            = CPR_VOLTAGE_MODE_NOMINAL,
    .sensorID             = 2,
    .kv                   = 135,
    .scalingFactor        = 10,
    .marginLimit          = 15000,
    .bypassSensorIDs      = (uint8[]) {0, 1, 3, 4, 5, 6, 7},
    .bypassSensorIDsCount = 7,
    .fusePackingFactor    = 1,
    .fuse                 = {.count = 2, .data = (struct raw_fuse_data[]) {
                                 {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 0, (1<<2) | (1<<1) | (1<<0)},
                                 {QFPROM_CORR_REG_BASE | (0x221C2A44 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 27, (1<<31) | (1<<30) | (1<<29) | (1<<28) | (1<<27)} } }
};


/*
 * Versioned Voltage Plans
 */

static cpr_versioned_voltage_plan cx_vvp = {
    .rail     = CPR_RAIL_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_22645813518 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_15700114200 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_cx
};


static cpr_versioned_voltage_plan mss_vvp = {
    .rail     = CPR_RAIL_MSS,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_10193013177 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_8853821055 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_mss
};


static cpr_versioned_voltage_plan gfx_vvp = {
    .rail     = CPR_RAIL_GFX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_29842248182 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_29842248182 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_gfx
};


static cpr_versioned_voltage_plan vdda_vvp = {
    .rail     = CPR_RAIL_VDDA,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_9513415475 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_9513415475 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan mx_vvp = {
    .rail     = CPR_RAIL_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_20132411682 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_24781091016 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_mx
};


static cpr_versioned_voltage_plan mxc_vvp = {
    .rail     = CPR_RAIL_MXC,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_28440627091 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_24902461435 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_mx_vvp = {
    .rail     = CPR_RAIL_LPI_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_3795520164 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_3795520164 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_cx_vvp = {
    .rail     = CPR_RAIL_LPI_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_13135399991 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_16257604244 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_lpi_cx
};


static cpr_versioned_voltage_plan mm_vvp = {
    .rail     = CPR_RAIL_MM,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_12693550707 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_13404261639 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_mm
};


static cpr_versioned_voltage_plan nsp_vvp = {
    .rail     = CPR_RAIL_NSP,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_19674933115 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_28516786506 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_nsp
};


static cpr_versioned_voltage_plan nsp2_vvp = {
    .rail     = CPR_RAIL_NSP2,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_10362258973 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_8588767687 },
     },
    .count    = 2,
    .agingCfg = &aging_cfg_nsp2
};


static cpr_versioned_voltage_plan wmss_cx_1_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_1,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_6968967943 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_6968967943 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_2_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_2,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_6968967943 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_6968967943 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_mx_1_vvp = {
    .rail     = CPR_RAIL_WMSS_MX_1,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_4508525342 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_4508525342 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_mx_2_vvp = {
    .rail     = CPR_RAIL_WMSS_MX_2,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_4508525342 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_4508525342 },
     },
    .count    = 2,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan nav_ldo_vvp = {
    .rail     = CPR_RAIL_NAV_LDO,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_3863315186 },

        { .version = &ver_ANY_2_0_2_255, .cfg = &voltage_plan_3863315186 },
     },
    .count    = 2,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28 },
    .sensorsCount = 29,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50 },
    .sensorsCount = 51,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33 },
    .sensorsCount = 34,
};


static cpr_hal_thread  gfx_thread = {
    .id   = 0,
    .cfg  = &gfx_thread_cfg,
};


static cpr_hal_thread_cfg nsp2_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7 },
    .sensorsCount = 8,
};


static cpr_hal_thread  nsp2_thread = {
    .id   = 0,
    .cfg  = &nsp2_thread_cfg,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28 },
    .sensorsCount = 29,
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
    .sensors      = (uint8[]){ 0,1,2,5,6,7,8,9,10,11,12,13,16,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36 },
    .sensorsCount = 29,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54 },
    .sensorsCount = 55,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7 },
    .sensorsCount = 8,
};


static cpr_hal_thread  nsp_thread = {
    .id   = 0,
    .cfg  = &nsp_thread_cfg,
};


/*
 * CPR Controller Config
 */

static cpr_hal_controller_cfg cpr3_controller_cfg = {
    .stepQuotMin         = 10,
    .stepQuotMax         = 16,
    .sensorsTotal        = 29,
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
    .stepQuotMin         = 12,
    .stepQuotMax         = 12,
    .sensorsTotal        = 51,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = (uint8[]){ 1,2,3,5,6,7,8,9,10,11,12,14,22,33,34,35,36,37,47,48,49,50 },
    .disableSensorsCount = 22,
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
    .stepQuotMin         = 13,
    .stepQuotMax         = 13,
    .sensorsTotal        = 34,
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


static cpr_hal_controller_cfg hmx_cpr3_controller_cfg = {
    .stepQuotMin         = 9,
    .stepQuotMax         = 16,
    .sensorsTotal        = 8,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  hmx_cpr3_controller = {
    .base                = 0x634000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &hmx_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &nsp2_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg lpass_cpr3_controller_cfg = {
    .stepQuotMin         = 10,
    .stepQuotMax         = 17,
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
    .stepQuotMin         = 11,
    .stepQuotMax         = 13,
    .sensorsTotal        = 29,
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
    .stepQuotMin         = 12,
    .stepQuotMax         = 13,
    .sensorsTotal        = 94,
    .bypassSensors       = (uint8[]){ 3,4,14,15,17,18,19,20,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93 },
    .bypassSensorsCount  = 65,
    .disableSensors      = (uint8[]){ 3,4,14,15,17,18,19,20,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88 },
    .disableSensorsCount = 60,
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
    .stepQuotMin         = 12,
    .stepQuotMax         = 13,
    .sensorsTotal        = 55,
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
    .stepQuotMin         = 10,
    .stepQuotMax         = 13,
    .sensorsTotal        = 8,
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


static cpr_rail cpr_rail_nsp2_cfg = {
    .id               = CPR_RAIL_NSP2,
    .name             = "NSP2",
    .hal              = { .controller = &hmx_cpr3_controller, .thread = &nsp2_thread },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_cx_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_CX,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_gfx_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_GFX,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_lpi_cx_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_LPI_CX,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_lpi_mx_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_LPI_MX,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_mm_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_MM,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_mss_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_MSS,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mx_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_MX,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mxc_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_MXC,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_SW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_nav_ldo_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_NAV_LDO,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_nsp_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_NSP,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_nsp2_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_NSP2,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_nsp2_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_NSP2,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_HW_CLOSED_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_vdda_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_VDDA,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_OPEN_LOOP,
    .fuseMultiplier    = 8000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_1_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_WMSS_CX_1,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_2_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_WMSS_CX_2,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_mx_1_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_WMSS_MX_1,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
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
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_mx_2_enablement_2_0_2_255 =
{
    .id                = CPR_RAIL_WMSS_MX_2,
    .version           = &ver_ANY_2_0_2_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 4000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } },
    .enable            = 0,
};


static cpr_misc_cfg misc_cfg = {
    .cprRev = {.count = 1, .data = (struct raw_fuse_data[]) { {QFPROM_CORR_REG_BASE | (0x221C2A48 & (QFPROM_CORR_REG_BASE_SIZE - 1)), 17, (1<<20) | (1<<19) | (1<<18) | (1<<17)} } }
};


cpr_settings cpr_settings_lanai =
{
    .hashValue        = voltage_plan_hash_value,

    .railVVPs         = (cpr_versioned_voltage_plan*[]) { &cx_vvp, &gfx_vvp, &lpi_cx_vvp, &lpi_mx_vvp, &mm_vvp, &mss_vvp, &mx_vvp, &mxc_vvp, &nav_ldo_vvp, &nsp_vvp, &nsp2_vvp, &vdda_vvp, &wmss_cx_1_vvp, &wmss_cx_2_vvp, &wmss_mx_1_vvp, &wmss_mx_2_vvp },
    .rails            = (cpr_rail*[]) { &cpr_rail_cx_cfg, &cpr_rail_gfx_cfg, &cpr_rail_lpi_cx_cfg, &cpr_rail_lpi_mx_cfg, &cpr_rail_mm_cfg, &cpr_rail_mss_cfg, &cpr_rail_mx_cfg, &cpr_rail_mxc_cfg, &cpr_rail_nav_ldo_cfg, &cpr_rail_nsp_cfg, &cpr_rail_nsp2_cfg, &cpr_rail_vdda_cfg, &cpr_rail_wmss_cx_1_cfg, &cpr_rail_wmss_cx_2_cfg, &cpr_rail_wmss_mx_1_cfg, &cpr_rail_wmss_mx_2_cfg },
    .railsCount       = 16,

    .controllers      = (cpr_hal_controller*[]) { &cpr3_controller, &cx_cpr3_controller, &gpu_cpr_controller, &hmx_cpr3_controller, &lpass_cpr3_controller, &mmcx_cpr3_controller, &mx_cpr3_controller, &mxc_cpr3_controller, &nsp_cx_cpr3_controller },
    .controllersCount = 9,

    .enablements      = (cpr_enablement*[]) { &cpr_rail_cx_enablement_1_0_1_255, &cpr_rail_cx_enablement_2_0_2_255, &cpr_rail_gfx_enablement_1_0_1_255, &cpr_rail_gfx_enablement_2_0_2_255, &cpr_rail_lpi_cx_enablement_1_0_1_255, &cpr_rail_lpi_cx_enablement_2_0_2_255, &cpr_rail_lpi_mx_enablement_1_0_1_255, &cpr_rail_lpi_mx_enablement_2_0_2_255, &cpr_rail_mm_enablement_1_0_1_255, &cpr_rail_mm_enablement_2_0_2_255, &cpr_rail_mss_enablement_1_0_1_255, &cpr_rail_mss_enablement_2_0_2_255, &cpr_rail_mx_enablement_1_0_1_255, &cpr_rail_mx_enablement_2_0_2_255, &cpr_rail_mxc_enablement_1_0_1_255, &cpr_rail_mxc_enablement_2_0_2_255, &cpr_rail_nav_ldo_enablement_1_0_1_255, &cpr_rail_nav_ldo_enablement_2_0_2_255, &cpr_rail_nsp_enablement_1_0_1_255, &cpr_rail_nsp_enablement_2_0_2_255, &cpr_rail_nsp2_enablement_1_0_1_255, &cpr_rail_nsp2_enablement_2_0_2_255, &cpr_rail_vdda_enablement_1_0_1_255, &cpr_rail_vdda_enablement_2_0_2_255, &cpr_rail_wmss_cx_1_enablement_1_0_1_255, &cpr_rail_wmss_cx_1_enablement_2_0_2_255, &cpr_rail_wmss_cx_2_enablement_1_0_1_255, &cpr_rail_wmss_cx_2_enablement_2_0_2_255, &cpr_rail_wmss_mx_1_enablement_1_0_1_255, &cpr_rail_wmss_mx_1_enablement_2_0_2_255, &cpr_rail_wmss_mx_2_enablement_1_0_1_255, &cpr_rail_wmss_mx_2_enablement_2_0_2_255 },
    .enablementsCount = 32,

    .miscCfg          = &misc_cfg,
};

