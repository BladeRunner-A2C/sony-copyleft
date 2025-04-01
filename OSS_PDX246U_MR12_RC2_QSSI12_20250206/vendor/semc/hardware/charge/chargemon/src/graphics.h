/*
 * Copyright (c) 2014 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef __CHARGEMON_GRAPHICS_H
#define __CHARGEMON_GRAPHICS_H

void graphics_disableCharging(void);
void screen_update(
	bool disp_on, int capacity, int charge_sts, int health,
	int phase, bool change, bool animation, bool disp_capacity,
	int smtchg_target_soc);
void screen_close(void);

#endif
