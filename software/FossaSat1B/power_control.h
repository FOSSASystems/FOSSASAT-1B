#ifndef POWER_CONTROL_H_INCLUDED
#define POWER_CONTROL_H_INCLUDED

#include "FossaSat1B.h"

/**
 * @file power_control.h
 *
 */

/**
 * @brief Power configuration strutcture, each entry is one bit long. Total 1 byte, lowPowerModeActive is the least significant bit.
 *
 */
struct powerConfigBits_t {
  uint8_t lowPowerModeActive : 1;       // LSB
  uint8_t lowPowerModeEnabled : 1;
  uint8_t mpptTempSwitchEnabled : 1;
  uint8_t mpptKeepAliveEnabled : 1;
  uint8_t transmitEnabled : 1;
};

/**
 * @brief Union to quickly access power configuration bits or the entire single-byte value.
 */
union powerConfig_t {
  struct powerConfigBits_t bits;
  uint8_t val;
};

/**
 * @brief The current power configuration settings.
 *
 */
extern powerConfig_t powerConfig;

/**
 * @brief Load the configuration bytes from the EEPROM into RAM.
 *
 * @test (ID POWER_CONT_H_T0) (SEV 1) Make sure that the power configuration is loaded from EEPROM correctly.
 *
 */
void Power_Control_Load_Configuration();

/**
 * @brief Saves the configuration bytes from RAM into EEPROM.
 *
 * @test (ID POWER_CONT_H_T1) (SEV 1) Make sure that the power configuration is wrote to the EEPROM correctly.
 *
 */
void Power_Control_Save_Configuration();

/**
 * @brief This function ensures that the battery is charging.
 * "set MPPT to input which enables battery charging, but only after checking keep alive and temperature limit"
 *
 * @test (ID POWER_CONT_H_T3) (SEV 1) Make sure the battery charges when this function is called.
 * @test (ID POWER_CONT_H_T4) (SEV 1) When mppt keep alive is enabled, make sure that the battery charges.
 * @test (ID POWER_CONT_H_T5) (SEV 1) When mppt temperature switch is enabled, make sure the battery doesn't charge.
 * @test (ID POWER_CONT_H_T6) (SEV 1) When the charge boolean is TRUE, is allows the battery to charge.
 * @test (ID POWER_CONT_H_T14) (SEV 1) When the charge boolean is FALSe, is prevents the battery to charge.
 *
 * @param charge The option to charge the battery or turn off the MPPT.
 */
void Power_Control_Charge(bool charge);

/**
 * @brief Get the amount of seconds to sleep for given the battery voltage.
 * 
 * @todo Julian -> The sleep intervals should be updated to match the new CW-synced communications.
 *
 * @test (ID POWER_CONT_H_T7) (SEV 1) Check what interval is returned at the designated voltages.
 *
 * @return uint32_t The number of milliseconds to sleep for.
 */
uint32_t Power_Control_Get_Sleep_Interval();

/**
 * @brief This function delays the program execution for the given number of milliseconds, while maintaining the watchdog signal to prevent it resetting.
 *
 * @test (ID POWER_CONT_H_T8) (SEV 1) Check that the satellite's program is delayed for the given number of seconds without restarting.
 *
 * @param ms The amount of time to delay the program for.
 * @param sleep Whether to use the LowPower libraries powerDown feature.
 * @param sleepRadio Whether to put the radio into sleep mode for the duration.
 */
void Power_Control_Delay(uint32_t ms, bool sleep, bool sleepRadio = false);

/**
 * @brief Initializes the INA226 current sensor.
 *
 *
 * @test (ID POWER_CONT_H_T9) (SEV 1) Check that the INA226 is configured ok.
 *
 */
void Power_Control_Setup_INA226();

/**
 * @brief Check that the INA2256 is valid.
 *
 * @test (ID POWER_CONT_H_T10) (SEV 1) Check that this function correctly returns the state of the INA226 component.
 *
 * @return true The INA226 is working correctly.
 * @return false The INA226 is not working correctly.
 */
bool Power_Control_INA226_Check();

/**
 * @brief Get the battery voltage by switching the MPPT off and then on again after reading is taken.
 *
 * @test (ID POWER_CONT_H_T11) (SEV 1) Check that this function returns the correct battery voltage.
 *
 * @return float The voltage returned by the INA266 of the battery.
 */
float Power_Control_Get_Battery_Voltage();

/**
 * @brief Gets the charging voltage (from the solar panels) by not switching the MPPT off and taking an INA226 reading.
 *
 * @test (ID POWER_CONT_H_T12) (SEV 1) Check that this function returns the correct solar panel charging voltage.
 *
 * @return float The voltage provided by the solar panels.
 */
float Power_Control_Get_Charging_Voltage();

/**
 * @brief Gets the amperage which is being provided to the battery.
 *
 * @test (ID POWER_CONT_H_T13) (SEV 1) Check the value returned by this function is the current charging solar panel Amperage.
 *
 * @return float The shunt current value of the INA2256
 */
float Power_Control_Get_Charging_Current();

/**
 * @brief Checks whether battery voltage is below low power limit. Will enable low power mode if that is the case.
 * 
 * @return bool Whether battery check passed or not.
 */
bool Power_Control_Check_Battery_Limit();

#endif
