#include "Person.h"
#include <iostream>

Person::Person()
{
	name = "BABY";
	age = 0;
	weight = 3;
}

Person::Person(double w, int a, string n)
{
	name = n;
	weight = w;
	age = a;
}

string Person::GetName()
{
	return name;
}

void Person::SetName(string s)
{
	name = s;
}

void Person::Eat()
{
	cout << "Nom nom nom" << endl;
}

void Person::Live()
{
	cout << "zzzz" << endl;
}