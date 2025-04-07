#ifndef __USB4PROTOCOL_H__
#define __USB4PROTOCOL_H__

/** @file     Usb4Protocol.h 
    @brief    USB4 Protocol
    @details  Platform specific APIs to configure USB4 host router.
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
typedef struct _USB4_PROTOCOL USB4_PROTOCOL;
/** @endcond */

/** @cond */
/*  
  Protocol version.
*/
#define EFI_USB4_PROTOCOL_REVISION   0x0000000000010000
#define EFI_USB4_PROTOCOL_REVISION_1 0x0000000000010000

/** @endcond */

/*  Protocol GUID definition */
/** @ingroup efi_usbConfig_protocol */
#define USB4_PROTOCOL_GUID \
  {0x01b1d7f5, 0x7768, 0x4fe6, {0x86, 0xb9, 0x5e, 0x10, 0x42, 0x74, 0x5d, 0x79}}

/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the USB4 Protocol GUID.
*/
extern EFI_GUID gQcomUsb4ProtocolGuid;

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/

typedef enum _USB4_CORE_NUM_TYPE {
  USB4_CORE_0 = 0,
  USB4_CORE_1 = 1,
} USB4_CORE_NUM_TYPE;

typedef enum _USB4_EVT_TYPE {
  USB4_CONNECT = 0,
  USB4_PATH_ENABLE,
  USB4_DP_HOT_PLUG,
  USB4_PATH_DISABLE,
  USB4_DISCONNECT,
} USB4_EVT_TYPE;

typedef enum _USB4_CLIENT_TYPE {
  USB4_CLIENT_PCIE,
  USB4_CLIENT_DP,
  USB4_CLIENT_USB3
} USB4_CLIENT_TYPE;

typedef enum _USB4_DP_HOT_PLUG_NOTIFICATION_TYPE {
  USB4_DP_NOTIFICATION_HPD_OUT = 0,
  USB4_DP_NOTIFICATION_HPD_IN
} USB4_DP_HOT_PLUG_NOTIFICATION_TYPE;

typedef union _USB4_EVT_DATA {
  USB4_DP_HOT_PLUG_NOTIFICATION_TYPE Usb4DpHpdStatus;
} USB4_EVT_DATA;

/*===========================================================================
  FUNCTION DECLARATIONS
===========================================================================*/

/**
   Client callback function prototype
 
   @param[in]      EvtType        - Type of USB4 event
   @param[in]      CoreNum        - Core number associated with the USB4 event
   @param[in]      Data           - Data associated with the USB4 event
   @retval True = Successful, False = Failure
 
 **/
typedef BOOLEAN (*USB4_PROTOCOL_CB) (
  IN USB4_EVT_TYPE      EvtType,
  IN USB4_CORE_NUM_TYPE CoreNum,
  IN USB4_EVT_DATA      Data
);

/**
   Register as a client with Usb4Protocol. Callback function gets invoked
   for all client specific USB4 events across all USB4 cores.
 
   @param[in]      This         - Instance of USB4_PROTOCOL
   @param[in]      ClientType   - Type of client registering with the protocol
   @param[in]      Cb           - Function pointer to client callback function
   @retval True = Successful, False = Failure
 
 **/
typedef BOOLEAN (*USB4_PROTOCOL_REGISTER) (
  IN USB4_PROTOCOL*   This,
  IN USB4_CLIENT_TYPE ClientType,
  IN USB4_PROTOCOL_CB Cb
);

/**
   Query if client specific USB4 path is enabled/disabled
 
   @param[in]      This         - Instance of USB4_PROTOCOL
   @param[in]      ClientType   - PCIE, DP or USB3 Client
   @retval True = Path in enabled state, False = Path is in disabled state.
 
 **/
typedef BOOLEAN (*USB4_QUERY_PATH_ENABLE) (
  IN USB4_PROTOCOL*     This,
  IN USB4_CLIENT_TYPE   ClientType,
  IN USB4_CORE_NUM_TYPE CoreNum
);

/**
   Unregister as a client with Usb4Protocol.
 
   @param[in]      This         - Instance of USB4_PROTOCOL
   @param[in]      ClientType   - Type of client unregistering with the protocol
   @retval True = Successful, False = Failure
 
 **/
typedef BOOLEAN (*USB4_PROTOCOL_UNREGISTER) (
  IN USB4_PROTOCOL*   This,
  IN USB4_CLIENT_TYPE ClientType
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/**
  Protocol declaration.
*/
struct _USB4_PROTOCOL {
  UINT64                   Revision;
  USB4_PROTOCOL_REGISTER   Register;
  USB4_PROTOCOL_UNREGISTER Unregister;
  USB4_QUERY_PATH_ENABLE   QueryPathEnable;
};
/** @endcond */



#endif /* __EFIUSB4PROTOCOL_H__ */
