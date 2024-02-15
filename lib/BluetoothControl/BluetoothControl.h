// bluetooth_control.h
#ifndef BLUETOOTH_CONTROL_H
#define BLUETOOTH_CONTROL_H

#include <BleKeyboard.h>
BleKeyboard bleKeyboard;

void setupBluetooth()
{
    bleKeyboard.begin();
}

void sendKeystroke(uint8_t key)
{
    if (bleKeyboard.isConnected())
    {
        Serial.println("Sending Space");
        // Keyboard.print(key);
    }
}

#endif
