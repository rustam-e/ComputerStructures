/* f3d_uart.c --- 
 * 
 * Filename: f3d_uart.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Sep 26 07:05:26 2013
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

#include <stm32f30x.h>
#include <f3d_led.h>

void f3d_uart_init(void) {
  // Initialization routines related to UART1

  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE); //enable the GPOIC clock

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC , &GPIO_InitStructure);	//PC4 PC5 configurations

  GPIO_PinAFConfig(GPIOC,4,GPIO_AF_7);
  GPIO_PinAFConfig(GPIOC,5,GPIO_AF_7);

  USART_InitTypeDef USART_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1 ,&USART_InitStructure);
  USART_Cmd(USART1 , ENABLE);		//UART1 configuration
}

int putchar(int c) {
  while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == (uint16_t)RESET);
USART_SendData(USART1, c);
  // 
  // take a character as input, check to see if the transmitter is busy
  // and then write the character when the transmitter is available
  //
 return 0;
} 

int getchar(void) {
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == (uint16_t)RESET);
  int c = USART_ReceiveData(USART1);
  //
  //read characters from UART the receiver and return it
  //
}

void putstring(char *s) {
  while (getchar()) {
    *s = putchar(getchar());
    *s++;
  }
  *s = '\0';

  //
  //
  //
}



/* f3d_uart.c ends here */
