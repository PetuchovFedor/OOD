#pragma once
#include "IDanceBehavior.h"
#include <iostream>

class NotDance : public IDanceBehavior
{
public:
	void Dance() override
	{
	}
};