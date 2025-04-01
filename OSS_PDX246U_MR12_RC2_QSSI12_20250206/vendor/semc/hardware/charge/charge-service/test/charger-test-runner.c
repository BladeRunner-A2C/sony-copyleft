/*********************************************************************
 * Copyright (c) 2016 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <sys/types.h>
#include <string.h>
#include <stdio.h>

#include "test_set_temp_state.h"

typedef char * (*TEST_SUITE_FUNC)(char *);

static TEST_SUITE_FUNC suites[] = {
	test_set_temp_state,
	NULL,
};

#define LOG_BUFF_SIZE	4096
static char logs_buff[LOG_BUFF_SIZE];
int main(int argc, char *argv[])
{
	char *pLogBuff = logs_buff;
	TEST_SUITE_FUNC *pSuite = suites;

	printf("charger_test_runner start. -->\n");

	memset(pLogBuff, 0, LOG_BUFF_SIZE);
	while (*pSuite) {
		pLogBuff = (*pSuite)(pLogBuff);
		pSuite++;
	}

	printf("--> charger_test_runner finish.\n");
	return 0;
}

