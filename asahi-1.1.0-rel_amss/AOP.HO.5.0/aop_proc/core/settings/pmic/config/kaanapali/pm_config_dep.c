
/*! \file pm_config_dep.c
 *
 *  \brief This file contains pmic resource dependencies.
 *
 *  &copy; Copyright 2016 - 2022 Qualcomm Technologies Inc, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/dev/aop.ho/5.0/kparsha.aop.ho.5.0.aop50_pakala_base/aop_proc/core/settings/pmic/config/lanai/pm_config_dep.c#1 $
 Version : 1.0
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_config_interface.h"

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource bob_b[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"bobb1",NULL},
  {"bobb2",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_b[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldob1",NULL},
  {"ldob2",NULL},
  {"ldob3",NULL},
  {"ldob4",NULL},
  {"ldob5",NULL},
  {"ldob6",NULL},
  {"ldob7",NULL},
  {"ldob8",NULL},
  {"ldob9",NULL},
  {"ldob10",NULL},
  {"ldob11",NULL},
  {"ldob12",NULL},
  {"ldob13",NULL},
  {"ldob14",NULL},
  {"ldob15","vrm.qf"},
  {"ldob16",NULL},
  {"ldob17",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_d[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldod1",NULL},
  {"ldod2",NULL},
  {"ldod3",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_f[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldof1",NULL},
  {"ldof2",NULL},
  {"ldof3",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_g[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldog1",NULL},
  {"ldog2",NULL},
  {"ldog3","vrm.qlnk"},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_i[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldoi1",NULL},
  {"ldoi2",NULL},
  {"ldoi3",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_j[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldoj1",NULL},
  {"ldoj2",NULL},
  {"ldoj3","vrm.lmx"},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_k[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldok1",NULL},
  {"ldok2",NULL},
  {"ldok3",NULL},
  {"ldok4",NULL},
  {"ldok5",NULL},
  {"ldok6",NULL},
  {"ldok7",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_m[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldom1",NULL},
  {"ldom2",NULL},
  {"ldom3",NULL},
  {"ldom4",NULL},
  {"ldom5",NULL},
  {"ldom6",NULL},
  {"ldom7",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_n[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldon1",NULL},
  {"ldon2",NULL},
  {"ldon3",NULL},
  {"ldon4",NULL},
  {"ldon5",NULL},
  {"ldon6",NULL},
  {"ldon7",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_d[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpd1",NULL},
  {"smpd2","vrm.mxg"},
  {"smpd3",NULL},
  {"smpd4",NULL},
  {"smpd5","vrm.gfx"},
  {"smpd6",NULL},
  {"smpd7",NULL},
  {"smpd8",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_f[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpf1",NULL},
  {"smpf2",NULL},
  {"smpf3",NULL},
  {"smpf4",NULL},
  {"smpf5",NULL},
  {"smpf6",NULL},
  {"smpf7",NULL},
  {"smpf8","vrm.mx"},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_g[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpg1",NULL},
  {"smpg2","vrm.ebi"},
  {"smpg3",NULL},
  {"smpg4",NULL},
  {"smpg5","vrm.mss"},
  {"smpg6",NULL},
  {"smpg7","vrm.nsp1"},
  {"smpg8",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_i[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpi1","vrm.nsp2"},
  {"smpi2",NULL},
  {"smpi3","vrm.mmcx"},
  {"smpi4",NULL},
  {"smpi5","vrm.lcx"},
  {"smpi6","vrm.mxc"},
  {"smpi7",NULL},
  {"smpi8",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_j[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpj1","vrm.cx"},
  {"smpj2",NULL},
  {"smpj3",NULL},
  {"smpj4",NULL},
  {"smpj5",NULL},
  {"smpj6",NULL},
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource clk_a[] =
{
  {NULL,NULL}, // this is invalid place holder
   {NULL,NULL}, //51
   {NULL,NULL}, //52
   {NULL,NULL}, //53
  {"clka1","rfclka1" },
  {"clka2","rfclka2" },
  {"clka3","rfclka3" },
  {"clka4", NULL },
  {"clka5","rfclka5" },
  {"clka6","vrm.xob" },
  {"clka7", NULL},
  {"clka8", NULL},
  {"clka9", NULL},
  { NULL, NULL},
  {"clka11", NULL},
  { NULL, NULL},
  { NULL, NULL},
};

// Component Resource Child Depend Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *bob1_b_child_dep[] =
{
  &ldo_b[2],
  &ldo_b[5],
  &ldo_b[6],
  &ldo_b[7],
  &ldo_b[8],
  &ldo_b[9],
  &ldo_b[13],
  &ldo_b[14],
  &ldo_b[16],
  &ldo_m[6],
  &ldo_m[7],
  &ldo_n[7],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *bob2_b_child_dep[] =
{
  &ldo_b[17],
  &ldo_m[3],
  &ldo_m[4],
  &ldo_n[5],
  &ldo_n[6],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps1_d_child_dep[] =
{
  &ldo_d[2],
  &ldo_d[3],
  &ldo_f[1],
  &ldo_g[1],
  &ldo_j[1],
  &ldo_j[3],
  &ldo_k[1],
  &ldo_k[2],
  &ldo_k[5],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps3_d_child_dep[] =
{
  &ldo_k[3],
  &ldo_k[4],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps4_d_child_dep[] =
{
  &ldo_k[7],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps3_g_child_dep[] =
{
  &ldo_b[1],
  &ldo_b[4],
  &ldo_b[10],
  &ldo_b[12],
  &ldo_b[15],
  &ldo_f[3],
  &ldo_g[2],
  &ldo_k[6],
  &ldo_m[5],
  &ldo_n[3],
  &ldo_n[4],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps7_i_child_dep[] =
{
  &ldo_b[3],
  &ldo_b[11],
  &ldo_d[1],
  &ldo_f[2],
  &ldo_i[1],
  &ldo_i[2],
  &ldo_j[2],
  &ldo_m[1],
  &ldo_m[2],
  &ldo_n[1],
  &ldo_n[2],
};
// Component Resource Dependency Information
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info bob_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // BOB1
   {
      NULL,// parent resource
      bob1_b_child_dep,// child resource dependencies
      12,  // num vreg children
      0,  // num xob children
   },
   // BOB2
   {
      NULL,// parent resource
      bob2_b_child_dep,// child resource dependencies
      5,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info clock_dep_a[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // CLK1_RF
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK2_RF
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK3_RF
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK4_RF
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK5_RF
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK6_LN
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK7_LN
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK8_LN
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK9_LN
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // EMPTY
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // CLK11_DIV
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // EMPTY
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // SLEEP_CLK1
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // SLEEP_CLK1
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // SLEEP_CLK1
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // SLEEP_CLK1
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L01B
   {
      &smps_g[3],// parent resource S3G
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L02B
   {
      &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L03B
   {
      &smps_i[7],// parent resource S7I
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L04B
   {
      &smps_g[3],// parent resource S3G
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L05B
   {
      &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L06B
   {
      &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L07B
   {
      &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L08B
   {
      &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L09B
   {
      &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L10B
   {
      &smps_g[3],// parent resource S3G
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L11B
   {
      &smps_i[7],// parent resource S7I
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L12B
   {
      &smps_g[3],// parent resource S3G
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L13B
   {
      &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L14B
   {
      &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L15B
   {
      &smps_g[3],// parent resource S3G
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L16B
   {
      &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L17B
   {
      &bob_b[2],// parent resource BOB2
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_d[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1D
   {
      &smps_i[7],// parent resource S7I
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2D
   {
      &smps_d[1],// parent resource S1D
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3D
   {
      &smps_d[1],// parent resource S1D
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_f[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1F
   {
      &smps_d[1],// parent resource S1D
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2F
   {
      &smps_i[7],// parent resource S7I
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3F
   {
      &smps_g[3],// parent resource S3G
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_g[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1G
   {
      &smps_d[1],// parent resource S1D
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2G
   {
      &smps_g[3],// parent resource S3G
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_i[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1I
   {
      &smps_i[7],// parent resource S7I
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2I
   {
      &smps_i[7],// parent resource S7I
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_j[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1J
   {
      &smps_d[1],// parent resource S1D
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2J
   {
      &smps_i[7],// parent resource S7I
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3J
   {
      &smps_d[1],// parent resource S1D
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_k[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1K
   {
      &smps_d[1],// parent resource S1D
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2K
   {
      &smps_d[1],// parent resource S1D
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3K
   {
      &smps_d[3],// parent resource S3D
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4K
   {
      &smps_d[3],// parent resource S3D
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5K
   {
      &smps_d[1],// parent resource S1D
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6K
   {
      &smps_g[3],// parent resource S3G
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7K
   {
      &smps_d[4],// parent resource S4D
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_m[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1M
   {
      &smps_i[7],// parent resource S7I
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2M
   {
      &smps_i[7],// parent resource S7I
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3M
   {
      &bob_b[2],// parent resource BOB2
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4M
   {
      &bob_b[2],// parent resource BOB2
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5M
   {
      &smps_g[3],// parent resource S3G
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6M
   {
      &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7M
   {
      &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_n[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1N
   {
      &smps_i[7],// parent resource S7I
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2N
   {
      &smps_i[7],// parent resource S7I
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3N
   {
      &smps_g[3],// parent resource S3G
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4N
   {
      &smps_g[3],// parent resource S3G
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5N
   {
      &bob_b[2],// parent resource BOB2
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6N
   {
      &bob_b[2],// parent resource BOB2
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7N
   {
      &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_d[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1D
   {
      NULL,// parent resource
      smps1_d_child_dep,// child resource dependencies
      9,  // num vreg children
      0,  // num xob children
   },
   // S2D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3D
   {
      NULL,// parent resource
      smps3_d_child_dep,// child resource dependencies
      2,  // num vreg children
      0,  // num xob children
   },
   // S4D
   {
      NULL,// parent resource
      smps4_d_child_dep,// child resource dependencies
      1,  // num vreg children
      0,  // num xob children
   },
   // S5D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S8D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_f[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // **S7F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // **S8F
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_g[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3G
   {
      NULL,// parent resource
      smps3_g_child_dep,// child resource dependencies
      11,  // num vreg children
      0,  // num xob children
   },
   // S4G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S8G
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_i[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S7I
   {
      NULL,// parent resource
      smps7_i_child_dep,// child resource dependencies
      11,  // num vreg children
      0,  // num xob children
   },
   // S8I
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_j[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6J
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
// resource dependency info
__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* smps_dep[] =
{
  NULL,
  NULL,
  NULL,
  smps_dep_d,
  NULL,
  smps_dep_f,
  smps_dep_g,
  NULL,
  smps_dep_i,
  smps_dep_j,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* ldo_dep[] =
{
  NULL,
  ldo_dep_b,
  NULL,
  ldo_dep_d,
  NULL,
  ldo_dep_f,
  ldo_dep_g,
  NULL,
  ldo_dep_i,
  ldo_dep_j,
  ldo_dep_k,
  NULL,
  ldo_dep_m,
  ldo_dep_n,
  NULL,
  NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* bob_dep[] =
{
  NULL,
  bob_dep_b,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* clk_dep[] =
{
  clock_dep_a,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* vs_dep[] =
{
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};


// resource info
__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* smps_rsrc[] =
{
  NULL,
  NULL,
  NULL,
  smps_d,
  NULL,
  smps_f,
  smps_g,
  NULL,
  smps_i,
  smps_j,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* ldo_rsrc[] =
{
  NULL,
  ldo_b,
  NULL,
  ldo_d,
  NULL,
  ldo_f,
  ldo_g,
  NULL,
  ldo_i,
  ldo_j,
  ldo_k,
  NULL,
  ldo_m,
  ldo_n,
  NULL,
  NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* bob_rsrc[] =
{
  NULL,
  bob_b,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* clk_rsrc[] =
{
  clk_a,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

