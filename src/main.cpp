#include <Arduino.h>
#include "config.h"
#include "EepromControl.h"
#include "IOExpander.h"
#include "DistanceSensor.h"
#include "MotorControl.h"
#include "BluetoothControl.h"
#include "WebInterface.h"
#include "ScanRoutine.h"

void setup()
{
  Serial.begin(115200);
  setupIOExpander();
  setupMotors();
  setupDistanceSensor();
  setupBluetooth();
  setupWebServer();
  setupEEPROM(512);
  Serial.println("setup");
}

void loop()
{
  loopWebServer();

  switch (commandState)
  {
  case 100:
    Serial.println("SAVE SETTINGS");
    saveSettings();
    commandState = 0;
    break;
  case 200:
    Serial.println("START REVO SCAN IN 5 SECOUNDS");
    delay(5000);
    performRevoScan(zDegrees, zRotations, yDegrees, yRotations, scanShotPause);
    commandState = 0;
    break;
  case 900:
    // todo textaxes zu motor
    Serial.println("Testing X");
    textAxes();
    commandState = 0;
    break;
  case 910:
    Serial.print("Testing Distance: ");
    Serial.println(measureDistance());
    commandState = 0;
    break;
  }
}
