/* main.c --- 
 * 
 * Filename: main.c
 * Description: lab4.
 * Author: Members from Group 10.
 * Maintainer: Members from Group 10.
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 25/9/2013
 *           By: Li, Ke
 *     Update #: NA
 * Keywords: board working.
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log: 
 *So now we have everything working. 
 * 
 */
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>

// Simple looping delay function
void delay(int i) {
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) { 
  GPIO_InitTypeDef GPIO_InitStructure;

  f3d_led_init();// initial the port and pins for the 8 leds

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure); //configure button A0

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|
			RCC_AHBPeriph_GPIOE, ENABLE);// enable the clock of port A and E

  int button_state;

  f3d_led_all_off();

  while (1) {
    int i;
    for (i = 0; i < 8 ; i++) {
      f3d_led_on(i);
      delay(6000000);
      button_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
      while (button_state) {
	delay(3);
        button_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
      }
      f3d_led_off(i);
    }
    f3d_led_all_on();
    delay(6000000);
    button_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
    while (button_state) {
      delay(3);
      button_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
    }
    f3d_led_all_off();
  }//while


}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
