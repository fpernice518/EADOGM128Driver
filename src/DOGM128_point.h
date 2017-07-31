/**
 * @file   DOGM128_point.c  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Header file for writing a point to the EA DOGM128. <br>
 * @defgroup DOGM128_point Point
 * @{
 *
 * This file contains the prototype for the dog_draw_point() function, 
 * which is used to set either a single pixel or a series of pixels for
 * increased line thickness.
 *
 */

/* Used to prevent multiple inclusion of the header file */
#ifndef DOGM128_POINT_H
#define DOGM128_POINT_H

/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_common.h"

/*----------------------------------------------------------------------------*/
/* Functions                                                                  */
/*----------------------------------------------------------------------------*/

/** This function is used to set an individual pixel or a pixel and a set of
 *  surrounding pixels for increased thickness.
 *
 *  @par Parameters
 *         - @a row =  The desired row to place the pixel or center of point 
 *                     (0-63)
 *
 *         - @a col = The desired column to place the pixel center of point 
 *                    (0-127)
 *         - @a size = The thickness of the point to place (0 or 1)
 *         - @a mode = 's' for set, 'c' for clear
 *
 *  @par Algorithm
 *       - Determines the size of the point based on the @a size parameter and 
 *         then sets or clears the corresponding pixel(s) based on the mode of
 *         operation.
 *
 *  @par Assumptions
 *       - None
 *
 */
void dog_draw_point(uint8_t row,
                  uint8_t col,
                  uint8_t size,
                  char mode);

#endif /* DOGM128_POINT_H */
/** @} */ /* DOGM128_point */