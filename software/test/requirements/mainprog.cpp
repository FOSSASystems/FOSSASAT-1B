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

#include "mainprog.h"

void MainProg_TestRunner_Start()
{

}


/**
*	@brief Reference ID: 		MAINPROGT1
*			Description: 		Startup configuration
*			Successful result: 	Once the program has started, are all the pins, 
								components and internal code configured correctly?
								Do they match the indended use?
*/
void MainProg_T1()
{

}


/**
* 	@brief Reference ID: 		MAINPROGT2
*			Description: 		Test pin configuration.
*			Successful result: 	Do all pins attach to their intended component pin correctly?
*/
void MainProg_T2()
{

}

/**
* 	@brief Reference ID: 		MAINPROGT3
*			Description: 		Test radio error mode handling.
*			Successful result: 	Are all the radio exceptions created handled?
*/
void MainProg_T3()
{

}

/**
* 	@brief Reference ID: 		MAINPROGT4
*			Description: 		Confirm the MCU has enough resources to run the software.
*			Successful result: 	When the software is executed on the target hardware,
								does it run the entire program without having memory issues?.
*/
void MainProg_T4()
{

}

/**
* 	@brief Reference ID: 		MAINPROGT5
*			Description: 		Check that the satellite transmits.
*			Successful result: 	Can the satellite transmissions be received by a radio?
*/
void MainProg_T5()
{

}

/**
* 	@brief Reference ID: 		MAINPROGT6
*			Description: 		Can the satellite receive transmissions?
*			Successful result: 	Do all pins attach to their intended component pin correctly?
*/
void MainProg_T6()
{

}

/**
* 	@brief Reference ID: 		MAINPROGT7
*			Description: 		Check that the radio re-configures successfully.
*			Successful result: 	When the radio is changed, does the satellite still transmit and receive correctly?
*/
void MainProg_T7()
{

}

/**
* 	@brief Reference ID: 		MAINPROGT8
*			Description: 		Check that the MCU can be delayed by up to 10 minutes.
*			Successful result: 	When the satellite is delayed, does it react the way you intended?
*/
void MainProg_T8()
{

}

/**
* 	@brief Reference ID: 		MAINPROGT9
*			Description: 		Check that the MCU can run the software system for at least a week.
*			Successful result: 	When you run the software on the related hardware, does it run how it should for a long time?
*/
void MainProg_T9()
{

}

/**
* 	@brief Reference ID: 		MAINPROGT10
*			Description: 		Check that the hardware watchdog is signalled correctly.
*			Successful result: 	Does the hardware watchdog cause any issues with restarting during its operation? For example causing restarts in long functions?
*/
void MainProg_T10()
{

}

/**
* 	@brief Reference ID: 		MAINPROGT11
*			Description: 		Check that the hardware watchdog does not switch the satellite off during transmission.
*			Successful result: 	When the satellite transmits in any mode, does it correctly send transmissions without the watchdog interefering, even with long transmissions
*/
void MainProg_T11()
{

}

/**
* 	@brief Reference ID: 		MAINPROGT12
*			Description: 		Check the software does not enter any restart loops.
*			Successful result: 	Does the code of the satellite enter any sections of code that cause it to restart over and over again? (check restart command useage)
*/
void MainProg_T12()
{

}