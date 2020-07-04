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


#include <Arduino.h>
#include <unity.h>

#include "ina226.h"

//
// Requirement tests
// https://github.com/FOSSASystems/FOSSASAT-1B/blob/master/docs/3%20-%20Testing%20and%20Integration.md
// 04/07/2020
//
#include "requirement_tests/mainprog.h"
#include "requirement_tests/deployment.h"
#include "requirement_tests/power_control.h"
#include "requirement_tests/auto_int.h"
#include "requirement_tests/hard_int.h"
#include "requirement_tests/safe_sec.h"
#include "requirement_tests/comms.h"

//
// Doxygen tests
// https://fossasystems.github.io/FOSSASAT-1B/test.html
// 04/07/2020
//
#include "unit_tests/comms.h"
#include "unit_tests/conf_debug_macros.h"
#include "unit_tests/conf_eeprom_addr_map.h"
#include "unit_tests/conf_fsk_radio.h"
#include "unit_tests/conf_ina266_conf.h"
#include "unit_tests/conf_lora_radio.h"
#include "unit_tests/conf_mcu_temp.h"
#include "unit_tests/conf_morse_cw.h"
#include "unit_tests/conf_pin_map.h"
#include "unit_tests/conf_power_conf.h"
#include "unit_tests/conf_power_management.h"
#include "unit_tests/conf_radio.h"
#include "unit_tests/conf_tmp100.h"
#include "unit_tests/deployment.h"
#include "unit_tests/persis_stor.h"
#include "unit_tests/pin_interf.h"
#include "unit_tests/power_cont.h"
#include "unit_tests/sys_inf.h"

void setup()
{
	UNITY_BEGIN();
    RUN_TEST(ina226_check_response);
	RUN_TEST(ina226_check_battery_range);
	UnitTests::Comms::RunTests();
	UNITY_END();

}

void loop()
{
}

