// IOExpander.h
#ifndef SCAN_ROUTINE_H
#define SCAN_ROUTINE_H

void performRevoScan(int zDegrees, int zRotations, int yDegrees, int yRotations, int scannerDistance, int pauseDuration)
{
  for (int yRot = 0; yRot < yRotations; yRot++)
  {
    for (int zRot = 0; zRot < zRotations; zRot++)
    {
      // Bewege Z-Achse um angegebene Gradzahl
      moveAxisZ(zDegrees, true); // Richtung ist hier als 'true' angenommen; anpassen, falls nötig
      delay(pauseBetweenScanmoves);

      // Überprüfe die Distanz und passe an, wenn nötig
      long currentDistance = measureDistance();
      if (currentDistance != scannerDistance)
      {
        adjustScannerDistance(scannerDistance); // Implementierung dieser Funktion muss vorhanden sein
        delay(pauseBetweenScanmoves);
      }

      // Auslösen des Scanners (hier symbolisch durch Senden eines Leerzeichens über Bluetooth)
      sendKeystroke(revoScanTrigger); // Anpassen an deine Implementierung für die Auslösung
      delay(pauseBetweenScanmoves);
    }

    // Bewege Y-Achse nach jeder Z-Rotation um die angegebene Gradzahl
    moveAxisY(yDegrees, true); // Richtung ist hier ebenfalls als 'true' angenommen; anpassen, falls nötig
    delay(pauseBetweenScanmoves);
  }
}

#endif
