/*
 * @file   DOGM128_characters.c  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Source code for writing characters to the EA DOGM128. <br>
 * @defgroup DOGM128_characters_source
 * @{
 *
 * This file contains the source code for the functions described in
 * characters.h. The user should include this file in his or her project
 * should they choose to write characters to the screen. It contains
 * a set of character bitmaps as well, which may be modified by the user. The
 * included executable charedit.exe will be of assistance in adding to and/or 
 * modifying the character set. It should be noted that charedit.exe is meant
 * to generate 6x8 characters, while the code in this file is written to
 * handle 5x7 characters exclusively; so the user should set/clear pixels
 * from B0-B4 and D0-D6, while throwing away the bottom-most row and right-most
 * columns D7 and B5 respectively.
 *
 */

/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_characters.h"

/*----------------------------------------------------------------------------*/
/* EXTERNAL DATA                                                              */
/*----------------------------------------------------------------------------*/
/**
 * @var uint8_t dog_buffer[DOG_PAGE_HEIGHT][DOG_WIDTH]
 * @brief External buffer used for storing screen contents before sending data
 *        to screen.
 */
extern uint8_t dog_buffer[DOG_PAGE_HEIGHT][DOG_WIDTH];

/*----------------------------------------------------------------------------*/
/* CONSTANTS                                                                  */
/*----------------------------------------------------------------------------*/
/**
 * @var const unsigned char dog_character_set[]
 * @brief Lookup-table containing 5x7 bitmap representations of ASCII characters
 *        (and a magical surprise character).
 */
const unsigned char dog_character_set[] =
{
	0x00, 0x00, 0x00, 0x00, 0x00,// (space)
	0x00, 0x00, 0x5F, 0x00, 0x00,// !
	0x00, 0x07, 0x00, 0x07, 0x00,// "
	0x14, 0x7F, 0x14, 0x7F, 0x14,// #
	0x24, 0x2A, 0x7F, 0x2A, 0x12,// $
	0x23, 0x13, 0x08, 0x64, 0x62,// %
	0x36, 0x49, 0x55, 0x22, 0x50,// &
	0x00, 0x05, 0x03, 0x00, 0x00,// '
	0x00, 0x1C, 0x22, 0x41, 0x00,// (
	0x00, 0x41, 0x22, 0x1C, 0x00,// )
	0x08, 0x2A, 0x1C, 0x2A, 0x08,// *
	0x08, 0x08, 0x3E, 0x08, 0x08,// +
	0x00, 0x50, 0x30, 0x00, 0x00,// ,
	0x08, 0x08, 0x08, 0x08, 0x08,// -
	0x00, 0x60, 0x60, 0x00, 0x00,// .
	0x20, 0x10, 0x08, 0x04, 0x02,// /
	0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
	0x00, 0x42, 0x7F, 0x40, 0x00,// 1
	0x42, 0x61, 0x51, 0x49, 0x46,// 2
	0x21, 0x41, 0x45, 0x4B, 0x31,// 3
	0x18, 0x14, 0x12, 0x7F, 0x10,// 4
	0x27, 0x45, 0x45, 0x45, 0x39,// 5
	0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
	0x01, 0x71, 0x09, 0x05, 0x03,// 7
	0x36, 0x49, 0x49, 0x49, 0x36,// 8
	0x06, 0x49, 0x49, 0x29, 0x1E,// 9
	0x00, 0x36, 0x36, 0x00, 0x00,// :
	0x00, 0x56, 0x36, 0x00, 0x00,// ;
	0x00, 0x08, 0x14, 0x22, 0x41,// <
	0x14, 0x14, 0x14, 0x14, 0x14,// =
	0x41, 0x22, 0x14, 0x08, 0x00,// >
	0x02, 0x01, 0x51, 0x09, 0x06,// ?
	0x32, 0x49, 0x79, 0x41, 0x3E,// @
	0x7E, 0x11, 0x11, 0x11, 0x7E,// A
	0x7F, 0x49, 0x49, 0x49, 0x36,// B
	0x3E, 0x41, 0x41, 0x41, 0x22,// C
	0x7F, 0x41, 0x41, 0x22, 0x1C,// D
	0x7F, 0x49, 0x49, 0x49, 0x41,// E
	0x7F, 0x09, 0x09, 0x01, 0x01,// F
	0x3E, 0x41, 0x41, 0x51, 0x32,// G
	0x7F, 0x08, 0x08, 0x08, 0x7F,// H
	0x00, 0x41, 0x7F, 0x41, 0x00,// I
	0x20, 0x40, 0x41, 0x3F, 0x01,// J
	0x7F, 0x08, 0x14, 0x22, 0x41,// K
	0x7F, 0x40, 0x40, 0x40, 0x40,// L
	0x7F, 0x02, 0x04, 0x02, 0x7F,// M
	0x7F, 0x04, 0x08, 0x10, 0x7F,// N
	0x3E, 0x41, 0x41, 0x41, 0x3E,// O
	0x7F, 0x09, 0x09, 0x09, 0x06,// P
	0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
	0x7F, 0x09, 0x19, 0x29, 0x46,// R
	0x46, 0x49, 0x49, 0x49, 0x31,// S
	0x01, 0x01, 0x7F, 0x01, 0x01,// T
	0x3F, 0x40, 0x40, 0x40, 0x3F,// U
	0x1F, 0x20, 0x40, 0x20, 0x1F,// V
	0x7F, 0x20, 0x18, 0x20, 0x7F,// W
	0x63, 0x14, 0x08, 0x14, 0x63,// X
	0x03, 0x04, 0x78, 0x04, 0x03,// Y
	0x61, 0x51, 0x49, 0x45, 0x43,// Z
	0x00, 0x00, 0x7F, 0x41, 0x41,// [
	0x02, 0x04, 0x08, 0x10, 0x20,// "\"
	0x41, 0x41, 0x7F, 0x00, 0x00,// ]
	0x04, 0x02, 0x01, 0x02, 0x04,// ^
	0x40, 0x40, 0x40, 0x40, 0x40,// _
	0x00, 0x01, 0x02, 0x04, 0x00,// `
	0x20, 0x54, 0x54, 0x54, 0x78,// a
	0x7F, 0x48, 0x44, 0x44, 0x38,// b
	0x38, 0x44, 0x44, 0x44, 0x20,// c
	0x38, 0x44, 0x44, 0x48, 0x7F,// d
	0x38, 0x54, 0x54, 0x54, 0x18,// e
	0x08, 0x7E, 0x09, 0x01, 0x02,// f
	0x08, 0x14, 0x54, 0x54, 0x3C,// g
	0x7F, 0x08, 0x04, 0x04, 0x78,// h
	0x00, 0x44, 0x7D, 0x40, 0x00,// i
	0x20, 0x40, 0x44, 0x3D, 0x00,// j
	0x00, 0x7F, 0x10, 0x28, 0x44,// k
	0x00, 0x41, 0x7F, 0x40, 0x00,// l
	0x7C, 0x04, 0x18, 0x04, 0x78,// m
	0x7C, 0x08, 0x04, 0x04, 0x78,// n
	0x38, 0x44, 0x44, 0x44, 0x38,// o
	0x7C, 0x14, 0x14, 0x14, 0x08,// p
	0x08, 0x14, 0x14, 0x18, 0x7C,// q
	0x7C, 0x08, 0x04, 0x04, 0x08,// r
	0x48, 0x54, 0x54, 0x54, 0x20,// s
	0x04, 0x3F, 0x44, 0x40, 0x20,// t
	0x3C, 0x40, 0x40, 0x20, 0x7C,// u
	0x1C, 0x20, 0x40, 0x20, 0x1C,// v
	0x3C, 0x40, 0x30, 0x40, 0x3C,// w
	0x44, 0x28, 0x10, 0x28, 0x44,// x
	0x0C, 0x50, 0x50, 0x50, 0x3C,// y
	0x44, 0x64, 0x54, 0x4C, 0x44,// z
	0x00, 0x08, 0x36, 0x41, 0x00,// {
	0x00, 0x00, 0x7F, 0x00, 0x00,// |
	0x00, 0x41, 0x36, 0x08, 0x00,// }
	0x08, 0x08, 0x2A, 0x1C, 0x08,// ->
	0x08, 0x1C, 0x2A, 0x08, 0x08, // <-
        0x06, 0x1E, 0x1C, 0x1E, 0x06, //Surprise
};

/*----------------------------------------------------------------------------*/
/* STATIC VARIABLES                                                           */
/*----------------------------------------------------------------------------*/
/**
 * @var static uint8_t page
 * @brief Used to store the current LCD page; should range from 0-7.
 *
 * @var static uint8_t col
 * @brief Used to store the current LCD column; should range from 0-126 (note 
 *        that we do not use the entire 128 columns because we want to ensure 
 *        that no character is split between lines).
 */
static uint8_t page = 0, col = 0; /* Used to store the current column and page
                                   * for puchar function. It should be noted 
                                   * that putchar operates on pages, not 
                                   * individual pixel rows, so page is a number
                                   * from 0-7.
                                   */
                               
/*----------------------------------------------------------------------------*/
/* FUNCTIONS                                                                  */
/*----------------------------------------------------------------------------*/                                                           
int putchar(int c)
{
  int table_start;    /* Used as a starting index to the lookup table */
  int table_end;      /* Lookup table ending index to the lookup table */
  int i;

  if(c == '\n')      /* Detect newline character */
  {
   while(col < DOG_WIDTH)
     dog_buffer[page][col++] = 0;  /* If newline character, clear rest of line */

   ++ page;                     /* Then increment the page */
   col = 0;                    /* Next reset the column (ie. carriage return)*/
   return 0;                   /* Return; nothing to do */
  }

  /* Note that the following two condition checks not only check for bounds, but
   * allow for character wrap-around should a bound be reached.
   */

  if(col+5 >= DOG_CHAR_WIDTH)       /* Check if column index has reached max.*/
  {
    col = 0;                  /* If so, reset the column */
    ++page;                   /* Increment the page */
  }

  if(page >= DOG_CHAR_HEIGHT)     /*Check if page index has reached the last page.*/
  {
   page = 0;                  /* If so, move to top of display */
  }

  table_start = 5*(c - ' ');   /* Determine where to begin table lookup. */

  table_end = table_start + 5; /* End location of table lookup will be at
                                * a 5-byte offset.
                                */

  /* Place each byte cooresponding to character 'c' in the buffer. */
  for(i = table_start; i < table_end; ++i, ++col)
  {
    dog_buffer[page][col] |= dog_character_set[i];
  }

  ++col;                       /* Increment col once more for proper spacing */

  if(col < DOG_CHAR_WIDTH) dog_buffer[page][col] |= 0;/* If not end of line, add
                                                   * 1 column wide space between
                                                   * letters.
                                                   */

  return c;
} /* putchar */

int8_t dog_set_column(uint8_t new_col)
{
 if((new_col + 5) >= DOG_CHAR_WIDTH) return -1;  /* We want to make sure that there
                                              * is room for an entire letter
                                              * hence the addition of 5 to the
                                              * value in new_col
                                              */
 else
 {
   col = new_col;
   return 0;
 }
}

int8_t dog_set_page(uint8_t new_page)
{
 if(new_page >= DOG_CHAR_HEIGHT) return -1;
 else
 {
   page = new_page;
   return 0;
 }
}

int8_t dog_putchar_select(uint8_t new_row, uint8_t new_col, char c)
{
  uint8_t old_col, old_page;
  uint8_t top_page_height, bottom_page_height;
  uint16_t table_start, table_end, i;

  /* Ensure that provided pixels are within range */
  if((new_row + 7) >= DOG_HEIGHT) return -1;
  if((new_col + 5) >= DOG_CHAR_WIDTH) return -1;

  old_col = col;
  old_page = page;

  col = new_col;
  page = new_row>>3;
  bottom_page_height = new_row % DOG_PAGE_HEIGHT;
  top_page_height = 8-bottom_page_height;
  
  /* locate character in lookup table */
  table_start = 5*(c - ' ');
  table_end = table_start + 5;
  
  /* Place character in buffer */
  for(i = table_start; i < table_end; ++i, ++col)
  {
    dog_buffer[page][col] |= dog_character_set[i]<<bottom_page_height;
    dog_buffer[page+1][col] |= dog_character_set[i]>>top_page_height;
  }

  ++col;                       /* Increment col once more for proper spacing */

  if(col < DOG_CHAR_WIDTH)
  {
    dog_buffer[page][col] |= 0;         /* If not end of line, add     */
    dog_buffer[++page][col] |= 0;       /* 1 column wide space between */
  }                                    /* letters.                    */

  page = old_page;
  col = old_col;
  return c;
}

/* @} */ /* DOGM128_characters_source */