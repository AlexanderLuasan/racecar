#pragma once
#include <string>
#include <fstream>
using namespace std;



class tmxtag
{
public:
	tmxtag();
	tmxtag(string space);
	tmxtag(string space[], int inial, int end);
	tmxtag(string path,int differ);
	string head();
	void display(int indent);


	string head(string key);

	int tagcount();
	tmxtag get(int i);
	
	string getData();

	bool clear();

private:
	int keysize;
	string keys[15];
	string values[15];
	
	string data;

	int tagCount;
	int maxtags;
	tmxtag * * tags;
};


