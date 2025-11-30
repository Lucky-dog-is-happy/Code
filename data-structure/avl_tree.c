#include <stdlib.h>

/* AVL树节点结构体 */
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

/* 获取节点高度 */
int height(TreeNode *node)
{
  // 空节点高度为-1，叶节点高度为0
  if(node != NULL)
    return node->height;
  return -1;
}

/* 更新节点高度 */
void updataHeight(TreeNode *node)
{
  int lh = height(node->left);
  int rh = height(node->right);
  // 节点高度等于最高子树高度 + 1
  if(lh > rh)
    node->height = lh + 1;
  else
    node->height = rh + 1;
}

/* 获取平衡因子 */
int balanceFactor(TreeNode *node)
{
  // 空节点平衡因子为0
  if(node == NULL)
    return 0;
  // 节点平衡因子 = 左子树高度 - 右子树高度
  return height(node->left) - height(node->right);
}

/* 右旋操作 */
TreeNode *rightRotate(TreeNode *node)
{
  TreeNode *child, *grandChild;
  child = node->left;
  grandChild = child->right;
  // 以child为原点，将node向右旋转
  child->right = node;
  node->left = grandChild;
  // 更新节点高度
  updateHeight(node);
  updateHeight(child);
  // 返回旋转后子树的根节点
  return child;
}

/* 左旋操作 */
TreeNode *leftRotate(TreeNode *node)
{
  TreeNode *child, *grandChild;
  child = node->right;
  grandChild = child->left;
  // 以child为原点，将node向左旋转
  child->left = node;
  node->right = grandChild;
  // 更新节点高度
  updateHeight(node);
  updateHeight(child);
  // 返回旋转后子树的根节点
  return child;
}

/* 执行旋转操作，使该子树重新恢复平衡 */
TreeNode *rotate(TreeNode *node) {
  // 获取节点node的平衡因子
  int bf = balanceFactor(node);
  // 左偏树
  if(bf > 1) {
    if(balanceFactor(node->left) >= 0)
      // 右旋
      return rightRotate(node);
    else {
      // 先左旋后右旋
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  // 右偏树
  if(bf < -1) {
    if(balanceFactor(node->right) <=0)
      // 左旋
      return leftRotate(node);
    else {
      // 先右旋后左旋
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  // 平衡树，无需旋转
  return node;
}

/* 插入节点 */
void insert(AVLTree *tree, int val)
{
  tree->root = insertHelper(tree->root, val);
}

/* 递归插入节点 */
TreeNode *insertHelper(TreeNode *node, int val)
{
  if(node == NULL)
    return newTreeNode(val);
  /* 1.查找插入位置并插入节点 */
  if(val < node->val)
    node->left = insertHelper(node->left, val);
  else if(val > node->val)
    node->right = insertHelper(node->right, val);
  else
    // 重复节点
    return node;
  // 更新节点长度
  updateHeight(node)
  /* 2.执行旋转操作，使该子树重新恢复平衡 */
  node = rotate(node);
  return node;
}

/* 删除节点 */
void removeItem(AVLTree *tree, int val)
{
  TreeNode *root = removeHelper(tree->root, val);
}

/* 递归删除节点 */
TreeNode *child, *grandchild;
if(node == NULL)
  return NULL;
/* 1.查找节点并删除 */
if(val < node->val)
  node->left = removeHelper(node->left, val);
else if(val > node->val)
  node->right = removeHelper(node->right, val);
else {
  if(node->left == NULL || node->right == NULL) {
    child = node->left;
    if(node->right != NULL)
      child = node->right;
    // 节点数量为0， 直接删除node并返回
    if(child == NULL)
      return NULL;
    else
      // 子节点数量为1，直接删除node
      node = child;
  } else {
    // 子节点数量为2，则将中序遍历的下一个节点删除，并用该节点替换当前节点
    TreeNode *temp = node->right;
    while(temp->left != NULL)
      temp = temp->left;
  }
}



