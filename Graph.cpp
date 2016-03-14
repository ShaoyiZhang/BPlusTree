#include "Graph.h"

void GraphNode::addFriend(string input){
  GraphNode* temp = this;
  while(temp->next){
    if(input == temp->name)
      return;
    temp = temp->next;
  }
  GraphNode* newFriend = new GraphNode(input);
  temp->next = newFriend;
}

Graph::Graph(){
  table = new GraphNode* [TABLE_SIZE];
  for(int i = 0; i < TABLE_SIZE; i++){
    table[i] = NULL;
  }
}

int Graph::hash(string input, int seed){
  unsigned int hash = seed;
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

void Graph::insert(GraphNode* node){
  pair<int, bool> index = helpInsert(node->name);
  if (!index.second)
    table[index.first] = node;
}

void Graph::insert(string name){
  pair<int, bool> index = helpInsert(name);

  if (!index.second){
    GraphNode* node = new GraphNode(name);
    table[index.first] = node;
  }

}

void Graph::insert(vector<string> input){
  int length = input.size();
  if (length == 0)
    return;

  GraphNode* init = new GraphNode(input[0]);
  insert(init);
  GraphNode* last = init;

  if(length < 4)
    return;

  for(int i = 3; i < length; i++){
    GraphNode* tmpGraphNode = new GraphNode(input[i]);
    last->next = tmpGraphNode;
    last = last->next;
    GraphNode* myFriend = find(input[i]);
    if(myFriend){
      myFriend->addFriend(input[0]);
    }
  }
}

GraphNode* Graph::find(string name){
  pair<int, bool> index = helpInsert(name);

  if(index.second){
    GraphNode* temp = table[index.first];
    return temp;
  }
  else
    return NULL;
}

void Graph::printAll(){
  for(int i = 0; i < TABLE_SIZE; i++){
    if(table[i]){
      GraphNode* temp = table[i];
      while(temp){
        cout << temp->name << " ";
        temp = temp->next;
      }
      cout << "\n";
    }

  }

}
