#include "FossaSat1B.h"

// compile-time checks
#if (!defined RADIOLIB_VERSION) || (RADIOLIB_VERSION < 0x03010000)
  #error "Unsupported RadioLib version (< 3.1.0)!"
#endif

#ifndef RADIOLIB_STATIC_ONLY
  #error "RadioLib is using dynamic memory management, enable static only in RadioLib/src/TypeDef.h"
#endif

void setup() {
  // initialize debug port
  FOSSASAT_DEBUG_PORT.begin(FOSSASAT_DEBUG_SPEED);
  FOSSASAT_DEBUG_PORT.println();

  // increment reset counter
  FOSSASAT_DEBUG_PORT.print(F("Restart #"));
  FOSSASAT_DEBUG_PORT.println(Persistent_Storage_Read<uint16_t>(EEPROM_RESTART_COUNTER_ADDR));
  Persistent_Storage_Write<uint16_t>(EEPROM_RESTART_COUNTER_ADDR, Persistent_Storage_Read<uint16_t>(EEPROM_RESTART_COUNTER_ADDR) + 1);

  // setup pins
  Configuration_Setup_Pins();

  #ifdef EEPROM_WIPE
    // wipe EEPROM
    Persistent_Storage_Wipe();
  #endif

  // check if this is the first run
  if(Persistent_Storage_Read<uint8_t>(EEPROM_FIRST_RUN_ADDR) != EEPROM_CONSECUTIVE_RUN) {
    // first run, set EEPROM flag
    Persistent_Storage_Write<uint8_t>(EEPROM_FIRST_RUN_ADDR, EEPROM_CONSECUTIVE_RUN);

  } else {
    // consecutive run, load power control configuration
    Power_Control_Load_Configuration();

  }

  // print power configuration
  FOSSASAT_DEBUG_PORT.print(F("Config: 0b"));
  FOSSASAT_DEBUG_PORT.println(powerConfig.val, BIN);

  // set temperature sensor resolution
  Pin_Interface_Set_Temp_Resolution(BOARD_TEMP_SENSOR_ADDR, TEMP_SENSOR_RESOLUTION_10_BITS);
  Pin_Interface_Set_Temp_Resolution(BATTERY_TEMP_SENSOR_ADDR, TEMP_SENSOR_RESOLUTION_10_BITS);

  // setup INA226
  Power_Control_Setup_INA226();

  // check deployment
  #ifdef ENABLE_DEPLOYMENT_SEQUENCE
    uint8_t attemptNumber = PersistentStorage_Read_Internal<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR);

    FOSSASAT_DEBUG_PORT.print(F("Deployment attempt #"));
    FOSSASAT_DEBUG_PORT.println(attemptNumber);

    // check number of deployment attempts
    if (attemptNumber == 0) {
      // print data for integration purposes (independently of FOSSASAT_DEBUG macro!)
      uint32_t start = millis();
      uint32_t lastSample = 0;
      while (millis() - start <= (uint32_t)DEPLOYMENT_DEBUG_LENGTH * (uint32_t)1000) {
        // check if its time for next measurement
        if (millis() - lastSample >= (uint32_t)DEPLOYMENT_DEBUG_SAMPLE_PERIOD) {
          lastSample = millis();
          FOSSASAT_DEBUG_PORT.println();

          FOSSASAT_DEBUG_PORT.print(F("Charging [V]:\t"))
          FOSSASAT_DEBUG_PORT.println(Power_Control_Get_Charging_Voltage(), 2);

          FOSSASAT_DEBUG_PORT.print(F("Charging [mA]:\t"))
          FOSSASAT_DEBUG_PORT.println(Power_Control_Get_Charging_Current(), 3);

          FOSSASAT_DEBUG_PORT.print(F("Battery [V]:\t"))
          FOSSASAT_DEBUG_PORT.println(Power_Control_Get_Battery_Voltage(), 2);

          FOSSASAT_DEBUG_PORT.print(F("Solar A [V]:\t"))
          FOSSASAT_DEBUG_PORT.println(Pin_Interface_Read_Voltage(ANALOG_IN_SOLAR_A_VOLTAGE_PIN) 2);

          FOSSASAT_DEBUG_PORT.print(F("Solar B [V]:\t"))
          FOSSASAT_DEBUG_PORT.println(Pin_Interface_Read_Voltage(ANALOG_IN_SOLAR_B_VOLTAGE_PIN) 2);

          FOSSASAT_DEBUG_PORT.print(F("Solar C [V]:\t"))
          FOSSASAT_DEBUG_PORT.println(Pin_Interface_Read_Voltage(ANALOG_IN_SOLAR_C_VOLTAGE_PIN) 2);

          FOSSASAT_DEBUG_PORT.print(F("Battery [°C]:\t"))
          FOSSASAT_DEBUG_PORT.println(Pin_Interface_Read_Temperature(BATTERY_TEMP_SENSOR_ADDR), 2);

          FOSSASAT_DEBUG_PORT.print(F("Board [°C]:\t"))
          FOSSASAT_DEBUG_PORT.println(Pin_Interface_Read_Temperature(BOARD_TEMP_SENSOR_ADDR), 2);

          FOSSASAT_DEBUG_PORT.print(F("MCU [°C]:\t"))
          FOSSASAT_DEBUG_PORT.println(Pin_Interface_Read_Temperature_Internal());

          FOSSASAT_DEBUG_PORT.print(F("Reset:\t\t"))
          FOSSASAT_DEBUG_PORT.println(Persistent_Storage_Read<uint16_t>(EEPROM_RESTART_COUNTER_ADDR));

          FOSSASAT_DEBUG_PORT.print(F("Power config:\t0b"))
          Power_Control_Load_Configuration();
          FOSSASAT_DEBUG_PORT.println(powerConfig.val, BIN);

          FOSSASAT_DEBUG_PORT.println(F("============================================================="));
        }

        // pet watchdog
        if (millis() - lastHeartbeat >= WATCHDOG_LOOP_HEARTBEAT_PERIOD) {
          PowerControl_Watchdog_Heartbeat();
        }
      }
    } else if(Persistent_Storage_Read<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR) < DEPLOYMENT_ATTEMPTS) {
      // sleep before deployment
      Power_Control_Delay(DEPLOYMENT_SLEEP_LENGTH, true, true);

      // deploy
      Deployment_Deploy();
    }
  #endif
}

void loop() {
  // check battery voltage
  float battVoltage = Power_Control_Get_Battery_Voltage();

  // set FSK modem
  Communication_Set_Modem(MODEM_FSK);
  FOSSASAT_DEBUG_DELAY(100);
  if(battVoltage >= BATTERY_CW_BEEP_VOLTAGE_LIMIT) {
    // transmit full Morse beacon
    Communication_Send_Morse_Beacon(battVoltage);
  } else {
    // battery is low, transmit CW beeps
    for(uint8_t i = 0; i < NUM_CW_BEEPS; i++) {
      Communication_CW_Beep();
      LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
    }
  }

  // wait for a bit
  FOSSASAT_DEBUG_DELAY(100);
  Power_Control_Delay(500, true, true);

  // send FSK system info
  Communication_Set_Modem(MODEM_FSK);
  Communication_Send_System_Info();

  // wait for a bit
  FOSSASAT_DEBUG_DELAY(100);
  Power_Control_Delay(500, true, true);

  // send LoRa system info
  Communication_Set_Modem(MODEM_LORA);
  Communication_Send_System_Info();

  // wait for a bit
  FOSSASAT_DEBUG_DELAY(100);
  Power_Control_Delay(500, true, true);

  // LoRa receive
  FOSSASAT_DEBUG_PRINTLN(F("LoRa Rx"));
  FOSSASAT_DEBUG_DELAY(100);
  radio.setDio1Action(Communication_Receive_Interrupt);
  radio.startReceive();

  uint32_t start = millis();
  while(millis() - start <= (uint32_t)LORA_RECEIVE_WINDOW_LENGTH * (uint32_t)1000) {
    Power_Control_Delay(SLEEP_1S, true);
    if(dataReceived) {
      radio.standby();
      Communication_Process_Packet();
      radio.startReceive();
    }
  }

  // GFSK receive
  Communication_Set_Modem(MODEM_FSK);
  FOSSASAT_DEBUG_PRINTLN(F("FSK Rx"));
  FOSSASAT_DEBUG_DELAY(100);
  radio.setDio1Action(Communication_Receive_Interrupt);
  radio.startReceive();

  start = millis();
  while(millis() - start <= (uint32_t)FSK_RECEIVE_WINDOW_LENGTH * (uint32_t)1000) {
    Power_Control_Delay(SLEEP_1S, true);
    if(dataReceived) {
      radio.standby();
      Communication_Process_Packet();
      radio.startReceive();
    }
  }

  radio.clearDio1Action();

  // set everything to sleep
  uint32_t interval = Power_Control_Get_Sleep_Interval();
  FOSSASAT_DEBUG_PRINT(F("Sleep for "));
  FOSSASAT_DEBUG_PRINTLN(interval);
  FOSSASAT_DEBUG_DELAY(100);
  Power_Control_Delay(interval, true, true);
}
