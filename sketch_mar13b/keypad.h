
#ifndef KEYPAD_H
#define KEYPAD_H

#include "usb_hid_keys.h"


#define ROWS 6
#define COLS 4
#define DEBOUNCE 4

#define ROW_PINS {4, 5, 6, 7, 8, 9}
#define COL_PINS {15, 14, 16,10}


#define OLED // needed for oled
#include "oled_driver.h"
#define OLED_WIDTH 128
#define OLED_HEIGHT 32

#define ENCODER_ON
#define ENCODER_DT 20
#define ENCODER_CLK 21
#define ENCODER_SW 19
#define ENCODER_CW KEY_VOLUMEUP // clockwise
#define ENCODER_CCW KEY_VOLUMEDOWN // couter-clockwise


extern const unsigned char* bitmap_array[];

extern int keymap[ROWS][COLS];  // Declare the keymap variable

#endif