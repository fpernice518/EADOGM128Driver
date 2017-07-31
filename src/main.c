#include <iom128.h>
#include <stdio.h>
#include "DOGM128_driver.h"

void main(void)
{
  DDRB = 0x37;    /* Set SS_bar, MOSI, SCK, reset, and A0 to outputs,
                   * leave rest alone. 
                   */

  dog_init(DOG_INVERTED_DISPLAY,0x16); /* Initialize Display */
     
  printf("Line %d: %c Hello World",1, 128); /* Print Line */
  
  dog_draw_rectangle(0,8,127,63,0,'s');             /* Draw a rectangle */
  
  /* Print the "LATEX" Logo */
  dog_putchar_select(25, 20, 'L');
  dog_putchar_select(23, 26, 'A');
  dog_putchar_select(25, 32, 'T');
  dog_putchar_select(29, 38, 'E');
  dog_putchar_select(25, 44, 'X');

  dog_set_page(6);                                  /* Set printing page */
  dog_set_column(20);                               /* Set printing column */
  printf("Hello Rectangle");                        /* Print "Hello Rectangle */

  dog_print_buffer();                  /* IMPORTANT: Print buffer to screen */

  while(1);

}




