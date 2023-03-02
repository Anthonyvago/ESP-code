#include "dht11.h"

#define DHT_PIN 32
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup_dht11()
{
    dht.begin();
}

float get_humidity()
{
    float humidity = dht.readHumidity();
    if ( isnan(humidity) )
    {
        Serial.println(F("Failed to read humidity from DHT sensor!"));
        return 0;
    }

    return humidity;
}

float get_temperature()
{
    float temperature = dht.readTemperature();
    if ( isnan(temperature) )
    {
        Serial.println(F("Failed to read temperature from DHT sensor!"));
        return 0;
    }

    return temperature;
}