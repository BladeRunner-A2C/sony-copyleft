/* ====================================================================
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * ====================================================================
 */

#include <string.h>
#include <net_api_socket.h>


int net_api_lib_init(void)
{
  return 0;
}


int net_api_lib_deinit(void)
{
  return 0;
}


int net_api_socket(int32_t family, int32_t type, int32_t protocol)
{
  /* Return a fake handle */
  return 1;
}

 
net_api_Status_t net_api_bind(int32_t handle, struct sockaddr *addr, int32_t addrlen)
{
  return 0;
}


net_api_Status_t net_api_listen(int32_t handle, int32_t backlog)
{
  return 0;
}


int net_api_accept(int32_t handle, struct sockaddr *cliaddr, int32_t *addrlen)
{
  /* Return fake handle */
  return 1;
}


net_api_Status_t net_api_connect(int32_t handle, struct sockaddr *srvaddr, int32_t addrlen)
{
  return 0;
}


net_api_Status_t net_api_setsockopt(int32_t handle, int32_t level, int32_t optname, void *optval, int32_t optlen)
{
  return 0;
}

 
net_api_Status_t net_api_getsockopt(int32_t handle, int32_t level, int32_t optname, void *optval, int32_t optlen)
{
  return 0;
}


net_api_Status_t net_api_socketclose(int32_t handle)
{
  return 0;
}


int net_api_errno(int32_t handle)
{
  return 0;
}


int net_api_recvfrom(int32_t handle, char *buf, int32_t len, int32_t flags, struct sockaddr *from, int32_t *fromlen)
{
  /* Fill the buffer with non zero data for length given to simulate receiving something. */

  /* Validate buffer pointer */
  if (buf == NULL)
  {
    return -1;
  }

  memset(buf,
         0xA5,
         len);

  return (int)len;
}


int net_api_recv(int32_t handle, char *buf, int32_t len, int32_t flags)
{
  /* Fill the buffer with non zero data for length given to simulate receiving something. */

  /* Validate buffer pointer */
  if (buf == NULL)
  {
    return -1;
  }

  memset(buf,
         0xA5,
         len);

  return (int)len;
}


int net_api_sendto(int32_t handle, char *buf, int32_t len, int32_t flags, struct sockaddr *to, int32_t tolen)
{
  /* Return length to simulate sending data */
  return (int)len;
}


int net_api_send(int32_t handle, char *buf, int32_t len, int32_t flags)
{
  /* Return length to simulate sending data */
  return (int)len;
}


int net_api_select(fd_set *rd, fd_set *wr, fd_set *ex, int32_t timeout_ms)
{
  return 0;
}


int net_api_select_v2(fd_set_v2 *rd, fd_set_v2 *wr, fd_set_v2 *ex, int32_t timeout_ms)
{
  return 0;
}


net_api_Status_t net_api_fd_zero(fd_set *set)
{
  return 0;
}


net_api_Status_t net_api_fd_zero_v2(fd_set_v2 *set)
{
  return 0;
}


net_api_Status_t net_api_fd_clr(int32_t handle, fd_set *set)
{
  return 0;
}


net_api_Status_t net_api_fd_clr_v2(int32_t handle, fd_set_v2 *set)
{
  return 0;
}


net_api_Status_t net_api_fd_set(int32_t handle, fd_set *set)
{
  return 0;
}


net_api_Status_t net_api_fd_set_v2(int32_t handle, fd_set_v2 *set)
{
  return 0;
}


net_api_Status_t net_api_fd_isset(int32_t handle, fd_set *set)
{
  return 0;
}


net_api_Status_t net_api_fd_isset_v2(int32_t handle, fd_set_v2 *set)
{
  return 0;
}


net_api_Status_t net_api_getpeername(int32_t handle, struct sockaddr *addr, int *addrlen)
{
  return 0;
}


net_api_Status_t net_api_getsockname(int32_t handle, struct sockaddr *addr, int *addrlen)
{
  return 0;
}


int net_api_shutdown(int32_t handle , int how)
{
  return 0;
}