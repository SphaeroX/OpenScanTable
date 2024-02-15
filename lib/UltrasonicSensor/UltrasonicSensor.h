// ultrasonic_sensor.h
#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

void setupUltrasonic()
{
    pinMode(ULTRASONIC_TRIG, OUTPUT); // Trig Pin als Ausgang setzen
    pinMode(ULTRASONIC_ECHO, INPUT);  // Echo Pin als Eingang setzen
}

long measureDistance()
{
    delay(200); // Entspannungszeit
    long duration;
    float distance;
    digitalWrite(ULTRASONIC_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG, LOW);
    duration = pulseIn(ULTRASONIC_ECHO, HIGH);
    distance = (duration / 2.0) / 29.1 * 10.0; // Korrekte Berechnung in Millimeter als Fließkommazahl

    // Konvertierung des Ergebnisses in eine Ganzzahl
    return (long)distance; // Umwandlung in long, wobei Nachkommastellen abgeschnitten werden
}

#endif
