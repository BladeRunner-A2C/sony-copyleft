/** 
  @file  EFIPmicPwm.h
  @brief PMIC Pulse Windth Modulation Protocol for UEFI.
*/
/*=============================================================================
Copyright (c) 2011-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/23/14   al      Added GetStatus 
 06/18/13   llg     (Tech Pubs) Edited/added Doxygen comments and markup.
 03/26/13   al      Adding glitch removal. 
 12/12/12   al      created

=============================================================================*/

#ifndef __EFIPMICPWM_H__
#define __EFIPMICPWM_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/** @defgroup efi_pmic_pwm_protocol EFI_PMIC_PWM_PROTOCOL
 *  @ingroup PMIC 
 */
 /** @defgroup  efi_pmic_pwm_protocol_prot PROTOCOL
 *  @ingroup efi_pmic_pwm_protocol 
 */ 
 /** @defgroup  efi_pmic_pwm_protocol_apis APIs
 *  @ingroup efi_pmic_pwm_protocol 
 */ 

/** @defgroup  efi_pmic_pwm_protocol_data DATA_STRUCTURES
 *  @ingroup efi_pmic_pwm_protocol 
 */

/** @ingroup efi_pmic_pwm_protocol_data 
  Protocol version.
*/

#define PMIC_PWM_REVISION       EFI_PMIC_PWM_REVISION_1
#define EFI_PMIC_PWM_REVISION_1 0x0000000000010005
/** @} */ /* end_addtogroup efi_pmicPwm_constants */

/*  Protocol GUID definition */
/** @ingroup efi_pmicPwm_protocol */
#define EFI_PMIC_PWM_PROTOCOL_GUID \
    { 0xe08051ae, 0xac38, 0x46db, { 0xa6, 0x96, 0xc5, 0x69, 0x52, 0xb0, 0x56, 0x16 } }

	
/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/** efi_pmic_pwm_protocol
  External reference to the PMIC PWM Protocol GUID.
*/
extern EFI_GUID gQcomPmicPwmProtocolGuid;

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/
/** efi_pmic_pwm_protocol
  Protocol declaration.
*/
typedef struct _EFI_QCOM_PMIC_PWM_PROTOCOL   EFI_QCOM_PMIC_PWM_PROTOCOL;

/** @endcond */
/** @ingroup efi_pmic_pwm_protocol_data
 * ! \enum pm_pwm_resource_type.
 *  \brief PWM channel
 */
typedef enum{
    EFI_PM_PWM_RSRC_PWM_1 ,
    EFI_PM_PWM_RSRC_PWM_2 ,
    EFI_PM_PWM_RSRC_PWM_3 ,
    EFI_PM_PWM_RSRC_PWM_4 ,
    EFI_PM_PWM_RSRC_PWM_5 ,
    EFI_PM_PWM_RSRC_PWM_6 ,
    EFI_PM_PWM_RSRC_PWM_7 ,
    EFI_PM_PWM_RSRC_PWM_8, 
    EFI_PM_PWM_RSRC_PWM_INVALID 
}EFI_PM_PWM_RSRC_TYPE;


/** @ingroup efi_pmic_pwm_protocol_data
  Pulse-width modulation clock frequency selection.
*/
typedef enum{
    EFI_PM_PWM_CLK_OFF,      /**< Clock is OFF. */
    EFI_PM_PWM_CLK_1_0_KHZ,  /**< Clock is 1 kHz. */
    EFI_PM_PWM_CLK_32_0_KHZ, /**< Clock is 32 kHz. */
    EFI_PM_PWM_CLK_19_2_MHZ, /**< Clock is 19.2 MHz. */
    /*Following CLK Frequencies are available from 0x0000000000010005*/
	EFI_PM_PWM_CLK_38_4_MHZ, /**< Clock is 38.4 MHz. */
    EFI_PM_PWM_CLK_76_8_MHZ, /**< Clock is 76.8 MHz. */
/** @cond */
    EFI_PM_CLK_MAX
/** @endcond */
} EFI_PM_PWM_CLOCK_FREQ_TYPE;

/** @ingroup efi_pmic_pwm_protocol_data
  Pulse-width modulation bit size.
*/
typedef enum{
    EFI_PM_PWM_SIZE_6BIT,  /**< 6 bits. */
    EFI_PM_PWM_SIZE_7BIT,  /**< 7 bits. */ /*This BIT size is available from 0x0000000000010005*/
    EFI_PM_PWM_SIZE_8BIT,  /**< 8 bits. */ /*This BIT size is available from 0x0000000000010005*/
    EFI_PM_PWM_SIZE_9BIT,  /**< 9 bits. */
    /*Following BIT sizes are available from 0x0000000000010005*/
	EFI_PM_PWM_SIZE_10BIT, /**< 10 bits. */
    EFI_PM_PWM_SIZE_11BIT, /**< 11 bits. */
    EFI_PM_PWM_SIZE_12BIT, /**< 12 bits. */
    EFI_PM_PWM_SIZE_13BIT, /**< 13 bits. */
    EFI_PM_PWM_SIZE_14BIT, /**< 14 bits. */
    EFI_PM_PWM_SIZE_15BIT, /**< 15 bits. */
/** @cond */
    EFI_PM_PWM_SIZE_MAX
/** @endcond */
} EFI_PM_PWM_BIT_SIZE_TYPE;




/** @ingroup efi_pmic_pwm_protocol_data
  EFI_PM_PWM_STATUS_TYPE
  PWM status
*/
typedef struct{
  BOOLEAN PwmEnable;
  /* PWM enabled or disabled */  
  UINT16 PwmValue;
  /* Value set for PWM duty cycle */
  EFI_PM_PWM_BIT_SIZE_TYPE BitSize; 
  /* PWM bit size */
  EFI_PM_PWM_CLOCK_FREQ_TYPE ClkFreq;
  /* PWM master clock frequency */
  UINT32 PreDiv;
  /* Frequency predivide to divide down PWM master clock */
  UINT32 Exp;
  /* Exponent values to divide down PWM master clock */
  BOOLEAN GlitchRemoval;
  /* PWM glitch removal enabled or disabled */
}EFI_PM_PWM_STATUS_TYPE;

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/* EFI_PM_PWM_CONFIG */ 
/** @ingroup efi_pmic_pwm_protocol_apis
  @par Summary
  Configures the pulse-width modulation.

  @param[in]  PmicDeviceIndex  Primary: 0. Secondary: 1.
  @param[in]  PwmRsrc        Pwm resource. Refer #EFI_PM_PWM_RSRC_TYPE for more info
  @param[in]  PwmValue       Pulse-width modulation value. Range: 0 to 511.
  @param[in]  PreDiv          Frequency predivider. Values are: 1, 3, 5, or 6.
  @param[in]  PreDivExponent   Exponent values to predivide the master clock. 
                               Range: 0 to 7.
  @param[in]  ClkFreq          Clock frequency selection; see 
                               #EFI_PM_PWM_CLOCK_FREQ_TYPE for details.
  @param[in]  BitSize          Bit size; see #EFI_PM_PWM_BIT_SIZE_TYPE for 
                               details.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef
EFI_STATUS (EFIAPI *EFI_PM_PWM_CONFIG)(
  IN UINT32                     PmicDeviceIndex, 
  IN EFI_PM_PWM_RSRC_TYPE       PwmRsrc,
  IN UINT16                     PwmValue,
  IN UINT32                     PreDiv,
  IN UINT32                     PreDivExponent,
  IN EFI_PM_PWM_CLOCK_FREQ_TYPE ClkFreq,
  IN EFI_PM_PWM_BIT_SIZE_TYPE   BitSize
);

/* EFI_PM_PWM_SET_PWM_VALUE */ 
/** @ingroup efi_pmic_pwm_protocol_apis
  @par Summary
  Sets the value for the duty cycle.

  @param[in]  PmicDeviceIndex  Primary: 0. Secondary: 1.
  @param[in]  PwmRsrc        Pwm resource. Refer #EFI_PM_PWM_RSRC_TYPE for more info
  @param[in]  PwmValue       Pulse-width modulation value. Range: 0 to 511.

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS (EFIAPI *EFI_PM_PWM_SET_PWM_VALUE)(
   IN UINT32                PmicDeviceIndex, 
   IN EFI_PM_PWM_RSRC_TYPE   PwmRsrc,
   IN UINT16                PwmValue
);

/* EFI_PM_PWM_GLITCH_REMOVAL */ 
/** @ingroup efi_pmic_pwm_protocol_apis
  @par Summary
  Enables/disables glitch removal.

  @param[in]  PmicDeviceIndex  Primary: 0. Secondary: 1. 
  @param[in]  PwmRsrc        Pwm resource. Refer #EFI_PM_PWM_RSRC_TYPE for more info
  @param[in]  Enable           If TRUE, enable glitch removal;
                               if FALSE, disable glitch removal.
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS (EFIAPI *EFI_PM_PWM_GLITCH_REMOVAL)(
   IN UINT32                PmicDeviceIndex, 
   IN EFI_PM_PWM_RSRC_TYPE   PwmRsrc,
   IN BOOLEAN               Enable
);


/* EFI_PM_PWM_GET_STATUS */ 
/** @ingroup efi_pmic_pwm_protocol_apis
  @par Summary
  Sets the value for duty cycle
  @param[in]   DeviceIndex     Primary or Secondary PMIC. 
  @param[in]   PwmRsrc       Pwm resource. Refer #EFI_PM_PWM_RSRC_TYPE for more info  
  @param[out]  PwmStatus      PWM status

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/

typedef
EFI_STATUS (EFIAPI *EFI_PM_PWM_GET_STATUS)(
   IN  UINT32                 PmicDeviceIndex, 
   IN EFI_PM_PWM_RSRC_TYPE     PwmRsrc,
   OUT EFI_PM_PWM_STATUS_TYPE *PwmStatus
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_pmic_pwm_protocol_prot
  @par Summary
  Qualcomm PMIC Pulse-Width Modulation (PWM) Protocol interface.

  @par Parameters
  @inputprotoparams{pmic_pwm_proto_params.tex} 
*/

struct _EFI_QCOM_PMIC_PWM_PROTOCOL {
  UINT64                    Revision;
  EFI_PM_PWM_CONFIG         PwmConfig;
  EFI_PM_PWM_SET_PWM_VALUE  SetPwmValue;
  EFI_PM_PWM_GLITCH_REMOVAL GlitchRemoval;
  EFI_PM_PWM_GET_STATUS     GetStatus;
};

#endif  /* __EFIPMICPWM_H__ */
