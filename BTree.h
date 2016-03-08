#ifndef _BTREEE_H_
#define _BTREEE_H_

const static int M = 5;   // num of max pointers to next level
const static int L = 3;   // num of max profiles 

class Node(){
private:
    string** names;             // pointer to an array of keys
    Node** nextLevels;          // pointer to anarray of pointers
    pair<string,int>** profiles  // array of profile
                                // int indicate the location in the text file
    bool isLeaf;
    int numOfKeys;          
public:
    Node():names(NULL),nextLevels(NULL),profiles(NULL),isAboveLeaf(False){};
    bool IsLeaf(){ return isLeaf; };
    Node* GetNextLevel() const;
    int IndexOfName() const;
};


class BTree{
private:
   Node* root 
   int count;
   pair<string, int>* SearchHelper(string name);
public:
	BTree():root(NULL),count(0){};
    int GetCount(){ return count; };
    void Insert(string name,int fileLocation);
    
};

#endif