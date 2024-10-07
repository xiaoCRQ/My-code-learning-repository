#include "stdio.h"
#include "stdlib.h"
#include <Windows.h>

void love() {
  int i, j, k, n = 0, x = 0, y = 50;
  printf("\n\n\n\n\n");
  printf("         lovelove                   lovelove\n");
  printf("       lovelovelove               lovelovelove\n");
  printf("     lovelovelovelove           lovelovelovelove\n");
  printf("   lovelovelovelovelove       lovelovelovelovelove\n");
  printf("  lovelovelovelovelovelo     lovelovelovelovelovelo\n");
  printf(" lovelovelovelovelovelove   lovelovelovelovelovelov\n");
  for (i = 0; i < 2; i++) {
    printf("lovelovelovelovelovelovelovelovelovelovelovelovelove\n");
  }
  for (i = 0; i < 5; i++) {
    y = 50;
    y = y - i * 2;
    n++;
    for (k = 0; k < n; k++) {
      printf(" ");
    }
    while (1) {
      if (x < y) {
        printf("l");
        y--;
      } else
        break;
      if (x < y) {
        printf("o");
        y--;
      } else
        break;
      if (x < y) {
        printf("v");
        y--;
      } else
        break;
      if (x < y) {
        printf("e");
        y--;
      } else
        break;
    }
    printf("\n");
  }
  for (i = 0, n = 3; i < 10; i++) {
    y = 37;
    y = y - i * 4;
    n++;
    for (k = 0; k < n; k++) {
      printf("  ");
    }
    while (1) {
      if (x < y) {
        printf("l");
        y--;
      } else
        break;
      if (x < y) {
        printf("o");
        y--;
      } else
        break;
      if (x < y) {
        printf("v");
        y--;
      } else
        break;
      if (x < y) {
        printf("e");
        y--;
      } else
        break;
    }
    printf("\n");
  }
  Sleep(100);
}

int main() {
  char cmd[] = "color 01";
  char FF[] = "0123456789ABCDEF";
  // char FF[] = "FFFFFFFFFFFFFFFFFFFF";
  int i = 0;
  while (1) {
    system("cls");
    system(cmd);
    cmd[7] = FF[i++];
    if (i > 16)
      i = 0;
    love();
  }
  return 0;
}
