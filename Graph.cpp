#include "Graph.h"

Graph::Graph(){
  table = new Node* [TABLE_SIZE];
  for(int i = 0; i < TABLE_SIZE; i++){
    table[i] = NULL;
  }
}

int Graph::hash(string input, int seed=0){
    int hash = seed;
    for(int i = 0; i < input.length(); i++){
      hash = hash*101 + input[i];
    }
    return hash % TABLE_SIZE;
  }

pair<int, bool> Graph::helpInsert(string name){
  int index = hash(name);
  while(table[index] && table[index]->name != name)
    index  = (index + 1) % TABLE_SIZE;

  //if we find a same element
  if(table[index] && table[index]->name == name){
    pair<int, bool> result(index, 1);
    return result;
  }

  //if we find a empty slot
  pair<int, bool>result(index, 0);
  return result;
}

void Graph::insert(Node* node){
  pair<int, bool> index = helpInsert(node->name);

  if (!index.second)
    table[index.first] = node;
}

void Graph::insert(string name){
  pair<int, bool> index = helpInsert(name);

  if (!index.second){
    Node* node = new Node(name);
    table[index.first] = node;
  }

}

void Graph::insert(vector<string> input){
  int length = input.size();
  if (length == 0)
    return;

  Node* init = new Node(input[0]);
  insert(init);
  Node* last = init;

  if(length < 4)
    return;

  for(int i = 3; i < length; i++){
    Node* tmpNode = new Node(input[i]);
    last->next = tmpNode;
    last = last->next;
  }
}

Node* Graph::find(string name){
  pair<int, bool> index = helpInsert(name);

  if(index.second){
    Node* temp = table[index.first];
    return temp;
  }
  else
    return NULL;
}

