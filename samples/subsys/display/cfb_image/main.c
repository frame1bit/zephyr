#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/display/cfb.h>
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>

#include "cfb_font_batt.h"
// #include "cfb_font_artha.h"
#include "cfb_font_artha2.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

const struct device *display;

void draw_artha(void)
{
    int err = 0;
    static int x_offset = 0;
    static uint8_t dir = 0;

    if (dir == 0) {
        x_offset = x_offset + 1;
        if (x_offset >= 62) {
            cfb_framebuffer_clear(display, false);
            LOG_INF("Change dir to 1\n");
            dir = 1;
        }
    } else {
        x_offset = x_offset - 1;
        if (x_offset <= 0) {
            cfb_framebuffer_clear(display, false);
            LOG_INF("Change dir to 0\n");
            dir = 0;
        }
    }

    err = cfb_print(display, "C", x_offset, 0);
	if (err) {
		printk("Could not display custom font (err %d)\n", err);
        return;
	}

    cfb_framebuffer_finalize(display);
}

int main(void)
{
    int err = 0;
    display = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

    if (!device_is_ready(display)) {
        printk("Display not ready\n");
        return 1;
    }

    if (cfb_framebuffer_init(display) != 0) {
        printk("CFB init failed\n");
        return 1;
    }

    // cfb_framebuffer_invert(display);  // white on black
    cfb_framebuffer_set_font(display, 1);

    /*err = cfb_print(display, "D", 0, 0);
	if (err) {
		printk("Could not display custom font (err %d)\n", err);
	}*/

    cfb_framebuffer_finalize(display);

    while (1) {
        draw_artha();
        k_sleep(K_MSEC(1));
    }

    return 0;
}
