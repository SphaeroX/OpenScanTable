// config.h
#ifndef CONFIG_H
#define CONFIG_H

// PIN-Konfigurationen Anschlüsse
#define ULTRASONIC_ECHO 34    // Y -
#define ULTRASONIC_TRIGGER 22 // I2S: BEEPER

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

#define ULTRASONIC_TRIG 22 // BEEPER

// I2S-Konfigurationen
#define CLOCK_PIN 25 // I2S_BCK
#define LATCH_PIN 26 // I2S_WS
#define DATA_PIN 27  // I2S_DATA

// Bluetooth-Konfiguration
// const char *BLUETOOTH_NAME = "3DScannerControl";

// Scaneinstellungen

// Motor-Konfiguration
#define STEP_DELAY_X 400 // Z_ENABLE
#define STEP_DELAY_Y 400 // Z_STEP
#define STEP_DELAY_Z 400 // Z_DIR

// Globale Variablen
int commandState = 0;
int measureDistanceTolerance = 5;  // +- mm at this distance an adujst will be made
int measureDistanceMaxChange = 40; // mm at this distance no adjust will be made because of wrong focus
int zDegrees = 20;
int zRotations = 18;
int yDegrees = 18;
int yRotations = 3;
int scanShotPause = 500;
boolean autoAdjust = false;
char revoScanTrigger = ' ';

// Konstanten für die Motorsteuerung
const int stepsPerRevolution = 6400;
const float mmPerRevolution = 20.0;
const int stepsPerMillimeter = stepsPerRevolution / mmPerRevolution;

#endif
