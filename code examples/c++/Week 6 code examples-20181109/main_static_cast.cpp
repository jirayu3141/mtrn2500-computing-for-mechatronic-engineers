// class type-casting
// Adapted from http://www.cplusplus.com/doc/tutorial/typecasting/
#include <iostream>
#include <conio.h>
#include <typeinfo>
using namespace std; 

class Dummy {
	double i, j;
};

class Addition {
	int x, y;
public:
	Addition(int a, int b) { x = a; y = b; }
	int result() { return x + y; }
};

int main() {
	Dummy d;
	Addition * padd;
	padd = (Addition*)&d;
	
	// Display the name of the type
	cout << typeid(d).name() << endl;

	// The below is not guaranteed to work as dummy and addition are not compatible types
	cout << padd->result();
	
	_getch();

	return 0;
}
