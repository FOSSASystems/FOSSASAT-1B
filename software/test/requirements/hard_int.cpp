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

#include "hard_int.h"



void HardInt_TestRunner_Start()
{

}


/**
*	@brief Reference ID: 		HARDINT1
*			Description: 		Test the bounds and normal readings of voltages. (Volts)
*			Successful result: 	Check that the voltage readings are ok, different scenarios such as broken component, disconnected component.etc
*/
void HardInt_T1()
{

}

/**
*	@brief Reference ID: 		HARDINT2
*			Description: 		Check that the battery voltage is output when the MPPT is disabled.
*			Successful result: 	When the MPPT is disabled, make sure that the battery voltage is output.
*/
void HardInt_T2()
{

}

/**
*	@brief Reference ID: 		HARDINT3
*			Description: 		Check that the battery charging voltage is output when the MPPT is enabled. (Volts)
*			Successful result: 	When the MPPT is enabled, double check that the voltage it reads matches the battery charging voltage.
*/
void HardInt_T3()
{

}

/**
*	@brief Reference ID: 		HARDINT4
*			Description: 		Test that the satellite restarts when the hardware watchdog is not given a signal. 	
*			Successful result: 	Disconnect the watchdog, does the satellite restart?
*/
void HardInt_T4()
{

}

/**
*	@brief Reference ID: 		HARDINT5
*			Description: 		Check that the battery charging voltage is output correctly. (Amperes)
*			Successful result: 	Doublecheck that the battery charging voltage reads correct values i.e. values that make sense.
*/
void HardInt_T5()
{

}

/**
*	@brief Reference ID: 		HARDINT6
*			Description: 		Check that the battery voltage reading is output correctly. (Volts) 	
*			Successful result: 	double check that the battery voltage read is correct and makes sense.
*/
void HardInt_T6()
{

}

/**
*	@brief Reference ID: 		HARDINT7
*			Description: 		Check that the solar cell's voltage readings are correct. (Volts)
*			Successful result: 	Double check the voltage readings.
*/
void HardInt_T7()
{

}


/**
*	@brief Reference ID: 		HARDINT8
*			Description: 		Check that the battery temperature reading is correct. (Celsius)
*			Successful result: 	Double check the battery temperature readings are ok.
*/
void HardInt_T8()
{

}

/**
*	@brief Reference ID: 		HARDINT9
*			Description: 		Check that the battery voltage reading is output correctly.
*			Successful result: 	Double check that the battery voltage
*/
void HardInt_T9()
{

}

/**
*	@brief Reference ID: 		HARDINT11
*			Description: 		Check that the sensors are configured correctly.
*			Successful result: 	Look at all the sensor readings together, do they all make sense?
*/
void HardInt_T11()
{

}
