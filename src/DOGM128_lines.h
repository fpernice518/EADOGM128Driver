/**
 * @file   DOGM128_lines.h  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Header file for drawing lines on the EA DOGM128. <br>
 * @defgroup DOGM128_lines Lines
 * @{
 *
 * This header file contains function prototypes for drawing lines on the EA 
 * DOGM128. It includes a generic line-drawing function prototype which works 
 * for lines of all slopes as well as fast line-drawing function prototypes for 
 * horizontal and vertical lines.
 *
 */

/* Used to prevent multiple inclusion of the header file */
#ifndef DOGM128_LINES_H
#define DOGM128_LINES_H

/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_common.h"

/*----------------------------------------------------------------------------*/
/* FUNCTIONS                                                                  */
/*----------------------------------------------------------------------------*/
/** This function is used to draw generic lines of any slope to the screen 
 *  buffer. If the user is only drawing horizontal or vertical lines, it is
 *  advised to use one of the two other functions in this file to conserve 
 *  system resources.
 *
 *  @par Parameters
 *        - @a x1 = X coordinate of line end point(x1,y1) in the set of [0,127].
 *        - @a y1 = Y coordinate of line end point(x1,y1) in the set of [0,63].
 *        - @a x2 = X coordinate of line end point(x2,y2) in the set of [0,127].
 *        - @a y2 = Y coordinate of line end point(x2,y2) in the set of [0,63].
 *        - @a size = Thickness of the line in the set [0,1].
 *        - @a mode = 'c' to clear the line, 's' to set the line.
 *
 *  @par Algorithm
 *       The function begins by checking parameter ranges, then computes
 *       point placement using 
 * <a title="Bresenham's Line Algorithm" href="http://www.cc.gatech.edu/g
 * rads/m/Aaron.E.McClennen/Bresenham/code.html">Bresenham's Line Algorithm</a>.
 *
 *  @par Assumptions
 *       - none
 */
void dog_draw_line(uint8_t x1,
                 uint8_t y1,
                 uint8_t x2,
                 uint8_t y2,
                 uint8_t size,
                 char mode);

/** This function is used to draw exclusively horizontal lines to the screen 
 *  buffer. It should be used in place of dog_draw_line() whenever possible to
 *  conserve resources.
 *
 *  @par Parameters
 *        - @a x1 = X coordinate of line end point(x1,y) in the set of [0,127].
 *        - @a x2 = X coordinate of line end point(x2,y) in the set of [0,127].
 *        - @a y  = Y coordinate of line in the set of [0,63]. Since a 
 *                  horizontal line maintains a constant Y value, we only need
 *                  one Y parameter.
 *        - @a size = Thickness of the line in the set [0,1].
 *        - @a mode = 'c' to clear the line, 's' to set the line.
 *
 *  @par Algorithm
 *       The function begins by checking the parameter ranges, then swaps the 
 *       x1 and x2 if needed. Finally, it loops through, setting or clearing
 *       every pixel between x1 and x2.
 *
 *  @par Assumptions
 *       - none
 */
 
void dog_draw_h_line(uint8_t x1,
                    uint8_t x2,
                    uint8_t y,
                    uint8_t size,
                    char mode);

/** This function is used to draw exclusively vertical lines to the screen 
 *  buffer. It should be used in place of dog_draw_line() whenever possible to
 *  conserve resources.
 *
 *  @par Parameters
 *        - @a x  = X coordinate of line in the set of [0,127]. Since a 
 *                  vertical line maintains a constant X value, we only need
 *                   one X parameter.
 *        - @a y1 = Y coordinate of line end point(x,y1) in the set of [0,63].
 *        - @a y2 = Y coordinate of line end point(x,y2) in the set of [0,63].
 *        - @a size = Thickness of the line in the set [0,1].
 *        - @a mode = 'c' to clear the line, 's' to set the line.
 *
 *  @par Algorithm
 *       The function begins by checking the parameter ranges, then swaps the 
 *       y1 and y2 if needed. Finally, it loops through, setting or clearing
 *       every pixel between y1 and y2.
 *
 *  @par Assumptions
 *       - none
 */                    
void dog_draw_v_line(uint8_t x,
                    uint8_t y1,
                    uint8_t y2,
                    uint8_t size,
                    char mode);

#endif  /* DOGM128_LINES_H */
/** @} */ /* DOGM128_lines */