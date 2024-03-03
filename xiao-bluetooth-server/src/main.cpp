#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <stdlib.h>
#include <ArduinoFFT.h>

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
unsigned long previousMillis = 0;
const long interval = 1000;

const int micPin = 2; // Microphone pin
const int sampleRate = 4000; // Sample rate in Hz
const int sampleSize = 256; // Number of samples for FFT
unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[sampleSize];
double vImag[sampleSize];
arduinoFFT FFT = arduinoFFT(vReal, vImag, sampleSize, sampleRate);
// TODO: add new global variables for your sensor readings and processed data

// TODO: Change the UUID to your own (any specific one works, but make sure they're different from others'). You can generate one here: https://www.uuidgenerator.net/
#define SERVICE_UUID        "01321ba9-d483-4cc0-a3c6-bdf4dea15d2d"
#define CHARACTERISTIC_UUID "2f133b7e-61c4-4664-adb2-cf268d56aa9c"

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
    }
};

// TODO: add DSP algorithm functions here

void setup() {
    Serial.begin(115200);
    pinMode(micPin, INPUT);
    samplingPeriod = round(1000000*(1.0/sampleRate));

    Serial.println("Starting BLE work!");

    // TODO: add codes for handling your sensor setup (pinMode, etc.)

    // TODO: name your device to avoid conflictions
    BLEDevice::init("XIAO_ESP32S3");
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    BLEService *pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY
    );
    pCharacteristic->addDescriptor(new BLE2902());
    pCharacteristic->setValue("Hello World");
    pService->start();
    // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
    // Read the input from the microphone
    for (int i = 0; i < sampleSize; i++) {
        microSeconds = micros(); // Overhead of calling micros() can be significant
        vReal[i] = analogRead(micPin);
        vImag[i] = 0;
        while (micros() < (microSeconds + samplingPeriod)) { 
        // Wait until the sampling period is reached
        }
    }

    // Perform FFT
    FFT.Windowing(vReal, sampleSize, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();

    // Find the dominant frequency
    double peakFrequency = 0;
    int peakBin = FFT.MajorPeak();

    peakFrequency = (double)peakBin * (double)sampleRate / (double)sampleSize;
    Serial.print("Peak Frequency: ");
    Serial.println(peakFrequency);

    // Simple sound level measurement (peak-to-peak)
    double soundLevel = 0;
    for(int i = 0; i < sampleSize; i++) {
        soundLevel += vReal[i]; // Summing up for an approximation
    }
    soundLevel /= sampleSize; // Average amplitude
    Serial.print("Sound Level: ");
    Serial.println(soundLevel);

    // delay(1000); // Delay between measurements

    // TODO: add codes for handling your sensor readings (analogRead, etc.)

    // TODO: use your defined DSP algorithm to process the readings

    
    if (deviceConnected) {
        // Send new readings to database
        // TODO: change the following code to send your own readings and processed data
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            if (soundLevel > 850) {
                pCharacteristic->setValue("A");
                pCharacteristic->notify();
                Serial.println("Notify value: A ");
            }
            // else {
            //     pCharacteristic->setValue("Hello World");
            //     pCharacteristic->notify();
            //     Serial.println("Notify value: Hello World");
            // }
        }
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500);  // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising();  // advertise again
        Serial.println("Start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
    delay(1000);
}
