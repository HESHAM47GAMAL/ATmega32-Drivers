/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ULTRASONIC_interface.h
 *
 * Description: Header file contain necessary definition
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_
/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


/**************************                   Prototypes                   **************************/

void Ultrasonic_Init(void);


void Ultrasonic_Trigger(void);

uint16 Ultrasonic_Distance(void);

void ULtrasonic_SignalProcessing(void);

#endif

