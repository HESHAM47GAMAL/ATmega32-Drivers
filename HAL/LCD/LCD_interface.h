 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD_interface.h
 *
 * Description: Header file conatain necessary definition
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


/**************************                   Macros Definition                   **************************/
#define LCD_CLEAR_DISPLAY                           0x01
#define LCD_RETURN_TO_HOME_IN_SCREEN                0x02
#define LCD_DISPLAY_ON_CURSOR_ON_BLINKING_OFF       0x0E
#define LCD_DISPLAY_ON_CURSOR_ON_BLINKING_ON        0x0F
#define LCD_DISPLAY_ON_CURSOR_OFF                   0x0C
#define LCD_DISPLAY_OFF_CURSOR_NO                   0x0A
#define LCD_DISPLAY_OFF_CURSOR_OFF                  0x08
#define LCD_CURSOR_MOVE_RIGHT                       0x14
#define LCD_CURSOR_MOVE_LEFT                        0x10
#define LCD_ENTIRE_DISPLAY_RIGHT                    0x1C
#define LCD_ENTIRE_DISPLAY_LEFT                     0x18
#define LCD_2_LINE_8_BIT_5x8_DOT                    0x38
#define LCD_2_LINE_4_BIT_5x8_DOT                    0x28
#define LCD_SET_CURSOR_LOCATION                     0x80


/**************************                   Function Prototype                   **************************/

void LCD_init(void);


void LCD_SendCommand(uint8 Instruction_value);

void LCD_DisplayCharacter(uint8 char_value);

void LCD_DisplayString(const uint8 * str_content);

void LCD_MoveCursor(uint8 row , uint8 col);

void LCD_DisplayStringRowCol(const uint8 * str_content , uint8 row , uint8 col);

void LCD_intgerToString(uint32 Data_int);


void LCD_ClearScreen(void);

void LCD_MoveCursorRight(void);

void LCD_MoveCursorLeft(void);

#endif