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
    /*
  string inpath1 = "./FinalProjectTestCases/Generated1.txt";
	ifstream f1;
	f1.open(inpath1, ios::in);

  string inpath2 = "./FinalProjectTestCases/Generated2.txt";
	ifstream f2;
	f2.open(inpath2, ios::in);

  string inpath3 = "./FinalProjectTestCases/Generated3.txt";
	ifstream f3;
	f3.open(inpath3, ios::in);

  string outpath1 = "./FinalProjectTestCases/padding1.txt";
  string outpath2 = "./FinalProjectTestCases/padding2.txt";
  string outpath3 = "./FinalProjectTestCases/padding3.txt";
	if(!f1 or !f2 or !f3) cerr << "File not found." << endl;
	else
	{
     
    padding(inpath1, outpath1);
    padding(inpath2, outpath2);
    padding(inpath3, outpath3);
     */
        BTree tree = BTree();
        tree.Insert("saber",123);
        tree.PrintAll(tree.GetRoot());
        cout<<endl;
        tree.Insert("lancer", 234);
        tree.PrintAll(tree.GetRoot());
        cout<<endl;
        tree.Insert("caster", 345);
        tree.PrintAll(tree.GetRoot());
        cout<<endl;
        tree.Insert("archer", 456);
        tree.PrintAll(tree.GetRoot());
        cout<<endl;
        tree.Insert("assassin", 567);
        tree.PrintAll(tree.GetRoot());
        cout<<endl;
        tree.Insert("berserker", 678);
        //previous wrong, fixed
        tree.PrintAll(tree.GetRoot());
        cout << tree.GetRoot()->GetOccupancy() << endl;
        cout<<endl;
        tree.Insert("rider", 789);
        tree.PrintAll(tree.GetRoot());
        cout<<endl;
        tree.Insert("teacher", 910);
        tree.PrintAll(tree.GetRoot());
        cout<<endl;
        tree.Insert("gaotian", 1789);
        tree.PrintAll(tree.GetRoot());
        cout<<endl;
        tree.Insert("hexiaohe", 111);
        tree.PrintAll(tree.GetRoot());
        cout<<endl;
    
        tree.Insert("az",11121);
        tree.PrintAll(tree.GetRoot());
        cout<<endl;
        tree.Insert("av",999);//split root
        tree.PrintAll(tree.GetRoot());
        cout<<endl;
    // check split root status
    assert(tree.GetRoot()->occupancy==2);
    assert(tree.root->children[0]->occupancy == 3);
    assert(tree.root->children[1]->occupancy == 3);
    assert(tree.root->children[1]->parent == tree.root->children[0]->parent);
  
        tree.Insert("tf", 11);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
        tree.Insert("tg", 12);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
        tree.Insert("th", 121);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
        tree.Insert("ti", 1313);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
        tree.Insert("tj",2134);
    tree.PrintAll(tree.GetRoot());
    cout<<endl;
        tree.Insert("tk", 12312);
        tree.PrintAll(tree.GetRoot());
        cout<<endl;
        //tree.Insert("", )
        cout << tree.GetRoot()->GetOccupancy() << endl;
    
//    assert(tree.root->children[0]->occupancy == 3);
  tree.Insert("tl", 314);
    tree.Insert("tm",2342);
    tree.Insert("tn",3245);
    tree.Insert("to",341212);
    tree.Insert("tp",38942723);
    tree.Insert("tr",23981);
    tree.Insert("ak", 312);
    tree.Insert("sb", 123);
    tree.PrintAll(tree.GetRoot());
    cout << tree.GetRoot()->GetOccupancy() << endl;
    tree.Search("to");
    tree.Search("ts");
    tree.Search("aa");
    tree.Search("ak");
    tree.Search("gaotian");
    tree.PrintBetween("tk", "tp");
    /*
    string line;
    Graph* g = new Graph();
    int count = 0;
		while(std::getline(f1, line))
		{
			vector<string> words = split(line, ',');
			cout << words.size() << endl;
            g->insert(words);
            count ++;
			// ... TO DO
		}
     */
//	}
	return 0;
}
