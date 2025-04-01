/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charge-service.h"
#include "sysfs_accessor.h"
#include "log.h"

#define PATH_BATTERY		"/sys/class/power_supply/battery/"
#define PATH_BATTERY_EXT	"/sys/class/power_supply/battery_ext/"
#define PATH_BMS		"/sys/class/power_supply/bms/"
#define PATH_USB		"/sys/class/power_supply/usb/"
#define PATH_DC			"/sys/class/power_supply/dc/" // Sagami is not necessary
#define PATH_PC_PORT		"/sys/class/power_supply/pc_port/"
#define PATH_USBPD		"/sys/class/usbpd/usbpd0/"
#define PATH_SMBCHG		PATH_BATTERY"device/"
#define PATH_FG			PATH_BMS"device/"
#define PATH_QG			PATH_BMS"device/"
#define PATH_TYPE_C		PATH_USB"subsystem/typec/device/"
#define PATH_WIRELESS		"/sys/class/power_supply/wireless/"
#define PATH_WIRELESS_DEV	PATH_WIRELESS"device/"
#define PATH_QCOM_BATTERY	"/sys/class/qcom-battery/"
#define PATH_BATTCHG_EXT	"/sys/class/battchg_ext/"
#define PATH_BATTMAN_DBG	"/sys/class/battman_dbg/"
#define PATH_BATTMAN_DBG2	"/sys/class/battman_dbg2/"
#define PATH_THERMAL		"/sys/class/thermal/"

enum path_type_t {
	PATH_TYPE_STATIC,
	PATH_TYPE_DYNAMIC
};

typedef char *(*dynamic_path_gen_func_t)(void);

typedef int (*val_proc_int_func_t)(char *fval);
typedef char *(*val_proc_str_func_t)(char *fval);

enum val_type_t {
	VAL_DEC_INT,
	VAL_HEX_INT,
	VAL_FLOAT,
	VAL_STR,
	VAL_CONV_INT,
	VAL_CONV_STR,
	VAL_PROC_INT,
	VAL_PROC_STR,
};

struct val_conv_int_elem_t {
	char	*fval;
	int	intval;
};

struct val_conv_str_elem_t {
	char	*fval;
	char	*strval;
};

struct sysfs_scan_elem_t {
	int	path_type;
	void	*path_ptr;
	int	val_type;
	void	*opt_ptr;
};

static struct val_conv_int_elem_t status_conv_table[] = {
	{"Charging",	STATE_CHARGE},
	{"Full",	STATE_FULL},
	{NULL,		STATE_DISCHARGE},
};

static struct val_conv_int_elem_t health_conv_table[] = {
	{"Hot",		HEALTH_HOT},
	{"Warm",	HEALTH_WARM},
	{NULL,		HEALTH_NORMAL},
};

static struct val_conv_int_elem_t batt_type_conv_table[] = {
	{"Loading Battery Data",	BATT_TYPE_LOADING},
	{"NAGARA_4480MV_V2D7",		BATT_TYPE_NAGARA},
	{"YODO_4480MV_V2D7",		BATT_TYPE_YODO},
	{"6066429_HUAQIN_PDX246_4930MAH_AVERAGED_MASTERSLAVE_JUL19TH2023",		BATT_TYPE_HUAQIN},
	{NULL,				BATT_TYPE_UNKNOWN},
};

static struct val_conv_int_elem_t usb_type_conv_table[] = {
	{"Unknown",		USB_TYPE_UNKNOWN},
	{"SDP",			USB_TYPE_SDP},
	{"DCP",			USB_TYPE_DCP},
	{"CDP",			USB_TYPE_CDP},
	{"ACA",			USB_ACA},
	{"C",			USB_TYPE_C},
	{"PD",			USB_TYPE_PD},
	{"PD_DRP",		USB_TYPE_PD_DPR},
	{"PD_PPS",		USB_TYPE_PD_PPS},
	{"BrickID",		USB_TYPE_BRICKID},
	{"HVDCP",		USB_TYPE_HVDCP},
	{"HVDCP_3",		USB_TYPE_HVDCP_3},
	{"HVDCP_3P5",		USB_TYPE_HVDCP_3P5},
	{NULL,			USB_TYPE_UNKNOWN},
};

static struct val_conv_int_elem_t typec_mode_conv_table[] = {
	{"Nothing source attached",			TYPEC_MODE_NOCONSUMER},
	{"Type-C source attached (default current)",	TYPEC_MODE_TYPEC_DFT},
	{"Legacy source attached",			TYPEC_MODE_BC},
	{"PD source attached",				TYPEC_MODE_PD},
	{"Type-C source attached (medium current)",	TYPEC_MODE_TYPEC_1P5A},
	{"Type-C source attached (high current)",	TYPEC_MODE_TYPEC_3A},
	{"Unknown",					TYPEC_MODE_UNKNOWN},
	{NULL,						TYPEC_MODE_UNKNOWN},
};

static char *sdm_therm_path_gen(void);

static char *bcext_fake_votable_proc(char *fval);
static char *bcext_fake_disallow_votable_proc(char *fval);
static char *bcext_fcc_votable_proc(char *fval);
static char *bcext_usb_icl_votable_proc(char *fval);
static char *battman_fcc_votable_proc(char *fval);
static char *battman_fv_votable_proc(char *fval);
static char *battman_usb_icl_votable_proc(char *fval);

static struct sysfs_scan_elem_t sysfs_scan_table[NUM_SFIDS] = {
/* SFID						Path Type		Path							Value Type	Option */

  /* PATH_BATTERY */
  [SFID_CAPACITY] =				{PATH_TYPE_STATIC,	PATH_BATTERY"capacity",					VAL_DEC_INT,	NULL},
  [SFID_STATUS] =				{PATH_TYPE_STATIC,	PATH_BATTERY"status",					VAL_CONV_INT,	status_conv_table},
  [SFID_HEALTH] =				{PATH_TYPE_STATIC,	PATH_BATTERY"health",					VAL_CONV_INT,	health_conv_table},
  [SFID_TEMP] =					{PATH_TYPE_STATIC,	PATH_BATTERY"temp",					VAL_DEC_INT,	NULL},
  [SFID_VOLTAGE_NOW] =				{PATH_TYPE_STATIC,	PATH_BATTERY"voltage_now",				VAL_DEC_INT,	NULL},
  [SFID_CURRENT_NOW] =				{PATH_TYPE_STATIC,	PATH_BATTERY"current_now",				VAL_DEC_INT,	NULL},
  [SFID_BATT_TYPE] =				{PATH_TYPE_STATIC,	PATH_BATTERY"model_name",				VAL_CONV_INT,	batt_type_conv_table},
  [SFID_CHARGE_FULL] =				{PATH_TYPE_STATIC,	PATH_BATTERY"charge_full",				VAL_DEC_INT,	NULL},
  [SFID_CHARGE_FULL_DESIGN] =			{PATH_TYPE_STATIC,	PATH_BATTERY"charge_full_design",			VAL_DEC_INT,	NULL},
  [SFID_TIME_TO_FULL_NOW] =			{PATH_TYPE_STATIC,	PATH_BATTERY"time_to_full_now",				VAL_DEC_INT,	NULL},

  /* PATH_USB */
  [SFID_USB_ONLINE] =				{PATH_TYPE_STATIC,	PATH_USB"online",					VAL_DEC_INT,	NULL},
  [SFID_USB_CURRENT_NOW] =			{PATH_TYPE_STATIC,	PATH_USB"current_now",					VAL_DEC_INT,	NULL},
  [SFID_USB_VOLTAGE_NOW] =			{PATH_TYPE_STATIC,	PATH_USB"voltage_now",					VAL_DEC_INT,	NULL},
  [SFID_USB_TYPE_DETERMINED] =			{PATH_TYPE_STATIC,	PATH_USB"charger_type_determined",			VAL_DEC_INT,	NULL},
  [SFID_USB_ICL] =				{PATH_TYPE_STATIC,	PATH_USB"input_current_limit",				VAL_DEC_INT,	NULL},

  /* PATH_DC */
  [SFID_DC_ONLINE] =				{PATH_TYPE_STATIC,	PATH_WIRELESS"online",					VAL_DEC_INT,	NULL},
  [SFID_DC_VOLTAGE_NOW] =			{PATH_TYPE_STATIC,	PATH_WIRELESS"voltage_now",				VAL_DEC_INT,	NULL},
  [SFID_DC_CURRENT_MAX] =			{PATH_TYPE_STATIC,	PATH_WIRELESS"current_max",				VAL_DEC_INT,	NULL},

  /* PATH_QCOM_BATTERY */
  [SFID_USB_TYPE] =				{PATH_TYPE_STATIC,	PATH_QCOM_BATTERY"usb_real_type",			VAL_CONV_INT,	usb_type_conv_table},
  [SFID_WIRELESS_BOOST_EN] =			{PATH_TYPE_STATIC,	PATH_QCOM_BATTERY"wireless_boost_en",			VAL_STR,	NULL},
  [SFID_RESISTANCE] =				{PATH_TYPE_STATIC,	PATH_QCOM_BATTERY"resistance",				VAL_DEC_INT,	NULL},

  /* PATH_BATTCHG_EXT */
  [SFID_USB_INPUT_SUSPEND] = 			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"usb_input_suspend",			VAL_DEC_INT,	NULL},
  [SFID_LRC_CHARGE_DISABLE] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"lrc_charge_disable",			VAL_DEC_INT,	NULL},
  [SFID_LRC_INPUT_SUSPEND] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"lrc_input_suspend",			VAL_DEC_INT,	NULL},
  [SFID_SYSTEM_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"bootup_shutdown_phase",		VAL_DEC_INT,	NULL},
  [SFID_BATT_ID] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"batt_id",				VAL_DEC_INT,	NULL},
  [SFID_AGING_LEVEL] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"batt_aging_level",			VAL_DEC_INT,	NULL},
  [SFID_BATTERY_SOC] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"batt_soc",				VAL_DEC_INT,	NULL},
  [SFID_SYSTEM_SOC] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"system_soc",				VAL_DEC_INT,	NULL},
  [SFID_MONOTONIC_SOC] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"monotonic_soc",			VAL_DEC_INT,	NULL},
  [SFID_REAL_NOM_CAP] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"real_nom_cap",				VAL_DEC_INT,	NULL},
  [SFID_SMT_CHARGING_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"smart_charging_status",		VAL_DEC_INT,	NULL},
  [SFID_BATT_TEMP] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"batt_temp",				VAL_DEC_INT,	NULL},
  [SFID_REAL_TEMP] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"real_temp",				VAL_DEC_INT,	NULL},
  [SFID_TYPEC_MODE] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"typec_mode",				VAL_CONV_INT,	typec_mode_conv_table},
  [SFID_VCELL_MAX] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"vcell_max",				VAL_DEC_INT,	NULL},
  [SFID_SYSTEM_TEMP_LEVEL] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"system_temp_level",			VAL_DEC_INT,	NULL},
  [SFID_SYSTEM_TEMP_LEVEL_MAX] =		{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"system_temp_level_max",		VAL_DEC_INT,	NULL},
  [SFID_WLS_VRECT] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"wls_vrect",				VAL_DEC_INT,	NULL},
  [SFID_WLS_VOUT] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"wls_vout",				VAL_DEC_INT,	NULL},
  [SFID_WLS_IOUT] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"wls_iout",				VAL_DEC_INT,	NULL},
  [SFID_WLS_STATUS] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"wls_status",				VAL_STR,	NULL},
  [SFID_WLS_TYPE] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"wls_type",				VAL_STR,	NULL},
  [SFID_WLS_MFR_CODE] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"wls_mfr_code",				VAL_HEX_INT,	NULL},
  [SFID_CURRENT_ICL] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"wls_current_icl",			VAL_DEC_INT,	NULL},
  [SFID_TARGET_ICL] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"wls_target_icl",			VAL_DEC_INT,	NULL},
  [SFID_CURRENT_VOUT] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"wls_current_vout",			VAL_DEC_INT,	NULL},
  [SFID_TARGET_VOUT] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"wls_target_vout",			VAL_DEC_INT,	NULL},
  [SFID_SDM_THERM] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"sdm_therm",				VAL_DEC_INT,	NULL},
  [SFID_CURRENT_STEP_PHASE] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"current_step_phase",			VAL_DEC_INT,	NULL},
  [SFID_CURRENT_JEITA_ZONE] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"current_jeita_zone",			VAL_DEC_INT,	NULL},
  [SFID_BATTERY_CHARGER_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"battery_charger_status",		VAL_STR,	NULL},
  [SFID_AICL_RESULT] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"aicl_result",				VAL_DEC_INT,	NULL},
  [SFID_D2CP_CFG] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"d2cp_cfg",				VAL_DEC_INT,	NULL},
  [SFID_ICM_STATE] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"icm_state",				VAL_DEC_INT,	NULL},
  [SFID_FV] =					{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"fv",					VAL_DEC_INT,	NULL},
  [SFID_FCC] =					{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"fcc",					VAL_DEC_INT,	NULL},
  [SFID_WLS_TXID] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"wls_mfr_code",				VAL_HEX_INT,	NULL},
  [SFID_WLC_TYPE] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"wls_type",				VAL_STR,	NULL},
  [SFID_LEARNED_CAPACITY] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"learned_capacity",			VAL_DEC_INT,	NULL},
  [SFID_LEARNING_COUNT] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"learning_counter",			VAL_DEC_INT,	NULL},
  [SFID_RESTORED_CAPACITY] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"restored_capacity",			VAL_DEC_INT,	NULL},
  [SFID_USB_ICL_VOTABLE_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"usb_icl_votable_status",		VAL_STR,	NULL},
  [SFID_FCC_VOTABLE_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"fcc_votable_status",			VAL_STR,	NULL},
  [SFID_FAKE_CHG_VOTABLE_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"fake_chg_votable_status",		VAL_STR,	NULL},
  [SFID_FAKE_CHG_DISALLOW_VOTABLE_STATUS] =	{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"fake_chg_disallow_votable_status",	VAL_STR,	NULL},
  [SFID_CHARGER_MAX_WATTAGE] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"charger_max_wattage",			VAL_DEC_INT,	NULL},
  [SFID_ACTIVE_CHAGER_TYPE] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"active_charger_type",			VAL_DEC_INT,	NULL},
  [SFID_FCSS_ERR_CNT] =				{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"fcss_err_cnt",				VAL_DEC_INT,	NULL},
  [SFID_WEAK_LIMIT_CURRENT] =			{PATH_TYPE_STATIC,	PATH_BATTCHG_EXT"weak_limit_current",			VAL_DEC_INT,	NULL},

  /* PATH_THERMAL */
  [SFID_THERMAL_ZONE_SDM_THERM] =		{PATH_TYPE_DYNAMIC,	sdm_therm_path_gen,					VAL_DEC_INT,	NULL},

  /* PATH_BATTMAN_DBG */
  [SFID_REGUPDATE_INTERVAL] = 			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"regupdate_interval",			VAL_DEC_INT,	NULL},
  [SFID_BMLOG_INTERVAL] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"log_interval",				VAL_DEC_INT,	NULL},
  [SFID_BMLOG_CATEGORIES] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"log_categories",			VAL_STR,	NULL},
  [SFID_BMLOG_LEVEL] =				{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"log_level",				VAL_DEC_INT,	NULL},
  [SFID_REG_CHGR_CHARGER_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_chgr_chager_status",		VAL_HEX_INT,	NULL},
  [SFID_REG_CHGR_VBAT_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_chgr_vbat_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_CHGR_VBAT_STATUS2] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_chgr_vbat_status2",		VAL_HEX_INT,	NULL},
  [SFID_REG_CHGR_IBAT_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_chgr_ibat_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_CHGR_VFLT_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_chgr_vflt_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_CHGR_INT_RT_STS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_chgr_int_rt_sts",			VAL_HEX_INT,	NULL},
  [SFID_REG_CHGR_ICHG_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_chgr_ichg_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_CHG_ENABLED] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_chg_enabled",			VAL_HEX_INT,	NULL},
  [SFID_REG_FAST_CHG_CURRENT_CFG] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_fast_chg_current_cfg",		VAL_HEX_INT,	NULL},
  [SFID_REG_FLOAT_VOLTAGE_CFG] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_float_voltage_cfg",		VAL_HEX_INT,	NULL},
  [SFID_REG_ICL_MAX_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_icl_max_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_AICL_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_aicl_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_ICL_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_icl_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_POWER_PATH_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_power_path_status",		VAL_HEX_INT,	NULL},
  [SFID_REG_BST_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_bst_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_DCDC_INT_RT_STS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_dcdc_int_rt_sts",			VAL_HEX_INT,	NULL},
  [SFID_REG_BATIF_TEMP_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_batif_temp_status",		VAL_HEX_INT,	NULL},
  [SFID_REG_BATIF_INT_RT_STS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_batif_int_rt_sts",			VAL_HEX_INT,	NULL},
  [SFID_REG_BATIF_SHIP_MODE] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_batif_ship_mode",			VAL_HEX_INT,	NULL},
  [SFID_REG_USBIN_INPUT_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_usbin_input_status",		VAL_HEX_INT,	NULL},
  [SFID_REG_VUSB_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_vusb_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_APSD_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_apsd_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_APSD_RESULT_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_apsd_result_status",		VAL_HEX_INT,	NULL},
  [SFID_REG_USB_INT_RT_STS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_usb_int_rt_sts",			VAL_HEX_INT,	NULL},
  [SFID_REG_USBIN_ADAPTER_ALLOW_OVERRIDE] = 	{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_usbin_adapter_allow_override",	VAL_HEX_INT,	NULL},
  [SFID_REG_USBIN_ADAPTER_ALLOW_CFG] = 		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_usbin_adapter_allow_cfg",		VAL_HEX_INT,	NULL},
  [SFID_REG_APSD_ENABLED] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_apsd_enabled",			VAL_HEX_INT,	NULL},
  [SFID_REG_USBIN_CURRENT_LIMIT_CFG] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_usbin_current_limit_cfg",		VAL_HEX_INT,	NULL},
  [SFID_REG_USB_CMD_IL] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_usb_cmd_il",			VAL_HEX_INT,	NULL},
  [SFID_REG_WLS_INPUT_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_wls_input_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_WLS_VWLS_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_wls_vwls_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_WLS_INT_RT_STS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_wls_int_rt_sts",			VAL_HEX_INT,	NULL},
  [SFID_REG_WLS_ADAPTER_ALLOW_CFG] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_wls_adapter_allow_cfg",		VAL_HEX_INT,	NULL},
  [SFID_REG_WLS_ICL_CFG] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_wls_icl_cfg",			VAL_HEX_INT,	NULL},
  [SFID_REG_WLS_SUSPEND] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_wls_suspend",			VAL_HEX_INT,	NULL},
  [SFID_REG_TYPEC_SNK_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_type_c_snk_status",		VAL_HEX_INT,	NULL},
  [SFID_REG_TYPEC_SNK_DBG_ACS_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_type_c_snk_debug_access_status",	VAL_HEX_INT,	NULL},
  [SFID_REG_TYPEC_SRC_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_type_c_src_status",		VAL_HEX_INT,	NULL},
  [SFID_REG_TYPEC_STAT_MCN_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_type_c_state_machine_status",	VAL_HEX_INT,	NULL},
  [SFID_REG_TYPEC_MISC_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_type_c_misc_status",		VAL_HEX_INT,	NULL},
  [SFID_REG_TYPEC_TRY_SNK_SRC_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_type_c_try_snk_src_status",	VAL_HEX_INT,	NULL},
  [SFID_REG_TYPEC_LGCY_CBL_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_type_c_legacy_cable_status",	VAL_HEX_INT,	NULL},
  [SFID_REG_TYPEC_INT_RT_STS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_typec_int_rt_sts",			VAL_HEX_INT,	NULL},
  [SFID_REG_TYPEC_MODE_CFG] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_type_c_mode_cfg",			VAL_HEX_INT,	NULL},
  [SFID_REG_MISC_AICL_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_misc_aicl_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_MISC_WDOG_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_misc_wdog_status",			VAL_HEX_INT,	NULL},
  [SFID_REG_MISC_SYSOK_REASON_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_misc_sysok_reason_status",		VAL_HEX_INT,	NULL},
  [SFID_REG_MISC_INT_RT_STS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG"reg_misc_int_rt_sts",			VAL_HEX_INT,	NULL},

  /* PATH_BATTMAN_DBG2 */
  [SFID_IUSB0_TOT_VOTABLE_STATUS] =		{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG2"iusb0_tot_votable_status",		VAL_STR,	NULL},
  [SFID_FCC_0_VOTABLE_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG2"fcc_0_votable_status",		VAL_STR,	NULL},
  [SFID_FV_0_VOTABLE_STATUS] =			{PATH_TYPE_STATIC,	PATH_BATTMAN_DBG2"fv_0_votable_status",			VAL_STR,	NULL},

};
/* -------------------------------------------- */

#define MAX_SYSFS_FILE_VAL_SIZE 4096

int read_sysfs_params(struct sysfs_param_t *sysfs_param, bool *sysfs_param_enabled)
{
	int i;
	FILE *fd;
	char *path;
	int raw_len;
	struct val_conv_int_elem_t *val_conv_int_table;
	struct val_conv_str_elem_t *val_conv_str_table;
	static char read_buf[MAX_SYSFS_FILE_VAL_SIZE];
	dynamic_path_gen_func_t dynamic_path_gen_func;
	val_proc_int_func_t val_proc_int_func;
	val_proc_str_func_t val_proc_str_func;

	LOGD("----- Read SysFS params start -----");
	for (i = 0; i < NUM_SFIDS; i++) {
		sysfs_param[i].buff_ptr = NULL;
		sysfs_param[i].raw = "";
		sysfs_param[i].val_type = SYSFS_PARAM_VAL_INVALID;

		if (!sysfs_param_enabled[i])
			continue;

		if (sysfs_scan_table[i].path_type == PATH_TYPE_STATIC) {
			path = (char *)sysfs_scan_table[i].path_ptr;
		} else if (sysfs_scan_table[i].path_type == PATH_TYPE_DYNAMIC) {
			dynamic_path_gen_func = (dynamic_path_gen_func_t)sysfs_scan_table[i].path_ptr;
			path = dynamic_path_gen_func();
		} else {
			path = NULL;
		}

		if (!path)
			continue;

		fd = fopen(path, "r");

		if (fd) {
			raw_len = 0;
			while (fgets(&read_buf[raw_len], sizeof(read_buf) - raw_len, fd)) {
				raw_len += strlen(&read_buf[raw_len]);
			}

			if (raw_len >= 1 && read_buf[raw_len - 1] == '\n') {
				read_buf[raw_len - 1] = '\0';
				raw_len--;
			}

			if (raw_len >= 1) {
				sysfs_param[i].buff_ptr = malloc(raw_len + 1);
				if (sysfs_param[i].buff_ptr) {
					sysfs_param[i].raw = sysfs_param[i].buff_ptr;
					strlcpy(sysfs_param[i].raw, read_buf, raw_len + 1);
				}
			}
			fclose(fd);
		} else {
			LOGD("Open path error: %s\n", path);
		}

		switch (sysfs_scan_table[i].val_type) {
		case VAL_DEC_INT:
			sysfs_param[i].val_type = SYSFS_PARAM_VAL_INT;
			sysfs_param[i].intval = strtol(sysfs_param[i].raw, NULL, 10);
			break;
		case VAL_HEX_INT:
			sysfs_param[i].val_type = SYSFS_PARAM_VAL_INT;
			sysfs_param[i].intval = strtol(sysfs_param[i].raw, NULL, 16);
			break;
		case VAL_FLOAT:
			sysfs_param[i].val_type = SYSFS_PARAM_VAL_FLOAT;
			sysfs_param[i].floatval = strtof(sysfs_param[i].raw, NULL);
			break;
		case VAL_STR:
			sysfs_param[i].val_type = SYSFS_PARAM_VAL_STR;
			sysfs_param[i].strval = sysfs_param[i].raw;
			break;
		case VAL_CONV_INT:
			sysfs_param[i].val_type = SYSFS_PARAM_VAL_INT;
			val_conv_int_table = (struct val_conv_int_elem_t *)sysfs_scan_table[i].opt_ptr;
			while (val_conv_int_table->fval) {
				if (!strcmp(sysfs_param[i].raw, val_conv_int_table->fval))
					break;
				val_conv_int_table++;
			}
			sysfs_param[i].intval = val_conv_int_table->intval;
			break;
		case VAL_CONV_STR:
			sysfs_param[i].val_type = SYSFS_PARAM_VAL_STR;
			val_conv_str_table = (struct val_conv_str_elem_t *)sysfs_scan_table[i].opt_ptr;
			while (val_conv_str_table->fval) {
				if (!strcmp(sysfs_param[i].raw, val_conv_str_table->fval))
					break;
				val_conv_str_table++;
			}
			sysfs_param[i].strval = val_conv_str_table->strval;
			break;
		case VAL_PROC_INT:
			sysfs_param[i].val_type = SYSFS_PARAM_VAL_INT;
			val_proc_int_func = (val_proc_int_func_t)sysfs_scan_table[i].opt_ptr;
			sysfs_param[i].intval = val_proc_int_func(sysfs_param[i].raw);
			break;
		case VAL_PROC_STR:
			sysfs_param[i].val_type = SYSFS_PARAM_VAL_STR;
			val_proc_str_func = (val_proc_str_func_t)sysfs_scan_table[i].opt_ptr;
			sysfs_param[i].strval = val_proc_str_func(sysfs_param[i].raw);
			break;
		default:
			break;
		}
	}
	LOGD("----- Read SysFS params end -----");

	return i;
}

void cleanup_sysfs_params(struct sysfs_param_t *sysfs_param)
{
	int i;

	for (i = 0; i < NUM_SFIDS; i++) {
		if (sysfs_param[i].buff_ptr) {
			free(sysfs_param[i].buff_ptr);
			sysfs_param[i].buff_ptr = NULL;
		}
		sysfs_param[i].raw = "";
		sysfs_param[i].val_type = SYSFS_PARAM_VAL_INVALID;
	}
}

int write_sysfs_param(const SYSFS_PARAM_ID id, struct sysfs_param_t *sysfs_value)
{
	FILE *fd;
	char *str_ptr;
	struct val_conv_int_elem_t *val_conv_int_table;
	struct val_conv_str_elem_t *val_conv_str_table;
	int n;
	char *path;
	dynamic_path_gen_func_t dynamic_path_gen_func;
	static char str_buff[MAX_SYSFS_FILE_VAL_SIZE];

	if (id >= NUM_SFIDS)
		return -1;

	if (sysfs_scan_table[id].path_type == PATH_TYPE_STATIC) {
		path = (char *)sysfs_scan_table[id].path_ptr;
	} else if (sysfs_scan_table[id].path_type == PATH_TYPE_DYNAMIC) {
		dynamic_path_gen_func = (dynamic_path_gen_func_t)sysfs_scan_table[id].path_ptr;
		path = dynamic_path_gen_func();
	} else {
		path = NULL;
	}

	if (!path)
		return -1;

	fd = fopen(path, "w");
	if (!fd)
		return -1;

	str_ptr = NULL;

	switch (sysfs_scan_table[id].val_type) {
	case VAL_DEC_INT:
		if (sysfs_value->val_type == SYSFS_PARAM_VAL_INT) {
			snprintf(str_buff, sizeof(str_buff), "%d\n", sysfs_value->intval);
			str_ptr = str_buff;
		}
		break;
	case VAL_HEX_INT:
		if (sysfs_value->val_type == SYSFS_PARAM_VAL_INT) {
			snprintf(str_buff, sizeof(str_buff), "0x%x\n", sysfs_value->intval);
			str_ptr = str_buff;
		}
		break;
	case VAL_FLOAT:
		if (sysfs_value->val_type == SYSFS_PARAM_VAL_FLOAT) {
			snprintf(str_buff, sizeof(str_buff), "%f\n", sysfs_value->floatval);
			str_ptr = str_buff;
		}
		break;
	case VAL_STR:
		if (sysfs_value->val_type == SYSFS_PARAM_VAL_STR)
			str_ptr = sysfs_value->strval;
		break;
	case VAL_CONV_INT:
		if (sysfs_value->val_type == SYSFS_PARAM_VAL_INT) {
			val_conv_int_table = (struct val_conv_int_elem_t *)sysfs_scan_table[id].opt_ptr;
			str_ptr = val_conv_int_table[sysfs_value->intval].fval;
		}
		break;
	case VAL_CONV_STR:
		if (sysfs_value->val_type == SYSFS_PARAM_VAL_STR) {
			val_conv_str_table = (struct val_conv_str_elem_t *)sysfs_scan_table[id].opt_ptr;
			while (val_conv_str_table->fval) {
				if (!strcmp(sysfs_value->strval, val_conv_str_table->fval))
					break;
				val_conv_str_table++;
			}
			if (val_conv_str_table)
				str_ptr = val_conv_str_table->fval;
		}
		break;
	default:
		break;
	}

	if (str_ptr) {
		LOGD("Write SysFS:%s <- %s\n", sysfs_scan_table[id].path, str_ptr);
		n = fputs(str_ptr, fd);
	} else {
		n = -1;
	}
	fclose(fd);

	return n;
}

#define MAX_THERMAL_ZONE_NUMBER 99

static char *sdm_therm_path_gen(void)
{
	int i;
	FILE *fd;
	char thermal_zone_type_path[MAX_FILE_PATH];
	char thermal_zone_type[MAX_SYSFS_FILE_VAL_SIZE];
	static char sdm_therm_path[MAX_FILE_PATH] = "";

	if (strlen(sdm_therm_path) > 0)
		return sdm_therm_path;

	for (i = 0; i <= MAX_THERMAL_ZONE_NUMBER; i++) {
		snprintf(thermal_zone_type_path, sizeof(thermal_zone_type_path), PATH_THERMAL"thermal_zone%d/type", i);
		fd = fopen(thermal_zone_type_path, "r");
		if (!fd)
			continue;

		if (!fgets(thermal_zone_type, sizeof(thermal_zone_type), fd))
			thermal_zone_type[0] = '\0';

		fclose(fd);

		if (strlen(thermal_zone_type) > 0 && thermal_zone_type[strlen(thermal_zone_type) - 1] == '\n')
			thermal_zone_type[strlen(thermal_zone_type) - 1] = '\0';

		if (!strcmp(thermal_zone_type, "sdm_therm")) {
			snprintf(sdm_therm_path, sizeof(sdm_therm_path), PATH_THERMAL"thermal_zone%d/temp", i);
			break;
		}
	}

	return sdm_therm_path;
}


