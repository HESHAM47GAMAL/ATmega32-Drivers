 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO_program.c
 *
 * Description: implementation for function for  GPIO
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/

#include "GPIO_private.h"
#include "GPIO_interface.h"
#include "GPIO_config.h"
#include "../../SERVICE/COMMON_MACROS.h"


/**************************                   Extern Global variable                   **************************/

// Here write all configuration you want for pins
extern GPIO_PORT_PIN_config GPIO_configParam [Configuration_NUM]  ;  // exist in GPIO_config.h


void GPIO_init(void)
{
#if (Param_Disable_All_PULLUP_resistor == Enable_PullUp_resistor)
SET_BIT(SFIOR,PUD);
#elif (Param_Disable_All_PULLUP_resistor == Disable_PullUp_resistor)
CLEAR_BIT(SFIOR,PUD);
#endif

	for(uint8 it = 0 ; it < Configuration_NUM ; it++)
	{
		if(GPIO_configParam[it].PORT_Selected >= NUM_PORT  || GPIO_configParam[it].PIN_SELECT > NUM_FOR_PINS_PER_PORT)
		{
			/* Do Nothing*/
		}
		else
		{
			switch(GPIO_configParam[it].PORT_Selected)
			{

			case PORTA_ID :
				if(GPIO_configParam[it].PIN_SELECT == PINS_ALL) // configure all port
				{
					if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PORT)
					{
						DDRA = ZEROS_WORD ; // set port input
						PORTA = ZEROS_WORD ; //disable pullup resistor

					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PORT_PULLUP)
					{
						DDRA = ZEROS_WORD ;// set port input
						PORTA = ONES_WORD ; //enable pullup resistor

					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == OUTPUT_PORT )
					{
						DDRA = ONES_WORD ;
					}
				}
				else // configure pin from port
				{
					if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PIN)
					{
						CLEAR_BIT( DDRA , GPIO_configParam[it].PIN_SELECT );
						CLEAR_BIT( PORTA , GPIO_configParam[it].PIN_SELECT );
					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PIN_PULLUP)
					{
						CLEAR_BIT( DDRA , GPIO_configParam[it].PIN_SELECT );
						SET_BIT( PORTA , GPIO_configParam[it].PIN_SELECT );
					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == OUTPUT_PIN)
					{
						SET_BIT( DDRA , GPIO_configParam[it].PIN_SELECT );
					}
				}

				break ;



			case PORTB_ID :
				if(GPIO_configParam[it].PIN_SELECT == PINS_ALL) // configure all port
				{
					if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PORT)
					{
						DDRB = ZEROS_WORD ; // set port input
						PORTB = ZEROS_WORD ; //disable pullup resistor

					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PORT_PULLUP)
					{
						DDRB = ZEROS_WORD ;// set port input
						PORTB = ONES_WORD ; //enable pullup resistor

					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == OUTPUT_PORT )
					{
						DDRB = ONES_WORD ;
					}
				}
				else // configure pin from port
				{
					if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PIN)
					{
						CLEAR_BIT( DDRB , GPIO_configParam[it].PIN_SELECT );
						CLEAR_BIT( PORTB , GPIO_configParam[it].PIN_SELECT );
					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PIN_PULLUP)
					{
						CLEAR_BIT( DDRB , GPIO_configParam[it].PIN_SELECT );
						SET_BIT( PORTB , GPIO_configParam[it].PIN_SELECT );
					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == OUTPUT_PIN)
					{
						SET_BIT( DDRB , GPIO_configParam[it].PIN_SELECT );
					}
				}

				break ;



			case PORTC_ID :
				if(GPIO_configParam[it].PIN_SELECT == PINS_ALL) // configure all port
				{
					if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PORT)
					{
						DDRC = ZEROS_WORD ; // set port input
						PORTC = ZEROS_WORD ; //disable pullup resistor

					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PORT_PULLUP)
					{
						DDRC = ZEROS_WORD ;// set port input
						PORTC = ONES_WORD ; //enable pullup resistor

					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == OUTPUT_PORT )
					{
						DDRC = ONES_WORD ;
					}
				}
				else // configure pin from port
				{
					if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PIN)
					{
						CLEAR_BIT( DDRC , GPIO_configParam[it].PIN_SELECT );
						CLEAR_BIT( PORTC , GPIO_configParam[it].PIN_SELECT );
					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PIN_PULLUP)
					{
						CLEAR_BIT( DDRC , GPIO_configParam[it].PIN_SELECT );
						SET_BIT( PORTC , GPIO_configParam[it].PIN_SELECT );
					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == OUTPUT_PIN)
					{
						SET_BIT( DDRC , GPIO_configParam[it].PIN_SELECT );
					}
				}

				break;



			case PORTD_ID :
				if(GPIO_configParam[it].PIN_SELECT == PINS_ALL) // configure all port
				{
					if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PORT)
					{
						DDRD = ZEROS_WORD ; // set port input
						PORTD = ZEROS_WORD ; //disable pullup resistor

					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PORT_PULLUP)
					{
						DDRD = ZEROS_WORD ;// set port input
						PORTD = ONES_WORD ; //enable pullup resistor

					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == OUTPUT_PORT )
					{
						DDRD = ONES_WORD ;
					}
				}
				else // configure pin from port
				{
					if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PIN)
					{
						CLEAR_BIT( DDRD , GPIO_configParam[it].PIN_SELECT );
						CLEAR_BIT( PORTD , GPIO_configParam[it].PIN_SELECT );
					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == INPUT_PIN_PULLUP)
					{
						CLEAR_BIT( DDRD , GPIO_configParam[it].PIN_SELECT );
						SET_BIT( PORTD , GPIO_configParam[it].PIN_SELECT );
					}
					else if(GPIO_configParam[it].INPUT_OUTPUT == OUTPUT_PIN)
					{
						SET_BIT( DDRD , GPIO_configParam[it].PIN_SELECT );
					}
				}
				break ;
			}
		}
	}
}



uint8 GPIO_ReadPin(uint8 PORTX , uint8 PIN )
{
    uint8 returned_value = LOGIC_LOW ;

    if(PORTX >= NUM_PORT  || PIN >= NUM_FOR_PINS_PER_PORT)
    {
        /* Do Nothing*/
    }
    else 
    {
        switch (PORTX)
        {
            case PORTA_ID :
                if( BIT_IS_SET(PINA,PIN) )
                    returned_value = LOGIC_HIGH;
                else
                    returned_value = LOGIC_LOW ;
                break ;

            case PORTB_ID :
                if( BIT_IS_SET(PINB,PIN) )
                    returned_value = LOGIC_HIGH;
                else
                    returned_value = LOGIC_LOW ;

                break ;

            case PORTC_ID :
                if( BIT_IS_SET(PINC,PIN) )
                    returned_value = LOGIC_HIGH;
                else
                    returned_value = LOGIC_LOW ;

                break ;

            case PORTD_ID :
                if( BIT_IS_SET(PIND,PIN) )
                    returned_value = LOGIC_HIGH;
                else
                    returned_value = LOGIC_LOW ;

                break ;

        }
    }

    return returned_value ;
}



void GPIO_WritePin(uint8 PORTX , uint8 PIN ,uint8 value)
{
    if(PORTX >= NUM_PORT  || PIN >= NUM_FOR_PINS_PER_PORT)
    {
        /* Do Nothing*/
    }
    else
    {
        switch(PORTX)
        {
            case PORTA_ID :
                if(value == LOGIC_HIGH)
                    SET_BIT(PORTA,PIN);
                else if(value == LOGIC_LOW)
                    CLEAR_BIT(PORTA,PIN);
                break;


            case PORTB_ID :
                if(value == LOGIC_HIGH)
                    SET_BIT(PORTB,PIN);
                else if(value == LOGIC_LOW)
                    CLEAR_BIT(PORTB,PIN);
                break;  

            case PORTC_ID :
                if(value == LOGIC_HIGH)
                    SET_BIT(PORTC,PIN);
                else if(value == LOGIC_LOW)
                    CLEAR_BIT(PORTC,PIN);
                break;

            case PORTD_ID :
                if(value == LOGIC_HIGH)
                    SET_BIT(PORTD,PIN);
                else if(value == LOGIC_LOW)
                    CLEAR_BIT(PORTD,PIN);
                break;

        }
    }
}



uint8 GPIO_ReadPort(uint8 PORTX)
{
    uint8 returned_value = 0 ;
    if(PORTX >= NUM_PORT )
    {
        /* Do Nothing  */
    }
    else
    {
        switch(PORTX)
        {
            case PORTA_ID :
                returned_value = PINA ;
                break ;
            
            case PORTB_ID :
                returned_value = PINB ;
                break ; 


            case PORTC_ID :
                returned_value = PINC ;
                break ;


            case PORTD_ID :
                returned_value = PIND ;
                break ;

        }
    }


    return returned_value ;
}



void GPIO_WritePort(uint8 PORTX  ,uint8 value)
{
    if(PORTX >= NUM_PORT )
    {
        /* Do Nothing  */
    }
    else
    {
        switch(PORTX)
        {
            case PORTA_ID :
                PORTA = value ;
                break ;

            case PORTB_ID :
                PORTB = value ;
                break ;


            case PORTC_ID :
                PORTC = value ;
                break ;

            case PORTD_ID :
                PORTD = value ;
                break ;
        }
    }
}



