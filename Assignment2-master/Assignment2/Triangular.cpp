#include "Triangluar.hpp"
#include <cmath>
#define PI 3.14159265358979323846;

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

Triangular::Triangular()
{
	Setside(10.0, 10.0, 10.0);
}

Triangular::Triangular(double sideA_len, double sideB_len)
{
	sideA = sideA_len;
	sideB = sideB_len;
	Setangle(60);
}

Triangular::Triangular(double sideA_len, double sideB_len, double sideC_len)
{
	Setside(sideA_len, sideB_len, sideC_len);
}

Triangular::Triangular(double sideA_len, double sideB_len, double sideC_len, double depth)
{
	Setside(sideA_len, sideB_len, sideC_len);
	this->depth = depth;
}

Triangular::Triangular(double sideA_len, double sideB_len, double sideC_len, double depth, double rotation)
{
	Setside(sideA_len, sideB_len, sideC_len);
	this->depth = depth;
	this->rotation = rotation;
}
double Triangular::GetsideA()
{
	return sideA;
}

double Triangular::GetsideB()
{
	return sideB;
}

double Triangular::GetsideC()
{
	return sideC;
}

double Triangular::Getdepth()
{
	return depth;
}

double Triangular::Getangle()
{
	return angle * 180 / PI;
}

void Triangular::SetsideA(double sideA_len)
{
	sideA = sideA_len;
	UpdateSideC();
}

void Triangular::SetsideB(double sideB_len)
{
	sideB = sideB_len;
	UpdateSideC();
}

void Triangular::SetsideC(double sideC_len)
{
	sideC = sideC_len;
	UpdateAngle();
}

void Triangular::Setside(double sideA_len, double sideB_len, double sideC_len)
{
	sideA = sideA_len;
	sideB = sideB_len;
	sideC = sideC_len;
	UpdateAngle();
}

void Triangular::Setdepth(double len)
{
	depth = len;
}

void Triangular::Setangle(double degree)
{
	angle = degree / 180 * PI;
	UpdateSideC();
}

void Triangular::UpdateAngle()
{
	double ratio = (pow(sideA, 2) + pow(sideB, 2) - pow(sideC, 2)) / (2 * sideA * sideB);
	angle = acos(ratio);
}

void Triangular::UpdateSideC()
{
	sideC = sqrt(pow(sideA, 2) + pow(sideB, 2) - 2 * sideA * sideB * cos(angle));
}

void Triangular::draw()
{
	glPushMatrix();
	positionInGL();
	glColor3d(red, green, blue);

	glBegin(GL_QUADS);
	// The plane(base) parallel to XZ plane
	glVertex3d((sideA / 2), 0, (depth / 2));
	glVertex3d(-(sideA / 2), 0, (depth / 2));
	glVertex3d(-(sideA / 2), 0, -(depth / 2));
	glVertex3d(+(sideA / 2), 0, -(depth / 2));

	// The rectangular plane containing sideB
	glVertex3d(-(sideA / 2), 0, (depth / 2));
	glVertex3d(-(sideA / 2), 0, -(depth / 2));
	glVertex3d(-(sideA / 2) + sideB * cos(angle), sideB * sin(angle), -(depth / 2));
	glVertex3d(-(sideA / 2) + sideB * cos(angle), sideB * sin(angle), (depth / 2));

	// The rectangular plane containing sideC
	glVertex3d((sideA / 2), 0, (depth / 2));
	glVertex3d((sideA / 2), 0, -(depth / 2));
	glVertex3d(-(sideA / 2) + sideB * cos(angle), sideB * sin(angle), -(depth / 2));
	glVertex3d(-(sideA / 2) + sideB * cos(angle), sideB * sin(angle), (depth / 2));

	glEnd();

	// Two trangle plane
	glBegin(GL_TRIANGLES);
	glVertex3d(-(sideA / 2), 0, (depth / 2));
	glVertex3d((sideA / 2), 0, (depth / 2));
	glVertex3d(-(sideA / 2) + sideB * cos(angle), sideB * sin(angle), (depth / 2));

	glVertex3d(-(sideA / 2), 0, -(depth / 2));
	glVertex3d((sideA / 2), 0, -(depth / 2));
	glVertex3d(-(sideA / 2) + sideB * cos(angle), sideB * sin(angle), -(depth / 2));

	glEnd();
	glPopMatrix();
}
