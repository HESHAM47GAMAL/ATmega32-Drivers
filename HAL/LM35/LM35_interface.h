 /******************************************************************************
 *
 * Module: LM35 Temperature Sensor
 *
 * File Name: LM35_interface.h
 *
 * Description:  Header contain function prototype to be used 
 * 
 * Author: Hesham Shehata
 *
 *******************************************************************************/

// Gard file
#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"

/**************************                   Definition                   **************************/
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150


/*
*   @brief : this function used to get current temperature for LM35
*   @args  : void
*   @return: temperature value 0 : 150
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Non Reentrant in case of using Interrupt
*/
uint8 LM35_GetTemperature(void);

#endif

