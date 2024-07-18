#pragma once
#include "IDanceBehavior.h"
#include <iostream>

class DanceMinuet : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dancing a minuet!!" << std::endl;
	}
};
