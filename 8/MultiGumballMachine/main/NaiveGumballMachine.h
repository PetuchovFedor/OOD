#pragma once
#include <iostream>
#include <format>

namespace naive
{
	class CGumballMachine
	{
	public:
		enum class State
		{
			SoldOut,		// Жвачка закончилась
			NoQuarter,		// Нет монетки
			HasQuarter,		// Есть монетка
			Sold,			// Монетка выдана
		};

		CGumballMachine(unsigned count)
			: m_countBalls(count)
			, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
		{
		}

		void InsertQuarter()
		{			
			switch (m_state)
			{
			case State::SoldOut:
				std::cout << "You can't insert a quarter, the machine is sold out" << std::endl;
				break;
			case State::NoQuarter:
				AddQuarter();
				m_state = State::HasQuarter;
				break;
			case State::HasQuarter:
				AddQuarter();
				break;
			case State::Sold:
				std::cout << "We're giving you a gumball" << std::endl;
				AddQuarter();
				break;
			}
		}

		void EjectQuarter()
		{
			//using namespace std;
			switch (m_state)
			{
			case State::HasQuarter:
				std::cout << "Quarters returned" << std::endl;
				m_countQuarters = 0;
				m_state = State::NoQuarter;
				break;
			case State::NoQuarter:
				std::cout << "You haven't inserted a quarter" << std::endl;
				break;
			case State::Sold:
				std::cout << "Sorry you already turned the crank" << std::endl;
				break;
			case State::SoldOut:
				m_countQuarters = 0;
				std::cout << "Quarters returned" << std::endl;
				break;
			}
		}

		void TurnCrank()
		{
			//using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				std::cout << "You turned but there's no gumballs" << std::endl;
				break;
			case State::NoQuarter:
				std::cout << "You turned but there's no quarter" << std::endl;
				break;
			case State::HasQuarter:
				std::cout << "You turned..." << std::endl;
				m_state = State::Sold;
				Dispense();
				break;
			case State::Sold:
				std::cout << "You turned..." << std::endl;
				Dispense();
				break;
			}
		}

		void Refill(unsigned numBalls)
		{
			m_countBalls = numBalls;
			m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
		}

		std::string ToString()const
		{
			std::string state =
				(m_state == State::SoldOut) ? "sold out" :
				(m_state == State::NoQuarter) ? "waiting for quarter" :
				(m_state == State::HasQuarter) ? "waiting for turn of crank"
				: "delivering a gumball";
			auto fmt = std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {0} gumball{1}, {2} quarter{3}
Machine is {4}
)", m_countBalls, m_countBalls != 1 ? "s" : "", m_countQuarters,
	m_countQuarters != 1 ? "s" : "", state);
			return fmt;
		}

	private:
		void AddQuarter()
		{
			if (m_countQuarters < 5)
			{
				std::cout << "You inserted a quarter" << std::endl;
				m_countQuarters++;
			}
			else
				std::cout << "You have already deposited the maximum number of coins" << std::endl;
		}
		void Dispense()
		{
			//using namespace std;
			switch (m_state)
			{
			case State::Sold:
				std::cout << "A gumball comes rolling out the slot" << std::endl;
				--m_countBalls;
				--m_countQuarters;
				if (m_countBalls == 0)
				{
					std::cout << "Oops, out of gumballs" << std::endl;
					m_state = State::SoldOut;
				}
				else
				{
					if (m_countQuarters == 0)
						m_state = State::NoQuarter;
					else
						m_state = State::HasQuarter;
				}
				break;
			case State::NoQuarter:
				std::cout << "You need to pay first" << std::endl;
				break;
			case State::SoldOut:
			case State::HasQuarter:
				std::cout << "No gumball dispensed" << std::endl;
				break;
			}
		}

		unsigned m_countBalls, m_countQuarters = 0;
		State m_state = State::SoldOut;
	};
}