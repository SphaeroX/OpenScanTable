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

void moveAxisX(int steps, bool direction, int customDelay = STEP_DELAY_X)
{
    setPin(EN_PIN_X, LOW);
    setPin(DIR_PIN_X, direction);
    for (int i = 0; i < steps; i++)
    {
        setPin(STEP_PIN_X, HIGH);
        delayMicroseconds(customDelay);
        setPin(STEP_PIN_X, LOW);
        delayMicroseconds(customDelay);
    }
}

void moveAxisY(int steps, bool direction, int customDelay = STEP_DELAY_Y)
{
    setPin(EN_PIN_Y, LOW);
    setPin(DIR_PIN_Y, direction);
    for (int i = 0; i < steps; i++)
    {
        setPin(STEP_PIN_Y, HIGH);
        delayMicroseconds(customDelay);
        setPin(STEP_PIN_Y, LOW);
        delayMicroseconds(customDelay);
    }
}

void moveAxisZ(int steps, bool direction, int customDelay = STEP_DELAY_Z)
{
    setPin(EN_PIN_Z, LOW);
    setPin(DIR_PIN_Z, direction);
    for (int i = 0; i < steps; i++)
    {
        setPin(STEP_PIN_Z, HIGH);
        delayMicroseconds(customDelay);
        setPin(STEP_PIN_Z, LOW);
        delayMicroseconds(customDelay);
    }
}

void adjustScannerDistance(int targetDistance)
{
    int currentDistance = measureDistance();
    Serial.println(currentDistance);
    bool direction = LOW; // Startet mit einer angenommenen Richtung

    // Führt eine kleine Testbewegung aus, um die korrekte Richtung zu bestimmen
    moveAxisZ(100, direction); // Bewegt einen Schritt in der anfänglichen Richtung
    int newDistance = measureDistance();
    moveAxisZ(100, !direction); // Bewegt einen Schritt in der anfänglichen Richtung

    // Bestimmt, ob sich der Abstand durch die Bewegung vergrößert oder verkleinert hat
    if (newDistance > currentDistance)
    {
        // Wenn der Abstand größer wird, ist die anfängliche Richtung falsch
        direction = !direction; // Wechselt die Richtung
    }

    // Anpassung der Distanz mit der ermittelten Richtung
    while (abs(currentDistance - targetDistance) > measureDistanceTolerance)
    {
        Serial.println(abs(currentDistance - targetDistance));
        int stepSize = 3000;

        // Bewegt den Scanner in der ermittelten richtigen Richtung
        moveAxisZ(stepSize, direction);

        int previousDistance = currentDistance;
        currentDistance = measureDistance(); // Misst die Distanz erneut

        // Überprüft, ob die Richtung angepasst werden muss, falls der Abstand sich nicht wie erwartet verändert
        if ((direction == LOW && currentDistance > previousDistance) || (direction == HIGH && currentDistance < previousDistance))
        {
            direction = !direction;              // Wechselt die Richtung, falls die Bewegung den Abstand nicht wie erwartet anpasst
            moveAxisZ(stepSize, direction);      // Macht einen Schritt in der neuen Richtung
            currentDistance = measureDistance(); // Misst die Distanz erneut
        }
        delay(500);
    }
}

#endif
