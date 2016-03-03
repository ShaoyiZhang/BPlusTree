#include "BTree.h"

BTree::BTree(){
  root = NULL;
}

pair<string, int>* BTree::find(string name){
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
    pair<string, int>* result = new pair<string, int>(*current->getLeaves()[index]);
    return result;
  }

  //if it doesn't find the node, return NULL
  return NULL;
}

pair<TreeNode*, TreeNode*>* BTree::splitLeaves(TreeNode* root, string name, int index){
  root->insertLeaf(name, index, L+1);
  TreeNode* back = new TreeNode();
  for(int i = L/2; i < L+1; i++){
    back->insertLeaf(root->getLeaves()[i]->first, root->getLeaves()[i]->second, L);
    delete root->getLeaves()[i];
    root->getLeaves()[i] = NULL;
  }
  pair<TreeNode*, TreeNode*>* result = new pair<TreeNode*, TreeNode*>(root, back);
  return result;
}

void BTree::insert(string name, int index){
  if (root == NULL){
    root = new TreeNode(name, index);;
    return;
  }

  if(find(name))
    return;
  if(root->checkLeaf()){
    if(root->getLeaves()[L-1]){
      pair<TreeNode*, TreeNode*>* temp = splitLeaves(root, name, index);
      TreeNode** arrayOfNodes = new TreeNode* [2];
      arrayOfNodes[0] = temp->first;
      arrayOfNodes[1] = temp->second;
      TreeNode* newRoot = new TreeNode(arrayOfNodes, 2);
      root = newRoot;
    }
    else{
      root->insertLeaf(name, index, L);
      return;
    }
  }
  //not finish
  // TreeNode* current = root;
  // int index = 0;
  // while(current && !current->checkLeaf() && current->getNameIndex()){
  //   while(index < M-1 && current->getNameIndex()[index].length() != 0 && name >= current->getNameIndex()[index])
  //     index ++;
  //   current = current->getNextNodes()[index];
  // }

}
