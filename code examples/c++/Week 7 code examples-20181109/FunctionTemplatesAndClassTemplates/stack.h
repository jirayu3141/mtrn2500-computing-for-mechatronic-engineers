#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

#define MEMORY_ALLOCATION_FAILED -1
// Class template
template <class T>
class Stack
{
private:
	int  Size;
	T*   StackPointer;
	int  Top;
	int  ErrorCode;
public:
	Stack();
	Stack(int size);
	~Stack();
	bool Push(const T& obj);
	bool Pop(T& obj);
	bool Empty();
	bool Full();
	int  GetSize();
	int GetErrorCode();
	T*   GetStackPointer();
};

//Class member function templates - does not generate code

template <class T>
Stack<T>::Stack()
{
	Top = 0;
	StackPointer = NULL;
	Size = 10;
	StackPointer = new T[Size];
	if (StackPointer == NULL)
		ErrorCode = MEMORY_ALLOCATION_FAILED;
}

template <class T>
Stack<T>::Stack(int size)
{
	Top = 0;
	StackPointer = NULL;
	Size = size;
	StackPointer = new T[Size];
	if (StackPointer == NULL)
		ErrorCode = MEMORY_ALLOCATION_FAILED;
}

template <class T>
Stack<T>::~Stack()
{
	if(StackPointer != NULL)
		delete [] StackPointer;
}

template <class T>
bool Stack<T>::Push(const T& obj)
{
	if(!Full())
	{
		*(StackPointer + Top++) = obj;
		return true;
	}
	else
		return false;
}

template <class T>
bool Stack<T>::Pop(T& obj)
{
	if(!Empty())
	{
		obj = *(StackPointer + Top--);
		return true;
	}
	else
		return false;
}

template <class T>
bool Stack<T>::Empty()
{
	if(Top < 0)
		return true;
	else
		return false;
}

template <class T>
bool Stack<T>::Full()
{
	if(Top >= Size)
		return true;
	else
		return false;
}

template <class T>
int  Stack<T>::GetSize()
{
	return Size;
}

template <class T>
T*  Stack<T>::GetStackPointer()
{
	return StackPointer;
}

template <class T>
int  Stack<T>::GetErrorCode()
{
	return ErrorCode;
}


// Function Templates
template<class T>
void PrintArray(T* ptr, int n)
{
	for(int i = 0; i < n; i++)
		cout << setw(10) << setprecision(3) << fixed  << *(ptr+i) << endl;
	cout << endl;
}

template<class T>
void PrintArray(T* ptr, int start, int end)
{
	for(int i = start; i < end; i++)
		cout << setw(10) << setprecision(3) << fixed  << *(ptr+i) << endl;
	cout << endl;
}

#endif // STACK_H