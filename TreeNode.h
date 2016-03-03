#ifndef TREE_NODE_H_
#define TREE_NODE_H_

#include <iostream>

using namespace std;

const int M = 5;
const int L = 3;

class TreeNode{
 private:
  string* nameIndex;
  TreeNode** nextNodes;
  pair<string, int>** leaves;
  bool isLeaf;
  int index;
 public:
  TreeNode();

  //constructor for a leaf
  TreeNode(string name, int index);

  //constructor for an internal node
  TreeNode(TreeNode** arrayOfNodes, int size);

  bool checkLeaf(){return isLeaf;}
  void setLeaf(bool value){isLeaf = value;}
  void insertLeaf(string name, int index, int endPos);
  string* getNameIndex(){return nameIndex;}
  TreeNode** getNextNodes(){return nextNodes;}
  pair<string, int>** getLeaves(){return leaves;}
};

#endif
