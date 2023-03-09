#include <Arduino.h>
#include <PrintStream.h>

void setFieldsInObject(int nFields, char *fields[], int64_t values[]);

void sendToInfluxDb();

void resetInfluxDbObject();

void setInfluxDbOptions();

void setInfluxDbTags();

void setInfluxDbTime();

void setupInfluxDb();

void connectToInfluxDb();