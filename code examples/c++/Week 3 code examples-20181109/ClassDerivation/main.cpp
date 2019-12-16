#include <iostream>
#include <conio.h>
#include "Point.h"
#include "Circle.h"

using namespace std;

int main()
{
	Point Centre(10.5, 9.76);
	
	cout << "[x,y] = [" << Centre.GetX() << ", " << Centre.GetY() << "]" << endl;
	Circle C1(Centre, 10.0);

	cout << "Circle C1 parameters [x, y, r] are [" << C1.GetX() << ", " << C1.GetY() << ", " << C1.GetRadius() << "]" << endl;
	
	Circle C2(1, 2, 3);

	cout << "Circle C2 parameters [x, y, r] are [" << C2.GetX() << ", " << C2.GetY() << ", " << C2.GetRadius() << "]" << endl;
	
	Circle C3();
	cout << "Circle C3 parameters [x, y, r] are [" << C3.GetX() << ", " << C3.GetY() << ", " << C3.GetRadius() << "]" << endl;

	_getch();
	return 0;

}

