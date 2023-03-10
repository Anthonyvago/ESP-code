#include "influxDb.hpp"

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

const char *DEVICE = "Anthony_Windows";
const char *DEVICE_LOCATION = "Nijmegen r26 C3.08";

const char *INFLUXDB_URL = "https://influx.mvrautomatisering.nl";
const char *INFLUXDB_TOKEN = "N_TrMa5KOAA-SvOc4QwB0wrbAjXIX5r3_7VPNT37h1r2XmIyNUXwr0giBbdZTGwzjA291CA-aE3uHskR0Y0oUw==";
const char *INFLUXDB_ORG = "han";
const char *INFLUXDB_BUCKET = "Anthony_bucket";

// Set timezone so your data will actually have a correct date and time
const char *TZ_INFO = "CET-1CEST,M3.5.0,M10.5.0/3";

// InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET,
                      INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Point object called deviceStatus with measurment name "devices"
Point deviceStatus("Wifi SSID's");

const int nFields = 7;
const char fields[nFields][14] = {
    "internal_temp",
    "wifi_strength",
    "uptime",
    "light",
    "temperature",
    "humidity",
    "moisture"};

void sendToInfluxDb()
{
    // Write point to InfluxDB
    if (client.writePoint(deviceStatus))
    {
        Serial << "Point successfully written: " << endl;
        Serial << deviceStatus.toLineProtocol() << endl;
    }
    else
    {
        Serial << "Write failed: ";
        Serial << client.getLastErrorMessage() << endl;
    }
}

void setFieldsInObject(int32_t values[])
{
    for (int i = 0; i < nFields; i++)
        deviceStatus.addField(fields[i], values[i]);
}

void resetInfluxDbObject()
{
    // Clear fields for reusing the point. Tags will remain untouched
    deviceStatus.clearFields();
}

void setInfluxDbOptions()
{
    // This line sets the options for the Influx client. It means that it will
    // send data in batches of size 1 and it will send the data immediately
    // (flushInterval 0)
    client.setWriteOptions(WriteOptions().batchSize(1).flushInterval(0));
}

void setInfluxDbTags()
{
    // Here you can add tags as you please.
    deviceStatus.addTag("device", DEVICE);
    deviceStatus.addTag("location", DEVICE_LOCATION);
    deviceStatus.addTag("SSID", WiFi.SSID());
}

void setInfluxDbTime()
{
    // Sync time for proper connection and data points
    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
}

/**
 * @brief Sets up the influxDb client with the above three functions
 *
 */
void setupInfluxDb()
{
    setInfluxDbOptions();
    setInfluxDbTags();
    setInfluxDbTime();
}

void connectToInfluxDb()
{
    // Check server connection
    if (client.validateConnection())
    {
        Serial << "Connected to InfluxDB: ";
        Serial << client.getServerUrl() << endl;
    }
    else
    {
        Serial << "InfluxDB connection failed: ";
        Serial << client.getLastErrorMessage() << endl;
    }
}