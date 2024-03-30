#include <Arduino.h>
#include <ArduinoJson.h>
#include "Networking/Network.h"
#include "Networking/MQTT.h"
#include "Utils/Time.h"
#include "cert.h"
#include <Wire.h>
#include <DHT.h>
#define DHT_PIN 23
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);
void setup()
{

  // Setup the certificate
  espClient.setCACert(ca_cert);
  // Begin UART transmittion
  Serial.begin(115200);

  if (connectWifi() == 1)
  {
    Serial.println("Connected to the WiFi network");
  }

  // Connect to MQTT
  if (connectMQTT() == 1)
  {
    Serial.println("Connected to the MQTT network");
  }
  // Time setup
  timeClient.begin();
  // DHT setup
  dht.begin();
}

void loop()
{
  // Update the time
  timeClient.update();

  // Get the timestamp
  long timeStamp = timeClient.getEpochTime();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // override the temperature and humidity values
  temperature = 25.0;
  humidity = 50.0;

  // Construct the JSON string with the timestamp
  String message = "{\"device_id\": \"" + String(client_id) + "\", \"sensor_name\": \"dht11\", \"humidity\": \"" + String(humidity) + "\", \"temperature\": \"" + String(temperature) + "\", \"timestamp\": \"" + String(timeStamp) + "\"}";

  // Publish the message to the MQTT broker
  publishMessage(message);

  // Wait for 5 seconds
  client.loop();
  delay(5000);
}
