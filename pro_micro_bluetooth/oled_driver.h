


#ifndef OLED_H
#define OLED_H


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C


void oled_setup();
void oled_display_text(const char* text_to_display);
void draw_bitmap(const unsigned char * bitmap);

#endif