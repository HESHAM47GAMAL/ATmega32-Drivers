/******************************************************************************
 *
 * Module: Seven Segment
 *
 * File Name: SevenSegment_interface.h
 *
 * Description: Header File contain function Prototype  
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef SEVEN_SEGMENT_INTERFACE_H_
#define SEVEN_SEGMENT_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "SevenSegment_config.h"
#include "../../MCAL/GPIO/GPIO_interface.h"


#if(CONFIGURATION_OF_BCD == NO_BCD_ANODE)

#elif(CONFIGURATION_OF_BCD == NO_BCD_CATHODE)



#elif( (CONFIGURATION_OF_BCD == BCD_7448) || (CONFIGURATION_OF_BCD == BCD_7447) )

#define _7_PORT         PORTB_ID


#define _7_PIN0         PIN0_ID
#define _7_PIN1         PIN1_ID
#define _7_PIN2         PIN2_ID
#define _7_PIN3         PIN4_ID    


#endif
void _7Segment_Init(void);

void _7Segment_Value(uint8 value );



#endif