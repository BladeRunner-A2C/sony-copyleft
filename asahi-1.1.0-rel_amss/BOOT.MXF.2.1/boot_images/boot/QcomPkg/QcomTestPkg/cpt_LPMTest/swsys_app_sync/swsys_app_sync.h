/**
  @file swsys_app_sync.h
  @brief
  This file contains the implementation of the interfaces for 
  apps synchronization 
*/
/*
 Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
 QUALCOMM Proprietary and Confidential.
===============================================================================

                             Edit History


when       who     what, where, why
--------   ---     ------------------------------------------------------------
04/21/18   ly      Create
===============================================================================
*/

#include <swsys_kernel_lib.h>

#define EXIT_APP_EVT        0x54495845505041ULL
#define TEST_SYNC_EVT       0x434E595354534554ULL
#define PAUSE_APP_EVT       0x4E5552505041ULL
#define CPU_LOAD_EXIT_EVT   0x44414F4C555043ULL
#define DDR_PWRS_EXIT_EVT   0x53525750524444ULL
#define AOP_TEMP_EVT        0x504D4554504F41ULL

//Thread* quest_exit_app_thread_init(char *);

#define QUESTAPP_LOCK_NAME  "QUESTAPP"
#define QUESTLOG_LOCK_NAME  "QUESTLOG"
#define QUESTERR_LOCK_NAME  "QUESTERR"

//Don't change this lock name. It will be used by SystemSleepLib
#define QUESTCLOCK_LOCK_NAME  "Clk_Lock"

Event* quest_exit_app_event_init(void);
Event* quest_pause_app_event_init(void);
Event* quest_aop_temp_event_init(void);



