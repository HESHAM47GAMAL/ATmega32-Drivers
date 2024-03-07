 /******************************************************************************
 *
 * Module: USART
 *
 * File Name: USART_program.c
 *
 * Description: contain Implementation of USART Driver 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "SPI_private.h"
#include "SPI_interface.h"
#include "SPI_config.h"
#include "../GPIO/GPIO_interface.h"
#include "../../SERVICE/COMMON_MACROS.h"
#include "../../SERVICE/IVT.h"

/**************************                   Extern Global variable                   **************************/
extern SPI_ConfigType  SPI_ConfigTypeParam ;

/**************************                   Function Implement                   **************************/

void SPI_Init(void)
{
	/*  Set Direction of 4 wires depend on it is master or slave*/
	if(SPI_ConfigTypeParam.SPI_Mode_value == SPI_Master)
	{
		GPIO_SetPinDirection(PORTB_ID,PIN5_ID,OUTPUT_PIN);
		GPIO_SetPinDirection(PORTB_ID,PIN4_ID,OUTPUT_PIN);
		GPIO_SetPinDirection(PORTB_ID,PIN7_ID,OUTPUT_PIN);
		GPIO_SetPinDirection(PORTB_ID,PIN6_ID,INPUT_PIN);
		SET_BIT(SPCR,MSTR);/*Set mode as Master*/
	}
	else if (SPI_ConfigTypeParam.SPI_Mode_value == SPI_Slave)
	{
		GPIO_SetPinDirection(PORTB_ID,PIN5_ID,INPUT_PIN);
		GPIO_SetPinDirection(PORTB_ID,PIN4_ID,INPUT_PIN);
		GPIO_SetPinDirection(PORTB_ID,PIN7_ID,INPUT_PIN);
		GPIO_SetPinDirection(PORTB_ID,PIN6_ID,OUTPUT_PIN);
		CLEAR_BIT(SPCR,MSTR);/*set mode as slave*/
	}
	/*  Enable SPI */
	SET_BIT(SPCR,SPE);
	/*  Set data order & clock polarity and phase and SCL freq*/
	SPCR |= (SPI_ConfigTypeParam.SPI_Data_order_value << DORD) | (SPI_ConfigTypeParam.SPI_CPOL_value << CPOL) |(SPI_ConfigTypeParam.SPI_PHA_value << CPHA) | ( (SPI_ConfigTypeParam.SPI_PREscaler_value & 0x03) << SPR0) ;

	SPSR |= ( ( (SPI_ConfigTypeParam.SPI_PREscaler_value & 0x04) >> 2 ) << SPI2X) ;
}


void SPI_SendBytePolling(uint8 send_data)
{

    /*  Set value that will send if you master */
    SPDR = send_data ;
    
    /*Here I will loop until Data transmit as when transmit end this bit will High and I access this bit once after conversion */
    while(BIT_IS_CLEAR(SPSR,SPIF));

    /*  To clear this flag in polling mode should access this bit after transfer finish and access Data regester    */
    SPDR ;
}


uint8 SPI_ReceiveBytePolling(void)
{

    /*  Set value that will send if you master */


    /*Here I will loop until Data transmit as when transmit end this bit will High and I access this bit once after conversion */
    while(BIT_IS_CLEAR(SPSR,SPIF));

    /*  To clear this flag in polling mode should access this bit after transfer finish and access Data regester    */
    return SPDR ;
}


void SPI_SendStringPolling(const uint8 * str)
{
    char it =0 ;
    while(str[it] != '\0')
    {
        SPI_SendBytePolling(str[it]);
        it++;
    }
}


void SPI_ReceiveStringPolling(uint8 * str)
{
    uint8 it = 0 ;
    str[it] = SPI_ReceiveBytePolling();
    while(str[it] != '#')
    {
        it++;
        str[it] = SPI_ReceiveBytePolling();
    }
    /*  Replace # character with Null character to be able to used*/
    str[it] = '\0';
}
