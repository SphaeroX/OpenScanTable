// ScanRoutine.h
#ifndef SCAN_ROUTINE_H
#define SCAN_ROUTINE_H

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
  // Messung und Speicherung der initialen Distanz zu Beginn des Scans
  initialDistance = measureDistance();

  // Berechnung der Schritte pro Grad
  float stepsPerDegree = 6400.0 / 360.0;

  for (int yRot = 0; yRot < yRotations; yRot++)
  {
    int ySteps = round(yDegrees * stepsPerDegree);
    for (int zRot = 0; zRot < zRotations; zRot++)
    {
      int zSteps = round(zDegrees * stepsPerDegree);

      // Bewege X-Achse um angegebene Gradzahl
      Serial.println("Rotate Z");
      moveAxisX(zSteps, true); // Richtung ist hier als 'true' angenommen; anpassen, falls nötig
      delay(pauseDuration);

      // Überprüfe die Distanz und passe an, wenn nötig
      long currentDistance = measureDistance();
      if (abs(currentDistance - initialDistance) > measureDistanceTolerance)
      {
        // adjustScannerDistance(initialDistance); // Korrigiert die Distanz zurück zum Initialwert
        // delay(pauseDuration);
      }

      // Auslösen des Scanners (hier symbolisch durch Senden eines Leerzeichens über Bluetooth)
      sendKeystroke(revoScanTrigger); // Anpassen an deine Implementierung für die Auslösung
      delay(pauseDuration);
    }

    // Bewege Y-Achse nach jeder Z-Rotation um die angegebene Gradzahl
    moveAxisY(ySteps, true); // Richtung ist hier ebenfalls als 'true' angenommen; anpassen, falls nötig
    Serial.println("Rotate Y");
    delay(pauseDuration);
  }
}

#endif
