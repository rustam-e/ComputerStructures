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
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include <stdio.h>
#include <f3d_delay.h>
#include <math.h>
#include <stdint.h>
#include <fcntl.h>

//bmp

struct bmpfile_magic {
  unsigned char magic [2];
};

struct bmpfile_header {
  uint32_t filesz ;
  uint16_t creator1 ;
  uint16_t creator2 ;
  uint32_t bmp_offset ;
};

typedef struct {
  uint32_t header_sz ;
  int32_t width ;
  int32_t height ;
  uint16_t nplanes ;
  uint16_t bitspp ;
  uint32_t compress_type ;
  uint32_t bmp_bytesz ;
  int32_t hres;
  int32_t vres;
  uint32_t ncolors ;
  uint32_t nimpcolors ;
} BITMAPINFOHEADER ;

typedef struct { // little endian byte order
  uint8_t b;
  uint8_t g;
  uint8_t r;
} bmppixel; 		//BMP File Structures

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

FATFS Fatfs;		/* File system object */
FIL Fil;		/* File object */
BYTE Buff[128];		/* File read buffer */

int main(void) { 
  char footer[20];
  int count=0;
  int i;

  FRESULT rc;			/* Result code */
  DIR dir;			/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br;
  unsigned int retval;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  delay(100);
  f3d_lcd_init();
  delay(100);
  f3d_delay_init();
  delay(100);
  f3d_rtc_init();
  delay(100);
  f3d_i2c1_init();
  delay(100);
  f3d_accel_init();
  delay(100);
  f3d_nunchuk_init();
  delay(100);

  f_mount(0, &Fatfs);		/* Register volume work area (never fails) */

  f3d_lcd_fillScreen(WHITE);

  struct bmpfile_magic magic;
  struct bmpfile_header header ;
  BITMAPINFOHEADER info;

  int f,j;
  uint16_t red, green, blue, color;
  bmppixel pixel;
  nunchuk_t nk;
  nunchuk_t* pnk = &nk;
  int button;			//button z,c 
  char a[11],b[11],c[11],h[11];
  float data[3];		
  float accData[3];		
  float magData[3];		
  while(1) {  
    f3d_nunchuk_read(&nk);
    // if (nk.c == 0 && nk.z == 0) { 
    //f3d_accel_read(accData);}
  

    if (nk.c == 0 && nk.z == 0) {
      //    f3d_lcd_drawString(30, 30, "whatever", WHITE, BLACK);
      printf("\nOpening file\n");
      f_open(&Fil, "smiley2.bmp", FA_READ);
    
      f_read(&Fil, (void *) &magic, 2, &br);
      printf ("Magic %c%c\n", magic.magic [0], magic.magic [1]);
      f_read(&Fil, (void *) &header , sizeof(header), &br);
      printf ("file size %d offset %d\n", header.filesz, header.bmp_offset);
      f_read(&Fil, (void *) &info, sizeof(info), &br);
      printf ("Width %d Height %d, bitspp %d\n", info.width, info.height, info.bitspp);
    
      bmppixel row_data[info.width];
      for (i = 0; i < info.width;i++) {
	f = f_read(&Fil, (void *) &row_data, sizeof(row_data), &br);
	for (j = 0; j < info.height; j++) {
	  pixel = row_data[j];
	  red = ((pixel.r >> 3) << 11);
	  green = ((pixel.g >> 3) << 5);
	  blue = (pixel.b >> 3);
	  color = red | green | blue;
	  f3d_lcd_drawPixel(i,j,color);
	}
      }
      f_close (&Fil);
    }
  
    if (nk.c == 0 && nk.z == 1) {
    
      printf("\nOpening file\n");
      f_open(&Fil, "guy2.bmp", FA_READ);
 
      f_read(&Fil, (void *) &magic, 2, &br);
      printf ("Magic %c%c\n", magic.magic [0], magic.magic [1]);
      f_read(&Fil, (void *) &header , sizeof(header), &br);
      printf ("file size %d offset %d\n", header.filesz, header.bmp_offset);
      f_read(&Fil, (void *) &info, sizeof(info), &br);
      printf ("Width %d Height %d, bitspp %d\n", info.width, info.height, info.bitspp);
  
      bmppixel row_data[info.width];
      for (i = 0; i < info.width;i++) {
	f = f_read(&Fil, (void *) &row_data, sizeof(row_data), &br);
	for (j = 0; j < info.height; j++) {
	  pixel = row_data[j];
	  red = ((pixel.r >> 3) << 11);
	  green = ((pixel.g >> 3) << 5);
	  blue = (pixel.b >> 3);
	  color = red | green | blue;
	  f3d_lcd_drawPixel(i,j,color);
	}
      }
      f_close (&Fil);
    }

    if (nk.c == 1 && nk.z == 0) {

      printf("\nOpening file\n");
      f_open(&Fil, "dex2.bmp", FA_READ);
 
      f_read(&Fil, (void *) &magic, 2, &br);
      printf ("Magic %c%c\n", magic.magic [0], magic.magic [1]);
      f_read(&Fil, (void *) &header , sizeof(header), &br);
      printf ("file size %d offset %d\n", header.filesz, header.bmp_offset);
      f_read(&Fil, (void *) &info, sizeof(info), &br);
      printf ("Width %d Height %d, bitspp %d\n", info.width, info.height, info.bitspp);
  
      bmppixel row_data[info.width];
      for (i = 0; i < info.width;i++) {
	f = f_read(&Fil, (void *) &row_data, sizeof(row_data), &br);
	for (j = 0; j < info.height; j++) {
	  pixel = row_data[j];
	  red = ((pixel.r >> 3) << 11);
	  green = ((pixel.g >> 3) << 5);
	  blue = (pixel.b >> 3);
	  color = red | green | blue;
	  f3d_lcd_drawPixel(i,j,color);
	}
      }
      f_close (&Fil);
    }
  }
  /*
  printf("\nOpen an existing file (message.txt).\n");
    rc = f_open(&Fil, "MESSAGE.TXT", FA_READ);
  if (rc) die(rc);
 
  printf("\nType the file content.\n");
  for (;;) {
    rc = f_read(&Fil, Buff, sizeof Buff, &br);	//Read a chunk of file 
    if (rc || !br) break;			// Error or end of file 
    for (i = 0; i < br; i++)		        // Type the data 
      putchar(Buff[i]);
  }
  if (rc) die(rc);
  
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
  
  printf("\nCreate a new file (hello.txt).\n");
  rc = f_open(&Fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
  if (rc) die(rc);
  
  printf("\nWrite a text data. (Hello world!)\n");
  rc = f_write(&Fil, "Hello world!\r\n", 14, &bw);
  if (rc) die(rc);
  printf("%u bytes written.\n", bw);
  
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
  
  printf("\nOpen root directory.\n");
  rc = f_opendir(&dir, "");
  if (rc) die(rc);
  
  printf("\nDirectory listing...\n");
  for (;;) {
    rc = f_readdir(&dir, &fno);		//Read a directory item 
    if (rc || !fno.fname[0]) break;	// Error or end of dir 
    if (fno.fattrib & AM_DIR)
      printf("   <dir>  %s\n", fno.fname);
    else
      printf("%8lu  %s\n", fno.fsize, fno.fname);
  }
  if (rc) die(rc);
  
  printf("\nTest completed.\n");

  rc = disk_ioctl(0,GET_SECTOR_COUNT,&retval);
  printf("%d %d\n",rc,retval);

  while (1);
  */

}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
