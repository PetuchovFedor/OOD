#pragma once
#include "IState.h"
#include "IGumballMachine.h"
#include <iostream>

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IGumballMachine& gumballMachine)
		: m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		//std::cout << "You inserted a quarter\n";
		m_gumballMachine.AddQuarter();
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter" << std::endl;
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter" << std::endl;
	}
	void Dispense() override
	{
		std::cout << "You need to pay first" << std::endl;
	}

	void Refill(unsigned numBalls) override
	{
		if (numBalls < m_gumballMachine.GetBallCount())
		{
			throw std::logic_error("You want to fill the machine with fewer balls than it has");			
		}
		m_gumballMachine.Refill(numBalls);
		std::cout << "The machine is filled with balss" << std::endl;
	}

	std::string ToString() const override
	{
		return "waiting for quarter";
	}
private:
	IGumballMachine& m_gumballMachine;
};