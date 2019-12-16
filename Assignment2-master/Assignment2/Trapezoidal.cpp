#include "Trapezoidal.hpp"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined(WIN32)
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

Trapezoidal::Trapezoidal()
{
	longside = 10;
	offset = 2.5;
	height = 10;
	depth = 10;
}

Trapezoidal::Trapezoidal(double longside, double offset, double height)
{
	SetTrapezium(longside, offset, height);
}

Trapezoidal::Trapezoidal(double longside, double offset, double height, double depth)
{
	SetTrapezium(longside, offset, height);
	this->depth = depth;
}

Trapezoidal::Trapezoidal(double longside, double offset, double height, double depth, double rotation)
{
	SetTrapezium(longside, offset, height);
	this->depth = depth;
	this->rotation = rotation;
}

double Trapezoidal::Getlong()
{
	return longside;
}

double Trapezoidal::Getshort()
{
	return shortside;
}

double Trapezoidal::Getoffset()
{
	return offset;
}

double Trapezoidal::Getheight()
{
	return height;
}

double Trapezoidal::Getdepth()
{
	return depth;
}

void Trapezoidal::Setlong(double longside)
{
	this->longside = longside;
}

void Trapezoidal::Setshort(double shortside)
{
	this->shortside = shortside;
	offset = (longside - shortside) / 2;
}


void Trapezoidal::Setoffset(double offset)
{
	this->offset = offset;
	shortside = longside - 2 * offset;
}

void Trapezoidal::Setheight(double height)
{
	this->height = height;
}

void Trapezoidal::Setdepth(double depth)
{
	this->depth = depth;
}

void Trapezoidal::SetTrapezium(double longside, double offset, double height)
{
	this->longside = longside;
	Setoffset(offset);
	this->height = height;
}

void Trapezoidal::draw()
{
	glColor3d(red, green, blue);
	glPushMatrix();
	positionInGL();
	glBegin(GL_QUADS);

	// Base
	glVertex3d(longside / 2, 0, depth / 2);
	glVertex3d(longside / 2, 0, -depth / 2);
	glVertex3d(-longside / 2, 0, -depth / 2);
	glVertex3d(-longside / 2, 0, depth / 2);
	// Top
	glVertex3d((longside - 2 * offset) / 2, height, depth / 2);
	glVertex3d((longside - 2 * offset) / 2, height , -depth / 2);
	glVertex3d(-(longside - 2 * offset) / 2, height, -depth / 2);
	glVertex3d(-(longside - 2 * offset) / 2, height , depth / 2);

	// First inclined plane
	glVertex3d(longside / 2, 0, depth / 2);
	glVertex3d(longside / 2, 0, -depth / 2);
	glVertex3d((longside - 2 * offset) / 2, height , -depth / 2);
	glVertex3d((longside - 2 * offset) / 2, height , depth / 2);
	// Second inclined plane
	glVertex3d(-longside / 2, 0, depth / 2);
	glVertex3d(-longside / 2, 0, -depth / 2);
	glVertex3d(-(longside - 2 * offset) / 2, height , -depth / 2);
	glVertex3d(-(longside - 2 * offset) / 2, height , depth / 2);

	// First trapezium
	glVertex3d(longside / 2, 0, depth / 2);
	glVertex3d(-longside / 2, 0, depth / 2);
	glVertex3d(-(longside - 2 * offset) / 2, height , depth / 2);
	glVertex3d((longside - 2 * offset) / 2, height , depth / 2);
	// Second trapezium
	glVertex3d(longside / 2, 0, -depth / 2);
	glVertex3d(-longside / 2, 0, -depth / 2);
	glVertex3d(-(longside - 2 * offset) / 2, height, -depth / 2);
	glVertex3d((longside - 2 * offset) / 2, height, -depth / 2);

	glEnd();
	glPopMatrix();
}
