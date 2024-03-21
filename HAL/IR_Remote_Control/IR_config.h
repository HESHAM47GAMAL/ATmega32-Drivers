 /******************************************************************************
 *
 * Module: Infrared Remote Control
 *
 * File Name: IR_config.h
 *
 * Description: Header to configure connection of Infrared Remote Control
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef IR_CONFIG_H_
#define IR_CONFIG_H_

/**************************                   INCLUDES                   **************************/
#include "../../MCAL/GPIO/GPIO_interface.h"

#define Infrared_Remote_PORT            PORTD_ID   

#define Infrared_Remote_PIN             PIN7_ID

#define IR_Transmitter_State           0    // option 1    -----|
#define IR_Receiver_State              1    // option 2    -----|      ----> (Not work Until Now)
                                            //                  | choose here
#define IR_STATE                        IR_Receiver_State  // <-| 


#define NoResponseTakenUntilPressCatched_IR                0          // Option 1   -----|  // work correct but your program will stuck until make Remote press
#define TakeResponseEvenNoPressCatched_IR                  1          // Option 2   -----| // ⚠️⚠️⚠️⚠️Not Work correct As sometimes when press ,this Press not catched or catched false
//                                                                                       | Choose Here 
#define WayDealingWithRemotePress_IR            NoResponseTakenUntilPressCatched_IR //<--|


#endif 