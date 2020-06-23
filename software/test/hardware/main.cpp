#include <Arduino.h>
#include <unity.h>
#include "ina226.h"

void setup()
{
	UNITY_BEGIN();
    RUN_TEST(ina226_check_response);
	RUN_TEST(ina226_check_battery_range);
	UNITY_END();
}

void loop()
{
}

