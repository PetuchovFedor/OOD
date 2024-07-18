#pragma once
#include "IState.h"
#include "IGumballMachine.h"
#include <iostream>

namespace with_state
{
	class CSoldOutState : public IState
	{
	public:
		CSoldOutState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			//m_gumballMachine.IncrementCountQuarter();
			std::cout << "You can't insert a quarter, the machine is sold out\n";
		}
		void EjectQuarter() override
		{
			if (m_gumballMachine.GetQuartersCount() == 0)
			{
				std::cout << "You can't eject, you haven't inserted a quarter yet" 
					<< std::endl;
			}
			else
			{
				m_gumballMachine.RemoveQuarters();
				std::cout << "Quarters returned" << std::endl;
			}
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no gumballs" << std::endl;
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed" << std::endl;
		}

		std::string ToString() const override
		{
			return "sold out";
		}

	private:
		IGumballMachine& m_gumballMachine;
	};
}