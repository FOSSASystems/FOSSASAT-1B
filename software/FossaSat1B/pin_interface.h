#ifndef PIN_INTERFACE_H_INCLUDED
#define PIN_INTERFACE_H_INCLUDED

#include "FossaSat1B.h"
/**
 * @file pin_interface.h
 * 
 * @brief This module controls access to the components connect to via pins.
 * 
 */

/**
 * @brief This function sets the resolution of the TMP100.
 * 
 * @test (ID PIN_INTERF_H_T0) (SEV 1) Make sure that this does not break with the given resolutions.
 * 
 * @param sensorAddr Wire address of the TMP100.
 * @param res The value that relates to the resolution property of the TMP100. See @ref defines_tmp100_configuration
 * 
 */
void Pin_Interface_Set_Temp_Resolution(uint8_t sensorAddr, uint8_t res);
/**
 * @brief This function reads the TMP100's value from its wire address.
 * 
 * @test (ID PIN_INTERF_H_T1) (SEV 1) Make sure that all resolutions do not break the satellite.
 * @test (ID PIN_INTERF_H_T2) (SEV 1) Make sure this returns the correct value.
 * 
 * @param sensorAddr Wire address of the TMP100
 * @return float The temperature value in Degrees C at the specified resolution.
 */
float Pin_Interface_Read_Temperature(uint8_t sensorAddr);
/**
 * @brief This function reads the MCU's internal temperature.
 * 
 * @test (ID PIN_INTERF_H_T3) (SEV 1) Make sure this does not break the satellite.
 * @test (ID PIN_INTERF_H_T4) (SEV 2) Make sure this returns the correct value.
 * 
 * @return int8_t The temperature returned by the MCU in Degrees C.
 */
int8_t Pin_Interface_Read_Temperature_Internal();

/**
 * @brief Read the voltage of a given pin.
 * 
 * @test (ID PIN_INTERF_H_T5) (SEV 1) Make sure the given equation is correct for all compatable pins.
 * 
 * @param pin The pin to read from.
 * @return float The voltage.
 */
float Pin_Interface_Read_Voltage(uint8_t pin);

/**
 * @brief This function toggles the signal to the watchdog and writes it to the pin.
 * 
 * @test (ID PIN_INTERF_H_T6) (SEV 1) Make sure this function keeps the satellite alive.
 * 
 * @param manageBattery Whether to perform battery and power management.
 */
void Pin_Interface_Watchdog_Heartbeat(bool manageBattery = false);
/**
 * @brief Restarts the watchdog.
 * 
 * @test (ID PIN_INTERF_H_T7) (SEV 1) Make sure this function resets the watchdog.
 * 
 */
void Pin_Interface_Watchdog_Restart();

#endif
