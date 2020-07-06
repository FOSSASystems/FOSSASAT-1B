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

#ifndef UNIT_COMMS_T_H
#define UNIT_COMMS_T_H

#include "../common.h"

namespace UnitTests
{

namespace Comms
{

extern void RunTests();

/**
 * @brief This test makes sure that the function "Communication_Receive_Interrupt()"
 *          is called when the radio receives data.
 * @test (ID COMMS_H_T0) (SEV 1)
 */
extern void t0();
extern void t1();
extern void t2();
extern void t3();
extern void t4();
extern void t5();
extern void t6();
extern void t7();
extern void t8();
extern void t9();
extern void t10();
extern void t11();
extern void t12();
extern void t13();
extern void t14();

}

}
#endif

