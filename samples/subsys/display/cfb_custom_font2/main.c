/*
 * Copyright (c) 2018 Henrik Brix Andersen <henrik@brixandersen.dk>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/display/cfb.h>
#include <zephyr/sys/printk.h>

#include <stdint.h>
#include <zephyr/logging/log.h>

#define SELECTED_FONT_INDEX  4  // perhaps make this a config parameter

static uint8_t font_width;
static uint8_t font_height;
static uint16_t rows;
static uint8_t ppt;


LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
	const struct device *const display = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	int err;
    uint8_t x_offset = 0;
    uint8_t y_offset;

	LOG_INF("Test cfb custom font!\n");

	if (!device_is_ready(display)) {
		LOG_ERR("Display device not ready\n");
        return 1;
	}

	if (display_set_pixel_format(display, PIXEL_FORMAT_MONO10) != 0) {
		if (display_set_pixel_format(display, PIXEL_FORMAT_MONO01) != 0) {
			LOG_ERR("Failed to set required pixel format");
			return 1;
		}
	}

    err = cfb_framebuffer_init(display);
	if (err) {
		LOG_ERR("Could not initialize framebuffer (err %d)\n", err);
	}

    int num_fonts = cfb_get_numof_fonts(display);

    for (int idx = 0; idx < num_fonts; idx++) {

        cfb_get_font_size(display, idx, &font_width, &font_height);

        LOG_INF("Index[%d] font dimensions %2dx%d",
                idx, font_width, font_height);
    }

    cfb_framebuffer_set_font(display, SELECTED_FONT_INDEX);
    ppt = cfb_get_display_parameter(display, CFB_DISPLAY_PPT);
    rows = cfb_get_display_parameter(display, CFB_DISPLAY_ROWS);

    cfb_framebuffer_invert(display);  // white on black

    LOG_INF("x_res %d, y_res %d, ppt %d, rows %d, cols %d",
            cfb_get_display_parameter(display, CFB_DISPLAY_WIDTH),
            cfb_get_display_parameter(display, CFB_DISPLAY_HEIGHT),
            ppt,
            rows,
            cfb_get_display_parameter(display, CFB_DISPLAY_COLS));

    

    while (1) {

        for (int i=0; i < rows; i++) {

            y_offset = i * ppt;

            switch (i) {
                case 0:
                    cfb_print(display, " average", x_offset, y_offset);
                    break;
                case 1:
                    cfb_print(display, " good",    x_offset, y_offset);
                    break;
                case 2:
                    cfb_print(display, " better",  x_offset, y_offset);
                    break;
                case 3:
                    cfb_print(display, " best",    x_offset, y_offset);
                    break;
                default:
                    break;
            }

            cfb_framebuffer_finalize(display);

            k_sleep(K_MSEC(100));
        }

        cfb_framebuffer_clear(display, false);

        if (x_offset > 50)
            x_offset = 0;
        else
            x_offset += 5;
    }

	return 0;
}
