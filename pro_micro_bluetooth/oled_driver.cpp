
#include "oled_driver.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void oled_setup() {
    Wire.setPins(2, 3); // set correct pins to match with pro micro
    Wire.begin();  
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        for (;;);
    }

    display.clearDisplay();
    display.setTextSize(1);      
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(0, 10);
    display.print(F("LEBRONNNN!"));
    display.display();
}

static unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 100;  // Update every 100ms

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
    oled_update();
}
