// motor_control.h
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

void setupMotors()
{
    setPin(STEP_PIN_X, LOW);
    setPin(STEP_PIN_Y, LOW);
    setPin(STEP_PIN_Z, LOW);
    setPin(EN_PIN_X, HIGH);
    setPin(EN_PIN_Y, HIGH);
    setPin(EN_PIN_Z, HIGH);
}

void driveMotor(int stepPin, int dirPin, int steps, bool direction, int customDelay = STEP_DELAY_Z)
{
    setPin(dirPin, direction);
    for (int i = 0; i < steps; i++)
    {
        setPin(stepPin, HIGH);
        delayMicroseconds(customDelay);
        setPin(stepPin, LOW);
        delayMicroseconds(customDelay);
    }
}

void moveAxisX(int steps, bool direction, boolean hold = false, int customDelay = STEP_DELAY_X)
{
    setPin(EN_PIN_X, LOW);
    driveMotor(STEP_PIN_X, DIR_PIN_X, steps, direction, customDelay);

    if (!hold)
    {
        setPin(EN_PIN_X, HIGH);
    }
}

void moveAxisY(int steps, bool direction, boolean hold = false, int customDelay = STEP_DELAY_Y)
{
    setPin(EN_PIN_Y, LOW);
    driveMotor(STEP_PIN_Y, DIR_PIN_Y, steps, direction, customDelay);

    if (!hold)
    {
        setPin(EN_PIN_Y, HIGH);
    }
}

void moveAxisZ(int steps, bool direction, boolean hold = false, int customDelay = STEP_DELAY_Z)
{
    setPin(EN_PIN_Z, LOW);
    driveMotor(STEP_PIN_Z, DIR_PIN_Z, steps, direction, customDelay);

    if (!hold)
    {
        setPin(EN_PIN_Z, HIGH);
    }
}

void adjustScannerDistance(int targetDistance)
{
    int currentDistance = measureDistance();
    Serial.println(currentDistance);
    bool movingCloser = true; // Startet mit der Annahme, dass wir uns dem Ziel nähern

    while (abs(currentDistance - targetDistance) > measureDistanceTolerance)
    {
        Serial.print("Adjust distance, remaining: ");
        Serial.println(abs(currentDistance - targetDistance));

        // Bestimmt die Bewegungsrichtung basierend darauf, ob wir uns dem Ziel nähern oder entfernen
        bool direction;
        if (currentDistance > targetDistance)
        {
            direction = movingCloser; // Bewegung in Richtung Ziel
        }
        else
        {
            direction = !movingCloser; // Bewegung weg vom Ziel
        }

        int stepSize = 3000;            // Festgelegte Schrittgröße
        moveAxisZ(stepSize, direction); // Bewegt den Scanner

        int newDistance = measureDistance(); // Misst die Distanz erneut
        if (abs(newDistance - targetDistance) >= abs(currentDistance - targetDistance))
        {
            // Wenn sich der Abstand zum Ziel nicht verringert hat, ändere die Bewegungsrichtung
            movingCloser = !movingCloser;
            moveAxisZ(stepSize / 2, direction); // Bewegt den Scanner
            Serial.print("Changing direction due to no improvement, remaining:");
            Serial.println(abs(newDistance - targetDistance));
        }

        currentDistance = newDistance; // Aktualisiere den aktuellen Abstand für den nächsten Durchgang
        delay(500);                    // Kurze Verzögerung, um zu viel schnelle Bewegung zu vermeiden
    }
}

#endif
