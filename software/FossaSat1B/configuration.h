#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include "FossaSat1B.h"

/**
 * @mainpage
 *
 * # NOTICE
 * The tests given here are only guidelines, please also refer to the FOSSASAT-1 software test plans and documentation for a complete view.
 *
 * # Navigation
 * - See the modules section for help with the satellite's configuration.
 * - Each header file contains documentation.
 *
 */

/**
 * @defgroup configuration_page Configuration
 * @brief

 * @{
 */

/**
 * @defgroup defines_string_memory_limits String Limits
 * @{
 */
#define MAX_STRING_LENGTH                               32			/*!< String length limit (bytes). */
#define MAX_OPT_DATA_LENGTH                             128			/*!< Optional data length limit (bytes). */
#define MAX_RADIO_BUFFER_LENGTH                         (MAX_STRING_LENGTH + 2 + MAX_OPT_DATA_LENGTH)     /*!< Radio buffer length limit. */

/**
 * @}
 */

/**
 * @defgroup defines_debug_macros Debug Macros (only comment out for debug usage.)
 *
 * @test (ID CONF_DEBUG_MACROS_T0) (SEV 1) Uncomment ENABLE_TRANSMISSION_CONTROL, test no transmissions are produced.
 * @test (ID CONF_DEBUG_MACROS_T1) (SEV 1) Uncomment ENABLE_DEPLOYMENT_SEQUENCE, test no deployment sequence ran (this define is for debugging purposes).
 * @test (ID CONF_DEBUG_MACROS_T2) (SEV 1) Uncomment ENABLE_INTERVAL_CONTROL, test that the battery voltages have no affect on the sleep duration.
 * @test (ID CONF_DEBUG_MACROS_T3) (SEV 1) Uncomment ENABLE_INA226, test that the current readings are correct.
 * @test (ID CONF_DEBUG_MACROS_T4) (SEV 1) Uncomment EEPROM_WIPE, test that the EEPROM clears and writes defaults correctly.
 *
 * @{
 */
#define FOSSASAT_STATIC_ONLY                                        /*!< Comment out to use dynamic memory management */
#define ENABLE_TRANSMISSION_CONTROL                                 /*!< Comment out to disable transmission control (transmission disable and no transmissions in low power mode) */
#define ENABLE_DEPLOYMENT_SEQUENCE                                  /*!< Comment out to disable deployment sequence */
#define ENABLE_INTERVAL_CONTROL                                     /*!< Comment out to disable automatic sleep interval and transmission control */
#define ENABLE_INA226                                               /*!< Comment out to skip INA226 reading */
//#define EEPROM_WIPE                                               /*!< Uncomment to wipe EEPROM on start (will also set all EEPROM variables to defaults) */
/**
 * @}
 */


/**
 * @defgroup defines_power_management_configuration Power Management Configuration
 *
 * @test (ID CONF_POWER_MANAGEMENT_T0) (SEV 1) Check that the satellite switches to low power mode when its voltage goes below BATTERY_VOLTAGE_LIMIT.
 * @test (ID CONF_POWER_MANAGEMENT_T1) (SEV 2) Check that the satellite sends a morse beacon transmission when it switches to Low Power Mode.
 * @test (ID CONF_POWER_MANAGEMENT_T2) (SEV 1) Check that the battery stops charging when the temperature goes below this threshold, and starts charging again when it is not.
 * @test (ID CONF_POWER_MANAGEMENT_T3) (SEV 1) Check that the watchdog is signalled every WATCHDOG_LOOP_HEARTBEAT_PERIOD.
 * @test (ID CONF_POWER_MANAGEMENT_T4) (SEV 1) Check that the satellite sleeping times using the SLEEP_LENGTH_CONSTANT is suitable to account for the LowPower libraries overhead.
 * @test (ID CONF_POWER_MANAGEMENT_T5) (SEV 1) Check that the satellite does not deploy after DEPLOYMENT_ATTEMPS has reached.
 * @test (ID CONF_POWER_MANAGEMENT_T6) (SEV 1) Check that the satellite waits for this amount of time before the deploy sequence starts, this is for jettison.
 * @test (ID CONF_POWER_MANAGEMENT_T7) (SEV 5) Check that each debug print waits DEPLOYMENT_DEBUG_SAMPLE_PERIOD amount of time between each print.
 *
 * @todo Julian -> Set appropriate BATTERY_VOLTAGE_LIMIT and BATTERY_CW_BEEP_VOLTAGE_LIMIT
 *
 * @{
 */
#define BATTERY_VOLTAGE_LIMIT                           3.8f        /*!< Battery voltage limit to enable low power mode (V). */
#define BATTERY_CW_BEEP_VOLTAGE_LIMIT                   3.8f        /*!< Battery voltage limit to switch into morse beep (V). */
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
 *
 * @test (ID CONF_POWER_CONF_T0) (SEV 1) Check that the low power mode works.
 * @test (ID CONF_POWER_CONF_T1) (SEV 1) Check that the low power mode can be disabled using LOW_POWER_MODE_ENABLED.
 * @test (ID CONF_POWER_CONF_T3) (SEV 1) Check that the MPPT is controlled by the temperature using MPPT_TEMP_SWITCH_ENABLED.
 * @test (ID CONF_POWER_CONF_T4) (SEV 1) Check that the MPPT's temperature controller can be disabled and enabled using MPPT_KEEP_ALIVE_ENABLED.
 * @test (ID CONF_POWER_CONF_T5) (SEV 1) Check that the satellite's transmissions can be disabled and enabled using TRANSMIT_ENABLED.
 *
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
 * @test (ID CONF_INA226_CONF_T0) (SEV 1) Check that the INA226 can be connected to and gives the correct values.
 *
 * @{
 */
#define INA_ADDR                                        0x40        /*!< The I2C address of the INA226 module. */
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
 * |Deployment counter (uint8_t).|0x0000|0x0000|1|
 * |Power configuration (powerConfig_t).|0x0001|0x0001|1|
 * |First run (uint8_t).|0x0002|0x0002|1|
 * |Restart counter (uint16_t).|0x0003|0x0004|2|
 * |FSK receive window length (uint8_t).|0x0005|0x0005|1|
 * |LoRa receive window length (uint8_t).|0x0006|0x0006|1|
 * |Seconds elapsed since last reset (uint32_t).|0x0007|0x000A|4|
 * |Number of received valid LoRa frames (uint16_t).|0x000B|0x000C|2|
 * |Number of received invalid LoRa frames (uint16_t).|0x000D|0x000E|2|
 * |Number of received valid FSK frames (uint16_t).|0x000F|0x0010|2|
 * |Number of received invalid FSK frames (uint16_t).|0x0011|0x0012|2|
 * |Length of callsign (uint8_t).|0x0013|0x0013|1|
 * |Callsign (C-string, max MAX_STRING_LENGTH bytes).|0x00014|0x0034|MAX_STRING_LENGTH|
 * |Charging voltage stats (min - avg - max, 3x uint8_t).|0x0040|0x0042|3|
 * |Charging current stats (min - avg - max, 3x int16_t).|0x0043|0x0048|6|
 * |Battery voltage stats (min - avg - max, 3x uint8_t).|0x0049|0x004B|3|
 * |Solar cell A voltage stats (min - avg - max, 3x uint8_t).|0x004C|0x004E|3|
 * |Solar cell B voltage stats (min - avg - max, 3x uint8_t).|0x004F|0x0051|3|
 * |Solar cell C voltage stats (min - avg - max, 3x uint8_t).|0x0052|0x0054|3|
 * |Battery temperature stats (min - avg - max, 3x int16_t).|0x0055|0x005A|6|
 * |Board temperature stats (min - avg - max, 3x int16_t).|0x005B|0x0060|6|
 * |MCU temperature stats (min - avg - max, 3x int8_t).|0x0061|0x0063|3|
 * |Total|||72|
 *
 *
 * @test (ID CONF_EEPROM_ADDR_MAP_T0) (SEV 1) Check that EEPROM_DEPLOYMENT_COUNTER_ADDR is functional, including restarts.
 * @test (ID CONF_EEPROM_ADDR_MAP_T1) (SEV 1) Check that EEPROM_POWER_CONFIG_ADDR is functional, including restarts.
 * @test (ID CONF_EEPROM_ADDR_MAP_T2) (SEV 1) Check that EEPROM_FIRST_RUN_ADDR is functional, including restarts.
 * @test (ID CONF_EEPROM_ADDR_MAP_T3) (SEV 1) Check that EEPROM_RESTART_COUNTER_ADDR is functional, including restarts.
 * @test (ID CONF_EEPROM_ADDR_MAP_T4) (SEV 1) Check that EEPROM_CALLSIGN_LEN_ADDR is functional, including restarts.
 * @test (ID CONF_EEPROM_ADDR_MAP_T5) (SEV 1) Check that EEPROM_CALLSIGN_ADDR is functional, including restarts.
 *
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
#define EEPROM_FSK_RECEIVE_LEN_ADDR                     0x0005

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0006|0x0006|
 */
#define EEPROM_LORA_RECEIVE_LEN_ADDR                    0x0006

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0007|0x000A|
 */
#define EEPROM_UPTIME_COUNTER_ADDR                      0x0007

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x000B|0x000C|
 */
#define EEPROM_LORA_VALID_COUNTER_ADDR                  0x000B

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x000D|0x000E|
 */
#define EEPROM_LORA_INVALID_COUNTER_ADDR                0x000D

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x000F|0x0010|
 */
#define EEPROM_FSK_VALID_COUNTER_ADDR                   0x000F

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0011|0x0012|
 */
#define EEPROM_FSK_INVALID_COUNTER_ADDR                 0x0011

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x00013|0x00013|
 */
#define EEPROM_CALLSIGN_LEN_ADDR                        0x0013

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0014|0x0024|
 */
#define EEPROM_CALLSIGN_ADDR                            0x0014

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0040|0x0042|
 */
#define EEPROM_CHARGING_VOLTAGE_STATS_ADDR              0x0040

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0043|0x0048|
 */
#define EEPROM_CHARGING_CURRENT_STATS_ADDR              0x0043

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0049|0x004B|
 */
#define EEPROM_BATTERY_VOLTAGE_STATS_ADDR               0x0049

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x004C|0x004E|
 */
#define EEPROM_CELL_A_VOLTAGE_STATS_ADDR                0x004C

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x004F|0x0051|
 */
#define EEPROM_CELL_B_VOLTAGE_STATS_ADDR                0x004F

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0052|0x0054|
 */
#define EEPROM_CELL_C_VOLTAGE_STATS_ADDR                0x0052

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0055|0x005A|
 */
#define EEPROM_BATTERY_TEMP_STATS_ADDR                  0x0055

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x005B|0x0060|
 */
#define EEPROM_BOARD_TEMP_STATS_ADDR                    0x005B

/**
 * @brief
 * |Start Address|End Address|
 * |--|--|
 * |0x0061|0x0063|
 */
#define EEPROM_MCU_TEMP_STATS_ADDR                      0x0061

/**
 * @}
 */


/**
 * @defgroup defines_eeprom_variables EEPROM Variables
 *
 * @test (ID CONF_EEPROM_VAR_T0) (SEV 1) Check that the EEPROM_RESET_VALUE is suitable.
 * @test (ID CONF_EEPROM_VAR_T1) (SEV 1) Check that the EEPROM_FIRST_RUN is suitable.
 * @test (ID CONF_EEPROM_VAR_T3) (SEV 1) Check that the EEPROM_CONSECUTIVE_RUN is suitable.
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
 * @test (ID CONF_PIN_MAP_T0) (SEV 1) Check that solar panel A voltage can be read from ANALOG_IN_SOLAR_A_VOLTAGE_PIN.
 * @test (ID CONF_PIN_MAP_T1) (SEV 1) Check that solar panel B voltage can be read from ANALOG_IN_SOLAR_B_VOLTAGE_PIN.
 * @test (ID CONF_PIN_MAP_T2) (SEV 1) Check that solar panel C voltage can be read from ANALOG_IN_SOLAR_C_VOLTAGE_PIN.
 * @test (ID CONF_PIN_MAP_T3) (SEV 1) Check that the random seed analog pin is suitable from ANALOG_IN_RANDOM_SEED.
 * @test (ID CONF_PIN_MAP_T4) (SEV 1) Check that the MPPT circuit is controlled correctly using DIGITAL_OUT_MPPT_PIN.
 * @test (ID CONF_PIN_MAP_T5) (SEV 1) Check that the deployment hardware deploys when DIGITAL_OUT_MOSFET_1 and DIGITAL_OUT_MOSFET_2 are brought high.
 * @test (ID CONF_PIN_MAP_T6) (SEV 1) Check that the radio can be communicated with using pins RADIO_NSS, RADIO_DIO1, RADIO_BUSY and RADIO_NRST.
 *
 * @{
 */
#define ANALOG_IN_SOLAR_A_VOLTAGE_PIN                   A0          /*!< PC0 */
#define ANALOG_IN_SOLAR_B_VOLTAGE_PIN                   A7          /*!< ADC7 */
#define ANALOG_IN_SOLAR_C_VOLTAGE_PIN                   A2          /*!< PC2 */
#define ANALOG_IN_RANDOM_SEED                           A6          /*!< ADC6; used as source for randomSeed(), should be left floating */
#define DIGITAL_OUT_MPPT_PIN                            5//10          /*!< PB2 */
#define DIGITAL_OUT_MOSFET_1                            9           /*!< PB1 */
#define DIGITAL_OUT_MOSFET_2                            8           /*!< PB0 */
#define DIGITAL_OUT_WATCHDOG_HEARTBEAT                  4           /*!< PD4 */
#define RADIO_NSS                                       7           /*!< PD7 */
#define RADIO_DIO1                                      2           /*!< PD2 */
#define RADIO_BUSY                                      6           /*!< PD6 */
#define RADIO_NRST                                      RADIOLIB_NC /*!< Not connected*/
/**
 * @}
 */

/**
 * @defgroup defines_tmp100_configuration TMP100 Temperature Sensor Configuration
 *
 * @test (ID CONF_TMP100_T0) (SEV 1) Check that the TMP100 sensor returns the correct value (given the resolution) from the Wire connection.
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
 * @test (ID CONF_MCU_TEMP_T0) (SEV 1) Check that the MCU_TEMP_OFFSET functions correctly.
 * @test (ID CONF_MCU_TEMP_T1) (SEV 1) Check that the MCU_TEMP_COEFFICIENT functions correctly.
 *
 * @{
 */
#define MCU_TEMP_OFFSET                                 324.31      /*!< This value is used to convert the sensors temperature to the real temperature. \n t = (raw - MCU_TEMP_OFFSET) / MCU_TEMP_COEFFICIENT */
#define MCU_TEMP_COEFFICIENT                            1.22        /*!< Empirical constant */
/**
 * @}
 */

/**
 * @defgroup defines_radio_common_configuraiton  Common Radio Configuration
 *
 * @test (ID CONF_RADIO_T0) (SEV 1) Check that the SYNC_WORD is compatable with all radios and is suitable.
 * @test (ID CONF_RADIO_T1) (SEV 1) Check that the TXC0_VOLTAGE value is suitable.
 * @test (ID CONF_RADIO_T2) (SEV 1) Check that the LOW_POWER_LEVEL is suitable.
 * @test (ID CONF_RADIO_T3) (SEV 1) Check that the MAX_NUMBER_OF_BLOCKS works.
 * @test (ID CONF_RADIO_T4) (SEV 1) Check that the LORA_RECEIVE_WINDOW_LENGTH works.
 * @test (ID CONF_RADIO_T5) (SEV 1) Check that the FSK_RECEIVE_WINDOW_LENGTH works.
 * @test (ID CONF_RADIO_T6) (SEV 1) Check that the RESPONSE_DELAY is suitable and works.
 *
 * @{
 */
#define SYNC_WORD                                       0x12        /*!< Ensure this sync word is compatable with all devices. */
#define TCXO_VOLTAGE                                    1.6         /*!< Sets the radio's TCX0 voltage. (V) */
#define MAX_NUM_OF_BLOCKS                               3           /*!< maximum number of AES128 blocks that will be accepted */
#define LORA_RECEIVE_WINDOW_LENGTH                      40          /*!< How long to listen out for LoRa transmissions for (s) */
#define FSK_RECEIVE_WINDOW_LENGTH                       20          /*!< How long to listen out for FSK transmissions for (s) */
#define RESPONSE_DELAY                                  600         /*!< How long to wait for before responding/processing a transmission (ms) */
#define WHITENING_INITIAL                               0x1FF       /*!< Whitening LFSR initial value, to ensure SX127x compatibility */
/**
 * @}
 */

/**
 * @defgroup defines_radio_lora_configuration  LoRa Radio Configuration
 *
 * @todo Julian -> double check these values please.
 * @test Test that we can receive LoRa transmissions from the satellite with these default parameters
 *
 * @brief
 * |Description|Value|Units|
 * |--|--|--|
 * |Carrier Frequency.|436.7|MHz|
 * |Bandwidth.|125.0|KHz dual sideband|
 * |Spreading Factor.|11|N/A|
 * |Spreading Factor Alternate.|10|N/A|
 * |Coding rate.|8 (4/8 Extended Hamming)|N/A|
 * |Output Power.|20|dBm|
 * |Current limit.|160.0|mA|
 *
 * @test (ID CONF_LORA_RADIO_T0) (SEV 1) Check that the radio transmits lora at LORA_CARRIER_FREQUENCY.
 * @test (ID CONF_LORA_RADIO_T1) (SEV 1) Check that the radio transmits at LORA_BANDWIDTH.
 * @test (ID CONF_LORA_RADIO_T2) (SEV 1) Check that the radio is transmitting at LORA_SPREADING_FACTOR.
 * @test (ID CONF_LORA_RADIO_T3) (SEV 1) Check that the radio can/is transmitting at LORA_SPREADING_FACTOR_ALT.
 * @test (ID CONF_LORA_RADIO_T4) (SEV 1) Check that the radio is transmitting at LORA_CODING_RATE.
 * @test (ID CONF_LORA_RADIO_T5) (SEV 1) Check that the radio is transmitting at LORA_OUTPUT_POWER.
 * @test (ID CONF_LORA_RADIO_T6) (SEV 1) Check that the radio draws no more than 160.0mA.
 *
 * @{
 */
#define LORA_CARRIER_FREQUENCY                          436.7       /*!< MHz */
#define LORA_BANDWIDTH                                  125.0       /*!< kHz dual sideband */
#define LORA_SPREADING_FACTOR                           11
#define LORA_SPREADING_FACTOR_ALT                       10
#define LORA_CODING_RATE                                8           /*!< 4/8, Extended Hamming */
#define LORA_OUTPUT_POWER                               20          /*!< dBm */
#define LORA_CURRENT_LIMIT                              140.0       /*!< mA */

/**
 * @defgroup defines_radio_non_ism_band_fsk_configuraiton  FSK Radio Configuration
 *
 * @todo check FSK_RX_BANDWIDTH value
 *
 * @brief
 * |Description|Value|Units|
 * |--|--|--|
 * |Carrier Frequency.|436.7|MHz|
 * |Bit Rate.|9.6|Kbps|
 * |Frequency Deviation.|5.0|KHz single-sideband|
 * |RX Bandwidth.|19.5|KHz single-sideband|
 * |Output Power.|20|dBm|
 * |Preamble Length.|16|bits|
 * |Data Shaping.|0.5|GFSK filter BT product|
 * |Current Limit.|160.0|mA|
 *
 * @test (ID CONF_FSK_RADIO_T0) (SEV 1) Check that the radio functions at FSK_CARRIER_FREQUENCY.
 * @test (ID CONF_FSK_RADIO_T1) (SEV 1) Check that the radio functions with bit rate of FSK_BIT_RATE.
 * @test (ID CONF_FSK_RADIO_T2) (SEV 1) Check that the radio functions with a frequency deviation of FSK_FREQUENCY_DEVIATION.
 * @test (ID CONF_FSK_RADIO_T3) (SEV 1) Check that the radio receives FSK messages at FSK_RX_BANDWIDTH.
 * @test (ID CONF_FSK_RADIO_T4) (SEV 1) Check that the radio outputs at FSK_OUTPUT_POWER.
 * @test (ID CONF_FSK_RADIO_T5) (SEV 1) Check that the radio preamble is FSK_PREAMBLE_LENGTH.
 * @test (ID CONF_FSK_RADIO_T6) (SEV 1) Check that the data shaping is FSK_DATA_SHAPING.
 * @test (ID CONF_FSK_RADIO_T7) (SEV 1) Check that the maximum drawn current is no more than FSK_CURRENT_LIMIT.
 *
 * @{
 */
#define FSK_CARRIER_FREQUENCY                           436.7       /*!< MHz */
#define FSK_BIT_RATE                                    9.6         /*!< kbps nominal */
#define FSK_FREQUENCY_DEVIATION                         5.0         /*!< kHz single-sideband */
#define FSK_RX_BANDWIDTH                                39.0        /*!< kHz single-sideband */
#define FSK_OUTPUT_POWER                                20          /*!< dBm */
#define FSK_PREAMBLE_LENGTH                             16          /*!< bits */
#define FSK_DATA_SHAPING                                0.5         /*!< GFSK filter BT product */
#define FSK_CURRENT_LIMIT                               140.0       /*!< mA */
/**
 * @}
 */


/**
 * @defgroup defines_radio_morse_cw_configuration  Morse/CW Radio Configuration
 *
 * @test (ID CONF_MORSE_CW_T0) (SEV 1) Check that the number of beeps given by the radio in low power mode is NUM_CW_BEEPS.
 * @test (ID CONF_MORSE_CW_T1) (SEV 1) Check that the morse starts a signal with MORSE_PREAMBLE_LENGTH.
 * @test (ID CONF_MORSE_CW_T2) (SEV 1) Check that the words per minute of the morse transmissions is MORSE_SPEED.
 *
 * @{
 */
#define NUM_CW_BEEPS                                    3           /*!< number of CW sync beeps in low power mode */
#define MORSE_PREAMBLE_LENGTH                           3           /*!< number of start signal repetitions */
#define MORSE_SPEED                                     20          /*!< words per minute */
#define MORSE_BATTERY_MIN                               3.2         /*!< minimum voltage value that can be send via Morse (corresponds to 'A'), volts*/
#define MORSE_BATTERY_STEP                              0.05        /*!< voltage step in Morse, volts*/
/**
 * @}
 */

/**
 * @defgroup defines_radio_modem_configuration Modem Identifiers
 *
 * @test (ID CONF_MODEM_T0) Check that MODEM_LORA is suitable.
 * @test (ID CONF_MODEM_T1) Check that MODEM_FSK is suitable.
 *
 * @{
 */
#define MODEM_LORA                                      'L'
#define MODEM_FSK                                       'F'
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup defines_global_variables Global Variables
 *
 * @{
 */
extern volatile bool interruptsEnabled;                             /*!< Flag to signal interrupts enabled/disabled. */
extern volatile bool dataReceived;                                  /*!< Flag to signal data was received from ISR. */
extern uint8_t currentModem;                                        /*!< Current modem configuration. */
extern uint8_t spreadingFactorMode;                                 /*!< Current spreading factor mode. */
extern uint32_t lastHeartbeat;                                      /*!< Timestamp for the watchdog. */
extern INA226 ina;                                                  /*!< INA226 object. */
extern SX1268 radio;                                                /*!< SX1268 object. */
extern MorseClient morse;                                           /*!< MorseClient object. */
extern const char* password;										                    /*!< Transmission password (AES). */
extern const uint8_t encryptionKey[];								                /*!< Encryption key (AES). */
/**
 * @}
 */

/**
 * @brief This function is called at the very beginning of the satellite's startup to configure each pin.
 *
 */
void Configuration_Setup_Pins();
/**
 * @}
 */

/**
 * @}
 */

#endif
