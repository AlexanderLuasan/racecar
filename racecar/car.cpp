#include "car.h"
#include <iostream>
car::car(int posx, int posy, int width, int height,int angle)
{
	this->angle = angle;
	velocity = 0;
	speedcountx = 0;
	speedcounty = 0;
	body.setX(posx);
	body.setY(posy);
	body.addline(line(-height /2, -width /2, height / 2,0));
	body.addline(line(-height / 2, width / 2, height / 2,0));
	body.addline(line(-height / 2, -width / 2, -height / 2, width / 2));
	body.setrotation(angle);
	right = false;
	left = false;
	power = false;
}

bool car::setpower(bool state)
{
	power = state;
	return false;
}

bool car::setleft(bool state)
{
	left = state;
	return false;
}

bool car::setright(bool state)
{
	right = state;
	return false;
}

int car::getx()
{
	return body.getx();
}

int car::gety()
{
	return body.gety();
}

poly * car::drawingbody()
{
	return body.getdraw();
}

bool car::update()
{
	if (right&&left) {
	}
	else if (right) {
		angle += 6;
		body.setrotation(angle);
	}
	else if (left) {
		angle -= 6;
		body.setrotation(angle);
	}
	if (power) {
		vectoradjust(&velangle, &velocity, angle, enginpower);
		if (velocity > maxvel) {
			velocity = maxvel;
		}
	}

	int x = cos(velangle*PI / 180) * velocity;
	int y = sin(velangle*PI / 180) * velocity;

	speedcountx += x;
	speedcounty += y;

	if (abs(speedcountx) > stepreduce) {
		body.setX(body.getx() + speedcountx/ stepreduce);
		speedcountx = speedcountx % stepreduce;
	}
	if (abs(speedcounty) > stepreduce) {
		body.setY(body.gety() + speedcounty / stepreduce);
		speedcounty = speedcounty % stepreduce;
	}
	

	return false;
}

bool vectoradjust(int * inangle, int * invel, int adj, int power)
{
	double vx1, vy1;
	double vx2, vy2;
	vx1 = cos(*inangle*PI/180) * *invel;
	vy1 = sin(*inangle*PI/180) * *invel;
	vx2 = cos(adj*PI/180) * power;
	vy2 = sin(adj*PI/180) * power;
	vx1 = vx1 + vx2;
	vy1 = vy1 + vy2;
	
	double angle;
	double speed;
	if (vy1 == 0) {// division by zero
		if (vx1 > 0) {
			angle = 0;
		}
		else if (vx1 < 0) {
			angle = 180;
		}
		else {
			angle = 0;
		}
	}
	else if (vx1 == 0) {
		if (vy1 > 0) {
			angle = 90;
		}
		else if (vy1 < 0) {
			angle = -90;
		}
		else {
			angle = 90;
		}
	}
	else {
		angle = 180*atan(vy1/vx1)/PI;
		if (vx1 < 0) {
			angle += 180;
		}
	}
	speed = sqrt((vx1)*vx1 + (vy1)*vy1);
	*invel = int(speed + .5);
	*inangle = int(angle + .5);
	return false;
}
