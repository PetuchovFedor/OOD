#pragma once
#include "SWeatherInfo.h"
#include "Observer.h"
#include <iostream>

class CDisplay : public IObserver<SWeatherInfo, WeatherEvent>
{
public:
	CDisplay(IObservable<SWeatherInfo, WeatherEvent>& in, IObservable<SWeatherInfo, WeatherEvent>& out, 
		std::ostream& output)
		: m_inObservable(&in)
		, m_outObservable(&out)
		, m_output(output)
	{}
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo, WeatherEvent>& observable,
		WeatherEvent event) override
	{
		m_output << data.sensorId << ':' << std::endl;
		if (event == WeatherEvent::TEMPERATURE)
		{
			m_output << "Current Temp " << data.temperature << std::endl;
		}
		else if (event == WeatherEvent::HUMIDITY)
		{
			m_output << "Current Hum " << data.humidity << std::endl;
		}
		else if (event == WeatherEvent::PRESSURE)
		{
			m_output << "Current Pressure " << data.pressure << std::endl;
		}
		else if (event == WeatherEvent::WIND)
		{
			m_output << "Current wind direction " << data.wind.direction << " degrees" << std::endl;
			m_output << "Current wind speed " << data.wind.speed << std::endl;
		}
		m_output << "----------------" << std::endl;
	}
	IObservable<SWeatherInfo, WeatherEvent>* m_inObservable;
	IObservable<SWeatherInfo, WeatherEvent>* m_outObservable;
	std::ostream& m_output;
};