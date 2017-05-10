/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: liliwen
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
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
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_delay.h>     
#include <f3d_lcd_sd.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_led.h>  
#include <stdio.h>
#include <stdlib.h>

int main(void) { 
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_lcd_init();
  f3d_uart_init();
  f3d_gyro_init();

  printf("Reset\n");
  
  int x, y, z, i, j;
  int input;
  float data[3];
 
  f3d_lcd_fillScreen(WHITE);

  f3d_lcd_drawString(21,80,"X",RED,WHITE);
  f3d_lcd_drawString(62,80,"Y",BLUE,WHITE);
  f3d_lcd_drawString(103,80,"Z",GREEN,WHITE);
  f3d_lcd_drawString(10, 10, "X: ", 133, WHITE);
  f3d_lcd_drawString(10, 30, "Y: ", 133, WHITE);
  f3d_lcd_drawString(10, 50, "Z: ", 133, WHITE);

  while (1){
    f3d_gyro_getdata(data);
     

    float x=data[0];
    float y=data[1];
    float z=data[2];
    
    char a[11];
    char b[11];
    char c[11];
    
    sprintf(a, "%f", x);
    sprintf(b, "%f", y);
    sprintf(c, "%f", z);

    f3d_lcd_drawString(30, 10, a, 133, WHITE);
    f3d_lcd_drawString(30, 30, b, 133, WHITE);
    f3d_lcd_drawString(30, 50, c, 133, WHITE);
    // x axis w/ width 20
    
    if(x >= 0){ //positive value of x
      for(i=89;i<89+x;i++){ 
	for(j=10;j<30;j++){ 
	  f3d_lcd_drawPixel(j,i,RED);
	}
      }
      for(i=89;i<89+x;i++){ //clear 
	for(j=10;j<30;j++){ 
	  f3d_lcd_drawPixel(j,i,WHITE);
	}
      }
    }
    else if (x < 0){ // neg. val of x
      for(i=79;i>79+x;i--){
	for(j=10;j<30;j++){ 
	  f3d_lcd_drawPixel(j,i,RED);
	}
      }
      for(i=79;i>79+x;i--){
	for(j=10;j<30;j++){ 
	  f3d_lcd_drawPixel(j,i,WHITE);
	}
      }
    }

    // y axis

    if(y >= 0){ //positive value of x 
      for(i=89;i<89+y;i++){ 
	for(j=50;j<70;j++){ 
	  f3d_lcd_drawPixel(j,i,BLUE);
	}
      }
      for(i=89;i<89+y;i++){ //clear 
	for(j=50;j<70;j++){ 
	  f3d_lcd_drawPixel(j,i,WHITE);
	}
      }
    }
    else if (y < 0){ // neg. val of y
      for(i=79;i>79+y;i--){
	for(j=50;j<70;j++){ 
	  f3d_lcd_drawPixel(j,i,BLUE);
	}
      }
      for(i=79;i>79+y;i--){
	for(j=50;j<70;j++){ 
	  f3d_lcd_drawPixel(j,i,WHITE);
	}
      }
    }

    // z axis

    if(z >= 0){ //positive value of z 
      for(i=89;i<89+z;i++){ 
	for(j=90;j<110;j++){ 
	  f3d_lcd_drawPixel(j,i,GREEN);
	}
      }
      for(i=89;i<89+z;i++){ //clear 
	for(j=50;j<110;j++){ 
	  f3d_lcd_drawPixel(j,i,WHITE);
	}
      }
    }
    else if (z < 0){ // neg. val of z
      for(i=79;i>79+z;i--){
	for(j=90;j<110;j++){ 
	  f3d_lcd_drawPixel(j,i,GREEN);
	}
      }
      for(i=79;i>79+z;i--){
	for(j=90;j<110;j++){ 
	  f3d_lcd_drawPixel(j,i,WHITE);
	}
      }
    }


  }// while
 


 
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif


/* main.c ends here */
