#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "poly.h"
#include <cmath>
#define globaladjust 10
#define globalscale 1
#define maxcamspeed 10
#define barsize 50

class display
{
public:
	display(int width, int height, int scale);
	ALLEGRO_DISPLAY * gets();
	void CamCenter(int x,int y);
	bool setCam(int x, int y);
	bool adjCam(int x, int y);
	bool drawstart();
	bool drawview();
	bool draw(ALLEGRO_BITMAP*image,int x,int y,int w,int h);
	bool draw(ALLEGRO_BITMAP*image, int x, int y, int w, int h,bool flip);
	bool draw(poly * shape);
	bool draw(int x, int y, int w, int h);
	bool drawview(int x, int y, double angle, double size, int range);
private:
	int scale;
	int camx;
	int camy;
	int camax;
	int camay;
	int width;//screen
	int height;//screen

	ALLEGRO_DISPLAY * screen;
};