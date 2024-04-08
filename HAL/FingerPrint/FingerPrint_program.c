 /******************************************************************************
 *
 * Module: Finger Print
 *
 * File Name: FingerPrint_program.c
 *
 * Description: contain Implementation of Finger Print Driver 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "FingerPrint_interface.h"
#include "FingerPrint_private.h"
#include "FingerPrint_config.h"
#include "../../SERVICE/STD_TYPES.h"
#include "../../MCAL/USART/USART_interface.h"
#include "../../SERVICE/IVT.h"
#include "../../MCAL/GPIO/GPIO_interface.h"

#if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
    #include "../LCD/LCD_interface.h"  /*  🪲🐞Used for Debug only */
    #define F_CPU 8000000
    #include "util/delay.h"
#endif


#define FingerPrint_Status_Index_For_12_Bytes         9

#define FingerPrint_Status_Index_For_14_Bytes         9

#define FingerPrint_Status_Index_For_16_Bytes         9


volatile  uint8 Global_SW_Go = 0;

/*  Buffer used temporarly to store Full packet Respond from Finger Print  */
volatile uint8 u8_Local_FingerPrintBuffer [20] ;

static volatile FingerPrint_Acknowledge_Status u8_Local_Current_FingerPrint_Status = FingerPrint_NotRespondUntilNow ;

static volatile FingerPrint_Result_Operation FingerPrint_Result_Current_Operation = FingerPrint_NoRespond_OP;

#if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)

    void convertU8_Hex_16(void)
    {
        LCD_MoveCursor(0,0);
    
        uint8 String_t = 0;
        for(uint8 it = 0 ; it < 16 ; it++)
        {
            if(it == 8)
            {
                LCD_MoveCursor(1,0);
            }
            uint8 shiftBits = 4 ;
            for(uint8 inner = 0 ; inner < 2 ; inner++)
            {
                
                uint8 var = (u8_Local_FingerPrintBuffer[it] >> shiftBits) & 0x0F;
                switch( var ) 
                {
                    case 0x0A : 
                        String_t = 'A';
                    break ;

                    case 0x0B :
                        String_t = 'B';
                    break ;

                    case 0x0C :
                        String_t = 'C';
                    break ;

                    case 0x0D :
                        String_t = 'D';
                    break ;

                    case 0x0E :
                        String_t = 'E';
                    break ;

                    case 0x0F :
                        String_t = 'F';
                    break ;

                    default :
                        String_t = ( var | 0x30 ); // to convert 0 from decimal to hexa
                    break;
                }
                shiftBits = 0;
                LCD_DisplayCharacter(String_t);
                
            }
        }    
    }


    void convertU8_Hex_14(void)
    {   
        LCD_MoveCursor(0,0);
    
        uint8 String_t = 0;
        for(uint8 it = 0 ; it < 14 ; it++)
        {
            if(it == 7)
            {
                LCD_MoveCursor(1,0);
            }
            uint8 shiftBits = 4 ;
            for(uint8 inner = 0 ; inner < 2 ; inner++)
            {
                
                uint8 var = (u8_Local_FingerPrintBuffer[it] >> shiftBits) & 0x0F;
                switch( var ) 
                {
                    case 0x0A : 
                        String_t = 'A';
                    break ;

                    case 0x0B :
                        String_t = 'B';
                    break ;

                    case 0x0C :
                        String_t = 'C';
                    break ;

                    case 0x0D :
                        String_t = 'D';
                    break ;

                    case 0x0E :
                        String_t = 'E';
                    break ;

                    case 0x0F :
                        String_t = 'F';
                    break ;

                    default :
                        String_t = ( var | 0x30 ); // to convert 0 from decimal to hexa
                    break;
                }
                shiftBits = 0;
                LCD_DisplayCharacter(String_t);
                
            }
        }
    }


    void convertU8_Hex_12(void)
    {   
        LCD_MoveCursor(0,0);
    
        uint8 String_t = 0;
        for(uint8 it = 0 ; it < 12 ; it++)
        {
            if(it == 6)
            {
                LCD_MoveCursor(1,0);
            }
            uint8 shiftBits = 4 ;
            for(uint8 inner = 0 ; inner < 2 ; inner++)
            {
                
                uint8 var = (u8_Local_FingerPrintBuffer[it] >> shiftBits) & 0x0F;
                switch( var ) 
                {
                    case 0x0A : 
                        String_t = 'A';
                    break ;

                    case 0x0B :
                        String_t = 'B';
                    break ;

                    case 0x0C :
                        String_t = 'C';
                    break ;

                    case 0x0D :
                        String_t = 'D';
                    break ;

                    case 0x0E :
                        String_t = 'E';
                    break ;

                    case 0x0F :
                        String_t = 'F';
                    break ;

                    default :
                        String_t = ( var | 0x30 ); // to convert 0 from decimal to hexa
                    break;
                }
                shiftBits = 0;
                LCD_DisplayCharacter(String_t);
                
            }
        }
    }

#endif

void FingerPrint_ReceiveAcknowledge_16_byte(void)
{
    /*  Should wait to take 12 bytes  */
   static uint8 Received_Bytes = 0 ;
   u8_Local_FingerPrintBuffer[Received_Bytes] = USART_Catch_UDR_Value();
   Received_Bytes++ ;
   if(Received_Bytes == 16 )
   {
       u8_Local_FingerPrintBuffer[Received_Bytes] = '\0';
       Received_Bytes = 0 ;
       #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
            convertU8_Hex_16();
            while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
            {

            }
        #endif

        /*  Store status of received Packet from Finger Print sensor  */
        u8_Local_Current_FingerPrint_Status  = u8_Local_FingerPrintBuffer[FingerPrint_Status_Index_For_16_Bytes] ;
        Global_SW_Go = 0;

   }

}


void FingerPrint_ReceiveAcknowledge_14_byte(void)
{
    /*  Should wait to take 12 bytes  */
   static uint8 Received_Bytes = 0 ;
   u8_Local_FingerPrintBuffer[Received_Bytes] = USART_Catch_UDR_Value();
   Received_Bytes++ ;
   if(Received_Bytes == 14 )
   {
       u8_Local_FingerPrintBuffer[Received_Bytes] = '\0';
       Received_Bytes = 0 ;
       #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
            convertU8_Hex_14();
            while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
            {

            }
        #endif
        /*  Store status of received Packet from Finger Print sensor  */
        u8_Local_Current_FingerPrint_Status  = u8_Local_FingerPrintBuffer[FingerPrint_Status_Index_For_14_Bytes] ;
        Global_SW_Go = 0;

   }

}


void FingerPrint_ReceiveAcknowledge_12_byte(void)
{
    /*  Should wait to take 12 bytes  */
   static uint8 Received_Bytes = 0 ;
   u8_Local_FingerPrintBuffer[Received_Bytes] = USART_Catch_UDR_Value();
   Received_Bytes++ ;
   if(Received_Bytes == 12 )
   {
       u8_Local_FingerPrintBuffer[Received_Bytes] = '\0';
       Received_Bytes = 0 ;
       #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
            convertU8_Hex_12();
            while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
            {

            }
        #endif
        /*  Store status of received Packet from Finger Print sensor  */
        u8_Local_Current_FingerPrint_Status  = u8_Local_FingerPrintBuffer[FingerPrint_Status_Index_For_12_Bytes] ;
        Global_SW_Go = 0;

   }

}



FingerPrint_Result_Operation FingerPrint_GetOperationStatus (void)
{
    return FingerPrint_Result_Current_Operation;
}



void FingerPrint_Init(void)
{
    /*  ⚠️⚠️⚠️⚠️ go to Config.h and Config.c modifiy baude rate as It start communication by default by
    * 57600 bps   
    * 8 bit data
    * no Parity
    * 1 stop bit
    */  
    USART_Init();
    sei();
    USART_EnableReceiveInerrupt();
    USART_receiveStringAsynchCallBack( FingerPrint_ReceiveAcknowledge_12_byte );
    

}

void FingerPrint_Enrollment(uint8 pageID_Flash)
{
    
    static sint8 it = -1 ;
    if(it == -1)
    {
        FingerPrint_Result_Current_Operation = FingerPrint_NoRespond_OP;
        /*  Enrollment Start with taje 1st finger image  */
        FingerPrint_GenerateImage();
        it++;
    }
    else if(it == 0 )
    {
        if(FingerPrint_CommandExecutionComplete == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"image G Done     ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /* next function*/
            FingerPrint_GenerateCharacterFile(FingerPrint_CharacterFile_1) ;
            it++ ;
        }
        else if(u8_Local_Current_FingerPrint_Status == FingerPrint_ErrorWhenReceivePackage)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Error Receive    ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if(u8_Local_Current_FingerPrint_Status == FingerPrint_NoFingerInSensor)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"No Finger      ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if(u8_Local_Current_FingerPrint_Status == FingerPrint_FailToEnrollFinger)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Fail Collect ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
    }

    else if(it == 1)
    {
        if(FingerPrint_CommandExecutionComplete == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Img 2 Char     ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /* next function*/
            FingerPrint_GenerateImage();
            it++ ;
        }
        else if( u8_Local_Current_FingerPrint_Status == FingerPrint_ErrorWhenReceivePackage)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Fail IMG2Char    ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if((u8_Local_Current_FingerPrint_Status == FingerPrint_FailGenerateCharacter_OverDisorder) || (u8_Local_Current_FingerPrint_Status == FingerPrint_FailGenerateCharacter_DueLeakness) || (u8_Local_Current_FingerPrint_Status == FingerPrint_FailGenerateImage_DueLeakness))
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"fail Not Included");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(3000);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
    }

    else if(it == 2)
    {
        if(FingerPrint_CommandExecutionComplete == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"image N G Done   ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /* next function*/
            FingerPrint_GenerateCharacterFile(FingerPrint_CharacterFile_2) ;
            it++ ;
        }
        else if(u8_Local_Current_FingerPrint_Status == FingerPrint_ErrorWhenReceivePackage)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Error Receive    ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if(u8_Local_Current_FingerPrint_Status == FingerPrint_NoFingerInSensor)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"No Finger      ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if(u8_Local_Current_FingerPrint_Status == FingerPrint_FailToEnrollFinger)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Fail Collect ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
    }
    else if(it == 3)
    {
        if(FingerPrint_CommandExecutionComplete == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"New Img 2 Char  ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /* next function*/
            FingerPrint_GenerateTemplate();
            it++ ;
        }
        else if( u8_Local_Current_FingerPrint_Status == FingerPrint_ErrorWhenReceivePackage)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Fail IMG2Char    ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if((u8_Local_Current_FingerPrint_Status == FingerPrint_FailGenerateCharacter_OverDisorder) || (u8_Local_Current_FingerPrint_Status == FingerPrint_FailGenerateCharacter_DueLeakness) || (u8_Local_Current_FingerPrint_Status == FingerPrint_FailGenerateImage_DueLeakness))
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"fail Not Included");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(3000);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
    }
    else if(it == 4)
    {
        if(FingerPrint_CommandExecutionComplete == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Done Combination ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /* next function*/
            FingerPrint_StoreTemplate(FingerPrint_CharacterFile_1,pageID_Flash);
            it++ ;
        }
        else if( u8_Local_Current_FingerPrint_Status == FingerPrint_ErrorWhenReceivePackage)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Error Receive ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if (u8_Local_Current_FingerPrint_Status ==  FingerPrint_FailedToCombineCharacter)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"fail combine");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
    }
    else if(it == 5)
    {
        if(FingerPrint_CommandExecutionComplete == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Storage Succcess ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /* Update that function Done*/

            it = -1 ;
            FingerPrint_Result_Current_Operation = FingerPrint_Success_OP;
        }
        else if( u8_Local_Current_FingerPrint_Status == FingerPrint_ErrorWhenReceivePackage)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Fail store    ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if(FingerPrint_StoreTemplatePageIDIsBeyond == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"pageID False   ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if(FingerPrint_StoreTemplateErrorWritingFlash == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Error Store  ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
    }


}


void FingerPrint_DeleteFullFlash(void)
{
    static sint8 it = -1 ;
    if(it == -1)
    {
        FingerPrint_Result_Current_Operation = FingerPrint_NoRespond_OP;
        FingerPrint_Empty();
        it++;
    }
    else if (it == 0)
    {
        if(FingerPrint_CommandExecutionComplete == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Deletion Done    ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Success_OP;
        }
        else if (u8_Local_Current_FingerPrint_Status == FingerPrint_ErrorWhenReceivePackage)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                 LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Error In deletion");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if(u8_Local_Current_FingerPrint_Status == FingerPrint_FailToClearFingerLibrary)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Fail Clear Fings ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;            
        }
        
    }
}


void FingerPrint_DeleteNumOfFinger(uint8 PageID , uint8 NumberOfPages)
{
    static sint8 it = -1 ;
    if(it == -1)
    {
        FingerPrint_Result_Current_Operation = FingerPrint_NoRespond_OP;
        FingerPrint_DeleteTemplate(PageID,NumberOfPages);
        it++;
    }
    else if (it == 0)
    {
        if(FingerPrint_CommandExecutionComplete == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Deletion Done    ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Success_OP;
        }
        else if (u8_Local_Current_FingerPrint_Status == FingerPrint_ErrorWhenReceivePackage)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Error In deletion");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if(u8_Local_Current_FingerPrint_Status == FingerPrint_FailToDeleteTemplate)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                 LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Fail Clear Fings ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;            
        }
        
    }    
}


void FingerPrint_Match_1_2_N(uint8 startingPage , uint8 NumOfPagesInSearch)
{
    static sint8 it = -1 ;
    if(it == -1)
    {
        FingerPrint_Result_Current_Operation = FingerPrint_NoRespond_OP;
        /*  Enrollment Start with take 1st finger image  */
        FingerPrint_GenerateImage();
        it++;
    }
    if(it == 0 )
    {
        if(FingerPrint_CommandExecutionComplete == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"image G Done     ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /* next function*/
            FingerPrint_GenerateCharacterFile(FingerPrint_CharacterFile_1) ;
            it++ ;
        }
        else if(u8_Local_Current_FingerPrint_Status == FingerPrint_ErrorWhenReceivePackage)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Error Receive    ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if(u8_Local_Current_FingerPrint_Status == FingerPrint_NoFingerInSensor)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"No Finger      ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if(u8_Local_Current_FingerPrint_Status == FingerPrint_FailToEnrollFinger)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                  LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Fail Collect ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
    }
    else if(it == 1)
    {
        if(FingerPrint_CommandExecutionComplete == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Img 2 Char     ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /* next function*/
            FingerPrint_SearchFinger(FingerPrint_CharacterFile_1,startingPage,NumOfPagesInSearch);
            it++ ;
        }
        else if( u8_Local_Current_FingerPrint_Status == FingerPrint_ErrorWhenReceivePackage)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Fail IMG2Char    ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if((u8_Local_Current_FingerPrint_Status == FingerPrint_FailGenerateCharacter_OverDisorder) || (u8_Local_Current_FingerPrint_Status == FingerPrint_FailGenerateCharacter_DueLeakness) || (u8_Local_Current_FingerPrint_Status == FingerPrint_FailGenerateImage_DueLeakness))
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"fail Not Included");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            /*  🫷🤚🛑 Stop  */
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
    }
    else if(it == 2)
    {
        if(FingerPrint_CommandExecutionComplete == u8_Local_Current_FingerPrint_Status)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Match Done (:  ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Success_OP;
        }
        else if( u8_Local_Current_FingerPrint_Status == FingerPrint_ErrorWhenReceivePackage)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"Error Receiving ");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        else if( u8_Local_Current_FingerPrint_Status == FingerPrint_FailedToFindMatchFinger)
        {
            #if(FingerPrint_Debug_mode == FingerPrint_Enable_Debug)
                 LCD_MoveCursor(0,0);
                LCD_DisplayString((const uint8 *)"No Match Done ):");
                while(GPIO_ReadPin(PORTD_ID , PIN7_ID) == LOGIC_HIGH)
                {

                }
                _delay_ms(500);
            #endif
            it = -1;
            FingerPrint_Result_Current_Operation = FingerPrint_Fail_OP;
        }
        
    }

}





void FingerPrint_HeaderSend(void)
{
    USART_SendBytePolling(0xEF); /* Send highest byte of finger print Header    */
    USART_SendBytePolling(0x01); /* Send highest byte of finger print Header    */
}

void FingerPrint_AddressSend(void)
{
    USART_SendBytePolling(0xFF);
    USART_SendBytePolling(0xFF);
    USART_SendBytePolling(0xFF);
    USART_SendBytePolling(0xFF);
}




/*  EF 01 FF FF FF FF 01 00 03 40 00 44  */
void FingerPrint_HandShake(void)
{

    /*  @ First Should set Call back function to call this function as after some time will happen update for status  */
    USART_receiveStringAsynchCallBack( FingerPrint_ReceiveAcknowledge_12_byte );

    /*  Update status */
    u8_Local_Current_FingerPrint_Status = FingerPrint_NotRespondUntilNow ;

    uint16 CheckSumAccumulate =0 ;
    
    FingerPrint_HeaderSend();


    FingerPrint_AddressSend();


    USART_SendBytePolling(FingerPrint_Command_Packet); /*   Here will send command to finger print  */
    CheckSumAccumulate += FingerPrint_Command_Packet;

    /*  Set package length  (size = 2 bytes) and send 3 bytes  */
    USART_SendBytePolling(0x00);
    USART_SendBytePolling(0x03);
    CheckSumAccumulate += 0x03 ;

    /*  instruction code   */
    USART_SendBytePolling(FingerPrint_HandShake_Command);

    CheckSumAccumulate += FingerPrint_HandShake_Command ;

    USART_SendBytePolling((CheckSumAccumulate >> 8)); /*   Send highest byte of checksum   */

    USART_SendBytePolling((uint8)CheckSumAccumulate );/*   Send Lowest byte of checksum   */


/*  have 2 status for this function : 1.Conformation 2.Not conformation*/
}

void FingerPrint_ColorControl(FingerPrint_ControlCode ControlCode_value , uint8 speed_value , FingerPrint_ColorIndex Color_index_value , uint8 time_value)
{

    /*  @ First Should set Call back function to call this function as after some time will happen update for status  */
    USART_receiveStringAsynchCallBack( FingerPrint_ReceiveAcknowledge_12_byte );

    /*  Update status */
    u8_Local_Current_FingerPrint_Status = FingerPrint_NotRespondUntilNow ;

    uint16 CheckSumAccumulate =0 ;
    
    FingerPrint_HeaderSend();


    FingerPrint_AddressSend();


    USART_SendBytePolling(FingerPrint_Command_Packet); /*   Here will send command to finger print  */
    CheckSumAccumulate += FingerPrint_Command_Packet;

    /*  Set package length  (size = 2 bytes) and send 3 bytes  */
    USART_SendBytePolling(0x00);
    USART_SendBytePolling(0x07);
    CheckSumAccumulate += 0x07 ;  

    /*  instruction code   */
    USART_SendBytePolling(FingerPrint_AuraLedControl_Command);
    CheckSumAccumulate += FingerPrint_AuraLedControl_Command ; 

    /*  send control code  */
    USART_SendBytePolling(ControlCode_value);
    CheckSumAccumulate += ControlCode_value ; 

    /*  Send speed  */
    USART_SendBytePolling(speed_value);
    CheckSumAccumulate += speed_value ; 

    /*  send color index */
    USART_SendBytePolling(Color_index_value);
    CheckSumAccumulate += Color_index_value ; 


    /*  Send counts */
    USART_SendBytePolling(time_value);
    CheckSumAccumulate += time_value ; 

    
    USART_SendBytePolling((CheckSumAccumulate >> 8)); /*   Send highest byte of checksum   */
    USART_SendBytePolling((uint8)CheckSumAccumulate );/*   Send Lowest byte of checksum   */


    /*  status for this command : 
    *   1.Confirmation code=00H: Success 
    *   2.Confirmation code=01H: error when receiving package;
    */  
}





void FingerPrint_GenerateImage(void)
{
    

    /*  @ First Should set Call back function to call this function as after some time will happen update for status  */
    USART_receiveStringAsynchCallBack( FingerPrint_ReceiveAcknowledge_12_byte );

    /*  Update status */
    u8_Local_Current_FingerPrint_Status = FingerPrint_NotRespondUntilNow ;

    uint16 CheckSumAccumulate =0 ;
    
    FingerPrint_HeaderSend();


    FingerPrint_AddressSend();


    USART_SendBytePolling(FingerPrint_Command_Packet); /*   Here will send command to finger print  */
    CheckSumAccumulate += FingerPrint_Command_Packet;

    /*  Set package length  (size = 2 bytes) and send 3 bytes  */
    USART_SendBytePolling(0x00);
    USART_SendBytePolling(0x03);
    CheckSumAccumulate += 0x03 ;

    /*  instruction code   */
    USART_SendBytePolling(FingerPrint_Generate_Image_Command);

    CheckSumAccumulate += FingerPrint_Generate_Image_Command ;

    USART_SendBytePolling((CheckSumAccumulate >> 8)); /*   Send highest byte of checksum   */

    USART_SendBytePolling((uint8)CheckSumAccumulate );/*   Send Lowest byte of checksum   */

    /*  have 2 status for this function : 1.Conformation 2.error when receiving packag 3.can’t detect finger 4.fail to collect finger*/
    
}


void FingerPrint_GenerateCharacterFile(uint8 File_Num)
{

    /*  @ First Should set Call back function to call this function as after some time will happen update for status  */
    USART_receiveStringAsynchCallBack( FingerPrint_ReceiveAcknowledge_12_byte );

    /*  Update status */
    u8_Local_Current_FingerPrint_Status = FingerPrint_NotRespondUntilNow ;
        
    uint16 CheckSumAccumulate =0 ;
    
    FingerPrint_HeaderSend();


    FingerPrint_AddressSend();


    USART_SendBytePolling(FingerPrint_Command_Packet); /*   Here will send command to finger print  */
    CheckSumAccumulate += FingerPrint_Command_Packet;

    /*  Set package length  (size = 2 bytes) and send 3 bytes  */
    USART_SendBytePolling(0x00);
    USART_SendBytePolling(0x04);
    CheckSumAccumulate += 0x04 ;   

    /*  instruction code   */
    USART_SendBytePolling(FingerPrint_Generate_Character_File_Command);

    CheckSumAccumulate += FingerPrint_Generate_Character_File_Command ;

    /*  Send Buffer 1 OR 2 */
    USART_SendBytePolling(File_Num);
    CheckSumAccumulate += File_Num ;   

    USART_SendBytePolling((CheckSumAccumulate >> 8)); /*   Send highest byte of checksum   */

    USART_SendBytePolling((uint8)CheckSumAccumulate );/*   Send Lowest byte of checksum   */

    /*  status for this command : 
    *   1.Confirmation code=00H: generate character file complete
    *   2.Confirmation code=01H: error when receiving package;
    *   3.Confirmation code=06H: fail to generate character file due to the over-disorderly fingerprint image;
    *   4.Confirmation code=07H: fail to generate character file due to lackness of character point or over-smallness of fingerprint image;
    *   5.Confirmation code=15H: fail to generate the image for the lackness of valid primary image;
    */
}

void FingerPrint_GenerateTemplate(void)
{
    /*  @ First Should set Call back function to call this function as after some time will happen update for status  */
    USART_receiveStringAsynchCallBack( FingerPrint_ReceiveAcknowledge_12_byte );

    /*  Update status */
    u8_Local_Current_FingerPrint_Status = FingerPrint_NotRespondUntilNow ;

    uint16 CheckSumAccumulate =0 ;
    
    FingerPrint_HeaderSend();


    FingerPrint_AddressSend();


    USART_SendBytePolling(FingerPrint_Command_Packet); /*   Here will send command to finger print  */
    CheckSumAccumulate += FingerPrint_Command_Packet;

    /*  Set package length  (size = 2 bytes) and send 3 bytes  */
    USART_SendBytePolling(0x00);
    USART_SendBytePolling(0x03);
    CheckSumAccumulate += 0x03 ; 

    /*  instruction code   */
    USART_SendBytePolling(FingerPrint_Generate_Template_Command);
    CheckSumAccumulate += FingerPrint_Generate_Template_Command ;

    USART_SendBytePolling((CheckSumAccumulate >> 8)); /*   Send highest byte of checksum   */
    USART_SendBytePolling((uint8)CheckSumAccumulate );/*   Send Lowest byte of checksum   */
    /*  status for this command : 
    *   1.Confirmation code=00H: operation success
    *   2.Confirmation code=01H: error when receiving package
    *   3.Confirmation code=0AH: fail to combine the character files. That’s, the character files don’t belong to one finger.
    */
}


void FingerPrint_StoreTemplate(uint8 File_Num , uint8 pageID_Flash)
{

        /*  @ First Should set Call back function to call this function as after some time will happen update for status  */
    USART_receiveStringAsynchCallBack( FingerPrint_ReceiveAcknowledge_12_byte );

    /*  Update status */
    u8_Local_Current_FingerPrint_Status = FingerPrint_NotRespondUntilNow ;

    uint16 CheckSumAccumulate =0 ;
    
    FingerPrint_HeaderSend();


    FingerPrint_AddressSend();


    USART_SendBytePolling(FingerPrint_Command_Packet); /*   Here will send command to finger print  */
    CheckSumAccumulate += FingerPrint_Command_Packet;

    /*  Set package length  (size = 2 bytes) and send 3 bytes  */
    USART_SendBytePolling(0x00);
    USART_SendBytePolling(0x06);
    CheckSumAccumulate += 0x06 ;

    /*  instruction code   */
    USART_SendBytePolling(FingerPrint_Store_Template_Command);
    CheckSumAccumulate += FingerPrint_Store_Template_Command ;

    /*  send file number*/
    USART_SendBytePolling(File_Num);
    CheckSumAccumulate += File_Num ;

    /*  Send page flash number*/
    USART_SendBytePolling((pageID_Flash >> 8));
    USART_SendBytePolling((uint8)pageID_Flash );
    CheckSumAccumulate += pageID_Flash ;

    USART_SendBytePolling((CheckSumAccumulate >> 8)); /*   Send highest byte of checksum   */
    USART_SendBytePolling((uint8)CheckSumAccumulate );/*   Send Lowest byte of checksum   */

    /*  status for this command : 
    *   1.Confirmation code=00H:  storage success
    *   2.Confirmation code=01H: error when receiving package;
    *   3.Confirmation code=0bH: addressing PageID is beyond the finger library
    *   4.Confirmation code=18H: error when writing in flash
    */    

}


void FingerPrint_SearchFinger(uint8 File_Num ,uint8 startingPage , uint8 NumOfPagesInSearch)
{
    /*  @ First Should set Call back function to call this function as after some time will happen update for status  */
    USART_receiveStringAsynchCallBack( FingerPrint_ReceiveAcknowledge_16_byte );

    /*  Update status */
    u8_Local_Current_FingerPrint_Status = FingerPrint_NotRespondUntilNow ;

    uint16 CheckSumAccumulate =0 ;
    
    FingerPrint_HeaderSend();


    FingerPrint_AddressSend();


    USART_SendBytePolling(FingerPrint_Command_Packet); /*   Here will send command to finger print  */
    CheckSumAccumulate += FingerPrint_Command_Packet;

    /*  Set package length  (size = 2 bytes) and send 3 bytes  */
    USART_SendBytePolling(0x00);
    USART_SendBytePolling(0x08);
    CheckSumAccumulate += 0x08 ;    

    /*  instruction code   */
    USART_SendBytePolling(FingerPrint_Search_Command);
    CheckSumAccumulate += FingerPrint_Search_Command ;

    /*  send file number(charBuffer1 or charBuffer2)*/
    USART_SendBytePolling(File_Num);
    CheckSumAccumulate += File_Num ;

    /*  Send start page for search*/
    USART_SendBytePolling((startingPage >> 8));    
    USART_SendBytePolling((uint8)startingPage );
    CheckSumAccumulate += startingPage ;

    /*  set max page that is after start page will check if it equal buffer want to search   */
    USART_SendBytePolling((NumOfPagesInSearch >> 8));    
    USART_SendBytePolling((uint8)NumOfPagesInSearch );
    CheckSumAccumulate += NumOfPagesInSearch ;

    USART_SendBytePolling((CheckSumAccumulate >> 8)); /*   Send highest byte of checksum   */
    USART_SendBytePolling((uint8)CheckSumAccumulate );/*   Send Lowest byte of checksum   */


    /*  status for this command : 
    *   1.Confirmation code=00H: found the matching finer
    *   2.Confirmation code=01H: error when receiving package;
    *   3.Confirmation code=0bH: addressing PageID is beyond the finger library
    *   4.Confirmation code=09H: No matching in the library (both the PageID and matching score are 0);
    */   
}


void FingerPrint_Empty(void)
{
    /*  @ First Should set Call back function to call this function as after some time will happen update for status  */
    USART_receiveStringAsynchCallBack( FingerPrint_ReceiveAcknowledge_12_byte );

    /*  Update status */
    u8_Local_Current_FingerPrint_Status = FingerPrint_NotRespondUntilNow ;

    uint16 CheckSumAccumulate =0 ;
    
    FingerPrint_HeaderSend();


    FingerPrint_AddressSend();


    USART_SendBytePolling(FingerPrint_Command_Packet); /*   Here will send command to finger print  */
    CheckSumAccumulate += FingerPrint_Command_Packet;

    /*  Set package length  (size = 2 bytes) and send 3 bytes  */
    USART_SendBytePolling(0x00);
    USART_SendBytePolling(0x03);
    CheckSumAccumulate += 0x03 ; 

    /*  instruction code   */
    USART_SendBytePolling(FingerPrint_EmptyFingerLibrary_Command);
    CheckSumAccumulate += FingerPrint_EmptyFingerLibrary_Command ;   

    USART_SendBytePolling((CheckSumAccumulate >> 8)); /*   Send highest byte of checksum   */
    USART_SendBytePolling((uint8)CheckSumAccumulate );/*   Send Lowest byte of checksum   */


    /*  status for this command : 
    *   1.Confirmation code=00H: empty success
    *   2.Confirmation code=01H: error when receiving package;
    *   3.Confirmation code=11H: fail to clear finger library;
    */   
}


void FingerPrint_DeleteTemplate(uint8 PageID , uint8 NumberOfPages)
{
        /*  @ First Should set Call back function to call this function as after some time will happen update for status  */
    USART_receiveStringAsynchCallBack( FingerPrint_ReceiveAcknowledge_12_byte );

    /*  Update status */
    u8_Local_Current_FingerPrint_Status = FingerPrint_NotRespondUntilNow ;

    uint16 CheckSumAccumulate =0 ;
    
    FingerPrint_HeaderSend();


    FingerPrint_AddressSend();


    USART_SendBytePolling(FingerPrint_Command_Packet); /*   Here will send command to finger print  */
    CheckSumAccumulate += FingerPrint_Command_Packet;

    /*  Set package length  (size = 2 bytes) and send 3 bytes  */
    USART_SendBytePolling(0x00);
    USART_SendBytePolling(0x07);
    CheckSumAccumulate += 0x07 ; 

    /*  instruction code   */
    USART_SendBytePolling(FingerPrint_DeleteTemplate_Command);
    CheckSumAccumulate += FingerPrint_DeleteTemplate_Command ;  

    /*  Send start page for delete*/
    USART_SendBytePolling((PageID >> 8));    
    USART_SendBytePolling((uint8)PageID );
    CheckSumAccumulate += PageID ;

    /*  set max page that is after start page will delete   */
    USART_SendBytePolling((NumberOfPages >> 8));    
    USART_SendBytePolling((uint8)NumberOfPages );
    CheckSumAccumulate += NumberOfPages ;   

    USART_SendBytePolling((CheckSumAccumulate >> 8)); /*   Send highest byte of checksum   */
    USART_SendBytePolling((uint8)CheckSumAccumulate );/*   Send Lowest byte of checksum   */


    /*  status for this command : 
    *   1.Confirmation code=00H: delete success
    *   2.Confirmation code=01H: error when receiving package;
    *   3.Confirmation code=10H: fail to delete templates
    */   
}



void FingerPrint_ReadFlashLibrary(uint8 File_Num , uint8 pageID)
{
        /*  @ First Should set Call back function to call this function as after some time will happen update for status  */
    USART_receiveStringAsynchCallBack( FingerPrint_ReceiveAcknowledge_12_byte );

    /*  Update status */
    u8_Local_Current_FingerPrint_Status = FingerPrint_NotRespondUntilNow ;

    uint16 CheckSumAccumulate =0 ;
    
    FingerPrint_HeaderSend();


    FingerPrint_AddressSend();


    USART_SendBytePolling(FingerPrint_Command_Packet); /*   Here will send command to finger print  */
    CheckSumAccumulate += FingerPrint_Command_Packet;

    /*  Set package length  (size = 2 bytes) and send 3 bytes  */
    USART_SendBytePolling(0x00);
    USART_SendBytePolling(0x06);
    CheckSumAccumulate += 0x06 ; 

    /*  instruction code   */
    USART_SendBytePolling(FingerPrint_ReadFromFlashLibrary_Command);
    CheckSumAccumulate += FingerPrint_ReadFromFlashLibrary_Command ;  

    /*  send file number(charBuffer1 or charBuffer2)*/
    USART_SendBytePolling(File_Num);
    CheckSumAccumulate += File_Num ;

    /*  Send start page for search*/
    USART_SendBytePolling((pageID >> 8));    
    USART_SendBytePolling((uint8)pageID );
    CheckSumAccumulate += pageID ;   

    USART_SendBytePolling((CheckSumAccumulate >> 8)); /*   Send highest byte of checksum   */
    USART_SendBytePolling((uint8)CheckSumAccumulate );/*   Send Lowest byte of checksum   */


    /*  status for this command : 
    *   1.Confirmation code=00H: Load Success 
    *   2.Confirmation code=01H: error when receiving package;
    *   3.Confirmation code=0CH: error when reading template from library or the readout template is invalid;
    *   4.Confirmation code=0BH: addressing PageID is beyond the finger library;
    */  

}


void FingerPrint_MatchcheckFile1File2(void)
{
    /*  @ First Should set Call back function to call this function as after some time will happen update for status  */
    USART_receiveStringAsynchCallBack( FingerPrint_ReceiveAcknowledge_14_byte );

    /*  Update status */
    u8_Local_Current_FingerPrint_Status = FingerPrint_NotRespondUntilNow ;


    uint16 CheckSumAccumulate =0 ;
    
    FingerPrint_HeaderSend();


    FingerPrint_AddressSend();


    USART_SendBytePolling(FingerPrint_Command_Packet); /*   Here will send command to finger print  */
    CheckSumAccumulate += FingerPrint_Command_Packet;

    /*  Set package length  (size = 2 bytes) and send 3 bytes  */
    USART_SendBytePolling(0x00);
    USART_SendBytePolling(0x03);
    CheckSumAccumulate += 0x03 ; 

    /*  instruction code   */
    USART_SendBytePolling(FingerPrint_MatchBetweenFile1File2_Command);
    CheckSumAccumulate += FingerPrint_MatchBetweenFile1File2_Command ;  

    USART_SendBytePolling((CheckSumAccumulate >> 8)); /*   Send highest byte of checksum   */
    USART_SendBytePolling((uint8)CheckSumAccumulate );/*   Send Lowest byte of checksum   */


    /*  status for this command : 
    *   1.Confirmation code=00H: Template Buffer match
    *   2.Confirmation code=01H: error when receiving package;
    *   3.Confirmation code=08H: Template Buffer  aren’t matching
    */  

}



