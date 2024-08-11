#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  srand(time(NULL));

  int max = 0, a, b,c, i, aux;
  FILE *txt = fopen("bigint.dat", "w");

  max = 200000; //+ rand() % 10000;
  
  for (i = 0; i < max; i++) {
    a = -500 + rand() % 1000;
    b = 1 + rand() % 32000;
    c = 1 + rand() % 9000;
    fprintf(txt, "%d %d%d\n", a, b, c);

  }

  return 0;
}
