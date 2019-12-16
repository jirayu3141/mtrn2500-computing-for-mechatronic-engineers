// Demonstrates the formatted output to the standard output device.

#include <iostream>
#include <iomanip> //  For setting format and width etc.
#include <conio.h>

using namespace std;

struct Data
{
	double A;
	float B;
	int C;
	char D;
};

class Storage
{
private:
	Data D;
public:
	Storage(double a = 1.0, float b = 2.0, int c = 3, char d = 'A');
	virtual ~Storage();
	virtual void Draw();
	virtual Data GetD() const;
	friend ostream& operator<<(ostream& os, const Data& d);
};

Storage::Storage(double a, float b, int c, char d)
{
	D.A = a;
	D.B = b;
	D.C = c;
	D.D = d;
}

Storage::~Storage()
{
}

void Storage::Draw()
{
}

Data Storage::GetD() const
{
	return D;
}

ostream& operator<<(ostream& os, const Storage& d)
{
	// Setf sets for format flags for the stream
	os.setf(ios::showpoint | ios::right |ios::fixed | ios:: uppercase | ios::showpos);
	// setw sets the field width
	// setprecision sets the decimal precision.
	os <<  setw(12) << setprecision(5) << d.GetD().A << ' ';
	os <<  setw(12) << d.GetD().B << ' ';
	os <<  setw(12) << hex << d.GetD().C << ' ';
	os <<  setw(12) << hex << d.GetD().D << ' ';

	return os;
}

#define SIZE 10

int main()
{
	Storage S[SIZE];

	// Fill in objects
	for(int i = 0; i < SIZE; i++)
		S[i] = Storage(1.0*i, 2.0*i, 3*i, 'A'+i);

	// Stream out objects using the overloaded operator '<<'
	for(int i = 0; i < SIZE; i++)
		cout << S[i] << endl;
	_getch();
	return 0;
}

//ios::left
//ios::right

//ios::dec
//ios::oct
//ios::hex

//ios::showbase
//ios::uppercase
//ios::showpoint
//ios::showpos

//ios::scientific
//ios::fixed
