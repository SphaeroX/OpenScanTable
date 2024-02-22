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
  // Verbesserte Initialmessung
  int initialDistance = 0;

  if (autoAdjust)
  {
    int lowestDistance = measureDistance();
    int currentDistance;

    for (int i = 0; i < 5; i++)
    {
      moveAxisX(150, true);                // Bewegt die Y-Achse um 10 Schritte; Richtung 'true' angenommen
      currentDistance = measureDistance(); // Führt eine Distanzmessung durch

      if (currentDistance < lowestDistance)
      {
        lowestDistance = currentDistance; // Aktualisiert die niedrigste Distanz
      }
    }

    // Setzt die Y-Achse zurück zum Ausgangspunkt, bevor der eigentliche Scan beginnt
    moveAxisX(750, true); // Annahme: Bewegung zurück; Wert muss ggf. angepasst werden

    initialDistance = lowestDistance; // Setzt die niedrigste gemessene Distanz als initiale Distanz
    Serial.print("initialDistance: ");
    Serial.println(initialDistance);
  }
  if (yRotations == 0)
  {
    yRotations = 1;
  }

  // Berechnung der Schritte pro Grad
  float stepsPerDegree = 6400.0 / 360.0;
  int ySteps = round(yDegrees * stepsPerDegree);
  int zSteps = round(zDegrees * stepsPerDegree);

  for (int yRot = 0; yRot < yRotations; yRot++)
  {
    for (int zRot = 0; zRot < zRotations; zRot++)
    {
      // Bewege X-Achse um angegebene Gradzahl
      Serial.println("Rotate Z");
      moveAxisX(zSteps, true);        // Richtung ist hier als 'true' angenommen; anpassen, falls nötig
      delay(pauseDuration);           // relax time
      sendKeystroke(revoScanTrigger); // Anpassen an deine Implementierung für die Auslösung
      delay(200);

      // Überprüfe die Distanz und passe an, wenn nötig
      if (autoAdjust)
      {
        long currentDistance = measureDistance();
        Serial.print("initialDistance: ");
        Serial.println(initialDistance);
        Serial.print("currentDistance: ");
        Serial.println(currentDistance);
        Serial.print("difference: ");
        Serial.println(initialDistance - currentDistance);

        if (abs(currentDistance - initialDistance) > measureDistanceTolerance && abs(currentDistance - initialDistance) <= measureDistanceFailMax)
        {
          adjustScannerDistance(initialDistance); // Korrigiert die Distanz zurück zum Initialwert
        }
      }
    }

    // Bewege Y-Achse nach jeder Z-Rotation um die angegebene Gradzahl
    moveAxisY(ySteps, true, true); // Richtung ist hier ebenfalls als 'true' angenommen; anpassen, falls nötig
    Serial.println("Rotate Y");
  }

  moveAxisY(ySteps * yRotations, false); // Bewege X-Achse wieder zurück zum Nullwert
}

#endif
