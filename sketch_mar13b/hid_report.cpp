
#include "hid_report.h"

HIDReport hidReport = {0};

// Function to send the HID keypress report
void sendHIDKey(byte key, bool keyState) {
    // Create the HID report for the keyboard

  hidReport.keys[key / 8] |= (1 << (key % 8));
  // Send the HID report
  HID().SendReport(1, &hidReport, sizeof(hidReport));
}

  // Function to release all keys
void releaseAllKeys() {
  memset(&hidReport, 0, sizeof(hidReport));
  HID().SendReport(1, &hidReport, sizeof(hidReport));
}

void releaseKey(byte key) {
  hidReport.keys[key / 8] &= ~(1 << (key % 8)); // Clear the bit
  HID().SendReport(1, &hidReport, sizeof(hidReport)); // Send HID update 
}



// HID report descriptor for a keyboard
static const uint8_t _hidReportDescriptor[] PROGMEM = {
  0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
  0x09, 0x06,                    // USAGE (Keyboard)
  0xA1, 0x01,                    // COLLECTION (Application)
  0x85, 0x01,                    //   REPORT ID (1)

  // Modifier keys (1 byte)
  0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
  0x19, 0xE0,                    //   USAGE_MINIMUM (Left Control)
  0x29, 0xE7,                    //   USAGE_MAXIMUM (Right GUI)
  0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
  0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
  0x75, 0x01,                    //   REPORT_SIZE (1)
  0x95, 0x08,                    //   REPORT_COUNT (8)
  0x81, 0x02,                    //   INPUT (Data,Var,Abs)

  // Reserved (1 byte)
  0x75, 0x08,                    //   REPORT_SIZE (8)
  0x95, 0x01,                    //   REPORT_COUNT (1)
  0x81, 0x03,                    //   INPUT (Const,Var,Abs)

  // Key bitmap (16 bytes for 128 keys)
  0x75, 0x01,                    //   REPORT_SIZE (1)
  0x95, 0x80,                    //   REPORT_COUNT (128)
  0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
  0x19, 0x00,                    //   USAGE_MINIMUM (0)
  0x29, 0x7F,                    //   USAGE_MAXIMUM (127)
  0x81, 0x02,                    //   INPUT (Data,Var,Abs)

  0xC0                           // END_COLLECTION
  };
void hid_start() {
    // Start the HID interface
    // Set the HID report descriptor
  static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);

  // Initialize HID
  HID().begin();

  delay(1000);  // Wait for the USB connection to stabilize
}