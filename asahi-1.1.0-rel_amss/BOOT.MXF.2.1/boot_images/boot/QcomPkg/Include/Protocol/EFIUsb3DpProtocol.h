#ifndef __USB3DPPROTOCOL_H__
#define __USB3DPPROTOCOL_H__

/** @file     Usb3DpProtocol.h
    @brief    USB3DP Protocol
    @details  Platform specific APIs to configure USB3 DP HW.
    @note     
    @ref      Copyright (c) 2020 Qualcomm Technologies, Inc.
              All Rights Reserved.
              Confidential and Proprietary - Qualcomm Technologies, Inc.

    
**/

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/** @cond */
/*  
  Protocol declaration.
*/
typedef struct _USB3DP_PROTOCOL USB3DP_PROTOCOL;
/** @endcond */

/** @cond */
/*  
  Protocol version.
*/
#define EFI_USB3DP_PROTOCOL_REVISION   0x00010000
#define EFI_USB3DP_PROTOCOL_REVISION_1 0x00010000

/** @endcond */

/*  Protocol GUID definition */
/** @ingroup efi_usb3dp_protocol */
#define USB3DP_PROTOCOL_GUID \
  {0x01a0cd08, 0x69cb, 0x4d81, {0xa3, 0xab, 0x5c, 0x19, 0x63, 0xbb, 0x49, 0xa7}}

/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the USB3DP Protocol GUID.
*/
extern EFI_GUID gQcomUsb3DpProtocolGuid;

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/

typedef enum _USB3DP_CORE_NUM {
  USB3DP_CORE_0 = 0,
  USB3DP_CORE_1 = 1
} USB3DP_CORE_NUM;

typedef enum _USB3DP_EVT_TYPE {
  USB3DP_HOT_PLUG = 0,
  USB3DP_IRQ_HPD
} USB3DP_EVT_TYPE;

typedef enum _USB3DP_HOT_PLUG_NOTIFICATION_TYPE {
  USB3DP_NOTIFICATION_HPD_OUT = 0,
  USB3DP_NOTIFICATION_HPD_IN_CC1_PIN_A,
  USB3DP_NOTIFICATION_HPD_IN_CC1_PIN_B,
  USB3DP_NOTIFICATION_HPD_IN_CC1_PIN_C,
  USB3DP_NOTIFICATION_HPD_IN_CC1_PIN_D,
  USB3DP_NOTIFICATION_HPD_IN_CC1_PIN_E,
  USB3DP_NOTIFICATION_HPD_IN_CC1_PIN_F,
  USB3DP_NOTIFICATION_HPD_IN_CC2_PIN_A,
  USB3DP_NOTIFICATION_HPD_IN_CC2_PIN_B,
  USB3DP_NOTIFICATION_HPD_IN_CC2_PIN_C,
  USB3DP_NOTIFICATION_HPD_IN_CC2_PIN_D,
  USB3DP_NOTIFICATION_HPD_IN_CC2_PIN_E,
  USB3DP_NOTIFICATION_HPD_IN_CC2_PIN_F 
} USB3DP_HOT_PLUG_NOTIFICATION_TYPE;

typedef enum _USB3DP_IRQ_HPD_NOTIFICATION_TYPE {
  USB3DP_INTERRUPT_NONE = 0,
  USB3DP_INTERRUPT_IRQ_HPD
} USB3DP_IRQ_HPD_NOTIFICATION_TYPE;

typedef union _USB3DP_EVT_DATA {
  USB3DP_HOT_PLUG_NOTIFICATION_TYPE HpdStatus;
  USB3DP_IRQ_HPD_NOTIFICATION_TYPE  IrqHpdStatus;
} USB3DP_EVT_DATA;

/*===========================================================================
  FUNCTION DECLARATIONS
===========================================================================*/

/**
   Client callback function prototype
 
   @param[in]      EvtType        - Type of USB3DP event
   @param[in]      CoreNum        - Core number associated with the USB3DP event
   @param[in]      Data           - Data associated with the USB3DP event
   @retval True = Successful, False = Failure
 
 **/
typedef BOOLEAN (*USB3DP_PROTOCOL_CB) (
  IN USB3DP_EVT_TYPE      EvtType,
  IN USB3DP_CORE_NUM      CoreNum,
  IN USB3DP_EVT_DATA      Data
);

/**
   Register as a client with Usb3DpProtocol. Callback function gets invoked
   for all USB3DP events across all USB3DP cores.
 
   @param[in]      This         - Instance of USB3DP_PROTOCOL
   @param[in]      Cb           - Function pointer to client callback function
   @retval True = Successful, False = Failure
 
 **/
typedef BOOLEAN (*USB3DP_PROTOCOL_REGISTER) (
  IN USB3DP_PROTOCOL*   This,
  IN USB3DP_PROTOCOL_CB Cb
);

/**
   Unregister as a client with Usb3DpProtocol.
 
   @param[in]      This         - Instance of USB3DP_PROTOCOL
   @retval True = Successful, False = Failure
 
 **/
typedef BOOLEAN (*USB3DP_PROTOCOL_UNREGISTER) (
  IN USB3DP_PROTOCOL*   This
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/**
  Protocol declaration.
*/
struct _USB3DP_PROTOCOL {
  UINT64                     Revision;
  USB3DP_PROTOCOL_REGISTER   Register;
  USB3DP_PROTOCOL_UNREGISTER Unregister;
};
/** @endcond */

#endif /* __EFIUSB3DPPROTOCOL_H__ */
