/*
 * Copyright (c) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <errno.h>
#include <fcntl.h>
#include <linux/kd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "display.h"
#include "png.h"
#include "log.h"

#include <drm_fourcc.h>
#include <xf86drm.h>
#include <xf86drmMode.h>

#define TO_BIT_32 32
#define ALIGN(x, align) (((x) + ((align)-1)) & ~((align)-1))
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define PIXELS_WIDTH_BYTE 4

struct surface {
	uint32_t fb_id;
	void *data;
	uint32_t handle;
	uint32_t format;
};

struct drm {
	/** drm */
	int drm_fd;
	uint32_t width;
	uint32_t height;
	uint32_t size;
	uint32_t pitches_width;
	uint32_t pixel_bytes;
	uint32_t row_bytes;
	struct surface *front;
	struct surface *back;
	drmModeConnector *connector;
	drmModeCrtc *crtc;
	/** resources */
	void *res_buf;
};

struct drm *drm;

struct area_pos {
	unsigned int x_start_pos;
	unsigned int y_start_pos;
	unsigned int width;
	unsigned int height;
};

static struct area_pos h_area_pos[DISPLAY_AREA_MAX];

/* crct/encoder/connector function based on minui */
static drmModeConnector* find_first_connected_connector(int fd, drmModeRes* resources)
{
	int i;
	drmModeConnector* connector;
	for (i = 0; i < resources->count_connectors; i++) {
		connector = drmModeGetConnector(fd, resources->connectors[i]);
		if (connector) {
			if ((connector->count_modes > 0) &&
				(connector->connection == DRM_MODE_CONNECTED))
				return connector;
			drmModeFreeConnector(connector);
		}
	}
	return NULL;
}

static drmModeCrtc* find_crtc_for_connector(int fd, drmModeRes* resources,
						drmModeConnector* connector)
{
	drmModeEncoder* encoder;
	int32_t crtc;
	int i, j;

	if (connector->encoder_id) {
		encoder = drmModeGetEncoder(fd, connector->encoder_id);
	} else {
		encoder = NULL;
	}

	if (encoder && encoder->crtc_id) {
		crtc = encoder->crtc_id;
		drmModeFreeEncoder(encoder);
		return drmModeGetCrtc(fd, crtc);
	}
	crtc = -1;
	for (i = 0; i < connector->count_encoders; i++) {
		encoder = drmModeGetEncoder(fd, connector->encoders[i]);
		if (encoder) {
			for (j = 0; j < resources->count_crtcs; j++) {
				if (!(encoder->possible_crtcs & (1 << j)))
					continue;
				crtc = resources->crtcs[j];
				break;
			}
			if (crtc >= 0) {
				drmModeFreeEncoder(encoder);
				return drmModeGetCrtc(fd, crtc);
			}
		}
	}
	return NULL;
}

static void disable_non_maincrtcs(int fd, drmModeRes* resources, drmModeCrtc* main_crtc)
{
	drmModeConnector* connector;
	drmModeCrtc* crtc;
	int i;

	for (i = 0; i < resources->count_connectors; i++) {
		connector = drmModeGetConnector(fd, resources->connectors[i]);
		crtc = find_crtc_for_connector(fd, resources, connector);
		if (crtc->crtc_id != main_crtc->crtc_id) {
			drmModeSetCrtc(fd, crtc->crtc_id, 0, 0, 0, NULL, 0, NULL);
		}
		drmModeFreeCrtc(crtc);
		drmModeFreeConnector(connector);
	}
}

static drmModeConnector* find_used_connector_by_type(int fd, drmModeRes* resources, unsigned type)
{
	int i;
	drmModeConnector* connector;

	for (i = 0; i < resources->count_connectors; i++) {
		connector = drmModeGetConnector(fd, resources->connectors[i]);
		if (connector) {
			if ((connector->connector_type == type) &&
						(connector->connection == DRM_MODE_CONNECTED) &&
				(connector->count_modes > 0)) {
				return connector;
			}
		}
	}
		return NULL;
}

static drmModeConnector* find_main_monitor(int fd, drmModeRes* resources, uint32_t* mode_index)
{
	static unsigned connectorpriority[] = {
		DRM_MODE_CONNECTOR_LVDS,
		DRM_MODE_CONNECTOR_eDP,
		DRM_MODE_CONNECTOR_DSI,
	};
	drmModeConnector* connector;
	unsigned i = 0;
	int modes;

	do {
		connector = find_used_connector_by_type
				(fd, resources, connectorpriority[i]);
		i++;
	} while (!connector && i < ARRAY_SIZE(connectorpriority));

	if (!connector) {
		connector = find_first_connected_connector(fd, resources);
	}
	if (!connector)
		return NULL;

	*mode_index = 0;
	for (modes = 0; modes < connector->count_modes; modes++) {
		if (connector->modes[modes].type & DRM_MODE_TYPE_PREFERRED) {
			*mode_index = modes;
			break;
		}
	}
	return connector;
}

static void drm_destroy_surface(struct surface *surface)
{
	int ret;
	struct drm_gem_close gem_close;

	if (surface->data) {
		munmap(surface->data, drm->row_bytes * drm->height);
	}
	if (surface->fb_id) {
		ret = drmModeRmFB(drm->drm_fd, surface->fb_id);
		if (ret) {
			LOG("drmModeRmFB failed ret=%d\n", ret);
		}
	}
	if (surface->handle) {
		gem_close.handle = surface->handle;
		ret = drmIoctl(drm->drm_fd, DRM_IOCTL_GEM_CLOSE, &gem_close);
		if (ret) {
			LOG("DRM_IOCTL_GEM_CLOSE failed ret=%d\n", ret);
		}
	}
}

static int drm_create_surface(struct surface *surface)
{
	struct drm_mode_create_dumb create_dumb;
	struct drm_mode_map_dumb map_dumb;
	uint32_t handles[4], pitches[4], offsets[4];
	int ret;

	surface->format = DRM_FORMAT_ABGR8888;
	create_dumb.height = drm->height;
	create_dumb.width = drm->width;
	create_dumb.bpp = TO_BIT_32;
	create_dumb.flags = 0;

	ret = drmIoctl(drm->drm_fd, DRM_IOCTL_MODE_CREATE_DUMB, &create_dumb);
	if (ret) {
		LOG("DRM_IOCTL_MODE_CREATE_DUMB failed ret=%d\n", ret);
		drm_destroy_surface(surface);
		return DISPLAY_ERROR;
	}

	drm->size = (int)create_dumb.size;
	drm->pitches_width = create_dumb.pitch/4;
	surface->handle = create_dumb.handle;

	handles[0] = surface->handle;
	pitches[0] = create_dumb.pitch;
	offsets[0] = 0;

	ret = drmModeAddFB2(drm->drm_fd, pitches[0]/4, drm->height,
				surface->format, handles, pitches, offsets,
				&surface->fb_id, 0);
	if (ret) {
		LOG("drmModeAddFB2 failed ret=%d\n", ret);
		drm_destroy_surface(surface);
		return DISPLAY_ERROR;
	}

	map_dumb.handle = create_dumb.handle;
	ret = drmIoctl(drm->drm_fd, DRM_IOCTL_MODE_MAP_DUMB, &map_dumb);
	if (ret) {
		LOG("DRM_IOCTL_MODE_MAP_DUMB failed ret=%d\n", ret);
		drm_destroy_surface(surface);
		return DISPLAY_ERROR;
	}

	drm->row_bytes = create_dumb.pitch;
	drm->pixel_bytes = create_dumb.bpp / 8;
	surface->data = mmap(0, drm->size,
				PROT_READ | PROT_WRITE, MAP_SHARED,
				drm->drm_fd, map_dumb.offset);
	if (surface->data == MAP_FAILED) {
		drm_destroy_surface(surface);
		return DISPLAY_ERROR;
	}

	return DISPLAY_SUCCESS;
}

static void drm_clear_surface(void)
{
	memset(drm->front->data, 0x00, drm->size);
	memset(drm->back->data, 0x00, drm->size);
}

static void drm_swap_surface(void)
{
	struct surface *temp;

	temp = drm->back;
	drm->back = drm->front;
	drm->front = temp;
}

static int drm_enable_crtc(void)
{
	int ret;

	ret = drmModeSetCrtc(drm->drm_fd, drm->crtc->crtc_id,
			drm->back->fb_id,
			0, 0, &drm->connector->connector_id,
			1,  // connector_count
			&drm->crtc->mode);

	return ret;
}

static void drm_disable_crtc(void)
{

 	drmModeSetCrtc(drm->drm_fd, drm->crtc->crtc_id,
		0,         // fb_id
		0, 0,      // x,y
		NULL,   // connectors
		0,         // connector_count
		NULL);  // mode
}

static int drm_release(void) {

	if (!drm->res_buf)
		free(drm->res_buf);
	if (!drm->drm_fd)
		close(drm->drm_fd);
	if (!drm->back)
		free(drm->back);
	if (!drm->front)
		free(drm->front);
	if (!drm)
		free(drm);

	return DISPLAY_SUCCESS;
}

static int drm_init(void)
{
	char* dev_name;
	int ret;
	uint64_t cap = 0;
	uint32_t selected_mode;
	unsigned i;
	drmModeRes* res = NULL;

	drm = malloc(sizeof(struct drm));
	if (!drm)
		return DISPLAY_ERROR;
	drm->front = malloc(sizeof(struct surface));
	if (!drm->front) {
		drm_release();
		return DISPLAY_ERROR;
	}
	drm->back = malloc(sizeof(struct surface));
	if (!drm->back) {
		drm_release();
		return DISPLAY_ERROR;
	}

	for (i = 0; i < DRM_MAX_MINOR; i++) {
		ret = asprintf(&dev_name, DRM_DEV_NAME, DRM_DIR_NAME, i);
		if (ret < 0)
			continue;
		drm->drm_fd = open(dev_name, O_RDWR, 0);
		free(dev_name);
		if (drm->drm_fd < 0)
			continue;
		ret = drmGetCap(drm->drm_fd, DRM_CAP_DUMB_BUFFER, &cap);
		if (ret || cap == 0) {
      			close(drm->drm_fd);
			continue;
		}

		res = drmModeGetResources(drm->drm_fd);
		if (!res) {
			close(drm->drm_fd);
			continue;
		}
		if (res->count_crtcs > 0 && res->count_connectors > 0) {
			if (find_first_connected_connector(drm->drm_fd, res))
				break;
		}

		drmModeFreeResources(res);
		close(drm->drm_fd);
		res = NULL;
	}
	if (drm->drm_fd < 0 || res == NULL) {
		LOG("cannot find/open a drm device");
		drm_release();
		return DISPLAY_ERROR;
	}

	drm->connector = find_main_monitor(drm->drm_fd, res, &selected_mode);
	if (!drm->connector) {
		LOG("connector not found\n");
		drmModeFreeResources(res);
		drm_release();
		return DISPLAY_ERROR;
	}

	drm->crtc = find_crtc_for_connector(drm->drm_fd, res, drm->connector);

	if (!drm->crtc) {
		LOG("crtc not found\n");
		drmModeFreeResources(res);
		drm_release();
		return DISPLAY_ERROR;
	}

	disable_non_maincrtcs(drm->drm_fd, res, drm->crtc);
	drm->crtc->mode = drm->connector->modes[selected_mode];

	drm->width = drm->crtc->mode.hdisplay;
	drm->height = drm->crtc->mode.vdisplay;
	drmModeFreeResources(res);

	ret = drm_create_surface(drm->front);
	if (ret) {
		drm_release();
		return DISPLAY_ERROR;
	}
	ret = drm_create_surface(drm->back);
	if (ret) {
		drm_release();
		return DISPLAY_ERROR;
	}

	drm->res_buf = NULL;
	drm->res_buf = malloc(drm->size);
	if (!drm->res_buf) {
		drm_release();
		return DISPLAY_ERROR;
	}

	return DISPLAY_SUCCESS;
}

int display_init(void)
{
	int result;

	result = drm_init();
	if (result != DISPLAY_SUCCESS)
		return result;

	display_clear();
	drm_clear_surface();

	return DISPLAY_SUCCESS;
}

void display_on(void)
{
	drm_enable_crtc();
}

void display_off(void)
{
	display_clear();
	drm_clear_surface();
	drm_disable_crtc();
}

void display_clear(void)
{
	memset(drm->res_buf, 0, drm->size);
}

void display_set_variable_pos(png_uint_32 width_1, png_uint_32 width_2,
				png_uint_32 width_3, png_uint_32 width_4,
						png_uint_32 height, int area)
{
	png_uint_32 width_sum;
	png_uint_32 y_start_pos;

	switch (area) {
	case DISPLAY_AREA_NUM_VALL:
		width_sum = width_1 + width_2 + width_3 + width_4;

		if (width_sum > drm->pitches_width)
			return;

		y_start_pos = h_area_pos[DISPLAY_AREA_SCALE].y_start_pos
								- height;
		if (y_start_pos + height > drm->height)
			return;

		h_area_pos[DISPLAY_AREA_NUM_V1].x_start_pos =
						(drm->pitches_width - width_sum) / 2;
		h_area_pos[DISPLAY_AREA_NUM_V2].x_start_pos =
			h_area_pos[DISPLAY_AREA_NUM_V1].x_start_pos + width_1;
		h_area_pos[DISPLAY_AREA_NUM_V3].x_start_pos =
			h_area_pos[DISPLAY_AREA_NUM_V2].x_start_pos + width_2;
		h_area_pos[DISPLAY_AREA_NUM_V4].x_start_pos =
			h_area_pos[DISPLAY_AREA_NUM_V3].x_start_pos + width_3;

		h_area_pos[DISPLAY_AREA_NUM_V1].y_start_pos = y_start_pos;
		h_area_pos[DISPLAY_AREA_NUM_V2].y_start_pos = y_start_pos;
		h_area_pos[DISPLAY_AREA_NUM_V3].y_start_pos = y_start_pos;
		h_area_pos[DISPLAY_AREA_NUM_V4].y_start_pos = y_start_pos;

		h_area_pos[DISPLAY_AREA_NUM_V1].width = width_1;
		h_area_pos[DISPLAY_AREA_NUM_V2].width = width_2;
		h_area_pos[DISPLAY_AREA_NUM_V3].width = width_3;
		h_area_pos[DISPLAY_AREA_NUM_V4].width = width_4;

		h_area_pos[DISPLAY_AREA_NUM_V1].height = height;
		h_area_pos[DISPLAY_AREA_NUM_V2].height = height;
		h_area_pos[DISPLAY_AREA_NUM_V3].height = height;
		h_area_pos[DISPLAY_AREA_NUM_V4].height = height;

		h_area_pos[DISPLAY_AREA_NUM_VALL].x_start_pos =
				h_area_pos[DISPLAY_AREA_NUM_V1].x_start_pos;
		h_area_pos[DISPLAY_AREA_NUM_VALL].y_start_pos = y_start_pos;
		h_area_pos[DISPLAY_AREA_NUM_VALL].width = width_sum;
		h_area_pos[DISPLAY_AREA_NUM_VALL].height = height;
		break;
	default:
		break;
	}
}

void display_set_pos(png_uint_32 width, png_uint_32 height, int area)
{
	unsigned int x_start_pos, y_start_pos = 0;

	if (area >= DISPLAY_AREA_MAX)
		return;

	if (area != DISPLAY_AREA_SCALE &&
		h_area_pos[DISPLAY_AREA_SCALE].y_start_pos == 0)
		return;

	switch (area) {
	case DISPLAY_AREA_SCALE:
		x_start_pos = (drm->pitches_width - width) / 2;

		y_start_pos = (drm->height - height) / 2;
		if (x_start_pos + width > drm->pitches_width ||
			y_start_pos + height > drm->height)
			return;

		h_area_pos[area].x_start_pos = x_start_pos;
		h_area_pos[area].y_start_pos = y_start_pos;
		break;
	case DISPLAY_AREA_MSG:
		x_start_pos = (drm->pitches_width - width) / 2;

		y_start_pos = h_area_pos[DISPLAY_AREA_SCALE].y_start_pos +
					h_area_pos[DISPLAY_AREA_SCALE].height;
		if (x_start_pos + width > drm->pitches_width ||
			y_start_pos + height > drm->height)
			return;

		h_area_pos[area].x_start_pos = x_start_pos;
		h_area_pos[area].y_start_pos = y_start_pos;
		break;
	default:
		return;
	}

	h_area_pos[area].width = width;
	h_area_pos[area].height = height;
}

void display_clear_buf(int area)
{
	unsigned int y;
	unsigned int x_start_pos = 0;
	unsigned int y_start_pos = 0;
	unsigned int width = 0;
	unsigned int height = 0;


	if (area >= DISPLAY_AREA_MAX ||
		h_area_pos[area].width <= 0 ||
		h_area_pos[area].height <= 0 ||
		h_area_pos[area].x_start_pos +
		h_area_pos[area].width > drm->pitches_width ||
		h_area_pos[area].y_start_pos +
		h_area_pos[area].height > drm->height
		)
		return;

	x_start_pos = h_area_pos[area].x_start_pos;
	y_start_pos = h_area_pos[area].y_start_pos;
	width = h_area_pos[area].width;
	height = h_area_pos[area].height;

	for (y = 0; y < height; y++) {
		unsigned int start_pos = (x_start_pos * PIXELS_WIDTH_BYTE) +
			(drm->pitches_width * (y_start_pos + y)) * PIXELS_WIDTH_BYTE;

		memset((char *)drm->res_buf + start_pos, 0, width * PIXELS_WIDTH_BYTE);
	}
}

void display_set_buf(void *pixels, int area)
{
	unsigned int y;
	unsigned int x_start_pos = 0;
	unsigned int y_start_pos = 0;
	unsigned int width = 0;
	unsigned int height = 0;


	if (area >= DISPLAY_AREA_MAX ||
		h_area_pos[area].width <= 0 ||
		h_area_pos[area].height <= 0 ||
		h_area_pos[area].x_start_pos +
		h_area_pos[area].width > drm->pitches_width ||
		h_area_pos[area].y_start_pos +
		h_area_pos[area].height > drm->height
		)
		return;


	x_start_pos = h_area_pos[area].x_start_pos;
	y_start_pos = h_area_pos[area].y_start_pos;
	width = h_area_pos[area].width;
	height = h_area_pos[area].height;

	for (y = 0; y < height; y++) {
		unsigned int start_pos = (x_start_pos * PIXELS_WIDTH_BYTE) +
			(drm->pitches_width * (y_start_pos + y)) * PIXELS_WIDTH_BYTE;

		unsigned int line_pos = (width * PIXELS_WIDTH_BYTE * y);

		memcpy((char *)drm->res_buf + start_pos,
			((char *)pixels + line_pos),
			width * PIXELS_WIDTH_BYTE);
	}
}

void display_update(void)
{
	int ret;

	memcpy((char *)drm->back->data, drm->res_buf, drm->size); /* blit */
	ret = drmModePageFlip(drm->drm_fd, drm->crtc->crtc_id,
		drm->back->fb_id, 0, NULL);
	if (ret)
		LOG("send frame faild\n");
	drm_swap_surface();
}

void display_close(void)
{
	drm_release();
}
