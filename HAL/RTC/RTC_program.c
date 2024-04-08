/******************************************************************************
 *
 * Module: Real Time Clock
 *
 * File Name: RTC_program.c
 *
 * Description: contain impelementation for RTC
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/
/**************************                   INCLUDES                   **************************/

#include "RTC_interface.h"
#include "RTC_private.h"



volatile uint8 RTC_Current_TimeMode ;

/*  Convert 49 to 0x49*/
uint8 u8_2_BCD(uint8 value)// 49
{
    uint8 temp = value %10; // 9
    value /= 10 ; //4 
    temp |= (value << 4);
    return temp;   
}

/*  Convert 0x49 to 49*/
uint8 BCD_2_u8(uint8 value)
{
    uint8 temp = (value >> 4) * 10;
    temp += (value & 0x0F);
    return temp ;
}

void RTC_Init(RTC_Time_Mode RTC_Time_Mode_Value)
{
    RTC_Current_TimeMode =  RTC_Time_Mode_Value;
    /*  call I2C init function so you need to edit in config.h & config.c ⚠️RTC use 100Khz baud rate */
    I2C_Init();
    
    /*  start communication to read old value  */
    I2C_Start();

    /*Send Address of RTC  */
    I2C_WriteByte(RTC_ADDRESS_WRITE_OP);

    /*  Send word address that I will read second from  */
    I2C_WriteByte(RTC_Base_Address_Time);

    /*  Make reStart  */
    I2C_Start();

    /*  read from Slave  */
    I2C_WriteByte(RTC_ADDRESS_READ_OP);

    /*  read second to make CH = 0 */
    uint8 Loc_RTC_SEC = I2C_ReadByteWithACK();

    /* read min  */
    uint8 Loc_RTC_min = I2C_ReadByteWithACK();

    /*  load hours then make change I need in clock mode As I don't want make data corruption  */
    uint8 Loc_RTC_HOUR = I2C_ReadByteWithNACK();

    /*  then stop */
    I2C_Stop(); 

    /*  start communication to set wich time mode I will use  */
    I2C_Start();

    /*Send Address of RTC and You will write to set mode  */
    I2C_WriteByte(RTC_ADDRESS_WRITE_OP);

    /*  go to address 0x00 in RTC to make "CH" in Bit 7 in this regester equal Zero  */
    I2C_WriteByte(RTC_Base_Address_Time);

    /*  Then write data in second to set "CH" = 0 */
    I2C_WriteByte(Loc_RTC_SEC & RTC_CH_BIT_Clear);

    I2C_WriteByte(Loc_RTC_min);

    if(RTC_Time_Mode_Value == RTC_12_Hour_MODE)
    {
        /*  Set Bit 6 make me in 12 hours mode  */
        I2C_WriteByte(Loc_RTC_HOUR | RTC_MACRO_SET_12_Hour_mode);
    }
    else if(RTC_Time_Mode_Value == RTC_24_Hour_MODE)
    {
        /*  Set Bit 6 make me in 24 hours mode  */
        I2C_WriteByte(Loc_RTC_HOUR & RTC_MACRO_SET_24_Hour_mode);
    }

    /*  then stop */
    I2C_Stop(); 

}


void RTC_SetTime(RTC_Time * RTC_Time_Value) 
{
    /*  start communication to read old value  */
    I2C_Start();

    /*Send Address of RTC in write mode  */
    I2C_WriteByte(RTC_ADDRESS_WRITE_OP);

    /*  Send word address that I will write at */
    I2C_WriteByte(RTC_Base_Address_Time);

    /*  send seconds that RTC will set with  */
    I2C_WriteByte( u8_2_BCD(RTC_Time_Value->RTC_SEC) );
    
    /*  send Minutes  */
    I2C_WriteByte( u8_2_BCD(RTC_Time_Value->RTC_MIN) );

    /*  Send Hours  */
    if(RTC_Current_TimeMode == RTC_12_Hour_MODE)
    {                                                                                       
        I2C_WriteByte( u8_2_BCD(RTC_Time_Value->RTC_HOUR) | (RTC_Time_Value->RTC_AM_PM << 5) | RTC_MACRO_SET_12_Hour_mode );
    }
    else if(RTC_Current_TimeMode == RTC_24_Hour_MODE)
    {
        I2C_WriteByte( u8_2_BCD(RTC_Time_Value->RTC_HOUR) );
    }

    /*  then stop */
    I2C_Stop(); 

}


void RTC_GetTime(RTC_Time * RTC_Time_Value)
{
    /*  start communication to read old value  */
    I2C_Start();

    /*Send Address of RTC in write mode  */
    I2C_WriteByte(RTC_ADDRESS_WRITE_OP);

    /*  Set Start address I will  read from    */
    I2C_WriteByte(RTC_Base_Address_Time);

    /*  Make Resart  */
    I2C_Start();

    /*  Send Address of RTC in Read mode  */
    I2C_WriteByte(RTC_ADDRESS_READ_OP);

    /*  Read Seconds  */
    RTC_Time_Value->RTC_SEC = BCD_2_u8( I2C_ReadByteWithACK() );

    /*  Read minutes  */
    RTC_Time_Value->RTC_MIN = BCD_2_u8( I2C_ReadByteWithACK() );

    /*  Read hours  */
    if(RTC_Current_TimeMode == RTC_12_Hour_MODE)
    {
        uint8 LastByte = I2C_ReadByteWithNACK();

        RTC_Time_Value->RTC_HOUR = (LastByte & 0x0F) + ((LastByte & 0x10) *10 );
        RTC_Time_Value->RTC_AM_PM = ( ( (LastByte & 0x20) > 0 ) ? RTC_PM : RTC_AM );
    }
    else if(RTC_Current_TimeMode == RTC_24_Hour_MODE)
    {
        RTC_Time_Value->RTC_HOUR = BCD_2_u8( I2C_ReadByteWithNACK() );   
    }

    /*  then stop */
    I2C_Stop(); 

}

/*  Read Day  🚩Here No Need to call BCD_2_u8 as it consist of 3 bits  */

void RTC_SetDate(RTC_Calendar * RTC_Days_Value) 
{

    /*  start communication to read old value  */
    I2C_Start();
    
    /*Send Address of RTC in write mode  */
    I2C_WriteByte(RTC_ADDRESS_WRITE_OP);

    /*  Send word address that I will read second from  */
    I2C_WriteByte(RTC_Base_Address_Calendar);

    /*  Set day of week first  */
    I2C_WriteByte(RTC_Days_Value->RTC_DAY);

    /*  Send date of this day  */
    I2C_WriteByte( u8_2_BCD(RTC_Days_Value->RTC_DATE) );

    /*  Send month  */
    I2C_WriteByte(u8_2_BCD(RTC_Days_Value->RTC_MONTH));

    /*  Send month  */
    I2C_WriteByte(u8_2_BCD(RTC_Days_Value->RTC_YEAR));

    /*  then stop */
    I2C_Stop(); 
}   


void RTC_GetDate(RTC_Calendar * RTC_Days_Value) 
{
    /*  start communication to read old value  */
    I2C_Start();
    
    /*Send Address of RTC in write mode  */
    I2C_WriteByte(RTC_ADDRESS_WRITE_OP);

    /*  Send word address that I will read second from  */
    I2C_WriteByte(RTC_Base_Address_Calendar);

    /*  Make Resart  */
    I2C_Start();

    /*  Send Address of RTC in Read mode  */
    I2C_WriteByte(RTC_ADDRESS_READ_OP);

    /*  Read Seconds  */
    RTC_Days_Value->RTC_DAY = BCD_2_u8( I2C_ReadByteWithACK() );

    /*  Read minutes  */
    RTC_Days_Value->RTC_DATE = BCD_2_u8( I2C_ReadByteWithACK() );

     /*  Read Seconds  */
    RTC_Days_Value->RTC_MONTH = BCD_2_u8( I2C_ReadByteWithACK() );

    /*  Read minutes  */
    RTC_Days_Value->RTC_YEAR = BCD_2_u8( I2C_ReadByteWithNACK() );

    /*  then stop */
    I2C_Stop(); 
}
