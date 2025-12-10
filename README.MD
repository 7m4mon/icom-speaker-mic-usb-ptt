# Icom Microphone → USB HID Gamepad Adapter

![Image](https://github.com/user-attachments/assets/9e31db43-6ea2-4e8c-94a8-cc75d8e75338)  
![Image](https://github.com/user-attachments/assets/3f880e6f-af01-4607-8acf-a3b267de6d9f)  
![Image](https://github.com/user-attachments/assets/0e1ba12b-6050-48ae-a206-d6e0644e93b4)  
![Image](https://github.com/user-attachments/assets/c03c2af9-a047-461d-a6d3-7771e206e4f2)  

**MCU:** ATmega32u4 (Arduino Micro / Pro Micro)

## Purpose
Converts an Icom desktop or handheld microphone into a USB HID gamepad device.  
The primary use case is Push-To-Talk (PTT) operation on Mumble (Mumla), but  
additional DOWN/UP buttons can be mapped to custom actions on the Windows version  
of Mumble.

## Overview
This sketch uses the **Joystick library by MHeironimus** to emulate a USB HID
gamepad with four buttons.

### Button Mapping
- **Button 0 → PTT** (Android & Windows)
- **Button 2 → UP** (Windows Mumble can assign freely)
- **Button 3 → DOWN**   (Windows Mumble can assign freely)

### Platform Notes
- **Android Mumble (Mumla)** supports *only one* gamepad button (Button 0) for PTT.
- **Windows Mumble** allows assigning DOWN/UP to any available function.

## Analog Inputs
- **PTT** — A1 analog input (external 2.2kΩ Pull-up for Desktop Microphone)  
- **DOWN/UP** — A2 analog input (external 2.2kΩ Pull-up)  
  - GND short → Button 2 (UP)  
  - 470Ω pull-Down → Button 3 (DOWN)  
  - Open circuit → No button  

## Block Graph
- Desktop Transceiver Microphone
<img width="1702" height="575" alt="Image" src="https://github.com/user-attachments/assets/3c18ff28-929f-476a-9add-29413e4941b1" />  

- Handheld Transceiver Microphone
<img width="1882" height="685" alt="Image" src="https://github.com/user-attachments/assets/0a957bbd-5a2c-402e-b7fb-b6892a636f6d" />  

## Library
Joystick library by MHeironimus  
https://github.com/MHeironimus/ArduinoJoystickLibrary

## Intended Use
- Connect the 32u4 board to a Windows PC or Android phone via USB.  
- Use the Icom microphone’s PTT button to control Mumble’s PTT.  
- DOWN/UP buttons are optional for PC but unsupported on Android Mumble.

---

**Author:** 7M4MON  
**Date:** 04/Dec/2025
