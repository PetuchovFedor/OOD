#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/CDisplay.h"
#include "../main/CStatsDisplay.h"
#include "../main/CWeatherData.h"
#include <sstream>

TEST_CASE("Check weather data output in different stream")
{
	GIVEN("2 weather data")
	{
		CWeatherData wdIn("in");
		CWeatherData wdOut("out");
		WHEN("Display")
		{
			std::stringstream ss1;
			std::stringstream ss2;
			CDisplay d1(wdIn, wdOut, ss1);
			CDisplay d2(wdIn, wdOut, ss2);
			wdIn.RegisterObserver(d1, 4);
			wdOut.RegisterObserver(d2, 4);
			wdIn.SetMeasurements(3, 0.7, 760);
			REQUIRE(ss1.str().find(wdIn.GetId()) != std::string::npos);
			REQUIRE(ss2.str().find(wdIn.GetId()) == std::string::npos);
			wdOut.SetMeasurements(3, 0.7, 760);
			REQUIRE(ss2.str().find(wdOut.GetId()) != std::string::npos);
			REQUIRE(ss1.str().find(wdOut.GetId()) == std::string::npos);
		}
		WHEN("StatsDisplay")
		{
			std::stringstream ss1;
			std::stringstream ss2;
			CStatsDisplay d1(wdIn, wdOut, ss1);
			CStatsDisplay d2(wdIn, wdOut, ss2);
			wdIn.RegisterObserver(d1, 4);
			wdOut.RegisterObserver(d2, 4);
			wdIn.SetMeasurements(3, 0.7, 760);
			REQUIRE(ss1.str().find(wdIn.GetId()) != std::string::npos);
			REQUIRE(ss2.str().find(wdIn.GetId()) == std::string::npos);
			wdOut.SetMeasurements(3, 0.7, 760);
			REQUIRE(ss2.str().find(wdOut.GetId()) != std::string::npos);
			REQUIRE(ss1.str().find(wdOut.GetId()) == std::string::npos);
		}
		WHEN("Display and StatsDispaly")
		{
			std::stringstream ss1;
			std::stringstream ss2;
			CStatsDisplay d1(wdIn, wdOut, ss1);
			CDisplay d2(wdIn, wdOut, ss2);
			wdIn.RegisterObserver(d1, 4);
			wdOut.RegisterObserver(d2, 4);
			wdIn.SetMeasurements(3, 0.7, 760);
			REQUIRE(ss1.str().find(wdIn.GetId()) != std::string::npos);
			REQUIRE(ss2.str().find(wdIn.GetId()) == std::string::npos);
			wdOut.SetMeasurements(3, 0.7, 760);
			REQUIRE(ss2.str().find(wdOut.GetId()) != std::string::npos);
			REQUIRE(ss1.str().find(wdOut.GetId()) == std::string::npos);
		}
	}
}

TEST_CASE("Check weather data output in another stream")
{
	GIVEN("2 weather data")
	{
		CWeatherData wdIn("in");
		CWeatherData wdOut("out");
		WHEN("Display")
		{
			std::stringstream ss;
			CDisplay d1(wdIn, wdOut, ss);
			CDisplay d2(wdIn, wdOut, ss);
			wdIn.RegisterObserver(d1, 4);
			wdOut.RegisterObserver(d2, 4);
			wdIn.SetMeasurements(3, 0.7, 760);
			wdOut.SetMeasurements(3, 0.7, 760);
			REQUIRE(ss.str().find(wdIn.GetId()) != std::string::npos);
			REQUIRE(ss.str().find(wdOut.GetId()) != std::string::npos);
		}
		WHEN("StatsDisplay")
		{
			std::stringstream ss;
			CStatsDisplay d1(wdIn, wdOut, ss);
			CStatsDisplay d2(wdIn, wdOut, ss);
			wdIn.RegisterObserver(d1, 4);
			wdOut.RegisterObserver(d2, 4);
			wdIn.SetMeasurements(3, 0.7, 760);
			wdOut.SetMeasurements(3, 0.7, 760);
			REQUIRE(ss.str().find(wdIn.GetId()) != std::string::npos);
			REQUIRE(ss.str().find(wdOut.GetId()) != std::string::npos);
		}
		WHEN("Display and StatsDispaly")
		{
			std::stringstream ss;
			CStatsDisplay d1(wdIn, wdOut, ss);
			CDisplay d2(wdIn, wdOut, ss);
			wdIn.RegisterObserver(d1, 4);
			wdOut.RegisterObserver(d2, 4);
			wdIn.SetMeasurements(3, 0.7, 760);
			wdOut.SetMeasurements(3, 0.7, 760);
			REQUIRE(ss.str().find(wdIn.GetId()) != std::string::npos);
			REQUIRE(ss.str().find(wdOut.GetId()) != std::string::npos);
		}
	}
}