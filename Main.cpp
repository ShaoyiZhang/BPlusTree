/*
 * Main.cpp
 *
 *  Created on: Feb 11, 2016
 *      Author: omid
 */
#include <assert.h>
#include "BTree.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;

vector<string> split(string str, char delimiter)
{
	vector<string> internal;
	stringstream ss(str);       // turn the string into a stream.
	string tok;

	while(getline(ss, tok, delimiter))
	{
		internal.push_back(tok);
	}

	return internal;
}

void padding(string inpath, string outpath){
  ifstream f;
  f.open(inpath, ios::in);
  ofstream o;
  o.open(outpath);
  string line, temp;
  while(std::getline(f, line)){
    vector<string>words = split(line, ',');
    temp += words[0];
    for(int i = words[0].length(); i < 20; i++)
      temp += "*";
    temp += words[1];
    for(int i = words[1].length(); i < 3; i++)
      temp += "*";
    temp += words[2];
    for(int i = words[2].length(); i < 30; i++)
      temp += "*";
    o << temp;
    temp = "";
  }
  f.close();
  o.close();
}

int main(int argc, char** argv)
{
        string inpath1 = "./FinalProjectTestCases/Generated1.txt";
        string outpath1 = "./FinalProjectTestCases/padding1.txt";
        padding(inpath1, outpath1);
        FILE* p1;
        p1=fopen("./FinalProjectTestCases/padding1.txt","r");
        int charSize = sizeof(char);
        int index = 0;
        fseek (p1 , index , SEEK_SET);
        size_t fileSize = ftell (p1);
        char name[21];
        fread(name,charSize,20,p1);
        printf("%s\n", name);
        
        char age[4];
        fseek(p1, index+20, SEEK_SET);
        fread(age, charSize, 3, p1);
        printf("%s\n", age);
        
        char occup[21];
        fseek(p1, index+23, SEEK_SET);
        fread(occup, charSize, 30, p1);
        printf("%s\n", occup);
        
        fclose(p1);
        
  BTree tree = BTree();
  Graph graph = Graph();
  string userInput;
  cout << "Enter your command; input 'help' for help" << endl;
  while(1){
    cin >> userInput;
    //cout << userInput << endl;
    
    if(userInput == "PrintGraph"){
      graph.printAll();
    }
    else if(userInput == "PrintTree"){
      tree.PrintAll();
    }
    
    else if(userInput == "Insert"){
      cout << "Input name" << endl;
      string name;
      cin >> name;
      int age;
      cout << "Input age" << endl;
      cin >> age;
      string occupation;
      cout << "Input occupation" << endl;
      cin >> occupation;
      
      GraphNode* added = new GraphNode(name);
      graph.insert(added);
      tree.Insert(name, tree.GetCount() * 53);
    }
    
    else if(userInput == "AddFriend"){
      cout << "Input first person" << endl;
      string firstone;
      cin >> firstone;
      
      cout << "Input second person" << endl;
      string secondone;
      cin >> secondone;

      graph.find(firstone)->addFriend(secondone);
      graph.find(secondone)->addFriend(firstone);
    }
    
    else if(userInput == "Initialize"){
      cout << "input the path" << endl;
      string tempPath;
      cin >> tempPath;
      ifstream f;
      string tempOutPath = "./FinalProjectTestCases/padding0.txt";
      f.open(tempPath, ios::in);
      if(!f){
	cerr << "File not found." << endl;
	continue;
      }
      padding(tempPath, tempOutPath);
      string line;
      int value = 0;
      while(std::getline(f, line)){
	vector<string> words = split(line, ',');
	graph.insert(words);
	tree.Insert(words[0], value);
	cout << words[0] << " " << value << endl;
	value += 53;
      }
    }
    else if(userInput == "help"){
      cout << "PrintGraph" << endl;
      cout << "PrintTree" << endl;
      cout << "Initialize" << endl;
      cout << "Insert" << endl;
      cout << "AddFriend" << endl;
      cout << "PrintBetween" << endl;
      cout << "PrintFriendInfo" << endl;
    }
    else if(userInput == "PrintBetween"){
      string lowerBound;
      string upperBound;
      cout << "input your lower bound" << endl;
      cin >> lowerBound;
      cout << "input your upper bound" << endl;
      cin >> upperBound;
      tree.PrintBetween(lowerBound, upperBound);
    }

    else if(userInput == "PrintFriendInfo"){
      string name;
      cout << "Enter name" << endl;
      cin >> name;
      for(GraphNode* temp = graph.find(name)->next; temp != NULL; temp = temp->next){
	tree.Search(name);
      }
    }
    else{
      //cout << "Enter next command" << endl;
    }
    
    userInput = "";
    //cin.clear();
  }
  return 0;
}
    
    /*
  }
  string inpath1 = "./FinalProjectTestCases/Generated1.txt";
  ifstream f1;
  f1.open(inpath1, ios::in);
  
  string inpath2 = "./FinalProjectTestCases/Generated2.txt";
  ifstream f2;
  f2.open(inpath2, ios::in);
  
  string inpath3 = "./FinalProjectTestCases/Generated3.txt";
  ifstream f3;
  f3.open(inpath3, ios::in);

  string inpath4 = "./FinalProjectTestCases/Test1.txt";
  ifstream f4;
  f4.open(inpath4, ios::in);
  
  string outpath1 = "./FinalProjectTestCases/padding1.txt";
  string outpath2 = "./FinalProjectTestCases/padding2.txt";
  string outpath3 = "./FinalProjectTestCases/padding3.txt";
	if(!f1 or !f2 or !f3) cerr << "File not found." << endl;
	else
	{
     
    padding(inpath1, outpath1);
    padding(inpath2, outpath2);
    padding(inpath3, outpath3);
        
    BTree tree = BTree();


    string line;
    Graph* g = new Graph();
    int count = 0;
		while(std::getline(f4, line))
		{
			vector<string> words = split(line, ',');
			cout << words.size() << endl;
			g->insert(words);
			count ++;
			// ... TO DO
		}
		g->printAll();
	}
    */
