#include "BTree.h"
#include <math.h>

Node::~Node(){
    delete keys;
    delete parent;
}

// a function for LeafNode (data goes here)
// return the index of a given key in the keys array
// if name is NOT present in the array, return -1
int Node::IndexOfKey(string key) const{
    int index = -1;
    for (int i = 0; i < occupancy; i++){
        if (key>=keys[i])
            index++;
    }
    return index;
}

// returns a pointer to next level
// the pointer may point to either InternalNode or LeafNode
Node* InternalNode::GetNextLevel(string key) const{
    return children[IndexOfChild(key)];
}

// A function for InternalNode (Road map)
// return the index of the pointer which lead us to next level
int InternalNode::IndexOfChild(string key) const{
    int index = 0;
    while (index < this->GetCapcity() && key > this->GetKeyAt(index)){
        index++;
        if (children[index+1] == NULL)
            break;
    }
    return index;
}

void InternalNode::SplitNonLeaf(InternalNode* root){

    int middle = ceil(M/2);
    int index = 0;
    InternalNode* newRoad = new InternalNode();
    for (int i = middle+1; i<=this->GetOccupancy(); i++){
        newRoad->GetKeyAt(i) = this->GetKeyAt(i);
        index++;
    }
    index = 0;
    for (int i = middle+1; i<=this->GetOccupancy(); i++){
        newRoad->children[index]=this->children[i];
        index++;
    }
    // finish copying, insert to parent
    // but if parent is root, things are differnt
    this->GetParent()->Add(newRoad,root);
    return;
}

void InternalNode::Add(Node* child,InternalNode* root){
    int index = this->IndexOfChild(child->GetKeyAt(0));
    for (int i=this->GetOccupancy()-1;i>=index;i--){
        SetKeyAt(i+1,GetKeyAt(i));
        children[i+1] = children[i];
    }
    this->children[index]=child;
    IncrOccupancy();
    if (this->GetOccupancy()>=this->GetCapcity()){
        if (this->GetParent() == NULL){
            //BTree b = BTree();
            SplitRoot(root);
            return;
        }
        else
            SplitNonLeaf(root);
    }
}

void InternalNode::SplitRoot(InternalNode* root){
    InternalNode* latterHalf = new InternalNode();
    int middle = ceil(M/2);
    int index = 0;
    // for now, occupancy = 5 = capacity = M
    for (int i = middle; i<this->GetOccupancy(); i++){
        latterHalf->SetKeyAt(index, this->GetKeyAt(i));
        index++;
    }
    index = 0;
    for (int i = middle; i<=GetOccupancy(); i++){
        latterHalf->children[index]=this->children[i];
        index++;
    }
    return;
}

InternalNode::~InternalNode(){
    delete []children;
}

/*
// creating a LeafNode from scratch
LeafNode(string key, int value, LeafNode* previous):LeafNode(){
    keys[0] = key;
    values[0] = value;
    this->previous = previous;
}*/

LeafNode::~LeafNode(){
    delete [] values;
    delete previous;
    delete next;
}

void LeafNode::SplitLeaf(InternalNode* root){
    LeafNode* newLeaf = new LeafNode();
    for (int i = L; i >= ceil(L/2); i--){
        // copy latterHalf(index 2,3) to new leaf
        newLeaf->Add(this->GetKeyAt(i), values[i],root);
        this->SetKeyAt(i, "BLANK");
        this->values[i]=2147483647;
        newLeaf->SetPrevious(this);
        newLeaf->SetNext(this->GetNext());
        newLeaf->SetParent(this->GetParent());
        this->SetNext(newLeaf);
    }
    // insert new leaf to parent
    this->GetParent()->Add(newLeaf,root);
    // Add function automatically split parent if necessary
}

void LeafNode::Add(string key, int value, InternalNode* root){
    int index = this->IndexOfKey(key);
    for (int i=this->GetOccupancy()-1;i>=index;i--){
        SetKeyAt(i+1, GetKeyAt(i));
        values[i+1] = values[i]; 
    }
    SetKeyAt(index, key);
    values[index]=value;
    if (this->GetOccupancy()>=this->GetCapcity()){
        SplitLeaf(root);
    }
}

void BTree::Insert(string key, int value){
    LeafNode* leaf = SearchHelper(key,root);
    InternalNode* parent = leaf->GetParent();
    int indexOfChild = parent->IndexOfChild(key);
    //assert(indexOfChild<M);
    if (leaf == NULL){
        LeafNode* newLeaf = new LeafNode(key,value,parent);
        parent->GetChildren()[indexOfChild] = newLeaf;
        newLeaf->SetPrevious(dynamic_cast<LeafNode*>(parent->GetChildren()[indexOfChild-1]));
        newLeaf->SetNext(NULL);
    }
    // leaf already exist, insert to leaf
    // check if need to split leaf
    else{ 
        leaf->Add(key,value,this->GetRoot());
    }
    count++;
}

// given a key and a node, search for the key
// return a pointer to a leaf node that might contains record
LeafNode* BTree::SearchHelper(string key, Node* current) const{
    if (current == NULL)
        return NULL;
    else if (current->IsLeaf())
        return dynamic_cast<LeafNode*>(current);
    else{
        return SearchHelper(key,dynamic_cast<InternalNode*>(current)->GetNextLevel(key));
    }
}

bool BTree::Search(string key) const{
    Node* result = SearchHelper(key,root);
    if (result){
        cout << "Find!" << endl;
        return true;
    }
    // if result == NULL
    else{
        cout << "Not find!" << endl;
        return false;
    }   
}


