#include "car.h"
#include <iostream>
car::car(int posx, int posy, int width, int height,int angle)
{
	this->angle = angle;
	velocityx = 0;
	velocityy = 0;
	speedcountx = 0;
	speedcounty = 0;
	body.setX(posx);
	body.setY(posy);
	body.addline(line(-height /2, -width /2, height / 2,0));
	body.addline(line(-height / 2, width / 2, height / 2,0));
	body.addline(line(-height / 2, -width / 2, -height / 2, width / 2));
	body.setrotation(angle);
	flame.setX(posx);
	flame.setY(posy);
	flame.addline(line(-40,0,0,0));
	flame.addline(line(-35, -10, 0, 0));
	flame.addline(line(-35, 10, 0, 0));
	flame.setrotation(angle);
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

bool car::setonwall(bool state)
{
	onwall = state;
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

void car::setx(int v)
{
	body.setX(v);
}

void car::sety(int v)
{
	body.setY(v);
}

poly * car::drawingbody()
{
	return body.getdraw();
}

poly * car::drawingflame()
{
	return flame.getdraw();
}

bool car::update()
{
	
	if (power) {
		if (onwall) {
			vectoradjust(&velocityx, &velocityy, angle, 3*enginpower);
		}
		else {
			vectoradjust(&velocityx, &velocityy, angle, enginpower);
		}
		double vector[2] = { velocityx, velocityy };
		if (distance(vector) > maxvel) {
			double len = distance(vector);
			velocityx = maxvel * velocityx / len;
			velocityy = maxvel * velocityy / len;

		}
	}

	int x = velocityx;
	int y = velocityy;

	speedcountx += x;
	speedcounty += y;

	if (abs(speedcountx) > stepreduce) {
		body.setX(body.getx() + speedcountx / stepreduce);
		speedcountx = speedcountx % stepreduce;
		flame.setX(body.getx());
	}
	if (abs(speedcounty) > stepreduce) {
		body.setY(body.gety() + speedcounty / stepreduce);
		speedcounty = speedcounty % stepreduce;
		flame.setY(body.gety());
	}


	return false;
}

bool car::rotationupdate()
{
	if (right&&left) {
	}
	else if (right) {
		angle += 6;
		body.setrotation(angle);
		flame.setrotation(angle);
	}
	else if (left) {
		angle -= 6;
		body.setrotation(angle);
		flame.setrotation(angle);
	}
	return false;
}

bool car::changevelocity(line edge)
{

	slope part = edge.getslope();
	vectorbounce(&velocityx, &velocityy, part);
	return false;
}

collisionObject * car::getc()
{
	return &body;
}

collisionObject * car::getf()
{
	return &flame;
}

bool car::collisionmove(collisionObject * other)
{

	int distances[4];
	distances[0] = body.top(other);
	distances[1] = body.bottom(other);
	distances[2] = body.left(other);
	distances[3] = body.right(other);
	int choice = -1;
	int index = 0;
	/*
	int xr;
	int yr;
	body.anglepush(velocityx,velocityy,&xr,&yr, other);
	body.setY(body.gety() + yr);
	body.setX(body.getx() + xr);
	if (abs(xr) > abs(velocityx)) {
		std::cout << "hi";
	}
	if (abs(yr) > abs(velocityy)) {
		std::cout << "hi";
	}
	std::cout << "push " << xr <<","<< yr << std::endl;
	*/


	if (velocityx > 0) {
		distances[3] = 0;
	}
	else if (velocityx < 0) {
		distances[2] = 0;
	}
	else {

	}

	if (velocityy > 0) {
		distances[1] = 0;
	}
	else if (velocityy < 0) {
		distances[0] = 0;
	}
	else {

	}

	if (false) {
		if (distances[2] != 0) {
			choice = 2;
		}
		else if (distances[3] != 0){
			choice = 3;
		}
		else {
			if (distances[0] != 0) {
				choice = 0;
			}
			else if (distances[1] != 0) {
				choice = 1;
			}
		}
	}
	else if(false) {
		if (distances[0] != 0) {
			choice = 0;
		}
		else if (distances[1] != 0) {
			choice = 1;
		}
		else {
			if (distances[2] != 0) {
				choice = 2;
			}
			else if (distances[3] != 0) {
				choice = 3;
			}
		}
	}
	else {
		while (true) {
			if (distances[index] != 0) {
				choice = index;
				break;
			}
			index += 1;
			if (index > 3) {
				return false;
			}
		}
		while (index < 4) {
			if (distances[index] != 0 && abs(distances[index]) < abs(distances[choice])) {
				choice = index;
			}
			index += 1;
		} 


	}
	
	if (choice < 2) {
		body.setY(body.gety()+ distances[choice]);
		velocityy = velocityy*.8;
	}
	else {
		body.setX(body.getx()+ distances[choice]);
		velocityx = velocityx * .8;
	}
	switch (choice) {
	case 0:
		std::cout << "top" << std::endl;
		break;
	case 1:
		std::cout << "bottom" << std::endl;
		break;
	case 2:
		std::cout << "left" << std::endl;
		break;
	case 3:
		std::cout << "right" << std::endl;
		break;
	default:
		std::cout << "fail" << std::endl;
	}
	


 	return true;
}

bool car::collisionrotation(collisionObject * other)
{
	int distances[4];
	distances[0] = body.top(other);
	distances[1] = body.bottom(other);
	distances[2] = body.left(other);
	distances[3] = body.right(other);
	int choice = -1;
	int index = 0;

	while (true) {
		if (distances[index] != 0) {
			choice = index;
			break;
		}
		index += 1;
		if (index > 3) {
			return false;
		}
	}
	while (index < 4) {
		if (distances[index] != 0 && abs(distances[index]) < abs(distances[choice])) {
			choice = index;
		}
		index += 1;
	}
	if (choice < 2) {
		body.setY(body.gety() + distances[choice]);
	}
	else {
		body.setX(body.getx() + distances[choice]);
	}
	return false;
}

bool vectoradjust(int * velx, int * vely, int adj, int power)
{
	double vx2, vy2;

	vx2 = cos(adj*PI/180) * power;
	vy2 = sin(adj*PI/180) * power;
	*velx = *velx + int(vx2+.5);
	*vely = *vely + int(vy2+.5);
	
	return false;
}

bool vectorbounce(int * velx, int * vely, slope line)
{

	double velocity[2];
	velocity[0] = *velx;
	velocity[1] = *vely;
	double wall[2];
	wall[0] = -line.deltay;
	wall[1] = line.deltax;


	if (line.deltay == 0) {
		*vely = *vely*-1;
	}
	else if (line.deltax == 0) {
		*velx = *velx*-1;
	}
	else {
		double mod = 2 * (dot(velocity, wall) / dot(wall, wall));

		double r[2];
		r[0] = velocity[0] - mod * wall[0];
		r[1] = velocity[1] - mod * wall[1];


		double lineangle;
		if (line.deltax != 0) {
			lineangle = atan(double(line.deltay) / line.deltax);
		}
		else {
			if (line.deltay > 0) {
				lineangle = PI / 2;
			}
			else {
				lineangle = -PI / 2;
			}
		}
		lineangle = lineangle * 180 / PI;
		int relineangle = int(lineangle) % 360;
		if (relineangle < 0) {
			relineangle += 360;
		}
		bool flipx = false;
		bool flipy = false;
		std::cout << "angle" << relineangle << std::endl;
		if (abs(relineangle - 0)<35 || abs(relineangle -180)<35 || abs(relineangle - 360)<35) {
			flipy = true;
 			std::cout << "flat" << std::endl;
		}
		else if (abs(relineangle - 90) < 35 || abs(relineangle - 270) < 35) {
			flipx = true;
			std::cout << "vert" << std::endl;
		}
		else {
			std::cout << "angle" << std::endl;
			flipy = true;
			flipx = true;
		}
		
   		if (flipy == true) {
			if (*vely > 0) {
				*vely = -abs(r[1]);
			}
			else if (*vely < 0) {
				*vely = abs(r[1]);
			}
		}
		if (flipx == true) {
			if (*velx > 0) {
				*velx = -abs(r[0]);
			}
			else if (*velx < 0) {
				*velx = abs(r[0]);
			}
		}


		return false;
	}
	return false;
}

bool vectorslide(int * velx, int * vely, slope line)
{
	double velocity[2];
	velocity[0] = *velx;
	velocity[1] = *vely;
	double wall[2];
	wall[0] = line.deltax;
	wall[1] = line.deltay;


	double prodot = dot(velocity, wall)/dot(velocity, velocity);
	std::cout << prodot << std::endl;
	double r[2];
	r[0] = prodot*wall[0]/distance(wall);
	r[1] = prodot*wall[1]/distance(wall);
	*velx = r[0];
	*vely = r[1];
	

	

	return false;
}

bool vectorpush(int * velx, int * vely, slope line)
{
	double velocity[2];
	velocity[0] = *velx;
	velocity[1] = *vely;
	double wall[2];
	wall[0] = -line.deltay;
	wall[1] = line.deltax;
	double len = distance(wall);
	wall[0] = wall[0]/len;
	wall[1] = wall[1]/len;

	double product = dot(velocity, wall);
	std::cout << product << std::endl;
	double r[2];
	r[0] = velocity[0]+wall[0];
	r[1] = velocity[1]+wall[1];
	*velx = r[0];
	*vely = r[1];




	return false;
}

double dot(double v1[2], double v2[2])
{
	return v1[0] * v2[0] + v1[1] * v2[1];
}

double distance(double v1[2])
{
	return sqrt(v1[0] * v1[0] + v1[1] * v1[1]);
}
