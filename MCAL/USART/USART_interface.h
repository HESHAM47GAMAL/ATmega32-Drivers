 /******************************************************************************
 *
 * Module: USART
 *
 * File Name: USART_interface.h
 *
 * Description: Header contain function prototype to be used 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "USART_config.h"

void USART_Init(void);

void USART_SendBytePolling(uint16 send_data);

uint16 USART_ReceiveBytePolling(void);


void USART_SendStringPolling(const uint8 * send_data);

void USART_ReceiveStringPolling(uint8 * receive_data);

void USART_AppendTerminateChar(uint8 * send_data);


#endif