#include <Arduino.h>
#include <PrintStream.h>


void wifiSetup();

bool checkWifiStillConnected();

int8_t get_wifi_strength();

void wifiConnect();