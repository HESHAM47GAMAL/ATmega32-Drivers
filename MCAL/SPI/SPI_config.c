 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: SPI_config.c
 *
 * Description: include configuration that will applied
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/


#include "SPI_config.h"


SPI_ConfigType SPI_ConfigTypeParam = {
    SPI_Slave ,
    LSB_First ,
    SPI_CLK_IDE_Low ,
    SPI_Sample_Setup ,
	F_CPU_64_SPI
};
