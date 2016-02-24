#include "Graph.h"

Graph::Graph(){
  table = new Node* [TABLE_SIZE];
  for(int i = 0; i < TABLE_SIZE; i++){
    table[i] = NULL;
  }
}

pair<int, bool> Graph::helpInsert(string name){
  int index = hash(name);
  while(table[index] && table[index] != name)
    index  = (index + 1) % TABLE_SIZE;

  //if we find a same element
  if(table[index] && table[index] == name){
    pair<int, bool> result(index, 1);
    return result;
  }

  //if we find a empty slot
  pair<int, bool>result(index, 0);
  return result;
}

void Graph::insert(string name){
  pair<int, bool> index = helpInsert(name);

  if (!index.second){
    Node *temp = new Node(name);
    table[index.first] = temp;
  }
}

Node* find(string name){
  pair<int, bool> index = helpInsert(name);

  if(index.second){
    Node* temp = table[index.first];
    return temp;
  }
  else
    return NULL;
}
