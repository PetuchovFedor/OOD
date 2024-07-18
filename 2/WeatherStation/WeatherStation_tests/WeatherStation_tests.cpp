#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "DestructObserver.h"
#include "../main/CWeatherData.h"
#include "../main/CDisplay.h"
#include "../main/CStatsDisplay.h"
#include <sstream>
#include "PriorityTestClasses.h"

TEST_CASE("Destruct observer, when Update()")
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, 4);
	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 6);
	std::stringstream ss;
	DestructObserver tmp(wd, ss);
	wd.RegisterObserver(tmp, 5);
	wd.SetMeasurements(3, 0.7, 760);
	REQUIRE(ss.str() == "Observer was deleted\n");
	wd.SetMeasurements(3, 0.7, 760);
	REQUIRE(ss.str() == "Observer was deleted\n");
}

TEST_CASE("Check priority")
{
	ObservableTest observable;
	std::stringstream ss;
	ObserverTest obserber1(ss, 5);
	ObserverTest obserber2(ss, 4);
	ObserverTest obserber3(ss, 3);
	ObserverTest obserber4(ss, 2);
	ObserverTest obserber5(ss, 1);
	observable.RegisterObserver(obserber3, obserber3.GetPriority());
	observable.RegisterObserver(obserber2, obserber2.GetPriority());
	observable.RegisterObserver(obserber1, obserber1.GetPriority());
	observable.RegisterObserver(obserber5, obserber5.GetPriority());
	observable.RegisterObserver(obserber4, obserber4.GetPriority());
	observable.Notify();
	REQUIRE(ss.str() == "54321");
}

