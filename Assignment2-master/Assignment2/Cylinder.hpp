#pragma once
#include "Shape.hpp"

class Cylinder : public Shape {
public:
	Cylinder();
	Cylinder(double radius, double length);
	Cylinder(double radius, double length, double rotation);

	double Getradius();
	double Getlength();

	void Setradius(double size);
	void Setlength(double size);

	void draw();

protected:
	double radius;
	double length;
};
