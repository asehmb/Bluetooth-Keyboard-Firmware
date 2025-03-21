
#ifndef OLED_H
#define OLED_H

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


void oled_setup();

void oled_update();
void draw_bitmap(const unsigned char *bitmap);


#endif