/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: Lili Wen(liliwen)
 * Maintainer: group 10 members
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 10/1/2013
 *           By: Li, Ke
 *     Update #: 2
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <stdio.h>
#include <mywc.h>	// Pull in include files for the local drivers 

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) { 
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0); //To prevent the library from buffing I/O

  f3d_uart_init(); //initialization of f3d_uart

  while (1) {
    mywc();
  } 
  //while
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
