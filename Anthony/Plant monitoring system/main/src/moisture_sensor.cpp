#include "moisture_sensor.hpp"

int moistSensPin = 36;


uint16_t get_moisture()
{
    return analogRead(moistSensPin);
}
