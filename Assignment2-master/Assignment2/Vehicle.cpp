#include "Vehicle.hpp"

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

Vehicle::Vehicle() {
	speed = steering = 0;
};

Vehicle::~Vehicle()
{ 
	// clean-up added shapes
	for(int i = 0; i < shapes.size(); i++) {
		delete shapes[i];
	}
}

void Vehicle::update(double dt)
{
	speed = clamp(MAX_BACKWARD_SPEED_MPS, speed, MAX_FORWARD_SPEED_MPS);
	steering = clamp(MAX_LEFT_STEERING_DEGS, steering, MAX_RIGHT_STEERING_DEGS);

	// update position by integrating the speed
	x += speed * dt * cos(rotation * 3.1415926535 / 180.0);
	z += speed * dt * sin(rotation * 3.1415926535 / 180.0);
	// update heading
	rotation += dt * steering * speed;

	while (rotation > 360) rotation -= 360;
	while (rotation < 0) rotation += 360;


	if(fabs(speed) < .1)
		speed = 0;
	if(fabs(steering) < .1)
		steering = 0;

}

void Vehicle::update(double speed_, double steering_, double dt) 
{
	speed = speed + ((speed_) - speed)*dt*4;
	steering = steering + (steering_ - steering)*dt * 6;

	update(dt);
}

void Vehicle::addShape(Shape * shape) 
{
	shapes.push_back(shape);
}

double clamp(double a, double n, double b) {

	if (a < b) {
		if (n < a) n = a;
		if (n > b) n = b;
	} else {
		if (n < b) n = b;
		if (n > a) n = a;
	}

	return n;

};

double* Vehicle::chase(Vehicle* objcar)
{
	double dx = objcar->getX() - x;
	double dz = objcar->getZ() - z;
	double distance = sqrt(dx * dx + dz * dz);
	double angle = atan2(dz, dx) / 3.1415926535 * 180;
	double steerangle = angle - rotation;
	double safedistance = 10;
	double steer = 0, rate = 0;
	double* RateandSteer = new double[2];

	while (steerangle > 180) steerangle -= 360;
	while (steerangle < -180) steerangle += 360;

	if (15 <= steerangle)
	{
		steer = MAX_LEFT_STEERING_DEGS;
	}
	else if (steerangle <= -15)
	{
		steer = MAX_RIGHT_STEERING_DEGS;
	}
	else
	{
		steer = steerangle;
	}
	if (distance <= safedistance) // Control distance when chasing 
	{
		double difference = (distance - safedistance) / safedistance;
		if (abs(difference) < 0.1) difference = 0;
		rate = (1 + difference) * objcar->getSpeed();
	}
	else
	{
		rate = MAX_FORWARD_SPEED_MPS;
	}
	RateandSteer[0] = rate;
	RateandSteer[1] = steer;
	return RateandSteer;
	delete[]RateandSteer;

}

void Vehicle::chaseswitch()
{
	ChaseorNot = !ChaseorNot;
}

bool Vehicle::getchasesignal()
{
	return ChaseorNot;
}
