// EepromControl.h
#ifndef EEPROM_CONTROL_H
#define EEPROM_CONTROL_H

#include <EEPROM.h>

#define MAX_SETTINGS 10 // Maximale Anzahl der Einstellungen

struct Setting
{
    int address;
    String value;
} settings[MAX_SETTINGS] = {
    // Beispiel-Einstellungen
    {0, "Einstellung1"},
    {50, "Einstellung2"} // Die Startadressen müssen manuell angepasst werden
};

void setupEEPROM(size_t size)
{
    if (!EEPROM.begin(size))
    {
        Serial.println("Failed to initialise EEPROM");
        return;
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

String loadString(int address)
{
    String result;
    char ch;
    do
    {
        ch = EEPROM.read(address++);
        if (ch)
            result += ch;
    } while (ch != '\0');
    return result;
}

void saveSettings()
{
    int address = 0;
    for (int i = 0; i < MAX_SETTINGS; i++)
    {
        if (settings[i].value.length() == 0)
            break; // Keine weiteren Einstellungen
        saveString(address, settings[i].value);
        address += settings[i].value.length() + 1; // +1 für Null-Terminator
    }
}

void loadSettings()
{
    int address = 0;
    for (int i = 0; i < MAX_SETTINGS; i++)
    {
        settings[i].value = loadString(address);
        if (settings[i].value.length() == 0)
            break;                                 // Keine weiteren Einstellungen
        address += settings[i].value.length() + 1; // +1 für Null-Terminator
    }
}

void clearEEPROM()
{
    for (int i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.write(i, 0xFF); // EEPROM mit 0xFF löschen
    }
    EEPROM.commit();
}

#endif
