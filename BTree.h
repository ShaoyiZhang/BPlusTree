#ifndef _BTREEE_H_
#define _BTREEE_H_

#include <iostream>
using namespace std;

const int M = 5;   // num of max pointers to next level
const int L = 3;   // num of max profiles 
class InternalNode;
class Node{
protected:
    string* keys;               // pointer to an array of keys
    InternalNode* parent;
    bool isLeaf;
    int occupancy;
    int capacity;
public:
    Node():keys(new string[L]),parent(NULL),isLeaf(false),occupancy(0),capacity(0){};
    Node(bool isLeaf, int capacity):keys(new string[L]),isLeaf(isLeaf),occupancy(0),capacity(capacity),parent(NULL){};
    Node(bool isLeaf, InternalNode* parent,int capacity):keys(new string[L]),parent(parent),isLeaf(isLeaf),occupancy(0),capacity(capacity){};
    virtual bool IsLeaf(){ return this->isLeaf; };
    int GetCapcity() const { return capacity; };
    int GetOccupancy() const { return occupancy; };
    int IndexOfKey(string key) const;
    string GetKeyAt(int index) const { return keys[index]; };
    void SetKeyAt(int index,string key){ this->keys[index]=key; };
    InternalNode* GetParent(){ return parent; };
    void SetParent(InternalNode* parent){ parent=parent; };
    void IncrOccupancy(){ occupancy++; };
    virtual ~Node();
    //int IndexOfKey(string name, int capacity) const;
};

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

// BTree has a root node which is of type InternalNode
// The children ptrs of root might be LeafNode AND InternalNode
class BTree{
private:
   InternalNode* root;
   int count;
public:
	BTree():root(new InternalNode()),count(0){};
    int GetCount(){ return count; };
    void Insert(string key,int value);
    LeafNode* SearchHelper(string key, Node* current) const;
    InternalNode* GetRoot(){ return root; };
    bool Search(string key) const;
    InternalNode* InsertHelper(string key, Node* current);
    void PrintAll(){ PrintAll(root); };
    void PrintAll(Node* root);
};

#endif