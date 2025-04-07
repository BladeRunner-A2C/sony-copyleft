#ifndef __PM_SCPQ_HS_DRIVER_H__
#define __PM_SCPQ_HS_DRIVER_H__

/*! \file pm_scpq_hs_driver.h
 *  \n
 *  \brief This file contains functions prototypes and variable/type/constant
*          declarations for supporting SCPQ_HS peripheral
 *  \n
 *  \n &copy;
 *  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*===========================================================================

                        EDIT HISTORY

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who    what, where, why
--------    ---    ----------------------------------------------------------
07/09/22    xj     Initial revision
01/19/23    rs     Added wd and batt thermal channel into register ds
========================================================================== */
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_target_information.h"

/*===========================================================================

                        STRUCTURE TYPE AND ENUM

===========================================================================*/


/************************************************************************/
/* register definitions                                                 */
/************************************************************************/
typedef struct
{
  pm_register_address_type peripheral_offset   ; //ADDRESS:0x2600
  pm_register_address_type charger_status      ; //0x06
  pm_register_address_type vsys_min_cfg        ; //0x40
  pm_register_address_type vph_pre_chg_cfg     ; //0x41
  pm_register_address_type chg_en              ; //0x46
  pm_register_address_type ipre_cfg            ; //0x50
  pm_register_address_type ichg_cfg            ; //0x54
  pm_register_address_type vflt_cfg            ; //0x58
  pm_register_address_type chg_term_cfg        ; //0x60
}scpq_hs_chgr_register_ds;

typedef struct scpq_hs_dcdc_register_ds
{
  pm_register_address_type peripheral_offset   ; //ADDRESS:0x2700
  pm_register_address_type perph_type          ; //0x04
  pm_register_address_type perph_subtype       ; //0x05
  pm_register_address_type icl_max_status      ; //0x06
  pm_register_address_type power_path_status   ; //0x0B
  pm_register_address_type lockbit_d1          ; //0xD1
  pm_register_address_type lockbit_d2          ; //0xD2
  pm_register_address_type bst_status          ; //0x0D, bst = boost
  pm_register_address_type int_rt_sts          ; //0x10
  pm_register_address_type int_set_type        ; //0x11
  pm_register_address_type int_polarity_high   ; //0x12
  pm_register_address_type int_polarity_low    ; //0x13
  pm_register_address_type int_latched_clr     ; //0x14
  pm_register_address_type int_en_set          ; //0x15
  pm_register_address_type int_en_clr          ; //0x16
  pm_register_address_type int_latched_sts     ; //0x18
  pm_register_address_type int_pending_sts     ; //0x19
  pm_register_address_type int_mid_sel         ; //0x1A
  pm_register_address_type int_priority        ; //0x1B
  pm_register_address_type bst_en              ; //0x50, bst = boost
  pm_register_address_type bst_cfg             ; //0x56, bst = boost
}scpq_hs_dcdc_register_ds;

typedef struct
{
  pm_register_address_type peripheral_offset       ; //ADDRESS:0x2800
  pm_register_address_type int_rt_sts              ; //0x10
  pm_register_address_type int_set_type            ; //0x11
  pm_register_address_type int_polarity_high       ; //0x12
  pm_register_address_type int_polarity_low        ; //0x13
  pm_register_address_type int_latched_clr         ; //0x14
  pm_register_address_type int_en_set              ; //0x15
  pm_register_address_type int_en_clr              ; //0x16
  pm_register_address_type int_latched_sts         ; //0x18
  pm_register_address_type int_pending_sts         ; //0x19
  pm_register_address_type ship_mode               ; //0x52
  pm_register_address_type afp_mode                ; //0x53
  pm_register_address_type bpd_cfg                 ; //0x60, Battery Missing Pin Source
  pm_register_address_type batt_diffsense_cfg      ; //0x68
  pm_register_address_type jeita_en_cfg            ; //0x7F
  pm_register_address_type jeita_thot_thd_msb      ; //0x84 Jeita too hot threshold MSB
  pm_register_address_type jeita_thot_thd_lsb      ; //0x85 Jeita too hot threshold LSB
  pm_register_address_type jeita_warm_thd_msb      ; //0x86 Jeita warm threshold MSB
  pm_register_address_type jeita_warm_thd_lsb      ; //0x87 Jeita warm threshold LSB
  pm_register_address_type jeita_cool_thd_msb      ; //0x88 Jeita coolthreshold MSB
  pm_register_address_type jeita_cool_thd_lsb      ; //0x89 Jeita cool threshold LSB
  pm_register_address_type jeita_tcold_thd_msb     ; //0x8A Jeita too cold threshold MSB
  pm_register_address_type jeita_tcold_thd_lsb     ; //0x8B Jeita too cold threshold LSB
  pm_register_address_type jeita_thot_afp_thd_msb  ; //0x8C Jeita too hot AFP threshold MSB
  pm_register_address_type jeita_thot_afp_thd_lsb  ; //0x8D Jeita too hot AFP threshold LSB
  pm_register_address_type jeita_tcold_afp_thd_msb ; //0x8E Jeita too cold AFP threshold MSB
  pm_register_address_type jeita_tcold_afp_thd_lsb ; //0x8F Jeita too cold AFP threshold LSB
}scpq_hs_batif_register_ds;

typedef struct
{
  pm_register_address_type peripheral_offset       ; //ADDRESS:0x2900
  pm_register_address_type apsd_status             ; //0x0A
  pm_register_address_type apsd_result_status      ; //0x0B
  pm_register_address_type qc_change_status        ; //0x0C
  pm_register_address_type qc_pulse_count_status   ; //0x0D
  pm_register_address_type int_rt_sts              ; //0x10
  pm_register_address_type int_set_type            ; //0x11
  pm_register_address_type int_polarity_high       ; //0x12
  pm_register_address_type int_polarity_low        ; //0x13
  pm_register_address_type int_latched_clr         ; //0x14
  pm_register_address_type int_en_set              ; //0x15
  pm_register_address_type int_en_clr              ; //0x16
  pm_register_address_type int_latched_sts         ; //0x18
  pm_register_address_type int_pending_sts         ; //0x19
  pm_register_address_type usbin_adapter_allow_cfg ; //0x40
  pm_register_address_type apsd_en                 ; //0x44
  pm_register_address_type apsd_cmd                ; //0x45
  pm_register_address_type usb_icl_options         ; //0x50
  pm_register_address_type usb_icl_override        ; //0x51
  pm_register_address_type usb_icl_cfg             ; //0x52
  pm_register_address_type usb_suspend             ; //0x54
  pm_register_address_type usb_aicl_cfg            ; //0x60
  pm_register_address_type inov_cfg                ; //0x68
}scpq_hs_usb_register_ds;

typedef struct
{
  pm_register_address_type peripheral_offset          ; //ADDRESS:0x2B00
  pm_register_address_type perph_type                 ; //0x04
  pm_register_address_type perph_subtype              ; //0x05
  pm_register_address_type typec_snk_status           ; //0x06
  pm_register_address_type typec_debug_access_status  ; //0x07
  pm_register_address_type typec_misc_status          ; //0x0B
  pm_register_address_type typec_mode_cfg             ; //0x44
  pm_register_address_type typec_vconn_control        ; //0x46
  pm_register_address_type typec_debug_access_snk_cfg ; //0x4A
  pm_register_address_type lockbit_d1                 ; //0xD1
}scpq_hs_typec_register_ds;

typedef struct
{
  pm_register_address_type peripheral_offset          ; //ADDRESS:0x2C00
  pm_register_address_type sysok_reason_status        ; //0x0D
  pm_register_address_type int_rt_sts                 ; //0x10
  pm_register_address_type int_set_type               ; //0x11
  pm_register_address_type int_polarity_high          ; //0x12
  pm_register_address_type int_polarity_low           ; //0x13
  pm_register_address_type int_latched_clr            ; //0x14
  pm_register_address_type int_en_set                 ; //0x15
  pm_register_address_type int_en_clr                 ; //0x16
  pm_register_address_type int_latched_sts            ; //0x18
  pm_register_address_type int_pending_sts            ; //0x19
  pm_register_address_type aicl_cmd                   ; //0x50
  pm_register_address_type aicl_rerun_time_cfg        ; //0x54
  pm_register_address_type wd_cfg                     ; //0x58
  pm_register_address_type wd_bb_time_sel             ; //0x59
  pm_register_address_type wd_snarl_time_sel          ; //0x5A
  pm_register_address_type bark_bite_wdog_pet         ; //0x5B
  pm_register_address_type therm_reg_src_cfg          ; //0x60
  pm_register_address_type die_temp_h_thd_msb         ; //0x64
  pm_register_address_type die_temp_h_thd_lsb         ; //0x65
  pm_register_address_type die_temp_l_thd_msb         ; //0x66
  pm_register_address_type die_temp_l_thd_lsb         ; //0x67
  pm_register_address_type batt_therm_ch_id           ; //0x9A
  pm_register_address_type batt_therm_ch_en           ; //0x99
  pm_register_address_type vin_div16_mux_sel          ; //0xBC
}scpq_hs_misc_register_ds;

typedef struct
{
  pm_comm_info_type             *comm_ptr;
  pm_register_address_type      base_address;
  uint32                        num_of_peripherals;
  scpq_hs_chgr_register_ds      *chgr_register;
  scpq_hs_dcdc_register_ds      *dcdc_register;
  scpq_hs_batif_register_ds     *batif_register;
  scpq_hs_usb_register_ds       *usb_register;
  scpq_hs_typec_register_ds     *typec_register;
  scpq_hs_misc_register_ds      *misc_register;
}pm_scpq_hs_data_type;

/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/
void
pm_scpq_hs_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index, uint32 bus_id);

pm_scpq_hs_data_type*
pm_scpq_hs_get_data(uint32 bus_id, uint32 pmic_index);

void
pm_scpq_hs_get_pmic_info(uint32 bus_id, uint32 *pmic_index, uint32 *slave_id, uint32* charger_count, uint32 max_charger);


#endif // __PM_SCPQ_HS_DRIVER_H__

