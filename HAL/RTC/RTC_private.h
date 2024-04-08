/******************************************************************************
 *
 * Module: Real Time Clock
 *
 * File Name: RTC_private.h
 *
 * Description: Header file as have function Prototype and Macros as can't called by user
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef RTC_PRIVATE_H_
#define RTC_PRIVATE_H_

/**************************                   INCLUDES                   **************************/
#include "RTC_config.h"


/*  Address of RTC + write operation*/
#define RTC_ADDRESS_WRITE_OP       ( (RTC_Address_HEX << 1 ) + 0 )

/*  Address of RTC + Read operation*/
#define RTC_ADDRESS_READ_OP        ( (RTC_Address_HEX << 1 ) + 1 )

/*  IT's start memory address that carry data of seconds and have "CH" Bit  */
#define RTC_Base_Address_Time           0x00

#define RTC_Base_Address_Calendar       0x03

#define RTC_CH_BIT_Clear            0x7F

#define RTC_MACRO_SET_12_Hour_mode   0x40

#define RTC_MACRO_SET_24_Hour_mode   0xBF

#endif
