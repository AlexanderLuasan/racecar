#include "line.h"


using namespace std;
line::line()
{
}

line::line(int x1, int y1, int x2, int y2)
{
	if (x1 < x2) {
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
	}else{
		this->x1 = x2;
		this->x2 = x1;
		this->y1 = y2;
		this->y2 = y1;
	}
	

}

line line::rotate(double cosangle,double sinangle)
{
	


	int a = this->x1*cosangle - this->y1*sinangle;
	int b = this->y1*cosangle + this->x1*sinangle;
	int c = this->x2*cosangle - this->y2*sinangle;
	int d = this->y2*cosangle + this->x2*sinangle;
	return line(a,b,c,d);
}

int line::left()
{

	return x1;
}

int line::right()
{

	return x2;
}

int line::top()
{
	if (y1 > y2) {
		return y2;
	}
	else {
		return y1;
	}
}

int line::bottom()
{
	if (y1 < y2) {
		return y2;
	}
	else {
		return y1;
	}
}

bool line::squareoverlap(line other, int x, int y)
{
	if (this->right() > other.left()+x) {
		if (this->left() < other.right()+x) {
			if (this->top() < other.bottom()+y) {
				if (this->bottom() > other.top()+y) {
					return true;
				}
			}
		}
	}
	return false;
}

bool line::generaloverlap(line other, int x, int y)
{
	if (this->right() > other.left() + x - flatedgespace) {
		if (this->left() < other.right() + x+ flatedgespace) {
			if (this->top() < other.bottom() + y+ flatedgespace) {
				if (this->bottom() > other.top() + y- flatedgespace) {
					return true;
				}
			}
		}
	}
	return false;
}

bool line::collision(line other,int x,int y)
{


	if (compareslope(this->getslope(), other.getslope())) {
		//parallel solve and comparer b's  m(x1)+y1
		slope m = this->getslope();

		int b1 =  -m.deltay*(this->x1)+ m.deltax*(this->y1);
		if (b1 == 0) {
			b1 = -m.deltay*(this->x2) + m.deltax*(this->y2);
		}
		int b2 = -m.deltay*(other.x1+x) + m.deltax*(other.y1+y);
		if (b2 == 0) {
			b2 = -m.deltay*(other.x2 + x) + m.deltax*(other.y2 + y);
		}
		if (b1 == b2) {
			return true;
		}
		else {
			return false;
		}


	}
	else if (this->getslope().deltax == 0 && other.getslope().deltay == 0) {
		if (!this->squareoverlap(other, x, y)) {
			return false;
		}
		return true;
	}
	else if (this->getslope().deltay == 0 && other.getslope().deltax == 0) {
		if (!this->squareoverlap(other, x, y)) {
			return false;
		}
		return true;
	}
	else {
		if (!this->squareoverlap(other, x, y)) {
			return false;
		}
		
		//1 and 2 are choice points
		bool yside = false;
		double m1;
		if (this->getslope().deltax == 0) {
			yside = true;
			m1 = double(this->getslope().deltay) * 1000000;
		}
		else {
			m1 = double(this->getslope().deltay) / this->getslope().deltax;
		}

		double m2;
		if (other.getslope().deltax == 0) {
			yside = true;
			m2 = double(other.getslope().deltay) * 1000000;
		}
		else {
			m2 = double(other.getslope().deltay) / other.getslope().deltax;
		}

		if (yside == false) {

			int locs[4];
			locs[0] = other.x1 + x;
			locs[1] = other.x2 + x;
			locs[2] = x1;
			locs[3] = x2;
			for (int i = 0; i < 4; i++) {
				for (int ii = i; ii > 0; ii--) {
					if (locs[ii] < locs[ii - 1]) {
						int temp = locs[ii];
						locs[ii] = locs[ii - 1];
						locs[ii - 1] = temp;
					}
				}
			}

			int cx = double(m1*x1 - y1 - m2 * (x + other.x1) + (y + other.y1)) / (m1 - m2);

			if (locs[1] < cx && cx < locs[2]) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			int locs[4];
			locs[0] = other.y1 + y;
			locs[1] = other.y2 + y;
			locs[2] = y1;
			locs[3] = y2;
			for (int i = 0; i < 4; i++) {
				for (int ii = i; ii > 0; ii--) {
					if (locs[ii] < locs[ii - 1]) {
						int temp = locs[ii];
						locs[ii] = locs[ii - 1];
						locs[ii - 1] = temp;
					}
				}
			}
			int cx = double(m1*x1 - y1 - m2 * (x + other.x1) + (y + other.y1)) / (m1 - m2);
			int cy = m1 * (cx - x1) + y1;
			if (locs[1] < cy && cy < locs[2]) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false; // error

}

slope line::getslope()
{
	slope end;
	end.deltay = y1 - y2;
	end.deltax = x1 - x2;
	return end;

}

int line::getx1()
{
	return x1;
}

int line::gety1()
{
	return y1;
}

int line::getx2()
{
	return x2;
}

int line::gety2()
{
	return y2;
}

void line::adjust(int x, int y)
{
	x1 = x1 + x;
	x2 = x2 + x;
	y1 = y1 + y;
	y2 = y2 + y;
}

slope reduce(slope inital)
{
	int maxfactor;
	if (inital.deltax > inital.deltay) {
		maxfactor = inital.deltay;
	}
	else {
		maxfactor = inital.deltax;
	}
	for (int i = maxfactor; i > 1; i--) {
		if (inital.deltay%i == 0 && inital.deltax%i == 0) {
			inital.deltay = inital.deltay / i;
			inital.deltax = inital.deltax / i;
		}
	}

	return inital;
}

bool compareslope(slope one, slope two)
{
	if (one.deltay*two.deltax == one.deltax*two.deltay) {
		return true;
	}
	else {
		return false;
	}
}
