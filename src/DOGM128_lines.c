/*
 * @file   DOGM128_lines.c  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Source code for drawing lines on the EA DOGM128. <br>
 * @defgroup DOGM128_lines_source 
 * @{
 *
 * This file contains the source code for drawing lines on the EA DOGM128. It
 * includes a generic line-drawing function which works for all slopes as well
 * as fast line-drawing functions for horizontal and vertical lines.
 *
 */
 
/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_lines.h"
#include "DOGM128_point.h"

/*----------------------------------------------------------------------------*/
/* Functions                                                                  */
/*----------------------------------------------------------------------------*/

void dog_draw_line(uint8_t x1,
                 uint8_t y1,
                 uint8_t x2,
                 uint8_t y2,
                 uint8_t size,
                 char mode)
{
  /* declare variables */
  uint8_t tmp;
  uint8_t x,y;
  uint8_t dx, dy;
  int8_t err;
  uint8_t swapxy = 0;
  int8_t ystep;
  
  /* Ensure parameters are properly set */
  if(x1 >= DOG_WIDTH || x2 >= DOG_WIDTH || y1 >= DOG_HEIGHT || y2 >= DOG_HEIGHT) return;
  if (mode != 'c' && mode != 's') return;
  if (size > 1) return;
  
  /* ensure dx and dy are positive numbers */
  if ( x1 > x2 ) dx = x1-x2; else dx = x2-x1;
  if ( y1 > y2 ) dy = y1-y2; else dy = y2-y1;
  
  /* If the difference in y is greater than the difference in x, swap them */
  if ( dy > dx )
  {
    swapxy = 1;
    tmp = dx; dx =dy; dy = tmp;
    tmp = x1; x1 =y1; y1 = tmp;
    tmp = x2; x2 =y2; y2 = tmp;
  }
  
  
  if ( x1 > x2 )               /* If x1 is greater than x2, swap them as well */
  {
    tmp = x1; x1 =x2; x2 = tmp;
    tmp = y1; y1 =y2; y2 = tmp;
  }
  
  err = dx >> 1;                                     /* Compute Initial Error */
  
 /* if ending y coordinate is greate than starting, step in +1 direction,
  * else step in -1 direction */
  if ( y2 > y1 ) ystep = 1; else ystep = -1;
  
  y = y1;                                          /* Set starting y position */
  
  for( x = x1; x <= x2; x++ )          /* iterate over all x values (columns) */
 {
   if ( swapxy == 0 )      /* If x and y were not swapped, draw point as such */
     dog_draw_point(y,x,size,mode);    //review this
   else                               /* Else draw point with swapped x and y */
     dog_draw_point(x,y,size,mode);
   
   err -= (uint8_t)dy;                                      /*Recompute Error */
   if ( err < 0 )
   {
     y += (uint8_t)ystep;
     err += (uint8_t)dx;
   }
 }
}

void dog_draw_h_line(uint8_t x1, uint8_t x2, uint8_t y, uint8_t size, char mode)
{
  uint8_t temp;
  uint8_t i;
  
  /* Ensure parameters are properly set */
  if(x1 >= DOG_WIDTH || x2 >= DOG_WIDTH || y >= DOG_HEIGHT) return;
  if (mode != 'c' && mode != 's') return;
  if (size > 1) return;
  
  /* swap x values if x1 > x2 */
  if(x1 > x2)
  {
    temp = x1;
    x1 = x2;
    x2 = temp;
  }
 /* Loop across all columns, setting or clearing each pixel between x1 and x2 */
  for(i = x1; i <= x2; ++i)
  {
    dog_draw_point(y,i,size,mode);
  }
}

void dog_draw_v_line(uint8_t x, uint8_t y1, uint8_t y2, uint8_t size, char mode)
{
  uint8_t temp;
  uint8_t i;
  
  /* Ensure parameters are properly set */
  if(x >= DOG_WIDTH || y1 >= DOG_HEIGHT || y2 >= DOG_HEIGHT) return;
  if (mode != 'c' && mode != 's') return;
  if (size > 1) return;
  
  /* swap y values if y1 > y2 */
  if(y1 > y2)
  {
    temp = y1;
    y1 = y2;
    y2 = temp;
  }
  
  /* Loop across all rows, setting or clearing each pixel between y1 and y2 */
  for(i = y1; i <= y2; ++i)
  {
    dog_draw_point(i,x,size,mode);
  }
}


/* @} */ /* DOGM128_lines */