/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/
#ifndef _UEVENT_PROCESSOR_H_
#define _UEVENT_PROCESSOR_H_

#define EVENT_NAME_SIZE 16

int create_uevent_socket(int *uevent_sock);
void cleanup_uevent_socket(int uevent_sock);
int wait_for_uevent(int uevent_sock, int timeout_sec, char *event_name);
bool is_periodic_event(const char *event_name);

#endif /* _UEVENT_PROCESSOR_H_ */
