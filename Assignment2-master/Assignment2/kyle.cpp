#include "Kyle.h"
#include "Wheel.hpp"
#include "Rectangular.hpp"
#include "Cylinder.hpp"
#include "Shape.hpp"
#include "Messages.hpp"
#include "Triangluar.hpp"
#include "Trapezoidal.hpp"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <sys/time.h>
#elif defined(WIN32)
#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include <sys/time.h>
#endif

Kyle::Kyle() {
	vm.remoteID == 0;

	ShapeInit wheel;
	wheel.type = CYLINDER;
	wheel.params.cyl.depth = 2.5;
	wheel.params.cyl.radius = 5;
	wheel.rgb[0] = 1;
	wheel.rgb[1] = 0;
	wheel.rgb[2] = 0;
	wheel.params.cyl.isRolling = true;

	wheel.xyz[0] = 0;
	wheel.xyz[1] = 0;
	wheel.xyz[2] = 0;

	ShapeInit leg1;
	leg1.type = RECTANGULAR_PRISM;
	leg1.params.rect.xlen = 2.5;
	leg1.params.rect.ylen = 15;
	leg1.params.rect.zlen = 2.5;
	leg1.rgb[0] = 0;
	leg1.rgb[1] = 1;
	leg1.rgb[2] = 0;

	leg1.xyz[0] = 0;
	leg1.xyz[1] = wheel.params.cyl.radius;
	leg1.xyz[2] = wheel.params.cyl.depth + leg1.params.rect.zlen/1.5;

	ShapeInit leg2;
	leg2.type = RECTANGULAR_PRISM;
	leg2.params.rect.xlen = 2.5;
	leg2.params.rect.ylen = 15;
	leg2.params.rect.zlen = 2.5;
	leg2.rgb[0] = 0;
	leg2.rgb[1] = 0;
	leg2.rgb[2] = 1;

	leg2.xyz[0] = 0;
	leg2.xyz[1] = wheel.params.cyl.radius;
	leg2.xyz[2] = -wheel.params.cyl.depth - leg1.params.rect.zlen / 1.5;

	ShapeInit pedals;
	pedals.type = CYLINDER;
	pedals.params.cyl.depth = 10;
	pedals.params.cyl.radius = 0.5;
	pedals.rgb[0] = 1;
	pedals.rgb[1] = 1;
	pedals.rgb[2] = 1;

	pedals.xyz[0] = 0;
	pedals.xyz[1] = wheel.params.cyl.radius - pedals.params.cyl.radius;
	pedals.xyz[2] = 0;

	ShapeInit body;
	body.type = RECTANGULAR_PRISM;
	body.params.rect.xlen = 10;
	body.params.rect.ylen = 15;
	body.params.rect.zlen = 10;
	body.rgb[0] = 1;
	body.rgb[1] = 1;
	body.rgb[2] = 0;

	body.xyz[0] = 0;
	body.xyz[1] = wheel.params.cyl.radius + body.params.rect.ylen/2;
	body.xyz[2] = 0;
	
	ShapeInit arm1;
	arm1.type = RECTANGULAR_PRISM;
	arm1.params.rect.xlen = 2.5;
	arm1.params.rect.ylen = 2.5;
	arm1.params.rect.zlen = 10;
	arm1.rgb[0] = 1;
	arm1.rgb[1] = 0;
	arm1.rgb[2] = 0;

	arm1.xyz[0] = 0;
	arm1.xyz[1] = 7.5 + wheel.params.cyl.radius + body.params.rect.ylen / 2 + 5;
	arm1.xyz[2] = 10;
	
	ShapeInit arm2;
	arm2.type = RECTANGULAR_PRISM;
	arm2.params.rect.xlen = 2.5;
	arm2.params.rect.ylen = 2.5;
	arm2.params.rect.zlen = 10;
	arm2.rgb[0] = 0;
	arm2.rgb[1] = 1;
	arm2.rgb[2] = 1;

	arm2.xyz[0] = 0;
	arm2.xyz[1] = 7.5 + wheel.params.cyl.radius + body.params.rect.ylen / 2 + 5;
	arm2.xyz[2] = -10;

	ShapeInit head;
	head.type = RECTANGULAR_PRISM;
	head.params.rect.xlen = 5;
	head.params.rect.ylen = 5;
	head.params.rect.zlen = 5;
	head.rgb[0] = 1;
	head.rgb[1] = 0;
	head.rgb[2] = 1;

	head.xyz[0] = 0;
	head.xyz[1] = 5+wheel.params.cyl.radius + body.params.rect.ylen / 2 + 10;
	head.xyz[2] = 0;

	vm.shapes.push_back(head);
	vm.shapes.push_back(arm1);
	vm.shapes.push_back(arm2);
	vm.shapes.push_back(leg1);
	vm.shapes.push_back(leg2);
	vm.shapes.push_back(body);
	vm.shapes.push_back(pedals);
	vm.shapes.push_back(wheel);
	
	initialisation();
}
void Kyle::initialisation() {
	int i = 0;
	while (i < vm.shapes.size()) {
		vm.shapes[i].rotation = 0;
		if (vm.shapes[i].type == RECTANGULAR_PRISM) {
			double x_len = vm.shapes[i].params.rect.xlen;
			double y_len = vm.shapes[i].params.rect.ylen;
			double z_len = vm.shapes[i].params.rect.zlen;
			Rectangular* rect = new Rectangular(x_len, y_len, z_len, vm.shapes[i].rotation);
			rect->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
			rect->setColor(vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2]);
			addShape(rect);
		}
		else if (vm.shapes[i].type == TRIANGULAR_PRISM) {
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
		}
		else if (vm.shapes[i].type == TRAPEZOIDAL_PRISM) {
			double a_len = vm.shapes[i].params.trap.alen;
			double offset = vm.shapes[i].params.trap.aoff;
			double height = vm.shapes[i].params.trap.height;
			double depth = vm.shapes[i].params.trap.depth;
			Trapezoidal* trap = new Trapezoidal(a_len, offset, height, depth, vm.shapes[i].rotation);
			trap->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
			trap->setColor(vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2]);
			addShape(trap);
		}
		else if (vm.shapes[i].type == CYLINDER) {
			double radius = vm.shapes[i].params.cyl.radius;
			double depth = vm.shapes[i].params.cyl.depth;
			if (vm.shapes[i].params.cyl.isRolling == true)
			{
				Wheel* wheel = new Wheel(radius, depth, vm.shapes[i].rotation);
				wheel->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
				wheel->setColor(vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2]);
				addShape(wheel);
			}
			else
			{
				Cylinder* cyl = new Cylinder(radius, depth, vm.shapes[i].rotation);
				cyl->setPosition(vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
				cyl->setColor(vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2]);
				addShape(cyl);
			}
		}
		i++;
	}
}
VehicleModel Kyle::GetVehicleModel() {
	return vm;
}
VehicleState Kyle::GetVehicleState() {
	return vs;
}
void Kyle::update(double dt) {
	speed = clamp(MAX_BACKWARD_SPEED_MPS, speed, MAX_FORWARD_SPEED_MPS);
	steering = clamp(MAX_LEFT_STEERING_DEGS, steering, MAX_RIGHT_STEERING_DEGS);

	// update position by integrating the speed
	x += speed * dt * cos(rotation * 3.1415926535 / 180.0);
	z += speed * dt * sin(rotation * 3.1415926535 / 180.0);
	// update heading
	rotation += dt * steering * speed;

	while (rotation > 360) rotation -= 360;
	while (rotation < 0) rotation += 360;

	// update wheels rolling
	
	if (wheelroll > 10*3.1415926535) wheelroll = 0;
	if (wheelroll < -10*3.1415926535) wheelroll = 0;
	
	// Having terminal prints outs of variables are so good for debugging
	//std::cout << wheelroll << std::endl;
	wheelroll += speed * dt;


	if (fabs(speed) < .1)
		speed = 0;
	if (fabs(steering) < .1)
		steering = 0;


}

void Kyle::draw() {
	
	glPushMatrix();
	//glScaled(0.5, 0.5,0.5);
	positionInGL();
	glRotated(steering, 1, 0, 0);
	int i = 0;
	std::vector<Shape *>::iterator it;
	it = shapes.begin();
	while (it != shapes.end()) {
		if ((*it) == dynamic_cast<Wheel*>(*it)) {
			dynamic_cast<Wheel*>(*it)->Setroll(wheelroll);
		}
		(*it)->draw();
		it++;
	}

	
	glPopMatrix();
}
