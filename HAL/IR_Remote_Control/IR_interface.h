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

typedef enum{
    NewPress_IR  = 1,
    StillPress_IR = 2 ,
    #if(WayDealingWithRemotePress_IR != NoResponseTakenUntilPressCatched_IR) // as this state not available in this option
        NOPress_IR = 3 
    #endif

}IR_Press_Status ;



void IR_Remote_Init(void);




uint64 IR_Remote_Receive(uint8 * ProtocalType , uint8 * pressState);




#endif