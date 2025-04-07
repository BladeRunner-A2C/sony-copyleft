/**
  @file EFIStorageResiliency.h
  @brief Storage Resiliency protocol definitions.
*/
/*=============================================================================
  Copyright (c) 2023 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when        who     what, where, why
 --------    ---     -----------------------------------------------------------
 01/04/23    jt      Initial version
 
=============================================================================*/
#ifndef __EFI_STORAGE_RESILIENCY_H__
#define __EFI_STORAGE_RESILIENCY_H__

/** @defgroup EFI_STORAGE_RESILIENCY_PROTOCOL  EFI_STORAGE_RESILIENCY_PROTOCOL
 *  @ingroup PERIPHERALS 
 */

/** @defgroup  EFI_STORAGE_RESILIENCY_PROTOCOL_prot PROTOCOL
 *  @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL 
 */ 

/** @defgroup  EFI_STORAGE_RESILIENCY_PROTOCOL_apis APIs
 *  @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL 
 */ 

/** @defgroup  EFI_STORAGE_RESILIENCY_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL 
 */

/** @cond */
typedef struct _EFI_STORAGE_RESILIENCY_PROTOCOL   EFI_STORAGE_RESILIENCY_PROTOCOL;
/** @endcond */

/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_data
  Protocol version.
*/
#define EFI_STORAGE_RESILIENCY_PROTOCOL_REVISION 0x0000000000010000

/* Protocol GUID definition */
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_data */
#define EFI_STORAGE_RESILIENCY_PROTOCOL_GUID \
   {0x6851982c, 0xd766, 0x4fe6, { 0x91, 0x95, 0xd0, 0x5d, 0x44, 0x3d, 0xf5, 0xcf } }

/** @cond */
/* External reference to the Storage Resiliency Protocol GUID */
extern EFI_GUID gEfiStorageResiliencyProtocolGuid; 
/** @endcond */

/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_data
  Scan and fix status types. 
*/
typedef enum _EFI_SCAN_AND_FIX_STATUS
{
  EFI_SCAN_AND_FIX_STATUS_NOT_STARTED = 1, 
  EFI_SCAN_AND_FIX_STATUS_RUNNING     = 2, 
  EFI_SCAN_AND_FIX_STATUS_COMPLETE    = 3
} EFI_SCAN_AND_FIX_STATUS;

/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_data
  Create HMAC status types. 
*/
typedef enum _EFI_CREATE_HMAC_STATUS
{
  EFI_CREATE_HMAC_STATUS_NOT_STARTED = 1, 
  EFI_CREATE_HMAC_STATUS_RUNNING     = 2, 
  EFI_CREATE_HMAC_STATUS_COMPLETE    = 3
} EFI_CREATE_HMAC_STATUS;

/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_data
  Health check status types. 
*/
typedef enum _EFI_HEALTH_CHECK_STATUS
{
  EFI_HEALTH_CHECK_STATUS_NOT_STARTED = 1, 
  EFI_HEALTH_CHECK_STATUS_RUNNING     = 2, 
  EFI_HEALTH_CHECK_STATUS_COMPLETE    = 3
} EFI_HEALTH_CHECK_STATUS;

/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_data
  Health check overall result types. 
*/
typedef enum
{
  EFI_HEALTH_CHECK_PRIMARY_BACKUP_GOOD = 0, 
  EFI_HEALTH_CHECK_ONE_GOOD_COPY       = 1,  
  EFI_HEALTH_CHECK_PRIMARY_BACKUP_BAD  = 2
} EFI_HEALTH_CHECK_OVERALL_RESULT;

/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_data
  Health check data structure 
*/
typedef struct 
{
  EFI_HEALTH_CHECK_OVERALL_RESULT    OverallResult; 
  UINT64                             Lba;  
  EFI_GUID                           PartitionGuid;   
} EFI_HEALTH_CHECK_DATA;

/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/

/* EFI_SCAN_AND_FIX_START */
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_apis
  @par Summary
  Starts scan and fix session for resilient partitions 

  @param[in]   This         Pointer to the EFI_STORAGE_RESILIENCY_PROTOCOL instance.
  @param[out]  Token        Pointer to a token 

  @par Description
  This function starts the scan and fix session for all the critical data 
  partitions.  

  @return
  EFI_SUCCESS           -- Function completed successfully. 
  @par
  EFI_INVALID_PARAMETER -- Invalid argument is provided.   
  @par
  EFI_OUT_OF_RESOURCES  -- Not enough resources are available.  
  @par
  EFI_ALREADY_STARTED   -- Ongoing session is already in progress.   
*/
typedef
EFI_STATUS 
(EFIAPI * EFI_SCAN_AND_FIX_START) (
   IN  EFI_STORAGE_RESILIENCY_PROTOCOL   *This, 
   OUT UINT32                            *Token
);

/* EFI_SCAN_AND_FIX_RUN_JOB */
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_apis
  @par Summary
  Checks one sector of a resilient partition and will try to 
  correct it if there is a MAC mismatch 

  @param[in]   This         Pointer to the EFI_STORAGE_RESILIENCY_PROTOCOL instance.
  @param[in]   Token        Token value from EFI_SCAN_AND_FIX_START 
  @param[out]  Result       Indication of the job status (running or not, complete)

  @par Description
  This function checks one sector of a resilient partition and sees whether 
  the MAC check succeeds or not. If one of the two copies is bad, then the 
  good copy will be used to correct the bad one. In case both copies are bad, 
  this will be logged.  

  @return
  EFI_SUCCESS           -- Function completed successfully. 
  @par
  EFI_INVALID_PARAMETER -- Invalid argument is provided.    
  @par
  EFI_COMPROMISED_DATA  -- MAC mismatch was found
  @par
  EFI_DEVICE_ERROR      -- Storage and/or MAC calculation failure
*/
typedef
EFI_STATUS 
(EFIAPI * EFI_SCAN_AND_FIX_RUN_JOB) (
   IN  EFI_STORAGE_RESILIENCY_PROTOCOL   *This, 
   IN  UINT32                            Token, 
   OUT EFI_SCAN_AND_FIX_STATUS           *Result
);

/* EFI_SCAN_AND_FIX_STOP */
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_apis
  @par Summary
  Stops scan and fix session for resilient partitions 

  @param[in]   This         Pointer to the EFI_STORAGE_RESILIENCY_PROTOCOL instance.
  @param[in]   Token        Token value from EFI_SCAN_AND_FIX_START 

  @par Description
  This function stops the scan and fix session corresponding to Token. 

  @return
  EFI_SUCCESS           -- Function completed successfully. 
  @par
  EFI_INVALID_PARAMETER -- Invalid argument is provided.    
*/
typedef
EFI_STATUS 
(EFIAPI * EFI_SCAN_AND_FIX_STOP) (
   IN  EFI_STORAGE_RESILIENCY_PROTOCOL   *This, 
   IN  UINT32                            Token
);

/* EFI_CREATE_HMAC_START */
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_apis
  @par Summary
  Starts create HMAC session for resilient partitions 

  @param[in]   This         Pointer to the EFI_STORAGE_RESILIENCY_PROTOCOL instance.
  @param[out]  Token        Pointer to a token 

  @par Description
  This function copies the data for all the critical data partitions
  from the primary guid to the backup guid and computes the HMAC 
  for both copies. It is only allowed in manufacturing mode.   

  @return
  EFI_SUCCESS           -- Function completed successfully. 
  @par
  EFI_INVALID_PARAMETER -- Invalid argument is provided.  
  @par
  EFI_OUT_OF_RESOURCES  -- Not enough resources are available.   
  @par
  EFI_ACCESS_DENIED     -- Not in manufacturing mode.    
  @par
  EFI_ALREADY_STARTED   -- Ongoing session is already in progress.   
*/
typedef
EFI_STATUS 
(EFIAPI * EFI_CREATE_HMAC_START) (
   IN  EFI_STORAGE_RESILIENCY_PROTOCOL   *This, 
   OUT UINT32                            *Token
);

/* EFI_CREATE_HMAC_RUN_JOB */
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_apis
  @par Summary
  Copies one block from the primary GUID to the backup GUID and computes
  the HMAC for both copies 

  @param[in]   This         Pointer to the EFI_STORAGE_RESILIENCY_PROTOCOL instance.
  @param[in]   Token        Token value from EFI_CREATE_HMAC_START 
  @param[out]  Result       Indication of the job status (running or not, complete)

  @par Description
  This function will copy one block from the primary GUID to the backup GUID
  and compute the HMAC for both copies. Users should keep calling this API 
  as long as the result value is CREATE_HMAC_STATUS_RUNNING. It is only 
  allowed in manufacturing mode.   

  @return
  EFI_SUCCESS           -- Function completed successfully. 
  @par
  EFI_INVALID_PARAMETER -- Invalid argument is provided.    
  @par
  EFI_ACCESS_DENIED     -- Not in manufacturing mode.  
  @par
  EFI_DEVICE_ERROR      -- Storage and/or MAC calculation failure
*/
typedef
EFI_STATUS 
(EFIAPI * EFI_CREATE_HMAC_RUN_JOB) (
   IN  EFI_STORAGE_RESILIENCY_PROTOCOL   *This, 
   IN  UINT32                            Token, 
   OUT EFI_CREATE_HMAC_STATUS            *Result
);

/* EFI_CREATE_HMAC_STOP */
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_apis
  @par Summary
  Stops create HMAC session for resilient partitions 

  @param[in]   This         Pointer to the EFI_STORAGE_RESILIENCY_PROTOCOL instance.
  @param[in]   Token        Token value from EFI_CREATE_HMAC_START 

  @par Description
  This function stops the create HMAC session corresponding to Token. It is 
  only allowed in manufacturing mode. 

  @return
  EFI_SUCCESS           -- Function completed successfully. 
  @par
  EFI_INVALID_PARAMETER -- Invalid argument is provided.  
  @par
  EFI_ACCESS_DENIED     -- Not in manufacturing mode.      
*/
typedef
EFI_STATUS 
(EFIAPI * EFI_CREATE_HMAC_STOP) (
   IN  EFI_STORAGE_RESILIENCY_PROTOCOL   *This, 
   IN  UINT32                            Token
);

/* EFI_HEALTH_CHECK_START */
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_apis
  @par Summary
  Starts health check session for resilient partitions 

  @param[in]   This         Pointer to the EFI_STORAGE_RESILIENCY_PROTOCOL instance.
  @param[out]  Token        Pointer to a token 

  @par Description
  This function starts the health check session for all the critical data 
  partitions.  

  @return
  EFI_SUCCESS           -- Function completed successfully. 
  @par
  EFI_INVALID_PARAMETER -- Invalid argument is provided.   
  @par
  EFI_ALREADY_STARTED   -- Ongoing session is already in progress.   
*/
typedef
EFI_STATUS 
(EFIAPI * EFI_HEALTH_CHECK_START) (
   IN  EFI_STORAGE_RESILIENCY_PROTOCOL   *This, 
   OUT UINT32                            *Token
);

/* EFI_HEALTH_CHECK_RUN_JOB */
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_apis
  @par Summary
  Computes the HMAC from one block of the primary and backup GUID and 
  sees whether the HMAC is correct 

  @param[in]   This         Pointer to the EFI_STORAGE_RESILIENCY_PROTOCOL instance.
  @param[in]   Token        Token value from EFI_HEALTH_CHECK_START 
  @param[out]  Data         Structure containing information about the last block check
  @param[out]  Result       Indication of the job status (running or not, complete)

  @par Description
  This function will do a HMAC health check by computing the HMAC from one
  block of the primary and backup GUID and seeing whether the HMAC entry 
  has the correct data. Users should keep calling this API as long as 
  the result value is HEALTH_CHECK_STATUS_RUNNING.    

  @return
  EFI_SUCCESS           -- Function completed successfully. 
  @par
  EFI_INVALID_PARAMETER -- Invalid argument is provided.    
  @par
  EFI_DEVICE_ERROR      -- Storage and/or MAC calculation failure
*/
typedef
EFI_STATUS 
(EFIAPI * EFI_HEALTH_CHECK_RUN_JOB) (
   IN  EFI_STORAGE_RESILIENCY_PROTOCOL   *This, 
   IN  UINT32                            Token, 
   OUT EFI_HEALTH_CHECK_DATA             *Data, 
   OUT EFI_HEALTH_CHECK_STATUS           *Result
);

/* EFI_HEALTH_CHECK_STOP */
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_apis
  @par Summary
  Stops health check session for resilient partitions 

  @param[in]   This         Pointer to the EFI_STORAGE_RESILIENCY_PROTOCOL instance.
  @param[in]   Token        Token value from EFI_HEALTH_CHECK_START 

  @par Description
  This function stops the health check session corresponding to Token.  

  @return
  EFI_SUCCESS           -- Function completed successfully. 
  @par
  EFI_INVALID_PARAMETER -- Invalid argument is provided.    
*/
typedef
EFI_STATUS 
(EFIAPI * EFI_HEALTH_CHECK_STOP) (
   IN  EFI_STORAGE_RESILIENCY_PROTOCOL   *This, 
   IN  UINT32                            Token
);

/* EFI_ENABLE_BACKUP */
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_apis
  @par Summary
  Enables backup resiliency for resilient partitions 

  @param[in]   This         Pointer to the EFI_STORAGE_RESILIENCY_PROTOCOL instance.

  @par Description
  This function enables backup resiliency for the resilient partitions. Both
  the primary and the backup partitions will be updated on a write operation. 

  @return
  EFI_SUCCESS           -- Function completed successfully. 
  @par
  EFI_DEVICE_ERROR      -- Failed to save configuration info to the resiliency partition.    
*/
typedef 
EFI_STATUS
(EFIAPI * EFI_ENABLE_BACKUP) (
   IN  EFI_STORAGE_RESILIENCY_PROTOCOL   *This
); 

/* EFI_DISABLE_BACKUP */
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_apis
  @par Summary
  Disables backup resiliency for resilient partitions 

  @param[in]   This         Pointer to the EFI_STORAGE_RESILIENCY_PROTOCOL instance.

  @par Description
  This function disables backup resiliency for the resilient partitions. Only
  the primary partition will be updated on a write operation. 

  @return
  EFI_SUCCESS           -- Function completed successfully. 
  @par
  EFI_DEVICE_ERROR      -- Failed to save configuration info to the resiliency partition.    
*/
typedef 
EFI_STATUS
(EFIAPI * EFI_DISABLE_BACKUP) (
   IN  EFI_STORAGE_RESILIENCY_PROTOCOL   *This                              
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup EFI_STORAGE_RESILIENCY_PROTOCOL_prot
  @par Summary
  Storage Resiliency Protocol interface. 

  @par Parameters
  @inputprotoparams{storage_resiliency_proto_params.tex} 
*/
struct _EFI_STORAGE_RESILIENCY_PROTOCOL 
{  
   UINT64                               Revision;
   EFI_SCAN_AND_FIX_START               ScanAndFixStart; 
   EFI_SCAN_AND_FIX_RUN_JOB             ScanAndFixRunJob;
   EFI_SCAN_AND_FIX_STOP                ScanAndFixStop; 
   EFI_CREATE_HMAC_START                CreateHmacStart; 
   EFI_CREATE_HMAC_RUN_JOB              CreateHmacRunJob;
   EFI_CREATE_HMAC_STOP                 CreateHmacStop; 
   EFI_HEALTH_CHECK_START               HealthCheckStart; 
   EFI_HEALTH_CHECK_RUN_JOB             HealthCheckRunJob;
   EFI_HEALTH_CHECK_STOP                HealthCheckStop; 
   EFI_ENABLE_BACKUP                    EnableBackup; 
   EFI_DISABLE_BACKUP                   DisableBackup; 
};

#endif	/* __EFI_STORAGE_RESILIENCY_H__ */

