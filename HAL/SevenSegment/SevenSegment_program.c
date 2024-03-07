/******************************************************************************
 *
 * Module: Seven Segment
 *
 * File Name: SevenSegment_program.c
 *
 * Description: source file for implementation
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


/**************************                   INCLUDES                   **************************/
#include "SevenSegment_config.h"
#include "SevenSegment_interface.h"

#include "../../MCAL/GPIO/GPIO_interface.h"

void _7Segment_Init(void)
{
    GPIO_SetPinDirection(_7_PORT,_7_PIN0,OUTPUT_PIN);
    GPIO_SetPinDirection(_7_PORT,_7_PIN1,OUTPUT_PIN);
    GPIO_SetPinDirection(_7_PORT,_7_PIN2,OUTPUT_PIN);
    GPIO_SetPinDirection(_7_PORT,_7_PIN3,OUTPUT_PIN);
}



void _7Segment_Value(uint8 value )
{
    uint8 PORT_Value = GPIO_ReadPort(_7_PORT);
    PORT_Value = (PORT_Value& (~0x07)) | (value & 0x07);
    PORT_Value &= ~(1<<4);
    PORT_Value |= ( (value & 0x08) << 1 );
    GPIO_WritePort(_7_PORT,PORT_Value);
 
}