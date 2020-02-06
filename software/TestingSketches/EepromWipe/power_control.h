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
 * @brief Saves the configuration bytes from RAM into EEPROM.
 *
 * @test (ID POWER_CONT_H_T1) (SEV 1) Make sure that the power configuration is wrote to the EEPROM correctly.
 *
 */
void Power_Control_Save_Configuration();

#endif
