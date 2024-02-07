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

/**************************                   Definition                   **************************/

/*	All of this Definiton need USART Send string function	*/
#define USART_Terminal_clear				"\033[2J"
#define USART_Terminal_Home_Position		"\033[H"
#define USART_Terminal_New_line             "\r\n"


/**************************                   Function Prototype                   **************************/


/*
*   @brief : this function used to initailize USART  with mode and speed and data bit ,..... configuration
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void USART_Init(void);

/*
*   @brief : this function used to send Data from MCU in Polling mode
*   ⚠️⛔note : AS  I use Polling Technique I will enter this function and I won't return Until Send data
*   @arg1  send_data: data that will send this variable with type short (16 bit)   as  if you will use 9 bit data
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void USART_SendBytePolling(uint16 send_data);

/*
*   @brief : this function used to receive Data  in Polling mode
*   ⚠️⛔note : AS  I use Polling Technique I will enter this function and I won't return Until receive data  --> SO if there are no MCU send data for You "Program Stuck here"
*   @args  : void
*   @return: retrun read data this variable with type short (16 bit)   as  if you will use 9 bit data
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
uint16 USART_ReceiveBytePolling(void);

/*
*   @brief : this function used to send muliple data byte 
*   @arg1  send_data: start address of array of data will send (Note ⚠️ this function not handle 9 bit data)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void USART_SendStringPolling(const uint8 * send_data);

/*
*   @brief : this function used to send muliple data byte 
*   @arg1  receive_data: start address of array of data will receive data (Note ⚠️ this function not handle 9 bit data)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void USART_ReceiveStringPolling(uint8 * receive_data);




#endif
