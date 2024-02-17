// config.h
#ifndef CONFIG_H
#define CONFIG_H

// PIN-Konfigurationen Anschlüsse
#define ULTRASONIC_ECHO 33 // X -

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

// I2C-Konfigurationen
#define SDA 21 // LCD_EN
#define SCL 22 // Z-

// Bluetooth-Konfiguration
// const char *BLUETOOTH_NAME = "3DScannerControl";

// Scaneinstellungen

// Motor-Konfiguration
#define STEP_DELAY_X 400 // Z_ENABLE
#define STEP_DELAY_Y 400 // Z_STEP
#define STEP_DELAY_Z 400 // Z_DIR

// Globale Variablen
int commandState = 0;
int initialDistance = 0;
int pauseBetweenScanmoves = 1000;
int measureDistanceTolerance = 500;
int scanAngleZ = 20;
int scanStepsZ = 18;
int scanAngleY = 18;
int scanStepsY = 3;
int scanShotPause = 1000;
uint8_t revoScanTrigger = ' ';

#endif
