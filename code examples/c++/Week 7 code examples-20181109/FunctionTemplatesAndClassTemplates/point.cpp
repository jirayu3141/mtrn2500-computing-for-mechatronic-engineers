#include <iostream>
#include <iomanip>
#include <point.h>
#include <GL/glut.h>

using namespace std;

Point::Point()
{
}

Point::Point(double x, double y)
{
	X = x;
	Y = y;
	R = 1.0;
	G = 1.0;
	B = 1.0;
}

Point::Point(double x, double y, double r, double g, double b)
{
	X = x;
	Y = y;
	R = r;
	G = g;
	B = b;
}

Point::~Point()
{
}

double Point::GetX()
{
	return X;
}

double Point::GetY()
{
	return Y;
}

double Point::GetR()
{
	return R;
}

double Point::GetG()
{
	return G;
}

double Point::GetB()
{
	return B;
}

void Point::SetX(double x)
{
	X = x;
}

void Point::SetY(double y)
{
	Y = y;
}

void Point::SetColour(double r, double g, double b)
{
	R = r;
	G = g;
	B = b;
}

void Point::Draw()
{
	glColor3f(R,G,B);
	glLoadIdentity();
	glBegin(GL_POINTS);
	glVertex2f(X,Y);
	glEnd();
}

void Point::Move(double x, double y)
{
	X = x;
	Y = y;
}
// End of Point class definition and the member function declaration ==========

ostream& operator<<(ostream& os, const Point& p)
{
	os.setf(ios::showpoint | ios::right);
	os << setw(10) << setprecision(3) << p.X;
	os << setw(10) << p.Y;
	os << setw(10) << p.R;
	os << setw(10) << p.G;
	os << setw(10) << p.B ;

	return os;
}
