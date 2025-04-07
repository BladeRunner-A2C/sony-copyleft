/**
  @file pcie_osal_uefi.c
  @brief Internal interface include file for the PCIe target specific
  configuration layer.

  This file contains definitions of constants, data structures, and
  interfaces that provide target specific configuration data.

*/
/*
===============================================================================

                             Edit History


   when       who     what, where, why
   --------   ---     ------------------------------------------------------------
   11/15/19   Yg      Ported to ADSP
   10/18/18   MK      Created

===============================================================================
                   Copyright (c) 2018 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                   Confidential and Proprietary - Qualcomm Technologies, Inc
===============================================================================
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "pcie_osal.h"
#include "pcie_host_log.h"
#include "pcie_cfg_types.h"
#include "pcie_host.h"
#include "PlatformInfo.h"
#include "DALDeviceId.h"
#include "DDIChipInfo.h"
#include "DDITlmm.h"
#include <api/boot/boot_logger.h>
#include <api/pmic/pm/pm_lib.h>
#include <api/systemdrivers/ClockBoot.h>
#include <api/systemdrivers/busywait.h>
#include <Library/ArmLib.h>
#include <Library/Clock.h>
#include "msmhwiobase.h"
#include "HALhwio.h"

#define GCC_CLK_CTL_REG_REG_BASE                                                                             (CLK_CTL_BASE      + 0x00010000)
#define GCC_CLK_CTL_REG_REG_BASE_SIZE                                                                        0x1e0000
#define GCC_CLK_CTL_REG_REG_BASE_USED                                                                        0xa5024

#define HWIO_GCC_PCIE_6A_PHY_BCR_ADDR                                                                        (GCC_CLK_CTL_REG_REG_BASE      + 0x9c01c)
#define HWIO_GCC_PCIE_6A_PHY_BCR_RMSK                                                                               0x1
#define HWIO_GCC_PCIE_6A_PHY_BCR_IN                    \
                in_dword(HWIO_GCC_PCIE_6A_PHY_BCR_ADDR)
#define HWIO_GCC_PCIE_6A_PHY_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_PCIE_6A_PHY_BCR_ADDR, m)
#define HWIO_GCC_PCIE_6A_PHY_BCR_OUT(v)            \
                out_dword(HWIO_GCC_PCIE_6A_PHY_BCR_ADDR,v)
#define HWIO_GCC_PCIE_6A_PHY_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_PCIE_6A_PHY_BCR_ADDR,m,v,HWIO_GCC_PCIE_6A_PHY_BCR_IN)
#define HWIO_GCC_PCIE_6A_PHY_BCR_BLK_ARES_BMSK                                                                      0x1
#define HWIO_GCC_PCIE_6A_PHY_BCR_BLK_ARES_SHFT                                                                        0

#define HWIO_GCC_PCIE_6A_BCR_ADDR                                                                            (GCC_CLK_CTL_REG_REG_BASE      + 0x21000)
#define HWIO_GCC_PCIE_6A_BCR_RMSK                                                                                   0x1
#define HWIO_GCC_PCIE_6A_BCR_IN                    \
                in_dword(HWIO_GCC_PCIE_6A_BCR_ADDR)
#define HWIO_GCC_PCIE_6A_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_PCIE_6A_BCR_ADDR, m)
#define HWIO_GCC_PCIE_6A_BCR_OUT(v)            \
                out_dword(HWIO_GCC_PCIE_6A_BCR_ADDR,v)
#define HWIO_GCC_PCIE_6A_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_PCIE_6A_BCR_ADDR,m,v,HWIO_GCC_PCIE_6A_BCR_IN)
#define HWIO_GCC_PCIE_6A_BCR_BLK_ARES_BMSK                                                                          0x1
#define HWIO_GCC_PCIE_6A_BCR_BLK_ARES_SHFT                                                                            0

/** Max size of the log message */
#define PCIE_OSAL_LOG_BUFSIZE                    64


typedef struct {
   ClockHandle clock_handle; /* TODO: determine if this should be port specific */
   char pcierc_log_buffer[PCIE_OSAL_LOG_BUFSIZE]; /* Temporary buffer for the log message */
} pcie_osal_ctxt_t;

static pcie_osal_ctxt_t pcie_osal_ctxt;

void pcie_osal_init()
{
   pcie_osal_ctxt.clock_handle = 0;
}

void pcie_osal_log_msg(const char *fmt, ...)
{
    va_list arg_list;

    va_start (arg_list, fmt);

    memset (pcie_osal_ctxt.pcierc_log_buffer,0,PCIE_OSAL_LOG_BUFSIZE);
    va_start (arg_list, fmt);
    vsnprintf (pcie_osal_ctxt.pcierc_log_buffer, PCIE_OSAL_LOG_BUFSIZE, fmt, arg_list);
    va_end (arg_list);
    boot_log_message (pcie_osal_ctxt.pcierc_log_buffer);
}

void* pcie_osal_malloc (size_t size)
{
   return NULL;
}

void pcie_osal_free (void *ptr)
{
}

void* pcie_osal_malloc_aligned (size_t size, uint8 align)
{
   return NULL;
}

void pcie_osal_free_aligned (void *ptr)
{
//   FreePages (ptr, number of pages);
}

pcie_status_t pcie_ldo_op (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_pwr_rails_config_t *pwr_config, int enable)
{
    int i;

      for (i=0; i < pwr_config->num_ldos; i++)
      {
         if (enable == TRUE)
         {
            if (pm_ldo_sw_enable(pwr_config->ldo_cfg[i].pmic_chip, pwr_config->ldo_cfg[i].ldo_num, PM_ON, TRUE) != PM_ERR_FLAG_SUCCESS)
            {
               PCIE_HOST_LOG_ERROR("ON fail : L%d%c", pwr_config->ldo_cfg[i].ldo_num + 1, 'A' + pwr_config->ldo_cfg[i].pmic_chip);
               return PCIE_ERROR;
            }
         }
         // off is not really required
      }

    return PCIE_SUCCESS;
}

/*******************************************************************************
 * GPIO related
********************************************************************************/
static DalDeviceHandle           *TLMMHandle = NULL;

pcie_status_t pcie_osal_gpio_set (uint32 pin, boolean level)
{
   DALGpioSignalType   dal_gpio_config     = 0;
   DALResult eStatus;

   dal_gpio_config = (DALGpioSignalType)DAL_GPIO_CFG(pin, 0, 0, 0, 0);  // WARNING: Verify if this doesn't mess up

   eStatus = DalTlmm_GpioOut(TLMMHandle, dal_gpio_config, level);
   if (eStatus != DAL_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Set GPIO failed\n");
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_osal_init_gpio(const pcie_gpio_cfg_t *gpio_cfg)
{
    DALGpioSignalType   dal_gpio_config     = 0;
    const tlmm_gpio_cfg_t *tlmm_cfg;
    DALResult eStatus;

    if (gpio_cfg == NULL)
        return PCIE_SUCCESS;

    if (TLMMHandle == NULL)
	{
	    eStatus = DAL_DeviceAttach(DALDEVICEID_TLMM, &TLMMHandle);
        if(eStatus != DAL_SUCCESS)
            return(PCIE_ERROR);
    }

    switch (gpio_cfg->cfg_type)
    {
       case MSM_GPIO:
           tlmm_cfg = &gpio_cfg->pcie_pin.tlmm;
           dal_gpio_config = (DALGpioSignalType)DAL_GPIO_CFG(tlmm_cfg->gpio_num, tlmm_cfg->func_sel, tlmm_cfg->direction, tlmm_cfg->pull, tlmm_cfg->drive_strength);

           eStatus = DalTlmm_ConfigGpio(TLMMHandle, dal_gpio_config, DAL_TLMM_GPIO_ENABLE);
           if (eStatus != DAL_SUCCESS)
               return PCIE_ERROR;

           if (tlmm_cfg->value != 0)
               eStatus = DalTlmm_GpioOut(TLMMHandle,dal_gpio_config, tlmm_cfg->value);
           break;

       case DELAY:
           busywait(gpio_cfg->pcie_pin.delay_us);
           break;

       default:
          break;
    }

    return PCIE_SUCCESS;
}

pcie_status_t pcie_initialize_gpios (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_gpio_cfg_t *gpio_cfg)
{
   EFI_STATUS Status = EFI_DEVICE_ERROR;
   int i;

   if ((gpio_cfg == NULL) || (rsrc_ctxt == NULL))
      return PCIE_ERROR;

   if (rsrc_ctxt->gpio_initialized == TRUE)
      return PCIE_SUCCESS;

   for (i = 0; gpio_cfg[i].cfg_type != NONE; ++i)
   {
      Status = pcie_osal_init_gpio (&gpio_cfg[i]);

      if (Status != EFI_SUCCESS)
         break;
   }

   if (Status == EFI_SUCCESS)
      rsrc_ctxt->gpio_initialized = TRUE;

   return PCIE_SUCCESS;
}

ClockHandle get_clock_handle()
{
   ClockResult res;

   if (pcie_osal_ctxt.clock_handle == 0)
   {
      res = Clock_Attach (&pcie_osal_ctxt.clock_handle, "PCIeRC");
      if (res != CLOCK_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to get Clk API handle\n");
         return 0;
      }
   }

   return pcie_osal_ctxt.clock_handle;
}

pcie_status_t pcie_clock_op (const char *clk_name, int enable)
{
   ClockResult   res;
   ClockIdType   clk_id;
   ClockHandle   clk_handle;

   if (clk_name == NULL)
      return PCIE_ERROR;

   clk_handle = get_clock_handle ();
   if (clk_handle == 0)
      return PCIE_ERROR;

   res = Clock_GetId (clk_handle, clk_name, &clk_id);
   if (res != CLOCK_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Clk get ID failed %a\n", clk_name);
      return PCIE_ERROR;
   }

   if (enable)
      res = Clock_Enable (clk_handle, clk_id);
   else
      res = Clock_Disable (clk_handle, clk_id);

   if (res != CLOCK_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Clk En/Dis failed %a\n", clk_name);
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_clks_set_freq (const clk_freq_cfg_t  *clk_freq)
{
   ClockResult   res;
   ClockIdType   clk_id;
   ClockHandle   clk_handle;

   clk_handle = get_clock_handle ();
   if (clk_handle == 0)
      return PCIE_ERROR;

   while (clk_freq->name != NULL)
   {
      uint32 freq_out = 0;

      res = Clock_GetId (clk_handle, clk_freq->name, &clk_id);
      if (res != CLOCK_SUCCESS)
         return PCIE_ERROR;

      res = Clock_SetFrequency (clk_handle, clk_id, clk_freq->freq, CLOCK_FREQUENCY_KHZ_AT_LEAST, &freq_out);
      if (res != CLOCK_SUCCESS)
         PCIE_HOST_LOG_ERROR ("Set frequency failed for %a\n", clk_freq->name);

      clk_freq++;
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_clock_mux_op (const pcie_clk_mux_cfg_t  *clk_mux_cfg, int enable)
{
   ClockResult res;
   ClockIdType   clk_id;
   ClockHandle    clk_handle;
   UINT32 mux_val;

   if ((clk_mux_cfg == NULL) || (clk_mux_cfg->clk_name == NULL))
      return PCIE_ERROR;

   clk_handle = get_clock_handle ();
   if (clk_handle == 0)
      return PCIE_ERROR;

   res = Clock_GetId (clk_handle, clk_mux_cfg->clk_name, &clk_id);
   if (res != CLOCK_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Get mux ID failed for %a\n", clk_mux_cfg->clk_name);
      return PCIE_ERROR;
   }

   if (enable)
      mux_val = clk_mux_cfg->en_mux_val;
   else
      mux_val = clk_mux_cfg->dis_mux_val;

   res = Clock_SelectExternalSource (clk_handle, clk_id, 0, mux_val, 0, 0, 0, 0);
   if (res != CLOCK_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Set mux failed for %a\n", clk_mux_cfg->clk_name);
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_disable_clocks (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_clocks_cfg_t *clock_config, boolean disable_phy_pwr)
{
   const char **clks;

   if ((clock_config == NULL) || (clock_config->core_clks == NULL) ||
       (clock_config->clk_reset == NULL) || (clock_config->clk_pwr == NULL) ||
       (clock_config->phy_pwr == NULL) || (clock_config->clk_freq == NULL))
      return PCIE_INVALID_PARAM;


   if (clock_config->clk_mux)  // Mux is optional in some targets
   {
      if (pcie_clock_mux_op (clock_config->clk_mux, DISABLE) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to switch mux en\n");
         return PCIE_ERROR;
      }
   }

   clks = clock_config->core_clks;
   while (*clks != NULL)
   {
      if (pcie_clock_op (*clks, DISABLE) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to turn OFF clk %a\n", *clks);
         return PCIE_ERROR;
      }
      ++clks;
   }

   /* GDSC Domain power off */
   if (pcie_clock_op (clock_config->clk_pwr, DISABLE) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to turn OFF GDSC\n");
      return PCIE_ERROR;
   }

   /* Some platforms, such as RUMI, do not enable phy power*/
   if (disable_phy_pwr)
   {
      if (pcie_clock_op (clock_config->phy_pwr, DISABLE) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to turn OFF GDSC\n");
         return PCIE_ERROR;
      }
   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_enable_clocks (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_clocks_cfg_t *clock_config, boolean enable_phy_pwr)
{
   const char **clks;

   if ((clock_config == NULL) || (clock_config->core_clks == NULL) ||
       (clock_config->clk_reset == NULL) || (clock_config->clk_pwr == NULL) ||
       (clock_config->phy_pwr == NULL) || (clock_config->clk_freq == NULL))
      return PCIE_INVALID_PARAM;

   /* GDSC Domain power up */
   if (pcie_clock_op (clock_config->clk_pwr, ENABLE) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to turn ON GDSC\n");
      return PCIE_ERROR;
   }

   /* Some platforms, such as RUMI, do not enable phy power*/
   if (enable_phy_pwr)
   {
      if (pcie_clock_op (clock_config->phy_pwr, ENABLE) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to turn ON PHY GDSC\n");
         return PCIE_ERROR;
      }
   }

   /*
    * The mux must be switched to source PIPE clock from the PHY before
    * the controller is reset. This ensures the PIPE clock will not be running
    * while the controller is reset. After the reset, software must program
    * the device type to RC before the PIPE clock is running. Otherwise,
    * default register values may be incorrect.
    */
   if (clock_config->clk_mux)
   {
      if (pcie_clock_mux_op (clock_config->clk_mux, ENABLE) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to switch mux en\n");
         return PCIE_ERROR;
      }
   }

   /* Temporarily poking the BCR register until the clock team provides an interface */
   HWIO_OUT(GCC_PCIE_6A_BCR, 1);
   busywait(100);
   HWIO_OUT(GCC_PCIE_6A_BCR, 0);

   HWIO_OUT(GCC_PCIE_6A_PHY_BCR, 1);
   busywait(100);
   HWIO_OUT(GCC_PCIE_6A_PHY_BCR, 0);

   clks = clock_config->core_clks;
   while (*clks != NULL)
   {
      if (pcie_clock_op (*clks, ENABLE) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to turn ON clk %a\n", *clks);
         return PCIE_ERROR;
      }
      ++clks;
   }

   if (pcie_clks_set_freq (clock_config->clk_freq) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Set freq failed\n");
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

pcie_status_t enable_pcie_resources (pcie_resources_ctxt_t *resources_ctxt,
                                     const pcie_port_config_t  *port_cfg)
{
   pcie_status_t res;
   DalPlatformInfoPlatformType platformType;

   if ((port_cfg == NULL) || (resources_ctxt == NULL))
      return PCIE_ERROR;

   if (port_cfg->driver_config == NULL)
      return PCIE_SUCCESS;

   platformType = PlatformInfo_Platform();

   if  (port_cfg->driver_config->pwr_rails_cfg != NULL)
   {
      if (pcie_ldo_op (resources_ctxt, port_cfg->driver_config->pwr_rails_cfg, ENABLE) != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Unable to turn ON ldos\n");
         if (platformType != DALPLATFORMINFO_TYPE_RUMI)
         {
            return PCIE_ERROR;
         }
      }
   }

   if (platformType == DALPLATFORMINFO_TYPE_RUMI)
   {
      //Do not enable phy pwr on the RUMI platform
      res = pcie_enable_clocks (resources_ctxt, port_cfg->driver_config->port_clk_cfg, false);
   }
   else
   {
      res = pcie_enable_clocks (resources_ctxt, port_cfg->driver_config->port_clk_cfg, true);
   }

   if (res != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Clock init failed\n");
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}

pcie_status_t disable_pcie_resources (pcie_resources_ctxt_t *resources_ctxt,
                                     const pcie_port_config_t  *port_cfg)
{
   pcie_status_t res;
   DalPlatformInfoPlatformType platformType;

   if ((port_cfg == NULL) || (resources_ctxt == NULL))
      return PCIE_ERROR;

   if (port_cfg->driver_config == NULL)
      return PCIE_SUCCESS;

   platformType = PlatformInfo_Platform();

   if (platformType == DALPLATFORMINFO_TYPE_RUMI)
   {
      //Do not disable phy pwr on the RUMI platform, it was never enabled
      res = pcie_disable_clocks (resources_ctxt, port_cfg->driver_config->port_clk_cfg, false);
   }
   else
   {
      res = pcie_disable_clocks (resources_ctxt, port_cfg->driver_config->port_clk_cfg, true);
   }

   if (res != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Clock deinit failed\n");
      return PCIE_ERROR;
   }

   if (pcie_ldo_op (resources_ctxt, port_cfg->driver_config->pwr_rails_cfg, DISABLE) != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to turn OFF ldos\n");
      return PCIE_ERROR;
   }

   return PCIE_SUCCESS;
}


