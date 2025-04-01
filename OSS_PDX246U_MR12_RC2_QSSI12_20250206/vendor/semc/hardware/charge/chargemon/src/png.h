/*
 * Copyright (C) 2011-2012 Sony Ericsson Mobile Communications AB.
 * Copyright (C) 2012 Sony Mobile Communications AB.
 * All rights, including trade secret rights, reserved.
 */

#ifndef __CHARGEMON_PNG_H
#define __CHARGEMON_PNG_H

struct PNG_LOAD {
	void *pixels;
	int width, height;
};

struct PNG_LOAD *PNG_Load(char *fname);

#endif
