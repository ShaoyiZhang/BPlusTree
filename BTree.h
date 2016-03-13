#ifndef _BTREEE_H_
#define _BTREEE_H_

#include <iostream>
using namespace std;

const int M = 5;   // num of max pointers to next level
const int L = 3;   // num of max profiles 
class InternalNode;
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
    Node* GetParent(){ return parent; };
    void SetParent(Node* parent){ parent=parent; };
    void IncrOccupancy(){ occupancy++; };
    Node* GetNextLevel(string key) const;
    int IndexOfChild(string key) const;
    void Add(Node* child,Node* root);
    void Add(string key, int value, Node* root);
    ~Node();
    void SplitNoneLeaf(Node* root);
    void SplitRoot(Node* root);
    void SplitLeaf(Node* root);
    void Print();
    Node** GetChildren(){ return children; };
    Node* GetNext(){ return next; };
    Node* GetPrevious(){ return previous; };
    void SetNext(Node* next){ next = next; };
    void SetPrevious(Node* previous){ previous = previous; };

    //int IndexOfKey(string name, int capacity) const;
};
/*
class InternalNode:public Node{
private:
    //const static int capacity = M; 
    Node** children;         // pointer to an array of pointers    
public:
    InternalNode():Node(false,M),children(new Node*[M]){};
    InternalNode(InternalNode* parent):Node(false,parent,M),children(new Node*[M]){};
    int IndexOfChild(string name) const;
    Node* GetNextLevel(string key) const;
    void SplitNonLeaf(InternalNode* root);
    void SplitRoot(InternalNode* root);
    void Add(Node* child,InternalNode* root);
    //Node* GetChildrenAt(int index) const { return children[index]; };
    Node** GetChildren(){ return children; };
    ~InternalNode();
};

class LeafNode:public Node{
private:
    //const static int capacity = L;
    int* values;          // int indicate the location in the text file
    LeafNode* next;
    LeafNode* previous;
public: 
    // key = name, value = fileLocation
    LeafNode():Node(true,L),values(new int[L]),next(NULL),previous(NULL){};
    LeafNode(InternalNode* parent):Node(true,parent,L),values(new int[L]),next(NULL),previous(NULL){};
    LeafNode(string key,int value,InternalNode* parent):Node(true,parent,L),values(new int[L]),next(NULL),previous(NULL){SetKeyAt(0, key); values[0]=value; };
    void SplitLeaf(InternalNode* root);
    void Add(string name,int value,InternalNode* root);
    LeafNode* GetNext(){ return next; };
    LeafNode* GetPrevious(){ return previous; };
    void SetNext(LeafNode* next){ next = next; };
    void SetPrevious(LeafNode* previous){ previous = previous; };
    void Print();
    ~LeafNode();
};
*/
// BTree has a root node which is of type InternalNode
// The children ptrs of root might be LeafNode AND InternalNode
class BTree{
private:
   Node* root;
   int count;
public:
	BTree():root(new Node()),count(0){};
    int GetCount(){ return count; };
    void Insert(string key,int value);
    Node* SearchHelper(string key, Node* current) const;
    Node* GetRoot(){ return root; };
    bool Search(string key) const;
    Node* InsertHelper(string key, Node* current);
    void PrintAll(){ PrintAll(root); };
    void PrintAll(Node* root);
};

#endif