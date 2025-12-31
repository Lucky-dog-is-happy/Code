
/* 查找节点 */
TreeNode *search(BinarySearchTree *bst, int num)
{
  TreeNode *cur = bst->root;
  // 循环查找，越过叶节点后退出
  while(cur != NULL) {
    if(cur->val < num)
      // 目标节点在cur的右子树中
      cur = cur->right;
    else if(cur->val > num)
      // 目标节点在cur的左子树中
      cur = cur->left;
    else
      // 找到目标节点，跳出循环
      break;
  }
  // 返回目标节点
  return cur;
}

/* 插入节点 */
void insert(BinarySearchTree *bst, int num)
{
  // 若树为空，则初始化根节点
  if(bst->root == NULL) {
    bst->root = newTreeNode(num);
    return;
  }
  TreeNode *cur = bst->root, *pre = NULL;
  // 循环查找，越过叶节点后跳出
  while(cur != NULL) {
    // 找到重复节点，直接返回
    if(cur->val == num)
      return;
    pre = cur;
    if(cur->val < num)
      // 插入位置在cur的右子树中
      cur = cur->right;
    else
      // 插入位置在cur的左子树中
      cur = cur->left;
  }

  // 插入节点
  TreeNode *node = newTreeNode(num);
  if(pre->val < num)
    pre->right = node;
  else
    pre->left = node;
}

/* 删除节点 */
void removeItem(BinarySearchTree *bst, int num)
{
  if(bst->root == NULL)
    return;
  TreeNode *cur = bst->root, *pre = NULL;
  // 循环查找，越过叶节点后跳出
  while(cur != NULL) {
    // 找到待删除节点，跳出循环
    if(cur->val == num)
      break;
    pre = cur;
    if(cur->val < num)
      // 待删除节点在root的右子树中
      cur = cur->right;
    else
      // 待删除节点在root的左子树中
      cur = cur->left;
  }

  // 若无待删除节点，则直接返回
  if(cur == NULL)
    return;
  // 判断待删除节点是否存在子节点
  if(cur->left == NULL || cur->right == NULL) {
    /* 子节点数量为 0 or 1
     * 该节点替换为NULL or 子节点
     */
    TreeNode *child = cur->left != NULL ? cur->left : cur->right;
    // 删除节点cur
    if(pre->left == cur)
      pre->left = child;
    else
      pre->right = child;
    // 释放内存
    free(cur);
  } else {
    /* 子节点数量为2
     * 将该节点替换为中序遍历的下一个节点
     */
    TreeNode *tmp = cur->right;
    while(tmp->left != NULL)
      tmp = tmp->left;
    int tmpVal = tmp->val;
    // 递归删除节点tmp
    // tmp本身可能也有子节点
    removeItem(bst, tmp->val);
    // 用tmp覆盖cur
    cur->val = tmpVal;
  }
}
