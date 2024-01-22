 /******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: Keypad_config.h
 *
 * Description: Header to configure connection of keypad and size of it
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

/**************************                   INCLUDES                   **************************/
#include <../../MCAL/GPIO/GPIO_interface.h>


//                                          |----> some time not exist
//                                          |
//                 -           c0  c1  c2  c3
//                |      r0   |--------------|
// input pin      |      r1      output pin
//                |      r2
//                |      r3
//                 - 

/**************************                   Definitions macro                   **************************/

#define KEYPAD_ROW_NUM              4
#define KEYPAD_COL_NUM              4 


/***  Choose port that will connected to keypad***/
#define PORT_FOR_KEYPAD         PORTB_ID

/***  choose first pin from cols lines of keypad will connect to MCU***/
#define KEYPAD_FIRST_PIN_ROW_ID         PIN0_ID

#define KEYPAD_FIRST_PIN_COL_ID         PIN4_ID    

/*** state that I will read in pin when press button from keypad ***/
#define KEYPAD_PRESSED_STATE            LOGIC_LOW   //(LOGIC_HIGH , LOGIC_LOW)


/*** here can control if i want to wait until pressed button release before return value ***/
#define WAIT_BEFORE_RETURN_PRESSED_KEY          TRUE  //(TRUE , FALSE)



#endif 