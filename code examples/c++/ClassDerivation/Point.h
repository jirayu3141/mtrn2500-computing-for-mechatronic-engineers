#ifndef POINT_H
#define POINT_H

class Point
{
protected:
	double X;
	double Y;
public:
	Point();//default constructor. If we did not provide ANY constructor, compiler will provide it.
	Point(double x, double y); //a developer defined constructor.
	Point(const Point& p);//copy constructor. Its job is to copy member by member of object p's data 
	                      //to 'this' object. (if we did not provide it, compiler will provide it.
	~Point();
	double GetX();
	double GetY();
	void SetX(double x);
	void SetY(double y);
};
#endif