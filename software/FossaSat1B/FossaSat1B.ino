/**
 * @file FossaSat1B.ino
 * @author FOSSA Systems
 * @brief
 *
 */

#include "FossaSat1B.h"

// compile-time checks
#if (!defined RADIOLIB_VERSION) || (RADIOLIB_VERSION < 0x03010000)
  #error "Unsupported RadioLib version (< 3.1.0)!"
#endif

#if defined(FOSSASAT_STATIC_ONLY) && (!defined(RADIOLIB_STATIC_ONLY))
  #error "RadioLib is using dynamic memory management, enable static only in RadioLib/src/TypeDef.h"
#endif

// cppcheck-suppress unusedFunction
void setup() {
  // initialize debug port
  FOSSASAT_DEBUG_PORT.begin(FOSSASAT_DEBUG_SPEED);
  FOSSASAT_DEBUG_PORT.println();

  // increment reset counter
  FOSSASAT_DEBUG_PORT.print(F("Restart #"));
  FOSSASAT_DEBUG_PORT.println(Persistent_Storage_Read<uint16_t>(EEPROM_RESTART_COUNTER_ADDR));
  Persistent_Storage_Increment_Counter(EEPROM_RESTART_COUNTER_ADDR);

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
  #ifdef ENABLE_INA226
    Power_Control_Setup_INA226();
  #endif

  // setup radio
  FOSSASAT_DEBUG_PORT.print(F("LoRa modem init: "));
  FOSSASAT_DEBUG_PORT.println(Communication_Set_Modem(MODEM_LORA));
  FOSSASAT_DEBUG_PORT.print(F("FSK modem init:\t"));
  FOSSASAT_DEBUG_PORT.println(Communication_Set_Modem(MODEM_FSK));

  #ifdef ENABLE_INA226
    FOSSASAT_DEBUG_PORT.print(F("INA226 check:\t"));
    FOSSASAT_DEBUG_PORT.println(Power_Control_INA2256_Check());
  #endif

  // check deployment
  #ifdef ENABLE_DEPLOYMENT_SEQUENCE
    uint8_t attemptNumber = Persistent_Storage_Read<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR);

    FOSSASAT_DEBUG_PORT.print(F("Deployment attempt #"));
    FOSSASAT_DEBUG_PORT.println(attemptNumber);
    delay(10);

    // check number of deployment attempts
    if (attemptNumber == 0) {
      // print sensor data for integration purposes (independently of FOSSASAT_DEBUG macro!)
      uint32_t start = millis();
      uint32_t lastSample = 0;
      while (millis() - start <= (uint32_t)DEPLOYMENT_DEBUG_LENGTH * (uint32_t)1000) {
        // check if its time for next measurement
        if (millis() - lastSample >= (uint32_t)DEPLOYMENT_DEBUG_SAMPLE_PERIOD) {
          lastSample = millis();
          FOSSASAT_DEBUG_PORT.println();

          #ifdef ENABLE_INA226
            FOSSASAT_DEBUG_PORT.print(F("Charging [V]:\t"));
            FOSSASAT_DEBUG_PORT.println(Power_Control_Get_Charging_Voltage(), 2);

            FOSSASAT_DEBUG_PORT.print(F("Charging [mA]:\t"));
            FOSSASAT_DEBUG_PORT.println(Power_Control_Get_Charging_Current(), 3);

            FOSSASAT_DEBUG_PORT.print(F("Battery [V]:\t"));
            FOSSASAT_DEBUG_PORT.println(Power_Control_Get_Battery_Voltage(), 2);
          #endif

          FOSSASAT_DEBUG_PORT.print(F("Solar A [V]:\t"));
          FOSSASAT_DEBUG_PORT.println(Pin_Interface_Read_Voltage(ANALOG_IN_SOLAR_A_VOLTAGE_PIN), 2);

          FOSSASAT_DEBUG_PORT.print(F("Solar B [V]:\t"));
          FOSSASAT_DEBUG_PORT.println(Pin_Interface_Read_Voltage(ANALOG_IN_SOLAR_B_VOLTAGE_PIN), 2);

          FOSSASAT_DEBUG_PORT.print(F("Solar C [V]:\t"));
          FOSSASAT_DEBUG_PORT.println(Pin_Interface_Read_Voltage(ANALOG_IN_SOLAR_C_VOLTAGE_PIN), 2);

          FOSSASAT_DEBUG_PORT.print(F("Battery [°C]:\t"));
          FOSSASAT_DEBUG_PORT.println(Pin_Interface_Read_Temperature(BATTERY_TEMP_SENSOR_ADDR), 2);

          FOSSASAT_DEBUG_PORT.print(F("Board [°C]:\t"));
          FOSSASAT_DEBUG_PORT.println(Pin_Interface_Read_Temperature(BOARD_TEMP_SENSOR_ADDR), 2);

          FOSSASAT_DEBUG_PORT.print(F("MCU [°C]:\t"));
          FOSSASAT_DEBUG_PORT.println(Pin_Interface_Read_Temperature_Internal());

          FOSSASAT_DEBUG_PORT.print(F("Reset:\t\t"));
          FOSSASAT_DEBUG_PORT.println(Persistent_Storage_Read<uint16_t>(EEPROM_RESTART_COUNTER_ADDR));

          FOSSASAT_DEBUG_PORT.print(F("Power config:\t0b"));
          Power_Control_Load_Configuration();
          FOSSASAT_DEBUG_PORT.println(powerConfig.val, BIN);

          FOSSASAT_DEBUG_PORT.println(F("======================="));
        }

        // pet watchdog
        if (millis() - lastHeartbeat >= WATCHDOG_LOOP_HEARTBEAT_PERIOD) {
          lastHeartbeat = millis();
          Pin_Interface_Watchdog_Heartbeat();
        }
      }

      // increment deployment counter
      Persistent_Storage_Write<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR, attemptNumber + 1);

    } else if(Persistent_Storage_Read<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR) <= DEPLOYMENT_ATTEMPTS) {
      // sleep before deployment
      FOSSASAT_DEBUG_PRINT(F("Pre-deploy sleep "));
      FOSSASAT_DEBUG_PRINTLN(DEPLOYMENT_SLEEP_LENGTH);
      FOSSASAT_DEBUG_DELAY(10);
      Power_Control_Delay(DEPLOYMENT_SLEEP_LENGTH, true, true);

      // deploy
      Deployment_Deploy();
    }

  #endif

  // reset uptime counter
  Persistent_Storage_Write<uint32_t>(EEPROM_UPTIME_COUNTER_ADDR, 0);
}

// cppcheck-suppress unusedFunction
void loop() {
  // variable to measure time when not in sleep mode
  uint32_t activeStart = millis();

  // check battery voltage
  FOSSASAT_DEBUG_PRINT(F("Battery check: "));
  #ifdef ENABLE_INA226
  float battVoltage = Power_Control_Get_Battery_Voltage();
  #else
  float battVoltage = 3.99;
  #endif
  FOSSASAT_DEBUG_PRINTLN(battVoltage, 2);
  Power_Control_Check_Battery_Limit();
  FOSSASAT_DEBUG_PRINT(F("Power config: 0b"));
  FOSSASAT_DEBUG_PRINTLN(powerConfig.val, BIN);

  // try to switch MPPT on (may be overridden by temperature check)
  Power_Control_Charge(true);

  // CW beacon
  Communication_Set_Modem(MODEM_FSK);
  FOSSASAT_DEBUG_DELAY(10);
  #ifdef ENABLE_TRANSMISSION_CONTROL
  if(!powerConfig.bits.transmitEnabled) {
    FOSSASAT_DEBUG_PRINTLN(F("Tx off by cmd"));
  } else {
  #endif

  if(battVoltage >= BATTERY_CW_BEEP_VOLTAGE_LIMIT) {
    // transmit full Morse beacon
    Communication_Send_Morse_Beacon(battVoltage);
  } else {
    // battery is low, transmit CW beeps
    for(uint8_t i = 0; i < NUM_CW_BEEPS; i++) {
      Communication_CW_Beep(500 * SLEEP_LENGTH_CONSTANT);
      Power_Control_Delay(500 * SLEEP_LENGTH_CONSTANT, true);
    }
  }

  #ifdef ENABLE_TRANSMISSION_CONTROL
  }
  #endif


  // wait for a bit
  FOSSASAT_DEBUG_DELAY(10);
  Power_Control_Delay(500, true, true);

  // send FSK system info
  Communication_Set_Modem(MODEM_FSK);
  Communication_Send_System_Info();

  // wait for a bit
  FOSSASAT_DEBUG_DELAY(10);
  Power_Control_Delay(500, true, true);

  // send LoRa system info if not in low power mode
  Communication_Set_Modem(MODEM_LORA);
  #ifdef ENABLE_INTERVAL_CONTROL
  if(!powerConfig.bits.lowPowerModeActive) {
    Communication_Send_System_Info();
  }
  #else
    Communication_Send_System_Info();
  #endif

  // wait for a bit
  FOSSASAT_DEBUG_DELAY(10);
  Power_Control_Delay(500, true, true);

  // LoRa receive
  uint8_t windowLenLoRa = Persistent_Storage_Read<uint8_t>(EEPROM_LORA_RECEIVE_LEN_ADDR);
  FOSSASAT_DEBUG_PRINT(F("LoRa Rx "));
  if(powerConfig.bits.lowPowerModeActive) {
    // use only half of the interval in low power mode
    windowLenLoRa /= 2;
    FOSSASAT_DEBUG_PRINT(F("(halved due to LP mode)"));
  }
  FOSSASAT_DEBUG_PRINTLN(windowLenLoRa);
  FOSSASAT_DEBUG_DELAY(10);
  radio.setDio1Action(Communication_Receive_Interrupt);
  radio.startReceive();

  for(uint8_t i = 0; i < windowLenLoRa * SLEEP_LENGTH_CONSTANT; i++) {
    Power_Control_Delay(1000, true);
    if(dataReceived) {
      radio.standby();
      Communication_Process_Packet();
      radio.startReceive();
    }
  }

  // GFSK receive
  uint8_t windowLenFsk = Persistent_Storage_Read<uint8_t>(EEPROM_FSK_RECEIVE_LEN_ADDR);
  Communication_Set_Modem(MODEM_FSK);
  FOSSASAT_DEBUG_PRINT(F("FSK Rx "));
  if(powerConfig.bits.lowPowerModeActive) {
    // use only half of the interval in low power mode
    windowLenFsk /= 2;
    FOSSASAT_DEBUG_PRINT(F("(halved due to LP mode)"));
  }
  FOSSASAT_DEBUG_PRINTLN(windowLenFsk);
  FOSSASAT_DEBUG_DELAY(10);
  radio.setDio1Action(Communication_Receive_Interrupt);
  radio.startReceive();

  for(uint8_t i = 0; i < windowLenFsk * SLEEP_LENGTH_CONSTANT; i++) {
    Power_Control_Delay(1000, true);
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
  FOSSASAT_DEBUG_DELAY(10);
  Power_Control_Delay(interval * SLEEP_LENGTH_CONSTANT, true, true);

  // update uptime counter
  uint32_t activeElapsed = (millis() - activeStart + 500)/1000;
  FOSSASAT_DEBUG_PRINT(activeElapsed);
  FOSSASAT_DEBUG_PRINTLN(F("s elapsed in active mode"))

  uint32_t elapsedTotal = NUM_CW_BEEPS + 2 + windowLenLoRa + windowLenFsk + activeElapsed + interval;
  FOSSASAT_DEBUG_PRINT(elapsedTotal);
  FOSSASAT_DEBUG_PRINTLN(F("s elapsed total"))

  Persistent_Storage_Write<uint32_t>(EEPROM_UPTIME_COUNTER_ADDR, Persistent_Storage_Read<uint32_t>(EEPROM_UPTIME_COUNTER_ADDR) + elapsedTotal);
}
