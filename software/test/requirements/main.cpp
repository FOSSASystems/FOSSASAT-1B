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

#include "../common.h"

//
// Requirement tests
// https://github.com/FOSSASystems/FOSSASAT-1B/blob/master/docs/3%20-%20Testing%20and%20Integration.md
// 04/07/2020
//
#include "mainprog.h"
#include "deploy.h"
#include "pow_cont.h"
#include "auto_int.h"
#include "hard_int.h"
#include "safe_sec.h"
#include "comms.h"


void setup()
{
	UNITY_BEGIN();
	
	// Deployment tests.
	Deploy_TestRunner_Start();

	// Automatic interval control tests.
	AutoInt_TestRunner_Start();

	UNITY_END();
}

void loop()
{
}

