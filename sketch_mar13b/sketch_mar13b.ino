/*
 * AJ Sehmbi
 * sketch with HID keyboard functionality
 * and oled display support
 */

#include "usb_hid_keys.h"
#include "keypad.h"
#include "oled_driver.h"
#include "hid_report.h"
// #include "encoder.h"

// get pin numbers from header
int rowPins[] = ROW_PINS; 
int colPins[] = COL_PINS;



// Variables for keypress detection
bool keyPressed[ROWS][COLS] = {false};  // Tracks the state of each key
unsigned long lastDebounceTime = 0;     // Tracks the last debounce time


void setup() {
  // Initialize row pins as outputs
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);  // Set rows HIGH initially
  }

  // Initialize column pins as inputs with pull-ups
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  hid_start();  // Initialize the HID keyboard

  // Initialize the OLED display
  #ifdef OLED
    oled_setup();
    draw_bitmap(bitmap_array[0]);
  #endif
}


void scan_keyboard() {
  for (int row = 0; row < ROWS; row++) {
    digitalWrite(rowPins[row], LOW);  // Activate current row

    for (int col = 0; col < COLS; col++) {
      bool keyState = !digitalRead(colPins[col]);  // Read the key state

      // Check if the key state has changed
      if (keyState != keyPressed[row][col]) {
        // Debounce check
        if (millis() - lastDebounceTime > DEBOUNCE) {
          keyPressed[row][col] = keyState;  // Update the key state
          byte key = keymap[row][col];
          if (key != 0) { // not none
            if (keyState) {
              // Key pressed
              // Send the corresponding HID key
              sendHIDKey(key, keyState);
            } else {
              // Release all keys
              releaseKey(key);
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
  scan_keyboard();
  #ifdef OLED
    oled_update();
  #endif
}