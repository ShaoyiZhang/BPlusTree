#include "BTree.h"

TreeNode::TreeNode(){
  isLeaf = false;

  index = -1;
  nameIndex = new string[M-1];
  for(int i = 0; i < M-1; i++){
    nameIndex[i] = "";
  }

  leaves = new pair<string, int>* [L];
  for(int i = 0; i < L; i++)
    leaves[i] = NULL;


}

//constructor for a leaf
TreeNode::TreeNode(string name, int index){
  isLeaf = true;

  nameIndex = new string[M-1];
  for(int i = 0; i < M-1; i++){
    nameIndex[i] = "";
  }

  leaves = new pair<string, int>* [L];
  for(int i = 0; i < L; i++)
    leaves[i] = NULL;

  nextNodes = new TreeNode* [M];
  for(int i = 0; i < M; i++)
    nextNodes[i] = NULL;

  pair<string, int>* temp = new pair<string, int>(name, index);
  leaves[0] = temp;
}

BTree::BTree(){
  root = NULL;
}

pair<pair<string, int>*, bool>* BTree::find(string name){
  TreeNode* current = root;
  int index = 0;
  while(current && !current->checkLeaf() && current->getNameIndex()){
    while(index < M-1 && current->getNameIndex()[index].length() != 0 && name >= current->getNameIndex()[index])
      index ++;
    current = current->getNextNodes()[index];
  }

  //up to here current is at a leaf
  index = 0;
  while(index < L && current->getLeaves()[index] != NULL
        && name > current->getLeaves()[index]->first)
    index ++;


  //if it finds a node, return the info and true
  if(name == current->getLeaves()[index]->first){
    pair<string, int>* temp = new pair<string, int>(*current->getLeaves()[index]);
    pair<pair<string, int>*, bool>* result = new pair<pair<string, int>*, bool>(temp, true);
    return result;
  }

  //if it doesn't find the node, return a pointer to where it should be and false
  //not sure if this is useful
  pair<string, int>* temp = current->getLeaves()[index];
  pair<pair<string, int>*, bool>* result = new pair<pair<string, int>*, bool>(temp, false);
  return result;
}

void BTree::insert(string name, int index){
  if (root == NULL){
    TreeNode* temp = new TreeNode(name, index);
    root = temp;
    return;
  }

}
