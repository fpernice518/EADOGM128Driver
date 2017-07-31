/**
 * @file   DOGM128_common.h  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Header file containing common macros, typedefs, and function 
 *         prototypes which belong in no particular category. <br>
 *
 * @defgroup DOGM128_common Common
 * @{
 *
 * This file contains various SPI macros, common constants, common typedefs, and 
 * various function prototypes which interface with the DOG module itself. The 
 * library is organized in such a way that the user should not have to 
 * interface with any of the macros in this file dealing with SPI communication.
 * The user will mostly only find the function prototypes in this file of 
 * interest and perhaps the constants and typedefs should they choose to expand
 * upon the library.
 *
 */

/* Used to prevent multiple inclusion of the header file */
#ifndef DOGM128_COMMON_H
#define DOGM128_COMMON_H  

/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_user_config.h"

/*----------------------------------------------------------------------------*/
/* CONSTANTS                                                                  */
/*----------------------------------------------------------------------------*/

/** Width of the entire display in pixels */
#define DOG_WIDTH  128
/** Height of the entire display in pixels */ 
#define DOG_HEIGHT 64
/** Height of a single page in pixels */
#define DOG_PAGE_HEIGHT 8

/*----------------------------------------------------------------------------*/
/* MACROS                                                                     */
/*----------------------------------------------------------------------------*/
/** Define SETBIT if not previously defined */
#ifndef SETBIT
#define SETBIT(port,bit) ((port) |= (1 << (bit)))
#endif /* SETBIT */

/** Define CLEARBIT if not previously defined */
#ifndef CLEARBIT
#define CLEARBIT(port,bit) ((port) &= ~(1 << (bit)))
#endif /* CLEARBIT */

/**Initialize SPI communication:                                           <BR>
 * SPIE  - SPI Interrupt DISABLED (we will poll instead)                   <BR>
 * SPE   - SPI ENABLED                                                     <BR>
 * DORD  - MSB First                                                       <BR>
 * MSTR  - Configured as a MASTER                                          <BR>
 * CPOL  - Clock Polarity = 0                                              <BR>
 * CPHA  - Clock Phase = 0                                                 <BR>
 * SPI Clock = f_clk/2          (EA DOGM128 can handle up to 20MHz)        <BR>
 * SPR1  - CLEARED                                                         <BR>
 * SPR0  - CLEARED                                                         <BR>
 * SPR2X - SET                  (When available)                           <BR>
 */                                                                        

#ifdef DOG_SPR2X
#define DOG_INIT_SPI() DOG_SPCR = ((0 << DOG_SPIE)|                        \
                                  (1 << DOG_SPE)  |                        \
                                  (0 << DORD)     |                        \
                                  (1 << MSTR)     |                        \
                                  (0 << DOG_CPOL) |                        \
                                  (0 << DOG_CPHA) |                        \
                                  (0 << DOG_SPR1) |                        \
                                  (0 << DOG_SPR0));                        \
                       SETBIT(DOG_SPSR, DOG_SPR2X);
#else
#define DOG_INIT_SPI() DOG_SPCR = ((0 << DOG_SPIE) |                       \
                                   (1 << DOG_SPE)  |                       \
                                   (0 << DORD)     |                       \
                                   (1 << MSTR)     |                       \
                                   (0 << DOG_CPOL) |                       \
                                   (0 << DOG_CPHA) |                       \
                                   (0 << DOG_SPR1) |                       \
                                   (0 << DOG_SPR0));                                            
#endif

/** Select the DOGM128 */
#define DOG_SLAVE_SELECT() CLEARBIT(DOG_SPI_PORT, DOG_SS_BAR_PIN);
/** Deselect the DOGM128 */
#define DOG_SLAVE_DESELECT() SETBIT(DOG_SPI_PORT, DOG_SS_BAR_PIN);
/** Activate DOGM128 reset */    
#define DOG_ASSERT_RESET() CLEARBIT(DOG_RESET_PORT, DOG_RESET_PIN);
/** Deactivate DOGM128 reset */
#define DOG_UNASSERT_RESET() SETBIT(DOG_RESET_PORT, DOG_RESET_PIN); 

/** Set A_0 pin; allows DOGM128 to receive data. */
#define DOG_SEND_DATA() \
        SETBIT(DOG_DATA_OR_COMMAND_PORT, DOG_DATA_OR_COMMAND_PIN);      
/** Clear A_0 pin; allows DOGM128 to receive commands. */                        
#define DOG_SEND_COMMAND() \
        CLEARBIT(DOG_DATA_OR_COMMAND_PORT, DOG_DATA_OR_COMMAND_PIN); 
        
/*----------------------------------------------------------------------------*/
/* TYPEDEFS                                                                   */
/*----------------------------------------------------------------------------*/

typedef unsigned char  uint8_t    /** portable 8-bit unsigned integer */  ;
typedef signed char     int8_t    /** portable 8-bit signed integer */    ;
typedef unsigned int  uint16_t    /** portable 16-bit unsigned integer */ ;
typedef signed int     int16_t    /** portable 16-bit signed integer */   ;

/** used for power-on and power off */
typedef enum{DOG_OFF = 0, DOG_ON} dog_power_state_t;

/** used for display mode */
typedef enum{DOG_NORMAL_DISPLAY = 0, DOG_INVERTED_DISPLAY} dog_display_mode_t;

/*----------------------------------------------------------------------------*/
/* FUNCTIONS                                                                  */
/*----------------------------------------------------------------------------*/

/** This function is used to initialize the EA DOGM128; it must be called prior
 *  to any of the other functions in this file and should only be called once. 
 *  It also clears the display.
 *
 *  @par Parameters
 *         - @a display_mode = When set to @b DOG_NORMAL_DISPLAY, the pixels are 
 *                              normally off.
 *                             When set to @b DOG_INVERTED_DISPLAY, the pixels
 *                              are normally on (inverted).
 *         - @a contrast     = Contrast value ranging on the set [0,63]. Higher
 *                             number means higher contrast.
 *
 *  @par Algorithm
 *       The function initializes SPI communication between the EA DOGM128 and
 *       the microcontroller. It then sends various setup commands to the LCD
 *       as specified by the datasheet. Finally, it clears the display to 
 *       remove any random pixels on the screen.
 *
 *  @par Assumptions
 *       - The user has correctly connected the screen to the microcontroller
 *         (keep your wiring neat) and has configured the user_config.h file
 *         according to his or her needs should the default configuration be
 *         changed.
 *
 */
void dog_init(dog_display_mode_t display_mode, uint8_t contrast);

/** This function is used to clear the entire LCD display; however 
 *  it does not clear the buffer.
 *
 *  @par Algorithm
 *       Beginning at page 0, column 0, the function mimics an old typewriter
 *       with a manual carriage return. It sends a value of zero to the display
 *       continuously for each column of the page until it reaches the end of
 *       the line (page). At which point, the page is manually advanced and 
 *       the column reset to zero (left side of display). It continues along
 *       this route until reaching the bottom-right corner. Finally, it resets
 *       the carriage to the top-left corner for future display writes.
 *
 *  @par Assumptions
 *       - The user has called the dog_init() function.
 *
 */
void dog_clear_display(void);

/** This function is used to clear the entire character buffer; however 
 *  it does not clear the display.
 *
 *  @par Algorithm
 *       The function simply advances through the two-dimensional array which
 *       makes up the buffer and sets its contents equal to zero. 
 *
 *  @par Assumptions
 *       - None
 *
 */
void dog_clear_buffer(void);

/** This function is used to print the entire contents of the buffer to the
 *  display.
 *
 *  @par Algorithm
 *       Beginning at page 0, column 0, the function mimics an old typewriter
 *       with a manual carriage return. It sends the corresponding buffer 
 *       contents to the display continuously for each column of the page until 
 *       it reaches the end of the line (page). At which point, the page is  
 *       manually advanced and the column reset to zero (left side of display). 
 *       It continues along this route until reaching the bottom-right corner. 
 *       Finally, it resets the carriage to the top-left corner for future
 *       display writes.
 *
 *  @par Assumptions
 *       - The user has called the dog_init() function.
 *
 */
void dog_print_buffer(void);

/** This function is used set the contrast of the DOG module.
 *  @par Parameters
 *         - @a contrast     = Contrast value ranging on the set [0,63]. Higher
 *                             number means higher contrast.
 *  @par Algorithm
 *       The function begins by masking out the 2 MSB's of the supplied contrast
 *       value. It then sends this value to the display using the contrast
 *       set commands as specified by the datasheet.
 *
 *  @par Assumptions
 *       - The user has called the dog_init() function.
 *
 */
void dog_set_contrast(uint8_t contrast);

/** This function is used set the display_mode of the DOG module.
 *  @par Parameters
 *         - @a display_mode = When set to @b DOG_NORMAL_DISPLAY, the pixels are 
 *                              normally off.
 *                             When set to @b DOG_INVERTED_DISPLAY, the pixels 
 *                              are normally on (inverted).
 *  @par Algorithm
 *       The function begins by masking out all bits except the LSB of the
 *       supplied display_mode value. It then sends this value to the display 
 *       using the display mode set command as specified by the datasheet.
 *
 *  @par Assumptions
 *       - The user has called the dog_init() function.
 *
 */
void dog_invert_pixels(dog_display_mode_t display_mode);

/** This function is used to turn the DOG module on or off. The DOG module is 
 *  powered on by default once the dog_init() function is called; this function
 *  can be used for toggling power once the dog_init() function has been called.
 *  It @b DOES @b NOT control the backlight.
 *  @par Parameters
 *         - @a state = DOG_OFF to power down, DOG_ON to power up.
 *  @par Algorithm
 *       The function begins simply transmits the on/off command to the display
 *
 *  @par Assumptions
 *       - The user has called the dog_init() function.
 *
 */
void dog_power(dog_power_state_t state);

#endif /* DOGM128_COMMON_H */
/** @} */ /* DOGM128_common */