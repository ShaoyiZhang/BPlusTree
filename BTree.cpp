#include "BTree.h"

TreeNode::TreeNode(){
  isLeaf = false;
  isRoot = false;
  name = "";
  index = -1;

  leaves = new TreeNode* [L];
  for(int i = 0; i < L; i++)
    leaves[i] = NULL;
}
