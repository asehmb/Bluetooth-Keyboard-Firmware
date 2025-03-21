
#ifndef OLED_H
#define OLED_H


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


#define OLED_RESET    -1 // Reset pin # sahred with arduino reset
#define SCREEN_ADDRESS 0x3C


void oled_setup();
void oled_update();
void draw_bitmap(const unsigned char *bitmap);



#endif