#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum {
  False, True  
} bool;

/* 双向链表节点 */
typedef struct DoublyListNode {
  int val;                      // 节点值
  struct DoublyListNode *next;  // 后继节点
  struct DoublyListNode *prev;  // 前驱节点
} DoublyListNode;

/* 构造函数 */
DoublyListNode *newDoublyListNode(int num)
{
  DoublyListNode *new = (DoublyListNode *)malloc(sizeof(DoublyListNode)); 
  new->val = num;
  new->next = NULL;
  new->prev = NULL;
  return new;
}

/* 析构函数 */
void dedoublyListNode(DoublyListNode *node)
{
  free(node); 
}

/* 基于双向链表实现的双向队列 */
typedef struct {
  DoublyListNode *front, *rear; // 头节点 front , 尾节点 rear
  int queSize;                  // 双向队列的长度
} LinkedListDeque;

/* 构造函数 */
LinkedListDeque *newLinkedListDeque()
{
  LinkedListDeque *deque = (LinkedListDeque *)malloc(sizeof(LinkedListDeque));
  deque->front = NULL;
  deque->rear = NULL;
  deque->queSize = 0;
  return deque;
}

/* 析构函数 */
void delinkedListDeque(LinkedListDeque *deque)
{
  // 释放所有节点
  for(int i=0; i<deque->queSize && deque->front != NULL; i++) {
    DoublyListNode *tmp = deque->front;
    deque->front = deque->front->next;
    free(tmp);
  }
  // 释放 deque 结构体
  free(deque);
}

/* 获取队列的长度 */
int size(LinkedListDeque *deque)
{
  return deque->queSize;  
}

/* 判断队列是否为空 */
bool empty(LinkedListDeque *deque)
{
  return size(deque) == 0;
}

/* 入队 */
void push(LinkedListDeque *deque, int num, bool isFront)
{
  DoublyListNode *node = newDoublyListNode(num);
  // 若队列为空，则令 front 和 rear 都指向 node
  if(empty(deque)) {
    deque->front = node;
    deque->rear = node;
  } else {
    // 队首入队操作
    if(isFront) {
      deque->front->prev = node;
      node->next = deque->front;
      deque->front = node; // 更新头节点
    } else {
      deque->rear->next = node;
      node->prev = deque->rear;
      deque->rear = node;  // 更新尾节点
    }
  }
  deque->queSize++; // 更新队列长度
}

/* 队首入队 */
void pushFirst(LinkedListDeque *deque, int num)
{
  push(deque, num, True);  
}
  
/* 队尾入队 */
void pushLast(LinkedListDeque *deque, int num)
{
  push(deque, num, False);  
}   

/* 访问队首元素 */
int peekFirst(LinkedListDeque *deque)
{
  assert(size(deque) && deque->front);
  return deque->front->val;
}

/* 访问队尾元素 */
int peekLast(LinkedListDeque *deque)
{
  assert(size(deque) && deque->rear);
  return deque->rear->val;
}

/* 出队 */
int pop(LinkedListDeque *deque, bool isFront)
{
  if(empty(deque)) {
    return -1;
  }
  int val;
  // 队首出队操作
  if(isFront) {
    val = peekFirst(deque);
    DoublyListNode *fNext = deque->front->next;
    if(fNext) {
      fNext->prev = NULL;
      // deque->front->next = NULL; 多余的，本来就要删掉
    }
    dedoublyListNode(deque->front);
    deque->front = fNext; // 更新头节点
  }
  // 队尾出队操作
  else {
    val = peekLast(deque);
    DoublyListNode *rPrev = deque->rear->prev;
    if(rPrev) {
      rPrev->next = NULL;
      // deque->rear->prev = NULL;  多余的，本来就要删掉
    }
    dedoublyListNode(deque->rear);
    deque->rear = rPrev;
  }
  deque->queSize--; // 更新队列长度
  return val;
}

/* 队首出队 */
int popFirst(LinkedListDeque *deque)
{
  return pop(deque, True);  
}

/* 队尾出队 */
int popLast(LinkedListDeque *deque)
{
  return pop(deque, False);  
}

/* 打印队列 */
void printLinkedListDeque(LinkedListDeque *deque)
{
  DoublyListNode *node = deque->front;
  for(int i=0; i<deque->queSize; i++) {
    printf("%d ", node->val);
    node = node->next;
  }
}

int main(int argc, char *argv[])
{
  LinkedListDeque *deque = newLinkedListDeque();
  pushFirst(deque, 3);
  pushFirst(deque, 5);
  pushLast(deque, 2);
  pushLast(deque, 6);
  printLinkedListDeque(deque);
  popFirst(deque);
  popLast(deque);
  printLinkedListDeque(deque);
}






















