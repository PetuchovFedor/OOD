#pragma once
#include "SWeatherInfo.h"
#include "Observer.h"
#include "CWindStatistic.h"

struct StatsDataGroup
{
	StatsDataGroup()
		: temperature{}
		, humidity{}
		, pressure{}
		, wind{}
	{}
	CStatisticData temperature;
	CStatisticData humidity;
	CStatisticData pressure;
	CWindStatistic wind;
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
		StatsDataGroup sdg1;
		StatsDataGroup sdg2;
		m_indicators.insert({ &in, sdg1 });
		m_indicators.insert({ &out, sdg2 });
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
		m_output << "Temp ";
		PrintStatistic(m_indicators.at(&observable).temperature);
		m_output << "Hum ";
		PrintStatistic(m_indicators.at(&observable).humidity);
		m_output << "Press ";
		PrintStatistic(m_indicators.at(&observable).pressure);
		if (&observable == m_outObservable)
		{
			m_indicators.at(&observable).wind.Update(data.wind);
			PrintWindStatistic(observable, data.wind);
			//m_indicators.at(&observable).wind.PrintWindStatistic(observable, data.wind);
		}
		m_output << "----------------" << std::endl;
		
	}

	void PrintStatistic(const CStatisticData& data)
	{
		m_output << "min: " << data.GetMin() << ", max: " << data.GetMax()
			<< ", average: " << data.GetAverage() << std::endl;
	}

	void PrintWindStatistic(IObservable<SWeatherInfo>& observable, Wind wind)
	{
		auto windStats = m_indicators.at(&observable).wind;
		auto aver = windStats.AverageWind(wind);
		m_output << "Wind: min speed " << windStats.GetMinSpeed()
			<< " max speed " << windStats.GetMaxSpeed() << " average speed "
			<< aver.second << " average direction: " << aver.first << std::endl;
	}
	std::map<IObservable<SWeatherInfo>*, StatsDataGroup> m_indicators;
	IObservable<SWeatherInfo>* m_inObservable;
	IObservable<SWeatherInfo>* m_outObservable;
	std::ostream& m_output;
};