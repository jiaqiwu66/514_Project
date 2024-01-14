# Sound Localizer
The Sound Localizer is a device crafted for elderly individuals with hearing impairments. It employs LEDs and a stepper-motor driven gauge needle to __visually signal the location and intensity of sounds, such as calls or knocks__, inside the home. This innovative tool also __identifies the caller__, enhancing situational awareness and providing a heightened sense of interactively.

<img width="516" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/255a036f-b345-45cc-bcb9-c9acea3a9f6a">


# Sensor
- __Sound Sensor (choose 1)* 3:__  
1. Adafruit Microphone Amplifier MAX4466 (sound level)
2. ICS-43434 (frequency + sound level)
3. I2S+ (frequency + sound level)
<img width="392" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/480805c5-19fe-4cf1-98b3-c7aaab1b65ea">


- __MCU *3__  
Seeed Studio XIAO ESP32S3, provide wifi and battery for each sensor

# Display
- __OLED screen:__ SSD1306 OLED display  
Show text information about the caller, like “ BB’s calling!”
- __LED__  
Shining to remind user to see the watch
- __Pointer：__ Stepper-motor driven gauge needle（like SG90 Micro Servo Motor）  
For indicating the direction or the specific room from which a caller is speaking
<img width="826" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/8132b4e5-4e8d-4504-a47a-1c6e5ecaa6aa">


# System Architecture

<img width="942" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/70dad49c-4b7f-4fab-8385-16732220f916">

- Detailed diagram
<img width="909" alt="image" src="https://github.com/jiaqiwu66/514_Project/assets/148316400/fb8cbc22-04f8-433f-833c-4e5d716de310">




