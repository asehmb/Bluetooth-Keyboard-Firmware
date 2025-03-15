/*
 * AJ Sehmbi
 * sketch with HID keyboard functionality
 */



#include <Arduino.h>
#include <HID.h>
#include "usb_hid_keys.h"
#include "keypad.h"


// Pin definitions
int rowPins[ROWS] = {4, 5, 6, 7, 8, 9};
int colPins[COLS] = {10, 16, 14, 15};


// HID report descriptor for a keyboard
static const uint8_t _hidReportDescriptor[] PROGMEM = {
  0x05, 0x01,        // Usage Page (Generic Desktop)
  0x09, 0x06,        // Usage (Keyboard)
  0xA1, 0x01,        // Collection (Application)
  0x85, 0x01,        //   Report ID (1)
  0x75, 0x01,        //   Report Size (1)
  0x95, 0x08,        //   Report Count (8)
  0x05, 0x07,        //   Usage Page (Key Codes)
  0x19, 0xE0,        //   Usage Minimum (224)
  0x29, 0xE7,        //   Usage Maximum (231)
  0x15, 0x00,        //   Logical Minimum (0)
  0x25, 0x01,        //   Logical Maximum (1)
  0x81, 0x02,        //   Input (Data, Variable, Absolute)
  0x95, 0x01,        //   Report Count (1)
  0x75, 0x08,        //   Report Size (8)
  0x81, 0x01,        //   Input (Constant)
  0x95, 0x05,        //   Report Count (5)
  0x75, 0x01,        //   Report Size (1)
  0x05, 0x08,        //   Usage Page (LEDs)
  0x19, 0x01,        //   Usage Minimum (1)
  0x29, 0x05,        //   Usage Maximum (5)
  0x91, 0x02,        //   Output (Data, Variable, Absolute)
  0x95, 0x01,        //   Report Count (1)
  0x75, 0x03,        //   Report Size (3)
  0x91, 0x01,        //   Output (Constant)
  0x95, 0x06,        //   Report Count (6)
  0x75, 0x08,        //   Report Size (8)
  0x15, 0x00,        //   Logical Minimum (0)
  0x25, 0x65,        //   Logical Maximum (101)
  0x05, 0x07,        //   Usage Page (Key Codes)
  0x19, 0x00,        //   Usage Minimum (0)
  0x29, 0x65,        //   Usage Maximum (101)
  0x81, 0x00,        //   Input (Data, Array)
  0xC0               // End Collection
};

// HID report structure for a keyboard
struct {
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} hidReport;

// Variables for keypress detection
bool keyPressed[ROWS][COLS] = {false};  // Tracks the state of each key
unsigned long lastDebounceTime = 0;     // Tracks the last debounce time

// Function to send the HID keypress report
void sendHIDKey(byte key) {
  // Create the HID report for the keyboard
  hidReport.modifiers = 0; // No modifier keys (Shift, Ctrl, etc.)
  hidReport.keys[0] = key; // Set the pressed key in the report
  hidReport.keys[1] = 0;   // No other keys pressed
  hidReport.keys[2] = 0;
  hidReport.keys[3] = 0;
  hidReport.keys[4] = 0;
  hidReport.keys[5] = 0;

  // Send the HID report
  HID().SendReport(1, &hidReport, sizeof(hidReport));
}

// Function to release all keys
void releaseAllKeys() {
  hidReport.modifiers = 0;
  hidReport.keys[0] = 0;
  hidReport.keys[1] = 0;
  hidReport.keys[2] = 0;
  hidReport.keys[3] = 0;
  hidReport.keys[4] = 0;
  hidReport.keys[5] = 0;

  // Send the HID report to release all keys
  HID().SendReport(1, &hidReport, sizeof(hidReport));
}

void setup() {
  Serial.begin(9600);

  // Initialize row pins as outputs
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);  // Set rows HIGH initially
  }

  // Initialize column pins as inputs with pull-ups
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  // Set the HID report descriptor
  static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);

  // Initialize HID
  HID().begin();

  delay(1000);  // Wait for the USB connection to stabilize
}

void scan_keyboard() {
  for (int row = 0; row < ROWS; row++) {
    digitalWrite(rowPins[row], LOW);  // Activate current row

    for (int col = 0; col < COLS; col++) {
      bool keyState = (digitalRead(colPins[col]) == LOW);  // Read the key state

      // Check if the key state has changed
      if (keyState != keyPressed[row][col]) {
        // Debounce check
        if (millis() - lastDebounceTime > DEBOUNCE) {
          keyPressed[row][col] = keyState;  // Update the key state

          if (keyState) {
            // Key pressed
            Serial.print("Button pressed at row ");
            Serial.print(row);
            Serial.print(", column ");
            Serial.println(col);

            // Send the corresponding HID key
            byte key = keymap[row][col];
            if (key != KEY_NONE) {  // Only send if the key is not KEY_NONE
              sendHIDKey(key);
            }
          } else {
            // Key released
            Serial.print("Button released at row ");
            Serial.print(row);
            Serial.print(", column ");
            Serial.println(col);

            // Release all keys
            releaseAllKeys();
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
}