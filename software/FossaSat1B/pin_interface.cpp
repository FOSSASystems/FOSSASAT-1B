#include "pin_interface.h"

void Pin_Interface_Set_Temp_Resolution(uint8_t sensorAddr, uint8_t res) {
  // set resolution
  Wire.beginTransmission(sensorAddr);
  Wire.write(TEMP_SENSOR_REG_CONFIG);
  Wire.write(res);
  Wire.endTransmission();

  // set mode back to temperature reading
  Wire.beginTransmission(sensorAddr);
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();
}

float Pin_Interface_Read_Temperature(uint8_t sensorAddr) {
  // read data from I2C sensor
  Wire.requestFrom(sensorAddr, (uint8_t)2);
  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();

  // convert raw data to temperature
  int16_t tempRaw = ((msb << 8) | lsb) >> 4;
  float temp = tempRaw * 0.0625f;
  return(temp);
}

int8_t Pin_Interface_Read_Temperature_Internal() {
  // select temperature sensor and reference
  ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3);
  // start AD conversion
  ADCSRA |= _BV(ADEN) | _BV(ADSC);
  // Detect end-of-conversion
  while (bit_is_set(ADCSRA, ADSC));
  // get raw data
  uint16_t raw =  ADCL | (ADCH << 8);

  // convert to real temperature
  int8_t temp = (int8_t)(((float)raw - MCU_TEMP_OFFSET) / MCU_TEMP_COEFFICIENT);
  return(temp);
}

float Pin_Interface_Read_Voltage(uint8_t pin) {
  // map ADC value to voltage
  return((analogRead(pin) * 3.3) / 1023.0);
}

void Pin_Interface_Watchdog_Heartbeat(bool manageBattery) {
  // toggle watchdog pin
  digitalWrite(DIGITAL_OUT_WATCHDOG_HEARTBEAT, !digitalRead(DIGITAL_OUT_WATCHDOG_HEARTBEAT));

  // check voltage
  if(manageBattery) {
    Power_Control_Check_Battery_Limit();
  }
}

void Pin_Interface_Watchdog_Restart() {
  FOSSASAT_DEBUG_PRINTLN(F("Rst"));
  
  // do not pet watchdog for more than 30 seconds to restart
  for(uint8_t i = 0; i < WATCHDOG_RESET_NUM_SLEEP_CYCLES; i++) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}
