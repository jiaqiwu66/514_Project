# Sound Localizer
The Sound Localizer is a device crafted for elderly individuals with hearing impairments. It employs LEDs and a stepper-motor driven gauge needle to __visually signal the location and intensity of sounds, such as calls or knocks__, inside the home. This innovative tool also __identifies the caller__, enhancing situational awareness and providing a heightened sense of interactively.

<img width="516" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/255a036f-b345-45cc-bcb9-c9acea3a9f6a">


# Sensor Devices
Sensors can be installed in various rooms, such as kitchens, living rooms, and bathrooms. Each sensor is equipped with a microphone and a microcontroller unit (MCU). The MCU activates the microphone and establishes a Wi-Fi connection. When the sensor detects a person‘s call, it captures audio data, including frequency and volume, and sends this information to a display.  
- __Sound Sensor (choose 1)* 3:__
1. Adafruit Microphone Amplifier MAX4466 (sound level)
2. ICS-43434 (frequency + sound level)
3. I2S+ (frequency + sound level)
<img width="392" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/480805c5-19fe-4cf1-98b3-c7aaab1b65ea">


- __MCU *3__  
Seeed Studio XIAO ESP32S3, control the circuit to power up the sensor and connect it to WIFI

# Display
- __OLED screen:__ SSD1306 OLED display  
Show text information about the caller, like “ BB’s calling!”
- __LED__  
Shining to remind user to see the watch
- __Pointer：__ Stepper-motor driven gauge needle（like SG90 Micro Servo Motor）  
For indicating the direction or the specific room from which a caller is speaking
<img width="826" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/8132b4e5-4e8d-4504-a47a-1c6e5ecaa6aa">


# System Architecture

<img width="943" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/488cbf81-eef2-40f6-ade5-9dc8043d103d">  

- Detailed diagram
<img width="1047" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/193e6d5b-8e21-4e57-bf4d-0521abbf695f">





