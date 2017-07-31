/**
 * @file   DOGM128_characters.h  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Header file for writing characters to the EA DOGM128. <br>
 * @defgroup DOGM128_characters Characters
 * @{
 *
 * This file contains function prototypes to write characters to the DOGM128. 
 * It contains a 5x7 ASCII character set and functions so that the user only   
 * needs to pass @b chars when placing a character on the screen rather than  
 * manually setting each individual pixel. Note that the functions included in 
 * this file DO NOT assume that the user has initialized the display.
 *
 *
 */

/* Used to prevent multiple inclusion of the header file */
#ifndef DOGM128_CHARACTERS_H
#define DOGM128_CHARACTERS_H 


/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_common.h"

/*----------------------------------------------------------------------------*/
/* DEFINES                                                                    */
/*----------------------------------------------------------------------------*/
/** Max line width. Note that characters are 5x7
  * pixels wide (actually 6x7 when we take into
  * account the automatic 1-column wide space
  * added to the buffer after almost all characters.
  * Due to this restriction, we can only print
  * up to 126/6 = 21 characters per line. 128/6
  * is not a whole number, hence why we cannot
  * print to the whole width of the display.
  */
#define DOG_CHAR_WIDTH  126   
   
/** Number of pages on the display. Included for
  * consistency.
  */
#define DOG_CHAR_HEIGHT 8         

/** Surprise character, just for fun! */
#define DOG_HIDDEN_MICKEY 128 

/*----------------------------------------------------------------------------*/
/* FUNCTION HEADERS                                                           */
/*----------------------------------------------------------------------------*/

/** This function is used by printf() to place individual characters on the
 *  print buffer; however, it may also be used standalone as well.
 *
 *  @par Parameters
 *         - @a c = The character to be printed to the display buffer. It is of
 *           type int rather than char to fit the predefined
 *           prototype in the stdio.h header.
 *
 *  @par Algorithm
 *       The function keeps track of the current column and page between
 *       subsequent calls. It begins by checking if @b c is a newline character
 *       and will increment to the next page accordingly. Otherwise, it will
 *       then check if the end of line has been reached (and if so, it will
 *       increment to the next page. It subsequently checks that the last page
 *       has not been reached (if it has, it will wrap around to the top of
 *       the display). Finally, it looks up the character's bitmap in a
 *       lookup table and prints that to the display buffer contained in
 *       the common.c file.
 *
 *  @par Assumptions
 *       - The user has no data they wish to leave on the screen that is
 *         in the path of the characters. That is, the user must be welcoming
 *         to the fact that all pixels along a <b> (6*n)x8 </b> path (where @b
 *         n is the number of characters printed) will be erased to make way for
 *         the characters.
 *
 *  @returns Upon sucessful completion, the original character @a c is returned.
 *
 */
int putchar(int c);

/** This function is used to set the page where putchar() will begin writing a 
 *  character to the screen.
 *
 *  @par Parameters
 *         - @a new_page = The new page number to be set. The value should be 
 *           between 0 and 7.
 *
 *  @par Algorithm
 *       Ensures that parameter @a new_page is within a valid range. If it is 
 *       within range, it sets the static variable @a page equal to @a new_page.
 *       Otherwise, @a page remains unchanged.
 *
 *  @par Assumptions
 *       - None
 *
 *  @returns Upon successful completion, the function returns zero. Otherwise it
 *           returns -1.
 */
int8_t dog_set_page(uint8_t new_page);

/** This function is used to set the column where putchar() will begin writing a 
 *  character to the screen (starting at the left-side of the letter).
 *
 *  @par Parameters
 *         - @a new_col = The new column number to be set. The value should be 
 *           between 0 and 122.
 *
 *  @par Algorithm
 *       Ensures that parameter @a new_col is within a valid range. If it is 
 *       within range, it sets the static variable @a col equal to @a new_col.
 *       Otherwise, @a col remains unchanged.
 *
 *  @par Assumptions
 *       - None
 *
 *  @returns Upon successful completion, the function returns zero. Otherwise it
 *           returns -1.
 */
int8_t dog_set_column(uint8_t new_col);

/** This function is used to write a character to the screen at any row
 *  (not page) or column on the screen regardless of the current cursor
 *  position. In other words, the character being written to the screen is not
 *  restricted to a particular page or column. @b NOTE: This function does not1
 *  move the current position; it will assume its old position before the
 *  function returns.
 *
 *  @par Parameters
 *         - @a row =  The desired row to place the character relative to
 *                  the top of character.
 *
 *         - @a new_col = The desired column to place the character to the left
 *                      hand side of the character.
 * 
 *         - @a c = The character to be written to the screen.
 *
 *  @par Algorithm
 *       Ensures that the provided row and column are within range. It then
 *       determines the page or pages in which the character will be placed on
 *       and the portion of the character that will be placed on each page.
 *       Next it looks up the character's bitmap in the character lookup table
 *       and places it in the screen buffer.
 *
 *  @par Assumptions
 *       - None
 *
 *  @returns Upon successful completion, the function returns zero. Otherwise it
 *           returns -1.
 */
int8_t dog_putchar_select(uint8_t row, uint8_t new_col, char c);

#endif /* DOGM128_CHARACTERS_H */

/** @} */ /* DOGM128_characters */