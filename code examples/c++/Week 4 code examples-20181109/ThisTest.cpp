#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;

class ThisTest {
private:
	int testData;
	static int testDataStatic;
public:
	ThisTest();
	~ThisTest();
	void setTestData(int value);
	void setTestDataStatic(int value);
	void setTestDataWithoutThis(int value);
	int getTestData();
	int getTestDataWithoutThis();
	int getTestDataStatic();
};

int ThisTest::testDataStatic; // This definition is needed for a static variable


ThisTest::ThisTest() {
	cout << "Address of this in constructor is \t" << hex << this << endl;
	cout << "\'this\' simply returns the address of an object" << endl;
};

ThisTest::~ThisTest() {};

void ThisTest::setTestData(int value) {
	this->testData = value;
	testDataStatic = value;
	cout << "Address of this in setTestData is \t" << hex << this << endl;
};
void ThisTest::setTestDataStatic(int value) {
	testDataStatic = value;
	cout << "Address of testDataStatic is \t\t" << hex << &testDataStatic << endl;
};
void ThisTest::setTestDataWithoutThis(int value) {
	testData = value;
	testDataStatic = value;
};
int ThisTest::getTestData() {
	return this->testData;
}
int ThisTest::getTestDataWithoutThis() {
	return testData;
}
int ThisTest::getTestDataStatic() {
	//return this->testDataStatic;
	// ^ Doesn't work, compiler gives an unresolved external symbol, as 'this'
	// can't be applied to static data.
	return testDataStatic;
}

int main() {
	// Difference between static and non-static member variables
	ThisTest lectureToday, lectureTomorrow;
	lectureToday.setTestData(16);
	lectureTomorrow.setTestData(17);
	lectureToday.setTestDataStatic(16);
	lectureTomorrow.setTestDataStatic(17);

	cout << "Value of lectureToday.getTestData(): " << dec << lectureToday.getTestData() << endl;
	cout << "Value of lectureTomorrow.getTestData(): " << dec << lectureTomorrow.getTestData() << endl;
	cout << "Value of lectureToday.getTestDataStatic(): " << dec << lectureToday.getTestDataStatic() << endl;
	cout << "Value of lectureTomorrow.getTestDataStatic(): " << dec << lectureTomorrow.getTestDataStatic() << endl;
	cout << "Note the difference in behaviour of static and non-static data and also the address of static data" << endl << endl;
	_getch();

	// Difference between stack and heap memory allocation
	ThisTest *pointerToNewThisTest = new(ThisTest);
	pointerToNewThisTest->setTestData(5);
	cout << "Address of pointerToNewThisTest is\t" << &pointerToNewThisTest << endl;
	cout << "Value of pointerToNewThisTest is\t" << pointerToNewThisTest << endl;
	cout << "Value of pointerToNewThisTest->getTestData()\t" << pointerToNewThisTest->getTestData() << endl;
	cout << "Value of pointerToNewThisTest->getTestDataStatic()\t" << pointerToNewThisTest->getTestDataStatic() << endl;
	cout << "Note the difference between addresses of items on the stack and on the heap" << endl << endl;
	_getch();

	// No difference between using 'this' and not in setters...
	lectureToday.setTestDataWithoutThis(1);
	lectureTomorrow.setTestData(2);
	pointerToNewThisTest->setTestDataWithoutThis(3);
	
	ThisTest *pointerToNewThisTest2 = new(ThisTest);
	pointerToNewThisTest2->setTestData(4);
	
	cout << "Value of lectureToday's TestData is\t" << lectureToday.getTestData() << endl;
	cout << "Value of lectureTomorrow's TestData is\t" << lectureTomorrow.getTestData() << endl;
	cout << "Value of pointerToNewThisTest's TestData is\t" << pointerToNewThisTest->getTestData() << endl;
	cout << "Value of pointerToNewThisTest2's TestData is\t" << pointerToNewThisTest2->getTestData() << endl;
	cout << "Value of lectureToday's TestData without this is\t" << lectureToday.getTestDataWithoutThis() << endl;
	cout << "Value of lectureTomorrow's TestData without this is\t" << lectureTomorrow.getTestDataWithoutThis() << endl;
	cout << "Value of pointerToNewThisTest's TestData without this is\t" << pointerToNewThisTest->getTestDataWithoutThis() << endl;
	cout << "Value of pointerToNewThisTest2's TestData without this is\t" << pointerToNewThisTest2->getTestDataWithoutThis() << endl;
	cout << "Hence, using \'this\' for non-static member data is fine." << endl;

	_getch();

};



