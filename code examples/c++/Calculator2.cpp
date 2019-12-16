#include <iostream>
#include <conio.h>
#include <cmath>

using namespace std;

int Add(int a, int b);
int Divide(int a, int b);
int Sub(int a, int b);
int Mult(int a, int b);

int main()
{
	int a = 4;
	int b = 5;
	int c = 0;

	int(*Function)(int, int);

	while (1)
	{
		//c = Divide(a, b);
		cout << "Press + to add, - to subtract, * to multiply, / to divide, q to quit" << endl;
		char key = _getch();

		switch (key)
		{
		case('+'):
			Function = Add;
			break;
		case('-'):
			Function = Sub;
			break;
		case('*'):
			Function = Mult;
			break;
		case('/'):
			Function = Divide;
			break;
		case('q'):
			return 0;
		default:
			cout << "Unknown key pressed, try again" << endl;
			continue;
		}

		c = Function(a, b);

		cout << "Value of C is " << c << endl;

	}
	return 0;
}

int Add(int a, int b)
{
	return a + b;
}
int Divide(int a, int b)
{
	return a / b;
}
int Sub(int a, int b)
{
	return a - b;
}
int Mult(int a, int b)
{
	return a * b;
}