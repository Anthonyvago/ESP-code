#include <Arduino.h>
#include <math.h>

#include "wifi.hpp"
#include "influxDb.hpp"
#include "dht11.hpp"
#include "moisture_sensor.hpp"
#include "rf_transmitter.hpp"
#include "water_pump_relais.hpp"

#include "PrintStream.h"

#ifdef __cplusplus
extern "C"
{
#endif
  uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

void setup()
{
  // Serial is always good to use for debugging!
  Serial.begin(115200);

  wifiSetup();
  wifiConnect();

  setupInfluxDb();
  connectToInfluxDb();

  setup_dht11();
  setup_water_pump_relais();
}

uint64_t lastMillis = 0;
const uint16_t LOOP_INTERVAL = 10000; // 10 seconds

void doLoop();

void loop()
{
  uint64_t curMillis = millis();
  if (curMillis - lastMillis >= LOOP_INTERVAL)
  {
    lastMillis = curMillis;

    doLoop();
  }
}

/**
 * @brief Following function is called every LOOP_INTERVAL milliseconds
 *
 */
void doLoop()
{
  resetInfluxDbObject(); // Resets the influxDb object

  int nFields = 6;

  char *fields[nFields] = {
    "internal_temp",
    "wifi_strength",
    "uptime",
    "temperature",
    "humidity",
    "moisture"
  };

  int64_t values[nFields] = {
    (int64_t)(temprature_sens_read() - 32) * 5 / 9,
    (int64_t)get_wifi_strength(),
    (int64_t)millis() / 1000,
    (int64_t)get_temperature(),
    (int64_t)get_humidity(),
    (int64_t)get_moisture()
  };

  setFieldsInObject(nFields, fields, values);

  // Check Wi-Fi connection and reconnect if needed
  if (!checkWifiStillConnected())
  {
    return;
  }

  sendToInfluxDb();
}
