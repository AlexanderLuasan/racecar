#pragma once
#define flatedgespace 1
struct slope
{
	int deltay;
	int deltax;
};

slope reduce(slope inital);
bool compareslope(slope one,slope two);


class line
{
public:
	line();
	line(int x1,int y1,int x2,int y2);
	line rotate(double cosangle,double sinangle);
	int left();
	int right();
	int top();
	int bottom();
	bool squareoverlap(line other, int x, int y);
	bool generaloverlap(line other, int x, int y);
	bool collision(line other,int x,int y);
	slope getslope();
	int getx1();
	int gety1();
	int getx2();
	int gety2();
	void adjust(int x,int y);
private:
	int x1, y1, x2, y2;

};