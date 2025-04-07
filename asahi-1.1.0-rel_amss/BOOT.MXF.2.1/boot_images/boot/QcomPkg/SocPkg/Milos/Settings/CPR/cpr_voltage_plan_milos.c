/*******************************************************************************
 *
 * Copyright (c) 2024 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * THIS IS AUTO-GENERATED CPR CONFIG FILE FOR milos.
 *
 * DateTime: 2024/04/03 06:55:07
 *
 *******************************************************************************/
#include "cpr_data.h"
#include "cpr_image_target_init.h"
#include "cpr_target_hwio.h"


//hash value of Voltage Plan file (extracted all cell values)
static char voltage_plan_hash_value[] = "D6301FB2F10FE69D3ADB2583B0576689";


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


static cpr_margin_cfg margins_2040 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 0, .cprRevMax = 255, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


static cpr_quotient_cfg  quotients_12505620831 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  374 },
                                      { .ro =  7, .quotient =  514 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 12, .quotient =  172 },
                                      { .ro = 15, .quotient =  390 } },
};


static cpr_fuse_data  fuses_4437284000 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_fuse_data  fuses_7324319380 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR0_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_quotient_cfg  quotients_11759349565 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  540 },
                                      { .ro =  7, .quotient =  702 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 12, .quotient =  303 },
                                      { .ro = 15, .quotient =  555 } },
};


static cpr_fuse_data  fuses_2731049041 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION12, CPR0_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_fuse_data  fuses_6208117669 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR0_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_quotient_cfg  quotients_9072533381 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  4, .quotient =  650 },
                                      { .ro =  7, .quotient =  822 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 12, .quotient =  389 },
                                      { .ro = 15, .quotient =  655 } },
};


static cpr_fuse_data  fuses_2880129911 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR0_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_quotient_cfg  quotients_13866746960 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1070 },
                                      { .ro =  3, .quotient = 1086 },
                                      { .ro =  4, .quotient =  960 },
                                      { .ro =  7, .quotient = 1183 },
                                      { .ro =  9, .quotient =  850 },
                                      { .ro = 15, .quotient =  981 } },
};


static cpr_fuse_data  fuses_1200101346 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR0_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_quotient_cfg  quotients_11925686640 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1217 },
                                      { .ro =  3, .quotient = 1226 },
                                      { .ro =  4, .quotient = 1091 },
                                      { .ro =  7, .quotient = 1306 },
                                      { .ro =  9, .quotient =  973 },
                                      { .ro = 15, .quotient = 1126 } },
};


static cpr_fuse_data  fuses_4099729697 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION4, CPR0_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION9, CPR0_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_kv_cfg  kvs_18092672755 =
{
    .count = 10,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  283 },
                                { .ro =  3, .kv =  283 },
                                { .ro =  4, .kv =  276 },
                                { .ro =  5, .kv =  291 },
                                { .ro =  7, .kv =  294 },
                                { .ro =  8, .kv =  267 },
                                { .ro =  9, .kv =  265 },
                                { .ro = 12, .kv =  237 },
                                { .ro = 14, .kv =  266 },
                                { .ro = 15, .kv =  276 } },
};


/*
 * CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_17590951096 =
{
    .modesCount      = 8,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_18092672755,
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
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_4437284000, .quotients = &quotients_12505620831, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_7324319380, .quotients = &quotients_12505620831, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_2731049041, .quotients = &quotients_11759349565, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_6208117669, .quotients = &quotients_11759349565, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_2880129911, .quotients = &quotients_9072533381, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  688000, .freq =       0, .interplEnabled = 30} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_1200101346, .quotients = &quotients_13866746960, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  716000, .freq =       0, .interplEnabled = 57} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_4099729697, .quotients = &quotients_11925686640, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_version  ver_ANY_1_0_1_255 = { .foundry = CPR_FOUNDRY_ANY, .min = CPR_CHIPINFO_VERSION(1,0), .max = CPR_CHIPINFO_VERSION(1,255) };


static cpr_quotient_cfg  quotients_10781037841 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  441 },
                                      { .ro =  4, .quotient =  345 },
                                      { .ro =  7, .quotient =  471 },
                                      { .ro =  9, .quotient =  286 },
                                      { .ro = 15, .quotient =  354 } },
};


static cpr_fuse_data  fuses_3432308697 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR1_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR1_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_quotient_cfg  quotients_12938576787 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  479 },
                                      { .ro =  4, .quotient =  374 },
                                      { .ro =  7, .quotient =  514 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 15, .quotient =  390 } },
};


static cpr_fuse_data  fuses_2941192896 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR1_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_quotient_cfg  quotients_14784687905 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  644 },
                                      { .ro =  4, .quotient =  540 },
                                      { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 15, .quotient =  555 } },
};


static cpr_fuse_data  fuses_7162440877 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR1_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR1_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_quotient_cfg  quotients_10465291542 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  754 },
                                      { .ro =  4, .quotient =  650 },
                                      { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 15, .quotient =  655 } },
};


static cpr_fuse_data  fuses_3736573214 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR1_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_quotient_cfg  quotients_11199639922 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  901 },
                                      { .ro =  4, .quotient =  809 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 },
                                      { .ro = 15, .quotient =  814 } },
};


static cpr_fuse_data  fuses_2539577410 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR1_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR1_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_quotient_cfg  quotients_6824406993 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1003 },
                                      { .ro =  4, .quotient =  900 },
                                      { .ro =  8, .quotient =  780 },
                                      { .ro =  9, .quotient =  794 },
                                      { .ro = 15, .quotient =  914 } },
};


static cpr_fuse_data  fuses_5304261981 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION13, CPR1_TARG_VOLT_NOML1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION14, CPR1_TARG_VOLT_OFFSET_NOML1) } } },
};


/*
 * MSS Voltage Plan
 */
static cpr_voltage_plan voltage_plan_6943136607 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_18092672755,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_3432308697, .quotients = &quotients_10781037841, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_2941192896, .quotients = &quotients_12938576787, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  528000, .freq =       0, .interplEnabled = 33} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_7162440877, .quotients = &quotients_14784687905, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3736573214, .quotients = &quotients_10465291542, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  624000, .freq =       0, .interplEnabled = 56} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_2539577410, .quotients = &quotients_11199639922, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_5304261981, .quotients = &quotients_6824406993, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  812000, .floor =  688000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_fuse_data  fuses_4861723185 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR2_TARG_VOLT_SVS3) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_fuse_data  fuses_3647994843 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR2_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR2_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_fuse_data  fuses_3193954134 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR2_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR2_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_fuse_data  fuses_316863594 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR2_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_quotient_cfg  quotients_3436877286 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  816 },
                                      { .ro =  4, .quotient =  717 },
                                      { .ro =  8, .quotient =  612 },
                                      { .ro =  9, .quotient =  625 },
                                      { .ro = 15, .quotient =  721 } },
};


static cpr_fuse_data  fuses_5447391691 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR2_TARG_VOLT_SVSL2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION17, CPR2_TARG_VOLT_OFFSET_SVSL2) } } },
};


static cpr_fuse_data  fuses_1795303972 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR2_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_fuse_data  fuses_2251246530 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR2_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_quotient_cfg  quotients_11193240481 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1070 },
                                      { .ro =  4, .quotient =  960 },
                                      { .ro =  8, .quotient =  836 },
                                      { .ro =  9, .quotient =  850 },
                                      { .ro = 15, .quotient =  981 } },
};


static cpr_fuse_data  fuses_4044750710 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR2_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_quotient_cfg  quotients_7856582879 =
{
    .count = 5,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient = 1217 },
                                      { .ro =  4, .quotient = 1091 },
                                      { .ro =  8, .quotient =  957 },
                                      { .ro =  9, .quotient =  973 },
                                      { .ro = 15, .quotient = 1126 } },
};


static cpr_fuse_data  fuses_6549929555 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION15, CPR2_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION16, CPR2_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_kv_cfg  kvs_10697389140 =
{
    .count = 7,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  277 },
                                { .ro =  4, .kv =  276 },
                                { .ro =  7, .kv =  283 },
                                { .ro =  8, .kv =  267 },
                                { .ro =  9, .kv =  266 },
                                { .ro = 14, .kv =  266 },
                                { .ro = 15, .kv =  274 } },
};


/*
 * GFX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_19189496339 =
{
    .modesCount      = 9,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_10697389140,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS_D1,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_SVS_L2,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_NOMINAL_L1,
                                                    CPR_VOLTAGE_MODE_TURBO,
                                                    CPR_VOLTAGE_MODE_TURBO_L1 },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS_D1
        {.fref = 544000, .freqDelta =       0, .fuses = &fuses_4861723185, .quotients = &quotients_10781037841, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  516000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_3647994843, .quotients = &quotients_12938576787, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_3193954134, .quotients = &quotients_14784687905, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_316863594, .quotients = &quotients_10465291542, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  624000, .freq =       0, .interplEnabled = 71} } },

        // SVS_L2
        {.fref = 704000, .freqDelta =       0, .fuses = &fuses_5447391691, .quotients = &quotients_3436877286, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  640000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_1795303972, .quotients = &quotients_11199639922, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  660000, .freq =       0, .interplEnabled = 15} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_2251246530, .quotients = &quotients_6824406993, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  688000, .freq =       0, .interplEnabled = 41} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4044750710, .quotients = &quotients_11193240481, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  716000, .freq =       0, .interplEnabled = 63} } },

        // TURBO_L1
        {.fref = 856000, .freqDelta =       0, .fuses = &fuses_6549929555, .quotients = &quotients_7856582879, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  904000, .floor =  760000, .freq =       0, .interplEnabled = 0} } }},
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
static cpr_voltage_plan voltage_plan_11429810818 =
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
        {.fref = 352000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  352000, .floor =  352000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 704000, .freqDelta =       0, .fuses = &fuses_2495965546, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  688000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_2244135014, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 892000, .freqDelta =       0, .fuses = &fuses_876138120, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  952000, .floor =  892000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_quotient_cfg  quotients_5577016373 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient =  755 },
                                      { .ro =  4, .quotient =  526 },
                                      { .ro =  6, .quotient =  588 } },
};


static cpr_fuse_data  fuses_2443258166 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION6, CPR4_TARG_VOLT_OFFSET_SVS3) } } },
};


static cpr_fuse_data  fuses_1214727534 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_fuse_data  fuses_6216256256 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR4_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_quotient_cfg  quotients_5255497865 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient =  893 },
                                      { .ro =  4, .quotient =  630 },
                                      { .ro =  6, .quotient =  711 } },
};


static cpr_fuse_data  fuses_184945056 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION21, CPR4_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_fuse_data  fuses_1683797650 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR4_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
};


static cpr_fuse_data  fuses_3363652595 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR4_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR4_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_quotient_cfg  quotients_7389087871 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1050 },
                                      { .ro =  4, .quotient =  750 },
                                      { .ro =  6, .quotient =  851 } },
};


static cpr_fuse_data  fuses_3662504792 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR4_TARG_VOLT_OFFSET_NOML1) } } },
};


static cpr_quotient_cfg  quotients_11191954126 =
{
    .count = 3,
    .quots = (cpr_quotient[]) { { .ro =  0, .quotient = 1151 },
                                      { .ro =  4, .quotient =  829 },
                                      { .ro =  6, .quotient =  943 } },
};


static cpr_fuse_data  fuses_6008565036 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION19, CPR4_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR4_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_fuse_data  fuses_5309333480 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION18, CPR4_TARG_VOLT_TURL1) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION20, CPR4_TARG_VOLT_OFFSET_TURL1) } } },
};


static cpr_kv_cfg  kvs_7487955074 =
{
    .count = 4,
    .kvs   = (cpr_kv[]) { { .ro =  0, .kv =  381 },
                                { .ro =  3, .kv =  261 },
                                { .ro =  4, .kv =  298 },
                                { .ro =  6, .kv =  335 } },
};


/*
 * MX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_17920376352 =
{
    .modesCount      = 10,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_7487955074,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS_D1,
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
        {.fref = 504000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  552000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS_D1
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_2443258166, .quotients = &quotients_5577016373, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_1214727534, .quotients = &quotients_5577016373, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 716000, .freqDelta =       0, .fuses = &fuses_6216256256, .quotients = &quotients_5577016373, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  716000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_184945056, .quotients = &quotients_5255497865, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L2
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_1683797650, .quotients = &quotients_5255497865, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3363652595, .quotients = &quotients_5255497865, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL_L1
        {.fref = 768000, .freqDelta =       0, .fuses = &fuses_3662504792, .quotients = &quotients_7389087871, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  752000, .freq =       0, .interplEnabled = 33} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_6008565036, .quotients = &quotients_11191954126, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } },

        // TURBO_L1
        {.fref = 832000, .freqDelta =       0, .fuses = &fuses_5309333480, .quotients = &quotients_11191954126, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  884000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_fuse_data  fuses_3701143162 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR6_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = NULL,
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
static cpr_voltage_plan voltage_plan_10179970396 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
                                                    CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_SVS_L1,
                                                    CPR_VOLTAGE_MODE_NOMINAL,
                                                    CPR_VOLTAGE_MODE_TURBO },
    .modes           = (struct cpr_voltage_data[]) {
        // RETENTION
        {.fref = 504000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = NULL,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  552000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // LOW_SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 752000, .freqDelta =       0, .fuses = &fuses_3701143162, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  752000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_3402849139, .quotients = NULL, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  848000, .floor =  800000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_quotient_cfg  quotients_14894021530 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  479 },
                                      { .ro =  4, .quotient =  374 },
                                      { .ro =  8, .quotient =  305 },
                                      { .ro =  9, .quotient =  312 },
                                      { .ro = 13, .quotient =  238 },
                                      { .ro = 15, .quotient =  390 } },
};


static cpr_fuse_data  fuses_5891593934 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION6, CPR7_TARG_VOLT_SVS2) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_OFFSET_SVS2) } } },
};


static cpr_quotient_cfg  quotients_15093661209 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  644 },
                                      { .ro =  4, .quotient =  540 },
                                      { .ro =  8, .quotient =  454 },
                                      { .ro =  9, .quotient =  462 },
                                      { .ro = 13, .quotient =  405 },
                                      { .ro = 15, .quotient =  555 } },
};


static cpr_fuse_data  fuses_4335291917 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_SVS) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_OFFSET_SVS) } } },
};


static cpr_quotient_cfg  quotients_12411622985 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  754 },
                                      { .ro =  4, .quotient =  650 },
                                      { .ro =  8, .quotient =  553 },
                                      { .ro =  9, .quotient =  564 },
                                      { .ro = 13, .quotient =  518 },
                                      { .ro = 15, .quotient =  655 } },
};


static cpr_fuse_data  fuses_3732569836 =
{
    .volt       = NULL,
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_OFFSET_SVSL1) } } },
};


static cpr_quotient_cfg  quotients_11984317008 =
{
    .count = 6,
    .quots = (cpr_quotient[]) { { .ro =  2, .quotient =  901 },
                                      { .ro =  4, .quotient =  809 },
                                      { .ro =  8, .quotient =  695 },
                                      { .ro =  9, .quotient =  709 },
                                      { .ro = 13, .quotient =  670 },
                                      { .ro = 15, .quotient =  814 } },
};


static cpr_fuse_data  fuses_3376468245 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION24, CPR7_TARG_VOLT_NOM) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR7_TARG_VOLT_OFFSET_NOM) } } },
};


static cpr_fuse_data  fuses_4764881353 =
{
    .volt       = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR7_TARG_VOLT_TUR) } } },
    .quot       = NULL,
    .rosel      = NULL,
    .quotOffset = NULL,
    .voltOffset = (cpr_fuse[]) { {.count = 1, .data = (struct raw_fuse_data[]) { CPR_FUSE_MAPPING(CALIBRATION23, CPR7_TARG_VOLT_OFFSET_TUR) } } },
};


static cpr_kv_cfg  kvs_17733211176 =
{
    .count = 7,
    .kvs   = (cpr_kv[]) { { .ro =  2, .kv =  286 },
                                { .ro =  4, .kv =  278 },
                                { .ro =  6, .kv =  278 },
                                { .ro =  8, .kv =  269 },
                                { .ro =  9, .kv =  267 },
                                { .ro = 13, .kv =  275 },
                                { .ro = 15, .kv =  279 } },
};


/*
 * LPI_CX Voltage Plan
 */
static cpr_voltage_plan voltage_plan_15723194478 =
{
    .modesCount      = 6,
    .tempAdjCfg      = NULL,
    .kvCfg           = &kvs_17733211176,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_RETENTION,
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

        // LOW_SVS
        {.fref = 572000, .freqDelta =       0, .fuses = &fuses_5891593934, .quotients = &quotients_14894021530, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  528000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 628000, .freqDelta =       0, .fuses = &fuses_4335291917, .quotients = &quotients_15093661209, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  568000, .freq =       0, .interplEnabled = 0} } },

        // SVS_L1
        {.fref = 684000, .freqDelta =       0, .fuses = &fuses_3732569836, .quotients = &quotients_12411622985, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  624000, .freq =       0, .interplEnabled = 36} } },

        // NOMINAL
        {.fref = 728000, .freqDelta =       0, .fuses = &fuses_3376468245, .quotients = &quotients_11984317008, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  660000, .freq =       0, .interplEnabled = 0} } },

        // TURBO
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_4764881353, .quotients = &quotients_11193240481, .margins = &margins_2040,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  852000, .floor =  716000, .freq =       0, .interplEnabled = 0} } }},
};


static cpr_margin_cfg margins_17 = {
    .count = 1,
    .data = (cpr_margin_data[]) { { .vpIdMin = 0, .vpIdMax = 0,.cprRevMin = 1, .cprRevMax = 1, .openLoop =       0, .closedLoop =       0, .agingOffset =       0, .sltOffset =       0, .maxFloorToCeil =      0 } }
};


/*
 * WMSS_CX_1 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_5735596638 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 592000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_17,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  648000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 672000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_17,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  720000, .floor =  592000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_17,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  864000, .floor =  712000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * WMSS_CX_2 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_5513991167 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 588000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_17,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  588000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 668000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_17,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  728000, .floor =  596000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 744000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_17,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  800000, .floor =  652000, .freq =       0, .interplEnabled = 0} } }},
};


/*
 * WMSS_CX_3 Voltage Plan
 */
static cpr_voltage_plan voltage_plan_6336402836 =
{
    .modesCount      = 3,
    .tempAdjCfg      = NULL,
    .kvCfg           = NULL,
    .supportedModes  = (cpr_voltage_mode[]) { CPR_VOLTAGE_MODE_LOW_SVS,
                                                    CPR_VOLTAGE_MODE_SVS,
                                                    CPR_VOLTAGE_MODE_NOMINAL },
    .modes           = (struct cpr_voltage_data[]) {
        // LOW_SVS
        {.fref = 588000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_17,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  644000, .floor =  504000, .freq =       0, .interplEnabled = 0} } },

        // SVS
        {.fref = 668000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_17,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  724000, .floor =  596000, .freq =       0, .interplEnabled = 0} } },

        // NOMINAL
        {.fref = 800000, .freqDelta =       0, .fuses = &fuses_0, .quotients = NULL, .margins = &margins_17,
         .marginTempBands = {0},
         .subModesCount   = 1,
         .subModes        = (cpr_freq_data[]){ {.ceiling =  864000, .floor =  712000, .freq =       0, .interplEnabled = 0} } }},
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

/*
 * Versioned Voltage Plans
 */

static cpr_versioned_voltage_plan cx_vvp = {
    .rail     = CPR_RAIL_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_17590951096 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan mss_vvp = {
    .rail     = CPR_RAIL_MSS,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_6943136607 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan gfx_vvp = {
    .rail     = CPR_RAIL_GFX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_19189496339 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan vdda_vvp = {
    .rail     = CPR_RAIL_VDDA,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_11429810818 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan mx_vvp = {
    .rail     = CPR_RAIL_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_17920376352 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_mx_vvp = {
    .rail     = CPR_RAIL_LPI_MX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_10179970396 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan lpi_cx_vvp = {
    .rail     = CPR_RAIL_LPI_CX,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_15723194478 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_1_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_1,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_5735596638 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_2_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_2,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_5513991167 },
     },
    .count    = 1,
    .agingCfg = NULL
};


static cpr_versioned_voltage_plan wmss_cx_3_vvp = {
    .rail     = CPR_RAIL_WMSS_CX_3,
    .list     = (struct voltage_plan_list[]) {
        { .version = &ver_ANY_1_0_1_255, .cfg = &voltage_plan_6336402836 },
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 },
    .sensorsCount = 25,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49 },
    .sensorsCount = 50,
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
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8 },
    .sensorsCount = 9,
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
    .sensors      = (uint8[]){ 0,1,2 },
    .sensorsCount = 3,
};


static cpr_hal_thread  lpi_cx_thread = {
    .id   = 0,
    .cfg  = &lpi_cx_thread_cfg,
};


static cpr_hal_thread_cfg mx_thread_cfg = {
    .upThresh     = 2,
    .dnThresh     = 2,
    .consecUp     = 0,
    .consecDn     = 0,
    .sensors      = (uint8[]){ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48 },
    .sensorsCount = 49,
};


static cpr_hal_thread  mx_thread = {
    .id   = 0,
    .cfg  = &mx_thread_cfg,
};


/*
 * CPR Controller Config
 */

static cpr_hal_controller_cfg cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 13,
    .sensorsTotal        = 25,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  cpr3_controller = {
    .base                = 0x2bd80000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &mss_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg cx_cpr3_controller_cfg = {
    .stepQuotMin         = 8,
    .stepQuotMax         = 12,
    .sensorsTotal        = 50,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
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
    .sensorsTotal        = 9,
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
    .sensorsTotal        = 3,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
    .refClk              = NULL,
    .ahbClk              = NULL,
};


static cpr_hal_controller  lpass_cpr3_controller = {
    .base                = 0x3430000,
    .type                = CPR_CONTROLLER_TYPE_HW_CL_ONLY,
    .cfg                 = &lpass_cpr3_controller_cfg,
    .threads             = (cpr_hal_thread*[]){ &lpi_cx_thread },
    .threadsCount        = 1,
};


static cpr_hal_controller_cfg mx_cpr3_controller_cfg = {
    .stepQuotMin         = 7,
    .stepQuotMax         = 13,
    .sensorsTotal        = 49,
    .bypassSensors       = NULL,
    .bypassSensorsCount  = 0,
    .disableSensors      = NULL,
    .disableSensorsCount = 0,
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


static cpr_rail cpr_rail_nav_ldo_cfg = {
    .id               = CPR_RAIL_NAV_LDO,
    .name             = "NAV_LDO",
    .hal              = { .controller = NULL, .thread = NULL },
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


static cpr_rail cpr_rail_wmss_cx_3_cfg = {
    .id               = CPR_RAIL_WMSS_CX_3,
    .name             = "WMSS_CX_3",
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
    .funcId            = CPR_INIT_NONE,
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
    .funcId            = CPR_INIT_NONE,
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
    .funcId            = CPR_INIT_NONE,
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
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 8000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 1,
};


static cpr_enablement cpr_rail_mss_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_MSS,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
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
    .funcId            = CPR_INIT_NONE,
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


static cpr_enablement cpr_rail_vdda_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_VDDA,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
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
    .stepSize          = 8000,
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
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_enablement cpr_rail_wmss_cx_3_enablement_1_0_1_255 =
{
    .id                = CPR_RAIL_WMSS_CX_3,
    .version           = &ver_ANY_1_0_1_255,
    .funcId            = CPR_INIT_NONE,
    .fuseMultiplier    = 10000,
    .stepSize          = 8000,
    .railCPRRevFuse    = {.count = 1, .data = (struct raw_fuse_data[]) {
                   {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } },
    .enable            = 0,
};


static cpr_misc_cfg misc_cfg = {
    .cprRev = {.count = 1, .data = (struct raw_fuse_data[]) { {FUSE_CONTROLLER_SW_RANGE4_REG_BASE | (0x221C8BC8 & (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE - 1)), 24, (1<<27) | (1<<26) | (1<<25) | (1<<24)} } }
};


cpr_settings cpr_settings_milos =
{
    .hashValue        = voltage_plan_hash_value,

    .railVVPs         = (cpr_versioned_voltage_plan*[]) { &cx_vvp, &gfx_vvp, &lpi_cx_vvp, &lpi_mx_vvp, &mss_vvp, &mx_vvp, &nav_ldo_vvp, &vdda_vvp, &wmss_cx_1_vvp, &wmss_cx_2_vvp, &wmss_cx_3_vvp },
    .rails            = (cpr_rail*[]) { &cpr_rail_cx_cfg, &cpr_rail_gfx_cfg, &cpr_rail_lpi_cx_cfg, &cpr_rail_lpi_mx_cfg, &cpr_rail_mss_cfg, &cpr_rail_mx_cfg, &cpr_rail_nav_ldo_cfg, &cpr_rail_vdda_cfg, &cpr_rail_wmss_cx_1_cfg, &cpr_rail_wmss_cx_2_cfg, &cpr_rail_wmss_cx_3_cfg },
    .railsCount       = 11,

    .controllers      = (cpr_hal_controller*[]) { &cpr3_controller, &cx_cpr3_controller, &gpu_cpr_controller, &lpass_cpr3_controller, &mx_cpr3_controller },
    .controllersCount = 5,

    .enablements      = (cpr_enablement*[]) { &cpr_rail_cx_enablement_1_0_1_255, &cpr_rail_gfx_enablement_1_0_1_255, &cpr_rail_lpi_cx_enablement_1_0_1_255, &cpr_rail_lpi_mx_enablement_1_0_1_255, &cpr_rail_mss_enablement_1_0_1_255, &cpr_rail_mx_enablement_1_0_1_255, &cpr_rail_nav_ldo_enablement_1_0_1_255, &cpr_rail_vdda_enablement_1_0_1_255, &cpr_rail_wmss_cx_1_enablement_1_0_1_255, &cpr_rail_wmss_cx_2_enablement_1_0_1_255, &cpr_rail_wmss_cx_3_enablement_1_0_1_255 },
    .enablementsCount = 11,

    .miscCfg          = &misc_cfg,
};

