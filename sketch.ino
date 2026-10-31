/**
 * @file smart_lock.ino
 * @brief Smart Lock System for ESP32 in Wokwi Simulator
 * @details This sketch controls a smart lock system using an ESP32 DevKit V1. It features a 4x4 keypad for PIN entry, a 16x2 I2C LCD for feedback, and a servo motor to lock/unlock a door. Users enter a 4-digit PIN (default: "1234") to unlock, press 'C' to delete digits, and '*' to lock. The LCD shows lock status and PIN feedback. WiFi is initialized but unused (placeholder for future features).
 * @author IoT Solution Development Team
 * @date May 2025
 * @license MIT
 * 
 * @section hardware Hardware Requirements
 * - ESP32 DevKit V1
 * - 4x4 Membrane Keypad (rows: D15, D2, D4, D5; columns: D18, D19, D27, D23)
 * - 16x2 I2C LCD (SDA: D21, SCL: D22, address: 0x27)
 * - Servo Motor (PWM: D14)
 * - Mini Breadboard for power/ground
 * 
 * @section libraries Libraries
 * - WiFi.h: ESP32 WiFi (not fully utilized)
 * - Keypad.h: Keypad input
 * - Wire.h: I2C communication
 * - LiquidCrystal_I2C.h: LCD control
 * - ESP32Servo.h: Servo control
 */

#include <WiFi.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

/** @brief Number of keypad rows */
const byte ROWS = 4;
/** @brief Number of keypad columns */
const byte COLS = 4;
/** @brief Keypad layout mapping */
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
/** @brief Keypad row pins (D15, D2, D4, D5) */
byte rowPins[ROWS] = {15, 2, 4, 5};
/** @brief Keypad column pins (D18, D19, D27, D23) */
byte colPins[COLS] = {18, 19, 27, 23};

/** @brief Keypad object */
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

/** @brief Servo object for lock mechanism */
Servo lockServo;
/** @brief Servo PWM pin (D14) */
const int servoPin = 14;
/** @brief Servo position for unlock (0 degrees) */
const int unlockPosition = 0;
/** @brief Servo position for lock (180 degrees) */
const int lockPosition = 180;

/** @brief LCD object with I2C address 0x27, 16x2 characters */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/** @brief Tracks lock state (true = locked, false = unlocked) */
bool locked = true;
/** @brief Buffer for entered PIN (4 digits + null terminator) */
char enteredCode[5];
/** @brief Current number of digits entered */
int codeIndex = 0;

/**
 * @brief Updates the LCD to show the current lock status
 */
void updateLockStatus() {
  lcd.clear();
  if (locked) {
    lcd.print("Door Locked"); ///< Display locked status
  } else {
    lcd.print("Door Unlocked"); ///< Display unlocked status
  }
}

/**
 * @brief Unlocks the door by moving the servo to the unlock position
 */
void unlockDoor() {
  locked = false; ///< Update lock state
  lockServo.write(unlockPosition); ///< Move servo to unlock position
  updateLockStatus(); ///< Update LCD
}

/**
 * @brief Locks the door by moving the servo to the lock position
 */
void lockDoor() {
  locked = true; ///< Update lock state
  lockServo.write(lockPosition); ///< Move servo to lock position
  updateLockStatus(); ///< Update LCD
}

/**
 * @brief Processes keypad input for PIN entry, deletion, and locking
 * @param key The key pressed on the keypad
 * @details Handles:
 * - '#' to submit PIN
 * - 'C' to delete last digit (when locked)
 * - '*' to lock door (when unlocked)
 * - Digits (0-9) to build PIN
 */
void handleKeypadInput(char key) {
  if (locked) {
    if (key == '#' && codeIndex > 0) { ///< Submit PIN
      enteredCode[codeIndex] = '\0'; ///< Null-terminate PIN
      codeIndex = 0; ///< Reset index

      if (strcmp(enteredCode, "1234") == 0) { ///< Check correct PIN
        unlockDoor();
      } else { ///< Handle incorrect PIN
        lcd.clear();
        lcd.print("Incorrect PIN!");
        delay(2000); ///< Show message for 2 seconds
        lcd.clear();
        lcd.print("Door Locked");
      }

      memset(enteredCode, 0, sizeof(enteredCode)); ///< Clear PIN buffer
    } else if (key == 'C' && codeIndex > 0) { ///< Delete last digit
      codeIndex--;
      enteredCode[codeIndex] = '\0';
      lcd.setCursor(codeIndex, 1);
      lcd.print(' '); ///< Clear last asterisk
    } else if (key != '#' && key != 'C' && codeIndex < sizeof(enteredCode) - 1) { ///< Add digit
      enteredCode[codeIndex] = key;
      lcd.setCursor(codeIndex, 1);
      lcd.print('*'); ///< Show asterisk for digit
      codeIndex++;
    }
  } else {
    if (key == '*') { ///< Lock door
      lockDoor();
    }
  }
}

/**
 * @brief Initializes the system
 * @details Sets up:
 * - Serial communication (9600 baud)
 * - WiFi (placeholder, not used)
 * - Servo on pin D14
 * - LCD with backlight
 * - Initial lock status
 */
void setup() {
  Serial.begin(9600); ///< Start Serial
  Serial.println("SmartLock on ESP32"); ///< Debug message

  WiFi.begin("Wokwi-GUEST", ""); ///< Initialize WiFi (unused)

  lockServo.attach(servoPin); ///< Attach servo

  lcd.init(); ///< Initialize LCD
  lcd.backlight(); ///< Enable backlight
  lockDoor();
  updateLockStatus(); ///< Show initial status
}

/**
 * @brief Main loop to read and process keypad input
 */
void loop() {
  char key = keypad.getKey(); ///< Get keypress
  if (key) { ///< If key pressed
    handleKeypadInput(key); ///< Process key
  }
}
