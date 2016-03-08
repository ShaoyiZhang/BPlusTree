#ifndef _BTREEE_H_
#define _BTREEE_H_

const static int M = 5;   // num of max pointers to next level
const static int L = 3;   // num of max profiles 

class Level(){
private:
    int numOfKeysOccupied;
    string** keys               // pointer to an array of keys
    Level** nextLevels;         // pointer to anarray of pointers
    bool isLeaf;
public:
    Level():keys(NULL),nextLevels(NULL),isAboveLeaf(False),numOfKeysOccupied(0){};
    bool IsLeaf(){ return isLeaf; };
    Level* GetNextLevel() const;
    int IndexOfName() const;
};

class RoadMap():public Level{    
public:
    TreeNode():names(NULL),nextLevels(NULL),profiles(NULL),isAboveLeaf(False){};
    bool IsAboveLeaf(){ return isLeaf; };


};

class DataArray():public Level{
    // int indicate the location in the text file
};


class BTree{
private:
   TreeNode* root 
   int count;
public:
	BTree():root(NULL),count(0){};
    int GetCount(){ return count; };
    void Insert(string name,int fileLocation);
    pair<string, int>* FindHelper(string name);
};

#endif