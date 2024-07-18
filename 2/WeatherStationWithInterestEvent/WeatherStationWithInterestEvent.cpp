#include "CWeatherData.h"
#include "CDisplay.h"
#include "CStatsDisplay.h"

int main()
{
	CWeatherData wdIn("in");
	CWeatherData wdOut("out");

	CDisplay display1(wdIn, wdOut, std::cout);
	CDisplay display2(wdIn, wdOut, std::cout);
	CDisplay display3(wdIn, wdOut, std::cout);
	CDisplay display4(wdIn, wdOut, std::cout);
	wdIn.RegisterObserver(display1, WeatherEvent::TEMPERATURE, 4);
	wdIn.RegisterObserver(display2, WeatherEvent::HUMIDITY, 6);
	wdIn.RegisterObserver(display3, WeatherEvent::PRESSURE, 3);
	wdOut.RegisterObserver(display1, WeatherEvent::TEMPERATURE, 10);
	wdOut.RegisterObserver(display2, WeatherEvent::HUMIDITY, 3);
	wdOut.RegisterObserver(display3, WeatherEvent::PRESSURE, 10);
	wdOut.RegisterObserver(display4, WeatherEvent::WIND, 5);

	CStatsDisplay statsDisplay1(wdIn, wdOut, std::cout);
	CStatsDisplay statsDisplay2(wdIn, wdOut, std::cout);

	wdIn.RegisterObserver(statsDisplay1, WeatherEvent::TEMPERATURE, 10);
	wdOut.RegisterObserver(statsDisplay1, WeatherEvent::PRESSURE, 10);
	wdIn.RegisterObserver(statsDisplay2, WeatherEvent::TEMPERATURE, 10);
	wdOut.RegisterObserver(statsDisplay2, WeatherEvent::PRESSURE, 10);
	wdIn.SetMeasurements(3, 0.7, 76);
	wdIn.SetMeasurements(4, 0.8, 761);
	wdOut.SetMeasurements(3, 0.7, 760, { 10, 180 });
	wdOut.SetMeasurements(4, 0.8, 761, { 5, 270 });
	return 0;
}