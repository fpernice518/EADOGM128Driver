#ifndef DOGM128_ARC_H
#define DOGM128_ARC_H

/**
 * @file   DOGM128_arc.h  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Header file for writing an arc or circle to the EA DOGM128. <br>
 * @defgroup DOGM128_arc Arcs and Circles
 * @{
 *
 * This file contains the prototype for the dog_draw_arc() function, 
 * which is used to set or clear an arc or unfilled circle.
 *
 */

/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_common.h"

/*----------------------------------------------------------------------------*/
/* FUNCTIONS                                                                  */
/*----------------------------------------------------------------------------*/

/** This function is used set or clear an arc or unfilled circle of thickness 0
 *  or 1. If both the start and end angle are the same number, then a circle 
 *  is drawn.
 *
 *  @par Parameters
 *    - @a x_center    = X coordinate of the arc or circle's center.
 *    - @a y_center    = Y coordinate of the arc or circle's center.
 *    - @a radius      = Radius of the arc or circle
 *
 *      Start and end angle are not represented in degrees nor radians.
 *      To convert from degrees to LCD_angles, use the following formula:
 *      <BR>  LCD_angle = angle_degrees * (32/45) <BR>
 *      So:                                                                 <BR>
 *       90 degrees = 64,                                                   <BR>
 *       180 degrees = 128,                                                 <BR>
 *       270 degrees = 192,                                                 <BR>
 *       360 degrees = 256 (due to 8-bit overflow, this is also zero)      .<BR>
 * 
 *    - @a start_angle = The start angle of the arc or circle
 *    - @a end_angle   = The end angle of the arc or circle                 <BR>
 *                                                                          <BR>
 *                                                                          <BR>
 *    - @a size        = The thickness of the point to place (0 or 1)
 *    - @a mode        = 's' for set, 'c' for clear
 *
 *  @par Algorithm
 *       This function essentially draws lines between two computed coordinates 
 *       through multiple iterations as it makes its way around the circle or 
 *       arc.
 *       - First computes the difference between provided angles
 *       - The computes the number of required iterations.
 *       - Then it computes X and Y coordinates for each iteration, drawing a 
 *         line between them with the dog_draw_line() function.
 *
 *  @par Assumptions
 *       - None
 *
 */
void dog_draw_arc(uint8_t x_center,
                 uint8_t y_center,
                 uint8_t radius,
                 uint8_t start_angle,
                 uint8_t end_angle,
                 uint8_t size,
                 char mode);

#endif /* DOGM128_ARC_H */
/** @} */ /* DOGM128_arc */