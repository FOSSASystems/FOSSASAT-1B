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

#ifndef COMMS_T_H
#define COMMS_T_H

extern void Comms_TestRunner_Start();


/**
*	@brief Reference ID: 		COMMST1
*			Description: 		Test the enable and disabling of transmissions.
*			Successful result: 	When the transmissions are enabled and disabled, does the satellite stop transmitting and start transmitting again correctly?
*/
extern void Comms_T1();

/**
*	@brief Reference ID: 		COMMST2
*			Description: 		Test the repeater command.
*			Successful result: 	Send the satellite a repeater command and receive it with a radio.
*/
extern void Comms_T2();

/**
*	@brief Reference ID: 		COMMST3
*			Description: 		Test the ping-pong command.
*			Successful result: 	Send a PING command to the satellite and receive a PONG command from a seperate radio.
*/
extern void Comms_T3();

/**
*	@brief Reference ID: 		COMMST4
*			Description: 		Test the callsign change command.
*			Successful result: 	Send the satellite a callsign change command and then receive a transmissions of the new callsign
*/
extern void Comms_T4();

/**
*	@brief Reference ID: 		COMMST5
*			Description: 		Test the command security features.
*			Successful result: 	Make sure protected security features cannot be invoked without permission
*/
extern void Comms_T5();

/**
*	@brief Reference ID: 		COMMST6
*			Description: 		Test that the satellite transmits a notification when it powers on.
*			Successful result: 	
*/
extern void Comms_T6();

/**
*	@brief Reference ID: 		COMMST7
*			Description: 		Test that the satellite transmits a notification after it deploys.
*			Successful result: 	
*/
extern void Comms_T7();

/**
*	@brief Reference ID: 		COMMST8
*			Description: 		Test that the EEPROM is reset on command.
*			Successful result: 	
*/
extern void Comms_T8();

/**
*	@brief Reference ID: 		COMMST9
*			Description: 		Test the restart command.
*			Successful result: 	
*/
extern void Comms_T9();

/**
*	@brief Reference ID: 		COMMST10
*			Description: 		Test the frequency band changing command.
*			Successful result: 	
*/
extern void Comms_T10();

/**
*	@brief Reference ID: 		COMMST11
*			Description: 		Test the manual deployment command.
*			Successful result: 	
*/
extern void Comms_T11();

/**
*	@brief Reference ID: 		COMMST12
*			Description: 		Test the manual system information command.
*			Successful result: 	
*/
extern void Comms_T12();

/**
*	@brief Reference ID: 		COMMST13
*			Description: 		Test the satellite transmits when it shuts down.
*			Successful result: 	
*/
extern void Comms_T13();

/**
*	@brief Reference ID: 		COMMST14
*			Description: 		Check the transmission timing is correct.
*			Successful result: 	
*/
extern void Comms_T14();

/**
*	@brief Reference ID: 		COMMST15
*			Description: 		Check the callisgn is transmitted.
*			Successful result: 	
*/
extern void Comms_T15();

/**
*	@brief Reference ID: 		COMMST16
*			Description: 		Check the spreading factor changes do not break transmissions.
*			Successful result: 	
*/
extern void Comms_T16();

/**
*	@brief Reference ID: 		COMMST17
*			Description: 		Check the low power mode disable and enable command.
*			Successful result: 	
*/
extern void Comms_T17();

/**
*	@brief Reference ID: 		COMMST18
*			Description: 		Check the MPPT keep-alive command.
*			Successful result: 	
*/
extern void Comms_T18();

/**
*	@brief Reference ID: 		COMMST19
*			Description: 		Check the MPPT enable and disable command.
*			Successful result: 	
*/
extern void Comms_T19();


#endif

