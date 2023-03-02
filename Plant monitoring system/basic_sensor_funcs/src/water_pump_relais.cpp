#include "water_pump_relais.h"

int pumpPin = 33;
bool water_pump_is_on = false;


void setup_water_pump_relais()
{
    pinMode(pumpPin, OUTPUT);
}


void set_water_pump(bool on)
{
    if (on)
    {
        digitalWrite(pumpPin, HIGH);
        water_pump_is_on = true;
    }
    else
    {
        digitalWrite(pumpPin, LOW);
        water_pump_is_on = false;
    }
}


void switch_water_pump()
{
    if (water_pump_is_on)
    {
        digitalWrite(pumpPin, LOW);
        water_pump_is_on = false;
    }
    else
    {
        digitalWrite(pumpPin, HIGH);
        water_pump_is_on = true;
    }
}


bool get_water_pump_status()
{
    return water_pump_is_on;
}