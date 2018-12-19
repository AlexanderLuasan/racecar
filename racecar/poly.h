#pragma once
#define liststepsize 5
struct lineunit
{
	int x1, x2, y1, y2;
};
class poly
{
public:
	poly();
	~poly();
	poly(int x, int y);
	void set(int x, int y);
	void addline(lineunit part);
	lineunit getline(int i);
	int getposx();
	int getposy();
	int getsize();
private:
	int posx;
	int posy;
	int sizecurrent;
	int sizemaximum;
	lineunit * lines;
};