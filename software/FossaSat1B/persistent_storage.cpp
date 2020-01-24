#include "persistent_storage.h"

// EEPROM only included once to supress unused variable warning
#include <EEPROM.h>

// EEPROM reading template
template <class T>
// cppcheck-suppress unusedFunction
T Persistent_Storage_Read(uint16_t addr) {
  T val;
  EEPROM.get(addr, val);
  return(val);
}

// EEPROM writing template
template <class T>
void Persistent_Storage_Write(uint16_t addr, T val) {
  EEPROM.put(addr, val);
}

void Persistent_Storage_Wipe() {
  // wipe EEPROM
  FOSSASAT_DEBUG_PRINTLN(F("Wiping"));
  for (uint16_t i = 0; i < EEPROM.length(); i++) {
    Persistent_Storage_Write<uint8_t>(i, EEPROM_RESET_VALUE);
  }

  // set default variable values

  // set deployment counter to 0
  Persistent_Storage_Write<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR, 0);

  // set default power configuration
  powerConfig.bits.lowPowerModeActive = LOW_POWER_MODE_ACTIVE;
  powerConfig.bits.lowPowerModeEnabled = LOW_POWER_MODE_ENABLED;
  powerConfig.bits.mpptTempSwitchEnabled = MPPT_TEMP_SWITCH_ENABLED;
  powerConfig.bits.mpptKeepAliveEnabled = MPPT_KEEP_ALIVE_ENABLED;
  powerConfig.bits.transmitEnabled = TRANSMIT_ENABLED;
  Power_Control_Save_Configuration();

  // reset first run flag
  Persistent_Storage_Write<uint8_t>(EEPROM_FIRST_RUN_ADDR, EEPROM_FIRST_RUN);

  // set reset counter to 0
  Persistent_Storage_Write<uint16_t>(EEPROM_RESTART_COUNTER_ADDR, 0);

  // set default receive window lengths
  Persistent_Storage_Write<uint8_t>(EEPROM_FSK_RECEIVE_LEN_ADDR, FSK_RECEIVE_WINDOW_LENGTH);
  Persistent_Storage_Write<uint8_t>(EEPROM_LORA_RECEIVE_LEN_ADDR, LORA_RECEIVE_WINDOW_LENGTH);

  // reset uptime counter
  Persistent_Storage_Write<uint32_t>(EEPROM_UPTIME_COUNTER_ADDR, 0);

  // reset frame counters
  Persistent_Storage_Write<uint16_t>(EEPROM_LORA_VALID_COUNTER_ADDR, 0);
  Persistent_Storage_Write<uint16_t>(EEPROM_LORA_INVALID_COUNTER_ADDR, 0);
  Persistent_Storage_Write<uint16_t>(EEPROM_FSK_VALID_COUNTER_ADDR, 0);
  Persistent_Storage_Write<uint16_t>(EEPROM_FSK_INVALID_COUNTER_ADDR, 0);

  // set default callsign
  System_Info_Set_Callsign((char*)"FOSSASAT-1B");

  // reset stats
  for(uint16_t addr = EEPROM_CHARGING_VOLTAGE_STATS_ADDR; addr <= EEPROM_MCU_TEMP_STATS_ADDR + 2; addr += sizeof(uint32_t)) {
    Persistent_Storage_Write<uint32_t>(addr, 0);
  }
  
}

void Persistent_Storage_Increment_Counter(uint16_t addr) {
  Persistent_Storage_Write<uint16_t>(addr, Persistent_Storage_Read<uint16_t>(addr) + 1);
}

void Persistent_Storage_Increment_Frame_Counter(bool valid) {
  uint16_t addr = EEPROM_LORA_VALID_COUNTER_ADDR;
  if(currentModem == MODEM_LORA) {
    if(!valid) {
      addr += 2;
    }
  } else {
    if(valid) {
      addr += 4;
    } else {
      addr += 6;
    }
  }

  Persistent_Storage_Increment_Counter(addr);
}

// explicitly instantiate templates
template uint8_t Persistent_Storage_Read<uint8_t>(uint16_t);
template uint16_t Persistent_Storage_Read<uint16_t>(uint16_t);
template int16_t Persistent_Storage_Read<int16_t>(uint16_t);
template uint32_t Persistent_Storage_Read<uint32_t>(uint16_t);

template void Persistent_Storage_Write<uint8_t>(uint16_t, uint8_t);
template void Persistent_Storage_Write<uint16_t>(uint16_t, uint16_t);
template void Persistent_Storage_Write<int16_t>(uint16_t, int16_t);
template void Persistent_Storage_Write<uint32_t>(uint16_t, uint32_t);
