#ifndef DOGM128_USER_CONFIG_H
#define DOGM128_USER_CONFIG_H

/**
 * @file   DOGM128_rectangle.h  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  User configuration header file. <br>
 * @defgroup DOGM128_user_configuration User Configuration
 * @{
 *
 * This file contains definitions that allow the user to customize the library.
 * Here, the user can change the i/o pins of the DOG module in addition to
 * changing the SPI registers, ports, and pins for maximum portability. In this
 * way, this code can be easilly ported to another compiler or even another 
 * microcontroller.
 *
 */

/** include file for the ATMega128. Can be replaced with 
 * another header file when porting to another MCU or
 * compiler.
 */
 
/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include <iom128.h>

/*----------------------------------------------------------------------------*/
/* SPI Settings                                                               */
/*----------------------------------------------------------------------------*/
/** MCU Port where SPI pins reside */
#define DOG_SPI_PORT             PORTB
/** Chip Select Pin */ 
#define DOG_SS_BAR_PIN           0  
/** SPI Interrupt Flag bit position */    
#define DOG_SPIF_BIT             7 

/** SPI Status Register */     
#define DOG_SPSR                 SPSR
/** SPI Double SCK */
#define DOG_SPR2X                0


/** SPI Data Register */ 
#define DOG_SPDR                 SPDR
 
/** SPI Control Register */  
#define DOG_SPCR                 SPCR
/** SPI Interrupt Enable Bit */
#define DOG_SPIE                 7
/** SPI Enable Bit*/
#define DOG_SPE                  6
/** SPI Data Order Bit */
#define DOG_DORD                 5
/** SPI Master/Slave Mode Bit */
#define DOG_MSTR                 4
/** SPI Clock Polarity Bit */
#define DOG_CPOL                 3
/** SPI Clock Phase Bit */
#define DOG_CPHA                 2
/** SPI Clock Speed Bit 1 */
#define DOG_SPR1                 1
/** SPI Clock Speed  Bit 0 */
#define DOG_SPR0                 0

/*----------------------------------------------------------------------------*/
/* I/O Settings                                                               */
/*----------------------------------------------------------------------------*/
/** Port where the DOG module's reset 
 *  pin is to be connected.
 */
#define DOG_RESET_PORT           PORTB  
/** Pin within @b DOG_RESET_PORT where 
 *  the DOG module's reset pin is 
 *  connected.
 */                                       
#define DOG_RESET_PIN            5      

/** Port where the DOG module's A0 
 *  pin is to be connected.
 */
#define DOG_DATA_OR_COMMAND_PORT PORTB 

/** Pin within @b 
 *  DOG_DATA_OR_COMMAND_PORT where 
 *  the DOG module's A0 pin is 
 *  connected.
 */                                    
#define DOG_DATA_OR_COMMAND_PIN  4


#endif /* DOGM128_USER_CONFIG_H */
/** @} */ /* DOGM128_user_configuration */