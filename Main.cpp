/*
 * Main.cpp
 *
 *  Created on: Feb 11, 2016
 *      Author: omid
 */

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
    string line;
    Graph* g = new Graph();
    int count = 0;
		while(std::getline(f1, line))
		{
			vector<string> words = split(line, ',');
			cout << words.size() << endl;
      g->insert(words);
      count ++;
      g->printAll();
			// ... TO DO
		}
	}
	return 0;
}
