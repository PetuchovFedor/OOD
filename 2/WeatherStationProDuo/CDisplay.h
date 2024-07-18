#pragma once
#include "SWeatherInfo.h"
#include "Observer.h"
#include <iostream>

class CDisplay : public IObserver<SWeatherInfo>
{
public:
	CDisplay(IObservable<SWeatherInfo>& in, IObservable<SWeatherInfo>& out, std::ostream& output)
		: m_inObservable(&in)
		, m_outObservable(&out)
		, m_output(output)
	{}
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		m_output << data.sensorId << ':' << std::endl;
		m_output << "Current Temp " << data.temperature << std::endl;
		m_output << "Current Hum " << data.humidity << std::endl;
		m_output << "Current Pressure " << data.pressure << std::endl;
		if (&observable == m_outObservable)
		{
			m_output << "Current wind direction " << data.wind.direction << " degrees" << std::endl;
			m_output << "Current wind speed " << data.wind.speed << std::endl;
		}
		m_output << "----------------" << std::endl;
	}
	IObservable<SWeatherInfo>* m_inObservable;
	IObservable<SWeatherInfo>* m_outObservable;
	std::ostream& m_output;
};