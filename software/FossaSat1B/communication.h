#ifndef COMMUNICATION_H_INCLUDED
#define COMMUNICATION_H_INCLUDED

#include "FossaSat1B.h"

void Communication_Receive_Interrupt();

int16_t Communication_Set_Modem(uint8_t modem);
int16_t Communication_Set_Configuration(uint8_t* optData, uint8_t optDataLen);
int16_t Communication_Set_SpreadingFactor(uint8_t sfMode);

void Communication_Send_Morse_Beacon(float battVoltage);
void Communication_CW_Beep();

void Communication_Send_System_Info();

void Communication_Process_Packet();
void Comunication_Parse_Frame(uint8_t* frame, size_t len);
void Communication_Execute_Function(uint8_t functionId, uint8_t* optData = NULL, size_t optDataLen = 0);
int16_t Communication_Send_Response(uint8_t respId, uint8_t* optData = NULL, size_t optDataLen = 0, bool overrideModem = true);
int16_t Communication_Send_Response_Encrypted(uint8_t respId, uint8_t* optData, size_t optDataLen, bool overrideModem = true);
int16_t Communication_Transmit(uint8_t* data, uint8_t len, bool overrideModem = true);
bool Communication_Check_OptDataLen(uint8_t expected, uint8_t actual);

#endif
