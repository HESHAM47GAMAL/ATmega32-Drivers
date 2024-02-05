 /******************************************************************************
 *
 * Module: Servo motor
 *
 * File Name: SERVO_program.c
 *
 * Description: source file for implementation
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "SERVO_config.h"
#include "SERVO_interface.h"

#include "../../MCAL/TIMER1/TIMER1_interface.h"


/**************************                   Function Implementation                   **************************/

void Servo_Init()
{
    /*  Set Top value  (as I use ICR1)    */
    Timer1_PhaseCorrectPWMSetICR_Register(ICR1_value_used);
    /*  Initialize Timer 1    */
    Timer1_Init();
    Servo_Angle_A(0);
    Servo_Angle_B(0);
}

void Servo_Angle_A(uint8 Angle_value)
{
    if(Angle_value < 0 )
        Angle_value = 0;
    else if (Angle_value > 180)
        Angle_value = 180 ;
    Timer1_PhaseCorrectPWMSetOCR1A( (uint16)( 62.5 + (0.35 * Angle_value) ));
}  //                                          | 
//                                             \/
//                              this value is number of ticks needed for 1ms as servo work in range 1ms to 2ms high of signal

void Servo_Angle_B(uint8 Angle_value)
{
    if(Angle_value < 0 )
        Angle_value = 0;
    else if (Angle_value > 180)
        Angle_value = 180 ;
    Timer1_PhaseCorrectPWMSetOCR1B( (uint16)( 62.5 + (0.35 * Angle_value) ));
}


