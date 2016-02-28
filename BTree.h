#include <iostream>


using namespace std;


class TreeNode{
 private:
  const int M = 5;
  const int L = 3;
  string* nameIndex;
  TreeNode** nextNodes;
  pair<string, int>** leaves;
  bool isLeaf;
  int index;
 public:
  TreeNode();

  //constructor for a leaf
  TreeNode(string name, int index);

  bool checkLeaf(){return isLeaf;}
  void setLeaf(bool value){isLeaf = value;}

  string* getNameIndex(){return nameIndex;}
  TreeNode** getNextNodes(){return nextNodes;}
  pair<string, int>** getLeaves(){return leaves;}
};

class BTree{
 private:
  TreeNode* root;
 public:
  BTree();
  void insert(string name, int index);
  pair<pair<string, int>*, bool>* find(string name);
};
