#include "Network.h"
#include <WiFiClientSecure.h>
#include <WiFi.h>

bool WIFI_CONNECTED = false;
// WIFI Functions
int connectWifi(void)
{
    WiFi.begin(WIFI_SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    WIFI_CONNECTED = true;
    return 1;
}
