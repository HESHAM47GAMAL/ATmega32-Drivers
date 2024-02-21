 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: SPI_config.h
 *
 * Description: Header to configure SPI
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"

/**************************                   Definition                   **************************/

#define Enable_Interrupt_SPI                1        //  Option 1 -----------|
#define Disable_Interrupt_SPI               0        //  Option 2 -----------|
//                                                                             |
#define INTERUPT_STATE_SPI          Disable_Interrupt_SPI    //<------------|


typedef enum 
{
    MSB_First,
    LSB_First 
}SPI_Data_order ;

typedef enum 
{
    SPI_Slave ,
    SPI_Master 
}SPI_Mode ;

typedef enum{
    SPI_CLK_IDE_Low ,
    SPI_CLK_IDE_High
}SPI_CPOL;

typedef enum 
{
    SPI_Sample_Setup ,
    SPI_Setup_Sample
}SPI_PHA ;

typedef enum 
{
    F_CPU_4_SPI ,
    F_CPU_16_SPI ,
    F_CPU_64_SPI ,
    F_CPU_128_SPI ,
    F_CPU_2_SPI ,
    F_CPU_8_SPI ,
    F_CPU_32_SPI
}SPI_PREscaler ;


typedef struct 
{
    SPI_Mode SPI_Mode_value ;
    SPI_Data_order SPI_Data_order_value ;
    SPI_CPOL SPI_CPOL_value ;
    SPI_PHA SPI_PHA_value ;
    SPI_PREscaler SPI_PREscaler_value ;
}SPI_ConfigType ;



#endif