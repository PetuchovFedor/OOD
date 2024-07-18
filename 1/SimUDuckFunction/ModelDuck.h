#pragma once
#include "Duck.h"
#include "FlyNoWay.h"
#include "QuackBehavior.h"
#include "NotDance.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(NULL, QuackBehavior, NULL)
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};
