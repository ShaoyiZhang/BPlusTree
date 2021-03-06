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

// add node to noneleaf
Node* Node::Add(Node* child,Node* root){
    // NoneLeafNode case
    int index = this->IndexOfChild(child->keys[0]);
    index ++;
    for (int i = occupancy-1; i >= index;i--){
        keys[i]=keys[i-1];
        children[i+1] = children[i];
    }
    this->children[index]=child;
    child->SetParent(this);
    keys[index-1] = children[index]->GetKeyAt(0);
    occupancy++;
    // if the none leaf node is FULL
    // need to split
    if (occupancy>capacity){
        if (parent == NULL){
            return SplitRoot(root);
        }
        else
            return SplitNoneLeaf(root);
    }
    return NULL;
}

// Add key-value to Leaf
Node* Node::Add(string key, int value, Node* root){
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
        Node* temp = SplitLeaf(root);
        if (temp)
            return temp;
    }
    return NULL;
}


Node* Node::SplitRoot(Node* root){
    Node* latterHalf = new Node(false);
    int middle = ceil(static_cast<double>(M)/2);
    int index = 0;
    // for now, occupancy = 6 = capacity = M
    // copy half of keys to new node
    // key index 3,4 go to new node
    for (int i = middle; i<occupancy-1; i++){
        latterHalf->keys[index]=this->keys[i];
        keys[i] = "";
        //latterHalf->SetKeyAt(index, this->GetKeyAt(i));
        index++;
    }
    index = 0;
    // copy half of children to new node
    // child index 3,4,5 go to new node
    int origOccupancy = occupancy;
    for (int i = middle; i<origOccupancy; i++){
        latterHalf->children[index]=this->children[i];
        latterHalf->children[index]->SetParent(latterHalf);
        index++;
        children[i]=NULL;
        latterHalf->occupancy++;
        this->occupancy--;
    }
    Node* newRoot = new Node(false);
    Node* temp = latterHalf;
    while (!temp->IsLeaf()){
        temp = latterHalf->GetChildren()[0];
    }
    // temp is leaf now
    newRoot->SetKeyAt(0,temp->GetKeyAt(0));
    newRoot->SetChildrenAt(0, this);
    this->SetParent(newRoot);
    newRoot->SetChildrenAt(1, latterHalf);
    latterHalf->SetParent(newRoot);
    newRoot->IncrOccupancy();
    newRoot->IncrOccupancy();
    return newRoot;
}

Node* Node::SplitNoneLeaf(Node* root){
    Node* latterHalf = new Node(false);
    int middle = ceil(static_cast<double>(M)/2);
    int index = 0;
    // for now, occupancy = 6 = capacity = M
    // copy half of keys to new node
    // key index 3,4 go to new node
    for (int i = middle; i<occupancy-1; i++){
        latterHalf->keys[index]=this->keys[i];
        keys[i] = "";
        index++;
    }
    index = 0;
    // copy half of children to new node
    // child index 3,4,5 go to new node
    int origOccupancy = occupancy;
    for (int i = middle; i<origOccupancy; i++){
        latterHalf->children[index]=this->children[i];
        latterHalf->children[index]->SetParent(latterHalf);
        index++;
        children[i]=NULL;
        latterHalf->occupancy++;
        this->occupancy--;
    }
    Node* temp = this->GetParent()->Add(latterHalf,root);
    if (temp!=NULL)
        root = temp;
    return root;
}

Node* Node::SplitLeaf(Node* root){
    Node* newLeaf = new Node(true);
    for (int i = L; i >= ceil(static_cast<double>(L)/2); i--){
        // copy latterHalf(index 2,3) to new leaf
        newLeaf->Add(keys[i], values[i],root);
        keys[i] = "";
        values[i]=INT_MIN;
        this->occupancy--;
    }
    // this->next might be 0x646576697265442f
    // this->previous might be 0x65646f63582f0009
    // should not happen since we initialize all nodes' next and previous to NULL at the first place
    if (this->next!=NULL/*&&this->next->keys[0]!=""*/)
        this->next->SetPrevious(newLeaf);
    newLeaf->next = this->next;
    newLeaf->parent = this->parent;
    newLeaf->previous = this;
    this->next = newLeaf;
    // insert new leaf to parent (which must be none-leaf)
    // if this is not root
    if(this->parent != NULL){
        Node* temp = this->parent->Add(newLeaf,root);
        if (temp!=NULL)
            root = temp;
    }
    // current node is root
    else{
        Node* newRoot = new Node(false);
        Node* temp = root;
        root = newRoot;
        newRoot->SetChildrenAt(0, temp);
        temp->SetParent(root);
        newRoot->IncrOccupancy();
        root->Add(newLeaf, this);
    }
    return root;
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
    if (parent->IsLeaf()){
        count ++;
        Node* tempRoot = parent->Add(key,value, root);
        if (tempRoot!= NULL)
            root = tempRoot;
    }
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
        newLeaf->IncrOccupancy();
        parent->IncrOccupancy();
    }
    // leaf already exist, insert to leaf
    // check if need to split leaf
    else{
        count ++;
        Node* temp = leaf->Add(key,value,this->GetRoot());
        if (temp)
            this->root = temp;
    }
}

// return a pointer points to the LAST level of the Road Map
// this level is right above the leaves
// thus we can construct pointers between leaves
// to make Range Qurey fast
Node* BTree::InsertHelper(string key, Node* current){
    Node* result = current;
    while(true){
        if (count<=3)
            break;
        if (result->GetChildren()[0]->IsLeaf() == true)
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
    if (current->IsLeaf())
        return current;
    return SearchHelper(key, current->GetNextLevel(key));
}

// calls search helper to look for key
bool BTree::Search(string key) const{
    Node* result = SearchHelper(key,root);
    // result must be a leaf node or NULL
    if (result){
        for (int i = 0; i < result->GetOccupancy(); i++){
            if (result->GetKeyAt(i) == key){
	      cout << "Key: " << key << " Value: " << result->GetValueAt(i) << endl;
                return true;
            }
        }
        cout << "Not find!" << endl;
        return false;
    }
    // if result == NULL
    else{
        cout << "Not find!" << endl;
        return false;
    }
}

/*void BTree::PrintAll(Node* root){
    if (root == NULL)
        return;
    else if (root->IsLeaf()){
         root->Print();
    }
    else{
        for(int i = 0; i < root->GetOccupancy(); i++)
            PrintAll(root->GetChildren()[i]);
    }
 }
*/

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

void BTree::PrintAllKeys(Node *root){
    if(root == NULL)
        return;
    root->PrintAllKeys();
    if(!root->IsLeaf())
        for(int i = 0; i < M; i++)
            PrintAllKeys(root->GetChildren()[i]);
}

void BTree::PrintBetween(string start, string end) {
    Node* begin = SearchHelper(start, root);
    Node* ending = SearchHelper(end, root);
    //std::ostringstream oss;
    ///////// INDICATE NOTHING BETWEEN
    
    
    
    if (begin!=NULL){
        // print valid output in Node* start
        for (int i = 0; i<begin->GetOccupancy(); i++){
            if (begin->GetKeyAt(i)>=start)
	      cout<< "Key: " << begin->GetKeyAt(i) << " Value:" << begin->GetValueAt(i) << endl;
        }
	if(begin != ending){
	  Node* current = begin->GetNext();
	  // loop to print all data until Node* ending
	  while (current!=NULL && current!=ending) {
            current->Print();
            current=current->GetNext();
	  }
        // print valid output in Node* ending
	  for (int i = 0; i<begin->GetOccupancy(); i++){
            if (ending->GetKeyAt(i)<=end && ending->GetKeyAt(i)!="")
	      cout<<"Key: " << ending->GetKeyAt(i)<<" Value: "<< ending->GetValueAt(i) << endl;
	  }
        }
    }
}




