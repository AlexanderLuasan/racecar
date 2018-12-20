#include "map.h"
#include <iostream>
using namespace std;
map::map()
{
	size = 0;
}

map::map(char * name)
{
	tmxtag file = tmxtag(string(name), 1);

	for (int i = 0; i < file.tagcount(); i++) {
		tmxtag current = file.get(i);
		if (current.head("type").compare("objectgroup")==0&& current.head("name").compare("walls")==0) {
			for (int ii = 0; ii < current.tagcount(); ii++) {
				if (current.get(ii).head("type").compare("object")==0) {
					for (int iii = 0; iii < current.get(ii).tagcount(); iii++) {
						if (current.get(ii).get(iii).head("type").compare("polygon") == 0) {
							addshape(current.get(ii).get(iii), current.get(ii).head("x"), current.get(ii).head("y"));
						}
					}
				}
			}
		}
		else if (current.head("type").compare("objectgroup") == 0 && current.head("name").compare("start") == 0) {
			start[0] = stoi(current.get(0).head("x").c_str());
			start[1] = stoi(current.get(0).head("y").c_str());
		}
	}
	file.clear();
	


}

bool map::addshape(tmxtag c,string x,string y)
{
	string ps = c.head("points");
	if (size >= maxsize) {
		maxsize = maxsize + incr;
		collisionObject * temp = new collisionObject[maxsize];
		for (int i = 0; i < size; i++) {
			temp[i] = walls[i];
		}
		delete walls;
		walls = temp;
	}


	walls[size] = collisionObject();
	walls[size].setX(stoi(x.c_str()));
	walls[size].setY(stoi(y.c_str()));
	int points[20][2];
	int index = 0;
	while (true) {
		int start;
		int middle;
		int end;

		start = 0;
		middle = ps.find(",");
		end = ps.find(" ");

		if (middle == string::npos || end == string::npos) {
			points[index][0] = stoi(ps.substr(start, middle).c_str());
			points[index][1] = stoi(ps.substr(middle+1, ps.length()-1).c_str());
			index += 1;
			break;
		}

		//cout << ps.substr(start, middle) << " / " << stoi(ps.substr(middle - 1, end)) << endl;

		points[index][0] = stoi(ps.substr(start, middle).c_str());
		points[index][1] = stoi(ps.substr(middle+1, end).c_str());

		ps = ps.substr(end + 1);
		index += 1;

	}
	for (int i = 0; i < index-1; i++) {
		walls[size].addline(line(points[i][0], points[i][1], points[i+1][0], points[i+1][1]));
	}
	walls[size].addline(line(points[0][0], points[0][1], points[index - 1][0], points[index - 1][1]));
	
	size += 1;
	return false;
}

collisionObject * map::getwalls()
{
	return walls;
}

int map::getsize()
{
	return size;
}
