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

//
// Doxygen tests
// https://fossasystems.github.io/FOSSASAT-1B/test.html
// 04/07/2020
//
#include "comms.h"
#include "conf_debug_macros.h"
#include "conf_eeprom_addr_map.h"
#include "conf_fsk_radio.h"
#include "conf_ina266_conf.h"
#include "conf_lora_radio.h"
#include "conf_mcu_temp.h"
#include "conf_morse_cw.h"
#include "conf_pin_map.h"
#include "conf_power_conf.h"
#include "conf_power_management.h"
#include "conf_radio.h"
#include "conf_tmp100.h"
#include "deployment.h"
#include "persis_stor.h"
#include "pin_interf.h"
#include "power_cont.h"
#include "sys_inf.h"

void setup()
{
	UNITY_BEGIN();
	UNITY_END();
}

void loop()
{
}

