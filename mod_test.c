/*
 * mod_image.c
 *
 *  Created on: Jun 14, 2022
 *      Author: jenkins
 */

#include "module.h"
#include "ssd1315/ssd1315_img.h"

typedef enum TEST_ENUM {
    SET_PIXEL,
    GET_PIXEL,
    TEST_COUNT
} Tests;

void show_test(Tests currentTest, SSD1315_IMG* img) {
    uint8_t x, y;

    switch (currentTest) {
    case SET_PIXEL:
        ssd1315_img_clear(&img[0]);
        y = 0;
        for (x = 0; x < 128; ++x) {
            ssd1315_img_set(&img[0], x, y, 1);
            ssd1315_img_set(&img[0], x, 8, 1);
            ssd1315_img_set(&img[0], x, 9, 1);
            ssd1315_img_set(&img[0], x, 10, 1);
            ssd1315_img_set(&img[0], x, 11, 1);
            ssd1315_img_set(&img[0], x, 12, 1);
            ssd1315_img_set(&img[0], x, 13, 1);
            ssd1315_img_set(&img[0], x, 14, 1);
            ssd1315_img_set(&img[0], x, 15, 1);

            if (++y == 8)
                y = 0;
        }
        for (x = 0; x < 128; ++x) {
            ssd1315_img_set(&img[0], x, 11, 0);
            ssd1315_img_set(&img[0], x, 12, 0);
        }
        ssd1315_img_draw(&img[0], 0, 1);
        ssd1315_print(0, 3, "[1] Set Pixel");
        break;
    case GET_PIXEL:
        ssd1315_img_clear(&img[1]);
        for (x = 0; x < 128; ++x) {
            for (y =0; y < 16; ++y) {
                uint8_t pixel = ssd1315_img_get(&img[0], x, y);
                ssd1315_img_set(&img[1], x, y, !pixel);
            }
        }
        ssd1315_img_draw(&img[1], 0, 1);
        ssd1315_print(0, 3, "[2] Get Pixel");
        break;
    }
}

ModRet run_test(void) {
    Tests currentTest = SET_PIXEL;
    SSD1315_IMG_ARRAY(img, 2, 128, 2);

    ssd1315_clear();
    module_print_menu();

    ssd1315_command(SSD1315_SET_ZOOM);
    ssd1315_command(SSD1315_ZOOM_ENABLE);

    show_test(currentTest, img);

    while (1) {
        switch(__even_in_range(gpio_get_button(), 0x7)) {
        case BTN_NONE: break;
        case BTN_LEFT:
            ssd1315_command(SSD1315_SET_ZOOM);
            ssd1315_command(SSD1315_ZOOM_DISABLE);
            return MOD_PREV;
        case BTN_RIGHT:
            ssd1315_command(SSD1315_SET_ZOOM);
            ssd1315_command(SSD1315_ZOOM_DISABLE);
            return MOD_NEXT;
        case BTN_A:
            ++currentTest;
            if (currentTest == TEST_COUNT)
                currentTest = SET_PIXEL;
            show_test(currentTest, img);
            break;
        default: break;
        }
    }
}
