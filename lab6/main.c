/* main.c ---
*
* Filename: main.c
* Description:
* Author:
* Maintainer:
* Created: Thu Jan 10 11:23:43 2013
* Last-Updated:
* By:
* Update #: 0
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

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h> // Pull in include file for the local drivers
#include <f3d_uart.h> // Pull in include file for the local drivers
#include <stdio.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_conf.h>

// Simple looping delay function
void delay(void) {
  int i = 20000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
  int led_state = 0;
  GPIO_InitTypeDef GPIO_InitStructure;


  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  f3d_uart_init();
  f3d_led_init();
  printf("Lab6 Init\n");

  // Part 2.2 Assertions
  // This broken code contains an issue that will generate an assertion.
  // Uncomment and debug the code.

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  while (1) {
    // flash north (red) led
    if (led_state^=2) {
      f3d_led_on(1);
    }
    else {
      f3d_led_off(1);
    }
    // provide a delay for the flashing
    // Part 3.1.1 Printf Debugging
    /*
printf("led_state=%d\n",led_state);
*/
    delay();
  }
}

#ifdef USE_FULL_ASSERT

#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */

// Part 2.2 Assertions

  printf("Assertion Raised at line %d in file %s\n",line,file);

  while (1);
}
#endif

/* main.c ends here */
