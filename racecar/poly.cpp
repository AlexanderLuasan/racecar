#include "poly.h"

poly::poly()
{
	posx = 0;
	posy = 0;
	sizemaximum = 0;
	sizecurrent = 0;
}

poly::~poly()
{
	//delete xs;
	//delete ys;
}

poly::poly(int x, int y)
{
	posx = x;
	posy = y;
	sizemaximum = 0;
	sizecurrent = 0;
}

void poly::set(int x, int y)
{
	posx = x;
	posy = y;
}

void poly::addline(lineunit part)
{
	if (sizecurrent >= sizemaximum) {
		sizemaximum += liststepsize;
		lineunit * temp1 = new lineunit[sizemaximum];
		for (int i = 0; i < sizecurrent; i++) {
			temp1[i] = lines[i];
		}
		delete lines;
		lines = temp1;
	}

	lines[sizecurrent] = part;
	sizecurrent += 1;
}

lineunit poly::getline(int i)
{
	return lines[i];
}


int poly::getposx()
{
	return posx;
}

int poly::getposy()
{
	return posy;
}

int poly::getsize()
{
	return sizecurrent;
}
