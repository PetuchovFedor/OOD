#pragma once
#include "Duck.h"
#include "FlyWithWings.h"
#include "QuackBehavior.h"
#include "DanceWaltz.h"
class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings, QuackBehavior, DanceWaltz)
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};