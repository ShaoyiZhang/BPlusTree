#include "Graph.h"

Graph::Graph(){
  table = new Node* [TABLE_SIZE];
  for(int i = 0; i < TABLE_SIZE; i++){
    table[i] = NULL;
  }
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

void Graph::insert(string input){
  int length = input.length();
  if (length == 0)
    return;
  string temp = "";
  int current = 0;
  while(current < length && input[current] != ','){
    temp += input[current];
    current ++;
  }

  Node* init = new Node(temp);
  insert(init);
  Node* last = init;

  int count = 0;
  current ++;
  while(current < length && count < 2){
    current ++;
    if(input[current] == ',')
      count ++;
  }
  current ++;
  temp = "";
  while(current < length){
    if(input[current] == ',' && temp.length() != 0){
      Node* tmpNode = new Node(temp);
      last->next = tmpNode;
      last = last->next;
      temp = "";
    }
    else
      temp += input[current];
  }
  if(temp.length() != 0){
    Node* tmpNode = new Node(temp);
    last->next = tmpNode;
    last = last->next;
    temp = "";
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

