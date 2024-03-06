#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <Stepper.h>
// Client Code
#include "BLEDevice.h"
//#include "BLEScan.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>
using namespace std;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define LED_PIN 7

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// TODO: change the service UUID to the one you are using on the server side.
// The remote service we wish to connect to.
static BLEUUID serviceUUID("01321ba9-d483-4cc0-a3c6-bdf4dea15d2d");
// The characteristic of the remote service we are interested in.
static BLEUUID    charUUID("2f133b7e-61c4-4664-adb2-cf268d56aa9c");
// static BLEUUID    charUUID2("a32d3bed-024d-469d-aba7-f98200660772");

static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLEAdvertisedDevice* myDevice;

const int stepsPerRevolution = 315;  // Change this depending on your stepper motor's steps per revolution

// Define pin connections for the ULN2003 driver
const int pin1 = 1;
const int pin2 = 2;
const int pin3 = 3;
const int pin4 = 4;

// Initialize the stepper library
Stepper myStepper(stepsPerRevolution, pin1, pin2, pin3, pin4);


// TODO: define new global variables for data collection

// TODO: define a new function for data aggregation

static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    // TODO: add codes to handle the data received from the server, and call the data aggregation function to process the data

    // TODO: change the following code to customize your own data format for printing
    Serial.print("Notify callback for characteristic ");
    Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
    Serial.print(" of data length ");
    Serial.println(length);
    Serial.print("data: ");
    Serial.write(pData, length);
    Serial.println();
    String str=String((char *) pData).substring(0,length);
    Serial.println(str.substring(0,length));

    String room = str.substring(0,1);
    String name = str.substring(2,length);


    // String data = String((char *) pData);
    Serial.println(room == "A");
    if (room == "A") {
      digitalWrite(LED_PIN, HIGH); // Turn the LED on
      Serial.println("LED is ON"); // Print message to the serial monitor
      display.setCursor(0,0);
      Serial.println(name + " is calling!");
      display.println(name + " is calling!");
      display.display();
      delay(1000);
      display.clearDisplay();
      // rotate the pointer
      myStepper.step(stepsPerRevolution / 2);
      delay(2000);
      myStepper.step(-stepsPerRevolution / 2);
    } else if (room == "B") {
      digitalWrite(LED_PIN, HIGH); // Turn the LED on
      Serial.println("LED is ON"); // Print message to the serial monitor
      display.setCursor(0,0);
      Serial.println(name + " is calling!");
      display.println(name + " is calling!");
      display.display();
      delay(1000);
      display.clearDisplay();
      // rotate the pointer
      myStepper.step(stepsPerRevolution);
      delay(2000);
      myStepper.step(-stepsPerRevolution);
    } else {
      Serial.println("No data");
    }
    // display
    
}

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
  }

  void onDisconnect(BLEClient* pclient) {
    connected = false;
    Serial.println("onDisconnect");
  }
};

bool connectToServer() {
    Serial.print("Forming a connection to ");
    Serial.println(myDevice->getAddress().toString().c_str());

    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    pClient->setClientCallbacks(new MyClientCallback());

    // Connect to the remove BLE Server.
    pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
    Serial.println(" - Connected to server");
    pClient->setMTU(517); //set client to request maximum MTU from server (default is 23 otherwise)

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our service");


    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our characteristic");

    // Read the value of the characteristic.
    if(pRemoteCharacteristic->canRead()) {
      std::string value = pRemoteCharacteristic->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }

    if(pRemoteCharacteristic->canNotify())
      pRemoteCharacteristic->registerForNotify(notifyCallback);

    connected = true;


    return true;
}
/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  /**
   * Called for each advertising BLE server.
   */
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;

    } // Found our server
  } // onResult
}; // MyAdvertisedDeviceCallbacks

void setup() {
  // Set the speed in RPM
  myStepper.setSpeed(60);

  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT); // Set the LED pin as an output
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");
  
  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 5 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the display buffer
  display.clearDisplay();

  // Set text size and color
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Display static text
  display.setCursor(0,0);
  // display.println(F("Hello, Seeed Xiao!"));
  // display.display();
} // End of setup.

// This is the Arduino main loop function.
void loop() {
  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }
 
  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  // with the current time since boot.
  if (connected) {
    String newValue = "Time since boot: " + String(millis()/1000);
    Serial.println("Setting new characteristic value to \"" + newValue  + "\"");

    // Set the characteristic's value to be the array of bytes that is actually a string.
    pRemoteCharacteristic->writeValue(newValue.c_str(), newValue.length());
  }else if(doScan){
    BLEDevice::getScan()->start(0);  // this is just example to start scan after disconnect, most likely there is better way to do it in arduino
  }

  delay(5000); // Delay a second between loops.
} // End of loop