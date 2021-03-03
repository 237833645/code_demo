#include "stdio.h"
#include "sum.h"

int main(void)
{
  int a = 10;
  int b = 20;
  int c;

  c = sum(a, b);
  printf("c = %d\n", c);

  return 0;
}