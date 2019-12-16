// Demonstrates user defined stream manipulators.

#include <iostream>
#include <fstream> // 
#include <iomanip>
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
	os.setf(ios::showpoint | ios::right |ios::fixed | ios::showpos | ios::uppercase);
	os <<  setw(12) << setprecision(3) << d.GetD().A << ' ';
	os <<  setw(12) << d.GetD().B << ' ';
	os <<  setw(12) << hex <<  d.GetD().C << ' ';
	os <<  setw(12) << hex << d.GetD().D << ' ';

	return os;
}

ostream& beep(ostream& os)
{
	os << '\a';

	return os;
}

#define SIZE 2

int main()
{
	Storage S[SIZE];

	// Fill in objects
	for(int i = 0; i < SIZE; i++)
		S[i] = Storage(1.0*i, -2.0f*i, 3*i, 'A'+i);

	// Stream out objects
	for (int i = 0; i < SIZE; i++) {
		cout << S[i] << beep << "First beep " << beep << "Second beep" << endl;
		_getch();
	}

	//ostream& operator<<(ostream& os, ostream& (*fp)(ostream& os));
	_getch();
	return 0;
}
