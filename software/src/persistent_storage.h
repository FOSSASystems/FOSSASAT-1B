#ifndef PERSISTENT_STORAGE_H_INCLUDED
#define PERSISTENT_STORAGE_H_INCLUDED

#include "FossaSat1B.h"

// EEPROM only included once to suppress unused variable warning
#include <EEPROM.h>

/**
 * @file persistent_storage.h
 * @brief This module controls access to the EEPROM.
 */

/**
 * @brief This function reads a value of type T from EEPROM.
 *
 * @tparam T
 * @param addr Memory address.
 * @return T
 */
template <typename T>
T Persistent_Storage_Read(uint16_t addr) {
  T val;
  EEPROM.get(addr, val);
  return(val);
}

/**
 * @brief This function writes a value of type T to the eerom.
 *
 * @tparam T
 * @param addr Memory address.
 * @param val
 */
template <typename T>
void Persistent_Storage_Write(uint16_t addr, T val) {
  EEPROM.put(addr, val);
}

/**
 * @brief This functions clears the EEPROM by writing EEPROM_RESET_VALUE to each memory addres.
 *
 * @test (ID PERSIS_STOR_H_T0) (SEV 1) Does the EEPROM enter a valid state after this function is ran?
 *
 */
void Persistent_Storage_Wipe();

/**
 * @brief This functions increments 2-byte counter in EEPROM
 *
 * @param addr The address of counter to increment
 *
 */
void Persistent_Storage_Increment_Counter(uint16_t addr);

/**
 * @brief This functions increments one of frame counters of the currently active modem in EEPROM
 *
 * @param valid Whether to increment valid or invalid counter
 *
 */
void Persistent_Storage_Increment_Frame_Counter(bool valid);

/**
 * @brief Updates minimum, average and maximum stats in EEPROM
 *
 * @tparam T
 * @param addr Memory address.
 * @param val
 *
 */
template <typename T>
void Persistent_Storage_Update_Stats(uint16_t addr, T val) {
  T min = Persistent_Storage_Read<T>(addr);
  T avg = Persistent_Storage_Read<T>(addr + sizeof(val));
  T max = Persistent_Storage_Read<T>(addr + 2*sizeof(val));

  if(val < min) {
    Persistent_Storage_Write<T>(addr, val);
  }

  Persistent_Storage_Write<T>(addr + sizeof(val), (avg + val)/2);

  if(val > max) {
    Persistent_Storage_Write<T>(addr + 2*sizeof(val), val);
  }
}

#endif
