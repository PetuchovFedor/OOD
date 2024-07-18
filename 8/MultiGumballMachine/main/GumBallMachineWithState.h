#pragma once
#include "CSoldState.h"
#include "CSoldOutState.h"
#include "CNoQuarterState.h"
#include "CHasQuarterState.h"
#include <format>

namespace with_state
{
	class CGumballMachine : private IGumballMachine
	{
	public:
		CGumballMachine(unsigned numBalls)
			: m_soldState(*this)
			, m_soldOutState(*this)
			, m_noQuarterState(*this)
			, m_hasQuarterState(*this)
			, m_state(&m_soldOutState)
			, m_countBalls(numBalls)			
		{
			if (m_countBalls > 0)
			{
				m_state = &m_noQuarterState;
			}
		}
		void EjectQuarter()
		{
			m_state->EjectQuarter();
		}

		void InsertQuarter()
		{
			m_state->InsertQuarter();
		}

		void TurnCrank()
		{
			m_state->TurnCrank();
			m_state->Dispense();
		}
		std::string ToString()const
		{
			//const std::string str = m_count != 1 ? "s" : " ";
			auto fmt = std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {0} gumball{1}, {2} quarter{3}
Machine is {4}
)", m_countBalls, m_countBalls != 1 ? "s" : "", 
	m_countQuarters, m_countQuarters != 1 ? "s" : "", m_state->ToString());
			return fmt;
		}
	private:
		
		unsigned GetBallCount() const override
		{
			return m_countBalls;
		}

		virtual void ReleaseBall() override
		{
			if (m_countBalls != 0)
			{
				std::cout << "A gumball comes rolling out the slot..." << std::endl;
				--m_countBalls;
				--m_countQuarters;
			}
		}

		void RemoveQuarters() override
		{
			m_countQuarters = 0;
		}

		void AddQuarter() override
		{
			if (m_countQuarters < 5)
			{
				std::cout << "You inserted a quarter" << std::endl;
				m_countQuarters++;
			}
			else
				std::cout << "you have already deposited the maximum number of coins" << std::endl;
		}

		unsigned GetQuartersCount() const override
		{
			return m_countQuarters;
		}

		void SetSoldOutState() override
		{
			m_state = &m_soldOutState;
		}

		void SetNoQuarterState() override
		{
			m_state = &m_noQuarterState;
		}

		void SetSoldState() override
		{
			m_state = &m_soldState;
		}

		void SetHasQuarterState() override
		{
			m_state = &m_hasQuarterState;
		}
	private:
		unsigned m_countBalls = 0;
		unsigned m_countQuarters = 0;
		CSoldState m_soldState;
		CSoldOutState m_soldOutState;
		CNoQuarterState m_noQuarterState;
		CHasQuarterState m_hasQuarterState;
		IState* m_state;
	};

}
