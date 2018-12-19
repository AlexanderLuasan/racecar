#include "display.h"
#include <iostream>
display::display(int w, int h, int s)
{
	camx = 0;
	camy = 0;
	width = w;
	height = h;
	screen = al_create_display((width+2*globaladjust)*globalscale*s, (height+ 2*globaladjust)*globalscale*s);
	scale = s;

}

ALLEGRO_DISPLAY * display::gets()
{
	return screen;
}

void display::CamCenter(int x, int y)
{
	x -= width/2;
	y -= height/2;
	if (x > camx+64&&camax<maxcamspeed) {
		camax += 1;
	}
	else if (x < camx- 64 &&camax>-maxcamspeed) {
		camax -= 1;
	}
	else if (x > camx + 32 && camax<maxcamspeed/2) {
		camax += 1;
	}
	else if (x < camx - 32 && camax>-maxcamspeed/2) {
		camax -= 1;
	}
	else if(x > camx - 32 && x < camx + 32){
		if (camax > 0) {
			camax -= 1;
		}
		else if(camax<0) {
			camax += 1;
		}
	}

	if (y > camy + 64 && camay<maxcamspeed) {
		camay += 1;
	}
	else if (y < camy - 64 && camay>-maxcamspeed) {
		camay -= 1;
	}
	else if (y > camy + 32 && camay<maxcamspeed / 2) {
		camay += 1;
	}
	else if (y < camy - 32 && camay>-maxcamspeed / 2) {
		camay -= 1;
	}
	else if (y > camy - 32 && y < camy + 32) {
		if (camay > 0) {
			camay -= 1;
		}
		else if (camay<0) {
			camay += 1;
		}
	}

	this->adjCam(camax, camay);
}

bool display::setCam(int x, int y)
{
	camx = x;
	camy = y;
	return false;
}

bool display::adjCam(int x, int y)
{
	camx = camx + x;
	camy = camy + y;
	return false;
}

bool display::drawstart()
{
	al_set_target_backbuffer(screen);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	return false;
}

bool display::drawview()
{
	al_draw_rectangle(scale*(0+ globaladjust), scale*(0+ globaladjust), scale*(width+ globaladjust), scale*(height+ globaladjust),al_map_rgb(0,0,0),4);
	return false;
}

bool display::draw(ALLEGRO_BITMAP * image, int x, int y, int w, int h)
{

	int sx, sy, sw, sh;
	int dx, dy, dw, dh;
	if (x < camx) {//off left on screen
		sx = camx - x;
		dx = 0;
	}
	else {
		sx = 0;
		dx = x - camx;
	}
	
	if (y < camy) {
		sy = camy - y;
		dy = 0;
	}
	else {
		sy = 0;
		dy = y - camy;
	}

	if (camx + width < x + w) {
		sw = (w-sx)-((x+w)-(camx+width));
		dw = (w-sx)- ((x + w) - (camx + width));

	}
	else {
		sw = w-sx;
		dw = w-sx;
		if (x + w < camx) {
			dw = 0;
		}
	}
	if (camy + height < y + h) {
		sh = h - ((y + h) - (camy + height))- camy;
		dh = h - ((y + h) - (camy + height))- camy;

	}
	else {
		sh = h-sy;
		dh = h-sy;
		if (y + h < camy) {
			dh = 0;
		}
	}

	if (dw <= 0 || dh <= 0) {
		return false;
	}

	al_draw_scaled_bitmap(image,sx,sy,sw,sh,scale*(dx+ globaladjust),scale*(dy+ globaladjust),scale*(dw),scale*(dh),0);



	return true;
}

bool display::draw(ALLEGRO_BITMAP * image, int x, int y, int w, int h, bool flip)
{
	int sx, sy, sw, sh;
	int dx, dy, dw, dh;
	if (x < camx) {//off left on screen
		sx = camx - x;
		dx = 0;
	}
	else {
		sx = 0;
		dx = x - camx;
	}

	if (y < camy) {
		sy = camy - x;
		dy = 0;
	}
	else {
		sy = 0;
		dy = y - camy;
	}

	if (camx + width < x + w) {
		sw = w - ((x + w) - (camx + width));
		dw = w - ((x + w) - (camx + width));

	}
	else {
		sw = w;
		dw = w;
		if (x + w < camx) {
			dw = 0;
		}
	}
	if (camy + height < y + h) {
		sh = h - ((y + h) - (camy + height));
		dh = h - ((y + h) - (camy + height));

	}
	else {
		sh = h;
		dh = h;
		if (y + h < camy) {
			dh = 0;
		}
	}

	if (dw <= 0 || dh <= 0|| dw <= 0 || dw <= 0) {
		return false;
	}
	if (flip) {
		al_draw_scaled_bitmap(image, sx, sy, sw, sh, scale*(dx + globaladjust), scale*(dy + globaladjust), scale*(dw), scale*(dh), ALLEGRO_FLIP_HORIZONTAL);
	}
	else {
		al_draw_scaled_bitmap(image, sx, sy, sw, sh, scale*(dx + globaladjust), scale*(dy + globaladjust), scale*(dw), scale*(dh),0);
	}
	return true;
}

bool display::draw(poly * shape)
{
	int xc, yc;
	xc = shape->getposx();
	yc = shape->getposy();
	al_draw_filled_circle(scale*(xc-camx+globaladjust), scale*(yc - camy + globaladjust), 5, al_map_rgb(0, 0, 0));
	for (int i = 0; i < shape->getsize(); i++) {

		lineunit t = shape->getline(i);

		al_draw_line(scale*(xc + t.x1 - camx + globaladjust), scale*(yc + t.y1 - camy + globaladjust), scale*(xc + t.x2- camx + globaladjust), scale*(yc + t.y2-camy+ globaladjust), al_map_rgb(0, 0, 0), 2);
	}
	delete shape;
	return false;
}

bool display::draw(int x, int y, int w, int h)
{
	al_draw_rectangle(scale*(x-camx + globaladjust), scale*(y-camy + globaladjust),scale*( w-camx + globaladjust),scale*( h-camy+globaladjust),al_map_rgb(0,0,0),2);
	return false;
}

bool display::drawview(int x, int y, double angle, double size, int range)
{
	if (size != 0) {
		int x2 = (double(x) + cos(angle + size)*range) - camx + globaladjust;
		int y2 = (double(y) + sin(angle + size)*range) - camy + globaladjust;

		int x3 = (double(x) + cos(angle - size)*range) - camx + globaladjust;
		int y3 = (double(y) + sin(angle - size)*range) - camy + globaladjust;
		x = x - camx + globaladjust;
		y = y - camy + globaladjust;
		al_draw_filled_triangle(x*scale, y*scale, x2*scale, y2*scale, x3*scale, y3*scale, al_map_rgba(125, 0, 125, 125));
	}
	else {
		int x2 = (double(x) + cos(angle)*range) - camx + globaladjust;
		int y2 = (double(y) + sin(angle)*range) - camy + globaladjust;
		x = x - camx + globaladjust;
		y = y - camy + globaladjust;
		al_draw_line(x*scale, y*scale, x2*scale, y2*scale,al_map_rgba(255,0,0,125),3);
	}
	return true;
}
