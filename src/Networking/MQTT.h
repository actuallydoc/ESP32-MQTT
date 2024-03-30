
#ifndef MQTT_H
#define MQTT_H
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

#define MQTT_SERVER ""
#define MQTT_PORT 8883
#define MQTT_USER ""
#define MQTT_PASSWORD ""
#define DEFAULT_TOPIC ""
#define DEFAULT_COMMAND_TOPIC ""
extern String client_id;

extern WiFiClientSecure espClient;
extern PubSubClient client;

void callback(char *topic, byte *message, unsigned int length);
int connectMQTT(void);
void publishMessage(String message);

#endif
