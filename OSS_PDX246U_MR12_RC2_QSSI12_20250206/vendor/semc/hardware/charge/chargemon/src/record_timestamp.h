/*********************************************************************
 * Copyright (c) 2016 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/
#ifndef _RECORD_TIMESTAMP_H_
#define _RECORD_TIMESTAMP_H_

/* Depens-on: record_timestamp.c#reason_table */
typedef enum {
	END_REASON_POWERKEY = 0,
	END_REASON_UNPLUG,
} end_reason;

void record_timestamp_init(void);
void record_timestamp_start(void);
void record_timestamp_end(end_reason reason);

#endif /* _RECORD_TIMESTAMP_ */
