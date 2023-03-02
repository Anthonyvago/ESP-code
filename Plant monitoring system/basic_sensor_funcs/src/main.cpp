#include <Arduino.h>
#include <PrintStream.h>

#include "moisture_sensor.h"
#include "water_pump_relais.h"
#include "dht11.h"
#include "rf_transmitter.h"

void setup()
{
    Serial.begin(115200);

    setup_water_pump_relais(); // setup water pump relais

    setup_dht11(); // setup DHT11 sensor
}

uint64_t curMillis = 0;
uint64_t prevMillis = 0;
uint16_t interval = 1000;

void loop()
{
    curMillis = millis();
    if (curMillis - prevMillis >= interval)
    {
        // MOISTURE SENSOR:
        uint16_t moistValue = get_moisture_sensor_value();
        Serial << "Moisture sensor value: " << moistValue << endl;

        // WATER PUMP RELAIS:
        switch_water_pump();
        Serial << "Water pump status: " << get_water_pump_status() << endl;

        // DHT11 SENSOR:
        float h = get_humidity();
        float t = get_temperature();
        Serial << "Humidity: " << h << " %\tTemperature: " << t << " °C" << endl;

        // KAKU SWITCH (RF transmitter):
        switch_rf_transmitter();
        Serial << "RF transmitter status: " << get_rf_transmitter_status() << endl;

        prevMillis = curMillis;
    }
}