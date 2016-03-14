#ifndef _BTREEE_H_
#define _BTREEE_H_

#include <iostream>
using namespace std;

const int M = 5;   // num of max pointers to next level
const int L = 3;   // num of max profiles 

class Node{
private:
    string* keys;
    int* values;
    Node** children;
    Node* parent;
    bool isLeaf;
    int occupancy;
    int capacity;
    Node* previous;
    Node* next;
public:
    Node():keys(NULL),values(NULL),children(NULL),parent(NULL),isLeaf(false),occupancy(0),capacity(0),previous(NULL),next(NULL){};
    Node(bool isLeaf);
    Node(bool isLeaf, Node* parent);
    bool IsLeaf(){ return this->isLeaf; };
    int GetCapcity() const { return this->capacity; };
    int GetOccupancy() const { return this->occupancy; };
    int IndexOfKey(string key) const;
    string GetKeyAt(int index) const { return keys[index]; };
    void SetKeyAt(int index,string key){ this->keys[index]=key; };
    void SetValueAt(int index, int value){ this->values[index]=value; };
    int GetValueAt(int index){return this->values[index];};
    Node* GetParent(){ return parent; };
    void SetParent(Node* parent){ this->parent=parent; };
    void IncrOccupancy(){ occupancy++; };
    Node* GetNextLevel(string key) const;
    int IndexOfChild(string key) const;
    Node* Add(Node* child,Node* root);
    Node* Add(string key, int value, Node* root);
    ~Node();
    void SplitNoneLeaf(Node* root);
    Node* SplitRoot(Node* root);
    Node* SplitLeaf(Node* root);
    void Print();
    Node** GetChildren(){ return children; };
    void SetChildrenAt(int index, Node* child){ this->children[index] = child;};
    Node* GetNext(){ return next; };
    Node* GetPrevious(){ return previous; };
    void SetNext(Node* next){ this->next = next; };
    void SetPrevious(Node* previous){ this->previous = previous; };
    void PrintAllKeys(){
        for(int i = 0; i < occupancy-1; i++)
            cout << keys[i];
        cout << endl;
    };
};

// BTree has a root node which is of type InternalNode
// The children ptrs of root might be LeafNode AND InternalNode
class BTree{
private:
   Node* root;
   int count;
public:
	BTree():root(new Node(true)),count(0){};
    int GetCount(){ return count; };
    void Insert(string key,int value);
    Node* SearchHelper(string key, Node* current) const;
    Node* GetRoot(){ return root; };
    bool Search(string key) const;
    Node* InsertHelper(string key, Node* current);
    void PrintAll(){ PrintAll(root); };
    void PrintAll(Node* root);
    void PrintAllKeys(Node* root);
};

#endif
