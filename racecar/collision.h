#pragma once
#include "line.h"
#include "poly.h"
// made of many lines
#include <cmath>
#include <iostream>
#define PI 3.1415
#define serchdistance 256


/*
double radianangle = double(angle) / 180 * PI;
double cosangle = cos(radianangle);
double sinangle = sin(radianangle);

*/
double distance(int x1, int y1, int x2, int y2);

class collisionObject
{
public:
	collisionObject();

	poly * getdraw();
	//collisionObject copy();
	bool addline(line component);
	void setX(int x);//basic movment
	void setY(int y);//basic movment
	bool centerpoint();
	int getx();
	int gety();

	int getrotation();
	void setrotation(int v);

	void makeready();
	bool circularcolide(collisionObject * other);
	bool colides(collisionObject * other);
	bool colidesforserch(collisionObject * other, int x, int y);
	int top(collisionObject * other); //the number of spcae up to top colision
	int bottom(collisionObject * other);
	int left(collisionObject * other);
	int right(collisionObject * other);
	
	/*
	line contact(collisionObject * other);
	*/
private:
	bool ready = true;
	int rotation;//0-360;
	double radius;
	int posx;
	int posy;
	int componestmaxsize;
	int componentsize;
	line * componentsorig;
	line * components;
};
