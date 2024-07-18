#include <iostream>
#include "CWeatherData.h"
#include "CDisplay.h"
#include "CStatsDisplay.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, 4);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 6);
	wd.SetMeasurements(3, 0.7, 760, {30, 90});
	wd.SetMeasurements(4, 0.8, 761, {15, 0});

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761, {10, 180});
	wd.SetMeasurements(-10, 0.8, 761, {20, 270});
	return 0;
}
