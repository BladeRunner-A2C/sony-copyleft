/** 
  @file  EFIHSUart.h
  @brief HSUart UEFI Protocol definitions.
*/
/*=============================================================================

  Copyright 2019-2023 by Qualcomm Technologies, Inc.  All Rights Reserved.

=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 1/4/23     rk      Initial revision for UEFI

=============================================================================*/

#ifndef __EFIHSUART_H__
#define __EFIHSUART_H__

#include "hsuart_common.h"

/** @ingroup efi_hsuart_protocol_data

  Protocol version. 
*/
#define HSUART_DXE_REVISION 0x0000000000010000


/** @ingroup efi_hsuart_protocol_data
  HS-UART UEFI typedefs
*/
typedef struct _EFI_QCOM_HSUART_PROTOCOL   EFI_QCOM_HSUART_PROTOCOL;
/** @endcond */

/*  HS-UART UEFI Procotol GUID */
/** @ingroup efi_hsuart_protocol_data */
extern EFI_GUID gQcomHSUartProtocolGuid;

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/* OPEN */ 
/** @ingroup efi_hsuart_protocol_apis
  @par Summary
  This function is called by the client code to initialize the respective 
  HS-UART core instance used by the client.
  
*/
typedef
RETURN_STATUS
(EFIAPI *OPEN) (
    void
);

/* READ */
/** @ingroup efi_hsuart_protocol_apis
  @par Summary
  Performs an hsuart read.

  @param[out] buffer                Buffer into which data is read.
  @param[in]  buffer_len            Length of data that needs to be read.
                                    the slave.
  @return 
  Actual bytes read
*/
typedef
UINTN
(EFIAPI *READ) (
    OUT UINT8 *user_buffer,
    IN UINTN bytes_requested
);

/* WRITE */
/** @ingroup efi_hsuart_protocol_apis
  @par Summary
  Performs an hsuart write.

  @param[out] buffer                Buffer from which data is written.
  @param[in]  buffer_len            Length of data that needs to be written.
                                    the slave.

  @return 
  Actual bytes written
*/
typedef
UINTN
(EFIAPI *WRITE) (
    IN UINT8 *user_buffer,
    IN UINTN bytes_to_send
);

/* POLL */
/** @ingroup efi_hsuart_protocol_apis
  @par Summary
  Polls for RX Watermark

  @return 
  Boolean TRUE if watermark set and vice versa.
*/
typedef
BOOLEAN
(EFIAPI *POLL) (
    void
);

/* CLOSE */ 
/** @ingroup efi_hsuart_protocol_apis
  @par Summary
  This function is called by the client code to de-initialize the respective 
  HS-UART core instance used by the client.
  
*/
typedef
RETURN_STATUS
(EFIAPI *CLOSE) (
    void
);

/* SETBAUD */
/** @ingroup efi_hsuart_protocol_apis
  @par Summary
  This function is called by the client code to de-initialize the respective
  HS-UART core instance used by the client.

*/
typedef
RETURN_STATUS
(EFIAPI *SETBAUD) (
    IN UINTN baud_rate
);

/* OPEN_EX */ 
/** @ingroup efi_hsuart_protocol_apis
  @par Summary
  This function is called by the client code to initialize the respective 
  HS-UART core instance used by the client.
  
  @param[in]   instance              HSUART core that client intend
  									 to initialize.
  @param[in]   open configs          Open configuratios for HSUART instance.
  @param[out]  HSUART_Handle         Handle to HSUART core.
  
*/
typedef
RETURN_STATUS
(EFIAPI *OPEN_EX) (
	hsuart_instance instance,
	hsuart_open_config *config,
	void **hsuart_handle
);

/* READ_EX */
/** @ingroup efi_hsuart_protocol_apis
  @par Summary
  Performs an hsuart read.

  @param[in]  HSUART_Handle         Handle to HSUART core.
  @param[out] buffer                Buffer into which data is read.
  @param[in]  buffer_len            Length of data that needs to be read.
                                    the slave.
  @return 
  Actual bytes read
*/
typedef
UINTN
(EFIAPI *READ_EX) (
	void *hsuart_handle,
    OUT UINT8 *user_buffer,
    IN UINTN bytes_requested
);

/* WRITE_EX */
/** @ingroup efi_hsuart_protocol_apis
  @par Summary
  Performs an hsuart write.

  @param[in]  HSUART_Handle         Handle to HSUART core.
  @param[out] buffer                Buffer from which data is written.
  @param[in]  buffer_len            Length of data that needs to be written.
                                    the slave.

  @return 
  Actual bytes written
*/
typedef
UINTN
(EFIAPI *WRITE_EX) (
	void *hsuart_handle,
    IN UINT8 *user_buffer,
    IN UINTN bytes_to_send
);

/* POLL_EX */
/** @ingroup efi_hsuart_protocol_apis
  @par Summary
  Polls for RX Watermark
  
  @param[in]  HSUART_Handle         Handle to HSUART core.

  @return 
  Boolean TRUE if watermark set and vice versa.
*/
typedef
BOOLEAN
(EFIAPI *POLL_EX) (
	void *hsuart_handle
);

/* CLOSE_EX */ 
/** @ingroup efi_hsuart_protocol_apis
  @par Summary
  This function is called by the client code to de-initialize the respective 
  HS-UART core instance used by the client.
  
  @param[in]  HSUART_Handle         Handle to HSUART core.
  
*/
typedef
RETURN_STATUS
(EFIAPI *CLOSE_EX) (
	void *hsuart_handle
);

/* SETBAUD_EX */
/** @ingroup efi_hsuart_protocol_apis
  @par Summary
  This function is called by the client code to change the baudrate.
  
  @param[in]  HSUART_Handle         Handle to HSUART core.
  @param[in]  baudrate              Baud rate to be set.

*/
typedef
RETURN_STATUS
(EFIAPI *SETBAUD_EX) (
	void *hsuart_handle,
    IN UINTN baud_rate
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_hsuart_protocol_prot
  @par Summary
  Qualcomm HS-UART Protocol interface.

  @par Parameters
  @inputprotoparams{hsuart_proto_params.tex} 
*/
struct _EFI_QCOM_HSUART_PROTOCOL {
  UINT64        Revision;           /* Added in HSUART_DXE_REVISION_1 */
  OPEN          open;               /* Added in HSUART_DXE_REVISION_1 */
  READ          read;               /* Added in HSUART_DXE_REVISION_1 */
  WRITE         write;              /* Added in HSUART_DXE_REVISION_1 */
  POLL          poll;               /* Added in HSUART_DXE_REVISION_1 */
  CLOSE         close;              /* Added in HSUART_DXE_REVISION_1 */
  SETBAUD       set_baudrate;       /* Added in HSUART_DXE_REVISION_1 */
  OPEN_EX       open_ex;            /* Added in HSUART_DXE_REVISION_1 */
  READ_EX       read_ex;            /* Added in HSUART_DXE_REVISION_1 */
  WRITE_EX      write_ex;           /* Added in HSUART_DXE_REVISION_1 */
  POLL_EX       poll_ex;            /* Added in HSUART_DXE_REVISION_1 */
  CLOSE_EX      close_ex;           /* Added in HSUART_DXE_REVISION_1 */
  SETBAUD_EX    set_baudrate_ex;    /* Added in HSUART_DXE_REVISION_1 */
};

#endif	/* __EFIHSUART_H__ */
