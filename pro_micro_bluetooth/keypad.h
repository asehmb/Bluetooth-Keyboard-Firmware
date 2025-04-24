
#ifndef KEYPAD_H
#define KEYPAD_H

#include <bluefruit.h>

#define MANUFACTURER "asehmb"
#define NAME "DepPad"

#define ROWS 6
#define COLS 4
#define DEBOUNCE 4

#define ROW_PINS {4, 5, 6, 7, 8, 9}
#define COL_PINS {13,12,11,10}


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32



#define OLED // needed for oled
#include "oled_driver.h"
#define OLED_WIDTH 128
#define OLED_HEIGHT 32

#define ENCODER_ON
#define ENCODER_DT 20
#define ENCODER_CLK 21
#define ENCODER_SW 19
#define ENCODER_CW HID_KEY_VOLUME_UP // clockwise
#define ENCODER_CCW HID_KEY_VOLUME_DOWN // couter-clockwise


extern const unsigned char* bitmap_array[];

extern int keymap[ROWS][COLS];  // Declare the keymap variable

#endif