#ifndef LINK_H
#define LINK_H

#define ElemType int

/* 布尔类型 */
typedef enum {
  False, True  
} bool;

/* 链表节点结构体 */
typedef struct ListNode {
  ElemType val;              // 节点值
  struct ListNode *next;     // 指向下一节点的指针
} ListNode;

ListNode *newListNode(int val);
void insert(ListNode *n0, ListNode *p);
void removeItem(ListNode *n0);
ListNode *access(ListNode *head, int index);
int find(ListNode *head, ElemType target);
void PrintLinkedList(ListNode *head);

#endif
