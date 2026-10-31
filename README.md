# Smart Lock System

## Overview
The Smart Lock System is an IoT project simulated in Wokwi, designed to secure a door using an ESP32 microcontroller. Users can unlock the door by entering a PIN on a 4x4 keypad, view feedback on a 16x2 I2C LCD, and control a servo motor to lock or unlock the door mechanism. The system provides visual feedback for PIN entry and supports manual locking.

### Features
- **Keypad Input**: Enter a 4-digit PIN to unlock the door, with support for deleting digits.
- **LCD Feedback**: Displays lock status ("Door Locked" or "Door Unlocked") and PIN entry feedback (asterisks for digits, "Incorrect PIN!" for wrong entries).
- **Servo Control**: Moves to -90 degrees to unlock and 90 degrees to lock the door.
- **WiFi Placeholder**: Includes WiFi setup for potential future remote access (not implemented).

## Hardware Requirements
- **ESP32 DevKit V1**: Main microcontroller.
- **4x4 Membrane Keypad**: For PIN entry.
- **16x2 I2C LCD**: For displaying status and feedback (I2C address: 0x27, verify with scanner if needed).
- **Servo Motor**: Controls the lock mechanism (connected to D14).
- **Mini Breadboard**: For power and ground connections.
- **Jumper Wires**: For connecting components.

## Software Requirements
- **Wokwi Simulator**: Run the project at [wokwi.com](https://wokwi.com/).
- **Libraries**:
  - `WiFi.h` (ESP32 WiFi, included in Wokwi)
  - `Keypad.h` (for keypad input)
  - `Wire.h` (for I2C communication)
  - `LiquidCrystal_I2C.h` (for LCD control)
  - `ESP32Servo.h` (for servo control)
