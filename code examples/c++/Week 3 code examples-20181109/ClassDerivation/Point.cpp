#include <iostream>
#include "point.h"

using namespace std;

Point::Point()
{
	cout << "A Point object created at " << this << " using default constructor" << endl; 
}

Point::Point(double x, double y)
{
	X = x;
	Y = y;
	cout << "A Point object created at " << this << " using normal constructor" << endl; 
}

Point::Point(const Point& p)
{
	X = p.X;
	Y = p.Y;
	cout << "A Point object created at " << this << " using copy constructor" << endl; 
}



Point::~Point()
{
	cout << "A Point object at " << this << " was destroyed." << endl; 
}
double Point::GetX()
{
	return X;
}

double Point::GetY()
{
	return Y;
}

void Point::SetX(double x)
{
	X = x;
}

void Point::SetY(double y)
{
	Y = y;
}
