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


/**************************                   Macros like function   & Function Declare                **************************/
#if(KEYPAD_COL_NUM == 3)

/*
*   @brief : this function used map pressed button to value of button for keypad matrex size    4*3
*   @args  : key number that pressed
*   @return: value of key pressed after mapping
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static uint8 Keypad_4X3_AdjustKeyNumber(uint8 Button_Number); // static that no another module will use it 

#elif(KEYPAD_COL_NUM == 4)

/*
*   @brief : this function used map pressed button to value of button for keypad matrex size    4*4
*   @args  : key number that pressed
*   @return: value of key pressed after mapping
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
static uint8 Keypad_4X4_AdjustKeyNumber(uint8 Button_Number); // static that no another module will use it 

#endif


uint8 Keypad_GetPressedKey(void)
{
    
}
