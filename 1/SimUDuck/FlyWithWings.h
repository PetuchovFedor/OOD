#pragma once
#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		m_countOfFlights++;
		std::cout << "I'm flying with wings!!" << std::endl;
	}

	void ShowCountOfFlights() override
	{
		std::cout << "I'm have " << m_countOfFlights << " flights" << std::endl;
	}
private:
	int m_countOfFlights = 0;
};
