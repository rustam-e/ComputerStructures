/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
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
#include <glcdfont.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_led.h>  
#include <stdio.h>
#include <stdlib.h>
#include <f3d_accel.h>
#include <f3d_i2c.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <math.h>


float x,y,z;
float heading,pitch,roll,yaw;

void drawBar(float, float, float);

int main(void) { 
  
  f3d_i2c1_init(); //I2C1 ACCEL MAG NUNCHUCK
  delay(100);
  f3d_accel_init();
  delay(100);
  f3d_mag_init();
  delay(100);
  f3d_nunchuk_init();
  delay(100);
  f3d_lcd_init(); //LCD GYRO
  delay(10);
  f3d_gyro_init();
  delay(10);
  //  f3d_uart_init();

  float data[3];		//gyrodata
  float accData[3];		//accel_data
  float magData[3];		//mag
  float i,j,g; 		//xyz axis, ij index num, g-gravity
  nunchuk_t nk;
  nunchuk_t* pnk = &nk;
  int button;			//button z,c 
  char a[11],b[11],c[11],h[11];

  //  float alpha,beta,gamma;
  g = 9.81;
  
  



  f3d_lcd_fillScreen(WHITE);

  while (1){

    f3d_nunchuk_read(&nk);
    //button = pnk[5];
      f3d_lcd_drawString(20, 100, "X      Y      Z", BLACK, WHITE);
      f3d_lcd_drawString(20, 120, "pitch  roll  yaw", BLACK, WHITE);
      f3d_lcd_drawString(20, 140, "heading", BLACK, WHITE);      
    if (nk.c == 0 && nk.z == 0) {      //none button print gyro
      f3d_gyro_getdata(data);
      x = data[0];
      y = data[1];
      z = data[2];

      sprintf(a, "%f", x);
      sprintf(b, "%f", y);
      sprintf(c, "%f", z);
      f3d_lcd_drawString(30, 10, a, BLACK, WHITE);
      f3d_lcd_drawString(30, 30, b, BLACK, WHITE);
      f3d_lcd_drawString(30, 50, c, BLACK, WHITE);

      //drawBar
      drawBar(x, y, z);

    }
    if (nk.c == 1 && nk.z == 0) { //press button c for tilt angle
      //clear
      f3d_lcd_drawString(30, 10, a, WHITE, WHITE);
      f3d_lcd_drawString(30, 30, b, WHITE, WHITE);
      f3d_lcd_drawString(30, 50, c, WHITE, WHITE);

      f3d_accel_read(accData);
      x = accData[0];
      y = accData[1];
      z = accData[2];
					// *180/pi convert radian to degree
      pitch = asin(x/g)*180.0/M_PI;
      roll = asin(y/g)*180.0/M_PI;
      yaw = (acos(z/g)-M_PI/2)*180.0/M_PI;

      sprintf(a, "%f", pitch); //pitch:
      sprintf(b, "%f", roll);  // roll: 
      sprintf(c, "%f", yaw);  //yaw:

      f3d_lcd_drawString(30, 10, a, BLACK, WHITE);
      f3d_lcd_drawString(30, 30, b, BLACK, WHITE);
      f3d_lcd_drawString(30, 50, c, BLACK, WHITE);
      drawBar(pitch,roll,yaw);

    }
    if (nk.c == 0 && nk.z == 1) { //press button z for compass
      f3d_lcd_drawString(30, 10, h, WHITE, WHITE); //CLEAR
      f3d_mag_read(magData);
      f3d_accel_read(accData);
      x = magData[0];			//x,y,z magnetic sensor measurements
      y = magData[1];
      z = magData[2];
      pitch = asin(-accData[0]);	//radian
      roll = asin(accData[1]/(cos(pitch)));

      heading = atan((x*(sin(pitch))*(sin(roll)) + y*(cos(roll)) 
		      - z*(sin(roll))*(cos(pitch)))
		     /(x*(cos(pitch)) + z*(sin(pitch))));

      heading = heading * 180.0/M_PI + 180;	// convert radian to degree
      sprintf(h, "%f", heading); //heading
      
      char n[11];
      sprintf(n, "%d: N, %d: S", 0, 180);
      f3d_lcd_drawString(30, 10, h, YELLOW, WHITE); 
      f3d_lcd_drawString(30, 30, n, BLACK, WHITE); 
    }
			 
    if (nk.z == 1 && nk.c == 1) { //press button c+z for nunchuk tilt angle
      //clear
      f3d_lcd_drawString(30, 10, a, WHITE, WHITE);
      f3d_lcd_drawString(30, 30, b, WHITE, WHITE);
      f3d_lcd_drawString(30, 50, c, WHITE, WHITE);

      //convert the range from -512 to 511
      x = nk.ax-512.0;
      y = nk.ay-512.0;
      z = nk.az-512.0;
      pitch = atan(x/(sqrt(y*y + z*z))) * 180.0/M_PI;
      roll = atan(y/(sqrt(x*x + z*z))) * 180.0/M_PI;
      yaw = (acos(z/512.0)-M_PI_2) * 180.0/M_PI;

      sprintf(a, "%f", pitch); //asdfadf
      sprintf(b, "%f", roll);
      sprintf(c, "%f", yaw);
      f3d_lcd_drawString(30, 10, a, BLACK, WHITE);
      f3d_lcd_drawString(30, 30, b, BLACK, WHITE);
      f3d_lcd_drawString(30, 50, c, BLACK, WHITE);
      drawBar(pitch,roll,yaw);
      
    }
  }  
  
}

 
void drawBar(float x, float y, float z){
  int i, j;
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
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif


/* main.c ends here */
