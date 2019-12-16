#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;


//Start of Point class ====================================
class Point
{
protected:
	double X;
	double Y;
	double R;
	double G;
	double B;
public:
	Point();
	Point(double x, double y);
	Point(double x, double y, double r, double g, double b);
	virtual ~Point();
	// Any other constructors
	// Getters and setters
	double GetX();
	double GetY();
	double GetR();
	double GetG();
	double GetB();
	void SetX(double x);
	void SetY(double y);
	void SetColour(double r, double g, double b);
	// Point class capabilities
	virtual void Draw();
	virtual void Move(double x, double y);
	friend ostream& operator<<(ostream& os, const Point& p);
	//any other capabilities
};
#endif
