// Demonstrates template functions.

#include <iostream>
#include <iomanip>
#include <circle.h>
#include "line.h"
#include "link.h"
#include <conio.h>

using namespace std;

#define PI 3.14159265358979323846

//Function template
template<class T> 
void PrintArray(T* ptr, int n)
{
	cout.setf(ios::fixed | ios::right | ios::showpoint);

	for(int i = 0; i < n; i++)
		cout << *(ptr+i) << endl;
	cout << endl;
}

int main()
{
	Circle C[10];
	Line L[10];
	Link Lk[10];


	for(int i = 0; i < 10; i++)
	{
		C[i] = Circle(10+i, 20+i, 10+2*i, 1,1,1);
		L[i] = Line(10+i, 20+i, 100+i,PI/(2+i),1,1,1);
		Lk[i] = Link(10+i, 20+i, 100+i,PI/(2+i),10+i,1,1,1);
	}

	cout << "Circles: " << endl << endl;
	// Template function
	PrintArray(C,10);
	cout << "Lines: " << endl << endl;
	// Template function
	PrintArray(L,1);
	cout << "Links: " << endl << endl;
	// Template function
	PrintArray(Lk,1);
	_getch();
	return 0;
}


