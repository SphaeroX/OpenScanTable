// EepromControl.h
#ifndef EEPROM_CONTROL_H
#define EEPROM_CONTROL_H

#include <EEPROM.h>

#define MAX_SETTINGS 10 // Maxiumum Settings in EEPROM

struct Setting
{
    int address;
    String value;
} settings[MAX_SETTINGS] = {
    // Examples
    {0, "Einstellung1"},
    {50, "Einstellung2"}};

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
    EEPROM.write(address + data.length(), '\0'); // Null-Terminator
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
            break;
        saveString(address, settings[i].value);
        address += settings[i].value.length() + 1;
    }
}

void loadSettings()
{
    int address = 0;
    for (int i = 0; i < MAX_SETTINGS; i++)
    {
        settings[i].value = loadString(address);
        if (settings[i].value.length() == 0)
            break;
        address += settings[i].value.length() + 1;
    }
}

void clearEEPROM()
{
    for (int i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.write(i, 0xFF);
    }
    EEPROM.commit();
}

void testEEPROM()
{
    settings[0].value = "WiFi SSID";
    settings[1].value = "PasswordSecret";

    saveSettings();

    Serial.println("Load settings from EEPROM...");
    loadSettings();

    for (int i = 0; i < MAX_SETTINGS; i++)
    {
        if (settings[i].value.length() == 0)
            break;
        Serial.println("Settings: " + settings[i].value);
    }
}

#endif
