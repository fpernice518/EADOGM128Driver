/*
 * @file   DOGM128_common.c  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Source file which contains the screen buffer and functions used
 *         to send information to and from the screen. <br>
 *
 * @defgroup DOGM128_common Common
 * @{
 *
 * This file contains various SPI macros, common constants, common typedefs, and 
 * various function prototypes which interface with the DOG module itself. The 
 * library is organized in such a way that the user should not have to 
 * interface with any of the macros in this file dealing with SPI communication.
 * The user will mostly only find the function prototypes in this file of 
 * interest and perhaps the constants and typedefs should they choose to expand
 * upon the library.
 *
 */
 
/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_common.h"

/*----------------------------------------------------------------------------*/
/* GLOBAL DATA                                                                */
/*----------------------------------------------------------------------------*/
/**
 * @var uint8_t dog_buffer[DOG_PAGE_HEIGHT][DOG_WIDTH]
 * @brief External buffer used for storing screen contents before sending data
 *        to screen.
 */
uint8_t dog_buffer[DOG_PAGE_HEIGHT][DOG_WIDTH];

/*----------------------------------------------------------------------------*/
/* FUNCTIONS                                                                  */
/*----------------------------------------------------------------------------*/

void dog_init(dog_display_mode_t display_mode, uint8_t contrast)
{
  DOG_INIT_SPI();
  DOG_ASSERT_RESET();
  DOG_UNASSERT_RESET();
  DOG_SLAVE_SELECT();
  DOG_SEND_COMMAND();
  
  display_mode &= 1;            /* mask out all but LSB */
  contrast &= 63;               /* mask out 2 MSB's */
  
  DOG_SPDR = 0x40; /* start at line 0 */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SPDR = 0xA1; /* ADC reverse (for 6:00 viewing) */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SPDR = 0xC0; /* Normal common output */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SPDR = (0xA6 | display_mode); /* display_mode = 0 => DOG_NORMAL_DISPLAY. 
                                 * display_mode = 1 => inverted display. 
                                 */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SPDR = 0xA2; /* LCD drive voltage bias set 1/9 */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SPDR = 0x2F; /* Power control: booster, regulator, and follower on
                  (for 3.3V operation).
                  */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  /* Booster adjustment must be done in 2 SPI writes */
  DOG_SPDR = 0xF8; /* Booster Set Ratio 4x */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SPDR = 0x00; /* Booster Set Ratio 4x */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SPDR = 0x27; /* Voltage Regulator Set */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  /* Contrast adjustment must be done in 2 SPI writes */
  DOG_SPDR = 0x81; /* Send Command to adjust contrast */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SPDR = contrast; /* Adjust contrast */  //originally 0x16
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  /* Static indicator set must be done in 2 SPI writes */
  DOG_SPDR = 0xAC; /* static indicator set */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SPDR = 0x00; /* static indicator set */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SPDR = 0xAF; /* Finally, turn the display on */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));
 
  dog_clear_display(); /* clear any random data on the screen */
  DOG_SLAVE_DESELECT();    /* Deselect the slave */
}

void dog_clear_display(void)
{
  /* start off in top-left corner */
  uint8_t page = 0;
  uint8_t col = 0;

  /* Select the LCD */
  DOG_SLAVE_SELECT();
  
  /* Loop across all pages. Picture each page as a line on a typewriter */
  for(page = 0; page < DOG_PAGE_HEIGHT; ++page)
  {
    DOG_SEND_COMMAND();   /* Ready display to receive commands */
    DOG_SPDR = 0xB0 | page;   /* Send over page number to write to */
    while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));
    
    /* Loop across all columns until the page (line) is filled */
    for(col = 0; col < DOG_WIDTH; ++col)
    {
      DOG_SEND_DATA();    /* Ready the display to receive data */
      DOG_SPDR = 0;           /* Send zero to clear */
      while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));
    }
    /* Now that the end line (page) was reached, we must advance to the next
     * page. Note that we did not need to advance the column address manually;
     * the LCD controller does that automatically. Again, picture an old
     * typewriter whose carriage must be returned upon reaching the end of a
     * line. Now that we've reached the end of line, we must reset the carriage
     * (column) back to the left side of the display. This takes two commands.
     */
    DOG_SEND_COMMAND(); /* Ready display to receive commands */
    DOG_SPDR = 0x10;        /* Send upper column address, 0*/
    while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));
    DOG_SPDR = 0x00;        /* Send lower column address, 0*/
    while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));
  }
  
  DOG_SEND_COMMAND();   /* Ready the display to receive a command */
  DOG_SPDR = 0xB0;          /* Go back to 0th page */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SLAVE_DESELECT();     /* Deselect the screen */
}

void dog_print_buffer(void)
{
  /* start off in top-left corner */
  uint8_t page = 0;
  uint8_t col = 0;

  /* Select the screen */
  DOG_SLAVE_SELECT();

  /* Loop across all pages. Picture each page as a line on a typewriter */
  for(page = 0; page < DOG_PAGE_HEIGHT; ++page)
  {
    DOG_SEND_COMMAND();            /* Ready display to receive commands */
    DOG_SPDR = 0xB0 | page;            /* Send over page number to be written */
    while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

    /* Loop across all columns until the page (line) is filled */
    for(col = 0; col < DOG_WIDTH; ++col)
    {
      DOG_SEND_DATA();                 /* Ready the display to receive data */
      DOG_SPDR = dog_buffer[page][col];    /* Send buffer data */
      while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));
    }
    /* Now that the end line (page) was reached, we must advance to the next
     * page. Note that we did not need to advance the column address manually;
     * the LCD controller does that automatically. Again, picture an old
     * typewriter whose carriage must be returned upon reaching the end of a
     * line. Now that we've reached the end of line, we must reset the carriage
     * (column) back to the left side of the display. This takes two commands.
     */
    DOG_SEND_COMMAND();            /* Ready display to receive commands */
    DOG_SPDR = 0x10;                         /* Send upper column address, 0*/
    while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));
    DOG_SPDR = 0x00;                         /* Send lower column address, 0*/
    while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));
  }
  DOG_SEND_COMMAND();         /* Ready the display to receive a command */
  DOG_SPDR = 0xB0;                                   /* Go back to 0th page */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SLAVE_DESELECT();                             /* Deselect the screen */
}

void dog_clear_buffer(void)
{
  uint8_t page = 0;
  uint8_t col = 0;

 
  /* Loop across all pages. */
  for(page = 0; page < DOG_PAGE_HEIGHT; ++page)
  {
    /* Loop across all columns */
    for(col = 0; col < DOG_WIDTH; ++col)
    {
      dog_buffer[page][col] = 0;    /* Send buffer data */
    }
  }
}

void dog_set_contrast(uint8_t contrast)
{
  contrast &= 63;                /*mask out 2 MSB's */
  
  
  DOG_SLAVE_SELECT();                /* Select the LCD */
  DOG_SEND_COMMAND();            /* Ready display to receive commands */
  
  /* Contrast adjustment must be done in 2 SPI writes */
  
  DOG_SPDR = 0x81;                   /* Send Command to adjust contrast */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));

  DOG_SPDR = contrast;               /* Adjust contrast */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));
  
  DOG_SLAVE_DESELECT();              /* Deselect the screen */
}

void dog_invert_pixels(dog_display_mode_t display_mode)
{

  DOG_SLAVE_SELECT();                /* Select the LCD */
  DOG_SEND_COMMAND();            /* Ready display to receive commands */
  
  display_mode &= 1;             /* mask out all but LSB */
  DOG_SPDR = (0xA6 | display_mode);  /* display_mode = 0 => DOG_NORMAL_DISPLAY. 
                                  * display_mode = 1 => inverted display. 
                                  */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));
  
  DOG_SLAVE_DESELECT();              /* Deselect the screen */

}

void dog_power(dog_power_state_t state)
{

  DOG_SLAVE_SELECT();                /* Select the LCD */
  DOG_SEND_COMMAND();            /* Ready display to receive commands */
  
  DOG_SPDR = (0xAE | state);          /* state = 0 => off. 
                                  * stae = 1 => on. 
                                  */
  while (!(DOG_SPSR & (1<<DOG_SPIF_BIT)));
  
  DOG_SLAVE_DESELECT();              /* Deselect the screen */

}

