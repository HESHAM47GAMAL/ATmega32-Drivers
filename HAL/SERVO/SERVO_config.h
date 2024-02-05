 /******************************************************************************
 *
 * Module: Servo motor
 *
 * File Name: SERVO_config.h
 *
 * Description: Header to configure connection of Servo and pins 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef SERVO_CONFIG_H_
#define SERVO_CONFIG_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


/**************************                   ⛔🙆‍♂️Need to config Timer1 config.c & config.h                   **************************/

/*  ⛔🙆‍♂️ note you will need to configure in function implement if not use prescaler 64 with F_clk = 8MHZ in phase correct mode*/
/* ⛔🙆‍♂️ choose OC1A  or OC1B or OC1A_B as which will drive signal */

#define ICR1_value_used        (uint16) 1250


// ⛔🙆‍♂️ Note  Top = value that will assigned to ICR1
// Fast PWM 
//                     F_clk
// FOC1A/B  =    ----------------------
//                 N  * (1 + TOP)



// Phase correct CO_PWM_T1
//                     F_clk
// FOC1A/B  =    ----------------------
//                 2 * N  *  TOP





#endif


