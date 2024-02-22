// DistanceSensor.h
#ifndef DISTANCE_SENSOR
#define DISTANCE_SENSOR

void setupDistanceSensor()
{
    pinMode(ULTRASONIC_ECHO, INPUT); // Setzt den Echo-Pin als Eingang
}

int measureDistance(int numSamples = 5)
{
    int sum = 0;
    for (int i = 0; i < numSamples; i++)
    {
        // Sendet Ultraschallwelle
        setPin(ULTRASONIC_TRIGGER, LOW);
        delayMicroseconds(2);
        setPin(ULTRASONIC_TRIGGER, HIGH);
        delayMicroseconds(10);
        setPin(ULTRASONIC_TRIGGER, LOW);

        // Misst die Zeit bis zum Echo
        int duration = pulseIn(ULTRASONIC_ECHO, HIGH);

        // Berechnet die Entfernung basierend auf der Zeit und der Schallgeschwindigkeit
        // Schallgeschwindigkeit = 343 m/s = 0.0343 cm/µs, Hin- und Rückweg, daher wird durch 2 geteilt
        int distance = (duration * 0.343) / 2;

        sum += distance;

        // Verzögerung zur Stabilisierung des Sensors, kann angepasst werden
        delay(10);
    }

    return sum / numSamples; // Gibt die durchschnittliche Entfernung zurück
}

#endif
