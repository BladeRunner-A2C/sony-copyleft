/** 
  @file  SpiApi.h
  @brief SPI APIs
*/
/*=============================================================================
  Copyright (c) 2014, 2019 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/15/19   bn	   SPI driver support for UEFI
 09/23/14   sg     Created

=============================================================================*/

#ifndef __SPIAPI_H__
#define __SPIAPI_H__

#include "SpiDeviceTypes.h"
#include "SpiDevice.h"
#include "Spi_common.h"


/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/* spi_open */ 
/** @ingroup spi_open
  @par Summary
  This function is called by the client code to initialize the respective 
  SPI core instance used by the client. On success, spi_handle points to the handle 
  for the SPI core. 
  
  @param[in]  instance              SPI core instance that the client intends to
                                    initialize; see #spi_instance for 
                                    details.
  @param[out] spi_handle            Pointer location to be filled by the
                                    driver with a handle to the core.

  @return
  See #spi_status for details.
*/
spi_status 
spi_open( 
	spi_instance instance, 
	void **spi_handle 
);

/**
  spi_transfer ()

  @brief
  Transfer implementation of EFI_QCOM_SPI_PROTOCOL
 */
spi_status 
spi_transfer( 
		void	*spi_handle,
		SpiDeviceInfoType	*devInfo,
		CONST UINT8	*write_buffer,
		UINT32	write_len,
		UINT8	*read_buffer,
		UINT32	read_len
);


/* spi_close */ 
/** @ingroup spi_close
  @par Summary
  De-initializes the SPI core.

  @param[in] spi_handle             Handle to the SPI core.

  @return
  See #spi_status for details.
*/
spi_status
spi_close(
    void *spi_handle
);

#endif	/* __SPIAPI_H__ */
