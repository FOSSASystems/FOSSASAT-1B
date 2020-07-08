#include "power_control.h"

powerConfigBits_t powerConfigBits = {
  .lowPowerModeActive = LOW_POWER_MODE_ACTIVE,
  .lowPowerModeEnabled = LOW_POWER_MODE_ENABLED,
  .mpptTempSwitchEnabled = MPPT_TEMP_SWITCH_ENABLED,
  .mpptKeepAliveEnabled = MPPT_KEEP_ALIVE_ENABLED,
  .transmitEnabled = TRANSMIT_ENABLED
};

powerConfig_t powerConfig = {
  .bits = powerConfigBits
};

void Power_Control_Save_Configuration() {
  Persistent_Storage_Write<uint8_t>(EEPROM_POWER_CONFIG_ADDR, powerConfig.val);
}
