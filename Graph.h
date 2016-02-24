#include <iostream>

using namespace std;

class Node{
 public:
  string name;
  Node* next;
  Node(){name = ""; next = NULL;}
  Node(string name){this->name = name; next = NULL;}
  Node(string name, Node* next){this->name = name; this->next = next;}
};

class Graph{
 private:
  static const int TABLE_SIZE = 201;
  Node** table;
 public:
  Graph();
  int hash(string input, int seed=0){
    int hash = seed;
    for(int i = 0; i < input.length(); i++){
      hash = hash*101 + input[i];
    }
    return hash % TABLE_SIZE;
  }
  pair<int, bool> helpInsert(string name);
  void insert(Node* node);
  void insert(string input);
  Node* find(string name);

};
