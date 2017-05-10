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
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <stdio.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_spi.h>


#define TIMER 20000

int main(void) {
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_led_init();
  f3d_uart_init(); 
  f3d_gyro_init();

   //configure button A0
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
 

  
  printf("Reset\n");
  
  int button_state;
  int c;// x=0, y=1, z=2
  int input;
  float data[3];
  float userData;


  while (1) {
    f3d_led_all_off();
    f3d_gyro_getdata(data);
    button_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);

    if (button_state) {
      c = (c + 1) % 3;
    }
    //read characters from UART the receiver and return it
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != (uint16_t)RESET){
      input = getchar();
      switch (input) {
      case 'x':
	c = 1;
	break;
      case 'y':
	c = 0;
	break;
      case 'z':
	c = 2;
	break;
      }
    } 

    switch(c) { 
    case 0: 
      printf("%f",data[0]);
      break;
    case 1:
      printf("%f",data[1]);
      break;
    case 2:
      printf("%f",data[2]);
      break;
    }
    userData = Data[c];
    //turn on leds 
    //positive
    if (userData >= 5) {
      f3d_led_all_off();
      f3d_led_on(1);
      if (userData >= 35) {
	f3d_led_on(0);
	if (userData >= 65) {
	  f3d_led_on(7);
	  if (userData >= 95) {
	    f3d_led_on(6);
	  }
	}
      }
    }
    //negative
    if (userData < -5) {
      f3d_led_all_off();
      f3d_led_on(2);
      if (userData < -35) {
        f3d_led_on(3);
        if (userData < -65) {
          f3d_led_on(4);
          if (userData < -95) {
            f3d_led_on(5);
          }
        }
      }
    }//if
     
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
