// bluetooth_control.h
#ifndef BLUETOOTH_CONTROL_H
#define BLUETOOTH_CONTROL_H

#include <BleKeyboard.h>
BleKeyboard bleKeyboard;

void setupBluetooth()
{
    bleKeyboard.begin();
}

void sendKeystroke(char key)
{
    if (bleKeyboard.isConnected())
    {
        Serial.println("Sending Space");
        bleKeyboard.print(key);
    }
}

#endif
