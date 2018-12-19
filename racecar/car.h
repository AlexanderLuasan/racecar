#pragma once
#include "collision.h"
#define stepreduce 100
#define maxvel 2000
#define enginpower 40

bool vectoradjust(int * inangle,int * invel,int adj,int power);

class car
{
public:
	car(int posx, int posy, int width,int height,int angle);
	
	bool setpower(bool state);
	bool setleft(bool state);
	bool setright(bool state);
	int getx();
	int gety();
	poly * drawingbody();
	bool update();
private:
	//key inputs
	bool left;
	bool right;
	bool power;
	//current satus
	int velangle;
	int velocity;
	int angle;
	collisionObject body;
	int speedcountx;
	int speedcounty;
};