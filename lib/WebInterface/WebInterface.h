// web_interface.h
#ifndef WEB_INTERFACE_H
#define WEB_INTERFACE_H

#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
#include <SPIFFS.h>

const char *ssid = "ESP32-AP";     // Set your desired AP SSID
const char *password = "password"; // Set your desired AP password

WebServer server(80);

void handleRoot()
{
    File file = SPIFFS.open("/index.html", "r"); // Öffnet die Datei index.html im Lesemodus
    if (!file)
    {
        // Wenn die Datei nicht geöffnet werden kann, senden Sie eine Fehlermeldung
        Serial.println("Failed to open file for reading");
        server.send(500, "text/plain", "Error loading index.html");
        return;
    }

    // Verwenden Sie server.streamFile() um die Datei direkt zu senden und als "text/html" zu kennzeichnen
    server.streamFile(file, "text/html");
    file.close(); // Schließen Sie die Datei nach dem Senden
}

void handleStartRevoscan()
{
    commandState = 200;

    zDegrees = server.arg("zDegrees").toInt();
    zRotations = server.arg("zRotations").toInt();
    yDegrees = server.arg("yDegrees").toInt();
    yRotations = server.arg("yRotations").toInt();
    scanShotPause = server.arg("scanShotPause").toInt();
    int autoAdjustValue = server.arg("autoAdjust").toInt();

    if (autoAdjustValue == 1)
    {
        autoAdjust = true;
    }
    else
    {
        autoAdjust = false;
    }

    server.send(200, "text/plain", "Starting revo scan");
}

void handleSaveSettings()
{
    scanShotPause = server.arg("scanShotPause").toInt();
    revoScanTrigger = server.arg("revoScanTrigger").toInt();

    commandState = 100;
    server.send(200, "text/plain", "Starting revo scan");
}

void handleTestAxes()
{
    commandState = 900;
    server.send(200, "text/plain", "Test");
}

void handleTestDistance()
{
    commandState = 910;
    server.send(200, "text/plain", "Test");
}

void setupWebServer()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    // Configure ESP32 as an access point
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);

    // Print ESP32 IP address
    Serial.println("HTTP server started");
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());

    // Set up routes
    server.on("/", handleRoot);
    server.on("/startRevoscan", handleStartRevoscan);
    server.on("/saveSettings", handleSaveSettings);
    server.on("/testAxes", handleTestAxes);
    server.on("/testDistance", handleTestDistance);

    // Start server
    server.begin();
}

void loopWebServer()
{
    server.handleClient();
}

#endif
