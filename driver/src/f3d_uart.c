
#include <stm32f30x.h>
#include <f3d_led.h>
#include <queue.h>
#include <f3d_uart.h>
#include <stm32f30x_misc.h>

queue_t rxbuf;
queue_t txbuf;


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

  NVIC_InitTypeDef NVIC_InitStructure;

  // Initialize the rx and tx queues
  init_queue(&rxbuf);
  init_queue(&txbuf);
  
  // Setup the NVIC priority and subpriority
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x08;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x08;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  // Enable the RX interrupt 
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

}
void USART1_IRQHandler(void) { //provide
  int data; 
  
  if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE)) {
    data = USART_ReceiveData(USART1);
    while (!enqueue(&rxbuf,data));
  }
  if (USART_GetFlagStatus(USART1,USART_FLAG_TXE)) {
    data = dequeue(&txbuf);
    if (data) {
      USART_SendData(USART1,data);
    }
    else {
      USART_ITConfig(USART1,USART_IT_TXE,DISABLE); 
    }
  }
}

int putchar(int c) {
  enqueue(&txbuf, c);
  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
  return 0;
  // 
  // take a character as input, check to see if the transmitter is busy
  // and then write the character when the transmitter is available
  //
}

int getchar(void) {
  return dequeue(&rxbuf);
  //
  //read characters from UART the receiver and return it
  //
}

void putstring(char *s) {
  while (*s != '\0') {
    putchar(*s);
    *s++;
  }

  //
  //
  //
}
void flush_uart(void) {
  USART_ITConfig(USART1,USART_IT_TXE,ENABLE); 
}

/* f3d_uart.c ends here */
