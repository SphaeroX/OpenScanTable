// MotorControl.h
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

void textAxes()
{
    moveAxisX(3000, true);
    delay(1000);
    Serial.println("Testing Y (CW/CCW)");
    moveAxisY(1000, true, true);
    moveAxisY(1000, false, true);
    moveAxisY(1000, true, true);
    moveAxisY(1000, false, true);
    moveAxisY(1000, true, true);
    moveAxisY(1000, false);
    delay(1000);
    Serial.println("Testing Z (DOWN/UP)");
    moveAxisZ(1600, true);
    moveAxisZ(1600, false);
    moveAxisZ(1600, true);
    moveAxisZ(1600, false);
    moveAxisZ(1600, true);
    moveAxisZ(1600, false);
    delay(1000);
    Serial.println("DONE");
}

void adjustScannerDistance(int targetDistance)
{
    int currentDistance = measureDistance();
    int distanceDifference = targetDistance - currentDistance;
    int absDistanceDifference = abs(targetDistance - currentDistance);

    if (abs(distanceDifference) > measureDistanceTolerance)
    {
        bool direction = distanceDifference < 0;
        int stepsNeeded = absDistanceDifference * stepsPerMillimeter;

        Serial.print("stepsNeeded: ");
        Serial.println(stepsNeeded);

        Serial.print("absDistanceDifference: ");
        Serial.println(absDistanceDifference);

        // Plausibilitätscheck
        if (absDistanceDifference < measureDistanceMaxChange)
        {
            Serial.println("Adjust the Distance.");
            moveAxisZ(stepsNeeded, direction, false, 150);
            return;
        }
        else
        {
            Serial.println("Error: Distance change out of bounds. Reverting movement.");
            return;
        }
    }
    else
    {
        Serial.println("Distance is within tolerance. No adjustment needed.");
    }
}

#endif
