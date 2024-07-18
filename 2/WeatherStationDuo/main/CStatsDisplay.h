#pragma once
#include "SWeatherInfo.h"
#include "Observer.h"
#include "CStatisticData.h"

struct StatsDataGroup
{
	StatsDataGroup()
		: temperature{}
		, humidity{}
		, pressure{}
	{}
	CStatisticData temperature;
	CStatisticData humidity;
	CStatisticData pressure;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(IObservable<SWeatherInfo>& in, IObservable<SWeatherInfo>& out, 
		std::ostream& output)
		: m_output(output)
		, m_inObservable(&in)
		, m_outObservable(&out)
	{
		m_indicators.insert({ &in, StatsDataGroup() });
		m_indicators.insert({ &out, StatsDataGroup() });
	}
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		if (m_indicators.find(&observable) != m_indicators.end())
		{
			m_indicators.at(&observable).temperature.Update(data.temperature);
			m_indicators.at(&observable).humidity.Update(data.humidity);
			m_indicators.at(&observable).pressure.Update(data.pressure);
		}
		m_output << data.sensorId << ':' << std::endl;
		PrintStats(observable);
	}

	void PrintStats(IObservable<SWeatherInfo>& observable)
	{
		m_output << "Temp ";
		PrintStatistic(m_indicators.at(&observable).temperature);
		m_output << "Hum ";
		PrintStatistic(m_indicators.at(&observable).humidity);
		m_output << "Press ";
		PrintStatistic(m_indicators.at(&observable).pressure);
		m_output << "----------------" << std::endl;
	}

	void PrintStatistic(const CStatisticData& data)
	{
		m_output << "min: " << data.GetMin() << ", max: " << data.GetMax()
			<< ", average: " << data.GetAverage() << std::endl;
	}

	std::map<IObservable<SWeatherInfo>*, StatsDataGroup> m_indicators;
	IObservable<SWeatherInfo>* m_inObservable;
	IObservable<SWeatherInfo>* m_outObservable;
	std::ostream& m_output;
};