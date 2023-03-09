#include "rf_transmitter.hpp"

#define TRANSMITTERID1 123456
#define rfPin 25

bool rf_transmitter_is_on = false;

void set_rf_transmitter(bool state)
{
    switchKaku(rfPin, TRANSMITTERID1, 1, 1, state, 3);
    rf_transmitter_is_on = state;
}

void switch_rf_transmitter()
{
    if (rf_transmitter_is_on)
    {
        set_rf_transmitter(false);
    }
    else
    {
        set_rf_transmitter(true);
    }
}


bool get_rf_transmitter_status()
{
    return rf_transmitter_is_on;
}