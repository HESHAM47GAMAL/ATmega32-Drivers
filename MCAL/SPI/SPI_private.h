 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: SPI_private.h
 *
 * Description: Header file for AVR contain all register memmory mapped adderess for SPI
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"

#define SPCR              ( * (volatile uint8 *) (0x2D))
#define SPSR              ( * (volatile uint8 *) (0x2E))
#define SPDR              ( * (volatile uint8 *) (0x2F))



#define SPE             6
#define MSTR            4
#define DORD            5
#define CPOL            3
#define CPHA            2
#define SPR0            0


#define SPIF            7
#define SPI2X           0


#endif
