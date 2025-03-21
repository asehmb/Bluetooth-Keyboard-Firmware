int counter = 0;
int currentClock;
int lastClock;
char *currDirection;
unsigned long timeSinceClick = 0;

void encoder_setup() {
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);

  Serial.begin(9600);

  lastClock = digitalRead(ENCODER_CLK);
}

int encoder_update() {
  currentClock = digitalRead(ENCODER_CLK);
  
  // Only update when CLK state changes
  if (currentClock != lastClock) {
    // Add a small debounce delay to avoid multiple reads
    delay(4);  // A small delay to allow state change to stabilize
    
    if (digitalRead(ENCODER_DT) != currentClock) {
      // Counter-clockwise rotation
      counter--;
      currDirection = "Counter Clockwise";
    } else {
      // Clockwise rotation
      counter++;
      currDirection = "Clockwise";
    }
    
    // Output direction and counter value

    
    lastClock = currentClock;  // Update lastClock for next iteration
  }

  // Check button state
  int buttonState = digitalRead(ENCODER_SW);
  if (buttonState == LOW) {
    if (millis() - timeSinceClick > 50) {  // Debounce button press
      Serial.println("CLICK");
    }
    timeSinceClick = millis();
  }
}