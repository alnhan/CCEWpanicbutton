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
#include "WirelessDataTransmission.h"

volatile bool isButtonPressed;
bool isDeviceConnected;
int count;

/*
* Tracks whether a phone or computer is connected to the Wearable Alert Device.
*
*/
class WADServerCallbacks : public BLEServerCallbacks {
  
  // A device has connected to WAD.
  // Set flag to true to indicate connection.
  void onConnect(BLEServer* pServer) {
    isDeviceConnected = true;
  }

  // Device has disconnected from WAD.
  // Set flag to false to indicate disconnection and restart BLE advertising.
  void onDisconnect(BLEServer* pServer) {
    isDeviceConnected = false;
    BLEDevice::startAdvertising();
  }
};

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
  isDeviceConnected = false;
  count = 0;

  // Bluetooth Initialization
  BLEDevice::init(BLE_SERVER_NAME);
  BLEDevice::setMTU(MTU_SIZE);

  // Create BLE Server.
  wadServer = BLEDevice::createServer();

  // Create BLE Service.
  wadService = wadServer->createService(SERVICE_UUID);

  // Add BLE callback functions to the server.
  wadServer->setCallbacks(new WADServerCallbacks());

  // Create BLE Characteristic.
  wadCharacteristic = wadService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  wadCharacteristic->addDescriptor(new BLE2902());

  // Start the BLE service.
  wadService->start();

  // Start advertising the WAD as a connectable BLE device.
  wadAdvertising = BLEDevice::getAdvertising();
  wadAdvertising->addServiceUUID(SERVICE_UUID);
  BLEDevice::startAdvertising();
}

void loop() {
  if (isButtonPressed && isDeviceConnected) {
    Serial.println("Button pressed.");
    count++;
    Serial.print("count: ");
    Serial.println(count);
    wadCharacteristic->setValue(String(count).c_str());
    wadCharacteristic->notify();
    isButtonPressed = false;
    delay(300);
  }
}
