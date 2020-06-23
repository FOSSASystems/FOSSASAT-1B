#include <Arduino.h>
#include <unity.h>
#include "power_control.h"

void ina226_check_response()
{
	Power_Control_Setup_INA226();
	TEST_ASSERT_TRUE(Power_Control_INA226_Check());
}

void ina226_check_battery_range()
{
	TEST_ASSERT_FLOAT_WITHIN(0.1, 5.0, Power_Control_Get_Battery_Voltage());
}

