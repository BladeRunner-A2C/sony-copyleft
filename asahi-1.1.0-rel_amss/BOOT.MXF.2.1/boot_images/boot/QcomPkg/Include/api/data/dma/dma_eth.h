#ifndef DMA_ETH_H
#define DMA_ETH_H
/*==============================================================================

                DMA_ETH.H

DESCRIPTION
  This file contains the declarations of IPA DMA channels

Copyright 2022 Qualcomm Technologies Incorporated. 
All Rights Reserved.
Qualcomm Confidential and Proprietary
==============================================================================*/



/*==============================================================================

                          INCLUDE FILES FOR MODULE

==============================================================================*/

#include "comdef.h"
#include "dma_hw_err.h"

#define DMA_HW_TRANSFER_RING_NUM_ELEMENTS (0x80)


typedef enum {
	ECPRI_DMA_ENDP_STREAM_DEST_FH = 0,
	ECPRI_DMA_ENDP_STREAM_DEST_C2C = 1,
	ECPRI_DMA_ENDP_STREAM_DEST_L2 = 2,
	ECPRI_DMA_ENDP_STREAM_DEST_MAX = 3,
} ecpri_dma_endp_stream_dest_e;

typedef struct
{
	uint64 ptr;
	uint32 len;
	uint32 status;
} ecpri_comp_pkt_t;


typedef struct {
  uint8 stream_type;
  uint8 port_id;
  uint8 link_id;
} ecpri_dma_eth_connection_param_t;

typedef struct {
	uint8 stream_type;
} ecpri_dma_eth_disconnection_param_t;

/*============================================================================== 
   
  FUNCTION:  ecpri_dma_eth_connect

=============================================================================*/
/*!
    @brief

DESCRIPTION
This function is used to open a DMA HW CH.

PARAMETERS
param - Channel parameters for opening a new DMA CH.

RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed


DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 ecpri_dma_eth_connect(ecpri_dma_eth_connection_param_t* param);

/*============================================================================== 
   
  FUNCTION:  ecpri_dma_eth_rx_poll

=============================================================================*/
/*!
    @brief

DESCRIPTION
This function is used to poll for transfer completions


PARAMETERS
stream_type - type of stream to poll
budget - budget of packet to poll for
comp -  pointer to array of completed packet to fill.
        array must of of size == budget
        caller allocates array and passes pointer to it
num_of_comp -   actual number of packet polled
                allocated by caller

RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed

DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 ecpri_dma_eth_rx_poll(ecpri_dma_endp_stream_dest_e stream_type,
	uint32 budget, ecpri_comp_pkt_t* comp, uint32* num_of_comp);


/*============================================================================== 
   
  FUNCTION:  dma_eth_hw_init

=============================================================================*/
/*!
    @brief
 
FUNCTION dma_eth_hw_init()

DESCRIPTION
This Function initialize the DMA HW,
Must be called before write/read/poll operations


RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed

DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 dma_eth_hw_init(void);

/*============================================================================== 
   
  FUNCTION:  dma_eth_hw_deinit

=============================================================================*/
/*!
    @brief
 
DESCRIPTION
This Function de-initializes the DMA HW


RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed

DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 dma_eth_hw_deinit(void);


/*============================================================================== 
   
  FUNCTION:  ecpri_dma_eth_transmit

=============================================================================*/
/*!
    @brief

DESCRIPTION
This Function sends a write request to DMA HW
Function is blocking until transfer is completed in DMA HW

PARAMETERS
stream_type - type of stream to send packet on
pkt - Pointer to packet buffer
len - Size of the packet to send

RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed

DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 ecpri_dma_eth_transmit(ecpri_dma_endp_stream_dest_e stream_type,
	uint64 pkt, uint32 len);


/*============================================================================== 
   
  FUNCTION:  ecpri_dma_eth_rx_replenish

=============================================================================*/
/*!
    @brief

DESCRIPTION
This Function sends empty buffers for Rx

PARAMETERS
stream_type - type of stream to send packet on
buf -   Pointer to array of empty buffers
        Allocated by caller of size num_of_bufs
len -   Pointer to array of sizes of the empty buffers
        Allocated by caller of size num_of_bufs
num_of_bufs - Number of empty buffers in the array

RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed

DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 ecpri_dma_eth_rx_replenish(ecpri_dma_endp_stream_dest_e stream_type,
	uint64* buf, uint32* len, uint32 num_of_bufs);

/*============================================================================== 
   
  FUNCTION:  ecpri_dma_eth_disconnect

=============================================================================*/
/*!
    @brief

DESCRIPTION
This Function sends empty buffers for Rx

PARAMETERS
param - parameter for the connection to disconnect

RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed

DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 ecpri_dma_eth_disconnect(ecpri_dma_eth_disconnection_param_t* param);

#endif /* DMA_ETH_H */
