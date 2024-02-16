// ultrasonic_sensor.h
#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

void setupUltrasonic()
{
    pinMode(ULTRASONIC_ECHO, INPUT); // Echo Pin als Eingang setzen
}

long measureDistance()
{
    long duration;

    // Sicherstellen, dass der Trigger-Pin LOW ist, um einen sauberen Start zu garantieren
    setPin(ULTRASONIC_TRIG, LOW);
    delayMicroseconds(5); // Kurze Pause, um sicherzustellen, dass der Trigger-Pin LOW ist

    // Trigger-Puls senden
    setPin(ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10); // Empfohlene Pulszeit für die meisten Ultraschallsensoren
    setPin(ULTRASONIC_TRIG, LOW);

    // Warten auf das Echo-Signal, maximal 1 Sekunde (1000000 Mikrosekunden)
    duration = pulseIn(ULTRASONIC_ECHO, HIGH, 10000);

    // Überprüfen, ob ein gültiges Signal empfangen wurde
    while (duration == 0 || duration == 1)
    {
        // Trigger-Puls erneut senden, falls kein gültiges Signal empfangen wurde
        setPin(ULTRASONIC_TRIG, HIGH);
        delayMicroseconds(10);
        setPin(ULTRASONIC_TRIG, LOW);

        duration = pulseIn(ULTRASONIC_ECHO, HIGH, 10000);
    }

    return duration; // Rückgabe der Distanz als Ganzzahl in Millimeter
}

#endif
