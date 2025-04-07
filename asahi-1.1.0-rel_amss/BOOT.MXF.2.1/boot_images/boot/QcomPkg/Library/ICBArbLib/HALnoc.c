/**

@file   HALnoc.c

@brief  Base file for HAL NOC.
        Intended to be used to check core revision, and call the correct
        implementation - mostly empty now as there is only one core
        revision.
        
===========================================================================

                             Edit History

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/ICBArbLib/HALnoc.c#1 $

when         who     what, where, why
----------   ---     --------------------------------------------------------
2021/03/11   sds     Add Critical/NonCritical fields to regulator
2021/02/05   sds     Add QosDisable support
2018/01/19   sds     Add TargetDisable support
2015/06/13   sds     Add ExtControl support
2011/08/15   sds     Created 

===========================================================================
          Copyright (c) 2011-2021 QUALCOMM Technologies, Incorporated.
                           All Rights Reserved.
                        QUALCOMM Proprietary/GTDR
===========================================================================
*/

/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include "HALnoc.h"
#include "HALnocHwio.h"
#include "HALnocHwioGeneric.h"

/* -----------------------------------------------------------------------
** Definitions
** ----------------------------------------------------------------------- */
#ifndef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

#define LIMIT(val, field) (val)>(field##_BMSK >> field##_SHFT)?\
                                (field##_BMSK >> field##_SHFT):val

/* -----------------------------------------------------------------------
** Types
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Data
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Functions
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Mandatory Interface
** ----------------------------------------------------------------------- */
/** 
@copydoc HAL_noc_Init
*/
void HAL_noc_Init
(
  HAL_noc_InfoType *info
)
{
  /* Nothing to do. */
  (void)info;
}

/**
@copydoc HAL_noc_Reset
*/
void HAL_noc_Reset
(
  HAL_noc_InfoType *info
)
{
  /* Unimplemented */
  (void)info;
}

/**
@copydoc HAL_noc_Save
*/
void HAL_noc_Save
(
  HAL_noc_InfoType *info
)
{
  /* Unimplemented */
  (void)info;
}

/**
@copydoc HAL_noc_Restore
*/
void HAL_noc_Restore
(
  HAL_noc_InfoType *info
)
{
  /* Unimplemented */
  (void)info;
}

/* -----------------------------------------------------------------------
** Configuration Interface
** ----------------------------------------------------------------------- */
/**
@copydoc HAL_noc_SetDefaultPriority
*/
void HAL_noc_SetDefaultPriority
(
  HAL_noc_InfoType *info,
  uint32_t          master_port,
  uint32_t          priority
)
{
  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters )
  {
    NOC_OUTFI(info->base_addr, info->qos_offset, info->qos_size,
              QOS_MAINCTL_LOW, master_port, DFLTPRIORITY, priority);
  }
}

/**
@copydoc HAL_noc_SetQosDisable
*/
void HAL_noc_SetQosDisable
(
  HAL_noc_InfoType *info,
  uint32_t          master_port,
  bool              disable
)
{
  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters )
  {
    uint32_t val = disable?1:0;

    NOC_OUTFI(info->base_addr, info->qos_offset, info->qos_size,
              QOS_MAINCTL_LOW, master_port, QOSDISABLE, val);
  }
}

/**
@copydoc HAL_noc_SetLimiter
*/
void HAL_noc_SetLimiter
(
  HAL_noc_InfoType *   info,
  uint32_t             master_port,
  HAL_noc_LimiterType *config
)
{
  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters &&
      NULL != config )
  {
    uint32_t bandwidth = LIMIT(config->bandwidth,NOC_QOS_LIMITBW_LOW_BANDWIDTH);
    uint32_t saturation = LIMIT(config->saturation,NOC_QOS_LIMITBW_LOW_SATURATION);

    NOC_OUTFI(info->base_addr, info->qos_offset, info->qos_size,
              QOS_LIMITBW_LOW, master_port, BANDWIDTH, bandwidth);
    NOC_OUTFI(info->base_addr, info->qos_offset, info->qos_size,
              QOS_LIMITBW_LOW, master_port, SATURATION, saturation);
  }
}

/**
@copydoc HAL_noc_EnableLimiter
*/
void HAL_noc_EnableLimiter
(
  HAL_noc_InfoType *info,
  uint32_t          master_port,
  bool              enable
)
{
  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters )
  {
    uint32_t val = enable?1:0;

    NOC_OUTFI(info->base_addr, info->qos_offset, info->qos_size,
              QOS_MAINCTL_LOW, master_port, BWLIMITEN, val);
  }
}

/**
@copydoc HAL_noc_SetRegulator
*/
void HAL_noc_SetRegulator
(
  HAL_noc_InfoType *     info,
  uint32_t               master_port,
  uint32_t               index,
  HAL_noc_RegulatorType *config
)
{
  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters &&
      NULL != config)
  {
    uint32_t bandwidth  = LIMIT(config->bandwidth,NOC_QOS_REGULmBW_LOWn_BANDWIDTH);
    uint32_t saturation = LIMIT(config->saturation,NOC_QOS_REGULmBW_LOWn_SATURATION);

    NOC_OUTFI2(info->base_addr, info->qos_offset, info->qos_size,
               QOS_REGULmCTL_LOWn, master_port, index, HIGHPRIORITY, config->high_priority);
    NOC_OUTFI2(info->base_addr, info->qos_offset, info->qos_size,
               QOS_REGULmCTL_LOWn, master_port, index, LOWPRIORITY, config->low_priority);
    NOC_OUTFI2(info->base_addr, info->qos_offset, info->qos_size,
               QOS_REGULmBW_LOWn, master_port, index, BANDWIDTH, bandwidth);
    NOC_OUTFI2(info->base_addr, info->qos_offset, info->qos_size,
               QOS_REGULmBW_LOWn, master_port, index, SATURATION, saturation);
  }
}

/**
@copydoc HAL_noc_SetRegulatorMode
*/
void HAL_noc_SetRegulatorMode
(
  HAL_noc_InfoType *         info,
  uint32_t                   master_port,
  uint32_t                   index,
  HAL_noc_RegulatorModeType *mode
)
{
  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters &&
      NULL != mode )
  {
    uint32_t rden = mode->read?1:0;
    uint32_t wren = mode->write?1:0;
    uint32_t noncriticalen = mode->noncritical?1:0;
    uint32_t criticalen = mode->critical?1:0;

    NOC_OUTFI2(info->base_addr, info->qos_offset, info->qos_size,
               QOS_REGULmCTL_LOWn, master_port, index, RDEN, rden);
    NOC_OUTFI2(info->base_addr, info->qos_offset, info->qos_size,
               QOS_REGULmCTL_LOWn, master_port, index, WREN, wren);
    NOC_OUTFI2(info->base_addr, info->qos_offset, info->qos_size,
               QOS_REGULmCTL_LOWn, master_port, index, CRITICALEN, criticalen);
    NOC_OUTFI2(info->base_addr, info->qos_offset, info->qos_size,
               QOS_REGULmCTL_LOWn, master_port, index, NONCRITICALEN, noncriticalen);
  }
}

/**
@copydoc HAL_noc_EnableUrgencyForwarding
*/
void HAL_noc_EnableUrgencyForwarding
(
  HAL_noc_InfoType *info,
  uint32_t          master_port,
  bool              enable
)
{
  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters )
  {
    uint32_t val = enable?1:0;

    NOC_OUTFI(info->base_addr, info->qos_offset, info->qos_size,
              QOS_MAINCTL_LOW, master_port, SLVURGMSGEN, val);
  }
}

/**
@copydoc HAL_noc_DisableTarget
*/
void HAL_noc_DisableTarget
(
  HAL_noc_InfoType *info,
  uint32_t          port,
  bool              disable
)
{
  uint32_t word, bit, val;

  /* Verify input parameters. */
  if( NULL != info )
  {
    /* Get the correct status bit. */
    bit = port % 32;
    val = 1 << bit;

    /* Get the right status register. */
    word = port / 32;
    switch(word)
    {
      case 0:
        if( disable )
        {
          NOC_OUT(info->base_addr, info->disable_offset, DISABLE_SBM_FLAGOUTSET0_LOW, val);
        }
        else
        {
          NOC_OUT(info->base_addr, info->disable_offset, DISABLE_SBM_FLAGOUTCLR0_LOW, val);
        }
        break;
      case 1:
        if( disable )
        {
          NOC_OUT(info->base_addr, info->disable_offset, DISABLE_SBM_FLAGOUTSET0_HIGH, val);
        }
        else
        {
          NOC_OUT(info->base_addr, info->disable_offset, DISABLE_SBM_FLAGOUTCLR0_HIGH, val);
        }
        break;
      default:
        break;
    }

  }
}

/* -----------------------------------------------------------------------
** Data Interface
** ----------------------------------------------------------------------- */
/**
@copydoc HAL_noc_GetDefaultPriority
*/
bool HAL_noc_GetDefaultPriority
(
  HAL_noc_InfoType *info,
  uint32_t          master_port,
  uint32_t *        priority
)
{
  bool ret = false;

  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters &&
      NULL != priority )
  {
    *priority = 
      NOC_INFI(info->base_addr, info->qos_offset, info->qos_size,
                QOS_MAINCTL_LOW, master_port, DFLTPRIORITY);
    ret = true;
  }

  return ret;
}

/**
@copydoc HAL_noc_IsQosDisabled
*/
bool HAL_noc_IsQosDisabled
(
  HAL_noc_InfoType *info,
  uint32_t          master_port
)
{
  bool ret = false;

  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters )
  {
    ret = 
      NOC_INFI(info->base_addr, info->qos_offset, info->qos_size,
                QOS_MAINCTL_LOW, master_port, QOSDISABLE) == 1;
  }

  return ret;
}

/**
@copydoc HAL_noc_GetLimiter
*/
bool HAL_noc_GetLimiter
(
  HAL_noc_InfoType *   info,
  uint32_t             master_port,
  HAL_noc_LimiterType *config
)
{
  bool ret = false;

  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters )
  {
    config->bandwidth =
      NOC_INFI(info->base_addr, info->qos_offset, info->qos_size,
               QOS_LIMITBW_LOW, master_port, BANDWIDTH);
    config->saturation =
      NOC_INFI(info->base_addr, info->qos_offset, info->qos_size,
               QOS_LIMITBW_LOW, master_port, SATURATION);
    ret = true;
  }

  return ret;
}

/**
@copydoc HAL_noc_IsLimiterEnabled
*/
bool HAL_noc_IsLimiterEnabled
(
  HAL_noc_InfoType *info,
  uint32_t          master_port
)
{
  bool ret = false;

  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters )
  {
    ret =
      NOC_INFI(info->base_addr, info->qos_offset, info->qos_size,
               QOS_MAINCTL_LOW, master_port, BWLIMITEN) == 1;
  }

  return ret;
}

/**
@copydoc HAL_noc_GetRegulator
*/
bool HAL_noc_GetRegulator
(
  HAL_noc_InfoType *     info,
  uint32_t               master_port,
  uint32_t               index,
  HAL_noc_RegulatorType *config
)
{
  bool ret = false;

  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters )
  {
    config->high_priority =
      NOC_INFI2(info->base_addr, info->qos_offset, info->qos_size,
                QOS_REGULmCTL_LOWn, master_port, index, HIGHPRIORITY);
    config->low_priority =
      NOC_INFI2(info->base_addr, info->qos_offset, info->qos_size,
                QOS_REGULmCTL_LOWn, master_port, index, LOWPRIORITY);
    config->bandwidth =
      NOC_INFI2(info->base_addr, info->qos_offset, info->qos_size,
                QOS_REGULmBW_LOWn, master_port, index, BANDWIDTH);
    config->saturation =
      NOC_INFI2(info->base_addr, info->qos_offset, info->qos_size,
                QOS_REGULmBW_LOWn, master_port, index, SATURATION);
    ret = true;
  }

  return ret;
}

/**
@copydoc HAL_noc_GetRegulatorMode
*/
bool HAL_noc_GetRegulatorMode
(
  HAL_noc_InfoType *         info,
  uint32_t                   master_port,
  uint32_t                   index,
  HAL_noc_RegulatorModeType *mode
)
{
  bool ret = false;

  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters &&
      NULL != mode )
  {
    mode->read = 
      NOC_INFI2(info->base_addr, info->qos_offset, info->qos_size,
                QOS_REGULmCTL_LOWn, master_port, index, RDEN) == 1;
    mode->write = 
      NOC_INFI2(info->base_addr, info->qos_offset, info->qos_size,
                QOS_REGULmCTL_LOWn, master_port, index, WREN) == 1;
    mode->critical = 
      NOC_INFI2(info->base_addr, info->qos_offset, info->qos_size,
                QOS_REGULmCTL_LOWn, master_port, index, CRITICALEN) == 1;
    mode->noncritical = 
      NOC_INFI2(info->base_addr, info->qos_offset, info->qos_size,
                QOS_REGULmCTL_LOWn, master_port, index, NONCRITICALEN) == 1;
    ret = true;
  }

  return ret;
}

/**
@copydoc HAL_noc_IsUrgencyForwardingEnabled
*/
bool HAL_noc_IsUrgencyForwardingEnabled
(
  HAL_noc_InfoType *info,
  uint32_t          master_port
)
{
  bool ret = false;

  /* Verify input parameters. */
  if( NULL != info &&
      master_port < info->num_masters )
  {
    ret = 
      NOC_INFI(info->base_addr, info->qos_offset, info->qos_size,
               QOS_MAINCTL_LOW, master_port, SLVURGMSGEN);
  }

  return ret;
}

/**
@copydoc HAL_noc_IsTargetDisabled
*/
bool HAL_noc_IsTargetDisabled
(
  HAL_noc_InfoType *info,
  uint32_t          port
)
{
  uint32_t word, bit, val;
  bool ret = false;

  /* Verify input parameters. */
  if( NULL != info )
  {
    /* Get the right status register. */
    word = port / 32;
    switch(word)
    {
      case 0:
        val = NOC_IN(info->base_addr, info->disable_offset, DISABLE_SBM_SENSEIN0_LOW);
        break;
      case 1:
        val = NOC_IN(info->base_addr, info->disable_offset, DISABLE_SBM_SENSEIN0_HIGH);
        break;
      default:
        val = 0;
        break;
    }

    /* Get the correct status bit. */
    bit = port % 32;
    ret = val & (1 << bit);
  }

  return ret;
}

