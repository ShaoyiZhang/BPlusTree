#include "BTree.h"
#include <iostream>
#include <math.h>
#include <climits>
Node::Node(bool isLeaf):keys(NULL),values(NULL),children(NULL),parent(NULL),isLeaf(isLeaf),occupancy(0),capacity(0){
    if (isLeaf==true){
        keys = new string[L+1];
        values = new int[L+1];
        for(int i = 0; i < L; i++){
            values[i] = INT_MIN;
            keys[i] = "";
        }
        capacity = L;
    } 
    else{
        keys = new string[M];
        children = new Node*[M+1];
        for (int i = 0; i < M; i++){
            children[i]=NULL;
            keys[i] = "";
        }
        children[M] = NULL;
        capacity = M;
    }
}

Node::Node(bool isLeaf, Node* parent):keys(NULL),values(NULL),children(NULL),parent(NULL),isLeaf(isLeaf),occupancy(0),capacity(0){
    this->parent = parent;    
    if (isLeaf==true){
        keys = new string[L+1];
        values = new int[L+1];
        for(int i = 0; i < L; i++){
            values[i] = INT_MIN;
            keys[i] = "";
        }
        
        capacity = L;
    } 
    else{
        keys = new string[M];
        children = new Node*[M+1];
        for (int i = 0; i < M; i++){
            children[i]=NULL;
            keys[i] = "";
        }
        children[M] = NULL;
        capacity = M;   
    }
}



Node::~Node(){
    delete keys;
    delete values;
    delete parent;
    delete [] children;
}

// a function for LeafNode (data goes here)
// return the index of a given key in the keys array
// if name is NOT present in the array, return -1
int Node::IndexOfKey(string key) const{
    int index = 0;
    for (int i = 0; i < occupancy; i++){
        if (key>=keys[i])
            index++;
    }
    return index;
}

// returns a pointer to next level
// the pointer may point to either InternalNode or LeafNode
Node* Node::GetNextLevel(string key) const{
    if(this->isLeaf)
        return NULL;
    return this->children[IndexOfChild(key)];
}

// A function for InternalNode (Road map)
// return the index of the pointer which lead us to next level
int Node::IndexOfChild(string key) const{
    int index = 0;
    while (index < occupancy-1 && key >= keys[index]){
        //cout << "capacity"<<this->GetCapcity()<<endl;
        index++;
    }
    //cout<<"index"<< index << endl;
    return index;
}

void Node::SplitNoneLeaf(Node* root){

    int middle = ceil(M/2);
    int index = 0;
    Node* newRoad = new Node(false);
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

// add node to noneleaf
void Node::Add(Node* child,Node* root){
    // NoneLeafNode case
    int index = this->IndexOfChild(child->keys[0]);
    index ++;
    for (int i = occupancy-1; i >= index;i--){
        //SetKeyAt(i+1,GetKeyAt(i));
        keys[i]=keys[i-1];
        children[i] = children[i-1];
    }
    this->children[index]=child;
    keys[index-1] = children[index]->GetKeyAt(0);
    occupancy++;
    // if the none leaf node is FULL
    // need to split
    if (occupancy>=capacity){
        if (parent == NULL){
            SplitRoot(root);
            return;
        }
        else
            SplitNoneLeaf(root);
    }
}

// Add key-value to Leaf
void Node::Add(string key, int value, Node* root){
    int index = this->IndexOfKey(key);
    for (int i=this->occupancy-1;i>=index;i--){
        //SetKeyAt(i+1, GetKeyAt(i));
        keys[i+1]=keys[i];
        values[i+1] = values[i];
    }
    SetKeyAt(index, key);
    values[index]=value;
    occupancy ++;
    if (this->occupancy>this->capacity){
        SplitLeaf(root);
    }
}


void Node::SplitRoot(Node* root){
    Node* latterHalf = new Node(false);
    int middle = ceil(M/2);
    int index = 0;
    // for now, occupancy = 5 = capacity = M
    // copy half of keys to new node
    for (int i = middle; i<occupancy; i++){
        latterHalf->keys[index]=this->keys[i];
        //latterHalf->SetKeyAt(index, this->GetKeyAt(i));
        index++;
    }
    index = 0;
    // copy half of children to new node
    for (int i = middle; i<=GetOccupancy(); i++){
        latterHalf->children[index]=this->children[i];
        index++;
    }
    return;
}

void Node::SplitLeaf(Node* root){
    Node* newLeaf = new Node(true);
    for (int i = L; i >= ceil(static_cast<double>(L)/2); i--){
        // copy latterHalf(index 2,3) to new leaf
        newLeaf->Add(keys[i], values[i],root);
        keys[i] = "";
        values[i]=INT_MIN;
        this->occupancy--;
    }
    newLeaf->next = this->next;
    newLeaf->parent = this->parent;
    newLeaf->previous = this;
    this->next = newLeaf;
    // insert new leaf to parent (which must be none-leaf)
    this->parent->Add(newLeaf,root);
    //cout << "splitleaf" << endl;
    // Add function automatically split parent if necessary
}

void Node::Print(){
    if (IsLeaf()){
        for (int i = 0; i < this->occupancy; i++){
            cout << "Key: "<< this->keys[i] << " Value: " << this->values[i] << endl;
        }
    }
}

void BTree::Insert(string key, int value){
    Node* parent = InsertHelper(key,root);
    Node* leaf = parent->GetNextLevel(key);
    int indexOfChild = parent->IndexOfChild(key);
    if(count == 0){
        count ++;
        parent->Add(key, value, root);
    }
    else if(count == 1){
        count ++;
        Node* newRoot = new Node(false, NULL);
        string temp1 = root->GetKeyAt(0);
        int temp2 = root->GetValueAt(0);
        root = newRoot;
        Insert(key, value);
        Insert(temp1, temp2);
        root->SetKeyAt(0, max(key, temp1));
        count --;
    }
    //assert(indexOfChild<M);
    else if (leaf == NULL){
        count ++;
        Node* newLeaf = new Node(true,parent);
        newLeaf->SetKeyAt(0, key);
        newLeaf->SetValueAt(0,value);
        parent->GetChildren()[indexOfChild] = newLeaf;
        // if newLeaf is the first leaf in that level
        // its previous should be NULL
        if (indexOfChild==0){
            newLeaf->SetPrevious(NULL);
        }
        else{
            newLeaf->SetPrevious(parent->GetChildren()[indexOfChild-1]);
            newLeaf->GetPrevious()->SetNext(newLeaf);
        }
        newLeaf->SetNext(NULL);
        //newLeaf->SetKeyAt(indexOfChild, key);
        newLeaf->IncrOccupancy();
        parent->IncrOccupancy();
    }
    // leaf already exist, insert to leaf
    // check if need to split leaf
    else{
        count ++;
        leaf->Add(key,value,this->GetRoot());
    }
}

// return a pointer points to the LAST level of the Road Map
// this level is right above the leaves
// thus we can construct pointers between leaves
// to make Range Qurey fast
Node* BTree::InsertHelper(string key, Node* current){
    Node* result = current;
    while(true){
        if (result->GetParent()==NULL)
            break;/*
        if (!result->IsLeaf()){
            if (result->GetChildren()[0]){
                result->GetChildren()[0]->IsLeaf();
                break;
            }
        }*/
        else
            result = current->GetNextLevel(key);
    }
    return result;
}

// given a key and a node, search for the key
// return a pointer to a leaf node that might contains record
Node* BTree::SearchHelper(string key, Node* current) const{
    if (current == NULL)
        return NULL;
    else if (current->IsLeaf())
        return current;
    else{
        return SearchHelper(key,current->GetNextLevel(key));
    }
}

// calls search helper to look for key
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

// void BTree::PrintAll(Node* root){
//     if (root == NULL)
//         return;
//     else if (root->IsLeaf()){
//         root->Print();
//     }
//     else{
//         for(int i = 0; i < root->GetOccupancy(); i++)
//             PrintAll(root->GetChildren()[i]);
//     }
// }

void BTree::PrintAll(Node* root){
    if(root == NULL)
        return;
    if(root->IsLeaf()){
        while(root->GetNext() != NULL){
            root->Print();
            root = root->GetNext();
        }
        root->Print();
    }
    else
        PrintAll(root->GetChildren()[0]);
}
