
//group 10 



#include <stdio.h>


//int mywc(void);

//when we worked on this part, my partner didn't notice we already have mywc.c. 
//It should be the same. 

int mywc()
{
  int lines = 0;
  int words = 0;
  int characters = 0;
  int c;
  int cpre = NULL;
  while((c = getchar()) != 0x1b)
  { 
    ++ characters;
    if (cpre != ' ' && cpre != '\n') {
      if (c == ' ' || c == '\n')
	++words;
    }
    if (c == '\n')
      ++lines;
    cpre = c;
  }

  printf("The file has %d lines, %d words, and %d characters.\n", lines, words, characters);
  return 0;
}
