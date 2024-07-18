#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/CGumballMachine.h"

std::string StateToString(unsigned count, const std::string& state)
{
	return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {0} gumball{1}
Machine is {2}
)", count, count != 1 ? "s" : "", state);
}

TEST_CASE("CGumballMachine methods")
{
	GIVEN("Gumball machine with 0 balls")
	{
		CGumballMachine m(0);
		WHEN("with any method, the state will not change because there are no balls")
		{
			THEN("InsertQuarter")
			{
				m.InsertQuarter();
				REQUIRE(StateToString(0, "sold out") == m.ToString());
			}
			THEN("EjectQuarter")
			{
				m.EjectQuarter();
				REQUIRE(StateToString(0, "sold out") == m.ToString());
			}
			THEN("TurnCrank")
			{
				m.TurnCrank();
				REQUIRE(StateToString(0, "sold out") == m.ToString());
			}
		}
	}

	GIVEN("Gumball machine with 5 balls")
	{
		CGumballMachine m(5);
		WHEN("Initial state is no quarter")
		{
			REQUIRE(StateToString(5, "waiting for quarter") == m.ToString());
		}
		WHEN("Insert quarter")
		{
			m.InsertQuarter();
			THEN("State is has quarter")
			{
				REQUIRE(StateToString(5, "waiting for turn of crank") == m.ToString());
			}
			WHEN("TurnCrank")
			{
				m.TurnCrank();
				THEN("We get gumball and state is no quarter")
				{
					REQUIRE(StateToString(4, "waiting for quarter") == m.ToString());
				}
				WHEN("try EjectQuarter")
				{
					m.EjectQuarter();
					REQUIRE(StateToString(4, "waiting for quarter") == m.ToString());
					WHEN("buy all gumballs")
					{
						m.InsertQuarter();
						m.TurnCrank();
						m.InsertQuarter();
						m.TurnCrank();
						m.InsertQuarter();
						m.TurnCrank();
						m.InsertQuarter();
						m.TurnCrank();
						THEN("State is sold out")
						{
							REQUIRE(StateToString(0, "sold out") == m.ToString());
						}
					}
				}
			}
			WHEN("Insert quarter again")
			{
				m.InsertQuarter();
				THEN("the state has not changed")
				{
					REQUIRE(StateToString(5, "waiting for turn of crank") == m.ToString());
				}
			}
			WHEN("EjectQuarter")
			{
				m.EjectQuarter();
				THEN("State is no quarter")
				{
					REQUIRE(StateToString(5, "waiting for quarter") == m.ToString());
				}
			}
		}
		WHEN("EjectQuarter")
		{
			m.EjectQuarter();
			THEN("the state has not changed")
			{
				REQUIRE(StateToString(5, "waiting for quarter") == m.ToString());
			}
		}
		WHEN("TurnCrank")
		{
			m.TurnCrank();
			THEN("the state has not changed")
			{
				REQUIRE(StateToString(5, "waiting for quarter") == m.ToString());
			}
		}
	}
}

//Протестировать нужно классы состояния
//TEST_CASE("Check transitions between states")
//{
//	WHEN("balls = 0")
//	{
//		MockGumballMachine mock(0);
//		THEN("State is sold out");
//		{
//			auto states = mock.GetTransitionsBetweenStates();
//			REQUIRE(states[0] ==
//				StateOfGumballMachine::SoldOut);
//		}
//	}
//	GIVEN("machine with 4 balss")
//	{
//		MockGumballMachine mock(4);
//		THEN("States is sold out and no quarter")
//		{
//			auto states = mock.GetTransitionsBetweenStates();
//			REQUIRE(states[0] == StateOfGumballMachine::SoldOut);
//			REQUIRE(states[1] == StateOfGumballMachine::NoQuarter);
//		}
//		WHEN("Try EjectQuarter, TurnCrank")
//		{
//			mock.EjectQuarter();
//			mock.TurnCrank();
//			THEN("states have not changed")
//			{
//				auto states = mock.GetTransitionsBetweenStates();
//				REQUIRE(states[0] == StateOfGumballMachine::SoldOut);
//				REQUIRE(states[1] == StateOfGumballMachine::NoQuarter);
//			}
//		}
//		WHEN("InsertQuarter")
//		{
//			mock.InsertQuarter();
//			THEN("transition to has quarter")
//			{
//				auto states = mock.GetTransitionsBetweenStates();
//				REQUIRE(states[2] == StateOfGumballMachine::HasQuarter);
//			}
//			WHEN("EjectQuarter")
//			{
//				mock.EjectQuarter();
//				THEN("transition to no quarter")
//				{
//					auto states = mock.GetTransitionsBetweenStates();
//					REQUIRE(states[3] == StateOfGumballMachine::NoQuarter);
//				}
//			}
//			WHEN("TurnCrank")
//			{
//				mock.TurnCrank();
//				THEN("transition to sold and then to no quarter")
//				{
//					auto states = mock.GetTransitionsBetweenStates();
//					REQUIRE(states[3] == StateOfGumballMachine::Sold);
//					REQUIRE(states[4] == StateOfGumballMachine::NoQuarter);
//				}
//				WHEN("InsertQuarter")
//				{
//					mock.InsertQuarter();
//					THEN("transition to has quarter")
//					{
//						auto states = mock.GetTransitionsBetweenStates();
//						REQUIRE(states[2] == StateOfGumballMachine::HasQuarter);
//					}
//				}
//			}
//		}
//		WHEN("Take all balls")
//		{
//			mock.InsertQuarter();
//			mock.TurnCrank();
//			mock.InsertQuarter();
//			mock.TurnCrank();
//			mock.InsertQuarter();
//			mock.TurnCrank();
//			mock.InsertQuarter();
//			mock.TurnCrank();
//			THEN("transition to sold out")
//			{
//				auto states = mock.GetTransitionsBetweenStates();
//				REQUIRE(states[states.size() - 1] == StateOfGumballMachine::SoldOut);
//			}
//		}
//	}
//	
//}