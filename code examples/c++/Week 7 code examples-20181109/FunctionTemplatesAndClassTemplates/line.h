#ifndef LINE_H
#define LINE_H
#include <iostream>
#include <point.h>

using namespace std;
// Start of Line class definition ============================================
class Line : public Point
{
protected:
	double Angle;
	double Length;
public:
	Line();
	Line(double x, double y, double length, double angle);
	Line(double x, double y, double length, double angle,
		double r, double g, double b);
	Line(Point start, double length, double angle);
	Line(Point start, double length, double angle,
		double r, double g, double b);
	~Line();
	double GetLength();
	double Getangle();
	Point GetStart();
	Point GetEnd();
	void Move(double x, double y, double angle);
	void Draw();
	friend ostream& operator<<(ostream& os, const Line& l);
};
#endif