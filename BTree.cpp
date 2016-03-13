#include "BTree.h"
#include <math.h>

LeafNode(InternalNode* parent):Node(true),keys(NULL),next(NULL),previous(NULL){
    keys = new string[L];
    values = new int[L];
}

// creating a LeafNode from scratch
LeafNode(string key, int value, LeafNode* previous):LeafNode(){
    keys[0] = key;
    values[0] = value;
    this->previous = previous;
}

// returns a pointer to next level
// the pointer may point to either InternalNode or LeafNode
Node* InternalNode::GetNextLevel(string name){
    return children[IndexOfChild(name)];
}

// a function for LeafNode (data goes here)
// return the index of a given key in the keys array
// if name is NOT present in the array, return -1
int Node::IndexOfKey(string key){
    int index = -1;
    for (int i = 0; i < occupancy; i++){
        if (key>=keys[i])
            index++;
    }
    return index;
}

// A function for InternalNode (Road map)
// return the index of the pointer which lead us to next level
int InternalNode::IndexOfChild(string key){
    int index = 0;
    while (index < capacity && key > keys[index]){
        index++;
        if (children[index+1] == NULL)
            break;
    }
    return children[index];
}

BTree::BTree(){
    r = new InternalNode(NULL);
}

void BTree::Insert(string name, int fileLocation){
    LeafNoede* leaf = SearchHelper(name,root);
    InternalNode* parent = leaf->GetParent();
    int indexOfChild = ->IndexOfChild(name);
    assert(indexOfChild<M);
    if (leaf == NULL){
        parent[indexOfChild] = new LeafNode(name,fileLocation);
        parent[indexOfChild]->SetPrevious(parent[indexOfChild-1]);
        parent[indexOfChild]->SetNext(NULL);
    }
    // leaf already exist, insert to leaf
    // check if need to split leaf
    else{ 
        leaf->Add(key,value);
    }
}

void LeafNode::SplitLeaf(){
    LeafNode* newLeaf = new LeafNode();
    for (int i = L; i >= ceil(L/2); i--){
        // copy latterHalf(index 2,3) to new leaf
        newLeaf.Add(keys[i], values[i]);
        this->keys[i]="BLANK";
        this->values[i]=2147483647;
        newLeaf->SetPrevious(this);
        newLeaf->SetNext(this->GetNext());
        newLeaf->SetParent(this->GetParent());
        this->SetNext(newLeaf);
    }
    // insert new leaf to parent
    this->GetParent()->Add(newLeaf);
    // Add function automatically split parent if necessary
}

void InternalNode::SplitNonLeaf(){

    int middle = ceil(M/2);
    int index = 0;
    InternalNode* newRoad = new InternalNode();
    for (int i = middle+1; i<=occupancy; i++){
        newRoad.keys[index] = this->keys[i];
        index++;
    }
    index = 0;
    for (int i = middle+1; i<=occupancy; i++){
        newRoad.children[index]=this->children[i];
        index++;
    }
    // finish copying, insert to parent
    // but if parent is root, things are differnt
    this->GetParent().Add(newRoad);
    return;
}

void BTree::SplitRoot(){
    InternalNode* latterHalf = new InternalNode();
    int middle = ceil(M/2);
    int index = 0;
    // for now, occupancy = 5 = capacity = M
    for (int i = middle; i<occupancy; i++){
        latterHalf.keys[index] = this->keys[i];
        index++;
    }
    index = 0;
    for (int i = middle; i<=occupancy; i++){
        latterHalf.children[index]=this->children[i];
        index++;
    }
    return;
}


LeafNode::Add(string key, int value){
    int index = this->IndexOfKey(key);
    for (int i=occupancy-1;i>=index;i--){
        keys[i+1] = keys[i];
        values[i+1] = values[i]; 
    }
    keys[index]=key;
    values[index]=value;
    if (occupancy>=capacity){
        SplitLeaf();
    }
}

InternalNode::Add(Node* child){
    int index = this->IndexOfChild(child->GetKeyAt(0));
    for (int i=occupancy-1;i>=index;i--){
        keys[i+1] = keys[i];
        children[i+1] = children[i]; 
    }
    this->keys[index]=key;
    this->children[index]=child;
    occupancy++;
    if (occupancy>=capacity){
        if (this->GetParent() == NULL){
            SplitRoot();
            return;
        }
        else
            SplitNonLeaf();
    }
}




// given a key and a node, search for the key
// return a pointer to a leaf node that contains record
LeafNode* BTree::SearchHelper(string name, Node* current) const{
    if (current->IsLeaf())
        return current;
    else{
        SearchHelper(current->GetNextLevel(name));
    }
}    

bool BTree::Search(string name) const{
    Node* result = SearchHelper(name,root);
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
