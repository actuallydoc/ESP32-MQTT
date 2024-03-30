#include "MQTT.h"

String client_id = "esp32-client-"; // Define client_id

WiFiClientSecure espClient;
PubSubClient client(espClient); // Define client

int connectMQTT(void)
{
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback);
    while (!client.connected())
    {

        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), MQTT_USER, MQTT_PASSWORD))
        {
            Serial.println("Public EMQX MQTT broker connected");
        }
        else
        {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    return 1;
}

void publishMessage(String message)
{
    if (client.connected())
    {
        client.publish(DEFAULT_TOPIC, message.c_str());
    }
}

void callback(char *topic, byte *message, unsigned int length)
{
    if (strcmp(topic, DEFAULT_COMMAND_TOPIC) == 0)
    {
        Serial.println("Command received");
        String messageTemp;
        for (int i = 0; i < length; i++)
        {
            messageTemp += (char)message[i];
        }
        Serial.println(messageTemp);
    }
    else
    {
        Serial.println("Message received");
        Serial.print("Message arrived on topic: ");
        Serial.print(topic);
        Serial.print(". Message: ");
        String messageTemp;

        for (int i = 0; i < length; i++)
        {
            Serial.print((char)message[i]);
            messageTemp += (char)message[i];
        }
        Serial.println();
    }
}