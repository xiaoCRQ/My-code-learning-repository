#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5

char *save_tin() { // 赋值字符串
  int i = 0;
  char *str = (char *)malloc(1);
  while ((str[i++] = getchar()) != '\n')
    realloc(str, i + 1);
  str[i - 1] = 0; // 结尾'\0'
  return str;
}

int save(char ***str) { // 给指针数组赋值字符串
  int i = 0, siz = sizeof(char *);
  *str = (char **)malloc(siz); // 分配初始的指针数组内存
  do {
    printf("字符串%d ", i);
    (*str)[i] = save_tin();                       // 赋值字符串
    *str = (char **)realloc(*str, siz * (i + 2)); // 增加字符串
  } while (*(*str)[i++]); // 无字符则跳出
  realloc(*str, siz * --i); // 删除最后的无用字符
  return i;
}

void sort(char **str, int n) { // 升序排序
  int i, j, k;
  char *t;
  for (i = 0; i < n - 1; i++) {
    k = i;
    for (j = i + 1; j < n; j++)
      if (strcmp(str[k], str[j]) > 0)
        k = j;
    if (k != i)
      t = str[i], str[i] = str[k], str[k] = t;
  }
}

int main() {
  char **str = NULL;
  int n;
  puts("输入字符串：");
  n = save(&str);
  printf("n=%d\n", n);
  while (n--)
    puts(*str++);
}
