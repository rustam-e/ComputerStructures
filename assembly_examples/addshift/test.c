#include <stdio.h>

extern int addsift(int,int);

main(){
  int i,j;
  for (i = 1; i < 5; i++)
    for (j = 0; j < 5; j++)
      printf("%d + (%d << 2) = %d\n", i, j, addshift(i,j));
}
