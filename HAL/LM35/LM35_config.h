 /******************************************************************************
 *
 * Module: LM35 Temperature Sensor
 *
 * File Name: LM35_config.h
 *
 * Description: Header to configure LM35
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

//Gard file
#ifndef LM35_CONFIG_H_
#define LM35_CONFIG_H_

/**************************                   INCLUDES                   **************************/

#include "../../MCAL/ADC/ADC_interface.h"

/**************************                   Definition                   **************************/

/*  Choose pin used to make analog read     */
#define LM35_PIN         ADC_Channel_2


#endif
