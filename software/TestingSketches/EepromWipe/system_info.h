#ifndef SYSTEM_INFO_H_INCLUDED
#define SYSTEM_INFO_H_INCLUDED

#include "FossaSat1B.h"

/**
 * @file system_info.h
 * @todo this module should contain the Restart Counter logic.
 */

/**
 * @brief Set the callsign to be used for each transmission to EEPROM.
 * 
 * @test (ID SYS_INF_T0) (SEV 1) Make sure this function writes the callsign to EEPROM.
 * 
 * @param newCallsign String containing the new callsign to use.
 */
void System_Info_Set_Callsign(char* newCallsign);

#endif
