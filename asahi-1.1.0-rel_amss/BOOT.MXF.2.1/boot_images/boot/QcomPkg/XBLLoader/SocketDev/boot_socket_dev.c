/*=============================================================================

                     Boot Socket Device

GENERAL DESCRIPTION
  This file contains the implementation for boot layer that provides the APIs
  for reading and writing to a network socket.

Copyright 2022-2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
02/15/23   ck           Renamed edk2 interfaces
12/19/22   ck           Corrected net_api_lib_init call
10/05/22   ck           Initial revision.
=============================================================================*/

#include <string.h>
#include "net_api_socket.h"
#include "boot_socket_dev.h"
#include "boot_memory_mgr_if.h"
#include "boot_config_context.h"
#include "boot_cache_if.h"


/* Socket device handle ID */
#define SDEV 0x53444556


// Socket device handle
typedef struct boot_socket_dev_obj
{
  uint32 id;
  boot_memory_mgr_if_type * mem_if;
  uint32 local_ip_address;
  uint32 remote_ip_address;
  int32 socket_handle;
  uint16 local_port;
  uint16 remote_port;
  boolean connected;
}socket_device_handle;

static boot_boolean boot_socket_dev_is_hw_initialized = FALSE;


/*=========================================================================
**  Function :  _init
** ==========================================================================
*/
/*!
* 
* @brief
*   intialize the socket dev handle.
* 
* @param[in] pointer to socket dev handle
* 
*/
static void _init(socket_device_handle * socket_dev_handle)
{
  /* Clear socket device handle */
  memset((void *)socket_dev_handle,
          0,
          sizeof(socket_device_handle));


  /* Set socket handle to invalid */
  socket_dev_handle->socket_handle = -1;

  
  /* Populate id */
  socket_dev_handle->id = SDEV;
}


/*=========================================================================
**  Function :  _handle_check
** ==========================================================================
*/
/*!
* 
* @brief
*   Sanitize the socket device handle.
* 
* @param[in] socket device handle
* 
*/
static bl_error_boot_type _handle_check(socket_device_handle * socket_dev_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;


  /* Verify socket device handle pointer */
  if (socket_dev_handle == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Verify id */
  if (socket_dev_handle->id != SDEV)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INVALID_HANDLE);
    goto exit;
  }


  /* Verify handle parameters */
  if ((socket_dev_handle->mem_if == NULL) ||
      (socket_dev_handle->local_ip_address == 0) ||
      (socket_dev_handle->local_port == 0) ||
      (socket_dev_handle->remote_ip_address == 0) ||
      (socket_dev_handle->remote_port == 0))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }

    
 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_socket_dev_open
** ==========================================================================
*/
/*!
* 
* @brief
*   Function to create a socket and connect with external node.
* 
* @param[in] pointer to config context handle, pointer to socket dev handle pointer
*
* 
*/
static bl_error_boot_type boot_socket_dev_open(const boot_handle config_context_handle,
                                               boot_handle * boot_handle_ptr)
{
  bl_error_boot_type error = BL_ERR_NONE;
  socket_device_handle * socket_dev_handle = NULL;
  boot_memory_mgr_if_type * mem_if = NULL;
  uint32 temp_port = 0;
  struct sockaddr address;

  
  /* Verify pointers */
  if((config_context_handle == NULL) ||
     (boot_handle_ptr == NULL))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }
  

  /* Get memory manager interface from config context */
  error = boot_config_context_get_ptr(config_context_handle,
                                      CONFIG_CONTEXT_MEMORY_MGR_INTERFACE,
                                      (void **)&mem_if);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }

  if(mem_if == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }


  /* Malloc memory to hold socket device handle */
  error = mem_if->malloc(sizeof(socket_device_handle),
                         (void *)&socket_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }
  
  if(socket_dev_handle == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_MEMORY_ALLOC_FAIL);
    goto exit;
  }

  
  /* Initalize the socket device handle */
  _init(socket_dev_handle);


  /* Store memory interface in page device handle */
  socket_dev_handle->mem_if = mem_if;

  
  /* Get LOCAL IP address and port from config context */  
  error = boot_config_context_get_value(config_context_handle,
                                        CONFIG_CONTEXT_LOCAL_IP_ADDRESS,
                                        &socket_dev_handle->local_ip_address);
  if(error != BL_ERR_NONE)
  {
    goto free_and_exit;
  }

  /* IP ports are 16 bits but boot_config_context_get_value only supports 32 bit values. */
  /* Read from config context to a temp value and then truncate into sock_dev_handle */
  temp_port = 0;
  error = boot_config_context_get_value(config_context_handle,
                                        CONFIG_CONTEXT_LOCAL_IP_PORT,
                                        &temp_port);
  if(error != BL_ERR_NONE)
  {
    goto free_and_exit;
  }
  socket_dev_handle->local_port = temp_port & 0xFFFF;


  /* Get REMOTE IP address and port from config context */  
  error = boot_config_context_get_value(config_context_handle,
                                        CONFIG_CONTEXT_REMOTE_IP_ADDRESS,
                                        &socket_dev_handle->remote_ip_address);
  if(error != BL_ERR_NONE)
  {
    goto free_and_exit;
  }

  /* IP ports are 16 bits but boot_config_context_get_value only supports 32 bit values. */
  /* Read from config context to a temp value and then truncate into sock_dev_handle */
  temp_port = 0;
  error = boot_config_context_get_value(config_context_handle,
                                        CONFIG_CONTEXT_REMOTE_IP_PORT,
                                        &temp_port);
  if(error != BL_ERR_NONE)
  {
    goto free_and_exit;
  }
  socket_dev_handle->remote_port = temp_port & 0xFFFF;


  /* Verify all local and remote values */
  if((socket_dev_handle->local_ip_address == 0) ||
     (socket_dev_handle->local_port == 0) ||
     (socket_dev_handle->remote_ip_address == 0) ||
     (socket_dev_handle->remote_port == 0))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;
  }


  /* Create socket */
  socket_dev_handle->socket_handle = net_api_socket(AF_INET,
                                                    SOCK_STREAM,
                                                    0);
  if (socket_dev_handle->socket_handle < 0)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;
  }
  

  /* Bind socket */
  memset(&address,
         0,
         sizeof(address));

  address.sa_family = AF_INET;
  address.sa_port = htons(socket_dev_handle->local_port);
  memscpy(&address.sa_data,
          sizeof(address.sa_data),
          &(socket_dev_handle->local_ip_address),
          sizeof(socket_dev_handle->local_ip_address));

  if (net_api_bind(socket_dev_handle->socket_handle,
                   &address,
                   sizeof(address)) != 0)
  {
    /* Close socket and disregard any errors as not to overwrite original error */
    net_api_socketclose(socket_dev_handle->socket_handle);
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;
  }


  /* Connect to remote node */
  memset(&address,
         0,
         sizeof(address));

  address.sa_family = AF_INET;
  address.sa_port = htons(socket_dev_handle->remote_port);
  memscpy(&address.sa_data,
          sizeof(address.sa_data),
          &(socket_dev_handle->remote_ip_address),
          sizeof(socket_dev_handle->remote_ip_address));

  if (net_api_connect(socket_dev_handle->socket_handle,
                      &address,
                      sizeof(address)))
  {
    /* Close socket and disregard any errors as not to overwrite original error */
    net_api_socketclose(socket_dev_handle->socket_handle);
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INTERFACE_FAILURE);
    goto free_and_exit;   
  }


  /* Set connected flag */
  socket_dev_handle->connected = TRUE;


  /* Return pointer to new socket device handle created */
  *boot_handle_ptr = (boot_handle)socket_dev_handle;
  

 free_and_exit:
  /* If error is not BL_ERR_NONE then free memory. */
  if (error != BL_ERR_NONE)
  {
    mem_if->free(socket_dev_handle);
  }


 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_socket_dev_read
** ==========================================================================
*/
/*!
* 
* @brief
*   Receive from socket
* 
* @param[in] socket dev handle, pointer to destination, source offset,
* number of bytes to read
* 
*/
static bl_error_boot_type boot_socket_dev_read(const boot_handle media_handle,
                                               void * ram_addr,
                                               uint64 src_offset,
                                               uint32 bytes_to_read)
{
  bl_error_boot_type error = BL_ERR_NONE;
  socket_device_handle * socket_dev_handle = NULL;
  boot_cache_if_type * cache_if = NULL;


  /* Verify arguments passed */
  if ((media_handle == NULL) ||
      (ram_addr == NULL) ||
      (bytes_to_read == 0))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Assign validated pointers */
  socket_dev_handle = (socket_device_handle *)media_handle;

  
  /* Validate socket device handle entries */
  error = _handle_check(socket_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }


  /* Make sure socket is connected to remote node */
  if (!socket_dev_handle->connected)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_NOT_INITIALIZED);
    goto exit;
  }


  /* Obtain cache interface */
  error = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE,
                                      CONFIG_CONTEXT_CACHE_INTERFACE,
                                      (void **)&cache_if);

  if (error != BL_ERR_NONE)
  {
    goto exit;
  }

  if (cache_if == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }


  /* Flush receive buffer before reading */
  cache_if->InvalidateDataCacheRange(ram_addr,
                                     bytes_to_read);


  /* Receive data */
  if (net_api_recv(socket_dev_handle->socket_handle,
                   ram_addr,
                   bytes_to_read,
                   0) != bytes_to_read)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }


 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_socket_dev_write
** ==========================================================================
*/
/*!
* 
* @brief
*   Write to socket
* 
* @param[in] socket dev handle, pointer to destination, source offset,
* number of bytes to write
* 
*/
static bl_error_boot_type boot_socket_dev_write(const boot_handle media_handle,
                                                void * ram_addr,
                                                uint64 dst_offset,
                                                uint32 bytes_to_write)
{
  bl_error_boot_type error = BL_ERR_NONE;
  socket_device_handle * socket_dev_handle = NULL;
  boot_cache_if_type * cache_if = NULL;
  

  /* Verify arguments passed */
  if ((media_handle == NULL) ||
      (ram_addr == NULL) ||
      (bytes_to_write == 0))
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Assign validated pointers */
  socket_dev_handle = (socket_device_handle *)media_handle;

  
  /* Validate socket device handle entries */
  error = _handle_check(socket_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }


  /* Make sure socket is connected to remote node */
  if (!socket_dev_handle->connected)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_NOT_INITIALIZED);
    goto exit;
  }


  /* Obtain cache interface */
  error = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE,
                                      CONFIG_CONTEXT_CACHE_INTERFACE,
                                      (void **)&cache_if);

  if (error != BL_ERR_NONE)
  {
    goto exit;
  }

  if (cache_if == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }


  /* Flush receive buffer before reading */
  cache_if->InvalidateDataCacheRange(ram_addr,
                                     bytes_to_write);


  /* Receive data */
  if (net_api_send(socket_dev_handle->socket_handle,
                   ram_addr,
                   bytes_to_write,
                   0) != bytes_to_write)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INTERFACE_FAILURE);
    goto exit;
  }


 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_socket_dev_close
** ==========================================================================
*/
/*!
* 
* @brief
*   Disconnect from remote node and close socket
* 
* @param[in] socket dev handle
* 
*/
static bl_error_boot_type boot_socket_dev_close(const boot_handle media_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;
  socket_device_handle * socket_dev_handle = NULL;

  
  /* Verify arguments passed */
  if (media_handle == NULL)
  {
    error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Assign validated socket device handle pointer */
  socket_dev_handle = (socket_device_handle *)media_handle;


  /* Validate socket device handle entries */
  error = _handle_check(socket_dev_handle);
  if(error != BL_ERR_NONE)
  {
    goto exit;
  }


  /* If connected to remote node shutdown socket */
  if (socket_dev_handle->connected)
  {
    if (net_api_shutdown(socket_dev_handle->socket_handle,
                         SHUT_RDWR) != 0)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_NOT_INITIALIZED);
      goto exit;
    }
  }


  /* If valid handle exists then close the handle */
  if (socket_dev_handle->socket_handle >= 0)
  {
    if (net_api_socketclose(socket_dev_handle->socket_handle) != 0)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }
  }

 
  /* Free handle memory.  mem_if was validated earlier in _handle_check */  
  error = socket_dev_handle->mem_if->free(socket_dev_handle);
  if (error != BL_ERR_NONE)
  {
    goto exit;
  }


  /* Clear the socket device handle */
  memset((void *)socket_dev_handle,
          0,
          sizeof(socket_device_handle));
  
 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_socket_dev_hw_init
** ==========================================================================
*/
/*!
* 
* @brief
*   Function to initialize the socket layer
* 
* @param[in] config context handle
*
* 
*/
static bl_error_boot_type boot_socket_dev_hw_init(const boot_handle config_context_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;


  if(!boot_socket_dev_is_hw_initialized)
  {
    /* Validate pointers */
    if (config_context_handle == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INVALID_PARAMETER);
      goto exit;
    }


    /* Initialize net socket library */
    if (net_api_lib_init() != 0)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }


    boot_socket_dev_is_hw_initialized = TRUE;
  }


 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_socket_dev_hw_deinit
** ==========================================================================
*/
/*!
* 
* @brief
*   Function to de-initialize the socket layer
* 
* @param[in] config context handle
*
* 
*/
static bl_error_boot_type boot_socket_dev_hw_deinit(const boot_handle config_context_handle)
{
  bl_error_boot_type error = BL_ERR_NONE;


  if(boot_socket_dev_is_hw_initialized)
  {
    /* Validate pointers */
    if (config_context_handle == NULL)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INVALID_PARAMETER);
      goto exit;
    }


    /* Initialize net socket library */
    if (net_api_lib_deinit != 0)
    {
      error = GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }


    boot_socket_dev_is_hw_initialized = FALSE;
  }

 exit:
  return error;
}


/*=========================================================================
**  Function :  boot_socket_dev_async_read
** ==========================================================================
*/
/*!
* 
* @brief
*   Async receive from socket
* 
* @param[in] socket dev handle, pointer to destination, source offset,
* number of bytes to read
* 
*/
static bl_error_boot_type boot_socket_dev_async_read(const boot_handle media_handle,
                                                     void * ram_addr,
                                                     uint64 src_offset,
                                                     uint32 bytes_to_read)
{
  return BL_ERR_FEATURE_NOT_SUPPORTED;
}


/*=========================================================================
**  Function :  boot_socket_dev_async_poll
** ==========================================================================
*/
/*!
* 
* @brief
*   Async read complete polling check
* 
* @param[in] socket dev handle, pointer to unknown
* 
*/
static bl_error_boot_type boot_socket_dev_async_poll(const boot_handle media_handle,
                                                     uint8 * unused)
{
  return BL_ERR_FEATURE_NOT_SUPPORTED;
}


/*=========================================================================
**  Function :  boot_socket_dev_ioctl
** ==========================================================================
*/
/*!
*
* @brief
*   control socket_dev params using ioctl
*
* @param[in] command, in ptr, in size, out ptr, out size ptr
*
*/
static bl_error_boot_type boot_socket_dev_ioctl(uint32 cmd,
                                                void * in,
                                                uintnt in_sz,
                                                void * out,
                                                uintnt * out_sz)
{
  return BL_ERR_NONE;
}


/*=========================================================================
**  Function :  boot_socket_dev_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   hook up the socket dev apis to media interface
* 
* @param[in] pointer to boot_media_interface_if_type
* 
*/
bl_error_boot_type boot_socket_dev_get_interface(void * media_interface_if)
{
  bl_error_boot_type error = BL_ERR_NONE;
  

  /* Verify arguments */
  if(media_interface_if == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_SOCKETDEV, BL_ERR_INVALID_PARAMETER);
  }
  

  /* Assign apis */
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_init = boot_socket_dev_hw_init;
  ((boot_media_interface_if_type *)media_interface_if)->media_hw_deinit = boot_socket_dev_hw_deinit;
  ((boot_media_interface_if_type *)media_interface_if)->open = boot_socket_dev_open;
  ((boot_media_interface_if_type *)media_interface_if)->close = boot_socket_dev_close;
  ((boot_media_interface_if_type *)media_interface_if)->read = boot_socket_dev_read;
  ((boot_media_interface_if_type *)media_interface_if)->write = boot_socket_dev_write;
  ((boot_media_interface_if_type *)media_interface_if)->async_read = boot_socket_dev_async_read;
  ((boot_media_interface_if_type *)media_interface_if)->async_read_poll = boot_socket_dev_async_poll;
  ((boot_media_interface_if_type *)media_interface_if)->ioctl = boot_socket_dev_ioctl;


  return error;
}
