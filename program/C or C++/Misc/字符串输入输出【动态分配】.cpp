#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5

char *save_tin() { // ��ֵ�ַ���
  int i = 0;
  char *str = (char *)malloc(1);
  while ((str[i++] = getchar()) != '\n')
    realloc(str, i + 1);
  str[i - 1] = 0; // ��β'\0'
  return str;
}

int save(char ***str) { // ��ָ�����鸳ֵ�ַ���
  int i = 0, siz = sizeof(char *);
  *str = (char **)malloc(siz); // �����ʼ��ָ�������ڴ�
  do {
    printf("�ַ���%d ", i);
    (*str)[i] = save_tin();                       // ��ֵ�ַ���
    *str = (char **)realloc(*str, siz * (i + 2)); // �����ַ���
  } while (*(*str)[i++]); // ���ַ�������
  realloc(*str, siz * --i); // ɾ�����������ַ�
  return i;
}

void sort(char **str, int n) { // ��������
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
  puts("�����ַ�����");
  n = save(&str);
  printf("n=%d\n", n);
  while (n--)
    puts(*str++);
}
