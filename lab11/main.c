/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */
#include <stm32f30x.h>
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_button.h>
#include <f3d_systick.h>
#include <f3d_delay.h>
#include <stdio.h>

int main(){
  int button;	
  f3d_button_init();
  delay(10);
  f3d_led_init();
  delay(10);
  f3d_uart_init();
  delay(10);
  f3d_systick_init();
  delay(10);
  
  button = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
  
  while(1){

  }//echo
  return 0;
 putchar(getchar()); 
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif
