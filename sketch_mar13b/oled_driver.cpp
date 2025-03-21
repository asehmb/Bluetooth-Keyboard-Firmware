// ssd 1306 over i2c
// 128x32

#include "oled_driver.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 100;  // Update every 100ms

void oled_setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner  
  display.println(F("NUMPAD"));
  display.display();
}

void oled_update() {
  unsigned long currentTime = millis();

  // Check if it's time to update the display
  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;

    // Update the display

    display.display();
  }
}

void draw_bitmap(const unsigned char * bitmap) {
    display.clearDisplay();
    display.drawBitmap(0,0, bitmap, 128, 32, WHITE);
}

