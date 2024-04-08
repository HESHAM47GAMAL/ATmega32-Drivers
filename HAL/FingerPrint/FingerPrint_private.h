/******************************************************************************
 *
 * Module: Finger Print
 *
 * File Name: FingerPrint_private.h
 *
 * Description: Header file as have function Prototype as can't called by user  
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef FINGERPRINT_PRIAVTE_H_
#define FINGERPRINT_PRIAVTE_H_


/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"

/*                    🙆‍♂️🙆‍♂️         Main Functions     🙆‍♂️🙆‍♂️ 

    1. make shake Hand Check 
    2. change color for finger print 
    3. make reading for finger  
        3.1.FingerPrint_GenerateImage();✔️
        3.2.FingerPrint_GenerateCharacterFile(FingerPrint_CharacterFile_1);✔️
        3.3.FingerPrint_GenerateImage();✔️
        3.4.FingerPrint_GenerateCharacterFile(FingerPrint_CharacterFile_2);✔️
        3.5.FingerPrint_GenerateTemplate();✔️
        3.6.FingerPrint_StoreTemplate();✔️


    4. make check 1 : 1
        4.1.FingerPrint_GenerateImage();✔️
        4.2FingerPrint_GenerateCharacterFile(FingerPrint_CharacterFile_1);✔️
        4.3FingerPrint_ReadFlashLibrary(FingerPrint_CharacterFile_1,4)✔️
        4.4FingerPrint_MatchcheckFile1File2()✔️
    5. make check 1 : N 

             */


/*  All instruction Codes used */
#define FingerPrint_HandShake_Command                                        0x40
#define FingerPrint_Generate_Image_Command                                   0x01
#define FingerPrint_Generate_Character_File_Command                          0x02
#define FingerPrint_Generate_Template_Command                                0x05
#define FingerPrint_Store_Template_Command                                   0x06
#define FingerPrint_Search_Command                                           0x04
#define FingerPrint_EmptyFingerLibrary_Command                               0x0D
#define FingerPrint_DeleteTemplate_Command                                   0x0C
#define FingerPrint_ReadFromFlashLibrary_Command                             0x07
#define FingerPrint_MatchBetweenFile1File2_Command                           0x03
#define FingerPrint_AuraLedControl_Command                                   0x35


#define FingerPrint_CharacterFile_1                 0x01
#define FingerPrint_CharacterFile_2                 0x02


typedef enum 
{
    FingerPrint_Command_Packet          = 0x01 ,
    FingerPrint_Data_Packet             = 0x02 ,
    FingerPrint_Acknowledge_Packet      = 0x07 ,
    FingerPrint_End_of_Packet           = 0x08
}FingerPrint_Package_Identifier ;



void FingerPrint_HeaderSend(void);

void FingerPrint_AddressSend(void);


void FingerPrint_GenerateImage(void);

void FingerPrint_GenerateCharacterFile(uint8 File_Num);

void FingerPrint_GenerateTemplate(void);

void FingerPrint_StoreTemplate(uint8 File_Num , uint8 pageID_Flash);

void FingerPrint_SearchFinger(uint8 File_Num ,uint8 startingPage , uint8 NumOfPagesInSearch);

void FingerPrint_Empty(void);

void FingerPrint_DeleteTemplate(uint8 PageID , uint8 NumberOfPages);

void FingerPrint_ReadFlashLibrary(uint8 File_Num , uint8 pageID);

void FingerPrint_MatchcheckFile1File2(void);

#endif