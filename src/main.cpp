#include <Arduino.h>
#include "config.h"
#include "EepromControl.h"
#include "IOExpander.h"
#include "DistanceSensor.h"
#include "MotorControl.h"
#include "BluetoothControl.h"
#include "WebInterface.h"
#include "ScanRoutine.h"

// oder 21/22

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
    Serial.print("scanAngleZ: ");
    Serial.print(zDegrees);
    Serial.print(", scanStepsZ: ");
    Serial.print(zRotations);
    Serial.print(", scanAngleY: ");
    Serial.print(yDegrees);
    Serial.print(", scanStepsY: ");
    Serial.print(yRotations);
    Serial.print(", pauseBetweenScanmoves: ");
    Serial.println(pauseBetweenScanmoves);
    performRevoScan(zDegrees, zRotations, yDegrees, yRotations, pauseBetweenScanmoves);
    commandState = 0;
    break;
  case 900:
    // todo textaxes zu motor
    Serial.println("Testing X");
    moveAxisX(3000, true);
    delay(1000);
    Serial.println("Testing Y (CW/CCW)");
    moveAxisY(1000, true, true);
    moveAxisY(1000, false, true);
    moveAxisY(1000, true, true);
    moveAxisY(1000, false, true);
    moveAxisY(1000, true, true);
    moveAxisY(1000, false);
    delay(1000);
    Serial.println("Testing Z (DOWN/UP)");
    moveAxisZ(1600, true);
    moveAxisZ(1600, false);
    moveAxisZ(1600, true);
    moveAxisZ(1600, false);
    moveAxisZ(1600, true);
    moveAxisZ(1600, false);
    delay(1000);
    Serial.println("DONE");
    commandState = 0;
    break;

  case 990:
    moveAxisX(30000, true);
    commandState = 0;
    break;
  }
}

void testEEPROM()
{
  settings[0].value = "WiFi SSID"; // Beispielwerte
  settings[1].value = "SehrGeheimesPasswort";

  saveSettings(); // Speichert die Einstellungen im EEPROM

  delay(1000); // Kurze Pause, um das Schreiben zu ermöglichen

  // Beispiel: Laden von Einstellungen aus dem EEPROM
  Serial.println("Laden von Einstellungen aus dem EEPROM...");
  loadSettings(); // Lädt die Einstellungen aus dem EEPROM

  // Ausgabe der geladenen Einstellungen auf die serielle Konsole
  for (int i = 0; i < MAX_SETTINGS; i++)
  {
    if (settings[i].value.length() == 0)
      break; // Ende der Einstellungen erreicht
    Serial.println("Geladene Einstellung: " + settings[i].value);
  }
}