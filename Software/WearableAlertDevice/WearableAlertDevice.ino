/*
* Main software file that handles all the functionality
* of the Wearable Alert Device.
*
* @author Alex Ho
* @2026 University of Oklahoma
*/

#include "config.h"
#include "GPSModule.h"
#include "GunshotDetection.h"

volatile bool isButtonPressed; 

/*
* Handles the state of the button when it is pressed.
* Button utilizes an interrupt. 
* Function is placed in internal RAM of ESP32, not flash. 
*
*/
void IRAM_ATTR handleButtonInterrupt() {
  // Toggle button state to true when it is pressed.
  isButtonPressed = true;
}

void setup() {
  Serial.begin(115200); // Baud rate set to 115200
  pinMode(BUTTON, INPUT_PULLUP);  // Button is active-low

  // Attach the interrupt function to the active-low button.
  attachInterrupt(digitalPinToInterrupt(BUTTON), handleButtonInterrupt, FALLING);

  isButtonPressed = false;
}

void loop() {
  if (isButtonPressed) {
    Serial.println("67");
    isButtonPressed = false;
  }

}
