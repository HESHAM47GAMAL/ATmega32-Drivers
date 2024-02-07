 /******************************************************************************
 *
 * Module: USART
 *
 * File Name: USART_config.h
 *
 * Description: Header to configure USART
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/



#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


#define USART_Asynchronous_Normal_Speed                     0   //  Option 1 -----------|
#define USART_Asynchronous_Double_Speed                     1   //  Option 1 -----------|
#define USART_Synchronous                                   2   //  Option 1 -----------|
#define USART_Multi_processor                              3   //  Option 1 -----------| (Actually I don't know how to use or work 😂 and Not Handled⚠️ )
//                                                                                      | Here
#define USART_CURRENT_MODE          USART_Asynchronous_Normal_Speed //<-----------------|


#define Enable_Interrupt_USART                1        //  Option 1 -----------|
#define Disable_Interrupt_USART               0        //  Option 2 -----------|
//                                                                             |
#define INTERUPT_STATE_USART          Disable_Interrupt_USART    //<------------|

typedef enum 
{
    USART_5_bit ,
    USART_6_bit ,
    USART_7_bit ,
    USART_8_bit ,
    USART_9_bit = 7 

}USART_DATA_Bit ;

typedef enum 
{
    USART_No_Parity ,
    USART_Even_Parity = 2 ,
    USART_Odd_Parity 
}USART_Parity;

typedef enum 
{
    USART_1_STOP ,
    USART_2_STOP
}USART_NUM_STOP_Bit ;

#if ((USART_CURRENT_MODE == USART_Asynchronous_Normal_Speed) || (USART_CURRENT_MODE == USART_Asynchronous_Double_Speed))
typedef enum 
{
    USART_Transmit_Only ,
    USART_Receive_Only ,
    USART_Transmit_Receive
}USART_COM_OPTION ;

typedef struct 
{
    USART_DATA_Bit USART_DATA_Bit_value ;
    USART_Parity USART_Parity_value ;
    USART_NUM_STOP_Bit USART_NUM_STOP_Bit_value ;
    USART_COM_OPTION USART_COM_OPTION_value ;
    uint16 UBRR_value ;
}USART_ConfigType ;

#elif(USART_CURRENT_MODE == USART_Synchronous)

typedef enum{
    USART_MASTER ,
    USART_SLAVE 
}USART_Synchronous_MS;

typdef enum 
{
    USART_TX_RISING_RX_FALLING ,
    USART_TX_FALLING_RX_RISING
}USART_CLK_Polarity ;



#endif



#endif