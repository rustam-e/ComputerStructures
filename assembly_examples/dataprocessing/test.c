#include <stdio.h>

extern int plus3(int);
extern int add3op(int,int,int);
extern int add3opnoflag(int,int,int);
extern int add2op(int,int);
extern int sub3op(int,int,int);

main(){
  int i,j,k;
  for (i = 0; i < 5; i++) {
    switch (i){
    case 0:
      printf("plus3 test\n"); break;
    case 1:
      printf("\nadd3op test\n"); break;
    case 2:
      printf("\nadd3onoflag test\n"); break;
    case 3:
      printf("\nadd2op test\n"); break;
    case 4:
      printf("\nsub3op test\n"); break;
    }

    for (j = 1; j < 5; j++)
      for (k = -3; k < 3; k++)	{
	switch (i){
	case 0:
	  printf("%d + 3 = %d\n", j, plus3(j)); break;
	case 1:
	  printf("%d + %d = %d\n", j, k,  add3op(0,j,k)); break;
	case 2:
	  printf("%d + %d = %d\n", j, k, add3opnoflag(0,j,k)); break;
	case 3:
	  printf("%d + %d = %d\n", j, k, add2op(j,k)); break;
	case 4:
	  printf("%d - %d = %d\n", j, k, sub3op(0,j,k));
	}
	if (!i) break;
      }
  }
}
