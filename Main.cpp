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

int main(int argc, char** argv)
{
    string path = "./FinalProjectTestCases/Generated1.txt";
    if(argc > 1)
    {
        path = argv[1];
    }

	ifstream f;
	f.open(path.c_str(), ios::in);
	if(!f) cerr << "File not found." << endl;
	else
	{
    Graph* g = new Graph();
    int count = 0;
		while(!f.eof())
		{
			string line;
			std::getline(f, line);
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
