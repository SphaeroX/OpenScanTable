// DistanceSensor.h
#ifndef DISTANCE_SENSOR
#define DISTANCE_SENSOR

void setupDistanceSensor()
{
    pinMode(ULTRASONIC_ECHO, INPUT);
}

int measureDistance(int numSamples = 5)
{
    delay(300); // relax time

    int sum = 0;
    for (int i = 0; i < numSamples; i++)
    {
        setPin(ULTRASONIC_TRIGGER, LOW);
        delayMicroseconds(2);
        setPin(ULTRASONIC_TRIGGER, HIGH);
        delayMicroseconds(10);
        setPin(ULTRASONIC_TRIGGER, LOW);

        int duration = pulseIn(ULTRASONIC_ECHO, HIGH);
        int distance = (duration * 0.343) / 2;

        sum += distance;

        delay(10);
    }

    return sum / numSamples;
}

#endif
