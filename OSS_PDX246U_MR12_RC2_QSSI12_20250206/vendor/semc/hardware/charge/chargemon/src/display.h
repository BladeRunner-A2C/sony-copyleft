/*
 * Copyright (c) 2014 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef __CHARGEMON_DISPLAY_H
#define __CHARGEMON_DISPLAY_H

#include <png.h>
#include <stdbool.h>

#define DISPLAY_ERROR -1
#define DISPLAY_SUCCESS 0

enum {
	DISPLAY_AREA_SCALE = 0,
	DISPLAY_AREA_NUM_V1,
	DISPLAY_AREA_NUM_V2,
	DISPLAY_AREA_NUM_V3,
	DISPLAY_AREA_NUM_V4,
	DISPLAY_AREA_NUM_VALL,
	DISPLAY_AREA_MSG,
	DISPLAY_AREA_MAX
};
#define DISPLAY_AREA_NUM_VCNT 4

int display_init(void);
void display_on(void);
void display_off(void);
void display_set_variable_pos(png_uint_32 width_1, png_uint_32 width_2,
				png_uint_32 width_3, png_uint_32 width_4,
						png_uint_32 height, int area);
void display_set_pos(png_uint_32 width, png_uint_32 height, int area);
void display_clear_buf(int area);
void display_set_buf(void *pixels, int area);
void display_update(void);
void display_close(void);
void display_clear(void);

#endif
