#include "system_info.h"

void System_Info_Set_Callsign(char* newCallsign) {
  // get length of the new callsign (callsign is saved to EEPROM including terminating NULL)
  uint8_t newCallsignLen = (uint8_t)strlen(newCallsign) + 1;

  // check new callsign length
  if(newCallsignLen > MAX_STRING_LENGTH) {
    FOSSASAT_DEBUG_PRINTLN(F("New callsign too long!"));
    return;
  }

  // write new callsign length
  Persistent_Storage_Write<uint8_t>(EEPROM_CALLSIGN_LEN_ADDR, newCallsignLen);

  // write new callsign (including terminating NULL)
  for(uint8_t i = 0; i < newCallsignLen; i++) {
    Persistent_Storage_Write<uint8_t>(EEPROM_CALLSIGN_ADDR + i, (uint8_t)newCallsign[i]);
  }
}
