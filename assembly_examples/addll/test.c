#include <stdio.h>

extern long long addll(long long, long long);

test(long long i, long long j)
{
 printf("%lld + %lld = %lld\n", i, j, addll(i,j));
}

main(){
  long long i,j;
  for (i = 1; i < 5; i++)
    for (j = 1; j < 5; j++)
      test(i,j);
  test(-1,2);
 printf("0x%llx + 0x%llx = 0x%llx\n", 0xffffffffll, 0x02ll, addll(0xffffffffll,2));
}
