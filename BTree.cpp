#include "BTree.h"

Node::Node(bool isAboveLeaf){
    this->names = new string* [M-1];
    this->nextLevels = new Node* [M];
    this->profiles = NULL;
    this->isAboveLeaf = isAboveLeaf;
    this->numOfKeys = 0;
}
Node* Node::GetNextLevel(string name){
    int index = 0;
    while (index < M && name > names[index]){
        index++;
        if (nextLevels[index] == NULL)
            break;
    }
    return nextLevels[index];
}

// return the index of a given name in the profile array
// if name is NOT present in the array, return -1
int Node::IndexOfName(string name){
    int index = -1;
    for (int i = 0; i<L; i++;){
        if (profiles[i]->first() == name){
            index = i;
        }
        if (profile[i+1] == NULL)
            break;
    }
    return index;
}

BTree::BTree(){
    Node* r = new Node(True);
}

BTree::Insert(string name, int fileLocation){
    // if there's nothing in the BTree
    if (count==0){
        root->profiles = new pair<string,int>* [L];
        root->profiles[0] = new pair<string,int>(name,fileLocation);
        count++;
    }
    // if there's one key in the root, but nothing else is in the tree
    else if (count == 1){
        if (name > root->names[0]){
            root->names[1] = name;
            root->profiles[1] = new pair<string,int>(name,fileLocation);
        }
        else{
            root->names[1] = root->names[0];
            root->profiles[1] = root->profiles[0];
            root->names[0] = name;
            root->profiles[0] = new pair<string,int>(name,fileLocation);
        }
        count++;
    }
    // there are 2 ~ M-2 profiles in the BTree
    // Insert into root 
    // until root is full -> numOfKeys = M-1
    else if (count >= 2 && count <= M-2){
        root->names[]
    }
    // the root is full
    else{
        
    }
}

// insert key to the right place
// return a pointer to the array of profile
Node* BTree::InsertKey()

// given a key and a node, search for the key
// return a leaf node that contains record
Node* BTree::SearchHelper(string name, Node* current) const{
    if (current->IsLeaf())
        return current;
    else{
        SearchHelper(current->GetNextLevel(name));
    }
}    
    /*Node* current = root;
    // traverse the road map
    while(current && !current->IsAboveLeaf() && current->GetNextLevel()){
            current = current->GetNextLevel();
    }
    // if the profile array does NOT contain the name we are looking for
    if (current->IndexOfName(name) == -1){
        return NULL;
    }
    else{
        return current->profiles[current->IndexOfName(name)];
    }
}*/

bool BTree::Search(string name) const{
    pair<string,int>* result = SearchHelper(name);
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