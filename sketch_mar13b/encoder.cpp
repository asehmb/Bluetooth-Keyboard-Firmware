#include "encoder.h"

int currentClock;

unsigned long timeSinceClick = 0;

void encoder_setup() {
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);

}

int encoder_update(int * ret_val, int * click) {
  static int lastClock = HIGH;  // Static variable to remember last state of CLK pin
  static unsigned long lastDebounceTime = 0;  // For debouncing
  static unsigned long lastButtonPress = 0;  // For debouncing the button
  const unsigned long debounceDelay = 50;  // Debounce time for encoder and button
  int currentClock = digitalRead(ENCODER_CLK);  // Current state of the encoder CLK
  int buttonState = digitalRead(ENCODER_SW);  // Read the button state

  *ret_val = 0;
  *click = 0;

  
  // Only update when CLK state changes
  if (currentClock != lastClock) {
    // Add a small debounce delay to avoid multiple reads
    
    if (digitalRead(ENCODER_DT) != currentClock) {
      // Counter-clockwise rotation
  
      *ret_val = 2;
    } else {
      // Clockwise rotation
      *ret_val = 1;
    }

    lastClock = currentClock;  // Update lastClock for next iteration
  }


  return 0;
}