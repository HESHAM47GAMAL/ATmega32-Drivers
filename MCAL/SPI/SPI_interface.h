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

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "SPI_config.h"




/**************************                   Function Prototype                   **************************/

void SPI_Init(void);


uint8 SPI_SendBytePolling(uint8 send_data);

uint8 SPI_ReceiveBytePolling(void);


void SPI_SendStringPolling(const uint8 * str);


void SPI_ReceiveStringPolling(uint8 * str);



#endif
