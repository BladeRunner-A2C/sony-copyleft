/*==============================================================================

FILE:      coreinit.c

DESCRIPTION: This file implements the coreinit driver.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/SocPkg/Lanai/Library/CoreInitTargetLib/coreinit.c#1 $ 
$DateTime: 2024/04/02 23:00:31 $
$Author: cirrusp4svc $
$Change: 53083464 $ 

When        Who    What, where, why
----------  ---    -----------------------------------------------------------
2022/07/29  sds    Initial revision
 
        Copyright (c) 2022 QUALCOMM Technologies, Incorporated.
                        All Rights Reserved.
                     QUALCOMM Proprietary/GTDR
==============================================================================*/
#include <api/systemdrivers/icbarb.h>

/*==============================================================================
                     GLOBAL VARIABLES FOR THIS MODULE
==============================================================================*/
static npa_client_handle config_handle = NULL;

/*=========================================================================
      Functions
==========================================================================*/
void coreinit_init( void )
{
  /* Path to CNOC. */
  ICBArb_MasterSlaveType routes[] =
  {
    { ICBID_MASTER_APPSS_PROC, ICBID_SLAVE_CLK_CTL },
    { ICBID_MASTER_QUP_1,      ICBID_SLAVE_EBI1 },
    { ICBID_MASTER_QUP_CORE_1, ICBID_SLAVE_QUP_CORE_1 }
  }; 

  ICBArb_RequestType requests[] =
  {
    {
      .arbType = ICBARB_REQUEST_TYPE_3,
      .arbData.type3 =
      {
        .uIb = 1,                 /**< Instantaneous bandwidth in Bytes/second */
        .uAb = 1,                 /**< Arbitrated bandwidth in Bytes/second */
        .uLatencyNs = 0           /**< Latency requirement in nanoseconds */
      }
    },
    {
      .arbType = ICBARB_REQUEST_TYPE_3,
      .arbData.type3 =
      {
        .uIb = 1,                 /**< Instantaneous bandwidth in Bytes/second */
        .uAb = 1,                 /**< Arbitrated bandwidth in Bytes/second */
        .uLatencyNs = 0           /**< Latency requirement in nanoseconds */
      }
    },
    {
      .arbType = ICBARB_REQUEST_TYPE_3,
      .arbData.type3 =
      {
        .uIb = 1,                 /**< Instantaneous bandwidth in Bytes/second */
        .uAb = 1,                 /**< Arbitrated bandwidth in Bytes/second */
        .uLatencyNs = 0           /**< Latency requirement in nanoseconds */
      }
    }
  };


  /* Create our client. */
  config_handle = npa_create_sync_client_ex( "/icb/arbiter",
                                             "Core Init Default Client",
                                             NPA_CLIENT_SUPPRESSIBLE_VECTOR,
                                             sizeof(routes),
                                             &routes );

  /* Issue the request if we successfully created the handle. */
  if( NULL != config_handle )
  {
    npa_issue_vector_request( config_handle,
                              sizeof(requests)/(sizeof(npa_resource_state)),
                              (npa_resource_state *)requests );
  }
}

/* vim: set ts=2 sts=2 sw=2 et :*/ 
