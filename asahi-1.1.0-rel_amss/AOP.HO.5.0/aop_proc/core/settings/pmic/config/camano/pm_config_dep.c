#
/*! \file pm_config_dep.c
 *
 *  \brief This file contains pmic resource dependencies.
 *
 *  &copy; Copyright 2016 - 2023 Qualcomm Technologies Inc, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: $
 Version : 1.0
 
 when       who     what, where, why
--------   	---     ----------------------------------------------------------
01/23/23	bde		Camano initial version based on PG R3P0
04/12/23	bde		Camano option decode specific changes
05/06/23	bde		Dummy clk peripherals added to avoid out of bound access in stub
07/06/23	bde		PG R6: Unused dependencies removed
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
  {"ldob7","vrm.qf"},
  {"ldob8",NULL},
  {"ldob9",NULL},
  {"ldob10",NULL},
  {"ldob11",NULL},
  {"ldob12",NULL},
  {"ldob13",NULL},
  {"ldob14",NULL},
  {"ldob15",NULL},
  {"ldob16",NULL},
  {"ldob17",NULL},
  {"ldob18",NULL},
  {"ldob19",NULL},
  {"ldob20",NULL},
  {"ldob21",NULL},
  {"ldob22",NULL},
  {"ldob23",NULL},
  {"ldob24",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_c[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldoc1",NULL},
  {"ldoc2","vrm.lcx"},
  {"ldoc3","vrm.lmx"},
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
static pm_pwr_resource ldo_e[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldoe1",NULL},
  {"ldoe2",NULL},
  {"ldoe3",NULL},
  {"ldoe4",NULL},
  {"ldoe5",NULL},
  {"ldoe6",NULL},
  {"ldoe7",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource ldo_f[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"ldof1",NULL},
  {"ldof2",NULL},
  {"ldof3",NULL},
  {"ldof4",NULL},
  {"ldof5",NULL},
  {"ldof6",NULL},
  {"ldof7",NULL},
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
static pm_pwr_resource
clk_a[] =
{
   {NULL,NULL}, // this is invalid place holder
   {NULL,NULL}, //51
   {NULL,NULL}, //52
   {NULL,NULL}, //53
   {"clka1","rfclka1"}, //54
   {"clka2","rfclka2"}, //55
   {"clka3","rfclka3"}, //56
   {"clka4","rfclka4"}, //57
   {"clka5",NULL}, //58
   {"clka6","vrm.xob"}, //59
   {"clka7",NULL}, //5a
   {"clka8",NULL}, //5b
   {"clka9",NULL},  //5c
   {NULL,NULL},  //5d
   {"clka11",NULL},   //5e
   {NULL,NULL},
   {NULL,NULL},
   {NULL,NULL},	//dummy
   {NULL,NULL},	//dummy
};

__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_b[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpb1",NULL},
  {"smpb2",NULL},
  {"smpb3",NULL},
  {"smpb4",NULL},
  {"smpb5","vrm.mx"},
  {"smpb6",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_c[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpc1","vrm.cx"},
  {"smpc2",NULL},
  {"smpc3",NULL},
  {"smpc4","vrm.mss"},
  {"smpc5",NULL},
  {"smpc6","vrm.mxc"},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_d[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpd1","vrm.gfx"},
  {"smpd2",NULL},
  {"smpd3","vrm.ebi"},
  {"smpd4",NULL},
  {"smpd5",NULL},
  {"smpd6",NULL},
};


__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource smps_e[] =
{
  {NULL,NULL},  // this is invalid place holder
  {"smpe1",NULL},
  {"smpe2",NULL},
  {"smpe3",NULL},
};


// Component Resource Child Depend Structure Creation
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *bob1_b_child_dep[] =
{
  &ldo_b[12],
  &ldo_b[13],
  &ldo_b[14],
//  &ldo_b[15],
  &ldo_b[16],
  &ldo_b[17],
  &ldo_b[18],
  &ldo_b[19],
  &ldo_b[20],
  &ldo_b[21],
  &ldo_b[22],
  &ldo_b[23],
//  &ldo_e[7],
  &ldo_m[3],
  &ldo_m[4],
  &ldo_m[6],
  &ldo_m[7],
  &ldo_n[5],
  &ldo_n[7]
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps1_b_child_dep_ufs3[] =
{
  &ldo_b[7],
  &ldo_b[8],
  &ldo_b[9],
  &ldo_b[10],
  &ldo_b[11],
  &ldo_e[4],
  &ldo_f[6],
  &ldo_m[5],
  &ldo_n[3],
  &ldo_n[4],
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource *smps1_b_child_dep[] =
{
  &ldo_b[7],
  &ldo_b[8],
  &ldo_b[9],
  &ldo_b[10],
  &ldo_b[11],
  &ldo_d[2],
  &ldo_e[4],
  &ldo_f[6],
  &ldo_m[5],
  &ldo_n[3],
  &ldo_n[4],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps2_b_child_dep_ufs3[] =
{
//  &ldo_b[4], //1p2 qref
  &ldo_b[5],
//  &ldo_b[6],
  &ldo_d[2],
  &ldo_d[3],
  &ldo_f[3],
  &ldo_f[4],
  &ldo_m[1],
  &ldo_m[2],
  &ldo_n[1],
  &ldo_n[2],
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource *smps2_b_child_dep[] =
{
//  &ldo_b[4], //1p2 qref
  &ldo_b[5],
//  &ldo_b[6],
  &ldo_d[3],
  &ldo_f[3],
  &ldo_f[4],
  &ldo_m[1],
  &ldo_m[2],
  &ldo_n[1],
  &ldo_n[2],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps3_b_child_dep[] =
{
  &ldo_b[1],
//  &ldo_b[2], //0p9 qref
  &ldo_b[3],
  &ldo_c[3],
  &ldo_d[1],
  &ldo_f[1],
  &ldo_f[2],
  &ldo_f[5],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps1_e_child_dep[] =
{
  &ldo_e[5],
  &ldo_e[6],
};
__attribute__((section("pm_ddr_reclaim_pool")))
static pm_pwr_resource *smps2_e_child_dep[] =
{
  &ldo_e[2],
  &ldo_e[3],
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
      17,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1B
   {
      &smps_b[3],// parent resource S3B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2B
   {
      NULL, //&smps_b[3],// parent resource S3B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3B
   {
      &smps_b[3],// parent resource S3B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4B
   {
      NULL, //&smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5B
   {
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6B
   {
      NULL,	//Azura VDDA &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7B
   {
      &smps_b[1],// parent resource S1B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L8B
   {
      &smps_b[1],// parent resource S1B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L9B
   {
      &smps_b[1],// parent resource S1B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L10B
   {
      &smps_b[1],// parent resource S1B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L11B
   {
      &smps_b[1],// parent resource S1B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L12B
   {
	  &bob_b[1],// parent resource BOB1
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L13B
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L14B
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L15B
   {
      NULL,//&bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L16B
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L17B
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L18B
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L19B
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L20B
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L21B
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L22B
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L23B
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L24B
   {
	  NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_c[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3C
   {
      &smps_b[3],// parent resource S3B
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
      &smps_b[3],// parent resource S3B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2D
   {
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3D
   {
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info ldo_dep_e[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // L1E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2E
   {
      &smps_e[2],// parent resource S2E
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3E
   {
      &smps_e[2],// parent resource S2E
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4E
   {
      &smps_b[1],// parent resource S1B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5E
   {
      &smps_e[1],// parent resource S1E
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6E
   {
      &smps_e[1],// parent resource S1E
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7E
   {
      NULL,// parent resource
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
      &smps_b[3],// parent resource S3B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2F
   {
      &smps_b[3],// parent resource S3B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3F
   {
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4F
   {
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5F
   {
      &smps_b[3],// parent resource S3B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6F
   {
      &smps_b[1],// parent resource S1B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7F
   {
      NULL,// parent resource
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
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2M
   {
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3M
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4M
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5M
   {
      &smps_b[1],// parent resource S1B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6M
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7M
   {
	  &bob_b[1],// parent resource BOB_B
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
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L2N
   {
      &smps_b[2],// parent resource S2B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L3N
   {
      &smps_b[1],// parent resource S1B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L4N
   {
      &smps_b[1],// parent resource S1B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L5N
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L6N
   {
      NULL,// parent resource BOB_B, removed, as LDO is unused
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // L7N
   {
	  &bob_b[1],// parent resource BOB_B
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_b[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1B
   {
      NULL,// parent resource
      smps1_b_child_dep_ufs3,// child resource dependencies
      10,  // num vreg children
      0,  // num xob children
   },
   // S2B
   {
      NULL,// parent resource
      smps2_b_child_dep_ufs3,// child resource dependencies
      9,  // num vreg children
      0,  // num xob children
   },
   // S3B
   {
      NULL,// parent resource
      smps3_b_child_dep,// child resource dependencies
      7,  // num vreg children
      0,  // num xob children
   },
   // S4B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6B
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_c[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S2C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S3C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S5C
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S6C
   {
      NULL,// parent resource
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
      NULL,// child resource dependencies
      0,  // num vreg children
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
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // S4D
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
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
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info smps_dep_e[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // S1E
   {
      NULL,// parent resource
      smps1_e_child_dep,// child resource dependencies
      2,  // num vreg children
      0,  // num xob children
   },
   // S2E
   {
      NULL,// parent resource
      smps2_e_child_dep,// child resource dependencies
      2,  // num vreg children
      0,  // num xob children
   },
   // S3E
   {
      NULL,// parent resource
      NULL,// child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_pwr_resource_dependency_info
clk_dep_a[] =
{
   { NULL, NULL, 0, 0,}, // Invalid zeroth array - NOT USED
   // C1
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C2
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C3
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C4
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C5
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C6
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C7
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C8
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C9
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C10
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C11
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C12
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C13
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },   
   // C14
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C15
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   // C16
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   //C17
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
   //C18
   {
      NULL, // parent resource
      NULL, // child resource dependencies
      0,  // num vreg children
      0,  // num xob children
   },
};

// resource dependency info
__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* smps_dep[] =
{
  NULL,
  smps_dep_b,
  smps_dep_c,
  smps_dep_d,
  smps_dep_e,
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
pm_pwr_resource_dependency_info* ldo_dep[] =
{
  NULL,
  ldo_dep_b,
  ldo_dep_c,
  ldo_dep_d,
  ldo_dep_e,
  ldo_dep_f,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  ldo_dep_m,
  ldo_dep_n,
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
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource_dependency_info* clk_dep[] =
{
  clk_dep_a,
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
};


// resource info
__attribute__((section("pm_dram_reclaim_pool")))
pm_pwr_resource* smps_rsrc[] =
{
  NULL,
  smps_b,
  smps_c,
  smps_d,
  smps_e,
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
pm_pwr_resource* ldo_rsrc[] =
{
  NULL,
  ldo_b,
  ldo_c,
  ldo_d,
  ldo_e,
  ldo_f,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  ldo_m,
  ldo_n,
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
};

