/*
 * @file   DOGM128_arc.c  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Source code for writing an arc or circle to the EA DOGM128. <br>
 * @defgroup DOGM128_arc_source
 * @{
 *
 * This file contains the source code for the dog_draw_arc() function, 
 * which is used to set or clear an arc or unfilled circle. Also included in
 * this file are fast sine and cosine functions needed to draw the arcs as well.
 *
 */

/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/

#include "DOGM128_arc.h"
#include "DOGM128_lines.h"



/*----------------------------------------------------------------------------*/
/* GLOBAL DATA                                                                */
/*----------------------------------------------------------------------------*/
/**
 * @var uint8_t dog_sin_table[]
 * @brief Table of integer-scaled sine values from 0 to 90 degrees.
 */
const uint8_t dog_sin_table[] = 
{
  0,2,3,5,6,8,9,11,12,14,16,17,19,20,22,23,24,26,27,
  29,30,32,33,34,36,37,38,39,41,42,43,44,45,46,47,48,49,50,
  51,52,53,54,55,56,56,57,58,59,59,60,60,61,61,62,62,62,63,
  63,63,64,64,64,64,64,64
};


/*----------------------------------------------------------------------------*/
/* FUNCTIONS                                                                  */
/*----------------------------------------------------------------------------*/

/** This function is used to compute an integer-justified sine value for the
 *  provided angle (in LCD_angles). This function should only be needed by the
 *  dogm128, hence it has been made static (of course that can be changed 
 *  according to course material).
 *
 *
 *  @par Parameters
 *    - @a angle = The angle whose sine value must be computed.
 *
 *  @par Algorithm
 *       - Pulls data from the constant sine table based upon the provided angle
 *       - Since the table only covers one quarter of the total sine wave, 
 *         sine values are flipped and negated according to the symmetry of the
 *         sine wave. This is exactly the same method used in both ESE 381
 *         and ESE 382 during the Spring 2013 semester.
 *
 *  @par Assumptions
 *       - None
 *
 */
static int8_t dog_sin(uint8_t angle)
{
  uint8_t case_angle = (angle>>6)&3;
  uint8_t angle_index = angle & 63;
  signed char result = 0;
  switch(case_angle)
  {
    case 0:
      result = dog_sin_table[angle_index];
      break;
    case 1:
      result = dog_sin_table[64-angle_index];
      break;
    case 2:
      result = -dog_sin_table[angle_index];
      break;
    case 3:
      result = -dog_sin_table[64-angle_index];
      break;
  }
  return result;
}

/** This function is used to compute an integer-justified cosine value for the
 *  provided angle (in LCD_angles). This function should only be needed by the
 *  dogm128, hence it has been made static(of course that can be changed 
 *  according to course material).
 *
 *  @par Parameters
 *    - @a angle = The angle whose cosine value must be computed.
 *
 *  @par Algorithm
 *       - Simply calls the dog_sin() function in this file, providing it with
 *         @a angle shifted 90 degrees because a cosine wave is the same thing 
 *         as a sine wave shifted 90 degrees.
 *
 *  @par Assumptions
 *       - None
 *
 */
static int8_t dog_cos(uint8_t angle)
{
  return dog_sin( (angle+64U) );
}

void dog_draw_arc(uint8_t x_center,
                 uint8_t y_center,
                 uint8_t radius,
                 uint8_t start_angle,
                 uint8_t end_angle,
                 uint8_t size,
                 char mode)
{
  uint8_t l,i,w,x1,y1,x2,y2;
  uint16_t dw;
  
  
  /* check parameters */
  if(mode != 'c' && mode != 's') return;
  if(size > 1) return;
  
  /* compute difference between angles */
  if ( end_angle > start_angle )
    dw = end_angle-start_angle;          
  else
    dw = 256-start_angle+end_angle;

  if ( dw == 0 )
    dw = 256;

  /* compute number of steps needed to draw arc or circle */
  l = (uint8_t)(((((uint16_t)radius * dw) >> 7) * (uint16_t)201)>>7);
 
  /* compute starting x and y coordinates */
  x1 = x_center+(((int16_t)radius*(int16_t)dog_cos(start_angle)) >> 6);
  y1 = y_center+(((int16_t)radius*(int16_t)dog_sin(start_angle)) >> 6);
  
  /* iterate through for all points along the arc */
  for ( i = 1; i <= l; i++ )
  {
    w = ((uint16_t)dw*(uint16_t)i )/(uint16_t)l + start_angle;
    x2 = x_center+(((int16_t)radius*(int16_t)dog_cos(w)) >> 6);
    y2 = y_center+(((int16_t)radius*(int16_t)dog_sin(w)) >> 6);
    dog_draw_line(x1,y1,x2,y2,size,mode);
    x1 = x2;
    y1 = y2;
  }
}