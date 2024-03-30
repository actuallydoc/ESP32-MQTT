#include <NTPClient.h>
#include <WifiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);