 /******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: Keypad_program.c
 *
 * Description: implementation for keypad 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
  
#include "Keypad_config.h"
#include "Keypad_interface.h"





/**************************                   Functions Definition                   **************************/

void Keypad_init(void)
{
    for(uint8 it = 0 ; it < KEYPAD_ROW_NUM ; it++)  // to setup all rows
    {
        #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)

        GPIO_SetPinDirection(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_ROW_ID + it , INPUT_PIN_PULLUP );

        #elif(KEYPAD_PRESSED_STATE == LOGIC_HIGH)

        GPIO_SetPinDirection(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_ROW_ID + it , INPUT_PIN );  // need external pull down

        #endif
    }
    for(uint8 it = 0 ; it < KEYPAD_COL_NUM ; it++)
    {
        GPIO_SetPinDirection(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + it , OUTPUT_PIN );
        #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)
            GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + it , LOGIC_HIGH ); // set all columns to High
        #elif  (KEYPAD_PRESSED_STATE == LOGIC_HIGH)
            GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + it , LOGIC_LOW ); // set all columns to low
        #endif
    }
}


uint8 Keypad_GetPressedKey(void)
{
    for(uint8 it = 0 ; it < KEYPAD_COL_NUM ; it++)
    {
        // set  one column with value want to read to loop in rows to read which key from this column pressed
        #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)
            GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + it , LOGIC_HIGH ); // set all columns to High
        #elif  (KEYPAD_PRESSED_STATE == LOGIC_HIGH)
            GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + it , LOGIC_LOW ); // set all columns to low
        #endif
    }
    
    while(1)
    {
        uint8 col , row, pressed_key;
        for(col = 0 ; col < KEYPAD_COL_NUM ; col++)
        {
            // set  one column with value want to read to loop in rows to read which key from this column pressed
            #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)
                GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + col , LOGIC_LOW ); // set one of columns to low
            #elif  (KEYPAD_PRESSED_STATE == LOGIC_HIGH)
                GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + col , LOGIC_HIGH ); // set one of columns to high
            #endif

            for(row = 0 ; row < KEYPAD_ROW_NUM ; row++)
            {
                if(GPIO_ReadPin(PORT_FOR_KEYPAD,KEYPAD_FIRST_PIN_ROW_ID + row) == KEYPAD_PRESSED_STATE)
                {
                    #if(KEYPAD_COL_NUM == 3)
                        pressed_key = Keypad_4X3_AdjustKeyNumber((row*KEYPAD_COL_NUM)+col+1);
                    #elif (KEYPAD_COL_NUM == 4)
                        pressed_key = Keypad_4X4_AdjustKeyNumber((row*KEYPAD_COL_NUM)+col+1);
                    #endif
                    #if(WAIT_BEFORE_RETURN_PRESSED_KEY ==  TRUE)
                        while(GPIO_ReadPin(PORT_FOR_KEYPAD,KEYPAD_FIRST_PIN_ROW_ID + row) == KEYPAD_PRESSED_STATE); //wait until pressed key released
                    #endif

                    return pressed_key ;
                   
                }         //          |
            }             //          |                
                          //          |     I mean this step
                          //          |  
                          //          \/            
            // retrive change happen to make same thing to next column
            #if (KEYPAD_PRESSED_STATE == LOGIC_LOW)
                GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + col , LOGIC_HIGH ); // set all columns to High
            #elif  (KEYPAD_PRESSED_STATE == LOGIC_HIGH)
                GPIO_WritePin(PORT_FOR_KEYPAD , KEYPAD_FIRST_PIN_COL_ID + col , LOGIC_LOW ); // set all columns to low
            #endif

        }
    }

}



