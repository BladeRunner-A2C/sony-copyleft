#ifndef __PM_SCPQ_HS_TYPEC_H__
#define __PM_SCPQ_HS_TYPEC_H__

/*! \file
 *  \n
 *  \brief  pm_scpq_hs_typec.h PMIC-SCPQ MODULE RELATED DECLARATION
 *  \details  This header file contains functions and variable declarations
 *  to support Qualcomm PMIC SCPQ (Switch-Mode Battery Charger) module. The
 *  Switched-Mode Battery Charger (SCPQ) module includes a buck regulated
 *  battery charger with integrated switches. The SCPQ module, along with the
 *  Over Voltage Proection (OVP) module will majorly be used by charger
 *  appliation for charging Li-Ion batteries with high current (up to 2A).
 *  \n &copy; Copyright 2022 QUALCOMM Technologies Inc, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    ----------------------------------------------------------
01/19/23    rs     Initial revision
========================================================================== */
#include "pm_chg.h"


/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/
typedef enum
{
  PM_SCPQ_HS_USB_TYPEC_VCONN_CONTROL_BY_HW,
  PM_SCPQ_HS_USB_TYPEC_VCONN_DISABLE_BY_SW, 
  PM_SCPQ_HS_USB_TYPEC_VCONN_ENABLE_BY_SW = 0x03,
  PM_SCPQ_HS_USB_TYPEC_VCONN_INVALID
}pm_scpq_hs_usb_typec_vconn_enable_type;

/**  TYPEC VConn Current Limit **/
typedef enum
{
  PM_SCPQ_HS_PM_TYPEC_VCONN_ILIMIT_300MA,
  PM_SCPQ_HS_TYPEC_VCONN_ILIMIT_500MA,
  PM_SCPQ_HSTYPEC_VCONN_ILIMIT_INVALID
}pm_scpq_hs_usb_typec_vconn_ilimit;

/**  TYPEC VConn Soft Start Pull Down Current mA - SS_PD_IMA **/
typedef enum
{
  PM_SCPQ_HS_TYPEC_VCONN_SS_PD_35MA,
  PM_SCPQ_HS_TYPEC_VCONN_SS_PD_88MA,
  PM_SCPQ_HS_TYPEC_VCONN_SS_PD_160MA,
  PM_SCPQ_HS_TYPEC_VCONN_SS_PD_248MA,
  PM_SCPQ_HS_TYPEC_VCONN_SS_PD_INVALID
}pm_scpq_hs_usb_typec_vconn_ss_pd_ima;

typedef enum
{
  PM_SCPQ_HS_TYPEC_DAM_ICL_3A,
  PM_SCPQ_HS_TYPEC_DAM_ICL_FMB
}pm_scpq_hs_usb_typec_dam_icl_sel;



/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/



/**
 * @brief This function returns the USB type-C status
 *
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:    The pmic_index of charger module.
 * @param[out] vbus_status:  True = VBUS is present.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_scpq_hs_usb_get_typec_vbus_status(uint32 bus_id, uint32 pmic_index, boolean *vbus_status);

/**
 * @brief This function configures Debug Access Mode(dam) icl.
 *
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:   The pmic_index of charger module.
 * @param[in] icl_sel:      Refer #pm_scpq_hs_usb_typec_dam_icl_sel for details.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_scpq_hs_typec_set_dam_icl(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_typec_dam_icl_sel icl_sel);

/**
 * @brief This function gets Debug Access Mode(dam) status.
 *
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:   The pmic_index of charger module.
 * @param[out] ConnectSts:  DAM status.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_scpq_hs_typec_get_dam_connect_sts(uint32 bus_id, uint32 pmic_index, boolean *ConnectSts);

/**
 * @brief This function gets the TypeC port role as DRP/DFP/UFP
 *
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in]  pmic_index: The pmic_index of charger module.
 * @param[out] port_role:  USB type c port role type. Refer #pm_chg_typec_port_role_type for details.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_scpq_hs_usb_typec_get_port_role(uint32 bus_id, uint32 pmic_index, pm_chg_typec_port_role_type *port_role);

/**
 * @brief This function returns the USB type-C status
 *
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:     The pmic_index of charger module.
 * @param[out] typec_status:  USB type c status type. Refer #pm_scpq_usb_typec_status_type for details.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_scpq_hs_usb_get_typec_status(uint32 bus_id, uint32 pmic_index, pm_chg_typec_status_type *typec_status);

#endif /* __PM_SCPQ_HS_TYPEC_H__ */

