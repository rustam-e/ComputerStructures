//backup for main.c
/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: Group 10
 * Maintainer: Group 10
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 2013/12/7
 *           By: Li, Ke
 *     Update #: 1
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
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <f3d_systick.h>
#include <f3d_dac.h>
#include <f3d_timer2.h>
#include <f3d_systick.h>
#include <ff.h>
#include <diskio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TIMER 20000
#define AUDIOBUFSIZE 128

extern uint8_t Audiobuf[AUDIOBUFSIZE];
extern int audioplayerHalf;
extern int audioplayerWhole;

FATFS Fatfs;	/* File system object */
FIL fid;	/* File object */
BYTE Buff[512];	/* File read buffer */
int ret;

struct ckhd {
  uint32_t ckID;
  uint32_t cksize;
};

struct fmtck {
  uint16_t wFormatTag;
  uint16_t nChannels;
  uint32_t nSamplesPerSec;
  uint32_t nAvgBytesPerSec;
  uint16_t nBlockAlign;
  uint16_t wBitsPerSample;
};

void readckhd(FIL *fid, struct ckhd *hd, uint32_t ckID) {
  f_read(fid, hd, sizeof(struct ckhd), &ret);
  if (ret != sizeof(struct ckhd))
    exit(-1);
  if (ckID && (ckID != hd->ckID))
    exit(-1);
}

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

int largestoffour(int a[4]) {
  int e = 0;
  int i;
  for (i = 0; i < 4; i++) {
    if (a[i] > e) {
      e = a[i];
    }
  }
  return e;
}

int main(void) {

  FRESULT rc;	/* Result code */
  DIR dir;	/* Directory object */
  FILINFO fno;	/* File information object */
  UINT bw, br;
  unsigned int retval;
  int bytesread;
  //new variables
  nunchuk_t n;
  int buttonvalue = -1;
  int state = 0;
  int play = 0;
  int score = 0;
  int time;
  int yellow = 0;
  int blue = 0;
  int red = 0;
  int green = 0;
  int i, j;
  int delaytime;
  int showtime;
  int played = 0;
  int wins = 0;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  f3d_timer2_init();
  f3d_dac_init();
  f3d_delay_init();
  f3d_rtc_init();
  f3d_systick_init();
  //init lcd and nunchuk
  f3d_lcd_init();
  f3d_i2c1_init();
  f3d_nunchuk_init();

  printf("Reset\n");

  //showing basic interface.

  f3d_lcd_fillScreen(WHITE);
  /*
  for (i = 35; i <= 95; i++) {
    for (j = 30; j <= 50; j++) {
      f3d_lcd_drawPixel(i, j, BLUE);
    }
  }

  for (i = 15; i <= 35; i++) {
    for (j = 50; j <= 110; j++) {
      f3d_lcd_drawPixel(i, j, RED);
    }
  }

  for (i = 35; i <= 95; i++) {
    for (j = 110; j <= 130; j++) {
      f3d_lcd_drawPixel(i, j, GREEN);
    }
  }

  for (i = 95; i <= 115; i++) {
    for (j = 50; j <= 110; j++) {
      f3d_lcd_drawPixel(i, j, YELLOW);
    }
  }
  */
  while (1) {
    char s[5];
    int random;
    int count[4];
    int value;

    buttonvalue = -1;
    //calc the score
    if (played == 0) {
      score = 0;
    }
    else {
      score = (int) (wins*100/played);
    }
    
    f_mount(0, &Fatfs);
    f3d_nunchuk_read(&n);
    //changing difficulty
    if (n.jx < 150 && n.jx > 100 && n.jy > 150) {
      state = state + 1;
    }
    if (n.jx < 150 && n.jx > 100 && n.jy < 100) {
      state = state - 1;
    }
    if (state == 3) {
      state = -2;
    }
    if (state == -3) {
      state = 2;
    }
    //showing instruction & score.
    score = (int) (wins/played*100);
    f3d_lcd_drawString(10, 40, "press c", BLACK, WHITE);
    f3d_lcd_drawString(10, 50, "and", BLACK, WHITE);
    f3d_lcd_drawString(10, 60, "count the colors!", BLACK, WHITE);
    f3d_lcd_drawString(10, 80, "press z to reset", BLACK, WHITE);

    if (state == 0) {
      f3d_lcd_drawString(30, 120, "  <normal>  ", BLACK, WHITE);
      delaytime = 50;
      showtime = 3000;
    }
    if (state == 1) {
      f3d_lcd_drawString(30, 120, "   <hard>   ", BLACK, WHITE);
      delaytime = 25;
      showtime = 2000;
    }
    if (state == 2) {
      f3d_lcd_drawString(30, 120, " <veryhard> ", BLACK, WHITE);
      delaytime = 0;
      showtime = 1000;
    }
    if (state == -1) {
      f3d_lcd_drawString(30, 120, "   <easy>   ", BLACK, WHITE);
      delaytime = 100;
      showtime = 5000;
    }
    if (state == -2) {
      f3d_lcd_drawString(30, 120, " <veryeasy> ", BLACK, WHITE);
      delaytime = 200;
      showtime = 10000;
    }

    f3d_lcd_drawString(40, 140, "Score:", BLACK, WHITE);
    sprintf(s, "%d", score);
    f3d_lcd_drawString(90, 140, s, 133, WHITE);
    f3d_lcd_drawString(110, 140, "%", 133, WHITE);

    //reset score with "z"
    if (n.z == 1 && n.c == 0) {
      wins = 0;
      played = 0;
      state = 0;
    }

    //start play with "c", the game last for "time" long.
    if (n.c == 1) {
      play = 1;
      score = 0;
      time = 30000;
      delay(200);
      while (time >= 0) {
	f3d_lcd_fillScreen(WHITE);
	//randomly get a color.
	random = rand() % 4;
	if (random < 1) {
	  blue = blue + 1;
	  for (i = 35; i <= 95; i++) {
	    for (j = 30; j <= 50; j++) {
	      f3d_lcd_drawPixel(i, j, BLUE);
	    }
	  }
	}
	else if (random < 2) {
	  red = red + 1;
	  for (i = 15; i <= 35; i++) {
	    for (j = 50; j <= 110; j++) {
	      f3d_lcd_drawPixel(i, j, RED);
	    }
	  }
	}
	else if (random < 3) {
	  green = green + 1;
	  for (i = 35; i <= 95; i++) {
	    for (j = 110; j <= 130; j++) {
	      f3d_lcd_drawPixel(i, j, GREEN);
	    }
	  }
	}
	else {
	  yellow = yellow + 1;
	  for (i = 95; i <= 115; i++) {
	    for (j = 50; j <= 110; j++) {
	      f3d_lcd_drawPixel(i, j, YELLOW);
	    }
	  }
	}
	//time reduced
	time = time - showtime;
	delay(delaytime);
      }
      //calculate the largest one
      count[0] = blue;
      count[1] = red;
      count[2] = yellow;
      count[3] = green;
      value = largestoffour(count);
      delay(50);
      f3d_lcd_fillScreen(WHITE);
      //reset the buttonvalues
      n.jx = 128;
      n.jy = 128;
      n.c = 0;
      n.z = 0;
      while (play == 1) {
	//showing direction.
	f3d_lcd_drawString(10, 40, "which one appears", BLACK, WHITE);
	f3d_lcd_drawString(10, 50, "the most?", BLACK, WHITE);
	f3d_lcd_drawString(20, 60, "up for blue", BLUE, WHITE);
	f3d_lcd_drawString(20, 70, "left for red", RED, WHITE);
	f3d_lcd_drawString(20, 80, "right for yellow", YELLOW, WHITE);
	f3d_lcd_drawString(20, 90, "up for green", GREEN, WHITE);
	
	//choosing the color by using nunchuk, #'s need to be FIXED!!!
	f3d_nunchuk_read(&n);
	//up
	if ( n.jx < 150 && n.jx > 100 && n.jy > 150 )
	  buttonvalue = blue;
	//left
	if ( n.jx < 100 && n.jy < 150 && n.jy > 100 )
	  buttonvalue = red;
	//right
	if ( n.jx > 150 && n.jy < 150 && n.jy > 100 )
	  buttonvalue = yellow;
	//down
	if ( n.jx < 150 && n.jx > 100 && n.jy < 100 )
	  buttonvalue = green;
	if (buttonvalue != -1) {
	  if (buttonvalue == value) {
	    played++;
	    wins++;
	    //shows right or wrong.
	    f3d_lcd_fillScreen(WHITE);
	    f3d_lcd_drawString(50, 70, "RIGHT", RED, WHITE);
	    //insert sound of right
	    rc = f_open(&fid, "win.wav", FA_READ);//file need to change
  
	    if (!rc) {
	      struct ckhd hd;
	      uint32_t waveid;
	      struct fmtck fck;
    
	      readckhd(&fid, &hd, 'FFIR');
    
	      f_read(&fid, &waveid, sizeof(waveid), &ret);
	      if ((ret != sizeof(waveid)) || (waveid != 'EVAW'))
		return -1;
    
	      readckhd(&fid, &hd, ' tmf');
    
	      f_read(&fid, &fck, sizeof(fck), &ret);
    
	      // skip over extra info
    
	      if (hd.cksize != 16) {
		printf("extra header info %d\n", hd.cksize - 16);
		f_lseek(&fid, hd.cksize - 16);
	      }
    
	      printf("audio format 0x%x\n", fck.wFormatTag);
	      printf("channels %d\n", fck.nChannels);
	      printf("sample rate %d\n", fck.nSamplesPerSec);
	      printf("data rate %d\n", fck.nAvgBytesPerSec);
	      printf("block alignment %d\n", fck.nBlockAlign);
	      printf("bits per sample %d\n", fck.wBitsPerSample);
	    
	      // now skip all non-data chunks !
    
	      while(1) {
		readckhd(&fid, &hd, 0);
		if (hd.ckID == 'atad')
		  break;
		f_lseek(&fid, hd.cksize);
	      }
    
	      printf("Samples %d\n", hd.cksize);
    
	      // Play it !
    
	      // audioplayerInit(fck.nSamplesPerSec);
    
	      f_read(&fid, Audiobuf, AUDIOBUFSIZE, &ret);
	      hd.cksize -= ret;
	      audioplayerStart();
	      while (hd.cksize) {
		int next = hd.cksize > AUDIOBUFSIZE/2 ? AUDIOBUFSIZE/2 : hd.cksize;
		if (audioplayerHalf) {
		  if (next < AUDIOBUFSIZE/2)
		    bzero(Audiobuf, AUDIOBUFSIZE/2);
		  f_read(&fid, Audiobuf, next, &ret);
		  hd.cksize -= ret;
		  audioplayerHalf = 0;
		}
		if (audioplayerWhole) {
		  if (next < AUDIOBUFSIZE/2)
		    bzero(&Audiobuf[AUDIOBUFSIZE/2], AUDIOBUFSIZE/2);
		  f_read(&fid, &Audiobuf[AUDIOBUFSIZE/2], next, &ret);
		  hd.cksize -= ret;
		  audioplayerWhole = 0;
		}
	      }
	      audioplayerStop();
	    }
  
	    printf("\nClose the file.\n");
	    rc = f_close(&fid);
  
	    if (rc) die(rc);
	    
	  }
	    
	  else {
	    played++;
	    //shows right or wrong.
	    f3d_lcd_fillScreen(WHITE);
	    f3d_lcd_drawString(50, 70, "WRONG", RED, WHITE);
	    //insert sound of wrong
	    rc = f_open(&fid, "fail.wav", FA_READ);//file need to change
  
	    if (!rc) {
	      struct ckhd hd;
	      uint32_t waveid;
	      struct fmtck fck;
    
	      readckhd(&fid, &hd, 'FFIR');
    
	      f_read(&fid, &waveid, sizeof(waveid), &ret);
	      if ((ret != sizeof(waveid)) || (waveid != 'EVAW'))
		return -1;
    
	      readckhd(&fid, &hd, ' tmf');
    
	      f_read(&fid, &fck, sizeof(fck), &ret);
    
	      // skip over extra info
    
	      if (hd.cksize != 16) {
		printf("extra header info %d\n", hd.cksize - 16);
		f_lseek(&fid, hd.cksize - 16);
	      }
    
	      printf("audio format 0x%x\n", fck.wFormatTag);
	      printf("channels %d\n", fck.nChannels);
	      printf("sample rate %d\n", fck.nSamplesPerSec);
	      printf("data rate %d\n", fck.nAvgBytesPerSec);
	      printf("block alignment %d\n", fck.nBlockAlign);
	      printf("bits per sample %d\n", fck.wBitsPerSample);
    
	      // now skip all non-data chunks !
    
	      while(1) {
		readckhd(&fid, &hd, 0);
		if (hd.ckID == 'atad')
		  break;
		f_lseek(&fid, hd.cksize);
	      }
    
	      printf("Samples %d\n", hd.cksize);
    
	      // Play it !
    
	      // audioplayerInit(fck.nSamplesPerSec);
    
	      f_read(&fid, Audiobuf, AUDIOBUFSIZE, &ret);
	      hd.cksize -= ret;
	      audioplayerStart();
	      while (hd.cksize) {
		int next = hd.cksize > AUDIOBUFSIZE/2 ? AUDIOBUFSIZE/2 : hd.cksize;
		if (audioplayerHalf) {
		  if (next < AUDIOBUFSIZE/2)
		    bzero(Audiobuf, AUDIOBUFSIZE/2);
		  f_read(&fid, Audiobuf, next, &ret);
		  hd.cksize -= ret;
		  audioplayerHalf = 0;
		}
		if (audioplayerWhole) {
		  if (next < AUDIOBUFSIZE/2)
		    bzero(&Audiobuf[AUDIOBUFSIZE/2], AUDIOBUFSIZE/2);
		  f_read(&fid, &Audiobuf[AUDIOBUFSIZE/2], next, &ret);
		  hd.cksize -= ret;
		  audioplayerWhole = 0;
		}
	      }
	      audioplayerStop();
	    }
  
	    printf("\nClose the file.\n");
	    rc = f_close(&fid);
  
	    if (rc) die(rc);
	  }
	  
	  delay(700);
	  play = 0;
	  f3d_lcd_fillScreen(WHITE);
	}
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

/*
  f_mount(0, &Fatfs);

  rc = f_open(&fid, "thermo.wav", FA_READ);
  
  if (!rc) {
  struct ckhd hd;
  uint32_t waveid;
  struct fmtck fck;
    
  readckhd(&fid, &hd, 'FFIR');
    
  f_read(&fid, &waveid, sizeof(waveid), &ret);
  if ((ret != sizeof(waveid)) || (waveid != 'EVAW'))
  return -1;
    
  readckhd(&fid, &hd, ' tmf');
    
  f_read(&fid, &fck, sizeof(fck), &ret);
    
  // skip over extra info
    
  if (hd.cksize != 16) {
  printf("extra header info %d\n", hd.cksize - 16);
  f_lseek(&fid, hd.cksize - 16);
  }
    
  printf("audio format 0x%x\n", fck.wFormatTag);
  printf("channels %d\n", fck.nChannels);
  printf("sample rate %d\n", fck.nSamplesPerSec);
  printf("data rate %d\n", fck.nAvgBytesPerSec);
  printf("block alignment %d\n", fck.nBlockAlign);
  printf("bits per sample %d\n", fck.wBitsPerSample);
    
  // now skip all non-data chunks !
    
  while(1) {
  readckhd(&fid, &hd, 0);
  if (hd.ckID == 'atad')
  break;
  f_lseek(&fid, hd.cksize);
  }
    
  printf("Samples %d\n", hd.cksize);
    
  // Play it !
    
  // audioplayerInit(fck.nSamplesPerSec);
    
  f_read(&fid, Audiobuf, AUDIOBUFSIZE, &ret);
  hd.cksize -= ret;
  audioplayerStart();
  while (hd.cksize) {
  int next = hd.cksize > AUDIOBUFSIZE/2 ? AUDIOBUFSIZE/2 : hd.cksize;
  if (audioplayerHalf) {
  if (next < AUDIOBUFSIZE/2)
  bzero(Audiobuf, AUDIOBUFSIZE/2);
  f_read(&fid, Audiobuf, next, &ret);
  hd.cksize -= ret;
  audioplayerHalf = 0;
  }
  if (audioplayerWhole) {
  if (next < AUDIOBUFSIZE/2)
  bzero(&Audiobuf[AUDIOBUFSIZE/2], AUDIOBUFSIZE/2);
  f_read(&fid, &Audiobuf[AUDIOBUFSIZE/2], next, &ret);
  hd.cksize -= ret;
  audioplayerWhole = 0;
  }
  }
  audioplayerStop();
  }
  
  printf("\nClose the file.\n");
  rc = f_close(&fid);
  
  if (rc) die(rc);
**/
