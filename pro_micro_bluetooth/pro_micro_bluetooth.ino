

#include "keypad.h"

#ifdef OLED
  #include "oled_driver.h"
#endif

#ifndef DEBOUNCE
  #define DEBOUNCE 4
#endif

int rowPins[] = ROW_PINS; 
int colPins[] = COL_PINS;

/*
// left side (top to bottom)
#define D0 (0ul) // P0.06 (TX)
#define D1 (1ul) // P0.08 (RX)
#define D2 (2ul) // P0.17 (SCK)
#define D3 (3ul) // P0.20 (MISO)
#define D4 (4ul) // P0.22 (MOSI)
#define D5 (5ul) // P0.24 (CS)
#define D6 (6ul) // P1.00 (SDA)
#define D7 (7ul) // P0.11 (SCL)
#define D8 (8ul) // P1.04
#define D9 (9ul) // P1.06

// right side (bottom to top)
#define D10 (10ul) // P0.09 (NFC1)
#define D11 (11ul) // P0.10 (NFC2)
#define D12 (12ul) // P1.11
#define D13 (13ul) // P1.13 (SDA1)
#define D14 (14ul) // P1.15 (SCL1)
#define D15 (15ul) // P0.02/AIN0 (A0)
#define D16 (16ul) // P0.29/AIN6 (A1)
#define D17 (17ul) // P0.31/AIN7 (A2)

// extra center pins (left to right)
#define D18 (18ul) // P1.01 (SCK1)
#define D19 (19ul) // P1.02 (MISO1)
#define D20 (20ul) // P1.07 (MOSI1)
*/

// Variables for keypress detection
bool keyPressed[ROWS][COLS] = {false};  // state of each key
unsigned long lastDebounceTime = 0;     // last debounce time

BLEDis bledis;
BLEHidAdafruit blehid;

bool hasKeyPressed = false;

void setup() {
  #ifdef OLED
    oled_setup();
  #endif

  delay(500);

  Bluefruit.begin();
  Bluefruit.setTxPower(4); 

  bledis.setManufacturer(MANUFACTURER);
  bledis.setModel(NAME);
  bledis.begin();

  blehid.begin(); // Start


  advertise_start();

  // ROW -> COL        ROW OUTPUT      COL INPUT
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);  

  }

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

  Bluefruit.setName(NAME);
  Bluefruit.Advertising.addName();
  

  Bluefruit.Advertising.restartOnDisconnect(true); // auto ad on dsiconnect
  Bluefruit.Advertising.setInterval(32, 244);    // different mode in .625ms units
  Bluefruit.Advertising.setFastTimeout(30);      // fast mode seconds
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

#define BTN_ACTIVE LOW

void scan_keyboard() {
  uint8_t key[6] = {0}; // 6 Key
  uint8_t count = 0;


  // ROW -> COL
  for (int row = 0; row < ROWS; row++) {
    digitalWrite(rowPins[row], LOW);  // activate current row

    for (int col = 0; col < COLS; col++) { // check if any of the columns were changed 
      bool currentState = (digitalRead(colPins[col]) == LOW); // Active LOW
      if (currentState != keyPressed[row][col]) {
        if (millis() - lastDebounceTime > DEBOUNCE) {
          keyPressed[row][col] = currentState;
          lastDebounceTime = millis();
        }
      }

      if (keyPressed[row][col] && count < 6) {
        key[count++] = keymap[row][col];
      }
    }

    digitalWrite(rowPins[row], HIGH); // Reset row
  }

  if (count > 0) {
    // send report if there is a pressed key
    blehid.keyboardReport(0, key);
  } else {
    // release keys
    blehid.keyRelease();
  }
}

void loop() {
  #ifdef OLED
    draw_bitmap(*bitmap_array);
  #endif

  scan_keyboard();

}
