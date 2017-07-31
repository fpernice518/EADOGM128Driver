/*
 * @file   DOGM128_pixels.c  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Source code for drawing individual pixels to the EA DOGM128. <br>
 * @defgroup DOGM128_pixels_source
 * @{
 *
 * This file contains the source code for the function described in
 * pixel.h. The user should include this file in his or her project
 * should they choose to draw individual pixels on the screen or use  
 * any functions dependent on the ones in this file. 
 */

/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_pixel.h"
#include "DOGM128_common.h"

/*----------------------------------------------------------------------------*/
/* External Data                                                              */
/*----------------------------------------------------------------------------*/
/**
 * @var uint8_t dog_buffer[DOG_PAGE_HEIGHT][DOG_WIDTH]
 * @brief External buffer used for storing screen contents before sending data
 *        to screen.
 */
extern uint8_t dog_buffer[DOG_PAGE_HEIGHT][DOG_WIDTH];

/*----------------------------------------------------------------------------*/
/* Functions                                                                  */
/*----------------------------------------------------------------------------*/ 

int8_t dog_draw_pixel(uint8_t row, uint8_t col, char mode)
{
  uint8_t page;                               /* Declare local variables */

  /* Ensure pixel position is not off the screen. Note that we do not
   * check for lower bounds since we are dealing with unsigned numbers
   */
  if(row >= DOG_HEIGHT)
    return -1;      /* return -1 if row is too large */
  if(col >= DOG_WIDTH)
    return -2;      /* return -2 if col is too large */
  
  
  /* Divide row by 8 and truncate to get page number,shift for efficiency */
  page = row >> 3; 
  
  switch (mode) /* Switch on function mode (clear or set pixel) */
  {
  case 's': /* Set Pixel */
                  
           /* Set the desired pixel by OR-ing the contents of the desired
            * buffer position with the row number mod 8. 
            * row % DOG_PAGE_HEIGHT obtains the specific row within the page.
            * So, suppose we want to set pixel (10, 20), we can obtain the
            * page number by dividing 20 by 8 as shown above, which equals 2 
            * when truncated. Next, we can determine the individual row we must
            * set on page 2 by computing 20 % 8, which equals 4.*/
           dog_buffer[page][col] =
             dog_buffer[page][col] | (1<<(row % DOG_PAGE_HEIGHT));
           
           return 0;   /* Return 0 upon successful completion */
           
  case 'c': /* Clear Pixel */
  
           /*See above comments, same logic applies */
           dog_buffer[page][col] = 
             dog_buffer[page][col] & (0<<(row % DOG_PAGE_HEIGHT));
           return 0;   /* Return 0 upon successful completion */
  default:
           return -3;  /* Return -3 upon invalid mode parameter*/
  }
}
/* @} */ /* DOGM128_pixels */