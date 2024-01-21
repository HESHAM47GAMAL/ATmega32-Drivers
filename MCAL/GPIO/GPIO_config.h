 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO_config.h
 *
 * Description: Header to configure pins for all ports
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef GPIO_CONFIG_H_
#define GPIO_CONFIG_H_

/**************************                   INCLUDES                   **************************/
#include "GPIO_interface.h"


/**************************                   Definitions macro                   **************************/
#define Configuration_NUM 				2


// Here write all configuration you want for pins

GPIO_PORT_PIN_config GPIO_configParam [Configuration_NUM] = {

		{PORTA_ID , PINS_ALL , OUTPUT_PORT}, //0
		{PORTC_ID , PIN0_ID , OUTPUT_PIN} //1



};


#endif
