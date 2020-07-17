#include <stdio.h>

int main() {
  int x = 30;
  printf("Valor de x: %i\n", x);
  int* y = &x;
  *y = 25;
  printf("Valor de x: %i\n", x);
  return 0;
}