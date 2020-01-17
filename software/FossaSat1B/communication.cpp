#include "communication.h"

void Communication_Receive_Interrupt() {
  // check interrups are enabled
  if(!interruptsEnabled) {
    return;
  }

  // set flag
  dataReceived = true;
}

void Communication_Set_Modem(uint8_t modem) {
  int16_t state = ERR_NONE;
  FOSSASAT_DEBUG_PRINT(F("Set modem "));
  FOSSASAT_DEBUG_WRITE(modem);
  FOSSASAT_DEBUG_PRINTLN();

  // initialize requested modem
  switch (modem) {
    case MODEM_LORA:
        state = radio.begin(LORA_CARRIER_FREQUENCY,
                            LORA_BANDWIDTH,
                            LORA_SPREADING_FACTOR,
                            LORA_CODING_RATE,
                            SYNC_WORD,
                            LORA_OUTPUT_POWER,
                            LORA_CURRENT_LIMIT);
        radio.setCRC(true);
      break;
    case MODEM_FSK: {
        state = radio.beginFSK(FSK_CARRIER_FREQUENCY,
                               FSK_BIT_RATE,
                               FSK_FREQUENCY_DEVIATION,
                               FSK_RX_BANDWIDTH,
                               FSK_OUTPUT_POWER,
                               FSK_CURRENT_LIMIT,
                               FSK_PREAMBLE_LENGTH,
                               FSK_DATA_SHAPING);
        uint8_t syncWordFSK[2] = {SYNC_WORD, SYNC_WORD};
        radio.setSyncWord(syncWordFSK, 2);
        radio.setCRC(2);
      } break;
    default:
      FOSSASAT_DEBUG_PRINT(F("Unkown modem "));
      FOSSASAT_DEBUG_PRINTLN(modem);
      return;
  }

  radio.setDio2AsRfSwitch(true);

  // handle possible error codes
  FOSSASAT_DEBUG_PRINT(F("Radio init "));
  FOSSASAT_DEBUG_PRINTLN(state);
  if (state != ERR_NONE) {
    // radio chip failed, restart
    Pin_Interface_Watchdog_Restart();
  }

  // set spreading factor
  Communication_Set_SpreadingFactor(spreadingFactorMode);

  // set TCXO
  radio.setTCXO(TCXO_VOLTAGE);

  // save current modem
  currentModem = modem;
}

int16_t Communication_Set_SpreadingFactor(uint8_t sfMode) {
  uint8_t sfs[] = {LORA_SPREADING_FACTOR, LORA_SPREADING_FACTOR_ALT};

  // check currently active modem
  if(currentModem == MODEM_FSK) {
    return(ERR_WRONG_MODEM);
  }

  // update standard/alternative spreading factor
  int16_t state = radio.setSpreadingFactor(sfs[sfMode]);

  // only save current spreading factor mode if the change was successful
  if(state == ERR_NONE) {
    spreadingFactorMode = sfMode;
  }

  return(state);
}

int16_t Communication_Set_Configuration(uint8_t* optData, uint8_t optDataLen) {
  // check optDataLen
  if(!((optDataLen >= 7 + 1) && (optDataLen <= 7 + MAX_STRING_LENGTH))) {
    FOSSASAT_DEBUG_PRINT(F("Invalid optDataLen: "));
    FOSSASAT_DEBUG_PRINTLN(optDataLen);
    return(ERR_PACKET_TOO_LONG);
  }

  // check bandwidth value (loaded from array - rest of settings are checked by library)
  if(optData[0] > 7) {
    FOSSASAT_DEBUG_PRINTLN(F("Invalid BW!"));
    return(ERR_INVALID_BANDWIDTH);
  }

  // attempt to change the settings
  float bws[] = {7.8, 10.4, 15.6, 20.8, 31.25, 41.7, 62.5, 125.0};
  uint16_t preambleLength = 0;
  memcpy(&preambleLength, optData + 3, sizeof(uint16_t));
  uint16_t state = radio.begin(LORA_CARRIER_FREQUENCY,
                               bws[optData[0]],
                               optData[1],
                               optData[2],
                               SYNC_WORD,
                               optData[6],
                               LORA_CURRENT_LIMIT,
                               preambleLength);
  if(state != ERR_NONE) {
    return(state);
  }

  // set CRC
  state = radio.setCRC(optData[5]);
  return(state);
}

void Communication_Send_Morse_Beacon(float battVoltage) {
  // initialize Morse client
  morse.begin(FSK_CARRIER_FREQUENCY, MORSE_SPEED);

  // read callsign
  uint8_t callsignLen = Persistent_Storage_Read<uint8_t>(EEPROM_CALLSIGN_LEN_ADDR);
  char callsign[MAX_STRING_LENGTH + 1];
  System_Info_Get_Callsign(callsign, callsignLen);

  // send start signals
  for(uint8_t i = 0; i < MORSE_PREAMBLE_LENGTH; i++) {
    morse.startSignal();
    FOSSASAT_DEBUG_PRINT('*');
    Pin_Interface_Watchdog_Heartbeat();
  }

  // send callsign
  for(uint8_t i = 0; i < callsignLen - 1; i++) {
    morse.print(callsign[i]);
    FOSSASAT_DEBUG_PRINT(callsign[i]);
    Pin_Interface_Watchdog_Heartbeat();
  }

  // space
  morse.print(' ');
  FOSSASAT_DEBUG_PRINT(' ');
  Pin_Interface_Watchdog_Heartbeat();

  // send battery voltage
  morse.println(battVoltage, 2);
  FOSSASAT_DEBUG_PRINTLN(battVoltage, 2);
  Pin_Interface_Watchdog_Heartbeat();
}

void Communication_CW_Beep() {
  radio.transmitDirect();
  LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
  radio.standby();
}

void Communication_Send_System_Info() {
  // build response frame
  static const uint8_t optDataLen = 6*sizeof(uint8_t) + 3*sizeof(int16_t) + sizeof(uint16_t) + sizeof(int8_t);
  uint8_t optData[optDataLen];
  uint8_t* optDataPtr = optData;

  FOSSASAT_DEBUG_PRINTLN(F("System info:"));

  // set batteryChargingVoltage variable
  #ifdef ENABLE_INA226
    uint8_t batteryChargingVoltage = Power_Control_Get_Charging_Voltage() * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  #else
    uint8_t batteryChargingVoltage = 4.02 * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  #endif
  memcpy(optDataPtr, &batteryChargingVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);
  FOSSASAT_DEBUG_PRINT(batteryChargingVoltage);
  FOSSASAT_DEBUG_PRINT('*');
  FOSSASAT_DEBUG_PRINT(VOLTAGE_MULTIPLIER);
  FOSSASAT_DEBUG_PRINTLN(F(" mV"));

  // set batteryChragingCurrent variable
  #ifdef ENABLE_INA226
    int16_t batteryChragingCurrent = Power_Control_Get_Charging_Current() * (CURRENT_UNIT / CURRENT_MULTIPLIER);
  #else
    int16_t batteryChragingCurrent = 0xAA19;
  #endif
  memcpy(optDataPtr, &batteryChragingCurrent, sizeof(int16_t));
  optDataPtr += sizeof(int16_t);
  FOSSASAT_DEBUG_PRINT(batteryChragingCurrent);
  FOSSASAT_DEBUG_PRINT('*');
  FOSSASAT_DEBUG_PRINT(CURRENT_MULTIPLIER);
  FOSSASAT_DEBUG_PRINTLN(F(" uA"));

  // set batteryVoltage variable
  #ifdef ENABLE_INA226
    uint8_t batteryVoltage = Power_Control_Get_Battery_Voltage() * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  #else
    uint8_t batteryVoltage = 4.02 * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  #endif
  memcpy(optDataPtr, &batteryVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);
  FOSSASAT_DEBUG_PRINT(batteryVoltage);
  FOSSASAT_DEBUG_PRINT('*');
  FOSSASAT_DEBUG_PRINT(VOLTAGE_MULTIPLIER);
  FOSSASAT_DEBUG_PRINTLN(F(" mV"));

  // set solarCellAVoltage variable
  //uint8_t solarCellAVoltage = Pin_Interface_Read_Voltage(ANALOG_IN_SOLAR_A_VOLTAGE_PIN) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  uint8_t solarCellAVoltage = 1.26 * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &solarCellAVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);
  FOSSASAT_DEBUG_PRINT(solarCellAVoltage);
  FOSSASAT_DEBUG_PRINT('*');
  FOSSASAT_DEBUG_PRINT(VOLTAGE_MULTIPLIER);
  FOSSASAT_DEBUG_PRINTLN(F(" mV"));

  // set solarCellBVoltage variable
  //uint8_t solarCellBVoltage = Pin_Interface_Read_Voltage(ANALOG_IN_SOLAR_B_VOLTAGE_PIN) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  uint8_t solarCellBVoltage = 0.42 * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &solarCellBVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);
  FOSSASAT_DEBUG_PRINT(solarCellBVoltage);
  FOSSASAT_DEBUG_PRINT('*');
  FOSSASAT_DEBUG_PRINT(VOLTAGE_MULTIPLIER);
  FOSSASAT_DEBUG_PRINTLN(F(" mV"));

  // set solarCellCVoltage variable
  //uint8_t solarCellCVoltage = Pin_Interface_Read_Voltage(ANALOG_IN_SOLAR_C_VOLTAGE_PIN) * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  uint8_t solarCellCVoltage = 0.0 * (VOLTAGE_UNIT / VOLTAGE_MULTIPLIER);
  memcpy(optDataPtr, &solarCellCVoltage, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);
  FOSSASAT_DEBUG_PRINT(solarCellCVoltage);
  FOSSASAT_DEBUG_PRINT('*');
  FOSSASAT_DEBUG_PRINT(VOLTAGE_MULTIPLIER);
  FOSSASAT_DEBUG_PRINTLN(F(" mV"));

  // set batteryTemperature variable
  //int16_t batteryTemperature = Pin_Interface_Read_Temperature(BATTERY_TEMP_SENSOR_ADDR) * (TEMPERATURE_UNIT / TEMPERATURE_MULTIPLIER);
  int16_t batteryTemperature = 9.5 * (TEMPERATURE_UNIT / TEMPERATURE_MULTIPLIER);
  memcpy(optDataPtr, &batteryTemperature, sizeof(int16_t));
  optDataPtr += sizeof(int16_t);
  FOSSASAT_DEBUG_PRINT(batteryTemperature);
  FOSSASAT_DEBUG_PRINT('*');
  FOSSASAT_DEBUG_PRINT(TEMPERATURE_MULTIPLIER);
  FOSSASAT_DEBUG_PRINTLN(F(" mdeg C"));

  // set boardTemperature variable
  //int16_t boardTemperature = Pin_Interface_Read_Temperature(BOARD_TEMP_SENSOR_ADDR) * (TEMPERATURE_UNIT / TEMPERATURE_MULTIPLIER);
  int16_t boardTemperature = 38.75 * (TEMPERATURE_UNIT / TEMPERATURE_MULTIPLIER);
  memcpy(optDataPtr, &boardTemperature, sizeof(int16_t));
  optDataPtr += sizeof(int16_t);
  FOSSASAT_DEBUG_PRINT(boardTemperature);
  FOSSASAT_DEBUG_PRINT('*');
  FOSSASAT_DEBUG_PRINT(TEMPERATURE_MULTIPLIER);
  FOSSASAT_DEBUG_PRINTLN(F(" mdeg C"));

  // set mcuTemperature variable (read twice since first value is often nonsense)
  Pin_Interface_Read_Temperature_Internal();
  int8_t mcuTemperature = Pin_Interface_Read_Temperature_Internal();
  memcpy(optDataPtr, &mcuTemperature, sizeof(int8_t));
  optDataPtr += sizeof(int8_t);
  FOSSASAT_DEBUG_PRINTLN(mcuTemperature);

  // set resetCounter variable
  uint16_t resetCounter = Persistent_Storage_Read<uint16_t>(EEPROM_RESTART_COUNTER_ADDR);
  memcpy(optDataPtr, &resetCounter, sizeof(uint16_t));
  optDataPtr += sizeof(uint16_t);
  FOSSASAT_DEBUG_PRINTLN(resetCounter);

  // set powerConfig variable
  Power_Control_Load_Configuration();
  FOSSASAT_DEBUG_PRINT(F("Config: 0b"));
  FOSSASAT_DEBUG_PRINTLN(powerConfig.val, BIN);
  memcpy(optDataPtr, &powerConfig.val, sizeof(uint8_t));
  optDataPtr += sizeof(uint8_t);

  // send as raw bytes
  Communication_Send_Response(RESP_SYSTEM_INFO, optData, optDataLen, false);
}

void Communication_Process_Packet() {
  // disable interrupts
  interruptsEnabled = false;

  // read data
  size_t len = radio.getPacketLength();
  if(len == 0) {
    dataReceived = false;
    interruptsEnabled = true;
    return;
  }
  uint8_t* frame = new uint8_t[len];
  int16_t state = radio.readData(frame, len);

  // check reception state
  if(state == ERR_NONE) {
    FOSSASAT_DEBUG_PRINT(F("Got frame "));
    FOSSASAT_DEBUG_PRINTLN(len);
    FOSSASAT_DEBUG_PRINT_BUFF(frame, len);

    // check callsign
    uint8_t callsignLen = Persistent_Storage_Read<uint8_t>(EEPROM_CALLSIGN_LEN_ADDR);
    char callsign[MAX_STRING_LENGTH + 1];
    System_Info_Get_Callsign(callsign, callsignLen);
    if(memcmp(frame, (uint8_t*)callsign, callsignLen - 1) == 0) {
      // check passed
      Comunication_Parse_Frame(frame, len);
    } else {
      FOSSASAT_DEBUG_PRINTLN(F("Callsign mismatch!"));
    }

  }

  // deallocate memory
  delete[] frame;

  // reset flag
  dataReceived = false;

  // enable interrupts
  interruptsEnabled = true;
}

void Comunication_Parse_Frame(uint8_t* frame, size_t len) {
  // read callsign from EEPROM
  uint8_t callsignLen = Persistent_Storage_Read<uint8_t>(EEPROM_CALLSIGN_LEN_ADDR);
  char callsign[MAX_STRING_LENGTH + 1];
  System_Info_Get_Callsign(callsign, callsignLen);

  // get functionID
  int16_t functionId = FCP_Get_FunctionID(callsign, frame, len);
  if(functionId < 0) {
    FOSSASAT_DEBUG_PRINT(F("Unable to get func. ID "));
    FOSSASAT_DEBUG_PRINTLN(functionId);
    return;
  }
  FOSSASAT_DEBUG_PRINT(F("Func. ID = 0x"));
  FOSSASAT_DEBUG_PRINTLN(functionId, HEX);

  // check encryption
  int16_t optDataLen = 0;
  uint8_t* optData = NULL;
  if(functionId >= PRIVATE_OFFSET) {
    // frame contains encrypted data, decrypt
    FOSSASAT_DEBUG_PRINTLN(F("Decrypting"));

    // get optional data length
    optDataLen = FCP_Get_OptData_Length(callsign, frame, len, encryptionKey, password);
    if(optDataLen < 0) {
      FOSSASAT_DEBUG_PRINT(F("Decrypt failed "));
      FOSSASAT_DEBUG_PRINTLN(optDataLen);

      // incorrect password, report to ground
      if(optDataLen == ERR_INCORRECT_PASSWORD) {
        FOSSASAT_DEBUG_PRINTLN(F("Wrong password!"));

        // build frame
        uint8_t encSectionLen = len - callsignLen;
        uint8_t* encSection = new uint8_t[encSectionLen];

        // copy encrypted section
        memcpy(encSection, frame + callsignLen, encSectionLen);

        // decrypt
        struct AES_ctx ctx;
        AES_init_ctx(&ctx, encryptionKey);
        uint8_t numBlocks = encSectionLen / 16;
        for(uint8_t i = 0; i < numBlocks; i++) {
          AES_ECB_decrypt(&ctx, encSection + (i * 16));
        }

        // copy into the response frame
        uint8_t failedOptDataLen = encSection[0];
        uint8_t maxLen = 16 * MAX_NUM_OF_BLOCKS;
        if(failedOptDataLen > maxLen) {
          // if we exceed allowed number of AES128 blocks, decryption probably failed due to wrong key
          failedOptDataLen = maxLen;
        }
        uint8_t* failedOptData = new uint8_t[failedOptDataLen];
        memcpy(failedOptData, encSection + 1, failedOptDataLen);
        delete[] encSection;

        // send response
        Communication_Send_Response_Encrypted(RESP_INCORRECT_PASSWORD, failedOptData, failedOptDataLen);

        // deallocate memory
        delete[] failedOptData;
      }

      // decryption failed, return
      return;
    }

    // get optional data
    if(optDataLen > 0) {
      optData = new uint8_t[optDataLen];
      FCP_Get_OptData(callsign, frame, len, optData, encryptionKey, password);
    }

  } else {
    // no decryption necessary

    // get optional data length
    optDataLen = FCP_Get_OptData_Length(callsign, frame, len);
    if(optDataLen < 0) {
      // optional data extraction failed,
      FOSSASAT_DEBUG_PRINT(F("Failed to get optDataLen "));
      FOSSASAT_DEBUG_PRINTLN(optDataLen);
      return;
    }

    // get optional data
    if(optDataLen > 0) {
      optData = new uint8_t[optDataLen];
      FCP_Get_OptData(callsign, frame, len, optData);
    }
  }

  // check optional data presence
  if(optDataLen > 0) {
    // execute with optional data
    FOSSASAT_DEBUG_PRINT(F("optDataLen = "));
    FOSSASAT_DEBUG_PRINTLN(optDataLen);
    FOSSASAT_DEBUG_PRINT_BUFF(optData, (uint8_t)optDataLen);
    Communication_Execute_Function(functionId, optData, optDataLen);

  } else {
    // execute without optional data
    Communication_Execute_Function(functionId);
  }

  // deallocate memory
  delete[] optData;
}

void Communication_Execute_Function(uint8_t functionId, uint8_t* optData, size_t optDataLen) {
  // delay before responding
  FOSSASAT_DEBUG_DELAY(100);
  Power_Control_Delay(RESPONSE_DELAY, true);

  // execute function based on ID
  switch(functionId) {
    case CMD_PING:
      // send pong
      Communication_Send_Response(RESP_PONG);
      break;

    case CMD_RETRANSMIT: {
        // check message length
        if(optDataLen <= MAX_MESSAGE_LENGTH) {
          // respond with the requested data
          Communication_Send_Response(RESP_REPEATED_MESSAGE, optData, optDataLen);
        }
      } break;

    case CMD_RETRANSMIT_CUSTOM: {
        // check message length
          if(optDataLen <= MAX_MESSAGE_LENGTH + 7) {
          // change modem configuration
          int16_t state = Communication_Set_Configuration(optData, optDataLen);

          // check if the change was successful
          if(state != ERR_NONE) {
            FOSSASAT_DEBUG_PRINT(F("Custom config failed "));
            FOSSASAT_DEBUG_PRINTLN(state);
          } else {
            // configuration changed successfully, transmit response
            uint8_t repeatedMessageLen = optDataLen - 7;
            uint8_t* repeatedMessage = new uint8_t[repeatedMessageLen];
            memcpy(repeatedMessage, optData + 7, repeatedMessageLen);
            Communication_Send_Response(RESP_REPEATED_MESSAGE_CUSTOM, repeatedMessage, repeatedMessageLen, true);

            // deallocate memory
            delete[] repeatedMessage;
          }
        }
      } break;

    case CMD_TRANSMIT_SYSTEM_INFO:
      // send system info via LoRa
      Communication_Send_System_Info();
      break;

    case CMD_GET_LAST_PACKET_INFO: {
        // get last packet info and send it
        uint8_t respOptData[] = {(uint8_t)(radio.getSNR() * 4.0), (uint8_t)(radio.getRSSI() * -2.0)};
        Communication_Send_Response(RESP_LAST_PACKET_INFO, respOptData, 2);
      } break;

    case CMD_DEPLOY: {
        // run deployment sequence
        Deployment_Deploy();

        // get deployment counter value and send it
        uint8_t counter = Persistent_Storage_Read<uint8_t>(EEPROM_DEPLOYMENT_COUNTER_ADDR);
        Communication_Send_Response_Encrypted(RESP_DEPLOYMENT_STATE, &counter, 1);
      } break;

    case CMD_RESTART:
      // restart satellite
      Pin_Interface_Watchdog_Restart();
      break;

    case CMD_WIPE_EEPROM:
      // wipe EEPROM and reset all EEPROM variables to default values
      Persistent_Storage_Wipe();
      break;

    case CMD_SET_TRANSMIT_ENABLE: {
        // check optional data is exactly 1 byte
        if(Communication_Check_OptDataLen(1, optDataLen)) {
          // load power config from EEPROM
          Power_Control_Load_Configuration();

          // update transmit enable flag
          powerConfig.bits.transmitEnabled = optData[0];
          FOSSASAT_DEBUG_PRINT(F("transmitEnabled="));
          FOSSASAT_DEBUG_PRINTLN(optData[0]);

          // save power config from EEPROM
          Power_Control_Save_Configuration();
        }
      } break;

    case CMD_SET_CALLSIGN: {
        // check optional data is less than limit
        if(optDataLen <= MAX_STRING_LENGTH) {
          // get callsign from frame
          char* newCallsign = new char[optDataLen + 1];
          memcpy(newCallsign, optData, optDataLen);
          newCallsign[optDataLen] = '\0';

          // update callsign
          System_Info_Set_Callsign(newCallsign);
          FOSSASAT_DEBUG_PRINT(F("newCallsign="));
          FOSSASAT_DEBUG_PRINTLN(newCallsign);

          // deallocate memory
          delete[] newCallsign;
        }
      } break;

    case CMD_SET_SF_MODE: {
        // check optional data is exactly 1 byte
        if(Communication_Check_OptDataLen(1, optDataLen)) {
          // update spreading factor mode
          spreadingFactorMode = optData[0];
          FOSSASAT_DEBUG_PRINT(F("spreadingFactorMode="));
          FOSSASAT_DEBUG_PRINTLN(optData[0]);
        }
      } break;

    case CMD_SET_MPPT_MODE: {
        // check optional data is exactly 2 bytes
        if(Communication_Check_OptDataLen(2, optDataLen)) {
          // load power config from EEPROM
          Power_Control_Load_Configuration();

          // update MPPT mode
          powerConfig.bits.mpptTempSwitchEnabled = optData[0];
          powerConfig.bits.mpptKeepAliveEnabled = optData[1];
          FOSSASAT_DEBUG_PRINT(F("mpptTempSwitchEnabled="));
          FOSSASAT_DEBUG_PRINTLN(optData[0]);
          FOSSASAT_DEBUG_PRINT(F("mpptKeepAliveEnabled="));
          FOSSASAT_DEBUG_PRINTLN(optData[1]);

          // save power config from EEPROM
          Power_Control_Save_Configuration();
        }
      } break;

    case CMD_SET_LOW_POWER_ENABLE: {
        // check optional data is exactly 1 byte
        if(Communication_Check_OptDataLen(1, optDataLen)) {
          // load power config from EEPROM
          Power_Control_Load_Configuration();

          // update low power enable flag
          powerConfig.bits.lowPowerModeEnabled = optData[0];
          FOSSASAT_DEBUG_PRINT(F("lowPowerModeEnabled="));
          FOSSASAT_DEBUG_PRINTLN(optData[0]);

          // save power config from EEPROM
          Power_Control_Save_Configuration();
        }
      } break;
  }
}

int16_t Communication_Send_Response(uint8_t respId, uint8_t* optData, size_t optDataLen, bool overrideModem) {
  // read callsign from EEPROM
  uint8_t callsignLen = Persistent_Storage_Read<uint8_t>(EEPROM_CALLSIGN_LEN_ADDR);
  char callsign[MAX_STRING_LENGTH + 1];
  System_Info_Get_Callsign(callsign, callsignLen);

  // build response frame
  uint8_t len = FCP_Get_Frame_Length(callsign, optDataLen);
  uint8_t* frame = new uint8_t[len];
  FCP_Encode(frame, callsign, respId, optDataLen, optData);

  // send response
  int16_t state = Communication_Transmit(frame, len, overrideModem);

  // deallocate memory
  delete[] frame;

  return(state);
}

int16_t Communication_Send_Response_Encrypted(uint8_t respId, uint8_t* optData, size_t optDataLen, bool overrideModem) {
  // read callsign from EEPROM
  uint8_t callsignLen = Persistent_Storage_Read<uint8_t>(EEPROM_CALLSIGN_LEN_ADDR);
  char callsign[MAX_STRING_LENGTH + 1];
  System_Info_Get_Callsign(callsign, callsignLen);

  // build response frame
  uint8_t len = FCP_Get_Frame_Length(callsign, optDataLen, password);
  uint8_t* frame = new uint8_t[len];
  FCP_Encode(frame, callsign, respId, optDataLen, optData, encryptionKey, password);

  // send response
  int16_t state = Communication_Transmit(frame, len, overrideModem);

  // deallocate memory
  delete[] frame;

  return(state);
}

int16_t Communication_Transmit(uint8_t* data, uint8_t len, bool overrideModem) {
  // check transmit enable flag
  #ifdef ENABLE_TRANSMISSION_CONTROL
    Power_Control_Load_Configuration();
    if(!powerConfig.bits.transmitEnabled) {
      FOSSASAT_DEBUG_PRINTLN(F("Tx off by cmd"));
      return(ERR_TX_TIMEOUT);
    }
  #endif

  // disable receive interrupt
  radio.clearDio1Action();

  // print frame for debugging
  FOSSASAT_DEBUG_PRINT(F("Sending frame "));
  FOSSASAT_DEBUG_PRINTLN(len);
  FOSSASAT_DEBUG_PRINT_BUFF(data, len);

  // check if modem should be switched - required for transmissions with custom settings
  uint8_t modem = currentModem;
  FOSSASAT_DEBUG_PRINT(F("Using modem "));
  if(overrideModem) {
    FOSSASAT_DEBUG_WRITE(MODEM_LORA);
    FOSSASAT_DEBUG_PRINTLN(F(" (overridden)"));
    Communication_Set_Modem(MODEM_LORA);
  } else {
    FOSSASAT_DEBUG_WRITE(modem);
    FOSSASAT_DEBUG_PRINTLN();
  }

  // get timeout
  uint32_t timeout = (float)radio.getTimeOnAir(len) * 1.5;

  // start transmitting
  int16_t state = radio.startTransmit(data, len);
  if(state != ERR_NONE) {
    FOSSASAT_DEBUG_PRINT(F("Tx failed "));
    FOSSASAT_DEBUG_PRINTLN(state);
    return(state);
  }

  // wait for transmission finish
  uint32_t start = micros();
  uint32_t lastBeat = 0;
  while(!digitalRead(RADIO_DIO1)) {
    // pet watchdog every second
    if(micros() - lastBeat > (uint32_t)WATCHDOG_LOOP_HEARTBEAT_PERIOD * (uint32_t)1000) {
      Pin_Interface_Watchdog_Heartbeat();
      lastBeat = micros();
    }

    // check timeout
    if(micros() - start > timeout) {
      // timed out while transmitting
      radio.standby();
      Communication_Set_Modem(modem);
      FOSSASAT_DEBUG_PRINT(F("Tx timeout"));
      return(ERR_TX_TIMEOUT);
    }
  }

  // transmission done, set mode standby
  state = radio.standby();

  // restore modem
  if(overrideModem) {
    Communication_Set_Modem(modem);
  }

  // set receive ISR
  radio.setDio1Action(Communication_Receive_Interrupt);

  FOSSASAT_DEBUG_PRINTLN(F("done"));

  return(state);
}

bool Communication_Check_OptDataLen(uint8_t expected, uint8_t actual) {
  if(expected != actual) {
    // received length of optional data does not match expected
    FOSSASAT_DEBUG_PRINT(F("optDataLen mismatch, exp. "));
    FOSSASAT_DEBUG_PRINT(expected);
    FOSSASAT_DEBUG_PRINT(F(" got "));
    FOSSASAT_DEBUG_PRINTLN(actual);
    return(false);
  }

  return(true);
}
