// Demonstrates function templates and overloaded function templates

#include <iostream>
#include <iomanip>
#include <circle.h>
#include <line.h>
#include <link.h>
#include <conio.h>

using namespace std;

#define PI 3.14159265358979323846

//Function template
template<class T>
void PrintArray(T* ptr, int n)
{
	for(int i = 0; i < n; i++)
		cout << setw(10) << setprecision(3) << fixed  << *(ptr+i) << endl;
	cout << endl;
}

//Overloaded function template.
template<class T>
void PrintArray(T* ptr, int start, int end)
{
	for(int i = start; i <= end; i++)
		cout << setw(10) << setprecision(3) << fixed  << *(ptr+i) << endl;
	cout << endl;
}

int main()
{
	Circle C[10];
	Line L[10];
	Link Lk[10];
	int Ints[10];


	for(int i = 0; i < 10; i++)
	{
		C[i] = Circle(i, 20+i, 10+2*i, 1,1,1);
		L[i] = Line(i, 20+i, 100+i,PI/(2+i),1,1,1);
		Lk[i] = Link(i, 20+i, 100+i,PI/(2+i),10+i,1,1,1);
		Ints[i] = int(i);
	}

	cout << "Ints: " << endl << endl;
	// Template function
	PrintArray(Ints,2);
	cout << "Circles: " << endl << endl;
	// Template function
	PrintArray(C,2);
	cout << "Lines: " << endl << endl;
	// Template function
	PrintArray(L,2);

	_getch();

	cout << "Links: " << endl << endl;
	// Overloaded template function
	PrintArray(Lk,5,9);

	_getch();

	return 0;
}

