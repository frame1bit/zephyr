#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <lvgl.h>
#include <zephyr/drivers/display.h>

extern lv_font_t pixel_operator;

void main(void)
{
    const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

    if (!device_is_ready(display_dev)) {
        printk("Display not ready\n");
        return;
    }

    lv_init();  // init LVGL (biasanya dilakukan otomatis oleh Zephyr jika CONFIG_LVGL=y)

    // Ambil screen aktif
    lv_obj_t *screen = lv_scr_act();

    // Buat label
    lv_obj_t *label = lv_label_create(screen);
    lv_label_set_text(label, "Teks ini sangat panjang dan akan discroll otomatis oleh LVGL.");
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);  // auto scroll
    lv_obj_set_width(label, 128);  // lebar layar
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);  // tengah layar

    // Set font kecil (pastikan tersedia)
    lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);

    // Tampilkan screen
    lv_disp_load_scr(screen);

    // Jalankan LVGL handler loop
    while (1) {
        lv_timer_handler();
        k_msleep(20);
    }
}
