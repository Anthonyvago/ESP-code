#include "wifi.hpp"

#include <WiFiMulti.h>

// Wi-Fi and Influx settings
WiFiMulti wifiMulti;

const char *WIFI_SSID = "TP Link slaapkamer Anthony";
const char *WIFI_PASSWORD = "alexandra02";

void wifiSetup()
{
    // Setup wifi
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
}

bool checkWifiStillConnected()
{
    if (wifiMulti.run() != WL_CONNECTED)
    {
        Serial << "Wifi connection lost... Restart device!" << endl;
        return false;
    }
    return true;
}

int8_t get_wifi_strength()
{
    return WiFi.RSSI();
}

void wifiConnect()
{
    Serial << "Connecting to wifi...";
    while (wifiMulti.run() != WL_CONNECTED)
    {
        Serial << ".";
        delay(100);
    }
    Serial << endl;

    Serial << "WiFi connected." << endl;
    Serial << "IP address: ";
    Serial << WiFi.localIP() << endl;
}