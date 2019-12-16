// Demonstrates how data is packed in memory.
// Compares the size of data and the size of objects.
// Demonstrates the effect of virtual functions on object size.
// Demonstrates how to change the data packing arrangement.

#include <iostream>
#include <conio.h>

using namespace std;

#pragma pack(8)
struct Data
{
	double A;  // Size = 8
	float B;   // Size = 4
	int C;     // Size = 4
	char D;    // Size = 1	
};

class Storage
{
private:
	Data D;
public:
	Storage();
	 ~Storage();
	void Draw();
	Data GetD();
};

Storage::Storage()
{
	D.A = 1.0;
	D.B = 2.0;
	D.C = 3;
	D.D = '4';
}

Storage::~Storage()
{
}

void Storage::Draw()
{
}

Data Storage::GetD()
{
	return D;
}

int main()
{
	Storage S;

	cout << "sizeof(Data) is " << sizeof(Data) << " bytes." << endl;
	cout << "sizeof(S) is " << sizeof(S) << " bytes." << endl;

	_getch();
	return 0;
}

