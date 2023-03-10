#include <Arduino.h>
#include <PrintStream.h>

void setFieldsInObject(int32_t values[]);

void sendToInfluxDb();

void resetInfluxDbObject();

void setInfluxDbOptions();

void setInfluxDbTags();

void setInfluxDbTime();

void setupInfluxDb();

void connectToInfluxDb();