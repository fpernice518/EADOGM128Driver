/**
 * @file   DOGM128_rectangle.h  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Header file for drawing a rectangle to the EA DOGM128. <br>
 * @defgroup DOGM128_rectangle Rectangle
 * @{
 *
 * This file contains the prototype for the dog_draw_rectangle() function, 
 * which is used to set or clear an unfilled rectangle.
 *
 */

/* Used to prevent multiple inclusion of the header file */
#ifndef DOGM128_RECTANGLE_H
#define DOGM128_RECTANGLE_H

/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_common.h"

/*----------------------------------------------------------------------------*/
/* FUNCTIONS                                                                  */
/*----------------------------------------------------------------------------*/
/** This function is used set or clear an unfilled rectangle of thickness 0
 *  or 1.
 *
 *  @par Parameters
 *    - @a x1 = X coordinate of the top-left corner of the rectangle.[0,127]
 *    - @a t1 = Y coordinate of the top-left corner of the rectangle.[0,63]
 *    - @a x2 = X coordinate of the bottom-right corner of the rectangle.[0,127]
 *    - @a y2 = Y coordinate of the bottom-right corner of the rectangle.[0,63]
 *    - @a size = The thickness of the point to place (0 or 1)
 *    - @a mode = 's' for set, 'c' for clear
 *
 *  @par Algorithm
 *       - Simply calls the fast line drawing functions dog_draw_v_line() and
 *         dog_draw_h_line() twice each to draw each side of the rectangle.
 *
 *  @par Assumptions
 *       - None
 *
 *
 */
void dog_draw_rectangle(uint8_t x1,
                       uint8_t y1,
                       uint8_t x2,
                       uint8_t y2,
                     uint8_t size,
                        char mode);

#endif /* DOGM128_RECTANGLE_H */
/** @} */ /* DOGM128_rectangle */