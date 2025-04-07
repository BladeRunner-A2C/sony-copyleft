/*===========================================================================

            GLink SMEM transport Configuration Structures

=============================================================================

  @file
    xport_smem_config.c

    Contains structures to be used in Glink SMEM trasnport configuration.

  Copyright (c) 2014 - 2015,2017-2022 Qualcomm Technologies, Inc.
  All rights reserved.
  Qualcomm Confidential and Proprietary
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/GLinkLib/xport_smem/src/xport_smem_config.c#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
10/15/18   mad     Removed MPSS edge 
05/11/15   an      QoS support
02/13/15   bc      Decrease the fifo size due to lack of space
01/14/15   bc      Update outgoing interrupt
01/13/15   bc      Update more processors
06/17/14   an      Initial version
===========================================================================*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include "xport_smem_config.h"
#include "xport_smem_qos_generic.h"
#include <Protocol/EFIIPCC.h>
#include <Library/DTBExtnUEFILib.h>
#include "smem_type.h"
#include "xport_smem.h"
#include "smem.h"
#include "spss_hwio.h"
#include "smem_v.h"

#define XPORT_SMEM_SPSS_MAILBOX_NUM 0
extern int32 xport_smem_smem_alloc_ex(smem_alloc_params_type *params);
extern int32 xport_smem_hwio_map_region(const char* module, void** addr);
static void xport_smem_notify_spss_ctrl_info (  uint64 ctrl_info_addr, uint32 ctrl_info_size );
static void xport_smem_clear_spss_interrupt(void);
static boolean xport_smem_alloc_spss_fifo( void *ctx_info );

static uint8 *xport_smem_sp_scsr_base_ptr = NULL;
/*===========================================================================
                    CONSTANT / MACRO DECLARATIONS
===========================================================================*/
#define XPORT_SMEM_DT_RET_CHECK(ret)                                   \
  {                                                               \
    if (ret) {                                                    \
      DEBUG((EFI_D_ERROR, "xport-smem DT parse return = %d\n", ret));                 \
      return ret;                                                 \
    }                                                             \
  }
  
#define XPORT_SMEM_DT_SUCCESS 0

/*===========================================================================
                    Type declarations
===========================================================================*/
/* Structure of xport-smem-config items in Device-Tree database */
typedef struct _xport_smem_dt_config_type
{
  smem_host_type remote_host;           /* Remote host ID          */
  uint32 fifo_size;                     /* Tx FIFO size            */
  uint32 mtu_size;                      /* Tx MTU size             */
  os_ipc_intr_type irq_out;             /* Outgoing interrupt      */
  uint32 default_qos;                   /* Whether this uses the default QoS interface (always true) */
  uint32 custom_fifo_alloc;             /* whether custom fifo allocation routine is used */
  uint32 clear_interrupt;               /* Whether this edge uses an explicit interrupt clear routine */
} xport_smem_dt_config_type;  

/*===========================================================================
                    Function declarations
===========================================================================*/
static const char* glink_host_name_from_smem_id(smem_host_type id);

/*===========================================================================
                        DATA DECLARATIONS
===========================================================================*/
static glink_transport_qos_if_type xport_smem_qos_config = 
{
  /** Provides maximum data rate (tokens/sec) associated with transport. */
  20000,
  /** Provides data rate achievable by the transport for given request. */
  xport_smem_get_req_rate_generic,
  /** Allocates context structure to use by transport servicing given QoS request. */
  xport_smem_alloc_req_ctx_generic,
  /** Frees context structure used by transport servicing given QoS request. */
  xport_smem_free_req_ctx_generic,
  /** Starts QoS mode. */
  xport_smem_start_req_generic,
  /** Stops QoS mode. */
  xport_smem_stop_req_generic,
  /** Provides ramp up time in microseconds. */
  xport_smem_get_ramp_time_generic
};

xport_smem_config_type *xport_smem_config = NULL;
uint32 xport_smem_config_num = 0;
const smem_host_type xport_smem_this_host = SMEM_APPS;


xport_smem_config_type* xport_smem_get_config(uint32 ind)
{
  if (ind >= xport_smem_config_num)
  {
    return NULL;
  }

  return &xport_smem_config[ind];
}


/*===========================================================================
FUNCTION      xport_smem_notify_spss_ctrl_info
===========================================================================*/
/**
  Notify spss allocated control info via sp_scsr register.
  This function will also map sp_scsr register to virtual address

  @param[in]  ctrl_info_addr address of allocated control info
  @param[in]  ctrl_info_size size of allocated control info

  @return     None

  @sideeffects  None.
*/
/*=========================================================================*/
void xport_smem_notify_spss_ctrl_info
(
  uint64 ctrl_info_addr,
  uint32 ctrl_info_size
)
{
	uint32 res;
	res = xport_smem_hwio_map_region("+SP_CNOC_SP_SCSR_REGS", (void**)&xport_smem_sp_scsr_base_ptr);
	if ( res != 0 || xport_smem_sp_scsr_base_ptr == NULL )
   {
      ERR_FATAL("xport_smem_notify_spss_ctrl_info:"
                " Failed to map sp_scsr region[result: %d][pBasePtr: 0x%x].",
                result, xport_smem_sp_scsr_base_ptr, 0);
    }
  /* Secure this mailbox to make sure only owner can access this resource */
  /* Don't see this being done for APPS */ 
  //outpdw( sp_scsr_base_ptr + 0x00009004, 1);
  //HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_OUTI(XPORT_SMEM_SPSS_MAILBOX_NUM,1);
 
  /* Populate sp scsr smem registers */
  /* Write to SP_SCSR_MBn_SMEM_ADDR_L */
   HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_OUTI(xport_smem_sp_scsr_base_ptr , XPORT_SMEM_SPSS_MAILBOX_NUM , ctrl_info_addr);

  /* Write to SP_SCSR_MBn_SMEM_ADDR_U,
   upper address register can only contain 16 bit
   But 32 bit is enough to represent smem ctrl info address so we just set 0 */
   HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_OUTI(xport_smem_sp_scsr_base_ptr , XPORT_SMEM_SPSS_MAILBOX_NUM , 0);

  /* Write to SP_SCSR_MBn_SMEM_SIZE */
   HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_OUTI(xport_smem_sp_scsr_base_ptr , XPORT_SMEM_SPSS_MAILBOX_NUM , ctrl_info_size);
}

/*===========================================================================
FUNCTION      xport_smem_clear_spss_interrupt
===========================================================================*/
/**
  Clear spss interrupt source. This is only for spss since interrupt from spss
  is level triggered

  @param[in]  ctx_ptr   Pointer to secure processor edge context

  @return       None.

  @sideeffects  None.
*/
/*=========================================================================*/
void xport_smem_clear_spss_interrupt(void)
{
   /*if(xport_smem_sp_scsr_base_ptr)
	  out_dword(xport_smem_sp_scsr_base_ptr + HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_CLR_OFFS(XPORT_SMEM_SPSS_MAILBOX_NUM) , 1);*/
}


/*===========================================================================
FUNCTION      xport_smem_alloc_spss_fifo
===========================================================================*/
/**
  allocate secure processor fifo/shared indices as this edge requires special
  initialization handshake. Client procesor (APPS-BOOT) is supposed to allocate
  everything and inform spss

  @param[in]  ctx_ptr   Pointer to secure processor edge context

  @return     TRUE if allocation was successful.
              FALSE otherwise

  @sideeffects  None.
*/
/*=========================================================================*/
boolean xport_smem_alloc_spss_fifo
(
  void *ctx_info
)
{
  xport_smem_ctx_type    *ctx_ptr = (xport_smem_ctx_type *)ctx_info;
  smem_alloc_params_type smem_params;
  
  /* Allocate SMEM channel descriptor item */
  smem_params.remote_host = ctx_ptr->pcfg->remote_host;
  smem_params.smem_type   = SMEM_GLINK_NATIVE_XPORT_DESCRIPTOR;
  smem_params.size        = ctx_ptr->pcfg->fifo_size * 2 +     /* allocate two fifo    */
                            sizeof(xport_smem_ind_type) * 2 +  /* allocate two indices */
                            sizeof(uint32) * 2;                /* two var of fifo size */
  smem_params.buffer      = NULL;
  smem_params.flags       = SMEM_ALLOC_FLAG_PARTITION_ONLY;

  if ( xport_smem_smem_alloc_ex( &smem_params ) != SMEM_STATUS_SUCCESS )
  {
    /* SMEM allocation, set index to invalid. */
    ctx_ptr->pcfg = NULL;
    return FALSE;
  }

  ASSERT( smem_params.buffer != NULL );
  ctx_ptr->spss_ctrl_info = smem_params.buffer;

  ctx_ptr->spss_ctrl_info->fifo_0_size = ctx_ptr->pcfg->fifo_size;
  ctx_ptr->spss_ctrl_info->fifo_1_size = ctx_ptr->pcfg->fifo_size;

  if ( xport_smem_this_host < ctx_ptr->pcfg->remote_host )
  {
    ctx_ptr->tx_fifo_size = ctx_ptr->spss_ctrl_info->fifo_0_size;
    ctx_ptr->tx_desc      = &ctx_ptr->spss_ctrl_info->fifo_0_ind;

    /* fifo_0 always starts from the beginning of ctrl info fifo */
    ctx_ptr->tx_fifo      = ctx_ptr->spss_ctrl_info->fifo;

    ctx_ptr->rx_fifo_size = ctx_ptr->spss_ctrl_info->fifo_1_size;
    ctx_ptr->rx_desc      = &ctx_ptr->spss_ctrl_info->fifo_1_ind;

    /* fifo 1 always starts from end of fifo 0 */
    ctx_ptr->rx_fifo      = ctx_ptr->spss_ctrl_info->fifo +
                            ctx_ptr->spss_ctrl_info->fifo_0_size;
  }
  else
  {
    ctx_ptr->tx_fifo_size = ctx_ptr->spss_ctrl_info->fifo_1_size;
    ctx_ptr->tx_desc      = &ctx_ptr->spss_ctrl_info->fifo_1_ind;

    /* fifo 1 always starts from end of fifo 0 */
    ctx_ptr->tx_fifo      = ctx_ptr->spss_ctrl_info->fifo +
                            ctx_ptr->spss_ctrl_info->fifo_0_size;

    ctx_ptr->rx_fifo_size = ctx_ptr->spss_ctrl_info->fifo_0_size;
    ctx_ptr->rx_desc      = &ctx_ptr->spss_ctrl_info->fifo_0_ind;

    /* fifo_0 always starts from the beginning of ctrl info fifo */
    ctx_ptr->rx_fifo      = ctx_ptr->spss_ctrl_info->fifo;
  }					
  xport_smem_notify_spss_ctrl_info( (uint64)ctx_ptr->spss_ctrl_info,
                                    smem_params.size );

  return TRUE;
}

/*===========================================================================
FUNCTION      xport_smem_config_init
===========================================================================*/
/**

  Initializes SMEM transport configuration by reading from DeviceTree database.
  Must be called before any other operations are done.

  @return     Returns error code.

  @sideeffects  None.
*/
/*=========================================================================*/
int xport_smem_config_init(void)
{
  INT32 ret = XPORT_SMEM_DT_SUCCESS;
  UINT32 n_cfg = 0;
  UINT32 idx = 0;
  EFI_DTB_EXTN_PROTOCOL *dtb_protocol = NULL;
  EFI_STATUS status = EFI_DEVICE_ERROR;
  FdtNodeHandle xport_smem_dt_node_hdl;
  FdtNodeHandle *cache = NULL;
  xport_smem_dt_config_type dt_cfg;
    
  status = gBS->LocateProtocol(&gEfiDtbExtnProtocolGuid, NULL,(VOID **)&dtb_protocol);
  if (EFI_ERROR(status)) 
  {
    DEBUG((EFI_D_ERROR, "%s: Locate DTB failed with error %r \n", __FUNCTION__, status));
    return -1;
  }
  ret = dtb_protocol->FdtGetNodeHandle(&xport_smem_dt_node_hdl, "/sw/glink/xport-smem-config");
  XPORT_SMEM_DT_RET_CHECK(ret);
  ret = dtb_protocol->FdtGetCountOfSubnodes(&xport_smem_dt_node_hdl, &n_cfg);
  XPORT_SMEM_DT_RET_CHECK(ret);
  
  if(n_cfg > 0)
	cache = glink_os_calloc(n_cfg * sizeof(FdtNodeHandle));
  if(!cache)
	  return -1;
  
  ret = dtb_protocol->FdtGetCacheOfSubnodes(&xport_smem_dt_node_hdl, cache, (UINT32)n_cfg);
  XPORT_SMEM_DT_RET_CHECK(ret);
  xport_smem_config = glink_os_calloc(n_cfg * sizeof(xport_smem_config_type));
  if(!xport_smem_config)
  {
	glink_os_free(cache);
	return -1;
  }
      
  for(idx = 0; idx < n_cfg; idx++)
  {
	memset(&dt_cfg, 0, sizeof(dt_cfg));
	ret = dtb_protocol->FdtGetPropValuesOfNode(&cache[idx], "wwwwwwww", (VOID*)&(dt_cfg), sizeof(dt_cfg));
	XPORT_SMEM_DT_RET_CHECK(ret);
	
    xport_smem_config[idx].remote_ss = glink_host_name_from_smem_id(dt_cfg.remote_host);
	if(!xport_smem_config[idx].remote_ss) 
	{
	  glink_os_free(cache);
	  glink_os_free(xport_smem_config);
	  return -1;
	}
	xport_smem_config[idx].remote_host = dt_cfg.remote_host;
	xport_smem_config[idx].fifo_size = dt_cfg.fifo_size;
	xport_smem_config[idx].mtu_size = dt_cfg.mtu_size;
	xport_smem_config[idx].irq_out.client = dt_cfg.irq_out.client;
	xport_smem_config[idx].irq_out.signal = dt_cfg.irq_out.signal;	
	if(!dt_cfg.default_qos)/* We only support default QoS */
	{
	  glink_os_free(cache);
	  glink_os_free(xport_smem_config);
	  return -1;
	}
	xport_smem_config[idx].qos_api = &xport_smem_qos_config;
	
	if(!dt_cfg.custom_fifo_alloc)
	{
	  xport_smem_config[idx].alloc_fifo = NULL; /* No custom FIFO alloc is needed. So use default */
	}
	
	if(dt_cfg.custom_fifo_alloc && dt_cfg.remote_host == SMEM_SPSS )
	{
      xport_smem_config[idx].alloc_fifo = &xport_smem_alloc_spss_fifo;/* Use SPSS-specific Alloc FIFO function */
	}
	
    if(!dt_cfg.clear_interrupt)
	{
	  xport_smem_config[idx].clear_interrupt = NULL; /* No interrupt clear routine is needed */
	}
  }
  xport_smem_config_num = n_cfg;
  
  glink_os_free(cache);
  return 0;
}

/*===========================================================================
FUNCTION      glink_host_name_from_smem_id
===========================================================================*/
/**
  Return the host name string (mostly used in debug logs), given the SMEM ID.
  
  @param[in]  id   The SMEM ID that needs to be translated to string.
  
  @return     Returns string constant corresponding to remote subsystem name.

  @sideeffects  None.
*/
/*=========================================================================*/
static const char* glink_host_name_from_smem_id(smem_host_type id)
{
	switch(id)
	{
	case SMEM_APPS:
	  return "apss";
	case SMEM_MODEM:
	  return "mpss";
	case SMEM_ADSP:
	  return "lpass";
	case SMEM_SSC:
	  return "dsps";
	case SMEM_WCN:
	  return "wcnss";
	case SMEM_CDSP:
	  return "cdsp";
	case SMEM_RPM:
	  return "rpm";
	case SMEM_TZ:
	  return "tz";
	case SMEM_SPSS:
	  return "spss";
	case SMEM_NPU:
	  return "npu";
	case SMEM_WPSS:
	  return "wpss";
	default:
	  return NULL;
	}
}