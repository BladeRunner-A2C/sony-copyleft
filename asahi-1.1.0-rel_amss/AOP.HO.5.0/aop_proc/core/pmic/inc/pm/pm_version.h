#ifndef _PM_VERSION__H
#define _PM_VERSION__H
/*! \file 
 *  \n
 *  \brief  pm_version.h ---- PMIC Version 
 *  \n
 *  \n This header file contains enums and API definitions for PMIC version 
 *      detection
 *  \n
 *  \n &copy; Copyright 2010-2018 QUALCOMM Technologies Incorporated, All Rights Reserved
 */
/* ======================================================================= */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/core/pmic/inc/pm/pm_version.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/10/23   bde     Version defines for Bonefish
01/17/23   arua    Version definition for Etna
01/05/21   nsm     Version defines for Amberjack and Cortes
01/28/13   kt      Added pm_get_pmic_info API to get the pmic device info.  
01/28/13   kt      Removed pm_set_hardware_version and pm_get_hardware_version APIs. 
12/06/12   hw      Remove comdef.h and use com_dtypes.h
09/19/12   vk      Add PM8019
03/10/12   wra     Removed old PMIC versions and added Badger PMIC versions. 
                   Reduced hardware versions in enumeration
10/18/11   jtn/mpt Add PM8821 and PM8038
04/04/11   hw      Added pm_get_hardware_version and pm_set_hardware_version API
02/08/11   hw      Merging changes from the PMIC Distributed Driver Arch branch
07/05/10   wra     Added pm_model_type entry for the PM8921 and PM8018
07/05/10   wra     Added file header and pm_model_type entry for the PM8901 
                   and ISL9519
=============================================================================*/
/*===========================================================================

                        HEADER FILES

===========================================================================*/
#include "pm_resources_and_types.h"
#include "pm_err_flags.h"


/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

/** 
  @enum pm_model_type
  @brief This enum gives the PMIC model type values (Peripheral
  Subtype values) for different PMIC Models. 
 */
typedef enum
{
   PMIC_IS_UNKNOWN   = 0x0,
   PMIC_IS_PM8941    = 0x1,
   PMIC_IS_PM8841    = 0x2,
   PMIC_IS_PM8019    = 0x3,
   PMIC_IS_PM8026    = 0x4,
   PMIC_IS_PM8110    = 0x5,
   PMIC_IS_PMA8084   = 0x6,
   PMIC_IS_PMI8962   = 0x7,
   PMIC_IS_PMD9635   = 0x8,
   PMIC_IS_PM8994    = 0x9,
   PMIC_IS_PMI8994   = 0xA,
   PMIC_IS_PM8916    = 0xB,
   PMIC_IS_PM8004    = 0xC,
   PMIC_IS_PMK8001   = 0x12,
   PMIC_IS_PMI8996   = 0x13,
   PMIC_IS_PM8998    = 0x14,
   PMIC_IS_PMI8998   = 0x15,
   PMIC_IS_PM8005    = 0x18,
   PMIC_IS_PM660L    = 0x1A,
   PMIC_IS_PM660     = 0x1B,
   PMIC_IS_SMB1355   = 0x1C,
   PMIC_IS_PM8150    = 0x1E,
   PMIC_IS_PM855     = PMIC_IS_PM8150,
   PMIC_IS_PM8150L   = 0x1F,
   PMIC_IS_PM855L    = PMIC_IS_PM8150L,
   PMIC_IS_PM6150L   = PMIC_IS_PM855L,
   PMIC_IS_PM7150L   = PMIC_IS_PM6150L,
   PMIC_IS_PM8150B   = 0x20,
   PMIC_IS_PM855B    = PMIC_IS_PM8150B,
   PMIC_IS_PMK8002   = 0x21,
   PMIC_IS_PMX24     = 0x22,
   PMIC_IS_SMB1390   = 0x23,
   PMIC_IS_PM8009    = 0x24,
   PMIC_IS_PMI632    = 0x25,
   PMIC_IS_PM8150C   = 0x26,
   PMIC_IS_PM855P    = PMIC_IS_PM8150C,
   PMIC_IS_PM8150A   = 0x27,
   PMIC_IS_PM855A    = PMIC_IS_PM8150A,
   PMIC_IS_PM6150    = 0x28,
   PMIC_IS_PM7150    = PMIC_IS_PM6150,
   PMIC_IS_PMX55     = 0x2A,
   PMIC_IS_LEICA     = 0x2C,
   PMIC_IS_TIOMAN    = 0x2E,
   PMIC_IS_PMK8350   = 0x2F,
   PMIC_IS_PM8350    = 0x30,
   PMIC_IS_PM8350C   = 0x31,
   PMIC_IS_PM8350B   = 0x32,
   PMIC_IS_PMR735A   = 0x33,
   PMIC_IS_PMR735B   = 0x34,
   PMIC_IS_SMB1398   = 0x35,
   PMIC_IS_HAPUNA    = 0x3A,
   PMIC_IS_PMX65     = 0x3B,
   PMIC_IS_PM7325B   = 0x3C,
   PMIC_IS_PM7325    = 0x3F,
   PMIC_IS_PM8010    = 0x41,
   PMIC_IS_SECOJR    = 0x43,
   PMIC_IS_VOODOO6   = 0x45,
   PMIC_IS_VOODOO8   = 0x46,
   PMIC_IS_KOHALA    = 0x47,
   PMIC_IS_NALOJR    = 0x48,
   PMIC_IS_HUMU      = 0x49,
   PMIC_IS_AZURA     = 0x4A,
   PMIC_IS_SCULPIN   = 0x4C,
   PMIC_IS_BONEFISH  = 0x50,
   PMIC_IS_MORRO     = 0x51,
   PMIC_IS_COSWORTH  = 0x52,
   PMIC_IS_PMX35     = 0x55,
   PMIC_IS_INVALID   = 0x7FFFFFFF,
} pm_model_type;

enum
{
  PMIC_A = 0,
  PMIC_B = 1,
  PMIC_C = 2,
  PMIC_D = 3,
  PMIC_E = 4,
  PMIC_F = 5,
  PMIC_G = 6,
  PMIC_H = 7,
  PMIC_I = 8,
  PMIC_J = 9,
  PMIC_K = 10,
  PMIC_L = 11,
  PMIC_M = 12,
  PMIC_N = 13,
  PMIC_O = 14,
  PMIC_INDEX_MAX = 15,
};

/** 
  @struct pm_device_info_type
  @brief Stores the PMIC's Model type value, the All Layer
  Revision number and the Metal Revision number. Please refer
  to pm_model_type enum above to get more info on which PMIC
  model type value represents which PMIC.For example, for
  PM8019 v2.1 the PMIC model type value is 3 (since PM8019
  model type value is 3 as per pm_model_type enum), All layer
  revision number is '2' and Metal revision number is '1'.
 */
typedef struct
{
  pm_model_type   ePmicModel;             /**< PMIC device model type */
  uint32          nPmicAllLayerRevision;  /**< PMIC device all layer revision number */
  uint32          nPmicMetalRevision;     /**< PMIC device metal revision number */
  uint32          nSlaveCount;            /**< Slave Count on PMIC */
} pm_device_info_type;

/*===========================================================================

                        API PROTOTYPE

===========================================================================*/

/** 
 * @name pm_get_pmic_model 
 *  
 * @brief This function returns the PMIC's model type value.
 *        For example, the API returns '1' for PM8941, '2'
 *        for PM8841 and so on. Please refer to pm_model_type
 *        enum above to get more info on which PMIC model type
 *        value represents which PMIC.
 * 
 * @param[in] pmic_device_index.Primary PMIC:0 Secondary PMIC:1 
 *
 * @return  pm_model_type 
 *          Returns valid PMIC model/tier type if successful
 *          Returns PMIC_IS_INVALID under error conditions (like
 *          invalid device index param).
 *
 */
pm_model_type pm_get_pmic_model(uint8 pmic_device_index);

/** 
 * @name pm_get_pmic_revision 
 *  
 * @brief This function returns the PMIC's All Layer revision
 *        number. For example, the API returs '1' for PMIC v1.x,
 *        '2' for PMIC v2.x  and so on.
 * 
 * @param[in] pmic_device_index.Primary PMIC:0 Secondary PMIC:1
 *
 * @return  uint8 
 *          Returns valid PMIC All Layer revision number if
 *          successful.
 *          Returns 0 under error conditions (like invalid
 *          device index param).
 *
 */
uint8 pm_get_pmic_revision(uint8 pmic_device_index);

/** 
 * @name pm_get_pmic_info 
 *  
 * @brief This function returns information about PMIC device 
 *        for a specific device index in the pmic_device_info
 *        argument. This API returns PMIC's model type value,
 *        All layer revision number and Metal revision number in
 *        pmic_device_info structure. Please refer to
 *        pm_device_info_type structure above for more info. For
 *        example, for PM8019 v2.1 the PMIC model type value is
 *        3 (since PM8019 model type value is 3 as per
 *        pm_model_type enum), All layer revision number is '2'
 *        and Metal revision number is '1'.
 * 
 * @param[in]  pmic_device_index.Primary PMIC:0 Secondary PMIC:1
 * @param[out] pmic_device_info:  
 *                Variable to return to the caller with PMIC
 *                device info. Please refer to
 *                pm_device_info_type structure above for more
 *                info on this structure.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Error in
 *          collecting and placing PMIC info.
 *          PM_ERR_FLAG__SUCCESS = SUCCESS.
 *
 */

pm_err_flag_type pm_get_pmic_info(uint8 pmic_index, pm_device_info_type* pmic_device_info_ptr);


#endif // PM_VERSION__H
