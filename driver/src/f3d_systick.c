/* f3d_systick.c --- 
 * 
 * Filename: f3d_systick.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Nov 14 07:57:37 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
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

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

#include <f3d_systick.h>
#include <f3d_led.h> 
#include <f3d_button.h>
#include <f3d_uart.h>
#include <stdio.h>
#include <queue.h>

volatile int systick_flag = 0;
extern queue_t txbuf;
extern queue_t rxbuf;
int i = 0, j = 0;


void f3d_systick_init(void) {
  SysTick_Config(SystemCoreClock/100);
  
}

void SysTick_Handler(void) {
  if (!get_button_state()){
    f3d_led_off(i);
    i = (i + 1) % 8;
    f3d_led_on(i);
  }else{
    j ++;
    if (j == 10){
      f3d_led_off(i);
      i = (i + 1) % 8;
      f3d_led_on(i);
      j = 0;
    }
  }
  if (!queue_empty(&txbuf)){
    flush_uart();
  }
}

/* f3d_systick.c ends here */
