/*
 * AJ Sehmbi
 * sketch with HID keyboard functionality
 * and oled display support
 */

#include "keypad.h"

// get pin numbers from header
int rowPins[] = ROW_PINS; 
int colPins[] = COL_PINS;


// Variables for keypress detection
bool keyPressed[ROWS][COLS] = {false};  // Tracks the state of each key
unsigned long lastDebounceTime = 0;     // Tracks the last debounce time


void setup() {
  Serial.begin(9600);
  delay(200);
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

  #ifdef ENCODER
    encoder_setup();
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
              sendHIDKey(key);
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

unsigned long previousMillis = 0;  // Store last time the event was triggered
const long interval = 4;  // The interval at which to run the action (in milliseconds)

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the current time

    scan_keyboard();

  }

  // Oled
  #ifdef OLED
    oled_update();
  #endif

  // encoder
  #ifdef ENCODER        
    int ret_val, click;
    encoder_update(&ret_val, &click);
          if (ret_val == 1) {
        Serial.println("CW");
        sendHIDKey(0xE9);
        delay(100);
        releaseKey(0xE9);
    } else if (ret_val == 2) {
        Serial.println("CCW");
        sendHIDKey(0xEA);
        delay(100);
        releaseKey(0xEA);
    }
  #endif

  delay(4);
    
}