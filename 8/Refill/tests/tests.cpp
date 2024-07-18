#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/CGumballMachine.h"

std::string StateToString(const std::string& state, unsigned countBalls,
	unsigned countQuarters)
{
	return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {0} gumball{1}, {2} quarter{3}
Machine is {4}
)", countBalls, countBalls != 1 ? "s" : "", countQuarters,
countQuarters != 1 ? "s" : "", state);
}

TEST_CASE("With state realisation")
{
	GIVEN("Gumball machine with 0 balls")
	{
		CGumballMachine m(0);
		WHEN("with any method, the state will not change because there are no balls")
		{
			THEN("InsertQuarter")
			{
				m.InsertQuarter();
				REQUIRE(StateToString("sold out", 0, 0) == m.ToString());
			}
			THEN("EjectQuarter")
			{
				m.EjectQuarter();
				REQUIRE(StateToString("sold out", 0, 0) == m.ToString());
			}
			THEN("TurnCrank")
			{
				m.TurnCrank();
				REQUIRE(StateToString("sold out", 0, 0) == m.ToString());
			}
		}
		WHEN("Refill")
		{
			m.ReFill(5);
			THEN("State is no quater")
			{
				REQUIRE(StateToString("waiting for quarter", 5, 0) == m.ToString());
			}
		}
	}
	GIVEN("Gumball machine with 5 balls")
	{
		CGumballMachine m(5);
		WHEN("Initial state is no quarter")
		{
			REQUIRE(StateToString("waiting for quarter", 5, 0) == m.ToString());
			WHEN("Refill")
			{
				m.ReFill(10);
				REQUIRE(StateToString("waiting for quarter", 10, 0) == m.ToString());
			}
		}
		WHEN("Insert quarter one time")
		{
			m.InsertQuarter();
			THEN("State is has quarter")
			{
				REQUIRE(StateToString("waiting for turn of crank", 5, 1) == m.ToString());
				WHEN("Refill")
				{
					m.ReFill(10);
					REQUIRE(StateToString("waiting for turn of crank", 10, 1) == m.ToString());
				}
			}
			WHEN("TurnCrank")
			{
				m.TurnCrank();
				THEN("We get gumball and state is no quarter")
				{
					REQUIRE(StateToString("waiting for quarter", 4, 0) == m.ToString());
				}
				WHEN("try EjectQuarter")
				{
					m.EjectQuarter();
					REQUIRE(StateToString("waiting for quarter", 4, 0) == m.ToString());

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
							REQUIRE(StateToString("sold out", 0, 0) == m.ToString());
						}
					}
				}
			}
		}
		WHEN("Insert quarte several times")
		{
			m.InsertQuarter();
			m.InsertQuarter();
			m.InsertQuarter();
			m.InsertQuarter();
			m.InsertQuarter();
			THEN("Machine state is has quarter and it has 5 coins")
			{
				REQUIRE(StateToString("waiting for turn of crank", 5, 5) == m.ToString());
			}
			WHEN("Trying again")
			{
				m.InsertQuarter();
				THEN("State is not change")
				{
					REQUIRE(StateToString("waiting for turn of crank", 5, 5) == m.ToString());
				}
			}
			WHEN("EjectQuarter when gumball there are")
			{
				m.EjectQuarter();
				THEN("State is no quarter")
				{
					REQUIRE(StateToString("waiting for quarter", 5, 0) == m.ToString());
				}
			}
			WHEN("TurnCrank one time")
			{
				m.TurnCrank();
				THEN("We get gumball and state is has quarter")
				{
					REQUIRE(StateToString("waiting for turn of crank", 4, 4) == m.ToString());
				}
			}
			WHEN("TurnCrank several times")
			{
				m.TurnCrank();
				m.TurnCrank();
				m.TurnCrank();
				THEN("We get gumballs and state is has quarter")
				{
					REQUIRE(StateToString("waiting for turn of crank", 2, 2) == m.ToString());
				}
			}
			WHEN("Eject quarter when gumballs is over")
			{
				m.TurnCrank();
				m.TurnCrank();
				m.TurnCrank();
				m.TurnCrank();
				m.InsertQuarter();
				m.InsertQuarter();
				m.InsertQuarter();
				m.TurnCrank();
				m.EjectQuarter();
				REQUIRE(StateToString("sold out", 0, 0) == m.ToString());
			}
		}
	}
}