#ifndef BTREE_H_
#define BTREE_H_

#include <iostream>
#include "TreeNode.h"

using namespace std;

class BTree{
 private:
  TreeNode* root;
  pair<TreeNode*, TreeNode*>* splitLeaves(TreeNode* root, string name, int index);
 public:
  BTree();
  void insert(string name, int index);
  pair<string, int>* find(string name);
};

#endif
