/*
  Icom Mic to USB Gamepad Adapter
  ---------------------------------------
  MCU: ATmega32u4 (Arduino Micro / Pro Micro)
  Purpose:
    Converts an Icom desktop or handheld microphone into a USB HID gamepad device. 
    The primary use case is Push-To-Talk (PTT) operation on Mumble (Mumla), but
    additional UP/DOWN buttons can be mapped to custom actions on the 
    Windows version of Mumble.

  Overview:
    This sketch uses the "Joystick" library by MHeironimus to emulate
    a USB HID gamepad with four buttons.

      - Button 0 → PTT (Android & Windows)
      - Button 2 → DOWN (Windows Mumble can assign freely)
      - Button 3 → UP   (Windows Mumble can assign freely)

    Android Mumble (Mumla) supports *only one* gamepad button (Button 0)
    for PTT.  
    Windows Mumble allows assigning UP/DOWN to any available function.

  Button Mapping:
    - PTT (A1 analog input)
    - UP/DOWN (A2 analog input)
        * GND short       → Button 2 (UP)
        * 470Ω pull-down  → Button 3 (DOWN)
        * Open circuit    → No button

  Library:
    Joystick library by MHeironimus
    https://github.com/MHeironimus/ArduinoJoystickLibrary

  Intended Use:
    - Connect the 32u4 board to an Windows PC / Android phone via USB.
    - Use the Icom mic’s PTT button to control Mumble’s PTT.
    - UP/DOWN buttons are provided for optional future expansion for PC, but
      Android Mumble does not currently support gamepad buttons other
      than PTT.

  Author: 7M4MON
  Date: 04/Dec/2025
*/

#include <Joystick.h>

// ボタン4個（0〜3）だけ使う設定。
// 実際に使うのは 0:PTT / 2:UP / 3:DOWN
Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_GAMEPAD,
  4,    // ボタン数
  0,    // ハットスイッチ数
  false, false, false,  // X, Y, Z
  false, false, false,  // Rx, Ry, Rz
  false, false,         // rudder, throttle
  false, false, false   // accelerator, brake, steering
);

// ピン定義
const int PIN_PTT_ANALOG = A1;  // ← PTT を A1 
const int PIN_UPDN_INPUT   = A2;  // A2 は UP / DOWN 

// --- PTT 用しきい値 ---
// 測定値：OFF 5.0V、ON 3.7V (750) → 中間 ≒ 4.3V
// 5V/10bit ADC → 約  に相当
const int TH_PTT = 880;
// --- PTT delay (to avoid pop noise caused by DC shift on mic line) ---
const uint16_t PTT_ON_DELAY_MS = 300; 

// --- A2用しきい値（元コードそのまま） ---
// 0V〜80未満    → ボタン2 (UP)
// 80〜260未満   → ボタン3 (DOWN)
// 260以上       → OFF
const int TH_GND  = 80;
const int TH_470  = 260;

void setup() {
  // A1/A2 はアナログ入力なので特に設定不要
  pinMode(PIN_PTT_ANALOG, INPUT);
  pinMode(PIN_UPDN_INPUT, INPUT);
  Joystick.begin();
}

void loop() {
  // --- A1: PTT with ON-delay to avoid pop noise ---
  static bool pttLatched = false;          // what we actually report to HID
  static bool pttPending = false;          // waiting for delay to expire
  static uint32_t pttT0  = 0;              // time when press was detected

  int valPTT = analogRead(PIN_PTT_ANALOG);
  bool pttRawPressed = (valPTT < TH_PTT);  // raw detection (pressed when ADC goes low)

  const uint32_t now = millis();

  if (pttRawPressed) {
    if (!pttLatched && !pttPending) {
      // First time we see press -> start delay timer
      pttPending = true;
      pttT0 = now;
    }
    // If pending and delay elapsed -> latch ON
    if (pttPending && (now - pttT0 >= PTT_ON_DELAY_MS)) {
      pttLatched = true;
      pttPending = false;
    }
  } else {
    // Released -> immediately stop transmitting
    pttLatched = false;
    pttPending = false;
  }

  Joystick.setButton(0, pttLatched);

  // --- A2 の電圧で UP / DOWN を判定 ---
  int val = analogRead(PIN_UPDN_INPUT);  // 0〜1023

  bool btn2 = false;  // UP
  bool btn3 = false;  // DOWN

  if (val < TH_GND) {
    btn2 = true;
  } else if (val < TH_470) {
    btn3 = true;
  }
  // それ以外は何も押されていない

  Joystick.setButton(2, btn2);  // UP
  Joystick.setButton(3, btn3);  // DOWN


  delay(10);  // チャタリング軽減・USBトラフィック控えめ
}
