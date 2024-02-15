// IOExpander.h
#ifndef IO_EXPANDER_H
#define IO_EXPANDER_H

#define NUM_REGISTERS 3
#define PINS_PER_REGISTER 8

byte registerStates[NUM_REGISTERS] = {0, 0, 0};

void setupIOExpander()
{
    pinMode(DATA_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
}

void updateShiftRegisters()
{
    digitalWrite(LATCH_PIN, LOW);
    for (int i = NUM_REGISTERS - 1; i >= 0; i--)
    {
        shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, registerStates[i]);
    }
    digitalWrite(LATCH_PIN, HIGH);
}

void setPin(int pin, bool state)
{
    int registerIndex = (pin - 1) / PINS_PER_REGISTER;
    int pinIndex = (pin - 1) % PINS_PER_REGISTER;

    if (state)
        registerStates[registerIndex] |= (1 << pinIndex);
    else
        registerStates[registerIndex] &= ~(1 << pinIndex);

    updateShiftRegisters();
}
#endif
