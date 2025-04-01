/*********************************************************************
 * Copyright (c) 2016 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <time.h>

#include "miscTA2491.h"
#include "logger/charge-logging/miscta_batt_stats.c"

static char *do_test(char *log_buff, int vol, int s_temp, int e_temp, int interval_time, uint64_t *valified_temp_total_time);

static char *test_001(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 45;
	int e_temp = 47;
	int interval_time = 12;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		12, 12, 12, 0, 0, 12, 0, 0
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_002(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 41;
	int e_temp = 44;
	int interval_time = 12;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 12, 0, 0, 12, 0, 0
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_003(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 40;
	int e_temp = 40;
	int interval_time = 12;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 12, 0, 12, 12, 0, 0
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_004(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 31;
	int e_temp = 39;
	int interval_time = 12;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 0, 0, 12, 0, 0, 0
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_005(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 30;
	int e_temp = 30;
	int interval_time = 12;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 0, 12, 12, 0, 0, 12
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_006(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 20;
	int e_temp = 29;
	int interval_time = 20;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 0, 20, 0, 0, 0, 20
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_007(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 11;
	int e_temp = 19;
	int interval_time = 12;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 0, 12, 0, 0, 0, 0
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_008(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 10;
	int e_temp = 9;
	int interval_time = 12;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 0, 12, 0, 0, 12, 0
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_009(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 31;
	int e_temp = 44;
	int interval_time = 28;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 10, 0, 20, 10, 0, 0
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_010(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 20;
	int e_temp = 44;
	int interval_time = 50;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 10, 22, 22, 10, 0, 22
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_011(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 11;
	int e_temp = 44;
	int interval_time = 68;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 10, 40, 22, 10, 0, 22
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_012(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 44;
	int e_temp = 31;
	int interval_time = 28;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 10, 0, 20, 10, 0, 0
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_013(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 20;
	int e_temp = 39;
	int interval_time = 40;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 0, 22, 20, 0, 0, 22
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_014(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 11;
	int e_temp = 39;
	int interval_time = 58;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 0, 40, 20, 0, 0, 22
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_015(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 44;
	int e_temp = 20;
	int interval_time = 50;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 10, 22, 22, 10, 0, 22
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_016(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 39;
	int e_temp = 20;
	int interval_time = 40;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 0, 22, 20, 0, 0, 22
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_017(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 11;
	int e_temp = 29;
	int interval_time = 38;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 0, 38, 0, 0, 0, 20
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_018(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 44;
	int e_temp = 11;
	int interval_time = 68;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 10, 40, 22, 10, 0, 22
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_019(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 39;
	int e_temp = 11;
	int interval_time = 58;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 0, 40, 20, 0, 0, 22
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_020(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 29;
	int e_temp = 11;
	int interval_time = 38;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 0, 38, 0, 0, 0, 20
	};

	log_buff = do_test(log_buff, vol, s_temp, e_temp, interval_time, valified_temp_total_time);
	*log_buff = 0x20;
	log_buff++;
	return log_buff;
}

static char *test_021(char *log_buff)
{
	int vol = 4250000;
	int s_temp = 28;
	int e_temp_1 = 42;
	int e_temp_2 = 38;
	int interval_time_1 = 30;
	int interval_time_2 = 5;
	uint64_t valified_temp_total_time[MAX_TEMP_TIME_NUM] = {
		0, 0, 9, 6, 25, 9, 0, 6
	};
	time_t check_time = time(NULL);
	int cnt_i;

	memset(&g_params, 0, sizeof(g_params));
	memset(&g_batt_stat, 0, sizeof(g_batt_stat));

	set_temp_state(s_temp, vol, check_time);
	check_time += interval_time_1;
	set_temp_state(e_temp_1, vol, check_time);
	check_time += interval_time_2;
	set_temp_state(e_temp_2, vol, check_time);

	for (cnt_i = 0; cnt_i<MAX_TEMP_TIME_NUM; cnt_i++) {
		if(memcmp(&g_batt_stat.temp_total_time[cnt_i],
			&valified_temp_total_time[cnt_i],
			sizeof(*valified_temp_total_time)) == 0)
			*log_buff = 0x2e;
		else
			*log_buff = 0x46;
		log_buff++;
	}

	*log_buff = 0x20;
	log_buff++;

	return log_buff;
}

char *test_set_temp_state(char *log_buff)
{
	char *temp = log_buff;

	log_buff = test_001(log_buff);
	log_buff = test_002(log_buff);
	log_buff = test_003(log_buff);
	log_buff = test_004(log_buff);
	log_buff = test_005(log_buff);
	log_buff = test_006(log_buff);
	log_buff = test_007(log_buff);
	log_buff = test_008(log_buff);
	log_buff = test_009(log_buff);
	log_buff = test_010(log_buff);
	log_buff = test_011(log_buff);
	log_buff = test_012(log_buff);
	log_buff = test_013(log_buff);
	log_buff = test_014(log_buff);
	log_buff = test_015(log_buff);
	log_buff = test_016(log_buff);
	log_buff = test_017(log_buff);
	log_buff = test_018(log_buff);
	log_buff = test_019(log_buff);
	log_buff = test_020(log_buff);
	log_buff = test_021(log_buff);

	*log_buff = 0;
	printf("%s\n", temp);

	return log_buff;
}

static char *do_test(char *log_buff, int vol, int s_temp, int e_temp, int interval_time, uint64_t *valified_temp_total_time)
{
	time_t check_time = time(NULL);
	int cnt_i;

	memset(&g_params, 0, sizeof(g_params));
	memset(&g_batt_stat, 0, sizeof(g_batt_stat));
	set_temp_state(s_temp, vol, check_time);
	set_temp_state(e_temp, vol, (check_time + interval_time));

	for (cnt_i = 0; cnt_i<MAX_TEMP_TIME_NUM; cnt_i++) {
		if(memcmp(&g_batt_stat.temp_total_time[cnt_i],
			&valified_temp_total_time[cnt_i],
			sizeof(*valified_temp_total_time)) == 0)
			*log_buff = 0x2e;
		else
			*log_buff = 0x46;
		log_buff++;
	}

	return log_buff;
}

