/*
 * Copyright (c) 2014 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

#include "graphics.h"
#include "display.h"
#include "hw.h"
#include "log.h"
#include "png.h"

#define MAX_STR 255
#define MAX_BATT_CAPACITY 100

#define NUM_OF_ICON_STEP 7

#define SCALE_CHARGE_IDX 0
#define SCALE_NON_CHARGE_IDX (SCALE_CHARGE_IDX + NUM_OF_ICON_STEP)
#define SCALE_NON_CHARGE_HEAT_IDX (SCALE_NON_CHARGE_IDX + NUM_OF_ICON_STEP)
#define SCALE_NON_CHARGE_INVALID_IDX\
				(SCALE_NON_CHARGE_HEAT_IDX + NUM_OF_ICON_STEP)
#define SCALE_CHARGE_WEAK_IDX (SCALE_NON_CHARGE_INVALID_IDX + NUM_OF_ICON_STEP)
#define SCALE_CHARGE_SMTCHG_IDX (SCALE_CHARGE_WEAK_IDX + NUM_OF_ICON_STEP)
#define NUM_IDX (SCALE_CHARGE_SMTCHG_IDX + NUM_OF_ICON_STEP)
#define NUM_PER_IDX (NUM_IDX + 10)
#define MSG_NON_CHARGE_HEAT_IDX (NUM_PER_IDX + 1)
#define MSG_NON_CHARGE_INVALID_IDX (MSG_NON_CHARGE_HEAT_IDX + 1)
#define MSG_CHARGE_WEAK_IDX (MSG_NON_CHARGE_INVALID_IDX + 1)
#define MSG_CHARGE_DISABLED_IDX (MSG_CHARGE_WEAK_IDX + 1)
#define IDX_MAX (MSG_CHARGE_DISABLED_IDX + 1)

const char *pImgFile[] = {
	"scale/ic_battery_charging_icon_01.png",
	"scale/ic_battery_charging_icon_02.png",
	"scale/ic_battery_charging_icon_03.png",
	"scale/ic_battery_charging_icon_04.png",
	"scale/ic_battery_charging_icon_05.png",
	"scale/ic_battery_charging_icon_06.png",
	"scale/ic_battery_charging_icon_07.png",
	"scale/ic_battery_level_icon_01.png",
	"scale/ic_battery_level_icon_02.png",
	"scale/ic_battery_level_icon_03.png",
	"scale/ic_battery_level_icon_04.png",
	"scale/ic_battery_level_icon_05.png",
	"scale/ic_battery_level_icon_06.png",
	"scale/ic_battery_level_icon_07.png",
	"scale/ic_battery_level_heat_icon_01.png",
	"scale/ic_battery_level_heat_icon_02.png",
	"scale/ic_battery_level_heat_icon_03.png",
	"scale/ic_battery_level_heat_icon_04.png",
	"scale/ic_battery_level_heat_icon_05.png",
	"scale/ic_battery_level_heat_icon_06.png",
	"scale/ic_battery_level_heat_icon_07.png",
	"scale/ic_battery_level_invalid_icon_01.png",
	"scale/ic_battery_level_invalid_icon_02.png",
	"scale/ic_battery_level_invalid_icon_03.png",
	"scale/ic_battery_level_invalid_icon_04.png",
	"scale/ic_battery_level_invalid_icon_05.png",
	"scale/ic_battery_level_invalid_icon_06.png",
	"scale/ic_battery_level_invalid_icon_07.png",
	"scale/ic_battery_charging_weak_icon_01.png",
	"scale/ic_battery_charging_weak_icon_02.png",
	"scale/ic_battery_charging_weak_icon_03.png",
	"scale/ic_battery_charging_weak_icon_04.png",
	"scale/ic_battery_charging_weak_icon_05.png",
	"scale/ic_battery_charging_weak_icon_06.png",
	"scale/ic_battery_charging_weak_icon_07.png",
	"scale/ic_battery_level_battery_care_icon_01.png",
	"scale/ic_battery_level_battery_care_icon_02.png",
	"scale/ic_battery_level_battery_care_icon_03.png",
	"scale/ic_battery_level_battery_care_icon_04.png",
	"scale/ic_battery_level_battery_care_icon_05.png",
	"scale/ic_battery_level_battery_care_icon_06.png",
	"scale/ic_battery_level_battery_care_icon_07.png",
	"num/0.png",
	"num/1.png",
	"num/2.png",
	"num/3.png",
	"num/4.png",
	"num/5.png",
	"num/6.png",
	"num/7.png",
	"num/8.png",
	"num/9.png",
	"num/per.png",
	"msg/ic_battery_level_heat_text.png",
	"msg/ic_battery_level_invalid_text.png",
	"msg/ic_battery_charging_weak_text.png",
	"msg/ic_battery_charging_disabled_text.png"
};

static bool is_disable_charging = false;
static bool graphics_initialized = false;

struct image_ll {
	struct PNG_LOAD *png;
	struct image_ll *next;
};

static struct {
	int num;
	struct image_ll *img;
} images;

static struct image_ll *graphics_new_image(void)
{
	struct image_ll *curr;
	static struct image_ll _image_ll;

	if (images.img == NULL) {
		images.img = calloc(1, sizeof(_image_ll));
		return images.img;
	}

	curr = images.img;
	while (curr->next != NULL)
		curr = curr->next;

	curr->next = calloc(1, sizeof(_image_ll));

	return curr->next;
}

static struct image_ll *graphics_get_image(int ndx)
{
	struct image_ll *curr;
	int i = 0;

	if ((ndx < 0) || (ndx >= IDX_MAX))
		return NULL;

	curr = images.img;
	while (i < ndx) {
		curr = curr->next;
		i++;
	}

	return curr;
}

static void graphics_init_image(void)
{
	FILE *test;
	int i = 0;
	char tmpStr[MAX_STR + 1];

	for (i = 0; i < IDX_MAX; i++) {
		snprintf(tmpStr, sizeof(tmpStr),
			"%s/%s", PATH_IMAGE_DATA, pImgFile[i]);
		LOGD("Trying to open %s\n", tmpStr);
		test = fopen(tmpStr, "rb");
		if (test != NULL) {
			struct image_ll *new;
			fclose(test);
			new = graphics_new_image();
			new->png = PNG_Load(tmpStr);
			LOGD(" new->png = %p\n", new->png);
		}
	}
}

static int graphics_init(void)
{
	struct image_ll *img;
	if (display_init() < DISPLAY_SUCCESS)
		return DISPLAY_ERROR;

	graphics_init_image();

	/* Calcurate battery icon's position*/
	img = graphics_get_image(SCALE_CHARGE_IDX);
	if (img)
		display_set_pos(img->png->width, img->png->height,
							DISPLAY_AREA_SCALE);

	/* Calcurate message's position*/
	img = graphics_get_image(MSG_NON_CHARGE_HEAT_IDX);
	if (img)
		display_set_pos(img->png->width, img->png->height,
							DISPLAY_AREA_MSG);
	display_on();
	return 0;
}

static void graphics_init_image_from_capacity(int capacity,
						struct image_ll *img[])
{
	if (capacity < 10) {
		img[0] = graphics_get_image(NUM_IDX + capacity);
		img[1] = graphics_get_image(NUM_PER_IDX);
		img[2] = NULL;
		img[3] = NULL;
	} else if (capacity < MAX_BATT_CAPACITY) {
		img[0] = graphics_get_image(NUM_IDX + (capacity / 10) % 10);
		img[1] = graphics_get_image(NUM_IDX + capacity % 10);
		img[2] = graphics_get_image(NUM_PER_IDX);
		img[3] = NULL;
	} else {
		img[0] = graphics_get_image(NUM_IDX + 1);
		img[1] = graphics_get_image(NUM_IDX);
		img[2] = graphics_get_image(NUM_IDX);
		img[3] = graphics_get_image(NUM_PER_IDX);
	}
}

static void graphics_set_buf_of_capacity(struct image_ll *img[])
{
	int set_width[DISPLAY_AREA_NUM_VCNT];
	int set_height = 0;
	int i;

	display_clear_buf(DISPLAY_AREA_NUM_VALL);

	if (img[0])
		set_height = img[0]->png->height;

	for (i = 0; i < DISPLAY_AREA_NUM_VCNT; i++) {
		if (img[i])
			set_width[i] = img[i]->png->width;
		else
			set_width[i] = 0;
	}

	display_set_variable_pos(set_width[0], set_width[1], set_width[2],
			set_width[3], set_height, DISPLAY_AREA_NUM_VALL);

	for (i = 0; i < DISPLAY_AREA_NUM_VCNT; i++) {
		if (img[i])
			display_set_buf(img[i]->png->pixels,
					DISPLAY_AREA_NUM_V1 + i);
	}
}

static void graphics_update(int capacity, int charge, int health, int invalid,
			int weak, int phase, bool change, bool animation,
			bool disp_capacity, int smtchg_target_soc)
{
	struct image_ll *num_img[DISPLAY_AREA_NUM_VCNT];
	struct image_ll *img;
	int scaleimgIndex = -1;
	int scaleimgIndexStep = 0;
	int msgimgIndex = -1;
	int scale_current = 0;
	static int saved_capacity = -1;

	if (capacity > MAX_BATT_CAPACITY)
		return;

	/* select a icon type */
	if (charge != CHARGING && charge != FULL) {
		if (is_disable_charging) {
			scaleimgIndex = SCALE_NON_CHARGE_IDX;
			msgimgIndex = MSG_CHARGE_DISABLED_IDX;
		} else if (health == OVERHEAT) {
			scaleimgIndex = SCALE_NON_CHARGE_IDX;
		} else if (invalid) {
			scaleimgIndex = SCALE_NON_CHARGE_INVALID_IDX;
			msgimgIndex = MSG_NON_CHARGE_INVALID_IDX;
		} else {
			scaleimgIndex = SCALE_NON_CHARGE_IDX;
		}
	} else if (weak) {
		scaleimgIndex = SCALE_CHARGE_WEAK_IDX;
		msgimgIndex = MSG_CHARGE_WEAK_IDX;
	} else if (smtchg_target_soc != SMTCHG_TARGET_SOC_NONE) {
		scaleimgIndex = SCALE_CHARGE_SMTCHG_IDX;
	} else {
		scaleimgIndex = SCALE_CHARGE_IDX;
	}

	/* decide several steps from capacity */
	if (smtchg_target_soc != SMTCHG_TARGET_SOC_NONE) {
		if (capacity < 67) {
			/* 0% ~ 66% */
			scale_current = (capacity > 0 ? (capacity * (NUM_OF_ICON_STEP - 1)) / MAX_BATT_CAPACITY : 0);
		} else if (capacity < smtchg_target_soc) {
			/* 67% ~ (smtchg_target_soc - 1) */
			scale_current = 4;
		} else {
			/* smtchg_target_soc ~ 100 */
			scale_current = 5;
		}
	} else {
		scale_current = (capacity > 0 ? (capacity * (NUM_OF_ICON_STEP - 1)) / MAX_BATT_CAPACITY : 0);
	}

	scaleimgIndex += scale_current;

	/* determine the increasing value during animation */
	if (animation && charge == CHARGING && charge != FULL && !weak) {
		scaleimgIndexStep = phase % (NUM_OF_ICON_STEP - scale_current);
		if (smtchg_target_soc == SMTCHG_TARGET_SOC_NONE &&
			scaleimgIndexStep + scaleimgIndex >=
			NUM_OF_ICON_STEP - 1) {
			scaleimgIndexStep = NUM_OF_ICON_STEP - 1
						- scaleimgIndex;
		}
	}

	if (change || animation) {
		/* display the battery icon */
		img = graphics_get_image(scaleimgIndex + scaleimgIndexStep);
		if (img)
			display_set_buf(img->png->pixels,
					DISPLAY_AREA_SCALE);

		if (change) {
			if (disp_capacity) {
				saved_capacity = capacity;
			}

			/* display the text message */
			if (msgimgIndex == -1) {
				display_clear_buf(DISPLAY_AREA_MSG);
			} else {
				img = graphics_get_image(msgimgIndex);
				if (img)
					display_set_buf(img->png->pixels,
							DISPLAY_AREA_MSG);
			}
		}
		if (saved_capacity >= 0) {
			/* determine positions of capacity images
			and display them */
			graphics_init_image_from_capacity(saved_capacity, num_img);
			graphics_set_buf_of_capacity(num_img);
		}
		display_update();
	}
}

void graphics_disableCharging(void)
{
	is_disable_charging = true;
}

void screen_update(
	bool disp_on, int capacity, int charge_sts, int health,
	int phase, bool change, bool animation, bool disp_capacity,
	int smtchg_target_soc)
{
	static bool prev_disp_on;

	if (!graphics_initialized) {
		if (graphics_init() < DISPLAY_SUCCESS) {
			LOG("graphics_init() failed\n");
			return;
		}
		prev_disp_on = true;
		graphics_initialized = true;
	}

	if (disp_on) {
		if (!prev_disp_on)
			display_on();

		graphics_update(capacity, charge_sts, health, 0, 0,
			phase, change, animation, disp_capacity, smtchg_target_soc);
	} else {
		if (prev_disp_on)
			display_off();
	}

	prev_disp_on = disp_on;
}

static void free_mem(void)
{
	struct image_ll *curr;
	struct image_ll *next;

	curr = images.img;
	while (curr) {
		next = curr->next;
		if (curr->png) {
			free(curr->png->pixels);
			free(curr->png);
		}
		free(curr);
		curr = next;
	}
}

void screen_close(void)
{
	if (!graphics_initialized)
		return;

	display_off();
	display_close();
	free_mem();
}
