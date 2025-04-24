


#ifndef OLED_H
#define OLED_H


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "keypad.h"

#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

#ifndef OLED_SDA
  #define OLED_SDA 2
#endif

#ifndef OLED_SCK
  #define OLED_SCK 3
#endif

void oled_setup();
void oled_display_text(const char* text_to_display);
void draw_bitmap(const unsigned char * bitmap);

#endif