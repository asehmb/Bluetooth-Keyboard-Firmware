
// #include "oled_driver.h"

#include "keypad.h"

int rowPins[] = ROW_PINS; 
int colPins[] = COL_PINS;



// Variables for keypress detection
bool keyPressed[ROWS][COLS] = {false};  // Tracks the state of each key
unsigned long lastDebounceTime = 0;     // Tracks the last debounce time

BLEDis bledis;
BLEHidAdafruit blehid;

bool hasKeyPressed = false;

void setup() {
  oled_setup();
  oled_display_text("Waiting for Serial");
  Serial.begin(115200);
  oled_display_text("Waiting for Serial");
  while (!Serial) {delay(5);}
  oled_display_text("Serial active; Continuing");

  Serial.print("Serial on");
  delay(500);

  Bluefruit.begin();
  Bluefruit.setTxPower(4); 

  bledis.setManufacturer("DepsiPepsi");
  bledis.setModel("NICE NANO");
  bledis.begin();

  blehid.begin(); // Start


  advertise_start();

  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);  // Set rows HIGH initially
    Serial.println(digitalRead(rowPins[i]));
  }

  // Initialize column pins as inputs with pull-ups
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  Serial.print("Setup complete");
}

void advertise_start(){
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  Bluefruit.Advertising.addService(blehid);

  Bluefruit.Advertising.addName();
  

  Bluefruit.Advertising.restartOnDisconnect(true); // auto ad on dsiconnect
  Bluefruit.Advertising.setInterval(32, 244);    // different mode in .625ms units
  Bluefruit.Advertising.setFastTimeout(30);      // fast mode seconds
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

#define BTN_ACTIVE LOW

void scan_keyboard() {




  for (int row = 0; row < ROWS; row++){
    digitalWrite(rowPins[row], LOW);
    for (int col = 0; col < COLS; col++) {
      bool keyState = !digitalRead(colPins[row]);  // Read the key state
      // Check if the key state has changed
      if (keyState != keyPressed[row][col]) {
        // Debounce check
        if (millis() - lastDebounceTime > DEBOUNCE) {
          keyPressed[row][col] = keyState;  // Update the key state
          unsigned key = keymap[row][col];
          if (key != 0) { // not none
            if (keyState) {
              // Key pressed
              // Send the corresponding HID key
              Serial.println("Pressed: ");
              Serial.print(row, col);
              blehid.keyPress(0, key);
              // sendHIDKey(key, keyState);
            } else {
              // Release all keys
              // releaseKey(key);
              blehid.keyRelease();
            } 
          }
          lastDebounceTime = millis();  // Update the debounce time
        }
      }
    }

    digitalWrite(rowPins[row], HIGH);  // Deactivate current row
  }

}

void loop() {
  // Nothing here for now
  // #ifdef OLED
  draw_bitmap(*bitmap_array);

  scan_keyboard();

}
