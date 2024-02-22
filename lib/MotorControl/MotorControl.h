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
    int currentDistance = measureDistance(); // Misst die aktuelle Entfernung
    bool wasTooClose = false;                // Indikator, ob die Distanz einmal zu nah war
    bool wasTooFar = false;                  // Indikator, ob die Distanz einmal zu weit war
    int differences[3] = {0, 0, 0};          // Speichert die letzten drei Differenzen
    int diffIndex = 0;                       // Index für das Speichern der aktuellen Differenz
    int stepsMade = 0;                       // Zählt die Anzahl der gemachten Schritte
    int lastValidDistance = currentDistance; // Speichert die letzte gültige Distanz

    // Schleife, bis die Differenz zwischen der gemessenen und der Zielentfernung innerhalb der Toleranz liegt
    while (abs(targetDistance - currentDistance) > measureDistanceTolerance)
    {
        bool direction = (currentDistance > targetDistance);   // Bestimmt die Richtung: näher ran, wenn aktuell > Ziel
        moveAxisZ(adujstDistanceSteps, direction, false, 150); // Bewegt die Z-Achse entsprechend
        stepsMade++;                                           // Inkrementiert die Anzahl der Schritte
        delay(200);                                            // relax time

        int previousDistance = currentDistance; // Speichert die vorherige Distanz
        currentDistance = measureDistance();    // Misst die Entfernung erneut nach der Anpassung

        // Überprüft, ob eine signifikante Änderung stattgefunden hat
        if (abs(currentDistance - lastValidDistance) < measureDistanceMinChange)
        { // Minimal erforderliche Änderung nicht erreicht
            Serial.print("Insignificant change, possible measurement error: ");
            Serial.println(abs(currentDistance - lastValidDistance));
            continue; // Überspringt den Rest der Schleife und misst erneut
        }
        lastValidDistance = currentDistance; // Aktualisiert die letzte gültige Distanz

        // Prüft, ob die Distanz einmal in die falsche Richtung überschritten wurde
        if (currentDistance < targetDistance)
            wasTooClose = true;
        if (currentDistance > targetDistance)
            wasTooFar = true;

        // Abbruchbedingung, wenn die Distanz zuerst zu klein und dann zu groß wird oder umgekehrt
        if ((wasTooClose && currentDistance > targetDistance) || (wasTooFar && currentDistance < targetDistance))
        {
            Serial.println("Invalid adjustment");
            break; // Beendet die Schleife und damit die Anpassung
        }

        // Speichert die aktuelle Differenz und aktualisiert den Index
        differences[diffIndex] = targetDistance - currentDistance;
        diffIndex = (diffIndex + 1) % 3; // Sorgt dafür, dass der Index im Bereich von 0 bis 2 bleibt

        // Überprüft, ob die letzten drei Differenzen gleich sind
        if (differences[0] == differences[1] && differences[1] == differences[2] && differences[0] != 0)
        {
            Serial.print("Adjustment failed: same difference three times: ");
            Serial.println(differences[0]);

            break; // Beendet die Schleife und damit die Anpassung
        }

        Serial.print("Adjust Difference :");
        Serial.println(targetDistance - currentDistance);
    }

    if (stepsMade > 0)
    {
        // Berechnet die Richtung für die Rückfahrt (umgekehrt zur letzten Bewegungsrichtung)
        bool returnDirection = !(currentDistance > targetDistance);
        // Fährt die Z-Achse zurück in die Ausgangsposition
        for (int i = 0; i < stepsMade; i++)
        {
            Serial.println("Returning to original position");
            moveAxisZ(adujstDistanceSteps, returnDirection, false, 150);
        }
    }
}

#endif
