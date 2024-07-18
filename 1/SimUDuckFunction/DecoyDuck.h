#pragma once
#include "Duck.h"
#include "FlyNoWay.h"
#include "MuteQuackBehavior.h"
#include "NotDance.h"
#include <iostream>

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(NULL, MuteQuackBehavior, NULL)
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}
};