#pragma once
#include "Vehicle.hpp"
#include "Messages.hpp"

class Kyle : public Vehicle {
public:
	Kyle();
	void draw();
	void update(double dt);
	VehicleModel GetVehicleModel();
	VehicleState GetVehicleState();
protected:
	VehicleModel vm;
	VehicleState vs;
	void initialisation();
	
};
