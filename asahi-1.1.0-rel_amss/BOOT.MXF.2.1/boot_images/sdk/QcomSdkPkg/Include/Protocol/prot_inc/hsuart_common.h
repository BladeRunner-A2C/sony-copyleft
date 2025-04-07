/** 
  @file  hsuart_common.h
  @brief HSUART header file
*/
/*=============================================================================
  Copyright 2019-2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/

/*=============================================================================z
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/04/23   RK     Created

=============================================================================*/

#ifndef __HSUART_COMMON_H__
#define __HSUART_COMMON_H__

/** @defgroup efi_hsuart_protocol EFI_HSUART_PROTOCOL
 *  @ingroup INTERFACES 
 */
 /** @defgroup  efi_hsuart_protocol_prot PROTOCOL
 *  @ingroup efi_hsuart_protocol 
 */ 
 /** @defgroup  efi_hsuart_protocol_apis APIs
 *  @ingroup efi_hsuart_protocol 
 */ 

/** @defgroup  efi_hsuart_protocol_data DATA_STRUCTURES
 *  @ingroup efi_hsuart_protocol 
 */
/** @ingroup efi_hsuart_protocol_data
  HSUART core passed to the hsuart_open() function. 
*/
typedef enum {
  HSUART_INSTANCE_001,          /**< Instance 01. */
  HSUART_INSTANCE_002,          /**< Instance 02. */
  HSUART_INSTANCE_003,          /**< Instance 03. */
  HSUART_INSTANCE_004,          /**< Instance 04. */
  HSUART_INSTANCE_005,          /**< Instance 05. */
  HSUART_INSTANCE_006,          /**< Instance 06. */
  HSUART_INSTANCE_007,          /**< Instance 07. */
  HSUART_INSTANCE_008,          /**< Instance 08. */
  HSUART_INSTANCE_009,          /**< Instance 09. */
  HSUART_INSTANCE_010,          /**< Instance 10. */
  HSUART_INSTANCE_011,          /**< Instance 11. */
  HSUART_INSTANCE_012,          /**< Instance 12. */
  HSUART_INSTANCE_013,          /**< Instance 13. */
  HSUART_INSTANCE_014,          /**< Instance 14. */
  HSUART_INSTANCE_015,			/**< Instance 15. */
  HSUART_INSTANCE_016,			/**< Instance 16. */
  HSUART_INSTANCE_017,			/**< Instance 17. */
  HSUART_INSTANCE_018,			/**< Instance 18. */
  HSUART_INSTANCE_019,			/**< Instance 19. */
  HSUART_INSTANCE_020,			/**< Instance 20. */
  HSUART_INSTANCE_021,			/**< Instance 21. */
  HSUART_INSTANCE_022,			/**< Instance 22. */
  HSUART_INSTANCE_023,			/**< Instance 23. */
  HSUART_INSTANCE_024,			/**< Instance 24. */
  HSUART_INSTANCE_MAX,			/**< Instance Max.*/
} hsuart_instance;

/** @ingroup efi_hsuart_protocol_data
  Function status codes.
*/
typedef enum
{
   HSUART_SUCCESS = 0,
   HSUART_ERROR,
}hsuart_result;

typedef void* hsuart_handle;

typedef void(*HSUART_CALLBACK)(UINT32 num_bytes, void *cb_data);

/** @ingroup efi_hsuart_protocol_data
*/
typedef enum
{
  HSUART_5_BITS_PER_CHAR  = 0,
  HSUART_6_BITS_PER_CHAR  = 1,
  HSUART_7_BITS_PER_CHAR  = 2,
  HSUART_8_BITS_PER_CHAR  = 3,
} hsuart_bits_per_char;

/** @ingroup efi_hsuart_protocol_data
*/
typedef enum
{
  HSUART_0_5_STOP_BITS    = 0,
  HSUART_1_0_STOP_BITS    = 1,
  HSUART_1_5_STOP_BITS    = 2,
  HSUART_2_0_STOP_BITS    = 3,
} hsuart_num_stop_bits;

/** @ingroup efi_hsuart_protocol_data
*/
typedef enum
{
  HSUART_NO_PARITY        = 0,
  HSUART_ODD_PARITY       = 1,
  HSUART_EVEN_PARITY      = 2,
  HSUART_SPACE_PARITY     = 3,
} hsuart_parity_mode;

/** @ingroup efi_hsuart_protocol_data
*/
typedef struct
{
   UINT32                baud_rate;
   hsuart_parity_mode      parity_mode;
   hsuart_num_stop_bits    num_stop_bits;
   hsuart_bits_per_char    bits_per_char;
   UINT32                enable_loopback;

   // The callbacks will be called from ISR context.
   // Necessary precautions needs to be taken in these functions to make sure not ISR guidelines
   // are violated.
   // DONT call uart_transmit or uart_receive API from these callback.
   HSUART_CALLBACK         tx_cb_isr;
   HSUART_CALLBACK         rx_cb_isr;
}hsuart_open_config;


#endif	/* __HSUART_COMMON_H__ */
