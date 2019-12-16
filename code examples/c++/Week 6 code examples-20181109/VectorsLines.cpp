// Demonstrates using a vector to store a list of objects (class type)
#include <Windows.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <math.h>
#include <conio.h>

using namespace std;

#define PI 3.14159265358979323846
// Start of Point class definition ===========================================
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
	void Draw();
	void Move(double x, double y, double);
	//any other capabilities
};
	
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

void Point::Move(double x, double y, double)
{
	X = x;
	Y = y;
}
// End of Point class definition and the member function declaration ==========

// Start of Circle class definition ===========================================
class Circle : public Point //Circle inherits everything from Point class.
{
protected:
	double Radius;

public:
	Circle();
	Circle(double x, double y, double radius, double r, double g, double b);
	Circle(Point c, double radius, double r, double g, double b);
	double GetRadius();
	void SetRadius(double radius);
	void Draw();
	void Move(double x, double y, double); //inherited move is sufficient - see definition
};

Circle::Circle():Point()
{
}

Circle::Circle(double x, double y,  double radius, double r, double g, double b):Point(x,y)
{
	SetColour(r,g,b);
	Radius = radius;
}

Circle::Circle(Point c, double radius, double r, double g, double b)
{
	X = c.GetX();
	Y = c.GetY();
	Radius = radius;
	R = r;
	G = g;
	B = b;
}

double Circle::GetRadius()
{
	return Radius;
}
void Circle::SetRadius(double radius)
{
	Radius = radius;
}
void Circle::Draw()
{
	double p, q, theta = 0.0;
	glColor3f(R,G,B);
	glLoadIdentity();
	glBegin(GL_LINE_LOOP);
	do
	{
		p = X + Radius*cos(theta);
		q = Y + Radius*sin(theta);
		glVertex2f(p,q);
		theta += 0.005;
	}
	while(theta < 2*PI);
	glEnd();
}

// This function is redundant however provides better readability
void Circle::Move(double x, double y, double) 
{
	Point::Move(x,y,0);
}

// End of circle class definition ============================================

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
	double GetLength();
	double Getangle();
	Point GetStart();
	Point GetEnd();
	void Move(double x, double y, double angle);
	void Draw();
};

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


int main()
{
	vector<Line> LineList;

	Point P(100,100);

	LineList.push_back(Line(100,100,150,PI/4.0));
	LineList.push_back(Line(100,100,200,PI/5.0));
	LineList.push_back(Line(100,100,250,PI/6.0));
	LineList.push_back(Line(P,300,PI/7.0));
	LineList.push_back(Line(100,100,350,PI/8.0));

	for(vector<Line>::iterator it=LineList.begin(); it != LineList.end();it++)
		cout << it->GetX() << " " << it->GetY() << " " << it->Getangle() << " " << it->GetLength() << endl;
	_getch();
	return 0;
}