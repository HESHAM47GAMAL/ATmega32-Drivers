 /******************************************************************************
 *
 * Module: Infrared Remote Control
 *
 * File Name: IR_interface.h
 *
 * Description:  Header that contain function prototype
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef IR_INTERFACE_H_
#define IR_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "IR_config.h"


/*  This is availble state for IR Remote*/
typedef enum{
    NewPress_IR  = 1,
    StillPress_IR = 2 ,
    #if(WayDealingWithRemotePress_IR != NoResponseTakenUntilPressCatched_IR) // as this state not available in this option
        NOPress_IR = 3 
    #endif

}IR_Press_Status ;



/* This is value for each button for my own Remote control  */
typedef enum 
{
    IR_CMD_1        = 0xFFA25D ,
    IR_CMD_2        = 0xFF629D ,
    IR_CMD_3        = 0xFFE21D ,
    IR_CMD_4        = 0xFF22DD ,
    IR_CMD_5        = 0xFF02FD ,
    IR_CMD_6        = 0xFFC23D ,
    IR_CMD_7        = 0xFFE01F ,
    IR_CMD_8        = 0xFFA857 ,
    IR_CMD_9        = 0xFF906F ,
    IR_CMD_STAR     = 0xFF6897 ,
    IR_CMD_0        = 0xFF9867 ,
    IR_CMD_HASH     = 0xFFB04F ,
    IR_CMD_UP       = 0xFF18E7 ,
    IR_CMD_DOWN     = 0xFF4AB5 ,
    IR_CMD_LEFT     = 0xFF10EF ,
    IR_CMD_RIGHT    = 0xFF5AA5 ,
    IR_CMD_OK       = 0xFF38C7

}IR_Button_Value ;


/*
*   @brief : this function used to initialize Infrared Remote control by initialize pin connected to output of IR and initialize Timer 1
*   @args  : void
*   @return: void
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void IR_Remote_Init(void);



/*
*   @brief : this function used to catch signal from Remote Control 
*   ⛔⛔⛔Note that you don;t return from this function until catch signal , read more in IR_config.h
*   @arg1 ProtocalType : carry string represent protocol type (NEC or Panasonic)
*   @arg2 pressState : pointer to uint8 carry state of press as if it (new press , still press same button)
*   @return: value of signal cathced 
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
uint64 IR_Remote_Receive(uint8 * ProtocalType , uint8 * pressState);




#endif