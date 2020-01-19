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
/**
 * @brief Gets the callsign which is current set in EEPROM.
 * 
 * @todo Implement a RAM variable to hold this since EEPROM degrades with use, memory restrictions do not allow this to be alloced in RAM.
 * 
 * @test (ID SYS_INF_T1) (SEV 1) Make sure that the callsign is retrieved correctly from EEPROM.
 * 
 * @param buff The destination for the callsign.
 * @param len The length of the callsign.
 */
void System_Info_Get_Callsign(char* buff, uint8_t len);

#endif
