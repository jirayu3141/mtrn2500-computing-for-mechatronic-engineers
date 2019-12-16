#pragma once

#include "CEO.h"
#include <conio.h>

class Batman : public CEO
{
	int speed;
	double crime_fighting_efficiency;
public:
	Batman();
	void Eat();
};
