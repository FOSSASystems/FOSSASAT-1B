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

void Power_Control_Load_Configuration() {
  powerConfig.val = Persistent_Storage_Read<uint8_t>(EEPROM_POWER_CONFIG_ADDR);
}

void Power_Control_Save_Configuration() {
  Persistent_Storage_Write<uint8_t>(EEPROM_POWER_CONFIG_ADDR, powerConfig.val);
}

void Power_Control_Charge(bool charge) {
  FOSSASAT_VERBOSE_PRINT(F("MPPT "));
  FOSSASAT_VERBOSE_PRINTLN(charge);

  Power_Control_Load_Configuration();
  if(powerConfig.bits.mpptKeepAliveEnabled) {
    // force MPPT to float regardless of anything else
    FOSSASAT_VERBOSE_PRINTLN('K');
    pinMode(DIGITAL_OUT_MPPT_PIN, INPUT);
  } else if((Pin_Interface_Read_Temperature(BATTERY_TEMP_SENSOR_ADDR) < BATTERY_TEMPERATURE_LIMIT) && powerConfig.bits.mpptTempSwitchEnabled) {
    // force MPPT low, only if temperature switch is enabled
    FOSSASAT_VERBOSE_PRINTLN('L');
    pinMode(DIGITAL_OUT_MPPT_PIN, OUTPUT);
    digitalWrite(DIGITAL_OUT_MPPT_PIN, LOW);
  } else if(charge){
    // set MPPT to float
    pinMode(DIGITAL_OUT_MPPT_PIN, INPUT);
  } else {
    // set MPPT to low
    pinMode(DIGITAL_OUT_MPPT_PIN, OUTPUT);
    digitalWrite(DIGITAL_OUT_MPPT_PIN, LOW);
  }
}

uint32_t Power_Control_Get_Sleep_Interval() {
  // sleep interval in ms (default for battery > 3.7 V)
  uint32_t interval = 0;

  #ifdef ENABLE_INTERVAL_CONTROL
    // get battery voltage
    float batt = Power_Control_Get_Battery_Voltage();

    if(batt > 4.05f) {
      interval = (uint32_t)20 * (uint32_t)1000;
    } else if(batt > 4.0f) {
      interval = (uint32_t)35 * (uint32_t)1000;
    } else if(batt > 3.9f) {
      interval = (uint32_t)100 * (uint32_t)1000;
    } else if(batt > 3.8f) {
      interval = (uint32_t)160 * (uint32_t)1000;
    } else if(batt > 3.7f) {
      interval = (uint32_t)180 * (uint32_t)1000;
    } else {
      interval = (uint32_t)240 * (uint32_t)1000;
    }
  #endif

  return(interval);
}

void Power_Control_Delay(uint32_t ms, bool sleep, bool sleepRadio) {
  if(ms == 0) {
    return;
  }

  // calculate number of required loops (rounded up)
  float numLoops = 0.5f;
  if(sleep) {
    numLoops += (float)ms / 500.0;
  } else {
    numLoops += (float)ms / 50.0;
  }

  // set radio to sleep
  if(sleepRadio) {
    radio.sleep();
  }

  // perform all loops
  for(uint32_t i = 0; i < (uint32_t)numLoops; i++) {
    Pin_Interface_Watchdog_Heartbeat();
    if(sleep) {
      LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
    } else {
      delay(50);
    }

  }

  // wake up radio
  if(sleepRadio) {
    radio.standby();
  }
}

void Power_Control_Setup_INA226() {
  ina.begin(INA_ADDR);
  ina.configure(INA226_AVERAGES_1, INA226_BUS_CONV_TIME_1100US, INA226_SHUNT_CONV_TIME_1100US, INA226_MODE_SHUNT_BUS_CONT);
  ina.calibrate(INA_RSHUNT, INA_MAX_CURRENT);
}

bool Power_Control_INA226_Check() {
  // attempt to read manufacturer ID register
  Wire.beginTransmission(INA_ADDR);
  Wire.write(INA_REG_MANUFACTURER_ID);
  Wire.endTransmission();
  delay(1);

  // try to read
  Wire.requestFrom((uint8_t)INA_ADDR, (uint8_t)2);
  if(Wire.available() != 2) {
    return(false);
  }

  // check value
  uint8_t vha = Wire.read();
  uint8_t vla = Wire.read();
  uint16_t value = vha << 8 | vla;

  if(value != INA_MANUFACTURER_ID) {
    return(false);
  }

  return(true);
}

float Power_Control_Get_Battery_Voltage() {
  // try to switch MPPT off (may be overridden by MPPT keep alive)
  Power_Control_Charge(false);

  // get voltage
  float val = -999;
  if(Power_Control_INA226_Check()) {
    val = ina.readBusVoltage();
  }

  // try to switch MPPT on (may be overridden by temperature check)
  Power_Control_Charge(true);

  return(val);
}

float Power_Control_Get_Charging_Voltage() {
  if(!Power_Control_INA226_Check()) {
    return(-999.0);
  }
  return(ina.readBusVoltage());
}

float Power_Control_Get_Charging_Current() {
  if(!Power_Control_INA226_Check()) {
    return(-999.0);
  }
  return(ina.readShuntCurrent());
}

bool Power_Control_Check_Battery_Limit() {
  // load power configuration from EEPROM
  Power_Control_Load_Configuration();

  // check battery voltage
  bool checkPassed = true;
  if((Power_Control_Get_Battery_Voltage() <= BATTERY_VOLTAGE_LIMIT) && powerConfig.bits.lowPowerModeEnabled) {
    // activate low power mode
    powerConfig.bits.lowPowerModeActive = 1;
    checkPassed = false;
  } else {
    // deactivate low power mode
    powerConfig.bits.lowPowerModeActive = 0;
    checkPassed = true;
  }

  // save power configuration to EEPROM
  Power_Control_Save_Configuration();
  return(checkPassed);
}
