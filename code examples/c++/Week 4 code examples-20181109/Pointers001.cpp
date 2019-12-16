#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;

int main()
{
	double M[3][2] = {{1,2},{3,4},{5,6}};
	double (*DblRow)[2];

	cout << "Address of M in hex is \t\t\t" << hex << M << endl;

	cout << "Value of *M in hex is \t\t\t" << hex << *M  << endl;
	cout << "Value of *M+1 in hex is \t\t" << hex << *M+1  << endl;
	cout << "Value of *(*M+1) in dec is \t\t" << dec << *(*M+1)  << endl;

	DblRow = M;

	cout << "Value of DblRow pointer in hex is \t" << hex << DblRow  << endl;
	cout << "Value of DblRow+1 in hex is  \t\t" << hex << (DblRow+1) << endl;


	_getch();
	return 0;
}