/**
 * @file mhi.c
 *
 * @brief This file contains the NULL implementation of the public MHI device
 * driver interface.
 */
/*============================================================================
               Copyright (c) 2023 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
/**
 * @brief      mhi_init
 *
 *             Initialize the MHI SW stack. Among other things, this includes initializing
 *             MMIO registers, internal data structures, MHI link layer, core layer, power management and state machine.
 *             Once finished set MHI status to ready to indicate to Host that we are initialized.
 *
 *
 * @dependencies
 *             None
 *
 * @return
 *             MHI_SUCCESS if operation succeeded
 *
 * @sideeffect None
 */
mhi_status_t mhi_init(void)
{
   return MHI_ERROR;
}

/**
 * @brief      mhi_deinit
 *
 *             De-Initialize the MHI driver
 *
 *
 * @param[in]  reset - Whether to reset the MMIO or leave it as is
 *
 * @dependencies
 *             mhi_init must be first called
 *
 *
 * @return
 *             MHI_SUCCESS if operation succeeded
 *
 * @sideeffect None
 */
mhi_status_t mhi_deinit(boolean reset)
{
   return MHI_ERROR;
}


/**
 * @brief      mhi_channel_open
 *
 *             Opens an MHI channel. This must be called before doing any read/write operations
 *             on the channel. A return, with one of the below values  is generated immediately if
 *             MHI STATE != MHI_STATE_READY. If state is READY, this function will wait for the HOST to finish
 *             configuring channels before it returns it's result. If however a CB is specified, then it
 *             will do an async notification once MHI has started.
 *
 * @param[in]  chId - ID of channel to open. Refer to latest MHI SPEC for list of channels
 * @param[in]  cb   - Callback type that specifies user supplied data and function to be called for
 *                    async notification.
 *
 * @dependencies
 *              mhi_init must be called before any other API
 *
 * @return
 *              MHI_SUCCESS if operation succeeded
 *              MHI_CH_INVAlID if channel is invalid or not enabled
 *              MHI_PENDING a result will be notified asynchronously
 *
 * @sideeffect  None
 */
mhi_status_t mhi_channel_open(uint32 chId, mhi_cb_t *cb)
{
   return MHI_ERROR;
}

/**
 * @brief      mhi_channel_abort
 *
 *             Aborts issued channel operations
 *
 *
 * @param[in]  chId - Channel id
 *
 * @dependencies
 *             mhi_channel_open must be called first
 *
 *
 * @return
 *             None
 *
 * @sideeffect None
 */
mhi_status_t mhi_channel_abort(uint32 chId)
{
   return MHI_ERROR;
}

/**
 * @brief      mhi_channel_close
 *
 *             Closes an MHI channel that was previously opened. The channel must be in DISABLED/ENABLED
 *             If it is not the channel will be set to ERROR state and an error condition will be generated
 *             to the host. This function is not expected to be called unless we are doing a total cleanup.
 *
 * @param[in]  chId - ID of channel.  Refer to <MHISPEC> for list of channels
 * @param[in]  cb   - Callback type that specifies user supplied data and function to be called for
 *                    async notification. If null, a sync operation is performed
 *
 * @dependencies
 *             Channel must be first opened.
 *
 * @return
 *             MHI_SUCCESS if operation succeeded
 *             MHI_CH_INVALID if channel was never opened
 *             MHI_CH_NOT_IDLE if channel is not in DISABLED/ENABLED state
 *
 * @sideeffect None
 */
mhi_status_t mhi_channel_close(uint32 chId)
{
   return MHI_ERROR;
}

/**
 * @brief      mhi_channel_rw_multiple
 *
 *             Internal function that issues multiple reads/writes on a particular channel. This function can only be used in
 *             asynchronous mode. In asynchronous mode tt will return immediately, and the cb supplied
 *             will be called with the status of the operation
 *
 *
 *
 * @param[in]  chId  - Channel to read/write on
 * @param[in]  *data_array - Pointer to local data buffer array to read in to , or write from
 * @param[in]  *size_array  - Pointer to size array describing the sizes of the buffers
 * @param[in]  nElements - Number of buffers in data and size array
 * @param[out] *nSubmitted - Number of buffers that were actually submitted
 * @param[in]  bytesrw  - Number of bytes read/written. Applies only to MHI_WRITE or MHI_READ
 * @param[in]  *cb      - CB to be used for asynchronous operation
 * @param[in]  op -  MHI operation read or write
 *
 * @dependencies
 *             mhi_channel_open must be called first
 *
 *
 * @return
 *             MHI_SUCCESS if operation succeeded
 *
 * @sideeffect None
 */
mhi_status_t mhi_channel_rw_multiple(uint32 chId, void** data_array, uint32* size_array, uint32 nElements, uint32 *nSubmitted, uint32* bytesrw, mhi_cb_t *cb, mhi_op_t op)
{
   return MHI_ERROR;
}

/**
 * @brief      mhi_channel_write
 *
 *             Writes data over a channel. The channel direction must be IN. If CB is specified
 *             the function will return with MHI_PENDING and perform an async notification
 *             once the write is completed. Otherwise this function will block until completion
 *             of the write. payload.bytesWritten will be set to actual amount of bytes written.
 *             Likewise in synchronous mode, bytesWritten will be set to actual size written.
 *
 * @param[in]  chId - ID of channel.  Refer to <MHISPEC> for list of channels
 * @param[in]  data - physical address of data to send
 * @param[in]  size - number of bytes to write
 * @param[out] bytesWritten - actual amount of bytes written
 * @param[in]  cb   - Callback type that specifies user supplied data and function to be called for
 *                    async notification
 *
 * @dependencies
 *              Channel must be first opened.
 *
 * @return
 *              MHI_SUCCESS if operation succeeded
 *              MHI_CH_INVALID if channel is invalid
 *              MHI_CH_INVALID_WRITE channel direction does not permit a write
 *              MHI_INVALID_ADDR data buffer address is invalid
 *              MHI_PENDING a result will be notified asynchronously
 *              MHI_INCOMPLETE - bytes were written but not all of them
 *
 *
 * @sideeffect  None
 */

mhi_status_t mhi_channel_write(uint32 chId, void* data, uint32 size, uint32 *bytesWritten, mhi_cb_t *cb )
{
   return MHI_ERROR;
}

/**
 * @brief      mhi_channel_read
 *
 *             Reads data over a channel. The channel direction must be OUT. If CB is specified
 *             the function will return with MHI_PENDING and perform an async notification
 *             once the read is completed . Otherwise the function will block until completion
 *             of the read. payload.bytesRead of mhi_return_t will be set to actual number of bytes read.
 *             Clients should always check bytesRead, as a read can be terminated by
 *             EOT (end of transaction)
 *
 * @param[in]  chId - ID of channel.  Refer to <MHISPEC> for list of channels
 * @param[out] data - physical address of data buffer to receive the read data
 * @param[in]  size - size of data buffer in bytes
 * @param[out] bytesRead - bytes actually read
 * @param[in]  cb   - Callback type that specifies user supplied data and function to be called for
 *                    async notification
 *
 * @dependencies
 *              Channel must be first opened.
 *
 * @return
 *              MHI_SUCCESS if operation succeeded
 *              MHI_CH_INVALID if channel is invalid
 *              MHI_CH_INVALID_READ channel direction does not permit a read
 *              MHI_INVALID_ADDR if data address is invalid
 *              MHI_PENDING a result will be notified asynchronously
 *
 *
 * @sideeffect  None
 */
mhi_status_t mhi_channel_read(uint32 chId, void* data, uint32 size, uint32 *bytesRead, mhi_cb_t *cb )
{
   return MHI_ERROR;
}

/**
 * @brief      mhi_channel_read_null
 *
 *             Reads null data. As optimization no actual read is performed, rather we only consume the ring TRB by the size
 *             specified
 *
 *
 * @param[in]  chId - Channel id
 * @param[in]  size - Size to consume
 * @param[in]  *bytesRead - Set to actual size consumed if api is used synchronously
 * @param[in]  *cb - CB type that specifies user supplied data and function to be called for async notification
 *
 * @dependencies
 *             None
 *
 *
 * @return
 *             None
 *
 * @sideeffect None
 */
mhi_status_t mhi_channel_read_null(uint32 chId, uint32 size, uint32 *bytesRead, mhi_cb_t *cb )
{
   return MHI_ERROR;
}

/**
 * @brief      mhi_channel_read_multiple
 *
 *             Reads multiple data requests over a channel. The channel direction must be OUT.
 *             The operation of this request will be asynchronous.
 *             payload.bytesRead of mhi_return_t will be set to actual number of bytes read.
 *             Client should always check bytesRead, as a read can be terminated by
 *             EOT (end of transaction)
 *
 * @param[in]  chId - ID of channel.  Refer to <MHISPEC> for list of channels
 * @param[in]  *data_array - physical address of data buffer to receive the read data
 * @param[in]  *size_array - size of data buffer in bytes
 * @param[in]  nElements - Number of buffers in data and size array
 * @param[out] *nSubmitted - Number of buffers that were actually submitted
 * @param[in]  cb   - Callback type that specifies user supplied data and function to be called for
 *                    async notification
 *
 * @dependencies
 *              Channel must be first opened.
 *
 * @return
 *              MHI_SUCCESS if operation succeeded
 *              MHI_CH_INVALID if channel is invalid
 *              MHI_CH_INVALID_READ channel direction does not permit a read
 *              MHI_INVALID_ADDR if data address is invalid
 *              MHI_PENDING a result will be notified asynchronously all buffers accepted
 *              MHI_OP_FULL - operation queue full, not all buffers accepted. Check nSubmitted
 *
 *
 * @sideeffect  None
 */

mhi_status_t mhi_channel_read_multiple(uint32 chId, void** data_array, uint32* size_array, uint32 nElements, uint32 *nSubmitted, mhi_cb_t *cb)
{
   return MHI_ERROR;
}

/**
 * @brief      mhi_channel_write
 *
 *             Writes multiple data requests over a channel. The channel direction must be IN.
 *             The operation of this request will be asynchronous.
 *             payload.bytesRead of mhi_return_t will be set to actual number of bytes written.
 *
 * @param[in]  chId - ID of channel.  Refer to <MHISPEC> for list of channels
 * @param[in]  *data_array - physical address of data buffer to receive the read data
 * @param[in]  *size_array - size of data buffer in bytes
 * @param[in]  nElements - Number of buffers in data and size array
 * @param[out] *nSubmitted - Number of buffers that were actually submitted
 * @param[in]  cb   - Callback type that specifies user supplied data and function to be called for
 *                    async notification
 *
 * @dependencies
 *              Channel must be first opened.
 *
 * @return
 *              MHI_SUCCESS if operation succeeded
 *              MHI_CH_INVALID if channel is invalid
 *              MHI_CH_INVALID_READ channel direction does not permit a read
 *              MHI_INVALID_ADDR if data address is invalid
 *              MHI_PENDING a result will be notified asynchronously all buffers accepted
 *              MHI_OP_FULL - operation queue full, not all buffers accepted. Check nSubmitted
 *
 *
 * @sideeffect  None
 */
mhi_status_t mhi_channel_write_multiple(uint32 chId, void** data_array, uint32* size_array, uint32 nElements, uint32 *nSubmitted, mhi_cb_t *cb)
{
   return MHI_ERROR;
}

/**
 * @brief      mhi_poll
 *
 *             Polls MHI for any pending operations
 *
 * @return
 *             None
 *
 * @sideeffect None
 */
void mhi_poll(void)
{
   return;
}

/**
 * @brief      mhi_is_enumerated
 *
 *             Returns true if MHI is enumerated by host
 *
 *
 *
 * @dependencies
 *             None
 *
 *
 * @return
 *             MHI_BOOT_ENUMERATED, MHI_AMSS_ENUMERATED, MHI_DISABLED
 *
 * @sideeffect  None
 */
mhi_status_t mhi_is_enumerated(void)
{
   return MHI_ERROR;
}

/**
 * @brief  mhi_is_edl_mode
 *
 *        Check if EDL mode is enabled by updating cookie at MHI
 *        DB channel by host.
 *
 * @return boolean  TRUE if enabled else FALSE.
 */
boolean mhi_is_edl_mode(void)
{
    return FALSE;
}

/**
 * This function enables or disables MHI DMA.
 *
 * @param[in]  enable  Whether to enable DMA
 *
 * @return None
 */
void mhi_set_dma_enable(boolean enable)
{
   return;
}
