#pragma once
#include "collision.h"
#define stepreduce 100
#define maxvel 1000
#define enginpower 30

bool vectoradjust(int * velx,int * vely,int adj,int power);
bool vectorbounce(int * velx, int * vely, slope line);
bool vectorslide(int * velx, int *vely, slope line);
bool vectorpush(int * velx, int *vely, slope line);
double dot(double v1[2], double v2[2]);
double distance(double v1[2]);
class car
{
public:
	car(int posx, int posy, int width,int height,int angle);
	
	bool setpower(bool state);
	bool setleft(bool state);
	bool setright(bool state);
	bool setonwall(bool state);

	int getx();
	int gety();
	void setx(int v);
	void sety(int v);
	poly * drawingbody();
	poly * drawingflame();
	bool update();
	bool rotationupdate();
	bool changevelocity(line edge);
	collisionObject * getc();
	collisionObject * getf();
	bool collisionmove(collisionObject * other);
	bool collisionrotation(collisionObject * other);

private:
	//key inputs
	bool left;
	bool right;
	bool power;
	//current satus
	bool onwall;
	int velocityx;
	int velocityy;
	int angle;
	collisionObject body;
	collisionObject flame;
	int speedcountx;
	int speedcounty;
};