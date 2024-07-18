#pragma once
#include "Duck.h"
#include "FlyWithWings.h"
#include "QuackBehavior.h"
#include "DanceMinuet.h"

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings, QuackBehavior, DanceMinuet)
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};
