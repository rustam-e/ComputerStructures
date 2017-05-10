
#include <stdio.h>

int main()
{
  static int lines = 0;
  static int words = 0;
  static int characters = 0;
  int c;
  while((c = getchar()) != 0x1b)
  {
    ++ characters;
    if (c == ' ' || c == '\n')
      ++words;
    if (c == '\n')
      ++lines;
  }
  printf("The file has %d lines, %d words, and %d characters.\n", lines, words, characters);
  return 0;
}
