#include "moisture_sensor.h"

int moistSensPin = 36;


uint16_t get_moisture_sensor_value()
{
    return analogRead(moistSensPin);
}
