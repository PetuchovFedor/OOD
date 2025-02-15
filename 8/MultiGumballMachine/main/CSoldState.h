#pragma once
#include "IState.h"
#include "IGumballMachine.h"
#include <iostream>

namespace with_state
{
	class CSoldState : public IState
	{
	public:
		CSoldState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}
		void InsertQuarter() override
		{
			m_gumballMachine.AddQuarter();
			//std::cout << "Please wait, we're already giving you a gumball\n";
		}
		void EjectQuarter() override
		{
			std::cout << "Sorry you already turned the crank" << std::endl;
		}
		void TurnCrank() override
		{
			std::cout << "Turning twice doesn't get you another gumball" << std::endl;
		}
		void Dispense() override
		{
			m_gumballMachine.ReleaseBall();
			if (m_gumballMachine.GetBallCount() == 0)
			{
				std::cout << "Oops, out of gumballs" << std::endl;
				m_gumballMachine.SetSoldOutState();
			}
			else if (m_gumballMachine.GetQuartersCount() == 0)
			{
				m_gumballMachine.SetNoQuarterState();
			}
			else
			{
				m_gumballMachine.SetHasQuarterState();
			}
		}
		std::string ToString() const override
		{
			return "delivering a gumball";
		}
	private:
		IGumballMachine& m_gumballMachine;
	};
}