/*
 * @file   DOGM128_rectangle.c  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Source file for writing a rectangle to the EA DOGM128. <br>
 * @defgroup DOGM128_rectangle_source
 * @{
 *
 * This file contains the source code for the dog_draw_rectangle() function, 
 * which is used to set or clear an unfilled rectangle.
 *
 */
/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_rectangle.h"
#include "DOGM128_lines.h"

/*----------------------------------------------------------------------------*/
/* FUNCTIONS                                                                  */
/*----------------------------------------------------------------------------*/

void dog_draw_rectangle(uint8_t x1,
                       uint8_t y1,
                       uint8_t x2,
                       uint8_t y2,
                     uint8_t size,
                        char mode)
{
  
   dog_draw_h_line(x1,x2,y1,size,mode);
   dog_draw_v_line(x2,y1,y2,size,mode);
   dog_draw_v_line(x1,y1,y2,size,mode);
   dog_draw_h_line(x1,x2,y2,size,mode);

}

/* @} */ /* DOGM128_rectangle_source */