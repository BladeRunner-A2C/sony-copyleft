/**
  @file  QuestExtHelper.h
  @brief QUESTEXT Protocol Helper/data structure implemenatation for UEFI.
*/

/*=============================================================================
  Copyright (c) 2022-2023 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when        who        what, where, why
 ---------   --------   --------------------------------------------------------
04/21/23   swaghmar    QUESTEXT Protocol Data Structures

=============================================================================*/
#ifndef QUESTEXTHELPER_H
#define QUESTEXTHELPER_H

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
#define QUEST_DEVICE_TYPE_MEMORY               0x0000000000000001
#define QUEST_DEVICE_TYPE_PROCESSOR            0x0000000000000002

//Max length for vendor name
#define MAX_VENDOR_NAME_LEN 50
/*===========================================================================
  DIAG_HELPER_RUN_LEVEL structure defines test run level
===========================================================================*/ 

typedef enum { 
    DIAG_HELPER_RUN_LEVEL_QUICK_TEST            = 0x01, 
    DIAG_HELPER_RUN_LEVEL_ADVANCED_TEST         = 0x02, 
    DIAG_HELPER_RUN_LEVEL_THOROUGH_TEST         = 0x04,   //For future use 
    DIAG_HELPER_RUN_LEVEL_MANUFACTURING_TEST    = 0x08,   //For future use 
} DIAG_HELPER_RUN_LEVEL;


/*===========================================================================
  TEST_INFO structure contains details about a particular test
===========================================================================*/  

typedef struct _TEST_INFO { 
    LIST_ENTRY                  NextTestNode;       //LIST_ENTRY member used to link objects
    UINT8                       TestId; 
    CHAR16                      *TestName; 
    DIAG_HELPER_RUN_LEVEL       TestType; 
    UINT64                      EstimatedTestTime; 
} TEST_INFO;

/*===========================================================================
  INPUT derived from TEST_CONTEXT for MEMORY_TEST
===========================================================================*/ 
typedef struct { 
    EFI_PHYSICAL_ADDRESS     PhysicalStart; 
    UINTN                   NumberOfPages; 
} MEMMAP_MEMORY_DESCRIPTOR;

typedef struct {
    MEMMAP_MEMORY_DESCRIPTOR    *MemoryDescriptors;
    UINTN                       NumberOfMemoryDescriptors;
    UINT32                      *DDR_freq_list;
    UINTN                       DDRFreqListCnt;
}MEMORY_TEST_INPUTS;

/*===========================================================================
  INPUT derived from TEST_CONTEXT for CPU_TEST
===========================================================================*/ 
typedef struct {
    UINT32  *Cluster0_freq_list;
    UINTN   Cluster0FreqListCnt;
    UINT32  *Cluster1_freq_list;
    UINTN   Cluster1FreqListCnt;
    UINT32  *Cluster2_freq_list;
    UINTN   Cluster2FreqListCnt;
}CPU_FREQ_LIST;

typedef struct {
    CPU_FREQ_LIST               CPU_freqs;
}CPU_TEST_INPUTS;

/*===========================================================================
  INPUT
===========================================================================*/ 
typedef union {
    CPU_TEST_INPUTS     CpuTestIn;    
    MEMORY_TEST_INPUTS  MemTestIn;
}TEST_INPUTS;

/*===========================================================================
  Output structure - DDR frequency at the point of failure
===========================================================================*/ 
typedef struct _DDR_FREQUENCY {
    BOOLEAN     Switch_failed;      // DDRFreqSwitch : True, other tests : False
    UINT32      Requested_freq;     //Switch requested to which DDR frequency 
    UINT32      Read_freq;          //Read back DDR freq post switch request or during QB issue
}DDR_FREQUENCY;


/*===========================================================================
  Output structure - CPU frequency per core at the point of failure
===========================================================================*/ 
typedef struct _CPU_FREQUENCY {
    UINTN Core;             //Core number, 1 –12
    UINT32 Last_CPU_freq;   //CPU frequency for core
}CPU_FREQUENCY;


/*===========================================================================
  Output structure - L1 and L2 cache error status per core. No L3 for this target.
===========================================================================*/ 
typedef struct _EDAC_STATUS{
    UINTN Core;             //Core number, 1 -12, since L1 is per core. L2 is per cluster
    UINT64 L1_ERRRMISC;
    UINT64 L1_ERRSTATUS;
    UINT64 L2_ERRRMISC;
    UINT64 L2_ERRSTATUS;
}EDAC_STATUS;

/*===========================================================================
  Output structure - LLCC cache error status
===========================================================================*/ 
typedef struct _LLCC_STATUS{
    UINT32 DRP_STATUS;      //LLCC DRP Status
    UINT32 TRP_STATUS;      //LLCC TRP Status, placeholder as TRP registers are not accessible
}LLCC_STATUS;

/*===========================================================================
  Output structure - Temp data
===========================================================================*/ 
typedef struct {
    UINTN MIN_CPU_TEMP;         //Minimum CPU temperature
    UINTN MAX_CPU_TEMP;         //Maximum CPU temperature
    UINTN MIN_DDR_TEMP;         //Minimum DDR temperature
    UINTN MAX_DDR_TEMP;         //Maximum DDR temperature
    UINTN MIN_AMBIENT_TEMP;     //Minimum AMBIENT temperature
    UINTN MAX_AMBIENT_TEMP;     //Maximum AMBIENT temperature
    UINTN MIN_SKIN_TEMP;        //Minimum SKIN temperature
    UINTN MAX_SKIN_TEMP;        //Maximum SKIN temperature
}TEMP_DATA;


/*===========================================================================
  Generic Output structure for all Quest Tests
===========================================================================*/ 
/*
typedef struct _TEST_RESULT {                   
    UINT16                  TestId;                 //Test identifier which detected the issue 
    CHAR8                   *Failure_reason;        //Failure message like DDR memory corruption    
    //UINT64                  Error_code;    
    UINTN                   Issue_cluster;          //Cluster Number from where issue was detected
    UINTN                   Issue_core;             //Core Number whose current thread detected the issue
    VOID                    *Address;               //Faulty address, either from DDR or cache.
    UINT64                  ExpectedValue;          //Expected value stored at the Faulty address.
    UINT64                  ActualValue;            //Actual value stored at the Faulty address.
    DDR_FREQUENCY           DDR_FREQUENCY;               //DDR frequency at the point of failure
    CPU_FREQUENCY           *CPU_FREQUENCY;              //CPU frequency per core at the point of failure
    UINT16                  CpuFreqCnt;
    EDAC_STATUS             *EDAC_status;           //L1 and L2 cache error status per core. No L3 for this target.
    UINT16                  EDACStatusCnt;
    LLCC_STATUS             LLCC_status;            //LLCC cache error status
    TEMP_DATA               Temp_data;
} TEST_RESULT;
*/
typedef struct _TEST_RESULT {
    UINT16                  TestId;                 //Test identifier which detected the issue 
    CHAR8                   *Failure_reason;        //Failure message like DDR memory corruption    
    UINTN                   Issue_cluster;          //Cluster Number from where issue was detected
    UINTN                   Issue_core;             //Core Number whose current thread detected the issue
    VOID                    *Address;               //Faulty address, either from DDR or cache.
    UINT64                  ExpectedValue;          //Expected value stored at the Faulty address.
    UINT64                  ActualValue;            //Actual value stored at the Faulty address.
    DDR_FREQUENCY           DDR_freq;               //DDR frequency at the point of failure
    CPU_FREQUENCY           *CPU_freq;              //CPU frequency per core at the point of failure
    UINT16                  CpuFreqCnt;
    EDAC_STATUS             *EDAC_status;           //L1 and L2 cache error status per core. No L3 for this target.
    UINT16                  EDACStatusCnt;
    LLCC_STATUS             LLCC_status;            //LLCC cache error status
    TEMP_DATA               Temp_data;				//Temperature data
	UINT64                  Error_code;
} TEST_RESULT;

/*===========================================================================
  TEST_CONTEXT
===========================================================================*/   
typedef struct {
    TEST_RESULT             *TestErrorList;
    UINTN                   TotalTestErrCnt;
    TEST_INPUTS             TestIn;
    VOID                    *Rsvd; //For future use
}TEST_CONTEXT;

 
/*===========================================================================
  Payload used for the callback function
===========================================================================*/  
typedef struct _PROGRESS_STRUCT { 
    UINTN                   TestId;
    CHAR16                  *ProgressMsg; 
    UINT64                  *RemainingTimeInSecs;
} PROGRESS_STRUCT;

/*=========================================================================
      Callback Function Pointer
==========================================================================*/

typedef VOID (*PROGRESS_CALLBACK_FUNC)(
    IN PROGRESS_STRUCT *ProgressUpdate
); 

#endif	//QUESTEXTHELPER_H