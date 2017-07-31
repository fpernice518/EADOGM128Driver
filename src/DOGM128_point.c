/*
 * @file   DOGM128_point.c  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Source file for writing a point to the EA DOGM128. <br>
 * @defgroup DOGM128_point_source
 * @{
 *
 * This file contains the dog_draw_point() function, which is used to set either
 * a single pixel or a series of pixels for increased line thickness.he user 
 * should include this file in his or her project should they choose to use this
 * function or use any functions dependent on it.
 *
 */

/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_pixel.h"
#include "DOGM128_point.h"

/*----------------------------------------------------------------------------*/
/* Functions                                                                  */
/*----------------------------------------------------------------------------*/
void dog_draw_point(uint8_t row,
                  uint8_t col,
                  uint8_t size,
                  char mode)
{
  if ( size == 0 ) /* If size = 0, simply draw given pixel */
  {
    dog_draw_pixel(row, col, mode);
  }
  else if ( size == 1 ) /* If size = 1, draw given pixel and those north, south
                         * east and west of it.
                         */
  {
    dog_draw_pixel(row, col, mode);
    dog_draw_pixel(row+1, col, mode);
    dog_draw_pixel(row, col+1, mode);
    /* ensure non-negativity among row and column */
    if ( row > 0 ) dog_draw_pixel(row-1, col, mode);
    if ( col > 0 ) dog_draw_pixel(row, col-1, mode);
  }
  else
    return;
}
/* @} */ /* DOGM128_point_source */