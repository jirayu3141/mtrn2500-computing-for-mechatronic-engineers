#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;

int main()
{
	int n;
	int* IntPtr;
	int a[2] = {1,2};

	cout << "Address of n in hex is \t\t" << hex << &n << endl;
	cout << "Address of a[0] in hex is \t" << hex << &a[0]  << endl;
	cout << "Address of a[1] in hex is \t" << hex << &a[1]  << endl;
	cout << "Address of the array in hex is \t" << hex << a << endl;

	_getch();

	IntPtr = a;
	cout << "Address of IntPtr in hex is \t" << hex << &IntPtr << endl;
	cout << "Pointer's value is \t\t" << hex << IntPtr << endl;
	cout << "Pointer + 1  is \t\t" << hex << (IntPtr+1) << endl;

	_getch();

	int *newIntPtr = new(int);
	*newIntPtr = 5;

	cout << "Address of newIntPtr in hex is \t" << hex << &newIntPtr << endl;
	cout << "newIntPtr's value is \t\t" << hex << newIntPtr << endl;
	cout << "newIntPtr + 1  is \t\t" << hex << (newIntPtr + 1) << endl;
	cout << "the value at the location of newIntPtr is\t" << dec << *newIntPtr << endl;

	delete newIntPtr;

	_getch();

	cout << "Address of newIntPtr in hex is \t" << hex << &newIntPtr << endl;
	cout << "newIntPtr's value is \t\t" << hex << newIntPtr << endl;
	cout << "the value at the location of newIntPtr is\t" << dec << *newIntPtr << endl;

	_getch();

	return 0;
}