# Sound Localizer
The Sound Localizer is a device crafted for elderly individuals with hearing impairments. It employs LEDs and a stepper-motor driven gauge needle to __visually signal the location and intensity of sounds, such as calls or knocks__, inside the home. This innovative tool also __identifies the caller__, enhancing situational awareness and providing a heightened sense of interactively.

<img width="464" alt="image" src="https://github.com/jiaqiwu66/514_project/assets/148316400/0f77be49-b2a6-433d-a109-c8defa90342d">


# Sensor
- __Sound Sensor (choose 1)* 3:__  
1. Adafruit Microphone Amplifier MAX4466 (sound level)
2. ICS-43434 (frequency + sound level)
3. I2S+ (frequency + sound level)
<img width="382" alt="image" src="https://github.com/jiaqiwu66/514_project/assets/148316400/82400c6d-2619-4ae9-aaf7-702f36745e7f">

- __MCU *3__  
Seeed Studio XIAO ESP32S3, provide wifi and battery for each sensor

# Display
- __OLED screen:__ SSD1306 OLED display  
Show text information about the caller, like “ BB’s calling!”
- __LED__  
Shining to remind user to see the watch
- __Pointer：__ Stepper-motor driven gauge needle（like SG90 Micro Servo Motor）  
For indicating the direction or the specific room from which a caller is speaking

<img width="777" alt="image" src="https://github.com/jiaqiwu66/514_project/assets/148316400/e6dea7a6-8dc8-4d68-9cb8-bddf0e4fbfff">

# System Architecture
<img width="855" alt="image" src="https://github.com/jiaqiwu66/514_project/assets/148316400/31744099-3980-43e8-990e-7df2dac93b5d">

- Detailed diagram
<img width="851" alt="image" src="https://github.com/jiaqiwu66/514_project/assets/148316400/a961f251-61dc-4346-9cb7-8618341425b3">




