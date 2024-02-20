// DistanceSensor.h
#ifndef DISTANCE_SENSOR
#define DISTANCE_SENSOR

#include <VL53L0X.h>

VL53L0X sensor;

void setupDistanceSensor()
{
    sensor.init();
    sensor.setTimeout(500);
    // Start continuous back-to-back mode (take readings as fast as possible).
    // To use continuous timed mode, provide a desired inter-measurement period in ms (e.g., sensor.startContinuous(100)).
    sensor.startContinuous();
}

long measureDistance(int numSamples = 10)
{
    long sum = 0;
    for (int i = 0; i < numSamples; i++)
    {
        sum += sensor.readRangeContinuousMillimeters();
        if (sensor.timeoutOccurred())
        {
            Serial.print("Sensor timeout!");
            return -1; // Return -1 if a timeout occurs
        }
    }
    return sum / numSamples; // Return the average distance
}

#endif
