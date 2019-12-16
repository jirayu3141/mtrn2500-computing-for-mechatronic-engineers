#include "Cylinder.hpp"

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

Cylinder::Cylinder()
{
}

Cylinder::Cylinder(double radius, double length)
{
	this->radius = radius;
	this->length = length;
}

Cylinder::Cylinder(double radius, double length, double rotation)
{
	this->radius = radius;
	this->length = length;
	this->rotation = rotation;
}

double Cylinder::Getradius()
{
	return radius;
}

double Cylinder::Getlength()
{
	return length;
}

void Cylinder::Setradius(double size)
{
	this->radius = size;
}

void Cylinder::Setlength(double size)
{
	this->length = size;
}

// Currently sets a cylinder with base at z = 0;
void Cylinder::draw() {
	glColor3d(red, green, blue);

	glPushMatrix();
	positionInGL();
	glTranslated(0, radius, 0);
	// For the curved surface of the cylinder the idea is to draw 2 half cylinders either side of the origin.
	glPushMatrix();
	gluCylinder(gluNewQuadric(), radius, radius, length / 2, 25, 25);
	glRotated(180, 0, 1, 0);
	gluCylinder(gluNewQuadric(), radius, radius, length / 2, 25, 25);
	glPopMatrix();

	// Draw a disc-
	glPushMatrix();
	glColor3d(1, 1, 1);
	glTranslated(0, 0, length / 2);
	gluDisk(gluNewQuadric(), 0, radius, 25, 25);
	glTranslated(0, 0, -length);
	gluDisk(gluNewQuadric(), 0, radius, 25, 25);
	glPopMatrix();

	glPopMatrix();
}