#ifndef LINK_H
#define LINK_H

#include <point.h>
#include <line.h>

// Start of Link class =======================================================
class Link : public Line
{
protected:
	double Radius;
public:
	Link();
	Link(double x, double y, double length, double angle, double radius);
	Link(double x, double y, double length, double angle, double radius,
		double r, double g, double b);
	Link(Point start, double length, double angle, double radius);
	Link(Point start, double length, double angle, double radius,
		double r, double g, double b);
	~Link();
	void Draw();
//	void Move(double x, double y, double angle);
	friend ostream& operator<<(ostream& os, const Link& l);
};
#endif
