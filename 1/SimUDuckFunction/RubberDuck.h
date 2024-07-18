#pragma once
#include "Duck.h"
#include "FlyNoWay.h"
#include "SqueakBehavior.h"
#include "NotDance.h"

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(NULL, SqueakBehavior, NULL)
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};