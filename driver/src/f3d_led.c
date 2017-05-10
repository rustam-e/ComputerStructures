/* led.c --- 
 * 
 * Filename: led.c
 * Description: led initialization 
 * Author: Members from group 10.
 * Maintainer: Members from group 10.
 * Created: Thu Jan 10 10:53:06 2013
 * Last-Updated: 25/9/2013
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
 * Changed the if statements in on/off functions and added Init line in init function. 
 * 
 */

/* Code: */
#include <stm32f30x.h>
#include <f3d_led.h>

void f3d_led_init(void) {
  // initialize the port and pins for the 8 leds
  GPIO_InitTypeDef GPIO_InitStructure;
 
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_8; 

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  
  GPIO_Init(GPIOE, &GPIO_InitStructure);

}

void f3d_led_on(int led) {
  // enable the led specified by led parameter
  // led = 0-7 representing the 8 leds
  if (led == 0) {
    GPIOE->BSRR = GPIO_Pin_9;}
  if (led == 1) {
    GPIOE->BSRR = GPIO_Pin_10;}
  if (led == 2) {
    GPIOE->BSRR = GPIO_Pin_11;}
  if (led == 3) {
    GPIOE->BSRR = GPIO_Pin_12; }
  if (led == 4) {
    GPIOE->BSRR = GPIO_Pin_13;}
  if (led == 5) {
    GPIOE->BSRR = GPIO_Pin_14;}
  if (led == 6) {
    GPIOE->BSRR = GPIO_Pin_15;}
  if (led == 7) {
    GPIOE->BSRR = GPIO_Pin_8;}
}
 
void f3d_led_off(int led) {
  // disable the led specified by led parameter
  // led = 0-7 representing the 8 leds
  if (led == 0) {
    GPIOE->BRR = GPIO_Pin_9;}
  if (led == 1) {
    GPIOE->BRR = GPIO_Pin_10;}
  if (led == 2) {
    GPIOE->BRR = GPIO_Pin_11;}
  if (led == 3) {
    GPIOE->BRR = GPIO_Pin_12;}
  if (led == 4) {
    GPIOE->BRR = GPIO_Pin_13;}
  if (led == 5) {
    GPIOE->BRR = GPIO_Pin_14;}
  if (led == 6) {
    GPIOE->BRR = GPIO_Pin_15;}
  if (led == 7) {
    GPIOE->BRR = GPIO_Pin_8;}
} 

void f3d_led_all_on(void) {
  // turn on all 8 leds
  int i; 
  for (i = 0; i < 8; i++) {
    f3d_led_on(i);
  }
  
} 

void f3d_led_all_off(void) {
  // turn off all 8 leds
  int i;
  for (i = 0; i < 8; i++) {
    f3d_led_off(i);
  }
  
} 

/* led.c ends here */

