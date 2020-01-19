#ifndef PERSISTENT_STORAGE_H_INCLUDED
#define PERSISTENT_STORAGE_H_INCLUDED

#include "FossaSat1B.h"

/**
 * @file persistent_storage.h
 */

/**
 * @brief This function reads a value of type T from EEPROM.
 * 
 * @tparam T 
 * @param addr Memory address.
 * @return T 
 */
template <class T>
T Persistent_Storage_Read(uint16_t addr);

/**
 * @brief This function writes a value of type T to the eerom.
 * 
 * @tparam T 
 * @param addr Memory address.
 * @param val 
 */
template <class T>
void Persistent_Storage_Write(uint16_t addr, T val);

/**
 * @brief This functions clears the EEPROM by writing EEPROM_RESET_VALUE to each memory addres.
 * 
 * @test (ID PERSIS_STOR_H_T0) (SEV 1) Does the EEPROM enter a valid state after this function is ran?
 * 
 */
void Persistent_Storage_Wipe();

#endif
