#pragma once
#include "IState.h"
#include "IGumballMachine.h"
#include <iostream>


class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachine& gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void InsertQuarter() override
	{
		//std::cout << "You inserted a quarter\n";
		m_gumballMachine.AddQuarter();
		//m_gumballMachine.IncrementCountQuarter();
		//std::cout << "You can't insert another quarter\n";
	}
	void EjectQuarter() override
	{
		std::cout << "Quarter returned" << std::endl;
		//m_gumballMachine.ResetQuatersToZero();
		m_gumballMachine.RemoveQuarters();
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned...\n";
		m_gumballMachine.SetSoldState();
	}

	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}

	void Refill(unsigned numBalls) override
	{
		if (numBalls <= m_gumballMachine.GetBallCount())
		{
			throw std::logic_error("You want to fill the machine with fewer balls than it has");
		}
		m_gumballMachine.Refill(numBalls);
		std::cout << "The machine is filled with balls" << std::endl;
	}

	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}

private:
	IGumballMachine& m_gumballMachine;
};