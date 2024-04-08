/******************************************************************************
 *
 * Module: Real Time Clock
 *
 * File Name: RTC_interface.h
 *
 * Description: Header file conatain necessary definition called by user
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef RTC_INTERFACE_H_
#define RTC_INTERFACE_H_


/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "../../MCAL/I2C/I2C_interface.h"

#define RTC_AM          0
#define RTC_PM          1


typedef struct 
{
    uint8 RTC_SEC ;
    uint8 RTC_MIN ;
    uint8 RTC_HOUR ;
    uint8 RTC_AM_PM ; // 🛑🛑no need to use this value in 24_Hour_Mode
    /* 0 = AM   & 1 = PM */
}RTC_Time;

typedef enum
{
    RTC_SUN_DAY = 1 ,
    RTC_MON_DAY ,
    RTC_TUES_DAY ,
    RTC_WEN_DAY ,
    RTC_THUR_DAY ,
    RTC_FRI_DAY ,
    RTC_SAT_DAY 

}RTC_DAYS;

typedef struct
{
    RTC_DAYS RTC_DAY ;
    uint8 RTC_DATE ;
    uint8 RTC_MONTH ;
    uint8 RTC_YEAR ;
}RTC_Calendar ;



typedef enum 
{
    RTC_12_Hour_MODE ,
    RTC_24_Hour_MODE
}RTC_Time_Mode ;


/*
*   @brief : this function use to make make Initialization for I2C Driver (🚩so need to go to I2C_config.h and .c and use 100KHZ clock and Disable Interrupt)
*   and set mode for time (12-Hour Mode or 24-Hour Mode)
*   @arg1  RTC_Time_Mode_Value: define time mode RTC_12_Hour_MODE or RTC_24_Hour_MODE
*   @return: void
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void RTC_Init(RTC_Time_Mode RTC_Time_Mode_Value);

/*
*   @brief : this function used to set RTC current time 
*   @arg1  RTC_Time_Value: pointer to RTC_Time Data type
*   @return: void
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void RTC_SetTime(RTC_Time * RTC_Time_Value) ;

/*
*   @brief : this function used to get RTC current time
*   @arg1  RTC_Time_Value: pointer to RTC_Time Data type
*   @return: void
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void RTC_GetTime(RTC_Time * RTC_Time_Value) ;

/*
*   @brief : this function used to set RTC current Calendar 
*   @arg1  RTC_Days_Value: pointer to RTC_Calendar data type
*   @return: void
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void RTC_SetDate(RTC_Calendar * RTC_Days_Value) ;

/*
*   @brief : this function used to get RTC current Calendar
*   @arg1  RTC_Days_Value: pointer to RTC_Calendar data type
*   @return: void
*   @synchronous / Asynchronous : Synchronous
*   @ Reentrant / Non Reentrant : Reentrant
*/
void RTC_GetDate(RTC_Calendar * RTC_Days_Value) ;






#endif