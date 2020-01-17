#include "configuration.h"

// flag to signal interrupts enabled/disabled
volatile bool interruptsEnabled = true;

// flag to signal data was received from ISR
volatile bool dataReceived = false;

// current modem configuration
uint8_t currentModem;

// current spreading factor mode
uint8_t spreadingFactorMode;

// timestamps
uint32_t lastHeartbeat = 0;

// INA226 instance
INA226 ina;

// RadioLib instances
SX1268 radio = new Module(RADIO_NSS, RADIO_DIO1, RADIO_NRST, RADIO_BUSY);
MorseClient morse(&radio);

// transmission password
const char* password = "password";

// encryption key
const uint8_t encryptionKey[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00};

void Configuration_Setup_Pins() {
  // set up digital pins
  pinMode(DIGITAL_OUT_MOSFET_1, OUTPUT);
  pinMode(DIGITAL_OUT_MOSFET_2, OUTPUT);
  pinMode(DIGITAL_OUT_WATCHDOG_HEARTBEAT, OUTPUT);
  pinMode(DIGITAL_OUT_MPPT_PIN, OUTPUT);

  // set up analog pins
  pinMode(ANALOG_IN_SOLAR_A_VOLTAGE_PIN, INPUT);
  pinMode(ANALOG_IN_SOLAR_B_VOLTAGE_PIN, INPUT);
  pinMode(ANALOG_IN_SOLAR_C_VOLTAGE_PIN, INPUT);
  pinMode(ANALOG_IN_RANDOM_SEED, INPUT);

  // bring deployment MOSFETs low
  digitalWrite(DIGITAL_OUT_MOSFET_1, LOW);
  digitalWrite(DIGITAL_OUT_MOSFET_2, LOW);

  // provide seed for encrpytion PRNG
  randomSeed(analogRead(ANALOG_IN_RANDOM_SEED));
}
