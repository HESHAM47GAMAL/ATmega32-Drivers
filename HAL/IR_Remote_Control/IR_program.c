 /******************************************************************************
 *
 * Module: Infrared Remote Control
 *
 * File Name: IR_program.c
 *
 * Description: implementation for Infrared Remote Control 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "IR_config.h"
#include "IR_interface.h"

#include "../../MCAL/TIMER1/TIMER1_interface.h"
#include "../../MCAL/TIMER1/TIMER1_private.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../SERVICE/COMMON_MACROS.h"
#include "../../SERVICE/STD_TYPES.h"
#include "../LCD/LCD_interface.h"



uint64 last_Code_Value = 0 ;



void IR_Remote_Analysis(uint16 * arr)
{

    uint16 i = 0 ;

    #if(WayDealingWithRemotePress_IR == NoResponseTakenUntilPressCatched_IR)

        /*  ⚠️⚠️⚠️⚠️🙆‍♂️🙆‍♂️🙆‍♂️  You are Stuck here until catch low in this pin  */
        /* As start of NEC remote frame is logic 1 and when I receive it , it will be logic 0  so will wait until catch 0  */
        while(GPIO_ReadPin(Infrared_Remote_PORT,Infrared_Remote_PIN) == LOGIC_HIGH);

    #elif(WayDealingWithRemotePress_IR == TakeResponseEvenNoPressCatched_IR)

        Timer1_UpdateValue(0);
        while( (GPIO_ReadPin(Infrared_Remote_PORT,Infrared_Remote_PIN) == LOGIC_HIGH) && (arr[i] < 65535) )
        {
            Timer1_Read_Timer_16bitValue(arr[i]);
        };

    #endif

    do
    {
        /*  Intialize timer with value = 3 as I take some time in before while */
        Timer1_UpdateValue(3);
        do 
        {
            Timer1_Read_Timer_16bitValue(arr[i]);
        }
        /*  purpose of this check that make me stop when I wait time >= 20ms or >= 20000 , as I told you need to make timer tick = 1us*/
        while((GPIO_ReadPin(Infrared_Remote_PORT,Infrared_Remote_PIN) == LOGIC_LOW)  && (arr[i] < 20000) );

        /*  Intialize timer with value = 3 as I take some time in before while */
        Timer1_UpdateValue(3);
        do
        {
            Timer1_Read_Timer_16bitValue(arr[i + 1]);
        }
        while((GPIO_ReadPin(Infrared_Remote_PORT,Infrared_Remote_PIN) == LOGIC_HIGH)  && (arr[i+1] < 20000) );

        i += 2;
    }
    while((arr[i-1] < 20000) && (arr[i-2] < 20000) );


}





/**************************                   Functions Definition                   **************************/

void IR_Remote_Init(void)
{
    #if(IR_STATE == IR_Transmitter_State)
        /*  Set pin as output pin to send data as there writing logic 1 or 0 to IR transmitter*/
        GPIO_SetPinDirection(Infrared_Remote_PORT,Infrared_Remote_PIN,OUTPUT_PIN);
    #elif(IR_STATE == IR_Receiver_State)
        /*  Set pin as input pin to receive signal from remote and give to MCU  */
        GPIO_SetPinDirection(Infrared_Remote_PORT,Infrared_Remote_PIN,INPUT_PIN);
    #endif
    /*  🔔🔔🔔🔔🔔👀👀👀Set timer 1 in normal mode to work as timer to tell me time for each bit  So go to driver and 
    do this configuration in Config.h and config.c and close interrupt  
    don't forget to make 1 tick count for timer = 1us to make calculation easy */
    
    /*  this only apply configuation that setted  in config.h and config.c*/
    Timer1_Init();

    /*  Provide clock for timer 1 peripheral as y default I don't provide clock in initialization  */
    Timer1_ProvideClock();

}



uint64 IR_Remote_Receive(uint8 * ProtocalType , uint8 * pressState)
{
    uint16 Array_bits [128];
    /*  Create variable to work as index  */
    uint16 i = 3; /*    [i=0] -> this for time of logic high  , [i=1] -> this for time of logic low , [i=2] -> this has constant time for logic 1 or 0 for sended signal 
    [i=3] -> this carry time that tell me if this signal 1 (take time 2.25ms) or  0(take time 1.125ms)  */
    volatile uint64 Code_Variale = 0; 

    IR_Remote_Analysis(Array_bits);

    /*  This check that if signal is NEC protoccol and user curently pressed on button*/
    if( ((Array_bits[0] < 10000) && (Array_bits[0] > 8400)) && ((Array_bits[1] < 4700) && (Array_bits[1] > 3800)) )
    {
        /*  so this is NEC protocol as start with 9ms high then 4.5ms low   */
        ProtocalType[0]= 'N' ;
        ProtocalType[1]= 'E' ;
        ProtocalType[2]= 'C' ;
        ProtocalType[3]= '\0' ;

        while(i <= 128)
        {
            if( (Array_bits[i] > 100) && (Array_bits[i] < 700) )
            {
                Code_Variale = (Code_Variale << 1);
            }
            else if ( (Array_bits[i] > 1200) && (Array_bits[i] < 1800) )
            {
                Code_Variale = ( (Code_Variale << 1) | (1) );
            }
            else 
            {
                break;
            }

            i += 2 ;
        }

		if(Code_Variale==0)
		{
			Code_Variale = last_Code_Value;
            LCD_MoveCursor(1,0);
            LCD_DisplayString("if_1");
		}
		else
		{
			last_Code_Value = Code_Variale;
            *pressState = NewPress_IR ;
		}

    }

    /*  This check that if signal is NEC protoccol and user still pressed on button  so return last press value  */
    else if( ((Array_bits[0] < 10000) && (Array_bits[0] > 8400)) && ((Array_bits[1] < 2600) && (Array_bits[1] > 1600)) )
    {
        Code_Variale = last_Code_Value;
        *pressState = StillPress_IR ;

    }

    else if(((Array_bits[0]<4000)&&(Array_bits[0]>3000))&&((Array_bits[1]<2000)&&(Array_bits[1]>1000)))
	{
		ProtocalType[0]='P';
		ProtocalType[1]='A';
		ProtocalType[2]='N';
		ProtocalType[3]='A';
		ProtocalType[4]='S';
		ProtocalType[5]='O';
		ProtocalType[6]='N';
		ProtocalType[7]='I';
		ProtocalType[8]='C';
		ProtocalType[9]='\0';
		while (i<=128)
		{
			
			if ((Array_bits[i]>30)&&(Array_bits[i]<630))
			{
				Code_Variale=(Code_Variale<<1);
				
			}
			else if ((Array_bits[i]>900)&&(Array_bits[i]<1500))
			{
				Code_Variale=((Code_Variale<<1)|(1));
				
			}
			else
			{
				break;
			}
			
			i=i+2;
			
		}
		
	}
	else
	{
		Code_Variale = 0;
        #if(WayDealingWithRemotePress_IR != NoResponseTakenUntilPressCatched_IR) // as this state not available in this option
            *pressState = NOPress_IR ;
        #endif
	}
	

    return Code_Variale ;
}
