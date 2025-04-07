/**
  @file  QPPCTypes.h
  @brief QPPC type definitions for UEFI.
*/
/*==============================================================================
 Copyright 2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
==============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who       what, where, why
 --------   ---       -----------------------------------------------------------
 12/08/22   arajashe  Added QPPC device ID

=============================================================================*/
#ifndef __QPPCTYPES_H__
#define __QPPCTYPES_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/


/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/
#define QPPC_GLOBAL_FLAG_LOG_CLOCK_FREQ_CHANGE 0x00000001

/**
 * Callback data type, natural datatype size based on processor.
 */
typedef void*         QPPC_CBData;

/**
 * Callback function prototype for registering the callbacks.
 */
typedef void (*PQPPC_CB) (QPPC_CBData nData);

/**
  QPPC return values.
 */
typedef enum QPPCResult
{
  QPPC_SUCCESS                         = 0,
  QPPC_ERROR                           = -1,
  QPPC_ERROR_INVALID_PARAMETER         = -2,
  QPPC_ERROR_NOT_FOUND                 = -3,
  QPPC_ERROR_INTERNAL                  = -4,
  QPPC_ERROR_OUT_OF_RANGE_PARAMETER    = -5,
  QPPC_ERROR_UNSUPPORTED               = -6,
} QPPCResult;

/** @ingroup efi_qppc_protocol_data
 * QPPC Query type.
 *
 * The following enumeration is used to specify specific query type
 * to get data from QPPC driver.
 */
typedef enum
{
  QPPC_QUERY_NUM_PERF_LEVELS,      /**< Query the number of performance levels. */
  QPPC_QUERY_PERF_LEVEL_FREQ_HZ,   /**< Query performance level frequency. */
  QPPC_QUERY_DFS_ENABLED,          /**< Query if DFS is enabled or not. */
  QPPC_QUERY_DFS_MODE,             /**< Query DFS mode Auto/Descrete. */
  QPPC_QUERY_UPDATE,
  QPPC_QUERY_ACTIVE_FREQ,
  QPPC_QUERY_MAX_NUM_CORES,
  
  /*TODO: Add new queries, required for power SW, Quest SW */
  
  QPPC_TOTAL_NUM_OF_QUERIES,
} QPPCQueryType;


/** @ingroup efi_qppc_protocol_data
 * QPPC Query type.
 *
 * The following enumeration is used to specify query specifi input parameters
 * to get data from QPPC driver.
 */
typedef union QppcQueryParam
{
  struct /**< QPPC_QUERY_NUM_PERF_LEVELS */
  {
    UINT32            nCoreid;            
  }id;
  struct /**<   QPPC_QUERY_PERF_LEVEL_FREQ_HZ */
  {
    UINT32            nCoreid;            
    UINT32            nPerfLevel;
  }nPerfData;
  
} QppcQueryParam;


/** @ingroup efi_qppc_protocol_data
 * QPPC Query result type.
 *
 * The following structure is used to store the query specific data which will 
 * be filled by QPPC driver.
 */
typedef struct QppcQueryResult
{
  QPPCQueryType eType;                       /**< Query type this result is for. */
  union
  {
    UINT32            nNumPerfLevels;     /**< QPPC_QUERY_NUM_PERF_LEVELS */
    UINT32            nPerfLevelFreqHz;   /**< QPPC_QUERY_PERF_LEVEL_FREQ_HZ */
    UINT32            bDFSEnabled;        /**< QPPC_QUERY_DFS_ENABLED */
    UINT32            nDFSMode;           /**< QPPC_QUERY_DFS_MODE */
    UINT32            nActivePerfFreqHz;  /**< QPPC_QUERY_ACTIVE_FREQ */
    UINT32            nMaxNumCores;       /**< QPPC_QUERY_MAX_NUM_CORES */
                                                 
  } Data;
} QppcQueryResultType;

/** @ingroup efi_qppc_protocol_data
 * QPPC configuration type.
 *
 * The following enumeration is used to specify specific configuration to set/get
 * to/from QPPC driver.
 */
typedef enum
{
  QPPC_CONFIG_PARAM_DISCRETE_PERF_LEVEL,
  QPPC_CONFIG_PARAM_AUTONOMOUS_PERF_LEVEL,
  QPPC_CONFIG_PARAM_DISCRETE_FREQUENCY,
  /* TODO: Add new configs */
  
  QPPC_CONFIG_PARAM_TOTAL_PERF_LEVEL,
} QPPCConfigType;

/** @ingroup efi_qppc_protocol_data
 * QPPC configuration parameters type.
 *
 * The following enumeration is used to specify specific configuration parameters to set/get
 * to/from QPPC driver.
 */
typedef union QppcConfigParam
{
  struct
  {
    UINT32            nCoreid;
    UINT32            nPerfLevel;
    UINT32            nFreqHz;
  } DescPerfLevel;
  struct
  {
    UINT32            nCoreid;
    UINT32            nMinPerfLevel;
    UINT32            nMaxPerfLevel;
  } AutoPerfLevel;
  
}QppcConfigParam;
 
#endif