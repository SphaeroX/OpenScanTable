// motor_control.h
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

void setupMotors()
{
    setPin(STEP_PIN_X, LOW);
    setPin(STEP_PIN_Y, LOW);
    setPin(STEP_PIN_Z, LOW);
}

void moveAxisX(int steps, bool direction)
{
    setPin(EN_PIN_X, LOW);
    setPin(DIR_PIN_X, direction);
    for (int i = 0; i < steps; i++)
    {
        setPin(STEP_PIN_X, HIGH);
        delayMicroseconds(STEP_DELAY_X);
        setPin(STEP_PIN_X, LOW);
        delayMicroseconds(STEP_DELAY_X);
    }
    setPin(EN_PIN_X, HIGH);
}

void moveAxisY(int steps, bool direction)
{
    setPin(EN_PIN_Y, LOW);
    setPin(DIR_PIN_Y, direction);
    for (int i = 0; i < steps; i++)
    {
        setPin(STEP_PIN_Y, HIGH);
        delayMicroseconds(STEP_DELAY_Y);
        setPin(STEP_PIN_Y, LOW);
        delayMicroseconds(STEP_DELAY_Y);
    }
    setPin(EN_PIN_Y, HIGH);
}

void moveAxisZ(int steps, bool direction)
{
    setPin(EN_PIN_Z, LOW);
    setPin(DIR_PIN_Z, direction);
    for (int i = 0; i < steps; i++)
    {
        setPin(STEP_PIN_Z, HIGH);
        delayMicroseconds(STEP_DELAY_Z);
        setPin(STEP_PIN_Z, LOW);
        delayMicroseconds(STEP_DELAY_Z);
    }
    setPin(EN_PIN_Z, HIGH);
}

void adjustScannerDistance(int targetDistance)
{
    int currentDistance = measureDistance();
    bool direction = HIGH; // Setzt eine anfängliche Richtung

    // Testfahrt, um die korrekte Richtung zu bestimmen
    moveAxisZ(10, direction); // Macht einen kleinen Schritt in die anfängliche Richtung
    int newDistance = measureDistance();

    // Überprüft, ob die Bewegung die Distanz verringert hat
    if (abs(newDistance - targetDistance) >= abs(currentDistance - targetDistance))
    {
        // Wenn die Distanz nicht verringert wurde, ändere die Richtung
        direction = !direction;
    }

    // Anpassung der Distanz mit der ermittelten Richtung
    while (abs(currentDistance - targetDistance) > measureDistanceTolerance)
    {
        int stepSize = abs(currentDistance - targetDistance) > 10 ? 10 : 1; // Verwendet größere Schritte, wenn die Distanz groß ist, und kleinere, wenn sie nahe am Ziel ist
        moveAxisZ(stepSize, direction);

        currentDistance = measureDistance(); // Misst die Distanz erneut
    }
}

#endif
