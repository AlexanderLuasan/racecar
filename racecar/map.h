#pragma once
#include "tiledparser.h"
#include "collision.h"
#include <fstream>
#include <string>

#define incr 20
class map 
{
public:
	map();
	map(char * name);

	bool addshape(tmxtag c, string x, string y);
	collisionObject * getwalls();
	int getsize();
	int start[2];
private:
	collisionObject * walls;
	int size;
	int maxsize;


	
};