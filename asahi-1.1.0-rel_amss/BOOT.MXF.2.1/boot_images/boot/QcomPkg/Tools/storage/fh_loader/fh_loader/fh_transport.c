/**************************************************************************
 * FILE: fh_transport.c
 *
 * Transport abstraction layer for for the different transport mediums:
 * USB, PCIe, HSUART.
 *
 * Copyright (c) 2019 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Qualcomm Proprietary
 *
 *************************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Tools/storage/fh_loader/fh_loader/fh_transport.c#1 $
  $DateTime: 2024/04/02 23:00:31 $
  $Author: cirrusp4svc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2019-05-16   wek   Create.

===========================================================================*/

#include "fh_comdef.h"
#include "fh_log.h"
#include "fh_transport.h"


static enum fh_transport_type session_transport_type = FH_TRANSPORT_NONE;
static struct fh_transport *transport;

/* Initializes the specific transport layer. This function should not
 * interact or open the port. */
fh_res_t fh_transport_init(enum fh_transport_type transport_type)
{
  if (session_transport_type != FH_TRANSPORT_NONE)
  {
    FH_LOGE("Tried to change transport layer at runtime %llu", (unsigned long long) transport_type);
    return INVALID_PARAMETER;
  }

  switch (transport_type)
  {
  case FH_TRANSPORT_NONE:
    return INVALID_PARAMETER;
    break;
  case FH_TRANSPORT_COM:
    transport = fh_transport_com_init();
    break;
  case FH_TRANSPORT_HSUART:
    transport = fh_transport_hsuart_init();
    break;
  case FH_TRANSPORT_VIP:
    return INVALID_PARAMETER;
    break;
  case FH_TRANSPORT_LINUX_PIPE_TEST:
    transport = fh_transport_linux_pipe_init();
    break;
  case FH_TRANSPORT_MAX:
  default:
    return INVALID_PARAMETER;
  }

  session_transport_type = transport_type;

  return SUCCESS;
}

enum fh_transport_type fh_transport_get_type(void)
{
  return session_transport_type;
}

fh_res_t fh_transport_deinit(void)
{
  if (session_transport_type == FH_TRANSPORT_NONE)
    return NOT_INITALIZED;

  return SUCCESS;
}

fh_res_t fh_transport_open(const char *path)
{
  if (session_transport_type == FH_TRANSPORT_NONE)
    return NOT_INITALIZED;

  return transport->ops->open(path);
}

fh_res_t fh_transport_rx_blocking(void *data, size_t size, size_t *bytes_rx)
{
  if (session_transport_type == FH_TRANSPORT_NONE)
    return NOT_INITALIZED;

  return transport->ops->rx_blocking(data, size, bytes_rx);
}

fh_res_t fh_transport_tx_blocking(void *data, size_t size)
{
  if (session_transport_type == FH_TRANSPORT_NONE)
    return NOT_INITALIZED;

  return transport->ops->tx_blocking(data, size);
}

fh_res_t fh_transport_close(void)
{
  if (session_transport_type == FH_TRANSPORT_NONE)
    return NOT_INITALIZED;

  return transport->ops->close();
}
