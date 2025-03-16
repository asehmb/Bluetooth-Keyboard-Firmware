
#ifndef HID_REPORT_H
#define HID_REPORT_H

#include <Arduino.h>
#include <HID.h>

// HID report structure for a keyboard
typedef struct {
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[16];
} HIDReport;

void hid_start();
void sendHIDKey(byte key, bool keyState);
void releaseAllKeys();
void releaseKey(byte key);

extern const uint8_t _hidReportDescriptor[] PROGMEM;


#endif