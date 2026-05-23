#include <stdlib.h>

#define MAX_SIZE 10000

/* 二叉树节点结构体 */
typedef struct TreeNode {
  int val;
  int height;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

/* 构造函数 */
TreeNode *newTreeNode(int val)
{
  TreeNode *node;

  node = (TreeNode *)malloc(sizeof(TreeNode));
  node->val = val;
  node->height = 0;
  node->left = NULL;
  node->right = NULL;
  return node;
}

/* 测序遍历 */
int *levelOrder(TreeNode *root, int *size)
{
  /* 辅助队列 */
  int front, rear;
  int index, *arr;
  TreeNode *node;
  TreeNode **queue;
  queue = (TreeNode **)malloc(sizeof(TreeNode *) * MAX_SIZE);
  // 队列指针
  front = 0, rear = 0;
  // 加入根节点
  queue[rear++] = root;
  // 初始化一个列表，用于保存遍历序列
  arr = (int *)malloc(sizeof(int) * MAX_SIZE);
  index = 0;
  while(front < rear) {
    // 队列出队
    node = queue[front++];
    // 保存节点值
    arr[index++] = node->val;
    if(node->left != NULL)
      queue[rear++] = node->left;
    if(node->right != NULL)
      queue[rear++] = node->right;
  }
  *size = index;
  arr = realloc(arr, sizeof(int) * (*size));

  // 释放辅助空间
  free(queue);
  return arr;
}

/* 前序遍历 */
void preOrder(TreeNode *root, int *size, int *arr)
{
  if(root == NULL)
    return;
  // 访问优先级：根节点->左子树->右子树
  arr[(*size)++] = root->val;
  preOrder(root->left, size, arr);
  preOrder(root->right, size, arr);
}

/* 中序遍历 */
void inOrder(TreeNode *root, int *size, int *arr)
{
  if(root == NULL)
    return;
  // 访问优先级：左子树->根节点->右子树
  inOrder(root->left, size, arr);
  arr[(*size)++] = root->val;
  inOrder(root->right, size, arr);
}

/* 后序遍历 */
void postOrder(TreeNode *root, int *size, int *arr)
{
  if(root == NULL)
    return;
  // 访问优先级：左子树->右子树->根节点
  postOrder(root->left, size, arr);
  postOrder(root->right, size, arr);
  arr[(*size)++] = root->val;
}

int main(int agrc, char *argv[])
{
  /* 初始化二叉树 */
  TreeNode *n1 = newTreeNode(1);
  TreeNode *n2 = newTreeNode(2);
  TreeNode *n3 = newTreeNode(3);
  TreeNode *n4 = newTreeNode(4);
  TreeNode *n5 = newTreeNode(5);
  TreeNode *n6 = newTreeNode(6);

  // 构建节点之间的引用
  n1->left = n2;
  n1->right = n3;
  n2->left = n4;
  n2->right = n5;
  n4->left = n6;

  /* 插入与删除节点 */
  TreeNode *P = newTreeNode(0);
  // 在n1->n2之间插入P
  P->left = n2;
  n1->left = P;
  // 删除节点P
  n1->left = n2;
  free(P);
}


