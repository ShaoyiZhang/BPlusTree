#ifndef _BTREEE_H_
#define _BTREEE_H_

#include <iostream>
using namespace std;

const int M = 5;   // num of max pointers to next level
const int L = 3;   // num of max profiles 

class Node(){
private:
    int capacity;
    int occupancy;
    bool isLeaf;
    string* keys;               // pointer to an array of keys
    Node* parent;
public:
    Node():keys(NULL),parent(NULL),isLeaf(False),occupancy(0),capacity(0);
    Node(bool isLeaf, int capcity):keys(NULL),isLeaf(isLeaf),occupancy(0),capacity(capacity),parent(NULL);
    Node(bool isLeaf, InternalNode* parent,int capcity):keys(NULL),parent(parent),isLeaf(isLeaf),occupancy(0),capacity(capacity);
    bool IsLeaf(){ return isLeaf; };
    int GetCapcity(){ return capacity; };
    int GetOccupancy(){ return occupancy; };
    int IndexOfKey(string name) const;
    int GetKeyAt(int index) const { return keys[index]; };
    //int IndexOfKey(string name, int capacity) const;
};

class InternalNode():public Node{
private:
    //const static int capacity = M; 
    Node** children;         // pointer to an array of pointers    
public:
    InternalNode():Node(false,M);
    InternalNode(InternalNode* parent):Node(false,parent,M);
    int IndexOfChild(string name);
    Node* GetNextLevel() const;
    Node* GetChildren() const { return children; };
};

class LeafNode():public Node{
private:
    //const static int capacity = L;
    int* values;          // int indicate the location in the text file
    Node* next;
    Node* previous;
public: 
    // key = name, value = fileLocation
    LeafNode():Node(true,L),next(NULL),previous(NULL);
    LeafNode(InternalNode* parent):Node(true,parent,L),next(NULL),previous(NULL);
    void SplitLeaf();
    void Add(string name,int value);
    LeafNode* GetNext(){ return next; };
    LeafNode* GetPrevious(){ return previous; };
    void SetNext(LeafNode* next){ next = next; };
    void SetPrevious(LeafNode* previous){ previous = previous; };    
};

// BTree has a root node which is of type InternalNode
// The children ptrs of root might be LeafNode AND InternalNode
class BTree{
private:
   InternalNode* root 
   int count;
public:
	BTree():root(NULL),count(0){};
    int GetCount(){ return count; };
    void Insert(string name,int fileLocation);
    void SplitRoot();
    LeafNode* SearchHelper(string name, Node* current) const;
    bool Search(string key) const;

};

#endif