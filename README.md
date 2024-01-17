# Sound Localizer
The Sound Localizer is a device crafted for elderly individuals with hearing impairments. It employs LEDs and a stepper-motor driven gauge needle to __visually signal the location and intensity of sounds, such as calls or knocks__, inside the home. This innovative tool also __identifies the caller__, enhancing situational awareness and providing a heightened sense of interactively.

<img width="516" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/255a036f-b345-45cc-bcb9-c9acea3a9f6a">


# Sensor Devices
Sensors can be installed in various rooms, such as kitchens, living rooms, and bathrooms. Each sensor is equipped with a microphone and a microcontroller unit (MCU). The MCU activates the microphone and establishes a Wi-Fi connection. When the sensor detects a person‘s call, it captures audio data, including frequency and volume, and sends this information to a display.  
- __Sound Sensor (choose 1)* 3:__
1. Adafruit Microphone Amplifier MAX4466 (sound level)
2. ICS-43434 (frequency + sound level)
3. I2S+ (frequency + sound level)

- __MCU *3__  
Seeed Studio XIAO ESP32S3, control the circuit to power up the sensor and connect it to WIFI

### Sketch
<img width="847" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/dc8322fe-7d52-4a67-b728-f93d1e24b14a">

# Display
The display device, designed like a wristwatch for seniors, includes a stepper-motor driven gauge needle, a button (ON/OFF), a LED, an OLED screen, a MCU, and a PCB. When the MCU gets a signal from a sensor, it'll do the math. It determines the direction of the caller based on which sensor sends the signal. And identify who is calling by the sound frequency. Then, the pointer indicates the room's location on a panel, the LED flashes as an alert, and the caller's name appears on the OLED screen.
- __OLED screen:__ SSD1306 OLED display  
Show text information about the caller, like “ BB’s calling!”
- __LED__  
Shining to remind user to see the watch
- __Pointer：__ Stepper-motor driven gauge needle（like SG90 Micro Servo Motor）  
For indicating the direction or the specific room from which a caller is speaking  
- __MCU:__ Seeed Studio XIAO ESP32S3  
Powered up the circuit and connect to WIFI
### Sketch

<img width="840" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/8ec08bcd-7f01-472e-8c75-60b6d1db702e">



# System Architecture
- __Work Detail__  
<img width="1438" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/8378b7a7-b67c-442b-9313-65c40f482083">
  
- __Architecture Figure__ 
<img width="1047" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/193e6d5b-8e21-4e57-bf4d-0521abbf695f">





