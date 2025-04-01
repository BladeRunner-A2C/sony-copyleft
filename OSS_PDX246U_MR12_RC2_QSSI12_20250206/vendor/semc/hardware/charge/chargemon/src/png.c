/* Copyright (c) 2005, James Jacobsson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 * Neither the name of the organization nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior
 * written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <errno.h>
#include <png.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "png.h"

#define PNG_HEADER_SIZE 8
#define PNG_HEADER_START 0
#define IMAGE_ARRAY_COUNT 4
#define BIT_DEPTHL_8 8
#define BIT_DEPTH_16 16
#define MASK 0xff

struct PNG_LOAD *PNG_Load(char *fname)
{
	FILE *in;
	unsigned char header[PNG_HEADER_SIZE];
	png_bytep *volatile row_pointers = NULL;
	png_uint_32 w = 0, h = 0;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	int bit_depth, color_type, interlace_type;
	int i;
	int number_of_passes;
	struct PNG_LOAD *ret = NULL;

	ret = calloc(1, sizeof(struct PNG_LOAD));
	if (ret == NULL)
		return NULL;

	in = fopen(fname, "rb");
	if (in == NULL) {
		printf("Unable to open %s: %s\n", fname, strerror(errno));
		goto done;
	}
	fread(header, sizeof(unsigned char), sizeof(header), in);

	if (png_sig_cmp(header, PNG_HEADER_START, sizeof(header)) != 0) {
		printf("File is not a PNG\n");
		goto done;
	}

	png_ptr = png_create_read_struct(
		PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		fprintf(stderr,
			"Unable to allocate memory to read the PNG file\n");
		goto done;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		fprintf(stderr,
			"Unable to create image information for PNG file\n");
		goto done;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "Error reading the PNG file.\n");
		goto done;
	}

	png_init_io(png_ptr, in);
	png_set_sig_bytes(png_ptr, BIT_DEPTHL_8);

	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &w, &h, &bit_depth, &color_type,
		&interlace_type, 0, 0);

	/* Set up some transformations to get everything
	 * in our nice ARGB format.
	 */

	/* 8 bits per channel: */
	if (bit_depth == BIT_DEPTH_16)
		png_set_strip_16(png_ptr);
	/* Convert palette to RGB: */
	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr),
		color_type = PNG_COLOR_TYPE_RGB;
	/* Extract 1/2/4bpp to 8bpp: */
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < BIT_DEPTHL_8)
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	/* Convert colorkey to alpha: */
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);
	/* Convert gray to RGB: */
	if (color_type == PNG_COLOR_TYPE_GRAY)
		png_set_gray_to_rgb(png_ptr),
	color_type = PNG_COLOR_TYPE_RGB;

	if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr),
	color_type = PNG_COLOR_TYPE_RGB_ALPHA;

	/* Convert BGR to BGRA */
	if (color_type == PNG_COLOR_TYPE_RGB)
		png_set_add_alpha(png_ptr, MASK, PNG_FILLER_AFTER);

	number_of_passes = png_set_interlace_handling(png_ptr);

	/* Update the info struct. */
	png_read_update_info(png_ptr, info_ptr);

	ret->pixels = (struct PNG_LOAD *)malloc(w * h * IMAGE_ARRAY_COUNT);
	if (!ret->pixels) {
		fprintf(stderr, "Out of memory reading PNG image.\n");
		goto done;
	}

	row_pointers = malloc(h * sizeof(png_bytep));
	if (!row_pointers) {
		fprintf(stderr,
			"Out of memory allocating row pointers PNG image.\n");
		goto done;
	}

	/* Build the array of row pointers. */
	for (i = 0; i < (int)h; i++)
		row_pointers[i] = ((png_bytep)ret->pixels) + (w * 4 * i);

	/* Read the thing. */
	png_read_image(png_ptr, row_pointers);

	/* Read the rest. */
	png_read_end(png_ptr, info_ptr);

done:
	if (png_ptr)
		png_destroy_read_struct(&png_ptr, info_ptr ? &info_ptr : 0, 0);
	if (in)
		fclose(in);
	if (row_pointers)
		free(row_pointers);

	ret->width = w;
	ret->height = h;

	return ret;
}
