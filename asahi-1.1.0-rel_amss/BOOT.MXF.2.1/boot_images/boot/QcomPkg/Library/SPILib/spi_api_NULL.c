
/*=============================================================================   
    @file  spi_api_NULL.c
    @brief SPI public API NULL implementation
   
    Copyright (c) 2023 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.
===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/09/23   MG     Created
 
=============================================================================*/

#include "SpiApi.h"    // implement the apis defined here
#include "spi_api.h"
#include "spi_drv.h"    // generic objects for an spi driver
#include <Uefi.h>

typedef void (*callback_fn) (uint32 transfer_status, void *callback_ctxt);

spi_hw_ctxt *spi_cores_head = NULL; 
 

spi_status spi_open (spi_instance instance, void **spi_handle)
{
   return (spi_status) EFI_UNSUPPORTED;
}

spi_status spi_close(void *spi_handle)
{
   return (spi_status) EFI_UNSUPPORTED;
}

spi_status spi_power_on (void *spi_handle)
{
   return (spi_status) EFI_UNSUPPORTED;
   
}

spi_status spi_power_off (void *spi_handle)
{
   return (spi_status) EFI_UNSUPPORTED;
}

spi_status spi_transfer( 
		void	*spi_handle,
		SpiDeviceInfoType	*devInfo,
		CONST UINT8	*write_buffer,
		UINT32	write_len,
		UINT8	*read_buffer,
		UINT32	read_len
)
{
   return (spi_status) EFI_UNSUPPORTED;
}

/* spi_full_duplex: Perform full duplex transfer over SPI BUS.
This is the only available transfer function. Callback is invoked upon completion of the full chain of
descriptors or an error condition.
*/
spi_status spi_full_duplex
(
    void *spi_handle,
    spi_config_t *config,
    spi_descriptor_t *desc,
    uint32 num_descriptors,
    callback_fn c_fn,
    void *caller_ctxt,
    boolean get_timestamp,
    boolean is_last
    )
{
   return (spi_status) EFI_UNSUPPORTED;
}
