#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;

double Add(double a, double b)
{
	return (a+b);
}

double Sub(double a, double b)
{
	return (a-b);
}

double Mult(double a, double b)
{
	return a*b;
}

int main()
{
	double (*FcnPtr)(double, double);

	cout << "Add function is at \t" << hex << Add << endl;
	cout << "Sub function is at \t" << hex << Sub << endl;
	cout << "Mult function is at \t" << hex << Mult << endl;

	_getch();
	FcnPtr = Add;

	cout << "After 'FcnPtr = Add' FcnPtr is pointing to \t" << hex << FcnPtr << endl;

	cout << "FcnPtr(10.0,20.0) gives " << FcnPtr(10.0,20.0) << endl;

	FcnPtr = Sub;

	cout << "After 'FcnPtr = Sub' FcnPtr is pointing to \t" << hex << FcnPtr << endl;

	cout << "FcnPtr(10.0,20.0) gives " << FcnPtr(10.0,20.0) << endl;

	FcnPtr = Mult;

	cout << "After 'FcnPtr = Mult' FcnPtr is pointing to \t" << hex << FcnPtr << endl;

	cout << "FcnPtr(10.0,20.0) gives " << FcnPtr(10.0,20.0) << endl;

	cout << "and finally address of main() is \t\t" << hex << main << endl;

	_getch();

	return 0;
}