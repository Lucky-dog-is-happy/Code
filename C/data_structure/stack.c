#include <stdio.h>
#include <stdlib.h>
#include "link.h"

/* 基于链表实现的栈 */
typedef struct {
  ListNode *top; // 头节点作为栈顶
  int size;      // 栈顶长度 
} LinkedListStack;

/* 构造函数 */
LinkedListStack *newLinkedListStack()
{
  LinkedListStack *s = malloc(sizeof(LinkedListStack));
  s->top = NULL;
  s->size = 0;
  return s;
}

/* 析构函数 */
void delinkedListStack(LinkedListStack *s) 
{
  while (s->top) {
    ListNode *n = s->top->next;
    free(s->top);
    s->top = n;
  }
  free(s);
}

/* 获取栈的长度 */
int size(LinkedListStack *s)
{
  return s->size;  
}

/* 判断栈是否为空 */
bool isEmpty(LinkedListStack *s)
{
  return size(s) == 0;
}

void push(LinkedListStack *s, int num)
{
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->next = s->top;  // 更新新加节点指针域
  node->val = num;      // 更新新加节点数据域
  s->top = node;        // 更新栈顶
  s->size++;
}

/* 访问栈顶元素 */
int peek(LinkedListStack *s)
{
  if(s->size == 0) {
    printf("栈为空\n");
    return INT_MAX;
  }
  return s->top->val;
}

/* 出栈 */
int pop(LinkedListStack *s)
{
  int val = peek(s);
  ListNode *tmp = s->top;
  s->top = s->top->next;
  // 释放内存
  free(tmp);
  s->size--;
  return val;
}

int main(int argc, char *argv[])
{
  LinkedListStack *stack = newLinkedListStack();
  push(stack, 2);
  push(stack, 3);
  push(stack, 5);
  push(stack, 1);
  printf("%d ", pop(stack));
  printf("%d ", peek(stack));

  delinkedListStack(stack);
  return 0;
}




