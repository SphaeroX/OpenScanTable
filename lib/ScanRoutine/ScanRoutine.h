// ScanRoutine.h
#ifndef SCAN_ROUTINE_H
#define SCAN_ROUTINE_H

int getMedianDistance(int measurementsPerDirection)
{
  const int totalMeasurements = measurementsPerDirection * 2;

  int distances[totalMeasurements];

  for (int i = 0; i < measurementsPerDirection; i++)
  {
    moveAxisX(150, true);
    distances[i] = measureDistance();
  }

  for (int i = measurementsPerDirection; i < totalMeasurements; i++)
  {
    moveAxisX(150, false);
    distances[i] = measureDistance();
  }

  // Sort for Median
  for (int i = 0; i < totalMeasurements - 1; i++)
  {
    for (int j = 0; j < totalMeasurements - i - 1; j++)
    {
      if (distances[j] > distances[j + 1])
      {
        int temp = distances[j];
        distances[j] = distances[j + 1];
        distances[j + 1] = temp;
      }
    }
  }

  // Calc Median
  int medianDistance;
  if (totalMeasurements % 2 == 0)
  {
    medianDistance = (distances[totalMeasurements / 2 - 1] + distances[totalMeasurements / 2]) / 2;
  }
  else
  {
    medianDistance = distances[totalMeasurements / 2];
  }

  Serial.print("Median Distance: ");
  Serial.println(medianDistance);
  return medianDistance;
}

/**
 * Performs a revolving scan by rotating the X and Y axes.
 *
 * Rotates the X axis by the specified number of degrees and rotations.
 * After each X rotation, rotates the Y axis by the specified degrees and rotations.
 * Measures and adjusts the distance before taking each scan measurement.
 * Sends a trigger to take the scan measurement after adjusting distance.
 *
 * @param zDegrees Degrees to rotate X axis each iteration
 * @param zRotations Number of rotations on X axis
 * @param yDegrees Degrees to rotate Y axis each iteration
 * @param yRotations Number of rotations on Y axis
 * @param pauseDuration Milliseconds to pause between each rotation and measurement
 */
void performRevoScan(int zDegrees, int zRotations, int yDegrees, int yRotations, int pauseDuration)
{
  int initialDistance = 0;

  if (yRotations == 0)
  {
    yRotations = 1;
  }

  float stepsPerDegree = 6400.0 / 360.0;
  int ySteps = round(yDegrees * stepsPerDegree);
  int zSteps = round(zDegrees * stepsPerDegree);

  for (int yRot = 0; yRot < yRotations; yRot++)
  {
    if (yRot > 0)
    {
      moveAxisY(ySteps, true, true);
      Serial.println("Rotate Y");
    }

    if (autoAdjust)
    {
      int medianDistance = getMedianDistance(5);
      if (medianDistance)
      {
        initialDistance = medianDistance;
      }
      else
      {
        autoAdjust = false;
        Serial.println("No median distance found, cancel AutoAdjust");
      }
    }

    for (int zRot = 0; zRot < zRotations; zRot++)
    {
      Serial.println("Rotate Z");
      moveAxisX(zSteps, true);

      if (autoAdjust)
      {
        long currentDistance = measureDistance();

        Serial.print("initialDistance: ");
        Serial.println(initialDistance);
        Serial.print("currentDistance: ");
        Serial.println(currentDistance);

        adjustScannerDistance(initialDistance);
      }

      delay(pauseDuration); // relax time
      sendKeystroke(revoScanTrigger);
      delay(scanShotPause);
    }
  }

  moveAxisY(ySteps * (yRotations - 1), false);
}

#endif
