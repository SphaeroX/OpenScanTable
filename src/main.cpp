#include <Arduino.h>
#include "config.h"
#include "EepromControl.h"
#include "IOExpander.h"
#include "MotorControl.h"
#include "UltrasonicSensor.h"
#include "BluetoothControl.h"
#include "WebInterface.h"
#include "ScanRoutine.h"

// oder 21/22

void setup()
{
  Serial.begin(115200);
  setupIOExpander();
  setupMotors();
  setupUltrasonic();
  setupBluetooth();
  setupWebServer();
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
    performRevoScan(20, 17, 10, 3, 100, 1000);
    commandState = 0;
    break;
  }
  // togglePin();
  // moveXAxis(500, HIGH);
  // moveYAxis(500, HIGH);
  // sendKeystroke();
  // loopWebServer();
  // Serial.println("MOVE");
  // moveAxisX(1000, HIGH);
  // delay(1000);

  // setPin(17, HIGH);
  // delay(500);
  // setPin(18, HIGH);
  // delay(500);
  // setPin(19, HIGH);
  // delay(500);
  //
  // setPin(19, LOW);
  // delay(500);
  // setPin(18, LOW);
  // delay(500);
  // setPin(17, LOW);
  // delay(500);
}
