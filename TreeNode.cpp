#include "TreeNode.h"

TreeNode::TreeNode(){
  isLeaf = false;

  index = -1;
  nameIndex = new string[M-1];
  for(int i = 0; i < M-1; i++){
    nameIndex[i] = "";
  }

  //give one more space to the leaves to make splitting more convient
  leaves = new pair<string, int>* [L+1];
  for(int i = 0; i < L+1; i++)
    leaves[i] = NULL;

  nextNodes = new TreeNode* [M];
  for(int i = 0; i < M; i++)
    nextNodes[i] = NULL;

}

//constructor for a leaf
TreeNode::TreeNode(string name, int index){
  isLeaf = true;

  nameIndex = new string[M-1];
  nextNodes = new TreeNode* [M];
  for(int i = 0; i < M-1; i++){
    nameIndex[i] = "";
    nextNodes[i] = NULL;
  }
  nextNodes[M-1] = NULL;

  leaves = new pair<string, int>* [L];
  for(int i = 0; i < L; i++)
    leaves[i] = NULL;

  pair<string, int>* temp = new pair<string, int>(name, index);
  leaves[0] = temp;
}

TreeNode::TreeNode(TreeNode** arrayOfNodes, int size){
  isLeaf = false;
  leaves = new pair<string, int>* [L];
  for(int i = 0; i < L; i++)
    leaves[i] = NULL;

  nameIndex = new string[M-1];
  nextNodes = new TreeNode* [M];
  for(int i = 0; i < M-1; i++){
    nameIndex[i] = "";
    nextNodes[i] = NULL;
  }
  nextNodes[M-1] = NULL;

  for(int i = 0; i < size; i++){
    nextNodes[i] = arrayOfNodes[i];
    if(i > 0)
      nameIndex[i-1] = nextNodes[i]->getNameIndex()[0];
  }
}

void TreeNode::insertLeaf(string name, int index, int endPos){
  bool isInserted = false;
  for(int i = 0; i < endPos; i++){
    if(this->leaves[i] && this->leaves[i]->first >= name){
      for(int j = endPos-1; j > i; j--)
        this->leaves[j] = this->leaves[j-1];
      this->leaves[i] = new pair<string, int>(name, index);
      isInserted = true;
      break;
    }
  }
  if(!isInserted){
    for(int i = 0; i < endPos; i++){
      if(this->leaves[i] == NULL){
        this->leaves[i] = new pair<string, int>(name, index);
        break;
      }
    }
  }
}
