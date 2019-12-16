#include <iostream>
#include "Circle.h"
#include "Point.h"

using namespace std;

Circle::Circle()
{
	cout << "A Circle object created at " << this << " using default constructor" << endl; 
}

Circle::Circle(double x, double y, double radius) : Point(x,y)
{
	Radius = radius;
	cout << "A Circle object created at " << this << " using normal constructor 1" << endl; 
}

Circle::Circle(Point centre, double radius) :Point(centre.GetX(),centre.GetY())
{
	Radius = radius;
	cout << "A Circle object created at " << this << " using normal constructor 2" << endl; 
}

Circle::~Circle()
{
	cout << "A Circle object at " << this << " was destroyed." << endl; 
}

double Circle::GetRadius()
{
	return Radius;
}

void Circle::SetRadius(double radius)
{
	Radius = radius;
}




