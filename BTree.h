#include <iostream>


using namespace std;


class TreeNode{
 private:
  static const int M = 5;
  static const int L = 3;
  TreeNode** names;
  TreeNode** indexArray;
  TreeNode** leaves;
  bool isLeaf;
  bool isRoot;
  string name;
  int index;
 public:
  TreeNode();

}
