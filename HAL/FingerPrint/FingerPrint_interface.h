/******************************************************************************
 *
 * Module: Finger Print
 *
 * File Name: FingerPrint_interface.h
 *
 * Description: Header File contain function Prototype  
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef FingerPrint_INTERFACE_H_
#define FingerPrint_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "../../MCAL/USART/USART_interface.h"



#define FingerPrint_BaudeRate_Base          9600



typedef enum 
{
    FingerPrint_BuadRate_9600           =  1,
    FingerPrint_BaudeRate_19200         =  2,
    FingerPrint_BaudeRate_38400         =  4,
    FingerPrint_BaudeRate_57600         =  6,
    FingerPrint_BaudeRate_115200        =  12,
    
}FingerPrint_BaudRate;



/*  data type represent all responds from Finger Print  */
typedef enum 
{
    FingerPrint_CommandExecutionComplete            = 0x00 , // Any success for any command will be this
    FingerPrint_ErrorWhenReceivePackage             = 0x01 ,
    FingerPrint_NoFingerInSensor                    = 0x02 ,
    FingerPrint_FailToEnrollFinger                  = 0x03 ,
    FingerPrint_FailGenerateCharacter_OverDisorder  = 0x06 ,
    FingerPrint_FailGenerateCharacter_DueLeakness   = 0x07 ,
    FingerPrint_FingerDoesntMatch                   = 0x08 ,
    FingerPrint_FailedToFindMatchFinger             = 0x09 ,
    FingerPrint_FailedToCombineCharacter            = 0x0A ,
    FingerPrint_StoreTemplatePageIDIsBeyond         = 0x0B ,
    FingerPrint_ErrorReadFlash                      = 0x0C ,
    FingerPrint_FailToDeleteTemplate                = 0x10 ,
    FingerPrint_FailToClearFingerLibrary            = 0x11 ,



    FingerPrint_FailGenerateImage_DueLeakness      = 0x15 ,
    FingerPrint_StoreTemplateErrorWritingFlash     = 0x18 ,

    FingerPrint_NotRespondUntilNow                 = 0xFE , /*  👀👀Status Added By my to make handling to know if Finger print Respond     */

}FingerPrint_Acknowledge_Status;


/*  This data type tell you status for last request for Finger print is still in prograss or complete succusfully or failed */
typedef enum{
    FingerPrint_Success_OP      = 0x00 ,
    FingerPrint_Fail_OP         = 0x01 ,
    FingerPrint_NoRespond_OP    = 0x0F 
}FingerPrint_Result_Operation ;


/*  this data type used for make control more easy as tell you main operation for Finger print  */
typedef enum 
{
    FingerPrint_HandShake_Fun               = 1 ,
    FingerPrint_Color_Fun                   = 2 ,
    FingerPrint_ReadNewFinger_Fun           = 3 ,
    FingerPrint_ChechMatch_1_2_N            = 4 ,
    FingerPrint_ChechMatch_1_2_1            = 5 ,
    FingerPrint_DeleteTemplate_Fun          = 6 ,
    FingerPrint_EmptyTemplate_Fun           = 7 ,

    FingerPrint_No_Fun                      = 200   
}FingerPrint_Functions ;


/*  Data type represent main light status for Finger print*/
typedef enum 
{
    FingerPrint_BreathingLight              = 0x01 ,
    FingerPrint_FlashingLight               = 0x02 ,
    FingerPrint_LightON                     = 0x03 ,
    FingerPrint_LightOFF                    = 0x04 ,
    FingerPrint_LightGraduallyON            = 0x05 ,
    FingerPrint_LightGraduallyOFF           = 0x06 ,

}FingerPrint_ControlCode ;

/*  Data type represent main light color for Finger print*/
typedef enum 
{
    FingerPrint_RedColor                = 0x01 ,
    FingerPrint_BlueColor               = 0x02 ,
    FingerPrint_PurpleColor             = 0x03 

}FingerPrint_ColorIndex ;




/*
*   @brief : this function used to initailize USART  (and you need to go to uart_config.c & .h to make data = 8 bit , 1 stop bit , No parity and use baudrate =57600 bps)
*   Enable gloal interrupt and this use Uart in transmit polling & receive interrupt
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void FingerPrint_Init(void);

/*
*   @brief : this function used to make check if sensor work
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void FingerPrint_HandShake(void);

/*
*   @brief : this function used to make Enrollment for New finger and work in state Machine mode (⚠️👀not each time enter function will make new enrollment but continue procces of Enrollment)
*   @arg1 pageID_Flash : number of page want to store this finger
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Non Reentrant
*/
void FingerPrint_Enrollment(uint8 pageID_Flash);

/*
*   @brief : this function used to make deletion for all finger and work in state Machine mode (⚠️👀not each time enter function will make delete but continue procces of Enrollment)
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Non Reentrant
*/
void FingerPrint_DeleteFullFlash(void);

/*
*   @brief : this function used to make delete for number of fingers and work in state Machine mode (⚠️👀not each time enter function will make delete but continue procces of Enrollment)
*   @arg1  PageID:  starting page for delete
*   @arg2  NumberOfPages:  number of pages to delete from start 
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Non Reentrant
*/
void FingerPrint_DeleteNumOfFinger(uint8 PageID , uint8 NumberOfPages);

/*
*   @brief : this function used to to make matching for current finger catched from sensor with stored in memory and work in state Machine mode (⚠️👀not each time enter function will make new matching check but continue procces of Enrollment)
*   here make match with range of memory 
*   @arg1   startingPage : starting page for checking
*   @arg2   NumOfPagesInSearch : Number of pages
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Non Reentrant
*/
void FingerPrint_Match_1_2_N(uint8 startingPage , uint8 NumOfPagesInSearch);

/*
*   @brief : this function used to get status of current operation (Enrollment , delete or match)
*   @args  : void
*   @return FingerPrint_Result_Operation : status for operation (compeleted with successfull or failure and if entrer this function again will make this operation again ) 
*   or still NoRespond_OP  (so need to enter it to continue state machine for this operation)
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
FingerPrint_Result_Operation FingerPrint_GetOperationStatus (void);


/*
*   @brief : this function used to control color for finger print
*   @args  : void
*   @return: no return
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void FingerPrint_ColorControl(FingerPrint_ControlCode ControlCode_value , uint8 speed_value , FingerPrint_ColorIndex Color_index_value , uint8 time_value);






#endif


