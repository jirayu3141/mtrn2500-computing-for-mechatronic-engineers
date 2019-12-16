#pragma once
#include "Cylinder.hpp"

class Wheel : public Cylinder
{
public: 
	Wheel(double radius, double length);
	Wheel(double radius, double length, double rotation);

	void Setroll(double roll);

	void draw();

protected:
	double roll;
};
