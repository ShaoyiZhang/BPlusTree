#include <iostream>
#include <vector>

using namespace std;

class GraphNode{
 public:
  string name;
  GraphNode* next;
  GraphNode(){name = ""; next = NULL;}
  GraphNode(string name){this->name = name; next = NULL;}
  GraphNode(string name, GraphNode* next){this->name = name; this->next = next;}
  void addFriend(string input);
};

class Graph{
 private:
  static const int TABLE_SIZE = 211;
  GraphNode** table;
 public:
  Graph();
  int hash(string input, int seed=0);
  pair<int, bool> helpInsert(string name);
  void insert(GraphNode* node);
  void insert(vector<string> input);
  void insert(string name);
  GraphNode* find(string name);
  void printAll();
};
