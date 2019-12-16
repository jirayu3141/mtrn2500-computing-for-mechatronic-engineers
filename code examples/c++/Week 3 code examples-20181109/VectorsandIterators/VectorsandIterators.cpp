#include <iostream>
#include <vector>
#include <math.h>
#include <conio.h>
#include "Point.h"
using namespace std;

int main()
{
	vector<int> intList;

	int i = 10;

	intList.push_back(i);
	intList.push_back(int(5));
	intList.push_back(int(9000));
	intList.push_back(int(-56));

	// Iterate through the list
	for (vector<int>::iterator it = intList.begin(); it != intList.end(); it++) {
		cout << *it << endl;
	}

	vector<Point> pointList;
	Point p(-1, 3);
	pointList.push_back(p);
	pointList.push_back(Point(3, 4));

	//pointList.pop_back();

	// Iterate through the list
	for (vector<Point>::iterator pit = pointList.begin(); pit != pointList.end(); pit++) {
		cout << "Point values: [" << pit->GetX() << ", " << pit->GetY() << "]" << endl;
	}

	// Iterate backwards through the list
	for (vector<Point>::reverse_iterator pit = pointList.rbegin(); pit != pointList.rend(); pit++) {
		cout << "Point values: [" << pit->GetX() << ", " << pit->GetY() << "]" << endl;
	}


	_getch();

	// Editing iterator is possible, hence cbegin and cend are available.

	return 0;
}