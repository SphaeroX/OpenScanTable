// config.h
#ifndef CONFIG_H
#define CONFIG_H

// PIN-Konfigurationen Anschlüsse
#define ULTRASONIC_TRIG 0 // TX 1 später da sonst kein serial debug möglich
#define ULTRASONIC_ECHO 4 // RX 3 später da sonst kein serial debug möglich

// PIN-Konfigurationen Expander
#define EN_PIN_X 1   // X_ENABLE
#define STEP_PIN_X 2 // X_STEP
#define DIR_PIN_X 3  // X_DIR

#define EN_PIN_Y 4   // Y_ENABLE
#define STEP_PIN_Y 5 // Y_STEP
#define DIR_PIN_Y 6  // Y_DIR

#define EN_PIN_Z 7   // Z_ENABLE
#define STEP_PIN_Z 8 // Z_STEP
#define DIR_PIN_Z 9  // Z_DIR

// I2S-Konfigurationen
#define CLOCK_PIN 25
#define LATCH_PIN 26
#define DATA_PIN 27

// Bluetooth-Konfiguration
// const char *BLUETOOTH_NAME = "3DScannerControl";

// Scaneinstellungen
const int SCAN_ANGLE_STEP = 20;     // Grad pro Schritt um die Z-Achse
const int Y_AXIS_STEP = 30;         // Grad pro Schritt für die Y-Achse
const int TARGET_DISTANCE_MM = 100; // Zielentfernung in mm

// Motor-Konfiguration
#define STEP_DELAY_X 800 // Z_ENABLE
#define STEP_DELAY_Y 800 // Z_STEP
#define STEP_DELAY_Z 800 // Z_DIR

// Globale Variablen
int commandState = 0;
int pauseBetweenScanmoves = 1000;
int measureDistanceTolerance = 2;
uint8_t revoScanTrigger = ' ';

#endif
