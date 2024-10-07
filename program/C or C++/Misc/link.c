#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <string.h>

#define SIZE(temp) (temp *)error(malloc(sizeof(temp)))

// 随机赋值的范围
#define MAX 1000
#define MIN 100
#define RAND rand() % (MAX - MIN + 1) + MIN
#define RAND_ABC 'A' + rand() % 26
#define RAND_abc 'a' + rand() % 26
#define LINK_PUT "%d %c"

typedef struct link {
  int data;
  char ch;
  char name[10];
  char number[18];
  struct link *next;
} LINK;

void *error(void *temp) { // 检查是否正确分配内存
  if (temp)
    return temp;
  puts("分配内存错误");
  exit(1);
}

LINK *link_creat(int lang) {
  if (lang < 1)
    return NULL;
  LINK *temp = SIZE(LINK);
  temp->next = link_creat(lang - 1);
  return temp;
}

void link_input_law(LINK *temp) {
  int count = 1;
  while (temp) {
    temp->data = count++;
    temp = temp->next;
  }
}

void link_input_rand_name(LINK *temp, int lang) {
  if (temp->next)
    link_input_rand_name(temp->next, lang);
  int count = 0;
  while (count < lang) {
    temp->name[count++] = RAND_ABC;
  }
  temp->name[lang] = '\0';
}

void link_input_rand_number(LINK *temp, int lang) {
  if (temp->next)
    link_input_rand_number(temp->next, lang);
  int count = 0;
  while (count < lang) {
    temp->number[count++] = '0' + rand() % 10;
  }
  temp->number[lang] = '\0';
}

LINK *link_creat_str(const char *str) {
  if (*str) {
    LINK *temp = SIZE(LINK);
    temp->next = link_creat_str(str + 1);
    temp->ch = *str;
    return temp;
  } else
    return NULL;
}

LINK *link_find(LINK *head, int count) { // 查询节点 非正整数 - 为结尾
  if (head && head->next && count)
    return count > 0 ? count-- : 0, link_find(head->next, count);
  return head;
}

LINK *link_free(LINK *head, int lang) { // 释放节点 返回第[lang]的节点
  LINK *temp = head;
  if (head && lang > 0)
    temp = link_free(head->next, lang - 1), free(head);
  return temp;
}

LINK *link_del(LINK *head, int start, int end) { // 删除start-end的节点
  if (start < 0 || start > end || !head)
    return head; // 无删除区间
  LINK *link_start;
  if (start)
    link_start = link_find(head, start - 1),
    link_start->next = link_free(link_start->next, end - start + 1);
  else
    return link_free(head, end - start + 1);
  return head;
}

LINK *link_insert(LINK *head, LINK *insert, int insert_number) {
  if (insert) {
    if (insert_number == 0) // 当插入点在头部时
      return link_find(insert, -1)->next = head, insert;
    LINK *temp = link_find(head, insert_number - 1);
    if (temp->next == NULL) // 当插入点在尾部时
      return temp->next = insert, head;
    link_find(insert, -1)->next = temp->next;
    temp->next = insert;
  }
  return head;
}

void link_put(const char *_cmd, LINK *head) {
  char cmd[256] = "link #%-3d ";
  int count = 0;
  while (head) {
    printf(cmd, count);
    printf("%s\t%s\n", head->name, head->number);
    printf(_cmd, head->data, head->ch);
    puts("");
    count++;
    head = head->next;
  }
}

void link_puts(LINK *head) {
  putchar(head->ch);
  if (head->next)
    link_puts(head->next);
  else
    putchar('\n');
}

int main() {
  LINK *head, *temp;
  srand(time(0));
  head = link_creat_str("123456789");
  link_find(head, 2)->next = link_free(link_find(head, 3), 2);
  link_puts(head);
  getchar();
  return 0;
}
