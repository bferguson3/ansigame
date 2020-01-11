#include <stdio.h>

int main()
{
  int i, j, n;
  
  for (i = 0; i < 11; i++) {
    for (j = 1; j < 11; j++) {
      n = 10*i + j - 1;
      if (n > 108) break;
      printf("\033[%dm %3d\033[m", n, n);
    }
    printf("\n");
  }
}
