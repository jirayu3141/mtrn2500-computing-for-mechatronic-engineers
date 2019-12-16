// Demonstrates the use of class templates
#include <iostream>
#include <iomanip>
#include <circle.h>
#include <line.h>
#include <link.h>
#include <Stack.h>
#include <conio.h>

using namespace std;

#define PI 3.14159265358979323846


int main()
{
	Circle C[10];
	Line L[10];
	Link Lk[10];

	// Template classes - generates code for the entire type-specific template class.
	Stack<int> IntStack(5);
	Stack<Link> LinkStack(6);



	for(int i = 0; i < 10; i++)
	{
		C[i] = Circle(i, 20+i, 10+2*i, 1,1,1);
		L[i] = Line(i, 20+i, 100+i,PI/(2+i),1,1,1);
		Lk[i] = Link(i, 20+i, 100+i,PI/(2+i),10+i,1,1,1);
	}

	for(int i = 0; i < LinkStack.GetSize(); i++)
	{
		LinkStack.Push(Lk[i]);
	}

	if(LinkStack.Full())
		cout << "The Link Stack is Full. " << endl;
	else
		cout << "The Link Stack is Not Full. "  << endl;

	for(int i = 0; i < IntStack.GetSize()-1; i++)
	{
		IntStack.Push(i);
	}

	if(IntStack.Full())
		cout << "The Int Stack is Full. " << endl;
	else
		cout << "The Int Stack is Not Full. "  << endl;

	cout << "Links: " << endl << endl;
	PrintArray(LinkStack.GetStackPointer(),LinkStack.GetSize());
	cout << "Ints: " << endl << endl;
	PrintArray(IntStack.GetStackPointer(),3);
	cout << "Circles: " << endl << endl;
	PrintArray(C,2);
	cout << "Lines: " << endl << endl;
	PrintArray(L,2);
	cout << "Links: " << endl << endl;
	PrintArray(Lk,5, 2);
	_getch();
	return 0;
}

