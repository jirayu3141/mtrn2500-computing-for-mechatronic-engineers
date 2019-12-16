// Demonstrates reading from a file.

#include <iostream>
#include <fstream>
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
	virtual void SetD(double a, float b, int c, char d);
	friend ostream& operator<<(ostream& os, const Data& d);
	friend istream& operator>>(istream& is, Storage& d);
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

void Storage::SetD(double a, float b, int c, char d)
{
	D.A = a;
	D.B = b;
	D.C = c;
	D.D = d;
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

istream& operator>>(istream& is, Storage& d)
{
	double a;
	float b;
	int c;
	char ch;
	is >> a >> b >> c >> ch;

	d.D.A = a;
	d.D.B = b;
	d.D.C = c;
	d.D.D = ch;

	return is;
}

ostream& sp(ostream& os)
{
	os << ' ';

	return os;
}

#define SIZE 100

int main()
{
	Storage S[SIZE];

	ifstream is("ASCIIData.dat", ios::in);

	int j = 0;
	while (!is.eof())
	{
		is >> hex >> S[j++];
	}

	for(int i = 0; i < j-1; i++)
	{
		cout << S[i] << endl;
	}

	cout << endl;
	is.close();
	_getch();
	return 0;
}

// ios::in		(input) Allow input operations on the stream.
// ios::ate		(at end) Set the stream's position indicator to the end of the stream on opening.
// ios::app		(append) Set the stream's position indicator to the end of the stream before each output operation.
// ios::binary	(binary) Consider stream as binary rather than text.
// ios::out 	(output) Allow output operations on the stream.
// ios::trunc	(truncate) Any current content is discarded, assuming a length of zero on opening.