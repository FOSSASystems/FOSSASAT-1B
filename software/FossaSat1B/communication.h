#ifndef COMMUNICATION_H_INCLUDED
#define COMMUNICATION_H_INCLUDED

#include "FossaSat1B.h"

/**
 * @file communication.h
 * @brief This system is the main interface that is used to transmit message, configure the radio and process received transmissions.
 */

/**
 * @brief This function is called by the ISR when a transmission is received.
 *
 * @test (ID COMMS_H_T0) (SEV 1) Make sure this function is called when the radio receives data.
 *
 */
void Communication_Receive_Interrupt();

/**
 * @brief This function configures the radio to the given modem.
 *
 * @test (ID COMMS_H_T1) (SEV 1) Make sure the modem mode is changed with no errors.
 *
 * @param modem see @ref defines_radio_modem_configuration
 * @return int16_t The RadioLib status code for .Begin().
 */
int16_t Communication_Set_Modem(uint8_t modem);

/**
 * @brief This function sets the configuration of the radio, which is used to Radio.Begin().
 *
 * @test (ID COMMS_H_T2) (SEV 1) Make sure the modem mode is changed with no errors.
 *
 * @param optData The data which is used to configure the radio.
 * @param optDataLen The length of the byte string given.
 * @return int16_t The status code returned by the radio.Begin() function.
 */
int16_t Communication_Set_Configuration(uint8_t* optData, uint8_t optDataLen);

/**
 * @brief This function sets the spreading factor of the radio.
 *
 * @test (ID COMMS_H_T3) (SEV 1) Make sure the radio's spreading factor can be changed with no errors.
 * @test (ID COMMS_H_T4) (SEV 1) Make sure the radio's spreading factors are compatable with generic radios.
 *
 * @param sfMode See @ref defines_radio_lora_configuraiton
 * @return int16_t The status code returned by the radio.setSpreadingFactor() function.
 */
int16_t Communication_Set_SpreadingFactor(uint8_t sfMode);

/**
 * @brief This function transmits a morse beacon message.
 *
 * @test (ID COMMS_H_T5) (SEV 1) Test that the beacon message can be received properly.
 * @test (ID COMMS_H_T6) (SEV 1) Test that the beacon messages battery voltage is received ok.
 *
 * @param battVoltage The battery voltage to send via morse code.
 */
void Communication_Send_Morse_Beacon(float battVoltage);

/**
 * @brief This function transmits a continous wave "BEEP"".
 *
 * @test (ID COMMS_H_T7) (SEV 2) Test that the CW beep is received ok.
 *
 * @param len Length of the beep in ms, with 500 ms resolution
 */
void Communication_CW_Beep(uint32_t len);

/**
 * @brief This function adds frame entry to a frame.
 *
 * @test (ID COMMS_H_T8) (SEV 1) Test that the system information is received correctly.
 *
 * @param buffPtr Pointer to the frame buffer.
 * @param val Value to be added.
 * @param name Name of the parameter (debug only);
 *
 */
 template <typename T>
 void Communication_Frame_Add(uint8_t** buffPtr, T val, const char* name) {
   memcpy(*buffPtr, &val, sizeof(val));
   (*buffPtr) += sizeof(val);
   FOSSASAT_DEBUG_PRINT(name);
   FOSSASAT_DEBUG_PRINT('=');
   FOSSASAT_DEBUG_PRINTLN(val);
 }
/**
 * @brief Send the satellite's information via the configured radio settings.
 *
 * @test (ID COMMS_H_T8) (SEV 1) Test that the system information is received correctly.
 *
 */
void Communication_Send_System_Info();

/**
 * @brief This function sends acknowledge for a received frame.
 *
 * @test (ID COMMS_H_T10) (SEV 1) Test that each command/packet is processed correctly.
 *
 * @param functionId Function ID to acknowledge.
 * @param result Result of frame processing.
 */
void Communication_Acknowledge(uint8_t functionId, uint8_t result);

/**
 * @brief This function reads the contents of the radio when it receives a transmission.
 *
 * @test (ID COMMS_H_T9) (SEV 1) Test that each command/packet is processed correctly.
 *
 */
void Communication_Process_Packet();

/**
 * @brief This function parses the internal contents of the message using the FOSSA COMMS Protocol
 *
 * @test (ID COMMS_H_T10) (SEV 1) Test that each command/packet is processed correctly.
 *
 * @param frame The raw data to process.
 * @param len The length of the raw data.
 */
void Comunication_Parse_Frame(uint8_t* frame, size_t len);

/**
 * @brief This function executes the given function id provided with the given data.
 *
 * @test (ID COMMS_H_T11) (SEV 1) Test that each command is responded to with the correct function and data.
 *
 * @param functionId The function to execute.
 * @param optData  The data to give to the function.
 * @param optDataLen The length of the data that is given to the function.
 *
 */
void Communication_Execute_Function(uint8_t functionId, uint8_t* optData = NULL, size_t optDataLen = 0);

/**
 * @brief Responds to a given function id execution (internally used).
 *
 * @test (ID COMMS_H_T12) (SEV 1) Test that each response transmits correctly.
 *
 * @param respId Function ID to respond with.
 * @param optData The data to respond with.
 * @param optDataLen  The length of the data to respond with.
 * @param overrideModem  Override the modem to use default LoRa modem and settings.
 * @return int16_t The status code of the Communication_Transmit() function.
 *
 */
int16_t Communication_Send_Response(uint8_t respId, uint8_t* optData = nullptr, size_t optDataLen = 0, bool overrideModem = false);

/**
 * @brief Transmits the given data.
 *
 * @test (ID COMMS_H_T13) (SEV 1) Check that each function/command transmits correctly.
 *
 * @param data The byte array to transmit.
 * @param len The length of the byte array to transmit.
 * @param overrideModem Override the modem to use default LoRa modem and settings.
 * @return int16_t The status code of the Radio.Tranmit() function.
 */
int16_t Communication_Transmit(uint8_t* data, uint8_t len, bool overrideModem = true);

/**
 * @brief Helper functions to check two variables are equal, with debug prints.
 *
 * @test (ID COMMS_H_T14) (SEV 1) Check that this function equates correctly.
 *
 * @param expected The expected value
 * @param actual The given value.
 * @return true They are the same value.
 * @return false They are not the same value.
 */
bool Communication_Check_OptDataLen(uint8_t expected, uint8_t actual);

#endif
