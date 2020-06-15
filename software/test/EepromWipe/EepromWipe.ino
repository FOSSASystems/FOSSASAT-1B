#include "FossaSat1B.h"

void setup() {
  FOSSASAT_DEBUG_PORT.begin(FOSSASAT_DEBUG_SPEED);
  while(!FOSSASAT_DEBUG_PORT);
  FOSSASAT_DEBUG_PORT.println();

  FOSSASAT_DEBUG_PRINT_EEPROM(0x00, 0x7F);
  FOSSASAT_DEBUG_PORT.println("EEPROM wipe start");
  Persistent_Storage_Wipe();
  FOSSASAT_DEBUG_PORT.println("EEPROM wipe done");
  FOSSASAT_DEBUG_PRINT_EEPROM(0x00, 0x7F);
}

void loop() {

}
