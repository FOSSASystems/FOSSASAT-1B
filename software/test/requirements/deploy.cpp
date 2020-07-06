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

#include "deploy.h"

void Deploy_TestRunner_Start()
{
	RUN_TEST(Deploy_T2);
	RUN_TEST(Deploy_T8);
}


/**
*	@brief Reference ID: 		DEPLOYT1
*			Description: 		Test the deployment sequence in scenarios debugging, integration and jettison.
*			Successful result: 	Does the deployment sequence run correctly in these 3 scenarios?
								the debugging deployment sequence,
								integration and jettison sequences are different.
*			Date Log:			05/07/2020 - R.Bamford
*/
void Deploy_T1()
{
}

/**
*	@brief Reference ID: 		DEPLOYT2
*			Description: 		Check that the deployment sequence writes to the EEPROM.
*			Successful result: 	When the deployment sequence runs in jettison mode,
								does it correctly save its state to the EEPROM?
*			Date Log:			05/07/2020 - R.Bamford
*								06/07/2020 - R.Bamford - First implementation.
*/
void Deploy_T2()
{
	// Get the EEPROM value pre-deployment.
	uint8_t originalEEPROMValue = Persistent_Storage_Read<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR);

	// Call the deployment sequence.
	Deployment_Deploy(); // Blocked until finished.

	// Get the EEPROM value post-deployment.
	uint8_t newEEPROMValue = Persistent_Storage_Read<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR);

	// Value that it should be.
	uint8_t EEPROMCorrectValue = originalEEPROMValue + 1;

	// Assert that the value and correct value are equal.
	TEST_ASSERT_EQUAL_INT(newEEPROMValue, EEPROMCorrectValue);
}

/**
*	@brief Reference ID: 		DEPLOYT3
*			Description: 		Check that the deployment sequence does not run if the EEPROM state has been set.
*			Successful result: 	If the deployment sequence has ran, does it run again?
*			Date Log:			05/07/2020 - R.Bamford
*/
void Deploy_T3()
{
}

/**
*	@brief Reference ID: 		DEPLOYT4
*			Description: 		Check that the deployment sequence enable time is suitable.
*			Successful result: 	When the satellite powers the deployment mechanism, does it work correctly?
*			Date Log:			05/07/2020 - R.Bamford
*/
void Deploy_T4()
{
}

/**
*	@brief Reference ID: 		DEPLOYT5
*			Description: 		Confirm that a system information transmission is sent before the deployment sequence begins.
*			Successful result: 	Before the deployment sequence begins,
								does it send a transmission to notify receivers that it is about to occur?
*			Date Log:			05/07/2020 - R.Bamford
*/
void Deploy_T5()
{
}

/**
*	@brief Reference ID: 		DEPLOYT6
*			Description: 		Check that the deployment sequence transmits a success transmission afterwards.
*			Successful result: 	After the deployment sequence, does it tell receivers that it has occured?
*			Date Log:			05/07/2020 - R.Bamford
*/
void Deploy_T6()
{
}

/**
*	@brief Reference ID: 		DEPLOYT7
*			Description: 		Check that the deployment system returns the correct value for its current state.
*			Successful result: 	When the satellite restarts, does it load the correct value from the EEPROM?
*			Date Log:			05/07/2020 - R.Bamford
*/
void Deploy_T7()
{
}


/**
*	@brief Reference ID: 		DEPLOYT8
*			Description: 		Test that the deployment system can run over the size of uint8_t used to track its number.
*			Successful result: 	Successful result is that the number  cleanly loops to 0.
*			Date Log:			06/07/2020 - R.Bamford
*/
void Deploy_T8()
{
	// 1. Save the previous number of deployments.
	uint8_t previousNumberOfDeployments = Persistent_Storage_Read<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR);



	// 2. Set the deployment counter to 0.
	{
		Persistent_Storage_Write<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR, 0);

		// 3. Check the EEPROM is at 0.
		uint8_t currentEEPROMValue = Persistent_Storage_Read<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR);
		TEST_ASSERT_EQUAL_INT_MESSAGE(currentEEPROMValue, 0, "EEPROM address for deployment counter did not reset.");
	}



	// 4. Deploy 255 times
	for (uint16_t i = 0; i < 255; i++)
	{
		// toggle watchdog pin
		digitalWrite(DIGITAL_OUT_WATCHDOG_HEARTBEAT, !digitalRead(DIGITAL_OUT_WATCHDOG_HEARTBEAT));

		Deployment_Deploy();
	}




	// 5. Check the deployment EEPROM is at 255.
	{
		uint8_t currentEEPROMValue = Persistent_Storage_Read<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR);
		TEST_ASSERT_EQUAL_INT_MESSAGE(currentEEPROMValue, 255, "EEPROM address did not end at 255 correctly.");
	}

	// 6. Deploy 100 more times.
	for (uint16_t i = 0; i < 100; i++)
	{
		// toggle watchdog pin
		digitalWrite(DIGITAL_OUT_WATCHDOG_HEARTBEAT, !digitalRead(DIGITAL_OUT_WATCHDOG_HEARTBEAT));
		
		Deployment_Deploy();
	}

	// 7. Check that the deployment EEPROM is at 100. (looped correctly)
	{
		uint8_t currentEEPROMValue = Persistent_Storage_Read<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR);
		TEST_ASSERT_EQUAL_INT_MESSAGE(currentEEPROMValue, 100, "EEPROM address did not end correctly.");
	}


	// 8. Restore the previous number of deployments.
	Persistent_Storage_Write<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR, previousNumberOfDeployments);
}

