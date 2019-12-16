#include "Rectangular.hpp"

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

Rectangular::Rectangular()
{
	Setlength(10.0, 10.0, 10.0);
}

Rectangular::Rectangular(double x_len, double y_len, double z_len)
{
	Setlength(x_len, y_len, z_len);
}

Rectangular::Rectangular(double x_len, double y_len, double z_len, double rotation) {
	Setlength(x_len, y_len, z_len);
	this->rotation = rotation;
}

double Rectangular::Getx_length()
{
	return x_length;
}

double Rectangular::Gety_length()
{
	return y_length;
}

double Rectangular::Getz_length()
{
	return z_length;
}

void Rectangular::Setx_length(double x_len)
{
	x_length = x_len;
}

void Rectangular::Sety_length(double y_len)
{
	y_length = y_len;
}

void Rectangular::Setz_length(double z_len)
{
	z_length = z_len;
}

void Rectangular::Setlength(double x_len, double y_len, double z_len)
{
	x_length = x_len;
	y_length = y_len;
	z_length = z_len;
}

void Rectangular::draw()
{
	glColor3d(red, green, blue);
	glPushMatrix();
	positionInGL();
	glBegin(GL_QUADS);

	// First plane paralell to YZ plane
	glVertex3d(x_length / 2, y_length , z_length / 2);
	glVertex3d(x_length / 2, 0, z_length / 2);
	glVertex3d(x_length / 2, 0, -z_length / 2);
	glVertex3d(x_length / 2, y_length, -z_length / 2);
	//Second plane paralell to YZ plane
	glVertex3d(-x_length / 2, y_length , z_length / 2);
	glVertex3d(-x_length / 2, 0, z_length / 2);
	glVertex3d(-x_length / 2, 0, -z_length / 2);
	glVertex3d(-x_length / 2, y_length, -z_length / 2);

	//First plane paralell to XZ plane
	glVertex3d(x_length / 2, y_length, z_length / 2);
	glVertex3d(-x_length / 2, y_length, z_length / 2);
	glVertex3d(-x_length / 2, y_length, -z_length / 2);
	glVertex3d(x_length / 2, y_length, -z_length / 2);
	//Second plane paralell to XZ plane
	glVertex3d(x_length / 2, 0, z_length / 2);
	glVertex3d(-x_length / 2, 0, z_length / 2);
	glVertex3d(-x_length / 2, 0, -z_length / 2);
	glVertex3d(x_length / 2, 0, -z_length / 2);

	// First plane paralell to XY plane
	glVertex3d(x_length / 2, y_length , z_length / 2);
	glVertex3d(-x_length / 2, y_length , z_length / 2);
	glVertex3d(-x_length / 2, 0, z_length / 2);
	glVertex3d(x_length / 2, 0, z_length / 2);
	// Second plane paralell to XY plane
	glVertex3d(x_length / 2, y_length , -z_length / 2);
	glVertex3d(-x_length / 2, y_length, -z_length / 2);
	glVertex3d(-x_length / 2, 0 , -z_length / 2);
	glVertex3d(x_length / 2, 0, -z_length / 2);

	glEnd();
	glPopMatrix();
}
