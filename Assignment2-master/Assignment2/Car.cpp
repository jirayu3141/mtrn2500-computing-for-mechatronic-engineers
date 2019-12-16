#include "Car.hpp"
#include "Rectangular.hpp"
#include "Triangluar.hpp"
#include "Trapezoidal.hpp"
#include "Cylinder.hpp"
#include "Wheel.hpp"

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

Car::Car()
{
	// Default model
	vm.remoteID = 0;
	
	// Shapes Appearance Parameters
	// Rectangular Prism (Body)
	ShapeInit body;
	body.type = RECTANGULAR_PRISM;
	body.params.rect.xlen = 3;
	body.params.rect.ylen = 1;
	body.params.rect.zlen = 2.5;
	body.rotation = 0;
	body.rgb[0] = 1;
	body.rgb[1] = 1;
	body.rgb[2] = 1;

	// Triangular Prism (Front)
	ShapeInit front;
	front.type = TRIANGULAR_PRISM;
	front.params.tri.alen = 1;
	front.params.tri.angle = 90;
	front.params.tri.blen = 1;
	front.params.tri.depth = 2.5;
	front.rotation = 0;
	front.rgb[0] = 0;
	front.rgb[1] = 1;
	front.rgb[2] = 1;

	// Triangular Prism (Back)
	ShapeInit back;
	back.type = TRIANGULAR_PRISM;
	back.params.tri.alen = 0.5;
	back.params.tri.angle = 90;
	back.params.tri.blen = 1;
	back.params.tri.depth = 2.5;
	back.rotation = 180;
	back.rgb[0] = 0;
	back.rgb[1] = 1;
	back.rgb[2] = 0;

	// Trapezodial (Cabin)
	ShapeInit cabin;
	cabin.type = TRAPEZOIDAL_PRISM;
	cabin.params.trap.alen = 2.5;
	cabin.params.trap.blen = 1.5;
	cabin.params.trap.aoff = 0.5;
	cabin.params.trap.depth = 2.5;
	cabin.params.trap.height = 0.5;
	cabin.rotation = 0;
	cabin.rgb[0] = 0;
	cabin.rgb[1] = 0;
	cabin.rgb[2] = 1;

	// Wheel 1 (Front Right)
	ShapeInit wheel1;
	wheel1.type = CYLINDER;
	wheel1.params.cyl.radius = 0.5;
	wheel1.params.cyl.depth = 0.25;
	wheel1.params.cyl.isRolling = true;
	wheel1.params.cyl.isSteering = true;
	wheel1.rotation = 0;
	wheel1.rgb[0] = 1;
	wheel1.rgb[1] = 1;
	wheel1.rgb[2] = 0;

	// Wheel 2 (Back Right)
	ShapeInit wheel2;
	wheel2.type = CYLINDER;
	wheel2.params.cyl.radius = 0.5;
	wheel2.params.cyl.depth = 0.25;
	wheel2.params.cyl.isRolling = true;
	wheel2.params.cyl.isSteering = false;
	wheel2.rotation = 0;
	wheel2.rgb[0] = 1;
	wheel2.rgb[1] = 0;
	wheel2.rgb[2] = 1;

	// Wheel 3 (Back Left)
	ShapeInit wheel3;
	wheel3.type = CYLINDER;
	wheel3.params.cyl.radius = 0.5;
	wheel3.params.cyl.depth = 0.25;
	wheel3.params.cyl.isRolling = true;
	wheel3.params.cyl.isSteering = false;
	wheel3.rotation = 0;
	wheel3.rgb[0] = 1;
	wheel3.rgb[1] = 0;
	wheel3.rgb[2] = 0;

	// Wheel 4 (Front Left)
	ShapeInit wheel4;
	wheel4.type = CYLINDER;
	wheel4.params.cyl.radius = 0.5;
	wheel4.params.cyl.depth = 0.25;
	wheel4.params.cyl.isRolling = true;
	wheel4.params.cyl.isSteering = true;
	wheel4.rotation = 0;
	wheel4.rgb[0] = 0;
	wheel4.rgb[1] = 0;
	wheel4.rgb[2] = 1;

	// Shapes Position Parameters
	body.xyz[0] = 0;
	body.xyz[1] = wheel1.params.cyl.radius;
	body.xyz[2] = 0;

	front.xyz[0] = (body.params.rect.xlen + front.params.tri.alen) / 2;
	front.xyz[1] = wheel1.params.cyl.radius;
	front.xyz[2] = 0;

	back.xyz[0] = -(body.params.rect.xlen + back.params.tri.alen) / 2;
	back.xyz[1] = wheel1.params.cyl.radius;
	back.xyz[2] = 0;

	cabin.xyz[0] = 0;
	cabin.xyz[1] = wheel1.params.cyl.radius + body.params.rect.ylen;
	cabin.xyz[2] = 0;

	wheel1.xyz[0] = body.params.rect.xlen / 2;
	wheel1.xyz[1] = 0;
	wheel1.xyz[2] = body.params.rect.zlen / 2;

	wheel2.xyz[0] = -body.params.rect.xlen / 2;
	wheel2.xyz[1] = 0;
	wheel2.xyz[2] = body.params.rect.zlen / 2;

	wheel3.xyz[0] = -body.params.rect.xlen / 2;
	wheel3.xyz[1] = 0;
	wheel3.xyz[2] = -body.params.rect.zlen / 2;

	wheel4.xyz[0] = body.params.rect.xlen / 2;
	wheel4.xyz[1] = 0;
	wheel4.xyz[2] = -body.params.rect.zlen / 2;

	// Add to shapes
	vm.shapes.push_back(body);
	vm.shapes.push_back(front);
	vm.shapes.push_back(back);
	vm.shapes.push_back(cabin);
	vm.shapes.push_back(wheel1);
	vm.shapes.push_back(wheel2);
	vm.shapes.push_back(wheel3);
	vm.shapes.push_back(wheel4);

	Initialization();
}

Car::Car(VehicleModel vm)
{
	this->vm = vm;
	Initialization();
}

VehicleModel Car::GetVehicleModel()
{
	return vm;
}

VehicleState Car::GetVehicleState()
{
	return vs;
}

std::vector<int> Car::Getrollwheellist()
{
	return rollwheelposition;
}

std::vector<int> Car::Getsteerwhellist()
{
	return steerwheelposition;
}

void Car::Addrollwheel(int position)
{
	rollwheelposition.push_back(position);
}

void Car::Addsteerwheel(int position)
{
	steerwheelposition.push_back(position);
}

// Vehicle Model Initialization
void Car::Initialization()
{
	for (int i = 0; i < vm.shapes.size(); i++)
	{
		switch (vm.shapes[i].type)
		{
		case RECTANGULAR_PRISM:
		{
			double x_len = vm.shapes[i].params.rect.xlen;
			double y_len = vm.shapes[i].params.rect.ylen;
			double z_len = vm.shapes[i].params.rect.zlen;
			Rectangular* rect = new Rectangular(x_len, y_len, z_len, vm.shapes[i].rotation);
			rect->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
			rect->setColor(vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2]);
			addShape(rect);
			break;
		}
		case TRIANGULAR_PRISM:
		{
			double a_len = vm.shapes[i].params.tri.alen;
			double b_len = vm.shapes[i].params.tri.blen;
			double angle = vm.shapes[i].params.tri.angle;
			Triangular* tri = new Triangular(a_len, b_len);
			tri->Setangle(angle);
			tri->Setdepth(vm.shapes[i].params.tri.depth);
			tri->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
			tri->setColor(vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2]);
			tri->setRotation(vm.shapes[i].rotation);
			addShape(tri);
			break;
		}
		case TRAPEZOIDAL_PRISM:
		{
			double a_len = vm.shapes[i].params.trap.alen;
			double offset = vm.shapes[i].params.trap.aoff;
			double height = vm.shapes[i].params.trap.height;
			double depth = vm.shapes[i].params.trap.depth;
			Trapezoidal* trap = new Trapezoidal(a_len, offset, height, depth, vm.shapes[i].rotation);
			trap->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
			trap->setColor(vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2]);
			addShape(trap);
			break;
		}
		case CYLINDER:
		{
			double radius = vm.shapes[i].params.cyl.radius;
			double depth = vm.shapes[i].params.cyl.depth;
			if (vm.shapes[i].params.cyl.isRolling == true)
			{
				Wheel* wheel = new Wheel(radius, depth, vm.shapes[i].rotation);
				wheel->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
				wheel->setColor(vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2]);
				addShape(wheel);
				Addrollwheel(shapes.size() - 1); // The index in shapes.
				if (vm.shapes[i].params.cyl.isSteering == true)
				{
					Addsteerwheel(shapes.size() - 1);
				}
			}
			else
			{
				Cylinder* cyl = new Cylinder(radius, depth, vm.shapes[i].rotation);
				cyl->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
				cyl->setColor(vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2]);
				addShape(cyl);
			}
			break;
		}
		default:
		{break; }
		}
	}
 }

void Car::update(double dt)
{
	speed = clamp(MAX_BACKWARD_SPEED_MPS, speed, MAX_FORWARD_SPEED_MPS);
	steering = clamp(MAX_LEFT_STEERING_DEGS, steering, MAX_RIGHT_STEERING_DEGS);

	// update position by integrating the speed
	x += speed * dt * cos(rotation * 3.1415926535 / 180.0);
	z += speed * dt * sin(rotation * 3.1415926535 / 180.0);
	// update heading
	rotation += dt * steering * speed;

	while (rotation > 180) rotation -= 360;
	while (rotation < -180) rotation += 360;

	// update wheels rolling

	if (wheelroll > 2 * 3.1415926535) wheelroll = 0;
	if (wheelroll < -2 * 3.1415926535) wheelroll = 0;
	wheelroll += speed * dt;

	if (fabs(speed) < .1)
		speed = 0;
	if (fabs(steering) < .1)
		steering = 0;


}

void Car::draw()
{
	glPushMatrix();
	positionInGL();

	for (int i = 0; i < shapes.size(); i++) // Draw all the shapes
	{
		for (int j = 0; j < rollwheelposition.size(); j++) // Find wheels
		{
			if (i == rollwheelposition[j])
			{
				dynamic_cast<Wheel*>(shapes[i])->Setroll(wheelroll);
				for (int k = 0; k < steerwheelposition.size(); k++) // Find steering wheels
				{
					if (i == steerwheelposition[k])
					{
						shapes[i]->setRotation(steering);
					}
				}
			}
		}
		shapes[i]->draw();
	}
	glPopMatrix();
}