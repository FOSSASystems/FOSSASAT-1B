/*
MIT License

Copyright (c) 2020 FOSSA Systems

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "auto_int.h"

void AutoInt_TestRunner_Start()
{
}


/**
*	@brief Reference ID: 		AUTOINT1
*			Description: 		Check that the intervals returned for a given battery charged level matches the specified table of delays.
*			Successful result: 	Simulate the battery charging level at the specified thresholds (using bounds testing too) and
								check the interval changes according to the specified delays (see Julian for spec)
*			Date Log:			05/07/2020 - R.Bamford
*								10/07/2020 - R.Bamford - Cannot test this since we cannot control battery voltage.
*/
void AutoInt_T1()
{
	// See date log
}

/**
*	@brief Reference ID: 		AUTOINT2
*			Description: 		Check that the maximum and minimum intervals do not cause errors. (resetting loops)
*			Successful result: 	When the satellite is delayed, does it restart when it should?
								does it get into a restart loop anywhere? check this
*			Date Log:			05/07/2020 - R.Bamford
*								10/07/2020 - R.Bamford - Using the values from power_control.h commit cc3330c5168ddbc09d68642ab37971dc3a5a73f3 
*/
void AutoInt_T2()
{
	//
	// 1. Check that the intervals are waiting without restarting.
	//
	{
		uint32_t interval = INTERVAL_MIN;

		// 1.1 Sleep true, radio sleep true 
		Power_Control_Delay(interval, true, true);
		TEST_ASSERT_TRUE(true);

		// 1.2. Sleep true, radio sleep false.
		Power_Control_Delay(interval, true, false);
		TEST_ASSERT_TRUE(true);

		// 1.3. Sleep false, radio sleep true
		Power_Control_Delay(interval, false, true);
		TEST_ASSERT_TRUE(true);

		// 1.4. Sleep false, radio sleep false
		Power_Control_Delay(interval, false, false);
		TEST_ASSERT_TRUE(true);
	}


	{
		uint32_t interval = INTERVAL_1;

		// 2.1 Sleep true, radio sleep true 
		Power_Control_Delay(interval, true, true);
		TEST_ASSERT_TRUE(true);

		// 2.2. Sleep true, radio sleep false.
		Power_Control_Delay(interval, true, false);
		TEST_ASSERT_TRUE(true);

		// 2.3. Sleep false, radio sleep true
		Power_Control_Delay(interval, false, true);
		TEST_ASSERT_TRUE(true);

		// 2.4. Sleep false, radio sleep false
		Power_Control_Delay(interval, false, false);
		TEST_ASSERT_TRUE(true);
	}

	{
		uint32_t interval = INTERVAL_2;

		// 3.1 Sleep true, radio sleep true 
		Power_Control_Delay(interval, true, true);
		TEST_ASSERT_TRUE(true);

		// 3.2. Sleep true, radio sleep false.
		Power_Control_Delay(interval, true, false);
		TEST_ASSERT_TRUE(true);

		// 3.3. Sleep false, radio sleep true
		Power_Control_Delay(interval, false, true);
		TEST_ASSERT_TRUE(true);

		// 3.4. Sleep false, radio sleep false
		Power_Control_Delay(interval, false, false);
		TEST_ASSERT_TRUE(true);
	}

	{
		uint32_t interval = INTERVAL_3;

		// 4.1 Sleep true, radio sleep true 
		Power_Control_Delay(interval, true, true);
		TEST_ASSERT_TRUE(true);

		// 4.2. Sleep true, radio sleep false.
		Power_Control_Delay(interval, true, false);
		TEST_ASSERT_TRUE(true);

		// 4.3. Sleep false, radio sleep true
		Power_Control_Delay(interval, false, true);
		TEST_ASSERT_TRUE(true);

		// 4.4. Sleep false, radio sleep false
		Power_Control_Delay(interval, false, false);
		TEST_ASSERT_TRUE(true);
	}
	
	{
		uint32_t interval = INTERVAL_4;

		// 5.1 Sleep true, radio sleep true 
		Power_Control_Delay(interval, true, true);
		TEST_ASSERT_TRUE(true);

		// 5.2. Sleep true, radio sleep false.
		Power_Control_Delay(interval, true, false);
		TEST_ASSERT_TRUE(true);

		// 5.3. Sleep false, radio sleep true
		Power_Control_Delay(interval, false, true);
		TEST_ASSERT_TRUE(true);

		// 5.4. Sleep false, radio sleep false
		Power_Control_Delay(interval, false, false);
		TEST_ASSERT_TRUE(true);
	}
	
	{
		uint32_t interval = INTERVAL_MAX;

		// 6.1 Sleep true, radio sleep true 
		Power_Control_Delay(interval, true, true);
		TEST_ASSERT_TRUE(true);

		// 6.2. Sleep true, radio sleep false.
		Power_Control_Delay(interval, true, false);
		TEST_ASSERT_TRUE(true);

		// 6.3. Sleep false, radio sleep true
		Power_Control_Delay(interval, false, true);
		TEST_ASSERT_TRUE(true);

		// 6.4. Sleep false, radio sleep false
		Power_Control_Delay(interval, false, false);
		TEST_ASSERT_TRUE(true);
	}


	//
	// 7. Delay for 100 seconds to trigger a restart.
	//
	delay(100 * 1000);
	TEST_ASSERT_TRUE(false);

}

/**
*	@brief Reference ID: 		AUTOINT3
*			Description: 		Check if the low power mode is enabled, if so force delay.
*			Successful result: 	If the low power mode is enabled, then make sure that the maximum interval for battery charging is used to maximise charging.
*			Date Log:			05/07/2020 - R.Bamford
*								10/07/2020 - R.Bamford - First implementation
*/
void AutoInt_T3()
{
	// 1. Save current power mode setting.
	uint8_t previousLowPowerActiveSetting = powerConfig.bits.lowPowerModeActive;
	uint8_t previousLowPowerModeEnabledSetting = powerConfig.bits.lowPowerModeEnabled;
	

	Pin_Interface_Watchdog_Heartbeat();

	// 2. Low power mode active but not enabled.
	{
		powerConfig.bits.lowPowerModeActive = 1;
		powerConfig.bits.lowPowerModeEnabled = 0;

		// assuming it is on full power.
		uint32_t interval = Power_Control_Get_Sleep_Interval();
		uint32_t intervalShouldBe = INTERVAL_MAX;
		TEST_ASSERT_EQUAL_UINT32(intervalShouldBe, interval);	
	}

	Pin_Interface_Watchdog_Heartbeat();

	{
		// 3. Low power mode not active but enabled.

		// assuming it is on full power.
		powerConfig.bits.lowPowerModeActive = 0;
		powerConfig.bits.lowPowerModeEnabled = 1;

		uint32_t interval = Power_Control_Get_Sleep_Interval();
		TEST_ASSERT_GREATER_THAN(intervalShouldBe, INTERVAL_MIN);
		TEST_ASSERT_LESS_THAN(intervalShouldBe, INTERVAL_MAX);	
	}

	Pin_Interface_Watchdog_Heartbeat();

	{
		// 4. Low power mode enabled and active.

		// assuming full power.
		powerConfig.bits.lowPowerModeActive = 1;
		powerConfig.bits.lowPowerModeEnabled = 1;

		uint32_t interval = Power_Control_Get_Sleep_Interval();
		uint32_t intervalShouldBe = INTERVAL_MAX;
		TEST_ASSERT_EQUAL_UINT32(intervalShouldBe, interval);	
	}

	Pin_Interface_Watchdog_Heartbeat();
	
	{
		// 5. Low power mode disabled and not active.
		powerConfig.bits.lowPowerModeActive = 0;
		powerConfig.bits.lowPowerModeEnabled = 0;

		uint32_t interval = Power_Control_Get_Sleep_Interval();
		TEST_ASSERT_GREATER_THAN(intervalShouldBe, INTERVAL_MIN);
		TEST_ASSERT_LESS_THAN(intervalShouldBe, INTERVAL_MAX);
	}
	
	Pin_Interface_Watchdog_Heartbeat();

	// Restore power mode setting.
	powerConfig.bits.lowPowerModeActive = previousLowPowerActiveSetting;
	powerConfig.bits.lowPowerModeEnabled = previousLowPowerModeEnabledSetting
}

/**
*	@brief Reference ID: 		AUTOINT4
*			Description: 		Check if the interval control is disabled, if so force no delay. 
*			Successful result: 	If the interval control is disabled, then test that there is no interval delay.
*			Date Log:			05/07/2020 - R.Bamforrd
*/
void AutoInt_T4()
{
}