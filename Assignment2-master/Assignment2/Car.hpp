#pragma once
#include "Vehicle.hpp"
#include "Messages.hpp"

class Car : public Vehicle
{
public:
	Car(); // local model
	Car(VehicleModel vm);

	VehicleModel GetVehicleModel();
	VehicleState GetVehicleState();
	std::vector<int> Getrollwheellist();
	std::vector<int> Getsteerwhellist();

	void Addrollwheel(int position);
	void Addsteerwheel(int position);

	void update(double dt);


	void draw();

protected:
	VehicleState vs;
	VehicleModel vm;
	std::vector<int> rollwheelposition; // Store the index of wheels in shapes
	std::vector<int> steerwheelposition;
	double wheelroll;
	void Initialization();
};
