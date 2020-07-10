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


/**
 * 10/07/2020 - R.Bamford
 * This macro is not needed, the watchdog should always be signalled using 
          "Pin_Interface_Watchdog_Heartbeat()" inside the test case code.

    - Remove this macro please -
 * 
 */
#define RUN_FS_TEST(func) \
	pinMode(DIGITAL_OUT_WATCHDOG_HEARTBEAT, OUTPUT); \
    digitalWrite(DIGITAL_OUT_WATCHDOG_HEARTBEAT, !digitalRead(DIGITAL_OUT_WATCHDOG_HEARTBEAT)); \
    RUN_TEST(func)

#endif
