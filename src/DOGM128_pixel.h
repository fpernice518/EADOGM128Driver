/**
 * @file   DOGM128_pixel.h  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Header file for writing pixels to the EA DOGM128. <br>
 * @defgroup DOGM128_pixel Pixel
 * @{
 *
 * This file contains the function prototype for the dog_draw_pixel() function.
 *
 */

/* Used to prevent multiple inclusion of the header file */
#ifndef DOGM128_PIXELS_H
#define DOGM128_PIXELS_H 

/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_common.h"

/*----------------------------------------------------------------------------*/
/* Functions                                                                  */
/*----------------------------------------------------------------------------*/  

/** This function is used to set an individual pixel on the screen.
 *
 *  @par Parameters
 *         - @a row =  The desired row to place the pixel (0-63)
 *
 *         - @a col = The desired column to place the pixel (0-127)
 * 
 *         - @a mode = 's' for set, 'c' for clear
 *
 *  @par Algorithm
 *       - Ensures that the provided row and column are within range. It then
 *       computes the which page the pixel will be placed on and where within
 *       that page. It then either sets or clears the pixel depending on the
 *       mode
 *
 *  @par Assumptions
 *       - None
 *
 *  @returns 
 *       - 0 upon sucessful completion
 *       - -1 in case of an out of range row
 *       - -2 in case of an out of range column
 *       - -3 in case of invalid mode character
 *
 */
int8_t dog_draw_pixel(uint8_t row, uint8_t col, char mode);

#endif /* DOGM128_PIXELS_H */
/** @} */ /* DOGM128_pixel */