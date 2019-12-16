#include "Shape.hpp"

class Rectangular : public Shape
{
public:
	Rectangular();
	Rectangular(double x_len, double y_len, double z_len);
	Rectangular(double x_len, double y_len, double z_len, double rotation);

	double Getx_length();
	double Gety_length();
	double Getz_length();

	void Setx_length(double x_len);
	void Sety_length(double y_len);
	void Setz_length(double z_len);
	void Setlength(double x_len, double y_len, double z_len);

	void draw();

protected:
	double x_length, y_length, z_length;
};
