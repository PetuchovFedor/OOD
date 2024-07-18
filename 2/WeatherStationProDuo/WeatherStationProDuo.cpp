#include "CWeatherData.h"
#include "CDisplay.h"
#include "CStatsDisplay.h"

int main()
{
	CWeatherData wdIn("in");
	CWeatherData wdOut("out");

	CDisplay display(wdIn, wdOut, std::cout);
	wdIn.RegisterObserver(display, 4);
	wdOut.RegisterObserver(display, 4);

	CStatsDisplay statsDisplay(wdIn, wdOut, std::cout);
	wdIn.RegisterObserver(statsDisplay, 6);
	wdOut.RegisterObserver(statsDisplay, 6);
	wdIn.SetMeasurements(3, 0.7, 76);
	wdIn.SetMeasurements(4, 0.8, 761);
	wdOut.SetMeasurements(3, 0.7, 760, {10, 180});
	wdOut.SetMeasurements(4, 0.8, 761, {5, 270});
	return 0;
}