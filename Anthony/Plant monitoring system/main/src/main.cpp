#include <Arduino.h>
#include <math.h>

#include <PrintStream.h>

#include "wifi.hpp"
#include "influxDb.hpp"
#include "dht11.hpp"
#include "moisture_sensor.hpp"
#include "rf_transmitter.hpp"
#include "water_pump_relais.hpp"
#include "light_sensor.hpp"

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

  // Setup the wifi
  wifiSetup();
  wifiConnect();

  // Setup the influxDb
  setupInfluxDb();
  connectToInfluxDb();

  // Setup the sensors
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

  int nFields = 7;
  int32_t values[nFields] = {
      (int32_t)(temprature_sens_read() - 32) * 5 / 9,
      (int32_t)get_wifi_strength(),
      (int32_t)millis() / 1000,
      (int32_t)get_analog_light_value(),
      (int32_t)get_temperature(),
      (int32_t)get_humidity(),
      (int32_t)get_moisture()};

  setFieldsInObject(values);

  char lightValueInContext[12];
  convert_analog_light_value_to_string(lightValueInContext);
  Serial << "Light value: " << lightValueInContext << endl;

  // Check Wi-Fi connection and reconnect if needed
  if (!checkWifiStillConnected())
  {
    return;
  }

  sendToInfluxDb();
}
