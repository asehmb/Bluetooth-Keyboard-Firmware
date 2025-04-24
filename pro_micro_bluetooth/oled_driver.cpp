
#include "oled_driver.h"

#ifdef OLED

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);
void oled_setup() {
    Wire.setPins(OLED_SDA, OLED_SCK); // set correct pins to match with pro micro
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
    display.drawBitmap(0,0, bitmap, OLED_WIDTH, OLED_HEIGHT, WHITE);
    oled_update();
}

void oled_display_text(const char* text_to_display){
    display.clearDisplay();
    display.setTextSize(1);      
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(0, 10);
    display.print(F(text_to_display));
    display.display();
}


#endif