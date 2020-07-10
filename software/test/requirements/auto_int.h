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

#ifndef AUTO_INT_T_H
#define AUTO_INT_T_H

#include "../common.h"
#include "power_control.h"
#include "pin_interface.h"


extern void AutoInt_TestRunner_Start();


/**
*	@brief Reference ID: 		AUTOINT1
*			Description: 		Check that the intervals returned for a given battery charged level matches the specified table of delays.
*			Successful result: 	Simulate the battery charging level at the specified thresholds (using bounds testing too) and
								check the interval changes according to the specified delays (see Julian for spec)
*			Date Log:			05/07/2020 - R.Bamford			
*/
extern void AutoInt_T1();

/**
*	@brief Reference ID: 		AUTOINT2
*			Description: 		Check that the maximum and minimum intervals do not cause errors. (resetting loops)
*			Successful result: 	When the satellite is delayed, does it restart when it should?
								does it get into a restart loop anywhere? check this
*			Date Log:			05/07/2020 - R.Bamford
*/
extern void AutoInt_T2();

/**
*	@brief Reference ID: 		AUTOINT3
*			Description: 		Check if the low power mode is enabled, if so force delay.
*			Successful result: 	If the low power mode is enabled, then make sure that the maximum interval for battery charging is used to maximise charging.
*			Date Log:			05/07/2020 - R.Bamforrd
*/
extern void AutoInt_T3();

/**
*	@brief Reference ID: 		AUTOINT4
*			Description: 		Check if the interval control is disabled, if so force no delay. 
*			Successful result: 	If the interval control is disabled, then test that there is no interval delay.
*			Date Log:			05/07/2020 - R.Bamforrd
*/
extern void AutoInt_T4();

#endif

