/*
   RadioLib SX126x Transmit Example

   This example transmits packets using SX1262 LoRa radio module.
   Each packet contains up to 256 bytes of data, in the form of:
    - Arduino String
    - null-terminated char array (C-string)
    - arbitrary binary data (byte array)

   Other modules from SX126x family can also be used.

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/RadioLib/
*/

// include the library
#include <RadioLib.h>

// SX1262 has the following connections:
// NSS pin:   10
// DIO1 pin:  2
// NRST pin:  3
// BUSY pin:  9
SX1262 lora = new Module(10, 2, 3, 9);

// or using RadioShield
// https://github.com/jgromes/RadioShield
//SX1262 lora = RadioShield.ModuleA;

void setup() {
  Serial.begin(9600);

  // initialize SX1262 with default settings
  Serial.print(F("Initializing ... "));
  // carrier frequency:           434.0 MHz
  // bandwidth:                   125.0 kHz
  // spreading factor:            9
  // coding rate:                 7
  // sync word:                   0x12 (private network)
  // output power:                14 dBm
  // current limit:               60 mA
  // preamble length:             8 symbols
  // TCXO voltage:                1.6 V (set to 0 to not use TCXO)
  // CRC:                         enabled
  int state = lora.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
}

void setPower() {
  Serial.println(F("Enter transmit power in dBm (-09 to +22)"));

  // get data
  while(Serial.available() < 3);
  char powerStr[4];
  for(uint8_t i = 0; i < 4; i++) {
    powerStr[i] = Serial.read();
  }
  powerStr[3] = '\0';

  // wait for a bit to receive any trailing characters
  delay(100);

  // dump the serial buffer
  while (Serial.available()) {
    Serial.read();
  }

  // get the number
  int16_t power = atoi(powerStr+1);
  if(powerStr[0] == '-') {
    power *= -1;
  }

  // set power
  Serial.print(F("Setting power to "));
  Serial.print(power);
  Serial.print(F(" dBm, status "));
  Serial.println(lora.setOutputPower(power));
}

void loop() {
  // request power config
  setPower();
  
  // send 10 packets
  Serial.println(F("Transmitting 10 packets"));
  for(uint8_t i = 0; i < 10; i++) {
    // send one packet
    int state = lora.transmit("Hello World!");
  
    // check the state
    if (state == ERR_NONE) {
      Serial.println(F("Success!"));
    } else {
      Serial.print(F("Failed, code "));
      Serial.println(state);
  
    }
  
    // wait for a second before transmitting again
    delay(1000);
  }
}
