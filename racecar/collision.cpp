#include "collision.h"
#include <iostream>
using namespace std;
collisionObject::collisionObject()
{
	ready = false;
	this->setX(0);
	this->setY(0);
	componestmaxsize = 1;
	componentsize = 0;
	radius = 0;
	this->setrotation(0);
	componentsorig = new line[1];
	components = new line[1];
}

poly * collisionObject::getdraw()
{
	if (ready == false) {
		makeready();
	}
	poly * end = new poly;

	end->set(posx, posy);
	for (int i = 0; i < componentsize; i++) {
		line current = components[i];
		lineunit l;
		l.x1 = current.getx1();
		l.y1 = current.gety1();
		l.x2 = current.getx2();
		l.y2 = current.gety2();
		end->addline(l);
	}

	return end;
}

bool collisionObject::addline(line component)
{
	ready = false;
	if (componentsize >= componestmaxsize) {
		componestmaxsize = componestmaxsize + 3;
		line * temp = new line[componestmaxsize];
		for (int i = 0; i < componentsize; i++) {
			temp[i] = componentsorig[i];
		}
		delete componentsorig;
		componentsorig = temp;
		delete components;
		components = new line[componestmaxsize];
	}
	componentsorig[componentsize] = component;
	componentsize += 1;
	return false;
}

void collisionObject::setX(int x)
{
	posx = x;
}

void collisionObject::setY(int y)
{
	posy = y;
}

bool collisionObject::centerpoint()
{
	ready = false;
	int count = 0;
	double totalx = 0.0;
	double totaly = 0.0;
	for (int i = 0; i < componentsize; i++) {
		double d = distance(0, 0, componentsorig[i].getx1(), 0);
		totalx += d;
		d = distance(0, 0, componentsorig[i].getx2(), 0);
		totalx += d;

		d = distance(0, 0, 0, componentsorig[i].getx1());
		totaly += d;
		d = distance(0, 0, 0, componentsorig[i].getx2());
		totaly += d;

		count += 2;
	}
	int meanx;
	int meany;
	meanx = totalx / count;
	meany = totaly / count;

	for (int i = 0; i < componentsize; i++) {
		componentsorig[i].adjust(-meanx, -meany);
	}
	posx += meanx;
	posy += meany;
	return true;
}

int collisionObject::getx()
{
	return posx;
}

int collisionObject::gety()
{
	return posy;
}

int collisionObject::getrotation()
{
	return rotation;
}

void collisionObject::setrotation(int v)
{
	ready = false;
	rotation = v % 360;
}

void collisionObject::makeready()
{
	ready = true;

	double radianangle = double(rotation) / 180 * PI;
	double cosangle = cos(radianangle);
	double sinangle = sin(radianangle);
	if (rotation != 0) {
		for (int i = 0; i < componentsize; i++) {
			components[i] = componentsorig[i].rotate(cosangle, sinangle);
		}
	}
	else {
		for (int i = 0; i < componentsize; i++) {
			components[i] = componentsorig[i];
		}
	}
	double maxdistance = 0;
	for (int i = 0; i < componentsize; i++) {
		double d = distance(0,0, components[i].getx1(), components[i].gety1());
		if (d > maxdistance) {
			maxdistance = d;
		}
		d = distance(0, 0, components[i].getx2(), components[i].gety2());
		if (d > maxdistance) {
			maxdistance = d;
		}
	}
	radius = maxdistance;
}

bool collisionObject::circularcolide(collisionObject * other)
{
	if (distance(this->posx, this->posy, other->posx, other->posy) < this->radius + other->radius + 3) {
		return true;
	}
	return false;
}

bool collisionObject::colides(collisionObject * other)
{
	if (ready == false) {
		makeready();
	}
	if (other->ready == false) {
		other->makeready();
	}
	for (int i = 0; i < componentsize; i++) {
		for (int ii = 0; ii < other->componentsize; ii++) {
			if (this->components[i].generaloverlap(other->components[ii],other->posx-this->posx, other->posy- this->posy)) {
				if(this->components[i].collision(other->components[ii], other->posx - this->posx, other->posy - this->posy)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool collisionObject::colidesforserch(collisionObject * other,int x,int y)
{
	this->setX(this->getx()+x);
	this->setY(this->gety()+y);
	bool end = colides(other);
	this->setX(this->getx() -x);
	this->setY(this->gety() - y);
	return end;
}

int collisionObject::top(collisionObject * other)
{
	int min = 0;
	int max = - serchdistance;
	if (this->colidesforserch(other, 0, max)) {
		return 0;
	}
	else {
		
	}
	while (true) {
		if (max==min-1) {
			return max;
		}
		if (this->colidesforserch(other, 0, (max+min)/2)) {
			min = (max + min) / 2;
		}
		else {
			max = (max + min) / 2;
		}
	}


	return 0;
}

int collisionObject::bottom(collisionObject * other)
{
	int min = 0;
	int max = serchdistance;
	if (this->colidesforserch(other, 0, max)) {
		return 0;
	}
	while (true) {
		if (max == min + 1) {
			return max;
		}
		if (this->colidesforserch(other, 0, (max + min) / 2)) {
			min = (max + min) / 2;
		}
		else {
			max = (max + min) / 2;
		}
	}
	return 0;
}

int collisionObject::left(collisionObject * other)
{
	int min = 0;
	int max =  - serchdistance;
	if (this->colidesforserch(other, max, 0)) {
		return 0;
	}
	while (true) {
		if (max == min - 1) {
			return max;
		}
		if (this->colidesforserch(other, (max + min) / 2, 0)) {
			min = (max + min) / 2;
		}
		else {
			max = (max + min) / 2;
		}
	}
	return 0;
}

int collisionObject::right(collisionObject * other)
{
	int min = 0;
	int max = serchdistance;
	if (this->colidesforserch(other,max, 0)) {
		return 0;
	}
	while (true) {
		if (max == min + 1) {
			return max;
		}
		if (this->colidesforserch(other, (max + min) / 2, 0)) {
			min = (max + min) / 2;
		}
		else {
			max = (max + min) / 2;
		}
	}
	return 0;
}

double distance(int x1, int y1, int x2, int y2)
{
	int t = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
	
	return sqrt(t);
}
