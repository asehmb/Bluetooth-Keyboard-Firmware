
// #include "oled_driver.h"

#include "keypad.h"

void setup() {
  Serial.begin(9600);
  delay(1000);
  oled_setup();

 
}



void loop() {
  // Nothing here for now
  // #ifdef OLED
  draw_bitmap(*bitmap_array);
  // #endif

}
