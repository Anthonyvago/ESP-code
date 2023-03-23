#include "light_sensor.hpp"

const uint8_t PIN_LIGHT_SENSOR = 39;

// No setup needed for this sensor

/**
 * @brief Get the analog light value
 *
 * @return uint16_t - Analog light value
 */
uint16_t get_analog_light_value()
{
    return analogRead(PIN_LIGHT_SENSOR);
}

/**
 * @brief Convert the analog light value to a string value such as "Dark", "Dim", "Light", "Bright" or "Very bright"
 *
 * @param buff The value above will be written into this character pointer
 */
void convert_analog_light_value_to_string(char *buff)
{
    // Check if the buffer is valid
    if (buff == NULL)
    {
        Serial << "Error: buffer is NULL" << endl;
        return;
    }

    uint16_t analog_light_value = get_analog_light_value();

    // Convert the analog value to a string value
    if (analog_light_value < 40)
        strcpy(buff, "Dark");
    else if (analog_light_value < 1000)
        strcpy(buff, "Dim");
    else if (analog_light_value < 2000)
        strcpy(buff, "Light");
    else if (analog_light_value < 3200)
        strcpy(buff, "Bright");
    else
        strcpy(buff, "Very bright");
}