/** @file cpt_MpTest.c
   
  Application to test Multi core/threading in UEFI env.
  
 Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved   

**/

/*=============================================================================
                              EDIT HISTORY


  when         who     what, where, why
  ----------   ---     -----------------------------------------------------------
  10/15/2020   pm      Initial version
=============================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/QcomLib.h>

#include <Library/UefiCfgLib.h>
#include <Library/HobLib.h>
#include <Library/SerialPortShLib.h>
#include <Protocol/EFIDisplayPwrCtrl.h>
#include <Protocol/EFIPsleepInterface.h>
#include <Protocol/EFIKernelInterface.h>

#include "swsys_app_sync/swsys_app_sync.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "swsys_env/swsys_env.h"

#define KEEP_DISPLAY_OFF    0   //Keep display off during and after the end of sleep test
#define KEEP_DISPLAY_ON     1   //Keep display on during sleep test
#define DISPLAY_TOGGLE      2   //Turn off display at beginning of sleep test an turn it back on when sleep test is done
#define DISPLAY_ITERATION   3	//Toggle display per sleep iteration
#define MAX_THREADS         10
#define CORES               8

typedef struct sleep_test_stat{
	uint32_t c4d4_count;
	uint32_t cxpc_count;
	uint32_t aosd_count;
}sleep_test_stat_t;



void swsys_error(const char* format, ...);
void swsys_debug(const char* format, ...);
void swsys_info(const char* format, ...);


uint32 orderlist[8]={0, 1, 2, 3, 4, 5, 6, 7};
int loggerlist[8]={0, 0, 0, 0, 0, 0, 0, 0};
int sleep_durations[8]={0, 0, 0, 0, 0, 0, 0, 0};
int sleep_delays[8]={0, 0, 0, 0, 0, 0, 0, 0};
int computational_threads[8]={0, 0, 0, 0, 0, 0, 0, 0};
bool display_toggle=false,enable_all_cores=false,ct_log=false;;
int sleep_window=5000,min_sleepduration=3000,iteration=1;
time_t time_stamp_1ms,itteration_start_time;

typedef struct sleep_test_thread_args {
	uint32_t sleep_duration_in_msec;
	uint32_t cpu_num;
	uint32_t delay;
	uint32_t computational_threads;
} sleep_test_thread_args_t;


typedef struct sleep_information {
	uint32_t core_num;
	uint32_t sleep_duration;
	uint32_t sleep_delay;
	uint32_t computational_threads;
	bool is_logger;
} sleep_information;



static sleep_test_stat_t sleep_stat_start,sleep_stat_end;
EFI_PSLEEP_PROTOCOL *psleep_ptr;

void sleep_pstat_init(void)
{
	//register with PSleep if needed
	EFI_HOB_GUID_TYPE *GuidHob;
	UINT32** DataPtr;

	GuidHob = GetFirstGuidHob (&gEfiPsleepProtocolGuid);
	if(GuidHob != NULL)
	{
		//check if psleep is running. If so, register callback
		DataPtr = GET_GUID_HOB_DATA (GuidHob);  
		psleep_ptr = (EFI_PSLEEP_PROTOCOL*) *DataPtr;
  }
}

EFI_STATUS print_lpm_stat(sleep_test_stat_t* p_sleep_stat)
{
    sleep_stats_t *c4d4_stats;
    sleep_stats_t *cxsd_stats;
    sleep_stats_t *aosd_stats;

    if(psleep_ptr)
    {
        aosd_stats = psleep_ptr->GetLpmCount(POWER_SLEEP_STATS_AOSD);
        cxsd_stats = psleep_ptr->GetLpmCount(POWER_SLEEP_STATS_CXSD);
        c4d4_stats = psleep_ptr->GetLpmCount(POWER_SLEEP_STATS_C4D4);
		p_sleep_stat->c4d4_count = c4d4_stats->count;
		p_sleep_stat->cxpc_count = cxsd_stats->count;
		p_sleep_stat->aosd_count = aosd_stats->count;
        swsys_info("[AOSD] count:	0x%x	Duration:	%ld\n",aosd_stats->count, aosd_stats->total_duration);
        swsys_info("[CXSD] count:	0x%x	Duration:	%ld\n",cxsd_stats->count, cxsd_stats->total_duration);
        swsys_info("[C4D4] count:	0x%x	Duration:	%ld\n",c4d4_stats->count, c4d4_stats->total_duration);
        return EFI_SUCCESS;
    }
    else
    {
        return EFI_NOT_STARTED;
    }
}

bool check_lpm_stat(void)
{

	bool sleep_error = false;

	if (sleep_stat_end.cxpc_count > sleep_stat_start.cxpc_count) {
		swsys_info("[SLEEP_INFO] CxPC count increased\n");
	}else{
		swsys_error("[SLEEP_INFO] Warning: CxPC count did not change\n");
	}

	if (sleep_stat_end.aosd_count > sleep_stat_start.aosd_count) {
		swsys_info("[SLEEP_INFO] AOSD count increased\n");
	}else{
		swsys_error("[SLEEP_INFO] Warning: AOSD count did not change\n");
	}

	//Only declare sleep test fail when c4d4 count does not increase
	if (sleep_stat_end.c4d4_count > sleep_stat_start.c4d4_count) {
		swsys_info("[SLEEP_INFO] C4D4 count increased\n");
	}else{
		swsys_error("[SLEEP_INFO] Error: C4D4 count did not change\n");
		sleep_error = true;
	}

	return sleep_error;
}

VOID EnableAllCores (VOID)
{
	if (MpcoreGetAvailCpuCount() < MpcoreGetMaxCpuCount())
		MpcoreInitDeferredCores (0);
	ThreadSleep (10);
}

uint32 initialize_cores()
{
	uint32_t active_core_num = 0;
	uint32_t max_core_num= MpcoreGetMaxCpuCount();

	active_core_num = MpcoreGetAvailCpuCount();
	AsciiPrint("\t ### Number of cores available %d \n", active_core_num);
	AsciiPrint("\t ### Maximum Number of cores available %d \n", max_core_num);

	if (max_core_num>active_core_num)
	{
		AsciiPrint("\t ### Activating all cores \n");
		EnableAllCores();
		active_core_num = MpcoreGetAvailCpuCount();
		AsciiPrint("\t ### Number of cores available %d \n", active_core_num);
		AsciiPrint("\t ### Maximum Number of cores available %d \n", max_core_num);
	}
	return active_core_num;
}

int pi_calculator(void* args)
{
	uint32_t cpu_num,comp_num;
	time_t comp_duration,last_log,frequency;
	sleep_test_thread_args_t *log_test_thread_args = (sleep_test_thread_args_t *)args;
	
	comp_duration = sleep_window * time_stamp_1ms;
	frequency = 500 * time_stamp_1ms;
	last_log = swsys_time(0);
	cpu_num = log_test_thread_args->cpu_num;
	if (cpu_num != MpcoreGetCurrCpu())
	{
		swsys_info (" CPU number missmatch Thread CPU: %d Target CPU: %d \n",MpcoreGetCurrCpu(),cpu_num);
		return 1;
	}
	comp_num = log_test_thread_args->computational_threads;
	double pi = 0.0;
	double numerator = 4.0;
	double denominator = 1.0;
	time_t time_init = swsys_time(0);
	int i=1;
	
	while (swsys_time(0)-time_init<comp_duration)
	{
		double fraction = numerator/denominator;
		if ( i % 2)
			pi += fraction; 
		else
			pi -= fraction; 
		denominator += 2.0;
		if (swsys_time(0)-last_log>frequency)
		{
			swsys_info (" Computational Thread #%u is running on Core #%u \n",comp_num,cpu_num);
			last_log = swsys_time(0);
		}
		i++;
	}
	i=pi/2;
	swsys_info (" Computational Thread #%u is running on Core #%u , PI is %u \n",comp_num,cpu_num,i);
	return 0;
}

Thread* int_comp_test_thread(sleep_test_thread_args_t *args)
{
	char thread_name[16];
	Thread *log_thread;
	uint32_t cpu_num = args->cpu_num;

	swsys_memcpy(&thread_name[0], "LOG_", swsys_strlen("COM_")+1);
	thread_name[swsys_strlen("LOG_")] = 0x30 + cpu_num;
	thread_name[swsys_strlen("LOG_")+1] = 0x0;

	log_thread = ThreadCreate (thread_name, &pi_calculator, (void*)args, DEFAULT_PRIORITY, DEFAULT_STACK_SIZE);

	if (log_thread == NULL)
	{
		DEBUG (( EFI_D_ERROR, "Unable to create thread on %d, exiting ...\n", cpu_num));
		return NULL;
	}

	ThreadSetPinnedCpu (log_thread, cpu_num);
	ThreadResume (log_thread);

	return log_thread;
}

int LPM_logger(void* args)
{
	UINT32 cpu_num;
	time_t log_duration;
	UINT32 frequency;
	sleep_test_thread_args_t *log_test_thread_args = (sleep_test_thread_args_t *)args;
	
	
	log_duration = sleep_window * time_stamp_1ms;
	cpu_num = log_test_thread_args->cpu_num;
	if (loggerlist[cpu_num] == 0) return 0;
	if (cpu_num != MpcoreGetCurrCpu())
	{
		swsys_info (" CPU number missmatch Thread CPU: %d Target CPU: %d \n",MpcoreGetCurrCpu(),cpu_num);
		return 1;
	}
	frequency = loggerlist[cpu_num]*time_stamp_1ms;//log_test_thread_args->frequency;

	
	time_t time_init = swsys_time(0);
	time_t last_log = swsys_time(0);
	swsys_info (" Logging to UART in cpu #%d using swsys_info \n",cpu_num);
	AsciiPrint (" Logging to UART in cpu #%d using AsciiPrint \n",cpu_num);
	while (swsys_time(0)-time_init<log_duration)
	{
		if (swsys_time(0)-last_log>frequency)
		{
			swsys_info (" Logging to UART in cpu #%d using swsys_info \n",cpu_num);
			AsciiPrint (" Logging to UART in cpu #%d using AsciiPrint \n",cpu_num);
			last_log = swsys_time(0);
		}
	}
	return 0;
}

Thread* int_logger_test_thread(sleep_test_thread_args_t *args)
{
	char thread_name[16];
	Thread *log_thread;
	uint32_t cpu_num = args->cpu_num;

	swsys_memcpy(&thread_name[0], "LOG_", swsys_strlen("LOG_")+1);
	thread_name[swsys_strlen("LOG_")] = 0x30 + cpu_num;
	thread_name[swsys_strlen("LOG_")+1] = 0x0;

	log_thread = ThreadCreate (thread_name, &LPM_logger, (void*)args, DEFAULT_PRIORITY, DEFAULT_STACK_SIZE);

	if (log_thread == NULL)
	{
		DEBUG (( EFI_D_ERROR, "Unable to create thread on %d, exiting ...\n", cpu_num));
		return NULL;
	}

	ThreadSetPinnedCpu (log_thread, cpu_num);
	ThreadResume (log_thread);

	return log_thread;
}

int sleep_test_iteration_thread(void* args)
{
	UINT32 status;
	UINTN sleep_duration; 
	UINTN whichcore;
	UINT32 delay;
  
	sleep_test_thread_args_t *sleep_test_thread_args = (sleep_test_thread_args_t *)args;
	sleep_duration = sleep_test_thread_args->sleep_duration_in_msec;
	whichcore = MpcoreGetCurrCpu ();
	delay = sleep_test_thread_args->delay;
  
	if (sleep_duration==0) return 0;
  
	if (sleep_test_thread_args->cpu_num != whichcore)
	{
		swsys_info (" CPU number missmatch Thread CPU: %d Target CPU: %d \n",whichcore,sleep_test_thread_args->cpu_num);
		return 1;
	}

	AsciiPrint("\t ###core %d : delay is %d \r\n",whichcore, delay);
	time_t delay_ticks=time_stamp_1ms*delay;
	while ((swsys_time(0)-itteration_start_time)< delay_ticks);

	AsciiPrint("\t ###core %d - slp %d msec\n", whichcore, sleep_duration);

	status = MpcoreSleepCpu (sleep_duration);

	AsciiPrint("\t ###core %d up!\r\n", whichcore);

	return status;

}
// st cpt_lpmtest "-en_all -sd 500 500 -delay 2000 100"

Thread* init_sleep_test_thread(sleep_test_thread_args_t *args)
{
   char thread_name[16];
   Thread *sleep_thread;
   uint32_t cpu_num = args->cpu_num;

   swsys_memcpy(&thread_name[0], "SLP_", swsys_strlen("SLP_")+1);
   thread_name[swsys_strlen("SLP_")] = 0x30 + cpu_num;
   thread_name[swsys_strlen("SLP_")+1] = 0x0;

   sleep_thread = ThreadCreate (thread_name, &sleep_test_iteration_thread, (void*)args, DEFAULT_PRIORITY, DEFAULT_STACK_SIZE);

	if (sleep_thread == NULL)
	{
		DEBUG (( EFI_D_ERROR, "Unable to create thread on %d, exiting ...\n", cpu_num));
		return NULL;
	}

	ThreadSetPinnedCpu (sleep_thread, cpu_num);
	ThreadResume (sleep_thread);

	return sleep_thread;
}

bool sleeptest_all_oneatatime()
{	
	bool err = false;
	

	if (display_toggle)
	{
		swsys_dispctrl_off();
		AsciiPrint("Display off");
	}
	sleep_test_thread_args_t comp_args_list[CORES][MAX_THREADS];
	sleep_test_thread_args_t thread_args_list[CORES];	
	Thread* sleep_thread_list[CORES];
	Thread* logger_thread_list[CORES];
	Thread* comp_thread_list[CORES][MAX_THREADS];
	sleep_information order[CORES];
	
	for (int i=0;i<CORES;i++)
	{
		// check for random
		if (sleep_durations[i]==-1)
		{
			int random_num=swsys_rand(swsys_time(0));
			if (random_num<0)
				random_num*=-1;
			order[i].sleep_duration= min_sleepduration + (random_num%(sleep_window - min_sleepduration));
		}
		else 
			order[i].sleep_duration=sleep_durations[i];			
		// check for random
		if (sleep_delays[i]==-1)
		{
			int random_num=swsys_rand(swsys_time(0));
			if (random_num<0)
				random_num*=-1;
			order[i].sleep_delay = random_num%(min_sleepduration /(CORES+1));
		}
		else
			order[i].sleep_delay = sleep_delays[i];
		if (computational_threads[i]==-1)
		{
			int random_num=swsys_rand(swsys_time(0));
			if (random_num<0)
				random_num*=-1;
			order[i].computational_threads = random_num%(MAX_THREADS+1);
		}
		else
			order[i].computational_threads = computational_threads[i];
		
		order[i].core_num=orderlist[i];

		
		order[i].is_logger=loggerlist[i];
	}
	
	AsciiPrint("\n\t ### Sleep orders is ");
	for (int i=0;i<CORES;i++)
	{
		AsciiPrint("%d ",order[i].core_num);
		
	}
	AsciiPrint("\n");
	
	AsciiPrint("\t ### Sleep durations is ");
	for (int i=0;i<CORES;i++)
	{
		AsciiPrint("%d ",order[i].sleep_duration);
	}
	AsciiPrint("\n");
	
	AsciiPrint("\t ### Sleep delays is ");
	for (int i=0;i<CORES;i++)
	{
		AsciiPrint("%d ",order[i].sleep_delay);
	}
	AsciiPrint("\n");
	
	AsciiPrint("\t ### Computational Thread is ");
	for (int i=0;i<CORES;i++)
	{
		AsciiPrint("%d ",order[i].computational_threads);
	}
	AsciiPrint("\n");

	int active_core_num = MpcoreGetAvailCpuCount();
	itteration_start_time = swsys_time(0);
  
	//Start the threads
	for (uint32_t i = 0; i < active_core_num; i++) {
		sleep_thread_list[i] = 0;
		logger_thread_list[i] = 0;
		thread_args_list[i].cpu_num = order[i].core_num;
		thread_args_list[i].sleep_duration_in_msec = order[i].sleep_duration;
		thread_args_list[i].delay = order[i].sleep_delay;
		thread_args_list[i].computational_threads = order[i].computational_threads;
		// initiate logger threads
		logger_thread_list[i] = int_logger_test_thread(&thread_args_list[i]);
		if (!logger_thread_list[i]) {
			err = true;
			return err;
		}else{
			swsys_debug("Sleep thread %d started\n", i);
		}
	
		// initiate computational threads
		for (int j=0;j< order[i].computational_threads; j++)
		{
			comp_args_list[i][j].cpu_num = order[i].core_num;
			comp_args_list[i][j].sleep_duration_in_msec = order[i].sleep_duration;
			comp_args_list[i][j].delay = order[i].sleep_delay;
			comp_args_list[i][j].computational_threads = j+1;
			
			comp_thread_list[i][j] = NULL;
			
			//swsys_debug("ino daram pass mikonam %d started\n", comp_args_list[i][j].computational_threads);
			comp_thread_list[i][j] = int_comp_test_thread(&comp_args_list[i][j]);
			if (!comp_thread_list[i][j]) {
				err = true;
				return err;
			}else{
				swsys_debug("Sleep thread %d started\n", i);
			}
		}
		
		// initiate sleep threads
		sleep_thread_list[i] = init_sleep_test_thread (&thread_args_list[i]);
		if (!sleep_thread_list[i]) {
			err = true;
			return err;
		}else{
			swsys_debug("Sleep thread %d started\n", i);
		}

	}

	// Wait for all threads to finish
	for (uint32_t i = 0; i < active_core_num; i++) {
		ThreadJoin(sleep_thread_list[i], (int32_t *) NULL, UINT32_MAX);
	}
	for (uint32_t i = 0; i < active_core_num; i++) {
		ThreadJoin(logger_thread_list[i], (int32_t *) NULL, UINT32_MAX);
	}
  
	for (uint32_t i = 0; i < active_core_num; i++) 
		for (uint32_t j = 0; j<order[i].computational_threads;j++)
			ThreadJoin(comp_thread_list[i][j], (int32_t *) NULL, UINT32_MAX);
  
	if (display_toggle)
	{
		swsys_dispctrl_on();
		AsciiPrint("Display ON\n");
	}
	return err;
	
}

int strcasecmp(char const *string1, char const *string2)
{
    for (;; string1++, string2++) {
        int diff = tolower((unsigned char)*string1) - tolower((unsigned char)*string2);
        if (diff != 0 || !*string1)
            return diff;
    }
}

void print_arguments()
{
	uint32_t max_core_num= MpcoreGetMaxCpuCount();

	swsys_info("Sleep Durations        : ");
	for (int i=0;i<max_core_num;i++)
		swsys_info("%d ",sleep_durations[i]);
	swsys_info("\n");

	swsys_info("Sleep Delays           : ");
	for (int i=0;i<max_core_num;i++)
		swsys_info("%d ",sleep_delays[i]);
	swsys_info("\n");

	swsys_info("Logging                : ");
	for (int i=0;i<max_core_num;i++)
		swsys_info("%d ",loggerlist[i]);
	swsys_info("\n");	

	swsys_info("Computational Threads  : ");
	for (int i=0;i<max_core_num;i++)
		swsys_info("%d ",computational_threads[i]);
	swsys_info("\n");		
	
	if (display_toggle)
		swsys_info("Display Test           : ON\n");
	else
		swsys_info("Display Test           : OFF\n");
	
	swsys_info("Sleep Window           : %d ms\n",sleep_window);
	swsys_info("Minimum Sleep Duration : %d ms\n",min_sleepduration);
	swsys_info("Execution Iterations   : %d\n",iteration);
	
}

void get_lpm_arguements(UINTN Argc,CHAR8 **Argv)
{
	uint32_t max_core_num= MpcoreGetMaxCpuCount();
	int result;
	for (int i=0;i<Argc;i++)
	{
		result = strcasecmp(Argv[i],"-SD");
		if (!result)
		{
			for (int j=i+1;j<Argc;j++)
			{
				if ((isdigit(Argv[j][0]) || isdigit(Argv[j][1])) && j-i <= max_core_num)
				{
					char* ptr;
					int next = strtol(Argv[j], &ptr, 10);
					sleep_durations[j-i-1]=next;
				}
				else
				{
					i = j - 1;
					break;
				}
			}
		}
		
		result = strcasecmp(Argv[i],"-delay");
		if (!result)
		{
			for (int j=i+1;j<Argc;j++)
			{
				if ((isdigit(Argv[j][0]) || isdigit(Argv[j][1])) && j-i <= max_core_num)
				{
					char* ptr;
					int next = strtol(Argv[j], &ptr, 10);
					sleep_delays[j-i-1]=next;
				}
				else
				{
					i = j - 1;
					break;
				}
			}
		}
		
		result = strcasecmp(Argv[i],"-ct");
		if (!result)
		{
			for (int j=i+1;j<Argc;j++)
			{
				if ((isdigit(Argv[j][0]) || isdigit(Argv[j][1])) && j-i <= max_core_num)
				{
					char* ptr;
					int next = strtol(Argv[j], &ptr, 10);
					computational_threads[j-i-1]=next;
				}
				else
				{
					i = j - 1;
					break;
				}
			}
		}
		
		result = strcasecmp(Argv[i],"-is_log");
		if (!result)
		{
			for (int j=i+1;j<Argc;j++)
			{
				if (isdigit(Argv[j][0]) && j-i <= max_core_num)
				{
					char* ptr;
					int next = strtol(Argv[j], &ptr, 10);
					loggerlist[j-i-1]=next;
				}
				else
				{
					i = j - 1;
					break;
				}
			}
		}

		result = strcasecmp(Argv[i],"-it");
		if (!result)
		{
			char* ptr;
			int next = strtol(Argv[i+1], &ptr, 10);
			iteration=next;
			i++;
		}
		
		result = strcasecmp(Argv[i],"-sw");
		if (!result)
		{
			char* ptr;
			int next = strtol(Argv[i+1], &ptr, 10);
			sleep_window=next;
			i++;
		}
		
		result = strcasecmp(Argv[i],"-msd");
		if (!result)
		{
			char* ptr;
			int next = strtol(Argv[i+1], &ptr, 10);
			min_sleepduration=next;
			i++;
		}
		
		result = strcasecmp(Argv[i],"-display");
		if (!result)
		{
			display_toggle= true;
		}
		
		result = strcasecmp(Argv[i],"-en_all");
		if (!result)
		{
			enable_all_cores= true;
		}
		
		result = strcasecmp(Argv[i],"-ct_log");
		if (!result)
		{
			ct_log= true;
		}
	}
	
	
	print_arguments();
}

/**
  Entry point for Menu App

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS           Erase successfully.
  @retval EFI_DEVICE_ERROR      Failed to program
  @retval EFI_OUT_OF_RESOURCES  Failed to allocate memory for 
                                the buffers
**/

EFI_STATUS
EFIAPI
CPT_LPMTestMain ( IN EFI_HANDLE         ImageHandle,
             IN EFI_SYSTEM_TABLE   *SystemTable)
{
	EFI_STATUS                  Status = EFI_SUCCESS;
	UINTN                       Argc;
	CHAR8                     **Argv = NULL;

	Status = GetCmdLineArgs (ImageHandle, &Argc, &Argv);

	if (EFI_ERROR (Status))
		return Status;

	time_t time_init,time_start,time_end;

	/* CPT Test suite */
	swsys_env_init();

	AsciiPrint("LPM Test Started\n");
	get_lpm_arguements(Argc,Argv);
	sleep_pstat_init();
	print_lpm_stat(&sleep_stat_start);
	if (enable_all_cores)
		initialize_cores();
  
	time_init = swsys_time(0);
	swsys_srand(time_init);
	//test start time
	swsys_info("\nStarting Time Tick test:\n");   
	time_start = swsys_time(0);
	swsys_info("\nStart Time mark: %u\n",time_start-time_init);    
	ThreadSleep(sleep_window/5);
	time_end = swsys_time(0);
	swsys_info("End Time mark: %u\n",time_end-time_init);  
	time_stamp_1ms=(time_end-time_init)/(sleep_window/5);
	swsys_info("1ms time stamp: %u\n\n",time_stamp_1ms);  
  
	time_start = swsys_time(0);
	for (int i=0;i<iteration;i++)
		sleeptest_all_oneatatime();
  
	print_lpm_stat(&sleep_stat_end);
	bool stat=check_lpm_stat();
	time_end = swsys_time(0);
	swsys_info("Total test duration : %u ms\n\n",(time_end-time_start)/time_stamp_1ms); 
	

	if (stat) 
	{
		swsys_error("\nLPM_FAIL, LPM did not happen\n");
		Status = true;
	}else{
		swsys_info("\nLPM_SUCCESS\n");
		swsys_debug("\nLPM_SUCCESS\n");
	}

	return Status;
}

