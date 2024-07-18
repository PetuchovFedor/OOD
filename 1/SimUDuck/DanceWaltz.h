#pragma once
#include "IDanceBehavior.h"
#include <iostream>

class DanceWaltz : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm waltzing!!" << std::endl;
	}
};