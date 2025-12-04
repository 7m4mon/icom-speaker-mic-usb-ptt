# Icom Microphone → USB HID Gamepad Adapter

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
- **PTT** — A1 analog input  
- **DOWN/UP** — A2 analog input  
  - GND short → Button 2 (UP)  
  - 470Ω pull-UP → Button 3 (DOWN)  
  - Open circuit → No button  

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
