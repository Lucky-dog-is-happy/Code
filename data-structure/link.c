#include <stdio.h>
#include <stdlib.h>
#include "link.h"

/* 构造函数 */
ListNode *newListNode(int val)
{
  ListNode *node;
  node = (ListNode *)malloc(sizeof(ListNode));
  node->val = val;
  node->next = NULL;
  return node;
}

/* 在链表的节点n0之后插入节点p */
void insert(ListNode *n0, ListNode *p)
{
  ListNode *n1 = n0->next;
  p->next = n1;
  n0->next = p;
}

/* 删除链表节点n0之后的首个节点 */
// stdio.h占用了remove关键字
void removeItem(ListNode *n0)
{
  if(!n0->next) 
    return;
  // n0->p->n1
  ListNode *p = n0->next;
  ListNode *n1 = p->next;
  n0->next = n1;
  // 释放内存
  free(p);
}

/* 访问链表中索引为index的节点 */
ListNode *access(ListNode *head, int index)
{
  for(int i=0; i<index; i++) {
    if(head == NULL) 
      return NULL;
    head = head->next;
  }
  return head;
}

/* 在链表中查找值为target的首个节点 */
int find(ListNode *head, ElemType target)
{
  int index = 0;
  while(head)
  {
    if(head->val == target)
      return index;
    head = head->next;
    index++;
  }
  return -1;
}

/* 遍历打印链表 */
void PrintLinkedList(ListNode *head)
{
  while(head != NULL) 
  {
    printf("%d ", head->val);
    head = head->next;
  }
  if(head == NULL)
    printf("\n");
}

int main(int argc, char *argv[])
{
  /* 初始化链表 1 -> 3 -> 2 -> 5 -> 4 */
  // 初始化各个节点
  ListNode* n0 = newListNode(1);
  ListNode* n1 = newListNode(3);
  ListNode* n2 = newListNode(2);
  ListNode* n3 = newListNode(5);
  ListNode* n4 = newListNode(4);
  // 构建节点之间的引用
  n0->next = n1;
  n1->next = n2;
  n2->next = n3;
  n3->next = n4;

  printf("%d\n", find(n0, 5));
  PrintLinkedList(n0);
  removeItem(access(n0, 2));  // 删除index为2后的首个节点
  PrintLinkedList(n0);
  
  return 0;
}
