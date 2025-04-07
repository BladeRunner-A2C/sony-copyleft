/**
@file  EFISpcom.h
@brief Spcom Protocol for UEFI.
*/
/*=============================================================================
Copyright (c) 2022 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     -----------------------------------------------------------
12/31/22   vp      Porting Health api from Makena
12/08/22   gn      Porting the SPSSProtocol files from Makena and updating
                   the protocol version
12/09/21   vp      Allocate/free memory used for SpNvmDxe callback in Spcomdxe
04/14/21   nc      spcom_unregister_client crash fix
02/24/21   vp      Add PollNvmCh api
01/11/21   vp      Load API fix
12/10/20   vp      Update Api Documentation
06/15/20   vp      initial release
=============================================================================*/

#ifndef __EFISPCOM_H__
#define __EFISPCOM_H__

#include <prot_dtypes.h>
/*
 * Protocol version.
 *
 */
#define SPCOM_REVISION EFI_SPCOM_PROTOCOL_VERSION_1_5
#define EFI_SPCOM_PROTOCOL_VERSION_1_5 0x0000000000010005

/*  Protocol GUID definition */
#define EFI_SPCOM_PROTOCOL_GUID \
  { 0x49623199, 0xa6a0, 0x4cba, { 0x9d, 0xf7, 0xaf, 0x06, 0xa3, 0xcc, 0xc0, 0x99 } }

/* Maximum number of logical channels supported */
#define SPCOM_MAX_CHANNELS     20

/* Maximum size (including null) for channel names - match GLINK_NAME_SIZE */
#define SPCOM_CHANNEL_NAME_SIZE        32

/**
 * Request buffer size.
 * Any large data (multiply of 4KB) is provided by temp buffer in DDR.
 */
#define SPCOM_MAX_REQUEST_SIZE         268
#define SPCOM_MAX_RESPONSE_SIZE        268


/**
 * Abstract spcom handle.
 * The actual struct definition is internal to the SpcomDxe.
 */
struct spcom_client; /* Forward declaration */

/**
 * Abstract spcom handle.
 * The actual struct definition is internal to the SpcomDxe.
 */
struct spcom_server; /* Forward declaration */

/**
 * Client registration info
 *
 * @ch_name:    glink logical channel name
 */
struct spcom_client_info {
        const char *ch_name;
};

/**
 * Server registration info
 *
 * @ch_name:   glink logical channel name
 * @notify_server_request_cb: callback to be used when the command on
 *      specific channel is pending.
 */
struct spcom_service_info {
       const char *ch_name;
       void (*notify_server_request_cb)(struct spcom_server*, const void*, size_t, void*, size_t *const, void* server_param); /* Valid only if server is in UEFI */
       void * server_param;
};

/**
 * Enum used to request SP health data.
 */
typedef enum {
    SP_HEALTH_ARI_MODE,
    SP_HEALTH_ARI_FUSE_GAUGE,
    SP_HEALTH_FIPS_ENABLED,
    SP_HEALTH_FIPS_SELF_TEST,
    SP_HEALTH_SENSORS_CALIBRATED,
    SP_HEALTH_ALL_TESTS,
    SP_HEALTH_GET_ARI_ON_FUSE
} sp_health_status_t;

/**
 * por_data_struct is por_data field in
 * sp_health_status_data struct
 */
typedef struct {
  uint8_t por_counter;
  uint8_t normal_boot_count_since_por;
  uint16_t commit_count_since_por;
} por_data_struct;

/**
 * ari_mismatch_data_struct is mismatch_data
 * field in sp_health_status_data struct
 */
typedef struct {
  uint8_t current_boot_mismatch;
  uint8_t por_boot_mismatch_num;
  uint8_t normal_boot_mismatch_num;
  uint8_t fuse_count_left_by_granularity;
} ari_mismatch_data_struct;


/**
 * Status returned by Health API.
 * The values in reservedx members shall be ignored.
 */
struct sp_health_status_data{
    uint32_t ari_lifecycle_state;
    uint32_t reserved1;
    uint32_t fips_enabled;
    uint32_t fips_self_test_passed;
    uint32_t sensors_calibrated;
    uint32_t reserved2;
    uint16_t por_indicator;
    uint16_t nvm_result;
    por_data_struct por_data;
    uint32_t aux_data0;
    uint32_t aux_data1;
    uint32_t aux_data2;
    uint32_t aux_data3;
    ari_mismatch_data_struct mismatch_data;
    uint32_t ari_fuse_gauge;
};

/*===========================================================================
EXTERNAL VARIABLES
===========================================================================*/
/**
External reference to the Spcom Protocol GUID.
*/

extern EFI_GUID gEfiSpcomProtocolGuid;

/*===========================================================================
TYPE DEFINITIONS
===========================================================================*/
/**
Protocol declaration.
*/
typedef struct _EFI_SPCOM_PROTOCOL EFI_SPCOM_PROTOCOL;

/**
 * IsAppLoaded() - check if the SP App is already loaded.
 *
 * This API will check if logical channel node has been created.
 *
 * @param[in]  ch_name       glink logical channel name.
 *
 * @return:
 *    EFI_SUCCESS           SPU Application is loaded
 *    EFI_TIMEOUT           Operation timed out
 *    EFI_INVALID_PARAMETER Invalid ch_name
 *    EFI_NOT_FOUND         SPU Application is not loaded
 *    EFI_DEVICE_ERROR      Connection error
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_IS_APP_LOADED) (const char *ch_name);

/**
 * IsSpssLinkUp()
 *
 * Checks if SPSS link is up.
 *
 * @return:
 *    EFI_SUCCESS if link is up
 *    EFI_TIMEOUT Operation timed out, spss link is not up
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_IS_SPSS_LINK_UP) (VOID);

/**
 * RegisterClient() - register client for channel
 *
 * @param[in]   info:     glink logical channel name info.
 * @param[out]  client:   Valid client handle on sucess,
 *                        NULL on failure.
 *
 * @return:
 *    EFI_SUCCESS           registration is successful
 *    EFI_INVALID_PARAMETER Invalid input param
 *    EFI_DEVICE_ERROR      Connection error
 *
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_REGISTER_CLIENT) (struct spcom_client_info *info, struct spcom_client **client);

/**
 * UnregisterClient() - unregister client for channel
 *
 * @client:    Client Handle.
 *
 * @return:
 *    EFI_SUCCESS           un-register is successful
 *    EFI_INVALID_PARAMETER Invalid input param
 *    EFI_DEVICE_ERROR      Connection error
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_UNREGISTER_CLIENT) (struct spcom_client **client);
/**
 * ClientSendMessage() - Send a synchronous request and response
 *
 * @param[in] client:       a pointer to spcom client
 * @param[in] req_ptr:      a pointer to the request buffer
 * @param[in] req_size:     size of the request buffer
 * @param[in] resp_ptr:     a pointer to the response buffer
 * @param[in] resp_size:    size of the response buffer
 * @param[out] rx_size:     num of rx bytes on success
 * @param[in] timeout_msec: Timeout in msec between command and response, 0=no timeout.
 *
 * @return:
 *    EFI_SUCCESS           Command is successfully sent
 *    EFI_DEVICE_ERROR      Connection error
 *    EFI_INVALID_PARAMETER Invalid input param
 *    EFI_OUT_OF_RESOURCES  Memory allocation failed
 *    EFI_TIMEOUT           Operation timed out
 *    EFI_ABORTED           Received channel abort from Glink
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_CLIENT_SEND_MESSAGE) (struct spcom_client *client,
                                         void *req_ptr, size_t req_size,
                                         void *resp_ptr, size_t resp_size,
                                         size_t *rx_size,
                                         size_t timeout_msec);

/**
 * ClientIsServerConnected() - Check if remote server connected.
 *
 * This API checks that the logical channel is fully connected between
 * the client and the server. Normally, the server should be up first
 * and connect first.
 *
 * @param[in] client:    a pointer to spcom client
 *
 * @return:
 *    EFI_SUCCESS    Server connected with client
 *    EFI_NOT_FOUND  Server not connected with client
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_CLIENT_IS_SERVER_CONNECTED) (struct spcom_client *client);

/**
 * RegisterService() - register server for channel
 *
 * Only one client/Server can register on each side of a channel.
 *
 * @param[in]  info:      Server configuration info (input).
 * @param[out] server:    Server handle on sucess, NULL on failure
 *
 * @return:
 *    EFI_SUCCESS           registration is successful
 *    EFI_INVALID_PARAMETER Invalid input param
 *    EFI_DEVICE_ERROR      Connection error
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_REGISTER_SERVICE) (struct spcom_service_info *info, struct spcom_server **server);

/**
 * UnregisterService() - unregister server for channel
 *
 * @param[in] server:    server Handle.
 *
 * @return:
 *    EFI_SUCCESS on success
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_UNREGISTER_SERVICE) (struct spcom_server *server);

/**
 * ServerGetNextRequest() - Poll for data on the logical channel
 *
 * @param[out] server:    a pointer to spcom server
 *
 * @return:
 *    EFI_SUCCESS           Command is successfully sent
 *    EFI_DEVICE_ERROR      Connection error
 *    EFI_INVALID_PARAMETER Invalid input param
 *    EFI_OUT_OF_RESOURCES  Memory allocation failed
 *    EFI_TIMEOUT           Operation timed out
 *    EFI_ABORTED           Received channel abort from Glink
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_SERVER_GET_NEXT_REQUEST) (struct spcom_server *server);

/**
 * LoadSpApp() - Load Secure Processor Application
 *
 * @param[in] ch_name:    Glink logical channel name
 * @param[in] appGuid:    Guid of partition that contains the SPU application.
 * @param[in] image_size: Application image size
 * @param[in] swap_size:  The size required to store the context of this application when
 *             it is swapped in/out.
 * @param[out] load_resp_code: Response code from SPU
 *
 * @return:
 *    EFI_SUCCESS           Application is successfully loaded
 *    EFI_DEVICE_ERROR      Connection error
 *    EFI_INVALID_PARAMETER Invalid input param
 *    EFI_OUT_OF_RESOURCES  Memory allocation failed
 *    EFI_TIMEOUT           Operation timed out
 *    EFI_ABORTED           Received channel abort from Glink
 *    EFI_LOAD_ERROR        Application is already loaded
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_LOAD_APP) (const char *ch_name, EFI_GUID *appGuid,
      size_t image_size, size_t swap_size, size_t *load_resp_code);


/**
 * LoadSpAppFromBuffer() - Load Secure Processor Application
 *
 * @param[in]  ch_name:    Glink logical channel name
 * @param[in]  app_name:   Application name
 * @param[in]  image_buff: A pointer to a buffer which contains the image
 * @param[in]  image_size: Application image size
 * @param[in]  swap_size:  The size required to store the context of this application
 *              when it is swapped in/out.
 * @param[out] load_resp_code: Response code from SPU
 *
 * @note: If the App is in NTFS filesystem, spcomdxe doesnt have access
 * to NTFS. The client should copy image directly to DDR before calling this api.
 *
 * @return:
 *    EFI_SUCCESS           Application is successfully loaded
 *    EFI_DEVICE_ERROR      Connection error
 *    EFI_INVALID_PARAMETER Invalid input param
 *    EFI_OUT_OF_RESOURCES  Memory allocation failed
 *    EFI_TIMEOUT           Operation timed out
 *    EFI_ABORTED           Received channel abort from Glink
 *    EFI_LOAD_ERROR        Application is already loaded
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_LOAD_APP_FROM_BUFFER)(const char *ch_name,
      void *image_buff, size_t image_size, size_t swap_size, size_t *load_resp_code);


/**
 * SpcomAlloc() - allocate an buffer from SPSS reserved PIL region.
 *
 * @param[in]  ch_name: glink logical channel name
 * @param[in]  size:    allocation size.
 * @param[out] buf:     buffer pointer on success, NULL on failure.
 *
 * @return:
 *    EFI_SUCCESS        If valid buffer pointer is returned
 *    EFI_UNSUPPORTED    Shared buffer is not supported with given app
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_ALLOC)(const char *ch_name, void **buf, size_t size);


/**
 * SpcomFree() - Free the buffer.
 *
 * @param[in] ch_name:  glink logical channel name
 * @param[in] buf:      buffer pointer.
 * @param[in] size:     allocation size.
 *
 * @return:
 *    EFI_SUCCESS        Shared buffer is successfully cleared
 *    EFI_UNSUPPORTED    Shared buffer is not supported with given app
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_FREE)(const char *ch_name, void *buf, size_t size);

/**
 * PollNvmCh() - Polls for data on the NVM channels alternatively.
 *
 * NVM channels should be already registered as service.
 *
 * @return:
 *    EFI_SUCCESS           Command is successfully sent
 *    EFI_DEVICE_ERROR      Connection error
 *    EFI_INVALID_PARAMETER Invalid input param
 *    EFI_OUT_OF_RESOURCES  Memory allocation failed
 *    EFI_TIMEOUT           Operation timed out
 *    EFI_ABORTED           Received channel abort from Glink
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_POLL_NVM_CH) (VOID);

/**
 * CheckSPHealth() - Checks for SP health. This API shall be invoked
 *                   after SPNVMDxe entry routine has finished executing.
 *
 * @param[in]  health_status_param: health parameter
 * @param[in]  status_data_ptr:    resulting health data
 *
 * @return:
 *    EFI_SUCCESS           Command is successfully sent
 *    EFI_DEVICE_ERROR      Connection error
 *    EFI_INVALID_PARAMETER Invalid input param
 *    EFI_OUT_OF_RESOURCES  Memory allocation failed
 *    EFI_TIMEOUT           Operation timed out
 *    EFI_ABORTED           Received channel abort from Glink
 */
typedef EFI_STATUS
(EFIAPI *EFI_SPCOM_CHECK_SP_HEALTH) (sp_health_status_t health_status_param, 
      struct sp_health_status_data* status_data_ptr);

/*===========================================================================
PROTOCOL INTERFACE
===========================================================================*/

struct _EFI_SPCOM_PROTOCOL
{
    UINT64                                    Revision;
    EFI_SPCOM_IS_APP_LOADED                   IsAppLoaded;              /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_IS_SPSS_LINK_UP                 IsSpssLinkUp;             /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_REGISTER_CLIENT                 RegisterClient;           /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_UNREGISTER_CLIENT               UnregisterClient;         /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_CLIENT_SEND_MESSAGE             ClientSendMessage;        /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_CLIENT_IS_SERVER_CONNECTED      ClientIsServerConnected;  /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_REGISTER_SERVICE                RegisterService;          /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_UNREGISTER_SERVICE              UnregisterService;        /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_SERVER_GET_NEXT_REQUEST         ServerGetNextRequest;     /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_LOAD_APP                        LoadSpApp;                /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_LOAD_APP_FROM_BUFFER            LoadSpAppFromBuffer;      /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_ALLOC                           SpcomAlloc;               /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_FREE                            SpcomFree;                /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
    EFI_SPCOM_POLL_NVM_CH                     PollNvmCh;                /* Added in EFI_SPCOM_PROTOCOL_VERSION_1_4 */
	EFI_SPCOM_CHECK_SP_HEALTH                 CheckSPHealth;			/* Added in EFI_SPCOM_PROTOCOL_VERSION_1_5 */
};

#endif
