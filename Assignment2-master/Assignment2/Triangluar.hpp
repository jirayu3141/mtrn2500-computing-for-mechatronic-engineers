#include "Shape.hpp"

class Triangular : public Shape
{
public:
	Triangular();
	Triangular(double sideA_len, double sideB_len);
	Triangular(double sideA_len, double sideB_len, double sideC_len);
	Triangular(double sideA_len, double sideB_len, double sideC_len, double depth);
	Triangular(double sideA_len, double sideB_len, double sideC_len, double depth, double rotation);

	double GetsideA();
	double GetsideB();
	double GetsideC();
	double Getdepth();
	double Getangle();

	void SetsideA(double sideA_len);
	void SetsideB(double sideB_len);
	void SetsideC(double sideC_len);
	void Setside(double sideA_len, double sideB_len, double sideC_len);
	void Setdepth(double len);
	void Setangle(double degree);

	// When SideC changes, Use it
	void UpdateAngle();
	// When SideA, SideB and angle change, Use it
	void UpdateSideC();

	void draw();

protected:
	double sideA = 0;
	double sideB = 0;
	double sideC = 0;
	double depth = 10;
	double angle = 0; // The angle between sideA and sideB


};