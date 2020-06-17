#include <unity.h>
#include <power_control.h>

void check_response()
{
    Power_Control_Setup_INA226();
    TEST_ASSERT_TRUE(Power_Control_INA226_Check());
}

void setup()
{
	UNITY_BEGIN();
    RUN_TEST(check_response);
	UNITY_END();
}

void loop()
{
}

