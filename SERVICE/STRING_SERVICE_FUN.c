 /******************************************************************************
 *
 * Module: String Service Functions
 *
 * File Name: STRING_SERVICE_FUN.C
 *
 * Description: provide Implementation for function that can handle some convertion including string
 *
 * Author: Hesham Shehata 
 *
 *******************************************************************************/


/**************************                   INCLUDES                   **************************/
#include "STRING_SERVICE_FUN.h"


void Convert_uint64_to_String(uint64 var , uint8 * String)
{
    uint8 index = 60 ; /*   As I will take last 4 bytes and convert them to Hexa Decemal  */

    uint8 it = 0 ;
    for( ; it < 16; it++)
    {
        switch( (var >> index) & 0x0F ) 
        {
            case 0x0A : 
                String[it] = 'A';
            break ;

            case 0x0B :
                String[it] = 'B';
            break ;

            case 0x0C :
                String[it] = 'C';
            break ;

            case 0x0D :
                String[it] = 'D';
            break ;

            case 0x0E :
                String[it] = 'E';
            break ;

            case 0x0F :
                String[it] = 'F';
            break ;

            default :
                String[it] = ( ( (var >> index) & 0x0F ) | 0x30 ); // to convert 0 from decimal to hexa
            break;
        }
    }


    it =0 ;
    index = 0 ;
    while(String[it] == '0')
    {
        it ++;
    }

    while(it < 16)
    {
        String[index] = String[it];
        it++ , index++ ; 
    }
    String[index] = '\0';

}




