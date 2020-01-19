#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include "FossaSat1B.h"

/**
 * @defgroup configuration_page Configuration
 * @{
 */


// string length limit
#define MAX_STRING_LENGTH                               32

// message length limit
#define MAX_MESSAGE_LENGTH                              64

/**
 * @defgroup defines_debug_macros Debug Macros (only comment out for debug usage.)
 * @{
 */
#define ENABLE_TRANSMISSION_CONTROL                                 /*!< Comment out to disable transmission control (transmission disable and no transmissions in low power mode) */
#define ENABLE_DEPLOYMENT_SEQUENCE                                  /*!< Comment out to disable deployment sequence */
#define ENABLE_INTERVAL_CONTROL                                     /*!< Comment out to disable automatic sleep interval control */
#define ENABLE_INA226                                               /*!< Comment out to skip INA226 reading */
//#define EEPROM_WIPE                                               /*!< Uncomment to wipe EEPROM on start (will also set all EEPROM variables to defaults) */
/**
 * @}
 */


/**
 * @defgroup defines_power_management_configuration Power Management Configuration
 * @{
 */
#define BATTERY_VOLTAGE_LIMIT                           3.8f        /*!< Battery voltage limit to enable low power mode (V). */
#define BATTERY_CW_BEEP_VOLTAGE_LIMIT                   3.8f        /*!< Battery voltage limit to enable low power mode (V). */
#define BATTERY_TEMPERATURE_LIMIT                       -0.7f       /*!< Battery charging temperature limit (deg. C). */
#define WATCHDOG_LOOP_HEARTBEAT_PERIOD                  1000        /*!< Watchdog heartbeat period in loop() (ms). */
#define SLEEP_LENGTH_CONSTANT                           0.9         /*!< Sleep times are multiplied by this constant to compensate for the LowPower libraries overhead. */
#define DEPLOYMENT_ATTEMPTS                             2           /*!< Number of deployment attempts. */
#define DEPLOYMENT_SLEEP_LENGTH                         180000      /*!< Sleep for this period of time before deployment (ms) */
#define DEPLOYMENT_DEBUG_LENGTH                         60          /*!< How long to wait until the debugging print routine breaks (s). See: FossaSat1B.ino */
#define DEPLOYMENT_DEBUG_SAMPLE_PERIOD                  1000        /*!< How long to wait between each debug parameter print (ms). See: FossaSat1B.ino */
/**
 * @}
 */

/**
 * @defgroup defines_default_power_configuration Default Power Configuration
 * @{
 */
#define LOW_POWER_MODE_ACTIVE                           0           /*!< Whether the low power mode is currently active (0 is no, 1 is yes). */
#define LOW_POWER_MODE_ENABLED                          1           /*!< Whether the low power mode can be active (0 is no, 1 is yes).*/
#define MPPT_TEMP_SWITCH_ENABLED                        1           /*!< Whether the temperature affects the MPPT circuits (0 is no, 1 is yes). */
#define MPPT_KEEP_ALIVE_ENABLED                         0           /*!< Whether the MPPT circuit disabling feature is enabled (0 is no, 1 is yes).*/
#define TRANSMIT_ENABLED                                1           /*!< Whether the satellite can transmit (0 is no, 1 is yes). */
/**
 * @}
 */

/**
 * @defgroup defines_ina226_configuration INA226 Configuration
 *
 * @todo Implement INA timeout (18/01/2020 RGB).
 *
 * @{
 */
#define INA_ADDR                                        0x40        /*!< The I2C address of the INA226 module. */
#define INA_TIMEOUT                                     2000        /*!< INA Timeout (ms) (not implemented).  */
#define INA_RSHUNT                                      0.1         /*!< Shunt resistor value (Ohm).  */
#define INA_MAX_CURRENT                                 0.5         /*!< Maximum Current allowed (A).  */
#define INA_REG_MANUFACTURER_ID                         0xFE        /*!< INA Reg Manufacturer Identification Number (254). */
#define INA_MANUFACTURER_ID                             0x5449      /*!< INA Manufacturer Identification Number (21577). */
/**
 * @}
 */

/**
 * @defgroup defines_eeprom_address_map EEPROM Address Map
 *
 * @brief
 * |Description|Start Address|End Address|Length (bytes)|
 * |--|--|--|--|
 * |Deployment counter (number).|0x0000|0x0000|1|
 * |Power configuration (bit set).|0x0001|0x0001|1|
 * |First run (boolean).|0x0002|0x0002|1|
 * |Restart counter (number).|0x0003|0x0004|2|
 * |Length of callsign (number).|0x0005|0x0005|1|
 * |Callsign (string).|0x0006|0x0026|32|
 * |Total|||38|
 * @{
 */

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0000|0x0000|
 */
#define EEPROM_DEPLOYMENT_COUNTER_ADDR                  0x0000
/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0001|0x0001|
 */
#define EEPROM_POWER_CONFIG_ADDR                        0x0001
/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0002|0x0002|
 */
#define EEPROM_FIRST_RUN_ADDR                           0x0002
/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0003|0x0004|
 */
#define EEPROM_RESTART_COUNTER_ADDR                     0x0003
/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0005|0x0005|
 */
#define EEPROM_CALLSIGN_LEN_ADDR                        0x0005
/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0006|0x0026|
 */
#define EEPROM_CALLSIGN_ADDR                            0x0006
/**
 * @}
 */


/**
 * @defgroup defines_eeprom_variables EEPROM Variables
 *
 * @{
 */
//EEPROM_FIRST_RUN_ADDR
#define EEPROM_RESET_VALUE                              0xFF        /*!< EEPROM reset value (255). */
#define EEPROM_FIRST_RUN                                0           /*!< The value written to the EEPROM address EEPROM_FIRST_RUN_ADDR before the startup sequence. \n See @ref defines_eeprom_address_map */
#define EEPROM_CONSECUTIVE_RUN                          1           /*!< The value written to the EEPROM address EEPROM_FIRST_RUN_ADDR after the first startup sequence. \n See @ref defines_eeprom_address_map */
/**
 * @}
 */


/**
 * @defgroup defines_pin_map Pin Map
 *
 * @todo Julian -> Please check MPPT pin, seems to be connected to PD5 on some versions.
 *
 * @brief
 * |Description|Arduino core pin|Physical pin|Mode|Direction|
 * |--|--|--|--|--|
 * |Solar Cell A Voltage.|A0|PC0|ANALOG|IN|
 * |Solar Cell B Voltage.|A7|ADC7|ANALOG|IN|
 * |Solar Cell C Voltage.|A2|PC2|ANALOG|IN|
 * |Analog source for the random number generator (should be left floating).|A6|ADC6|ANALOG|IN|
 * |MPPT power control pin.|10|PB2|DIGITAL|OUT|
 * |Deployment mosfet number 1 (controls nicrome wires).|9|PB2|DIGITAL|OUT|
 * |Deployment mosfet number 2 (controls nicrome wires).|8|PB0|DIGITAL|OUT|
 * |Watchdog signal pin.|4|PD4|DIGITAL|OUT|
 * |Radio chip select.|7|PD7|DIGITAL|OUT|
 * |Radio digital pin 1 for reading direct data.|2|PD2|DIGITAL|IN|
 * |Radio BUSY pin.|6|PD6|DIGITAL|IN|
 * |Radio NRST pin.|NC|N/A|N/A|N/A|
 *
 * @{
 */
#define ANALOG_IN_SOLAR_A_VOLTAGE_PIN                   A0          /*!< PC0 */
#define ANALOG_IN_SOLAR_B_VOLTAGE_PIN                   A7          /*!< ADC7 */
#define ANALOG_IN_SOLAR_C_VOLTAGE_PIN                   A2          /*!< PC2 */
#define ANALOG_IN_RANDOM_SEED                           A6          /*!< ADC6; used as source for randomSeed(), should be left floating */
#define DIGITAL_OUT_MPPT_PIN                            10          /*!< PB2 */
#define DIGITAL_OUT_MOSFET_1                            9           /*!< PB1 */
#define DIGITAL_OUT_MOSFET_2                            8           /*!< PB0 */
#define DIGITAL_OUT_WATCHDOG_HEARTBEAT                  4           /*!< PD4 */
#define RADIO_NSS                                       7           /*!< PD7 */
#define RADIO_DIO1                                      2           /*!< PD2 */
#define RADIO_BUSY                                      6           /*!< PD6 */
#define RADIO_NRST                                      NC          /*!< Not connected*/
/**
 * @}
 */

/**
 * @defgroup defines_tmp100_configuration TMP100 Temperature Sensor Configuration
 *
 * @{
 */
#define BOARD_TEMP_SENSOR_ADDR                          0b1001100   /*!< Board TMP100 temperature sensor Wire address. */
#define BATTERY_TEMP_SENSOR_ADDR                        0b1001011   /*!< Battery TMP100 temperature sensor Wire address. */
#define TEMP_SENSOR_REG_CONFIG                          0b01        /*!< Initial temperature sensor configuration value (1). */
#define TEMP_SENSOR_RESOLUTION_9_BITS                   0b00000000  /*!< e.g. 0.5 deg. C */
#define TEMP_SENSOR_RESOLUTION_10_BITS                  0b00100000  /*!< e.g. 0.25 deg. C */
#define TEMP_SENSOR_RESOLUTION_11_BITS                  0b01000000  /*!< e.g. 0.125 deg. C */
#define TEMP_SENSOR_RESOLUTION_12_BITS                  0b01100000  /*!< e.g. 0.0625 deg. C */
/**
 * @}
 */


/**
 * @defgroup defines_mcu_temperature_configuration  MCU Temperature Sensor Configuration
 *
 * @todo Julian -> Verify both MCU_TEMP constants give accurate internal temperature.
 *
 * @{
 */
#define MCU_TEMP_OFFSET                                 324.31      /*!< This value is used to convert the sensors temperature to the real temperature. \n t = (raw - MCU_TEMP_OFFSET) / MCU_TEMP_COEFFICIENT */
#define MCU_TEMP_COEFFICIENT                            1.22        /*!< Empirical constant*/
/**
 * @}
 */


// radio configuration

// comment out to disable RTTY
#define RTTY_ENABLED

// common
#define SYNC_WORD                                       0x12
#define TCXO_VOLTAGE                                    1.6     // V
#define LOW_POWER_LEVEL                                 10      // dBm
#define MAX_NUM_OF_BLOCKS                               3       // maximum number of AES128 blocks that will be accepted
#define LORA_RECEIVE_WINDOW_LENGTH                      40      // s
#define FSK_RECEIVE_WINDOW_LENGTH                       20      // s
#define RESPONSE_DELAY                                  1000    // ms

// LoRa
#define LORA_CARRIER_FREQUENCY                          436.7   // MHz
#define LORA_BANDWIDTH                                  125.0   // kHz dual sideband
#define LORA_SPREADING_FACTOR                           11
#define LORA_SPREADING_FACTOR_ALT                       10
#define LORA_CODING_RATE                                8       // 4/8, Extended Hamming
#define LORA_OUTPUT_POWER                               20      // dBm
#define LORA_CURRENT_LIMIT                              160.0   // mA

// Non-ISM band FSK
#define FSK_CARRIER_FREQUENCY                           436.7   // MHz
#define FSK_BIT_RATE                                    9.6     // kbps nominal
#define FSK_FREQUENCY_DEVIATION                         5.0     // kHz single-sideband
#define FSK_RX_BANDWIDTH                                19.5    // kHz single-sideband
#define FSK_OUTPUT_POWER                                20      // dBm
#define FSK_PREAMBLE_LENGTH                             16      // bits
#define FSK_DATA_SHAPING                                0.5     // GFSK filter BT product
#define FSK_CURRENT_LIMIT                               160.0   // mA

// Morse/CW configuration
#define NUM_CW_BEEPS                                    3       // number of CW sync beeps in low power mode
#define MORSE_PREAMBLE_LENGTH                           3       // number of start signal repetitions
#define MORSE_SPEED                                     40      // words per minute

// modems
#define MODEM_LORA                                      'L'
#define MODEM_FSK                                       'F'

// spreading factor modes
#define SPREADING_FACTOR_STANDARD                       0
#define SPREADING_FACTOR_ALTERNATIVE                    1

// global variables

// flag to signal interrupts enabled/disabled
extern volatile bool interruptsEnabled;

// flag to signal data was received from ISR
extern volatile bool dataReceived;

// current modem configuration
extern uint8_t currentModem;

// current spreading factor mode
extern uint8_t spreadingFactorMode;

// timestamps
extern uint32_t lastHeartbeat;

// INA226 instance
extern INA226 ina;

// RadioLib instances
extern SX1268 radio;
extern MorseClient morse;

// transmission password
extern const char* password;

// encryption key
extern const uint8_t encryptionKey[];

void Configuration_Setup_Pins();

/** Endof configuration module
 * @}
 */

#endif
