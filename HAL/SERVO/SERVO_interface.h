 /******************************************************************************
 *
 * Module: Servo motor
 *
 * File Name: SERVO_interface.h
 *
 * Description: Header file contain necessary definition
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"

/*
*   @brief : this function used to initailize Servo as at same time initialize Timer 1 
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Servo_Init();

/*
*   @brief : this function used to control rotate angel of servo motor connected to OC1A
* ⛔Note : keep in mind that in Timer1_config.c need to set CO_used_pin_value (argument 4 in struct) to OC1A_pin or OC1A_B_pin 
*   @arg1 Angle_value : rotate angle (0:180)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Servo_Angle_A(uint8 Angle_value);

/*
*   @brief : this function used to control rotate angel of servo motor connected to OC1B
* ⛔Note : keep in mind that in Timer1_config.c need to set CO_used_pin_value (argument 4 in struct) to OC1B_pin or OC1A_B_pin 
*   @arg1 Angle_value : rotate angle (0:180)
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void Servo_Angle_B(uint8 Angle_value);


//As F_cpu = 8MHZ and Servo frequency required = 50HZ
//F_pwm = F_clk / (2*N * ( TOP_value))
//edit equation  (2*N * (TOP_value)) = F_clk / F_pwm = (8* 10^6) / 50 = 160 *10^3
//So I want try way to get prepor frequency for Servo so I will use Prescaler make me able to get suitable value for  (TOP_value)= ICR
//(2 * N * ( TOP_value)) =  160 *10^3
//if use prescaler 64 So (TOP_value) = 1250
//So Top value = 1250 that will assigned to ICR1


/***          From Data Sheet but can't get 0 OR 180 degree              ***/
//in this hard case 🥲 tick = prescaler / F_CPU =(2* 64) / (8*10^6) = 8us‍
//Servo need frequency = 50HZ and need Dury cycle time = 1 : 2 ms 🙆‍♂️
//		|
//		|
//		|
//		\/
//	OCR1 value = 62.5	: 125
//	to get 		 1ms	: 2ms
//  Angle 		 -90	  90


/****       So After some tries get that   in Real World ****/
//⛔🙆‍♂️ value of OCR1 will change

#endif