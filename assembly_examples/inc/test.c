#include <stdio.h>

extern int inc(int);

main(){
  int i;
  for (i = 1; i < 10; i++)
    printf("%d + 1 = %d\n", i, inc(i));
}
