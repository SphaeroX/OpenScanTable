// EepromControl.h
#ifndef EEPROM_CONTROL_H
#define EEPROM_CONTROL_H

#include <EEPROM.h>

void initEEPROM(size_t size)
{
    if (!EEPROM.begin(size))
    {
        Serial.println("Failed to initialise EEPROM");
    }
}

void saveString(int address, String data)
{
    for (int i = 0; i < data.length(); i++)
    {
        EEPROM.write(address + i, data[i]);
    }
    EEPROM.write(address + data.length(), '\0'); // Null-Terminator hinzufügen
    EEPROM.commit();
}

void saveSettings()
{
    return;
}

void loadSettings()
{
    return;
}

String loadString(int address, int length)
{
    char data[length + 1]; // +1 für Null-Terminator
    for (int i = 0; i < length; i++)
    {
        data[i] = EEPROM.read(address + i);
    }
    data[length] = '\0'; // Stelle sicher, dass die Zeichenkette korrekt terminiert ist
    return String(data);
}

void clearEEPROM()
{
    for (int i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.write(i, 0xFF); // EEPROM mit 0xFF löschen, was dem gelöschten Zustand entspricht
    }
    EEPROM.commit();
}

#endif
