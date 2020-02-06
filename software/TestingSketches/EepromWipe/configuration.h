#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include "FossaSat1B.h"

/**
 * @defgroup defines_string_memory_limits String Limits
 * @{
 */
#define MAX_STRING_LENGTH                               32      /*!< String length limit (bytes). */
#define MAX_OPT_DATA_LENGTH                             128     /*!< Optional data length limit (bytes). */
#define MAX_RADIO_BUFFER_LENGTH                         (MAX_STRING_LENGTH + 2 + MAX_OPT_DATA_LENGTH)     /*!< Radio buffer length limit. */

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
#define RESPONSE_DELAY                                  1000        /*!< How long to wait for before responding/processing a transmission (ms) */
/**
 * @}
 */

#endif
