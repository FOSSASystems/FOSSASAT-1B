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

#ifndef COMMON_H_
#define COMMON_H_

#include <Arduino.h>
#include <stdint.h>
#include <unity.h>

#include "configuration.h"


// these are the interval times for the power control (power_control.cpp)
#define INTERVAL_MIN	(20 * 1000UL)
#define INTERVAL_1		(35 * 1000UL)
#define INTERVAL_2		(100 * 1000UL)
#define INTERVAL_3		(160 * 1000UL)
#define INTERVAL_4		(180 * 1000UL)
#define INTERVAL_MAX	(240 * 1000UL)

/**
 * 10/07/2020 - R.Bamford
 * This macro is not needed, the watchdog should always be signalled using 
		  "Pin_Interface_Watchdog_Heartbeat()" inside the test case code.


 * 10/07/2020 - P.Buchegger
 * The macro will trigger the watchdog between test runs.
 * otherwise the posssibility is high that the watchdog will kill long running test. Please use this macro instead of RUN_TEST().
 * 
 */
#define RUN_FS_TEST(func) \
	pinMode(DIGITAL_OUT_WATCHDOG_HEARTBEAT, OUTPUT); \
	digitalWrite(DIGITAL_OUT_WATCHDOG_HEARTBEAT, !digitalRead(DIGITAL_OUT_WATCHDOG_HEARTBEAT)); \
	RUN_TEST(func)

#endif
