/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include "charge-service.h"
#include "uevent_processor.h"
#include "log.h"

int create_uevent_socket(int *uevent_sock)
{
	struct sockaddr_nl socknladdr;

	memset(&socknladdr, 0, sizeof(socknladdr));
	socknladdr.nl_family = AF_NETLINK;
	socknladdr.nl_pid = getpid();
	socknladdr.nl_groups = 0xffffffff;

	*uevent_sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
	if (*uevent_sock < 0) {
		LOG("Unable to create uevent socket\n");
		return -EIO;
	}

	if (bind(*uevent_sock, (struct sockaddr *)&socknladdr, sizeof(socknladdr)) < 0) {
		LOG("Unable to bind uevent socket\n");
		close(*uevent_sock);
		return -EIO;
	}

	return 0;
}

void cleanup_uevent_socket(int uevent_sock)
{
	if (uevent_sock >= 0)
		close(uevent_sock);
}

#define POWER_SUPPLY_NAME_TAG       "POWER_SUPPLY_NAME="
#define POWER_SUPPLY_NAME_TAG_LENTH 18 /* strlen(POWER_SUPPLY_NAME_TAG) */

static char *parse_uevent(char *uevent_buf, int recv_cnt)
{
	char *str, *end;
	char *ps_name = NULL;

	str = uevent_buf;
	end = str + recv_cnt;
	/* skip path name */
	str += strlen(str) + 1;

	while (str < end) {
		if (!strncmp(str, POWER_SUPPLY_NAME_TAG, POWER_SUPPLY_NAME_TAG_LENTH)) {
			ps_name = &str[POWER_SUPPLY_NAME_TAG_LENTH];
			break;
		} else {
			str += strlen(str) + 1;
		}
	}

	return ps_name;
}

#define UEVENT_BUF_SIZE (64 * 1024)
#define EVENT_NAME_NONE ""

int wait_for_uevent(int uevent_sock, int timeout_sec, char *event_name)
{
	fd_set fds;
	int recv_cnt;
	char *ps_name;
	int i;
	static char uevent_buf[UEVENT_BUF_SIZE];
	char *available_ps_name[] = {
		"battery",
		"usb",
		"wireless"
	};
	const int num_available_ps_names = sizeof(available_ps_name) / sizeof(char *);
	static struct timeval timeout_tv = {0, 0};
	int rc;

	if (uevent_sock < 0)
		return -1;

	while (1) {
		FD_ZERO(&fds);
		FD_SET(uevent_sock, &fds);

		if (timeout_sec > 0 && timeout_tv.tv_sec == 0 && timeout_tv.tv_usec == 0) {
			timeout_tv.tv_sec = timeout_sec;
			timeout_tv.tv_usec = 0;
		}

		LOGD("--- select in ---\n");
		rc = select(uevent_sock + 1, &fds, NULL, NULL, (timeout_sec > 0) ? &timeout_tv : NULL);
		if (rc < 0) {
			if (errno == EINTR) {
				LOGD("EINTR occurred\n");
				continue;
			} else {
				LOG("select error: '%s'\n", strerror(errno));
				return -1;
			}
		} else if (rc == 0) {
			strlcpy(event_name, EVENT_NAME_NONE, EVENT_NAME_SIZE);
			break;
		}

		if (!FD_ISSET(uevent_sock, &fds))
			continue;

		memset(uevent_buf, 0, sizeof(uevent_buf));
		recv_cnt = recv(uevent_sock, uevent_buf, sizeof(uevent_buf) - 1, 0);
		if (recv_cnt < 0) {
			LOG("recv error: '%s'\n", strerror(errno));
			continue;
		}

		ps_name = parse_uevent(uevent_buf, recv_cnt);
		if (!ps_name)
			continue;

		for (i = 0; i < num_available_ps_names; i++) {
			if (strcmp(ps_name, available_ps_name[i]) == 0)
				break;
		}
		if (i == num_available_ps_names)
			continue;

		strlcpy(event_name, ps_name, EVENT_NAME_SIZE);
		break;
	}

	return 0;
}

bool is_periodic_event(const char *event_name)
{
	return (strcmp(event_name, EVENT_NAME_NONE) == 0);
}
