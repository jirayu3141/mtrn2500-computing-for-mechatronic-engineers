#include <iostream>
#include <iomanip>
#include <GL/glut.h>
#include <math.h>
#include "point.h"
#include "line.h"

using namespace std;

#define PI 3.14159265358979323846


Line::Line():Point()
{
}

Line::Line(double x, double y, double length, double angle): Point(x,y)
{
	Angle = angle;
	Length = length;
}

Line::Line(double x, double y, double length, double angle,
		   double r, double g, double b):Point(x,y,r,g,b)
{
	Angle = angle;
	Length = length;
}

Line::Line(Point start, double length, double angle): Point(start)
{
	Angle = angle;
	Length = length;
}

Line::Line(Point start, double length, double angle,
		   double r, double g, double b): Point(start)
{
	R = r;
	B = b;
	G = g;
	Angle = angle;
	Length = length;

}

Line::~Line()
{
}

double Line::GetLength()
{
	return Length;
}

double Line::Getangle()
{
	return Angle;
}

Point Line::GetStart()
{
	return Point(X,Y);
}

Point Line::GetEnd()
{
	return Point(X + Length*cos(Angle),Y + Length*sin(Angle));
}

void Line::Move(double x, double y, double angle)
{
	X = x;
	Y = y;
	Angle = angle;
}

void Line::Draw()
{
	glColor3f(R,G,B);
	// Draw a point
	glLoadIdentity();
	glBegin(GL_LINES);
		glVertex2f(X,Y);
		glVertex2f(GetEnd().GetX(),GetEnd().GetY());
	glEnd();
	glFlush();
}

// End of Line class definition   ============================================
ostream& operator<<(ostream& os, const Line& l)
{
	os.setf(ios::showpoint | ios::right);

	os << setw(10) << setprecision(3) << l.X;  
	os << setw(10) << l.Y;
	os << setw(10) << l.Angle;
	os << setw(10) << l.R;
	os << setw(10) << l.G;
	os << setw(10) << l.B;

	return os;
}
