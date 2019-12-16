#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

class Circle : public Point
{
private:
	double Radius;
public:
	Circle();
	Circle(double x, double y, double radius);
	Circle(Point centre, double radius);
	~Circle();
	double GetRadius();
	void SetRadius(double radius);
};
#endif